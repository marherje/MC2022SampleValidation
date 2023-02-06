#!/bin/sh

mkdir output
# file,outputname,ignoreoverlay true or false,min momentum ,quark pdg

#250 with overlay, without, quark c and b
for overlay in true false
do
    for secondary in true false
    do
	for mom in 0 1 2
	do
	    for quark in 4 5
	    do
		#root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/15162_0_eL_pR.root\",\"250GeV_eL_pR\",${overlay},0,${quark}\) 
		#mv *root output/250GeV_IO_${overlay}_quark${quark}_eL_pR.root
		#root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eR_pL/15165_0_eR_pL.root\",\"250GeV_eR_pL\",${overlay},0,${quark}\) 
		#mv *root output/250GeV_IO_${overlay}_quark${quark}_eR_pL.root
		#root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eL_pR_500GeV.root\",\"500GeV_eL_pR_old\",${overlay},0,${quark}\)
		#mv *root output/500GeV_IO_${overlay}_quark${quark}_eL_pR_old.root
		#root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eR_pL_500GeV.root\",\"500GeV_eR_pL_old\",${overlay},0,${quark}\)
		#mv *root output/500GeV_IO_${overlay}_quark${quark}_eR_pL_old.root
		root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/eL_pR_500GeV_NewSamples.root\",\"500GeV_eL_pR_new\",${secondary},${overlay},${mom},${quark}\)
		mv *root output/500GeV_sectrack_${secondary}_IO_${overlay}_mommin_${mom}_quark${quark}_eL_pR_new.root
		root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/eR_pL_500GeV_NewSamples.root\",\"500GeV_eR_pL_new\",${secondary},${overlay},${mom},${quark}\)
	    mv *root output/500GeV_sectrack_${secondary}_IO_${overlay}_mommin_${mom}_quark${quark}_eR_pL_new.root
	    done
	done
    done
done
#mv *root DQplots/.
