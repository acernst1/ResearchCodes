
#include "RooPlot.h"
{
  //using namespace RooFit;
char batch[100]= "may2020";
char runperiod[100]="2018-08";
char version[100]="ANAver05LE";
char plotversion[100]="accsub";
char filename[100];
char outputname[100];
char testoutputname[100];
char plotname[100];
char plot[100];
char accplotname[100];
char accsubplotname[100];
sprintf(filename,"kpkpxim__M23_2018_08_LE_ANAver05_may11.root");
sprintf(outputname,"datafit_kpkpxim_XiMass_KinFit_%s_%s_%s_%s.png",runperiod,version,batch,plotversion);
sprintf(testoutputname,"prefit_kpkpxim_XiMass_KinFit_%s_%s_%s_%s.png",runperiod,version,batch, plotversion);
sprintf(plotname,"XiMass%s_KinFit",plotversion);
//sprintf(plot,"xsec_sigfit_%s.png",bin);
sprintf(plotname,"XiMass_KinFit");
sprintf(accplotname,"XiMass_KinFit_wacc");
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

  // Get plots and perform accidental subtraction
  TH1F * XiMassKinFit = (TH1F*)f->Get(plotname);
  XiMassKinFit->GetXaxis()->SetRangeUser(1.1,1.5);
  TH1F * XiMassKinFit_acc = (TH1F*)f->Get(accplotname);
  TH1F *h_mass = (TH1F *) XiMassKinFit->Clone(accsubplotname);
  h_mass->Add(XiMassKinFit_acc,-0.5);
  h_mass->Rebin(5);
  h_mass->Draw("e0");
  
  h_mass->GetYaxis()->SetRangeUser(0,1500);
  Xi_canvas1->Print(testoutputname);
  RooRealVar mass("mass", "mass", 1.2, 1.5);
  
  // import data (histograms)
  RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, h_mass);

  w->import(RooArgSet(mass));
  
  // background and signal functions
  w->factory("Chebychev::bkgd(mass,{c1[0,-1.e4,1.e4],c2[0,-1.e4,1.e4]})");
  w->factory("Gaussian::gaus(mass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");

  // build model for data:  accidental shape + background + signals
  w->factory("SUM::model(nbkgd[1500,0,1e5]*bkgd, nsig[1600,0,1e5]*gaus)");

  // do the fit
  w->pdf("model")->fitTo(*data,RooFit::Range(1.25,1.5),RooFit::Minos(1));
  
  // make some plots
  RooPlot* massframe = mass.frame(RooFit::Title(" "));
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
  }
