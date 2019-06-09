#ifndef DTW_HPP_
#define DTW_HPP_

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <tuple>
#include <vector>

namespace dtw {

double distance(double y1, double y2);
double dtw(double series1[], int len1, double series2[], int len2, double c);

} // namespace dtw

#endif // DTW_HPP_