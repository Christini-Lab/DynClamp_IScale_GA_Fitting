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
      Bpls[0][0] * ((GNa - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][0] * ((GNab - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][0] * ((GCaL - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][0] * ((GCaT - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][0] * ((GCab - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][0] * ((GK1 - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][0] * ((GKr - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][0] * ((GKs - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][0] * ((GKp - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][0] * ((INaK - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][0] * ((kNCX - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][0] * ((alpha_rel - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][0] * ((GpCa - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][0] * ((Gserca - Xmean_all[13]) / Xstd_all[13])
              ) * std_Nai + mean_Nai);
}

double LivR_SS_Prediction::predict_Ki(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][1] * ((GNa - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][1] * ((GNab - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][1] * ((GCaL - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][1] * ((GCaT - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][1] * ((GCab - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][1] * ((GK1 - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][1] * ((GKr - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][1] * ((GKs - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][1] * ((GKp - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][1] * ((INaK - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][1] * ((kNCX - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][1] * ((alpha_rel - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][1] * ((GpCa - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][1] * ((Gserca - Xmean_all[13]) / Xstd_all[13])
              ) * std_Ki + mean_Ki);
}

double LivR_SS_Prediction::predict_Cai(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][2] * ((GNa - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][2] * ((GNab - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][2] * ((GCaL - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][2] * ((GCaT - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][2] * ((GCab - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][2] * ((GK1 - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][2] * ((GKr - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][2] * ((GKs - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][2] * ((GKp - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][2] * ((INaK - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][2] * ((kNCX - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][2] * ((alpha_rel - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][2] * ((GpCa - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][2] * ((Gserca - Xmean_all[13]) / Xstd_all[13])
              ) * std_Cai + mean_Cai) / 1e6;
}

double LivR_SS_Prediction::predict_CaJSR(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  // Alpha_rel is not modified, and set to 1.0
  return exp((
      Bpls[0][3] * ((GNa - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][3] * ((GNab - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][3] * ((GCaL - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][3] * ((GCaT - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][3] * ((GCab - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][3] * ((GK1 - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][3] * ((GKr - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][3] * ((GKs - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][3] * ((GKp - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][3] * ((INaK - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][3] * ((kNCX - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][3] * ((alpha_rel - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][3] * ((GpCa - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][3] * ((Gserca - Xmean_all[13]) / Xstd_all[13])
              ) * std_CaJSR + mean_CaJSR);
}

double LivR_SS_Prediction::predict_CaNSR(
    double GNa, double GNab, double GCaL, double GCaT, double GCab, double GK1,
    double GKr, double GKs, double GKp, double INaK, double kNCX, double GpCa,
    double Gserca) {
  return exp((
      Bpls[0][4] * ((GNa - Xmean_all[0]) / Xstd_all[0]) +
      Bpls[1][4] * ((GNab - Xmean_all[1]) / Xstd_all[1]) +
      Bpls[2][4] * ((GCaL - Xmean_all[2]) / Xstd_all[2]) +
      Bpls[3][4] * ((GCaT - Xmean_all[3]) / Xstd_all[3]) +
      Bpls[4][4] * ((GCab - Xmean_all[4]) / Xstd_all[4]) +
      Bpls[5][4] * ((GK1 - Xmean_all[5]) / Xstd_all[5]) +
      Bpls[6][4] * ((GKr - Xmean_all[6]) / Xstd_all[6]) +
      Bpls[7][4] * ((GKs - Xmean_all[7]) / Xstd_all[7]) +
      Bpls[8][4] * ((GKp - Xmean_all[8]) / Xstd_all[8]) +
      Bpls[9][4] * ((INaK - Xmean_all[9]) / Xstd_all[9]) +
      Bpls[10][4] * ((kNCX - Xmean_all[10]) / Xstd_all[10]) +
      Bpls[11][4] * ((alpha_rel - Xmean_all[11]) / Xstd_all[11]) +
      Bpls[12][4] * ((GpCa - Xmean_all[12]) / Xstd_all[12]) +
      Bpls[13][4] * ((Gserca - Xmean_all[13]) / Xstd_all[13])
              ) * std_CaNSR + mean_CaNSR);
}
