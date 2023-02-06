#!/bin/sh

mkdir output
root -l -q DQChecks.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/15162_0_eL_pR.root\",\"test\",35\) 
mv *root output/250GeV_eL_pR.root
root -l -q DQChecks.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eR_pL/15165_0_eR_pL.root\",\"test\",35\)
mv *root output/250GeV_eR_pL.root
root -l -q DQChecks.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eL_pR_500GeV.root\",\"test\",50\)
mv *root output/500GeV_eL_pR_old.root
root -l -q DQChecks.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/eR_pL_500GeV.root\",\"test\",50\)
mv *root output/500GeV_eR_pL_old.root
root -l -q DQChecks.cc\(\"../../../500GeV_NewNTuples2022/eL_pR_500GeV_NewSamples.root\",\"test\",50\)
mv *root output/500GeV_eL_pR_new.root
root -l -q DQChecks.cc\(\"../../../500GeV_NewNTuples2022/eR_pL_500GeV_NewSamples.root\",\"test\",50\)
mv *root output/500GeV_eR_pL_new.root


#mv *root DQplots/.
