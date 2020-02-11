#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

char filename[500];
char thrownfilename[500];

void plot_tslope_mass_width(){
int trials[][3] = {{0,18,6},{0,18,8},{0,18,10},{0,20,2},{0,20,4},{0,20,6},{0,20,8},{0,20,10},{0,22,2},{0,22,4},{0,22,6},{0,22,8},{0,22,10},{0,24,2},{0,24,4},{0,24,6},{0,24,8},{0,24,10},{0,26,2},{0,26,4},{0,26,6},{0,26,8},{0,26,10},{0,28,2},{0,28,4},{0,28,6},{0,28,8},{0,28,10},{7,18,2},{7,18,4},{7,18,6},{7,18,8},{7,18,10},{7,20,2},{7,20,4},{7,20,6},{7,20,8},{7,20,10},{7,22,2},{7,22,4},{7,22,6},{7,22,8},{7,22,10},{7,24,2},{7,24,4},{7,24,6},{7,24,8},{7,24,10},{7,26,2},{7,26,4},{7,26,6},{7,26,8},{7,26,10},{7,28,2},{7,28,4},{7,28,6},{7,28,8},{7,28,10},{14,18,2},{14,18,4},{14,18,6},{14,18,8},{14,18,10},{14,20,2},{14,20,4},{14,20,6},{14,20,8},{14,20,10},{14,22,2},{14,22,4},{14,22,6},{14,22,8},{14,22,10},{21,18,2},{35,28,8},{35,28,10}};


for( int i=0; i< sizeof(trials)/sizeof(trials[0]);i++){
	sprintf(filename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	sprintf(thrownfilename, "/cache/halld/home/acernst/MC/2018-08_ANAver02/tslope_tests/temp/thrown_kpkpxim__B4_M23_genr8_kpkpxim_2018-08_ANAver02_tslope%02d_mass%02d_width%02d.root",trials[i][0],trials[i][1],trials[i][2]);	
	TFile * MCfile = TFile::Open(filename);
	TFile * Thrownfile = TFile::Open(thrownfilename);
	}
}
