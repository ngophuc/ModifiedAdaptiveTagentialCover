#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "DGtal/geometry/curves/FreemanChain.h"
#include <DGtal/io/readers/PointListReader.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include "myfunctions.h"
#include "testfunctions.h"

namespace po = boost::program_options;
using namespace std;
const std::string version = "1.0.1";

int main(int argc, char *argv[])
{
    /********* Prepare programme argument ********/
    po::options_description general_opt("Allowed options are: ");
    general_opt.add_options()
    ("help,h", "display this message")
    ("input,i", po::value<std::string>(), "input contour basename (without sdp extension).")
    ("imageneDir,d", po::value<std::string>(), "specify the imagene dir.")
    ("sourceImageWidth", po::value<unsigned int>(), "source image width")
    ("sourceImageHeight", po::value<unsigned int>(), "source image height")
    ("maxMT,m", po::value<double>()->default_value(20), "maximal thickness of meaningful thickness detector (default 20)")
    ("stepMT,s", po::value<double>()->default_value(1), "step of thickness for meaningful thickness detector (default 1)")
    ("output,o", po::value<std::string>()->default_value("./"), "output dir (default ./).")
    ("version,v", "display the version num")
    ("eps,e","set output with eps format");
    
    double maxMT=20.0;
    double stepMT=1;
    bool parseOK=true;
    po::variables_map vm;
    try{
        po::store(po::parse_command_line(argc, argv, general_opt), vm);
    }catch(const std::exception& ex){
        trace.info()<< "Error checking program options: "<< ex.what()<< std::endl;
        parseOK=false;
    }
    if(vm.count("version")){
        trace.info() << "version: " << version << std::endl;
        return 0;
    }
    
    po::notify(vm);
    if(vm.count("help")||argc<=1|| !parseOK || !vm.count("input") || !vm.count("imageneDir"))
    {
        trace.info()<< "Apply the adaptative tangential cover and polgonalisation." <<std::endl << "Options: "<<std::endl
        << general_opt << "\n";
        return 0;
    }
    bool verbose = false;
    bool isClosed = false;
    bool eps = vm.count("eps");
    bool displayImageCanvas = vm.count("sourceImageWidth") && vm.count("sourceImageHeight");
    
    unsigned int widthCanvas, heightCanvas = 0;
    if (displayImageCanvas){
        widthCanvas = vm["sourceImageWidth"].as<unsigned int>();
        heightCanvas  = vm["sourceImageHeight"].as<unsigned int>();
    }
    if(vm.count("maxMT"))
        maxMT=vm["maxMT"].as<double>();
    if(vm.count("stepMT"))
        stepMT=vm["stepMT"].as<double>();
    /********* Prepare programme argument ********/
    
    /********** read data ***************/
    stringstream fileContour;
    string baseInputName  = vm["input"].as<std::string>();
    string outDir  = vm["output"].as<std::string>();
    string singleName = baseInputName.substr(baseInputName.find_last_of("/")+1);
    std::string outputExt = baseInputName.substr(baseInputName.find_last_of(".")+1);
    if(outputExt != "sdp"){
        trace.error() << "input file should be sdp file" << std::endl;
        return 1;
    }
    singleName = singleName.substr(0, singleName.find_last_of("."));
    
    trace.info() << singleName << std::endl;
    string ImaGeneDIR = vm["imageneDir"].as<std::string>();
    fileContour << baseInputName ;
    vector<vector<Point> > aContour = readFile(fileContour.str().c_str());
    cout<<fileContour.str()<<endl;
    /********** read data ***************/
    
    std::stringstream instruction;
    /********** call meaningful thickness prog ***************/
    vector<vector<double> > vecMT;
    size_t it_contour=0;
    //for(size_t it_contour=0;it_contour != aContour.size();it_contour++)
    {
        cout<<"Contour "<<it_contour<<"..............................."<<endl;
        // save each part of the contour
        std::stringstream oneContour;
        oneContour << outDir << "/" << singleName << "_" << it_contour << ".sdp";
        if (!ifstream(oneContour.str()))
            writeFile(aContour.at(it_contour),oneContour.str().c_str(),false);
        
        std::stringstream noiseLevelMTFile;
        noiseLevelMTFile << outDir << "/" << singleName << "MeanThickness_" << it_contour << ".txt";
        instruction << ImaGeneDIR << "/build/tests/TestCompNoiseDetect/displayNoiseBS -srcPolygon " << oneContour.str() 
            << " 0 1 CLOSED -exportNoiseLevel "<< noiseLevelMTFile.str()
            << " -setSampling "<<maxMT<<" "<<stepMT;
        std::system(instruction.str().c_str());
        
        vector<double> oneVecMT=readMeanindfulThicknessFile(noiseLevelMTFile.str().c_str());//*sqrt(2)
        if(!isClosed)
            oneVecMT.push_back(oneVecMT.back());
        cout<<"oneVecMT size="<<oneVecMT.size()<<endl;
        
        vecMT.push_back(oneVecMT);
    }
    /********** call meaningful thickness prog ***************/
    
    /********** calculate the modified adaptive tangent cover ***************/
    std::stringstream coutFile;
    coutFile << outDir << "/" << singleName << "_Log.txt";
    if(verbose)
        freopen(coutFile.str().c_str(),"w",stdout);
    
    std::stringstream filenameBS;
    filenameBS << outDir << "/" << singleName; //MATC=Modified Adaptative Tangent Cover
    vector<vector<MaximalBlurredSegment> > tangentCorverSet;
    tangentCorverSet.push_back(vector<MaximalBlurredSegment>());
    tangentCorverSet=modifiedTangentCoverCurveDecomposition(aContour,vecMT,isClosed,filenameBS.str().c_str(),eps);
    
    if(tangentCorverSet.size()==0)
    {
        cout<<"Error tangentCorverSet.size()=0"<<endl;
        exit(-1);
    }
    //for(size_t it_contour=0; it_contour<tangentCorverSet.size(); it_contour++)
    {
        if(tangentCorverSet.at(it_contour).size()==0)
        {
            cout<<"Error tangentCorverSet.at(it_contour).size()=0"<<endl;
            exit(-1);
        }
    }
    /********** calculate the modified adaptive tangent cover ***************/
    
    /******** dominant point detection with the MATC ******/
    cout<<"MATC DP detection"<<endl;
    vector<vector<Point> > DP;
    std::stringstream filenameDP;
    filenameDP << outDir << "/" << singleName << (eps ? "_DP_MATC.eps" :"_DP_MATC.svg");
    // Version without seq of ANGLE ordering of burred segments
    DP=testDominantPointOnShape(tangentCorverSet,aContour,false,isClosed,filenameDP.str().c_str(),verbose,eps);
    
    //Find index of DP on the curve
    if(verbose)
        cout<<"File: "<<fileContour.str()<<endl;
    vector<vector<int> > indexDP;
    //for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        indexDP.push_back(vector<int>());
        for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it != DP.at(it_contour).end(); it++)
            indexDP.at(it_contour).push_back(findElement(aContour.at(it_contour),*it));
        cout<<"Errors: "; error_All(aContour.at(it_contour),DP.at(it_contour),indexDP.at(it_contour),isClosed);
    }
    if(DP.size()==0)
    {
        cout<<"Error DominantPoint.size()=0"<<endl;
        exit(-1);
    }
    //for(size_t it_contour=0; it_contour<DP.size(); it_contour++)
    {
        if(DP.at(it_contour).size()==0)
        {
            cout<<"Error DominantPoint.at(it_contour).size()=0"<<endl;
            exit(-1);
        }
    }
    /******** dominant point detection with the MATC ******/
    
    /********** selection of dominant points ***************/
    std::stringstream filenameDPnew;
    filenameDPnew << outDir << "/" << singleName << (eps ? "_DPnew_MATC.eps" :"_DPnew_MATC.svg");
    isClosed=true;
    vector<vector<Point> > newDP=testDominantPointSelection(DP,indexDP,aContour,10.0*M_PI/180.0,isClosed,filenameDPnew.str().c_str(),verbose,eps); // ISE * ANGLE
    
    if(verbose)
        cout<<"File: "<<fileContour.str()<<endl;
    vector<vector<int> > indexNewDP;
    //for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        indexNewDP.push_back(vector<int>());
        for(vector<Point>::const_iterator it=newDP.at(it_contour).begin(); it != newDP.at(it_contour).end(); it++)
            indexNewDP.at(it_contour).push_back(findElement(aContour.at(it_contour),*it));
        cout<<"Errors: "; error_All(aContour.at(it_contour),newDP.at(it_contour),indexNewDP.at(it_contour),isClosed);
    }
    
    if(newDP.size()==0)
    {
        cout<<"Error DominantPoint.size()=0"<<endl;
        exit(-1);
    }
    //for(size_t it_contour=0; it_contour<newDP.size(); it_contour++)
    {
        if(newDP.at(it_contour).size()==0)
        {
            cout<<"Error newDP.at(it_contour).size()=0"<<endl;
            exit(-1);
        }
    }
    /********** selection of dominant points ***************/
    return 0;
}

