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

double getbincontent(TH1F* hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F* AccH, int bin){  return AccH->GetBinError(bin);}

void xsec_diff(TString dataFilePath, TString fluxFilePath, TString mcFilePath, TString thrownFilePath1,const char version[17])
{
    gStyle->SetOptStat(0);
    double mintval = 0.0;
    double maxtval = 10.0;
    int numtBins=10; 
    double minEval=6.4; 
    double maxEval=11.4; 
    int numEBins=10;
    double deltat = (maxtval - mintval) / float(numtBins) ;
    double deltaE = (maxEval - minEval) / float(numEBins) ;
    double constant = 1.22e-9; // constant in nb
    double flux=1.0;
    double flux_err=0.0;
    double tagged=1.0;
    double tagged_err=0.0;
    double xsec_val[numEBins][numtBins];
    double xsec_err[numEBins][numtBins];
    double efficiency[numEBins][numtBins];
    double eff_err[numEBins][numtBins];
    double canvas_margins = 1e-50;
    TH1F * SignalYields[numEBins+1];
    TH1F * MCYields[numEBins+1];
    TH1F * ThrownYields[numEBins+1];
    TH1F * Xsec[numEBins+1];

    TFile* datafile = TFile::Open(dataFilePath);
    TFile* fluxfile = TFile::Open(fluxFilePath);
    TFile* mcfile = TFile::Open(mcFilePath);
 /*   DONE
    TCanvas * flux_canvas = new TCanvas("flux_canvas", "flux_canvas",800,600);
    TH1F*  FluxH= (TH1F*) fluxfile->Get("tagged_flux");
    FluxH->Draw(); 
    char flux_macro_name[100];
    sprintf(flux_macro_name,"flux_numbers_%s.C",version);
    FluxH->SaveAs(flux_macro_name);
    char flux_plot_name[100];
   sprintf(flux_plot_name,"xsec_flux_%s.png",version);
    flux_canvas->Print(flux_plot_name);
*/

    TFile* thrownfile = TFile::Open(thrownFilePath1);
    TCanvas * thrown_canvas = new TCanvas("thrown_canvas", "thrown_canvas",800,600);
    thrown_canvas->cd();
    thrownfile->cd(); 
    TH2F*  ThrownH= (TH2F*) thrownfile->Get("Egamma_t");
    ThrownH->GetXaxis()->SetRangeUser(minEval,maxEval);	
    ThrownH->GetYaxis()->SetRangeUser(mintval,maxtval);
    ThrownH->RebinX(ThrownH->GetNbinsX()/numEBins);    
    ThrownH->RebinY(ThrownH->GetNbinsY()/numtBins);
    ThrownH->Draw("colz");
    char thrown_numbers_macro_name[100];
    char thrown_numbers_plot_name[100];
    sprintf(thrown_numbers_macro_name,"thrown_numbers_%s.C",version);
    sprintf(thrown_numbers_plot_name, "xsec_thrown_%s.png",version);
    ThrownH->SaveAs(thrown_numbers_macro_name);
    thrown_canvas->Print(thrown_numbers_plot_name);


/* DONE
    TCanvas * sigyields_canvas = new TCanvas("sigyields_canvas", "sigyields_canvas",1200,900);
    sigyields_canvas->Divide(4,3,canvas_margins,canvas_margins);
    char sigyields_EBin_name[100];
    char EBin_Title[100];

    TCanvas * mcyields_canvas = new TCanvas("mcyields_canvas", "mcyields_canvas",1200,900);
    mcyields_canvas->Divide(4,3,canvas_margins,canvas_margins);
    char mcyields_EBin_name[100];

   TH3F * XiMassKinFit_Egamma_t = (TH3F*)datafile->Get("Xi_Egamma_t");
   TH3F * XiMassKinFit_Egamma_t_acc = (TH3F*)datafile->Get("Xi_Egamma_t_acc");
   TH3F * XiMassKinFit_Egamma_t_accsub = (TH3F *) XiMassKinFit_Egamma_t->Clone("XiMassKinFit_Egamma_t_accsub");
   XiMassKinFit_Egamma_t_accsub->Add(XiMassKinFit_Egamma_t_acc,-0.5);

   TH3F * MC_XiMassKinFit_Egamma_t = (TH3F*)mcfile->Get("Xi_Egamma_t");
   TH3F * MC_XiMassKinFit_Egamma_t_acc = (TH3F*)mcfile->Get("Xi_Egamma_t_acc");
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

	mcyields_canvas->cd(iE+1);
	int MC_Ebinmin = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emin);
	int MC_Ebinmax = MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->FindBin(Emax) -1.;
	MC_XiMassKinFit_Egamma_t_accsub->GetYaxis()->SetRange(MC_Ebinmin,MC_Ebinmax);
	TH2F * MC_XiMassKinFit_Ebin_t_accsub = (TH2F *) MC_XiMassKinFit_Egamma_t_accsub->Project3D("xz");
	sprintf(mcyields_EBin_name,"mcyields_%03d",Ebuffer);
    	MCYields[iE+1] = new TH1F(mcyields_EBin_name, "; -t (GeV^2); Yields",numtBins,mintval,maxtval); 
	sprintf(EBin_Title,"%3.1f <= E_{#gamma} < %3.1f",Emin,Emax);
	MCYields[iE+1]->SetTitle(EBin_Title);
    	MCYields[iE+1]->SetMarkerColor(kRed);
    	MCYields[iE+1]->SetMarkerStyle(21);
    	MCYields[iE+1]->SetLabelSize(0.035,"xy");
    	MCYields[iE+1]->SetLabelOffset(0.001,"xy");

	for(int it =0; it<numtBins; it++){
		double tmin = deltat * it + mintval;
		double tmax = deltat * (it+1) +mintval;
		int tbuffer = tmin*10;
		int tbinmin = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int tbinmax = XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(tbinmin,tbinmax);
		TH1F * XiMassKinFit_Ebin_tbin_accsub = (TH1F *) XiMassKinFit_Ebin_t_accsub->ProjectionY("XiMassKinFit_Ebin_tbin_accsub",tbinmin,tbinmax);

		int MC_tbinmin = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmin);
		int MC_tbinmax = MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->FindBin(tmax) -1.;
		MC_XiMassKinFit_Ebin_t_accsub->GetXaxis()->SetRange(MC_tbinmin,MC_tbinmax);
		TH1F * MC_XiMassKinFit_Ebin_tbin_accsub = (TH1F *) MC_XiMassKinFit_Ebin_t_accsub->ProjectionY("MC_XiMassKinFit_Ebin_tbin_accsub",MC_tbinmin,MC_tbinmax); 

		sprintf(workspace,"w%03d_%03d",Ebuffer,tbuffer);
        	sprintf(canvas,"Xi_canvas_%03d_%03d",Ebuffer,tbuffer);
        	sprintf(plot,"diffxsec_sigfit_%s_%03d_%03d.png",version, Ebuffer,tbuffer);
       
		 sprintf(mcworkspace,"wmc%03d_%03d",Ebuffer,tbuffer);
		sprintf(mccanvas,"Xi_canvas_mc_%03d_%03d",Ebuffer,tbuffer);
        	sprintf(mcplot,"diffxsec_mcfit_%s_%03d_%03d.png",version, Ebuffer,tbuffer);
       
		RooWorkspace* w = new RooWorkspace(workspace);
        	TCanvas * Xi_canvas = new TCanvas(canvas, canvas,800,600);
        	RooRealVar mass("mass", "mass", 1.2, 1.5);
        	RooDataHist *data = new RooDataHist("data", "Dataset of mass", mass, XiMassKinFit_Ebin_tbin_accsub);
        	XiMassKinFit_Ebin_tbin_accsub->Print();
        	w->import(RooArgSet(mass));
        	w->factory("Chebychev::bkgd(mass,{c1[2.20,-1.e4,1.e4],c2[-1.557,-1.e4,1.e4]})");
        	w->factory("Gaussian::gaus(mass,mean[1.32,1.31,1.33],sigma[0.005,0.001,0.01])");
        	w->factory("SUM::model(nbkgd[150,0,1e5]*bkgd, nsig[20,0,1e3]*gaus)");
        	w->pdf("model")->fitTo(*data,RooFit::Range(1.27,1.5),RooFit::Minos(1));
        	RooPlot* massframe = mass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        	massframe->SetMaximum(75);
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
		cout << "~~~~~~~sig~" << iE << "~" << it << " " << sig_events << " " << sig_events_err << endl; 
		double max_y = sig_events*0.3;
		massframe->SetMaximum(max_y);
        	massframe->Draw();
	     	Xi_canvas->Print(plot);

       		RooWorkspace* wmc = new RooWorkspace(mcworkspace);
        	TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
        	RooRealVar mcmass("mcmass", "mcmass", 1.2, 1.5);
        	RooDataHist *mc = new RooDataHist("mc", "MC of mass", mcmass, MC_XiMassKinFit_Ebin_tbin_accsub );
        	MC_XiMassKinFit_Ebin_tbin_accsub->Print();
        	wmc->import(RooArgSet(mcmass));
        	wmc->factory("Gaussian::gausmc(mcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
        	wmc->factory("SUM::mcmodel(nsigmc[50,0,1e6]*gausmc)");
        	wmc->pdf("mcmodel")->fitTo(*mc,RooFit::Range(1.305,1.35),RooFit::Minos(1));
        	RooPlot* mcmassframe = mcmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
        	mcmassframe->SetMaximum(2000);
        	mcmassframe->SetXTitle("#Lambda#pi^{-} mass");
        	mc->plotOn(mcmassframe) ;
        	wmc->pdf("mcmodel")->paramOn(mcmassframe);
       	 	wmc->pdf("mcmodel")->plotOn(mcmassframe);
        	wmc->pdf("gausmc")->plotOn(mcmassframe, RooFit::LineStyle(kDotted),
 			RooFit::Normalization(wmc->var("nsigmc")->getVal(), RooAbsReal::NumEvent));
        	double_t mc_sig_events = wmc->var("nsigmc")->getVal();
		double_t mc_sig_events_err = wmc->var("nsigmc")->getError();
		cout << "~~~~~~~MC~" << iE << "~" << it << " " << mc_sig_events << " " << mc_sig_events_err << endl; 
		double mc_max_y = mc_sig_events *0.3;
		mcmassframe->SetMaximum(mc_max_y);
        	mcmassframe->Draw();
	     	Xi_mc_canvas->Print(mcplot);

		SignalYields[iE+1]->SetBinContent(it+1,sig_events);
		SignalYields[iE+1]->SetBinError(it+1,sig_events_err);
		MCYields[iE+1]->SetBinContent(it+1,mc_sig_events);
		MCYields[iE+1]->SetBinError(it+1,mc_sig_events_err);

	}
	sigyields_canvas->cd(iE+1);
	SignalYields[iE+1]->GetYaxis()->SetRangeUser(0,650);
	SignalYields[iE+1]->Draw("pe1");
	sigyields_canvas->Print("SignalYields_test.png");
	sigyields_canvas->SaveAs("SignalYields_test.C");
	mcyields_canvas->cd(iE+1);
	MCYields[iE+1]->GetYaxis()->SetRangeUser(0,1750);
	MCYields[iE+1]->Draw("pe1");
	mcyields_canvas->Print("MCYields_test.png");
	mcyields_canvas->SaveAs("MCYields_test.C");
	
   }
*/
/*
    TH1F * eff = new TH1F("eff", "Efficiency; E_{#gamma}; Efficiency (%)",numtBins,minEval,maxEval);
    TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",800,600);
    eff->SetMarkerColor(kRed);
    eff->SetMarkerStyle(21);
    eff->SetLabelSize(0.035,"xy");
    eff->SetLabelOffset(0.001,"xy");
    eff->GetYaxis()->SetRangeUser(0,3);

	cout << "~~~~~~~E~ " << i << " " << Emin << " " << Emax << " " << buffer << endl;
        flux=getbincontent(FluxH,i+1);
        flux_err=getbinerror(FluxH,i+1); //+1 because 0 is the underflow, +5 because of binning
	cout << "~~~~~~~flux~ " << i << " " << flux << " " << flux_err << endl;
        tagged=getbincontent(thrown_hist,i+1);
        tagged_err=getbinerror(thrown_hist,i+1);
	cout << "~~~~~~~thrown~ " << i << " " << tagged << " " << tagged_err << endl; 
        
	efficiency[i]= mc_sig_events / tagged; 
	eff_err[i] = efficiency[i]*sqrt(pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

       cout << "~~~~~~~~~fit~mc~efficiency~" << i << " " << mc_sig_events << " " << tagged << " " << efficiency[i] << " " << eff_err[i] << endl;

        xsec_val[i] = (sig_events)/(constant * flux * mc_sig_events / tagged);
	xsec_err[i] = xsec_val[i]*sqrt(pow(sig_events_err/sig_events,2)+pow(flux_err/flux,2)+pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

	cout << "~~~~~~~fit~xsec~ " << i << " " << xsec_val[i] << " " << xsec_err[i] << endl;

 	xsec_canvas->cd();
	xsec->SetBinContent(i, xsec_val[i]);
	xsec->SetBinError(i, xsec_err[i]);

	eff_canvas->cd();
	eff->SetBinContent(i+1,  efficiency[i]*100.);
	eff->SetBinError(i+1,eff_err[i]*100.);
  }
  	xsec_canvas->cd();
        xsec->Draw("PE1");
	sprintf(xsecplot,"xsec_fit_%s.png",version );
	sprintf(xsecplotC,"xsec_fit_%s.C",version );
	xsec_canvas->Print(xsecplot);
	xsec->SaveAs(xsecplotC);
	eff_canvas->cd();	
	eff->Draw("PE1");
	char efficiency_hist_numbers[100];
       sprintf(efficiency_hist_numbers,"efficiency_hist_%s.C",version);
	eff->SaveAs(efficiency_hist_numbers);
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
