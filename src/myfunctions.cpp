#include "myfunctions.h"

double sort_increase(double a, double b)
{
    return a<b;
}

double sort_decrease(double a, double b)
{
    return a>b;
}

int max(int n, int m)
{
    return n>m ? n:m;
}

int min(int n, int m)
{
    return n<m ? n:m;
}

int pgcd(int a, int b)
{
    a=abs(a);
    b=abs(b);
    int r;
    while (b != 0)
    {
        r=a%b;
        a=b;
        b=r;
    }
    return a;
}

vector<PointD> generateCircle(PointD center, double radius, const char* filename)
{
    vector<PointD> P;
    /*
     * x=sin(theta)*r
     * y=cos(theta)*r
    */
    double step=1/radius;
    for(double theta=0; theta<2*M_PI; theta += step)
        P.push_back(PointD(center[0]+radius*sin(theta), center[1]+radius*cos(theta)));
    /* save into files */
    /*
    std::ofstream FILE(filename);
    std::ostream_iterator<PointD> output_iterator(FILE, "\n");
    std::copy(P.begin(), P.end(), output_iterator);
    */
    std::ofstream FILE(filename);
    for(vector<PointD>::const_iterator it=P.begin(); it != P.end(); it++) {
        FILE << (*it)[0]<<" "<<(*it)[1] <<'\n';
    }
    /* save into files */

    return P;
}

vector<Point> generateCircle(Point center, int radius, const char* filename)
{
    vector<Point> P;
    for(int x=-radius; x<radius; x++)
    {
        int y=round(sqrt(radius*radius-x*x));
        P.push_back(Point(center[0]+x,center[1]+y));
    }
    for(int x=radius; x>-radius; x--)
    {
        int y=-round(sqrt(radius*radius-x*x));
        P.push_back(Point(center[0]+x,center[1]+y));
    }

    if(filename != NULL)
    {
        /* save into files */
        std::ofstream FILE(filename);
        for(vector<Point>::const_iterator it=P.begin(); it != P.end(); it++) {
            FILE << (*it)[0]<<" "<<(*it)[1] <<'\n';
        }
        /* save into files */
    }
    return P;
}

vector<PointD> generateArc(PointD center, double radius, double angleStart, double angleEnd, const char* filename)
{
    vector<PointD> P;
    double step=1/radius;
    if(angleStart<angleEnd)
        for(double theta=angleStart; theta<angleEnd; theta += step)
            P.push_back(PointD(center[0]+radius*sin(theta), center[1]+radius*cos(theta)));
    else
        for(double theta=angleEnd; theta<angleStart; theta += step)
            P.push_back(PointD(center[0]+radius*sin(theta), center[1]+radius*cos(theta)));
    /* save into files */
    std::ofstream FILE(filename);
    for(vector<PointD>::const_iterator it=P.begin(); it != P.end(); it++) {
        FILE << (*it)[0]<<" "<<(*it)[1] <<'\n';
    }
    /* save into files */
    return P;
}

vector<Point> generateArc(Point center, int radius, double angleStart, double angleEnd, const char* filename)
{
    vector<Point> P;
    Point tmp;
    double step=1.0/radius;
    if(angleStart<angleEnd)
        for(double theta=angleStart; theta<angleEnd; theta += step)
        {
            tmp=Point(round(center[0]+radius*sin(theta)), round(center[1]+radius*cos(theta)));
            if(P.empty() || P.back() != tmp)
                P.push_back(tmp);
            /*
            if(P.empty())
                P.push_back(tmp);
            else if ()
                P.push_back(tmp);
            */
        }
    else
        for(double theta=angleEnd; theta<angleStart; theta += step)
        {
            tmp=Point(round(center[0]+radius*sin(theta)), round(center[1]+radius*cos(theta)));
            if(P.empty() || P.back() != tmp)
                P.push_back(tmp);
        }
    if(filename != NULL)
    {
        /* save into files */
        std::ofstream FILE(filename);
        for(vector<Point>::const_iterator it=P.begin(); it != P.end(); it++) {
            FILE << (*it)[0]<<" "<<(*it)[1] <<'\n';
        }
        /* save into files */
    }
    return P;
}

vector<PointD> generateSegment(PointD startPoint, PointD endPoint, double step, const char* filename)
{
    vector<PointD> P;
    //AB: y=a x + b where a=dy/dx and b=yA - a(xA)
    double dx=endPoint[0] - startPoint[0] , dy=endPoint[1] - startPoint[1];
    double x, y;
    if(dx == 0) //vertical line
    {
        x=startPoint[0];
        if(startPoint[1]<endPoint[1])
            for(y=startPoint[1]; y <= endPoint[1]; y += step)
                P.push_back(PointD(x,y));
        else
            for(y=startPoint[1]; y >= endPoint[1]; y -= step)
                P.push_back(PointD(x,y));
    }
    else
    {
        double a=dy/dx;
        double b=startPoint[1] - a*startPoint[0];
        if(startPoint[0]<endPoint[0])
            for(x=startPoint[0]; x <= endPoint[0]; x += step)
                P.push_back(PointD(x,a*x+b));
        else
            for(x=startPoint[0]; x >= endPoint[0]; x -= step)
                P.push_back(PointD(x,a*x+b));
    }
    /* save into files */
    std::ofstream FILE(filename);
    for(vector<PointD>::const_iterator it=P.begin(); it != P.end(); it++) {
        FILE << (*it)[0]<<" "<<(*it)[1] <<'\n';
    }
    /* save into files */
    return P;
}

//vertical distancePoints of p to the line (aF,aL)
double verticaldistancePoints(Point p, Point aF, Point aL)
{
    //line (aF,aL) y=a x + b
    cout<<"p="<<p<<endl<<"aF="<<aF<<endl<<"aL="<<aL<<endl;
    double a=(double)(aL[1]-aF[1])/(aL[0]-aF[0]);
    double b=aF[1]-a*aF[0];
    return fabs(p[1] - a*p[0]-b);//vertical distancePoints of p to the line
}

//max vertical distancePoints between (Uf,Ul), (aF,aL)
double verticaldistancePoints(Point Uf, Point Ul, Point Lf, Point Ll)
{
    //upper line y=a1 x + b1
    double a1=(double)(Ul[1]-Uf[1])/(Ul[0]-Uf[0]);
    double b1=Uf[1]-a1*Uf[0];
    double d11=a1*Lf[0]+b1;//vertical distancePoints of Lf to upper line
    double d12=a1*Ll[0]+b1;//vertical distancePoints of Ll to upper line

    //lower line y=a2 x + b2
    double a2=(double)(Ll[1]-Lf[1])/(Ll[0]-Lf[0]);
    double b2=Lf[1]-a2*Lf[0];
    double d21=a2*Uf[0]+b2;//vertical distancePoints of Uf to lower line
    double d22=a2*Ul[0]+b2;//vertical distancePoints of Ul to lower line

    return max(d11,max(d12,max(d21,d22)));
}

PointVector<2,double> intersectionLines(double a, double b, double c, double d, double e, double f)
{
    //l1 : a x - b y=c
    //l1 : d x - e y=f
    PointVector<2,double> p(0,0);
    if(b*d-a*e!=0)
    {
        p[0]=(b*f - c*e)/(b*d-a*e);
        p[1]=(a*p[0] - c)/b;
    }
    //cout<<"lines ("<<a<<","<<b<<","<<c<<") and ("<<d<<","<<e<<","<<f<<") ==> intersection point : "<<p<<endl;
    return p;
}

int findElement(const vector<Point>& vec, Point p)
{
    //cout<<"vec size="<<vec.size()<<" and p="<<p<<" found at ";
    vector<Point>::const_iterator it=find(vec.begin(),vec.end(),p);
    //cout<< (it == vec.end() ? -1 : it-vec.begin()) <<endl;
    if(it != vec.end())
        return (it-vec.begin());
    else
        return -1;
}

int findElement(const vector<Point>& vec, Point p, int start)
{
    int it;
    for(it=start; it<vec.size(); it++)
        if(vec.at(it)==p)
            return it;
    //if(it==vec.size())
    for(it=0; it<start; it++)
        if(vec.at(it)==p)
            //return vec.size()+it;//FIXME
            return (int)vec.size()+it;
    return -1;
}

int findElement(const vector<PointD>& vec, PointD p)
{
    vector<PointD>::const_iterator it=find(vec.begin(),vec.end(),p);
    if(it != vec.end())
        return (it-vec.begin());
    else
        return -1;
}

int findStartElement(const vector<Point>& vec, const AlphaThickSegmentComputer2D s)
{
    Point pStart=getStartPoint(s);
    vector<Point>::const_iterator it=find(vec.begin(),vec.end(),pStart);
    if(it != vec.end())
        return (it-vec.begin());
    return -1;
}

int findEndElement(const vector<Point>& vec, const AlphaThickSegmentComputer2D s)
{
    Point pStart=getStartPoint(s);
    Point pEnd=getEndPoint(s);
    int indexStart=-1;
    vector<Point>::const_iterator itStart=find(vec.begin(),vec.end(),pStart);
    if(itStart != vec.end())
        indexStart=(itStart-vec.begin());
    int indexEnd=-1;
    vector<Point>::const_iterator itEnd=find(vec.begin(),vec.end(),pEnd);
    if(itEnd != vec.end())
        indexEnd=(itEnd-vec.begin());
    if(indexStart != -1 && indexEnd != -1)
    {
        if(indexEnd<indexStart)
            //indexEnd += vec.size();//FIXME
            indexEnd += (int)vec.size();
    }
    return indexEnd;
}


double distancePoints(Point p1, Point p2)
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]));
}

double distancePoints(PointD p1, PointD p2)
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]));
}

double distancePoints(Point p, PointD c)
{
    return sqrt((p[0]-c[0])*(p[0]-c[0]) + (p[1]-c[1])*(p[1]-c[1]));
}
/*
Point projectionPointSegment(Point p, Point s1, Point s2);
Point projectionPointSegment(Point p, double a, double b, double c);
*/

double distancePointSegment(Point p, double a, double b, double c) //Segment : a x + by + c=0
{
    if(a==0 && b==0)
        return 0;
    return fabs(a*p[0] + b*p[1] + c)/sqrt(a*a+b*b);
}

double signedDistancePointSegment(Point p, double a, double b, double c) //Segment : a x + by + c=0
{
    if(a==0 && b==0)
        return 0;
    return (a*p[0] + b*p[1] + c)/sqrt(a*a+b*b);
}

double distancePointSegment(Point p, Point s1, Point s2)
{
    double a, b, c;
    //line : ax + by + c=0
    //(y1 – y2)x + (x2 – x1)y + (x1y2 – x2y1)=0
    a=s1[1] - s2[1];
    b=s2[0] - s1[0];
    c=s1[0]*s2[1] - s2[0]*s1[1];
    return distancePointSegment(p, a, b, c);
}

double signedDistancePointSegment(Point p, Point s1, Point s2)
{
    double a, b, c;
    //line : ax + by + c=0
    //(y1 – y2)x + (x2 – x1)y + (x1y2 – x2y1)=0
    a=s1[1] - s2[1];
    b=s2[0] - s1[0];
    c=s1[0]*s2[1] - s2[0]*s1[1];
    return signedDistancePointSegment(p, a, b, c);
}

double distancePointCircle(Point p, PointD center, double radius)
{
    return fabs(distancePoints(p,center) - radius);
}

double signedDistancePointCircle(Point p, PointD center, double radius)
{
    return distancePoints(p,center) - radius;
}



//cos(THETA)=a*b / (||a|| ||b||)
//This gives us just the relative angle between a and b, in [0,PI].
double relativeAngle(Point v1, Point v2)
{
    //normalize the vector
    PointVector<2,double> n_v1, n_v2;
    n_v1[0]=v1[0]/(sqrt(v1[0]*v1[0] + v1[1]*v1[1]));
    n_v1[1]=v1[1]/(sqrt(v1[0]*v1[0] + v1[1]*v1[1]));

    n_v2[0]=v2[0]/(sqrt(v2[0]*v2[0] + v2[1]*v2[1]));
    n_v2[1]=v2[1]/(sqrt(v2[0]*v2[0] + v2[1]*v2[1]));

    //float dotProduct=ax*bx + ay*by;
    //float theta=acos( dotProduct / (vec1Len*vec2Len) );
    return acos(n_v1[0]*n_v2[0]+n_v1[1]*n_v2[1]);
}

// angle between three points (p1,p2,p3)=(b,c,a)
//c*c=a*a + b*b - 2abcos(alpha)
double relativeAngle(Point p1, Point p2, Point p3)
{
    if(p1 == p2 || p1 == p3 || p2==p3)
        return 0;
    double a, b, c, ac;
    a=distancePoints(p1,p2);
    b=distancePoints(p2,p3);
    c=distancePoints(p1,p3);
    ac=(c*c-a*a-b*b);
    if(fabs(ac)<1e-6)
        return M_PI/2;
    if(fabs(c-a-b)<1e-6)
        return M_PI;
    //ac=(c*c-a*a-b*b)/(-2*a*b);
    return acos(ac/(-2*a*b));
}

/*
//THETA=atan2(by,bx) - atan2(ay,ax)
//This gives us the relative angle between a and b with a sign, in [-PI,PI]
double signedAngle(Point v1, Point v2)
{
    //theta=atan2(by,bx) - atan2(ay,ax);
    double alpha1=atan2(v1[1],v1[0]);
    double alpha2=atan2(v2[1],v2[0]);
    if(alpha1<0) alpha1 += 2*M_PI;
    if(alpha2<0) alpha2 += 2*M_PI;
    return alpha2 - alpha1;
}
*/
// angle between two vector
double signedAngle(Point v1, Point v2)
{
    double Na=sqrt(v1[0]*v1[0] + v1[1]*v1[1]);
    double Nb=sqrt(v2[0]*v2[0] + v2[1]*v2[1]);
    double C=(v1[0]*v2[0] + v1[1]*v2[1])/(Na*Nb);
    double S=(v1[0]*v2[1] - v1[1]*v2[0]);
    if(S<0)
        return(-acos(C));
    else
        return (acos(C));
}

// angle between three points
/*
double signedAngle(Point p1, Point p2, Point p3)
{
    double d1, d2, d,ac;
    d1=distancePoints(p1,p2);
    d2=distancePoints(p2,p3);
    d=distancePoints(p1,p3);

    ac=(d*d-d1*d1-d2*d2)/(2*d1*d2);

    double angle;
    if(1-ac<0.0005) angle=0.0;
    else angle=fabs(acos(ac));
    //angle=180*angle/M_PI;

    if(isLeft(p1,p2,p3)>0)
        angle=-angle;
    return angle;
}
*/

double acuteAngle(Point p1, Point p2, Point p3)
{
    Point v1=Point(p1[0]-p2[0],p1[1]-p2[1]);
    Point v2=Point(p3[0]-p2[0],p3[1]-p2[1]);
    double angle=atan2(v2[0],-v2[1]) - atan2(v1[0],-v1[1]);
    if(angle<0)
        angle += 2*M_PI; //report angle to (0,2pi)
    if(angle>M_PI)
        angle=2*M_PI - angle;
    return angle;
}

bool isIncreasingOrder(Point v1, Point v2)
{
    //Normal vector of two segments !!!!
    double angle=atan2(v2[0],-v2[1]) - atan2(v1[0],-v1[1]); //oriented angle (anti-clockwise) between two vectors in (-pi,pi)
    //double angle=atan2(-v2[0],v2[1]) - atan2(-v1[0],v1[1]); //oriented angle (anti-clockwise) between two vectors in (-pi,pi)
    if(angle<0)
        angle += 2*M_PI; //report angle to (0,2pi)
    return angle<M_PI;
}

Point getStartPoint(const AlphaThickSegmentComputer2D s)
{
    if(s.size()==0)
        return *(s.begin()); //add point from iterator
    return *(s.containerBegin());
}

Point getEndPoint(const AlphaThickSegmentComputer2D s)
{
    Point p;
    if(s.size()==0)
    {
        for(vector<Point>::const_iterator it=s.begin();it != s.end();it++)
            p=*(it);
    }
    else
    {
        for(vector<Point>::const_iterator it=s.containerBegin();it != s.containerEnd();it++)
            p=*(it);
    }
    return p;
}

PointD getStartPoint(const AlphaThickSegmentComputer2DD s)
{
    return *(s.begin());
}

PointD getEndPoint(const AlphaThickSegmentComputer2DD s)
{
    PointD p;
    for(vector<PointD>::const_iterator it=s.begin();it != s.end();it++)
    {
        p=*(it);
    }
    return p;
}

PointD determineCenter(PointD p1, PointD p2, PointD p3)
{
    double a1, b1, a2, b2, c1, c2;
    double xA, yA, xB, yB, xC, yC;
    xA=p1[0];
    yA=p1[1];
    xB=p2[0];
    yB=p2[1];
    xC=p3[0];
    yC=p3[1];

    a1=xA-xB;
    b1=yA-yB;
    a2=xA-xC;
    b2=yA-yC;
    c1=(xA*xA-xB*xB+yA*yA-yB*yB)/2;
    c2=(xA*xA-xC*xC+yA*yA-yC*yC)/2;
    double x,y,dentaY;
    dentaY=b1*a2-a1*b2;
    if(dentaY!=0){
        y= (double)(c1*a2-a1*c2)/(double)dentaY;
        if (a1!=0) x=(double)(c1-b1*y)/(double)a1;
        else if(a2!=0) x=(double)(c2-b2*y)/(double)a2;
        else {
            cout<<"Error: 3 points of the arc are colinear."<<endl;
            x=-1;
            y=-1;
        }
    }
    else
    {
        x=-1;
        y=-1;
    }
    return PointD(x,y);
}

double determineRadius(PointD p1, PointD p2, PointD p3)
{
    PointD center=determineCenter(p1,p2,p3);
    return (distancePoints(p1,center) + distancePoints(p2,center) + distancePoints(p3,center))/3.0;
}

double determineRadius(PointD center, PointD p)
{
    return distancePoints(center,p);
}

PointD determineCenter(Point p1, Point p2, Point p3)
{
    double a1, b1, a2, b2, c1, c2;
    double xA, yA, xB, yB, xC, yC;
    xA=p1[0];
    yA=p1[1];
    xB=p2[0];
    yB=p2[1];
    xC=p3[0];
    yC=p3[1];

    a1=xA-xB;
    b1=yA-yB;
    a2=xA-xC;
    b2=yA-yC;
    c1=(xA*xA-xB*xB+yA*yA-yB*yB)/2;
    c2=(xA*xA-xC*xC+yA*yA-yC*yC)/2;
    double x,y,dentaY;
    dentaY=(b1*a2-a1*b2);
    if(dentaY!=0) {
        y= (c1*a2-a1*c2)/dentaY;
        if (a1!=0) x=(c1-b1*y)/a1;
        else if(a2!=0) x=(c2-b2*y)/a2;
        else {
            cout<<"Error: 3 points of the arc are colinear."<<endl;
            x=-1;
            y=-1;
        }
    }
    else {
        x=-c1;
        y=-1;
    }
    //return Point((int)x,(int)y);
    return PointD(x,y);
}

PointD determineCenter(Point p1, Point p2, double radius, bool negatif)
{
    double a, b, c, q;
    double xA, yA, xB, yB, xC, yC;
    xA=p1[0];
    yA=p1[1];
    xB=p2[0];
    yB=p2[1];
    xC=(p1[0]+p2[0])/2.0;
    yC=(p1[1]+p2[1])/2.0;

    a=xB-xA;
    b=yA-yB;
    q=sqrt(a*a+b*b);
    c=sqrt(radius*radius - (q*q)/4.0);

    //find direction from p1 to p2
    double x,y;
    //if(xA<xB){ //p1 is right and p2 is left
    if(negatif){ //p1 is left and p2 is right
        x=xC - c*b/q;
        y=yC - c*a/q;
    }
    else{ //p1 is left and p2 is right
        x=xC + c*b/q;
        y=yC + c*a/q;
    }
    //return Point((int)x,(int)y);
    return PointD(x,y);
}

double determineRadius(Point p1, Point p2, Point p3)
{
    PointD center=determineCenter(p1,p2,p3);
    return (distancePoints(p1,center) + distancePoints(p2,center) + distancePoints(p3,center))/3.0;
}

double determineRadius(PointD center, Point p)
{
    return distancePoints(p,center);
}

double arcLength(Point p1, Point p2, Point p3)
{
    double R=determineRadius(p1,p2,p3);
    double angle=2*(M_PI - acuteAngle(p1,p2,p3));//2*M_PI - 2*angle;
    //Point center=determineCenter(p1,p2,p3);relativeAngle(p1,center,p3);
    return R*angle;
}


bool isIsololatedPoint(PointD p, PointD p_next,double alphaMax)
{
    //cout<<"=> different (angle) is "<<fabs(p[1]-p_next[1])*180/M_PI<<endl;
    //cout<<"=> length is "<<p[0]<<" and different (length) is "<<fabs(p[0]-p_next[0])<<endl;
    return (fabs(p[1]-p_next[1])>alphaMax);
}

bool isIsololatedPoint(PointD p_prev, PointD p, PointD p_succ, double alphaMax)
{
    //cout<<"=> different is "<<fabs(p[1]-p_prev[1])*180/M_PI<<" and "<<fabs(p[1]-p_succ[1])*180/M_PI<<endl;
    //cout<<"=> different (length) is "<<fabs(p[0]-p_prev[0])<<" and "<<fabs(p[0]-p_succ[0])<<endl;
    return ((fabs(p[1]-p_prev[1])>alphaMax) && (fabs(p[1]-p_succ[1])>alphaMax));
}

/* calcul curvature passing 3 points */
//verify whether p3 is left of p1p2
int isLeft(Point p3, Point p1, Point p2)
{
    int v1, v2, v3, v4;
    v1=p2[0] - p1[0];
    v2=p3[1] - p1[1];
    v3=p3[0] - p1[0];
    v4=p2[1] - p1[1];

    int t=v1*v2 - v3*v4;
    if(t>0) return 1;//left
    else if(t<0) return -1;//right
    else return 0;//on the line
}

/* 1/radius of the circle passing thought 3 points */
double getCurvatureCircle(Point P1, Point P2, Point P3)
{
    if(P1==P2 || P2==P3 || P1==P3)
        return 0;

    double a,b,c,p,pa,pb,pc,S;
    a=distancePoints(P1,P2);
    b=distancePoints(P2,P3);
    c=distancePoints(P3,P1);
    //cout<<"a="<<a<<" b="<<b<<" c="<<c<<endl;

    p=a+b+c; pa=b+c-a;
    pb=a+c-b; pc=a+b-c;
    S=sqrt(p*pa*pb*pc);

    double radius, curvature=0;
    if (S!=0)
    {
        radius=a*b*c/S;
        curvature=(double) 1/radius;
        //if(isLeft(P2,P3,P1)<0) curvature=-curvature;
        if(isLeft(P1,P2,P3)<0) curvature=-curvature;
    }
    //else
    //    curvature=1e-6;

    return curvature;
}

double getCurvatureRatio(Point P1, Point P2, Point P3)
{
    if(P1==P2 || P2==P3 || P1==P3)
        return 0;

    double l=distancePoints(P2,P3);
    double d=distancePointSegment(P1,P2,P3);
    double curvature=d/l;
    //if(isLeft(P2,P3,P1)<0) curvature=-curvature;
    if(isLeft(P1,P2,P3)<0) curvature=-curvature;

    return curvature;
}

double getCurvatureCosine(Point P1, Point P2, Point P3)
{
    if(P1==P2 || P2==P3 || P1==P3)
        return 0;
    Point v1=Point(P2[0]-P1[0],P2[1]-P1[1]);
    Point v2=Point(P3[0]-P1[0],P3[1]-P1[1]);
    double curvature=cos(relativeAngle(v1,v2));
    //if(isLeft(P2,P3,P1)<0) curvature=-curvature;
    if(isLeft(P1,P2,P3)<0) curvature=-curvature;

    return curvature;
}

double getCurvatureAngle(Point P1, Point P2, Point P3)
{
    if(P1==P2 || P2==P3 || P1==P3)
        return 0;
    Point v1=Point(P2[0]-P1[0],P2[1]-P1[1]);
    Point v2=Point(P3[0]-P1[0],P3[1]-P1[1]);
    double curvature=1.0/relativeAngle(v1,v2);
    //double curvature=1.0/signedAngle(v1,v2);
    //if(isLeft(P1,P2,P3)<0) curvature=-curvature;
    return curvature;
}

//(Nx,Ny) : normal vector of the line
double getSlope(double Nx,double Ny)
{
    //cout<<"Nx="<<-Ny<<" and Ny="<<Nx<<"  ==> ";
    //cout<<"Nx="<<Ny<<" and Ny="<<-Nx<<"  ==> ";
    //cout<<"Nx="<<Nx<<" and Ny="<<Ny<<"  ==> ";
    if(fabs(Ny)<1e-6) //vertical line
    {
        if(Nx>0)
            return -1e6; // -INFINITY ?
        else
            return 1e6; //INFINITY ?
    }
    return (-Nx/Ny);
    //return (-Nx/Ny)*(sqrt(Nx*Nx + Ny*Ny));
}

double getSlope(double Nx,double Ny, int signe)
{
    //cout<<"Nx="<<Ny<<" and Ny="<<-Nx<<" and sign "<<signe<<" ==> ";
    double angle=atan(-Nx/Ny);
    if(signe<0)
    {
        if(angle>0)
            return angle - M_PI;
        return angle;
    }
    else//signe>0
    {
        if(angle<0)
            return angle + M_PI;
        return angle;
    }
}

double getAbsSlope(double Nx,double Ny)
{
    //cout<<"Nx="<<Nx<<" and Ny="<<Ny<<" ";
    if(fabs(Ny)<1e-6) //vertical line
        return 1e6;
    return fabs(-Nx/Ny);
}

double lengthContour(const vector<Point>& contour)
{
    double length=0;
    for(vector<Point>::const_iterator it=contour.begin(); it+1 != contour.end(); it++)
        //cout<<"length "<<distancePoints(*it,*(it+1))<<endl;
        length += distancePoints(*it,*(it+1));
    return length;
}

double lengthContour(const vector<Point>& contour, Point p1, Point p2)
{
    double length=0;
    int indexP1=findElement(contour,p1);
    int indexP2=findElement(contour,p2);
    if(indexP1 != -1 && indexP2 != -1)
        for(int it=indexP1; it<indexP2; it++)
            length += distancePoints(contour.at(it),contour.at(it+1));
    return length;
}

double iseContourCircle(const vector<Point>& contour, Point p1, Point p2, PointD center, double radius)
{
    double ise=0, d=0;
    int indexP1=findElement(contour,p1);
    int indexP2=findElement(contour,p2);
    if(indexP1 != -1 && indexP2 != -1)
        for(int it=indexP1+1; it<indexP2; it++)
        {
            d=distancePointCircle(contour.at(it),center,radius);
            ise += d*d;
        }
    return ise;
}

double iseContourCircle(const vector<Point>& contour, int indexP1, int indexP2, PointD center, double radius)
{
    double ise=0, d=0;
    for(int it=indexP1+1; it<indexP2; it++)
    {
        d=distancePointCircle(contour.at(it),center,radius);
        ise += d*d;
    }
    return ise;
}

double lmaxContourCircle(const vector<Point>& contour, Point p1, Point p2, PointD center, double radius)
{
    double lmax=0, l=0;
    int indexP1=findElement(contour,p1);
    int indexP2=findElement(contour,p2);
    if(indexP1 != -1 && indexP2 != -1)
        for(int it=indexP1+1; it<indexP2; it++)
        {
            l=distancePointCircle(contour.at(it),center,radius);
            if(lmax<l)
                lmax=l;
        }
    return lmax;
}

double lmaxContourCircle(const vector<Point>& contour, int indexP1, int indexP2, PointD center, double radius)
{
    double lmax=0, l=0;
    for(int it=indexP1+1; it<indexP2; it++)
    {
        l=distancePointCircle(contour.at(it),center,radius);
        if(lmax<l)
            lmax=l;
    }
    return lmax;
}

double iseContourSegment(const vector<Point>& contour, Point p1, Point p2)
{
    double ise=0, d=0;
    int indexP1=findElement(contour,p1);
    int indexP2=findElement(contour,p2);
    if(indexP1 != -1 && indexP2 != -1)
        for(int it=indexP1+1; it<indexP2; it++)
        {
            d=distancePointSegment(contour.at(it),contour.at(indexP1),contour.at(indexP2));
            ise += d*d;
        }
    return ise;
}

double iseContourSegment(const vector<Point>& contour, int indexP1, int indexP2)
{
    double ise=0, d=0;
    for(int it=indexP1+1; it<indexP2; it++)
    {
        d=distancePointSegment(contour.at(it),contour.at(indexP1),contour.at(indexP2));
        ise += d*d;
    }
    return ise;
}

double lmaxContourSegment(const vector<Point>& contour, Point p1, Point p2)
{
    double lmax=0, l=0;
    int indexP1=findElement(contour,p1);
    int indexP2=findElement(contour,p2);
    if(indexP1 != -1 && indexP2 != -1)
        for(int it=indexP1+1; it<indexP2; it++)
        {
            l=distancePointSegment(contour.at(it),contour.at(indexP1),contour.at(indexP2));
            if(lmax<l)
                lmax=l;
        }
    return lmax;
}

double lmaxContourSegment(const vector<Point>& contour, int indexP1, int indexP2)
{
    double lmax=0, l=0;
    for(int it=indexP1+1; it<indexP2; it++)
    {
        l=distancePointSegment(contour.at(it),contour.at(indexP1),contour.at(indexP2));
        if(lmax<l)
            lmax=l;
    }
    return lmax;
}

bool comparisonPoint(Point i, Point j)
{
    return i<j;
}



double getShapeDetail(const vector<Point>& contour)
{
    /*
    auto biggest=std::max_element(std::begin(contour), std::end(contour),comparisonPoint);
    std::cout << "Max element is " << *biggest
              << " at position " << std::distancePoints(std::begin(contour), biggest) << std::endl;

    auto smallest=std::min_element(std::begin(contour), std::end(contour),comparisonPoint);
    std::cout << "Min element is " << *smallest
              << " at position " << std::distancePoints(std::begin(contour), smallest) << std::endl;
    */
    int x_min=contour.back()[0], y_min=contour.back()[1], x_max=contour.back()[0], y_max=contour.back()[1];
    for(vector<Point>::const_iterator it=contour.begin(); it+1 != contour.end(); it++)
    {
        if(x_min>(*it)[0]) x_min=(*it)[0];
        if(y_min>(*it)[1]) y_min=(*it)[1];
        if(x_max<(*it)[0]) x_max=(*it)[0];
        if(y_max<(*it)[1]) y_max=(*it)[1];
    }
    double boundingBox=(x_max-x_min)*(y_max-y_min);
    //cout<<"x_min="<<x_min<<" y_min="<<y_min<<" x_max="<<x_max<<" y_max="<<y_max<<endl;
    //cout<<"nb of pixels "<<contour.size();
    //cout<<" and length of contours is "<<lengthContour(contour);
    //cout<<" and bouding box is "<<boundingBox<<" ==> ratio is "<< boundingBox/lengthContour(contour) <<endl;
    //cout<<" and bouding box is "<<boundingBox<<" ==> ratio is "<< lengthContour(contour)/boundingBox <<endl;
    //return 0.02*boundingBox/lengthContour(contour);
    return 50*lengthContour(contour)/boundingBox;
}

/******* Evaluation criteria **********/
double error_CR(const vector<Point>& contour, const vector<Point>& DP)
{
    return (double)contour.size()/DP.size();
}

double error_ISE(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed)
{
    double ise=0.0, d=0.0;
    for(size_t it=0; it+1<DP.size(); it++)
    {
        int indexStart=indexDP.at(it);
        int indexEnd=indexDP.at(it+1);
        if(indexStart<0 || indexEnd<0)
            cout<<"Pb in error_ISE index of DP"<<endl;
        for(int index=indexStart+1; index<indexEnd; index++)
        {
            d=distancePointSegment(contour.at(index),DP.at(it), DP.at(it+1));
            ise += d*d;
        }
        if(isClosed && indexStart>indexEnd)
        {
            //cout<<"it="<<it<<" : indexStart="<<indexStart<<", indexEnd="<<indexEnd<<endl;
            for(int index=indexStart+1; index<indexEnd+contour.size(); index++)
            {
                d=distancePointSegment(contour.at(index%contour.size()),DP.at(it), DP.at(it+1));
                ise += d*d;
            }
        }
    }
    //cout<<"ise="<<ise<<endl;
    if(isClosed)//consider the last seg DP.front() and DP.back()
    {
        int indexStart=indexDP.back();
        int indexEnd=indexDP.front();
        if(indexStart>indexEnd)
            indexEnd=indexEnd+contour.size();
        //cout<<"isClosed"<<" : indexStart="<<indexStart<<", indexEnd="<<indexEnd<<endl;
        if(indexStart<0 || indexEnd<0)
            cout<<"Pb in error_ISE index of DP"<<endl;
        for(int index=indexStart+1; index<indexEnd; index++)
        {
            d=distancePointSegment(contour.at(index%contour.size()),DP.back(), DP.front());
            ise += d*d;
        }
    }
    return ise;
}

double error_L_infini(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed)
{
    double d_max=0.0, d;
    for(size_t it=0; it+1<DP.size(); it++)
    {
        int indexStart=indexDP.at(it);
        int indexEnd=indexDP.at(it+1);
        if(indexStart<0 || indexEnd<0)
            cout<<"Pb in error_ISE index of DP"<<endl;
        for(int index=indexStart+1; index<indexEnd; index++)
        {
            d=distancePointSegment(contour.at(index),DP.at(it), DP.at(it+1));
            if(d>d_max)
                d_max=d;
        }
    }
    if(isClosed)//consider the last seg DP.front() and DP.back()
    {
        int indexStart=indexDP.back();
        int indexEnd=indexDP.front()+contour.size();
        //cout<<"it="<<it<<" : indexStart="<<indexStart<<", indexEnd="<<indexEnd<<endl;
        if(indexStart<0 || indexEnd<0)
            cout<<"Pb in error_ISE index of DP"<<endl;
        for(int index=indexStart+1; index<indexEnd; index++)
        {
            d=distancePointSegment(contour.at(index%contour.size()),DP.back(), DP.front());
            if(d>d_max)
                d_max=d;
        }
    }
    return d_max;
}

void error_All(const vector<Point>& contour, const vector<Point>& DP, const vector<int>& indexDP, bool isClosed)
{
    double cr=error_CR(contour,DP);
    double ise=error_ISE(contour,DP,indexDP,isClosed);
    double dmax=error_L_infini(contour,DP,indexDP,isClosed);
    double fom=cr/ise;
    double fom_M=(cr*cr)/ise;
    double fom_ND=(cr*cr*cr)/(ise*dmax);

    cout<<"cr="<<cr<<", ise="<<ise<<", dmax="<<dmax<<", FOM="<<fom<<", FOM_M="<<fom_M<<", FOM_ND="<<fom_ND<<endl;
}

/******* Evaluation criteria **********/

bool isBelongTo(int indexP, int indexL, int indexR)
{
    if(indexP<0 || indexL<0 || indexR<0)
        cout<<"negatif index !!!!!"<<endl;

    //cout<<"==> "<<indexP<<" "<<indexL<<"  "<<indexR<<endl;

    return ((indexP >= indexL) && (indexP <= indexR));
}

vector<vector<Point>> readFile(const char* filename)
{
    vector<vector<Point>> P;
    FILE *myfile;
    myfile =fopen(filename, "r");

    if (!myfile)
    {
        cout << "Unable to open file " <<filename;
        return P;
    }
    else
    {
        //Format 1, nb of Points : 100
        //Format 2, a Point : 15 15
        //Format 3, from freeman code : # grid curve 1/1 closed
        //Read and analyse the first line to know the format
        int ch=getc(myfile), num_blank=0;
        while (ch != EOF && ch != '\n'){
            if(ch==' ')
                num_blank++;
            ch=getc(myfile);
        }
        fclose(myfile);
        //cout<<"num_blank="<<num_blank<<endl;

        myfile =fopen(filename, "r");
        int x,y,count=0;
        if(num_blank==0)//Format 1
        {
            P.push_back(vector<Point>());
            int nbPoint=0;
            fscanf(myfile,"%d\n",&nbPoint);
            while (count<nbPoint)
            {
                fscanf(myfile,"%d %d\n",&x,&y);
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                    P[0].push_back(point);
                else
                    cout<<"repeated point "<<point<<endl;
                count++;
            }
        }
        else if(num_blank==1)//Format 2
        {
            P.push_back(vector<Point>());
            while(fscanf(myfile,"%d %d\n",&x,&y)!=EOF)
            {
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                    P[0].push_back(point);
                else
                    cout<<"repeated point "<<point<<endl;
                count++;
            }
        }
        else if(num_blank==2)//Format 2
        {
            P.push_back(vector<Point>());
            while(fscanf(myfile,"%d %d \n",&x,&y)!=EOF)
            {
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                    P[0].push_back(point);
                else
                    cout<<"repeated point "<<point<<endl;
                count++;
            }
        }
        else if(num_blank==4)//Format 3
        {
            int id_Contour=0,num_Contour=0;
            char s1[10],s2[10],s3[10];
            fscanf(myfile,"# %s %s %d/%d %s\n",s1,s2,&id_Contour,&num_Contour,s3);
            //cout<<"id_Contour="<<id_Contour<<" and num_Contour="<<num_Contour<<endl;
            for(int id=0; id<num_Contour; id++)
            {
                P.push_back(vector<Point>());
                int val = fscanf(myfile,"%d %d\n",&x,&y);
                while(val!=EOF && val==2)
                {
                    Point point = Point((int)x,(int)y);
                    vector<Point>::const_iterator it = find(P[id].begin(),P[id].end(),point);
                    if(it == P[id].end())
                        P[id].push_back(point);
                    else
                        cout<<"repeated point "<<point<<endl;
                    count++;
                    val = fscanf(myfile,"%d %d\n",&x,&y);
                }
                //cout<<id<<" sequence finish"<<endl;
                fscanf(myfile,"# %s %s %d/%d %s\n",s1,s2,&id_Contour,&num_Contour,s3);
            }
        }
        else
        {
            cout << "Format unknow " <<filename<<endl;
        }
    }
    fclose(myfile);
    return P;
}

vector<vector<Point>> readFile(const char* filename, vector<vector<bool>>& vect)
{
    vector<vector<Point>> P;
    FILE *myfile;
    myfile =fopen(filename, "r");

    if (!myfile)
    {
        cout << "Unable to open file " <<filename;
        return P;
    }
    else
    {
        //Format 1, nb of Points : 100
        //Format 2, a Point : 15 15
        //Format 3, from freeman code : # grid curve 1/1 closed
        //Read and analyse the first line to know the format
        int ch=getc(myfile), num_blank=0;
        while (ch != EOF && ch != '\n'){
            if(ch==' ')
                num_blank++;
            ch=getc(myfile);
        }
        fclose(myfile);
        //cout<<"num_blank="<<num_blank<<endl;

        myfile =fopen(filename, "r");
        int x,y,count=0;
        if(num_blank==0)//Format 1
        {
            P.push_back(vector<Point>());
            vect.push_back(vector<bool>());
            int nbPoint=0;
            fscanf(myfile,"%d\n",&nbPoint);
            while (count<nbPoint)
            {
                fscanf(myfile,"%d %d\n",&x,&y);
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                {
                    P[0].push_back(point);
                    vect[0].push_back(true);
                }
                else
                {
                    cout<<"repeated point "<<point<<endl;
                    vect[0].push_back(false);
                }
                count++;
            }
        }
        else if(num_blank==1)//Format 2
        {
            P.push_back(vector<Point>());
            vect.push_back(vector<bool>());
            while(fscanf(myfile,"%d %d\n",&x,&y)!=EOF)
            {
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                {
                    P[0].push_back(point);
                    vect[0].push_back(true);
                }
                else
                {
                    cout<<"repeated point "<<point<<endl;
                    vect[0].push_back(false);
                }
                count++;
            }
        }
        else if(num_blank==2)//Format 2
        {
            P.push_back(vector<Point>());
            vect.push_back(vector<bool>());
            while(fscanf(myfile,"%d %d \n",&x,&y)!=EOF)
            {
                Point point = Point(x,y);
                vector<Point>::const_iterator it = find(P[0].begin(),P[0].end(),point);
                if(it == P[0].end())
                {
                    P[0].push_back(point);
                    vect[0].push_back(true);
                }
                else
                {
                    cout<<"repeated point "<<point<<endl;
                    vect[0].push_back(false);
                }
                count++;
            }
        }
        else if(num_blank==4)//Format 3
        {
            int id_Contour=0,num_Contour=0;
            char s1[10],s2[10],s3[10];
            fscanf(myfile,"# %s %s %d/%d %s\n",s1,s2,&id_Contour,&num_Contour,s3);
            //cout<<"id_Contour="<<id_Contour<<" and num_Contour="<<num_Contour<<endl;
            for(int id=0; id<num_Contour; id++)
            {
                P.push_back(vector<Point>());
                vect.push_back(vector<bool>());
                int val = fscanf(myfile,"%d %d\n",&x,&y);
                while(val!=EOF && val==2)
                {
                    Point point = Point((int)x,(int)y);
                    vector<Point>::const_iterator it = find(P[id].begin(),P[id].end(),point);
                    if(it == P[id].end())
                    {
                        P[id].push_back(point);
                        vect[id].push_back(true);
                    }
                    else
                    {
                        cout<<"repeated point "<<point<<endl;
                        vect[id].push_back(false);
                    }
                    count++;
                    val = fscanf(myfile,"%d %d\n",&x,&y);
                }
                //cout<<id<<" sequence finish"<<endl;
                fscanf(myfile,"# %s %s %d/%d %s\n",s1,s2,&id_Contour,&num_Contour,s3);
            }
        }
        else
        {
            cout << "Format unknow " <<filename<<endl;
        }
    }
    fclose(myfile);
    return P;
}

vector<Point> readFile(const char* filename, bool header)
{
    vector<Point> P;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        int nbPoint=0,count=0;
        double x=0,y=0;
        if(header)
        {
            myfile >> nbPoint;
            while (count<nbPoint)
            {
                myfile >> x >> y;
                //P.push_back(Point((int)x,(int)y));
                Point point=Point((int)x,(int)y);
                vector<Point>::const_iterator it=find(P.begin(),P.end(),point);
                if(it == P.end())
                    P.push_back(point);
                else
                    cout<<"repeated point "<<point<<endl;
                count++;
            }
        }
        else
        {
            while(myfile >> x >> y)
            {
                //P.push_back(Point((int)x,(int)y));
                Point point=Point((int)x,(int)y);
                vector<Point>::const_iterator it=find(P.begin(),P.end(),point);
                if(it == P.end())
                    P.push_back(point);
                else
                    cout<<"repeated point "<<point<<endl;
                count++;
            }
        }
        myfile.close();
        cout<<count<<" points are read"<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

vector<Point> readFileInverse(const char* filename, bool header)
{
    vector<Point> P;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        int nbPoint=0,count=0;
        double x=0,y=0;
        if(header)
        {
            myfile >> nbPoint;
            while (count<nbPoint)
            {
                myfile >> x >> y;
                Point point=Point((int)x,(int)y);
                vector<Point>::const_iterator it=find(P.begin(),P.end(),point);
                if(it == P.end())
                    P.insert(P.begin(),point);
                count++;
            }
        }
        else
        {
            while(myfile >> x >> y)
            {
                Point point=Point((int)x,(int)y);
                vector<Point>::const_iterator it=find(P.begin(),P.end(),point);
                if(it == P.end())
                    P.insert(P.begin(),point);
                count++;
            }
        }
        myfile.close();
        cout<<count<<" points are read"<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

vector<Point> readFile(const char* filename, int header)
{
    vector<Point> P;
    ifstream myfile (filename);
    string lineTmp;
    if (myfile.is_open())
    {
        int count=0;
        double x=0,y=0;
        for(int i=0; i<header; i++)
            std::getline(myfile, lineTmp);//ignore the lines

        while(myfile >> x >> y)
        {
            //P.push_back(Point((int)x,(int)y));
            Point point=Point((int)x,(int)y);
            vector<Point>::const_iterator it=find(P.begin(),P.end(),point);
            if(it == P.end())
                P.push_back(point);
            else
                cout<<"repeated point "<<point<<endl;
            count++;
        }
        myfile.close();
        cout<<count<<" points are read"<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

//return global
vector<int> readMeanindfulScaleFile(const char* filename)
{
    vector<int> P;
    ifstream myfile (filename);
    string lineTmp;
    if (myfile.is_open())
    {
        int count=0;
        //idx noiselvl code x y
        int i=0,m=0,c=0,x=0,y=0;
        std::getline(myfile, lineTmp);//ignore the first two lines
        std::getline(myfile, lineTmp);
        while(myfile >> i >> m >> c >> x >> y)//idx noiselvl code x y
        {
            P.push_back(m);
            count++;
        }
        myfile.close();
        //cout<<count<<" points are read and globalNoise="<<globalNoise<<endl;
        cout<<count<<" points are read "<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

vector<double> readMeanindfulThicknessFile(const char* filename)
{
    vector<double> P;
    ifstream myfile (filename);
    string lineTmp;
    if (myfile.is_open())
    {
        int count=0;
        //idx noiselvl code x y
        double m=0,x=0,y=0;
        std::getline(myfile, lineTmp);//ignore the first two lines
        std::getline(myfile, lineTmp);
        while(myfile >> x >> y >> m)// X Y noiseLevel
        {
            P.push_back(2.0*m);
            count++;
        }
        myfile.close();
        //cout<<count<<" points are read and globalNoise="<<globalNoise<<endl;
        cout<<count<<" points are read "<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

vector<double> readMeanindfulThicknessFile(const char* filename,const vector<bool>& vect)
{
    vector<double> P;
    ifstream myfile (filename);
    string lineTmp;
    if (myfile.is_open())
    {
        int count=0;
        //idx noiselvl code x y
        double m=0,x=0,y=0;
        std::getline(myfile, lineTmp);//ignore the first two lines
        std::getline(myfile, lineTmp);
        while(myfile >> x >> y >> m)// X Y noiseLevel
        {
            if(vect.at(count)==true)
                P.push_back(2.0*m);
            count++;
        }
        myfile.close();
        //cout<<count<<" points are read and globalNoise="<<globalNoise<<endl;
        cout<<count<<" points are read "<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

double getGlobalNoise(const vector<double>& vect)
{
    double globalNoise=std::accumulate(std::begin(vect), std::end(vect), 0.0);
    globalNoise= globalNoise / vect.size();

    return globalNoise;
}

double getThirdQuartile(const vector<double>& vect)
{
    vector<double> vectSort=vect;
    std::sort(vectSort.begin(),vectSort.end(),sort_increase);
    double median, fstQuartile, thrdQuartile;
    int mid, midFstQuartile, midThrdQuartile;
    //median
    mid=vectSort.size()/2;
    if(vectSort.size()%2==1)
    {
        median=vectSort.at(mid);
        midFstQuartile=mid;
        midThrdQuartile=mid + 1;
    }
    else
    {
        median=(vectSort.at(mid)+vectSort.at(mid-1))/2.0;
        midFstQuartile=mid - 1;
        midThrdQuartile=mid + 1;
    }
    //first quartile
    if(midFstQuartile%2==1)
        fstQuartile=vectSort.at(midFstQuartile/2);
    else
        fstQuartile=(vectSort.at(midFstQuartile/2)+vectSort.at(midFstQuartile/2 - 1))/2.0;
    //third quartile
    if((vectSort.size() - midThrdQuartile)%2==1)
        thrdQuartile=vectSort.at(mid + (vectSort.size() - midThrdQuartile)/2);
    else
        thrdQuartile=(vectSort.at(mid + (vectSort.size() - midThrdQuartile)/2)+vectSort.at(mid + (vectSort.size() - midThrdQuartile)/2 + 1))/2.0;

    return thrdQuartile;
}

vector<double> findVectorElement(const vector<double>& vect)
{
    vector<double> vectElement;
    vectElement.push_back(vect.front());
    for(vector<double>::const_iterator it=vect.begin()+1; it != vect.end(); it++)
    {
        double m=(*it);
        if (std::find(vectElement.begin(), vectElement.end(),m)==vectElement.end())
            vectElement.push_back(m);
    }
    std::sort(vectElement.begin(),vectElement.end(),sort_increase);

    return vectElement;
}

vector<PointD> readSmoothContourFile(const char* filename)
{
    vector<PointD> P;
    ifstream myfile (filename);
    string lineTmp;
    if (myfile.is_open())
    {
        int count=0;
        // Format X Y
        double x=0,y=0;
        std::getline(myfile, lineTmp);//ignore the first two lines
        std::getline(myfile, lineTmp);
        while(myfile >> x >> y)// X Y
        {
            PointD point=PointD((double)x,(double)y);
            P.push_back(point);
            count++;
        }
        myfile.close();
        cout<<count<<" points are read "<<endl;
    }
    else cout << "Unable to open file " <<filename;

    return P;
}

void writeFile(const vector<int>& v, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v.size();
        for(vector<int>::const_iterator it=v.begin(); it != v.end(); it++)
        {
            myfile <<count<<" "<<*it<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

void writeFile(const vector<double>& v, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v.size();
        for(vector<double>::const_iterator it=v.begin(); it != v.end(); it++)
        {
            myfile <<count<<" "<<*it<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

void writeFile(const vector<int>& index_v, const vector<double>& v, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v.size();
        for(size_t i=0; i<index_v.size(); i++)
        {
            myfile <<index_v.at(i)<<" "<<v.at(i)<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

void writeFile(const vector<double>& v1, const vector<double>& v2, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v1.size();
        for(size_t i=0; i<v1.size(); i++)
        {
            myfile <<v1.at(i)<<" "<<v2.at(i)<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

void writeFile(const vector<Point>& v, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v.size()<<endl;
        for(vector<Point>::const_iterator it=v.begin(); it != v.end(); it++)
        {
            //myfile <<count<<" "<<(*it)[0]<<" "<<(*it)[1]<<endl;
            myfile <<(*it)[0]<<" "<<(*it)[1]<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

void writeFile(const vector<PointD>& v, const char* filename, bool header)
{
    int count=0;
    ofstream myfile (filename);
    if (myfile.is_open())
    {
        if(header)
            myfile << v.size();
        for(vector<PointD>::const_iterator it=v.begin(); it != v.end(); it++)
        {
            //myfile <<count<<" "<<(*it)[0]<<" "<<(*it)[1]<<endl;
            myfile <<(*it)[0]<<" "<<(*it)[1]<<endl;
            count++;
        }
        myfile.close();
        //cout<<count<<" points are written"<<endl;
    }
    else cout << "Unable to open file " <<filename;
}

bool myfunction (int i,int j) { return (i<j); }
bool myfunction1 (int i,int j) { return (i>j); }
bool fmyfunction (int i,int j) { return (fabs(i)<fabs(j)); }
bool fmyfunction1 (int i,int j) { return (fabs(i)>fabs(j)); }

vector<int> sortIndex(vector<double> const& values, bool isIncrease)
{
    /*
    vector<int> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<int>(0));

    if(isIncrease)
        std::sort( begin(indices), end(indices), [&](int a, int b) { return values[a]<values[b]; } );
    else//decrease
        std::sort( begin(indices), end(indices), [&](int a, int b) { return values[a]>values[b]; } );
    return indices;
    */
    vector<int> indices;
    for(size_t i=0;i<values.size();i++)
        indices.push_back(i);
    if(isIncrease)
        std::sort ( indices.begin(),  indices.end(), [&](int a, int b) { return values[a]<values[b]; });
    else
        std::sort ( indices.begin(),  indices.end(), [&](int a, int b) { return values[a]>values[b]; });
    return indices;
}

vector<int> absSortIndex(vector<double> const& values, bool isIncrease)
{
    /*
    vector<int> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<int>(0));
    if(isIncrease)
        std::sort( begin(indices), end(indices), [&](int a, int b) { return fabs(values[a])<fabs(values[b]); } );
    else//decrease
        std::sort( begin(indices), end(indices), [&](int a, int b) { return fabs(values[a])>fabs(values[b]); } );
    return indices;
    */
    vector<int> indices;
    for(size_t i=0;i<values.size();i++)
        indices.push_back(i);
    if(isIncrease)
        std::sort ( begin(indices), end(indices), [&](int a, int b) { return fabs(values[a])<fabs(values[b]); });
    else
        std::sort ( begin(indices), end(indices), [&](int a, int b) { return fabs(values[a])>fabs(values[b]); });

    return indices;
}

vector<int> sortIndex(vector<int> const& values, bool isIncrease)
{
    /*
    vector<int> indices(values.size());
    std::iota(begin(indices), end(indices), static_cast<int>(0));

    if(isIncrease)
        std::sort( begin(indices), end(indices), [&](int a, int b) { return values[a]<values[b]; } );
    else//decrease
        std::sort( begin(indices), end(indices), [&](int a, int b) { return values[a]>values[b]; } );
    return indices;
    */
    vector<int> indices;
    for(size_t i=0;i<values.size();i++)
        indices.push_back(i);
    if(isIncrease)
        std::sort ( indices.begin(),  indices.end(), [&](int a, int b) { return values[a]<values[b]; });
    else
        std::sort ( indices.begin(),  indices.end(), [&](int a, int b) { return values[a]>values[b]; });
    return indices;
}

int signeInt(int n)
{
    if(n<0)
        return -1;
    if(n>0)
        return 1;
    return 0;
}

/* signe of vector */
Point directionOfVector(Point N, Point startS, Point endS)
{
    Point N_tmp=N;
    int signNx=1, signNy=1;
    signNx=signeInt(endS[0] - startS[0]);
    signNy=signeInt(endS[1] - startS[1]);
    //N : vector normal => (Nx, Ny)
    //vector of direction => (Ny, -Nx) or (-Ny, Nx)
    if(N[1]*signNx>0) N_tmp[1]=-N[1];
    //if(signNx!= 0) N_tmp[1]=signNx*N[1];
    if(N[0]*signNy<0) N_tmp[0]=-N[0];
    //if(signNy!=0) N_tmp[0]=-signNy*N[0];
    return N_tmp;
}

/* Errors of noisy contours */
Point findIndex(const vector<Point>& aContour, Point p1, Point p2, int idStart=0)
{
    Point p1C=Point(min(p1[0],p2[0]),min(p1[1],p2[1]));
    Point p2C=Point(max(p1[0],p2[0]),max(p1[1],p2[1]));
    int i1=idStart,i2=0;
    bool found=false;
    Point p;
    //while (i1<aContour.size() && !found)//FIXME
    while (i1<(int)aContour.size() && !found)
    {
        p=aContour.at(i1);
        if((p1C[0]<=p[0] && p[0]<=p2C[0]) && (p1C[1]<=p[1] && p[1]<=p2C[1]))
            found=true;
        else
            i1++;
    }
    //if(i1==aContour.size() || found==false)//FIXME
    if(i1==(int)aContour.size() || found==false)
        return Point(-1,-1);
    else
    {
        found=false;
        i2=i1;
        //while (i2<aContour.size() && !found)//FIXME
        while (i2<(int)aContour.size() && !found)
        {
            p=aContour.at(i2);
            if((p1C[0]<=p[0] && p[0]<=p2C[0]) && (p1C[1]<=p[1] && p[1]<=p2C[1]))
                i2++;
            else
                found=true;
        }
        //if((i2==aContour.size() && p2==p) || found==true)//FIXME
        if((i2==(int)aContour.size() && p2==p) || found==true)
            return Point(i1,i2-1);
        return Point(-1,-1);
    }
}

double error_ISE(const vector<Point>& contour, const vector<Point>& DP, bool isClosed)
{
    double ise=0.0, d=0.0;
    Point index=Point(0,0);
    for(size_t it=0; it+1<DP.size(); it++)
    {
        index=findIndex(contour,DP.at(it),DP.at(it+1));//,index[1]
        if(index[0]<0 || index[1]<0)
            ;//cout<<"Pb in error_ISE index of DP"<<endl;
        else
        {
            //cout<<"index[0]="<<index[0]<<", index[1]="<<index[1]<<endl;
            for(int i=index[0]; i<index[1]; i++)
            {
                d=distancePointSegment(contour.at(i),DP.at(it), DP.at(it+1));
                ise += d*d;
            }
        }
    }
    return ise;
}

double error_L_infini(const vector<Point>& contour, const vector<Point>& DP, bool isClosed)
{
    double d_max=0.0, d;
    Point index=Point(0,0);
    for(size_t it=0; it+1<DP.size(); it++)
    {
        index=findIndex(contour,DP.at(it),DP.at(it+1));//,index[1]
        if(index[0]<0 || index[1]<0)
            ;//cout<<"Pb in error_ISE index of DP"<<endl;
        else
        {
            //cout<<"index[0]="<<index[0]<<", index[1]="<<index[1]<<endl;
            for(int i=index[0]; i<index[1]; i++)
            {
                d=distancePointSegment(contour.at(i),DP.at(it), DP.at(it+1));
                if(d>d_max)
                    d_max=d;
            }
        }
    }
    return d_max;
}

void error_All(const vector<Point>& contour, const vector<Point>& DP, bool isClosed)
{
    double cr=error_CR(contour,DP);
    double ise=error_ISE(contour,DP,isClosed);
    double dmax=error_L_infini(contour,DP,isClosed);
    double fom=cr/ise;
    double fom_M=(cr*cr)/ise;
    double fom_ND=(cr*cr*cr)/(ise*dmax);

    cout<<"cr="<<cr<<", ise="<<ise<<", dmax="<<dmax<<", FOM="<<fom<<", FOM_M="<<fom_M<<", FOM_ND="<<fom_ND<<endl;
}

bool isCircle(Point A, Point B, Point C, Point D)
{
    double AC=sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1]));
    double BD=sqrt((B[0]-D[0])*(B[0]-D[0])+(B[1]-D[1])*(B[1]-D[1]));
    double AB=sqrt((B[0]-A[0])*(B[0]-A[0])+(B[1]-A[1])*(B[1]-A[1]));
    double CD=sqrt((C[0]-D[0])*(C[0]-D[0])+(C[1]-D[1])*(C[1]-D[1]));
    double BC=sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1]));
    double AD=sqrt((D[0]-A[0])*(D[0]-A[0])+(D[1]-A[1])*(D[1]-A[1]));
    return AC*BD==AB*CD+BC*AD;//calcul exact possible
}

bool isCircle(PointD A, PointD B, PointD C, PointD D)
{
    double AC=sqrt((C[0]-A[0])*(C[0]-A[0])+(C[1]-A[1])*(C[1]-A[1]));
    double BD=sqrt((B[0]-D[0])*(B[0]-D[0])+(B[1]-D[1])*(B[1]-D[1]));
    double AB=sqrt((B[0]-A[0])*(B[0]-A[0])+(B[1]-A[1])*(B[1]-A[1]));
    double CD=sqrt((C[0]-D[0])*(C[0]-D[0])+(C[1]-D[1])*(C[1]-D[1]));
    double BC=sqrt((B[0]-C[0])*(B[0]-C[0])+(B[1]-C[1])*(B[1]-C[1]));
    double AD=sqrt((D[0]-A[0])*(D[0]-A[0])+(D[1]-A[1])*(D[1]-A[1]));
    return AC*BD==AB*CD+BC*AD;
}
