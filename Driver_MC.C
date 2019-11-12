void Driver_MC(int runnumber){
	char file[100];
	sprintf(file, "TFile *_file0 = TFile::Open(\"./../trees/tree_kpkpxim__B4_M23_genr8_0%d.root\")",runnumber);
	gROOT->ProcessLine(file);
	gROOT->ProcessLine(".x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C");
	gROOT->ProcessLine("kpkpxim__B4_M23_Tree->Process(\"$ACECODE/DSelector_kpkpxim__B4_M23_sept19.C+\")");
	gROOT->ProcessLine(".q");
}
