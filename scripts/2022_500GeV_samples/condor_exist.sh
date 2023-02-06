#!/bin/bash

path=$PWD
#eL: 00015902/000/ , 00015903/000/ , 00015908/000/
#eR: 00015905/000/ , 00015906/000/

for prod in "eR_pL" #"eL_pR"
do
    if ((prod == "eL_pR" ))
    then
	for fprod in "00015902" "00015903" "00015908"
	do
	    folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
	    cd $folder_name
	    echo $folder_name
	    echo $fprod
	    
	    FILES=*
	    
	    i=0
	    for f in $FILES
	    do
		name="00"$i
		if [ $i -gt 9 ]; then
		    name="0"$i
		fi
		
		if [ $i -gt 99 ]; then
		    name=$i
		fi
		if [ -f ${path}/${prod}_${name}.root ];
		then
		    echo "Skip "${name}
		else
		    cp ${path}/test_default.xml ${path}/test_${prod}_${name}.xml
		    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/test_${prod}_${name}.xml
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${name}.xml
		    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${name}.xml
		    sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${name}.xml
		    
		    cp ${path}/run_default.sh ${path}/run_${prod}_${name}.sh
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sh
		    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sh
		    cp ${path}/run_default.sub ${path}/run_${prod}_${name}.sub
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sub
		    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sub
		    
		    echo "Submit --- > " ${name}   
		    cd -
		    condor_submit run_${prod}_${name}.sub
		    #sleep 0.1s 
		    cd -
		fi    
		#rm ${path}/run_${prod}_${name}.sub
		#rm ${path}/run_${prod}_${name}.sh
		i=$((i+1))
	    done
	    cd -
	done
    fi
    if ((prod == "eR_pL" ))
    then
        for fprod in "00015905" "00015906"
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
            cd $folder_name
            echo $folder_name
            echo $fprod

            FILES=*

            i=0
            for f in $FILES
            do
                name="00"$i
                if [ $i -gt 9 ]; then
                    name="0"$i
                fi

                if [ $i -gt 99 ]; then
                    name=$i
                fi
                if [ -f ${path}/${prod}_${name}.root ];
                then
                    echo "Skip "${name}
                else
                    cp ${path}/test_default.xml ${path}/test_${prod}_${name}.xml
                    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/test_${prod}_${name}.xml
                    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${name}.xml
                    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${name}.xml
                    sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${name}.xml

                    cp ${path}/run_default.sh ${path}/run_${prod}_${name}.sh
                    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sh
                    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sh
                    cp ${path}/run_default.sub ${path}/run_${prod}_${name}.sub
                    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${name}.sub
                    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${name}.sub

                    echo "Submit --- > " ${name}
                    cd -
                    condor_submit run_${prod}_${name}.sub
                    #sleep 0.1s                                                                                                                                                                          
                    cd -
                fi
                #rm ${path}/run_${prod}_${name}.sub                                                                                                                                                      
                #rm ${path}/run_${prod}_${name}.sh                                                                                                                                                       
                i=$((i+1))
            done
            cd -
        done
    fi
done


