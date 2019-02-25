#ifndef TESTFUNCTION
#define TESTFUNCTION

#include <iostream>
#include <exception>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"
#include "DGtal/geometry/curves/estimation/LambdaMST2D.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
#include "DGtal/base/Circulator.h"

#include "maximalblurredsegment.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;

#define IS_PLOT false
//#define DRAW_LINE
#define FILENAMESIZE 200

/*** Burred segments decomposition ***/
vector<MaximalBlurredSegment> blurredSegmentCurveDecomposition(const vector<Point>& aContour, double thickness, bool isClosed, const char* filename, bool verbose);
vector<vector<MaximalBlurredSegment> > blurredSegmentCurveDecomposition(const vector<vector<Point> > &aContour, double thickness, bool isClosed=false, const char* filename=NULL, bool verbose=false);
/*** Burred segments decomposition ***/

/*** Adaptative tangent cover decomposition ***/
vector<vector<MaximalBlurredSegment> > adaptiveTangentCoverCurveDecomposition(const vector<vector<Point> > &aContour, const vector<vector<double> > &vecMT,  bool isClosed=false, const char* filename=NULL, bool eps=false);
/*** Adaptative tangent cover decomposition ***/

/*** Modified tangent cover computation ***/
vector<vector<MaximalBlurredSegment> > modifiedTangentCoverCurveDecomposition(const vector<vector<Point> >& aContour, const vector<vector<double> >& vecMT, bool isClosed, const char* filename=NULL, bool eps=false);
/*** Modified tangent cover computation ***/

/**** Dominant points detections ****/
vector<vector<Point> > testDominantPointOnShape(const vector<vector<MaximalBlurredSegment> > &fuzzySegmentSet, const vector<vector<Point> > &aContour, bool isSymmetry, bool isClosed, const char* filename=NULL, bool verbose=false, bool eps=false);
/**** Dominant points detections ****/

/**** Dominant points selection ****/
vector<vector<Point> > testDominantPointSelection(const vector<vector<Point> > &DP, const vector<vector<int> > &indexDP, const vector<vector<Point> > &aContour, bool isClosed, const char* filename=NULL, bool verbose=false, bool eps=false); /* by max Error crierion FOM1/FOM2/FOM3/FOM_ND */
vector<vector<Point> > testDominantPointSelection(const vector<vector<Point> > &DP, const vector<vector<int> > &indexDP, const vector<vector<Point> > &aContour, double angleTol, bool isClosed, const char* filename=NULL, bool verbose=false, bool eps=false); /* by max Error crierion FOM1/FOM2/FOM3/FOM_ND */
/**** Dominant points selection ****/

#endif // TESTFUNCTION

