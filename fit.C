
#include "RooPlot.h"
{
  //using namespace RooFit;
char batch[100]= "347runs_dec20";
char runperiod[100]="2017-01";
char version[100]="ANAver20";
char plotversion[100]="accsub";
char filename[100];
char outputname[100];
char testoutputname[100];
char plotname[100];
char plot[100];
char accplotname[100];
char accsubplotname[100];
sprintf(filename,"/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_%s_%s_%s.root",runperiod,version,batch);
sprintf(outputname,"datafit_kpkpxim_XiMass_KinFit_%s_%s_%s_%s.png",runperiod,version,batch,plotversion);
sprintf(testoutputname,"prefit_kpkpxim_XiMass_KinFit_%s_%s_%s_%s.png",runperiod,version,batch, plotversion);
sprintf(plotname,"XiMass%s_KinFit",plotversion);
//sprintf(plot,"xsec_sigfit_%s.png",bin);
sprintf(plotname,"XiMass_KinFit");
sprintf(accplotname,"XiMass_KinFit_acc");
//sprintf(plotname,"XiMass069");
//sprintf(accplotname,"XiMass069_acc");
sprintf(accsubplotname,"XiMassKinFitsacc");

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetOptTitle(0);

  // initialization
  RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  TFile* f = TFile::Open(filename);

  RooWorkspace* w = new RooWorkspace("w");
  TCanvas * Xi_canvas1 = new TCanvas("Xi_canvas1", "Xi_canvas1",800,600);

  TH1F * XiMassKinFit = (TH1F*)f->Get(plotname);
  XiMassKinFit->GetXaxis()->SetRangeUser(1.1,1.5);
  TH1F * XiMassKinFit_acc = (TH1F*)f->Get(accplotname);
  TH1F *h_mass = (TH1F *) XiMassKinFit->Clone(accsubplotname);
  h_mass->Add(XiMassKinFit_acc,-0.5);
  h_mass->Rebin(5);
  h_mass->Draw("e0");
  //h_mass->GetXaxis()->SetRangeUser(1.1,1.5);
  h_mass->GetYaxis()->SetRangeUser(0,1500);
  Xi_canvas1->Print(testoutputname);
  // observable(s)
  RooRealVar mass("mass", "mass", 1.2, 1.5);
  //mass.setBins(150);

  // import data (histograms)
  RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, h_mass);

  w->import(RooArgSet(mass));
  mass.setRange("signal",1.31,1.34);
  mass.setRange("total",1.25,1.50);
  mass.setRange("sideband1",1.25,1.3);
  mass.setRange("sideband2",1.35,1.5); 

  // background and signals
        w->factory("Chebychev::bkgd(mass,{c1[0,-1.e4,1.e4],c2[0,-1.e4,1.e4]})");
        //w->factory("Chebychev::bkgd(mass,{c1[2.20],c2[-1.557]})");
        w->factory("Gaussian::gaus(mass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");

  // build model for data:  accidental shape + background + signals
  w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[100,0,1e5]*gaus)");

  // do the fit
  //w->pdf("model")->fitTo(*data,RooFit::Extended(kTRUE),RooFit::Range(1.25,1.5),RooFit::Minos(1));
  w->pdf("model")->fitTo(*data,RooFit::Range(1.25,1.5),RooFit::Minos(1));
  
  // make some plots
  RooPlot* massframe = mass.frame(RooFit::Title(" "));
  //massframe->SetMaximum(1500);
  massframe->SetXTitle("#Lambda#pi^{-} mass (GeV)");
  massframe->GetYaxis()->SetTitleOffset(1.2);
  data->plotOn(massframe,RooFit::MarkerColor(kBlack),RooFit::LineColor(kBlack));
  w->pdf("model")->paramOn(massframe); //comment out to turn off stats
  w->pdf("model")->plotOn(massframe);
  w->pdf("gaus")->plotOn(massframe, RooFit::LineStyle(kDotted),
  		RooFit::Normalization(w->var("nsig")->getVal(), RooAbsReal::NumEvent));
  w->pdf("bkgd")->plotOn(massframe, RooFit::LineStyle(kDotted),
  		RooFit::Normalization(w->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
  massframe->Draw();
  Xi_canvas1->Print(outputname);  
  double_t bkgd_total_integral = w->pdf("bkgd")->createIntegral(mass,RooFit::Range("total"))->getVal();
  double_t bkgd_signal_integral = w->pdf("bkgd")->createIntegral(mass,RooFit::Range("signal"))->getVal();

  double_t bkgd_sb1_integral = w->pdf("bkgd")->createIntegral(mass,RooFit::Range("sideband1"))->getVal();
  double_t bkgd_sb2_integral = w->pdf("bkgd")->createIntegral(mass,RooFit::Range("sideband2"))->getVal();

  double_t bkgd_total_events = w->var("nbkgd")->getVal();
  double_t sig_total_integral = w->pdf("gaus")->createIntegral(mass,RooFit::Range("total"))->getVal();
  double_t sig_signal_integral = w->pdf("gaus")->createIntegral(mass,RooFit::Range("signal"))->getVal();
  double_t sig_total_events = w->var("nsig")->getVal();
  double_t bkgd_events = bkgd_total_events*bkgd_signal_integral/bkgd_total_integral;
  double_t sig_events = sig_total_events*sig_signal_integral/sig_total_integral;
  double_t bkgd_sb1_events = bkgd_total_events*bkgd_sb1_integral/bkgd_total_integral;
  double_t bkgd_sb2_events = bkgd_total_events*bkgd_sb2_integral/bkgd_total_integral;

  cout << "BKGD SIGNAL INTEGRAL:TOTAL INTEGRAL= " << bkgd_signal_integral << ":" << bkgd_total_integral  << " = " << bkgd_signal_integral/bkgd_total_integral << endl;
  cout << "SIG SIGNAL INTEGRAL:TOTAL INTEGRAL= " << sig_signal_integral << ":" << sig_total_integral << " = " << sig_signal_integral/sig_total_integral << endl;
  cout << "SIG EVENTS:BKGD EVENTS: " << sig_events << ":" << bkgd_events << " = " << sig_events/bkgd_events << endl;
  cout << endl << "signal events   " << "total background events   " << "bkgd under peak " << endl; 
  cout << sig_events << "          " << bkgd_total_events << "                  " << bkgd_events << endl;
  cout << "left sideband   " << "right sideband      " << "both sidebands" << endl;
  cout << bkgd_sb1_events << "         " << bkgd_sb2_events << "              " << bkgd_sb1_events+bkgd_sb2_events << endl;

}
