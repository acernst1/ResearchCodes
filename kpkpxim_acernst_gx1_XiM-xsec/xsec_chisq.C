#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"
Color_t color171 = kGreen;
Color_t color181 = kRed;
Color_t color188 = kBlue;
Color_t color;
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
//initialize all the things
double getbincontent(TH1F * AccH, int bin);
double getbinerror(TH1F * AccH, int bin);
char plotname[100];
char accplotname[100];
char accsubplotname[100];
char workspace[100];
char xsec_workspace[100];
char bin[100];
char diffxsec_xiplot[100];
char xsec_xiplot[100];
char xicanvas[100];
char xsec_xicanvas[100];
char mcworkspace[100];
char mc_xsec_workspace[100];
char diffxsec_mcplot[100];
char xsec_mcplot[100];
char mccanvas[100];
char xsec_mccanvas[100];
char mcplotname[100];
char mcaccplotname[100];
char mcaccsubplotname[100];
char tplotname[100];
char effplot[100];
char signal_numbers[100];
char mcsignal_numbers[100];
char fluxmacro[100];
char fluxhist[100];
char thrownmacro[100];
char thrownhist[100];
char diffxsec_chibin_name[100];
char thrownyields_chibin_name[100];
char sigyields_chibin_name[100];
char esigfit_chibin_name[100];
char sigmass_chibin_name[100];
char sigwidth_chibin_name[100];
char mcmass_chibin_name[100];
char mcwidth_chibin_name[100];
char EBin_Title[100];
char mcyields_chibin_name[100];
char eff_chibin_name[100];
char fluxFilePath[100];
char thrownhistname[100];
char XiMasshistname[100];
char XiMasshistnameacc[100];
char MCXiMasshistname[100];
char MCXiMasshistnameacc[100];
char signalyieldshist[100];
char signalyieldsmacro[100];
char signalmasshist[100];
char signalmassmacro[100];
char signalwidthhist[100];
char signalwidthmacro[100];
char mcyieldshist[100];
char mcyieldsmacro[100];
char mcmasshist[100];
char mcmassmacro[100];
char mcwidthhist[100];
char mcwidthmacro[100];
char thrownyieldshist[100];
char ethrownyieldshist[100];
char thrownyieldsmacro[100];
char ethrownyieldsmacro[100];
char effhist[100];
char effmacro[100];
char diffxsechist[100];
char diffxsecmacro[100];
char ethrownmacro[100];
char ethrownhist[100];
char esignalyieldshist[100];
char esignalyieldsmacro[100];
char esignalfithist[100];
char esignalfitmacro[100];
char esignalmasshist[100];
char esignalmassmacro[100];
char esignalwidthhist[100];
char esignalwidthmacro[100];
char emcyieldshist[100];
char emcyieldsmacro[100];
char emcmasshist[100];
char emcmassmacro[100];
char emcwidthhist[100];
char emcwidthmacro[100];
char ebineffhist[100];
char ebineffmacro[100];
char xsechist[100];
char xsecmacro[100];
char pad[100];
double minEval = 8.4;
double maxEval = 8.9;
const int numEBins=1; 
double minmass=1.2; 
double minfitmass=1.27;
double maxmass=1.5; 
const int nummassBins=80;
int columns = 4;
int rows;
double constant = 1.22e-9; // constant in nb
double tagged=1.0;
double tagged_err=0.0;
double canvas_margins = 1e-50;
double deltachi;
double deltaE;
double_t sig_events;
double_t sig_events_err;
double_t sig_mass;
double_t sig_mass_err;
double_t sig_width;
double_t sig_width_err;
double_t xsec_sig_events;
double_t xsec_sig_events_err;
double_t xsec_sig_mass;
double_t xsec_sig_mass_err;
double_t xsec_sig_width;
double_t xsec_sig_width_err;
double getbincontent(TH1F * hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F * AccH, int bin){  return AccH->GetBinError(bin);}

void xsec_chisq(TString dataFilePath, const char fluxFilePathtemp[100], TString mcFilePath, TString thrownFilePath,const char version[50], double minchisq, const int numchiBins)
{
//initialize things that depend on number of energy bins
	int binning = minchisq*10;	
	double maxchisq=6.0; 
	double_t flux_val;
	double_t flux_err;
	double_t xsec_sig_val[numchiBins+1];
	double_t xsec_sig_err[numchiBins+1];
	double_t xsec_mc_val[numchiBins+1];
	double_t xsec_mc_err[numchiBins+1];
	double_t xsec_thrown_val[numchiBins+1];
	double_t xsec_thrown_err[numchiBins+1];
	double_t xsec_eff_val[numchiBins+1];
	double_t xsec_eff_err[numchiBins+1];
	double_t xsec_val[numchiBins+1];
	double_t xsec_err[numchiBins+1];
	TH1F * SignalFits_chibin;
	TH1F * SignalYields_chibin;
	TH1F * SignalMass_chibin;
	TH1F * SignalWidth_chibin;    
	TH1F * MCMass_chibin;
	TH1F * MCWidth_chibin;
	TH1F * MCYields_chibin;
	TH1F * Eff_chibin;
	TH1F * ThrownYields_chibin;
	TH1F * XSec_chibin;
	gStyle->SetOptStat(0);
	deltachi = (maxchisq - minchisq) / float(numchiBins) ;
	deltaE = (maxEval - minEval) / float(numEBins) ;
	cout << "E: " << minEval << " - " << maxEval << " in " << numEBins << " bins with width " << deltaE  << endl;
	cout << "ChiSq: " << minchisq << " - " << maxchisq << " in " << numchiBins << " bins with width " << deltachi  << endl;

//open the necessary files
	sprintf(fluxFilePath,"%s",fluxFilePathtemp);		
	TFile* datafile = TFile::Open(dataFilePath);
	TFile* fluxfile = TFile::Open(fluxFilePath);
	TFile* mcfile = TFile::Open(mcFilePath);
	TFile* thrownfile = TFile::Open(thrownFilePath);

//Create the necessary TCanvases and initialize the appropriate histograms
	TCanvas * flux_canvas = new TCanvas("flux_canvas", "flux_canvas",800,600);
	TCanvas * thrown_canvas = new TCanvas("thrown_canvas", "thrown_canvas",800,600);
	TCanvas * thrownyields_canvas = new TCanvas("thrownyields_canvas", "thrownyields_canvas",1200,900);
	TCanvas * sigyields_canvas = new TCanvas("sigyields_canvas", "sigyields_canvas",1200,900);
	TCanvas * sigmass_canvas = new TCanvas("sigmass_canvas", "sigmass_canvas",1200,900);
	TCanvas * sigwidth_canvas = new TCanvas("sigwidth_canvas", "sigwidth_canvas",1200,900);
	TCanvas * mcyields_canvas = new TCanvas("mcyields_canvas", "mcyields_canvas",1200,900);
	TCanvas * mcmass_canvas = new TCanvas("mcmass_canvas", "mcmass_canvas",1200,900);
	TCanvas * mcwidth_canvas = new TCanvas("mcwidth_canvas", "mcwidth_canvas",1200,900);
	TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",1200,900);
	TCanvas * diffxsec_canvas = new TCanvas("diffxsec_canvas", "diffxsec_canvas",1200,900);
	TCanvas * ethrown_canvas = new TCanvas("ethrown_canvas", "ethrown_canvas",800,600);
	TCanvas * ethrownyields_canvas = new TCanvas("ethrownyields_canvas", "ethrownyields_canvas",800,600);
	ThrownYields_chibin = new TH1F("ThrownYields_chibin", ";-t (GeV^{2}); Thrown Yields (Events)",numchiBins,minchisq,maxchisq);
	TCanvas * esigyields_canvas = new TCanvas("esigyields_canvas", "esigyields_canvas",800,600);
	SignalYields_chibin = new TH1F("SignalYields_chibin", ";-t (GeV^{2}); Signal Yields (Events)",numchiBins,minchisq,maxchisq);
	TCanvas * esigmass_canvas = new TCanvas("esigmass_canvas", "esigmass_canvas",800,600);
	SignalMass_chibin = new TH1F("SignalMass_chibin", ";-t (GeV^{2}); Signal Mass (GeV)",numchiBins,minchisq,maxchisq);
	TCanvas * esigwidth_canvas = new TCanvas("esigwidth_canvas", "esigwidth_canvas",800,600);
	SignalWidth_chibin = new TH1F("SignalWidth_chibin", ";-t (GeV^{2}); Signal Width (GeV)",numchiBins,minchisq,maxchisq);
	TCanvas * emcyields_canvas = new TCanvas("emcyields_canvas", "emcyields_canvas",800,600);
	MCYields_chibin = new TH1F("MCYields_chibin", ";-t (GeV^{2}); MC Yields (Events)",numchiBins,minchisq,maxchisq);
	TCanvas * emcmass_canvas = new TCanvas("emcmass_canvas", "emcmass_canvas",800,600);
	MCMass_chibin = new TH1F("MCMass_chibin", ";-t (GeV^{2}); MC Mass (GeV)",numchiBins,minchisq,maxchisq);
	TCanvas * emcwidth_canvas = new TCanvas("emcwidth_canvas", "emcwidth_canvas",800,600);
	MCWidth_chibin = new TH1F("MCWidth_chibin", ";-t (GeV^{2}); MC Width (GeV)",numchiBins,minchisq,maxchisq);
	TCanvas * ebineff_canvas = new TCanvas("ebineff_canvas", "ebineff_canvas",800,600);
	Eff_chibin = new TH1F("Eff_chibin", ";-t; Efficiency ",numchiBins,minchisq,maxchisq);
	TCanvas * esigfit_canvas = new TCanvas("esigfit_canvas", "esigfit_canvas",800,600);
	TCanvas * xsec_canvas = new TCanvas("xsec_canvas", "xsec_canvas",800,600);
	XSec_chibin = new TH1F("XSec_chibin", "Cross Section;X^{2}/NDF; #sigma (#gamma p -> K^{+}K^{+}#Xi^{-}) (nb)",numchiBins,minchisq,maxchisq);

//Output file names independent of energy bin and t bin
	sprintf(fluxmacro,"Xsec_pieces/Xsec_flux_numbers_%s_%03d_%02dchibins.C",version,binning,numchiBins);
	sprintf(fluxhist,"Xsec_pieces/Xsec_flux_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(ethrownmacro,"Xsec_pieces/Xsec_thrown_numbers_%s_%03d_%02dchibins.C",version,binning, numchiBins);
    sprintf(ethrownhist,"Xsec_pieces/Xsec_thrown_%s_%03d_%02dchibins.png",version,binning, numEBins);
    sprintf(ethrownyieldshist,"Xsec_pieces/Xsec_ThrownYields_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(ethrownyieldsmacro,"Xsec_pieces/Xsec_ThrownYields_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(esignalyieldshist,"Xsec_pieces/Xsec_SignalYields_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(esignalyieldsmacro,"Xsec_pieces/Xsec_SignalYields_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(esignalfithist,"Xsec_systematics/Xsec_SignalFits_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(esignalfitmacro,"Xsec_systematics/Xsec_SignalFits_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(esignalmasshist,"Xsec_systematics/Xsec_SignalMass_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(esignalmassmacro,"Xsec_systematics/Xsec_SignalMass_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(esignalwidthhist,"Xsec_systematics/Xsec_SignalWidth_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(esignalwidthmacro,"Xsec_systematics/Xsec_SignalWidth_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(emcyieldshist,"Xsec_pieces/Xsec_MCyields_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(emcyieldsmacro,"Xsec_pieces/Xsec_MCyields_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(emcmasshist,"Xsec_systematics/Xsec_MCMass_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(emcmassmacro,"Xsec_systematics/Xsec_MCMass_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(emcwidthhist,"Xsec_systematics/Xsec_MCwidth_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(emcwidthmacro,"Xsec_systematics/Xsec_MCwidth_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(ebineffhist,"Xsec_pieces/Xsec_Eff_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(ebineffmacro,"Xsec_pieces/Xsec_Eff_%s_%03d_%02dchibins.C",version,binning,numchiBins);
    sprintf(xsechist,"Xsec_%s_%03d_%02dchibins.png",version,binning,numchiBins);
    sprintf(xsecmacro,"Xsec_%s_%03d_%02dchibins.C",version,binning,numchiBins);

//Create and save flux histogram
	flux_canvas->cd();
	TH1F *  FluxH= (TH1F *) fluxfile->Get("tagged_flux");
	FluxH->Draw(); 
	flux_canvas->SaveAs(fluxmacro);
	flux_canvas->Print(fluxhist);

//Create and save thrown histograms for diff xsec and total xsec
	thrown_canvas->cd();
	thrownfile->cd(); 
	sprintf(thrownhistname,"Egamma_t_064");
	TH2F*  ThrownH= (TH2F*) thrownfile->Get(thrownhistname);
	ThrownH->RebinX(deltaE/ThrownH->GetXaxis()->GetBinWidth(1));    
	ThrownH->RebinY(2.0/ThrownH->GetYaxis()->GetBinWidth(1));
	ThrownH->Draw("colz");
	thrown_canvas->SaveAs(thrownmacro);
	thrown_canvas->Print(thrownhist);
	ethrown_canvas->cd();
	TH1F * ThrownH_chibin = (TH1F *) ThrownH->ProjectionY("ThrownH_chibin",ThrownH->GetXaxis()->FindBin(minEval),ThrownH->GetXaxis()->FindBin(maxEval)-1);
	ThrownH_chibin->Draw();
	ethrown_canvas->SaveAs(ethrownmacro);
	ethrown_canvas->Print(ethrownhist);

//Set up the grid structure of histograms
	if (numEBins % columns == 0) { rows = numEBins/columns; }
	else { rows = numEBins/columns + 1; }	

//Divide the canvases into the grids for histograms
	esigfit_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	sigyields_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	sigmass_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	sigwidth_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	mcyields_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	mcmass_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	mcwidth_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	eff_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	diffxsec_canvas->Divide(columns,rows,canvas_margins,canvas_margins);
	for(int padnumber=1; padnumber<numchiBins+1; padnumber++){
		sprintf(pad,"diffxsec_pad_%02d",padnumber);
		TPad * pad = (TPad *) diffxsec_canvas->cd(padnumber);
		pad->SetLogy();	
	}

//Perform accidental subtraction for signal histogram
	sprintf(XiMasshistname,"Xi_Egamma_ChiSq_064");	
	sprintf(XiMasshistnameacc,"Xi_Egamma_ChiSq_064_wacc");	
	TH3F * XiMassKinFit_Egamma_ChiSq = (TH3F*)datafile->Get(XiMasshistname);
	TH3F * XiMassKinFit_Egamma_ChiSq_acc = (TH3F*)datafile->Get(XiMasshistnameacc);
	TH3F * XiMassKinFit_Egamma_ChiSq_accsub = (TH3F *) XiMassKinFit_Egamma_ChiSq->Clone("XiMassKinFit_Egamma_ChiSq_accsub");
	XiMassKinFit_Egamma_ChiSq_accsub->Add(XiMassKinFit_Egamma_ChiSq_acc,-0.5);

//Perform accidental subtraction for mc histogram
	sprintf(MCXiMasshistname,"Xi_Egamma_ChiSq_064");	
	sprintf(MCXiMasshistnameacc,"Xi_Egamma_ChiSq_064_wacc");	
	TH3F * MC_XiMassKinFit_Egamma_ChiSq = (TH3F*)mcfile->Get(MCXiMasshistname);
	TH3F * MC_XiMassKinFit_Egamma_ChiSq_acc = (TH3F*)mcfile->Get(MCXiMasshistnameacc);
	TH3F * MC_XiMassKinFit_Egamma_ChiSq_accsub = (TH3F *) MC_XiMassKinFit_Egamma_ChiSq->Clone("MC_XiMassKinFit_Egamma_ChiSq_accsub");
	MC_XiMassKinFit_Egamma_ChiSq_accsub->Add(MC_XiMassKinFit_Egamma_ChiSq_acc,-0.5);

//Main beam energy loop
	for(int it=0; it<numchiBins; it++){
		double chimin = deltachi * it + (minchisq);
		double chimax = deltachi * (it+1) + (minchisq);
		int chibuffer = chimin*10;

	//Get thrown values for total cross section
		ethrownyields_canvas->cd(it+1);
		double thrown_chibin = ThrownH_chibin->GetBinContent(0+1);
		double thrown_chibin_err = ThrownH_chibin->GetBinError(0+1);
		xsec_thrown_val[it+1] = thrown_chibin;
		xsec_thrown_err[it+1] = thrown_chibin_err;
		ThrownYields_chibin->SetBinContent(it+1,thrown_chibin);
		ThrownYields_chibin->SetBinError(it+1,thrown_chibin_err);
		cout << "~~~~~~~Thrownxsec~ " << it << "~ " << thrown_chibin << " " << thrown_chibin_err << endl;

	//Create a histogram of signal for this particular energy bin
		int Ebinmin = XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->FindBin(minEval);
		int Ebinmax = XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->FindBin(maxEval) -1.;
		int MC_Ebinmin = MC_XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->FindBin(minEval);
		int MC_Ebinmax = MC_XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->FindBin(maxEval) -1.;
		XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->SetRange(XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->FindBin(0.0),XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->FindBin(chimax)-1);	
		XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
		TH1F * XiMassKinFit_chibin_accsub = (TH1F *) XiMassKinFit_Egamma_ChiSq_accsub->Project3D("x");
		XiMassKinFit_chibin_accsub->Rebin(XiMassKinFit_chibin_accsub->GetNbinsX()/nummassBins);

	//Create a histogram of mc for this particular energy bin	
		MC_XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->SetRange(MC_XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->FindBin(0.0),MC_XiMassKinFit_Egamma_ChiSq_accsub->GetZaxis()->FindBin(chimax)-1);	
		MC_XiMassKinFit_Egamma_ChiSq_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
		TH1F * MC_XiMassKinFit_chibin_accsub = (TH1F *) MC_XiMassKinFit_Egamma_ChiSq_accsub->Project3D("x");

	//Only perform signal fit for total cross section if there are at least 20 entries in the whole histogram
		if(XiMassKinFit_chibin_accsub->GetEntries() < 20){
			xsec_sig_events = 0.0;
			xsec_sig_events_err = 0.0;
			xsec_sig_mass = 0.0;
			xsec_sig_mass_err = 0.0;
			xsec_sig_width =  0.0;
			xsec_sig_width_err =  0.0;
		} //end not enough signal loop for total cross section
		else{	//Set up and perform signal fit for total cross section
			sprintf(xsec_xiplot,"Xsec_fits/Xsec_sigfit_%s_%03d_%02dchibins_%03d.png",version, binning,numchiBins,chibuffer);
			sprintf(xsec_workspace,"w%03d",chibuffer);
			sprintf(xsec_xicanvas,"Xi_canvas_%03d",chibuffer);
			TCanvas * Xsec_Xi_canvas = new TCanvas(xsec_xicanvas, xsec_xicanvas,800,600);
			RooWorkspace* xsecw = new RooWorkspace(xsec_workspace);
			RooRealVar xsecmass("xsecmass", "xsecmass", minmass, maxmass);
			RooDataHist *xsecdata = new RooDataHist("xsecdata", "Dataset of mass", xsecmass, XiMassKinFit_chibin_accsub);
			XiMassKinFit_chibin_accsub->Print();
			xsecw->import(RooArgSet(xsecmass));
			xsecw->factory("Chebychev::xsecbkgd(xsecmass,{c1t[2.20,-1.e4,1.e4],c2t[-1.557,-1.e4,1.e4]})");
			xsecw->factory("Gaussian::xsecgaus(xsecmass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");
			xsecw->factory("SUM::xsecmodel(nbkgd[150,0,1e5]*xsecbkgd, nsig[20,0,1e4]*xsecgaus)");
			xsecw->pdf("xsecmodel")->fitTo(*xsecdata,RooFit::Range(minfitmass,maxmass),RooFit::Minos(1));
			RooPlot* xsecmassframe = xsecmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
			xsecmassframe->SetXTitle("#Lambda#pi^{-} mass");
			xsecdata->plotOn(xsecmassframe) ;
			xsecw->pdf("xsecmodel")->paramOn(xsecmassframe);
			xsecw->pdf("xsecmodel")->plotOn(xsecmassframe);
			xsecw->pdf("xsecgaus")->plotOn(xsecmassframe, RooFit::LineStyle(kDotted),
			RooFit::Normalization(xsecw->var("nsig")->getVal(), RooAbsReal::NumEvent));
			xsecw->pdf("xsecbkgd")->plotOn(xsecmassframe, RooFit::LineStyle(kDotted),
			RooFit::Normalization(xsecw->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
			xsec_sig_events = xsecw->var("nsig")->getVal();
			xsec_sig_events_err = xsecw->var("nsig")->getError();
			xsec_sig_mass = xsecw->var("mean")->getVal();
			xsec_sig_mass_err = xsecw->var("mean")->getError();
			xsec_sig_width = xsecw->var("sigma")->getVal();
			xsec_sig_width_err = xsecw->var("sigma")->getError();
			double max_xsec_y = sig_events*0.3;
			xsecmassframe->SetMaximum(max_xsec_y);
			xsecmassframe->Draw();
			Xsec_Xi_canvas->Print(xsec_xiplot);
			esigfit_canvas->cd(it+1);
			xsecmassframe->Draw();
		} //end enough signal loop for total cross section

	//Save signal fit yields and error for total cross section
		xsec_sig_val[it+1] = xsec_sig_events;
		xsec_sig_err[it+1] = xsec_sig_events_err;
		cout << "~~~~~~~sigxsec~" << it << "~ " << xsec_sig_events << " " << xsec_sig_events_err << endl; 
		esigyields_canvas->cd();	
		SignalYields_chibin->SetBinContent(it+1,xsec_sig_events);
		SignalYields_chibin->SetBinError(it+1,xsec_sig_events_err);
		esigmass_canvas->cd();
		SignalMass_chibin->SetBinContent(it+1,xsec_sig_mass); 
		SignalMass_chibin->SetBinError(it+1,xsec_sig_mass_err);
		esigwidth_canvas->cd();
		SignalWidth_chibin->SetBinContent(it+1,xsec_sig_width);
		SignalWidth_chibin->SetBinError(it+1,xsec_sig_width_err);

	//MC fit for total cross section 
		sprintf(xsec_mcplot,"Xsec_fits/Xsec_mcfit_%s_%03d_%02dchibins_%03d.png",version, binning,numchiBins,chibuffer);	
		sprintf(mc_xsec_workspace,"wmc%03d",chibuffer);
		sprintf(xsec_mccanvas,"Xi_canvas_mc_%03d",chibuffer);
		TCanvas * Xsec_Xi_mc_canvas = new TCanvas(xsec_mccanvas, xsec_mccanvas,800,600);
		RooWorkspace* xsecwmc = new RooWorkspace(mc_xsec_workspace);
		RooRealVar xsecmcmass("xsecmcmass", "xsecmcmass", minmass, maxmass);
		RooDataHist *xsecmc = new RooDataHist("xsecmc", "MC of mass", xsecmcmass, MC_XiMassKinFit_chibin_accsub );
		MC_XiMassKinFit_chibin_accsub->Print();
		xsecwmc->import(RooArgSet(xsecmcmass));
		xsecwmc->factory("Gaussian::xsecgausmc(xsecmcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
		xsecwmc->factory("SUM::xsecmcmodel(nsigmc[50,0,1e6]*xsecgausmc)");
		xsecwmc->pdf("xsecmcmodel")->fitTo(*xsecmc,RooFit::Range(1.305,1.35),RooFit::Minos(1));
		RooPlot* xsecmcmassframe = xsecmcmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
		xsecmcmassframe->SetXTitle("#Lambda#pi^{-} mass");
		xsecmc->plotOn(xsecmcmassframe) ;
		xsecwmc->pdf("xsecmcmodel")->paramOn(xsecmcmassframe);
		xsecwmc->pdf("xsecmcmodel")->plotOn(xsecmcmassframe);
		xsecwmc->pdf("xsecgausmc")->plotOn(xsecmcmassframe, RooFit::LineStyle(kDotted),
		RooFit::Normalization(xsecwmc->var("nsigmc")->getVal(), RooAbsReal::NumEvent));
		double_t xsec_mc_sig_events = xsecwmc->var("nsigmc")->getVal();
		double_t xsec_mc_sig_events_err = xsecwmc->var("nsigmc")->getError();
		double_t xsec_mc_mass = xsecwmc->var("meanmc")->getVal();
		double_t xsec_mc_mass_err = xsecwmc->var("meanmc")->getError();
		double_t xsec_mc_width = xsecwmc->var("sigmamc")->getVal();
		double_t xsec_mc_width_err = xsecwmc->var("sigmamc")->getError();
		xsec_mc_val[it+1] = xsec_mc_sig_events;
		xsec_mc_err[it+1] = xsec_mc_sig_events_err;
		cout << "~~~~~~~MCxsec~" << it << "~ " << xsec_mc_sig_events << " " << xsec_mc_sig_events_err << endl; 
		double xsec_mc_max_y = xsec_mc_sig_events *0.5;
		xsecmcmassframe->SetMaximum(xsec_mc_max_y);
		xsecmcmassframe->Draw();
		Xsec_Xi_mc_canvas->Print(xsec_mcplot);

	// Save MC information to histograms binned in beam energy
		emcyields_canvas->cd();	
		MCYields_chibin->SetBinContent(it+1,xsec_mc_sig_events);
		MCYields_chibin->SetBinError(it+1,xsec_mc_sig_events_err);
		emcmass_canvas->cd();
		MCMass_chibin->SetBinContent(it+1,xsec_mc_mass); 
		MCMass_chibin->SetBinError(it+1,xsec_mc_mass_err);
		emcwidth_canvas->cd();
		MCWidth_chibin->SetBinContent(it+1,xsec_mc_width);
		MCWidth_chibin->SetBinError(it+1,xsec_mc_width_err);

	//Get flux values
		flux_val=FluxH->IntegralAndError(FluxH->FindBin(minEval),FluxH->FindBin(maxEval)-1,flux_err,"");
		cout << "~~~~~~~flux~" << it << "~" << flux_val << " " << flux_err << endl;

	//Calculate efficiencies and total cross section in terms of only energy binning
		xsec_eff_val[it+1] = xsec_mc_val[it+1]/xsec_thrown_val[it+1];
		xsec_eff_err[it+1] = xsec_eff_val[it+1] * sqrt(pow(xsec_mc_err[it+1]/xsec_mc_val[it+1],2)+pow(xsec_thrown_err[it+1]/xsec_thrown_val[it+1],2));
		cout << "~~~~~~~Effxsec~" << it << "~" << xsec_eff_val[it+1] << " " << xsec_eff_err[it+1] << endl;
		Eff_chibin->SetBinContent(it+1,xsec_eff_val[it+1]);
		Eff_chibin->SetBinError(it+1,xsec_eff_err[it+1]);
		xsec_val[it+1] = (xsec_sig_val[it+1])/(deltachi * constant * flux_val * (xsec_mc_val[it+1]/xsec_thrown_val[it+1]));
		if(xsec_sig_val[it+1] != 0){ //Calculate normally
		    xsec_err[it+1] = xsec_val[it+1]*sqrt(pow(xsec_sig_err[it+1]/xsec_sig_val[it+1],2)+pow(flux_err/flux_val,2)+pow(xsec_mc_err[it+1]/xsec_mc_val[it+1],2)+pow(xsec_thrown_err[it+1]/xsec_thrown_val[it+1],2));
		}
		else{ 
			xsec_err[it+1] = 0.0; // Set to zero if fit wasn't performed to prevent NaNs.
		}	
		cout << "~~~~~~~Xsec~" << it << "~" << xsec_val[it+1] << " " << xsec_err[it+1] << endl;
		XSec_chibin->SetBinContent(it+1,xsec_val[it+1]);
		XSec_chibin->SetBinError(it+1,xsec_err[it+1]);

	//Draw and save histograms that depend on energy bin
		esigfit_canvas->cd(it+1);
		esigfit_canvas->Print(esignalfithist);
		esigfit_canvas->SaveAs(esignalfitmacro);

} //end E loop

//Save all the total cross section histograms
	ethrownyields_canvas->cd();
	ThrownYields_chibin->Draw("pe1");
	ethrownyields_canvas->Print(ethrownyieldshist);
	ethrownyields_canvas->SaveAs(ethrownyieldsmacro);

	esigyields_canvas->cd();
	SignalYields_chibin->Draw("pe1");
	esigyields_canvas->Print(esignalyieldshist);
	esigyields_canvas->SaveAs(esignalyieldsmacro);

	emcyields_canvas->cd();
	MCYields_chibin->Draw("pe1");
	emcyields_canvas->Print(emcyieldshist);
	emcyields_canvas->SaveAs(emcyieldsmacro);

	esigmass_canvas->cd();
	SignalMass_chibin->Draw("pe1");
	esigmass_canvas->Print(esignalmasshist);
	esigmass_canvas->SaveAs(esignalmassmacro);

	emcmass_canvas->cd();
	MCMass_chibin->Draw("pe1");
	emcmass_canvas->Print(emcmasshist);
	emcmass_canvas->SaveAs(emcmassmacro);

	esigwidth_canvas->cd();
	SignalWidth_chibin->Draw("pe1");
	esigwidth_canvas->Print(esignalwidthhist);
	esigwidth_canvas->SaveAs(esignalwidthmacro);

	emcwidth_canvas->cd();
	MCWidth_chibin->Draw("pe1");
	emcwidth_canvas->Print(emcwidthhist);
	emcwidth_canvas->SaveAs(emcwidthmacro);

	ebineff_canvas->cd();
	Eff_chibin->Draw("pe1");
	ebineff_canvas->Print(ebineffhist);
	ebineff_canvas->SaveAs(ebineffmacro);

	xsec_canvas->cd();
	XSec_chibin->GetXaxis()->SetRangeUser(0,12.5);
	XSec_chibin->GetYaxis()->SetRangeUser(0,15);
	if(std::strstr(version,"2017_01") != NULL){ color = color171;} 
	if(std::strstr(version,"2018_01") != NULL){ color = color181;} 
	if(std::strstr(version,"2018_08") != NULL){ color = color188;} 
	setformatTH1F(XSec_chibin,color,data);
	XSec_chibin->Draw("pe1");
	xsec_canvas->Print(xsechist);
	xsec_canvas->SaveAs(xsecmacro);

//Print out all values at end of running
for(int itbin=0; itbin<numchiBins; itbin++){
	cout << "chi: " << 0.0 << " - " << deltachi * (itbin+1) + (minchisq) << endl; 
	cout << "\t" << "Energy:  " 		<< minEval << " - " << maxEval << endl; 
	cout << "\t" << "Signal Yields: " 	<< xsec_sig_val[itbin+1] 	<< " +/- " 	<< xsec_sig_err[itbin+1] 	<< endl;
	cout << "\t" << "MC Yields: " 		<< xsec_mc_val[itbin+1] 	<< " +/- " 	<< xsec_mc_err[itbin+1] 	<< endl;
	cout << "\t" << "Thrown Yields: " 	<< xsec_thrown_val[itbin+1] 	<< " +/- " 	<< xsec_thrown_err[itbin+1] 	<< endl;
	cout << "\t" << "Flux Yields: " 	<< flux_val		<< " +/- " 	<< flux_err		<< endl;
	cout << "\t" << "Efficiency: " 		<< xsec_eff_val[itbin+1] 	<< " +/- " 	<< xsec_eff_err[itbin+1] 	<< endl;
	cout << "\t" << "XSec: " 			<< xsec_val[itbin+1] 		<< " +/- " 	<< xsec_err[itbin+1] 		<< endl;
} //end print E loop

return;	

} //end macro

