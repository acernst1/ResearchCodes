# Xi- Cross Section

Within are the codes used to determine the production cross section for Xi- determined from the reaction gamma p -> K+ K+ Xi- -> K+ K+ pi- Lambda -> K+ K+ pi- pi- p. The results at the conclusion of membership within the collaboration are summarized in *DocDB 4595* as presented at the Physics Working Group Meeting on July 21st, 2020.
>https://halldweb.jlab.org/doc-private/DocDB/ShowDocument?docid=4595

This work used the following reconstruction and analysis versions: 
- 2017-01: reconstruction version 03, analysis launch 20
- 2018-01: reconstruction version 02, analysis launch 03
- 2018-08: reconstruction version 02, analysis launch 02
- 2018-08 Low energy: reconstruction version 02, analysis launch 05

Summary of the selection criteria:
- default analysis launch selection
- P4 and vertex kinematic fit
- mass constaint on Lambda but not XiM
- chi squared/ndf cut of 3.5 

## Codes in this repository:
### DSelector_kpkpxim.\* 
Runs over the data from the analysis launch (or Monte Carlo files) and produces all the plots required for further analysis. 

### Driver_\*.C
Driver script with options for the files needs to produce the cross sections and with some limited options such as for the binning of the cross section. 

### xsec_diff.C
Code, which is run using the Driver_xsec_diff_\*.C, that takes the histograms from the DSelector outputs and computes/plots the corresponding differential production cross section, total production cross section, and a variety of other plots. 

### plot_kinematics.C
Code that plots the various kinematic distributions from the DSelector output. Focuses on plotting data vs Monte Carlo distributions. 
