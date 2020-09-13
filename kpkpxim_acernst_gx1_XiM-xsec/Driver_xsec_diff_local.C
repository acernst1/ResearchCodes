{
//xsec_diff(TString dataFilePath, const char fluxFilePathtemp[100], TString mcFilePath, TString thrownFilePath,const char version[50], double minEval, const int numEBins)

cout << "2017-01_ANAver20: Egamma bin start 6.4; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",	\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\", \"2017_01_ANAver20_waccnoMC_july20\", 6.4, 10)");

/*
cout << "2017-01_ANAver20: Egamma bin start 6.4; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",	\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\",	\"2017_01_ANAver20_wacc_june13\",6.4,10)");
cout << "2017-01_ANAver20: Egamma bin start 6.4; 15 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",		\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\",	\"2017_01_ANAver20_wacc_june13\",6.4,15)");
cout << "2017-01_ANAver20: Egamma bin start 6.4; 20 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",	\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\",	\"2017_01_ANAver20_wacc_june13\",6.4,20)");

cout << "2018-01_ANAver03: Egamma bin start 6.4; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_june12.root\",\"~/2020xsec_workfest/flux_2018_01_40856_42577_543runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_01_ANAver03_june12.root\",	\"~/2020xsec_workfest/thrown_2018-01_ANAver03_june12.root\",	\"2018_01_ANAver03_wacc_june13\",6.4,10)");
cout << "2018-01_ANAver03: Egamma bin start 6.4; 15 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_june12.root\",\"~/2020xsec_workfest/flux_2018_01_40856_42577_543runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_01_ANAver03_june12.root\",	\"~/2020xsec_workfest/thrown_2018-01_ANAver03_june12.root\",	\"2018_01_ANAver03_wacc_june13\",6.4,15)");
cout << "2018-01_ANAver03: Egamma bin start 6.4; 20 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_june12.root\",\"~/2020xsec_workfest/flux_2018_01_40856_42577_543runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_01_ANAver03_june12.root\",	\"~/2020xsec_workfest/thrown_2018-01_ANAver03_june12.root\",	\"2018_01_ANAver03_wacc_june13\",6.4,20)");

cout << "2018-08_ANAver02: Egamma bin start 6.4; 10 bins" << endl;	
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_june12.root\",\"~/2020xsec_workfest/flux_2018_08_50677_51768_449runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_08_ANAver02_june12.root\",	\"~/2020xsec_workfest/thrown_2018-08_ANAver02_june12.root\",	\"2018_08_ANAver02_wacc_june13\",6.4,10)");
cout << "2018-08_ANAver02: Egamma bin start 6.4; 15 bins" << endl;	
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_june12.root\",\"~/2020xsec_workfest/flux_2018_08_50677_51768_449runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_08_ANAver02_june12.root\",	\"~/2020xsec_workfest/thrown_2018-08_ANAver02_june12.root\",	\"2018_08_ANAver02_wacc_june13\",6.4,15)");
cout << "2018-08_ANAver02: Egamma bin start 6.4; 20 bins" << endl;	
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_june12.root\",\"~/2020xsec_workfest/flux_2018_08_50677_51768_449runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_08_ANAver02_june12.root\",	\"~/2020xsec_workfest/thrown_2018-08_ANAver02_june12.root\",	\"2018_08_ANAver02_wacc_june13\",6.4,20)");
*/
	/*
cout << "2017-01_ANAver20: Egamma bin start 6.5; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",	\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\",	\"2017_01_ANAver20_wacc_june13\",6.5,10)");
cout << "2017-01_ANAver20: Egamma bin start 6.3; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2017-01_june13.root\",	\"~/2020xsec_workfest/flux_2017_01_30274_31057_347runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2017_01_ANAver20_june13.root\",	\"~/2020xsec_workfest/thrown_2017-01_ANAver20_june13.root\",	\"2017_01_ANAver20_wacc_june13\",6.3,10)");
*/
/*
cout << "2018-01_ANAver03: Egamma bin start 6.3; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_june13.root\",	\"~/2020xsec_workfest/flux_2018_01_40856_42577_543runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_01_ANAver03_june13.root\",	\"~/2020xsec_workfest/thrown_2018-01_ANAver03_june13.root\",	\"2018_01_ANAver03_wacc_june13\",6.3,10)");

cout << "2018-08_ANAver02: Egamma bin start 6.3; 10 bins" << endl;	
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_june13.root\",	\"~/2020xsec_workfest/flux_2018_08_50677_51768_449runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_08_ANAver02_june13.root\",	\"~/2020xsec_workfest/thrown_2018-08_ANAver02_june13.root\",	\"2018_08_ANAver02_wacc_june13\",6.3,10)");

cout << "2018-01_ANAver03: Egamma bin start 6.5; 10 bins" << endl;
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_june13.root\",	\"~/2020xsec_workfest/flux_2018_01_40856_42577_543runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_01_ANAver03_june13.root\",	\"~/2020xsec_workfest/thrown_2018-01_ANAver03_june13.root\",	\"2018_01_ANAver03_wacc_june13\",6.5,10)");

cout << "2018-08_ANAver02: Egamma bin start 6.5; 10 bins" << endl;	
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"~/2020xsec_workfest/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_june13.root\",	\"~/2020xsec_workfest/flux_2018_08_50677_51768_449runs_jan03\",	\"~/2020xsec_workfest/kpkpxim__B4_M23_genr8_2018_08_ANAver02_june13.root\",	\"~/2020xsec_workfest/thrown_2018-08_ANAver02_june13.root\",	\"2018_08_ANAver02_wacc_june13\",6.5,10)");
*/

}
