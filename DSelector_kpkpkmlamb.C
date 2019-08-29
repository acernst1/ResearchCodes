#include "DSelector_kpkpkmlamb.h"

void DSelector_kpkpkmlamb::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "kpkpkmlamb.root"; //"" for none
	dOutputTreeFileName = ""; //"" for none

	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	Get_ComboWrappers();
	dPreviousRunNumber = 0;

	/**** EXAMPLE USER INITIALIZATION: ANALYSIS ACTIONS ****/

	//ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
	//false/true below: use measured/kinfit data

	//PID
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.4, KPlus, SYS_BCAL));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.2, KPlus, SYS_TOF));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.4, KMinus, SYS_BCAL));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.2, KMinus, SYS_TOF));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.8, Proton, SYS_BCAL));
	dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.5, Proton, SYS_TOF));
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false, "PostPID"));

	//MASSES
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda, 800, 1.0, 1.2, "Lambda"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 750, -0.1, 0.1));
	deque<Particle_t> locXiStarPIDs;  locXiStarPIDs.push_back(KMinus);  locXiStarPIDs.push_back(Lambda);
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locXiStarPIDs, 260, 1.3, 2.6, "XiStar"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locXiStarPIDs, 260, 1.3, 2.6, "XiStar_KinFit"));
	deque<Particle_t> locKKLambdaPIDs;  locKKLambdaPIDs.push_back(KMinus);  locKKLambdaPIDs.push_back(Lambda);  locKKLambdaPIDs.push_back(KPlus);
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKLambdaPIDs, 750, 1.5, 3.0, "KKLambda"));
	deque<Particle_t> locKKKPIDs;  locKKKPIDs.push_back(KMinus);  locKKKPIDs.push_back(KPlus);  locKKKPIDs.push_back(KPlus);
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKKPIDs, 750, 0.7, 2.2, "KKK"));
	deque<Particle_t> locKKPIDs;  locKKPIDs.push_back(KMinus);  locKKPIDs.push_back(KPlus);  
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKPIDs, 550, 0.7, 1.8, "KK"));
	deque<Particle_t> locKpLambdaPIDs;  locKpLambdaPIDs.push_back(Lambda);  locKpLambdaPIDs.push_back(KPlus);  
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKpLambdaPIDs, 600, 1.1, 1.7, "KpLambda"));

	//5sigma
	//dAnalysisActions.push_back(new DCutAction_KinFitFOM(dComboWrapper, 5.73303E-7));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda, 200, 1.0, 1.2, "Lambda_PostKinFitCut"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 750, -0.1, 0.1, "PostKinFitCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locXiStarPIDs, 220, 1.5, 2.6, "XiStar_PostKinFitCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locXiStarPIDs, 220, 1.5, 2.6, "XiStar_PostKinFitCut_KinFit"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKLambdaPIDs, 200, 2.0, 3.5, "KKLambda_PostKinFitCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKKPIDs, 150, 1.5, 2.2, "KKK_PostKinFitCut")); 
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKPIDs, 600, 0.9, 1.8, "KK_PostKinFitCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKpLambdaPIDs, 750, 1.6, 3.0, "KpLambda_PostKinFitCut"));

	//Phi cut
	dAnalysisActions.push_back(new DCutAction_InvariantMassVeto(dComboWrapper, false, 0, locKKPIDs, 1.0, 1.05, "PhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda,200, 1.0, 1.2, "Lambda_PostPhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, Lambda, 200, 1.0, 1.2, "Lambda_PostPhiCut_KinFit"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 750, -0.1, 0.1, "PostPhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locXiStarPIDs, 220, 1.5, 2.6, "XiStar_PostPhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locXiStarPIDs, 220, 1.5, 2.6, "XiStar_PostPhiCut_KinFit_5"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locXiStarPIDs, 110, 1.5, 2.6, "XiStar_PostPhiCut_KinFit_10"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locXiStarPIDs, 70, 1.55, 2.6, "XiStar_PostPhiCut_KinFit_15"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKLambdaPIDs, 200, 2.0, 3.5, "KKLambda_PostPhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKKPIDs, 150, 1.5, 2.2, "KKK_PostPhiCut")); 
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKKPIDs, 600, 0.9, 1.8, "KK_PostPhiCut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKpLambdaPIDs, 750, 1.6, 3.0, "KpLambda_PostPhiCut"));

	//KINEMATICS
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, false));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true, "KinFit"));
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false, "PostKinFit"));

	//INITIALIZE ACTIONS
	//If you create any actions that you want to run manually (i.e. don't add to dAnalysisActions), be sure to initialize them here as well
	Initialize_Actions();

	/**** EXAMPLE USER INITIALIZATION: STAND-ALONE HISTOGRAMS ****/
	dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
	dHist_BeamBunch = new TH1I("BeamBunch", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_ChiSq = new TH1I("ChiSq", "ChiSq", 200, 0.0, 100.0);
	dHist_ChiSqXi = new TH2I("ChiSqXi", "ChiSq",100,0.0,100.0,220,1.5,2.6);
	dHist_XiMass_Measured=new TH1I("XiMass","#Xi- Invariant Mass (GeV/c^{2})", 220,1.5,2.6);
	dHist_KKMassless_Measured=new TH1I("KKMassless_Measured","KK Invariant Mass (GeV/c^{2})", 200,1.0,2.0);
	dHist_KKMassless_KinFit=new TH1I("KKMassless_KinFit","KK Invariant Mass (GeV/c^{2})", 200,1.0,2.0);
	dHist_KKMassmore_Measured=new TH1I("KKMassmore_Measured","KK Invariant Mass (GeV/c^{2})", 200,1.0,2.0);
	dHist_KKMassmore_KinFit=new TH1I("KKMassmore_KinFit","KK Invariant Mass (GeV/c^{2})", 200,1.0,2.0);
	dHist_XiMass_KinFit=new TH1I("XiMass_KinFit","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 220,1.5,2.6);
	dHist_XiMass_Measured_acc=new TH1I("XiMass_acc","#Xi- Invariant Mass (GeV/c^{2})", 220,1.5,2.6);
	dHist_XiMass_KinFit_acc=new TH1I("XiMass_KinFit_acc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 220,1.5,2.6);
	dHist_K_pTheta_Measured = new TH2I("K_pTheta_Measured", "K^{+} pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_K_pTheta_Measured_acc = new TH2I("K_pTheta_Measured_acc", "K^{+} pvsTheta Measured",28,0.0,140,40,0.0,10.0);

	/****EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - MAIN TREE ****/

	//EXAMPLE MAIN TREE CUSTOM BRANCHES (OUTPUT ROOT FILE NAME MUST FIRST BE GIVEN!!!! (ABOVE: TOP)):
	//The type for the branch must be included in the brackets
	//1st function argument is the name of the branch
	//2nd function argument is the name of the branch that contains the size of the array (for fundamentals only)
	/*
	dTreeInterface->Create_Branch_Fundamental<Int_t>("my_int"); //fundamental = char, int, float, double, etc.
	dTreeInterface->Create_Branch_FundamentalArray<Int_t>("my_int_array", "my_int");
	dTreeInterface->Create_Branch_FundamentalArray<Float_t>("my_combo_array", "NumCombos");
	dTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("my_p4");
	dTreeInterface->Create_Branch_ClonesArray<TLorentzVector>("my_p4_array");
	*/

	/**** EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - FLAT TREE ****/

	//EXAMPLE FLAT TREE CUSTOM BRANCHES (OUTPUT ROOT FILE NAME MUST FIRST BE GIVEN!!!! (ABOVE: TOP)):
	//The type for the branch must be included in the brackets
	//1st function argument is the name of the branch
	//2nd function argument is the name of the branch that contains the size of the array (for fundamentals only)
	/*
	dFlatTreeInterface->Create_Branch_Fundamental<Int_t>("flat_my_int"); //fundamental = char, int, float, double, etc.
	dFlatTreeInterface->Create_Branch_FundamentalArray<Int_t>("flat_my_int_array", "flat_my_int");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("flat_my_p4");
	dFlatTreeInterface->Create_Branch_ClonesArray<TLorentzVector>("flat_my_p4_array");
	*/

	/**** ADVANCED EXAMPLE: CHOOSE BRANCHES TO READ ****/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

	//dTreeInterface->Clear_GetEntryBranches(); //now get none
	//dTreeInterface->Register_GetEntryBranch("Proton__P4"); //manually set the branches you want
}

Bool_t DSelector_kpkpkmlamb::Process(Long64_t locEntry)
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
	//TLorentzVector locProductionX4 = Get_X4_Production();

	/**** GET POLARIZATION ORIENTATION ****/

	//Only if the run number changes
	//RCDB environment must be setup in order for this to work! (Will return false otherwise)
	UInt_t locRunNumber = Get_RunNumber();
	if(locRunNumber != dPreviousRunNumber)
	{
		dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
		dPreviousRunNumber = locRunNumber;
	}

	/**** SETUP UNIQUENESS TRACKING ****/

	//ANALYSIS ACTIONS: Reset uniqueness tracking for each action
	//For any actions that you are executing manually, be sure to call Reset_NewEvent() on them here
	Reset_Actions_NewEvent();

	//PREVENT-DOUBLE COUNTING WHEN HISTOGRAMMING
		//Sometimes, some content is the exact same between one combo and the next
			//e.g. maybe two combos have different beam particles, but the same data for the final-state
		//When histogramming, you don't want to double-count when this happens: artificially inflates your signal (or background)
		//So, for each quantity you histogram, keep track of what particles you used (for a given combo)
		//Then for each combo, just compare to what you used before, and make sure it's unique

	//EXAMPLE 1: Particle-specific info:
	set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search

	//EXAMPLE 2: Combo-specific info:
		//In general: Could have multiple particles with the same PID: Use a set of Int_t's
		//In general: Multiple PIDs, so multiple sets: Contain within a map
		//Multiple combos: Contain maps within a set (easier, faster to search)
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_ChiSq;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_Phi;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts;


	/**** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES ****/

	/*
	Int_t locMyInt = 7;
	dTreeInterface->Fill_Fundamental<Int_t>("my_int", locMyInt);

	TLorentzVector locMyP4(4.0, 3.0, 2.0, 1.0);
	dTreeInterface->Fill_TObject<TLorentzVector>("my_p4", locMyP4);

	for(int loc_i = 0; loc_i < locMyInt; ++loc_i)
		dTreeInterface->Fill_Fundamental<Int_t>("my_int_array", 3*loc_i, loc_i); //2nd argument = value, 3rd = array index
	*/

	/**** LOOP OVER COMBOS ****/

	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);

		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut()) // Is false when tree originally created
			continue; // Combo has been cut previously

		/**** GET PARTICLE INDICES ****/

		//Used for tracking uniqueness when filling histograms, and for determining unused particles

		//Step 0
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locKPlus1TrackID = dKPlus1Wrapper->Get_TrackID();
		Int_t locKPlus2TrackID = dKPlus2Wrapper->Get_TrackID();
		Int_t locKMinusTrackID = dKMinusWrapper->Get_TrackID();

		//Step 1
		Int_t locPiMinusTrackID = dPiMinusWrapper->Get_TrackID();
		Int_t locProtonTrackID = dProtonWrapper->Get_TrackID();

		/**** GET FOUR-MOMENTUM ****/

		// Get P4's: //is kinfit if kinfit performed, else is measured
		//dTargetP4 is target p4
		//Step 0
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locKPlus1P4 = dKPlus1Wrapper->Get_P4();
		TLorentzVector locKPlus2P4 = dKPlus2Wrapper->Get_P4();
		TLorentzVector locKMinusP4 = dKMinusWrapper->Get_P4();
		//Step 1
		TLorentzVector locDecayingLambdaP4 = dDecayingLambdaWrapper->Get_P4();
		TLorentzVector locPiMinusP4 = dPiMinusWrapper->Get_P4();
		TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();

		// Get Measured P4's:
		//Step 0
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locKPlus1P4_Measured = dKPlus1Wrapper->Get_P4_Measured();
		TLorentzVector locKPlus2P4_Measured = dKPlus2Wrapper->Get_P4_Measured();
		TLorentzVector locKMinusP4_Measured = dKMinusWrapper->Get_P4_Measured();
		//Step 1
		TLorentzVector locPiMinusP4_Measured = dPiMinusWrapper->Get_P4_Measured();
		TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();

		/**** COMBINE FOUR-MOMENTUM ****/

		// DO YOUR STUFF HERE

		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locKPlus1P4_Measured + locKPlus2P4_Measured + locKMinusP4_Measured + locPiMinusP4_Measured + locProtonP4_Measured;
		TLorentzVector locXiP4_Measured =  locPiMinusP4_Measured + locKMinusP4_Measured + locProtonP4_Measured;
		TLorentzVector locXiP4_KinFit =  locKMinusP4 + locPiMinusP4 + locProtonP4;

		/**** EXECUTE ANALYSIS ACTIONS ****/

		// Loop through the analysis actions, executing them in order for the active particle combo
		if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
			continue;

		//if you manually execute any actions, and it fails a cut, be sure to call:
			//dComboWrapper->Set_IsComboCut(true);

		/**** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES ****/

		/*
		TLorentzVector locMyComboP4(8.0, 7.0, 6.0, 5.0);
		//for arrays below: 2nd argument is value, 3rd is array index
		//NOTE: By filling here, AFTER the cuts above, some indices won't be updated (and will be whatever they were from the last event)
			//So, when you draw the branch, be sure to cut on "IsComboCut" to avoid these.
		dTreeInterface->Fill_Fundamental<Float_t>("my_combo_array", -2*loc_i, loc_i);
		dTreeInterface->Fill_TObject<TLorentzVector>("my_p4_array", locMyComboP4, loc_i);
		*/

		/**** EXAMPLE: HISTOGRAM BEAM ENERGY ****/

			if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		{
			dHist_BeamEnergy->Fill(locBeamP4.E());
			locUsedSoFar_BeamEnergy.insert(locBeamID);
		}

		/**** EXAMPLE: HISTOGRAM MISSING MASS SQUARED ****/
/*
		//Missing Mass Squared
		double locMissingMassSquared = locMissingP4_Measured.M2();

		//Uniqueness tracking: Build the map of particles used for the missing mass
			//For beam: Don't want to group with final-state photons. Instead use "Unknown" PID (not ideal, but it's easy).
		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_MissingMass[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_MissingMass[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_MissingMass[KMinus].insert(locKMinusTrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);

		//compare to what's been used so far
		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
		{
			//unique missing mass combo: histogram it, and register this combo of particles
			dHist_MissingMassSquared->Fill(locMissingMassSquared);
			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
		}

		//E.g. Cut
		//if((locMissingMassSquared < -0.04) || (locMissingMassSquared > 0.04))
		//{
		//	dComboWrapper->Set_IsComboCut(true);
		//	continue;
		//}
*/

		//E.g.  ChiSq 
		Float_t locChiSq = dComboWrapper->Get_ChiSq_KinFit("");
		Float_t locNDF = dComboWrapper->Get_NDF_KinFit("");
		map<Particle_t, set<Int_t> > locUsedThisCombo_ChiSq;
		locUsedThisCombo_ChiSq[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_ChiSq[KMinus].insert(locKMinusTrackID);
		locUsedThisCombo_ChiSq[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_ChiSq.find(locUsedThisCombo_ChiSq) == locUsedSoFar_ChiSq.end())
		{
			dHist_ChiSq->Fill(locChiSq);
			dHist_ChiSqXi->Fill(locChiSq, locXiP4_Measured.M());
			//cerr << locNDF << endl;
			locUsedSoFar_ChiSq.insert(locUsedThisCombo_ChiSq);
		}		
		//E.g. ChiSq Cut
		if((locChiSq > 22.0))
		{
			dComboWrapper->Set_IsComboCut(true);
			continue;
		}

		//E.g.  Phi
		map<Particle_t, set<Int_t> > locUsedThisCombo_Phi;
		locUsedThisCombo_Phi[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_Phi[KMinus].insert(locKMinusTrackID);
		locUsedThisCombo_Phi[KPlus].insert(locKPlus2TrackID);
		TLorentzVector locKPlusP4less_KinFit;	
		TLorentzVector locKPlusP4more_KinFit;	
		TLorentzVector locKPlusP4less_Measured;	
		TLorentzVector locKPlusP4more_Measured;	
		if(locKPlus1P4.Theta() < 15*TMath::Pi()/180.) { 
			locKPlusP4less_KinFit = locKPlus1P4; 
			locKPlusP4more_KinFit = locKPlus2P4;
			locKPlusP4less_Measured = locKPlus1P4_Measured; 
			locKPlusP4more_Measured = locKPlus2P4_Measured;}
		else { 
			locKPlusP4less_KinFit = locKPlus2P4; 
			locKPlusP4more_KinFit = locKPlus1P4;
			locKPlusP4less_Measured = locKPlus2P4_Measured; 
			locKPlusP4more_Measured = locKPlus1P4_Measured;}
		TLorentzVector locKKless_KinFit = locKPlusP4less_KinFit + locKMinusP4;	
		TLorentzVector locKKless_Measured = locKPlusP4less_Measured + locKMinusP4_Measured;	
		TLorentzVector locKKmore_KinFit= locKPlusP4more_KinFit + locKMinusP4;
		TLorentzVector locKKmore_Measured = locKPlusP4more_Measured + locKMinusP4_Measured;	
		TLorentzVector locX4 = dComboBeamWrapper->Get_X4();
		double locRFTime = dComboWrapper->Get_RFTime_Measured();
		double dTargetCenterZ = dComboWrapper->Get_TargetCenter().Z();
		double locPropagatedRFTime = locRFTime + (locX4.Z() - dTargetCenterZ)/29.9792458;
		double locDeltaT = locX4.T() - locPropagatedRFTime;
		if(locUsedSoFar_Phi.find(locUsedThisCombo_Phi) == locUsedSoFar_Phi.end()){
			if(fabs(locDeltaT) < 6.004) {	
				dHist_KKMassless_Measured->Fill(locKKless_Measured.M());
				dHist_KKMassless_KinFit->Fill(locKKless_KinFit.M());
				dHist_KKMassmore_Measured->Fill(locKKmore_Measured.M());
				dHist_KKMassmore_KinFit->Fill(locKKmore_KinFit.M());
			}
			locUsedSoFar_Phi.insert(locUsedThisCombo_Phi);
		}
/*		
		//E.g. Phi
		if((locChiSq > 38.5))
		{
			dComboWrapper->Set_IsComboCut(true);
			continue;
		}
*/
		//E.g.  PostCuts Hists 
		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts;
		locUsedThisCombo_PostCuts[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_PostCuts[KMinus].insert(locKMinusTrackID);
		locUsedThisCombo_PostCuts[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_PostCuts.find(locUsedThisCombo_PostCuts) == locUsedSoFar_PostCuts.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					dHist_XiMass_Measured->Fill(locXiP4_Measured.M());
					dHist_XiMass_KinFit->Fill(locXiP4_KinFit.M());
					dHist_K_pTheta_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P());
					dHist_K_pTheta_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P());
				}
				else { 
					dHist_XiMass_Measured_acc->Fill(locXiP4_Measured.M());
					dHist_XiMass_KinFit_acc->Fill(locXiP4_KinFit.M());
					dHist_K_pTheta_Measured_acc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P());
					dHist_K_pTheta_Measured_acc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P());
				}
			}
			locUsedSoFar_PostCuts.insert(locUsedThisCombo_PostCuts);	
		}	
		/**** FILL FLAT TREE (IF DESIRED) ****/

		/*
		//FILL ANY CUSTOM BRANCHES FIRST!!
		Int_t locMyInt_Flat = 7;
		dFlatTreeInterface->Fill_Fundamental<Int_t>("flat_my_int", locMyInt_Flat);

		TLorentzVector locMyP4_Flat(4.0, 3.0, 2.0, 1.0);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("flat_my_p4", locMyP4_Flat);

		for(int loc_j = 0; loc_j < locMyInt_Flat; ++loc_j)
		{
			dFlatTreeInterface->Fill_Fundamental<Int_t>("flat_my_int_array", 3*loc_j, loc_j); //2nd argument = value, 3rd = array index
			TLorentzVector locMyComboP4_Flat(8.0, 7.0, 6.0, 5.0);
			dFlatTreeInterface->Fill_TObject<TLorentzVector>("flat_my_p4_array", locMyComboP4_Flat, loc_j);
		}
		*/

		//FILL FLAT TREE
		//Fill_FlatTree(); //for the active combo
	} // end of combo loop

	//FILL HISTOGRAMS: Num combos / events surviving actions
	Fill_NumCombosSurvivedHists();

	/**** LOOP OVER THROWN DATA (OPTIONAL) ****/
/*
	//Thrown beam: just use directly
	if(dThrownBeam != NULL)
		double locEnergy = dThrownBeam->Get_P4().E();

	//Loop over throwns
	for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dThrownWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/
	/**** LOOP OVER OTHER ARRAYS (OPTIONAL) ****/
/*
	//Loop over beam particles (note, only those appearing in combos are present)
	for(UInt_t loc_i = 0; loc_i < Get_NumBeam(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dBeamWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over charged track hypotheses
	for(UInt_t loc_i = 0; loc_i < Get_NumChargedHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dChargedHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over neutral particle hypotheses
	for(UInt_t loc_i = 0; loc_i < Get_NumNeutralHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dNeutralHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/

	/**** EXAMPLE: FILL CLONE OF TTREE HERE WITH CUTS APPLIED ****/
/*
	Bool_t locIsEventCut = true;
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i) {
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);
		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut())
			continue;
		locIsEventCut = false; // At least one combo succeeded
		break;
	}
	if(!locIsEventCut && dOutputTreeFileName != "")
		Fill_OutputTree();
*/

	return kTRUE;
}

void DSelector_kpkpkmlamb::Finalize(void)
{
	//Save anything to output here that you do not want to be in the default DSelector output ROOT file.

	//Otherwise, don't do anything else (especially if you are using PROOF).
		//If you are using PROOF, this function is called on each thread,
		//so anything you do will not have the combined information from the various threads.
		//Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

	//DO YOUR STUFF HERE

	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
