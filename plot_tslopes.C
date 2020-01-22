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

//2017-01 data
	TH2F * XiMassKinFit_Egamma_t171 = (TH2F*)data201701->Get("Xi_t");
	TH2F * XiMassKinFit_Egamma_t171_acc = (TH2F*)data201701->Get("Xi_t_acc");
	TH2F * XiMassKinFit_Egamma_t171_accsub = (TH2F *) XiMassKinFit_Egamma_t171->Clone("XiMassKinFit_Egamma_t171_accsub");
	XiMassKinFit_Egamma_t171_accsub->Add(XiMassKinFit_Egamma_t171_acc,-0.5);
	TH1F * t171 = (TH1F *)XiMassKinFit_Egamma_t171_accsub->ProjectionY("t171",XiMassKinFit_Egamma_t171_accsub->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t171_accsub->GetXaxis()->FindBin(1.34));
//2018-01 data
	TH2F * XiMassKinFit_Egamma_t181 = (TH2F*)data201801->Get("Xi_t");
	TH2F * XiMassKinFit_Egamma_t181_acc = (TH2F*)data201801->Get("Xi_t_acc");
	TH2F * XiMassKinFit_Egamma_t181_accsub = (TH2F *) XiMassKinFit_Egamma_t181->Clone("XiMassKinFit_Egamma_t181_accsub");
	XiMassKinFit_Egamma_t181_accsub->Add(XiMassKinFit_Egamma_t181_acc,-0.5);
	TH1F * t181 = (TH1F *)XiMassKinFit_Egamma_t181_accsub->ProjectionY("t181",XiMassKinFit_Egamma_t181_accsub->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t181_accsub->GetXaxis()->FindBin(1.34));
//2018-08 data
	TH2F * XiMassKinFit_Egamma_t188 = (TH2F*)data201808->Get("Xi_t");
	TH2F * XiMassKinFit_Egamma_t188_acc = (TH2F*)data201808->Get("Xi_t_acc");
	TH2F * XiMassKinFit_Egamma_t188_accsub = (TH2F *) XiMassKinFit_Egamma_t188->Clone("XiMassKinFit_Egamma_t188_accsub");
	XiMassKinFit_Egamma_t188_accsub->Add(XiMassKinFit_Egamma_t188_acc,-0.5);
	TH1F * t188 = (TH1F *)XiMassKinFit_Egamma_t188_accsub->ProjectionY("t188",XiMassKinFit_Egamma_t188_accsub->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t188_accsub->GetXaxis()->FindBin(1.34));
//reconstructed MC tests for 2018-08
	TH2F * XiMassKinFit_Egamma_t14MC = (TH2F*)filetslope14->Get("Xi_t");
	TH1F * t14MC = (TH1F *)XiMassKinFit_Egamma_t14MC->ProjectionY("t14MC",XiMassKinFit_Egamma_t14MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t14MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t15MC = (TH2F*)filetslope15->Get("Xi_t");
	TH1F * t15MC = (TH1F *)XiMassKinFit_Egamma_t15MC->ProjectionY("t15MC",XiMassKinFit_Egamma_t15MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t15MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t16MC = (TH2F*)filetslope16->Get("Xi_t");
	TH1F * t16MC = (TH1F *)XiMassKinFit_Egamma_t16MC->ProjectionY("t16MC",XiMassKinFit_Egamma_t16MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t16MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t17MC = (TH2F*)filetslope17->Get("Xi_t");
	TH1F * t17MC = (TH1F *)XiMassKinFit_Egamma_t17MC->ProjectionY("t17MC",XiMassKinFit_Egamma_t17MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t17MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t18MC = (TH2F*)filetslope18->Get("Xi_t");
	TH1F * t18MC = (TH1F *)XiMassKinFit_Egamma_t18MC->ProjectionY("t18MC",XiMassKinFit_Egamma_t18MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t18MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t19MC = (TH2F*)filetslope19->Get("Xi_t");
	TH1F * t19MC = (TH1F *)XiMassKinFit_Egamma_t19MC->ProjectionY("t19MC",XiMassKinFit_Egamma_t19MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t19MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t20MC = (TH2F*)filetslope20->Get("Xi_t");
	TH1F * t20MC = (TH1F *)XiMassKinFit_Egamma_t20MC->ProjectionY("t20MC",XiMassKinFit_Egamma_t20MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t20MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t25MC = (TH2F*)filetslope25->Get("Xi_t");
	TH1F * t25MC = (TH1F *)XiMassKinFit_Egamma_t25MC->ProjectionY("t25MC",XiMassKinFit_Egamma_t25MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t25MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t30MC = (TH2F*)filetslope30->Get("Xi_t");
	TH1F * t30MC = (TH1F *)XiMassKinFit_Egamma_t30MC->ProjectionY("t30MC",XiMassKinFit_Egamma_t30MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t30MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t35MC = (TH2F*)filetslope35->Get("Xi_t");
	TH1F * t35MC = (TH1F *)XiMassKinFit_Egamma_t35MC->ProjectionY("t35MC",XiMassKinFit_Egamma_t35MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t35MC->GetXaxis()->FindBin(1.34));
	TH2F * XiMassKinFit_Egamma_t40MC = (TH2F*)filetslope40->Get("Xi_t");
	TH1F * t40MC = (TH1F *)XiMassKinFit_Egamma_t40MC->ProjectionY("t40MC",XiMassKinFit_Egamma_t40MC->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t40MC->GetXaxis()->FindBin(1.34));
//MC Truth tslope tests for 2018-08
 	TH2F * XiMassKinFit_Egamma_t14MC_Truth = (TH2F*)filetslope14->Get("Xi_t_Truth");
	TH1F * t14MC_Truth = (TH1F *)XiMassKinFit_Egamma_t14MC_Truth->ProjectionY("t14MC_Truth",XiMassKinFit_Egamma_t14MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t14MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t15MC_Truth = (TH2F*)filetslope15->Get("Xi_t_Truth");
	TH1F * t15MC_Truth = (TH1F *)XiMassKinFit_Egamma_t15MC_Truth->ProjectionY("t15MC_Truth",XiMassKinFit_Egamma_t15MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t15MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t16MC_Truth = (TH2F*)filetslope16->Get("Xi_t_Truth");
	TH1F * t16MC_Truth = (TH1F *)XiMassKinFit_Egamma_t16MC_Truth->ProjectionY("t16MC_Truth",XiMassKinFit_Egamma_t16MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t16MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t17MC_Truth = (TH2F*)filetslope17->Get("Xi_t_Truth");
	TH1F * t17MC_Truth = (TH1F *)XiMassKinFit_Egamma_t17MC_Truth->ProjectionY("t17MC_Truth",XiMassKinFit_Egamma_t17MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t17MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t18MC_Truth = (TH2F*)filetslope18->Get("Xi_t_Truth");
	TH1F * t18MC_Truth = (TH1F *)XiMassKinFit_Egamma_t18MC_Truth->ProjectionY("t18MC_Truth",XiMassKinFit_Egamma_t18MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t18MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t19MC_Truth = (TH2F*)filetslope19->Get("Xi_t_Truth");
	TH1F * t19MC_Truth = (TH1F *)XiMassKinFit_Egamma_t19MC_Truth->ProjectionY("t19MC_Truth",XiMassKinFit_Egamma_t19MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t19MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t20MC_Truth = (TH2F*)filetslope20->Get("Xi_t_Truth");
	TH1F * t20MC_Truth = (TH1F *)XiMassKinFit_Egamma_t20MC_Truth->ProjectionY("t20MC_Truth",XiMassKinFit_Egamma_t20MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t20MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t25MC_Truth = (TH2F*)filetslope25->Get("Xi_t_Truth");
	TH1F * t25MC_Truth = (TH1F *)XiMassKinFit_Egamma_t25MC_Truth->ProjectionY("t25MC_Truth",XiMassKinFit_Egamma_t25MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t25MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t30MC_Truth = (TH2F*)filetslope30->Get("Xi_t_Truth");
	TH1F * t30MC_Truth = (TH1F *)XiMassKinFit_Egamma_t30MC_Truth->ProjectionY("t30MC_Truth",XiMassKinFit_Egamma_t30MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t30MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t35MC_Truth = (TH2F*)filetslope35->Get("Xi_t_Truth");
	TH1F * t35MC_Truth = (TH1F *)XiMassKinFit_Egamma_t35MC_Truth->ProjectionY("t35MC_Truth",XiMassKinFit_Egamma_t35MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t35MC_Truth->GetXaxis()->FindBin(1.34));
 	TH2F * XiMassKinFit_Egamma_t40MC_Truth = (TH2F*)filetslope40->Get("Xi_t_Truth");
	TH1F * t40MC_Truth = (TH1F *)XiMassKinFit_Egamma_t40MC_Truth->ProjectionY("t40MC_Truth",XiMassKinFit_Egamma_t40MC_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_t40MC_Truth->GetXaxis()->FindBin(1.34));

//legends
	auto legend_datasets = new TLegend(0.70,0.8,0.98,0.93);
	legend_datasets->AddEntry(t171,"2017-01_ANAver20 data","lep");
	legend_datasets->AddEntry(t181,"2018-01_ANAver03 data","lep");
	legend_datasets->AddEntry(t188,"2018-08_ANAver02 data","lep");
	auto legend_MCtests = new TLegend(0.50,0.8,0.98,0.98);
	legend_MCtests->AddEntry(t188,"2018-08_ANAver02 data","lep");
	legend_MCtests->AddEntry(t14MC,"MC tslope = 1.4","lep");
	legend_MCtests->AddEntry(t15MC,"MC tslope = 1.5","lep");
	legend_MCtests->AddEntry(t16MC,"MC tslope = 1.6","lep");
	legend_MCtests->AddEntry(t17MC,"MC tslope = 1.7","lep");
	legend_MCtests->AddEntry(t18MC,"MC tslope = 1.8","lep");
	legend_MCtests->AddEntry(t19MC,"MC tslope = 1.9","lep");
	legend_MCtests->AddEntry(t20MC,"MC tslope = 2.0","lep");
	legend_MCtests->AddEntry(t25MC,"MC tslope = 2.5","lep");
	legend_MCtests->AddEntry(t30MC,"MC tslope = 3.0","lep");
	legend_MCtests->AddEntry(t35MC,"MC tslope = 3.5","lep");
	legend_MCtests->AddEntry(t40MC,"MC tslope = 4.0","lep");

//No statistics box on histogram 
	gStyle->SetOptStat(0000);

//Data t distributions
	TCanvas *cctdistdata = new TCanvas("cctdistdata", "cctdistdata", 800, 600);	
	t171->SetLineColor(kGreen);
	t181->SetLineColor(kRed);
	t188->SetLineColor(kBlue);
	t171->SetMarkerColor(kGreen);
	t181->SetMarkerColor(kRed);
	t188->SetMarkerColor(kBlue);
	t171->SetMarkerStyle(21);
	t181->SetMarkerStyle(21);
	t188->SetMarkerStyle(21);
	t171->SetTitle("");
	t171->GetYaxis()->SetTitle("Combos");
	t171->GetYaxis()->SetRangeUser(0,t181->GetMaximum()+100);
	t171->Draw("pe1");
	t181->Draw("pe1 same");
	t188->Draw("pe1 same");
	legend_datasets->Draw();
	cctdistdata->Print("tdist_datasets.png");

	TCanvas *cctdistMC = new TCanvas("cctdistMC", "cctdistMC", 800, 600);
	t188->SetLineColor(kBlue);
	t188->SetMarkerColor(kBlue);
	t188->SetMarkerStyle(20);
	t188->RebinX(6);
	double norm188 = t188->GetMaximum();
	t188->SetTitle("");
	t188->GetYaxis()->SetTitle("Combos");
	t188->GetYaxis()->SetRangeUser(0,t188->GetMaximum()+100);
	t188->Draw("p");

	t14MC->SetLineColor(kWhite);
	t14MC->SetMarkerColor(kRed);
	t14MC->SetMarkerStyle(21);
	t14MC->RebinX(6);
	double norm14 = t14MC->GetMaximum();
	t14MC->Scale(norm188/norm14);
	t14MC->Draw("p same");
/*
	t14MC_Truth->SetLineColor(kRed);
	t14MC_Truth->SetMarkerColor(kRed);
	t14MC_Truth->SetMarkerStyle(24);
	t14MC_Truth->RebinX(6);
	t14MC_Truth->Scale(norm188/norm14);
	t14MC_Truth->Draw("pe1 same");
*/	
	t15MC->SetLineColor(kWhite);
	t15MC->SetMarkerColor(kRed+2);
	t15MC->SetMarkerStyle(21);
	t15MC->RebinX(6);
	double norm15 = t15MC->GetMaximum();
	t15MC->Scale(norm188/norm15);
	t15MC->Draw("p same");
/*	t15MC_Truth->SetLineColor(kRed+2);
	t15MC_Truth->SetMarkerColor(kRed+2);
	t15MC_Truth->SetMarkerStyle(24);
	t15MC_Truth->RebinX(6);
	t15MC_Truth->Scale(norm188/norm15);
	//t15MC_Truth->Draw("pe1 same");
*/
	t16MC->SetLineColor(kWhite);
	t16MC->SetMarkerColor(kPink);
	t16MC->SetMarkerStyle(21);
	t16MC->RebinX(6);
	double norm16 = t16MC->GetMaximum();
	t16MC->Scale(norm188/norm16);
	t16MC->Draw("p same");
/*	t16MC_Truth->SetLineColor(kPink);
	t16MC_Truth->SetMarkerColor(kPink);
	t16MC_Truth->SetMarkerStyle(24);
	t16MC_Truth->RebinX(6);
	t16MC_Truth->Scale(norm188/norm16);
	t16MC_Truth->Draw("p same");
*/
	t17MC->SetLineColor(kWhite);
	t17MC->SetMarkerColor(kPink+2);
	t17MC->SetMarkerStyle(21);
	t17MC->RebinX(6);
	double norm17 = t17MC->GetMaximum();
	t17MC->Scale(norm188/norm17);
	t17MC->Draw("p same");

	t18MC->SetLineColor(kWhite);
	t18MC->SetMarkerColor(kMagenta);
	t18MC->SetMarkerStyle(21);
	t18MC->RebinX(6);
	double norm18 = t18MC->GetMaximum();
	t18MC->Scale(norm188/norm18);
	t18MC->Draw("p same");

	t19MC->SetLineColor(kWhite);
	t19MC->SetMarkerColor(kMagenta+2);
	t19MC->SetMarkerStyle(21);
	t19MC->RebinX(6);
	double norm19 = t19MC->GetMaximum();
	t19MC->Scale(norm188/norm19);
	t19MC->Draw("p same");

	t20MC->SetLineColor(kWhite);
	t20MC->SetMarkerColor(kViolet);
	t20MC->SetMarkerStyle(21);
	t20MC->RebinX(6);
	double norm20 = t20MC->GetMaximum();
	t20MC->Scale(norm188/norm20);
	t20MC->Draw("p same");

	t25MC->SetLineColor(kWhite);
	t25MC->SetMarkerColor(kViolet+2);
	t25MC->SetMarkerStyle(21);
	t25MC->RebinX(6);
	double norm25 = t25MC->GetMaximum();
	t25MC->Scale(norm188/norm25);
	t25MC->Draw("p same");

	t30MC->SetLineColor(kWhite);
	t30MC->SetMarkerColor(kBlue+2);
	t30MC->SetMarkerStyle(21);
	t30MC->RebinX(6);
	double norm30 = t30MC->GetMaximum();
	t30MC->Scale(norm188/norm30);
	t30MC->Draw("p same");

	t35MC->SetLineColor(kWhite);
	t35MC->SetMarkerColor(kCyan);
	t35MC->SetMarkerStyle(21);
	t35MC->RebinX(6);
	double norm35 = t35MC->GetMaximum();
	t35MC->Scale(norm188/norm35);
	t35MC->Draw("p same");

	t40MC->SetLineColor(kWhite);
	t40MC->SetMarkerColor(kCyan+2);
	t40MC->SetMarkerStyle(21);
	t40MC->RebinX(6);
	double norm40 = t40MC->GetMaximum();
	t40MC->Scale(norm188/norm40);
	t40MC->Draw("p same");

	legend_MCtests->Draw();
	cctdistMC->Print("tdist_MCtlopestests.png");


}
