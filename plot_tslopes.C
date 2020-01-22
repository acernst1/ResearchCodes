void plot_tslopes() {
	TFile * data201701 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2017-01_ANAver20_347runs_jan02.root");
	TFile * data201801 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_jan02.root");
	TFile * data201808 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_jan02.root");

	TFile * filetslope14 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope14.root");
	TFile * filetslope15 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope15.root");
	TFile * filetslope16 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope16.root");
	TFile * filetslope17 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope17.root");
	TFile * filetslope18 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope18.root");
	TFile * filetslope19 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope19.root");
	TFile * filetslope20 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope20.root");
	TFile * filetslope25 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope25.root");
	TFile * filetslope30 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope30.root");
	TFile * filetslope35 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope35.root");
	TFile * filetslope40 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope40.root");

	TFile * throwntslope14 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope14.root");
	TFile * throwntslope15 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope15.root");
	TFile * throwntslope16 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope16.root");
	TFile * throwntslope17 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope17.root");
	TFile * throwntslope18 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope18.root");
	TFile * throwntslope19 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope19.root");
	TFile * throwntslope20 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope20.root");
	TFile * throwntslope25 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope25.root");
	TFile * throwntslope30 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope30.root");
	TFile * throwntslope35 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope35.root");
	TFile * throwntslope40 = TFile::Open("/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/thrown_kpkpxim__B4_M23_genr8_2018-08_ANAver02_tslope40.root");

	char tdistname[100];
	TCanvas *cctdist = new TCanvas("cctdist", "cctdist", 800, 600);
	TH2F * XiMassKinFit_Egamma_t188 = (TH2F*)data201808->Get("Xi_t");
	TH2F * XiMassKinFit_Egamma_t188_acc = (TH2F*)data201808->Get("Xi_t_acc");
	TH2F * XiMassKinFit_Egamma_t188_accsub = (TH2F *) XiMassKinFit_Egamma_t188->Clone("XiMassKinFit_Egamma_t188_accsub");
	XiMassKinFit_Egamma_t188_accsub->Add(XiMassKinFit_Egamma_t188_acc,-0.5);
	TH1F * t188 = (TH1F *)XiMassKinFit_Egamma_t188_accsub->ProjectionY("t188",XiMassKinFit_Egamma_t188_accsub->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t188_accsub->GetXaxis()->FindBin(1.34));

	TH2F * XiMassKinFit_Egamma_t14MC = (TH2F*)filetslope14->Get("Xi_t");
	TH1F * t14MC = (TH1F *)XiMassKinFit_Egamma_t188MC_accsub->ProjectionY("t4MC",XiMassKinFit_Egamma_t14MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t14MC->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t14MC_Truth = (TH2F*)filetslope14->Get("Xi_t_Truth");
	TH1F * t14MC_Truth = (TH1F *)XiMassKinFit_Egamma_t14MC_Truth->ProjectionY("t14MC_Truth",XiMassKinFit_Egamma_t14MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t14MC_Truth->GetXaxis()->FindBin(1.34));
	t14MC->RebinX(5);
	t14MC->SetLineColor(kBlue);
	t14MC->SetTitle("");
	t14MC->GetYaxis()->SetTitle("Combos");
	t14MC->Draw();
	auto legend_datamc = new TLegend(0.70,0.8,0.98,0.93);
	legend_datamc->AddEntry(t188,"2018-08_ANAver02 data","lep");
	legend_datamc->AddEntry(t14MC,"MC tslope = 1.4","lep");
	legend_datamc->Draw();
	sprintf(tdistname,"tdist_2018-08_varyingtslopes.png",);
	cct188dist->Print(tdistname);

}
