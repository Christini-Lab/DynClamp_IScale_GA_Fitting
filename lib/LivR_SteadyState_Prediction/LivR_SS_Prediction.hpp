/*** INTRO
 *
 * LivR_SS_Prediction.hpp
 *
 * Predictions the steady-state conditions of the model based on conductance
 * scaling parameters.
 *
 ***/

class LivR_SS_Prediction {
 public:
  LivR_SS_Prediction() {};
  ~LivR_SS_Prediction() {};

  double predict_Nai(double, double, double, double, double, double, double,
                     double, double, double, double, double, double);
  double predict_Ki(double, double, double, double, double, double, double,
                    double, double, double, double, double, double);
  double predict_Cai(double, double, double, double, double, double, double,
                     double, double, double, double, double, double);
  double predict_CaJSR(double, double, double, double, double, double, double,
                       double, double, double, double, double, double);
  double predict_CaNSR(double, double, double, double, double, double, double,
                       double, double, double, double, double, double);

 private:
  // Matrix to predict 5 concentrations from 14 parameter scale factors (all
  // log-transformed).
  const double Bpls[14][5] = {
    {0.0243688050906311, -0.017168938869489, 0.040812207325678,
     0.10218232818167, 0.0479027701944269},
    {0.201078386536598, -0.213407600439858, 0.164176030352628,
     0.0967089488885253, 0.112865386010599},
    {0.189761171938377, -0.189206967360087, 0.385389190039954,
     0.32909303160785, 0.430548296926269},
    {0.00795385237490631, -0.0038631335775844, 0.00732387953934647,
     0.0259423172306477, 0.0226145101709291},
    {0.182907114051726, -0.219685595311772, 0.40103229094216,
     0.307899107574248, 0.316635307740201},
    {0.0756160345058463, -0.0928306520596124, 0.0128231728610962,
     0.00395929273472639, 0.00308529926567137},
    {0.0468095947771349, -0.042472465376618, -0.0386221258006959,
     -0.0748808248436095, -0.0561519367411381},
    {0.0769717979100198, -0.0784642803652744, -0.0483732602387792,
     -0.0816763827614118, -0.0800205730775937},
    {0.0335409374008689, -0.0200467993337881, 0.0235411698152877,
     0.000944022046749046, 0.010523204889242},
    {-0.914080585159506, 0.902615099838274, -0.594163559626884,
     -0.406472350784344, -0.440204953677725},
    {0.246166306511051, -0.206941263263394, -0.235407321042465,
     -0.214140924654253, -0.206299289074962},
    {-0.0142368265208928, 0.0218221672341253, -0.0588109845146705,
     -0.192287794961176, -0.08714856806397},
    {-0.158666618706937, 0.19373228289662, -0.364130050862198,
     -0.318496203408904, -0.319394299502711},
    {-0.0360409332939269, 0.0193355684333516, 0.152311341935872,
     0.534155358827419, 0.498347696210971}
  };

  // Means of log-transformed parameters from population used to create Bpls
  // (source population)
  const double Xmean_all[14] = {
    0.0497890012969638, 0.015618406055183, -0.000943336033734523,
    0.0114069784509712, -0.024594427534407, 0.00853894405249672,
    0.00509566599339127, 0.0171361857438691, -0.0414926145199833,
    -0.00690227783926231, -0.0343025770475656, -0.0508378553806951,
    -0.00131307535220171, 0.0318667092501497
  };

  // Standard deviations of log-transformed parameters from source population
  const double Xstd_all[14] = {
    0.397906832013667, 0.381101864675594, 0.398372610412821,
    0.367938250378842, 0.401967268258348, 0.400248889568829,
    0.402623825455435, 0.395643189200996, 0.412856642883163,
    0.385490084297738, 0.413418952111769, 0.393421655181335,
    0.407729675893004, 0.408484484829309
  };

  // From source population
  // Standard deviation of log(Nai)
  const double std_Nai = 0.257479453353149;
  // Standard deviation of log(Ki)
  const double std_Ki = 0.0274581206956115;
  // Standard deviation of log(Cai)
  const double std_Cai = 0.413114780194052;
  // Standard deviation of log(CaJSR)
  const double std_CaJSR = 0.371768377155022;
  // Standard deviation of log(CaNSR)
  const double std_CaNSR = 0.307120893750645;

  // Mean of log(Nai)
  const double mean_Nai = 2.62114693232696;
  // Mean of log(Ki)
  const double mean_Ki = 4.90958929805788;
  // Mean of log(Cai)
  const double mean_Cai = 5.28934549199569;
  // Mean of log(CaJSR)
  const double mean_CaJSR = 0.591689745847846;
  // Mean of log(CaNSR)
  const double mean_CaNSR = 0.94805098222702;

  // Following conductances are not modified from nominal values
  const double alpha_rel = 1.0;
};
