#ifndef DSelector_kpkpxim__M23_sept19_h
#define DSelector_kpkpxim__M23_sept19_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

class DSelector_kpkpxim__M23_sept19 : public DSelector
{
	public:

		DSelector_kpkpxim__M23_sept19(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_kpkpxim__M23_sept19(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

		// ANALYZE CUT ACTIONS
		// // Automatically makes mass histograms where one cut is missing
		DHistogramAction_AnalyzeCutActions* dAnalyzeCutActions;

		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dKPlus1Wrapper;
		DChargedTrackHypothesis* dKPlus2Wrapper;

		//Step 1
		DParticleComboStep* dStep1Wrapper;
		DChargedTrackHypothesis* dPiMinus1Wrapper;

		//Step 2
		DParticleComboStep* dStep2Wrapper;
		DKinematicData* dDecayingLambdaWrapper;
		DChargedTrackHypothesis* dPiMinus2Wrapper;
		DChargedTrackHypothesis* dProtonWrapper;

		//OUTPUT FILES
		//ofstream *myfile;

		// HISTOGRAMS
		//General histograms
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_BeamEnergy;
		TH1I* dHist_BeamBunch;
		TH1I* dHist_ChiSq;
		TH2I* dHist_ChiSqXi;
		TH1I* dHist_XiMass_Measured;	
		TH1I* dHist_XiMass_KinFit;
		TH1I* dHist_MMKK_Measured;
		TH1I* dHist_MMKK_KinFit;	
		TH2F* dHist_Xi_LambFlight;
		TH2F* dHist_Xi_LambFlight_acc;

		//Detached vertices check
		TH1I* dHist_XiPath;
		TH1I* dHist_XiPath_preCL;
		TH1I* dHist_XiPath_postCL;
		TH1I* dHist_ProdVert;
		TH1I* dHist_XiVert;
		TH1I* dHist_LambVert;
		TH1I* dHist_LambPath;

		//Beam asymmetry plots
		TH2I* dHist_phi_t;
		TH2I* dHist_acc_phi_t_1;
		TH2I* dHist_acc_phi_t_2;
		TH2I* dHist_acc_phi_t_3;
		TH2I* dHist_acc_phi_t_4;

		//Spin Measurement
		TH2I* dHist_Xi_cosGJ;
		TH2I* dHist_Xi_cosGJ_acc;

		//Cross section plots
		TH2F* dHist_Xi_Egamma;
		TH2F* dHist_Xi_Egamma_acc;
		TH2F* dHist_Xi_t;
		TH2F* dHist_Xi_t_acc;
		TH3F* dHist_Xi_Egamma_t;
		TH3F* dHist_Xi_Egamma_t_acc;
		TH2F* dHist_Xi_t_064;
		TH2F* dHist_Xi_t_064_acc;
		TH2F* dHist_Xi_t_069;
		TH2F* dHist_Xi_t_069_acc;
		TH2F* dHist_Xi_t_074;
		TH2F* dHist_Xi_t_074_acc;
		TH2F* dHist_Xi_t_079;
		TH2F* dHist_Xi_t_079_acc;
		TH2F* dHist_Xi_t_084;
		TH2F* dHist_Xi_t_084_acc;
		TH2F* dHist_Xi_t_089;
		TH2F* dHist_Xi_t_089_acc;
		TH2F* dHist_Xi_t_094;
		TH2F* dHist_Xi_t_094_acc;
		TH2F* dHist_Xi_t_099;
		TH2F* dHist_Xi_t_099_acc;
		TH2F* dHist_Xi_t_104;
		TH2F* dHist_Xi_t_104_acc;
		TH2F* dHist_Xi_t_109;
		TH2F* dHist_Xi_t_109_acc;
		TH2F* dHist_Xi_t_114;
		TH2F* dHist_Xi_t_114_acc;

		//Intermediate hyperon
		TH1I* dHist_KlowpXim;
		TH1I* dHist_KlowpXim_acc;
		TH2I* dHist_Klowp_pvstheta;
		TH2I* dHist_Khighp_pvstheta;
		TH2I* dHist_Klowp_pvstheta_acc;
		TH2I* dHist_Khighp_pvstheta_acc;

		//Angular distributions
		TH1I* dHist_XiMass_KinFit_Selected;
		TH2I* dHist_K_pTheta_Measured;
		TH2I* dHist_p_pTheta_Measured;
		TH2I* dHist_K_pTheta_KinFit;
		TH2I* dHist_K_ptTheta_Measured;
		TH2I* dHist_K_ptTheta_KinFit;
		TH1I* dHist_XiMass_kTheta15to35_Measured;
		TH1I* dHist_XiMass_kTheta15to35_KinFit;
		TH2I* dHist_pi_pTheta_Measured;
		TH2I* dHist_pi_pTheta_KinFit;
		TH2I* dHist_pi_ptTheta_Measured;
		TH2I* dHist_pi_ptTheta_KinFit;
		TH1I* dHist_XiMass_piTheta15to35_Measured;
		TH1I* dHist_XiMass_piTheta15to35_KinFit;
		TH1I* dHist_XiMass_MM_piTheta15to35_Measured;
		TH1I* dHist_XiMass_MM_piTheta15to35_KinFit;
		TH1I* dHist_XiMass_MM_kTheta15to35_Measured;
		TH1I* dHist_XiMass_MM_kTheta15to35_KinFit;
		TH1I* dHist_XiMass_KinFit_Selected_acc;	
		TH1I* dHist_XiMass_Measured_acc;	
		TH1I* dHist_XiMass_KinFit_acc;
		TH1I* dHist_MMKK_Measured_acc;
		TH1I* dHist_MMKK_KinFit_acc;
		TH2I* dHist_K_pTheta_Measured_acc;
		TH2I* dHist_p_pTheta_Measured_acc;
		TH2I* dHist_K_pTheta_KinFit_acc;
		TH2I* dHist_K_ptTheta_Measured_acc;
		TH2I* dHist_K_ptTheta_KinFit_acc;
		TH1I* dHist_XiMass_kTheta15to35_Measured_acc;
		TH1I* dHist_XiMass_kTheta15to35_KinFit_acc;
		TH2I* dHist_pi_pTheta_Measured_acc;
		TH2I* dHist_pi_pTheta_KinFit_acc;
		TH2I* dHist_pi_ptTheta_Measured_acc;
		TH2I* dHist_pi_ptTheta_KinFit_acc;
		TH1I* dHist_XiMass_piTheta15to35_Measured_acc;
		TH1I* dHist_XiMass_piTheta15to35_KinFit_acc;
		TH1I* dHist_XiMass_MM_piTheta15to35_Measured_acc;
		TH1I* dHist_XiMass_MM_piTheta15to35_KinFit_acc;
		TH1I* dHist_XiMass_MM_kTheta15to35_Measured_acc;
		TH1I* dHist_XiMass_MM_kTheta15to35_KinFit_acc;

		//Start timer trigger tests
		TH1F* dHist_Xi_Egamma_all;
		TH1F* dHist_Xi_t_all;
		TH1F* dHist_Xi_pP_all;
		TH1F* dHist_Xi_pTheta_all;
		TH1F* dHist_Xi_Egamma_withST;
		TH1F* dHist_Xi_t_withST;
		TH1F* dHist_Xi_pP_withST;
		TH1F* dHist_Xi_pTheta_withST;


	ClassDef(DSelector_kpkpxim__M23_sept19, 0);
};

void DSelector_kpkpxim__M23_sept19::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dKPlus1Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
	dKPlus2Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));

	//Step 1
	dStep1Wrapper = dComboWrapper->Get_ParticleComboStep(1);
	dPiMinus1Wrapper = static_cast<DChargedTrackHypothesis*>(dStep1Wrapper->Get_FinalParticle(0));

	//Step 2
	dStep2Wrapper = dComboWrapper->Get_ParticleComboStep(2);
	dDecayingLambdaWrapper = dStep2Wrapper->Get_InitialParticle();
	dPiMinus2Wrapper = static_cast<DChargedTrackHypothesis*>(dStep2Wrapper->Get_FinalParticle(0));
	dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep2Wrapper->Get_FinalParticle(1));
}

#endif // DSelector_kpkpxim__M23_sept19_h