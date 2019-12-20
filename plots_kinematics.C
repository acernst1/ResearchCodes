void plots_kinematics() {

	TFile *file1 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2017-01_347runs_dec19.root");
	TFile *file2 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-01_543runs_dec19.root");
	TFile *file3 = TFile::Open("/cache/halld/home/acernst/data/kpkpxim__B4_M23_allbatches_2018-08_449runs_dec19.root");
	TFile *file1MC = TFile::Open("/cache/halld/home/acernst/MC/2017-01_ANAver20/kpkpxim__B4_M23_2017-01_ANAver20_dec19.root");


	gStyle->SetOptStat(0000);

	char XiKptheta17name[100];
	TCanvas *ccXiKptheta17 = new TCanvas("ccXiKptheta17", "ccXiKptheta17", 800, 600);
	TH2I * XiKptheta17 = (TH2I*)file1->Get("K_pTheta_Measured");	
	TH2I * XiKptheta17_acc = (TH2I*)file1->Get("K_pTheta_Measured_acc");
	TH2I *XiKptheta17_accsub = (TH2I *) XiKptheta17->Clone("XiKptheta17_accsub");
	XiKptheta17_accsub->Add(XiKptheta17_acc,-0.5);
        XiKptheta17_accsub->Draw("colz");
	sprintf(XiKptheta17name, "XiKptheta_2017-01_ANAver20.png");
	ccXiKptheta17->Print(XiKptheta17name);

	char Xipiptheta17name[100];
	TCanvas *ccXipiptheta17 = new TCanvas("ccXipiptheta17", "ccXipiptheta17", 800, 600);
	TH2I * Xipiptheta17 = (TH2I*)file1->Get("pi_pTheta_Measured");	
	TH2I * Xipiptheta17_acc = (TH2I*)file1->Get("pi_pTheta_Measured_acc");
	TH2I *Xipiptheta17_accsub = (TH2I *) Xipiptheta17->Clone("Xipiptheta17_accsub");
	Xipiptheta17_accsub->Add(Xipiptheta17_acc,-0.5);
        Xipiptheta17_accsub->Draw("colz");
	sprintf(Xipiptheta17name, "Xipiptheta_2017-01_ANAver20.png");
	ccXipiptheta17->Print(Xipiptheta17name);

	char Xipptheta17name[100];
	TCanvas *ccXipptheta17 = new TCanvas("ccXipptheta17", "ccXipptheta17", 800, 600);
	TH2I * Xipptheta17 = (TH2I*)file1->Get("p_pTheta_Measured");	
	TH2I * Xipptheta17_acc = (TH2I*)file1->Get("p_pTheta_Measured_acc");
	TH2I *Xipptheta17_accsub = (TH2I *) Xipptheta17->Clone("Xipptheta17_accsub");
	Xipptheta17_accsub->Add(Xipptheta17_acc,-0.5);
        Xipptheta17_accsub->Draw("colz");
	sprintf(Xipptheta17name, "Xipptheta_2017-01_ANAver20.png");
	ccXipptheta17->Print(Xipptheta17name);

	char XiKptheta17KinFitname[100];
	TCanvas *ccXiKptheta17KinFit = new TCanvas("ccXiKptheta17KinFit", "ccXiKptheta17KinFit", 800, 600);
	TH2I * XiKptheta17KinFit = (TH2I*)file1->Get("K_pTheta_KinFit");	
	TH2I * XiKptheta17KinFit_acc = (TH2I*)file1->Get("K_pTheta_KinFit_acc");
	TH2I *XiKptheta17KinFit_accsub = (TH2I *) XiKptheta17KinFit->Clone("XiKptheta17KinFit_accsub");
	XiKptheta17KinFit_accsub->Add(XiKptheta17KinFit_acc,-0.5);
        XiKptheta17KinFit_accsub->Draw("colz");
	sprintf(XiKptheta17KinFitname, "XiKpthetaKinFit_2017-01_ANAver20.png");
	ccXiKptheta17KinFit->Print(XiKptheta17KinFitname);

	char Xipiptheta17KinFitname[100];
	TCanvas *ccXipiptheta17KinFit = new TCanvas("ccXipiptheta17KinFit", "ccXipiptheta17KinFit", 800, 600);
	TH2I * Xipiptheta17KinFit = (TH2I*)file1->Get("pi_pTheta_KinFit");	
	TH2I * Xipiptheta17KinFit_acc = (TH2I*)file1->Get("pi_pTheta_KinFit_acc");
	TH2I *Xipiptheta17KinFit_accsub = (TH2I *) Xipiptheta17KinFit->Clone("Xipiptheta17KinFit_accsub");
	Xipiptheta17KinFit_accsub->Add(Xipiptheta17KinFit_acc,-0.5);
        Xipiptheta17KinFit_accsub->Draw("colz");
	sprintf(Xipiptheta17KinFitname, "XipipthetaKinFit_2017-01_ANAver20.png");
	ccXipiptheta17KinFit->Print(Xipiptheta17KinFitname);

	char Xipptheta17KinFitname[100];
	TCanvas *ccXipptheta17KinFit = new TCanvas("ccXipptheta17KinFit", "ccXipptheta17KinFit", 800, 600);
	TH2I * Xipptheta17KinFit = (TH2I*)file1->Get("p_pTheta_KinFit");	
	TH2I * Xipptheta17KinFit_acc = (TH2I*)file1->Get("p_pTheta_KinFit_acc");
	TH2I *Xipptheta17KinFit_accsub = (TH2I *) Xipptheta17KinFit->Clone("Xipptheta17KinFit_accsub");
	Xipptheta17KinFit_accsub->Add(Xipptheta17KinFit_acc,-0.5);
        Xipptheta17KinFit_accsub->Draw("colz");
	sprintf(Xipptheta17KinFitname, "XippthetaKinFit_2017-01_ANAver20.png");
	ccXipptheta17KinFit->Print(Xipptheta17KinFitname);

	char XiKptheta181name[100];
	TCanvas *ccXiKptheta181 = new TCanvas("ccXiKptheta181", "ccXiKptheta181", 800, 600);
	TH2I * XiKptheta181 = (TH2I*)file2->Get("K_pTheta_Measured");	
	TH2I * XiKptheta181_acc = (TH2I*)file2->Get("K_pTheta_Measured_acc");
	TH2I *XiKptheta181_accsub = (TH2I *) XiKptheta181->Clone("XiKptheta181_accsub");
	XiKptheta181_accsub->Add(XiKptheta181_acc,-0.5);
        XiKptheta181_accsub->Draw("colz");
	sprintf(XiKptheta181name, "XiKptheta_2018-01_ANAver03.png");
	ccXiKptheta181->Print(XiKptheta181name);

	char Xipiptheta181name[100];
	TCanvas *ccXipiptheta181 = new TCanvas("ccXipiptheta181", "ccXipiptheta181", 800, 600);
	TH2I * Xipiptheta181 = (TH2I*)file2->Get("pi_pTheta_Measured");	
	TH2I * Xipiptheta181_acc = (TH2I*)file2->Get("pi_pTheta_Measured_acc");
	TH2I *Xipiptheta181_accsub = (TH2I *) Xipiptheta181->Clone("Xipiptheta181_accsub");
	Xipiptheta181_accsub->Add(Xipiptheta181_acc,-0.5);
        Xipiptheta181_accsub->Draw("colz");
	sprintf(Xipiptheta181name, "Xipiptheta_2018-01_ANAver03.png");
	ccXipiptheta181->Print(Xipiptheta181name);

	char Xipptheta181name[100];
	TCanvas *ccXipptheta181 = new TCanvas("ccXipptheta181", "ccXipptheta181", 800, 600);
	TH2I * Xipptheta181 = (TH2I*)file2->Get("p_pTheta_Measured");	
	TH2I * Xipptheta181_acc = (TH2I*)file2->Get("p_pTheta_Measured_acc");
	TH2I *Xipptheta181_accsub = (TH2I *) Xipptheta181->Clone("Xipptheta181_accsub");
	Xipptheta181_accsub->Add(Xipptheta181_acc,-0.5);
        Xipptheta181_accsub->Draw("colz");
	sprintf(Xipptheta181name, "Xipptheta_2018-01_ANAver03.png");
	ccXipptheta181->Print(Xipptheta181name);

	char XiKptheta181KinFitname[100];
	TCanvas *ccXiKptheta181KinFit = new TCanvas("ccXiKptheta181KinFit", "ccXiKptheta181KinFit", 800, 600);
	TH2I * XiKptheta181KinFit = (TH2I*)file2->Get("K_pTheta_KinFit");	
	TH2I * XiKptheta181KinFit_acc = (TH2I*)file2->Get("K_pTheta_KinFit_acc");
	TH2I *XiKptheta181KinFit_accsub = (TH2I *) XiKptheta181KinFit->Clone("XiKptheta181KinFit_accsub");
	XiKptheta181KinFit_accsub->Add(XiKptheta181KinFit_acc,-0.5);
        XiKptheta181KinFit_accsub->Draw("colz");
	sprintf(XiKptheta181KinFitname, "XiKpthetaKinFit_2018-01_ANAver03.png");
	ccXiKptheta181KinFit->Print(XiKptheta181KinFitname);

	char Xipiptheta181KinFitname[100];
	TCanvas *ccXipiptheta181KinFit = new TCanvas("ccXipiptheta181KinFit", "ccXipiptheta181KinFit", 800, 600);
	TH2I * Xipiptheta181KinFit = (TH2I*)file2->Get("pi_pTheta_KinFit");	
	TH2I * Xipiptheta181KinFit_acc = (TH2I*)file2->Get("pi_pTheta_KinFit_acc");
	TH2I *Xipiptheta181KinFit_accsub = (TH2I *) Xipiptheta181KinFit->Clone("Xipiptheta181KinFit_accsub");
	Xipiptheta181KinFit_accsub->Add(Xipiptheta181KinFit_acc,-0.5);
        Xipiptheta181KinFit_accsub->Draw("colz");
	sprintf(Xipiptheta181KinFitname, "XipipthetaKinFit_2018-01_ANAver03.png");
	ccXipiptheta181KinFit->Print(Xipiptheta181KinFitname);

	char Xipptheta181KinFitname[100];
	TCanvas *ccXipptheta181KinFit = new TCanvas("ccXipptheta181KinFit", "ccXipptheta181KinFit", 800, 600);
	TH2I * Xipptheta181KinFit = (TH2I*)file2->Get("p_pTheta_KinFit");	
	TH2I * Xipptheta181KinFit_acc = (TH2I*)file2->Get("p_pTheta_KinFit_acc");
	TH2I *Xipptheta181KinFit_accsub = (TH2I *) Xipptheta181KinFit->Clone("Xipptheta181KinFit_accsub");
	Xipptheta181KinFit_accsub->Add(Xipptheta181KinFit_acc,-0.5);
        Xipptheta181KinFit_accsub->Draw("colz");
	sprintf(Xipptheta181KinFitname, "XippthetaKinFit_2018-01_ANAver03.png");
	ccXipptheta181KinFit->Print(Xipptheta181KinFitname);


	char XiKptheta188name[100];
	TCanvas *ccXiKptheta188 = new TCanvas("ccXiKptheta188", "ccXiKptheta188", 800, 600);
	TH2I * XiKptheta188 = (TH2I*)file3->Get("K_pTheta_Measured");	
	TH2I * XiKptheta188_acc = (TH2I*)file3->Get("K_pTheta_Measured_acc");
	TH2I *XiKptheta188_accsub = (TH2I *) XiKptheta188->Clone("XiKptheta188_accsub");
	XiKptheta188_accsub->Add(XiKptheta188_acc,-0.5);
        XiKptheta188_accsub->Draw("colz");
	sprintf(XiKptheta188name, "XiKptheta_2018-08_ANAver02.png");
	ccXiKptheta188->Print(XiKptheta188name);

	char Xipiptheta188name[100];
	TCanvas *ccXipiptheta188 = new TCanvas("ccXipiptheta188", "ccXipiptheta188", 800, 600);
	TH2I * Xipiptheta188 = (TH2I*)file3->Get("pi_pTheta_Measured");	
	TH2I * Xipiptheta188_acc = (TH2I*)file3->Get("pi_pTheta_Measured_acc");
	TH2I *Xipiptheta188_accsub = (TH2I *) Xipiptheta188->Clone("Xipiptheta188_accsub");
	Xipiptheta188_accsub->Add(Xipiptheta188_acc,-0.5);
        Xipiptheta188_accsub->Draw("colz");
	sprintf(Xipiptheta188name, "Xipiptheta_2018-08_ANAver02.png");
	ccXipiptheta188->Print(Xipiptheta188name);

	char Xipptheta188name[100];
	TCanvas *ccXipptheta188 = new TCanvas("ccXipptheta188", "ccXipptheta188", 800, 600);
	TH2I * Xipptheta188 = (TH2I*)file3->Get("p_pTheta_Measured");	
	TH2I * Xipptheta188_acc = (TH2I*)file3->Get("p_pTheta_Measured_acc");
	TH2I *Xipptheta188_accsub = (TH2I *) Xipptheta188->Clone("Xipptheta188_accsub");
	Xipptheta188_accsub->Add(Xipptheta188_acc,-0.5);
        Xipptheta188_accsub->Draw("colz");
	sprintf(Xipptheta188name, "Xipptheta_2018-08_ANAver02.png");
	ccXipptheta188->Print(Xipptheta188name);

	char XiKptheta188KinFitname[100];
	TCanvas *ccXiKptheta188KinFit = new TCanvas("ccXiKptheta188KinFit", "ccXiKptheta188KinFit", 800, 600);
	TH2I * XiKptheta188KinFit = (TH2I*)file3->Get("K_pTheta_KinFit");	
	TH2I * XiKptheta188KinFit_acc = (TH2I*)file3->Get("K_pTheta_KinFit_acc");
	TH2I *XiKptheta188KinFit_accsub = (TH2I *) XiKptheta188KinFit->Clone("XiKptheta188KinFit_accsub");
	XiKptheta188KinFit_accsub->Add(XiKptheta188KinFit_acc,-0.5);
        XiKptheta188KinFit_accsub->Draw("colz");
	sprintf(XiKptheta188KinFitname, "XiKpthetaKinFit_2018-08_ANAver02.png");
	ccXiKptheta188KinFit->Print(XiKptheta188KinFitname);

	char Xipiptheta188KinFitname[100];
	TCanvas *ccXipiptheta188KinFit = new TCanvas("ccXipiptheta188KinFit", "ccXipiptheta188KinFit", 800, 600);
	TH2I * Xipiptheta188KinFit = (TH2I*)file3->Get("pi_pTheta_KinFit");	
	TH2I * Xipiptheta188KinFit_acc = (TH2I*)file3->Get("pi_pTheta_KinFit_acc");
	TH2I *Xipiptheta188KinFit_accsub = (TH2I *) Xipiptheta188KinFit->Clone("Xipiptheta188KinFit_accsub");
	Xipiptheta188KinFit_accsub->Add(Xipiptheta188KinFit_acc,-0.5);
        Xipiptheta188KinFit_accsub->Draw("colz");
	sprintf(Xipiptheta188KinFitname, "XipipthetaKinFit_2018-08_ANAver02.png");
	ccXipiptheta188KinFit->Print(Xipiptheta188KinFitname);

	char Xipptheta188KinFitname[100];
	TCanvas *ccXipptheta188KinFit = new TCanvas("ccXipptheta188KinFit", "ccXipptheta188KinFit", 800, 600);
	TH2I * Xipptheta188KinFit = (TH2I*)file3->Get("p_pTheta_KinFit");	
	TH2I * Xipptheta188KinFit_acc = (TH2I*)file3->Get("p_pTheta_KinFit_acc");
	TH2I *Xipptheta188KinFit_accsub = (TH2I *) Xipptheta188KinFit->Clone("Xipptheta188KinFit_accsub");
	Xipptheta188KinFit_accsub->Add(Xipptheta188KinFit_acc,-0.5);
        Xipptheta188KinFit_accsub->Draw("colz");
	sprintf(Xipptheta188KinFitname, "XippthetaKinFit_2018-08_ANAver02.png");
	ccXipptheta188KinFit->Print(Xipptheta188KinFitname);

	char XiMassMeasured17name[100];
	TCanvas *ccXiMassMeasured17 = new TCanvas("ccXiMassMeasured17", "ccXiMassMeasured17", 800, 600);
	TH1I * XiMassMeasured17 = (TH1I*)file1->Get("XiMass");	
	TH1I * XiMassMeasured17_acc = (TH1I*)file1->Get("XiMass_acc");
	XiMassMeasured17->RebinX(5);
	TH1I *XiMassMeasured17_accsub = (TH1I *) XiMassMeasured17->Clone("XiMassMeasured17_accsub");
	XiMassMeasured17_accsub->Add(XiMassMeasured17_acc,-0.5);
	TH1I * XiMass17KinFit = (TH1I*)file1->Get("XiMass_KinFit");
	TH1I * XiMass17KinFit_acc = (TH1I*)file1->Get("XiMass_KinFit_acc");
	TH1I *XiMass17KinFit_accsub = (TH1I *) XiMass17KinFit->Clone("XiMass17KinFit_accsub");
	XiMass17KinFit_accsub->Add(XiMass17KinFit_acc,-0.5);
	XiMass17KinFit_accsub->RebinX(5);
	XiMassMeasured17_accsub->SetLineColor(kRed);
	XiMassMeasured17_accsub->SetMarkerStyle(21);
	XiMassMeasured17_accsub->SetMarkerColor(kRed);
	XiMassMeasured17_accsub->SetMarkerSize(0.8);
	XiMass17KinFit_accsub->SetMarkerStyle(21);
	XiMass17KinFit_accsub->SetMarkerColor(kBlue);
	XiMass17KinFit_accsub->SetMarkerSize(0.8);
        XiMassMeasured17_accsub->Draw("");
        XiMass17KinFit_accsub->Draw("same");
	auto legend = new TLegend(0.70,0.8,0.98,0.93);
	legend->AddEntry(XiMassMeasured17_accsub,"Measured P4","lep");
	legend->AddEntry(XiMass17KinFit_accsub,"KinFit P4","lep");
	legend->Draw();
	sprintf(XiMassMeasured17name, "XiMass_2017-01_ANAver20.png");
	ccXiMassMeasured17->Print(XiMassMeasured17name);

	char XiMassMeasured181name[100];
	TCanvas *ccXiMassMeasured181 = new TCanvas("ccXiMassMeasured181", "ccXiMassMeasured181", 800, 600);
	TH1I * XiMassMeasured181 = (TH1I*)file2->Get("XiMass");	
	TH1I * XiMassMeasured181_acc = (TH1I*)file2->Get("XiMass_acc");
	XiMassMeasured181->RebinX(5);
	TH1I *XiMassMeasured181_accsub = (TH1I *) XiMassMeasured181->Clone("XiMassMeasured181_accsub");
	XiMassMeasured181_accsub->Add(XiMassMeasured181_acc,-0.5);
	TH1I * XiMass181KinFit = (TH1I*)file2->Get("XiMass_KinFit");
	TH1I * XiMass181KinFit_acc = (TH1I*)file2->Get("XiMass_KinFit_acc");
	TH1I *XiMass181KinFit_accsub = (TH1I *) XiMass181KinFit->Clone("XiMass181KinFit_accsub");
	XiMass181KinFit_accsub->Add(XiMass181KinFit_acc,-0.5);
	XiMass181KinFit_accsub->RebinX(5);
	XiMassMeasured181_accsub->SetLineColor(kRed);
	XiMassMeasured181_accsub->SetMarkerStyle(21);
	XiMassMeasured181_accsub->SetMarkerColor(kRed);
	XiMassMeasured181_accsub->SetMarkerSize(0.8);
	XiMass181KinFit_accsub->SetMarkerStyle(21);
	XiMass181KinFit_accsub->SetMarkerColor(kBlue);
	XiMass181KinFit_accsub->SetMarkerSize(0.8);
        XiMassMeasured181_accsub->Draw("");
        XiMass181KinFit_accsub->Draw("same");
	legend->Draw();
	sprintf(XiMassMeasured181name, "XiMass_2018-01_ANAver03.png");
	ccXiMassMeasured181->Print(XiMassMeasured181name);

	char XiMassMeasured188name[100];
	TCanvas *ccXiMassMeasured188 = new TCanvas("ccXiMassMeasured188", "ccXiMassMeasured188", 800, 600);
	TH1I * XiMassMeasured188 = (TH1I*)file3->Get("XiMass");	
	TH1I * XiMassMeasured188_acc = (TH1I*)file3->Get("XiMass_acc");
	XiMassMeasured188->RebinX(5);
	TH1I *XiMassMeasured188_accsub = (TH1I *) XiMassMeasured188->Clone("XiMassMeasured188_accsub");
	XiMassMeasured188_accsub->Add(XiMassMeasured188_acc,-0.5);
	TH1I * XiMass188KinFit = (TH1I*)file3->Get("XiMass_KinFit");
	TH1I * XiMass188KinFit_acc = (TH1I*)file3->Get("XiMass_KinFit_acc");
	TH1I *XiMass188KinFit_accsub = (TH1I *) XiMass188KinFit->Clone("XiMass188KinFit_accsub");
	XiMass188KinFit_accsub->Add(XiMass188KinFit_acc,-0.5);
	XiMass188KinFit_accsub->RebinX(5);
	XiMassMeasured188_accsub->SetLineColor(kRed);
	XiMassMeasured188_accsub->SetMarkerStyle(21);
	XiMassMeasured188_accsub->SetMarkerColor(kRed);
	XiMassMeasured188_accsub->SetMarkerSize(0.8);
	XiMass188KinFit_accsub->SetMarkerStyle(21);
	XiMass188KinFit_accsub->SetMarkerColor(kBlue);
	XiMass188KinFit_accsub->SetMarkerSize(0.8);
        XiMassMeasured188_accsub->Draw("");
        XiMass188KinFit_accsub->Draw("same");
	legend->Draw();
	sprintf(XiMassMeasured188name, "XiMass_2018-08_ANAver02.png");
	ccXiMassMeasured188->Print(XiMassMeasured188name);
/*
	char LambPathname[100];
	TCanvas *ccLambPath = new TCanvas("ccLambPath", "ccLambPath", 800, 600);
	TH1I * LambPath = (TH1I*)file1->Get("LambPathLength");	
	TH1I * LambPathPCK = (TH1I*)file1->Get("Hist_ParticleComboKinematics/Step2__Lambda_->_Pi-_Proton/LambdaPathLength");	
        LambPath->Draw("e");
	LambPath->SetLineColor(kRed);
	LambPath->SetMarkerStyle(21);
	LambPath->SetMarkerColor(kRed);
	LambPath->SetMarkerSize(0.8);
	LambPathPCK->SetMarkerStyle(21);
	LambPathPCK->SetMarkerColor(kBlue);
	LambPathPCK->SetMarkerSize(0.8);
	LambPathPCK->Draw("e,same");
	sprintf(LambPathname, "LambPath_2017-ver20.png");
	ccLambPath->Print(LambPathname);

	char XiVertZname[100];
	TCanvas *ccXiVertZ = new TCanvas("ccXiVertZ", "ccXiVertZ", 800, 600);
	TH1I * XiVertZ = (TH1I*)file1->Get("XiVert");	
	TH1I * XiVertZPCK = (TH1I*)file1->Get("Hist_ParticleComboKinematics/Step1__Xi-_->_Pi-_Lambda/StepVertexZ");	
        XiVertZ->Draw("e");
	XiVertZ->SetLineColor(kRed);
	XiVertZ->SetMarkerStyle(21);
	XiVertZ->SetMarkerColor(kRed);
	XiVertZ->SetMarkerSize(0.8);
	XiVertZPCK->SetMarkerStyle(21);
	XiVertZPCK->SetMarkerColor(kBlue);
	XiVertZPCK->SetMarkerSize(0.8);
	XiVertZPCK->Draw("e,same");
	sprintf(XiVertZname, "XiVertZ_2017-ver20.png");
	ccXiVertZ->Print(XiVertZname);

	char LambVertZname[100];
	TCanvas *ccLambVertZ = new TCanvas("ccLambVertZ", "ccLambVertZ", 800, 600);
	TH1I * LambVertZ = (TH1I*)file1->Get("LambVert");	
	TH1I * LambVertZPCK = (TH1I*)file1->Get("Hist_ParticleComboKinematics/Step2__Lambda_->_Pi-_Proton/StepVertexZ");	
        LambVertZ->Draw("e");
	LambVertZ->SetLineColor(kRed);
	LambVertZ->SetMarkerStyle(21);
	LambVertZ->SetMarkerColor(kRed);
	LambVertZ->SetMarkerSize(0.8);
	LambVertZPCK->SetMarkerStyle(21);
	LambVertZPCK->SetMarkerColor(kBlue);
	LambVertZPCK->SetMarkerSize(0.8);
	LambVertZPCK->Draw("e,same");
	legend->Draw();
	sprintf(LambVertZname, "LambVertZ_2017-ver20.png");
	ccLambVertZ->Print(LambVertZname);

	char ProdVertZname[100];
	TCanvas *ccProdVertZ = new TCanvas("ccProdVertZ", "ccProdVertZ", 800, 600);
	TH1I * ProdVertZ = (TH1I*)file1->Get("ProdVert");	
	TH1I * ProdVertZPCK = (TH1I*)file1->Get("Hist_ParticleComboKinematics/Step0__Photon_Proton_->_K+_K+_Xi-/StepVertexZ");	
        ProdVertZ->Draw("e");
	ProdVertZ->SetLineColor(kRed);
	ProdVertZ->SetMarkerStyle(21);
	ProdVertZ->SetMarkerColor(kRed);
	ProdVertZ->SetMarkerSize(0.8);
	ProdVertZPCK->SetMarkerStyle(21);
	ProdVertZPCK->SetMarkerColor(kBlue);
	ProdVertZPCK->SetMarkerSize(0.8);
	ProdVertZPCK->Draw("e,same");
	legend->Draw();
	sprintf(ProdVertZname, "ProdVertZ_2017-ver20.png");
	ccProdVertZ->Print(ProdVertZname);

Step0__Photon_Proton_->_K+_K+_Xi-
Step2__Lambda_->_Pi-_Proton
	char Xiname[100];
	TH1I * XiIM_KinFit = (TH1I*)file1->Get("kpkpxim__B4_M23/Hist_InvariantMass_Xi-_PostKinFit_KinFit/InvariantMass");	
	TH1I * XiIM_Measured = (TH1I*)file1->Get("kpkpxim__B4_M23/Hist_InvariantMass_Xi-_PostKinFit/InvariantMass");	
	TCanvas *cc2 = new TCanvas("cc2", "cc2", 800, 600);
	XiIM_Measured->RebinX(4);
        XiIM_Measured->Draw("e");
	XiIM_Measured->SetLineColor(kRed);
	XiIM_KinFit->RebinX(4);
        XiIM_KinFit->Draw("e,same");
	sprintf(Xiname, "Xim_%s.png",version);
	cc2->Print(Xiname);

	char XinameM18[100];
	TH1I * XiIMM18_KinFit = (TH1I*)file1->Get("kpkpxim__B4_M18_M23/Hist_InvariantMass_Xi-_PostKinFit_KinFit/InvariantMass");	
	TH1I * XiIMM18_Measured = (TH1I*)file1->Get("kpkpxim__B4_M18_M23/Hist_InvariantMass_Xi-_PostKinFit/InvariantMass");	
	TCanvas *cc2M18 = new TCanvas("cc2M18", "cc2", 800, 600);
	XiIMM18_Measured->RebinX(4);
        XiIMM18_Measured->Draw("e");
	XiIMM18_Measured->SetLineColor(kRed);
	XiIMM18_KinFit->RebinX(4);
        XiIMM18_KinFit->Draw("e,same");
	sprintf(XinameM18, "Xim_M18_%s.png",version);
	cc2M18->Print(XinameM18);

	char Lambname[100];
	TH1I * LambIM_Measured = (TH1I*)file1->Get("kpkpxim__B4_M23/Hist_InvariantMass_Lambda_PostKinFit/InvariantMass");	
	TCanvas *cc3 = new TCanvas("cc3", "cc3", 800, 600);
	LambIM_Measured->RebinX(4);
	LambIM_Measured->SetLineColor(kRed);
        LambIM_Measured->Draw("e");
	sprintf(Lambname, "Lamb_%s.png",version);
	cc3->Print(Lambname);

	char LambnameM18[100];
	TH1I * LambIMM18_KinFit = (TH1I*)file1->Get("kpkpxim__B4_M18_M23/Hist_InvariantMass_Lambda_PostKinFit_KinFit/InvariantMass");
	TH1I * LambIMM18_Measured = (TH1I*)file1->Get("kpkpxim__B4_M18_M23/Hist_InvariantMass_Lambda_PostKinFit/InvariantMass");	
	TCanvas *cc3M18 = new TCanvas("cc3M18", "cc3M18", 800, 600);
	LambIMM18_Measured->RebinX(4);
        LambIMM18_Measured->Draw("e");
	LambIMM18_Measured->SetLineColor(kRed);
	LambIMM18_KinFit->RebinX(4);
        LambIMM18_KinFit->Draw("e,same");
	sprintf(LambnameM18, "Lamb_M18_%s.png",version);
	cc3M18->Print(LambnameM18);

	char KPxname[100];
	TH2I * KPx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Px_VsPhi");	
	TCanvas *ccPx = new TCanvas("ccPx", "ccPx", 800, 600);
	KPx->RebinX(5);
	KPx->RebinY(5);
        KPx->Draw("colz");
	sprintf(KPxname, "Kp_Px_%s.png",version);
	ccPx->Print(KPxname);

	char KPxnameM18[100];
	TH2I * KPxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Px_VsPhi");	
	TCanvas *ccPxM18 = new TCanvas("ccPxM18", "ccPxM18", 800, 600);
	KPxM18->RebinX(5);
	KPxM18->RebinY(5);
        KPxM18->Draw("colz");
	sprintf(KPxnameM18, "Kp_Px_M18_%s.png",version);
	ccPxM18->Print(KPxnameM18);

	char KPyname[100];
	TH2I * KPy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Py_VsPhi");	
	TCanvas *ccPy = new TCanvas("ccPy", "ccPy", 800, 600);
	KPy->RebinX(5);
	KPy->RebinY(5);
        KPy->Draw("colz");
	sprintf(KPyname, "Kp_Py_%s.png",version);
	ccPy->Print(KPyname);

	char KPynameM18[100];
	TH2I * KPyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Py_VsPhi");	
	TCanvas *ccPyM18 = new TCanvas("ccPyM18", "ccPyM18", 800, 600);
	KPyM18->RebinX(5);
	KPyM18->RebinY(5);
        KPyM18->Draw("colz");
	sprintf(KPynameM18, "Kp_Py_M18_%s.png",version);
	ccPyM18->Print(KPynameM18);

	char KPzname[100];
	TH2I * KPz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Pz_VsPhi");	
	TCanvas *ccPz = new TCanvas("ccPz", "ccPz", 800, 600);
	KPz->RebinX(5);
	KPz->RebinY(5);
        KPz->Draw("colz");
	sprintf(KPzname, "Kp_Pz_%s.png",version);
	ccPz->Print(KPzname);

	char KPznameM18[100];
	TH2I * KPzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Pz_VsPhi");	
	TCanvas *ccPzM18 = new TCanvas("ccPzM18", "ccPzM18", 800, 600);
	KPzM18->RebinX(5);
	KPzM18->RebinY(5);
        KPzM18->Draw("colz");
	sprintf(KPznameM18, "Kp_Pz_M18_%s.png",version);
	ccPzM18->Print(KPznameM18);

	char KXxname[100];
	TH2I * KXx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xx_VsPhi");	
	TCanvas *ccXx = new TCanvas("ccXx", "ccXx", 800, 600);
	KXx->RebinX(5);
	KXx->RebinY(5);
        KXx->Draw("colz");
	sprintf(KXxname, "Kp_Xx_%s.png",version);
	ccXx->Print(KXxname);

	char KXxnameM18[100];
	TH2I * KXxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xx_VsPhi");	
	TCanvas *ccXxM18 = new TCanvas("ccXxM18", "ccXxM18", 800, 600);
	KXxM18->RebinX(5);
	KXxM18->RebinY(5);
        KXxM18->Draw("colz");
	sprintf(KXxnameM18, "Kp_Xx_M18_%s.png",version);
	ccXxM18->Print(KXxnameM18);

	char KXyname[100];
	TH2I * KXy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xy_VsPhi");	
	TCanvas *ccXy = new TCanvas("ccXy", "ccXy", 800, 600);
	KXy->RebinX(5);
	KXy->RebinY(5);
        KXy->Draw("colz");
	sprintf(KXyname, "Kp_Xy_%s.png",version);
	ccXy->Print(KXyname);

	char KXynameM18[100];
	TH2I * KXyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xy_VsPhi");	
	TCanvas *ccXyM18 = new TCanvas("ccXyM18", "ccXyM18", 800, 600);
	KXyM18->RebinX(5);
	KXyM18->RebinY(5);
        KXyM18->Draw("colz");
	sprintf(KXynameM18, "Kp_Xy_M18_%s.png",version);
	ccXyM18->Print(KXynameM18);


	char KXzname[100];
	TH2I * KXz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xz_VsPhi");	
	TCanvas *ccXz = new TCanvas("ccXz", "ccXz", 800, 600);
	KXz->RebinX(5);
	KXz->RebinY(5);
        KXz->Draw("colz");
	sprintf(KXzname, "Kp_Xz_%s.png",version);
	ccXz->Print(KXzname);

	char KXznameM18[100];
	TH2I * KXzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step0__Photon_Proton__K+_K+_Xi-/K+/Pull_Xz_VsPhi");	
	TCanvas *ccXzM18 = new TCanvas("ccXzM18", "ccXzM18", 800, 600);
	KXzM18->RebinX(5);
	KXzM18->RebinY(5);
        KXzM18->Draw("colz");
	sprintf(KXznameM18, "Kp_Xz_M18_%s.png",version);
	ccXzM18->Print(KXznameM18);

	char pixiPxname[100];
	TH2I * pixiPx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Px_VsPhi");	
	TCanvas *ccpixiPx = new TCanvas("ccpixiPx", "ccpixiPx", 800, 600);
	pixiPx->RebinX(5);
	pixiPx->RebinY(5);
        pixiPx->Draw("colz");
	sprintf(pixiPxname, "PimXi_Px_%s.png",version);
	ccpixiPx->Print(pixiPxname);

	char pixiPxnameM18[100];
	TH2I * pixiPxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Px_VsPhi");	
	TCanvas *ccpixiPxM18 = new TCanvas("ccpixiPxM18", "ccpixiPxM18", 800, 600);
	pixiPxM18->RebinX(5);
	pixiPxM18->RebinY(5);
        pixiPxM18->Draw("colz");
	sprintf(pixiPxnameM18, "PimXi_Px_M18_%s.png",version);
	ccpixiPxM18->Print(pixiPxnameM18);

	char pixiPyname[100];
	TH2I * pixiPy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Py_VsPhi");	
	TCanvas *ccpixiPy = new TCanvas("ccpixiPy", "ccpixiPy", 800, 600);
	pixiPy->RebinX(5);
	pixiPy->RebinY(5);
        pixiPy->Draw("colz");
	sprintf(pixiPyname, "PimXi_Py_%s.png",version);
	ccpixiPy->Print(pixiPyname);

	char pixiPynameM18[100];
	TH2I * pixiPyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Py_VsPhi");	
	TCanvas *ccpixiPyM18 = new TCanvas("ccpixiPyM18", "ccpixiPyM18", 800, 600);
	pixiPyM18->RebinX(5);
	pixiPyM18->RebinY(5);
        pixiPyM18->Draw("colz");
	sprintf(pixiPynameM18, "PimXi_Py_M18_%s.png",version);
	ccpixiPyM18->Print(pixiPynameM18);

	char pixiPzname[100];
	TH2I * pixiPz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Pz_VsPhi");	
	TCanvas *ccpixiPz = new TCanvas("ccpixiPz", "ccpixiPz", 800, 600);
	pixiPz->RebinX(5);
	pixiPz->RebinY(5);
        pixiPz->Draw("colz");
	sprintf(pixiPzname, "PimXi_Pz_%s.png",version);
	ccpixiPz->Print(pixiPzname);

	char pixiPznameM18[100];
	TH2I * pixiPzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Pz_VsPhi");	
	TCanvas *ccpixiPzM18 = new TCanvas("ccpixiPzM18", "ccpixiPzM18", 800, 600);
	pixiPzM18->RebinX(5);
	pixiPzM18->RebinY(5);
        pixiPzM18->Draw("colz");
	sprintf(pixiPznameM18, "PimXi_Pz_M18_%s.png",version);
	ccpixiPzM18->Print(pixiPznameM18);

	char pixiXxname[100];
	TH2I * pixiXx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xx_VsPhi");	
	TCanvas *ccpixiXx = new TCanvas("ccpixiXx", "ccpixiXx", 800, 600);
	pixiXx->RebinX(5);
	pixiXx->RebinY(5);
        pixiXx->Draw("colz");
	sprintf(pixiXxname, "PimXi_Xx_%s.png",version);
	ccpixiXx->Print(pixiXxname);

	char pixiXxnameM18[100];
	TH2I * pixiXxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xx_VsPhi");	
	TCanvas *ccpixiXxM18 = new TCanvas("ccpixiXxM18", "ccpixiXxM18", 800, 600);
	pixiXxM18->RebinX(5);
	pixiXxM18->RebinY(5);
        pixiXxM18->Draw("colz");
	sprintf(pixiXxnameM18, "PimXi_Xx_M18_%s.png",version);
	ccpixiXxM18->Print(pixiXxnameM18);

	char pixiXyname[100];
	TH2I * pixiXy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xy_VsPhi");	
	TCanvas *ccpixiXy = new TCanvas("ccpixiXy", "ccpixiXy", 800, 600);
	pixiXy->RebinX(5);
	pixiXy->RebinY(5);
        pixiXy->Draw("colz");
	sprintf(pixiXyname, "PimXi_Xy_%s.png",version);
	ccpixiXy->Print(pixiXyname);

	char pixiXynameM18[100];
	TH2I * pixiXyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xy_VsPhi");	
	TCanvas *ccpixiXyM18 = new TCanvas("ccpixiXyM18", "ccpixiXyM18", 800, 600);
	pixiXyM18->RebinX(5);
	pixiXyM18->RebinY(5);
        pixiXyM18->Draw("colz");
	sprintf(pixiXynameM18, "PimXi_Xy_M18_%s.png",version);
	ccpixiXyM18->Print(pixiXynameM18);


	char pixiXzname[100];
	TH2I * pixiXz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xz_VsPhi");	
	TCanvas *ccpixiXz = new TCanvas("ccpixiXz", "ccpixiXz", 800, 600);
	pixiXz->RebinX(5);
	pixiXz->RebinY(5);
        pixiXz->Draw("colz");
	sprintf(pixiXzname, "PimXi_Xz_%s.png",version);
	ccpixiXz->Print(pixiXzname);

	char pixiXznameM18[100];
	TH2I * pixiXzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step1__Xi-__Pi-_Lambda/Pi-/Pull_Xz_VsPhi");	
	TCanvas *ccpixiXzM18 = new TCanvas("ccpixiXzM18", "ccpixiXzM18", 800, 600);
	pixiXzM18->RebinX(5);
	pixiXzM18->RebinY(5);
        pixiXzM18->Draw("colz");
	sprintf(pixiXznameM18, "PimXi_Xz_M18_%s.png",version);
	ccpixiXzM18->Print(pixiXznameM18);

	char pilambPxname[100];
	TH2I * pilambPx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Px_VsPhi");	
	TCanvas *ccpilambPx = new TCanvas("ccpilambPx", "ccpilambPx", 800, 600);
	pilambPx->RebinX(5);
	pilambPx->RebinY(5);
        pilambPx->Draw("colz");
	sprintf(pilambPxname, "PimLamb_Px_%s.png",version);
	ccpilambPx->Print(pilambPxname);

	char pilambPxnameM18[100];
	TH2I * pilambPxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Px_VsPhi");	
	TCanvas *ccpilambPxM18 = new TCanvas("ccpilambPxM18", "ccpilambPxM18", 800, 600);
	pilambPxM18->RebinX(5);
	pilambPxM18->RebinY(5);
        pilambPxM18->Draw("colz");
	sprintf(pilambPxnameM18, "PimLamb_Px_M18_%s.png",version);
	ccpilambPxM18->Print(pilambPxnameM18);

	char pilambPyname[100];
	TH2I * pilambPy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Py_VsPhi");	
	TCanvas *ccpilambPy = new TCanvas("ccpilambPy", "ccpilambPy", 800, 600);
	pilambPy->RebinX(5);
	pilambPy->RebinY(5);
        pilambPy->Draw("colz");
	sprintf(pilambPyname, "PimLamb_Py_%s.png",version);
	ccpilambPy->Print(pilambPyname);

	char pilambPynameM18[100];
	TH2I * pilambPyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Py_VsPhi");	
	TCanvas *ccpilambPyM18 = new TCanvas("ccpilambPyM18", "ccpilambPyM18", 800, 600);
	pilambPyM18->RebinX(5);
	pilambPyM18->RebinY(5);
        pilambPyM18->Draw("colz");
	sprintf(pilambPynameM18, "PimLamb_Py_M18_%s.png",version);
	ccpilambPyM18->Print(pilambPynameM18);

	char pilambPzname[100];
	TH2I * pilambPz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Pz_VsPhi");	
	TCanvas *ccpilambPz = new TCanvas("ccpilambPz", "ccpilambPz", 800, 600);
	pilambPz->RebinX(5);
	pilambPz->RebinY(5);
        pilambPz->Draw("colz");
	sprintf(pilambPzname, "PimLamb_Pz_%s.png",version);
	ccpilambPz->Print(pilambPzname);

	char pilambPznameM18[100];
	TH2I * pilambPzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Pz_VsPhi");	
	TCanvas *ccpilambPzM18 = new TCanvas("ccpilambPzM18", "ccpilambPzM18", 800, 600);
	pilambPzM18->RebinX(5);
	pilambPzM18->RebinY(5);
        pilambPzM18->Draw("colz");
	sprintf(pilambPznameM18, "PimLamb_Pz_M18_%s.png",version);
	ccpilambPzM18->Print(pilambPznameM18);

	char pilambXxname[100];
	TH2I * pilambXx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xx_VsPhi");	
	TCanvas *ccpilambXx = new TCanvas("ccpilambXx", "ccpilambXx", 800, 600);
	pilambXx->RebinX(5);
	pilambXx->RebinY(5);
        pilambXx->Draw("colz");
	sprintf(pilambXxname, "PimLamb_Xx_%s.png",version);
	ccpilambXx->Print(pilambXxname);

	char pilambXxnameM18[100];
	TH2I * pilambXxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xx_VsPhi");	
	TCanvas *ccpilambXxM18 = new TCanvas("ccpilambXxM18", "ccpilambXxM18", 800, 600);
	pilambXxM18->RebinX(5);
	pilambXxM18->RebinY(5);
        pilambXxM18->Draw("colz");
	sprintf(pilambXxnameM18, "PimLamb_Xx_M18_%s.png",version);
	ccpilambXxM18->Print(pilambXxnameM18);

	char pilambXyname[100];
	TH2I * pilambXy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xy_VsPhi");	
	TCanvas *ccpilambXy = new TCanvas("ccpilambXy", "ccpilambXy", 800, 600);
	pilambXy->RebinX(5);
	pilambXy->RebinY(5);
        pilambXy->Draw("colz");
	sprintf(pilambXyname, "PimLamb_Xy_%s.png",version);
	ccpilambXy->Print(pilambXyname);

	char pilambXynameM18[100];
	TH2I * pilambXyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xy_VsPhi");	
	TCanvas *ccpilambXyM18 = new TCanvas("ccpilambXyM18", "ccpilambXyM18", 800, 600);
	pilambXyM18->RebinX(5);
	pilambXyM18->RebinY(5);
        pilambXyM18->Draw("colz");
	sprintf(pilambXynameM18, "PimLamb_Xy_M18_%s.png",version);
	ccpilambXyM18->Print(pilambXynameM18);


	char pilambXzname[100];
	TH2I * pilambXz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xz_VsPhi");	
	TCanvas *ccpilambXz = new TCanvas("ccpilambXz", "ccpilambXz", 800, 600);
	pilambXz->RebinX(5);
	pilambXz->RebinY(5);
        pilambXz->Draw("colz");
	sprintf(pilambXzname, "PimLamb_Xz_%s.png",version);
	ccpilambXz->Print(pilambXzname);

	char pilambXznameM18[100];
	TH2I * pilambXzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Pi-/Pull_Xz_VsPhi");	
	TCanvas *ccpilambXzM18 = new TCanvas("ccpilambXzM18", "ccpilambXzM18", 800, 600);
	pilambXzM18->RebinX(5);
	pilambXzM18->RebinY(5);
        pilambXzM18->Draw("colz");
	sprintf(pilambXznameM18, "PimLamb_Xz_M18_%s.png",version);
	ccpilambXzM18->Print(pilambXznameM18);

	char protPxname[100];
	TH2I * protPx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Px_VsPhi");	
	TCanvas *ccprotPx = new TCanvas("ccprotPx", "ccprotPx", 800, 600);
	protPx->RebinX(5);
	protPx->RebinY(5);
        protPx->Draw("colz");
	sprintf(protPxname, "P_Px_%s.png",version);
	ccprotPx->Print(protPxname);

	char protPxnameM18[100];
	TH2I * protPxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Px_VsPhi");	
	TCanvas *ccprotPxM18 = new TCanvas("ccprotPxM18", "ccprotPxM18", 800, 600);
	protPxM18->RebinX(5);
	protPxM18->RebinY(5);
        protPxM18->Draw("colz");
	sprintf(protPxnameM18, "P_Px_M18_%s.png",version);
	ccprotPxM18->Print(protPxnameM18);

	char protPyname[100];
	TH2I * protPy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Py_VsPhi");	
	TCanvas *ccprotPy = new TCanvas("ccprotPy", "ccprotPy", 800, 600);
	protPy->RebinX(5);
	protPy->RebinY(5);
        protPy->Draw("colz");
	sprintf(protPyname, "P_Py_%s.png",version);
	ccprotPy->Print(protPyname);

	char protPynameM18[100];
	TH2I * protPyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Py_VsPhi");	
	TCanvas *ccprotPyM18 = new TCanvas("ccprotPyM18", "ccprotPyM18", 800, 600);
	protPyM18->RebinX(5);
	protPyM18->RebinY(5);
        protPyM18->Draw("colz");
	sprintf(protPynameM18, "P_Py_M18_%s.png",version);
	ccprotPyM18->Print(protPynameM18);

	char protPzname[100];
	TH2I * protPz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Pz_VsPhi");	
	TCanvas *ccprotPz = new TCanvas("ccprotPz", "ccprotPz", 800, 600);
	protPz->RebinX(5);
	protPz->RebinY(5);
        protPz->Draw("colz");
	sprintf(protPzname, "P_Pz_%s.png",version);
	ccprotPz->Print(protPzname);

	char protPznameM18[100];
	TH2I * protPzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Pz_VsPhi");	
	TCanvas *ccprotPzM18 = new TCanvas("ccprotPzM18", "ccprotPzM18", 800, 600);
	protPzM18->RebinX(5);
	protPzM18->RebinY(5);
        protPzM18->Draw("colz");
	sprintf(protPznameM18, "P_Pz_M18_%s.png",version);
	ccprotPzM18->Print(protPznameM18);

	char protXxname[100];
	TH2I * protXx = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xx_VsPhi");	
	TCanvas *ccprotXx = new TCanvas("ccprotXx", "ccprotXx", 800, 600);
	protXx->RebinX(5);
	protXx->RebinY(5);
        protXx->Draw("colz");
	sprintf(protXxname, "P_Xx_%s.png",version);
	ccprotXx->Print(protXxname);

	char protXxnameM18[100];
	TH2I * protXxM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xx_VsPhi");	
	TCanvas *ccprotXxM18 = new TCanvas("ccprotXxM18", "ccprotXxM18", 800, 600);
	protXxM18->RebinX(5);
	protXxM18->RebinY(5);
        protXxM18->Draw("colz");
	sprintf(protXxnameM18, "P_Xx_M18_%s.png",version);
	ccprotXxM18->Print(protXxnameM18);

	char protXyname[100];
	TH2I * protXy = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xy_VsPhi");	
	TCanvas *ccprotXy = new TCanvas("ccprotXy", "ccprotXy", 800, 600);
	protXy->RebinX(5);
	protXy->RebinY(5);
        protXy->Draw("colz");
	sprintf(protXyname, "P_Xy_%s.png",version);
	ccprotXy->Print(protXyname);

	char protXynameM18[100];
	TH2I * protXyM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xy_VsPhi");	
	TCanvas *ccprotXyM18 = new TCanvas("ccprotXyM18", "ccprotXyM18", 800, 600);
	protXyM18->RebinX(5);
	protXyM18->RebinY(5);
        protXyM18->Draw("colz");
	sprintf(protXynameM18, "P_Xy_M18_%s.png",version);
	ccprotXyM18->Print(protXynameM18);


	char protXzname[100];
	TH2I * protXz = (TH2I*)file1->Get("kpkpxim__B4_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xz_VsPhi");	
	TCanvas *ccprotXz = new TCanvas("ccprotXz", "ccprotXz", 800, 600);
	protXz->RebinX(5);
	protXz->RebinY(5);
        protXz->Draw("colz");
	sprintf(protXzname, "P_Xz_%s.png",version);
	ccprotXz->Print(protXzname);

	char protXznameM18[100];
	TH2I * protXzM18 = (TH2I*)file1->Get("kpkpxim__B4_M18_M23/Hist_KinFitResults/Step2__Lambda__Pi-_Proton/Proton/Pull_Xz_VsPhi");	
	TCanvas *ccprotXzM18 = new TCanvas("ccprotXzM18", "ccprotXzM18", 800, 600);
	protXzM18->RebinX(5);
	protXzM18->RebinY(5);
        protXzM18->Draw("colz");
	sprintf(protXznameM18, "P_Xz_M18_%s.png",version);
	ccprotXzM18->Print(protXznameM18);

*/
	return;	
	
}
