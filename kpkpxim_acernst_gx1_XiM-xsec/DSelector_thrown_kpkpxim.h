#ifndef DSelector_thrown_kpkpxim_h
#define DSelector_thrown_kpkpxim_h

#include <iostream>
#include <fstream>

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

		//output files
		ofstream *myfile;
		Int_t count_event;
		Int_t count_KKXi;

		//Histograms
		TH2F* dHist_Egamma_t;
		TH2F* dHist_Egamma_t_063;
		TH2F* dHist_Egamma_t_064;
		TH1F* dHist_Egamma_064;
		TH2F* dHist_Egamma_t_065;
		TH2F* dHist_Egamma_t_064_upperTarget;
		TH2F* dHist_Egamma_t_064_lowerTarget;
		TH2F* dHist_KPlus1vsKPlus2_p;
		TH2F* dHist_KPlus1vsKPlus2_theta;
		TH2F* dHist_KPlus1_pTheta;
		TH2F* dHist_KPlus2_pTheta;
		TH1I* dHist_prodvert;

		TH2I* dHist_Klowp_phiTheta_YstarGJ;
		TH2I* dHist_Xi_phiTheta_YstarGJ;

		TH2I* dHist_Khighp_phiTheta_CM;
		TH2I* dHist_Khighp_phiTheta_Ystar;
		TH2I* dHist_Klowp_phiTheta_Ystar;
		TH1I* dHist_Ystar_p_Ystar;
		TH2I* dHist_Ystar_phiTheta_CM;

	ClassDef(DSelector_thrown_kpkpxim, 0);
};

#endif // DSelector_thrown_kpkpxim_h
