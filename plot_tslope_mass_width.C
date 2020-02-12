#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

char filename[500];
char thrownfilename[500];
char MClegendentry[100];
char tMC[100];

void plot_tslope_mass_width(){
int trials[][3] = {{0,18,6}, {0,18,8}, {0,18,10}, {0,20,2}, {0,20,4}, {0,20,6}, {0,20,8}, {0,20,10}, {0,22,2}, {0,22,4}, {0,22,6}, {0,22,8}, {0,22,10}, {0,24,2}, {0,24,4}, {0,24,6}, {0,24,8}, {0,24,10}, {0,26,2}, {0,26,4}, {0,26,6}, {0,26,8}, {0,26,10}, {0,28,2}, {0,28,4}, {0,28,6}, {0,28,8}, {0,28,10}, {7,18,2}, {7,18,4}, {7,18,6}, {7,18,8}, {7,18,10}, {7,20,2}, {7,20,4}, {7,20,6}, {7,20,8}, {7,20,10}, {7,22,2}, {7,22,4}, {7,22,6}, {7,22,8}, {7,22,10}, {7,24,2}, {7,24,4}, {7,24,6}, {7,24,8}, {7,24,10}, {7,26,2}, {7,26,4}, {7,26,6}, {7,26,8}, {7,26,10}, {7,28,2}, {7,28,4}, {7,28,6}, {7,28,8}, {7,28,10}, {14,18,2}, {14,18,4}, {14,18,6}, {14,18,8}, {14,18,10}, {14,20,2}, {14,20,4}, {14,20,6}, {14,20,8}, {14,20,10}, {14,22,2}, {14,22,4}, {14,22,6}, {14,22,8}, {14,22,10}, {14,24,2}, {14,24,4}, {14,24,6}, {14,24,8}, {14,24,10}, {14,26,2}, {14,26,4}, {14,26,6}, {14,26,8}, {14,26,10}, {14,28,2}, {14,28,4}, {14,28,6}, {21,18,2}, {35,28,8}, {35,28,10}};
int colors[] =  {kRed-10, kRed-9, kRed-8, kRed-7, kRed-6, kRed-5,  kRed-4, kRed-3, kRed-2, kRed-1, kRed, kRed+1, kRed+2, kRed+3, kRed+4, kPink-9, kPink-8, kPink-7, kPink-6, kPink-5, kPink-4, kPink-3, kPink-2, kPink-1, kPink, kPink+1, kPink+2, kPink+3,kAzure-9, kAzure-8, kAzure-7, kAzure-6, kAzure-5, kAzure-4, kAzure-3, kAzure-2, kAzure-1, kAzure, kAzure+1, kAzure+2, kAzure+3, kAzure+4, kAzure+5, kAzure+6, kAzure+7, kAzure+8, kAzure+9, kAzure+10, kCyan+4, kCyan+3, kCyan+2, kCyan+1, kCyan, kCyan-1, kCyan-2, kCyan-3, kCyan-4, kCyan-5, kGreen+4, kGreen+3, kGreen+2, kGreen+1, kGreen,  kGreen-1, kGreen-2, kGreen-3, kGreen-4, kGreen-5, kGreen-6, kGreen-7, kGreen-8, kGreen-9, kGreen-10, kSpring-9, kSpring-8, kSpring-7, kSpring-6, kSpring-5, kSpring-4, kSpring-3, kSpring-2, kSpring-1, kSpring, kSpring+1, kSpring+2, kSpring+3, kSpring+4, kSpring+5, kBlue+2, kGray, kGray+2};

TFile * data201701 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2017-01_ANAver20_347runs_jan02.root");
TFile * data201801 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-01_ANAver03_543runs_jan02.root");
TFile * data201808 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-08_ANAver02_449runs_jan02.root");


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
//legends
	auto legend_datasets = new TLegend(0.70,0.8,0.98,0.93);
	legend_datasets->AddEntry(t171,"2017-01_ANAver20 data","lep");
	legend_datasets->AddEntry(t181,"2018-01_ANAver03 data","lep");
	legend_datasets->AddEntry(t188,"2018-08_ANAver02 data","lep");

	auto legend_MCtests = new TLegend(0.50,0.6,0.98,0.98);
	legend_MCtests->SetNColumns(2);
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
//Reconstructed MC distributions
	TCanvas *cctdistMC = new TCanvas("cctdistMC", "cctdistMC", 800, 600);
	t188->Draw("p hist");

for( int i=0; i< sizeof(trials)/sizeof(trials[0]);i++){
	//Opening MC files
	sprintf(filename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	sprintf(thrownfilename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/thrown_kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	cout << "tslope: " << trials[i][0] << " Y: " << trials[i][1] << " +/- " << trials[i][2] << endl;
	TFile * MCfile = TFile::Open(filename);
	TFile * Thrownfile = TFile::Open(thrownfilename);
	//reconstructed MC tests for 2018-08
	sprintf(tMC,"tdist_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);
	TH2F * XiMassKinFit_Egamma = (TH2F*)MCfile->Get("Xi_t");
	TH1F * tMC = (TH1F *)XiMassKinFit_Egamma->ProjectionY("tMC",XiMassKinFit_Egamma->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma->GetXaxis()->FindBin(1.34));
	//MC Truth tslope tests for 2018-08
 	TH2F * XiMassKinFit_Egamma_Truth = (TH2F*)MCfile->Get("Xi_t_Truth");
	TH1F * tMC_Truth = (TH1F *)XiMassKinFit_Egamma_Truth->ProjectionY("tMC_Truth",XiMassKinFit_Egamma_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_Truth->GetXaxis()->FindBin(1.34));
	//MC Thrown tslope tests for 2018-08
 	TH2F * Egamma_tMC_Thrown = (TH2F*)Thrownfile->Get("Egamma_t");
	TH1F * tMC_Thrown = (TH1F *)Egamma_tMC_Thrown->ProjectionY("tMC_Thrown",Egamma_tMC_Thrown->GetXaxis()->FindBin(6.3),Egamma_tMC_Thrown->GetXaxis()->FindBin(11.9));
 	//Add legend entry
	cctdistMC->cd();
	tMC->SetLineColor(colors[i]);
	tMC->SetMarkerColor(colors[i]);
	tMC->SetMarkerStyle(21);
	tMC->RebinX(5);
	tMC->Draw("p hist same");
	double tslope = trials[i][0]/10.;
	double Ymass = trials[i][1]/10.; 
	double Ywidth = trials[i][2]/10.;
	sprintf(MClegendentry,"MC t=%0.1f, Y=%0.1f+/-%0.1f",tslope,Ymass,Ywidth);
	legend_MCtests->AddEntry(tMC,MClegendentry,"p");
	}
legend_MCtests->Draw();
cctdistMC->Print("tdist_MCtlopestests_varyingtandY.png");
}
