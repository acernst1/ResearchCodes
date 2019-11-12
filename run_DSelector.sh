#!/bin/bash -f

#directory_list=$(ls ../trees/tree_kpkpxim__B4_M23_genr8_05*.root | cut -c "38","39","40","41","42" | head -1)
directory_list=$(ls ../trees/tree_kpkpxim__B4_M23_genr8_05*.root | cut -c "38","39","40","41","42" )
echo $directory_list

# Get Number of files
total_num_files=0
for directory in ${directory_list[*]}; do
	total_num_files=$(($total_num_files + 1))
done

echo You have $total_num_files files to process

counter=0
# Loop Over run numbers
for directory in ${directory_list[*]}; do
	counter=$(($counter + 1))
	echo
	echo You have processed $counter / $total_num_files files ...
	echo
	root -l -b "Driver_MC.C(${directory})"
	mv kpkpxim__B4_M23_sept19.root kpkpxim__B4_M23_2018-08_ANAver02_${directory}.root
done


