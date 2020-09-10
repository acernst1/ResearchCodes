#ifndef DSelector_kpkpkmlamb_h
#define DSelector_kpkpkmlamb_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"
#include "TH3F.h"

class DSelector_kpkpkmlamb : public DSelector
{
	public:

		DSelector_kpkpkmlamb(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_kpkpkmlamb(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dKPlus1Wrapper;
		DChargedTrackHypothesis* dKPlus2Wrapper;
		DChargedTrackHypothesis* dKMinusWrapper;

		//Step 1
		DParticleComboStep* dStep1Wrapper;
		DKinematicData* dDecayingLambdaWrapper;
		DChargedTrackHypothesis* dPiMinusWrapper;
		DChargedTrackHypothesis* dProtonWrapper;

		// DEFINE YOUR HISTOGRAMS HERE
		// EXAMPLES:
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_BeamEnergy;
		TH1I* dHist_BeamBunch;
		TH1I* dHist_ChiSq;
		TH2I* dHist_ChiSqXi;
		TH1I* dHist_ChiSq_wacc;
		TH2I* dHist_ChiSqXi_wacc;
		TH1I* dHist_XiMass_Measured;	
		TH1I* dHist_XiMass_KinFit;
		TH1I* dHist_XiMass_Measured_acc;	
		TH1I* dHist_XiMass_KinFit_acc;
		TH1I* dHist_KKMassless_Measured;	
		TH1I* dHist_KKMassless_KinFit;
		TH1I* dHist_KKMassmore_Measured;	
		TH1I* dHist_KKMassmore_KinFit;
		TH2I* dHist_K_pTheta_Measured;
		TH2I* dHist_K_pTheta_Measured_acc;
		TH1I* dHist_LambdaSigma;
		TH1I* dHist_LambdaSigma_wacc;
		TH3F* dHist_XiMass_ChiSq_LambdaSigma;
		TH3F* dHist_XiMass_ChiSq_LambdaSigma_wacc;
		TH1F* dHist_KKMass_Measured;
		TH1F* dHist_KKMass_Measured_wacc;
		TH1F* dHist_KKMass_KinFit;
		TH1F* dHist_KKMass_KinFit_wacc;
		TH2F* dHist_KKLambdaMass_KinFit;
		TH2F* dHist_KKLambdaMass_KinFit_wacc;
		TH2F* dHist_KKLambdaMass_Measured;
		TH2F* dHist_KKLambdaMass_Measured_wacc;

	/****EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - MAIN TREE ****/

	ClassDef(DSelector_kpkpkmlamb, 0);
};

void DSelector_kpkpkmlamb::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dKPlus1Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
	dKPlus2Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
	dKMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(2));

	//Step 1
	dStep1Wrapper = dComboWrapper->Get_ParticleComboStep(1);
	dDecayingLambdaWrapper = dStep1Wrapper->Get_InitialParticle();
	dPiMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep1Wrapper->Get_FinalParticle(0));
	dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep1Wrapper->Get_FinalParticle(1));
}

#endif // DSelector_kpkpkmlamb_h
