#include "DSelector_kpkpxim__B4_M23_sept19.h"

void DSelector_kpkpxim__B4_M23_sept19::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "kpkpxim__B4_M23_sept19.root"; //"" for none
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

	// EXAMPLE: Create deque for histogramming particle masses:
	// // For histogramming the phi mass in phi -> K+ K-
	// // Be sure to change this and dAnalyzeCutActions to match reaction

	//ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
	//false/true below: use measured/kinfit data

	//PID

	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));
	//dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.4, KPlus, SYS_BCAL));
	//dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.2, KPlus, SYS_TOF));
	//dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.8, Proton, SYS_BCAL));
	//dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.5, Proton, SYS_TOF));

	//MASSES
	deque<Particle_t> locLambdaPIDs;  locLambdaPIDs.push_back(Proton); locLambdaPIDs.push_back(PiMinus); 
	deque<Particle_t> locXiPIDs;  locXiPIDs.push_back(Lambda);  locXiPIDs.push_back(PiMinus); 
	deque<Particle_t> locKXiPIDs;  locKXiPIDs.push_back(XiMinus);  locKXiPIDs.push_back(KPlus);   
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda, 200, 1.0, 1.2, "Lambda"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false,  XiMinus, 200, 1.1, 1.5, "XiMinus"));		
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, XiMinus, 200, 1.1, 1.5, "XiMinus_KinFit"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, 0, locKXiPIDs, 250, 1.5, 3.0, "KpXim"));

	//KINFIT RESULTS
	dAnalysisActions.push_back(new DHistogramAction_KinFitResults(dComboWrapper));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, false));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true, "KinFit"));


	// ANALYZE CUT ACTIONS
	// // Change MyPhi to match reaction


	//INITIALIZE ACTIONS
	//If you create any actions that you want to run manually (i.e. don't add to dAnalysisActions), be sure to initialize them here as well
	Initialize_Actions();

	/******************************** EXAMPLE USER INITIALIZATION: STAND-ALONE HISTOGRAMS *******************************/

	//EXAMPLE MANUAL HISTOGRAMS:
	dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 600, -0.06, 0.06);
	dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
	dHist_XiPath = new TH1I("XiPathLength", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_XiPath_preCL = new TH1I("XiPathLength_preCL", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_XiPath_postCL = new TH1I("XiPathLength_postCL", ";#Xi^{-} Path Length (cm)", 600, 0.0, 15.0);
	dHist_ProdVert = new TH1I("ProdVert", ";Production Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_XiVert = new TH1I("XiVert", ";#Xi^{-} Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambVert = new TH1I("LambVert", ";#Lambda Vertex Z (cm)", 600, -50.0, 200.0);
	dHist_LambPath = new TH1I("LambPathLength", ";#Lambda Path Length (cm)", 600, 0.0, 15.0);
	
	dHist_BeamBunch = new TH1I("BeamBunch", ";Beam Bunch", 400, -20.0, 20.0);
	dHist_ChiSq = new TH1I("ChiSq", "ChiSq", 200, 0.0, 100.0);
	dHist_ChiSqXi = new TH2I("ChiSqXi", "ChiSq",100,0.0,100.0,80,1.1,1.5);
	dHist_K_pTheta_Measured = new TH2I("K_pTheta_Measured", "K^{+} pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_Measured = new TH2I("p_pTheta_Measured", "p pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_K_pTheta_KinFit = new TH2I("K_pTheta_KinFit", "K^{+} pvsTheta KinFit",28,0.0,140,40,0.0,10.0);
	dHist_K_ptTheta_Measured = new TH2I("K_ptTheta_Measured", "K^{+} ptvsTheta Measured",28,0.0,140,40,0.0,2.0);
	dHist_K_ptTheta_KinFit = new TH2I("K_ptTheta_KinFit", "K^{+} ptvsTheta KinFit",28,0.0,140,40,0.0,2.0);
	dHist_XiMass_Measured=new TH1I("XiMass","#Xi- Invariant Mass (GeV/c^{2})", 80,1.1,1.5);
	dHist_XiMass_KinFit=new TH1I("XiMass_KinFit","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_KinFit_Selected=new TH1I("XiMass_KinFit_Selected","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 80,1.1,1.5);
	dHist_MMKK_Measured=new TH1I("MMKK_Measured","MM(K^{+}K^{+}) (GeV/c^{2})", 80,1.1,1.5);
	dHist_MMKK_KinFit=new TH1I("MMKK_KinFit","MM(K^{+}K^{+}) (GeV/c^{2},KinFit)", 80,1.1,1.5);
	dHist_XiMass_kTheta15to35_Measured=new TH1I("XiMass_kTheta_Measured","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_kTheta15to35_KinFit=new TH1I("XiMass_kTheta_KinFit","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_pi_pTheta_Measured = new TH2I("pi_pTheta_Measured", "#pi^{-} pvsTheta Measured",28,0.0,140,30,0.0,3.0);
	dHist_pi_pTheta_KinFit = new TH2I("pi_pTheta_KinFit", "#pi^{-} pvsTheta KinFit",28,0.0,140,30,0.0,3.0);
	dHist_pi_ptTheta_Measured = new TH2I("pi_ptTheta_Measured", "#pi^{-} ptvsTheta Measured",28,0.0,140,40,0.0,1.0);
	dHist_pi_ptTheta_KinFit = new TH2I("pi_ptTheta_KinFit", "#pi^{-} ptvsTheta KinFit",28,0.0,140,40,0.0,1.0);
	dHist_XiMass_piTheta15to35_Measured=new TH1I("XiMass_piTheta_Measured","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_piTheta15to35_KinFit=new TH1I("XiMass_piTheta_KinFit","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_Measured=new TH1I("XiMass_MM_piTheta_Measured","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_KinFit=new TH1I("XiMass_MM_piTheta_KinFit","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_Measured=new TH1I("XiMass_MM_kTheta_Measured","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_KinFit=new TH1I("XiMass_MM_kTheta_KinFit","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_phi_t = new TH2I("phi_t", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 100, 0.0, 5.0,180, -180., 180.);
	dHist_acc_phi_t_1 = new TH2I("acc_phi_t_1", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 100, 0.0, 5.0,180, -180., 180.);
	dHist_acc_phi_t_2 = new TH2I("acc_phi_t_2", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 100, 0.0, 5.0,180, -180., 180.);
	dHist_acc_phi_t_3 = new TH2I("acc_phi_t_3", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 100, 0.0, 5.0,180, -180., 180.);
	dHist_acc_phi_t_4 = new TH2I("acc_phi_t_4", ";-t (GeV/c)^{2}; #phi_{K^{+}}", 100, 0.0, 5.0,180, -180., 180.);
	dHist_XiMass024 =new TH1I("XiMass024",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass029 =new TH1I("XiMass029",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass034 =new TH1I("XiMass034",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass039 =new TH1I("XiMass039",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass044 =new TH1I("XiMass044",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass049 =new TH1I("XiMass049",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass054 =new TH1I("XiMass054",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass059 =new TH1I("XiMass059",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass064 =new TH1I("XiMass064",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass069 =new TH1I("XiMass069",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass074 =new TH1I("XiMass074",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass079 =new TH1I("XiMass079",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass084 =new TH1I("XiMass084",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass089 =new TH1I("XiMass089",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass094 =new TH1I("XiMass094",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass099 =new TH1I("XiMass099",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass104 =new TH1I("XiMass104",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass109 =new TH1I("XiMass109",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass114 =new TH1I("XiMass114",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	
	dHist_K_pTheta_Measured_acc = new TH2I("K_pTheta_Measured_acc", "K^{+} pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_p_pTheta_Measured_acc = new TH2I("p_pTheta_Measured_acc", "p pvsTheta Measured",28,0.0,140,40,0.0,10.0);
	dHist_K_pTheta_KinFit_acc = new TH2I("K_pTheta_KinFit_acc", "K^{+} pvsTheta KinFit",28,0.0,140,40,0.0,10.0);
	dHist_K_ptTheta_Measured_acc = new TH2I("K_ptTheta_Measured_acc", "K^{+} ptvsTheta Measured",28,0.0,140,40,0.0,2.0);
	dHist_K_ptTheta_KinFit_acc = new TH2I("K_ptTheta_KinFit_acc", "K^{+} ptvsTheta KinFit",28,0.0,140,40,0.0,2.0);
	dHist_XiMass_Measured_acc=new TH1I("XiMass_acc","#Xi- Invariant Mass (GeV/c^{2})", 80,1.1,1.5);
	dHist_XiMass_KinFit_acc=new TH1I("XiMass_KinFit_acc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 400,1.1,1.5);
	dHist_XiMass_KinFit_Selected_acc=new TH1I("XiMass_KinFit_Selected_acc","#Xi- Invariant Mass (GeV/c^{2},KinFit)", 80,1.1,1.5);
	dHist_MMKK_Measured_acc=new TH1I("MMKK_Measured_acc","MM(K^{+}K^{+}) (GeV/c^{2})", 80,1.1,1.5);
	dHist_MMKK_KinFit_acc=new TH1I("MMKK_KinFit_acc","MM(K^{+}K^{+}) (GeV/c^{2},KinFit)", 80,1.1,1.5);
	dHist_XiMass_kTheta15to35_Measured_acc=new TH1I("XiMass_kTheta_Measured_acc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_kTheta15to35_KinFit_acc=new TH1I("XiMass_kTheta_KinFit_acc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_pi_pTheta_Measured_acc = new TH2I("pi_pTheta_Measured_acc", "#pi^{-} pvsTheta Measured",28,0.0,140,30,0.0,3.0);
	dHist_pi_pTheta_KinFit_acc = new TH2I("pi_pTheta_KinFit_acc", "#pi^{-} pvsTheta KinFit",28,0.0,140,30,0.0,3.0);
	dHist_pi_ptTheta_Measured_acc = new TH2I("pi_ptTheta_Measured_acc", "#pi^{-} ptvsTheta Measured",28,0.0,140,40,0.0,1.0);
	dHist_pi_ptTheta_KinFit_acc = new TH2I("pi_ptTheta_KinFit_acc", "#pi^{-} ptvsTheta KinFit",28,0.0,140,40,0.0,1.0);
	dHist_XiMass_piTheta15to35_Measured_acc=new TH1I("XiMass_piTheta_Measured_acc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_piTheta15to35_KinFit_acc=new TH1I("XiMass_piTheta_KinFit_acc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_Measured_acc=new TH1I("XiMass_MM_piTheta_Measured_acc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_piTheta15to35_KinFit_acc=new TH1I("XiMass_MM_piTheta_KinFit_acc","#Xi- Invariant Mass #theta_{#pi}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_Measured_acc=new TH1I("XiMass_MM_kTheta_Measured_acc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass_MM_kTheta15to35_KinFit_acc=new TH1I("XiMass_MM_kTheta_KinFit_acc","#Xi- Invariant Mass #theta_{K}(15,35) (GeV/c^{2},KinFit)", 40,1.1,1.5);
	dHist_XiMass024_acc=new TH1I("XiMass024_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass029_acc=new TH1I("XiMass029_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass034_acc=new TH1I("XiMass034_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass039_acc=new TH1I("XiMass039_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass044_acc=new TH1I("XiMass044_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass049_acc=new TH1I("XiMass049_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass054_acc=new TH1I("XiMass054_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass059_acc=new TH1I("XiMass059_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass064_acc=new TH1I("XiMass064_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass069_acc=new TH1I("XiMass069_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass074_acc=new TH1I("XiMass074_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass079_acc=new TH1I("XiMass079_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass084_acc=new TH1I("XiMass084_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass089_acc=new TH1I("XiMass089_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass094_acc=new TH1I("XiMass094_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass099_acc=new TH1I("XiMass099_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass104_acc=new TH1I("XiMass104_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass109_acc=new TH1I("XiMass109_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);
	dHist_XiMass114_acc=new TH1I("XiMass114_acc",";#Xi^{-} Invariant Mass (GeV/c^{2})", 40,1.1,1.5);	
	dHist_Xi_cosGJ = new TH2I("Xi_cosGJ", " ;#Lambda#pi^{-} mass (GeV); cos #theta_{GJ}", 80, 1.1, 1.5,180, -1., 1.);
	dHist_Xi_cosGJ_acc = new TH2I("Xi_cosGJ_acc", " ;#Lambda#pi^{-} mass (GeV); cos #theta_{GJ}", 80, 1.1, 1.5,180, -1., 1.);
	dHist_Xi_Egamma = new TH2I("Xi_Egamma", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma}", 80, 1.1, 1.5,180, 3.0, 12.0);
	dHist_Xi_Egamma_acc = new TH2I("Xi_Egamma_acc", " ;#Lambda#pi^{-} mass (GeV); E_{#gamma} (GeV)", 80, 1.1, 1.5,180, 3.0, 12.0);
	
	dHist_KplowXim = new TH1I("KplowXim",";K_{plow}#Xi^{-} mass (GeV)", 80,1.6,2.0);
	dHist_KplowXim_acc = new TH1I("KplowXim_acc",";K_{plow}#Xi^{-} mass (GeV)", 80,1.6,2.0);

	myfile = new ofstream("XiEventNumbers_XiMassKinFit_2018-08_batch01.txt");
	*myfile << "RunNumber " << "EventNumber " << "XiMass_Measured " << "XiMass_KinFit " << "DeltaT " << "BeamE " << " ChiSqNDf" <<  endl;

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

Bool_t DSelector_kpkpxim__B4_M23_sept19::Process(Long64_t locEntry)
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

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_Pathlength;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_ChiSq;
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_Asymmetry;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts2;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts3;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts4;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_PostCuts5;
	set<map<Particle_t,set<Int_t>>>locUsedSoFar_Eventlist;
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

		// DO YOUR STUFF HERE

		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locKPlus1P4_Measured + locKPlus2P4_Measured + locPiMinus1P4_Measured + locPiMinus2P4_Measured + locProtonP4_Measured;
		TLorentzVector locDecayingLambdaX4 = dDecayingLambdaWrapper->Get_X4();

		TLorentzVector locDecayingXiX4 = dTreeInterface->Get_TObject<TLorentzVector>("DecayingXiMinus__X4",loc_i);
		TLorentzVector locDecayingLambX4 = dTreeInterface->Get_TObject<TLorentzVector>("DecayingLambda__X4",loc_i);
		TLorentzVector locProdSpacetimeVertex =dComboBeamWrapper->Get_X4();//Get production vertex
		TLorentzVector locDeltaSpacetimeXi = locProdSpacetimeVertex - locDecayingXiX4;//vertex difference
		TLorentzVector locDeltaSpacetimeLamb = locDecayingXiX4 - locDecayingLambX4;//vertex difference
		double locPathLengthXi = locDeltaSpacetimeXi.Vect().Mag();//pathlength is just the magnitude
		double locPathLengthLamb = locDeltaSpacetimeLamb.Vect().Mag();//pathlength is just the magnitude

		TLorentzVector locXiP4_Measured =  locPiMinus1P4_Measured + locPiMinus2P4_Measured + locProtonP4_Measured;
		TLorentzVector locXiP4_KinFit =  locPiMinus1P4 + locPiMinus2P4 + locProtonP4;
		TLorentzVector locMMKKP4_Measured = locBeamP4_Measured + dTargetP4 - locKPlus1P4_Measured - locKPlus2P4_Measured;
		TLorentzVector locMMKKP4_KinFit = locBeamP4 + dTargetP4 - locKPlus1P4 - locKPlus2P4;

        //BoostVector for CoM
     		TLorentzVector locCoMP4=locBeamP4 + dTargetP4;
	        TVector3 boostCoM=locCoMP4.BoostVector();
       //Boost in CoM
	        TLorentzVector locBeamP4_CM=locBeamP4;
	        TLorentzVector locKPlus1P4_CM=locKPlus1P4;
	        TLorentzVector locKPlus2P4_CM=locKPlus2P4;
		TLorentzVector locXiP4_CM = locXiP4_KinFit;
	        TLorentzVector locPiMinus1P4_CM=locPiMinus1P4;
	        TLorentzVector locDecayingLambdaP4_CM =  locDecayingLambdaP4;
		locBeamP4_CM.Boost(-boostCoM);
		locKPlus1P4_CM.Boost(-boostCoM);
		locKPlus2P4_CM.Boost(-boostCoM);
		locXiP4_CM.Boost(-boostCoM);
		locPiMinus1P4_CM.Boost(-boostCoM);
		locDecayingLambdaP4_CM.Boost(-boostCoM);
	//BoostVector for GJ
		TVector3 boostGJ =locXiP4_CM.BoostVector();
	//Boost in GJ
	        TLorentzVector locBeamP4_GJ=locBeamP4_CM;
	        TLorentzVector locKPlus1P4_GJ=locKPlus1P4_CM;
	        TLorentzVector locKPlus2P4_GJ=locKPlus2P4_CM;
		TLorentzVector locXiP4_GJ = locXiP4_CM;
	        TLorentzVector locPiMinus1P4_GJ=locPiMinus1P4_CM;
	        TLorentzVector locDecayingLambdaP4_GJ =  locDecayingLambdaP4_CM;
		locBeamP4_GJ.Boost(-boostGJ);
		locKPlus1P4_GJ.Boost(-boostGJ);
		locKPlus2P4_GJ.Boost(-boostGJ);
		locXiP4_GJ.Boost(-boostGJ);
		locPiMinus1P4_GJ.Boost(-boostGJ);
		locDecayingLambdaP4_GJ.Boost(-boostGJ);
	//GJ Frame
		TVector3 z_GJ;
		z_GJ.SetXYZ(locBeamP4_GJ.X(),locBeamP4_GJ.Y(),locBeamP4_GJ.Z());
		TVector3 z_hat_GJ=z_GJ.Unit();
		TVector3 y_GJ=locBeamP4_CM.Vect().Cross(locXiP4_CM.Vect());
		TVector3 y_hat_GJ=y_GJ.Unit();
		TVector3 x_hat_GJ=y_hat_GJ.Cross(z_hat_GJ);
	//Definition of Angles
		TVector3 v_GJ(locPiMinus1P4_GJ.Vect()*x_hat_GJ,locPiMinus1P4_GJ.Vect()*y_hat_GJ,locPiMinus1P4_GJ.Vect()*z_hat_GJ);
		double cosTheta_GJ = v_GJ.CosTheta();
		double theta_GJ = v_GJ.Theta();
		double phi_GJ = v_GJ.Phi()*180./TMath::Pi();


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

		/************************************ EXAMPLE: HISTOGRAM MISSING MASS SQUARED ************************************/

		//Missing Mass Squared
		double locMissingMassSquared = locMissingP4_Measured.M2();

		//Uniqueness tracking: Build the map of particles used for the missing mass
			//For beam: Don't want to group with final-state photons. Instead use "Unknown" PID (not ideal, but it's easy).
		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_MissingMass[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_MissingMass[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);

		//compare to what's been used so far
		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
		{
			//unique missing mass combo: histogram it, and register this combo of particles
			dHist_MissingMassSquared->Fill(locMissingMassSquared);
			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
		}


		map<Particle_t, set<Int_t> > locUsedThisCombo_Pathlength;
		locUsedThisCombo_Pathlength[Unknown].insert(locBeamID); 
		locUsedThisCombo_Pathlength[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_Pathlength[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_Pathlength[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_Pathlength[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_Pathlength[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_Pathlength.find(locUsedThisCombo_Pathlength) == locUsedSoFar_Pathlength.end()){
			dHist_XiPath->Fill(locPathLengthXi);
			dHist_LambPath->Fill(locPathLengthLamb);
			dHist_ProdVert->Fill(locProdSpacetimeVertex.Z());
			dHist_XiVert->Fill(locDecayingXiX4.Z());
			dHist_LambVert->Fill(locDecayingLambX4.Z());
			locUsedSoFar_Pathlength.insert(locUsedThisCombo_Pathlength);
		}

		//E.g.  ChiSq 
		Float_t locChiSq = dComboWrapper->Get_ChiSq_KinFit("");
		Float_t locNDF = dComboWrapper->Get_NDF_KinFit("");
		Float_t locChiSqNdf = locChiSq/locNDF;
		map<Particle_t, set<Int_t> > locUsedThisCombo_ChiSq;
		locUsedThisCombo_ChiSq[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_ChiSq[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_ChiSq[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_ChiSq.find(locUsedThisCombo_ChiSq) == locUsedSoFar_ChiSq.end())
		{
			dHist_ChiSq->Fill(locChiSqNdf);
			dHist_ChiSqXi->Fill(locChiSqNdf, locXiP4_Measured.M());
			dHist_XiPath_preCL->Fill(locPathLengthXi);
			//cerr << locNDF << endl;
			locUsedSoFar_ChiSq.insert(locUsedThisCombo_ChiSq);
		}		
		//E.g. ChiSq Cut
		if((locChiSqNdf > 3.50))
		{
			dComboWrapper->Set_IsComboCut(true);
			continue;
		}


		//E.g.  PostCuts Hists 
		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts;
		locUsedThisCombo_PostCuts[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_PostCuts[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_PostCuts[Proton].insert(locProtonTrackID);
		TLorentzVector locX4 = dComboBeamWrapper->Get_X4();
		double locRFTime = dComboWrapper->Get_RFTime_Measured();
		double dTargetCenterZ = dComboWrapper->Get_TargetCenter().Z();
		double locPropagatedRFTime = locRFTime + (locX4.Z() - dTargetCenterZ)/29.9792458;
		double locDeltaT = locX4.T() - locPropagatedRFTime;
		if(locUsedSoFar_PostCuts.find(locUsedThisCombo_PostCuts) == locUsedSoFar_PostCuts.end()){
			dHist_XiPath_postCL->Fill(locPathLengthXi);
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					*myfile << Get_RunNumber() << " " << Get_EventNumber() << " " << locXiP4_Measured.M() << " " << locXiP4_KinFit.M() << " " << locDeltaT << " " << locBeamP4.E() << " " << locChiSqNdf  << endl;
					dHist_XiMass_Measured->Fill(locXiP4_Measured.M());
					dHist_XiMass_KinFit->Fill(locXiP4_KinFit.M());
					dHist_Xi_cosGJ->Fill(locXiP4_KinFit.M(),cosTheta_GJ);
					dHist_Xi_Egamma->Fill(locXiP4_KinFit.M(),locBeamP4.E());
				}
				else { 
					dHist_XiMass_Measured_acc->Fill(locXiP4_Measured.M());
					dHist_XiMass_KinFit_acc->Fill(locXiP4_KinFit.M());
					dHist_Xi_cosGJ_acc->Fill(locXiP4_KinFit.M(),cosTheta_GJ);
					dHist_Xi_Egamma_acc->Fill(locXiP4_KinFit.M(),locBeamP4.E());

				}
				
				if(locXiP4_KinFit.M() >1.31 && locXiP4_KinFit.M() < 1.33){ 
					if(fabs(locDeltaT) < 2.004) { 
						dHist_p_pTheta_Measured->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P());
					}
					else { 
						dHist_p_pTheta_Measured_acc->Fill(locProtonP4_Measured.Theta()*180./TMath::Pi(), locProtonP4_Measured.P());
					}		
				}
				if((locPiMinus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locPiMinus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){ 
					if(fabs(locDeltaT) < 2.004) {	
						dHist_XiMass_piTheta15to35_Measured->Fill(locXiP4_Measured.M());
						dHist_XiMass_piTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
					}
					else {
						dHist_XiMass_piTheta15to35_Measured_acc->Fill(locXiP4_Measured.M());
						dHist_XiMass_piTheta15to35_KinFit_acc->Fill(locXiP4_KinFit.M());
					}
				}
				if(fabs(locDeltaT) < 2.004) {
					if(locBeamP4.E() >= 2.4 && locBeamP4.E() < 2.9)	{dHist_XiMass024->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 2.9 && locBeamP4.E() < 3.4)	{dHist_XiMass029->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 3.4 && locBeamP4.E() < 3.9)	{dHist_XiMass034->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 3.9 && locBeamP4.E() < 4.4)	{dHist_XiMass039->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 4.4 && locBeamP4.E() < 4.9)	{dHist_XiMass044->Fill(locXiP4_KinFit.M());}	
					if(locBeamP4.E() >= 4.9 && locBeamP4.E() < 5.4)	{dHist_XiMass049->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 5.4 && locBeamP4.E() < 5.9)	{dHist_XiMass054->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 5.9 && locBeamP4.E() < 6.4)	{dHist_XiMass059->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 6.4 && locBeamP4.E() < 6.9)	{dHist_XiMass064->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 6.9 && locBeamP4.E() < 7.4)	{dHist_XiMass069->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 7.4 && locBeamP4.E() < 7.9)	{dHist_XiMass074->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 7.9 && locBeamP4.E() < 8.4)	{dHist_XiMass079->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 8.4 && locBeamP4.E() < 8.9)	{dHist_XiMass084->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 8.9 && locBeamP4.E() < 9.4)	{dHist_XiMass089->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 9.4 && locBeamP4.E() < 9.9)	{dHist_XiMass094->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 9.9 && locBeamP4.E() < 10.4)	{dHist_XiMass099->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 10.4 && locBeamP4.E() < 10.9)	{dHist_XiMass104->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 10.9 && locBeamP4.E() < 11.4)	{dHist_XiMass109->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 11.4 && locBeamP4.E() < 11.9)	{dHist_XiMass114->Fill(locXiP4_KinFit.M());}
				}
				else {
					if(locBeamP4.E() >= 2.4 && locBeamP4.E() < 2.9)	{dHist_XiMass024_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 2.9 && locBeamP4.E() < 3.4)	{dHist_XiMass029_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 3.4 && locBeamP4.E() < 3.9)	{dHist_XiMass034_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 3.9 && locBeamP4.E() < 4.4)	{dHist_XiMass039_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 4.4 && locBeamP4.E() < 4.9)	{dHist_XiMass044_acc->Fill(locXiP4_KinFit.M());}	
					if(locBeamP4.E() >= 4.9 && locBeamP4.E() < 5.4)	{dHist_XiMass049_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 5.4 && locBeamP4.E() < 5.9)	{dHist_XiMass054_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 5.9 && locBeamP4.E() < 6.4)	{dHist_XiMass059_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 6.4 && locBeamP4.E() < 6.9)	{dHist_XiMass064_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 6.9 && locBeamP4.E() < 7.4)	{dHist_XiMass069_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 7.4 && locBeamP4.E() < 7.9)	{dHist_XiMass074_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 7.9 && locBeamP4.E() < 8.4)	{dHist_XiMass079_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 8.4 && locBeamP4.E() < 8.9)	{dHist_XiMass084_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 8.9 && locBeamP4.E() < 9.4)	{dHist_XiMass089_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 9.4 && locBeamP4.E() < 9.9)	{dHist_XiMass094_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 9.9 && locBeamP4.E() < 10.4)	{dHist_XiMass099_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 10.4 && locBeamP4.E() < 10.9)	{dHist_XiMass104_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 10.9 && locBeamP4.E() < 11.4)	{dHist_XiMass109_acc->Fill(locXiP4_KinFit.M());}
					if(locBeamP4.E() >= 11.4 && locBeamP4.E() < 11.9)	{dHist_XiMass114_acc->Fill(locXiP4_KinFit.M());}
				}
			}

			locUsedSoFar_PostCuts.insert(locUsedThisCombo_PostCuts);
		}


		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts2;
		locUsedThisCombo_PostCuts2[Unknown].insert(locBeamID);
		locUsedThisCombo_PostCuts2[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_PostCuts2[KPlus].insert(locKPlus2TrackID);
		if(locUsedSoFar_PostCuts2.find(locUsedThisCombo_PostCuts2) == locUsedSoFar_PostCuts2.end())	{
			if(fabs(locDeltaT) < 6.004) {	
				if(fabs(locDeltaT) < 2.004) {	
					dHist_MMKK_Measured->Fill(locMMKKP4_Measured.M());
					dHist_MMKK_KinFit->Fill(locMMKKP4_KinFit.M());
				}
				else {
					dHist_MMKK_Measured_acc->Fill(locMMKKP4_Measured.M());
					dHist_MMKK_KinFit_acc->Fill(locMMKKP4_KinFit.M());
				}
				if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
					if(fabs(locDeltaT) < 2.004) {
						dHist_K_pTheta_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P());
						dHist_K_pTheta_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P());
						dHist_K_pTheta_KinFit->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.P());
						dHist_K_pTheta_KinFit->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.P());
						dHist_K_ptTheta_Measured->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.Pt());
						dHist_K_ptTheta_Measured->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.Pt());
						dHist_K_ptTheta_KinFit->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.Pt());
						dHist_K_ptTheta_KinFit->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.Pt());
					}
					else {
						dHist_K_pTheta_Measured_acc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.P());
						dHist_K_pTheta_Measured_acc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.P());
						dHist_K_pTheta_KinFit_acc->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.P());
						dHist_K_pTheta_KinFit_acc->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.P());
						dHist_K_ptTheta_Measured_acc->Fill(locKPlus1P4_Measured.Theta()*180./TMath::Pi(),locKPlus1P4_Measured.Pt());
						dHist_K_ptTheta_Measured_acc->Fill(locKPlus2P4_Measured.Theta()*180./TMath::Pi(),locKPlus2P4_Measured.Pt());
						dHist_K_ptTheta_KinFit_acc->Fill(locKPlus1P4.Theta()*180./TMath::Pi(),locKPlus1P4.Pt());
						dHist_K_ptTheta_KinFit_acc->Fill(locKPlus2P4.Theta()*180./TMath::Pi(),locKPlus2P4.Pt());
					}
				}
			}		
			locUsedSoFar_PostCuts2.insert(locUsedThisCombo_PostCuts2);
		}

		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts3;
		locUsedThisCombo_PostCuts3[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_PostCuts3[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_PostCuts3[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_PostCuts3[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_PostCuts3[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_PostCuts3.find(locUsedThisCombo_PostCuts3) == locUsedSoFar_PostCuts3.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if((locKPlus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locKPlus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locKPlus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){
					if(fabs(locDeltaT) < 2.004) {	
						dHist_XiMass_kTheta15to35_Measured->Fill(locXiP4_Measured.M());
						dHist_XiMass_kTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
						if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
							dHist_XiMass_MM_kTheta15to35_Measured->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_kTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
						}
					}
					else {
						dHist_XiMass_kTheta15to35_Measured_acc->Fill(locXiP4_Measured.M());
						dHist_XiMass_kTheta15to35_KinFit_acc->Fill(locXiP4_KinFit.M());
						if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
							dHist_XiMass_MM_kTheta15to35_Measured_acc->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_kTheta15to35_KinFit_acc->Fill(locXiP4_KinFit.M());
						}
					}
				}
			}
			locUsedSoFar_PostCuts3.insert(locUsedThisCombo_PostCuts3);
		}



		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts4;
		locUsedThisCombo_PostCuts4[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_PostCuts4[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_PostCuts4[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_PostCuts4[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_PostCuts4[Unknown].insert(locBeamID);
		if(locUsedSoFar_PostCuts4.find(locUsedThisCombo_PostCuts4) == locUsedSoFar_PostCuts4.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
					if(fabs(locDeltaT) < 2.004) {	
						dHist_pi_pTheta_Measured->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.P());
						dHist_pi_pTheta_Measured->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.P());
						dHist_pi_pTheta_KinFit->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.P());
						dHist_pi_pTheta_KinFit->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.P());
						dHist_pi_ptTheta_Measured->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.Pt());
						dHist_pi_ptTheta_Measured->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.Pt());
						dHist_pi_ptTheta_KinFit->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.Pt());
						dHist_pi_ptTheta_KinFit->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.Pt());
					}
					else {
						dHist_pi_pTheta_Measured_acc->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.P());
						dHist_pi_pTheta_Measured_acc->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.P());
						dHist_pi_pTheta_KinFit_acc->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.P());
						dHist_pi_pTheta_KinFit_acc->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.P());
						dHist_pi_ptTheta_Measured_acc->Fill(locPiMinus1P4_Measured.Theta()*180./TMath::Pi(),locPiMinus1P4_Measured.Pt());
						dHist_pi_ptTheta_Measured_acc->Fill(locPiMinus2P4_Measured.Theta()*180./TMath::Pi(),locPiMinus2P4_Measured.Pt());
						dHist_pi_ptTheta_KinFit_acc->Fill(locPiMinus1P4.Theta()*180./TMath::Pi(),locPiMinus1P4.Pt());
						dHist_pi_ptTheta_KinFit_acc->Fill(locPiMinus2P4.Theta()*180./TMath::Pi(),locPiMinus2P4.Pt());
					}
				}	
			}	
			locUsedSoFar_PostCuts4.insert(locUsedThisCombo_PostCuts4);
		}


		map<Particle_t, set<Int_t> > locUsedThisCombo_PostCuts5;
		locUsedThisCombo_PostCuts5[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_PostCuts5[KPlus].insert(locKPlus2TrackID);
		locUsedThisCombo_PostCuts5[PiMinus].insert(locPiMinus1TrackID);
		locUsedThisCombo_PostCuts5[PiMinus].insert(locPiMinus2TrackID);
		locUsedThisCombo_PostCuts5[Unknown].insert(locBeamID);
		locUsedThisCombo_PostCuts5[Proton].insert(locProtonTrackID);
		if(locUsedSoFar_PostCuts5.find(locUsedThisCombo_PostCuts5) == locUsedSoFar_PostCuts5.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if((locPiMinus1P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus1P4_Measured.Theta() < 35.*TMath::Pi()/180.) || (locPiMinus2P4_Measured.Theta() > 15.*TMath::Pi()/180. && locPiMinus2P4_Measured.Theta() < 35.*TMath::Pi()/180.)){			
					if(locMMKKP4_Measured.M() >= 1.27 && locMMKKP4_Measured.M() < 1.37){
						if(fabs(locDeltaT) < 2.004) {	
							dHist_XiMass_MM_piTheta15to35_Measured->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_piTheta15to35_KinFit->Fill(locXiP4_KinFit.M());
						}
						else {
							dHist_XiMass_MM_piTheta15to35_Measured_acc->Fill(locXiP4_Measured.M());
							dHist_XiMass_MM_piTheta15to35_KinFit_acc->Fill(locXiP4_KinFit.M());
						}
					}
				}
			}
			locUsedSoFar_PostCuts5.insert(locUsedThisCombo_PostCuts5);
		}

		//Asymmetry
		TLorentzVector locKPlusP4;		
		if(locKPlus1P4.Theta() < 13*TMath::Pi()/180.) { locKPlusP4 = locKPlus1P4; }
		else { locKPlusP4 = locKPlus2P4; }
		double t= (locBeamP4 - locKPlusP4).M2();
		double phi = locKPlusP4.Phi()*180/TMath::Pi();
		if(phi < -180.) phi = phi + 360.;
		if (phi > 180.) phi = phi - 360.;
		map<Particle_t, set<Int_t>> locUsedThisCombo_Asymmetry;
		locUsedThisCombo_Asymmetry[Unknown].insert(locBeamID);
		locUsedThisCombo_Asymmetry[KPlus].insert(locKPlus1TrackID);
		locUsedThisCombo_Asymmetry[KPlus].insert(locKPlus2TrackID);
		if(locUsedSoFar_Asymmetry.find(locUsedThisCombo_Asymmetry) == locUsedSoFar_Asymmetry.end()){
			if(fabs(locDeltaT) < 6.004) {	
				if (locBeamP4.E() >= 8.2 && locBeamP4.E() <= 8.8){ 
					if (locXiP4_Measured.M() >= 1.31 && locXiP4_Measured.M() <= 1.34){ 
						dHist_BeamBunch->Fill(locDeltaT);
						if(fabs(locDeltaT) < 2.004) {
							dHist_XiMass_KinFit_Selected->Fill(locXiP4_KinFit.M());	
							dHist_phi_t->Fill(-1.*t, phi); 
						}
						else {
							dHist_XiMass_KinFit_Selected_acc->Fill(locXiP4_KinFit.M());	
							dHist_acc_phi_t_1->Fill(-1.*t, phi);
						} 
					}
				}
			}
			else {
				dHist_acc_phi_t_4->Fill(-1.*t, phi);
			}
			locUsedSoFar_Asymmetry.insert(locUsedThisCombo_Asymmetry);
		}
		//E.g. Cut
		//if((locMissingMassSquared < -0.04) || (locMissingMassSquared > 0.04))
		//{
		//	dComboWrapper->Set_IsComboCut(true);
		//	continue;
		//}

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

void DSelector_kpkpxim__B4_M23_sept19::Finalize(void)
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
