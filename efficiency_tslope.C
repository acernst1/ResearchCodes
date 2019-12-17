#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

double getbincontent(TH1F* AccH, int bin);
double getbinerror(TH1F* AccH, int bin);
double loc_i;
double getbincontent(TH1F* hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F* AccH, int bin){  return AccH->GetBinError(bin);}
char bin[100];
char mcworkspace[100];
char mccanvas[100];
char mcplotname[100];
char mcaccplotname[100];
char accplotname[100];
char mcplot[100];
char effplot[100];
char effnumbers[100];
char effcountnumbers[100];
char mcFilePath[100];
char thrownFilePath[100];
char thrown_canvas[100];
char thrown_plot[100];
char version[100]="tslope_subset";

void efficiency_tslope()
{
    int numTests=6; //10
    double minVal=6.4;
    double maxVal=11.4;
    double tagged=1.0;
    double tagged_err=0.0;
    double efficiency[numTests];
    double eff_err[numTests];
    double efficiency_count[numTests];
    double eff_count_err[numTests];

    double Tests [] = {1.19, 1.26, 1.33, 1.47, 1.54, 1.61};

    gStyle->SetOptStat(0);
    gStyle->SetErrorX(0);
    TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",800,600);
    TH1F * eff_runs = new TH1F("eff_runs", "Efficiency; -t (GeV); Efficiency (%)",numTests*100,Tests[0]-0.1,Tests[numTests-1]+0.1); 
    TH1F * eff_count_runs = new TH1F("eff_count_runs", "Efficiency; -t (GeV); Efficiency (%)",numTests*100,Tests[0]-0.1,Tests[numTests-1]+0.1);

    eff_runs->SetMarkerColor(kBlue);
    eff_runs->SetMarkerStyle(21);
    eff_runs->SetLabelSize(0.035,"xy");
    eff_runs->SetLabelOffset(0.001,"xy");
    eff_runs->GetYaxis()->SetRangeUser(0,3);
    eff_runs->SetTitle("MC Efficiency by t-slope; -t (GeV); Efficiency (%)");

    double fit_nom = 0.700301;
    double fit_nom_err = 0.0402051;
    TLine *nom_line = new TLine(1.4,0.0,1.4,2.0);
    TLine *nom_fit_line = new TLine(Tests[0]-0.1,fit_nom,Tests[numTests-1]+0.1,fit_nom);
    TLine *nom_fit_line_uperr = new TLine(Tests[0]-0.1,fit_nom+fit_nom_err,Tests[numTests-1]+0.1,fit_nom+fit_nom_err);
    TLine *nom_fit_line_downerr = new TLine(Tests[0]-0.1,fit_nom-fit_nom_err,Tests[numTests-1]+0.1,fit_nom-fit_nom_err);
    nom_line->SetLineStyle(1);
    nom_line->SetLineColor(kGreen+2);
    nom_fit_line->SetLineStyle(9);
    nom_fit_line->SetLineColor(kGreen+2);
    nom_fit_line_uperr->SetLineStyle(7);
    nom_fit_line_uperr->SetLineColor(kGreen+2);
    nom_fit_line_downerr->SetLineStyle(7);
    nom_fit_line_downerr->SetLineColor(kGreen+2);

    eff_count_runs->SetMarkerColor(kRed);
    eff_count_runs->SetMarkerStyle(21);
    eff_count_runs->SetLabelSize(0.035,"xy");
    eff_count_runs->SetLabelOffset(0.001,"xy");
    eff_count_runs->SetTitle("MC Efficiency by t-slope; -t (GeV); Efficiency (%)");

    auto legend = new TLegend(0.1,0.7,0.3,0.9);
    legend->AddEntry(eff_runs,"fit method");
    legend->AddEntry(eff_count_runs,"counting method");
    legend->AddEntry(nom_line,"nominal value","l");

    for(int i=0; i<numTests; i++)
	{
    int run = Tests[i]*100;
    sprintf(mcFilePath, "subset/kpkpxim__B4_M23_genr8_kpkpxim_nodecay_wrandom_039_t_%03d.root", run);
    sprintf(thrownFilePath, "subset/tree_thrown_genr8_kpkpxim_nodecay_wrandom_039_t_%03d.root", run);
    sprintf(thrown_canvas,"thrown_canvas_%03d",run);
    sprintf(thrown_plot, "thrown_%03d.png", run);
    sprintf(mccanvas,"Xi_canvas_mc_%03d",run);
    sprintf(mcworkspace,"wmc%03d",run);
    sprintf(mcplotname,"XiMass_KinFit");
    sprintf(mcaccplotname,"XiMass_KinFit_acc");
    sprintf(accplotname,"XiMassKinFit%03dacc",run);
    sprintf(mcplot,"mcfitforeff_%03d.png", run);

    TCanvas * thrwn_canvas = new TCanvas(thrown_canvas,thrown_canvas,800,600);

    TFile* mcfile = TFile::Open(mcFilePath);
    TFile* thrownfile = TFile::Open(thrownFilePath);

    thrwn_canvas->cd();
    thrownfile->cd(); 
    TTree* thrownT=(TTree*) gDirectory->Get("Thrown_Tree");
    TH1F* thrown_hist=new TH1F("thrown_hist","thrown_hist",1,minVal,maxVal);
    thrownT->Draw("ThrownBeam__P4->E()>>thrown_hist");
    thrwn_canvas->Print(thrown_plot);
    tagged=getbincontent(thrown_hist,1);
    tagged_err=getbinerror(thrown_hist,1); 

    TH1F * XiMassKinFit = (TH1F*)mcfile->Get(mcplotname);
    XiMassKinFit->Sumw2();
    TH1F * XiMassKinFit_acc = (TH1F*)mcfile->Get(mcaccplotname);
    XiMassKinFit_acc->Sumw2();
    TH1F *mass_mc_hist = (TH1F *) XiMassKinFit->Clone(accplotname);
    mass_mc_hist->Add(XiMassKinFit_acc,-0.5);

    RooWorkspace* wmc = new RooWorkspace(mcworkspace);
    TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
    RooRealVar mcmass("mcmass", "mcmass", 1.2, 1.5);
    RooDataHist *mc = new RooDataHist("mc", "MC of mass", mcmass, mass_mc_hist);
    mass_mc_hist->Print();
    wmc->import(RooArgSet(mcmass));
    wmc->factory("Gaussian::gausmc(mcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
    wmc->factory("SUM::mcmodel(nsigmc[50,0,1e5]*gausmc)");
    wmc->pdf("mcmodel")->fitTo(*mc,RooFit::Range(1.31,1.335),RooFit::Minos(1));
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
    Xi_mc_canvas->Print(mcplot);

    double mc_sig_events_count= getbincontent(mass_mc_hist, 43)+getbincontent(mass_mc_hist, 44)+getbincontent(mass_mc_hist, 45)+getbincontent(mass_mc_hist, 46)+getbincontent(mass_mc_hist, 47)+getbincontent(mass_mc_hist, 48);
    double mc_sig_events_count_err= sqrt(pow(getbinerror(mass_mc_hist,43),2)+pow(getbinerror(mass_mc_hist, 44),2)+pow(getbinerror(mass_mc_hist, 45),2)+pow(getbinerror(mass_mc_hist, 46),2)+pow(getbinerror(mass_mc_hist, 47),2)+pow(getbinerror(mass_mc_hist, 48),2));

    efficiency[i]= 100.*mc_sig_events / tagged; 
    eff_err[i] = efficiency[i]*sqrt(pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

    efficiency_count[i]= 100.*mc_sig_events_count / tagged; 
    eff_count_err[i] = efficiency_count[i]*sqrt(pow(mc_sig_events_count_err/mc_sig_events_count,2)+pow(tagged_err/tagged,2));

    cout << "~~~~~~~~~fit~~" << mc_sig_events << " " << tagged << " " << efficiency[i] << " " << eff_err[i] << endl;
    cout << "~~~~~~~~~count~~" << mc_sig_events_count << " " << tagged << " " << efficiency_count[i] << " " << eff_count_err[i] << endl;

    eff_canvas->cd();
    int eff_bin = eff_runs->GetXaxis()->FindBin(Tests[i]);
    eff_runs->SetBinContent(eff_bin, efficiency[i]);
    eff_runs->SetBinError(eff_bin,eff_err[i]);
    eff_runs->Draw("PE1");
    eff_count_runs->SetBinContent(eff_bin, efficiency_count[i]);
    eff_count_runs->SetBinError(eff_bin,eff_count_err[i]);
    eff_count_runs->Draw("SAME");
    nom_line->Draw();
    nom_fit_line->Draw();
    nom_fit_line_uperr->Draw();
    nom_fit_line_downerr->Draw();
    legend->Draw();
    eff_canvas->Update();
    sprintf(effplot,"efficiency_%s.png",version);
    eff_canvas->Print(effplot);


   }
sprintf(effnumbers,"eff_%s.C",version);
eff_runs->SaveAs(effnumbers);
sprintf(effcountnumbers,"eff_count_%s.C",version);
eff_runs->SaveAs(effcountnumbers);
}

