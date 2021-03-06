#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

//initialize all the things
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
char diffxsec_EBin_name[100];
char thrownyields_EBin_name[100];
char sigyields_EBin_name[100];
char esigfit_EBin_name[100];
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
double mintval = 0.0;
double maxtval = 5.0;
const int numtBins=1; 
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
double deltat;
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

void xsec_LE(TString dataFilePath, const char fluxFilePathtemp[100], TString mcFilePath, TString thrownFilePath,const char version[50], double minEval, const int numEBins)
{
//initialize things that depend on number of energy bins
	int binning = minEval*10;	
	double maxEval=6.0; 
	double_t flux_val[numEBins+1];
	double_t flux_err[numEBins+1];
	double_t xsec_sig_val[numEBins+1];
	double_t xsec_sig_err[numEBins+1];
	double_t xsec_mc_val[numEBins+1];
	double_t xsec_mc_err[numEBins+1];
	double_t xsec_thrown_val[numEBins+1];
	double_t xsec_thrown_err[numEBins+1];
	double_t xsec_eff_val[numEBins+1];
	double_t xsec_eff_err[numEBins+1];
	double_t xsec_val[numEBins+1];
	double_t xsec_err[numEBins+1];
	TH1F * SignalFits[numEBins+1];
	TH1F * SignalYields[numEBins+1];
	TH1F * SignalMass[numEBins+1];
	TH1F * SignalWidth[numEBins+1];    
	TH1F * MCMass[numEBins+1];
	TH1F * MCWidth[numEBins+1];
	TH1F * MCYields[numEBins+1];
	TH1F * Eff[numEBins+1];
	TH1F * ThrownYields[numEBins+1];
	TH1F * DiffXSec[numEBins+1];
	TH1F * SignalFits_Ebin;
	TH1F * SignalYields_Ebin;
	TH1F * SignalMass_Ebin;
	TH1F * SignalWidth_Ebin;    
	TH1F * MCMass_Ebin;
	TH1F * MCWidth_Ebin;
	TH1F * MCYields_Ebin;
	TH1F * Eff_Ebin;
	TH1F * ThrownYields_Ebin;
	TH1F * XSec_Ebin;
	gStyle->SetOptStat(0);
	deltat = (maxtval - mintval) / float(numtBins) ;
	deltaE = (maxEval - minEval) / float(numEBins) ;
	cout << "E: " << minEval << " - " << maxEval << " in " << numEBins << " bins with width " << deltaE  << endl;
	cout << "t: " << mintval << " - " << maxtval << " in " << numtBins << " bins with width " << deltat  << endl;

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
	ThrownYields_Ebin = new TH1F("ThrownYields_Ebin", ";E_{#gamma}; Thrown Yields (Events)",numEBins,minEval,maxEval);
	TCanvas * esigyields_canvas = new TCanvas("esigyields_canvas", "esigyields_canvas",800,600);
	SignalYields_Ebin = new TH1F("SignalYields_Ebin", ";E_{#gamma}; Signal Yields (Events)",numEBins,minEval,maxEval);
	TCanvas * esigmass_canvas = new TCanvas("esigmass_canvas", "esigmass_canvas",800,600);
	SignalMass_Ebin = new TH1F("SignalMass_Ebin", ";E_{#gamma}; Signal Mass (GeV)",numEBins,minEval,maxEval);
	TCanvas * esigwidth_canvas = new TCanvas("esigwidth_canvas", "esigwidth_canvas",800,600);
	SignalWidth_Ebin = new TH1F("SignalWidth_Ebin", ";E_{#gamma}; Signal Width (GeV)",numEBins,minEval,maxEval);
	TCanvas * emcyields_canvas = new TCanvas("emcyields_canvas", "emcyields_canvas",800,600);
	MCYields_Ebin = new TH1F("MCYields_Ebin", ";E_{#gamma}; MC Yields (Events)",numEBins,minEval,maxEval);
	TCanvas * emcmass_canvas = new TCanvas("emcmass_canvas", "emcmass_canvas",800,600);
	MCMass_Ebin = new TH1F("MCMass_Ebin", ";E_{#gamma}; MC Mass (GeV)",numEBins,minEval,maxEval);
	TCanvas * emcwidth_canvas = new TCanvas("emcwidth_canvas", "emcwidth_canvas",800,600);
	MCWidth_Ebin = new TH1F("MCWidth_Ebin", ";E_{#gamma}; MC Width (GeV)",numEBins,minEval,maxEval);
	TCanvas * ebineff_canvas = new TCanvas("ebineff_canvas", "ebineff_canvas",800,600);
	Eff_Ebin = new TH1F("Eff_Ebin", ";E_{#gamma}; Efficiency (%)",numEBins,minEval,maxEval);
	TCanvas * esigfit_canvas = new TCanvas("esigfit_canvas", "esigfit_canvas",800,600);
	TCanvas * xsec_canvas = new TCanvas("xsec_canvas", "xsec_canvas",800,600);
	XSec_Ebin = new TH1F("XSec_Ebin", "Cross Section;E_{#gamma}; #sigma_{total} (nb)",numEBins,minEval,maxEval);

//Output file names independent of energy bin and t bin
	sprintf(fluxmacro,"Xsec_pieces/Xsec_flux_numbers_%s_%03d_%02dbins.C",version,binning,numEBins);
	sprintf(fluxhist,"Xsec_pieces/Xsec_flux_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(ethrownmacro,"Xsec_pieces/Xsec_thrown_numbers_%s_%03d_%02dbins.C",version,binning, numEBins);
    sprintf(ethrownhist,"Xsec_pieces/Xsec_thrown_%s_%03d_%02dbins.png",version,binning, numEBins);
    sprintf(ethrownyieldshist,"Xsec_pieces/Xsec_ThrownYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(ethrownyieldsmacro,"Xsec_pieces/Xsec_ThrownYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalyieldshist,"Xsec_pieces/Xsec_SignalYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalyieldsmacro,"Xsec_pieces/Xsec_SignalYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalfithist,"Xsec_systematics/Xsec_SignalFits_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalfitmacro,"Xsec_systematics/Xsec_SignalFits_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalmasshist,"Xsec_systematics/Xsec_SignalMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalmassmacro,"Xsec_systematics/Xsec_SignalMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalwidthhist,"Xsec_systematics/Xsec_SignalWidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalwidthmacro,"Xsec_systematics/Xsec_SignalWidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcyieldshist,"Xsec_pieces/Xsec_MCyields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcyieldsmacro,"Xsec_pieces/Xsec_MCyields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcmasshist,"Xsec_systematics/Xsec_MCMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcmassmacro,"Xsec_systematics/Xsec_MCMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcwidthhist,"Xsec_systematics/Xsec_MCwidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcwidthmacro,"Xsec_systematics/Xsec_MCwidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(ebineffhist,"Xsec_pieces/Xsec_Eff_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(ebineffmacro,"Xsec_pieces/Xsec_Eff_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(xsechist,"Xsec_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(xsecmacro,"Xsec_%s_%03d_%02dbins.C",version,binning,numEBins);

//Create and save flux histogram
	flux_canvas->cd();
	TH1F *  FluxH= (TH1F *) fluxfile->Get("tagged_flux");
	FluxH->Rebin(deltaE/FluxH->GetBinWidth(1));
	FluxH->Draw(); 
	flux_canvas->SaveAs(fluxmacro);
	flux_canvas->Print(fluxhist);

//Create and save thrown histograms for diff xsec and total xsec
	thrown_canvas->cd();
	thrownfile->cd(); 
	sprintf(thrownhistname,"Egamma_t");
	TH2F*  ThrownH= (TH2F*) thrownfile->Get(thrownhistname);
	ThrownH->RebinX(deltaE/ThrownH->GetXaxis()->GetBinWidth(1));    
	ThrownH->RebinY(deltat/ThrownH->GetYaxis()->GetBinWidth(1));
	ThrownH->Draw("colz");
	thrown_canvas->SaveAs(thrownmacro);
	thrown_canvas->Print(thrownhist);
	ethrown_canvas->cd();
	TH1F * ThrownH_Ebin = (TH1F *) ThrownH->ProjectionX("ThrownH_Ebin",1,ThrownH->GetYaxis()->FindBin(maxtval)-1);
	ThrownH_Ebin->Draw();
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
	for(int padnumber=1; padnumber<numEBins+1; padnumber++){
		sprintf(pad,"diffxsec_pad_%02d",padnumber);
		TPad * pad = (TPad *) diffxsec_canvas->cd(padnumber);
		pad->SetLogy();	
	}

//Perform accidental subtraction for signal histogram
	sprintf(XiMasshistname,"Xi_Egamma_t");	
	sprintf(XiMasshistnameacc,"Xi_Egamma_t_acc");	
	TH3F * XiMassKinFit_Egamma_t = (TH3F*)datafile->Get(XiMasshistname);
	TH3F * XiMassKinFit_Egamma_t_acc = (TH3F*)datafile->Get(XiMasshistnameacc);
	TH3F * XiMassKinFit_Egamma_t_accsub = (TH3F *) XiMassKinFit_Egamma_t->Clone("XiMassKinFit_Egamma_t_accsub");
	XiMassKinFit_Egamma_t_accsub->Add(XiMassKinFit_Egamma_t_acc,-0.5);

//Perform accidental subtraction for mc histogram
	sprintf(MCXiMasshistname,"Xi_Egamma_t");	
	sprintf(MCXiMasshistnameacc,"Xi_Egamma_t_acc");	
	TH3F * MC_XiMassKinFit_Egamma_t = (TH3F*)mcfile->Get(MCXiMasshistname);
	TH3F * MC_XiMassKinFit_Egamma_t_acc = (TH3F*)mcfile->Get(MCXiMasshistnameacc);
	TH3F * MC_XiMassKinFit_Egamma_t_accsub = (TH3F *) MC_XiMassKinFit_Egamma_t->Clone("MC_XiMassKinFit_Egamma_t_accsub");
	MC_XiMassKinFit_Egamma_t_accsub->Add(MC_XiMassKinFit_Egamma_t_acc,-0.5);

//Main beam energy loop
	for(int iE=0; iE<numEBins; iE++){
		double Emin = deltaE * iE + (minEval);
		double Emax = deltaE * (iE+1) + (minEval);
		int Ebuffer = Emin*10;

	//Initialize histograms on the divided canvases
		esigfit_canvas->cd(iE+1);	
		sprintf(esigfit_EBin_name,"sigfit_%03d",Ebuffer);
		sprintf(EBin_Title,"%3.1f <= E_{#gamma} < %3.1f",Emin,Emax);

		thrownyields_canvas->cd(iE+1);
		sprintf(thrownyields_EBin_name,"thrownyields_%03d",Ebuffer);
		ThrownYields[iE+1] = new TH1F(thrownyields_EBin_name, "; -t (GeV^2); Thrown Yields",numtBins,mintval,maxtval); 
		ThrownYields[iE+1]->SetTitle(EBin_Title);
		ThrownYields[iE+1]->SetMarkerColor(kRed);
		ThrownYields[iE+1]->SetMarkerStyle(21);
		ThrownYields[iE+1]->SetLabelSize(0.035,"xy");
		ThrownYields[iE+1]->SetLabelOffset(0.001,"xy");

		sigyields_canvas->cd(iE+1);	
		sprintf(sigyields_EBin_name,"sigyields_%03d",Ebuffer);
		SignalYields[iE+1] = new TH1F(sigyields_EBin_name, "; -t (GeV^2); Yields",numtBins,mintval,maxtval); 
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

		diffxsec_canvas->cd(iE+1);
		sprintf(diffxsec_EBin_name,"diffxsec_%03d",Ebuffer);
		DiffXSec[iE+1] = new TH1F(diffxsec_EBin_name, "; -t (GeV^2); d#sigma/dt (nb)",numtBins,mintval,maxtval); 
		DiffXSec[iE+1]->SetTitle(EBin_Title);
		DiffXSec[iE+1]->SetMarkerColor(kRed);
		DiffXSec[iE+1]->SetMarkerStyle(21);
		DiffXSec[iE+1]->SetLabelSize(0.035,"xy");
		DiffXSec[iE+1]->SetLabelOffset(0.001,"xy");

	//Get thrown values for total cross section
		ethrownyields_canvas->cd(iE+1);
		double thrown_Ebin = ThrownH_Ebin->GetBinContent(iE+1);
		double thrown_Ebin_err = ThrownH_Ebin->GetBinError(iE+1);
		xsec_thrown_val[iE+1] = thrown_Ebin;
		xsec_thrown_err[iE+1] = thrown_Ebin_err;
		ThrownYields_Ebin->SetBinContent(iE+1,thrown_Ebin);
		ThrownYields_Ebin->SetBinError(iE+1,thrown_Ebin_err);
		cout << "~~~~~~~Thrownxsec~ " << iE << "~ " << thrown_Ebin << " " << thrown_Ebin_err << endl;

	//Create a histogram of signal for this particular energy bin
		int Ebinmin = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
		int Ebinmax = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
		int MC_Ebinmin = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
		int MC_Ebinmax = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
		XiMassKinFit_Egamma_t_accsub->GetZaxis()->SetRange(1,XiMassKinFit_Egamma_t_accsub->GetZaxis()->FindBin(maxtval)-1);	
		XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
		TH1F * XiMassKinFit_Ebin_accsub = (TH1F *) XiMassKinFit_Egamma_t_accsub->Project3D("x");
		XiMassKinFit_Ebin_accsub->Rebin(XiMassKinFit_Ebin_accsub->GetNbinsX()/nummassBins);

	//Create a histogram of mc for this particular energy bin	
		MC_XiMassKinFit_Egamma_t_accsub->GetZaxis()->SetRange(1,MC_XiMassKinFit_Egamma_t_accsub->GetZaxis()->FindBin(maxtval)-1);	
		MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
		TH1F * MC_XiMassKinFit_Ebin_accsub = (TH1F *) MC_XiMassKinFit_Egamma_t_accsub->Project3D("x");

	//Only perform signal fit for total cross section if there are at least 20 entries in the whole histogram
		if(XiMassKinFit_Ebin_accsub->GetEntries() < 20){
			xsec_sig_events = 0.0;
			xsec_sig_events_err = 0.0;
			xsec_sig_mass = 0.0;
			xsec_sig_mass_err = 0.0;
			xsec_sig_width =  0.0;
			xsec_sig_width_err =  0.0;
		} //end not enough signal loop for total cross section
		else{	//Set up and perform signal fit for total cross section
			sprintf(xsec_xiplot,"Xsec_fits/Xsec_sigfit_%s_%03d_%02dbins_%03d.png",version, binning,numEBins,Ebuffer);
			sprintf(xsec_workspace,"w%03d",Ebuffer);
			sprintf(xsec_xicanvas,"Xi_canvas_%03d",Ebuffer);
			TCanvas * Xsec_Xi_canvas = new TCanvas(xsec_xicanvas, xsec_xicanvas,800,600);
			RooWorkspace* xsecw = new RooWorkspace(xsec_workspace);
			RooRealVar xsecmass("xsecmass", "xsecmass", minmass, maxmass);
			RooDataHist *xsecdata = new RooDataHist("xsecdata", "Dataset of mass", xsecmass, XiMassKinFit_Ebin_accsub);
			XiMassKinFit_Ebin_accsub->Print();
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
			esigfit_canvas->cd(iE+1);
			xsecmassframe->Draw();
		} //end enough signal loop for total cross section
	//Save signal fit yields and error for total cross section
		xsec_sig_val[iE+1] = xsec_sig_events;
		xsec_sig_err[iE+1] = xsec_sig_events_err;
		cout << "~~~~~~~sigxsec~" << iE << "~ " << xsec_sig_events << " " << xsec_sig_events_err << endl; 
		esigyields_canvas->cd();	
		SignalYields_Ebin->SetBinContent(iE+1,xsec_sig_events);
		SignalYields_Ebin->SetBinError(iE+1,xsec_sig_events_err);
		esigmass_canvas->cd();
		SignalMass_Ebin->SetBinContent(iE+1,xsec_sig_mass); 
		SignalMass_Ebin->SetBinError(iE+1,xsec_sig_mass_err);
		esigwidth_canvas->cd();
		SignalWidth_Ebin->SetBinContent(iE+1,xsec_sig_width);
		SignalWidth_Ebin->SetBinError(iE+1,xsec_sig_width_err);

	//MC fit for total cross section 
		sprintf(xsec_mcplot,"Xsec_fits/Xsec_mcfit_%s_%03d_%02dbins_%03d.png",version, binning,numEBins,Ebuffer);	
		sprintf(mc_xsec_workspace,"wmc%03d",Ebuffer);
		sprintf(xsec_mccanvas,"Xi_canvas_mc_%03d",Ebuffer);
		TCanvas * Xsec_Xi_mc_canvas = new TCanvas(xsec_mccanvas, xsec_mccanvas,800,600);
		RooWorkspace* xsecwmc = new RooWorkspace(mc_xsec_workspace);
		RooRealVar xsecmcmass("xsecmcmass", "xsecmcmass", minmass, maxmass);
		RooDataHist *xsecmc = new RooDataHist("xsecmc", "MC of mass", xsecmcmass, MC_XiMassKinFit_Ebin_accsub );
		MC_XiMassKinFit_Ebin_accsub->Print();
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
		xsec_mc_val[iE+1] = xsec_mc_sig_events;
		xsec_mc_err[iE+1] = xsec_mc_sig_events_err;
		cout << "~~~~~~~MCxsec~" << iE << "~ " << xsec_mc_sig_events << " " << xsec_mc_sig_events_err << endl; 
		double xsec_mc_max_y = xsec_mc_sig_events *0.5;
		xsecmcmassframe->SetMaximum(xsec_mc_max_y);
		xsecmcmassframe->Draw();
		Xsec_Xi_mc_canvas->Print(xsec_mcplot);

	// Save MC information to histograms binned in beam energy
		emcyields_canvas->cd();	
		MCYields_Ebin->SetBinContent(iE+1,xsec_mc_sig_events);
		MCYields_Ebin->SetBinError(iE+1,xsec_mc_sig_events_err);
		emcmass_canvas->cd();
		MCMass_Ebin->SetBinContent(iE+1,xsec_mc_mass); 
		MCMass_Ebin->SetBinError(iE+1,xsec_mc_mass_err);
		emcwidth_canvas->cd();
		MCWidth_Ebin->SetBinContent(iE+1,xsec_mc_width);
		MCWidth_Ebin->SetBinError(iE+1,xsec_mc_width_err);

	//Get flux values
		flux_val[iE+1]=getbincontent(FluxH,iE+1);
		flux_err[iE+1]=getbinerror(FluxH,iE+1); //+1 because 0 is the underflow
		cout << "~~~~~~~flux~" << iE << "~" << flux_val[iE+1] << " " << flux_err[iE+1] << endl;

	//Calculate efficiencies and total cross section in terms of only energy binning
		xsec_eff_val[iE+1] = xsec_mc_val[iE+1]/xsec_thrown_val[iE+1];
		xsec_eff_err[iE+1] = xsec_eff_val[iE+1] * sqrt(pow(xsec_mc_err[iE+1]/xsec_mc_val[iE+1],2)+pow(xsec_thrown_err[iE+1]/xsec_thrown_val[iE+1],2));
		cout << "~~~~~~~Effxsec~" << iE << "~" << xsec_eff_val[iE+1] << " " << xsec_eff_err[iE+1] << endl;
		Eff_Ebin->SetBinContent(iE+1,xsec_eff_val[iE+1]);
		Eff_Ebin->SetBinError(iE+1,xsec_eff_err[iE+1]);
		xsec_val[iE+1] = (xsec_sig_val[iE+1])/(constant * flux_val[iE+1] * xsec_mc_val[iE+1]/xsec_thrown_val[iE+1]);
		if(xsec_sig_val[iE+1] != 0){ //Calculate normally
		    xsec_err[iE+1] = xsec_val[iE+1]*sqrt(pow(xsec_sig_err[iE+1]/xsec_sig_val[iE+1],2)+pow(flux_err[iE+1]/flux_val[iE+1],2)+pow(xsec_mc_err[iE+1]/xsec_mc_val[iE+1],2)+pow(xsec_thrown_err[iE+1]/xsec_thrown_val[iE+1],2));
		}
		else{ 
			xsec_err[iE+1] = 0.0; // Set to zero if fit wasn't performed to prevent NaNs.
		}	
		cout << "~~~~~~~Xsec~" << iE << "~" << xsec_val[iE+1] << " " << xsec_err[iE+1] << endl;
		XSec_Ebin->SetBinContent(iE+1,xsec_val[iE+1]);
		XSec_Ebin->SetBinError(iE+1,xsec_err[iE+1]);

	//Draw and save histograms that depend on energy bin
		esigfit_canvas->cd(iE+1);
		esigfit_canvas->Print(esignalfithist);
		esigfit_canvas->SaveAs(esignalfitmacro);

		thrownyields_canvas->cd(iE+1);
		ThrownYields[iE+1]->Draw("pe1");
		thrownyields_canvas->Print(thrownyieldshist);
		thrownyields_canvas->SaveAs(thrownyieldsmacro);

		sigyields_canvas->cd(iE+1);
		SignalYields[iE+1]->GetYaxis()->SetRangeUser(0,300);
		SignalYields[iE+1]->Draw("pe1");
		sigyields_canvas->Print(signalyieldshist);
		sigyields_canvas->SaveAs(signalyieldsmacro);

		sigmass_canvas->cd(iE+1);
		SignalMass[iE+1]->GetYaxis()->SetRangeUser(1.30,1.35);
		SignalMass[iE+1]->Draw("pe1");
		sigmass_canvas->Print(signalmasshist);
		sigmass_canvas->SaveAs(signalmassmacro);

		sigwidth_canvas->cd(iE+1);
		SignalWidth[iE+1]->GetYaxis()->SetRangeUser(0.001,0.01);
		SignalWidth[iE+1]->Draw("pe1");
		sigwidth_canvas->Print(signalwidthhist);
		sigwidth_canvas->SaveAs(signalwidthmacro);

		mcyields_canvas->cd(iE+1);
		MCYields[iE+1]->GetYaxis()->SetRangeUser(0,1750);
		MCYields[iE+1]->Draw("pe1");
		mcyields_canvas->Print(mcyieldshist);
		mcyields_canvas->SaveAs(mcyieldsmacro);

		mcmass_canvas->cd(iE+1);
		MCMass[iE+1]->GetYaxis()->SetRangeUser(1.30,1.35);
		MCMass[iE+1]->Draw("pe1");
		mcmass_canvas->Print(mcmasshist);
		mcmass_canvas->SaveAs(mcmassmacro);

		mcwidth_canvas->cd(iE+1);
		MCWidth[iE+1]->GetYaxis()->SetRangeUser(0.001,0.01);
		MCWidth[iE+1]->Draw("pe1");
		mcwidth_canvas->Print(mcwidthhist);
		mcwidth_canvas->SaveAs(mcwidthmacro);

		eff_canvas->cd(iE+1);
		Eff[iE+1]->GetYaxis()->SetRangeUser(0,0.25);
		Eff[iE+1]->Draw("pe1");
		eff_canvas->Print(effhist);
		eff_canvas->SaveAs(effmacro);

		diffxsec_canvas->cd(iE+1);
		DiffXSec[iE+1]->GetYaxis()->SetRangeUser(0.0001,10);
		DiffXSec[iE+1]->Draw("pe1");
		diffxsec_canvas->Print(diffxsechist);
		diffxsec_canvas->SaveAs(diffxsecmacro);
	} //end E loop

//Save all the total cross section histograms
	ethrownyields_canvas->cd();
	ThrownYields_Ebin->Draw("pe1");
	ethrownyields_canvas->Print(ethrownyieldshist);
	ethrownyields_canvas->SaveAs(ethrownyieldsmacro);

	esigyields_canvas->cd();
	SignalYields_Ebin->Draw("pe1");
	esigyields_canvas->Print(esignalyieldshist);
	esigyields_canvas->SaveAs(esignalyieldsmacro);

	emcyields_canvas->cd();
	MCYields_Ebin->Draw("pe1");
	emcyields_canvas->Print(emcyieldshist);
	emcyields_canvas->SaveAs(emcyieldsmacro);

	esigmass_canvas->cd();
	SignalMass_Ebin->Draw("pe1");
	esigmass_canvas->Print(esignalmasshist);
	esigmass_canvas->SaveAs(esignalmassmacro);

	emcmass_canvas->cd();
	MCMass_Ebin->Draw("pe1");
	emcmass_canvas->Print(emcmasshist);
	emcmass_canvas->SaveAs(emcmassmacro);

	esigwidth_canvas->cd();
	SignalWidth_Ebin->Draw("pe1");
	esigwidth_canvas->Print(esignalwidthhist);
	esigwidth_canvas->SaveAs(esignalwidthmacro);

	emcwidth_canvas->cd();
	MCWidth_Ebin->Draw("pe1");
	emcwidth_canvas->Print(emcwidthhist);
	emcwidth_canvas->SaveAs(emcwidthmacro);

	ebineff_canvas->cd();
	Eff_Ebin->Draw("pe1");
	ebineff_canvas->Print(ebineffhist);
	ebineff_canvas->SaveAs(ebineffmacro);

	xsec_canvas->cd();
	XSec_Ebin->GetXaxis()->SetRangeUser(0,12.5);
	XSec_Ebin->GetYaxis()->SetRangeUser(0,15);
	XSec_Ebin->SetMarkerStyle(21);
	if(std::strstr(version,"2017_01") != NULL){ XSec_Ebin->SetMarkerColor(kGreen);} 
	if(std::strstr(version,"2018_01") != NULL){ XSec_Ebin->SetMarkerColor(kRed);} 
	if(std::strstr(version,"2018_08") != NULL){ XSec_Ebin->SetMarkerColor(kBlue);} 
	XSec_Ebin->Draw("pe1");
	xsec_canvas->Print(xsechist);
	xsec_canvas->SaveAs(xsecmacro);

//Print out all values at end of running
for(int iEbin=0; iEbin<numEBins; iEbin++){
	cout << "Energy: " << deltaE * (iEbin) + (minEval) << " - " << deltaE * (iEbin+1) + (minEval) << endl; 
	cout << "\t" << "-t:  " 		<< mintval << " - " << maxtval << endl; 
	cout << "\t" << "Signal Yields: " 	<< xsec_sig_val[iEbin+1] 	<< " +/- " 	<< xsec_sig_err[iEbin+1] 	<< endl;
	cout << "\t" << "MC Yields: " 		<< xsec_mc_val[iEbin+1] 	<< " +/- " 	<< xsec_mc_err[iEbin+1] 	<< endl;
	cout << "\t" << "Thrown Yields: " 	<< xsec_thrown_val[iEbin+1] 	<< " +/- " 	<< xsec_thrown_err[iEbin+1] 	<< endl;
	cout << "\t" << "Flux Yields: " 	<< flux_val[iEbin+1] 		<< " +/- " 	<< flux_err[iEbin+1] 		<< endl;
	cout << "\t" << "Efficiency: " 		<< xsec_eff_val[iEbin+1] 	<< " +/- " 	<< xsec_eff_err[iEbin+1] 	<< endl;
	cout << "\t" << "XSec: " 		<< xsec_val[iEbin+1] 		<< " +/- " 	<< xsec_err[iEbin+1] 		<< endl;
} //end print E loop

cout << "Table for LaTex: " << endl;
cout << "Energy Bin (GeV) & Signal Yield & MC Yield & Thrown Yield & Efficiency*BR  \\\\ " << endl;
for(int iTable=0; iTable<numEBins; iTable++){
	cout <<  setprecision(3) << deltaE * (iTable) + (minEval) << " - " << deltaE * (iTable+1) + (minEval) << " &$ " << (int)round(xsec_sig_val[iTable+1]) << " \\pm " << (int)round(xsec_sig_err[iTable+1]) << " $&$ " << (int)round(xsec_mc_val[iTable+1]) << " \\pm " << (int)round(xsec_mc_err[iTable+1]) << " $&$ " << setprecision(6) << xsec_thrown_val[iTable+1] << " \\pm " << setprecision(3) << (int)round(xsec_thrown_err[iTable+1]) << " $&$ " << setprecision(3) << 100.*xsec_eff_val[iTable+1] << " \\pm " << setprecision(2) << 100.*xsec_eff_err[iTable+1] << " $\\\\ " << endl;
} //end Table construction
return;	

} //end macro