#include "testfunctions.h"

/*************************************/
/*** Burred segments decomposition ***/
/*************************************/
vector<MaximalBlurredSegment> blurredSegmentCurveDecomposition(const vector<Point>& aContour, double thickness, bool isClosed, const char* filename, bool verbose)
{
    double mu, nu;
    PointD N;
    vector<MaximalBlurredSegment> fuzzySegmentSet;
    int idBegin=0, idEnd=0;
    //run over the points on the contours
    if(!isClosed)
    {
        for(vector<Point>::const_iterator it=aContour.begin();it!=aContour.end();it++)
        {
            idEnd=idBegin;
            AlphaThickSegmentComputer2D aSegment(thickness);
            aSegment.init(it);
            /* travel over the contour points and add to the seg */
            while(aSegment.end()!=aContour.end() && aSegment.extendFront()){idEnd++;}
            idEnd--;
            if(it==aContour.begin())
            {
                if(verbose)
                {
                    aSegment.computeParallelStripParams(mu,N,nu);
                    cout<<fuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                    cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                }
                //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                fuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
            }
            //else if(findElement(aContour,getEndPoint(aSegment))>findElement(aContour,getEndPoint(fuzzySegmentSet.back())))
            else if(idEnd>fuzzySegmentSet.back().getIdEnd())
            {
                if(verbose)
                {
                    aSegment.computeParallelStripParams(mu,N,nu);
                    cout<<fuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                    cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                }
                //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                fuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
            }
            if(getEndPoint(aSegment)==aContour.back() || it==aContour.end())
                break;
            idBegin++;
        }
    }
    else
    {
        for(vector<Point>::const_iterator it=aContour.begin();it!=aContour.end();it++)
        {
            idEnd=idBegin;
            AlphaThickSegmentComputer2D aSegment(thickness);
            aSegment.init(it);
            /* travel over the contour points and add to the seg */
            while(idBegin<aContour.size() && aSegment.extendFront(aContour.at(idEnd%aContour.size()))){idEnd++;}
            idEnd--;
            if(it==aContour.begin())
            {
                if(verbose)
                {
                    aSegment.computeParallelStripParams(mu,N,nu);
                    cout<<fuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                    cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                }
                //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                fuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
            }
            else if(idEnd>fuzzySegmentSet.back().getIdEnd())
            {
                if(verbose)
                {
                    aSegment.computeParallelStripParams(mu,N,nu);
                    cout<<fuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                    cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                }
                //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                fuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
            }
            if(getEndPoint(aSegment)==aContour.back() || it==aContour.end() || idBegin>=aContour.size())
                break;
            idBegin++;
        }
    }

    if(filename!=NULL)
    {
        Board2D aBoard;
        /* display the boundary */
        aBoard << SetMode("PointVector", "Both");
        for(vector<Point>::const_iterator it=aContour.begin(); it!=aContour.end(); it++)
            aBoard << *it;
        /* display the boundary */
        /* display the start and end points of segment */
        vector<Point> startPoint, endPoint;
        for(size_t it=0;it<fuzzySegmentSet.size();it++)
        {
            //cout<<"idBegin="<<fuzzySegmentSet.at(it).getIdBegin()<<" and idEnd="<<fuzzySegmentSet.at(it).getIdEnd()%aContour.size()<<endl;
            startPoint.push_back(aContour.at(fuzzySegmentSet.at(it).getIdBegin()));
            endPoint.push_back(aContour.at(fuzzySegmentSet.at(it).getIdEnd()%aContour.size()));
        }
        for(vector<Point>::const_iterator it=startPoint.begin(); it!=startPoint.end(); it++)
            aBoard  << SetMode("PointVector", "Both")
                    << CustomStyle((*it).className(), new CustomColors( Color(255,0,0), Color(192,0,0)))
                    << *it;
        for(vector<Point>::const_iterator it=endPoint.begin(); it!=endPoint.end(); it++)
            aBoard  << SetMode("PointVector", "Both")
                    << CustomStyle((*it).className(), new CustomColors( Color(0,255,0), Color(0,192,0)))
                    << *it;
        /* display the start and end points of segment */
        /* Display boundingbox */
        for(vector<MaximalBlurredSegment>::const_iterator it=fuzzySegmentSet.begin();it!=fuzzySegmentSet.end();it++)
            aBoard << SetMode((*it).getSegment().className(), "BoundingBox")
                   <<(*it).getSegment();
        /*
        for(size_t it=0;it<fuzzySegmentSet.size();it++)
            aBoard << SetMode(fuzzySegmentSet.at(it).getSegment().className(), "BoundingBox")
                   << fuzzySegmentSet.at(it).getSegment();
        */
        /* Display boundingbox */
        aBoard.saveSVG(filename);
    }
    return fuzzySegmentSet;
}

vector<vector<MaximalBlurredSegment> > blurredSegmentCurveDecomposition(const vector<vector<Point> >& aContour, double thickness, bool isClosed, const char* filename, bool verbose)
{
    double mu, nu;
    PointD N;
    vector<vector<MaximalBlurredSegment> > fuzzySegmentSet;
    //Calcul BS Decomposition for each part of the contour
    for(size_t it_contour=0;it_contour != aContour.size();it_contour++)
    {
        vector<MaximalBlurredSegment> oneFuzzySegmentSet;
        //run over the points on the contours
        int idBegin=0, idEnd=0;
        if(!isClosed)
        {
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin();it!=aContour.at(it_contour).end();it++)
            {
                idEnd=idBegin;
                AlphaThickSegmentComputer2D aSegment(thickness);
                aSegment.init(it);
                /* travel over the contour points and add to the seg */
                while(aSegment.end()!=aContour.at(it_contour).end() && aSegment.extendFront()){idEnd++;}
                idEnd--;
                if(it==aContour.at(it_contour).begin())
                {
                    if(verbose)
                    {
                        aSegment.computeParallelStripParams(mu,N,nu);
                        cout<<oneFuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                        cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                    }
                    //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                    oneFuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
                }
                else if(idEnd>oneFuzzySegmentSet.back().getIdEnd())
                {
                    if(verbose)
                    {
                        aSegment.computeParallelStripParams(mu,N,nu);
                        cout<<oneFuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                        cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                    }
                    //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                    oneFuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
                }
                if(getEndPoint(aSegment)==aContour.at(it_contour).back() || it==aContour.at(it_contour).end())
                    break;
                idBegin++;
            }
        }
        else
        {
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin();it!=aContour.at(it_contour).end();it++)
            {
                idEnd=idBegin;
                AlphaThickSegmentComputer2D aSegment(thickness);
                aSegment.init(it);
                /* travel over the contour points and add to the seg */
                while(idBegin<aContour.at(it_contour).size() && aSegment.extendFront(aContour.at(it_contour).at(idEnd%aContour.at(it_contour).size()))){idEnd++;}
                idEnd--;
                if(it==aContour.at(it_contour).begin())
                {
                    if(verbose)
                    {
                        aSegment.computeParallelStripParams(mu,N,nu);
                        cout<<oneFuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                        cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                    }
                    //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                    oneFuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
                }
                else if(idEnd>oneFuzzySegmentSet.back().getIdEnd())
                {
                    if(verbose)
                    {
                        aSegment.computeParallelStripParams(mu,N,nu);
                        cout<<oneFuzzySegmentSet.size()<<" with slope="<<getSlope(N[0],N[1])<<" :("<<N[0]<<" , "<<N[1]<<" , "<<mu<<" , "<<nu<<")==> ";
                        cout<<getStartPoint(aSegment)<<" and "<<getEndPoint(aSegment)<<endl;
                    }
                    //cout<<"idBegin="<<idBegin<<" and idEnd="<<idEnd<<endl;
                    oneFuzzySegmentSet.push_back(MaximalBlurredSegment(idBegin,idEnd,aSegment));
                }
                if(getEndPoint(aSegment)==aContour.at(it_contour).back() || it==aContour.at(it_contour).end() || idBegin>=aContour.at(it_contour).size())
                    break;
                idBegin++;
            }
        }
        fuzzySegmentSet.push_back(oneFuzzySegmentSet);
        //cout<<"Contour "<<it_contour<<" => Number of seg is "<<fuzzySegmentSet.back().size()<<endl;
    }

    if(filename!=NULL)
    {
        Board2D aBoard;
        //int count=0;
        /* display the boundary */
        for(size_t it_contour=0;it_contour != aContour.size();it_contour++)
        {
            /* display the boundary */
            aBoard << SetMode("PointVector", "Both");
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin(); it!=aContour.at(it_contour).end(); it++)
                aBoard << *it;
            /* display the boundary */
            /* display the start and end points of segment *
            vector<Point> startPoint, endPoint;
            for(size_t it=0;it<fuzzySegmentSet.size();it++)
            {
                cout<<"idBegin="<<fuzzySegmentSet.at(it).getIdBegin()<<" and idEnd="<<fuzzySegmentSet.at(it).getIdEnd()%aContour.at(it_contour).size()<<endl;
                startPoint.push_back(aContour.at(it_contour).at(fuzzySegmentSet.at(it).getIdBegin()));
                endPoint.push_back(aContour.at(it_contour).at(fuzzySegmentSet.at(it).getIdEnd()%aContour.at(it_contour).size()));
            }
            for(vector<Point>::const_iterator it=startPoint.begin(); it!=startPoint.end(); it++)
                aBoard  << SetMode("PointVector", "Both")
                        << CustomStyle((*it).className(), new CustomColors( Color(255,0,0), Color(192,0,0)))
                        << *it;
            for(vector<Point>::const_iterator it=endPoint.begin(); it!=endPoint.end(); it++)
                aBoard  << SetMode("PointVector", "Both")
                        << CustomStyle((*it).className(), new CustomColors( Color(0,255,0), Color(0,192,0)))
                        << *it;
           *display the start and end points of segment */
            /* Display boundingbox */
            for(vector<MaximalBlurredSegment>::const_iterator it=fuzzySegmentSet.at(it_contour).begin();it!=fuzzySegmentSet.at(it_contour).end();it++)
                aBoard << SetMode((*it).getSegment().className(), "BoundingBox")
                       <<(*it).getSegment();
            /*
            for(size_t it=0;it<fuzzySegmentSet.at(it_contour).size();it++)
                aBoard << SetMode(fuzzySegmentSet.at(it_contour).at(it).getSegment().className(), "BoundingBox")
                       << fuzzySegmentSet.at(it_contour).at(it).getSegment();
            */
            /* Display boundingbox */
        }
        aBoard.saveSVG(filename);
    }
    return fuzzySegmentSet;
}
/*************************************/
/*** Burred segments decomposition ***/
/*************************************/

/********************************************************/
/**************** Draw Multi-Thickness Cover ************/
/********************************************************/
void drawMultiThicknessCover(const vector<Point>& aContour, const vector<double>& thckVect, char* filename, bool eps)
{
    Board2D aBoard;
    /* display the boundary */
    // Creating colormap
    double maxColor= *max_element(thckVect.begin(),thckVect.end());
    HueShadeColorMap<double> hueMap(0.9, maxColor+1.0);
    string className = "PointVector/Both";
    aBoard << SetMode("PointVector", "Both");
    for (int it = 0; it < aContour.size(); it++)
    {
        double c = (double)thckVect.at(it);
        aBoard << CustomStyle(className, new CustomColors( Color::Gray, hueMap(c)))
               << aContour.at(it);
    }
    /* display the boundary */
    if(eps)
        aBoard.saveEPS(filename);
    else
        aBoard.saveSVG(filename);
}

void drawMultiThicknessCover(const vector<vector<Point> >& aContour, const vector<vector<MaximalBlurredSegment> >& meaningThicknessTangentCover, char* filename, bool eps)
{
    Board2D aBoard;
    aBoard << SetMode("PointVector", "Both");
    for(size_t it_contour=0; it_contour<aContour.size();it_contour++)
    {
        /* display the boundary */
        for(vector<Point>::const_iterator it=aContour.at(it_contour).begin(); it!=aContour.at(it_contour).end(); it++)
            aBoard << CustomStyle((*it).className(), new CustomColors( Color(0,0,0), Color(204,204,204)))
                   << *it;
        /* display the boundary */
        /* Display boundingbox */
        for(vector<MaximalBlurredSegment>::const_iterator it=meaningThicknessTangentCover.at(it_contour).begin(); it!=meaningThicknessTangentCover.at(it_contour).end(); it++)
            aBoard << SetMode((*it).getSegment().className(), "BoundingBox")
                   <<(*it).getSegment();
        /*
        for(size_t it=0;it<meaningThicknessTangentCover.at(it_contour).size();it++)
            aBoard << SetMode(meaningThicknessTangentCover.at(it_contour).at(it).getSegment().className(), "BoundingBox")
                   << meaningThicknessTangentCover.at(it_contour).at(it).getSegment();
        */
        /* Display boundingbox */
    }
    if(eps)
        aBoard.saveEPS(filename);
    else
        aBoard.saveSVG(filename);
}

void drawMultiThicknessCoverColor(const vector<vector<Point> >& aContour, size_t idContour, const vector<vector<MaximalBlurredSegment> >& meaningThicknessTangentCover, char* filename, bool eps)
{
    Board2D aBoard;
    /* display the boundary */
    //aBoard << SetMode("PointVector", "Grid");
    aBoard << SetMode("PointVector", "Both");
    for(vector<Point>::const_iterator it=aContour.at(idContour).begin(); it!=aContour.at(idContour).end(); it++)
    {
        aBoard << *it;
        //aBoard.drawLine((*it)[0], (*it)[1], (*(it+1))[0], (*(it+1))[1],10);
    }
    /*
    int idPoint=1320;//1300 1323 1320
    aBoard  << SetMode("PointVector", "Both")
            << CustomStyle("PointVector", new CustomColors(Color(255,0,0), Color(192,0,0)))
            << aContour.at(0).at(idPoint);
    aBoard.setPenColor(DGtal::Color::Red);
    aBoard.fillCircle(aContour.at(0).at(idPoint)[0], aContour.at(0).at(idPoint)[1], 1.0);
    */
    /* display the boundary */

    /* Display boundingbox */
    // Draw each segment
    string className="AlphaThickSegment/BoundingBox";
    unsigned int count=1, nbSeg=0;
    // Creating colormap
    HueShadeColorMap<double> hueMap(0.9,(double)meaningThicknessTangentCover.size()+1.0);
    for(vector<vector<MaximalBlurredSegment> >::const_iterator it=meaningThicknessTangentCover.begin(); it!=meaningThicknessTangentCover.end(); it++)
    {
        vector<MaximalBlurredSegment> fuzzySegmentSet=*it;
        //cout<<"==== "<<count<<" ===="<<endl;
        for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
        {
            //int idBegin=(*it_bis).getIdBegin();
            //int idEnd=(*it_bis).getIdEnd();
            //if(idPoint>=idBegin && idPoint<=idEnd)// && nbSeg==0
            {
                aBoard << SetMode((*it_bis).getSegment().className(), "BoundingBox")
                       << CustomStyle( className,  new CustomPenColor( hueMap(count)))
                       <<(*it_bis).getSegment();
                /*
                unsigned int pos=std::distance((*it_bis).getSegment().containerBegin(), std::find((*it_bis).getSegment().containerBegin(), (*it_bis).getSegment().containerEnd(), aContour.at(idContour).at(idPoint)));
                //auto pos=(std::find((*it_bis).getSegment().containerBegin(), (*it_bis).getSegment().containerEnd(), aContour.at(idContour).at(idPoint)))-(*it_bis).getSegment().containerBegin();
                unsigned int dssLen=std::distance((*it_bis).getSegment().containerBegin(), (*it_bis).getSegment().containerEnd());
                //unsigned int dssLen=(*it_bis).getSegment().size();
                int a=(*it_bis).getSegment().a();
                int b=(*it_bis).getSegment().b();
                int mu=(*it_bis).getSegment().mu();
                int omega=(*it_bis).getSegment().omega();
                cout<<"Seg "<<nbSeg<<": D("<<a<<","<<b<<","<<mu<<","<<omega
                    <<") with idBegin="<<idBegin<<" and idEnd="<<idEnd
                    <<" --> pos("<<idPoint<<")="<<pos<<" and dssLen="<<dssLen<<endl;
                */
                nbSeg++;
            }
            //cout<<count<<", Seg : "<<findStartElement(aContour,*it_bis)<<"--"<<findEndElement(aContour,*it_bis)<<endl;
        }
        count++;
    }
    /* Display boundingbox */
    if(eps)
        aBoard.saveEPS(filename);
    else
        aBoard.saveSVG(filename);
}
/********************************************************/
/**************** Draw Multi-Thickness Cover ************/
/********************************************************/

/*********************************************************/
/********* Adaptive Tangent Cover computation ************/
/*********************************************************/
double maxThicknessSegment(const MaximalBlurredSegment& seg, const vector<double>& thckVect)
{
    int idStart=seg.getIdBegin();
    int idEnd=seg.getIdEnd();
    double maxThickness=-1;
    for(int i=idStart; i<=idEnd; i++)
    {
        double thicknessPoint=thckVect.at(i%thckVect.size());
        if(thicknessPoint>maxThickness)
            maxThickness=thicknessPoint;
    }
    return maxThickness;
}

double statThicknessSegment(const MaximalBlurredSegment& seg, const vector<double>& thckVect)
{
    int idStart=seg.getIdBegin();
    int idEnd=seg.getIdEnd();
    vector<double> segThick;
    for(int i=idStart; i<=idEnd; i++)
    {
        double thicknessPoint=thckVect.at(i%thckVect.size());
        segThick.push_back(thicknessPoint);
    }
    
    double maxThick=-1;
    int countMax=-1, countThick=-1;
    for(vector<double>::const_iterator it=segThick.begin(); it!=segThick.end(); it++)
    {
        countThick=std::count(segThick.begin(), segThick.end(), *it);
        if(countThick>countMax)
        {
            maxThick=*it;
            countMax=countThick;
        }
    }
    return maxThick;
}
vector<vector<MaximalBlurredSegment> > adaptiveTangentCoverCurveDecomposition(const vector<vector<Point> >& aContour, const vector<vector<double> >& vecMT, bool isClosed, const char* filename, bool eps)
{
    char fileAdaptMT[FILENAMESIZE];
    vector<vector<MaximalBlurredSegment> > adaptiveTangentCover;
    //Calcul ATC for each part of the contour
    for(size_t it_contour=0;it_contour != aContour.size();it_contour++)
    {
        //1. Find vector of thickness element
        vector<double> meaningThicknessElement;
        meaningThicknessElement.push_back(vecMT.at(it_contour).front());
        for(vector<double>::const_iterator it=vecMT.at(it_contour).begin()+1; it!=vecMT.at(it_contour).end(); it++)
        {
            double m=(*it);
            if(std::find(meaningThicknessElement.begin(), meaningThicknessElement.end(),m)==meaningThicknessElement.end())
                meaningThicknessElement.push_back(m);
        }
        std::sort(meaningThicknessElement.begin(),meaningThicknessElement.end(),sort_increase);
        for(vector<double>::const_iterator it=meaningThicknessElement.begin(); it!=meaningThicknessElement.end(); it++)
            cout<<"meaningThicknessElement : "<<*it<<endl;
        if(filename != NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_ATC_Step1_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_ATC_Step1_%zu.svg",filename,it_contour);
            drawMultiThicknessCover(aContour.at(it_contour),vecMT.at(it_contour),fileAdaptMT,eps);
        }
        
        //2. Compute different thickness tangent covers(blurred segments)
        vector<vector<MaximalBlurredSegment> > meaningThicknessTangentCover(meaningThicknessElement.size());
        int index=0;
        for(vector<double>::const_iterator it=meaningThicknessElement.begin(); it!=meaningThicknessElement.end(); it++)
        {
            double thickness=(*it)*sqrt(2);
            //double thickness=(*it);
            vector<MaximalBlurredSegment> fuzzySegmentSet=blurredSegmentCurveDecomposition(aContour.at(it_contour),thickness,isClosed,NULL,false);
            cout<<"===> Num of seg decomposed is "<<fuzzySegmentSet.size()<<endl;
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
                meaningThicknessTangentCover[index].push_back(*it_bis);
            index++;
        }

        //3. Update thickness of points with tangent covers
        vector<double> vecMTmodified;
        for(vector<double>::const_iterator it=vecMT.at(it_contour).begin(); it!=vecMT.at(it_contour).end(); it++)
            vecMTmodified.push_back(*it);
        //for(vector<vector<MaximalBlurredSegment> >::const_iterator it=meaningThicknessTangentCover.begin(); it!=meaningThicknessTangentCover.end(); it++)
        for(int it=(int)meaningThicknessTangentCover.size()-1; it>=0; it--)
        {
            vector<MaximalBlurredSegment> fuzzySegmentSet=meaningThicknessTangentCover.at(it);//*it;
            double thickness=meaningThicknessElement.at(it);
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
            {
                int idStart=(*it_bis).getIdBegin();
                int idEnd=(*it_bis).getIdEnd();
                if(idStart!=-1 && idEnd!=-1)
                {
                    double maxThickness=maxThicknessSegment(*it_bis, vecMT.at(it_contour));
                    for(int i=idStart; i<=idEnd; i++) //FIXME : idStart+1 => justify !!!
                    {
                        if(maxThickness==thickness)//vecMTmodified.at(i)<maxThickness &&
                            vecMTmodified.at(i%aContour.at(it_contour).size())=maxThickness;
                    }
                }
                else
                    cout<<"negatif"<<endl;
            }
        }
        if(filename != NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_ATC_Step3_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_ATC_Step3_%zu.svg",filename,it_contour);
            drawMultiThicknessCover(aContour.at(it_contour),vecMTmodified,fileAdaptMT,eps);
        }

        //4. Travel over the tangent covers and select the segments w.r.t the associated thickness of points
        vector<vector<MaximalBlurredSegment> > adaptiveMeaningThicknessTangentCover;
        int idCover=0;
        for(vector<vector<MaximalBlurredSegment> >::const_iterator it=meaningThicknessTangentCover.begin(); it!=meaningThicknessTangentCover.end(); it++)
        {
            adaptiveMeaningThicknessTangentCover.push_back(vector<MaximalBlurredSegment>());
            vector<MaximalBlurredSegment> fuzzySegmentSet=*it;
            vector<MaximalBlurredSegment> AdaptiveFuzzySegmentSet;
            int idSeg=0;
            double thickness=meaningThicknessElement.at(idCover);
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
            {
                int idStart=(*it_bis).getIdBegin();
                int idEnd=(*it_bis).getIdEnd();
                if(idStart!=-1 && idEnd!=-1)
                {
                    bool isGoodMTmodif=false, isGoodMT=false;//true
                    for(int i=idStart; i<=idEnd; i++)
                    {
                        double thicknessMT=vecMT.at(it_contour).at(i%aContour.at(it_contour).size()); //all elt have same meaningful thickness value(dont contain other meaningful thickness)
                        if(thicknessMT==thickness)
                            isGoodMT=true;
                        double thicknessMTmodif=vecMTmodified.at(i%aContour.at(it_contour).size());
                        if(thicknessMTmodif==thickness) //there exist at least one elt in modif having meaningful thickness value
                            isGoodMTmodif=true;
                    }
                    if(isGoodMTmodif && isGoodMT)
                        AdaptiveFuzzySegmentSet.push_back(*it_bis);
                }
                idSeg++;
            }
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=AdaptiveFuzzySegmentSet.begin();it_bis!=AdaptiveFuzzySegmentSet.end();it_bis++)
                adaptiveMeaningThicknessTangentCover[idCover].push_back(*it_bis);

            idCover++;
        }

        // 4 cont. : selection of Seg
        for(vector<vector<MaximalBlurredSegment> >::reverse_iterator it1=adaptiveMeaningThicknessTangentCover.rbegin(); it1!=adaptiveMeaningThicknessTangentCover.rend(); ++it1)
        {
            vector<MaximalBlurredSegment>& segmentSet1=*it1;
            for(vector<vector<MaximalBlurredSegment> >::reverse_iterator it2=it1+1; it2!=adaptiveMeaningThicknessTangentCover.rend(); ++it2)
            {
                vector<MaximalBlurredSegment>& segmentSet2=*it2;
                for(vector<MaximalBlurredSegment>::iterator itSeg1=segmentSet1.begin();itSeg1!=segmentSet1.end();itSeg1++)
                {
                    //get idStart and idEnd of current seg
                    int idCurrentStart=(*itSeg1).getIdBegin();
                    int idCurrentEnd=(*itSeg1).getIdEnd();

                    for(vector<MaximalBlurredSegment>::iterator itSeg2=segmentSet2.begin();itSeg2!=segmentSet2.end();itSeg2++)
                    {
                        int idStart=(*itSeg2).getIdBegin();
                        int idEnd=(*itSeg2).getIdEnd();
                        if(idCurrentStart<=idStart && idCurrentEnd>=idEnd)
                        {
                            //cout<<"SUPP : CurrentSeg=("<<idCurrentStart<<" , "<<idCurrentEnd<<") -- Seg("<<idStart<<" , "<<idEnd<<")"<<endl;
                            segmentSet2.erase(itSeg2);
                            itSeg2--;
                        }
                    }
                }
            }
        }

        //5. Reorder the multi-thickness tangent cover
        vector<MaximalBlurredSegment> oneAdaptiveTangentCover;
        int seg=0,nbSeg=0;
        vector<int> idThicknessCover; //stock idSeg of the last seg at idThicknessCover
        for(size_t it=0; it<meaningThicknessElement.size();it++)
            idThicknessCover.push_back(0);
        for(size_t it=0; it<adaptiveMeaningThicknessTangentCover.size(); it++)
            nbSeg+=(adaptiveMeaningThicknessTangentCover.at(it)).size();

        while(seg<nbSeg)
        {
            int idMinStart,idMinEnd;
            if(isClosed)
            {
                idMinStart=2*aContour.at(it_contour).size();
                idMinEnd=2*aContour.at(it_contour).size();//x2 : due to the closed curve can have ending index over contour.size()
            }
            else
            {
                idMinStart=aContour.at(it_contour).size();
                idMinEnd=aContour.at(it_contour).size();
            }
            int idMin=-1, idSeg=-1;
            //scan adaptiveMeaningThicknessTangentCover
            for(size_t it=0; it<adaptiveMeaningThicknessTangentCover.size(); it++)//thickness level=it
            {
                ///vector<Point> extremitySeg;
                //current seg of thickness level idThicknessCover.at(i)
                int idCurrentSeg=idThicknessCover.at(it);
                if(idCurrentSeg<(adaptiveMeaningThicknessTangentCover.at(it)).size())
                {
                    //get idStart and idEnd of seg
                    int idCurrentStart=(adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg).getIdBegin();
                    int idCurrentEnd=(adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg).getIdEnd();
                    ///extremitySeg.push_back(Point(idStart,idEnd));
                    //cout<<"idCurrentStart="<<idCurrentStart<<" and idCurrentEnd="<<idCurrentEnd<<"; idMinStart="<<idMinStart<<" and idMinEnd="<<idMinEnd<<endl;
                    if(idThicknessCover.at(it)<(adaptiveMeaningThicknessTangentCover.at(it)).size())
                    {
                        //find min idCurrentStart
                        if(idMinStart==idCurrentStart && idMinEnd<idCurrentEnd)
                        {
                            if(idThicknessCover.at(it)<(int)(adaptiveMeaningThicknessTangentCover.at(it)).size()-1)
                            {
                                idThicknessCover.at(idMin)=idThicknessCover.at(idMin)+1;
                                seg++;
                            }
                            idSeg=idCurrentSeg;
                            idMin=it;
                            idMinStart=idCurrentStart;
                            idMinEnd=idCurrentEnd;
                            ///extremitySeg.push_back(Point(idCurrentStart,idCurrentEnd));
                        }
                        //if(idMinStart>=idCurrentStart && idMinEnd>=idCurrentEnd)
                        else if(idMinStart>idCurrentStart && idMinEnd>=idCurrentEnd)
                        {
                            idSeg=idCurrentSeg;
                            idMin=it;
                            idMinStart=idCurrentStart;
                            idMinEnd=idCurrentEnd;
                            ///extremitySeg.push_back(Point(idCurrentStart,idCurrentEnd));
                        }
                    }
                }
            }
            oneAdaptiveTangentCover.push_back((adaptiveMeaningThicknessTangentCover.at(idMin)).at(idSeg));
            idThicknessCover.at(idMin)=idThicknessCover.at(idMin)+1;
            seg++;
        }
        if(filename!=NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_ATC_Step4_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_ATC_Step4_%zu.svg",filename,it_contour);
            drawMultiThicknessCoverColor(aContour,it_contour,adaptiveMeaningThicknessTangentCover,fileAdaptMT,eps);
        }
        adaptiveTangentCover.push_back(oneAdaptiveTangentCover);
    }

    if(filename!=NULL)
    {
        if(eps)
                sprintf(fileAdaptMT,"%s_ATC.eps",filename);
        else
            sprintf(fileAdaptMT,"%s_ATC.svg",filename);
        drawMultiThicknessCover(aContour,adaptiveTangentCover,fileAdaptMT,eps);
    }
    return adaptiveTangentCover;
}
/*********************************************************/
/********* Adaptive Tangent Cover computation ************/
/*********************************************************/

/*********************************************************/
/******** Modified Tangent Cover computation **********/
/*********************************************************/
vector<vector<MaximalBlurredSegment> > modifiedTangentCoverCurveDecomposition(const vector<vector<Point> >& aContour, const vector<vector<double> >& vecMT, bool isClosed, const char* filename, bool eps)
{
    char fileAdaptMT[FILENAMESIZE];
    vector<vector<MaximalBlurredSegment> > adaptiveTangentCover;
    //Calcul ATC for each part of the contour
    for(size_t it_contour=0;it_contour != aContour.size();it_contour++)
    {
        //1. Find vector of thickness element
        vector<double> meaningThicknessElement;
        meaningThicknessElement.push_back(vecMT.at(it_contour).front());
        for(vector<double>::const_iterator it=vecMT.at(it_contour).begin()+1; it!=vecMT.at(it_contour).end(); it++)
        {
            double m=(*it);
            if(std::find(meaningThicknessElement.begin(), meaningThicknessElement.end(),m)==meaningThicknessElement.end())
                meaningThicknessElement.push_back(m);
        }
        std::sort(meaningThicknessElement.begin(),meaningThicknessElement.end(),sort_increase);
        for(vector<double>::const_iterator it=meaningThicknessElement.begin(); it!=meaningThicknessElement.end(); it++)
            cout<<"meaningThicknessElement : "<<*it<<endl;
        if(filename != NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_MATC_Step1_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_MATC_Step1_%zu.svg",filename,it_contour);
            drawMultiThicknessCover(aContour.at(it_contour),vecMT.at(it_contour),fileAdaptMT,eps);
        }
        
        //2. Compute different thickness tangent covers(blurred segments)
        vector<vector<MaximalBlurredSegment> > meaningThicknessTangentCover(meaningThicknessElement.size());
        int index=0;
        for(vector<double>::const_iterator it=meaningThicknessElement.begin(); it!=meaningThicknessElement.end(); it++)
        {
            double thickness=(*it)*sqrt(2);
            //double thickness=(*it);
            vector<MaximalBlurredSegment> fuzzySegmentSet=blurredSegmentCurveDecomposition(aContour.at(it_contour),thickness,isClosed,NULL,false);
            cout<<"===> Num of seg decomposed is "<<fuzzySegmentSet.size()<<endl;
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
                meaningThicknessTangentCover[index].push_back(*it_bis);
            index++;
        }
        
        //3. Update thickness of points with tangent covers
        vector<double> vecMTmodified;
        for(vector<double>::const_iterator it=vecMT.at(it_contour).begin(); it!=vecMT.at(it_contour).end(); it++)
            vecMTmodified.push_back(*it);
        //for(vector<vector<MaximalBlurredSegment> >::const_iterator it=meaningThicknessTangentCover.begin(); it!=meaningThicknessTangentCover.end(); it++)
        for(int it=(int)meaningThicknessTangentCover.size()-1; it>=0; it--)
        {
            vector<MaximalBlurredSegment> fuzzySegmentSet=meaningThicknessTangentCover.at(it);//*it;
            double thickness=meaningThicknessElement.at(it);
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
            {
                int idStart=(*it_bis).getIdBegin();
                int idEnd=(*it_bis).getIdEnd();
                if(idStart!=-1 && idEnd!=-1)
                {
                    //double maxThickness=maxThicknessSegment(*it_bis, vecMT.at(it_contour));
                    double maxThickness=statThicknessSegment(*it_bis, vecMT.at(it_contour));
                    for(int i=idStart; i<=idEnd; i++) //FIXME : idStart+1 => justify !!!
                    {
                        if(maxThickness==thickness)//vecMTmodified.at(i)<maxThickness &&
                            vecMTmodified.at(i%aContour.at(it_contour).size())=maxThickness;
                    }
                }
                else
                    cout<<"negatif"<<endl;
            }
        }
        if(filename != NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_MATC_Step3_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_MATC_Step3_%zu.svg",filename,it_contour);
            drawMultiThicknessCover(aContour.at(it_contour),vecMTmodified,fileAdaptMT,eps);
        }
        
        //4. Travel over the tangent covers and select the segments w.r.t the associated thickness of points
        vector<vector<MaximalBlurredSegment> > adaptiveMeaningThicknessTangentCover;
        int idCover=0;
        for(vector<vector<MaximalBlurredSegment> >::const_iterator it=meaningThicknessTangentCover.begin(); it!=meaningThicknessTangentCover.end(); it++)
        {
            adaptiveMeaningThicknessTangentCover.push_back(vector<MaximalBlurredSegment>());
            vector<MaximalBlurredSegment> fuzzySegmentSet=*it;
            vector<MaximalBlurredSegment> AdaptiveFuzzySegmentSet;
            int idSeg=0;
            double thickness=meaningThicknessElement.at(idCover);
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=fuzzySegmentSet.begin();it_bis!=fuzzySegmentSet.end();it_bis++)
            {
                int idStart=(*it_bis).getIdBegin();
                int idEnd=(*it_bis).getIdEnd();
                if(idStart!=-1 && idEnd!=-1)
                {
                    bool isGoodMTmodif=false, isGoodMT=false;//true
                    for(int i=idStart; i<=idEnd; i++)
                    {
                        double thicknessMT=vecMT.at(it_contour).at(i%aContour.at(it_contour).size()); //all elt have same meaningful thickness value(dont contain other meaningful thickness)
                        if(thicknessMT==thickness)
                            isGoodMT=true;
                        double thicknessMTmodif=vecMTmodified.at(i%aContour.at(it_contour).size());
                        if(thicknessMTmodif==thickness) //there exist at least one elt in modif having meaningful thickness value
                            isGoodMTmodif=true;
                    }
                    if(isGoodMTmodif && isGoodMT)
                        AdaptiveFuzzySegmentSet.push_back(*it_bis);
                }
                idSeg++;
            }
            for(vector<MaximalBlurredSegment>::const_iterator it_bis=AdaptiveFuzzySegmentSet.begin();it_bis!=AdaptiveFuzzySegmentSet.end();it_bis++)
                adaptiveMeaningThicknessTangentCover[idCover].push_back(*it_bis);
            
            idCover++;
        }
        
        // 4 cont. : selection of Seg
        for(vector<vector<MaximalBlurredSegment> >::reverse_iterator it1=adaptiveMeaningThicknessTangentCover.rbegin(); it1!=adaptiveMeaningThicknessTangentCover.rend(); ++it1)
        {
            vector<MaximalBlurredSegment>& segmentSet1=*it1;
            for(vector<vector<MaximalBlurredSegment> >::reverse_iterator it2=it1+1; it2!=adaptiveMeaningThicknessTangentCover.rend(); ++it2)
            {
                vector<MaximalBlurredSegment>& segmentSet2=*it2;
                for(vector<MaximalBlurredSegment>::iterator itSeg1=segmentSet1.begin();itSeg1!=segmentSet1.end();itSeg1++)
                {
                    //get idStart and idEnd of current seg
                    int idCurrentStart=(*itSeg1).getIdBegin();
                    int idCurrentEnd=(*itSeg1).getIdEnd();
                    
                    for(vector<MaximalBlurredSegment>::iterator itSeg2=segmentSet2.begin();itSeg2!=segmentSet2.end();itSeg2++)
                    {
                        int idStart=(*itSeg2).getIdBegin();
                        int idEnd=(*itSeg2).getIdEnd();
                        if(idCurrentStart<=idStart && idCurrentEnd>=idEnd)
                        {
                            //cout<<"SUPP : CurrentSeg=("<<idCurrentStart<<" , "<<idCurrentEnd<<") -- Seg("<<idStart<<" , "<<idEnd<<")"<<endl;
                            segmentSet2.erase(itSeg2);
                            itSeg2--;
                        }
                    }
                }
            }
        }
        
        //5. Reorder the multi-thickness tangent cover
        vector<MaximalBlurredSegment> oneAdaptiveTangentCover;
        int seg=0,nbSeg=0;
        vector<int> idThicknessCover; //stock idSeg of the last seg at idThicknessCover
        for(size_t it=0; it<meaningThicknessElement.size();it++)
            idThicknessCover.push_back(0);
        for(size_t it=0; it<adaptiveMeaningThicknessTangentCover.size(); it++)
            nbSeg+=(adaptiveMeaningThicknessTangentCover.at(it)).size();
        
        while(seg<nbSeg)
        {
            int idMinStart,idMinEnd;
            if(isClosed)
            {
                idMinStart=2*aContour.at(it_contour).size();
                idMinEnd=2*aContour.at(it_contour).size();//x2 : due to the closed curve can have ending index over contour.size()
            }
            else
            {
                idMinStart=aContour.at(it_contour).size();
                idMinEnd=aContour.at(it_contour).size();
            }
            int idMin=-1, idSeg=-1;
            //scan adaptiveMeaningThicknessTangentCover
            for(size_t it=0; it<adaptiveMeaningThicknessTangentCover.size(); it++)//thickness level=it
            {
                ///vector<Point> extremitySeg;
                //current seg of thickness level idThicknessCover.at(i)
                int idCurrentSeg=idThicknessCover.at(it);
                if(idCurrentSeg<(adaptiveMeaningThicknessTangentCover.at(it)).size())
                {
                    //get idStart and idEnd of seg
                    int idCurrentStart=(adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg).getIdBegin();
                    int idCurrentEnd=(adaptiveMeaningThicknessTangentCover.at(it)).at(idCurrentSeg).getIdEnd();
                    ///extremitySeg.push_back(Point(idStart,idEnd));
                    //cout<<"idCurrentStart="<<idCurrentStart<<" and idCurrentEnd="<<idCurrentEnd<<"; idMinStart="<<idMinStart<<" and idMinEnd="<<idMinEnd<<endl;
                    if(idThicknessCover.at(it)<(adaptiveMeaningThicknessTangentCover.at(it)).size())
                    {
                        //find min idCurrentStart
                        if(idMinStart==idCurrentStart && idMinEnd<idCurrentEnd)
                        {
                            if(idThicknessCover.at(it)<(int)(adaptiveMeaningThicknessTangentCover.at(it)).size()-1)
                            {
                                idThicknessCover.at(idMin)=idThicknessCover.at(idMin)+1;
                                seg++;
                            }
                            idSeg=idCurrentSeg;
                            idMin=it;
                            idMinStart=idCurrentStart;
                            idMinEnd=idCurrentEnd;
                            ///extremitySeg.push_back(Point(idCurrentStart,idCurrentEnd));
                        }
                        //if(idMinStart>=idCurrentStart && idMinEnd>=idCurrentEnd)
                        else if(idMinStart>idCurrentStart && idMinEnd>=idCurrentEnd)
                        {
                            idSeg=idCurrentSeg;
                            idMin=it;
                            idMinStart=idCurrentStart;
                            idMinEnd=idCurrentEnd;
                            ///extremitySeg.push_back(Point(idCurrentStart,idCurrentEnd));
                        }
                    }
                }
            }
            oneAdaptiveTangentCover.push_back((adaptiveMeaningThicknessTangentCover.at(idMin)).at(idSeg));
            idThicknessCover.at(idMin)=idThicknessCover.at(idMin)+1;
            seg++;
        }
        if(filename!=NULL)
        {
            if(eps)
                sprintf(fileAdaptMT,"%s_MATC_Step4_%zu.eps",filename,it_contour);
            else
                sprintf(fileAdaptMT,"%s_MATC_Step4_%zu.svg",filename,it_contour);
            drawMultiThicknessCoverColor(aContour,it_contour,adaptiveMeaningThicknessTangentCover,fileAdaptMT,eps);
        }
        adaptiveTangentCover.push_back(oneAdaptiveTangentCover);
    }
    
    if(filename!=NULL)
    {
        if(eps)
            sprintf(fileAdaptMT,"%s_MATC.eps",filename);
        else
            sprintf(fileAdaptMT,"%s_MATC.svg",filename);
        drawMultiThicknessCover(aContour,adaptiveTangentCover,fileAdaptMT,eps);
    }
    return adaptiveTangentCover;
}
/*********************************************************/
/******** Modified Tangent Cover computation **********/
/*********************************************************/

/************************************/
/**** Dominant points detections ****/
/************************************/
vector<vector<Point> > testDominantPointOnShape(const vector<vector<MaximalBlurredSegment> >& fuzzySegmentSet, const vector<vector<Point> >& aContour, bool isSymmetry, bool isClosed, const char* filename, bool verbose, bool eps)
{
    vector<vector<Point> > vecDP, vecExtremityPoint, vecCommonPoint;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        int p=1, q=0, Eq=0, Bp=0, m=fuzzySegmentSet.at(it_contour).size();
        vector<Point> pile;
        while(p<m && q<m && Bp>=0 && Eq>=0)
        {
            Bp=fuzzySegmentSet.at(it_contour)[p].getIdBegin();
            Eq=fuzzySegmentSet.at(it_contour)[q].getIdEnd();//FIXME: %contour.size()
            while(Eq>=Bp && p<m && q<m && Bp>=0 && Eq>=0)
            {
                Bp=fuzzySegmentSet.at(it_contour)[p].getIdBegin();
                Eq=fuzzySegmentSet.at(it_contour)[q].getIdEnd();//FIXME: %contour.size()
                if(verbose && Eq>=Bp)
                    cout<<"Pair segment :("<<q<<","<<p<<")and Pair points :("<<Bp<<","<<Eq<<")"<<endl;
                p++;
            }
            if(Eq<Bp && q<p-1) /* Phuc: (add cond) q<p-1 */
            {
                p--;//when out of loop => Eq<Bp
                pile.push_back(Point(q,p-1));
                if(verbose)
                    cout<<"Pile :("<<q<<" , "<<p-1<<")"<<endl<<endl;
                q=p-1;
            }
            else
            {
                if(p>=m || q>=m)
                {
                    pile.push_back(Point(q,p-1));
                    if(verbose)
                        cout<<"Pile :("<<q<<" , "<<p-1<<")"<<endl<<endl;
                }
                else
                    q=p;
            }
        }
        /* pile construction */

        /* calcul point dominant */
        vector<Point> DP, extremityPoint, commonPoint;
        for(vector<Point>::const_iterator it=pile.begin(); it!=pile.end(); it++)
        {
            q=(*it)[0];
            p=(*it)[1];
            //find point with max(local) curvature
            int indexB=fuzzySegmentSet.at(it_contour)[p].getIdBegin();
            int indexE=fuzzySegmentSet.at(it_contour)[q].getIdEnd();//FIXME: %contour.size()
            int indexC=indexB;
            int indexBi=fuzzySegmentSet.at(it_contour)[q].getIdBegin();
            int indexEi=fuzzySegmentSet.at(it_contour)[p].getIdEnd();//FIXME: %contour.at(it_contour).size()
            if(verbose)
                cout<<"angle at "<<indexC<<" is "<<(acuteAngle(aContour.at(it_contour).at(indexBi),aContour.at(it_contour).at(indexC),aContour.at(it_contour).at(indexEi%aContour.at(it_contour).size()))*180/M_PI)<<endl;

            for(int i=indexB+1; i<=indexE; i++)//for each common zone
            {
                int minIndex=0;//for symmetry angle calculation
                int modIndex=i%aContour.at(it_contour).size();//index of current point
                if(isSymmetry)
                {
                    /*
                    minIndex=fabs(modIndex-indexB)<fabs(modIndex-indexE) ? fabs(modIndex-indexB) : fabs(modIndex-indexE);
                    if(fabs(acuteAngle(aContour.at(it_contour).at(modIndex),aContour.at(it_contour).at(modIndex-minIndex),aContour.at(it_contour).at(modIndex+minIndex))) <=
                            fabs(acuteAngle(aContour.at(it_contour).at(indexC),aContour.at(it_contour).at(modIndex-minIndex),aContour.at(it_contour).at(modIndex+minIndex))))
                        indexC=modIndex;
                    */
                    cout<<"comming soon..."<<endl;
                }
                else
                {
                    if(fabs(acuteAngle(aContour.at(it_contour).at(indexBi),aContour.at(it_contour).at(modIndex),aContour.at(it_contour).at(indexEi%aContour.at(it_contour).size()))) <=
                            fabs(acuteAngle(aContour.at(it_contour).at(indexBi),aContour.at(it_contour).at(indexC),aContour.at(it_contour).at(indexEi%aContour.at(it_contour).size()))))
                        indexC=modIndex;
                }
                if(verbose)
                    cout<<"angle at "<<modIndex<<" is "<<(acuteAngle(aContour.at(it_contour).at(indexBi-minIndex),aContour.at(it_contour).at(modIndex),aContour.at(it_contour).at(indexEi%aContour.at(it_contour).size()+minIndex))*180/M_PI)<<endl;
            }
            if(verbose)
                cout<<" ==> max local curvature at "<<aContour.at(it_contour)[indexC]<<endl;

            if(DP.empty() || aContour.at(it_contour)[indexC]!=DP.back())
            {
                DP.push_back(aContour.at(it_contour)[indexC]);
                extremityPoint.push_back(aContour.at(it_contour)[indexB]);
                extremityPoint.push_back(aContour.at(it_contour)[indexE%aContour.at(it_contour).size()]);
                for(size_t i=indexB; i<=indexE; i++)
                    commonPoint.push_back(aContour.at(it_contour)[i%aContour.at(it_contour).size()]);
            }
        }
        if(!isClosed)//consider the first and last elt of the contour as a DP
        {
            DP.insert(DP.begin(),aContour.at(it_contour).front());
            DP.insert(DP.end(),aContour.at(it_contour).back());
        }
        cout<<"===> Num of dominant points is "<<DP.size()<<endl;
        /* calcul point dominant */

        vecDP.push_back(DP);
        vecExtremityPoint.push_back(extremityPoint);
        vecCommonPoint.push_back(commonPoint);
    }

    if(filename!=NULL)
    {
        Board2D aBoard;
        for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        {
            /* Display the boundary */
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin(); it!=aContour.at(it_contour).end(); it++)
                aBoard << SetMode("PointVector", "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(0,0,0), Color(204,204,204)))
                       << *it;

            aBoard << SetMode("PointVector", "Both")
                   << CustomStyle(aContour.at(it_contour).front().className(), new CustomColors(Color(0,255,0), Color(0,92,0)))
                   << aContour.at(it_contour).front();

            /* Display the boundary */
            /* Display points in common zone *
            for(vector<Point>::const_iterator it=vecCommonPoint.at(it_contour).begin(); it!=vecCommonPoint.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                       << CustomStyle((*it).className(), new CustomColors(Color(0,255,0), Color(0,92,0)))
                       <<(*it);
            /* Display points in common zone */
            /* Display dominant point */
            for(vector<Point>::const_iterator it=vecDP.at(it_contour).begin(); it!=vecDP.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(255,0,0), Color(192,0,0)))
                       <<(*it);
            /* Display dominant point */
            /* Display the segments by DP */
            aBoard.setPenColor(Color(0, 0, 255));
            aBoard.setLineWidth(10.0);
            //aBoard.drawLine(aContour.at(it_contour).front()[0],aContour.at(it_contour).front()[1],DP.front()[0],DP.front()[1]);
            for(vector<Point>::const_iterator it=vecDP.at(it_contour).begin(); it+1!=vecDP.at(it_contour).end(); it++)
                aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
            if(isClosed)
                aBoard.drawLine(vecDP.at(it_contour).front()[0],vecDP.at(it_contour).front()[1],vecDP.at(it_contour).back()[0],vecDP.at(it_contour).back()[1]);
            /* Display the segments by DP */
        }
        if(eps)
            aBoard.saveEPS(filename);
        else
            aBoard.saveSVG(filename);
    }
    return vecDP;
}
/************************************/
/**** Dominant points detections ****/
/************************************/

/***********************************/
/**** Dominant points selection ****/
/***********************************/
/* Selection by max error criterion */
vector<vector<Point> > testDominantPointSelection(const vector<vector<Point> >& DP, const vector<vector<int> >& indexDP, const vector<vector<Point> >& aContour, bool isClosed, const char* filename, bool verbose, bool eps)
{
    vector<vector<Point> > vecSelectedDP;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        vector<Point> selectedDP;
        for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it!=DP.at(it_contour).end(); it++)
            selectedDP.push_back(*it);
        vector<int> indexSelectedDP;
        for(vector<int>::const_iterator it=indexDP.at(it_contour).begin(); it!=indexDP.at(it_contour).end(); it++)
            indexSelectedDP.push_back(*it);
        vector<double> iseDP;
        double ise_prev, ise=error_ISE(aContour.at(it_contour),selectedDP,indexSelectedDP,isClosed);
        double cr=error_CR(aContour.at(it_contour),selectedDP);
        double error_prev, error;
        error_prev=error=(cr*cr)/ise;
        int lastIndex=-1,lastIndexSelectedDP=-1;
        Point lastSelectedDP;

        do{
            error_prev=error;
            ise_prev=ise;
            for(size_t it=1; it+1<selectedDP.size(); it++)
            {
                double ise=0.0, d=0.0, angle=0.0;
                int indexStart=indexSelectedDP.at(it-1);
                int indexEnd=indexSelectedDP.at(it+1);
                if(indexStart<0 || indexEnd<0)
                    cout<<"Pb in error_ISE index of DP"<<endl;
                if(isClosed && indexStart>indexEnd)//in case of closed cuves
                    indexEnd=indexEnd+aContour.at(it_contour).size();
                for(int index=indexStart+1; index<indexEnd; index++)
                {
                    d=distancePointSegment(aContour.at(it_contour).at(index%aContour.at(it_contour).size()),
                                           aContour.at(it_contour).at(indexStart),
                                           aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                    ise += d*d;
                }
                angle=acuteAngle(aContour.at(it_contour).at(indexStart),
                                 aContour.at(it_contour).at(indexSelectedDP.at(it)%aContour.at(it_contour).size()),
                                 aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                if(verbose)
                    cout<<" DP "<<it<<" : ise="<<ise<<", and angle="<<angle<<endl;
                iseDP.push_back(ise/angle);
            }
            iseDP.insert(iseDP.begin(),(int)aContour.at(it_contour).size()*aContour.at(it_contour).size());//Keep the fist point as DP
            if(!isClosed)//Keep the last point as DP
                iseDP.push_back((int)aContour.at(it_contour).size()*aContour.at(it_contour).size());
            else//isClosed => calcule ISE of the last point
            {
                double ise=0.0, d=0.0, angle=0.0;
                int indexStart=indexSelectedDP.at((int)indexSelectedDP.size()-2);
                //int indexEnd=aContour.at(it_contour).size();
                int indexEnd=indexSelectedDP.front()+aContour.at(it_contour).size();
                int it=(int)indexSelectedDP.size()-1;
                //cout<<"it="<<it<<" : indexStart="<<indexStart<<", indexEnd="<<indexEnd<<endl;
                for(int index=indexStart+1; index<indexEnd; index++)
                {
                    /*
                    d=distancePointSegment(aContour.at(it_contour).at(index),
                                           aContour.at(it_contour).at(indexStart),
                                           aContour.at(it_contour).front());

                    */
                    d=distancePointSegment(aContour.at(it_contour).at(index%aContour.at(it_contour).size()),
                                           aContour.at(it_contour).at(indexStart),
                                           aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));

                    ise += d*d;
                }
                /*
                angle=acuteAngle(aContour.at(it_contour).at(indexStart),
                                 aContour.at(it_contour).at(indexSelectedDP.at(it)),
                                 aContour.at(it_contour).front());
                */
                angle=acuteAngle(aContour.at(it_contour).at(indexStart),
                                 aContour.at(it_contour).at(indexSelectedDP.at(it)%aContour.at(it_contour).size()),
                                 aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));

                if(verbose)
                    cout<<" DP "<<selectedDP.size()<<" : ise="<<ise<<", and angle="<<angle<<endl;
                iseDP.push_back(ise/angle);
            }

            vector<int> indexOrderedDP=absSortIndex(iseDP,true);
            if(verbose)
                for(vector<int>::const_iterator it=indexOrderedDP.begin(); it!=indexOrderedDP.end(); it++)
                    cout<<"ise of DP "<<*it<< " : "<<iseDP.at(*it)<<endl;

            /* erease the first elt */
            lastIndex=indexOrderedDP.front();
            lastSelectedDP=selectedDP.at(lastIndex);
            lastIndexSelectedDP=indexSelectedDP.at(lastIndex);
            selectedDP.erase(selectedDP.begin()+lastIndex);//indexOrderedDP.front()
            indexSelectedDP.erase(indexSelectedDP.begin()+lastIndex);//indexOrderedDP.front()
            iseDP.clear();
            /* erease the first elt */

            /* update errors */
            ise=error_ISE(aContour.at(it_contour),selectedDP,indexSelectedDP,isClosed);
            cr=error_CR(aContour.at(it_contour),selectedDP);
            error=(cr*cr)/ise;
            /* update errors */
        } while(error_prev<=error && fabs(ise_prev/ise)<1.2);

        /* Push back the last element */
        if(lastIndex !=-1)
        {
            selectedDP.insert(selectedDP.begin()+lastIndex,lastSelectedDP);
            indexSelectedDP.insert(indexSelectedDP.begin()+lastIndex,lastIndexSelectedDP);
        }
        /* Push back the last element */
        cout<<"===> New num of dominant points is "<<selectedDP.size()<<endl;
        vecSelectedDP.push_back(selectedDP);
    }

    if(filename!=NULL)
    {
        Board2D aBoard;
        for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        {
            /* Display the boundary */
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin(); it!=aContour.at(it_contour).end(); it++)
                aBoard << SetMode("PointVector", "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(0,0,0), Color(204,204,204)))
                       << *it;
            /* Display the boundary */
            /* Display old dominant point */
            for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it!=DP.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(0,255,0), Color(0,192,0)))//green
                       <<(*it);
            /* Display old dominant point */
            /* Display new dominant point */
            for(vector<Point>::const_iterator it=vecSelectedDP.at(it_contour).begin(); it!=vecSelectedDP.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                          //<< CustomStyle((*it).className(), new CustomPen( Color(0,0,255), Color(0,0,192), 100.0, Board2D::Shape::SolidStyle, Board2D::Shape::SquareCap,Board2D::Shape::MiterJoin))
                       << CustomStyle((*it).className(), new CustomPen( Color(255,0,0), Color(192,0,0)))//red
                       <<(*it);
            /* Display new dominant point */

            aBoard.setLineWidth(10.0);
            /* Display the segments by old DP */
            aBoard.setPenColor(Color(0, 192, 0));
            for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it+1!=DP.at(it_contour).end(); it++)
                aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
            if(isClosed)//NOTE : DP.front()=aContour.at(it_contour).front()
                aBoard.drawLine(DP.at(it_contour).front()[0],DP.at(it_contour).front()[1],DP.at(it_contour).back()[0],DP.at(it_contour).back()[1]);
            /* Display the segments by old DP */
            /* Display the segments by new DP */
            aBoard.setPenColor(Color(192, 0, 0));
            for(vector<Point>::const_iterator it=vecSelectedDP.at(it_contour).begin(); it+1!=vecSelectedDP.at(it_contour).end(); it++)
                aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
            if(isClosed)//NOTE : DP.front()=aContour.at(it_contour).front()
                aBoard.drawLine(vecSelectedDP.at(it_contour).front()[0],vecSelectedDP.at(it_contour).front()[1],vecSelectedDP.at(it_contour).back()[0],vecSelectedDP.at(it_contour).back()[1]);
            /* Display the segments by new DP */
            //sprintf(filename,"%s_N%d.svg",filename,selectedDP.size());
        }
        if(eps)
            aBoard.saveEPS(filename);
        else
            aBoard.saveSVG(filename);
    }
    return vecSelectedDP;
}
/* Selection by max error criterion */

/* Selection by max error criterion + angle tol*/
vector<vector<Point> > testDominantPointSelection(const vector<vector<Point> >& DP, const vector<vector<int> >& indexDP, const vector<vector<Point> >& aContour, double angleTol, bool isClosed, const char* filename, bool verbose, bool eps)
{
    vector<vector<Point> > vecSelectedDP;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        vector<Point> selectedDP, selectedDP_prev;
        for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it!=DP.at(it_contour).end(); it++)
            selectedDP.push_back(*it);
        vector<int> indexSelectedDP, indexSelectedDP_prev;
        for(vector<int>::const_iterator it=indexDP.at(it_contour).begin(); it!=indexDP.at(it_contour).end(); it++)
            indexSelectedDP.push_back(*it);
        vector<double> iseDP;
        double ise_prev, ise=error_ISE(aContour.at(it_contour),selectedDP,indexSelectedDP,isClosed);
        double cr=error_CR(aContour.at(it_contour),selectedDP);
        double error_prev, error;
        error_prev=error=(cr*cr)/ise;
        ise_prev=ise;
        int lastIndex=-1;
        do{
            selectedDP_prev.clear();
            indexSelectedDP_prev.clear();
            for(vector<Point>::const_iterator it=selectedDP.begin(); it!=selectedDP.end(); it++)
                selectedDP_prev.push_back(*it);
            for(vector<int>::const_iterator it=indexSelectedDP.begin(); it!=indexSelectedDP.end(); it++)
                indexSelectedDP_prev.push_back(*it);
            if(verbose)
                cout<<"===> error_prev/error="<<error_prev<<"/"<<error<<" and ise_prev/ise="<<ise_prev<<"/"<<ise<<endl;
            error_prev=error;
            ise_prev=ise;
            for(size_t it=1; it+1<selectedDP.size(); it++)
            {
                double ise=0.0, d=0.0, angle=0.0;
                int indexStart=indexSelectedDP.at(it-1);
                int indexEnd=indexSelectedDP.at(it+1);
                if(indexStart<0 || indexEnd<0)
                    cout<<"Pb in error_ISE index of DP"<<endl;
                if(isClosed && indexStart>indexEnd)//in case of closed cuves
                    indexEnd=indexEnd+aContour.at(it_contour).size();
                for(int index=indexStart+1; index<indexEnd; index++)
                {
                    d=distancePointSegment(aContour.at(it_contour).at(index%aContour.at(it_contour).size()),
                                           aContour.at(it_contour).at(indexStart),
                                           aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                    ise+=d*d;
                }
                angle=acuteAngle(aContour.at(it_contour).at(indexStart),
                                 aContour.at(it_contour).at(indexSelectedDP.at(it)%aContour.at(it_contour).size()),
                                 aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                if(verbose)
                    cout<<" DP "<<it<<" : ise="<<ise<<", and angle="<<angle<<endl;
                iseDP.push_back(ise/(angle*angle));
            }
            iseDP.insert(iseDP.begin(),(int)aContour.at(it_contour).size()*aContour.at(it_contour).size());//Keep the fist point as DP
            if(!isClosed)//Keep the last point as DP
                iseDP.push_back((int)aContour.at(it_contour).size()*aContour.at(it_contour).size());
            else//isClosed => calcule ISE of the last point
            {
                double ise=0.0, d=0.0, angle=0.0;
                int indexStart=indexSelectedDP.at((int)indexSelectedDP.size()-2);
                int indexEnd=indexSelectedDP.front()+aContour.at(it_contour).size();
                int it=(int)indexSelectedDP.size()-1;
                for(int index=indexStart+1; index<indexEnd; index++)
                {
                    d=distancePointSegment(aContour.at(it_contour).at(index%aContour.at(it_contour).size()),
                                           aContour.at(it_contour).at(indexStart),
                                           aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                    ise+=d*d;
                }
                angle=acuteAngle(aContour.at(it_contour).at(indexStart),
                                 aContour.at(it_contour).at(indexSelectedDP.at(it)%aContour.at(it_contour).size()),
                                 aContour.at(it_contour).at(indexEnd%aContour.at(it_contour).size()));
                if(verbose)
                    cout<<" DP "<<selectedDP.size()<<" : ise="<<ise<<", and angle="<<angle<<endl;
                iseDP.push_back(ise/angle*angle);
            }

            vector<int> indexOrderedDP=absSortIndex(iseDP,true);
            if(verbose)
                for(vector<int>::const_iterator it=indexOrderedDP.begin(); it!=indexOrderedDP.end(); it++)
                    cout<<"ise of DP "<<*it<< " : "<<iseDP.at(*it)<<endl;

            /* erease the first elt */
            lastIndex=indexOrderedDP.front();
            selectedDP.erase(selectedDP.begin()+lastIndex);//indexOrderedDP.front()
            indexSelectedDP.erase(indexSelectedDP.begin()+lastIndex);//indexOrderedDP.front()
            iseDP.clear();
            /* erease the first elt */

            /* update errors */
            ise=error_ISE(aContour.at(it_contour),selectedDP,indexSelectedDP,isClosed);
            cr=error_CR(aContour.at(it_contour),selectedDP);
            error=(cr*cr)/ise;
            /* update errors */
        }while(error_prev<=error && fabs(ise_prev/ise)<1.2);// && fabs(error/error_prev)<1.4
        vecSelectedDP.push_back(selectedDP_prev);
    }

    /* Quasi linear DP remove */
    vector<vector<Point> > vecSelectedDPNew;
    for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
    {
        vector<Point> selectedDP, selectedDP_prev;
        for(vector<Point>::const_iterator it=vecSelectedDP.at(it_contour).begin(); it!=vecSelectedDP.at(it_contour).end(); it++)
            selectedDP_prev.push_back(*it);
        int simpifiedPoint=1;
        while(simpifiedPoint!=0){
            simpifiedPoint=0;
            selectedDP.clear();
            //Handle the first point
            size_t it=0;
            double angle=acuteAngle(selectedDP_prev.back(),selectedDP_prev.at(it),selectedDP_prev.at(it+1));
            if(!(angle<angleTol || angle>(M_PI-angleTol)))
                selectedDP.push_back(selectedDP_prev.at(it));
            else
                simpifiedPoint++;
            if(verbose)
                cout<<"it="<<it<<" ==> Angle="<<angle*180.0/M_PI<<endl;
            //selectedDP.push_back(selectedDP_prev.front());

            //Handle the inbetween points
            for(it=1; it+1<selectedDP_prev.size(); it++)
            {
                angle=acuteAngle(selectedDP_prev.at(it-1),selectedDP_prev.at(it),selectedDP_prev.at(it+1));
                if(!(angle<angleTol || angle>(M_PI-angleTol)))
                    selectedDP.push_back(selectedDP_prev.at(it));
                else
                    simpifiedPoint++;
                if(verbose)
                    cout<<"it="<<it<<" ==> Angle="<<angle*180.0/M_PI<<endl;
            }
            //Handle the last point
            it=selectedDP_prev.size()-1;
            angle=acuteAngle(selectedDP_prev.at(it-1),selectedDP_prev.at(it),selectedDP_prev.front());
            if(!(angle<angleTol || angle>(M_PI-angleTol)))
                selectedDP.push_back(selectedDP_prev.at(it));
            else
                simpifiedPoint++;
            if(verbose)
                cout<<"it="<<it<<" ==> Angle="<<angle*180.0/M_PI<<endl;
            //selectedDP.push_back(selectedDP_prev.back());

            if(verbose)
                cout<<"=> num of simpifiedPoint="<<simpifiedPoint<<endl;

            //copy data to selectedDP_prev
            selectedDP_prev.clear();
            for(vector<Point>::const_iterator it=selectedDP.begin(); it!=selectedDP.end(); it++)
                selectedDP_prev.push_back(*it);
        }
        cout<<"===> New num of dominant points is "<<selectedDP_prev.size()<<endl;
        vecSelectedDPNew.push_back(selectedDP);
    }
    /* Quasi linear DP remove */

    if(filename!=NULL)
    {
        Board2D aBoard;
        for(size_t it_contour=0; it_contour<aContour.size(); it_contour++)
        {
            /* Display the boundary */
            for(vector<Point>::const_iterator it=aContour.at(it_contour).begin(); it!=aContour.at(it_contour).end(); it++)
                aBoard << SetMode("PointVector", "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(0,0,0), Color(204,204,204)))
                       << *it;
            /* Display the boundary */
            /* Display old dominant point *
            for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it!=DP.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                       << CustomStyle((*it).className(), new CustomColors( Color(0,255,0), Color(0,192,0)))//green
                       <<(*it);
            /* Display old dominant point */
            /* Display new dominant point */
            for(vector<Point>::const_iterator it=vecSelectedDPNew.at(it_contour).begin(); it!=vecSelectedDPNew.at(it_contour).end(); it++)
                aBoard << SetMode((*it).className(), "Both")
                          //<< CustomStyle((*it).className(), new CustomPen( Color(0,0,255), Color(0,0,192), 100.0, Board2D::Shape::SolidStyle, Board2D::Shape::SquareCap,Board2D::Shape::MiterJoin))
                       << CustomStyle((*it).className(), new CustomPen( Color(255,0,0), Color(192,0,0)))//red
                       <<(*it);
            /* Display new dominant point */

            aBoard.setLineWidth(10.0);
            /* Display the segments by old DP *
            aBoard.setPenColor(Color(0, 192, 0));
            for(vector<Point>::const_iterator it=DP.at(it_contour).begin(); it+1!=DP.at(it_contour).end(); it++)
                aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
            if(isClosed)//NOTE : DP.front()=aContour.at(it_contour).front()
                aBoard.drawLine(DP.at(it_contour).front()[0],DP.at(it_contour).front()[1],DP.at(it_contour).back()[0],DP.at(it_contour).back()[1]);
            /* Display the segments by old DP */
            /* Display the segments by new DP */
            aBoard.setPenColor(Color(192, 0, 0));
            for(vector<Point>::const_iterator it=vecSelectedDPNew.at(it_contour).begin(); it+1!=vecSelectedDPNew.at(it_contour).end(); it++)
                aBoard.drawLine((*it)[0],(*it)[1],(*(it+1))[0],(*(it+1))[1]);
            if(isClosed)//NOTE : DP.front()=aContour.at(it_contour).front()
                aBoard.drawLine(vecSelectedDPNew.at(it_contour).front()[0],vecSelectedDPNew.at(it_contour).front()[1],vecSelectedDPNew.at(it_contour).back()[0],vecSelectedDPNew.at(it_contour).back()[1]);
            /* Display the segments by new DP */
            //sprintf(filename,"%s_N%d.svg",filename,selectedDP.size());
        }
        if(eps)
            aBoard.saveEPS(filename);
        else
            aBoard.saveSVG(filename);
    }
    return vecSelectedDPNew;
}
/* Selection by max error criterion + angle tol */
/************************************/
/**** Dominant points selection ****/
/************************************/
