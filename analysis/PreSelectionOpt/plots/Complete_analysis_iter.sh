for pol in eL_pR eR_pL
do
    for cut in {0..7}
    do
	for k in 50 #90
	do
	    root -l -q analysis500GeV.cc\($cut,\"$pol\",\"$k\"\)
	done		 
    done
done
