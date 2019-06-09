
#include "dtw.hpp"

namespace dtw {

double distance(double y1, double y2) {
  double diff = abs(y1 - y2);
  return diff * diff;
} // distance

double dtw(double series1[], int len1, double series2[], int len2, double c) {
  double inf = std::numeric_limits<double>::infinity();
  int len1_ = len1 + 1;
  int len2_ = len2 + 1;
  double c1 = len1 * c + 1;
  double c2 = len2 * c + 1;
  double step1 = (double)len1 / len2;
  double step2 = (double)len2 / len1;

  // 1. distance matrix
  double dists[len1_][len2_];
  dists[0][0] = inf;
  for (int i = 1; i < len1_; ++i) {
    dists[i][0] = inf;
  } // for
  for (int j = 1; j < len2_; ++j) {
    dists[0][j] = inf;
  } // for
  for (int i = 1; i < len1_; ++i) {
    for (int j = 1; j < len2_; ++j) {
      if (i >= c1 + (int)((j - 1) * step1) ||
          j >= c2 + (int)((i - 1) * step2)) {
        dists[i][j] = inf;
      } else {
        dists[i][j] = distance(series1[i - 1], series2[j - 1]);
      } // else
    }   // for j
  }     // for i

  // 2. accumulated minumum matrix
  for (int j = 2; j < len2_; ++j) {
    dists[1][j] += dists[1][j - 1];
  } // for j
  for (int i = 2; i < len1_; ++i) {
    for (int j = 1; j < len2_; ++j) {
      double vals[] = {dists[i - 1][j], dists[i][j - 1], dists[i - 1][j - 1]};
      dists[i][j] += *std::min_element(vals, vals + 3);
    } // for j
  }   // for i

  return dists[len1][len2] / (len1 + len2);
} // dtw

} // namespace dtw
