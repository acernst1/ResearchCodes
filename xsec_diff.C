#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

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
const int numtBins=10; 
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

void xsec_diff(TString dataFilePath, const char fluxFilePathtemp[100], TString mcFilePath, TString thrownFilePath,const char version[17], double minEval, const int numEBins)
{
//initialize things that depend on number of energy bins
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
    double_t eff_val[numEBins+1][numtBins+1];
    double_t eff_err[numEBins+1][numtBins+1];
    double_t diffxsec_val[numEBins+1][numtBins+1];
    double_t diffxsec_err[numEBins+1][numtBins+1];
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

//open the necessary files
    sprintf(fluxFilePath,"%s_%03d.root",fluxFilePathtemp,binning);		
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
    TH1F * ThrownYields_Ebin = new TH1F("ThrownYields_Ebin", ";E_{#gamma}; Thrown Yields (Events)",numEBins,minEval,maxEval);
    TCanvas * esigyields_canvas = new TCanvas("esigyields_canvas", "esigyields_canvas",800,600);
    TH1F * SignalYields_Ebin = new TH1F("SignalYields_Ebin", ";E_{#gamma}; Signal Yields (Events)",numEBins,minEval,maxEval);
    TCanvas * esigmass_canvas = new TCanvas("esigmass_canvas", "esigmass_canvas",800,600);
    TH1F * SignalMass_Ebin = new TH1F("SignalMass_Ebin", ";E_{#gamma}; Signal Mass (GeV)",numEBins,minEval,maxEval);
    TCanvas * esigwidth_canvas = new TCanvas("esigwidth_canvas", "esigwidth_canvas",800,600);
    TH1F * SignalWidth_Ebin = new TH1F("SignalWidth_Ebin", ";E_{#gamma}; Signal Width (GeV)",numEBins,minEval,maxEval);
    TCanvas * emcyields_canvas = new TCanvas("emcyields_canvas", "emcyields_canvas",800,600);
    TH1F * MCYields_Ebin = new TH1F("MCYields_Ebin", ";E_{#gamma}; MC Yields (Events)",numEBins,minEval,maxEval);
    TCanvas * emcmass_canvas = new TCanvas("emcmass_canvas", "emcmass_canvas",800,600);
    TH1F * MCMass_Ebin = new TH1F("MCMass_Ebin", ";E_{#gamma}; MC Mass (GeV)",numEBins,minEval,maxEval);
    TCanvas * emcwidth_canvas = new TCanvas("emcwidth_canvas", "emcwidth_canvas",800,600);
    TH1F * MCWidth_Ebin = new TH1F("MCWidth_Ebin", ";E_{#gamma}; MC Width (GeV)",numEBins,minEval,maxEval);
    TCanvas * ebineff_canvas = new TCanvas("ebineff_canvas", "ebineff_canvas",800,600);
    TH1F * Eff_Ebin = new TH1F("Eff_Ebin", ";E_{#gamma}; Efficiency (%)",numEBins,minEval,maxEval);
    TCanvas * esigfit_canvas = new TCanvas("esigfit_canvas", "esigfit_canvas",800,600);
    TCanvas * xsec_canvas = new TCanvas("xsec_canvas", "xsec_canvas",800,600);
    TH1F * XSec_Ebin = new TH1F("XSec_Ebin", "Cross Section;E_{#gamma}; #sigma_{total} (nb)",numEBins,minEval,maxEval);
    
//Output file names independent of energy bin and t bin
    sprintf(fluxmacro,"Xsec_flux_numbers_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(fluxhist,"Xsec_flux_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(thrownmacro,"Diffxsec_thrown_numbers_%s_%03d_%02dbins.C",version,binning, numEBins);
    sprintf(thrownhist,"Diffxsec_thrown_%s_%03d_%02dbins.png",version,binning, numEBins);
    sprintf(thrownyieldshist,"Diffxsec_ThrownYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(thrownyieldsmacro,"Diffxsec_ThrownYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(signalyieldshist,"Diffxsec_SignalYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(signalyieldsmacro,"Diffxsec_SignalYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(signalmasshist,"Diffxsec_SignalMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(signalmassmacro,"Diffxsec_SignalMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(signalwidthhist,"Diffxsec_SignalWidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(signalwidthmacro,"Diffxsec_SignalWidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(mcyieldshist,"Diffxsec_MCyields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(mcyieldsmacro,"Diffxsec_MCyields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(mcmasshist,"Diffxsec_MCMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(mcmassmacro,"Diffxsec_MCMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(mcwidthhist,"Diffxsec_MCwidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(mcwidthmacro,"Diffxsec_MCwidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(effhist,"Diffxsec_Eff_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(effmacro,"Diffxsec_Eff_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(diffxsechist,"Diffxsec_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(diffxsecmacro,"Diffxsec_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(ethrownmacro,"Xsec_thrown_numbers_%s_%03d_%02dbins.C",version,binning, numEBins);
    sprintf(ethrownhist,"Xsec_thrown_%s_%03d_%02dbins.png",version,binning, numEBins);
    sprintf(ethrownyieldshist,"Xsec_ThrownYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(ethrownyieldsmacro,"Xsec_ThrownYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalyieldshist,"Xsec_SignalYields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalyieldsmacro,"Xsec_SignalYields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalfithist,"Xsec_SignalFits_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalfitmacro,"Xsec_SignalFits_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalmasshist,"Xsec_SignalMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalmassmacro,"Xsec_SignalMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(esignalwidthhist,"Xsec_SignalWidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(esignalwidthmacro,"Xsec_SignalWidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcyieldshist,"Xsec_MCyields_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcyieldsmacro,"Xsec_MCyields_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcmasshist,"Xsec_MCMass_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcmassmacro,"Xsec_MCMass_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(emcwidthhist,"Xsec_MCwidth_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(emcwidthmacro,"Xsec_MCwidth_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(ebineffhist,"Xsec_Eff_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(ebineffmacro,"Xsec_Eff_%s_%03d_%02dbins.C",version,binning,numEBins);
    sprintf(xsechist,"Xsec_%s_%03d_%02dbins.png",version,binning,numEBins);
    sprintf(xsecmacro,"Xsec_%s_%03d_%02dbins.C",version,binning,numEBins);

//Create and save flux histogram
    flux_canvas->cd();
    TH1F *  FluxH= (TH1F *) fluxfile->Get("tagged_flux");
    FluxH->Rebin(deltaE/FluxH->GetBinWidth(1));
    FluxH->Draw(); 
    FluxH->SaveAs(fluxmacro);
    flux_canvas->Print(fluxhist);

//Create and save thrown histograms for diff xsec and total xsec
    thrown_canvas->cd();
    thrownfile->cd(); 
    sprintf(thrownhistname,"Egamma_t_%03d",binning);
    TH2F*  ThrownH= (TH2F*) thrownfile->Get(thrownhistname);
    ThrownH->RebinX(deltaE/ThrownH->GetXaxis()->GetBinWidth(1));    
    ThrownH->RebinY(deltat/ThrownH->GetYaxis()->GetBinWidth(1));
    ThrownH->Draw("colz");
    ThrownH->SaveAs(thrownmacro);
    thrown_canvas->Print(thrownhist);
    ethrown_canvas->cd()
    TH1F * ThrownH_Ebin = (TH1F *) ThrownH->ProjectionX("ThrownH_Ebin",1,ThrownH->GetYaxis()->FindBin(maxtval)-1);
    ThrownH_Ebin->Draw();
    ThrownH_Ebin->SaveAs(ethrownmacro);
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
   sprintf(XiMasshistname,"Xi_Egamma_t_%03d",binning);	
   sprintf(XiMasshistnameacc,"Xi_Egamma_t_%03d_acc",binning);	
   TH3F * XiMassKinFit_Egamma_t = (TH3F*)datafile->Get(XiMasshistname);
   TH3F * XiMassKinFit_Egamma_t_acc = (TH3F*)datafile->Get(XiMasshistnameacc);
   TH3F * XiMassKinFit_Egamma_t_accsub = (TH3F *) XiMassKinFit_Egamma_t->Clone("XiMassKinFit_Egamma_t_accsub");
   XiMassKinFit_Egamma_t_accsub->Add(XiMassKinFit_Egamma_t_acc,-0.5);

//Perform accidental subtraction for mc histogram
   TH3F * MC_XiMassKinFit_Egamma_t = (TH3F*)mcfile->Get(XiMasshistname);
   TH3F * MC_XiMassKinFit_Egamma_t_acc = (TH3F*)mcfile->Get(XiMasshistnameacc);
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
	SignalFits[iE+1]->SetTitle(EBin_Title);

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

    //Create a histogram of signal vs t for this particular energy bin	
	int Ebinmin = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
	int Ebinmax = XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
	XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(Ebinmin,Ebinmax);
	TH2F * XiMassKinFit_Ebin_t_accsub = (TH2F *) XiMassKinFit_Egamma_t_accsub->Project3D("xz");

    //Create a histogram of mc vs t for this particular energy bin	
	int MC_Ebinmin = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
	int MC_Ebinmax = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
	MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(MC_Ebinmin,MC_Ebinmax);
	TH2F * MC_XiMassKinFit_Ebin_t_accsub = (TH2F *) MC_XiMassKinFit_Egamma_t_accsub->Project3D("xz");

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
	else{    //Set up and perform signal fit for total cross section
		sprintf(xsec_xiplot,"Xsec_sigfit_%s_%03d_%02dbins_%03d.png",version, binning,numEBins,Ebuffer);
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
        	xsecw->factory("SUM::xsecmodel(nbkgd[150,0,1e5]*bkgd, nsig[20,0,1e3]*xsecgaus)");
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

    //MC fit for total cross section 
	sprintf(xsec_mcplot,"Xsec_mcfit_%s_%03d_%02dbins_%03d.png",version, binning,numEBins,Ebuffer);	
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

    //Main t loop
	for(int it =0; it<numtBins; it++){
	//Initialize other things
		double tmin = deltat * it + mintval;
		double tmax = deltat * (it+1) +mintval;
		int tbuffer = tmin*10;
		sprintf(workspace,"w%03d_%03d",Ebuffer,tbuffer);
		sprintf(mcworkspace,"wmc%03d_%03d",Ebuffer,tbuffer);
	//Initialize t dependent TCanvas
        	sprintf(xicanvas,"Xi_canvas_%03d_%03d",Ebuffer,tbuffer);
		sprintf(mccanvas,"Xi_canvas_mc_%03d_%03d",Ebuffer,tbuffer);
       		TCanvas * Xi_canvas = new TCanvas(xicanvas, xicanvas,800,600);
        	TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
	
	//t dependent output file names
		sprintf(diffxsec_xiplot,"Diffxsec_sigfit_%s_%03d_%02dbins_%03d_%03d.png",version, binning,numEBins,Ebuffer,tbuffer);
		sprintf(diffxsec_mcplot,"Diffxsec_mcfit_%s_%03d_%02dbins_%03d_%03d.png",version, binning,numEBins,Ebuffer,tbuffer);

	//Preparing signal for fit, projecting within t range
		int tbinmin = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int tbinmax = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(tbinmin,tbinmax);
		TH1F * XiMassKinFit_Ebin_tbin_accsub = (TH1F *) XiMassKinFit_Ebin_t_accsub->ProjectionY("XiMassKinFit_Ebin_tbin_accsub",tbinmin,tbinmax);
		XiMassKinFit_Ebin_tbin_accsub->Rebin(XiMassKinFit_Ebin_tbin_accsub->GetNbinsX()/nummassBins);

	//Preparing mc for fit, projecting within t range
		int MC_tbinmin = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int MC_tbinmax = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(MC_tbinmin,MC_tbinmax);
		TH1F * MC_XiMassKinFit_Ebin_tbin_accsub = (TH1F *) MC_XiMassKinFit_Ebin_t_accsub->ProjectionY("MC_XiMassKinFit_Ebin_tbin_accsub",MC_tbinmin,MC_tbinmax); 
		MC_XiMassKinFit_Ebin_tbin_accsub->Rebin(MC_XiMassKinFit_Ebin_tbin_accsub->GetNbinsX()/nummassBins);

	//Only perform signal fit if there are at least 20 entries in the whole histogram
		if(XiMassKinFit_Ebin_tbin_accsub->GetEntries() < 20){
			sig_events = 0.0;
			sig_events_err = 0.0;
			sig_mass = 0.0;
			sig_mass_err = 0.0;
			sig_width =  0.0;
			sig_width_err =  0.0;
		} //end not enough signal loop
		else{
	//Set up and perform signal fit	
			Xi_canvas->cd();
			RooWorkspace* w = new RooWorkspace(workspace);
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
			double max_y = sig_events*0.3;
			massframe->SetMaximum(max_y);
        		massframe->Draw();
	     		Xi_canvas->Print(diffxsec_xiplot);
		} //end enough signal loop

	//Add signal value and error to to an array
		sig_val[iE+1][it+1] = sig_events;
		sig_err[iE+1][it+1] = sig_events_err;
		cout << "~~~~~~~sig~" << iE << "~" << it << " " << sig_events << " " << sig_events_err << endl; 

	//Set up and perform mc fit
		Xi_mc_canvas->cd();
       		RooWorkspace* wmc = new RooWorkspace(mcworkspace);
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
	     	Xi_mc_canvas->Print(diffxsec_mcplot);

	//Add signal yield and errors to stability check histograms
		SignalYields[iE+1]->SetBinContent(it+1,sig_events);
		SignalYields[iE+1]->SetBinError(it+1,sig_events_err);
		SignalMass[iE+1]->SetBinContent(it+1,sig_mass);
		SignalMass[iE+1]->SetBinError(it+1,sig_mass_err);
		SignalWidth[iE+1]->SetBinContent(it+1,sig_width);
		SignalWidth[iE+1]->SetBinError(it+1,sig_width_err);

	//Add mc yield and errors to stability check histograms
		MCYields[iE+1]->SetBinContent(it+1,mc_sig_events);
		MCYields[iE+1]->SetBinError(it+1,mc_sig_events_err);
		MCMass[iE+1]->SetBinContent(it+1,mc_mass);
		MCMass[iE+1]->SetBinError(it+1,mc_mass_err);
		MCWidth[iE+1]->SetBinContent(it+1,mc_width);
		MCWidth[iE+1]->SetBinError(it+1,mc_width_err);

	//Get thrown values for differential cross section
		thrownyields_canvas->cd(iE+1);
		double thrown_Ebin_tbin = ThrownH->GetBinContent(iE+1,it+1);
		double thrown_Ebin_tbin_err = ThrownH->GetBinError(iE+1,it+1);
		thrown_val[iE+1][it+1] = thrown_Ebin_tbin;
		thrown_err[iE+1][it+1] = thrown_Ebin_tbin_err;
		ThrownYields[iE+1]->SetBinContent(it+1,thrown_Ebin_tbin);
		ThrownYields[iE+1]->SetBinError(it+1,thrown_Ebin_tbin_err);
		cout << "~~~~~~~Thrown~ " << iE << "~" << it << " " << thrown_Ebin_tbin << " " << thrown_Ebin_tbin_err << endl;

	//Get flux values
        	flux_val[iE+1]=getbincontent(FluxH,iE+1);
        	flux_err[iE+1]=getbinerror(FluxH,iE+1); //+1 because 0 is the underflow
		cout << "~~~~~~~flux~" << iE << "~" << it << " " << flux_val[iE+1] << " " << flux_err[iE+1] << endl;

	//Calculate efficiency from mc yields and thrown values
		eff_val[iE+1][it+1] = mc_val[iE+1][it+1]/thrown_val[iE+1][it+1];
		eff_err[iE+1][it+1] = eff_val[iE+1][it+1] * sqrt(pow(mc_err[iE+1][it+1]/mc_val[iE+1][it+1],2)+pow(thrown_err[iE+1][it+1]/thrown_val[iE+1][it+1],2));
		cout << "~~~~~~~Eff~" << iE << "~" << it << " " << eff_val[iE+1][it+1] << " " << eff_err[iE+1][it+1] << endl;
		Eff[iE+1]->SetBinContent(it+1,eff_val[iE+1][it+1]);
		Eff[iE+1]->SetBinError(it+1,eff_err[iE+1][it+1]);

	//Calculate the differential cross section
		diffxsec_val[iE+1][it+1] = (sig_val[iE+1][it+1])/(constant * deltat * flux_val[iE+1] * mc_val[iE+1][it+1] /thrown_val[iE+1][it+1]);
		if(sig_val[iE+1][it+1] == 0.0){ 
		//Set the differential cross section error to zero if there wasn't enough signal to fit. This prevents NaNs.
			diffxsec_err[iE+1][it+1] = 0.0;
		} //end no-signal diff xsec error loop
		else {
		//Calculate error normally
		diffxsec_err[iE+1][it+1] = diffxsec_val[iE+1][it+1]*sqrt(pow(sig_err[iE+1][it+1]/sig_val[iE+1][it+1],2)+pow(flux_err[iE+1]/flux_val[iE+1],2)+pow(mc_err[iE+1][it+1]/mc_val[iE+1][it+1],2)+pow(thrown_err[iE+1][it+1]/thrown_val[iE+1][it+1],2));
		} //end signal diff xsec error loop

	//Add final differential cross section values and errors to histograms	
		cout << "~~~~~~~diffxsec~" << iE << "~" << it << " " << diffxsec_val[iE+1][it+1] << " " << diffxsec_err[iE+1][it+1] << endl;
		DiffXSec[iE+1]->SetBinContent(it+1,diffxsec_val[iE+1][it+1]);
		DiffXSec[iE+1]->SetBinError(it+1,diffxsec_err[iE+1][it+1]);
	} //end t loop

    //Draw and save histograms
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
	for(int itbin=0; itbin<numtBins; itbin++){	
	cout << "\t" << "-t: " << deltat * itbin + mintval << " - " << deltat * (itbin+1) + mintval << endl; 
	cout << "\t" << "\t" << "Signal Yields: " << sig_val[iEbin+1][itbin+1] 	<< " +/- " 	<< sig_err[iEbin+1][itbin+1] 	<< endl;
	cout << "\t" << "\t" << "MC Yields: " 	<< mc_val[iEbin+1][itbin+1] 	<< " +/- " 	<< mc_err[iEbin+1][itbin+1] 	<< endl;
	cout << "\t" << "\t" << "Thrown Yields: " << thrown_val[iEbin+1][itbin+1] << " +/- " 	<< thrown_err[iEbin+1][itbin+1] << endl;
	cout << "\t" << "\t" << "Flux Yields: " << flux_val[iEbin+1] 		<< " +/- " 	<< flux_err[iEbin+1] 		<< endl;
	cout << "\t" << "\t" << "Efficiency: " 	<< eff_val[iEbin+1][itbin+1] 	<< " +/- " 	<< eff_err[iEbin+1][itbin+1] 	<< endl;
	cout << "\t" << "\t" << "DiffXSec: " 	<< diffxsec_val[iEbin+1][itbin+1] 	<< " +/- " 	<< diffxsec_err[iEbin+1][itbin+1] << endl;
	} //end print t loop 
} //end print E loop
} //end macro

/*
//clas results, Goetz thesis Table D.1

TCanvas * adiffxsec_canvas = new TCanvas("adiffxsec_canvas", "adiffxsec_canvas",800,600);
adiffxsec_canvas->cd();
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
	xsec_gluex->SetBinContent(ith,diffxsec_val[ith-13]);
	xsec_gluex->SetBinError(ith,diffxsec_err[ith-13]);
}
//xsec_gluex->SetBinContent(14,4.48811);
//xsec_gluex->SetBinError(14,0.43384);
xsec_gluex->Draw("PE1");
//xsec_gluex_count->Draw("same");
adiffxsec_canvas->Update();
const Int_t NumBins=24;
Double_t g12xsec[NumBins] =  {0.256, 1.145, 2.981, 4.927, 5.63, 7.296, 8.47, 8.872, 10.796, 11.017, 10.583, 10.132, 9.729, 11.614, 11.553, 10.133, 10.413, 11.179, 11.478, 8.48, 8.14, 10.004,9.855, 10.513};
Double_t g12diffxsec_err[NumBins] = {0.300, 0.300, 0.521, 0.408, 0.630, 0.881, 0.708, 0.616, 0.621, 0.677, 0.752, 0.797, 0.925, 0.918, 1.103, 1.091, 1.164, 1.068, 1.269, 1.299, 1.020, 1.761, 1.273, 4.630};
TH1F * xsec_clas = new TH1F("xsec_clas", "xsec_clas",NumBins,2.625,5.4); 
xsec_clas->SetMarkerColor(kOrange);
xsec_clas->SetMarkerStyle(21);
for(int jth=0; jth<NumBins; jth++)
{
	xsec_clas->SetBinContent(jth+1,g12xsec[jth]);
	xsec_clas->SetBinError(jth+1,g12diffxsec_err[jth]);
}
Double_t g12energy[NumBins] =  { };
Double_t deltaE[NumBins] = { };
xsec_clas->Draw("same,PE1");
auto legend = new TLegend(0.7,0.7,0.9,0.9);
legend->AddEntry(xsec_gluex,"GlueX");
//legend->AddEntry(xsec_gluex_count,"GlueX MC Counting");
legend->AddEntry(xsec_clas, "CLAS g12");
legend->Draw();
adiffxsec_canvas->Update();
char xsec_wclas_macro_name[100];
sprintf(xsec_wclas_macro_name,"xsec_wclas_%s.C",version);
adiffxsec_canvas->SaveAs(xsec_wclas_macro_name);
char xsec_wclas_plot_name[100];
sprintf(xsec_wclas_plot_name,"xsec_wclas_%s.png",version);
adiffxsec_canvas->Print(xsec_wclas_plot_name);

*/

//xsec_gluex->SetName("Xi- Cross Section");
//axsec->SetTitle("#Xi^{-} Cross Section; E_{#gamma} (GeV); #sigma (nb)");
//adiffxsec_canvas->Print("test_axsec.png");
//TCanvas * gdiffxsec_canvas = new TCanvas("gdiffxsec_canvas", "gdiffxsec_canvas",800,600);
//TGraphErrors * axsec = new TGraphErrors(nBins, energy, diffxsec_val, denergy, diffxsec_err);
//Double_t energy[nBins]= {6.65,7.15, 7.65, 8.15, 8.65, 9.15, 9.65, 10.15, 10.65, 11.15};
//Double_t denergy[nBins]= {0.25, 0.25, 0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25};
