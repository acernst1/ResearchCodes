#include "RooPlot.h"
#include "RooGenericPdf.h"
Color_t color171 = kGreen;
Color_t color181 = kRed;
Color_t color188 = kBlue;
int data = 0;
int mc = 1;

void setformatTH1F(TH1F * hist, Color_t color, int type) {  
	if(type == 0 )	{ hist->SetMarkerStyle(20); }
	if(type == 1 ) 	{ hist->SetMarkerStyle(25); }
	hist->GetYaxis()->SetTitleOffset(1.3);
	hist->SetMarkerSize(0.8);
	hist->SetMarkerColor(color);
	hist->SetLineColor(color);	
}

void setformatTH1I(TH1I * hist, Color_t color, int type) {  
	if(type == 0 )	{ hist->SetMarkerStyle(20); } //data format
	if(type == 1 ) 	{ hist->SetMarkerStyle(25); } //mc format
	hist->GetYaxis()->SetTitleOffset(1.3);
	hist->SetMarkerSize(0.8);
	hist->SetMarkerColor(color);
	hist->SetLineColor(color);	
}

void plot_kpkpkmlamb() {
	TFile * file1701 = TFile::Open("kpkpkmlamb_2017_01_ver30_june4.root");
	TFile * file1801 = TFile::Open("kpkpkmlamb__B4_2018_01_ver03_june4.root");
	TFile * file1808 = TFile::Open("kpkpkmlamb_2018_08_ver06_june30.root");

	gStyle->SetOptStat(0000);
	//gStyle->SetTitleSize(0.04);

	TCanvas * KKcanvas = new TCanvas("KKcanvas", "KKcanvas",800,600);
	TH1F * KK_Measured = (TH1F*)file1808->Get("KKMass_KinFit");
	TH1F * KK_Measured_wacc = (TH1F*)file1808->Get("KKMass_KinFit_wacc");
	TH1F * KK_Measured_accsub = (TH1F *) KK_Measured->Clone("KK_Measured_accsub");
	KK_Measured_accsub->Add(KK_Measured_wacc,-0.5);
	KK_Measured_accsub->SetTitle(" ");
	KK_Measured_accsub->GetXaxis()->SetTitle("K^{+}K^{-} Invariant Mass (GeV)");
	KK_Measured_accsub->GetYaxis()->SetTitle("Combos");
	setformatTH1F(KK_Measured_accsub, color188, data);
	KK_Measured_accsub->Draw("pe");
	KKcanvas->Print("tempjuly/XiStar_KK_201808_june2020.png");

	TCanvas * PhiLambda_canvas = new TCanvas("PhiLambda_canvas", "PhiLambda_canvas",800,600);
	TH2I * KKLambda_Measured = (TH2I*)file1808->Get("KKLambdaMass_Measured");
	TH2I * KKLambda_Measured_wacc = (TH2I*)file1808->Get("KKLambdaMass_Measured_wacc");
	TH2I * KKLambda_Measured_accsub = (TH2I *) KKLambda_Measured->Clone("KKLambda_Measured_accsub");
	//KKLambda_Measured_accsub->Add(KKLambda_Measured_wacc,-0.5);
	KKLambda_Measured_accsub->SetTitle(" ");
	KKLambda_Measured_accsub->GetXaxis()->SetTitle("K^{+}K^{-} Invariant Mass (GeV)");
	KKLambda_Measured_accsub->GetYaxis()->SetTitle("p#pi^{-} Invariant Mass (GeV)");
	KKLambda_Measured_accsub->Draw("COLZ");
	PhiLambda_canvas->Print("tempjuly/XiStar_PhiLambda_201808_june2020.png");

	TCanvas * K_canvas = new TCanvas("K_canvas", "K_canvas",800,600);
	TH2I * K_pTheta_Measured = (TH2I*)file1808->Get("K_pTheta_Measured");
	TH2I * K_pTheta_Measured_wacc = (TH2I*)file1808->Get("K_pTheta_Measured_acc");
	TH2I * K_pTheta_Measured_accsub = (TH2I *) K_pTheta_Measured->Clone("K_pTheta_Measured_accsub");
	K_pTheta_Measured_accsub->Add(K_pTheta_Measured_wacc,-0.5);
	K_pTheta_Measured_accsub->SetTitle("K^{+} ");
	K_pTheta_Measured_accsub->GetXaxis()->SetTitle("#theta (deg)");
	K_pTheta_Measured_accsub->GetYaxis()->SetTitle("p (GeV)");
	K_pTheta_Measured_accsub->Draw("COLZ");
	K_canvas->Print("XiStar_KPlus_pTheta_201808_june2020.png");

	TH3F * XiMass_ChiSq_LambdaSigma1701 = (TH3F*)file1701->Get("XiMass_ChiSq_LambdaSigma");
	TH3F * XiMass_ChiSq_LambdaSigma1701_wacc = (TH3F*)file1701->Get("XiMass_ChiSq_LambdaSigma_wacc");
	TH3F * XiMass_ChiSq_LambdaSigma1701_accsub = (TH3F *) XiMass_ChiSq_LambdaSigma1701->Clone("XiMass_ChiSq_LambdaSigma1701_accsub");
	XiMass_ChiSq_LambdaSigma1701_accsub->Add(XiMass_ChiSq_LambdaSigma1701_wacc,-0.5);
	TH3F * XiMass_ChiSq_LambdaSigma1801 = (TH3F*)file1801->Get("XiMass_ChiSq_LambdaSigma");
	TH3F * XiMass_ChiSq_LambdaSigma1801_wacc = (TH3F*)file1801->Get("XiMass_ChiSq_LambdaSigma_wacc");
	TH3F * XiMass_ChiSq_LambdaSigma1801_accsub = (TH3F *) XiMass_ChiSq_LambdaSigma1801->Clone("XiMass_ChiSq_LambdaSigma1801_accsub");
	XiMass_ChiSq_LambdaSigma1801_accsub->Add(XiMass_ChiSq_LambdaSigma1801_wacc,-0.5);
	TH3F * XiMass_ChiSq_LambdaSigma1808 = (TH3F*)file1808->Get("XiMass_ChiSq_LambdaSigma");
	TH3F * XiMass_ChiSq_LambdaSigma1808_wacc = (TH3F*)file1808->Get("XiMass_ChiSq_LambdaSigma_wacc");
	TH3F * XiMass_ChiSq_LambdaSigma1808_accsub = (TH3F *) XiMass_ChiSq_LambdaSigma1808->Clone("XiMass_ChiSq_LambdaSigma1808_accsub");
	XiMass_ChiSq_LambdaSigma1808_accsub->Add(XiMass_ChiSq_LambdaSigma1808_wacc,-0.5);

	TH2F * XiMass_ChiSq_1701 = (TH2F*)file1701->Get("ChiSqXi");
	TH2F * XiMass_ChiSq_1701_wacc = (TH2F*)file1701->Get("ChiSqXi_wacc");
	TH2F * XiMass_ChiSq_1701_accsub = (TH2F *) XiMass_ChiSq_1701->Clone("XiMass_ChiSq_1701_accsub");
	XiMass_ChiSq_1701_accsub->Add(XiMass_ChiSq_1701_wacc,-0.5);
	TH2F * XiMass_ChiSq_1801 = (TH2F*)file1801->Get("ChiSqXi");
	TH2F * XiMass_ChiSq_1801_wacc = (TH2F*)file1801->Get("ChiSqXi_wacc");
	TH2F * XiMass_ChiSq_1801_accsub = (TH2F *) XiMass_ChiSq_1801->Clone("XiMass_ChiSq_1801_accsub");
	XiMass_ChiSq_1801_accsub->Add(XiMass_ChiSq_1801_wacc,-0.5);
	TH2F * XiMass_ChiSq_1808 = (TH2F*)file1808->Get("ChiSqXi");
	TH2F * XiMass_ChiSq_1808_wacc = (TH2F*)file1808->Get("ChiSqXi_wacc");
	TH2F * XiMass_ChiSq_1808_accsub = (TH2F *) XiMass_ChiSq_1808->Clone("XiMass_ChiSq_1808_accsub");
	XiMass_ChiSq_1808_accsub->Add(XiMass_ChiSq_1808_wacc,-0.5);


	TCanvas * Lamb_canvas = new TCanvas("Lamb_canvas", "Lamb_canvas",800,600);
	TH1F * Lambsig1701 = (TH1F *) XiMass_ChiSq_LambdaSigma1701_accsub->Project3D("z");
	Lambsig1701->SetTitle("");
	Lambsig1701->GetXaxis()->SetTitle("#Lambda Flight Significance");
	Lambsig1701->GetYaxis()->SetTitle("Combos");
	setformatTH1F(Lambsig1701,color171,data);
	Lambsig1701->GetYaxis()->SetRangeUser(0,140e3);
	Lambsig1701->Draw("pe");
	TH1F * Lambsig1801 = (TH1F *) XiMass_ChiSq_LambdaSigma1801_accsub->Project3D("z");
	Lambsig1801->SetTitle("");
	Lambsig1801->GetXaxis()->SetTitle("#Lambda Flight Significance");
	Lambsig1801->GetYaxis()->SetTitle("Combos");
	setformatTH1F(Lambsig1801,color181,data);
	Lambsig1801->Draw("pe,same");
	TH1F * Lambsig1808 = (TH1F *) XiMass_ChiSq_LambdaSigma1808_accsub->Project3D("z");
	Lambsig1808->SetTitle("");
	Lambsig1808->GetXaxis()->SetTitle("#Lambda Flight Significance");
	Lambsig1808->GetYaxis()->SetTitle("Combos");
	setformatTH1F(Lambsig1808,color188,data);
	Lambsig1808->Draw("pe,same");
	Lamb_canvas->Print("Lambsig_allsets_june2020.png");



	double maxlambsig = 200.0;
	double maxChiSq = 3.5;
	TCanvas * LambXi_canvas = new TCanvas("LambXi_canvas", "LambXi_canvas",800,600);
	XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(maxChiSq)-1);
	TH2F * LambVsXi1808 = (TH2F *) XiMass_ChiSq_LambdaSigma1808_accsub->Project3D("xz");
	LambVsXi1808->SetTitle("");
	LambVsXi1808->RebinX(2);
	LambVsXi1808->RebinY(2);
	LambVsXi1808->GetXaxis()->SetTitle("#Lambda Flight Significance");
	LambVsXi1808->GetYaxis()->SetTitle("K^{-}#Lambda Mass (GeV)");
	TLine *linelambsig = new TLine(1.0,1.5,1.0,3.0);
	linelambsig->SetLineColor(kRed);
	TArrow *arrowlambsig = new TArrow(1.0,2.9,5.0,2.9,0.01,"|>");
	arrowlambsig->SetLineColor(kRed);
	arrowlambsig->SetFillColor(kRed);
	arrowlambsig->SetLineWidth(2);
	linelambsig->SetLineWidth(2);
	LambVsXi1808->Draw("colz");
	linelambsig->Draw("Same");
	arrowlambsig->DrawArrow(1.0,2.9,5.0,2.9,0.01,"|>");
	LambXi_canvas->Print("tempjuly/LambsigVsXi_201808_june2020.png");

	TCanvas * ChiXi_canvas = new TCanvas("ChiXi_canvas", "ChiXi_canvas",800,600);
	XiMass_ChiSq_1701_accsub->SetTitle("");
	XiMass_ChiSq_1701_accsub->GetXaxis()->SetTitle("X^{2}/NDF");
	XiMass_ChiSq_1701_accsub->GetYaxis()->SetTitle("K^{-}#Lambda Mass (GeV)");

	TLine *line1820 = new TLine(1.823,0,1.823,500);
	line1820->SetLineColor(kGray);
	double canvas_margins = 1e-50;
	int nummassBins = (2.6-1.5)/0.015;
	double LambCut;
	int columns = 4;
	int rows = 3;
	double DeltaLamb = 0.5;
	double MaxLambCut;
	TH1F * XiLamb1701[13];
	TH1F * XiLamb1801[13];
	TH1F * XiLamb1808[13];
	char XiLamb_histname[100];
	char LambBin_Title[100];
	TCanvas * XiLamb_canvas = new TCanvas("XiLamb_canvas", "XiLamb_canvas",1200,900);
	XiLamb_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	for(int iLambCut = 0; iLambCut<12; iLambCut++){
		LambCut = DeltaLamb*iLambCut;
		XiLamb_canvas->cd(iLambCut+1);
		if(iLambCut < 12){	MaxLambCut = DeltaLamb*(iLambCut+1); } else { MaxLambCut = 200;}
		XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->FindBin(LambCut),XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
		XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->FindBin(maxChiSq)-1);
		XiLamb1701[iLambCut+1] = (TH1F *) XiMass_ChiSq_LambdaSigma1701_accsub->Project3D("x");
	
		XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->FindBin(LambCut),XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
		XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->FindBin(maxChiSq)-1);
		XiLamb1801[iLambCut+1] = (TH1F *) XiMass_ChiSq_LambdaSigma1801_accsub->Project3D("x");
	 	
		XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->FindBin(LambCut),XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
		XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(maxChiSq)-1);
		XiLamb1808[iLambCut+1] = (TH1F *) XiMass_ChiSq_LambdaSigma1808_accsub->Project3D("x");

	 	XiLamb1701[iLambCut+1]->Rebin(4);
	 	XiLamb1801[iLambCut+1]->Rebin(4);
	 	XiLamb1808[iLambCut+1]->Rebin(4);
	 	sprintf(LambBin_Title,"%3.1f#sigma < #Lambda Flight Sig. < %3.1f#sigma",LambCut, MaxLambCut);
		XiLamb1701[iLambCut+1]->SetTitle(LambBin_Title);
		setformatTH1F(XiLamb1701[iLambCut+1],color171,data);
		setformatTH1F(XiLamb1801[iLambCut+1],color181,data);
		setformatTH1F(XiLamb1808[iLambCut+1],color188,data);
		XiLamb1701[iLambCut+1]->SetLabelSize(0.04,"xy");
		XiLamb1701[iLambCut+1]->SetLabelOffset(0.002,"xy");
		XiLamb1701[iLambCut+1]->GetYaxis()->SetTitleSize(0.05);
		XiLamb1701[iLambCut+1]->GetXaxis()->SetTitleSize(0.04);
		XiLamb1701[iLambCut+1]->SetTitleSize(0.05);
		if(iLambCut < 4 && iLambCut >= 0){
			XiLamb1701[iLambCut+1]->GetYaxis()->SetRangeUser(0,150);
		}
		if(iLambCut < 8 && iLambCut >= 4){
			XiLamb1701[iLambCut+1]->GetYaxis()->SetRangeUser(0,100);
		}
		if(iLambCut < 12 && iLambCut >= 8){
			XiLamb1701[iLambCut+1]->GetYaxis()->SetRangeUser(0,100);
		}
		XiLamb1701[iLambCut+1]->Draw("pe");
		line1820->Draw("p,same");
		XiLamb1801[iLambCut+1]->Draw("pe,same");
		XiLamb1808[iLambCut+1]->Draw("pe,same");
		XiLamb_canvas->Update();
		if(iLambCut == 11) {	XiLamb_canvas->Print("tempjuly/XiLamb_allsets_june2020.png");}
	}


	TH1F * XiChi1701[13];
	TH1F * XiChi1801[13];
	TH1F * XiChi1808[13];

	char XiChi_histname1701[100];
	char XiChi_histname1801[100];
	char XiChi_histname1808[100];
	char ChiBin_Title[100];
	double ChiCut;
	double DeltaChi = 0.5;
	double MaxChi = 6.0;
	TCanvas * XiChi_canvas = new TCanvas("XiChi_canvas", "XiChi_canvas",1200,900);
	XiChi_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	for(int iChiCut = 0; iChiCut<12; iChiCut++){
		ChiCut = -DeltaChi*iChiCut + MaxChi;
		XiChi_canvas->cd(iChiCut+1);
		
		sprintf(XiChi_histname1701,"XiChi1701_%03d",iChiCut);
		XiChi1701[iChiCut+1] = (TH1F *) XiMass_ChiSq_1701_accsub->ProjectionY(XiChi_histname1701,XiMass_ChiSq_1701_accsub->GetXaxis()->FindBin(ChiCut-DeltaChi),XiMass_ChiSq_1701_accsub->GetXaxis()->FindBin(ChiCut)-1);
	 	XiChi1701[iChiCut+1]->Rebin(4);
		sprintf(XiChi_histname1801,"XiChi1801_%03d",iChiCut);
		XiChi1801[iChiCut+1] = (TH1F *) XiMass_ChiSq_1801_accsub->ProjectionY(XiChi_histname1801,XiMass_ChiSq_1801_accsub->GetXaxis()->FindBin(ChiCut-DeltaChi),XiMass_ChiSq_1801_accsub->GetXaxis()->FindBin(ChiCut)-1);
	 	XiChi1801[iChiCut+1]->Rebin(4);
	 	sprintf(XiChi_histname1808,"XiChi1808_%03d",iChiCut);
		XiChi1808[iChiCut+1] = (TH1F *) XiMass_ChiSq_1808_accsub->ProjectionY(XiChi_histname1808,XiMass_ChiSq_1808_accsub->GetXaxis()->FindBin(ChiCut-DeltaChi),XiMass_ChiSq_1808_accsub->GetXaxis()->FindBin(ChiCut)-1);
	 	XiChi1808[iChiCut+1]->Rebin(4);
	 		 	

	 	sprintf(ChiBin_Title,"%3.1f <= X^{2}/NDF < %3.1f",ChiCut-DeltaChi,ChiCut);
		XiChi1701[iChiCut+1]->SetTitle(ChiBin_Title);
		setformatTH1F(XiChi1701[iChiCut+1],color171,data);
		setformatTH1F(XiChi1801[iChiCut+1],color181,data);
		setformatTH1F(XiChi1808[iChiCut+1],color188,data);
		XiChi1701[iChiCut+1]->SetLabelSize(0.04,"xy");
		XiChi1701[iChiCut+1]->SetLabelOffset(0.002,"xy");
		XiChi1701[iChiCut+1]->GetYaxis()->SetTitleSize(0.05);
		XiChi1701[iChiCut+1]->GetXaxis()->SetTitleSize(0.04);
		XiChi1701[iChiCut+1]->SetTitleSize(0.05);
		if(iChiCut < 4 && iChiCut >= 0){
			XiChi1701[iChiCut+1]->GetYaxis()->SetRangeUser(0,350);
		}
		if(iChiCut < 8 && iChiCut >= 4){
			XiChi1701[iChiCut+1]->GetYaxis()->SetRangeUser(0,350);
		}
		if(iChiCut < 12 && iChiCut >= 8){
			XiChi1701[iChiCut+1]->GetYaxis()->SetRangeUser(0,350);
		}
		XiChi1701[iChiCut+1]->Draw("pe");
		line1820->Draw("p,same");
		XiChi1801[iChiCut+1]->Draw("pe,same");
		XiChi1808[iChiCut+1]->Draw("pe,same");
		XiChi_canvas->Update();
		XiChi_canvas->Print("tempjuly/XiChi_allsets_june2020.png");
	}
	ChiXi_canvas->cd();
	XiMass_ChiSq_1808_accsub->RebinY(2);
	XiMass_ChiSq_1808_accsub->GetXaxis()->SetRangeUser(0,20);
	TLine *lineChi = new TLine(3.5,1.5,3.5,3.0);
	lineChi->SetLineColor(kRed);
	TArrow *arrowChi = new TArrow(3.5,2.9,2.5,2.9,0.01,"|>");
	arrowChi->SetLineColor(kRed);
	arrowChi->SetFillColor(kRed);
	arrowChi->SetLineWidth(2);
	lineChi->SetLineWidth(2);
	XiMass_ChiSq_1808_accsub->Draw("colz");
	lineChi->Draw("Same");
	arrowChi->DrawArrow(3.5,2.9,2.5,2.9,0.01,"|>");
	ChiXi_canvas->Print("tempjuly/ChiVsXi_201808_june2020.png");


	TH1F * XiMass1701;
	TH1F * XiMass1801;
	TH1F * XiMass1808;
	double MinLambCut = 1.0;
	MaxLambCut = 200;
	maxChiSq = 3.5;
	TCanvas * XiMass_canvas = new TCanvas("XiMass_canvas", "XiMass_canvas",800,600);
	XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->FindBin(MinLambCut),XiMass_ChiSq_LambdaSigma1701_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
	XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1701_accsub->GetYaxis()->FindBin(maxChiSq)-1);
	XiMass1701 = (TH1F *) XiMass_ChiSq_LambdaSigma1701_accsub->Project3D("x");
	XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->FindBin(MinLambCut),XiMass_ChiSq_LambdaSigma1801_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
	XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1801_accsub->GetYaxis()->FindBin(maxChiSq)-1);
	XiMass1801 = (TH1F *) XiMass_ChiSq_LambdaSigma1801_accsub->Project3D("x");
	XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->SetRange(XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->FindBin(MinLambCut),XiMass_ChiSq_LambdaSigma1808_accsub->GetZaxis()->FindBin(MaxLambCut)-1);	
	XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->SetRange(XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(0.0),XiMass_ChiSq_LambdaSigma1808_accsub->GetYaxis()->FindBin(maxChiSq)-1);
	XiMass1808 = (TH1F *) XiMass_ChiSq_LambdaSigma1808_accsub->Project3D("x");
	setformatTH1F(XiMass1701,color171,data);
	setformatTH1F(XiMass1801,color181,data);
	setformatTH1F(XiMass1808,color188,data);
	XiMass1701->Rebin(2);
	XiMass1801->Rebin(2);
	XiMass1808->Rebin(2);
	XiMass1808->SetTitle("");
	XiMass1808->GetYaxis()->SetTitle("Combos");
	XiMass1808->Draw("pe");
	XiMass1801->Draw("pe,same");
	XiMass1701->Draw("pe,same");
	auto legend_sets = new TLegend(0.70,0.8,0.98,0.93);
	legend_sets->AddEntry(XiMass1701,"Spring 2017","lep");
	legend_sets->AddEntry(XiMass1801,"Spring 2018","lep");
	legend_sets->AddEntry(XiMass1808,"Fall 2018","lep");
	legend_sets->Draw();
	XiMass_canvas->Print("tempjuly/XiMass_allsets_june2020.png");

	cout << "===All the bins===" << endl;
	cout << "XiMass1701: " << XiMass1701->GetBinWidth(1)*1000 << endl;
	cout << "XiLamb1701[iLambCut+1] " << XiLamb1701[1]->GetBinWidth(1)*1000 << endl;
	cout << "XiChi1701[iChiCut+1] " << XiChi1701[1]->GetBinWidth(1)*1000 << endl;
	cout << "LambVsXi1808 " << LambVsXi1808->GetYaxis()->GetBinWidth(1)*1000 << endl;
	cout << "XiMass_ChiSq_1808_accsub " << XiMass_ChiSq_1808_accsub->GetYaxis()->GetBinWidth(1)*1000 << endl;



/*
  //using namespace RooFit;
char version[100]="combined_1820";
char plotversion[100]="";
char outputname[100];
char preoutputname[100];
sprintf(outputname,"datafit_kpkpkmlamb_XiStarMass_KinFit_new_%s.png",version);
sprintf(preoutputname,"prefit_kpkpkmlamb_XiStarMass_KinFit_new_%s.png",version);

gROOT->SetStyle("Plain");
gStyle->SetOptStat(1111);
gStyle->SetOptTitle(0);
//gStyle->SetOptStat(0);

// initialization
RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");

RooWorkspace* w = new RooWorkspace("w");
TCanvas * Xi_canvas1 = new TCanvas("Xi_canvas1", "Xi_canvas1",800,600);
TH1F *h_mass = (TH1F *) XiMass1701->Clone("kLamb");
h_mass->Add(XiMass1801);
h_mass->Add(XiMass1808);
h_mass->GetXaxis()->SetTitle("K^{-}#Lambda Invariant Mass");
h_mass->Draw("e0");
Xi_canvas1->Print(preoutputname);

  // observable(s)
RooRealVar mass("mass", "mass", 1.55, 2.6);
mass.setBins(70);

  // import data (histograms)
RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, h_mass);
w->import(RooArgSet(mass));

// background and signals
//w->factory("Chebychev::bkgd(mass,{c1[0.055,-1.e4,1.e4],c2[-0.9978,-1.e4,1.e4],c3[0.520,-1.e4,1.e4]})");
  
//w->factory("EXPR::bkgd('(mass+m)*sqrt(((mass+m)/m0)**2-1.0)*exp(c*(((mass+m)/m0)**2-1.0))',mass, m[0.,-1.e2,1.e2],m0[0.,-1.e2,1.e2],c[0.,-1.e2,1.e2])");
w->factory("EXPR::bkgd('(mass)*sqrt(((mass)/m0)**2-1.0)*exp(b*(((mass)/m0)**2-1.0))',mass, m0[1.61,1.60,1.65],b[-2,-25.,0.])");

w->factory("Voigtian::v1820(mass,mean1820[1.823,1.818,1.828],gamma1820[0.024,0.015,0.1],sigma[0.004295])");
//w->factory("Voigtian::v(mass,mean[1.818],gamma[0.05],sigma[0.004295])");
//w->factory("Voigtian::v2(mass,mean2[1.690,1.680,1.700],gamma2[0.02,0.005,0.060],sigma[0.004295])");
//w->factory("Voigtian::v3(mass,mean3[1.950,1.935,1.965],gamma3[0.06,0.040,0.080],sigma[0.004295])");  
//w->factory("Voigtian::v4(mass,mean4[2.025,2.020,2.030],gamma4[0.02,0.015,0.030],sigma[0.004295])");
//w->factory("Voigtian::v2120(mass,mean2120[2.120,2.116,2.141],gamma2120[0.02,0.013,0.037],sigma[0.004295])");
//w->factory("Voigtian::v6(mass,mean6[2.500,2.400,2.600],gamma6[0.1,0.02,0.2],sigma[0.004295])");

// build model for data:  accidental shape + background + signals
//w->factory("SUM::model(nbkgd[8200,0,1e5]*bkgd)");
w->factory("SUM::model(nbkgd[32000,0.,1.5e5]*bkgd, nsig1820[3000,0,1.5e4]*v1820)");
//w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[100,0,1e5]*v,nsig2[50,0,1e3]*v2,nsig3[0,0,1e3]*v3,nsig4[50,0,1e3]*v4,nsig5[50,0,1e3]*v5)");
//w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[168,0,1e5]*v, nsig4[20,0,1e5]*v4, nsig5[20,0,1e5]*v5)");
//w->factory("SUM::model(nbkgd[8200,0,1e5]*bkgd, nsig1820[650,0,1.5e3]*v1820, nsig2120[100,0,2e2]*v2120)");
 

  // do the fit
  w->pdf("model")->fitTo(*data,RooFit::Range(1.6,2.6),RooFit::Minos(1));

  // make some plots
  RooPlot* massframe = mass.frame(RooFit::Title("#Lambda K^{-} Invariant Mass"));
  massframe->SetMaximum(75);
  massframe->SetXTitle("#Lambda K^{-} mass (GeV)");
  massframe->GetYaxis()->SetTitleOffset(1.2);
  data->plotOn(massframe);
  w->pdf("model")->paramOn(massframe);
  w->pdf("model")->plotOn(massframe);
  w->pdf("v1820")->plotOn(massframe, RooFit::LineStyle(kDotted),
  		RooFit::Normalization(w->var("nsig1820")->getVal(), RooAbsReal::NumEvent));
  w->pdf("bkgd")->plotOn(massframe, RooFit::LineStyle(kDotted),
  		RooFit::Normalization(w->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
  w->pdf("v2120")->plotOn(massframe, RooFit::LineStyle(kDotted),
  	RooFit::Normalization(w->var("nsig2120")->getVal(), RooAbsReal::NumEvent));
  massframe->Draw();
  Xi_canvas1->Print(outputname);  
*/

}
