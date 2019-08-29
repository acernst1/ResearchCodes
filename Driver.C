{
//void xsec(TString dataFilePath, TString fluxFilePath, TString mcFilePath, TString thrownFilePath1, TString thrownFilePath2, TString thrownFilePath3)
gROOT->ProcessLine(".x xsec.C(\"kpkpxim_wf_2017_new.root\",\"flux_30274_31057.root\",\"./requestedMC/kpkpxim__B4_M23_genr8.root\",\"./requestedMC/thrown/tree_thrown_genr8_0302_306.root\",\"./requestedMC/thrown/tree_thrown_genr8_0307_309.root\",\"./requestedMC/thrown/tree_thrown_genr8_0310.root\" )");
}
