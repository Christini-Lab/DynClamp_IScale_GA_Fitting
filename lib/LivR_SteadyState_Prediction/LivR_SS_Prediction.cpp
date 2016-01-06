/*** INTRO
 *
 * LivR_SS_Prediction.cpp
 *
 * Predictions the steady-state conditions of the model based on conductance
 * scaling parameters.
 *
 ***/

#include <cmath>

#include "LivR_SS_Prediction.hpp"

double LivR_SS_Prediction::predict_Nai(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][0] * ((log(GNa) - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][0] * ((log(GNab) - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][0] * ((log(GCaL) - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][0] * ((log(GCaT) - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][0] * ((log(GCab) - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][0] * ((log(GK1) - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][0] * ((log(GKr) - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][0] * ((log(GKs) - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][0] * ((log(GKp) - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][0] * ((log(INaK) - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][0] * ((log(kNCX) - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][0] * ((log(alpha_rel) - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][0] * ((log(GpCa) - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][0] * ((log(Gserca) - Xmean_all[13]) / Xstd_all[13])
              ) * std_Nai + mean_Nai);
}

double LivR_SS_Prediction::predict_Ki(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][1] * ((log(GNa) - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][1] * ((log(GNab) - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][1] * ((log(GCaL) - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][1] * ((log(GCaT) - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][1] * ((log(GCab) - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][1] * ((log(GK1) - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][1] * ((log(GKr) - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][1] * ((log(GKs) - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][1] * ((log(GKp) - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][1] * ((log(INaK) - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][1] * ((log(kNCX) - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][1] * ((log(alpha_rel) - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][1] * ((log(GpCa) - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][1] * ((log(Gserca) - Xmean_all[13]) / Xstd_all[13])
              ) * std_Ki + mean_Ki);
}

double LivR_SS_Prediction::predict_Cai(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][2] * ((log(GNa) - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][2] * ((log(GNab) - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][2] * ((log(GCaL) - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][2] * ((log(GCaT) - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][2] * ((log(GCab) - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][2] * ((log(GK1) - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][2] * ((log(GKr) - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][2] * ((log(GKs) - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][2] * ((log(GKp) - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][2] * ((log(INaK) - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][2] * ((log(kNCX) - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][2] * ((log(alpha_rel) - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][2] * ((log(GpCa) - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][2] * ((log(Gserca) - Xmean_all[13]) / Xstd_all[13])
              ) * std_Cai + mean_Cai) / 1e6;
}

double LivR_SS_Prediction::predict_CaJSR(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][3] * ((log(GNa) - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][3] * ((log(GNab) - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][3] * ((log(GCaL) - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][3] * ((log(GCaT) - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][3] * ((log(GCab) - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][3] * ((log(GK1) - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][3] * ((log(GKr) - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][3] * ((log(GKs) - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][3] * ((log(GKp) - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][3] * ((log(INaK) - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][3] * ((log(kNCX) - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][3] * ((log(alpha_rel) - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][3] * ((log(GpCa) - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][3] * ((log(Gserca) - Xmean_all[13]) / Xstd_all[13])
              ) * std_CaJSR + mean_CaJSR);
}

double LivR_SS_Prediction::predict_CaNSR(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  return exp((
      Bpls[0][4] * ((log(GNa) - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][4] * ((log(GNab) - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][4] * ((log(GCaL) - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][4] * ((log(GCaT) - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][4] * ((log(GCab) - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][4] * ((log(GK1) - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][4] * ((log(GKr) - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][4] * ((log(GKs) - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][4] * ((log(GKp) - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][4] * ((log(INaK) - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][4] * ((log(kNCX) - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][4] * ((log(alpha_rel) - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][4] * ((log(GpCa) - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][4] * ((log(Gserca) - Xmean_all[13]) / Xstd_all[13])
              ) * std_CaNSR + mean_CaNSR);
}
