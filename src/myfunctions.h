#ifndef MYFUNCTIONS
#define MYFUNCTIONS

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include <stdio.h>
#include <numeric>
#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;
using namespace DGtal;
using namespace Z2i;

typedef PointVector<2, double> PointD;
typedef PointVector<2,int> Point;
typedef std::vector<Point> Range;
typedef std::vector<Point>::const_iterator ConstIterator;
typedef std::vector<PointD>::const_iterator ConstIteratorD;
typedef ArithmeticalDSS<ConstIterator,int,4> DSS4;

typedef  AlphaThickSegmentComputer< Z2i::Point > AlphaThickSegmentComputer2D;
typedef  AlphaThickSegmentComputer<PointD> AlphaThickSegmentComputer2DD;

struct MyDrawStyleCustomColor : public DrawableWithBoard2D
{
  Color myPenColor;
  Color myFillColor;
  MyDrawStyleCustomColor( const Color & penColor,
        const Color & fillColor )
    : myPenColor( penColor ), myFillColor( fillColor )
  {}
  virtual void setStyle( Board2D & aboard) const
  {
    aboard.setFillColor( myFillColor);
    aboard.setPenColor( myPenColor );
  }
};

typedef PointVector<2, double> RealVector;
struct Value
{
  RealVector first;
  double second;
  Value () : second ( 0. ) {}
  Value & operator+= ( const Value & ch )
  {
    this->first += ch.first;
    this->second += ch.second;
    return *this;
  }
};

double sort_increase(double a, double b);
double sort_decrease(double a, double b);

int max(int n, int m);
int min(int n, int m);
int pgcd(int a, int b);

int isLeft(Point p1, Point p2, Point p3);

double verticalDistance(Point p, Point aF, Point aL);
double verticalDistance(Point Uf, Point Ul, Point Lf, Point Ll);

vector<PointD> generateCircle(PointD center, double radius, const char* filename);
vector<Point> generateCircle(Point center, int radius, const char* filename);

vector<PointD> generateArc(PointD center, double radius, double angleStart, double angleEnd, const char* filename);
vector<Point> generateArc(Point center, int radius, double angleStart, double angleEnd, const char* filename);

vector<PointD> generateSegment(PointD startPoint, PointD endPoint, double step, const char* filename);

PointD intersectionLines(double a, double b, double c, double d, double e, double f);

int findElement(const vector<Point>& vec, Point p);
int findElement(const vector<Point>& vec, Point p, int start);
int findElement(const vector<PointD>& vec, PointD p);

int findStartElement(const vector<Point>& vec, const AlphaThickSegmentComputer2D s);
int findEndElement(const vector<Point>& vec, const AlphaThickSegmentComputer2D s);

Point projectionPointSegment(Point p, Point s1, Point s2);
Point projectionPointSegment(Point p, double a, double b, double c);

double distancePoints(Point p1, Point p2);
double distancePoints(PointD p1, PointD p2);
double distancePoints(Point p, PointD c);

double distancePointSegment(Point p, Point s1, Point s2);
double signedDistancePointSegment(Point p, Point s1, Point s2);
double distancePointSegment(Point p, double a, double b, double c); //Segment : a x + b y + c = 0
double signedDistancePointSegment(Point p, double a, double b, double c); //Segment : a x + b y + c = 0

double distancePointCircle(Point p, PointD center, double radius);
double signedDistancePointCircle(Point p, PointD center, double radius);

double relativeAngle(Point v1, Point v2); //relative angle between two vectors
double relativeAngle(Point bp1, Point bp2, Point bp3); //relative angle between three points
double signedAngle(Point v1, Point v2); //angle between two vectors
double signedAngle(Point bp1, Point bp2, Point bp3); //angle between three points
double acuteAngle(Point bp1, Point bp2, Point bp3); //acute angle between three points

double iseContourCircle(const vector<Point>& contour, Point p1, Point p2, PointD center, double radius);//ise of points between two points p1,p2 w.r.t the circle (center,radius)
double iseContourCircle(const vector<Point>& contour, int indexP1, int indexP2, PointD center, double radius);//ise of points between two points of index idp1,idp2 w.r.t the circle (center,radius)
double lmaxContourCircle(const vector<Point>& contour, Point p1, Point p2, PointD center, double radius);//lmax
double lmaxContourCircle(const vector<Point>& contour, int indexP1, int indexP2, PointD center, double radius);//lmax

double iseContourSegment(const vector<Point>& contour, Point p1, Point p2);//ise of points between two points p1,p2 w.r.t the circle (center,radius)
double iseContourSegment(const vector<Point>& contour, int indexP1, int indexP2);//ise of points between two points of index idp1,idp2 w.r.t the circle (center,radius)
double lmaxContourSegment(const vector<Point>& contour, Point p1, Point p2);//lmax
double lmaxContourSegment(const vector<Point>& contour, int indexP1, int indexP2);//lmax

bool isIncreasingOrder(Point v1, Point v2); //return if two vectors is in an increasing order

Point getStartPoint(const AlphaThickSegmentComputer2D s);
Point getEndPoint(const AlphaThickSegmentComputer2D s);
PointD getStartPoint(const AlphaThickSegmentComputer2DD s);
PointD getEndPoint(const AlphaThickSegmentComputer2DD s);

PointD determineCenter(PointD p1, PointD p2, PointD p3);
double determineRadius(PointD p1, PointD p2, PointD p3);

PointD determineCenter(Point p1, Point p2, Point p3);
PointD determineCenter(Point p1, Point p2, double radius, bool negatif);
double determineRadius(Point p1, Point p2, Point p3);
double determineRadius(PointD centre, Point p);
double arcLength(Point p1, Point p2, Point p3);

bool isIsololatedPoint(PointD p_neighbour, PointD p, double alphaMax);
bool isIsololatedPoint(PointD p_prev, PointD p, PointD p_succ, double alphaMax);

double getCurvatureCircle(Point P1, Point P2, Point P3);
double getCurvatureRatio(Point P1, Point P2, Point P3);
double getCurvatureCosine(Point P1, Point P2, Point P3);
double getCurvatureAngle(Point P1, Point P2, Point P3);

double getSlope(double Nx,double Ny);//(Nx,Ny) : normal vector of the line
double getSlope(double Nx,double Ny, int signe);//(Nx,Ny) : normal vector of the line
double getAbsSlope(double Nx,double Ny);//(Nx,Ny) : normal vector of the line

double lengthContour(const vector<Point>& contour);
double lengthContour(const vector<Point>& contour, Point p1, Point p2);
double getShapeDetail(const vector<Point>& contour);

double error_CR(const vector<Point>& contour, const vector<Point>& DP);
double error_ISE(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);
double error_L_infini(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);
double error_FOM(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);
double error_FOM_M(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);
double error_FOM_ND(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);
void error_All(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed);

//bool isBelongTo(Point P, AlphaThickSegmentComputer2D s);
bool isBelongTo(int indexP, int indexL, int indexR);

vector<vector<Point>> readFile(const char* filename);
vector<vector<Point>> readFile(const char* filename, vector<vector<bool>> &vect);
vector<Point> readFile(const char* filename, bool header);
vector<Point> readFileInverse(const char* filename, bool header);
vector<Point> readFile(const char* filename, int header);

vector<int> readMeanindfulScaleFile(const char* filename);
vector<double> readMeanindfulThicknessFile(const char* filename);
vector<double> readMeanindfulThicknessFile(const char* filename,const vector<bool>& vect);

double getGlobalNoise(const vector<double>& vect);
double getThirdQuartile(const vector<double>& vect);

vector<double> findVectorElement(const vector<double>& vect);

vector<PointD> readSmoothContourFile(const char* filename);

void writeFile(const vector<int>& v, const char* filename, bool header);
void writeFile(const vector<double>& v, const char* filename, bool header);
void writeFile(const vector<int>& index_v, const vector<double>& v, const char* filename, bool header);
void writeFile(const vector<double>& v1, const vector<double>& v2, const char* filename, bool header);
void writeFile(const vector<Point>& v, const char* filename, bool header);
void writeFile(const vector<PointD>& v, const char* filename, bool header);

vector<int> sortIndex(vector<double> const& values, bool isIncrease = true);
vector<int> absSortIndex(vector<double> const& values, bool isIncrease = true);

vector<int> sortIndex(vector<int> const& values, bool isIncrease = true);

Point directionOfVector(Point N, Point startS, Point endS);

double error_ISE(const vector<Point>& aContour, const vector<Point>& DP, bool isClosed=false);
double error_L_infini(const vector<Point>& contour, const vector<Point>& DP, bool isClosed=false);
void error_All(const vector<Point>& contour, const vector<Point>& DP, bool isClosed=false);

bool isCircle(Point A, Point B, Point C, Point D);
bool isCircle(PointD A, PointD B, PointD C, PointD D);

#endif // MYFUNCTIONS

