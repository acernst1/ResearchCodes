# Research
Main codes for dissertation

## DSelectors
The DSelector is a Hall D specific form of a TSelector in Root. The DSelectors can only be used for specific specified TTrees. To run a DSelector in root:
> root -l -b my_file.root\
> [0] .x $ROOT_ANALYSIS_HOME/scripts/Load_DSelector.C\
> [1] Name_Tree->Process("DSelector_name.C+")

The cross section code (xsec.C) is run by using the driver code (Driver.C). The input files for xsec are listed in Driver. 



