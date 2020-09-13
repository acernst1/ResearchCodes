#include "DSelector_thrown_kpkpxim.h"

double getphi(TLorentzVector P4){
		// Returns a phi angle between -180deg and 180deg
		double phi = P4.Phi()*180/TMath::Pi();
		if(phi < -180.) phi += 360.;
		if(phi >  180.) phi -= 360.;
		return phi;
}

void DSelector_thrown_kpkpxim::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "thrown_kpkpxim.root"; //"" for none
	//USERS: SET OUTPUT TREE FILES/NAMES //e.g. binning into separate files for AmpTools
	//dOutputTreeFileNameMap["Bin1"] = "mcgen_bin1.root"; //key is user-defined, value is output file name
	//dOutputTreeFileNameMap["Bin2"] = "mcgen_bin2.root"; //key is user-defined, value is output file name
	//dOutputTreeFileNameMap["Bin3"] = "mcgen_bin3.root"; //key is user-defined, value is output file name

	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	dPreviousRunNumber = 0;

	/******************************** EXAMPLE USER INITIALIZATION: STAND-ALONE HISTOGRAMS *******************************/
	dHist_Egamma_t = new TH2F("Egamma_t","; E_{#gamma} (GeV); -t (GeV/c)^{2}",180, 3.0, 11.4,200, 0.0, 10.0);
	dHist_Egamma_t_063 = new TH2F("Egamma_t_063","; E_{#gamma} (GeV); -t (GeV/c)^{2}",100, 6.3, 11.3,200, 0.0, 10.0);
	dHist_Egamma_t_064 = new TH2F("Egamma_t_064","; E_{#gamma} (GeV); -t (GeV/c)^{2}",100,6.4, 11.4,200, 0.0, 10.0);
	dHist_Egamma_064 = new TH1F("Egamma_064","; E_{#gamma} (GeV)",100,6.4, 11.4);
	dHist_Egamma_t_064_upperTarget = new TH2F("Egamma_t_064_upperTarget","; E_{#gamma} (GeV); -t (GeV/c)^{2}",100,6.4, 11.4,200, 0.0, 10.0);
	dHist_Egamma_t_064_lowerTarget = new TH2F("Egamma_t_064_lowerTarget","; E_{#gamma} (GeV); -t (GeV/c)^{2}",100,6.4, 11.4,200, 0.0, 10.0);
	dHist_Egamma_t_065 = new TH2F("Egamma_t_065","; E_{#gamma} (GeV); -t (GeV/c)^{2}",100,6.5,11.5,200, 0.0, 10.0);
	
	dHist_KPlus1vsKPlus2_p = new TH2F("KPlus1vsKPlus2_p",";K^{+}_{1} p (GeV);K^{+}_{2} p (GeV)",200,0.0,10.0,200,0.0,10.0);
	dHist_KPlus1vsKPlus2_theta = new TH2F("KPlus1vsKPlus2_theta",";K^{+}_{1} #theta;K^{+}_{2} #theta",140,0.0,140.0,140,0.0,140.0);
	dHist_KPlus1_pTheta = new TH2F("KPlus1_ptheta",";K^{+}_{1} #theta; K^{+}_{1} p (GeV);",140,0.0,140.0, 200,0.0,10.0);
	dHist_KPlus2_pTheta = new TH2F("KPlus2_ptheta",";K^{+}_{2} #theta; K^{+}_{2} p (GeV);",140,0.0,140.0, 200,0.0,10.0);
	dHist_prodvert = new TH1I("prodvert","Production Vertex;;",1000,0,100);

	dHist_Klowp_phiTheta_YstarGJ = new TH2I("Klowp_phiTheta_YstarGJ", "K^{+}_{decay};#Theta (deg); #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Xi_phiTheta_YstarGJ = new TH2I("Xi_phiTheta_YstarGJ", "#Xi^{-};#Theta (deg);#phi (deg)",30,0.0,180,180,-180,180.0);
	
	dHist_Khighp_phiTheta_CM = new TH2I("Khighp_phiTheta_CM", "K^{+}_{highp} ;#Theta (deg); #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Khighp_phiTheta_Ystar = new TH2I("Khighp_phiTheta_Ystar", "K^{+}_{highp}; #Theta (deg);  #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_Ystar = new TH2I("Klowp_phiTheta_Ystar", "K^{+}_{decay} ; #Theta (deg);  #phi (deg)",30,0.0,180,180,-180,180.0); 
	dHist_Ystar_p_Ystar = new TH1I("Ystar_p_Ystar", "Y^{*}; p (GeV)",50,0.0,5.0);
	dHist_Ystar_phiTheta_CM = new TH2I("Ystar_phiTheta_CM", "Y^{*} ; #Theta (deg);  #phi (deg)",30,0.0,180,180,-180,180.0);
	
	myfile = new ofstream("ThrownP4.txt");
	Int_t count_event = 0;
	Int_t count_KKXi = 0;


	/************************************* ADVANCED EXAMPLE: CHOOSE BRANCHES TO READ ************************************/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

	//dTreeInterface->Clear_GetEntryBranches(); //now get none
	//dTreeInterface->Register_GetEntryBranch("Proton__P4"); //manually set the branches you want
}

Bool_t DSelector_thrown_kpkpxim::Process(Long64_t locEntry)
{
	// The Process() function is called for each entry in the tree. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	// Use fStatus to set the return value of TTree::Process().
	// The return value is currently not used.

	//CALL THIS FIRST
	DSelector::Process(locEntry); //Gets the data from the tree for the entry
	//cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;

	/******************************************** GET POLARIZATION ORIENTATION ******************************************/

	//Only if the run number changes
	//RCDB environment must be setup in order for this to work! (Will return false otherwise)
	UInt_t locRunNumber = Get_RunNumber();
	if(locRunNumber != dPreviousRunNumber)
	{
		dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
		dPreviousRunNumber = locRunNumber;
	}

	/********************************************* SETUP UNIQUENESS TRACKING ********************************************/

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_thrown;

	/******************************************* LOOP OVER THROWN DATA ***************************************/

	//Counting
	count_event++;

	//Thrown beam: just use directly
	double locBeamEnergyUsedForBinning = 0.0;
	if(dThrownBeam != NULL)
		locBeamEnergyUsedForBinning = dThrownBeam->Get_P4().E();
		TLorentzVector locBeamP4 = dThrownBeam->Get_P4();
		TLorentzVector locProdSpacetimeVertex =dThrownBeam->Get_X4();//Get production vertex

	TLorentzVector locKPlus1P4;
	TLorentzVector locKPlus2P4;
	TLorentzVector locXiP4;
	TLorentzVector locPiMinusP4;
	TLorentzVector locLambdaP4;
	//Loop over throwns
	*myfile << "New Event: " << endl;
	for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dThrownWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
		Particle_t locPID = dThrownWrapper->Get_PID();
		TLorentzVector locThrownP4 = dThrownWrapper->Get_P4();
		*myfile << "Thrown Paricle No " << loc_i << " PID:" << locPID << " Mass:  " << locThrownP4.M() << endl; 
		*myfile << "\t P4 (Px Py Pz E): " << locThrownP4.Px() << " " << locThrownP4.Py() << " " << locThrownP4.Pz() << " " << locThrownP4.E() << endl;
		if(locPID == 11) {
			if(loc_i == 0) {locKPlus1P4 = locThrownP4; }
			if(loc_i == 1) {locKPlus2P4 = locThrownP4; }
		}
		if(locPID == 23) {locXiP4 = locThrownP4; }
		if(locPID ==  9 && loc_i == 2) {locPiMinusP4 = locThrownP4;}
		if(locPID ==  18 && loc_i == 6) {locLambdaP4 = locThrownP4;}

	}

	//BoostVector for CoM 
	TLorentzVector locCoMP4 = locBeamP4 + dTargetP4;
	TVector3 boostCoM = locCoMP4.BoostVector();
	//Boost in CoM 
	TLorentzVector locBeamP4_CM = locBeamP4;
	TLorentzVector locKPlus1P4_CM = locKPlus1P4;
	TLorentzVector locKPlus2P4_CM = locKPlus2P4;
	TLorentzVector locXiP4_CM = locXiP4;
	locBeamP4_CM.Boost(-boostCoM);
	locKPlus1P4_CM.Boost(-boostCoM);
	locKPlus2P4_CM.Boost(-boostCoM);
	locXiP4_CM.Boost(-boostCoM);
	TLorentzVector locIntermediate_CM = locKPlus2P4_CM + locXiP4_CM;
	//Boost in Ystar rest frame in the GJ reference frame
	TVector3 boostYstar = locIntermediate_CM.BoostVector();
	TLorentzVector locBeamP4_Ystar = locBeamP4_CM;
	TLorentzVector locKPlusP4_highp_Ystar = locKPlus1P4_CM;
	TLorentzVector locIntermediate_Ystar = locIntermediate_CM;
	TLorentzVector locKPlusP4_lowp_Ystar = locKPlus2P4_CM;
	TLorentzVector locXiP4_Ystar = locXiP4_CM;
	locBeamP4_Ystar.Boost(-boostYstar);
	locKPlusP4_highp_Ystar.Boost(-boostYstar);
	locIntermediate_Ystar.Boost(-boostYstar);
	locKPlusP4_lowp_Ystar.Boost(-boostYstar);
	locXiP4_Ystar.Boost(-boostYstar);
	TVector3 z_YstarGJ;
	z_YstarGJ.SetXYZ(locBeamP4_Ystar.X(),locBeamP4_Ystar.Y(),locBeamP4_Ystar.Z());
	TVector3 z_hat_YstarGJ = z_YstarGJ.Unit();
	TVector3 y_YstarGJ = locBeamP4_Ystar.Vect().Cross(locIntermediate_Ystar.Vect());
	TVector3 y_hat_YstarGJ = y_YstarGJ.Unit();
	TVector3 x_hat_YstarGJ = y_hat_YstarGJ.Cross(z_hat_YstarGJ);
	TVector3 locKPlusP3_lowp_YstarGJ(locKPlusP4_lowp_Ystar.Vect()*x_hat_YstarGJ,locKPlusP4_lowp_Ystar.Vect()*y_hat_YstarGJ,locKPlusP4_lowp_Ystar.Vect()*z_hat_YstarGJ);
	TVector3 locXiP3_YstarGJ(locXiP4_Ystar.Vect()*x_hat_YstarGJ,locXiP4_Ystar.Vect()*y_hat_YstarGJ,locXiP4_Ystar.Vect()*z_hat_YstarGJ);

	TLorentzVector locKPlusP4_lowp = locKPlus2P4;
	TLorentzVector locKPlusP4_highp = locKPlus1P4;		
	double t= (locBeamP4 - locKPlusP4_highp).M2();
	double phiKhighp_CM = getphi(locKPlus1P4_CM);
	double phiKlowp_CM = getphi(locKPlus2P4_CM);
	double phiYstar_CM = getphi(locIntermediate_CM);
	double phiKhighp_Ystar = getphi(locKPlusP4_highp_Ystar);
	double phiKlowp_Ystar = getphi(locKPlusP4_lowp_Ystar);
	double phiKlowp_YstarGJ = getphi(locKPlusP3_lowp_YstarGJ);
	double phiXi_YstarGJ = getphi(locXiP3_YstarGJ);

	map<Particle_t, set<Int_t> > locUsedThisCombo_thrown;
		if(locUsedSoFar_thrown.find(locUsedThisCombo_thrown) == locUsedSoFar_thrown.end()){
			dHist_KPlus1vsKPlus2_p->Fill(locKPlus1P4.P(),locKPlus2P4.P());
			dHist_KPlus1vsKPlus2_theta->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus2P4.Theta()*180./TMath::Pi());
			dHist_KPlus1_pTheta->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.P()); 
			dHist_KPlus2_pTheta->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.P());  
			dHist_Egamma_t->Fill(locBeamEnergyUsedForBinning,-1.*t);
			dHist_Egamma_t_063->Fill(locBeamEnergyUsedForBinning,-1.*t);
			dHist_Egamma_t_064->Fill(locBeamEnergyUsedForBinning,-1.*t);
			dHist_Egamma_064->Fill(locBeamEnergyUsedForBinning);
			dHist_Egamma_t_065->Fill(locBeamEnergyUsedForBinning,-1.*t);
			dHist_prodvert->Fill(locProdSpacetimeVertex.Z());
			dHist_Khighp_phiTheta_CM->Fill(locKPlus1P4_CM.Theta()*180./TMath::Pi(), phiKhighp_CM);
			dHist_Ystar_phiTheta_CM->Fill(locIntermediate_CM.Theta()*180./TMath::Pi(), phiYstar_CM);
			dHist_Khighp_phiTheta_Ystar->Fill(locKPlusP4_highp_Ystar.Theta()*180./TMath::Pi(), phiKhighp_Ystar);
			dHist_Klowp_phiTheta_Ystar->Fill(locKPlusP4_lowp_Ystar.Theta()*180./TMath::Pi(), phiKlowp_Ystar);
			dHist_Ystar_p_Ystar->Fill(locIntermediate_Ystar.P());
			dHist_Klowp_phiTheta_YstarGJ->Fill(locKPlusP3_lowp_YstarGJ.Theta()*180./TMath::Pi(), phiKlowp_YstarGJ);
			dHist_Xi_phiTheta_YstarGJ->Fill(locXiP3_YstarGJ.Theta()*180./TMath::Pi(),phiXi_YstarGJ);
			if(locProdSpacetimeVertex.Z() > 50.0 && locProdSpacetimeVertex.Z() < 65.0){
				dHist_Egamma_t_064_lowerTarget->Fill(locBeamEnergyUsedForBinning,-1.*t);
			}
			if(locProdSpacetimeVertex.Z() > 65.0 && locProdSpacetimeVertex.Z() < 80.0){
				dHist_Egamma_t_064_upperTarget->Fill(locBeamEnergyUsedForBinning,-1.*t);
			}
		locUsedSoFar_thrown.insert(locUsedThisCombo_thrown);
	}
	

	//OR Manually:
	//BEWARE: Do not expect the particles to be at the same array indices from one event to the next!!!!
	//Why? Because while your channel may be the same, the pions/kaons/etc. will decay differently each event.

	//BRANCHES: https://halldweb.jlab.org/wiki/index.php/Analysis_TTreeFormat#TTree_Format:_Simulated_Data
	TClonesArray** locP4Array = dTreeInterface->Get_PointerToPointerTo_TClonesArray("Thrown__P4");
	TBranch* locPIDBranch = dTreeInterface->Get_Branch("Thrown__PID");
/*
	Particle_t locThrown1PID = PDGtoPType(((Int_t*)locPIDBranch->GetAddress())[0]);
	TLorentzVector locThrown1P4 = *((TLorentzVector*)(*locP4Array)->At(0));
	cout << "Particle 1: " << locThrown1PID << ", " << locThrown1P4.Px() << ", " << locThrown1P4.Py() << ", " << locThrown1P4.Pz() << ", " << locThrown1P4.E() << endl;
	Particle_t locThrown2PID = PDGtoPType(((Int_t*)locPIDBranch->GetAddress())[1]);
	TLorentzVector locThrown2P4 = *((TLorentzVector*)(*locP4Array)->At(1));
	cout << "Particle 2: " << locThrown2PID << ", " << locThrown2P4.Px() << ", " << locThrown2P4.Py() << ", " << locThrown2P4.Pz() << ", " << locThrown2P4.E() << endl;
*/


	/******************************************* BIN THROWN DATA INTO SEPARATE TREES FOR AMPTOOLS ***************************************/

/*
	//THESE KEYS MUST BE DEFINED IN THE INIT SECTION (along with the output file names)
	if((locBeamEnergyUsedForBinning >= 8.0) && (locBeamEnergyUsedForBinning < 9.0))
		Fill_OutputTree("Bin1"); //your user-defined key
	else if((locBeamEnergyUsedForBinning >= 9.0) && (locBeamEnergyUsedForBinning < 10.0))
		Fill_OutputTree("Bin2"); //your user-defined key
	else if((locBeamEnergyUsedForBinning >= 10.0) && (locBeamEnergyUsedForBinning < 11.0))
		Fill_OutputTree("Bin3"); //your user-defined key
*/

	return kTRUE;
}

void DSelector_thrown_kpkpxim::Finalize(void)
{
	//Save anything to output here that you do not want to be in the default DSelector output ROOT file.

	//Otherwise, don't do anything else (especially if you are using PROOF).
		//If you are using PROOF, this function is called on each thread,
		//so anything you do will not have the combined information from the various threads.
		//Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

	//DO YOUR STUFF HERE
	myfile->close();
	delete myfile;
	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
