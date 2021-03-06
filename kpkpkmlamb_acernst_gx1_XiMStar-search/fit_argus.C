
#include "RooPlot.h"
#include "RooGenericPdf.h"
{
  //using namespace RooFit;
char version[100]="argus_no1820_201701_oldcode";
char plotversion[100]="";
char filename[100];
char outputname[100];
char outputnamewo[100];
char plotname[100];
char plot[100];
char accplotname[100];
char accsubplotname[100];
//sprintf(filename,"kpkpkmlamb_allsets_oldcode.root");
//sprintf(filename,"kpkpkmlamb_2018_08_ver06_oldcode.root");
//sprintf(filename,"kpkpkmlamb_2018_01_ver03_oldcode.root");
sprintf(filename,"kpkpkmlamb_2017_01_ver30_oldcode.root");
sprintf(outputname,"datafit_kpkpkmlamb_XiStarMass_KinFit_%s.png",version);
sprintf(plotname,"XiMass%s_KinFit",plotversion);
//sprintf(plot,"xsec_sigfit_%s.png",bin);
//sprintf(plotname,"XiMass_KinFit");
//sprintf(accplotname,"XiMass_KinFit_acc");
sprintf(plotname,"XiMass_KinFit");
sprintf(accplotname,"XiMass_KinFit_acc");
sprintf(accsubplotname,"XiMassKinFitsacc");

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);

  // initialization
  RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D");
  TFile* f = TFile::Open(filename);

  RooWorkspace* w = new RooWorkspace("w");
  TCanvas * Xi_canvas1 = new TCanvas("Xi_canvas1", "Xi_canvas1",800,600);

  TH1F * XiMassKinFit = (TH1F*)f->Get(plotname);
  TH1F * XiMassKinFit_acc = (TH1F*)f->Get(accplotname);
  TH1F *h_mass = (TH1F *) XiMassKinFit->Clone(accsubplotname);
  h_mass->Add(XiMassKinFit_acc,-0.5);
  h_mass->Rebin(3);

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

//w->factory("Voigtian::v1820(mass,mean1820[1.823,1.818,1.828],gamma1820[0.024,0.015,0.1],sigma[0.004295])");
//w->factory("Voigtian::v(mass,mean[1.818],gamma[0.05],sigma[0.004295])");
//w->factory("Voigtian::v2(mass,mean2[1.690,1.680,1.700],gamma2[0.02,0.005,0.060],sigma[0.004295])");
//w->factory("Voigtian::v3(mass,mean3[1.950,1.935,1.965],gamma3[0.06,0.040,0.080],sigma[0.004295])");  
//w->factory("Voigtian::v4(mass,mean4[2.025,2.020,2.030],gamma4[0.02,0.015,0.030],sigma[0.004295])");
//w->factory("Voigtian::v2120(mass,mean2120[2.120,2.116,2.141],gamma2120[0.02,0.013,0.037],sigma[0.004295])");
//w->factory("Voigtian::v6(mass,mean6[2.500,2.400,2.600],gamma6[0.1,0.02,0.2],sigma[0.004295])");

// build model for data:  accidental shape + background + signals
w->factory("SUM::model(nbkgd[8200,0,1e5]*bkgd)");
//w->factory("SUM::model(nbkgd[8200,0.,1.5e5]*bkgd, nsig1820[3000,0,1.5e4]*v1820)");
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
/*  w->pdf("v1820")->plotOn(massframe, RooFit::LineStyle(kDotted),
      RooFit::Normalization(w->var("nsig1820")->getVal(), RooAbsReal::NumEvent));
 */ w->pdf("bkgd")->plotOn(massframe, RooFit::LineStyle(kDotted),
      RooFit::Normalization(w->var("nbkgd")->getVal(), RooAbsReal::NumEvent));
 /* w->pdf("v2120")->plotOn(massframe, RooFit::LineStyle(kDotted),
    RooFit::Normalization(w->var("nsig2120")->getVal(), RooAbsReal::NumEvent));
 */ massframe->Draw();
  Xi_canvas1->Print(outputname);  

}
