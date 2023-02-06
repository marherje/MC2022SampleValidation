mkdir output/
for pol in eL_pR eR_pL
do
    mkdir output/${pol}/
    for gamma in 0 #50 100
    do
	mkdir output/${pol}/${gamma}/
	for erre in 100 #50 75 125 150
	do
	    mkdir output/${pol}/${gamma}/${erre}/   
	    for k in 50 #10 30 40 60 80 90 100 120 130 140 150
	    do
		mkdir output/${pol}/${gamma}/${erre}/${k}/
		for cuts in {0..9}
		do
		    #cuts=5
		    echo $cuts
		    root -l test_selection_new.cc\($gamma,$erre,\"$pol\",$cuts,$k\) > log_sel_bkg_${k}_eL_genkt_restorer_cuts${cuts}
		    mv log_sel* output/${pol}/${gamma}/${erre}/${k}/
		    mv selection_cuts${cuts}_qqbar* output/${pol}/${gamma}/${erre}/${k}/
		    if [ $pol == eL_pR ]
		    then
			cp output/${pol}/${gamma}/${erre}/${k}/selection_cuts${cuts}_qqbar* output/selection_cuts${cuts}_2f_hadronic_sample_eL_pR_Kgamma${k}_500GeV.root
		    else
			cp output/${pol}/${gamma}/${erre}/${k}/selection_cuts${cuts}_qqbar* output/selection_cuts${cuts}_2f_hadronic_sample_eR_pL_Kgamma${k}_500GeV.root	
		    fi	
		done
	    done
	done
    done
done
