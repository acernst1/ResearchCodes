#include "DSelector_kpkpxim.h"

double getphi(TLorentzVector P4){
		// Returns a phi angle between -180deg and 180deg
		double phi = P4.Phi()*180/TMath::Pi();
		if(phi < -180.) phi += 360.;
		if(phi >  180.) phi -= 360.;
		return phi;
}

void DSelector_kpkpxim::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "kpkpxim.root"; //"" for none
	dOutputTreeFileName = ""; //"" for none
	dFlatTreeFileName = ""; //output flat tree (one combo per tree entry), "" for none
	dFlatTreeName = ""; //if blank, default name will be chosen

	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	Get_ComboWrappers();
	dPreviousRunNumber = 0;

/*********************************** EXAMPLE USER INITIALIZATION: ANALYSIS ACTIONS **********************************/

	//ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
	//false/true below: use measured/kinfit data

	//PID
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));

	//MASSES
	deque<Particle_t> locLambdaPIDs;  locLambdaPIDs.push_back(Proton); locLambdaPIDs.push_back(PiMinus); 
	deque<Particle_t> locXiPIDs;  locXiPIDs.push_back(Lambda);  locXiPIDs.push_back(PiMinus); 
	deque<Particle_t> locKXiPIDs;  locKXiPIDs.push_back(XiMinus);  locKXiPIDs.push_back(KPlus);   
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda, 200, 1.0, 1.2, "Lambda"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false,  XiMinus, 200, 1.1, 1.5, "XiMinus"));		
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, XiMinus, 200, 1.1, 1.5, "XiMinus_KinFit"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKXiPIDs, 250, 1.5, 3.0, "KpXim"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, locKXiPIDs, 250, 1.5, 3.0, "KpXim_KinFit"));

	//KINFIT RESULTS
	dAnalysisActions.push_back(new DHistogramAction_KinFitResults(dComboWrapper));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, false));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true, "KinFit"));

	//INITIALIZE ACTIONS
	//If you create any actions that you want to run manually (i.e. don't add to dAnalysisActions), be sure to initialize them here as well
	Initialize_Actions();

/******************************** USER INITIALIZATION: STAND-ALONE HISTOGRAMS *******************************/

	//General Histograms
	//In general, accidental subtrraction is performed by creating two histograms, one in-time, and one containing the events located in the nearest sideband peaks. 
	//The nominal naming scheme for these histograms is:
		// X for the in-time events, 
		// X_acc for out-of-time events (ACCidentals), 
		// X_wacc for out-of-time events with the scaling factor (Weighted ACCidentals)
	dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 600, -0.06, 0.06);
	dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
	dHist_BeamBunch_Asym = new TH1I("BeamBunch_Asym", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_BeamBunch_Xi = new TH1I("BeamBunch_Xi", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_BeamBunch_Xi_acc = new TH1I("BeamBunch_Xi_acc", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_BeamBunch_Xi_wacc = new TH1I("BeamBunch_Xi_wacc", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_ChiSq = new TH1I("ChiSq", ";X^{2}/NDF", 200, 0.0, 100.0);
	dHist_ChiSqXi = new TH2I("ChiSqXi", " ;X^{2}/NDF; #Lambda#pi^{-} mass (GeV)",100,0.0,100.0,400,1.1,1.5);
	dHist_ChiSqXi_KinFit = new TH2I("ChiSqXi_KinFit", ";X^{2}/NDF; #Lambda#pi^{-} mass (GeV)",100,0.0,50.0,400,1.1,1.5);
	dHist_ChiSqXi_KinFit_acc = new TH2I("ChiSqXi_KinFit_acc", ";X^{2}/NDF;#Lambda#pi^{-} mass (GeV)",100,0.0,50.0,400,1.1,1.5);
	dHist_ChiSqXi_KinFit_wacc = new TH2I("ChiSqXi_KinFit_wacc", ";X^{2}/NDF;#Lambda#pi^{-} mass (GeV)",100,0.0,50.0,400,1.1,1.5);
	dHist_ChiSqXi_KinFit_postCL = new TH2I("ChiSqXi_KinFit_postCL", ";X^{2}/NDF; #Lambda#pi^{-} mass (GeV)",100,0.0,3.50,400,1.1,1.5);
	dHist_ChiSqXi_KinFit_postCL_wacc = new TH2I("ChiSqXi_KinFit_postCL_wacc", ";X^{2}/NDF;#Lambda#pi^{-} mass (GeV)",100,0.0,3.50,400,1.1,1.5);
	dHist_ChiSqKp = new TH2I("ChiSqKp", " ;X^{2}/NDF; p_{K}",100,0.0,100.0, 100,1.1,10.);
	dHist_ChiSqKp_wacc = new TH2I("ChiSqKp_wacc", " ;X^{2}/NDF; p_{K}",100,0.0,100.0, 100,1.1,10.);
	dHist_XiMass_Measured = new TH1I("XiMass","#Xi- Invariant Mass (GeV/c^{2})", 400,1.1,1.5);
	dHist_XiMass_KinFit = new TH1I("XiMass_KinFit","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_Measured_nan = new TH1I("XiMass_nan","#Xi- Invariant Mass (GeV/c^{2})", 400,1.1,1.5);
	dHist_XiMass_KinFit_nan = new TH1I("XiMass_KinFit_nan","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_Measured_wacc = new TH1I("XiMass_wacc","#Xi- Invariant Mass (GeV/c^{2})", 400,1.1,1.5);
	dHist_XiMass_KinFit_acc = new TH1I("XiMass_KinFit_acc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_KinFit_wacc = new TH1I("XiMass_KinFit_wacc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_Measured_nan_wacc = new TH1I("XiMass_nan_wacc","#Xi- Invariant Mass (GeV/c^{2})", 400,1.1,1.5);
	dHist_XiMass_KinFit_nan_wacc = new TH1I("XiMass_KinFit_nan_wacc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_MMKK_Measured = new TH1I("MMKK_Measured","MM(K^{+}K^{+}) (GeV/c^{2})", 400,1.1,1.5);
	dHist_MMKK_KinFit = new TH1I("MMKK_KinFit","MM(K^{+}K^{+}) (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_Xi_LambFlight = new TH2F("Xi_LambFlight", " ;#Lambda#pi^{-} mass (GeV); #sigma_{#Lambda}", 400, 1.1, 1.5,400, 0.0, 200.0);
	dHist_Xi_LambFlight_wacc = new TH2F("Xi_LambFlight_wacc", " ;#Lambda#pi^{-} mass (GeV); #sigma_{#Lambda}", 400, 1.1, 1.5,400, 0.0, 200.0);
	dHist_Xi_XiFlight = new TH2F("Xi_XiFlight", " ;#Lambda#pi^{-} mass (GeV); #sigma_{#Xi}", 400, 1.1, 1.5,400, 0.0, 200.0);
	dHist_Xi_XiFlight_wacc = new TH2F("Xi_XiFlight_wacc", " ;#Lambda#pi^{-} mass (GeV); #sigma_{#Xi}", 400, 1.1, 1.5,400, 0.0, 200.0);

	//plots to check vertices
	dHist_ProdVert_preCL = new TH1I("ProdVert_preCL", ";Production Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiVert_preCL = new TH1I("XiVert_preCL", ";#Xi^{-} Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambVert_preCL = new TH1I("LambVert_preCL", ";#Lambda Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiPath_preCL = new TH1I("XiPathLength_preCL", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_LambPath_preCL = new TH1I("LambPathLength_preCL", ";#Lambda Path Length (cm)", 600, 0.0, 15.0);
	dHist_ProdVert_postCL = new TH1I("ProdVert_postCL", ";Production Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiVert_postCL = new TH1I("XiVert_postCL", ";#Xi^{-} Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambVert_postCL = new TH1I("LambVert_postCL", ";#Lambda Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiPath_postCL = new TH1I("XiPathLength_postCL", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_LambPath_postCL = new TH1I("LambPathLength_postCL", ";#Lambda Path Length (cm)", 600, 0.0, 15.0);
	dHist_ProdVert_preCL_wacc = new TH1I("ProdVert_preCL_wacc", ";Production Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiVert_preCL_wacc = new TH1I("XiVert_preCL_wacc", ";#Xi^{-} Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambVert_preCL_wacc = new TH1I("LambVert_preCL_wacc", ";#Lambda Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiPath_preCL_wacc = new TH1I("XiPathLength_preCL_wacc", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_LambPath_preCL_wacc = new TH1I("LambPathLength_preCL_wacc", ";#Lambda Path Length (cm)", 600, 0.0, 15.0);
	dHist_ProdVert_postCL_wacc = new TH1I("ProdVert_postCL_wacc", ";Production Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiVert_postCL_wacc = new TH1I("XiVert_postCL_wacc", ";#Xi^{-} Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambVert_postCL_wacc = new TH1I("LambVert_postCL_wacc", ";#Lambda Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiPath_postCL_wacc = new TH1I("XiPathLength_postCL_wacc", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_LambPath_postCL_wacc = new TH1I("LambPathLength_postCL_wacc", ";#Lambda Path Length (cm)", 600, 0.0, 15.0);
	dHist_LambPathSig_postCL = new TH1I("LambPathLengthSig_postCL", ";#Lambda Path Length #sigma", 600, 0.0, 15.0);
	dHist_LambPathSig_postCL_wacc = new TH1I("LambPathLengthSig_postCL_wacc", ";#Lambda Path Length #sigma", 600, 0.0, 15.0);
	
	//plots for beam asymmetry
	dHist_phi_t = new TH2I("phi_t", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 1000, 0.0, 5.0,180, -180., 180.);
	dHist_wacc_phi_t_1 = new TH2I("wacc_phi_t_1", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 1000, 0.0, 5.0,180, -180., 180.);
	dHist_wacc_phi_t_2 = new TH2I("wacc_phi_t_2", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 1000, 0.0, 5.0,180, -180., 180.);
	dHist_wacc_phi_t_3 = new TH2I("wacc_phi_t_3", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 1000, 0.0, 5.0,180, -180., 180.);
	dHist_wacc_phi_t_4 = new TH2I("wacc_phi_t_4", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 1000, 0.0, 5.0,180, -180., 180.);

	//plots for spin measurement of Xi-
	dHist_Xi_cosGJ = new TH2I("Xi_cosGJ", " ;#Lambda#pi^{-} mass (GeV); cos #theta_{GJ}", 400, 1.1, 1.5,180, -1., 1.);
	dHist_Xi_cosGJ_wacc = new TH2I("Xi_cosGJ_wacc", " ;#Lambda#pi^{-} mass (GeV); cos #theta_{GJ}", 400, 1.1, 1.5,180, -1., 1.);
	
	//plots for cross section measurements. The work mainly used dHist_Xi_Egamma_t_06X to calculate the differential cross section in terms of Egamma and t and cross sections in terms of Egamma or t
	//Several of these plots have 06X in their naming scheme. This denotes the starting beam energy for the plot. (i.g. 064 = 6.4 GeV)
	dHist_Xi_Egamma_064 = new TH2F("Xi_Egamma_064", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma}", 400, 1.1, 1.5,100,6.4,11.4);
	dHist_Xi_Egamma_064_wacc = new TH2F("Xi_Egamma_064_wacc", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma}", 400, 1.1, 1.5,100,6.4,11.4);
	dHist_Xi_Egamma = new TH2F("Xi_Egamma", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma}", 400, 1.1, 1.5,180, 3.0, 12.0);
	dHist_Xi_Egamma_acc = new TH2F("Xi_Egamma_acc", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV)", 400, 1.1, 1.5,180, 3.0, 12.0);
	dHist_Xi_Egamma_wacc = new TH2F("Xi_Egamma_wacc", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV)", 400, 1.1, 1.5,180, 3.0, 12.0);
	dHist_Xi_t = new TH2F("Xi_t", " ;#Lambda#pi^{-} mass (GeV); -t (GeV/c)^{2}", 400, 1.1, 1.5,200, 0.0, 10.0);
	dHist_Xi_t_acc = new TH2F("Xi_t_acc", " ;#Lambda#pi^{-} mass (GeV); -t (GeV/c)^{2}", 400, 1.1, 1.5,200, 0.0, 10.0);
	dHist_Xi_t_wacc = new TH2F("Xi_t_wacc", " ;#Lambda#pi^{-} mass (GeV); -t (GeV/c)^{2}", 400, 1.1, 1.5,200, 0.0, 10.0);
	dHist_Xi_Egamma_t = new TH3F("Xi_Egamma_t",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,180, 3.0, 12.0,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_acc = new TH3F("Xi_Egamma_t_acc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,180, 3.0, 12.0,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_wacc = new TH3F("Xi_Egamma_t_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,180, 3.0, 12.0,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_063 = new TH3F("Xi_Egamma_t_063",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.3,11.3,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_063_acc = new TH3F("Xi_Egamma_t_063_acc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.3,11.3,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_063_wacc = new TH3F("Xi_Egamma_t_063_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.3,11.3,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064 = new TH3F("Xi_Egamma_t_064",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_acc = new TH3F("Xi_Egamma_t_064_acc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_wacc = new TH3F("Xi_Egamma_t_064_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_065 = new TH3F("Xi_Egamma_t_065",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.5,11.5,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_065_acc = new TH3F("Xi_Egamma_t_065_acc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.5,11.5,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_065_wacc = new TH3F("Xi_Egamma_t_065_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.5,11.5,200, 0.0, 10.0);

	// X_alltracked denotes that all the particles are tracked for the uniqueness
	dHist_Xi_Egamma_t_064_alltracked = new TH3F("Xi_Egamma_t_064_alltracked",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_alltracked_acc = new TH3F("Xi_Egamma_t_064_alltracked_acc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_alltracked_wacc = new TH3F("Xi_Egamma_t_064_alltracked_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);

	//	X_thrownEgamma is to check the effect of using the thrown vs the reconstructed beam photon for the binning of the cross section
	dHist_Xi_thrownEgamma_t_064 = new TH3F("Xi_thrownEgamma_t_064",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_thrownEgamma_t_064_wacc = new TH3F("Xi_thrownEgamma_t_064_wacc",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	
	// X_lowerTarget and X_upperTarget is to see the effect of where the event is within the target. There should be no effect due to this as the physics shouldn't matter. 
	// This test ultimately didn't work as the Monte Carlo was generated using only the center of the target.
	dHist_Xi_Egamma_t_064_lowerTarget = new TH3F("Xi_Egamma_t_064_lowerTarget",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_lowerTarget_wacc = new TH3F("Xi_Egamma_t_064_lowerTarget_wacc",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_upperTarget = new TH3F("Xi_Egamma_t_064_upperTarget",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	dHist_Xi_Egamma_t_064_upperTarget_wacc = new TH3F("Xi_Egamma_t_064_upperTarget_wacc",";#Lambda#pi^{-} mass (GeV); thrown E_{#gamma} (GeV); -t (GeV/c)^{2}",400, 1.1, 1.5,100,6.4,11.4,200, 0.0, 10.0);
	
	// Histograms to calculate the effect of the ChiSq cut on the cross section. 
	dHist_Xi_Egamma_ChiSq_063 = new TH3F("Xi_Egamma_ChiSq_063",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDF",400, 1.1, 1.5,100,6.3,11.3,100, 0.0, 50.0);
	dHist_Xi_Egamma_ChiSq_063_wacc = new TH3F("Xi_Egamma_ChiSq_063_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDF",400, 1.1, 1.5,100,6.3,11.3,100, 0.0, 50.0);
	dHist_Xi_Egamma_ChiSq_064 = new TH3F("Xi_Egamma_ChiSq_064",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDFF",400, 1.1, 1.5,100,6.4,11.4,100, 0.0, 50.0);
	dHist_Xi_Egamma_ChiSq_064_wacc = new TH3F("Xi_Egamma_ChiSq_064_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDF",400, 1.1, 1.5,100,6.4,11.4,100, 0.0, 50.0);
	dHist_Xi_Egamma_ChiSq_065 = new TH3F("Xi_Egamma_ChiSq_065",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDF",400, 1.1, 1.5,100,6.5,11.5,100, 0.0, 50.0);
	dHist_Xi_Egamma_ChiSq_065_wacc = new TH3F("Xi_Egamma_ChiSq_065_wacc",";#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV); X^{2}/NDF",400, 1.1, 1.5,100,6.5,11.5,100, 0.0, 50.0);
	dHist_Xi_t_Truth = new TH2F("Xi_t_Truth", " ;#Lambda#pi^{-} mass (GeV); -t (GeV/c)^{2}", 400, 1.1, 1.5,200, 0.0, 10.0);

	dHist_Xi_Chisq_084 = new TH2F("Xi_Chisq_084", " ;#Lambda#pi^{-} mass (GeV); #Chi^{2}/NDF", 400, 1.1, 1.5,100, 0.0, 15.0);
	dHist_Xi_Chisq_084_wacc = new TH2F("Xi_Chisq_084_wacc", " ;#Lambda#pi^{-} mass (GeV); #Chi^{2}/NDF", 400, 1.1, 1.5,100, 0.0, 15.0);
	dHist_ChisqVsCL = new TH2F("ChisqVsCL", ";X^{2}/NDF; Confidence Level",400, 0.0, 100.0,40000, 0.0, 1.0);
	
	//For studying the intermediate hyperon
	dHist_KlowpXim = new TH1I("KlowpXim",";K_{plow}#Xi^{-} mass (GeV)", 240,1.7,2.9);
	dHist_KlowpXim_Truth = new TH1I("KlowpXim_Truth",";K_{plow}#Xi^{-} mass (GeV)", 240,1.7,2.9);
	dHist_KlowpXim_wacc = new TH1I("KlowpXim_wacc",";K_{plow}#Xi^{-} mass (GeV)", 240,1.7,2.9);
	dHist_Klowp_pvstheta = new TH2I("Klowp_pvstheta", "K^{+}_{p low}; #theta; p (GeV) ",28,0.0,140,40,0.0,10.0);
	dHist_Khighp_pvstheta = new TH2I("Khighp_pvstheta", "K^{+}_{p high}; #theta; p (GeV) ",28,0.0,140,40,0.0,10.0);
	dHist_Klowp_pvstheta_wacc = new TH2I("Klowp_pvstheta_wacc", "K^{+}_{p low}; #theta; p (GeV) ",28,0.0,140,40,0.0,10.0);
	dHist_Khighp_pvstheta_wacc = new TH2I("Khighp_pvstheta_wacc", "K^{+}_{p high}; #theta; p (GeV) ",28,0.0,140,40,0.0,10.0);

	//angular distributions for every particle
	dHist_K_pThetaPhi_Measured = new TH3I("K_pThetaPhi_Measured", "K^{+} ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_p_pThetaPhi_Measured = new TH3I("p_pThetaPhi_Measured", "p ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_pi_pThetaPhi_Measured = new TH3I("pi_pThetaPhi_Measured", "#pi^{-} ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_K_pThetaPhi_Measured_wacc = new TH3I("K_pThetaPhi_Measured_wacc", "K^{+} ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_p_pThetaPhi_Measured_wacc = new TH3I("p_pThetaPhi_Measured_wacc", "p ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_pi_pThetaPhi_Measured_wacc = new TH3I("pi_pThetaPhi_Measured_wacc", "#pi^{-} ;Measured #theta (deg.) ;Measured p (GeV);Measured #phi (deg)",28,0.0,140,40,0.0,10.0, 180,-180., 180.);
	dHist_allK_phiTheta_CM_KinFit = new TH2I("allK_phiTheta_CM_KinFit", "K^{+}_{highp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_allK_phiTheta_CM_KinFit_wacc = new TH2I("allK_phiTheta_CM_KinFit_wacc", "K^{+}_{highp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Khighp_phiTheta_CM_KinFit = new TH2I("Khighp_phiTheta_CM_KinFit", "K^{+}_{highp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_Ystar_KinFit = new TH2I("Klowp_phiTheta_Ystar_KinFit", "K^{+}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Khighp_phiTheta_CM_KinFit_wacc = new TH2I("Khighp_phiTheta_CM_KinFit_wacc", "K^{+}_{highp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_Ystar_KinFit_wacc = new TH2I("Klowp_phiTheta_Ystar_KinFit_wacc", "K^{+}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Khighp_phiTheta_CM_Truth = new TH2I("Khighp_phiTheta_CM_Truth", "K^{+}_{t} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_Ystar_Truth = new TH2I("Klowp_phiTheta_Ystar_Truth", "K^{+}_{decay} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0); 
	dHist_Ystar_p_Ystar_KinFit = new TH1I("Ystar_p_Ystar_KinFit", "Y^{*};KinFit p (GeV)",50,0.0,5.0);
	dHist_Ystar_p_Ystar_Measured = new TH1I("Ystar_p_Ystar_Measured", "Y^{*};Measured p (GeV)",50,0.0,5.0);
	dHist_Ystar_p_Ystar_KinFit_wacc = new TH1I("Ystar_p_Ystar_KinFit_wacc", "Y^{*};KinFit p (GeV)",50,0.0,5.0);
	dHist_Ystar_p_Ystar_Measured_wacc = new TH1I("Ystar_p_Ystar_Measured_wacc", "Y^{*};Measured p (GeV)",50,0.0,5.0);
	dHist_allK_phiTheta_Ystar_KinFit = new TH2I("allK_phiTheta_Ystar_KinFit", "K^{+};KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_allK_phiTheta_Ystar_Measured = new TH2I("allK_phiTheta_Ystar_Measured", "K^{+};Measured #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_allK_phiTheta_Ystar_KinFit_wacc = new TH2I("allK_phiTheta_Ystar_KinFit_wacc", "K^{+};KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_allK_phiTheta_Ystar_Measured_wacc = new TH2I("allK_phiTheta_Ystar_Measured_wacc", "K^{+};Measured #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Ystar_phiTheta_CM_KinFit = new TH2I("Ystar_phiTheta_CM_KinFit", "Y^{*} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_noXi_phiTheta_Ystar_KinFit = new TH2I("Klowp_noXi_phiTheta_Ystar_KinFit", "K^{+}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_noXi_phiTheta_Ystar_KinFit_wacc = new TH2I("Klowp_noXi_phiTheta_Ystar_KinFit_wacc", "K^{+}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Xi_phiTheta_Ystar_KinFit = new TH2I("Xi_phiTheta_Ystar_KinFit", "#Xi^{-}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_Xi_phiTheta_Ystar_KinFit_wacc = new TH2I("Xi_phiTheta_Ystar_KinFit_wacc", "#Xi^{-}_{lowp} ;KinFit #theta (deg); KinFit #phi (deg)",30,0.0,180,180,-180,180.0);
	dHist_KXi_dTheta_Ystar_KinFit = new TH1I("KXi_dTheta_Ystar_KinFit", "#theta_{#Xi} - #theta_{Kdecay} in Y^{*} rest frame; #theta_{#Xi} - #theta_{Kdecay} (deg)",90,0,180);
	dHist_KXi_dTheta_Ystar_KinFit_wacc = new TH1I("KXi_dTheta_Ystar_KinFit_wacc", "#theta_{#Xi} - #theta_{Kdecay} in Y^{*} rest frame; #theta_{#Xi} - #theta_{Kdecay} (deg)",90,0,180);
	dHist_KYstar_dMass_Ystar_KinFit = new TH1I("KYstar_dMass_Ystar_KinFit", "M_{Y*} - M_{Kdecay} in Y^{*} rest frame; M_{Y*} - M_{Kdecay} (GeV)",80,1.1,1.5);
	dHist_KYstar_dMass_Ystar_KinFit_wacc = new TH1I("KYstar_dMass_Ystar_KinFit_wacc", "M_{Y*} - M_{Kdecay} in Y^{*} rest frame; M_{Y*} - M_{Kdecay} (GeV)",80,1.1,1.5);
	dHist_Khighp_choicevstruth_KinFit = new TH2I("Khighp_choicevstruth_KinFit", "K_{decay} p;chosen K p (GeV); truth K p (GeV)",40,0,10,40,0,10);
	dHist_Klowp_choicevstruth_KinFit = new TH2I("Klowp_choicevstruth_KinFit", "K_{t} p;chosen K p (GeV); truth K p (GeV)",40,0,10,40,0,10);
	dHist_Klowp_phiTheta_YstarGJ = new TH2I("Klowp_phiTheta_YstarGJ_KinFit", "K^{+}_{decay};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Xi_phiTheta_YstarGJ = new TH2I("Xi_phiTheta_YstarGJ_KinFit", "#Xi^{-};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_YstarGJ_wacc = new TH2I("Klowp_phiTheta_YstarGJ_KinFit_wacc", "K^{+}_{decay};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Xi_phiTheta_YstarGJ_wacc = new TH2I("Xi_phiTheta_YstarGJ_KinFit_wacc", "#Xi^{-};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	
	dHist_Klowp_phiTheta_YstarGJ_reconthrown = new TH2I("Klowp_phiTheta_YstarGJ_reconthrown", "K^{+}_{decay};#theta_{GJ} (deg);  #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_dtheta_reconthrown = new TH1I("Klowp_dtheta_reconthrown", "#theta^{K^+}_{thrown} - #theta^{K^+}_{recon}; #theta_{thrown} - #theta_{recon} (deg)",90,-45,45);
	dHist_Klowp_phiTheta_YstarGJ_thrown150to180 = new TH2I("Klowp_phiTheta_YstarGJ_thrown150to180", "K^{+}_{decay};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_phiTheta_YstarGJ_reconthrown_wacc = new TH2I("Klowp_phiTheta_YstarGJ_reconthrown_wacc", "K^{+}_{decay};#theta_{GJ} (deg);  #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);
	dHist_Klowp_dtheta_reconthrown_wacc = new TH1I("Klowp_dtheta_reconthrown_wacc", "#theta^{K^+}_{thrown} - #theta^{K^+}_{recon}; #theta_{thrown} - #theta_{recon} (deg)",90,-45,45);
	dHist_Klowp_phiTheta_YstarGJ_thrown150to180_wacc = new TH2I("Klowp_phiTheta_YstarGJ_thrown150to180_wacc", "K^{+}_{decay};KinFit #theta_{GJ} (deg); KinFit #phi_{GJ} (deg)",30,0.0,180,180,-180,180.0);

	dHist_XiMass_KinFit_Selected = new TH1I("XiMass_KinFit_Selected","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_K_pEgamma_Measured = new TH2I("K_pEgamma_Measured", "K^{+} ;E_{#gamma}; Measured p (GeV)",180,3.0,12.0,40,0.0,10.0);
	dHist_p_pEgamma_Measured = new TH2I("p_pEgamma_Measured", "p ;E_{#gamma}; Measured p (GeV)",180,3.0,12.0,40,0.0,10.0);
	dHist_pi_pEgamma_Measured = new TH2I("pi_pEgamma_Measured", "#pi^{-} ;E_{#gamma}; Measured p (GeV)",180,3.0,12.00,40,0.0,10.0);
	dHist_K_pEgamma_Measured_wacc = new TH2I("K_pEgamma_Measured_wacc", "K^{+} ;E_{#gamma}; Measured p (GeV)",180,3.0,12.0,40,0.0,10.0);
	dHist_p_pEgamma_Measured_wacc = new TH2I("p_pEgamma_Measured_wacc", "p ;E_{#gamma}; Measured p (GeV)",180,3.0,12.0,40,0.0,10.0);
	dHist_pi_pEgamma_Measured_wacc = new TH2I("pi_pEgamma_Measured_wacc", "#pi^{-} ;E_{#gamma}; Measured p (GeV)",180,3.0,12.00,40,0.0,10.0);
	dHist_K_pt_Measured = new TH2I("K_pt_Measured", "K^{+} ;-t; Measured p (GeV)",40,0.0,2.0,40,0.0,10.0);
	dHist_p_pt_Measured = new TH2I("p_pt_Measured", "p ;-t; Measured p (GeV)",40,0.0,2.0,40,0.0,10.0);
	dHist_pi_pt_Measured = new TH2I("pi_pt_Measured", "#pi^{-} ;-t; Measured p (GeV)",40,0.0,2.00,40,0.0,10.0);
	dHist_K_pt_Measured_wacc = new TH2I("K_pt_Measured_wacc", "K^{+} ;-t; Measured p (GeV)",40,0.0,2.0,40,0.0,10.0);
	dHist_p_pt_Measured_wacc = new TH2I("p_pt_Measured_wacc", "p ;-t; Measured p (GeV)",40,0.0,2.0,40,0.0,10.0);
	dHist_pi_pt_Measured_wacc = new TH2I("pi_pt_Measured_wacc", "#pi^{-} ;-t; Measured p (GeV)",40,0.0,2.00,40,0.0,10.0);
	dHist_K_pTheta_Measured = new TH2I("K_pTheta_Measured", "K^{+} ;Measured #theta; Measured p (GeV)",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_Measured = new TH2I("p_pTheta_Measured", "p ;Measured #theta; Measured p (GeV)",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_KinFit = new TH2I("p_pTheta_KinFit", "p ;Measured #theta; Measured p (GeV)",28,0.0,140,40,0.0,10.0);
	dHist_K_pTheta_KinFit = new TH2I("K_pTheta_KinFit", "K^{+} ;KinFit #theta; KinFit p (GeV) KinFit",28,0.0,140,40,0.0,10.0);
	dHist_K_ptTheta_Measured = new TH2I("K_ptTheta_Measured", "K^{+} ;Measured #theta; Measured p_{t} (GeV)",28,0.0,140,40,0.0,2.0);
	dHist_K_ptTheta_KinFit = new TH2I("K_ptTheta_KinFit", "K^{+} ;KinFit #theta; KinFit p_{t} (GeV)",28,0.0,140,40,0.0,2.0);
	dHist_XiMass_kTheta15to35_Measured = new TH1I("XiMass_kTheta_Measured","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_kTheta15to35_KinFit = new TH1I("XiMass_kTheta_KinFit","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_pi_pTheta_Measured = new TH2I("pi_pTheta_Measured", "#pi^{-} pvsTheta Measured",28,0.0,140,30,0.0,3.0);
	dHist_pi_pTheta_KinFit = new TH2I("pi_pTheta_KinFit", "#pi^{-} pvsTheta KinFit",28,0.0,140,30,0.0,3.0);
	dHist_pi_ptTheta_Measured = new TH2I("pi_ptTheta_Measured", "#pi^{-} ptvsTheta Measured",28,0.0,140,40,0.0,1.0);
	dHist_pi_ptTheta_KinFit = new TH2I("pi_ptTheta_KinFit", "#pi^{-} ptvsTheta KinFit",28,0.0,140,40,0.0,1.0);
	dHist_XiMass_piTheta15to35_Measured = new TH1I("XiMass_piTheta_Measured","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_piTheta15to35_KinFit = new TH1I("XiMass_piTheta_KinFit","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_Measured = new TH1I("XiMass_MM_piTheta_Measured","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_KinFit = new TH1I("XiMass_MM_piTheta_KinFit","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_Measured = new TH1I("XiMass_MM_kTheta_Measured","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_KinFit = new TH1I("XiMass_MM_kTheta_KinFit","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_K_pTheta_Measured_wacc = new TH2I("K_pTheta_Measured_wacc", "K^{+} pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_Measured_wacc = new TH2I("p_pTheta_Measured_wacc", "p pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_KinFit_wacc = new TH2I("p_pTheta_KinFit_wacc", "p pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_K_pTheta_KinFit_wacc = new TH2I("K_pTheta_KinFit_wacc", "K^{+} pvsTheta KinFit",28,0.0,140,40,0.0,10.0);
	dHist_K_ptTheta_Measured_wacc = new TH2I("K_ptTheta_Measured_wacc", "K^{+} ptvsTheta Measured",28,0.0,140,40,0.0,2.0);
	dHist_K_ptTheta_KinFit_wacc = new TH2I("K_ptTheta_KinFit_wacc", "K^{+} ptvsTheta KinFit",28,0.0,140,40,0.0,2.0);
	dHist_XiMass_KinFit_Selected_wacc = new TH1I("XiMass_KinFit_Selected_wacc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_MMKK_Measured_wacc = new TH1I("MMKK_Measured_wacc","MM(K^{+}K^{+}) (GeV/c^{2})", 400,1.1,1.5);
	dHist_MMKK_KinFit_wacc = new TH1I("MMKK_KinFit_wacc","MM(K^{+}K^{+}) (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_kTheta15to35_Measured_wacc = new TH1I("XiMass_kTheta_Measured_wacc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_kTheta15to35_KinFit_wacc = new TH1I("XiMass_kTheta_KinFit_wacc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_pi_pTheta_Measured_wacc = new TH2I("pi_pTheta_Measured_wacc", "#pi^{-} pvsTheta Measured",28,0.0,140,30,0.0,3.0);
	dHist_pi_pTheta_KinFit_wacc = new TH2I("pi_pTheta_KinFit_wacc", "#pi^{-} pvsTheta KinFit",28,0.0,140,30,0.0,3.0);
	dHist_pi_ptTheta_Measured_wacc = new TH2I("pi_ptTheta_Measured_wacc", "#pi^{-} ptvsTheta Measured",28,0.0,140,40,0.0,1.0);
	dHist_pi_ptTheta_KinFit_wacc = new TH2I("pi_ptTheta_KinFit_wacc", "#pi^{-} ptvsTheta KinFit",28,0.0,140,40,0.0,1.0);
	dHist_XiMass_piTheta15to35_Measured_wacc = new TH1I("XiMass_piTheta_Measured_wacc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_piTheta15to35_KinFit_wacc = new TH1I("XiMass_piTheta_KinFit_wacc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_Measured_wacc = new TH1I("XiMass_MM_piTheta_Measured_wacc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_KinFit_wacc = new TH1I("XiMass_MM_piTheta_KinFit_wacc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_Measured_wacc = new TH1I("XiMass_MM_kTheta_Measured_wacc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_KinFit_wacc = new TH1I("XiMass_MM_kTheta_KinFit_wacc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);

	//Output file initialization
	myfile = new ofstream("XiEventNumbers_brokenChiSq.txt");
		*myfile << "Run Number " << "Event Number " << "locXiP4_Measured.M() " << "locXiP4_KinFit.M()  " << "locChiSqNdf  " << "ConfidenceLevel "<< "locBeamP4.E() " << "locDeltaT " << endl;
		*myfile << "       " << "locKPlus1P4_Measured.P() " << "locKPlus2P4_Measured.P() " << "locProtonP4_Measured.P() " << "locPiMinus1P4_Measured.P() " << "locPiMinus2P4_Measured.P()" << endl;
		*myfile << "       " << "locKPlus1P4.P() " << "locKPlus2P4.P() " << "locProtonP4.P() " << "locPiMinus1P4.P() " << "locPiMinus2P4.P()" << endl;
	myP4file = new ofstream("XiP4forboosting.txt");

/************************** EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - MAIN TREE *************************/

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

/************************** EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - FLAT TREE *************************/

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

/************************************* ADVANCED EXAMPLE: CHOOSE BRANCHES TO READ ************************************/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

	//dTreeInterface->Clear_GetEntryBranches(); //now get none
	//dTreeInterface->Register_GetEntryBranch("Proton__P4"); //manually set the branches you want
}

Bool_t DSelector_kpkpxim::Process(Long64_t locEntry)
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

	// Updated Uniqueness tracking
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_gXi;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_gKK;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_gKhighXi;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_gKlowXi;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_gKKXi;

/**************************************** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES **************************************/

	/*
	Int_t locMyInt = 7;
	dTreeInterface->Fill_Fundamental<Int_t>("my_int", locMyInt);

	TLorentzVector locMyP4(4.0, 3.0, 2.0, 1.0);
	dTreeInterface->Fill_TObject<TLorentzVector>("my_p4", locMyP4);

	for(int loc_i = 0; loc_i < locMyInt; ++loc_i)
		dTreeInterface->Fill_Fundamental<Int_t>("my_int_array", 3*loc_i, loc_i); //2nd argument = value, 3rd = array index
	*/

/************************************************* LOOP OVER COMBOS *************************************************/

	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);

		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut()) // Is false when tree originally created
			continue; // Combo has been cut previously

	/********************************************** GET PARTICLE INDICES *********************************************/

		//Used for tracking uniqueness when filling histograms, and for determining unused particles

		//Step 0
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locKPlus1TrackID = dKPlus1Wrapper->Get_TrackID();
		Int_t locKPlus2TrackID = dKPlus2Wrapper->Get_TrackID();

		//Step 1
		Int_t locPiMinus1TrackID = dPiMinus1Wrapper->Get_TrackID();

		//Step 2
		Int_t locPiMinus2TrackID = dPiMinus2Wrapper->Get_TrackID();
		Int_t locProtonTrackID = dProtonWrapper->Get_TrackID();

	/*********************************************** GET FOUR-MOMENTUM **********************************************/

		// Get P4's: //is kinfit if kinfit performed, else is measured
		//dTargetP4 is target p4
		//Step 0
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locKPlus1P4 = dKPlus1Wrapper->Get_P4();
		TLorentzVector locKPlus2P4 = dKPlus2Wrapper->Get_P4();
		//Step 1
		TLorentzVector locPiMinus1P4 = dPiMinus1Wrapper->Get_P4();
		//Step 2
		TLorentzVector locDecayingLambdaP4 = dDecayingLambdaWrapper->Get_P4();
		TLorentzVector locPiMinus2P4 = dPiMinus2Wrapper->Get_P4();
		TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();

		// Get Measured P4's:
		//Step 0
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locKPlus1P4_Measured = dKPlus1Wrapper->Get_P4_Measured();
		TLorentzVector locKPlus2P4_Measured = dKPlus2Wrapper->Get_P4_Measured();
		//Step 1
		TLorentzVector locPiMinus1P4_Measured = dPiMinus1Wrapper->Get_P4_Measured();
		//Step 2
		TLorentzVector locPiMinus2P4_Measured = dPiMinus2Wrapper->Get_P4_Measured();
		TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();

	/********************************************* COMBINE FOUR-MOMENTUM ********************************************/

		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locKPlus1P4_Measured + locKPlus2P4_Measured + locPiMinus1P4_Measured + locPiMinus2P4_Measured + locProtonP4_Measured;
		TLorentzVector locXiP4_Measured =  locPiMinus1P4_Measured + locPiMinus2P4_Measured + locProtonP4_Measured;
		TLorentzVector locXiP4_KinFit =  locPiMinus1P4 + locPiMinus2P4 + locProtonP4;
		TLorentzVector locLambdaP4_Measured = locPiMinus2P4_Measured + locProtonP4_Measured;
		TLorentzVector locMMKKP4_Measured = locBeamP4_Measured + dTargetP4 - locKPlus1P4_Measured - locKPlus2P4_Measured;
		TLorentzVector locMMKKP4_KinFit = locBeamP4 + dTargetP4 - locKPlus1P4 - locKPlus2P4;

		//Path length and flight significance calculations
		//TLorentzVector locDecayingLambdaP4 = locPiMinus2P4 +	locProtonP4; //Decaying Lambda for M18 is manually calculated
		TLorentzVector locDecayingLambdaX4 = dDecayingLambdaWrapper->Get_X4(); //Doesn't exist for M18
		TLorentzVector locDecayingXiX4 = dTreeInterface->Get_TObject<TLorentzVector>("DecayingXiMinus__X4",loc_i);
		TLorentzVector locDecayingLambX4 = dTreeInterface->Get_TObject<TLorentzVector>("DecayingLambda__X4",loc_i);
		TLorentzVector locProdSpacetimeVertex = dComboBeamWrapper->Get_X4();//Get production vertex
		TLorentzVector locDeltaSpacetimeXi = locProdSpacetimeVertex - locDecayingXiX4;//vertex difference
		TLorentzVector locDeltaSpacetimeLamb = locDecayingXiX4 - locDecayingLambX4;//vertex difference
		double locPathLengthXi = locDeltaSpacetimeXi.Vect().Mag();//pathlength is just the magnitude
		double locPathLengthLamb = locDeltaSpacetimeLamb.Vect().Mag();//pathlength is just the magnitude
		float locPathLengthSigmaXi = Get_Fundamental<Float_t>("DecayingXiMinus__PathLengthSigma", loc_i);
		float locPathLengthSigmaLamb = Get_Fundamental<Float_t>("DecayingLambda__PathLengthSigma", loc_i);
		double locPathLengthSignificanceXi = locPathLengthXi/locPathLengthSigmaXi;
		double locPathLengthSignificanceLamb = locPathLengthLamb/locPathLengthSigmaLamb;

		//BoostVector for CoM with KinFit and Measured 4vectors
		TLorentzVector locCoMP4_KinFit = locBeamP4 + dTargetP4;
		TVector3 boostCoM_KinFit = locCoMP4_KinFit.BoostVector();
		TLorentzVector locCoMP4_Measured = locBeamP4_Measured + dTargetP4;
		TVector3 boostCoM_Measured = locCoMP4_Measured.BoostVector();
		//Boost in CoM for KinFit 4Vectors
		TLorentzVector locBeamP4_KinFit_CM = locBeamP4;
		TLorentzVector locKPlus1P4_KinFit_CM = locKPlus1P4;
		TLorentzVector locKPlus2P4_KinFit_CM = locKPlus2P4;
		TLorentzVector locXiP4_KinFit_CM = locXiP4_KinFit;
		TLorentzVector locPiMinus1P4_KinFit_CM = locPiMinus1P4;
		TLorentzVector locDecayingLambdaP4_KinFit_CM =  locDecayingLambdaP4;
		locBeamP4_KinFit_CM.Boost(-boostCoM_KinFit);
		locKPlus1P4_KinFit_CM.Boost(-boostCoM_KinFit);
		locKPlus2P4_KinFit_CM.Boost(-boostCoM_KinFit);
		locXiP4_KinFit_CM.Boost(-boostCoM_KinFit);
		locPiMinus1P4_KinFit_CM.Boost(-boostCoM_KinFit);
		locDecayingLambdaP4_KinFit_CM.Boost(-boostCoM_KinFit);
		//Boost in CoM for Measured 4vectors
		TLorentzVector locBeamP4_Measured_CM = locBeamP4_Measured;
		TLorentzVector locKPlus1P4_Measured_CM = locKPlus1P4_Measured;
		TLorentzVector locKPlus2P4_Measured_CM = locKPlus2P4_Measured;
		TLorentzVector locXiP4_Measured_CM = locXiP4_Measured;
		TLorentzVector locPiMinus1P4_Measured_CM = locPiMinus1P4_Measured;
		TLorentzVector locDecayingLambdaP4_Measured_CM = locLambdaP4_Measured;
		locBeamP4_Measured_CM.Boost(-boostCoM_Measured);
		locKPlus1P4_Measured_CM.Boost(-boostCoM_Measured);
		locKPlus2P4_Measured_CM.Boost(-boostCoM_Measured);
		locXiP4_Measured_CM.Boost(-boostCoM_Measured);
		locPiMinus1P4_Measured_CM.Boost(-boostCoM_Measured);
		locDecayingLambdaP4_Measured_CM.Boost(-boostCoM_Measured);

		//BoostVector for Gottfried-Jackson Frame
		TVector3 boostGJ = locXiP4_KinFit_CM.BoostVector();
		//Boost in GJ
		TLorentzVector locBeamP4_GJ = locBeamP4_KinFit_CM;
		TLorentzVector locKPlus1P4_GJ = locKPlus1P4_KinFit_CM;
	    TLorentzVector locKPlus2P4_GJ = locKPlus2P4_KinFit_CM;
		TLorentzVector locXiP4_GJ = locXiP4_KinFit_CM;
	    TLorentzVector locPiMinus1P4_GJ = locPiMinus1P4_KinFit_CM;
	    TLorentzVector locDecayingLambdaP4_GJ =  locDecayingLambdaP4_KinFit_CM;
		locBeamP4_GJ.Boost(-boostGJ);
		locKPlus1P4_GJ.Boost(-boostGJ);
		locKPlus2P4_GJ.Boost(-boostGJ);
		locXiP4_GJ.Boost(-boostGJ);
		locPiMinus1P4_GJ.Boost(-boostGJ);
		locDecayingLambdaP4_GJ.Boost(-boostGJ);
		//GJ Frame
		TVector3 z_GJ;
		z_GJ.SetXYZ(locBeamP4_GJ.X(),locBeamP4_GJ.Y(),locBeamP4_GJ.Z());
		TVector3 z_hat_GJ = z_GJ.Unit();
		TVector3 y_GJ = locBeamP4_KinFit_CM.Vect().Cross(locXiP4_KinFit_CM.Vect());
		TVector3 y_hat_GJ = y_GJ.Unit();
		TVector3 x_hat_GJ = y_hat_GJ.Cross(z_hat_GJ);
		//Definition of Angles in GJ frame
		TVector3 v_GJ(locPiMinus1P4_GJ.Vect()*x_hat_GJ,locPiMinus1P4_GJ.Vect()*y_hat_GJ,locPiMinus1P4_GJ.Vect()*z_hat_GJ);
		double cosTheta_GJ = v_GJ.CosTheta();
		double theta_GJ = v_GJ.Theta();
		double phi_GJ = v_GJ.Phi()*180./TMath::Pi();

		//Kaon determination 
		TLorentzVector locKPlusP4_lowp_KinFit;
		TLorentzVector locKPlusP4_highp_KinFit;
		TLorentzVector locKPlusP4_highp_KinFit_CM;	
		TLorentzVector locKPlusP4_lowp_KinFit_CM;
		TLorentzVector locKPlusP4_lowp_Measured;
		TLorentzVector locKPlusP4_highp_Measured;
		TLorentzVector locKPlusP4_lowp_Measured_CM;
		TLorentzVector locKPlusP4_highp_Measured_CM;	
		Int_t locKhighTrackID;
		Int_t locKlowTrackID;	
		if(locKPlus1P4.Theta() < locKPlus2P4.Theta()) { 
			locKPlusP4_highp_KinFit = locKPlus1P4; 
			locKPlusP4_lowp_KinFit = locKPlus2P4;
			locKhighTrackID = locKPlus1TrackID;
			locKlowTrackID = locKPlus2TrackID;
			locKPlusP4_highp_KinFit_CM = locKPlus1P4_KinFit_CM; 
			locKPlusP4_lowp_KinFit_CM = locKPlus2P4_KinFit_CM;
			locKPlusP4_highp_Measured = locKPlus1P4_Measured; 
			locKPlusP4_lowp_Measured = locKPlus2P4_Measured;
			locKPlusP4_highp_Measured_CM = locKPlus1P4_Measured_CM; 
			locKPlusP4_lowp_Measured_CM = locKPlus2P4_Measured_CM;
		}
		else if(locKPlus2P4.Theta() < locKPlus1P4.Theta()) {
			locKPlusP4_highp_KinFit = locKPlus2P4; 
			locKPlusP4_lowp_KinFit = locKPlus1P4; 
			locKhighTrackID = locKPlus2TrackID;
			locKlowTrackID = locKPlus1TrackID;
			locKPlusP4_highp_KinFit_CM = locKPlus2P4_KinFit_CM; 
			locKPlusP4_lowp_KinFit_CM = locKPlus1P4_KinFit_CM; 
			locKPlusP4_highp_Measured = locKPlus2P4_Measured; 
			locKPlusP4_lowp_Measured = locKPlus1P4_Measured; 
			locKPlusP4_highp_Measured_CM = locKPlus2P4_Measured_CM; 
			locKPlusP4_lowp_Measured_CM = locKPlus1P4_Measured_CM; 
		}
		else {
			if(locKPlus1P4.P() > locKPlus2P4.P()) { 
				locKPlusP4_highp_KinFit = locKPlus1P4; 
				locKPlusP4_lowp_KinFit = locKPlus2P4;
				locKhighTrackID = locKPlus1TrackID;
				locKlowTrackID = locKPlus2TrackID;
				locKPlusP4_highp_KinFit_CM = locKPlus1P4_KinFit_CM; 
				locKPlusP4_lowp_KinFit_CM = locKPlus2P4_KinFit_CM;
				locKPlusP4_highp_Measured = locKPlus1P4_Measured; 
				locKPlusP4_lowp_Measured = locKPlus2P4_Measured;
				locKPlusP4_highp_Measured_CM = locKPlus1P4_Measured_CM; 
				locKPlusP4_lowp_Measured_CM = locKPlus2P4_Measured_CM;
			}
			else if(locKPlus2P4.P() > locKPlus1P4.P()) {
				locKPlusP4_highp_KinFit = locKPlus2P4; 
				locKPlusP4_lowp_KinFit = locKPlus1P4; 
				locKhighTrackID = locKPlus2TrackID;
				locKlowTrackID = locKPlus1TrackID;
				locKPlusP4_highp_KinFit_CM = locKPlus2P4_KinFit_CM; 
				locKPlusP4_lowp_KinFit_CM = locKPlus1P4_KinFit_CM; 
				locKPlusP4_highp_Measured = locKPlus2P4_Measured; 
				locKPlusP4_lowp_Measured = locKPlus1P4_Measured; 
				locKPlusP4_highp_Measured_CM = locKPlus2P4_Measured_CM; 
				locKPlusP4_lowp_Measured_CM = locKPlus1P4_Measured_CM; 
			}
		}

		//Define intermediate hyperon and boost decay Kaon into rest frame of it and rotation to align the z axis to be in the direction of the beam
		TLorentzVector locIntermediate_KinFit_CM = locKPlusP4_lowp_KinFit_CM + locXiP4_KinFit_CM;
		TVector3 boostYstar = locIntermediate_KinFit_CM.BoostVector();
		TLorentzVector locBeamP4_Ystar = locBeamP4_KinFit_CM;
		TLorentzVector locKPlusP4_lowp_KinFit_Ystar = locKPlusP4_lowp_KinFit_CM;
		TLorentzVector locKPlusP4_highp_KinFit_Ystar = locKPlusP4_highp_KinFit_CM;
		TLorentzVector locIntermediate_KinFit_Ystar = locIntermediate_KinFit_CM;
		TLorentzVector locXiP4_KinFit_Ystar = locXiP4_KinFit_CM;
		locBeamP4_Ystar.Boost(-boostYstar);
		locKPlusP4_lowp_KinFit_Ystar.Boost(-boostYstar);
		locKPlusP4_highp_KinFit_Ystar.Boost(-boostYstar);
		locIntermediate_KinFit_Ystar.Boost(-boostYstar);
		locXiP4_KinFit_Ystar.Boost(-boostYstar);
		TVector3 z_Ystar;
		z_Ystar.SetXYZ(locBeamP4_Ystar.X(),locBeamP4_Ystar.Y(),locBeamP4_Ystar.Z());
		TVector3 z_hat_Ystar = z_Ystar.Unit();
		TVector3 y_Ystar = locBeamP4_KinFit_CM.Vect().Cross(locIntermediate_KinFit_CM.Vect());
		TVector3 y_hat_Ystar = y_Ystar.Unit();
		TVector3 x_hat_Ystar = y_hat_Ystar.Cross(z_hat_Ystar);
		TVector3 locKPlusP3_lowp_KinFit_Ystar_GJ(locKPlusP4_lowp_KinFit_Ystar.Vect()*x_hat_GJ,locKPlusP4_lowp_KinFit_Ystar.Vect()*y_hat_GJ,locKPlusP4_lowp_KinFit_Ystar.Vect()*z_hat_GJ);
		TVector3 locXiP3_KinFit_Ystar_GJ(locXiP4_KinFit_Ystar.Vect()*x_hat_GJ,locXiP4_KinFit_Ystar.Vect()*y_hat_GJ,locXiP4_KinFit_Ystar.Vect()*z_hat_GJ);

		TLorentzVector locIntermediate_Measured_CM = locKPlusP4_lowp_Measured_CM + locXiP4_Measured_CM;
		TVector3 boostYstar_Measured = locIntermediate_Measured_CM.BoostVector();
		TLorentzVector locKPlusP4_lowp_Measured_Ystar = locKPlusP4_lowp_Measured_CM;
		TLorentzVector locKPlusP4_highp_Measured_Ystar = locKPlusP4_highp_Measured_CM;
		TLorentzVector locIntermediate_Measured_Ystar = locIntermediate_Measured_CM;
		TLorentzVector locXiP4_Measured_Ystar = locXiP4_Measured_CM;
		locKPlusP4_lowp_Measured_Ystar.Boost(-boostYstar_Measured);
		locKPlusP4_highp_Measured_Ystar.Boost(-boostYstar_Measured);
		locIntermediate_Measured_Ystar.Boost(-boostYstar_Measured);
		locXiP4_Measured_Ystar.Boost(-boostYstar_Measured);

		//Truth values
		TLorentzVector locKPlusP4_t_Truth;
		TLorentzVector locKPlusP4_decay_Truth;
		TLorentzVector locXiTruth;
		TLorentzVector locIntermediate_Truth;
		TLorentzVector locIntermediate_Truth_CM;
		TLorentzVector locKPlusP4_t_CM_Truth;
		TLorentzVector locKPlusP4_decay_CM_Truth;
		TLorentzVector locKPlusP4_decay_Ystar_Truth;
		TLorentzVector locCoMP4_Truth;
		TVector3 boostCoMTruth;
		TVector3 boostYstarTruth;
		double t_Truth = 0.0;
		if(dThrownBeam != NULL){
			locCoMP4_Truth = dThrownBeam->Get_P4() + dTargetP4;
	    	boostCoMTruth = locCoMP4_Truth.BoostVector();
			for(UInt_t loc_particlei = 0; loc_particlei < Get_NumThrown(); ++loc_particlei)	{
				dThrownWrapper->Set_ArrayIndex(loc_particlei);
				Particle_t locPID = dThrownWrapper->Get_PID();
				TLorentzVector locThrownP4 = dThrownWrapper->Get_P4();
				if(locPID == 11) {
					if(loc_particlei == 0) { locKPlusP4_t_Truth = locThrownP4; }
					if(loc_particlei == 1) { locKPlusP4_decay_Truth = locThrownP4; }
				}
				if(locPID == 23 ) { locXiTruth = locThrownP4;}
			}
			t_Truth = (dThrownBeam->Get_P4() - locKPlusP4_t_Truth).M2();
			locIntermediate_Truth = locXiTruth + locKPlusP4_decay_Truth;
			locIntermediate_Truth_CM = locIntermediate_Truth;
			locIntermediate_Truth_CM.Boost(-boostCoMTruth);
			boostYstarTruth = locIntermediate_Truth_CM.BoostVector();
			locKPlusP4_t_CM_Truth = locKPlusP4_t_Truth;
			locKPlusP4_decay_CM_Truth = locKPlusP4_decay_Truth;
			locKPlusP4_t_CM_Truth.Boost(-boostCoMTruth);
			locKPlusP4_decay_CM_Truth.Boost(-boostCoMTruth);
			locKPlusP4_decay_Ystar_Truth = locKPlusP4_decay_CM_Truth;
			locKPlusP4_decay_Ystar_Truth.Boost(-boostYstarTruth);
		}

	/******************************************** EXECUTE ANALYSIS ACTIONS *******************************************/

		// Loop through the analysis actions, executing them in order for the active particle combo
		if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
			continue;

		//if you manually execute any actions, and it fails a cut, be sure to call:
			//dComboWrapper->Set_IsComboCut(true);

	/**************************************** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES **************************************/

		/*
		TLorentzVector locMyComboP4(8.0, 7.0, 6.0, 5.0);
		//for arrays below: 2nd argument is value, 3rd is array index
		//NOTE: By filling here, AFTER the cuts above, some indices won't be updated (and will be whatever they were from the last event)
			//So, when you draw the branch, be sure to cut on "IsComboCut" to avoid these.
		dTreeInterface->Fill_Fundamental<Float_t>("my_combo_array", -2*loc_i, loc_i);
		dTreeInterface->Fill_TObject<TLorentzVector>("my_p4_array", locMyComboP4, loc_i);
		*/

	/**************************************** EXAMPLE: HISTOGRAM BEAM ENERGY *****************************************/

		//Histogram beam energy (if haven't already)
		if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		{
			dHist_BeamEnergy->Fill(locBeamP4.E());
			locUsedSoFar_BeamEnergy.insert(locBeamID);
		}

	/************************************ USER DEFINED HISTOGRAMS************************************/

	//Definitions for filling histograms
		//Missing Mass squared
		double locMissingMassSquared = locMissingP4_Measured.M2();
		//ChiSq
		Float_t locChiSq = dComboWrapper->Get_ChiSq_KinFit("");
		Float_t locNDF = dComboWrapper->Get_NDF_KinFit("");
		Float_t locChiSqNdf = locChiSq/locNDF;
		Float_t locCL = dComboWrapper->Get_ConfidenceLevel_KinFit("");
		//DeltaT
		TLorentzVector locX4 = dComboBeamWrapper->Get_X4();
		double locRFTime = dComboWrapper->Get_RFTime_Measured();
		double dTargetCenterZ = dComboWrapper->Get_TargetCenter().Z();
		double locPropagatedRFTime = locRFTime + (locX4.Z() - dTargetCenterZ)/29.9792458;
		double locDeltaT = locX4.T() - locPropagatedRFTime;

		//Phi angles and -t Mandelstam variable
		double t = (locBeamP4 - locKPlusP4_highp_KinFit).M2();
		double phiKhighp_KinFit = getphi(locKPlusP4_highp_KinFit);
		double phiK1_Measured = locKPlus1P4_Measured.Phi()*180/TMath::Pi();
		if(phiK1_Measured < -180.) phiK1_Measured += 360.;
		if(phiK1_Measured >  180.) phiK1_Measured -= 360.;
		double phiK2_Measured = locKPlus2P4_Measured.Phi()*180/TMath::Pi();
		if(phiK2_Measured < -180.) phiK2_Measured += 360.;
		if(phiK2_Measured >  180.) phiK2_Measured -= 360.;
		double phiP_Measured = locProtonP4_Measured.Phi()*180/TMath::Pi();
		if(phiP_Measured < -180.) phiP_Measured += 360.;
		if(phiP_Measured >  180.) phiP_Measured -= 360.;
		double phiPi1_Measured = locPiMinus1P4_Measured.Phi()*180/TMath::Pi();
		if(phiPi1_Measured < -180.) phiPi1_Measured += 360.;
		if(phiPi1_Measured >  180.) phiPi1_Measured -= 360.;
		double phiPi2_Measured = locPiMinus2P4_Measured.Phi()*180/TMath::Pi();
		if(phiPi2_Measured < -180.) phiPi2_Measured += 360.;
		if(phiPi2_Measured >  180.) phiPi2_Measured -= 360.;
		double phiKhighp_KinFit_CM = locKPlusP4_highp_KinFit_CM.Phi()*180/TMath::Pi();
		if(phiKhighp_KinFit_CM < -180.) phiKhighp_KinFit_CM += 360.;
		if(phiKhighp_KinFit_CM > 180.)  phiKhighp_KinFit_CM -= 360.;
		double phiKlowp_KinFit_CM = locKPlusP4_lowp_KinFit_CM.Phi()*180/TMath::Pi();
		if(phiKlowp_KinFit_CM < -180.) phiKlowp_KinFit_CM += 360.;
		if(phiKlowp_KinFit_CM >  180.) phiKlowp_KinFit_CM -= 360.;
		double phiKlowp_KinFit_Ystar = locKPlusP4_lowp_KinFit_Ystar.Phi()*180/TMath::Pi();
		if(phiKlowp_KinFit_Ystar < -180.) phiKlowp_KinFit_Ystar += 360.;
		if(phiKlowp_KinFit_Ystar >  180.) phiKlowp_KinFit_Ystar -= 360.;
		double phiKlowp_Measured_Ystar = locKPlusP4_lowp_Measured_Ystar.Phi()*180/TMath::Pi();
		if(phiKlowp_Measured_Ystar < -180.) phiKlowp_Measured_Ystar += 360.;
		if(phiKlowp_Measured_Ystar >  180.) phiKlowp_Measured_Ystar -= 360.;
		double phiKhighp_KinFit_Ystar = locKPlusP4_highp_KinFit_Ystar.Phi()*180/TMath::Pi();
		if(phiKhighp_KinFit_Ystar < -180.) phiKhighp_KinFit_Ystar += 360.;
		if(phiKhighp_KinFit_Ystar >  180.) phiKhighp_KinFit_Ystar -= 360.;
		double phiKhighp_Measured_Ystar = locKPlusP4_highp_Measured_Ystar.Phi()*180/TMath::Pi();
		if(phiKhighp_Measured_Ystar < -180.) phiKhighp_Measured_Ystar += 360.;
		if(phiKhighp_Measured_Ystar >  180.) phiKhighp_Measured_Ystar -= 360.;
		double phiYstar_KinFit_CM = locIntermediate_KinFit_CM.Phi()*180/TMath::Pi();
		if(phiYstar_KinFit_CM < -180.) phiYstar_KinFit_CM += 360.;
		if(phiYstar_KinFit_CM >  180.) phiYstar_KinFit_CM -= 360.;
		double phiXi_KinFit_Ystar = locXiP4_KinFit_Ystar.Phi()*180/TMath::Pi();
		if(phiXi_KinFit_Ystar < -180.) phiXi_KinFit_Ystar += 360.;
		if(phiXi_KinFit_Ystar >  180.) phiXi_KinFit_Ystar -= 360.;
		double phiKlowp_KinFit_YstarGJ = locKPlusP3_lowp_KinFit_Ystar_GJ.Phi()*180/TMath::Pi();
		if(phiKlowp_KinFit_YstarGJ < -180.) phiKlowp_KinFit_YstarGJ += 360.;
		if(phiKlowp_KinFit_YstarGJ >  180.) phiKlowp_KinFit_YstarGJ -= 360.;	
		double phiXi_KinFit_YstarGJ = locXiP3_KinFit_Ystar_GJ.Phi()*180/TMath::Pi();
		if(phiXi_KinFit_YstarGJ < -180.) phiXi_KinFit_YstarGJ += 360.;
		if(phiXi_KinFit_YstarGJ >  180.) phiXi_KinFit_YstarGJ -= 360.;



		//Truth phi angles
		double phiKhighp_CM_Truth = 0.0;
		double phiKlowp_CM_Truth = 0.0;
		double phiKlowp_Ystar_Truth = 0.0;
		if(dThrownBeam != NULL){
			phiKhighp_CM_Truth = locKPlusP4_t_CM_Truth.Phi()*180/TMath::Pi();
			if(phiKhighp_CM_Truth < -180.) phiKhighp_CM_Truth = phiKhighp_CM_Truth + 360.;
			if (phiKhighp_CM_Truth > 180.) phiKhighp_CM_Truth = phiKhighp_CM_Truth - 360.;
			phiKlowp_CM_Truth = locKPlusP4_decay_CM_Truth.Phi()*180/TMath::Pi();
			if(phiKlowp_CM_Truth < -180.) phiKlowp_CM_Truth = phiKlowp_CM_Truth + 360.;
			if (phiKlowp_CM_Truth > 180.) phiKlowp_CM_Truth = phiKlowp_CM_Truth - 360.;
			phiKlowp_Ystar_Truth = locKPlusP4_decay_Ystar_Truth.Phi()*180/TMath::Pi();
			if(phiKlowp_Ystar_Truth < -180.) phiKlowp_Ystar_Truth = phiKlowp_Ystar_Truth + 360.;
			if (phiKlowp_Ystar_Truth > 180.) phiKlowp_Ystar_Truth = phiKlowp_Ystar_Truth - 360.;
		}

		//Scaling factor for accidental subtraction
		double scaling_factor = dAnalysisUtilities.Get_AccidentalScalingFactor(locRunNumber, locBeamP4.E());
		double scaling_factor_err = dAnalysisUtilities.Get_AccidentalScalingFactorError(locRunNumber, locBeamP4.E());


	//Setting up uniqueness tracking maps
		map<Particle_t, set<Int_t> > locUsedThisCombo_gXi;
		locUsedThisCombo_gXi[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_gXi[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_gXi[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_gXi[Proton].insert(locProtonTrackID);
		
		map<Particle_t, set<Int_t> > locUsedThisCombo_gKhighXi;
		locUsedThisCombo_gKhighXi[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_gKhighXi[KPlus].insert(locKhighTrackID);
		locUsedThisCombo_gKhighXi[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_gKhighXi[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_gKhighXi[Proton].insert(locProtonTrackID);

		map<Particle_t, set<Int_t> > locUsedThisCombo_gKlowXi;
		locUsedThisCombo_gKlowXi[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_gKlowXi[KPlus].insert(locKlowTrackID);
		locUsedThisCombo_gKlowXi[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_gKlowXi[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_gKlowXi[Proton].insert(locProtonTrackID);

		map<Particle_t, set<Int_t> > locUsedThisCombo_gKKXi;
		locUsedThisCombo_gKKXi[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_gKKXi[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_gKKXi[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_gKKXi[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_gKKXi[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_gKKXi[Proton].insert(locProtonTrackID);

		map<Particle_t, set<Int_t> > locUsedThisCombo_gKK;
		locUsedThisCombo_gKK[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_gKK[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_gKK[KPlus].insert(locKPlus2TrackID);

	//Pre-cut histograms
		if(locUsedSoFar_gXi.find(locUsedThisCombo_gXi) == locUsedSoFar_gXi.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					dHist_XiPath_preCL->Fill(locPathLengthXi);
					dHist_LambPath_preCL->Fill(locPathLengthLamb);
					dHist_ProdVert_preCL->Fill(locProdSpacetimeVertex.Z());
					dHist_XiVert_preCL->Fill(locDecayingXiX4.Z());
					dHist_LambVert_preCL->Fill(locDecayingLambX4.Z());
				}
				else {
					dHist_XiPath_preCL_wacc->Fill(locPathLengthXi,scaling_factor);
					dHist_LambPath_preCL_wacc->Fill(locPathLengthLamb,scaling_factor);
					dHist_ProdVert_preCL_wacc->Fill(locProdSpacetimeVertex.Z(),scaling_factor);
					dHist_XiVert_preCL_wacc->Fill(locDecayingXiX4.Z(),scaling_factor);
					dHist_LambVert_preCL_wacc->Fill(locDecayingLambX4.Z(),scaling_factor);
				}
			}
		} //end of uniqueness for gXi preChiSq

		if(locUsedSoFar_gKhighXi.find(locUsedThisCombo_gKhighXi) == locUsedSoFar_gKhighXi.end()){
		
		} //end of uniqueness for gKhighXi preChiSq


		if(locUsedSoFar_gKlowXi.find(locUsedThisCombo_gKlowXi) == locUsedSoFar_gKlowXi.end()){
		
		} //end of uniqueness for gKlowXi preChiSq

		if(locUsedSoFar_gKKXi.find(locUsedThisCombo_gKKXi) == locUsedSoFar_gKKXi.end()){
			dHist_MissingMassSquared->Fill(locMissingMassSquared);
			dHist_ChiSq->Fill(locChiSqNdf);
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					dHist_ChiSqXi->Fill(locChiSqNdf, locXiP4_Measured.M());
					dHist_ChiSqXi_KinFit->Fill(locChiSqNdf, locXiP4_KinFit.M());
					dHist_ChiSqKp->Fill(locChiSqNdf, locKPlus1P4.P());
					dHist_ChiSqKp->Fill(locChiSqNdf, locKPlus2P4.P());
					dHist_Xi_Egamma_ChiSq_063->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf);
					dHist_Xi_Egamma_ChiSq_064->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf);
					dHist_Xi_Egamma_ChiSq_065->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf);
					dHist_ChisqVsCL->Fill(locChiSqNdf,locCL);
					if(locBeamP4.E() >= 8.4 && locBeamP4.E() < 8.9)	{dHist_Xi_Chisq_084->Fill(locXiP4_KinFit.M(),locChiSqNdf);}
					if(locChiSqNdf < 3.50){
						dHist_XiMass_Measured_nan->Fill(locXiP4_Measured.M());
						dHist_XiMass_KinFit_nan->Fill(locXiP4_KinFit.M());
					}
				}
				else { 
					dHist_ChiSqXi_KinFit_acc->Fill(locChiSqNdf, locXiP4_KinFit.M());
					dHist_ChiSqXi_KinFit_wacc->Fill(locChiSqNdf, locXiP4_KinFit.M(),scaling_factor);
					dHist_ChiSqKp_wacc->Fill(locChiSqNdf, locKPlus1P4.P(),scaling_factor);
					dHist_ChiSqKp_wacc->Fill(locChiSqNdf, locKPlus2P4.P(),scaling_factor);
					dHist_Xi_Egamma_ChiSq_063_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf,scaling_factor);
					dHist_Xi_Egamma_ChiSq_064_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf,scaling_factor);
					dHist_Xi_Egamma_ChiSq_065_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),locChiSqNdf,scaling_factor);
					if(locBeamP4.E() >= 8.4 && locBeamP4.E() < 8.9)	{dHist_Xi_Chisq_084_wacc->Fill(locXiP4_KinFit.M(),locChiSqNdf,scaling_factor);}
					if(locChiSqNdf < 3.50){
						dHist_XiMass_Measured_nan_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
						dHist_XiMass_KinFit_nan_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);
					}
				}
			}	
			if(isnan(locChiSqNdf)){
				*myfile << Get_RunNumber() << " " << Get_EventNumber() << " " << locXiP4_Measured.M() << " " << locXiP4_KinFit.M() << " " << locChiSqNdf << " " << locCL << " "<< locBeamP4.E() << " " << locDeltaT << endl;
				*myfile << "       " << locKPlus1P4_Measured.P() << " " << locKPlus2P4_Measured.P() << " " << locProtonP4_Measured.P() << " " << locPiMinus1P4_Measured.P() << " " << locPiMinus2P4_Measured.P() << endl;
				*myfile << "       " << locKPlus1P4.P() << " " << locKPlus2P4.P() << " " << locProtonP4.P() << " " << locPiMinus1P4.P() << " " << locPiMinus2P4.P() << endl;
			}
		} //end of uniqueness for gKKXi preChiSq

		
	//ChiSq Cut
		if((locChiSqNdf > 3.50 || isnan(locChiSqNdf))){ //In the 2018-08 dataset, some events that failed the KinFit have been written out
			dComboWrapper->Set_IsComboCut(true);
			locUsedSoFar_gXi.insert(locUsedThisCombo_gXi);
			locUsedSoFar_gKhighXi.insert(locUsedThisCombo_gKhighXi);
			locUsedSoFar_gKlowXi.insert(locUsedThisCombo_gKlowXi);
			locUsedSoFar_gKKXi.insert(locUsedThisCombo_gKKXi);
			continue;
		}

	//Post-cut histograms
		if(locUsedSoFar_gXi.find(locUsedThisCombo_gXi) == locUsedSoFar_gXi.end()){
			if(fabs(locDeltaT) < 6.004) {
				if(fabs(locDeltaT) < 2.004) {	
					dHist_XiMass_Measured->Fill(locXiP4_Measured.M());
					dHist_XiMass_KinFit->Fill(locXiP4_KinFit.M());
					dHist_Xi_cosGJ->Fill(locXiP4_KinFit.M(),cosTheta_GJ);
					dHist_Xi_Egamma->Fill(locXiP4_KinFit.M(),locBeamP4.E());
					dHist_Xi_LambFlight->Fill(locXiP4_Measured.M(),locPathLengthSignificanceLamb);
					dHist_Xi_XiFlight->Fill(locXiP4_Measured.M(),locPathLengthSignificanceXi);
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){ 
						dHist_XiPath_postCL->Fill(locPathLengthXi);
						dHist_LambPath_postCL->Fill(locPathLengthLamb);
						dHist_ProdVert_postCL->Fill(locProdSpacetimeVertex.Z());
						dHist_XiVert_postCL->Fill(locDecayingXiX4.Z());
						dHist_LambVert_postCL->Fill(locDecayingLambX4.Z());
						dHist_LambPathSig_postCL->Fill(locPathLengthSigmaLamb);
						dHist_p_pThetaPhi_Measured->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P(),phiP_Measured);
						dHist_p_pEgamma_Measured->Fill(locBeamP4.E(), locProtonP4_Measured.P());
						dHist_p_pt_Measured->Fill(-1*t, locProtonP4_Measured.P());
						dHist_p_pTheta_Measured->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P());
						dHist_p_pTheta_KinFit->Fill(locProtonP4.Theta()*180./TMath::Pi(), locProtonP4.P());
						dHist_pi_pThetaPhi_Measured->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(), locPiMinus1P4_Measured.P(),phiPi1_Measured);
						dHist_pi_pThetaPhi_Measured->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(), locPiMinus2P4_Measured.P(),phiPi2_Measured);
						dHist_pi_pEgamma_Measured->Fill(locBeamP4.E(), locPiMinus1P4_Measured.P());
						dHist_pi_pEgamma_Measured->Fill(locBeamP4.E(), locPiMinus2P4_Measured.P());
						dHist_pi_pt_Measured->Fill(-1*t, locPiMinus1P4_Measured.P());
						dHist_pi_pt_Measured->Fill(-1*t, locPiMinus2P4_Measured.P());
						dHist_pi_pTheta_Measured->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.P());
						dHist_pi_pTheta_Measured->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.P());
						dHist_pi_pTheta_KinFit->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.P());
						dHist_pi_pTheta_KinFit->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.P());
						dHist_pi_ptTheta_Measured->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.Pt());
						dHist_pi_ptTheta_Measured->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.Pt());
						dHist_pi_ptTheta_KinFit->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.Pt());
						dHist_pi_ptTheta_KinFit->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.Pt());
						if (locBeamP4.E() >= 8.2 && locBeamP4.E() <= 8.8){ 
							dHist_BeamBunch_Asym->Fill(locDeltaT);
							dHist_XiMass_KinFit_Selected->Fill(locXiP4_KinFit.M());	
						}
					}
					if((locPiMinus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locPiMinus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){ 
						dHist_XiMass_piTheta15to35_Measured->Fill(locXiP4_Measured.M());
						dHist_XiMass_piTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
					}		
				}
				else { 
					dHist_XiMass_Measured_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
					dHist_XiMass_KinFit_acc->Fill(locXiP4_KinFit.M());
					dHist_XiMass_KinFit_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);
					dHist_Xi_cosGJ_wacc->Fill(locXiP4_KinFit.M(),cosTheta_GJ,scaling_factor);
					dHist_Xi_Egamma_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E());
					dHist_Xi_Egamma_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),scaling_factor);
					dHist_Xi_LambFlight_wacc->Fill(locXiP4_Measured.M(),locPathLengthSignificanceLamb,scaling_factor);
					dHist_Xi_XiFlight_wacc->Fill(locXiP4_Measured.M(),locPathLengthSignificanceXi,scaling_factor);
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){ 
						dHist_XiPath_postCL_wacc->Fill(locPathLengthXi,scaling_factor);
						dHist_LambPath_postCL_wacc->Fill(locPathLengthLamb,scaling_factor);
						dHist_ProdVert_postCL_wacc->Fill(locProdSpacetimeVertex.Z(),scaling_factor);
						dHist_XiVert_postCL_wacc->Fill(locDecayingXiX4.Z(),scaling_factor);
						dHist_LambVert_postCL_wacc->Fill(locDecayingLambX4.Z(),scaling_factor);
						dHist_LambPathSig_postCL_wacc->Fill(locPathLengthSigmaLamb,scaling_factor);
						dHist_p_pThetaPhi_Measured_wacc->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P(),phiP_Measured,scaling_factor);
						dHist_p_pEgamma_Measured_wacc->Fill(locBeamP4.E(), locProtonP4_Measured.P(),scaling_factor);
						dHist_p_pt_Measured_wacc->Fill(-1*t, locProtonP4_Measured.P(),scaling_factor);
						dHist_p_pTheta_Measured_wacc->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P(),scaling_factor);
						dHist_p_pTheta_KinFit_wacc->Fill(locProtonP4.Theta()*180./TMath::Pi(), locProtonP4.P(),scaling_factor);
						dHist_pi_pThetaPhi_Measured_wacc->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(), locPiMinus1P4_Measured.P(),phiPi1_Measured,scaling_factor);
						dHist_pi_pThetaPhi_Measured_wacc->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(), locPiMinus2P4_Measured.P(),phiPi2_Measured,scaling_factor);
						dHist_pi_pEgamma_Measured_wacc->Fill(locBeamP4.E(), locPiMinus1P4_Measured.P(),scaling_factor);
						dHist_pi_pEgamma_Measured_wacc->Fill(locBeamP4.E(), locPiMinus2P4_Measured.P(),scaling_factor);
						dHist_pi_pt_Measured_wacc->Fill(-1*t, locPiMinus1P4_Measured.P(),scaling_factor);
						dHist_pi_pt_Measured_wacc->Fill(-1*t, locPiMinus2P4_Measured.P(),scaling_factor);							
						dHist_pi_pTheta_Measured_wacc->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.P(),scaling_factor);
						dHist_pi_pTheta_Measured_wacc->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.P(),scaling_factor);
						dHist_pi_pTheta_KinFit_wacc->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.P(),scaling_factor);
						dHist_pi_pTheta_KinFit_wacc->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.P(),scaling_factor);
						dHist_pi_ptTheta_Measured_wacc->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.Pt(),scaling_factor);
						dHist_pi_ptTheta_Measured_wacc->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.Pt(),scaling_factor);
						dHist_pi_ptTheta_KinFit_wacc->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.Pt(),scaling_factor);
						dHist_pi_ptTheta_KinFit_wacc->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.Pt(),scaling_factor);
						if (locBeamP4.E() >= 8.2 && locBeamP4.E() <= 8.8){ 
							dHist_XiMass_KinFit_Selected_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);	
						}
					}
					if((locPiMinus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locPiMinus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){ 
						dHist_XiMass_piTheta15to35_Measured_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
						dHist_XiMass_piTheta15to35_KinFit_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);
					}
				} //end of else loop for OOT photons
			} //end of 6.004 loop
			locUsedSoFar_gXi.insert(locUsedThisCombo_gXi);
		} //end of uniqueness for gXi postChiSq

		if(locUsedSoFar_gKhighXi.find(locUsedThisCombo_gKhighXi) == locUsedSoFar_gKhighXi.end()){
			if(fabs(locDeltaT) > 2.004) {
				dHist_BeamBunch_Xi_acc->Fill(locDeltaT);
				dHist_BeamBunch_Xi_wacc->Fill(locDeltaT,scaling_factor);
			}
			if(fabs(locDeltaT) < 6.004) {
				if(fabs(locDeltaT) < 2.004) {	
					dHist_BeamBunch_Xi_acc->Fill(locDeltaT);
					dHist_BeamBunch_Xi_wacc->Fill(locDeltaT);
					dHist_Xi_t->Fill(locXiP4_KinFit.M(),-1.*t);
					dHist_Xi_Egamma_t->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_063->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_064->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_065->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_064->Fill(locXiP4_KinFit.M(),locBeamP4.E());
					if(locProdSpacetimeVertex.Z() > 50.0 && locProdSpacetimeVertex.Z() < 65.0){
						dHist_Xi_Egamma_t_064_lowerTarget->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					}
					if(locProdSpacetimeVertex.Z() > 65.0 && locProdSpacetimeVertex.Z() < 80.0){
						dHist_Xi_Egamma_t_064_upperTarget->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					}
					if(dThrownBeam != NULL){
						dHist_Xi_t_Truth->Fill(locXiP4_KinFit.M(),-1.*t_Truth);
						dHist_Xi_thrownEgamma_t_064->Fill(locXiP4_KinFit.M(),dThrownBeam->Get_P4().E(),-1.*t);
					}
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){
						dHist_Khighp_pvstheta->Fill(locKPlusP4_highp_KinFit.Theta()*180./TMath::Pi(),locKPlusP4_highp_KinFit.P());
						if (locBeamP4.E() >= 8.2 && locBeamP4.E() <= 8.8){ 
							dHist_phi_t->Fill(-1.*t, phiKhighp_KinFit); 
						}
					} 	
				}
				else { 
					dHist_Xi_t_acc->Fill(locXiP4_KinFit.M(),-1.*t);
					dHist_Xi_Egamma_t_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_063_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_064_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_065_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_064_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),scaling_factor);
					dHist_Xi_t_wacc->Fill(locXiP4_KinFit.M(),-1.*t,scaling_factor);
					dHist_Xi_Egamma_t_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					dHist_Xi_Egamma_t_063_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					dHist_Xi_Egamma_t_064_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					dHist_Xi_Egamma_t_065_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					if(locProdSpacetimeVertex.Z() > 50.0 && locProdSpacetimeVertex.Z() < 65.0){
						dHist_Xi_Egamma_t_064_lowerTarget_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					}
					if(locProdSpacetimeVertex.Z() > 65.0 && locProdSpacetimeVertex.Z() < 80.0){
						dHist_Xi_Egamma_t_064_upperTarget_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					}
					if(dThrownBeam != NULL){
						dHist_Xi_thrownEgamma_t_064_wacc->Fill(locXiP4_KinFit.M(),dThrownBeam->Get_P4().E(),-1.*t,scaling_factor);
					}
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){	
						dHist_Khighp_pvstheta_wacc->Fill(locKPlusP4_highp_KinFit.Theta()*180./TMath::Pi(),locKPlusP4_highp_KinFit.P(),scaling_factor);
						if (locBeamP4.E() >= 8.2 && locBeamP4.E() <= 8.8){ 
							dHist_wacc_phi_t_1->Fill(-1.*t, phiKhighp_KinFit); 
						}
					}	
				}
			}
			locUsedSoFar_gKhighXi.insert(locUsedThisCombo_gKhighXi);
		} //end of uniqueness for gKhighXi postChiSq

		if(locUsedSoFar_gKlowXi.find(locUsedThisCombo_gKlowXi) == locUsedSoFar_gKlowXi.end()){
			if(fabs(locDeltaT) < 6.004) {
				if(fabs(locDeltaT) < 2.004) {
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){
						dHist_KlowpXim->Fill(locIntermediate_KinFit_CM.M());
						if(dThrownBeam != NULL){ dHist_KlowpXim_Truth->Fill(locIntermediate_Truth.M()); }
						dHist_Klowp_pvstheta->Fill(locKPlusP4_lowp_KinFit.Theta()*180./TMath::Pi(),locKPlusP4_lowp_KinFit.P());
					}
					else {
						dHist_KlowpXim_wacc->Fill(locIntermediate_KinFit_CM.M(),scaling_factor);
						dHist_Klowp_pvstheta_wacc->Fill(locKPlusP4_lowp_KinFit.Theta()*180./TMath::Pi(),locKPlusP4_lowp_KinFit.P(),scaling_factor);
					}
				}	
			}	
			locUsedSoFar_gKlowXi.insert(locUsedThisCombo_gKlowXi);
		} //end of uniqueness for gKlowXi postChiSq

		if(locUsedSoFar_gKKXi.find(locUsedThisCombo_gKKXi) == locUsedSoFar_gKKXi.end()){
			if(fabs(locDeltaT) < 6.004) {
				if(fabs(locDeltaT) < 2.004) {
					dHist_Xi_Egamma_t_064_alltracked->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Klowp_noXi_phiTheta_Ystar_KinFit->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKlowp_KinFit_Ystar);
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){
						*myP4file << "====New Combo====" << endl;
						*myP4file << "KinFit P4 in lab frame:\t" << endl;
						*myP4file << "Beam:\t" << locBeamP4.E() << "\t" << locBeamP4.Px() << "\t" << locBeamP4.Py() << "\t" << locBeamP4.Pz() << endl;
						*myP4file << "Kt:\t" << locKPlusP4_highp_KinFit.E() << "\t" << locKPlusP4_highp_KinFit.Px() << "\t" << locKPlusP4_highp_KinFit.Py() << "\t" << locKPlusP4_highp_KinFit.Pz() << endl;
						*myP4file << "Kd:\t" << locKPlusP4_lowp_KinFit.E() << "\t" << locKPlusP4_lowp_KinFit.Px() << "\t" << locKPlusP4_lowp_KinFit.Py() << "\t" << locKPlusP4_lowp_KinFit.Pz() << endl;
						*myP4file << "Xi:\t" << locXiP4_KinFit.E() << "\t" << locXiP4_KinFit.Px() << "\t" << locXiP4_KinFit.Py() << "\t" << locXiP4_KinFit.Pz() << endl;
						*myP4file << "KinFit P4 in CM frame:\t" << endl;
						*myP4file << "Boost vector KinFit from lab to CoM:\t" << boostCoM_KinFit.X() << "\t" << boostCoM_KinFit.Y() << "\t" << boostCoM_KinFit.Z() << endl;
						*myP4file << "Beam:\t" << locBeamP4_KinFit_CM.E() << "\t" << locBeamP4_KinFit_CM.Px() << "\t" << locBeamP4_KinFit_CM.Py() << "\t" << locBeamP4_KinFit_CM.Pz() << endl;
						*myP4file << "Kt:\t" << locKPlusP4_highp_KinFit_CM.E() << "\t" << locKPlusP4_highp_KinFit_CM.Px() << "\t" << locKPlusP4_highp_KinFit_CM.Py() << "\t" << locKPlusP4_highp_KinFit_CM.Pz() << endl;
						*myP4file << "Kd:\t" << locKPlusP4_lowp_KinFit_CM.E() << "\t" << locKPlusP4_lowp_KinFit_CM.Px() << "\t" << locKPlusP4_lowp_KinFit_CM.Py() << "\t" << locKPlusP4_lowp_KinFit_CM.Pz() << endl;
						*myP4file << "Xi:\t" << locXiP4_KinFit_CM.E() << "\t" << locXiP4_KinFit_CM.Px() << "\t" << locXiP4_KinFit_CM.Py() << "\t" << locXiP4_KinFit_CM.Pz() << endl;	
						*myP4file << "KinFit P4 in Ystar rest frame:\t" << endl;
						*myP4file << "Boost vector from CoM to Ystar:\t" << boostYstar.X() << "\t" << boostYstar.Y() << "\t" << boostYstar.Z() << endl;
						*myP4file << "Kd:\t" << locKPlusP4_lowp_KinFit_Ystar.E() << "\t" << locKPlusP4_lowp_KinFit_Ystar.Px() << "\t" << locKPlusP4_lowp_KinFit_Ystar.Py() << "\t" << locKPlusP4_lowp_KinFit_Ystar.Pz() << endl;
						*myP4file << "Values of interest: Kd P():\t" << locKPlusP4_lowp_KinFit_Ystar.P() << endl;
						*myP4file << "Values of interest: Kd Theta():\t" << locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi() <<endl;
						*myP4file << "Values of interest: Kd Phi():\t" << locKPlusP4_lowp_KinFit_Ystar.Phi()*180./TMath::Pi() << endl;
						*myP4file << "Kt vs Kd: P vs Theta:" << endl;
						*myP4file << "Kt:\t" << locKPlusP4_highp_KinFit.P() << "GeV " << locKPlusP4_highp_KinFit.Theta()*180./TMath::Pi() << " deg" << endl;
						*myP4file << "Kdecay:\t" << locKPlusP4_lowp_KinFit.P() << "GeV " << locKPlusP4_lowp_KinFit.Theta()*180./TMath::Pi() << " deg" << endl;
						if(dThrownBeam != NULL){
							dHist_Khighp_choicevstruth_KinFit->Fill(locKPlusP4_highp_KinFit.P(), locKPlusP4_t_Truth.P());
							dHist_Klowp_choicevstruth_KinFit->Fill(locKPlusP4_lowp_KinFit.P(), locKPlusP4_decay_Truth.P());
							bool thetaCheck = locKPlusP4_t_Truth.Theta()*180./TMath::Pi() < locKPlusP4_decay_Truth.Theta()*180./TMath::Pi();
							bool theta13Check = locKPlusP4_t_Truth.Theta()*180./TMath::Pi() < 13.;
							bool momentumCheck = locKPlusP4_t_Truth.P() > locKPlusP4_decay_Truth.P();
							bool thetapCheck = thetaCheck * momentumCheck;
							bool choiceCheck = locKPlusP4_t_Truth.P() == locKPlusP4_highp_Measured.P();
							*myP4file << "==TRUTH CHECK new event==" << endl;
							*myP4file << "CHECK Kt theta < 13: " << theta13Check << " " << locKPlusP4_t_Truth.Theta()*180./TMath::Pi() << " < 13deg" << endl;
							*myP4file << "CHECK Kt theta < Kdecay theta: " << thetaCheck << " " << locKPlusP4_t_Truth.Theta()*180./TMath::Pi() << " < " <<  locKPlusP4_decay_Truth.Theta()*180./TMath::Pi() << endl;
							*myP4file << "CHECK Kt p > Kdecay p: " << momentumCheck << " " << locKPlusP4_t_Truth.P() << " > " <<  locKPlusP4_decay_Truth.P() <<  endl;
							*myP4file << "CHECK Kt theta && Kt p: " << thetapCheck << endl;
							*myP4file << "TRUTH Kt p theta:\t" << locKPlusP4_t_Truth.P() << "GeV " << locKPlusP4_t_Truth.Theta()*180./TMath::Pi() << " deg" << endl;
							*myP4file << "TRUTH Kdecay p theta:\t" << locKPlusP4_decay_Truth.P() << "GeV " << locKPlusP4_decay_Truth.Theta()*180./TMath::Pi() << " deg" << endl;
							*myP4file << "CHOICE vs TRUTH: DeltaP " << locKPlusP4_t_Truth.P() - locKPlusP4_highp_Measured.P() << endl;
						}
						dHist_K_pThetaPhi_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P(),phiK1_Measured);
						dHist_K_pThetaPhi_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P(),phiK2_Measured);
						dHist_K_pEgamma_Measured->Fill(locBeamP4.E(), locKPlus1P4_Measured.P());
						dHist_K_pEgamma_Measured->Fill(locBeamP4.E(), locKPlus2P4_Measured.P());
						dHist_K_pt_Measured->Fill(-1*t, locKPlus1P4_Measured.P());
						dHist_K_pt_Measured->Fill(-1*t, locKPlus2P4_Measured.P());
						dHist_K_pTheta_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P());
						dHist_K_pTheta_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P());
						dHist_K_pTheta_KinFit->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.P());
						dHist_K_pTheta_KinFit->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.P());
						dHist_K_ptTheta_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.Pt());
						dHist_K_ptTheta_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.Pt());
						dHist_K_ptTheta_KinFit->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.Pt());
						dHist_K_ptTheta_KinFit->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.Pt());
						dHist_allK_phiTheta_CM_KinFit->Fill(locKPlusP4_highp_KinFit_CM.Theta()*180./TMath::Pi(),phiKhighp_KinFit_CM);
						dHist_allK_phiTheta_CM_KinFit->Fill(locKPlusP4_lowp_KinFit_CM.Theta()*180./TMath::Pi(),phiKlowp_KinFit_CM);
						dHist_Khighp_phiTheta_CM_KinFit->Fill(locKPlusP4_highp_KinFit_CM.Theta()*180./TMath::Pi(), phiKhighp_KinFit_CM);
						dHist_Klowp_phiTheta_Ystar_KinFit->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(),phiKlowp_KinFit_Ystar);
						dHist_Ystar_p_Ystar_KinFit->Fill(locIntermediate_KinFit_Ystar.P());
						dHist_Ystar_p_Ystar_Measured->Fill(locIntermediate_Measured_Ystar.P());
						dHist_allK_phiTheta_Ystar_KinFit->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKlowp_KinFit_Ystar);
						dHist_allK_phiTheta_Ystar_KinFit->Fill(locKPlusP4_highp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKhighp_KinFit_Ystar);
						dHist_allK_phiTheta_Ystar_Measured->Fill(locKPlusP4_lowp_Measured_Ystar.Theta()*180./TMath::Pi(), phiKlowp_Measured_Ystar);
						dHist_allK_phiTheta_Ystar_Measured->Fill(locKPlusP4_highp_Measured_Ystar.Theta()*180./TMath::Pi(), phiKhighp_Measured_Ystar);
						dHist_Ystar_phiTheta_CM_KinFit->Fill(locIntermediate_KinFit_CM.Theta()*180./TMath::Pi(), phiYstar_KinFit_CM);
						dHist_Xi_phiTheta_Ystar_KinFit->Fill(locXiP4_KinFit_Ystar.Theta()*180./TMath::Pi(), phiXi_KinFit_Ystar);
						dHist_KXi_dTheta_Ystar_KinFit->Fill(abs((locXiP4_KinFit_Ystar.Theta()+locKPlusP4_lowp_KinFit_Ystar.Theta())*180./TMath::Pi()));
						dHist_KYstar_dMass_Ystar_KinFit->Fill((locIntermediate_KinFit_Ystar-locKPlusP4_lowp_KinFit_Ystar).M());
						dHist_Klowp_phiTheta_YstarGJ->Fill(locKPlusP3_lowp_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(), phiKlowp_KinFit_YstarGJ);
						dHist_Xi_phiTheta_YstarGJ->Fill(locXiP3_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(),phiXi_KinFit_YstarGJ);
						if(dThrownBeam != NULL){
							dHist_Khighp_phiTheta_CM_Truth->Fill(locKPlusP4_t_CM_Truth.Theta()*180./TMath::Pi(), phiKhighp_CM_Truth);
							dHist_Klowp_phiTheta_Ystar_Truth->Fill(locKPlusP4_decay_Ystar_Truth.Theta()*180./TMath::Pi(),phiKlowp_Ystar_Truth);
							dHist_Klowp_phiTheta_YstarGJ_reconthrown->Fill(locKPlusP4_decay_Ystar_Truth.Theta()*180./TMath::Pi(),phiKlowp_Ystar_Truth);
							dHist_Klowp_dtheta_reconthrown->Fill((locKPlusP4_decay_Ystar_Truth.Theta() - locKPlusP3_lowp_KinFit_Ystar_GJ.Theta())*180./TMath::Pi());
							if(locKPlusP4_decay_Ystar_Truth.Theta()*180./TMath::Pi() > 150.){
								dHist_Klowp_phiTheta_YstarGJ_thrown150to180->Fill(locKPlusP3_lowp_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(), phiKlowp_KinFit_YstarGJ);
							}
						}
					}
					if((locKPlus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locKPlus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){
						dHist_XiMass_kTheta15to35_Measured->Fill(locXiP4_Measured.M());
						dHist_XiMass_kTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
						if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
							dHist_XiMass_MM_kTheta15to35_Measured->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_kTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
							dHist_XiMass_MM_piTheta15to35_Measured->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_piTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
						}
					}	
				}	
				else {
					dHist_Xi_Egamma_t_064_alltracked_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t);
					dHist_Xi_Egamma_t_064_alltracked_wacc->Fill(locXiP4_KinFit.M(),locBeamP4.E(),-1.*t,scaling_factor);
					dHist_Klowp_noXi_phiTheta_Ystar_KinFit_wacc->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKlowp_KinFit_Ystar, scaling_factor);
					if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){
						dHist_allK_phiTheta_CM_KinFit_wacc->Fill(locKPlusP4_highp_KinFit_CM.Theta()*180./TMath::Pi(),phiKhighp_KinFit_CM,scaling_factor);
						dHist_allK_phiTheta_CM_KinFit_wacc->Fill(locKPlusP4_lowp_KinFit_CM.Theta()*180./TMath::Pi(),phiKlowp_KinFit_CM,scaling_factor);
						dHist_K_pThetaPhi_Measured_wacc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P(),phiK1_Measured,scaling_factor);
						dHist_K_pThetaPhi_Measured_wacc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P(),phiK2_Measured,scaling_factor);
						dHist_K_pEgamma_Measured_wacc->Fill(locBeamP4.E(), locKPlus1P4_Measured.P(),scaling_factor);
						dHist_K_pEgamma_Measured_wacc->Fill(locBeamP4.E(), locKPlus2P4_Measured.P(),scaling_factor);
						dHist_K_pt_Measured_wacc->Fill(-1*t, locKPlus1P4_Measured.P(),scaling_factor);
						dHist_K_pt_Measured_wacc->Fill(-1*t, locKPlus2P4_Measured.P(),scaling_factor);
						dHist_K_pTheta_Measured_wacc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P(),scaling_factor);
						dHist_K_pTheta_Measured_wacc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P(),scaling_factor);
						dHist_K_pTheta_KinFit_wacc->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.P(),scaling_factor);
						dHist_K_pTheta_KinFit_wacc->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.P(),scaling_factor);
						dHist_K_ptTheta_Measured_wacc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.Pt(),scaling_factor);
						dHist_K_ptTheta_Measured_wacc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.Pt(),scaling_factor);
						dHist_K_ptTheta_KinFit_wacc->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.Pt(),scaling_factor);
						dHist_K_ptTheta_KinFit_wacc->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.Pt(),scaling_factor);
						dHist_Khighp_phiTheta_CM_KinFit_wacc->Fill(locKPlusP4_highp_KinFit_CM.Theta()*180./TMath::Pi(), phiKhighp_KinFit_CM, scaling_factor);
						dHist_Klowp_phiTheta_Ystar_KinFit_wacc->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKlowp_KinFit_Ystar,scaling_factor);
						dHist_Ystar_p_Ystar_KinFit_wacc->Fill(locIntermediate_KinFit_Ystar.P(), scaling_factor);
						dHist_Ystar_p_Ystar_Measured_wacc->Fill(locIntermediate_Measured_Ystar.P(), scaling_factor);
						dHist_allK_phiTheta_Ystar_KinFit_wacc->Fill(locKPlusP4_lowp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKlowp_KinFit_Ystar,scaling_factor);
						dHist_allK_phiTheta_Ystar_KinFit_wacc->Fill(locKPlusP4_highp_KinFit_Ystar.Theta()*180./TMath::Pi(), phiKhighp_KinFit_Ystar,scaling_factor);
						dHist_allK_phiTheta_Ystar_Measured_wacc->Fill(locKPlusP4_highp_Measured_Ystar.Theta()*180./TMath::Pi(), phiKhighp_Measured_Ystar,scaling_factor);
						dHist_allK_phiTheta_Ystar_Measured_wacc->Fill(locKPlusP4_lowp_Measured_Ystar.Theta()*180./TMath::Pi(), phiKlowp_Measured_Ystar,scaling_factor);
						dHist_Xi_phiTheta_Ystar_KinFit_wacc->Fill(locXiP4_KinFit_Ystar.Theta()*180./TMath::Pi(), phiXi_KinFit_Ystar,scaling_factor);
						dHist_KXi_dTheta_Ystar_KinFit_wacc->Fill(abs((locXiP4_KinFit_Ystar.Theta()+locKPlusP4_lowp_KinFit_Ystar.Theta())*180./TMath::Pi()),scaling_factor);
						dHist_KYstar_dMass_Ystar_KinFit_wacc->Fill((locIntermediate_KinFit_Ystar-locKPlusP4_lowp_KinFit_Ystar).M(),scaling_factor);
						dHist_Klowp_phiTheta_YstarGJ_wacc->Fill(locKPlusP3_lowp_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(), phiKlowp_KinFit_YstarGJ,scaling_factor);
						dHist_Xi_phiTheta_YstarGJ_wacc->Fill(locXiP3_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(),phiXi_KinFit_YstarGJ,scaling_factor);
						if(dThrownBeam != NULL){
							dHist_Klowp_phiTheta_YstarGJ_reconthrown_wacc->Fill(locKPlusP4_decay_Ystar_Truth.Theta()*180./TMath::Pi(),phiKlowp_Ystar_Truth,scaling_factor);
							dHist_Klowp_dtheta_reconthrown_wacc->Fill((locKPlusP4_decay_Ystar_Truth.Theta() - locKPlusP3_lowp_KinFit_Ystar_GJ.Theta())*180./TMath::Pi(),scaling_factor);
							if(locKPlusP4_decay_Ystar_Truth.Theta()*180./TMath::Pi() > 150.){
								dHist_Klowp_phiTheta_YstarGJ_thrown150to180_wacc->Fill(locKPlusP3_lowp_KinFit_Ystar_GJ.Theta()*180./TMath::Pi(), phiKlowp_KinFit_YstarGJ,scaling_factor);
							}	
						}
					}
					if((locKPlus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locKPlus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){
						dHist_XiMass_kTheta15to35_Measured_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
						dHist_XiMass_kTheta15to35_KinFit_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);
						if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
							dHist_XiMass_MM_kTheta15to35_Measured_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
							dHist_XiMass_MM_kTheta15to35_KinFit_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);
							dHist_XiMass_MM_piTheta15to35_Measured_wacc->Fill(locXiP4_Measured.M(),scaling_factor);
							dHist_XiMass_MM_piTheta15to35_KinFit_wacc->Fill(locXiP4_KinFit.M(),scaling_factor);

						}
					}
				}
			}				
			locUsedSoFar_gKKXi.insert(locUsedThisCombo_gKKXi);
		} //end of uniqueness for gKKXi	postChiSq

		if(locUsedSoFar_gKK.find(locUsedThisCombo_gKK) == locUsedSoFar_gKK.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					dHist_MMKK_Measured->Fill(locMMKKP4_Measured.M());
					dHist_MMKK_KinFit->Fill(locMMKKP4_KinFit.M());
				}
				else {
					dHist_MMKK_Measured_wacc->Fill(locMMKKP4_Measured.M(),scaling_factor);
					dHist_MMKK_KinFit_wacc->Fill(locMMKKP4_KinFit.M(),scaling_factor);
				}
			}				
			locUsedSoFar_gKK.insert(locUsedThisCombo_gKK);
		}	//end of uniqueness for gKK	postChiSq




/****************************************** FILL FLAT TREE (IF DESIRED) ******************************************/

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

/******************************************* LOOP OVER THROWN DATA (OPTIONAL) ***************************************/
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
/****************************************** LOOP OVER OTHER ARRAYS (OPTIONAL) ***************************************/
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

/************************************ EXAMPLE: FILL CLONE OF TTREE HERE WITH CUTS APPLIED ************************************/
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

void DSelector_kpkpxim::Finalize(void)
{
	//Save anything to output here that you do not want to be in the default DSelector output ROOT file.

	//Otherwise, don't do anything else (especially if you are using PROOF).
		//If you are using PROOF, this function is called on each thread,
		//so anything you do will not have the combined information from the various threads.
		//Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

	//DO YOUR STUFF HERE
	myfile->close();
	delete myfile;
	myP4file->close();
	delete myP4file;

	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
