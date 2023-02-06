mkdir results/
for pol in eL_pR eR_pL
do
    for gamma in 0 #50 100
    do
	for erre in 100 #50 75 125 150
	do  
	    for k in 50 #10 20 30 40 50 60 70 80 90 100 110 120 140 150 
	    do
		for cuts in {0..9}
		do
		    #cuts=5
		    echo $cuts
		    root -l test_jettag_new.cc\($gamma,$erre,\"$pol\",$cuts,$k\) > log_sel_bkg_${k}_eL_genkt_restorer_cuts${cuts}
		    mv log_sel* results/.
		    mv jettag_cuts${cuts}_2f_hadronic* results/.	
		done
	    done
	done
    done
done
