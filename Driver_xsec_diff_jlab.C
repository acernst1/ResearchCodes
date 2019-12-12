{
//void xsec(TString dataFilePath, TString fluxFilePath, TString mcFilePath, TString thrownFilePath1, TString thrownFilePath2, TString thrownFilePath3)
//gROOT->ProcessLine(".x xsec.C(\"kpkpxim_wf_2017_new.root\",\"flux_30274_31057.root\",\"./requestedMC/kpkpxim__B4_M23_genr8.root\",\"./requestedMC/thrown/tree_thrown_genr8_0302_306.root\" )");
//gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-01_new.root\",\"/cache/halld/home/acernst/data/flux_40856_42577.root\",\"/cache/halld/home/acernst/MC/2018-01_ANAver03/kpkpxim__B4_M23_2018-01_ANAver03_genr8.root\",\"/cache/halld/home/acernst/MC/2018-01_ANAver03/tree_thrown_genr8_2018-01_ANAver03.root\",\"2018-01_ANAver03\" )");
gROOT->ProcessLine(".x $ACECODE/xsec_diff.C(\"/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-08_nov22.root\",\"/cache/halld/home/acernst/data/flux_50685_51768.root\",\"/cache/halld/home/acernst/MC/2018-08_ANAver02/kpkpxim__B4_M23_2018-08_ANAver02_genr8.root\",\"/cache/halld/home/acernst/MC/2018-08_ANAver02/thrown_kpkpxim.root\",\"2018-08_ANAver02\" )");
}
