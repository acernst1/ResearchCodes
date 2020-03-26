#ifndef DSelector_kpkpxim_h
#define DSelector_kpkpxim_h

#include <iostream>
#include <fstream>
#include <math.h>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

class DSelector_kpkpxim : public DSelector
{
	public:

		DSelector_kpkpxim(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_kpkpxim(){}

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
		ofstream *myfile;

		// HISTOGRAMS
		//General histograms
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_BeamEnergy;
		TH1I* dHist_BeamBunch_Asym;
		TH1I* dHist_BeamBunch_Xi;
		TH1I* dHist_BeamBunch_Xi_acc;
		TH1I* dHist_BeamBunch_Xi_wacc;
		TH1I* dHist_ChiSq;
		TH2I* dHist_ChiSqXi;
		TH2I* dHist_ChiSqXi_KinFit;
		TH2I* dHist_ChiSqXi_KinFit_acc;
		TH2I* dHist_ChiSqXi_KinFit_wacc;
		TH2I* dHist_ChiSqKp;
		TH2I* dHist_ChiSqKp_wacc;
		TH1I* dHist_XiMass_Measured;	
		TH1I* dHist_XiMass_KinFit;
		TH1I* dHist_XiMass_Measured_nan;	
		TH1I* dHist_XiMass_KinFit_nan;
		TH1I* dHist_XiMass_Measured_wacc;	
		TH1I* dHist_XiMass_KinFit_acc;
		TH1I* dHist_XiMass_KinFit_wacc;
		TH1I* dHist_XiMass_Measured_nan_wacc;	
		TH1I* dHist_XiMass_KinFit_nan_wacc;
		TH1I* dHist_MMKK_Measured;
		TH1I* dHist_MMKK_KinFit;	
		TH2F* dHist_Xi_LambFlight;
		TH2F* dHist_Xi_LambFlight_wacc;
		TH2F* dHist_Xi_XiFlight;
		TH2F* dHist_Xi_XiFlight_wacc;

		//Detached vertices check
		TH1I* dHist_ProdVert_preCL;
		TH1I* dHist_XiVert_preCL;
		TH1I* dHist_LambVert_preCL;
		TH1I* dHist_XiPath_preCL;
		TH1I* dHist_LambPath_preCL;
		TH1I* dHist_ProdVert_preCL_wacc;
		TH1I* dHist_XiVert_preCL_wacc;
		TH1I* dHist_LambVert_preCL_wacc;
		TH1I* dHist_XiPath_preCL_wacc;
		TH1I* dHist_LambPath_preCL_wacc;
		TH1I* dHist_ProdVert_postCL;
		TH1I* dHist_XiVert_postCL;
		TH1I* dHist_LambVert_postCL;
		TH1I* dHist_XiPath_postCL;
		TH1I* dHist_LambPath_postCL;
		TH1I* dHist_ProdVert_postCL_wacc;
		TH1I* dHist_XiVert_postCL_wacc;
		TH1I* dHist_LambVert_postCL_wacc;
		TH1I* dHist_XiPath_postCL_wacc;
		TH1I* dHist_LambPath_postCL_wacc;

		//Beam asymmetry plots
		TH2I* dHist_phi_t;
		TH2I* dHist_wacc_phi_t_1;
		TH2I* dHist_wacc_phi_t_2;
		TH2I* dHist_wacc_phi_t_3;
		TH2I* dHist_wacc_phi_t_4;

		//Spin Measurement
		TH2I* dHist_Xi_cosGJ;
		TH2I* dHist_Xi_cosGJ_wacc;

		//Cross section plots
		TH2F* dHist_Xi_Egamma;
		TH2F* dHist_Xi_Egamma_acc;
		TH2F* dHist_Xi_Egamma_wacc;
		TH2F* dHist_Xi_t;
		TH2F* dHist_Xi_t_acc;
		TH2F* dHist_Xi_t_wacc;
		TH3F* dHist_Xi_Egamma_t;
		TH3F* dHist_Xi_Egamma_t_acc;
		TH3F* dHist_Xi_Egamma_t_wacc;
		TH3F* dHist_Xi_Egamma_t_063;
		TH3F* dHist_Xi_Egamma_t_063_acc;
		TH3F* dHist_Xi_Egamma_t_063_wacc;
		TH3F* dHist_Xi_Egamma_t_064;
		TH3F* dHist_Xi_Egamma_t_064_acc;
		TH3F* dHist_Xi_Egamma_t_064_wacc;
		TH3F* dHist_Xi_Egamma_t_065;
		TH3F* dHist_Xi_Egamma_t_065_acc;
		TH3F* dHist_Xi_Egamma_t_065_wacc;
		TH3F* dHist_Xi_Egamma_ChiSq_063;
		TH3F* dHist_Xi_Egamma_ChiSq_063_wacc;
		TH3F* dHist_Xi_Egamma_ChiSq_064;
		TH3F* dHist_Xi_Egamma_ChiSq_064_wacc;
		TH3F* dHist_Xi_Egamma_ChiSq_065;
		TH3F* dHist_Xi_Egamma_ChiSq_065_wacc;
		TH2F* dHist_Xi_t_Truth;		
		TH1I* dHist_XiMass024;
		TH1I* dHist_XiMass029;
		TH1I* dHist_XiMass034;
		TH1I* dHist_XiMass039;
		TH1I* dHist_XiMass044;
		TH1I* dHist_XiMass049;
		TH1I* dHist_XiMass054;
		TH1I* dHist_XiMass059;
		TH1I* dHist_XiMass064;
		TH1I* dHist_XiMass069;
		TH1I* dHist_XiMass074;
		TH1I* dHist_XiMass079;
		TH1I* dHist_XiMass084;
		TH1I* dHist_XiMass089;
		TH1I* dHist_XiMass094;
		TH1I* dHist_XiMass099;
		TH1I* dHist_XiMass104;
		TH1I* dHist_XiMass109;
		TH1I* dHist_XiMass114;
		TH1I* dHist_XiMass024_wacc;
		TH1I* dHist_XiMass029_wacc;
		TH1I* dHist_XiMass034_wacc;
		TH1I* dHist_XiMass039_wacc;
		TH1I* dHist_XiMass044_wacc;
		TH1I* dHist_XiMass049_wacc;
		TH1I* dHist_XiMass054_wacc;
		TH1I* dHist_XiMass059_wacc;
		TH1I* dHist_XiMass064_wacc;
		TH1I* dHist_XiMass069_wacc;
		TH1I* dHist_XiMass074_wacc;
		TH1I* dHist_XiMass079_wacc;
		TH1I* dHist_XiMass084_wacc;
		TH1I* dHist_XiMass089_wacc;
		TH1I* dHist_XiMass094_wacc;
		TH1I* dHist_XiMass099_wacc;
		TH1I* dHist_XiMass104_wacc;
		TH1I* dHist_XiMass109_wacc;
		TH1I* dHist_XiMass114_wacc;
		TH2F* dHist_Xi_t_064;
		TH2F* dHist_Xi_t_064_wacc;
		TH2F* dHist_Xi_t_069;
		TH2F* dHist_Xi_t_069_wacc;
		TH2F* dHist_Xi_t_074;
		TH2F* dHist_Xi_t_074_wacc;
		TH2F* dHist_Xi_t_079;
		TH2F* dHist_Xi_t_079_wacc;
		TH2F* dHist_Xi_t_084;
		TH2F* dHist_Xi_t_084_wacc;
		TH2F* dHist_Xi_t_089;
		TH2F* dHist_Xi_t_089_wacc;
		TH2F* dHist_Xi_t_094;
		TH2F* dHist_Xi_t_094_wacc;
		TH2F* dHist_Xi_t_099;
		TH2F* dHist_Xi_t_099_wacc;
		TH2F* dHist_Xi_t_104;
		TH2F* dHist_Xi_t_104_wacc;
		TH2F* dHist_Xi_t_109;
		TH2F* dHist_Xi_t_109_wacc;
		TH2F* dHist_Xi_t_114;
		TH2F* dHist_Xi_t_114_wacc;

		//Intermediate hyperon
		TH1I* dHist_KlowpXim;
		TH1I* dHist_KlowpXim_Truth;
		TH1I* dHist_KlowpXim_wacc;
		TH2I* dHist_Klowp_pvstheta;
		TH2I* dHist_Khighp_pvstheta;
		TH2I* dHist_Klowp_pvstheta_wacc;
		TH2I* dHist_Khighp_pvstheta_wacc;

		//Angular distributions
		TH1I* dHist_XiMass_KinFit_Selected;
		TH3I* dHist_K_pThetaPhi_Measured;
		TH3I* dHist_p_pThetaPhi_Measured;
		TH3I* dHist_pi_pThetaPhi_Measured;
		TH3I* dHist_K_pThetaPhi_Measured_wacc;
		TH3I* dHist_p_pThetaPhi_Measured_wacc;
		TH3I* dHist_pi_pThetaPhi_Measured_wacc;					
		TH2I* dHist_K_pEgamma_Measured;
		TH2I* dHist_p_pEgamma_Measured;
		TH2I* dHist_pi_pEgamma_Measured;
		TH2I* dHist_K_pEgamma_Measured_wacc;
		TH2I* dHist_p_pEgamma_Measured_wacc;
		TH2I* dHist_pi_pEgamma_Measured_wacc;
		TH2I* dHist_K_pt_Measured;
		TH2I* dHist_p_pt_Measured;
		TH2I* dHist_pi_pt_Measured;
		TH2I* dHist_K_pt_Measured_wacc;
		TH2I* dHist_p_pt_Measured_wacc;
		TH2I* dHist_pi_pt_Measured_wacc;
		TH2I* dHist_K_pTheta_Measured;
		TH2I* dHist_p_pTheta_Measured;
		TH2I* dHist_p_pTheta_KinFit;
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
		TH1I* dHist_XiMass_KinFit_Selected_wacc;	
		TH1I* dHist_MMKK_Measured_wacc;
		TH1I* dHist_MMKK_KinFit_wacc;
		TH2I* dHist_K_pTheta_Measured_wacc;
		TH2I* dHist_p_pTheta_Measured_wacc;
		TH2I* dHist_p_pTheta_KinFit_wacc;
		TH2I* dHist_K_pTheta_KinFit_wacc;
		TH2I* dHist_K_ptTheta_Measured_wacc;
		TH2I* dHist_K_ptTheta_KinFit_wacc;
		TH1I* dHist_XiMass_kTheta15to35_Measured_wacc;
		TH1I* dHist_XiMass_kTheta15to35_KinFit_wacc;
		TH2I* dHist_pi_pTheta_Measured_wacc;
		TH2I* dHist_pi_pTheta_KinFit_wacc;
		TH2I* dHist_pi_ptTheta_Measured_wacc;
		TH2I* dHist_pi_ptTheta_KinFit_wacc;
		TH1I* dHist_XiMass_piTheta15to35_Measured_wacc;
		TH1I* dHist_XiMass_piTheta15to35_KinFit_wacc;
		TH1I* dHist_XiMass_MM_piTheta15to35_Measured_wacc;
		TH1I* dHist_XiMass_MM_piTheta15to35_KinFit_wacc;
		TH1I* dHist_XiMass_MM_kTheta15to35_Measured_wacc;
		TH1I* dHist_XiMass_MM_kTheta15to35_KinFit_wacc;
		

	ClassDef(DSelector_kpkpxim, 0);
};

void DSelector_kpkpxim::Get_ComboWrappers(void)
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

#endif // DSelector_kpkpxim_h
