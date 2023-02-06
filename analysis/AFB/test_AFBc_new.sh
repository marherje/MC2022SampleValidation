
process=$1
pol=$2
folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/"${process}"_"${pol}"/"
local=$PWD


for method in 0 1 2
do
    for dedx in 2 3 4
    do
	counter=0
	
	for file in ${folder}/*
	do
	    echo $file $counter
	    name="00"$counter
	    if [ $counter -gt 9 ]; then
		name="0"$counter
	    fi
	    
	    if [ $counter -gt 99 ]; then
		name=$counter
	    fi
	    
	    cat > ${local}/steer/afc${dedx}_method${method}_${process}_${pol}_${name}.sh <<EOF
source ${local}/../init_ilcsoft.sh
root -l ${local}/test_AFBc1.cc\(\"${file}\",\"${process}\",\"${pol}\",${counter},35,${method},${dedx}\) > ${local}/output/log_AFBc_method${method}_${process}_${pol}_${name}_${dedx}
mv AFBc${dedx}_method${method}_${process}_${pol}_file_${name}_250GeV.root ${local}/output/.
EOF
	    
	    cat > ${local}/steer/afc${dedx}_method${method}_${process}_${pol}_${name}.sub <<EOF
# Unix submit description file
# kt_xNAMEfile.sub -- simple Marlin job
executable              = ${local}/steer/afc${dedx}_method${method}_${process}_${pol}_${name}.sh
log                     = ${local}/log/afc${dedx}_method${method}_${process}_${pol}_${name}.log
output                  = ${local}/log/outfile_afc${dedx}_method${method}_${process}_${pol}_${name}.txt
error                   = ${local}/log/errors_afc${dedx}_method${method}_${process}_${pol}_${name}.txt
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
queue 1
EOF
      	    
	    if [ -f ${local}/output/AFBc${dedx}_method${method}_${process}_${pol}_file_${name}_250GeV.root ];
	    then
		echo "Skip method${method}_${process}_${pol}_${name}_${dedx}"
	    else	
		condor_submit ${local}/steer/afc${dedx}_method${method}_${process}_${pol}_${name}.sub
	    fi
	    
	    counter=$((counter+1))
	done
    done
done



