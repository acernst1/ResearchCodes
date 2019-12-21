#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

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
double minEval=6.4; 
double maxEval=11.4; 
int numEBins=10;
double mintval = 0.0;
double maxtval = 5.0;
int numtBins = 1.0;
double minmass=1.2; 
double minfitmass=1.27;
double maxmass=1.5; 
int nummassBins=80;

double loc_i;
double getbincontent(TH1F* hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F* AccH, int bin){  return AccH->GetBinError(bin);}
void xsec(TString dataFilePath, TString fluxFilePath, TString mcFilePath, TString thrownFilePath1,const char version[17])
{
    gStyle->SetOptStat(0);
    double constant = 1.22e-9; // constant in nb
    double flux=1.0;
    double flux_err=0.0;
    double tagged=1.0;
    double tagged_err=0.0;
    double xsec_val[numEBins];
    double xsec_err[numEBins];
    double efficiency[numEBins];
    double eff_err[numEBins];
    double efficiency_count[numEBins];
    double eff_count_err[numEBins];
    double xsec_count_val[numEBins];
    double xsec_count_err[numEBins];
  
    TFile* datafile = TFile::Open(dataFilePath);
    TFile* fluxfile = TFile::Open(fluxFilePath);
    TFile* mcfile = TFile::Open(mcFilePath);
    

    TCanvas * flux_canvas = new TCanvas("flux_canvas", "flux_canvas",800,600);
    TH1F*  FluxH= (TH1F*) fluxfile->Get("tagged_flux");
    FluxH->GetXaxis()->SetRangeUser(minEval,maxEval);
    FluxH->Rebin(FluxH->GetNbinsX()/numEBins);
    FluxH->Draw(); 
    char flux_macro_name[100];
    sprintf(flux_macro_name,"flux_numbers_%s.C",version);
    FluxH->SaveAs(flux_macro_name);
    char flux_plot_name[100];
   sprintf(flux_plot_name,"xsec_flux_%s.png",version);
    flux_canvas->Print(flux_plot_name);


    TFile* thrownfile = TFile::Open(thrownFilePath1);
    TCanvas * thrown_canvas = new TCanvas("thrown_canvas", "thrown_canvas",800,600);
    thrown_canvas->cd();
    thrownfile->cd(); 
    TH2F*  ThrownHtemp= (TH2F*) thrownfile->Get("Egamma_t");
    ThrownHtemp->GetXaxis()->SetRangeUser(minEval,maxEval);	
    ThrownHtemp->GetYaxis()->SetRangeUser(mintval,maxtval);
    ThrownHtemp->RebinX(ThrownHtemp->GetNbinsX()/numEBins);    
    ThrownHtemp->RebinY(ThrownHtemp->GetNbinsY()/numtBins);
    double tmin = mintval; 
    double tmax = maxtval;
    int tbinmin = ThrownHtemp->GetYaxis()->FindBin(tmin);
    int tbinmax = ThrownHtemp->GetYaxis()->FindBin(tmax) -1.;
    TH1F * ThrownH = (TH1F *) ThrownHtemp->ProjectionY("ThrownH",tbinmin,tbinmax);
    ThrownH->Draw("colz");
    sprintf(thrown_numbers_macro_name,"thrown_numbers_%s.C",version);
    sprintf(thrown_numbers_plot_name, "xsec_thrown_%s.png",version);
    ThrownH->SaveAs(thrown_numbers_macro_name);
    thrown_canvas->Print(thrown_numbers_plot_name);

 
    TCanvas * xsec_canvas = new TCanvas("xsec_canvas", "xsec_canvas",800,600);
    TH1F * xsec = new TH1F("xsec", "Cross Section; E_{#gamma}; #sigma_{total} (nb)",numEBins,minEval,maxEval); 
    TH1F * xsec_count = new TH1F("xsec_count", "Cross Section; E_{#gamma}; #sigma_{total} (nb)",numEBins,minEval,maxEval); 
    xsec->SetMarkerColor(kRed);
    xsec->SetMarkerStyle(21);
    xsec_count->SetMarkerColor(kBlue);
    xsec_count->SetMarkerStyle(21);
    xsec->SetLabelSize(0.035,"xy");
    xsec->SetLabelOffset(0.001,"xy");

    TH1F * eff = new TH1F("eff", "Efficiency; E_{#gamma}; Efficiency (%)",numEBins,minEval,maxEval);
    TH1F * eff_count = new TH1F("eff_count", "Efficiency; E_{#gamma}; #Efficiency (%)",numEBins,minEval,maxEval);
    TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",800,600);
    eff->SetMarkerColor(kRed);
    eff->SetMarkerStyle(21);
    eff_count->SetMarkerColor(kBlue);
    eff_count->SetMarkerStyle(21);
    eff->SetLabelSize(0.035,"xy");
    eff->SetLabelOffset(0.001,"xy");
    eff->GetYaxis()->SetRangeUser(0,3);

    for(int i=0; i<numEBins; i++)
	{
	double delta=(maxEval- minEval)/float(numEBins);
	double Emin = delta * i + (minEval);
	double Emax = delta * i + (minEval);
	int buffer = Emin*10;
	cout << "~~~~~~~E~ " << i << " " << Emin << " " << Emax << " " << buffer << endl;
        flux=getbincontent(FluxH,i+1);
        flux_err=getbinerror(FluxH,i+1); //+1 because 0 is the underflow, +5 because of binning
	cout << "~~~~~~~flux~ " << i << " " << flux << " " << flux_err << endl;
        tagged=getbincontent(ThrownH,i+1);
        tagged_err=getbinerror(ThrownH,i+1);
	cout << "~~~~~~~thrown~ " << i << " " << tagged << " " << tagged_err << endl; 
        
	sprintf(bin,"%03d",buffer);

        sprintf(workspace,"w%s",bin);
        sprintf(canvas,"Xi_canvas_%s",bin);
        sprintf(plot,"xsec_sigfit_%s_%s.png",version, bin);
        sprintf(plotname,"XiMass%s",bin);
        sprintf(accplotname,"XiMass%s_acc",bin);
        sprintf(accsubplotname,"XiMassKinFit%sacc",bin);

        sprintf(mcworkspace,"wmc%s",bin);
        sprintf(mccanvas,"Xi_canvas_mc_%s",bin);
        sprintf(mcplot,"xsec_mcfit_%s_%s.png",version, bin);
        sprintf(effplot,"xsec_eff_beamenergy_%s.png",version);
        sprintf(mcplotname,"XiMass%s",bin);
        sprintf(mcaccplotname,"XiMass%s_acc",bin);
        sprintf(mcaccsubplotname,"XiMassKinFit%sacc",bin);

	TH1F * XiMassKinFit = (TH1F*)datafile->Get(plotname);
	TH1F * XiMassKinFit_acc = (TH1F*)datafile->Get(accplotname);
	TH1F *mass_hist = (TH1F *) XiMassKinFit->Clone(accsubplotname);
	mass_hist->Add(XiMassKinFit_acc,-0.5);
	
	cout << "MC file is " << mcfile << ". MC plot is " << mcplotname << endl;
	TH1F * XiMassKinFit_mc = (TH1F*)mcfile->Get(mcplotname);
	//XiMassKinFit_mc->Sumw2();
	TH1F * XiMassKinFit_acc_mc = (TH1F*)mcfile->Get(mcaccplotname);
	//XiMassKinFit_acc_mc->Sumw2();
	TH1F *mass_mc_hist = (TH1F *) XiMassKinFit_mc->Clone(mcaccsubplotname);
	mass_mc_hist->Add(XiMassKinFit_acc_mc,-0.5);

        RooWorkspace* w = new RooWorkspace(workspace);
        TCanvas * Xi_canvas = new TCanvas(canvas, canvas,800,600);
        RooRealVar mass("mass", "mass", 1.2, 1.5);
        RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, mass_hist);
        mass_hist->Print();
        w->import(RooArgSet(mass));
        w->factory("Chebychev::bkgd(mass,{c1[2.20,-1.e4,1.e4],c2[-1.557,-1.e4,1.e4]})");
        w->factory("Gaussian::gaus(mass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");
        w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[100,0,1e3]*gaus)");
        w->pdf("model")->fitTo(*data,RooFit::Range(1.27,1.5),RooFit::Minos(1));
        RooPlot* massframe = mass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        massframe->SetMaximum(325);
        massframe->SetXTitle("#Lambda#pi^{-} mass");
        data->plotOn(massframe) ;
        w->pdf("model")->paramOn(massframe);
        w->pdf("model")->plotOn(massframe);
        w->pdf("gaus")->plotOn(massframe, RooFit::LineStyle(kDotted),
 		RooFit::Normalization(w->var("nsig")->getVal(), RooAbsReal::NumEvent));
        w->pdf("bkgd")->plotOn(massframe, RooFit::LineStyle(kDotted),
  		RooFit::Normalization(w->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
	double_t sig_events = w->var("nsig")->getVal();
	double_t sig_events_err = w->var("nsig")->getError();
	cout << "~~~~~~~sig~ " << i << " " << sig_events << " " << sig_events_err << endl; 
        massframe->Draw();
	sprintf(signal_numbers, "signal_numbers_%s_%s.C", bin,version);
	massframe->SaveAs(signal_numbers);
        Xi_canvas->Print(plot);

        RooWorkspace* wmc = new RooWorkspace(mcworkspace);
        TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
        RooRealVar mcmass("mcmass", "mcmass", 1.2, 1.5);
        RooDataHist *mc = new RooDataHist("mc", "MC of mass", mcmass, mass_mc_hist);
        mass_mc_hist->Print();
        wmc->import(RooArgSet(mcmass));
        wmc->factory("Gaussian::gausmc(mcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
        wmc->factory("SUM::mcmodel(nsigmc[50,0,1e6]*gausmc)");
        wmc->pdf("mcmodel")->fitTo(*mc,RooFit::Range(1.305,1.35),RooFit::Minos(1));
        RooPlot* mcmassframe = mcmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        mcmassframe->SetMaximum(1000);
        mcmassframe->SetXTitle("#Lambda#pi^{-} mass");
        mc->plotOn(mcmassframe) ;
        wmc->pdf("mcmodel")->paramOn(mcmassframe);
        wmc->pdf("mcmodel")->plotOn(mcmassframe);
        wmc->pdf("gausmc")->plotOn(mcmassframe, RooFit::LineStyle(kDotted),
 		RooFit::Normalization(wmc->var("nsigmc")->getVal(), RooAbsReal::NumEvent));
        double_t mc_sig_events = wmc->var("nsigmc")->getVal();
	double_t mc_sig_events_err = wmc->var("nsigmc")->getError();
        mcmassframe->Draw();
	sprintf(mcsignal_numbers, "mcsignal_numbers_%s_%s.C", bin,version);
	mcmassframe->SaveAs(signal_numbers);
        Xi_mc_canvas->Print(mcplot);

        double mc_sig_events_count= getbincontent(mass_mc_hist, 22)+getbincontent(mass_mc_hist, 23)+getbincontent(mass_mc_hist, 24);
        double mc_sig_events_count_err= sqrt(pow(getbinerror(mass_mc_hist,22),2)+pow(getbinerror(mass_mc_hist, 23),2)+pow(getbinerror(mass_mc_hist, 24),2));

	efficiency[i]= mc_sig_events / tagged; 
	eff_err[i] = efficiency[i]*sqrt(pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

        efficiency_count[i]= mc_sig_events_count / tagged; 
        eff_count_err[i] = efficiency_count[i]*sqrt(pow(mc_sig_events_count_err/mc_sig_events_count,2)+pow(tagged_err/tagged,2));

        cout << "~~~~~~~~~fit~mc~efficiency~" << i << " " << mc_sig_events << " " << tagged << " " << efficiency[i] << " " << eff_err[i] << endl;
        cout << "~~~~~~~~~count~mc~efficiency~" << i << " " << mc_sig_events_count << " " << tagged << " " << efficiency_count[i] << " " << eff_count_err[i] << endl; 
 
        xsec_val[i] = (sig_events)/(constant * flux * mc_sig_events / tagged);
	xsec_err[i] = xsec_val[i]*sqrt(pow(sig_events_err/sig_events,2)+pow(flux_err/flux,2)+pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

        xsec_count_val[i] = (sig_events)/(constant  * flux * (efficiency_count[i]));
	xsec_count_err[i] = xsec_count_val[i]*sqrt(pow(sig_events_err/sig_events,2)+pow(flux_err/flux,2)+pow(eff_count_err[i]/efficiency_count[i],2));

	cout << "~~~~~~~fit~xsec~ " << i << " " << xsec_val[i] << " " << xsec_err[i] << endl;
	cout << "~~~~~~~count~xsec~ " << i << " " << xsec_count_val[i] << " " << xsec_count_err[i] << endl; 

 	xsec_canvas->cd();
	xsec->SetBinContent(i, xsec_val[i]);
	xsec->SetBinError(i, xsec_err[i]);
	xsec_count->SetBinContent(i, xsec_count_val[i]);
	xsec_count->SetBinError(i, xsec_count_err[i]);

	eff_canvas->cd();
	eff->SetBinContent(i+1,  efficiency[i]*100.);
	eff->SetBinError(i+1,eff_err[i]*100.);
	eff_count->SetBinContent(i+1, efficiency_count[i]*100.);
	eff_count->SetBinError(i+1,eff_count_err[i]*100.);

  }
	auto legend02 = new TLegend(0.7,0.7,0.9,0.9);
	legend02->AddEntry(xsec,"GlueX MC Fitting");
	legend02->AddEntry(xsec_count,"GlueX MC Counting");
  	xsec_canvas->cd();
        xsec->Draw("PE1");
	xsec_count->Draw("same");
	legend02->Draw();
	sprintf(xsecplot,"xsec_fitandcount_%s.png",version );
	sprintf(xsecplotC,"xsec_fitandcount_%s.C",version );
	xsec_canvas->Print(xsecplot);
	xsec->SaveAs(xsecplotC);
	eff_canvas->cd();	
	eff->Draw("PE1");
	char efficiency_hist_numbers[100];
       sprintf(efficiency_hist_numbers,"efficiency_hist_%s.C",version);
	eff->SaveAs(efficiency_hist_numbers);
	//eff_count->Draw("same");
	legend02->Draw();
	eff_canvas->Print(effplot);


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
const Int_t numEBins=24;
Double_t g12xsec[numEBins] =  {0.256, 1.145, 2.981, 4.927, 5.63, 7.296, 8.47, 8.872, 10.796, 11.017, 10.583, 10.132, 9.729, 11.614, 11.553, 10.133, 10.413, 11.179, 11.478, 8.48, 8.14, 10.004,9.855, 10.513};
Double_t g12xsec_err[numEBins] = {0.300, 0.300, 0.521, 0.408, 0.630, 0.881, 0.708, 0.616, 0.621, 0.677, 0.752, 0.797, 0.925, 0.918, 1.103, 1.091, 1.164, 1.068, 1.269, 1.299, 1.020, 1.761, 1.273, 4.630};
TH1F * xsec_clas = new TH1F("xsec_clas", "xsec_clas",numEBins,2.625,5.4); 
xsec_clas->SetMarkerColor(kOrange);
xsec_clas->SetMarkerStyle(21);
for(int jth=0; jth<numEBins; jth++)
{
	xsec_clas->SetBinContent(jth+1,g12xsec[jth]);
	xsec_clas->SetBinError(jth+1,g12xsec_err[jth]);
}
Double_t g12energy[numEBins] =  { };
Double_t deltaE[numEBins] = { };
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


}
//xsec_gluex->SetName("Xi- Cross Section");
//axsec->SetTitle("#Xi^{-} Cross Section; E_{#gamma} (GeV); #sigma (nb)");
//axsec_canvas->Print("test_axsec.png");
//TCanvas * gxsec_canvas = new TCanvas("gxsec_canvas", "gxsec_canvas",800,600);
//TGraphErrors * axsec = new TGraphErrors(nBins, energy, xsec_val, denergy, xsec_err);
//Double_t energy[nBins]= {6.65,7.15, 7.65, 8.15, 8.65, 9.15, 9.65, 10.15, 10.65, 11.15};
//Double_t denergy[nBins]= {0.25, 0.25, 0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25};
