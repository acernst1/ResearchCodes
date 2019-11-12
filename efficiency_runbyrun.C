#include "RooArgList.h"
#include "RooBreitWigner.h"
#include <math.h>
#include "TMath.h"
#include "RooPlot.h"

double getbincontent(TH1F* AccH, int bin);
double getbinerror(TH1F* AccH, int bin);
double loc_i;
double getbincontent(TH1F* hist, int bin) {  return hist->GetBinContent(bin);}
double getbinerror(TH1F* AccH, int bin){  return AccH->GetBinError(bin);}
char bin[100];
char mcworkspace[100];
char mccanvas[100];
char mcplotname[100];
char mcaccplotname[100];
char accplotname[100];
char mcplot[100];
char effplot[100];
char effnumbers[100];
char effcountnumbers[100];
char mcFilePath[100];
char thrownFilePath[100];
char thrown_canvas[100];
char thrown_plot[100];

void efficiency_runbyrun()
{
    int numRuns=347; 
    double minVal=6.4;
    double maxVal=11.4;
    double tagged=1.0;
    double tagged_err=0.0;
    double efficiency[numRuns];
    double eff_err[numRuns];
    double efficiency_count[numRuns];
    double eff_count_err[numRuns];

    int Runs[] = {30274, 30276, 30277, 30279, 30280, 30281, 30282, 30283, 30284, 30285, 30286, 30298, 30299, 30300, 30320, 30321, 30322, 30323, 30324, 30326, 30327, 30329, 30330, 30331, 30332, 30343, 30344, 30345, 30346, 30347, 30348, 30349, 30350, 30351, 30352, 30355, 30361, 30380, 30381, 30383, 30384, 30385, 30386, 30387, 30388, 30389, 30390, 30401, 30402, 30403, 30404, 30405, 30406, 30407, 30408, 30409, 30410, 30411, 30420, 30421, 30422, 30424, 30428, 30429, 30431, 30432, 30433, 30434, 30436, 30437, 30441, 30442, 30446, 30447, 30448, 30449, 30450, 30451, 30452, 30453, 30454, 30455, 30459, 30460, 30461, 30462, 30463, 30464, 30465, 30466, 30467, 30468, 30469, 30470, 30471, 30473, 30474, 30477, 30480, 30481, 30482, 30484, 30485, 30486, 30487, 30488, 30489, 30490, 30493, 30494, 30495, 30496, 30497, 30499, 30567, 30568, 30570, 30571, 30575, 30577, 30578, 30579, 30580, 30581, 30582, 30586, 30587, 30589, 30590, 30591, 30592, 30593, 30595, 30596, 30597, 30598, 30600, 30602, 30607, 30608, 30610, 30611, 30612, 30614, 30616, 30618, 30620, 30621, 30622, 30623, 30624, 30625, 30626, 30627, 30629, 30630, 30632, 30633, 30634, 30635, 30636, 30637, 30638, 30639, 30641, 30642, 30643, 30648, 30649, 30650, 30651, 30652, 30653, 30654, 30655, 30656, 30657, 30658, 30659, 30660, 30666, 30667, 30668, 30672, 30673, 30674, 30675, 30676, 30677, 30678, 30679, 30680, 30682, 30684, 30686, 30687, 30688, 30690, 30693, 30694, 30695, 30696, 30697, 30698, 30699, 30701, 30730, 30731, 30732, 30733, 30734, 30735, 30736, 30737, 30738, 30739, 30740, 30741, 30742, 30743, 30744, 30745, 30749, 30754, 30769, 30770, 30778, 30779, 30780, 30783, 30784, 30785, 30787, 30788, 30796, 30797, 30800, 30801, 30802, 30803, 30804, 30805, 30807, 30808, 30809, 30810, 30811, 30812, 30813, 30815, 30816, 30818, 30821, 30822, 30823, 30824, 30826, 30827, 30829, 30830, 30833, 30834, 30835, 30836, 30838, 30839, 30840, 30841, 30842, 30843, 30844, 30847, 30848, 30855, 30856, 30857, 30858, 30859, 30888, 30889, 30890, 30891, 30893, 30895, 30896, 30898, 30899, 30900, 30902, 30903, 30920, 30923, 30924, 30926, 30927, 30928, 30929, 30930, 30947, 30951, 30952, 30953, 30954, 30955, 30956, 30957, 30958, 30959, 30961, 30962, 30963, 30964, 30965, 30966, 30980, 30981, 30982, 30992, 30993, 30994, 30995, 30996, 30998, 30999, 31000, 31001, 31002, 31003, 31004, 31005, 31018, 31023, 31029, 31031, 31032, 31034, 31036, 31046, 31049, 31050, 31051, 31052, 31053, 31054, 31055, 31056, 31057};

    double BeamCurrent [] = {161.146, 144.092, 167.456, 144.176, 121.668, 97.5908, 61.2577, 81.5232, 111.376, 126.375, 63.1527, 84.0278, 106.627, 139.835, 175.002, 145.243, 143.578, 128.515, 131.08, 138.762, 143.839, 154.825, 147.471, 138.791, 129.413, 93.4207, 95.0209, 89.2617, 95.663, 88.5487, 92.8048, 85.1121, 79.3894, 128.732, 127.449, 88.876, 94.2243, 83.1491, 96.5838, 97.3287, 82.5422, 59.6603, 90.3194, 73.8722, 111.744, 110.259, 131.407, 127.281, 114.935, 139.161, 133.99, 178.597, 149.485, 119.008, 88.2123, 86.1776, 87.9864, 28.2027, 90.0756, 75.6181, 84.5132, 48.3097, 76.6002, 89.2185, 84.3355, 90.0826, 90.6284, 80.1312, 110.567, 134.463, 89.7259, 80.1385, 98.2015, 92.6868, 89.7461, 95.9849, 89.5135, 86.017, 92.0476, 95.6104, 92.1564, 124.178, 133.847, 84.1886, 80.187, 95.3343, 76.4566, 70.6919, 91.568, 72.0427, 90.2384, 81.0191, 76.0658, 86.114, 128.749, 85.325, 89.2338, 77.4406, 75.7113, 73.8614, 90.5839, 82.4384, 83.678, 89.0807, 77.3202, 89.0919, 136.257, 89.433, 74.437, 84.1491, 71.2112, 90.0844, 94.285, 80.716, 80.5275, 94.4144, 91.0318, 89.0211, 130.405, 86.6611, 94.1035, 82.3432, 75.5243, 91.9592, 91.1294, 70.8148, 83.1057, 91.5719, 92.2206, 80.8259, 88.9862, 127.466, 85.9929, 96.716, 91.5769, 88.1417, 83.7157, 72.2266, 99.6714, 82.4363, 87.3304, 93.8794, 98.0325, 76.1966, 96.3908, 136.257, 87.3994, 69.4781, 84.6397, 91.0795, 80.9365, 39.7587, 79.3053, 67.973, 44.5317, 88.4644, 91.2255, 86.4487, 134.133, 143.149, 92.1445, 92.5084, 66.0393, 51.2191, 79.9848, 56.9053, 53.0177, 90.2472, 84.7995, 83.4953, 86.2604, 135.847, 86.1785, 87.6779, 73.6212, 71.6859, 74.0851, 78.6595, 83.7255, 84.8426, 66.5054, 123.511, 87.4615, 90.3584, 91.2045, 88.2953, 98.4514, 96.6802, 88.2923, 85.843, 93.5602, 83.5744, 141.124, 92.9308, 92.6247, 66.1934, 87.9183, 88.796, 83.2505, 93.7751, 43.8686, 72.0823, 94.0047, 106.435, 135.358, 94.5842, 86.6793, 92.7815, 97.1315, 95.991, 77.93, 93.0886, 75.8608, 93.3158, 87.0214, 140.47, 86.0149, 84.412, 95.5016, 87.7485, 93.6191, 83.4973, 91.2652, 86.5119, 144.36, 97.9077, 93.9433, 76.1718, 80.9273, 67.2127, 77.4039, 58.272, 68.591, 130.21, 130.938, 131.051, 150.545, 144.053, 144.946, 111.578, 139.927, 140.42, 134.559, 205.115, 139.9, 49.5313, 126.487, 121.406, 137.353, 134.257, 137.698, 132.979, 134.2, 187.671, 116.075, 123.658, 136.249, 132.752, 142.475, 149.694, 133.77, 118.998, 130.327, 136.525, 121.283, 210.282, 75.8367, 131.169, 119.834, 110.375, 131.438, 103.489, 134.57, 138.839, 127.272, 214.131, 119.64, 94.4738, 174.533, 138.831, 126.818, 139.08, 144.588, 125.765, 137.445, 126.64, 144.168, 195.672, 126.22, 81.8974, 116.301, 136.411, 129.049, 129.76, 111.417, 116.359, 106.665, 161.379, 185.243, 138.164, 136.454, 141.714, 141.161, 141.585, 100.011, 139.14, 135.71, 195.136, 131.983, 141.104, 147.995, 129.329, 139.035, 131.745, 41.9749, 37.8416, 41.3421, 185.062, 97.4545, 138.56, 143.818, 145.751, 95.0268, 129.99, 133.913, 143.555, 140.699, 137.993, 87.4412, 192.159, 128.997, 191.855, 135.731, 137.087, 145.181, 108.202, 187.698, 36.4829, 101.844, 38.4964, 39.2494, 67.7582, 88.7107, 78.6925, 84.9878, 90.853, 85.5629
};
    double BeamOnCurrent [] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 150.471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100.148, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100.256, 99.7962, 100.371, 99.8841, 99.8273, 100.403, 150.023, 150.075, 100.279, 100.322, 100.028, 100.05, 99.1054, 100.397, 100.872, 99.7646, 100.305, 100.305, 98.1984, 150.128, 99.6279, 100.371, 100.275, 99.4128, 99.6275, 100.547, 99.6263, 99.8868, 99.9428, 99.8277, 100.385, 149.799, 100.697, 100.907, 99.7697, 98.6977, 99.8401, 100.494, 100.956, 100.769, 99.7691, 100.796, 100.651, 150.073, 100.107, 101.508, 98.993, 100.815, 101.304, 99.2801, 99.2221, 100.344, 99.6927, 102.004, 101.401, 99.5033, 150.076, 99.8506, 100.98, 101.523, 100.337, 99.5051, 98.5634, 99.6714, 100.128, 100.187, 100.086, 100.466, 100.105, 99.1319, 150.014, 99.8204, 100.259, 100.594, 100.044, 99.8852, 100.307, 100.158, 100.134, 99.3108, 100.254, 100.384, 100.246, 149.92, 150.027, 100.236, 100.119, 100.068, 100.422, 100.231, 100.67, 99.9533, 105.694, 103.996, 100.091, 100.13, 149.991, 100.273, 100.311, 99.9103, 100.074, 100.081, 100.193, 100.365, 100.266, 100.389, 149.689, 100.001, 99.8502, 99.9304, 99.8999, 99.7271, 100.231, 99.7504, 100.143, 100.084, 99.9974, 149.952, 100.098, 100.143, 100.183, 99.9118, 100.192, 100.147, 100.255, 100.137, 100.198, 99.7778, 149.92, 150.002, 100.055, 99.9076, 100.028, 100.175, 99.9069, 99.9283, 100.08, 99.2139, 99.8504, 99.7261, 149.976, 100.106, 100.084, 100.256, 100.243, 100.083, 100.256, 100.054, 99.8763, 150.202, 100.11, 99.8715, 100.304, 99.9553, 100.054, 99.1677, 99.8004, 99.7958, 149.999, 149.641, 149.583, 150.545, 150.044, 149.883, 148.742, 149.736, 149.249, 149.77, 225.289, 150.573, 149.913, 149.978, 149.874, 149.829, 149.892, 150.091, 149.854, 149.942, 224.878, 149.527, 150.04, 145.207, 149.423, 147.089, 149.694, 149.852, 150.044, 149.664, 149.587, 149.246, 224.867, 149.363, 149.952, 148.057, 146.96, 150.402, 146.418, 148.406, 150.108, 149.788, 225.035, 148.759, 150.356, 219.501, 148.338, 147.869, 149.47, 149.51, 148.713, 149.289, 148.434, 149.125, 223.99, 148.724, 148.956, 148.263, 149.06, 149.133, 148.865, 149.018, 149.337, 148.842, 220.104, 256.15, 148.723, 149.626, 149.393, 149.714, 149.838, 147.458, 149.944, 149.796, 223.49, 149.657, 149.661, 149.497, 149.194, 148.972, 149.317, 47.1824, 47.0223, 48.365, 215.293, 145.646, 149.538, 148.421, 149.276, 143.498, 148.705, 148.243, 148.895, 149.68, 148.642, 145.681, 214.213, 197.062, 224.882, 149.147, 150.124, 149.286, 149.499, 215.377, 49.4067, 193.166, 96.4465, 99.449, 100.553, 99.9645, 99.9775, 100.104, 100.033, 100.015
};

    gStyle->SetOptStat(0);
    TCanvas * eff_canvas = new TCanvas("eff_canvas", "eff_canvas",1600,1200);
    TH1F * eff_runs = new TH1F("eff_runs", "Efficiency; Run Number; Efficiency (%)",numRuns,Runs[0],Runs[numRuns-1]); 
    TH1F * eff_count_runs = new TH1F("eff_count_runs", "Efficiency; Run Number; Efficiency (%)",numRuns,Runs[0],Runs[numRuns-1]);

    eff_runs->SetMarkerColor(kBlue);
    eff_runs->SetMarkerStyle(21);
    eff_runs->SetLabelSize(0.035,"xy");
    eff_runs->SetLabelOffset(0.001,"xy");
    eff_runs->GetYaxis()->SetRangeUser(0,3);
    eff_runs->SetTitle("MC Efficiency by Run Number; Run Number; Efficiency (%)");

    eff_count_runs->SetMarkerColor(kRed);
    eff_count_runs->SetMarkerStyle(21);
    eff_count_runs->SetLabelSize(0.035,"xy");
    eff_count_runs->SetLabelOffset(0.001,"xy");
    eff_count_runs->SetTitle("MC Efficiency by Run Number; Run Number; Efficiency (%)");

    auto legend = new TLegend(0.1,0.7,0.3,0.9);
    legend->AddEntry(eff_runs,"fit method");
    legend->AddEntry(eff_count_runs,"counting method");

    TCanvas * bc_canvas = new TCanvas("bc_canvas", "bc_canvas",1600,1200);
    TH1F * bc = new TH1F("bc", "Beam Current; Run Number;  Beam Current (nA)",numRuns,Runs[0],Runs[numRuns-1]); 
    TH1F * boc = new TH1F("boc", "Beam on Current; Run Number; Beam Current (nA)",numRuns,Runs[0],Runs[numRuns-1]);
    bc->GetYaxis()->SetRangeUser(0,250);
    bc->SetMarkerColor(kBlue);
    boc->SetMarkerColor(kRed);
    bc->SetMarkerStyle(21);
    boc->SetMarkerStyle(21);
    bc->SetLabelSize(0.035,"xy");
    boc->SetLabelSize(0.035,"xy");
    bc->SetLabelOffset(0.001,"xy");
    boc->SetLabelOffset(0.001,"xy");

    auto legend02 = new TLegend(0.1,0.7,0.3,0.9);
    legend02->AddEntry(bc,"Beam Current");
    legend02->AddEntry(boc,"Beam On Current");

    for(int i=0; i<numRuns; i++)
	{
    int run = Runs[i];
    sprintf(mcFilePath, "requestedMC/kpkpxim__B4_M23_genr8_%06d.root", run);
    sprintf(thrownFilePath, "requestedMC/thrown/tree_thrown_genr8_%06d.root", run);
    sprintf(thrown_canvas,"thrown_canvas_%06d",run);
    sprintf(thrown_plot, "thrown_%06d.png", run);
    sprintf(mccanvas,"Xi_canvas_mc_%06d",run);
    sprintf(mcworkspace,"wmc%06d",run);
    sprintf(mcplotname,"XiMass_KinFit");
    sprintf(mcaccplotname,"XiMass_KinFit_acc");
    sprintf(accplotname,"XiMassKinFit%06dacc",run);
    sprintf(mcplot,"mcfitforeff_%06d.png", run);

    TCanvas * thrwn_canvas = new TCanvas(thrown_canvas,thrown_canvas,800,600);

    TFile* mcfile = TFile::Open(mcFilePath);
    TFile* thrownfile = TFile::Open(thrownFilePath);

    thrwn_canvas->cd();
    thrownfile->cd(); 
    TTree* thrownT=(TTree*) gDirectory->Get("Thrown_Tree");
    TH1F* thrown_hist=new TH1F("thrown_hist","thrown_hist",1,minVal,maxVal);
    thrownT->Draw("ThrownBeam__P4->E()>>thrown_hist");
    thrwn_canvas->Print(thrown_plot);
    tagged=getbincontent(thrown_hist,1);
    tagged_err=getbinerror(thrown_hist,1); 

    TH1F * XiMassKinFit = (TH1F*)mcfile->Get(mcplotname);
    XiMassKinFit->Sumw2();
    TH1F * XiMassKinFit_acc = (TH1F*)mcfile->Get(mcaccplotname);
    XiMassKinFit_acc->Sumw2();
    TH1F *mass_mc_hist = (TH1F *) XiMassKinFit->Clone(accplotname);
    mass_mc_hist->Add(XiMassKinFit_acc,-0.5);

    RooWorkspace* wmc = new RooWorkspace(mcworkspace);
    TCanvas * Xi_mc_canvas = new TCanvas(mccanvas, mccanvas,800,600);
    RooRealVar mcmass("mcmass", "mcmass", 1.2, 1.5);
    RooDataHist *mc = new RooDataHist("mc", "MC of mass", mcmass, mass_mc_hist);
    mass_mc_hist->Print();
    wmc->import(RooArgSet(mcmass));
    wmc->factory("Gaussian::gausmc(mcmass,meanmc[1.32,1.31,1.33],sigmamc[0.005,0.001,0.01])");
    wmc->factory("SUM::mcmodel(nsigmc[50,0,1e5]*gausmc)");
    wmc->pdf("mcmodel")->fitTo(*mc,RooFit::Range(1.31,1.335),RooFit::Minos(1));
    RooPlot* mcmassframe = mcmass.frame(RooFit::Title("Lambda pi^{-} Invariant Mass KinFit"));
    mcmassframe->SetMaximum(1000);
    mcmassframe->SetXTitle("#Lambda#pi^{-} mass");
    mc->plotOn(mcmassframe) ;
    wmc->pdf("mcmodel")->paramOn(mcmassframe);
    wmc->pdf("mcmodel")->plotOn(mcmassframe);
    wmc->pdf("gausmc")->plotOn(mcmassframe, RooFit::LineStyle(kDotted),
 	RooFit::Normalization(wmc->var("nsigmc")->getVal(), RooAbsReal::NumEvent));
    double_t mc_sig_events = wmc->var("nsigmc")->getVal();
    double_t mc_sig_events_err = wmc->var("nsigmc")->getError();
    mcmassframe->Draw();
    Xi_mc_canvas->Print(mcplot);

    double mc_sig_events_count= getbincontent(mass_mc_hist, 43)+getbincontent(mass_mc_hist, 44)+getbincontent(mass_mc_hist, 45)+getbincontent(mass_mc_hist, 46)+getbincontent(mass_mc_hist, 47)+getbincontent(mass_mc_hist, 48);
    double mc_sig_events_count_err= sqrt(pow(getbinerror(mass_mc_hist,43),2)+pow(getbinerror(mass_mc_hist, 44),2)+pow(getbinerror(mass_mc_hist, 45),2)+pow(getbinerror(mass_mc_hist, 46),2)+pow(getbinerror(mass_mc_hist, 47),2)+pow(getbinerror(mass_mc_hist, 48),2));

    efficiency[i]= 100.*mc_sig_events / tagged; 
    eff_err[i] = efficiency[i]*sqrt(pow(mc_sig_events_err/mc_sig_events,2)+pow(tagged_err/tagged,2));

    efficiency_count[i]= 100.*mc_sig_events_count / tagged; 
    eff_count_err[i] = efficiency_count[i]*sqrt(pow(mc_sig_events_count_err/mc_sig_events_count,2)+pow(tagged_err/tagged,2));

    cout << "~~~~~~~~~fit~~" << mc_sig_events << " " << tagged << " " << efficiency[i] << " " << eff_err[i] << endl;
    cout << "~~~~~~~~~count~~" << mc_sig_events_count << " " << tagged << " " << efficiency_count[i] << " " << eff_count_err[i] << endl;

    eff_canvas->cd();
    eff_runs->SetBinContent(i+1, efficiency[i]);
    eff_runs->SetBinError(i+1,eff_err[i]);
    eff_runs->Draw("PE1");
    eff_count_runs->SetBinContent(i+1, efficiency_count[i]);
    eff_count_runs->SetBinError(i+1,eff_count_err[i]);
    eff_count_runs->Draw("SAME");
    legend->Draw();
    eff_canvas->Update();
    sprintf(effplot,"efficiency_runbyrun.png");
    eff_canvas->Print(effplot);

    bc_canvas->cd();
    bc->SetBinContent(i+1,BeamCurrent[i]);
    boc->SetBinContent(i+1,BeamOnCurrent[i]);
    bc->SetBinError(i+1,0);
    boc->SetBinError(i+1,0);
    bc->Draw("PE1");
    boc->Draw("PE1,SAME");
    legend02->Draw();
    bc_canvas->Update();
    bc_canvas->Print("beam_current_runbyrun.png");


   }
sprintf(effnumbers,"eff_runbyrun.C");
eff_runs->SaveAs(effnumbers);
sprintf(effcountnumbers,"eff_count_runbyrun.C");
eff_runs->SaveAs(effcountnumbers);
}

