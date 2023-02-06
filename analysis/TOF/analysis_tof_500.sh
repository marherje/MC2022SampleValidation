#!/bin/sh

mkdir output
# file,outputname,ignoreoverlay true or false,min momentum ,quark pdg

#250 with overlay, without, quark c and b
for overlay in true false
do
    root -l -q analysis_tof.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/15162_0_eL_pR.root\",\"250GeV_eL_pR\",${overlay}\) 
    mv *root output/.
    root -l -q analysis_tof.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eR_pL/15165_0_eR_pL.root\",\"250GeV_eR_pL\",${overlay}\) 
    mv *root output/.
    root -l -q analysis_tof.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eL_pR_500GeV.root\",\"500GeV_eL_pR_old\",${overlay}\)
    mv *root output/.
    root -l -q analysis_tof.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eR_pL_500GeV.root\",\"500GeV_eR_pL_old\",${overlay}\)
    mv *root output/.
    root -l -q analysis_tof.cc\(\"../../../500GeV_NewNTuples2022/eL_pR_500GeV_NewSamples.root\",\"500GeV_eL_pR_new\",${overlay}\)
    mv *root output/.
    root -l -q analysis_tof.cc\(\"../../../500GeV_NewNTuples2022/eR_pL_500GeV_NewSamples.root\",\"500GeV_eR_pL_new\",${overlay}\)
    mv *root output/.
done
#mv *root DQplots/.
