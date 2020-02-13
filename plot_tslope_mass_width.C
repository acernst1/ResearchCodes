#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

char filename[500];
char thrownfilename[500];
char MClegendentry[100];
char tMCname[100];
char Trial_Title[100];
double normMC;
int color_mass;
int color_tslope;
int color_width;
double canvas_margins = 1e-50;

void plot_tslope_mass_width(){
TH1F * tMC[200];
int trials[][3] = {{0,18,4}, {0,18,6}, {0,18,8}, {0,18,10}, {0,20,2}, {0,20,4}, {0,20,6}, {0,20,8}, {0,20,10}, {0,22,2}, {0,22,4}, {0,22,6}, {0,22,8}, {0,22,10}, {0,24,2}, {0,24,4}, {0,24,6}, {0,24,8}, {0,24,10}, {0,26,2}, {0,26,4}, {0,26,6}, {0,26,8}, {0,26,10}, {0,28,2}, {0,28,4}, {0,28,6}, {0,28,8}, {0,28,10}, {7,18,2}, {7,18,4}, {7,18,6}, {7,18,8}, {7,18,10}, {7,20,2}, {7,20,4}, {7,20,6}, {7,20,8}, {7,20,10}, {7,22,2}, {7,22,4}, {7,22,6}, {7,22,8}, {7,22,10}, {7,24,2}, {7,24,4}, {7,24,6}, {7,24,8}, {7,24,10}, {7,26,2}, {7,26,4}, {7,26,6}, {7,26,8}, {7,26,10}, {7,28,2}, {7,28,4}, {7,28,6}, {7,28,8}, {7,28,10}, {14,18,2}, {14,18,4}, {14,18,6}, {14,18,8}, {14,18,10}, {14,20,2}, {14,20,4}, {14,20,6}, {14,20,8}, {14,20,10}, {14,22,2}, {14,22,4}, {14,22,6}, {14,22,8}, {14,22,10}, {14,24,2}, {14,24,4}, {14,24,6}, {14,24,8}, {14,24,10}, {14,26,2}, {14,26,4}, {14,26,6}, {14,26,8}, {14,26,10}, {14,28,2}, {14,28,4}, {14,28,6}, {14,28,8}, {14,28,10}, {21,18,2}, {21,18,4}, {21,18,6}, {21,18,8}, {21,18,10}, {21,20,2}, {21,20,4}, {21,20,6}, {21,20,8}, {21,20,10}, {21,22,2}, {21,22,4}, {21,22,6}, {21,22,8}, {21,22,10}, {21,24,2}, {21,24,4}, {21,24,6}, {21,24,8}, {21,24,10}, {21,26,2}, {21,26,4}, {21,26,6}, {21,26,8}, {21,26,10}, {21,28,2}, {21,28,4}, {21,28,6}, {21,28,8}, {21,28,10}, {28,18,2}, {28,18,4}, {28,18,6}, {28,18,8}, {28,18,10}, {28,20,2}, {28,20,4}, {28,20,6}, {28,20,8}, {28,20,10}, {28,22,2}, {28,22,4}, {28,22,6}, {28,22,8}, {28,22,10}, {28,24,2}, {28,24,4}, {28,24,6}, {28,24,8}, {28,24,10}, {28,26,2}, {28,26,4}, {28,26,6}, {28,26,8}, {28,26,10}, {28,28,2}, {28,28,4}, {28,28,6}, {28,28,8}, {28,28,10}, {35,18,2}, {35,18,4}, {35,18,6}, {35,18,8}, {35,18,10}, {35,20,2}, {35,20,4}, {35,20,6}, {35,20,8}, {35,20,10}, {35,22,2}, {35,22,4}, {35,22,6}, {35,22,8}, {35,22,10}, {35,24,2}, {35,24,4}, {35,24,6}, {35,24,8}, {35,24,10}, {35,26,2}, {35,26,4}, {35,26,6}, {35,26,8}, {35,26,10}, {35,28,2}, {35,28,4}, {35,28,6}, {35,28,8}, {35,28,10}};
int colors[] =  { kRed, kViolet, kCyan, kGreen,  kSpring, kGray};
 
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

	auto legend_MCtests_tslope = new TLegend(0.50,0.6,0.98,0.98);
	legend_MCtests_tslope->SetNColumns(2);
	auto legend_MCtests_mass = new TLegend(0.50,0.6,0.98,0.98);
	legend_MCtests_mass->SetNColumns(2);
	auto legend_MCtests_width = new TLegend(0.50,0.6,0.98,0.98);
	legend_MCtests_width->SetNColumns(2);

//No statistics box on histogram 
	gStyle->SetOptStat(0);
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
	TCanvas *cctdistMC = new TCanvas("cctdistMC", "cctdistMC", 1200, 900);
	cctdistMC->Divide(4,3,canvas_margins,canvas_margins);
	double norm201808= t188->GetMaximum();
	norm201808 = norm201808;
	t188->GetYaxis()->SetRangeUser(0,300);
	for(int ploti188 = 0; ploti188 < 12; ploti188++){
		cctdistMC->cd(ploti188+1);
		t188->SetMarkerStyle(8);
		t188->SetMarkerSize(0.75);
		t188->Draw("p hist");
	}


for( int i=0; i< sizeof(trials)/sizeof(trials[0]);i++){
	//Opening MC files
	sprintf(filename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	sprintf(thrownfilename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/thrown_kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	cout << "tslope: " << trials[i][0] << " Y: " << trials[i][1] << " +/- " << trials[i][2] << endl;
	TFile * MCfile = TFile::Open(filename);
	TFile * Thrownfile = TFile::Open(thrownfilename);
	//reconstructed MC tests for 2018-08
	sprintf(tMCname,"tdist_tslope%02d_mass%02d_width%02d",trials[i][0],trials[i][1],trials[i][2]);
	TH2F * XiMassKinFit_Egamma = (TH2F*)MCfile->Get("Xi_t");
	tMC[i] = (TH1F *)XiMassKinFit_Egamma->ProjectionY(tMCname,XiMassKinFit_Egamma->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma->GetXaxis()->FindBin(1.34));
	//MC Truth tslope tests for 2018-08
 	TH2F * XiMassKinFit_Egamma_Truth = (TH2F*)MCfile->Get("Xi_t_Truth");
	TH1F * tMC_Truth = (TH1F *)XiMassKinFit_Egamma_Truth->ProjectionY("tMC_Truth",XiMassKinFit_Egamma_Truth->GetXaxis()->FindBin(1.31),XiMassKinFit_Egamma_Truth->GetXaxis()->FindBin(1.34));
	//MC Thrown tslope tests for 2018-08
 	TH2F * Egamma_tMC_Thrown = (TH2F*)Thrownfile->Get("Egamma_t");
	TH1F * tMC_Thrown = (TH1F *)Egamma_tMC_Thrown->ProjectionY("tMC_Thrown",Egamma_tMC_Thrown->GetXaxis()->FindBin(6.3),Egamma_tMC_Thrown->GetXaxis()->FindBin(11.9));
 	//Add legend entry
	cctdistMC->cd();
	tMC[i]->SetMarkerStyle(8);
	tMC[i]->SetMarkerSize(0.75);
	tMC[i]->RebinX(5);
	normMC = tMC[i]->GetMaximum();
	tMC[i]->Scale(norm201808/normMC);
	double tslope = trials[i][0]/10.;
	double Ymass = trials[i][1]/10.; 
	double Ywidth = trials[i][2]/10.;
	//tMC[i]->Draw("p hist same");
//loop to color based on Y* mass
	if(trials[i][1] == 18){color_mass = 0;}
	if(trials[i][1] == 20){color_mass = 1;}
	if(trials[i][1] == 22){color_mass = 2;}
	if(trials[i][1] == 24){color_mass = 3;}
	if(trials[i][1] == 26){color_mass = 4;}
	if(trials[i][1] == 28){color_mass = 5;}

	if(trials[i][0] == 0){color_tslope = 0;}
	if(trials[i][0] == 7){color_tslope = 1;}
	if(trials[i][0] == 14){color_tslope = 2;}
	if(trials[i][0] == 21){color_tslope = 3;}
	if(trials[i][0] == 28){color_tslope = 4;}
	if(trials[i][0] == 35){color_tslope = 5;}
	
	sprintf(Trial_Title, "M_{Y} = %0.1f, #Gamma_{Y} = %0.1f", Ymass, Ywidth);	

	for(int ploti = 0; ploti < 12; ploti++){
		if(ploti == 0 & trials[i][1] == 20 & trials[i][2] == 4){
			cctdistMC->cd(ploti+1);
			tMC[i]->SetMarkerColor(colors[color_tslope]);
			tMC[i]->SetTitle(Trial_Title);
			tMC[i]->Draw("p hist same");
			sprintf(MClegendentry,"MC t=%0.1f",tslope);
			legend_MCtests_tslope->AddEntry(tMC[i],MClegendentry,"p");
			legend_MCtests_tslope->Draw();
			}
		if(ploti == 1 & trials[i][1] == 20 & trials[i][2] == 6){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");	}
		if(ploti == 2 & trials[i][1] == 20 & trials[i][2] == 8){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 3 & trials[i][1] == 20 & trials[i][2] == 10){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]);tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 4 & trials[i][1] == 24 & trials[i][2] == 4){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 5 & trials[i][1] == 24 & trials[i][2] == 6){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");	}
		if(ploti == 6 & trials[i][1] == 24 & trials[i][2] == 8){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 7 & trials[i][1] == 24 & trials[i][2] == 10){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}	
		if(ploti == 8 & trials[i][1] == 28 & trials[i][2] == 4){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 9 & trials[i][1] == 28 & trials[i][2] == 6){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 10 & trials[i][1] == 28 & trials[i][2] == 8){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}
		if(ploti == 11 & trials[i][1] == 28 & trials[i][2] == 10){
			cctdistMC->cd(ploti+1); tMC[i]->SetMarkerColor(colors[color_tslope]); tMC[i]->SetTitle(Trial_Title); tMC[i]->Draw("p hist same");}				
		} // end ploti for loop
	} //end i for loop
cctdistMC->Print("tdist_MCtslopestests_varyingt.png");
} // end main fuction











