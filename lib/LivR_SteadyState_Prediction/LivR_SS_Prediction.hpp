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
    {-0.00604772217281899, 0.0127302619391436, 0.0272444101570233,
     0.0798348694018977, 0.0298730873035144},
    {0.210621984652347, -0.214680832157151, 0.164735865029053,
     0.0931402080068089, 0.112198212913738},
    {0.178976006404672, -0.181252409458966, 0.371714182374934,
     0.328378512128941, 0.418630004208874},
    {0.018628773473795, -0.0130155898245991, 0.0186244035088969,
     0.0438729591750543, 0.0376370254007174},
    {0.187986206806352, -0.222413355505939, 0.407946862044175,
     0.314196486445806, 0.320423477138305},
    {0.0728312706709435, -0.0913215991627867, 0.0231853413245945,
     0.0166449514066237, 0.0180918411401758},
    {0.0634895506343454, -0.0595515797786012, -0.0148293517523075,
     -0.0626049656496512, -0.0370576783940498},
    {0.0739676421436068, -0.0742356904865949, -0.0365849684147182,
     -0.0733173450446005, -0.0690537856152055},
    {0.0135427921905585, 0.000451666302720314, 0.00193758309999631,
     -0.0159189707856815, -0.014914208348055},
    {-0.89123408055925, 0.835788635743391, -0.54955040724531,
     -0.359975152977494, -0.405823992628121},
    {0.202913722746916, -0.17043365548845, -0.249900633080528,
     -0.224004098126868, -0.219685113306807},
    {-0.0152035097172769, 0.0235561059478314, -0.0575963557904543,
     -0.179698384626973, -0.0842133354040842},
    {-0.15856846382645, 0.183556431130255, -0.367337938220922,
     -0.311937022920722, -0.320723455435665},
    {-0.0417243201391387, 0.0222692111359484, 0.178005701323169,
     0.524876795096936, 0.476018940721839},
  };

  // Means of un-transformed parameters from population used to create Bpls
  // (source population)
  const double Xmean_all[14] = {
    1.13388884798518, 1.0905682015875, 1.08257556631704, 1.07920741511571,
    1.05557841739646, 1.09167592316274, 1.08981771562501, 1.09994789060509,
    1.04715369200318, 1.06786503723479, 1.05323575265383, 1.03600637261871,
    1.08734387654737, 1.11844846869089
  };
  // Standard deviations of un-transformed parameters from source population
  const double Xstd_all[14] = {
    0.465640438180291, 0.435176710704605, 0.437498065901692, 0.408259256607783,
    0.440335461090714, 0.442214412816424, 0.437914105559293, 0.435807565966675,
    0.450230254863058, 0.422297875539267, 0.438687436779493, 0.439231482648116,
    0.461686300531073, 0.468755564331666
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
