#ifndef DSelector_thrown_kpkpxim_h
#define DSelector_thrown_kpkpxim_h

#include <iostream>

#include "DSelector/DSelector.h"

#include "TH1I.h"
#include "TH2I.h"
#include "TH2F.h"

class DSelector_thrown_kpkpxim : public DSelector
{
	public:

		DSelector_thrown_kpkpxim(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_thrown_kpkpxim(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

		//Histograms
		TH2F* dHist_Egamma_t;
		TH2F* dHist_Egamma_t_acc;
		TH2F* dHist_Egamma_t_063;
		TH2F* dHist_Egamma_t_063_acc;
		TH2F* dHist_Egamma_t_064;
		TH2F* dHist_Egamma_t_064_acc;
		TH2F* dHist_Egamma_t_065;
		TH2F* dHist_Egamma_t_065_acc;
		TH2F* dHist_KPlus1vsKPlus2_p;
		TH2F* dHist_KPlus1vsKPlus2_theta;
		TH2F* dHist_KPlus1_pTheta;
		TH2F* dHist_KPlus2_pTheta;

	ClassDef(DSelector_thrown_kpkpxim, 0);
};

#endif // DSelector_thrown_kpkpxim_h
