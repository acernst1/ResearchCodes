#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

//initialize all the things
double getbincontent(TH1F* AccH, int bin);
double getbinerror(TH1F* AccH, int bin);
char plotname[100];
char accplotname[100];
char accsubplotname[100];
char workspace[100];
char bin[100];
char plot[100];
char canvas[100];
char mcworkspace[100];
char mcplot[100];
char mccanvas[100];
char mcplotname[100];
char mcaccplotname[100];
char mcaccsubplotname[100];
char tplotname[100];
char effplot[100];
char signal_numbers[100];
char mcsignal_numbers[100];
char xsecplot[100];
char xsecplotC[100];
char flux_macro_name[100];
char flux_plot_name[100];
char thrown_numbers_macro_name[100];
char thrown_numbers_plot_name[100];
char xsec_EBin_name[100];
char sigyields_EBin_name[100];
char sigmass_EBin_name[100];
char sigwidth_EBin_name[100];
char mcmass_EBin_name[100];
char mcwidth_EBin_name[100];
char EBin_Title[100];
char mcyields_EBin_name[100];
char eff_EBin_name[100];
char fluxFilePath[100];
char thrownhistname[100];
char XiMasshistname[100];
char XiMasshistnameacc[100];
char signalyieldshist[100];
char signatyieldsmacro[100];
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
char effhist[100];
char effmacro[100];
char diffxsechist[100];
char diffxsecmacro[100];
double mintval = 0.0;
double maxtval = 5.0;
const int numtBins=10; 
double minmass=1.2; 
double minfitmass=1.27;
double maxmass=1.5; 
const int nummassBins=80;
double constant = 1.22e-9; // constant in nb
double tagged=1.0;
double tagged_err=0.0;
double canvas_margins = 1e-50;
double deltat;
double deltaE;
double_t sig_events;
double_t sig_events_err;
double_t sig_mass;
double_t sig_mass_err;
double_t sig_width;
double_t sig_width_err;
double getbincontent(TH1F* hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F* AccH, int bin){  return AccH->GetBinError(bin);}

void xsec_diff(TString dataFilePath, const char fluxFilePathtemp[100], TString mcFilePath, TString thrownFilePath1,const char version[17], double minEval, const int numEBins)
{
    int binning = minEval*10;	
    double maxEval=minEval + 5.0; 
    double_t sig_val[numEBins+1][numtBins+1];
    double_t sig_err[numEBins+1][numtBins+1];
    double_t mc_val[numEBins+1][numtBins+1];
    double_t mc_err[numEBins+1][numtBins+1];
    double_t thrown_val[numEBins+1][numtBins+1];
    double_t thrown_err[numEBins+1][numtBins+1];
    double_t flux_val[numEBins+1];
    double_t flux_err[numEBins+1];
    double_t eff_val[numEBins+1][numtBins+1];
    double_t eff_err[numEBins+1][numtBins+1];
    double_t xsec_val[numEBins+1][numtBins+1];
    double_t xsec_err[numEBins+1][numtBins+1];
    TH1F * SignalYields[numEBins+1];
    TH1F * SignalMass[numEBins+1];
    TH1F * SignalWidth[numEBins+1];    
    TH1F * MCMass[numEBins+1];
    TH1F * MCWidth[numEBins+1];
    TH1F * MCYields[numEBins+1];
    TH1F * Eff[numEBins+1];
    TH1F * ThrownYields[numEBins+1];
    TH1F * XSec[numEBins+1];

    gStyle->SetOptStat(0);
    deltat = (maxtval - mintval) / float(numtBins) ;
    deltaE = (maxEval - minEval) / float(numEBins) ;

    sprintf(fluxFilePath,"%s_%03d.root",fluxFilePathtemp,binning);		
    TFile* datafile = TFile::Open(dataFilePath);
    TFile* fluxfile = TFile::Open(fluxFilePath);
    TFile* mcfile = TFile::Open(mcFilePath);

    TCanvas * flux_canvas = new TCanvas("flux_canvas", "flux_canvas",800,600);
    TH1F*  FluxH= (TH1F*) fluxfile->Get("tagged_flux");
    FluxH->Rebin(deltaE/FluxH->GetBinWidth(1));
    FluxH->Draw(); 
    sprintf(flux_macro_name,"flux_numbers_%s_%03d_%02dbins.C",version,binning,numEBins);
    FluxH->SaveAs(flux_macro_name);
    sprintf(flux_plot_name,"xsec_flux_%s_%03d_%02dbins.png",version,binning,numEBins);
    flux_canvas->Print(flux_plot_name);

    TFile* thrownfile = TFile::Open(thrownFilePath1);
    TCanvas * thrown_canvas = new TCanvas("thrown_canvas", "thrown_canvas",800,600);
    thrown_canvas->cd();
    thrownfile->cd(); 
    sprintf(thrownhistname,"Egamma_t_%03d",binning);
    TH2F*  ThrownH= (TH2F*) thrownfile->Get(thrownhistname);
    ThrownH->RebinX(deltaE/ThrownH->GetXaxis()->GetBinWidth(1));    
    ThrownH->RebinY(deltat/ThrownH->GetYaxis()->GetBinWidth(1));
    ThrownH->Draw("colz");
    sprintf(thrown_numbers_macro_name,"thrown_numbers_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(thrown_numbers_plot_name, "xsec_thrown_%s_%03d_%02dbins.png",version,binning,numEBins);
    ThrownH->SaveAs(thrown_numbers_macro_name);
    thrown_canvas->Print(thrown_numbers_plot_name);

    TCanvas * sigyields_canvas = new TCanvas("sigyields_canvas", "sigyields_canvas",1200,900);
    sigyields_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * sigmass_canvas = new TCanvas("sigmass_canvas", "sigmass_canvas",1200,900);
    sigmass_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * sigwidth_canvas = new TCanvas("sigwidth_canvas", "sigwidth_canvas",1200,900);
    sigwidth_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * mcyields_canvas = new TCanvas("mcyields_canvas", "mcyields_canvas",1200,900);
    mcyields_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * mcmass_canvas = new TCanvas("mcmass_canvas", "mcmass_canvas",1200,900);
    mcmass_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * mcwidth_canvas = new TCanvas("mcwidth_canvas", "mcwidth_canvas",1200,900);
    mcwidth_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",1200,900);
    eff_canvas->Divide(4,3,canvas_margins,canvas_margins);

    TCanvas * xsec_canvas = new TCanvas("xsec_canvas", "xsec_canvas",1200,900);
    xsec_canvas->Divide(4,3,canvas_margins,canvas_margins);

   sprintf(XiMasshistname,"Xi_Egamma_t_%03d",binning);	
   sprintf(XiMasshistnameacc,"Xi_Egamma_t_%03d_acc",binning);	
   TH3F * XiMassKinFit_Egamma_t = (TH3F*)datafile->Get(XiMasshistname);
   TH3F * XiMassKinFit_Egamma_t_acc = (TH3F*)datafile->Get(XiMasshistnameacc);
   TH3F * XiMassKinFit_Egamma_t_accsub = (TH3F *) XiMassKinFit_Egamma_t->Clone("XiMassKinFit_Egamma_t_accsub");
   XiMassKinFit_Egamma_t_accsub->Add(XiMassKinFit_Egamma_t_acc,-0.5);

   TH3F * MC_XiMassKinFit_Egamma_t = (TH3F*)mcfile->Get(XiMasshistname);
   TH3F * MC_XiMassKinFit_Egamma_t_acc = (TH3F*)mcfile->Get(XiMasshistnameacc);
   TH3F * MC_XiMassKinFit_Egamma_t_accsub = (TH3F *) MC_XiMassKinFit_Egamma_t->Clone("MC_XiMassKinFit_Egamma_t_accsub");
   MC_XiMassKinFit_Egamma_t_accsub->Add(MC_XiMassKinFit_Egamma_t_acc,-0.5);

    for(int iE=0; iE<numEBins; iE++){
	sigyields_canvas->cd(iE+1);
	double Emin = deltaE * iE + (minEval);
	double Emax = deltaE * (iE+1) + (minEval);
	int Ebuffer = Emin*10;
	int Ebinmin = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
	int Ebinmax = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
	XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
	TH2F * XiMassKinFit_Ebin_t_accsub = (TH2F *) XiMassKinFit_Egamma_t_accsub->Project3D("xz");
	sprintf(sigyields_EBin_name,"sigyields_%03d",Ebuffer);
    	SignalYields[iE+1] = new TH1F(sigyields_EBin_name, "; -t (GeV^2); Yields",numtBins,mintval,maxtval); 
	sprintf(EBin_Title,"%3.1f <= E_{#gamma} < %3.1f",Emin,Emax);
	SignalYields[iE+1]->SetTitle(EBin_Title);
    	SignalYields[iE+1]->SetMarkerColor(kRed);
    	SignalYields[iE+1]->SetMarkerStyle(21);
    	SignalYields[iE+1]->SetLabelSize(0.035,"xy");
    	SignalYields[iE+1]->SetLabelOffset(0.001,"xy");

	sigmass_canvas->cd(iE+1);
	sprintf(sigmass_EBin_name,"sigmass_%03d",Ebuffer);
    	SignalMass[iE+1] = new TH1F(sigmass_EBin_name, "; -t (GeV^2); Mass",numtBins,mintval,maxtval); 
	SignalMass[iE+1]->SetTitle(EBin_Title);
    	SignalMass[iE+1]->SetMarkerColor(kRed);
    	SignalMass[iE+1]->SetMarkerStyle(21);
    	SignalMass[iE+1]->SetLabelSize(0.035,"xy");
    	SignalMass[iE+1]->SetLabelOffset(0.001,"xy");

	sigwidth_canvas->cd(iE+1);
	sprintf(sigwidth_EBin_name,"sigwidth_%03d",Ebuffer);
    	SignalWidth[iE+1] = new TH1F(sigwidth_EBin_name, "; -t (GeV^2); Width",numtBins,mintval,maxtval); 
	SignalWidth[iE+1]->SetTitle(EBin_Title);
    	SignalWidth[iE+1]->SetMarkerColor(kRed);
    	SignalWidth[iE+1]->SetMarkerStyle(21);
    	SignalWidth[iE+1]->SetLabelSize(0.035,"xy");
    	SignalWidth[iE+1]->SetLabelOffset(0.001,"xy");

	mcyields_canvas->cd(iE+1);
	int MC_Ebinmin = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
	int MC_Ebinmax = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
	MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(MC_Ebinmin,MC_Ebinmax);
	TH2F * MC_XiMassKinFit_Ebin_t_accsub = (TH2F *) MC_XiMassKinFit_Egamma_t_accsub->Project3D("xz");
	sprintf(mcyields_EBin_name,"mcyields_%03d",Ebuffer);
    	MCYields[iE+1] = new TH1F(mcyields_EBin_name, "; -t (GeV^2); Yields",numtBins,mintval,maxtval); 
	MCYields[iE+1]->SetTitle(EBin_Title);
    	MCYields[iE+1]->SetMarkerColor(kRed);
    	MCYields[iE+1]->SetMarkerStyle(21);
    	MCYields[iE+1]->SetLabelSize(0.035,"xy");
    	MCYields[iE+1]->SetLabelOffset(0.001,"xy");

	mcmass_canvas->cd(iE+1);
	sprintf(mcmass_EBin_name,"mcmass_%03d",Ebuffer);
    	MCMass[iE+1] = new TH1F(mcmass_EBin_name, "; -t (GeV^2); Mass",numtBins,mintval,maxtval); 
	MCMass[iE+1]->SetTitle(EBin_Title);
    	MCMass[iE+1]->SetMarkerColor(kRed);
    	MCMass[iE+1]->SetMarkerStyle(21);
    	MCMass[iE+1]->SetLabelSize(0.035,"xy");
    	MCMass[iE+1]->SetLabelOffset(0.001,"xy");

	mcwidth_canvas->cd(iE+1);
	sprintf(mcwidth_EBin_name,"mcwidth_%03d",Ebuffer);
    	MCWidth[iE+1] = new TH1F(mcwidth_EBin_name, "; -t (GeV^2); Width",numtBins,mintval,maxtval); 
	MCWidth[iE+1]->SetTitle(EBin_Title);
    	MCWidth[iE+1]->SetMarkerColor(kRed);
    	MCWidth[iE+1]->SetMarkerStyle(21);
    	MCWidth[iE+1]->SetLabelSize(0.035,"xy");
    	MCWidth[iE+1]->SetLabelOffset(0.001,"xy");

	eff_canvas->cd(iE+1);
	sprintf(eff_EBin_name,"eff_%03d",Ebuffer);
    	Eff[iE+1] = new TH1F(eff_EBin_name, "; -t (GeV^2); Efficiency (%)",numtBins,mintval,maxtval); 
	Eff[iE+1]->SetTitle(EBin_Title);
    	Eff[iE+1]->SetMarkerColor(kRed);
    	Eff[iE+1]->SetMarkerStyle(21);
    	Eff[iE+1]->SetLabelSize(0.035,"xy");
    	Eff[iE+1]->SetLabelOffset(0.001,"xy");

	xsec_canvas->cd(iE+1);
	sprintf(xsec_EBin_name,"xsec_%03d",Ebuffer);
    	XSec[iE+1] = new TH1F(xsec_EBin_name, "; -t (GeV^2); d#sigma/dt (nb)",numtBins,mintval,maxtval); 
	XSec[iE+1]->SetTitle(EBin_Title);
    	XSec[iE+1]->SetMarkerColor(kRed);
    	XSec[iE+1]->SetMarkerStyle(21);
    	XSec[iE+1]->SetLabelSize(0.035,"xy");
    	XSec[iE+1]->SetLabelOffset(0.001,"xy");

	for(int it =0; it<numtBins; it++){
		double tmin = deltat * it + mintval;
		double tmax = deltat * (it+1) +mintval;
		int tbuffer = tmin*10;
		int tbinmin = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int tbinmax = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(tbinmin,tbinmax);
		TH1F * XiMassKinFit_Ebin_tbin_accsub = (TH1F *) XiMassKinFit_Ebin_t_accsub->ProjectionY("XiMassKinFit_Ebin_tbin_accsub",tbinmin,tbinmax);
		XiMassKinFit_Ebin_tbin_accsub->Rebin(XiMassKinFit_Ebin_tbin_accsub->GetNbinsX()/nummassBins);

		int MC_tbinmin = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int MC_tbinmax = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(MC_tbinmin,MC_tbinmax);
		TH1F * MC_XiMassKinFit_Ebin_tbin_accsub = (TH1F *) MC_XiMassKinFit_Ebin_t_accsub->ProjectionY("MC_XiMassKinFit_Ebin_tbin_accsub",MC_tbinmin,MC_tbinmax); 
		MC_XiMassKinFit_Ebin_tbin_accsub->Rebin(MC_XiMassKinFit_Ebin_tbin_accsub->GetNbinsX()/nummassBins);

		sprintf(workspace,"w%03d_%03d",Ebuffer,tbuffer);
        	sprintf(canvas,"Xi_canvas_%03d_%03d",Ebuffer,tbuffer);
        	sprintf(plot,"diffxsec_sigfit_%s_%03d_%02dbins_%03d_%03d.png",version,binning,numEBins,Ebuffer,tbuffer);
       
		 sprintf(mcworkspace,"wmc%03d_%03d",Ebuffer,tbuffer);
		sprintf(mccanvas,"Xi_canvas_mc_%03d_%03d",Ebuffer,tbuffer);
        	sprintf(mcplot,"diffxsec_mcfit_%s_%03d_%02dbins_%03d_%03d.png",version,binning,numEBins,Ebuffer,tbuffer);
       
		if(XiMassKinFit_Ebin_tbin_accsub->GetEntries() < 20){
			sig_events = 0.0;
			sig_events_err = 0.0;
			sig_mass = 0.0;
			sig_mass_err = 0.0;
			sig_width =  0.0;
			sig_width_err =  0.0;
		}
		else{
			RooWorkspace* w = new RooWorkspace(workspace);
        		TCanvas * Xi_canvas = new TCanvas(canvas, canvas,800,600);
        		RooRealVar mass("mass", "mass", minmass, maxmass);
        		RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, XiMassKinFit_Ebin_tbin_accsub);
        		XiMassKinFit_Ebin_tbin_accsub->Print();
        		w->import(RooArgSet(mass));
        		w->factory("Chebychev::bkgd(mass,{c1[2.20,-1.e4,1.e4],c2[-1.557,-1.e4,1.e4]})");
        		w->factory("Gaussian::gaus(mass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");
        		w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[20,0,1e3]*gaus)");
        		w->pdf("model")->fitTo(*data,RooFit::Range(minfitmass,maxmass),RooFit::Minos(1));
        		RooPlot* massframe = mass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        		massframe->SetXTitle("#Lambda#pi^{-} mass");
        		data->plotOn(massframe) ;
        		w->pdf("model")->paramOn(massframe);
        		w->pdf("model")->plotOn(massframe);
        		w->pdf("gaus")->plotOn(massframe, RooFit::LineStyle(kDotted),
 				RooFit::Normalization(w->var("nsig")->getVal(), RooAbsReal::NumEvent));
        		w->pdf("bkgd")->plotOn(massframe, RooFit::LineStyle(kDotted),
  				RooFit::Normalization(w->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
			sig_events = w->var("nsig")->getVal();
			sig_events_err = w->var("nsig")->getError();
			sig_mass = w->var("mean")->getVal();
			sig_mass_err = w->var("mean")->getError();
			sig_width = w->var("sigma")->getVal();
			sig_width_err = w->var("sigma")->getError();
		}
		sig_val[iE+1][it+1] = sig_events;
		sig_err[iE+1][it+1] = sig_events_err;
		cout << "~~~~~~~sig~" << iE << "~" << it << " " << sig_events << " " << sig_events_err << endl; 
		double max_y = sig_events*0.3;
		massframe->SetMaximum(max_y);
        	massframe->Draw();
	     	Xi_canvas->Print(plot);

       		RooWorkspace* wmc = new RooWorkspace(mcworkspace);
        	TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
        	RooRealVar mcmass("mcmass", "mcmass", minmass, maxmass);
        	RooDataHist *mc = new RooDataHist("mc", "MC of mass", mcmass, MC_XiMassKinFit_Ebin_tbin_accsub );
        	MC_XiMassKinFit_Ebin_tbin_accsub->Print();
        	wmc->import(RooArgSet(mcmass));
        	wmc->factory("Gaussian::gausmc(mcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
        	wmc->factory("SUM::mcmodel(nsigmc[50,0,1e6]*gausmc)");
        	wmc->pdf("mcmodel")->fitTo(*mc,RooFit::Range(1.305,1.35),RooFit::Minos(1));
        	RooPlot* mcmassframe = mcmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        	mcmassframe->SetXTitle("#Lambda#pi^{-} mass");
        	mc->plotOn(mcmassframe) ;
        	wmc->pdf("mcmodel")->paramOn(mcmassframe);
       	 	wmc->pdf("mcmodel")->plotOn(mcmassframe);
        	wmc->pdf("gausmc")->plotOn(mcmassframe, RooFit::LineStyle(kDotted),
 			RooFit::Normalization(wmc->var("nsigmc")->getVal(), RooAbsReal::NumEvent));
        	double_t mc_sig_events = wmc->var("nsigmc")->getVal();
		double_t mc_sig_events_err = wmc->var("nsigmc")->getError();
		double_t mc_mass = wmc->var("meanmc")->getVal();
		double_t mc_mass_err = wmc->var("meanmc")->getError();
		double_t mc_width = wmc->var("sigmamc")->getVal();
		double_t mc_width_err = wmc->var("sigmamc")->getError();
		mc_val[iE+1][it+1] = mc_sig_events;
		mc_err[iE+1][it+1] = mc_sig_events_err;
		cout << "~~~~~~~MC~" << iE << "~" << it << " " << mc_sig_events << " " << mc_sig_events_err << endl; 
		double mc_max_y = mc_sig_events *0.5;
		mcmassframe->SetMaximum(mc_max_y);
        	mcmassframe->Draw();
	     	Xi_mc_canvas->Print(mcplot);

		SignalYields[iE+1]->SetBinContent(it+1,sig_events);
		SignalYields[iE+1]->SetBinError(it+1,sig_events_err);
		SignalMass[iE+1]->SetBinContent(it+1,sig_mass);
		SignalMass[iE+1]->SetBinError(it+1,sig_mass_err);
		SignalWidth[iE+1]->SetBinContent(it+1,sig_width);
		SignalWidth[iE+1]->SetBinError(it+1,sig_width_err);
		
		MCYields[iE+1]->SetBinContent(it+1,mc_sig_events);
		MCYields[iE+1]->SetBinError(it+1,mc_sig_events_err);
		MCMass[iE+1]->SetBinContent(it+1,mc_mass);
		MCMass[iE+1]->SetBinError(it+1,mc_mass_err);
		MCWidth[iE+1]->SetBinContent(it+1,mc_width);
		MCWidth[iE+1]->SetBinError(it+1,mc_width_err);

		double thrown_Ebin_tbin = ThrownH->GetBinContent(iE+1,it+1);
		double thrown_Ebin_tbin_err = ThrownH->GetBinError(iE+1,it+1);
		thrown_val[iE+1][it+1] = ThrownH->GetBinContent(iE+1,it+1);
		thrown_err[iE+1][it+1] = ThrownH->GetBinError(iE+1,it+1);
		cout << "~~~~~~~Thrown~ " << iE << "~" << it << " " << thrown_Ebin_tbin << " " << thrown_Ebin_tbin_err << endl;

        	flux_val[iE+1]=getbincontent(FluxH,iE+1);
        	flux_err[iE+1]=getbinerror(FluxH,iE+1); //+1 because 0 is the underflow
		cout << "~~~~~~~flux~" << iE << "~" << it << " " << flux_val[iE+1] << " " << flux_err[iE+1] << endl;

		eff_val[iE+1][it+1] = mc_val[iE+1][it+1]/thrown_val[iE+1][it+1];
		eff_err[iE+1][it+1] = eff_val[iE+1][it+1] * sqrt(pow(mc_err[iE+1][it+1]/mc_val[iE+1][it+1],2)+pow(thrown_err[iE+1][it+1]/thrown_val[iE+1][it+1],2));
		cout << "~~~~~~~Eff~" << iE << "~" << it << " " << eff_val[iE+1][it+1] << " " << eff_err[iE+1][it+1] << endl;
		Eff[iE+1]->SetBinContent(it+1,eff_val[iE+1][it+1]);
		Eff[iE+1]->SetBinError(it+1,eff_err[iE+1][it+1]);

		xsec_val[iE+1][it+1] = (sig_val[iE+1][it+1])/(constant * deltat * flux_val[iE+1] * mc_val[iE+1][it+1] /thrown_val[iE+1][it+1]);
		xsec_err[iE+1][it+1] = xsec_val[iE+1][it+1]*sqrt(pow(sig_err[iE+1][it+1]/sig_val[iE+1][it+1],2)+pow(flux_err[iE+1]/flux_val[iE+1],2)+pow(mc_err[iE+1][it+1]/mc_val[iE+1][it+1],2)+pow(thrown_err[iE+1][it+1]/thrown_val[iE+1][it+1],2));
		cout << "~~~~~~~xsec~" << iE << "~" << it << " " << xsec_val[iE+1][it+1] << " " << xsec_err[iE+1][it+1] << endl;
		XSec[iE+1]->SetBinContent(it+1,xsec_val[iE+1][it+1]);
		XSec[iE+1]->SetBinError(it+1,xsec_err[iE+1][it+1]);
	}
	sigyields_canvas->cd(iE+1);
	SignalYields[iE+1]->GetYaxis()->SetRangeUser(0,300);
	SignalYields[iE+1]->Draw("pe1");
	sprintf(signalyieldshist,"SignalYields_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(signatyieldsmacro,"SignalYields_%s_%03d_%02dbins.C",version,binning,numEBins);
	sigyields_canvas->Print(signalyieldshist);
	sigyields_canvas->SaveAs(signatyieldsmacro);

	sigmass_canvas->cd(iE+1);
	SignalMass[iE+1]->GetYaxis()->SetRangeUser(1.30,1.35);
	SignalMass[iE+1]->Draw("pe1");
	sprintf(signalmasshist,"SignalMass_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(signalmassmacro,"SignalMass_%s_%03d_%02dbins.C",version,binning,numEBins);
	sigmass_canvas->Print(signalmasshist);
	sigmass_canvas->SaveAs(signalmassmacro);

	sigwidth_canvas->cd(iE+1);
	SignalWidth[iE+1]->GetYaxis()->SetRangeUser(0.001,0.01);
	SignalWidth[iE+1]->Draw("pe1");
	sprintf(signalwidthhist,"SignalWidth_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(signalwidthmacro,"SignalWidth_%s_%03d_%02dbins.C",version,binning,numEBins);
	sigwidth_canvas->Print(signalwidthhist);
	sigwidth_canvas->SaveAs(signalwidthmacro);

	mcyields_canvas->cd(iE+1);
	MCYields[iE+1]->GetYaxis()->SetRangeUser(0,1750);
	MCYields[iE+1]->Draw("pe1");
	sprintf(mcyieldshist,"MCyields_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(mcyieldsmacro,"MCyields_%s_%03d_%02dbins.C",version,binning,numEBins);
	mcyields_canvas->Print(mcyieldshist);
	mcyields_canvas->SaveAs(mcyieldsmacro);

	mcmass_canvas->cd(iE+1);
	MCMass[iE+1]->GetYaxis()->SetRangeUser(1.30,1.35);
	MCMass[iE+1]->Draw("pe1");
	sprintf(mcmasshist,"MCMass_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(mcmassmacro,"MCMass_%s_%03d_%02dbins.C",version,binning,numEBins);
	mcmass_canvas->Print(mcmasshist);
	mcmass_canvas->SaveAs(mcmassmacro);

	mcwidth_canvas->cd(iE+1);
	MCWidth[iE+1]->GetYaxis()->SetRangeUser(0.001,0.01);
	MCWidth[iE+1]->Draw("pe1");
	sprintf(mcwidthhist,"MCwidth_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(mcwidthmacro,"MCwidth_%s_%03d_%02dbins.C",version,binning,numEBins);
	mcwidth_canvas->Print(mcwidthhist);
	mcwidth_canvas->SaveAs(mcwidthmacro);

	eff_canvas->cd(iE+1);
	Eff[iE+1]->GetYaxis()->SetRangeUser(0,0.25);
	Eff[iE+1]->Draw("pe1");
	sprintf(effhist,"Eff_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(effmacro,"Eff_%s_%03d_%02dbins.C",version,binning,numEBins);
	eff_canvas->Print(effhist);
	eff_canvas->SaveAs(effmacro);

	xsec_canvas->cd(iE+1);
	XSec[iE+1]->GetYaxis()->SetRangeUser(0,10);
	XSec[iE+1]->Draw("pe1");
	gPad->SetLogy();
	sprintf(diffxsechist,"Diffxsec_%s_%03d_%02dbins.png",version,binning,numEBins);
	sprintf(diffxsecmacro,"Diffxsec_%s_%03d_%02dbins.C",version,binning,numEBins);
	xsec_canvas->Print(diffxsechist);
	xsec_canvas->SaveAs(diffxsecmacro);
   }

for(int iEbin=0; iEbin<numEBins; iEbin++){
	cout << "Energy: " << deltaE * (iEbin) + (minEval) << " - " << deltaE * (iEbin+1) + (minEval) << endl; 
	for(int itbin=0; itbin<numtBins; itbin++){	
	cout << "     " << "-t: " << deltat * itbin + mintval << " - " << deltat * (itbin+1) + mintval << endl; 
	cout << "     " << "     " << "Signal Yields: " << sig_val[iEbin+1][itbin+1] << " +/- " << sig_err[iEbin+1][itbin+1] << endl;
	cout << "     " << "     " << "MC Yields: " << mc_val[iEbin+1][itbin+1] << " +/- " << mc_err[iEbin+1][itbin+1] << endl;
	cout << "     " << "     " << "Thrown Yields: " << thrown_val[iEbin+1][itbin+1] << " +/- " << thrown_err[iEbin+1][itbin+1] << endl;
	cout << "     " << "     " << "Flux Yields: " << flux_val[iEbin+1] << " +/- " << flux_err[iEbin+1] << endl;
	cout << "     " << "     " << "Efficiency: " << eff_val[iEbin+1][itbin+1] << " +/- " << eff_err[iEbin+1][itbin+1] << endl;
	cout << "     " << "     " << "XSec: " << xsec_val[iEbin+1][itbin+1] << " +/- " << xsec_err[iEbin+1][itbin+1] << endl;
	}
}

/*
//clas results, Goetz thesis Table D.1

TCanvas * axsec_canvas = new TCanvas("axsec_canvas", "axsec_canvas",800,600);
axsec_canvas->cd();
TPad *c1 = new TPad("pad1","pad1", 0.05, .05, .95, .95);
c1->Draw();
const Int_t nBins=10;
TH1F * xsec_gluex_count = new TH1F("xsec_gluex_count", "xsec_gluex_count",24,0.4,12.4);
TH1F * xsec_gluex = new TH1F("xsec_gluex", "xsec_gluex",24,0.4,12.4); 
xsec_gluex->SetMarkerColor(kRed);
xsec_gluex_count->SetMarkerColor(kBlue);
xsec_gluex->SetMarkerStyle(21);
xsec_gluex_count->SetMarkerStyle(21);
xsec_gluex->GetYaxis()->SetRangeUser(0,15);
xsec_gluex->GetYaxis()->SetTitle("#sigma_{total} (#gamma p -> K^{+}K^{+}#Xi^{-}) (nb)");
xsec_gluex->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
xsec_gluex->SetTitle("#Xi^{-} Cross Section");
for(int ith=13; ith<23; ith++)
{
	xsec_gluex_count->SetBinContent(ith,xsec_count_val[ith-13]);
	xsec_gluex_count->SetBinError(ith,xsec_count_err[ith-13]);
	xsec_gluex->SetBinContent(ith,xsec_val[ith-13]);
	xsec_gluex->SetBinError(ith,xsec_err[ith-13]);
}
//xsec_gluex->SetBinContent(14,4.48811);
//xsec_gluex->SetBinError(14,0.43384);
xsec_gluex->Draw("PE1");
//xsec_gluex_count->Draw("same");
axsec_canvas->Update();
const Int_t NumBins=24;
Double_t g12xsec[NumBins] =  {0.256, 1.145, 2.981, 4.927, 5.63, 7.296, 8.47, 8.872, 10.796, 11.017, 10.583, 10.132, 9.729, 11.614, 11.553, 10.133, 10.413, 11.179, 11.478, 8.48, 8.14, 10.004,9.855, 10.513};
Double_t g12xsec_err[NumBins] = {0.300, 0.300, 0.521, 0.408, 0.630, 0.881, 0.708, 0.616, 0.621, 0.677, 0.752, 0.797, 0.925, 0.918, 1.103, 1.091, 1.164, 1.068, 1.269, 1.299, 1.020, 1.761, 1.273, 4.630};
TH1F * xsec_clas = new TH1F("xsec_clas", "xsec_clas",NumBins,2.625,5.4); 
xsec_clas->SetMarkerColor(kOrange);
xsec_clas->SetMarkerStyle(21);
for(int jth=0; jth<NumBins; jth++)
{
	xsec_clas->SetBinContent(jth+1,g12xsec[jth]);
	xsec_clas->SetBinError(jth+1,g12xsec_err[jth]);
}
Double_t g12energy[NumBins] =  { };
Double_t deltaE[NumBins] = { };
xsec_clas->Draw("same,PE1");
auto legend = new TLegend(0.7,0.7,0.9,0.9);
legend->AddEntry(xsec_gluex,"GlueX");
//legend->AddEntry(xsec_gluex_count,"GlueX MC Counting");
legend->AddEntry(xsec_clas, "CLAS g12");
legend->Draw();
axsec_canvas->Update();
char xsec_wclas_macro_name[100];
sprintf(xsec_wclas_macro_name,"xsec_wclas_%s.C",version);
axsec_canvas->SaveAs(xsec_wclas_macro_name);
char xsec_wclas_plot_name[100];
sprintf(xsec_wclas_plot_name,"xsec_wclas_%s.png",version);
axsec_canvas->Print(xsec_wclas_plot_name);

*/
}
//xsec_gluex->SetName("Xi- Cross Section");
//axsec->SetTitle("#Xi^{-} Cross Section; E_{#gamma} (GeV); #sigma (nb)");
//axsec_canvas->Print("test_axsec.png");
//TCanvas * gxsec_canvas = new TCanvas("gxsec_canvas", "gxsec_canvas",800,600);
//TGraphErrors * axsec = new TGraphErrors(nBins, energy, xsec_val, denergy, xsec_err);
//Double_t energy[nBins]= {6.65,7.15, 7.65, 8.15, 8.65, 9.15, 9.65, 10.15, 10.65, 11.15};
//Double_t denergy[nBins]= {0.25, 0.25, 0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25};
