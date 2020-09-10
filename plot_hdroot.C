#include <cstdlib>

void plot_hdroot() {
	TFile * file = TFile::Open("~/2020xsec_workfest/hd_root_051582.root");

	gStyle->SetOptStat(0000);
	gStyle->SetTitleSize(0.3);

	char TOFqplusname[100];
	TCanvas *ccTOFqplus = new TCanvas("ccTOFqplus", "ccTOFqplus", 800, 600);
	TH2I * TOFqplus = (TH2I*)file->Get("Independent/Hist_DetectorPID/TOF/BetaVsP_q+");
	TOFqplus->GetYaxis()->SetRangeUser(0.2,1.2);
	ccTOFqplus->SetLogz();
	TOFqplus->Draw("colz");
	sprintf(TOFqplusname, "TOF_qPlus_tracks.png");
	ccTOFqplus->Print(TOFqplusname);

	char TOFqminusname[100];
	TCanvas *ccTOFqminus = new TCanvas("ccTOFqminus", "ccTOFqminus", 800, 600);
	TH2I * TOFqminus = (TH2I*)file->Get("Independent/Hist_DetectorPID/TOF/BetaVsP_q-");
	TOFqminus->GetYaxis()->SetRangeUser(0.2,1.2);
	ccTOFqminus->SetLogz();
	TOFqminus->Draw("colz");
	sprintf(TOFqminusname, "TOF_qminus_tracks.png");
	ccTOFqminus->Print(TOFqminusname);

	char TOFKplusname[100];
	TCanvas *ccTOFKplus = new TCanvas("ccTOFKplus", "ccTOFKplus", 800, 600);
	TH2I * TOFKplus = (TH2I*)file->Get("Independent/Hist_DetectorPID/TOF/DeltaTVsP_K+");
	ccTOFKplus->SetLogz();
	TOFKplus->Draw("colz");
	sprintf(TOFKplusname, "TOF_Kplus_tracks.png");
	ccTOFKplus->Print(TOFKplusname);

	char CDCqplusname[100];
	TCanvas *ccCDCqplus = new TCanvas("ccCDCqplus", "ccCDCqplus", 800, 600);
	TH2I * CDCqplus = (TH2I*)file->Get("Independent/Hist_DetectorPID/CDC/dEdXVsP_Int_q+");
	CDCqplus->GetYaxis()->SetRangeUser(0,12);
	CDCqplus->GetZaxis()->SetRangeUser(0,150e3);
	CDCqplus->GetYaxis()->SetTitle("CDC dE/dx (keV/cm)");
	CDCqplus->Draw("colz");
	sprintf(CDCqplusname, "CDC_qplus_tracks.png");
	ccCDCqplus->Print(CDCqplusname);

	cout << "RAND_MAX: " << RAND_MAX << endl; 
	int randomnum = rand(); // Returns a random number between 0 and RAND_MAX
	int helicity = (randomnum % 2);
	cout << "RNG: " << randomnum << " helicity: " << helicity << endl;


}