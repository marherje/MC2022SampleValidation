#include "DQPlots.h"

void DQPlots_Comparison(TString pol, TString mode) {


  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetTitleY(0.8);

  gStyle->SetMarkerSize(0.05);
  TGaxis::SetMaxDigits(3);
  
  TString folder="./";
  TString names[9];
  names[0]="_uds";
  names[1]="_c";
  names[2]="_b";
  names[3]="_uds_rad";
  names[4]="_c_rad";
  names[5]="_b_rad";
  names[6]="_rad";
  names[7]="_signal";
  names[8]="_all";
  
  TString file[3];
  int nfiles;

  if(mode=="250vs500old"){
    file[0]="../output/250GeV_"+pol+".root";
    file[1]="../output/500GeV_"+pol+"_old.root";
    nfiles=2;
  }
  else if(mode=="250vs500new"){
    file[0]="../output/250GeV_"+pol+".root";
    file[1]="../output/500GeV_"+pol+"_new.root";
    nfiles=2;
  }
  else if(mode=="500oldvs500new"){
    file[0]="../output/500GeV_"+pol+"_old.root";
    file[1]="../output/500GeV_"+pol+"_new.root";
    nfiles=2;
  }
  else if(mode=="250vs500oldvs500new"){
    file[0]="../output/250GeV_"+pol+".root";
    file[1]="../output/500GeV_"+pol+"_old.root";
    file[2]="../output/500GeV_"+pol+"_new.root";
    nfiles=3;
  }


  //file[0]="DQ_250GeV_250GeV_DBD_eL_norestorer.root";
  //file[0]="DQ_250GeV_250GeV_mc2020-15161_eL_lcfi_VVB1.17_norestorer.root";
  //  file[0]="../DQ_250GeV_15161.root";//DQ_250GeV_250GeV_mc2020-15162_eL_20210219.root";
  //file[1]="../DQ_250GeV_15162.root";//
  //file[0]="DQ_250GeV_250GeV_mc2020-15161_eL_norestorer.root";
    // file[1]="DQ_250GeV_250GeV_mc2020-15161_eL_norestorer2.root";
  //  file[2]="DQ_250GeV_250GeV_DBD_eL.root";
  //int nfiles=2;

    
  //NMC
  std::vector<TH1F *> histos_NMC;
  std::vector<TH1F *> histos_NMC_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_NMC.push_back(getHisto("MC",file[i],"QCDFSR_n"+names[j]));
      histos_NMC.push_back(getHisto("MC",file[i],"particle_n"+names[j]));
    }
    histos_NMC_all.push_back(getHisto("MC",file[i],"QCDFSR_n"+names[8]));
    histos_NMC_all.push_back(getHisto("MC",file[i],"particle_n"+names[8]));
  } 
  Compare_2Histos("NMC", histos_NMC, histos_NMC_all,nfiles);
  
  //Number of events:
  Float_t Signal1=getHisto("MC",file[0],"QCDFSR_n"+names[7])->GetEntries();
  Float_t Signal2=getHisto("MC",file[1],"QCDFSR_n"+names[7])->GetEntries();
  Float_t ISR1=getHisto("MC",file[0],"QCDFSR_n"+names[6])->GetEntries();
  Float_t ISR2=getHisto("MC",file[1],"QCDFSR_n"+names[6])->GetEntries();
  Float_t Ratio1=ISR1/Signal1;
  Float_t Ratio2=ISR2/Signal2;
  cout<<"Signal events type 1: "<<Signal1<<endl;
  cout<<"Signal events type 2: "<<Signal2<<endl;
  cout<<"ISR events type 1: "<<ISR1<<endl;
  cout<<"ISR events type 2: "<<ISR2<<endl;
  cout<<"Ratio 1: "<<Ratio1<<endl;
  cout<<"Ratio 2: "<<Ratio2<<endl;

  //-------

  

  //Nreco
  std::vector<TH1F *> histos_Nreco;
  std::vector<TH1F *> histos_Nreco_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_Nreco.push_back(getHisto("reco",file[i],"nvtx"+names[j]));
      histos_Nreco.push_back(getHistoRemove0("reco",file[i],"vtx_ntrack"+names[j]));
      //   else histos_Nreco.push_back(getHisto("reco",file[i],"vtx_ntrack"+names[j],"nprimtrack"+names[j]));
      histos_Nreco.push_back(getHisto("reco",file[i],"PFO_njet"+names[j]));
    }
    histos_Nreco_all.push_back(getHisto("reco",file[i],"nvtx"+names[8]));
    histos_Nreco_all.push_back(getHistoRemove0("reco",file[i],"vtx_ntrack"+names[8]));
    //if(newfile[i]==false) histos_Nreco.push_back(getHisto("reco",file[i],"vtx_ntrack"+names[6]));
    //else histos_Nreco.push_back(getHisto("reco",file[i],"vtx_ntrack"+names[6],"nprimtrack"+names[6]));
    histos_Nreco_all.push_back(getHisto("reco",file[i],"PFO_njet"+names[8]));
  } 
  Compare_3Histos("Nreco", histos_Nreco, histos_Nreco_all,nfiles);
    
  /*  
  //quark
  std::vector<TH1F *> histos_quark;
  std::vector<TH1F *> histos_quark_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_quark.push_back(getHisto("MC",file[i],"quark_phi"+names[j]));
      histos_quark.push_back(getHisto("MC",file[i],"quark_theta"+names[j]));
      histos_quark.push_back(getHisto("MC",file[i],"quark_mom"+names[j]));
    }
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_phi"+names[8]));
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_theta"+names[8]));
    histos_quark_all.push_back(getHisto("MC",file[i],"quark_mom"+names[8]));
  } 
  Compare_3Histos("quark", histos_quark, histos_quark_all,nfiles);
    
 //quark_afterps
  std::vector<TH1F *> histos_quark_afterps;
  std::vector<TH1F *> histos_quark_afterps_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_phi"+names[j]));
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_theta"+names[j]));
      histos_quark_afterps.push_back(getHisto("MC",file[i],"quark_afterps_mom"+names[j]));
    }
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_phi"+names[8]));
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_theta"+names[8]));
    histos_quark_afterps_all.push_back(getHisto("MC",file[i],"quark_afterps_mom"+names[8]));
  }
  Compare_3Histos("quark_afterps", histos_quark_afterps, histos_quark_afterps_all,nfiles);
  */
    
  //QCDFSR
  std::vector<TH1F *> histos_QCDFSR;
  std::vector<TH1F *> histos_QCDFSR_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_phi"+names[j]));
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_theta"+names[j]));
      histos_QCDFSR.push_back(getHisto("MC",file[i],"QCDFSR_mom"+names[j]));
    }
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_phi"+names[8]));
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_theta"+names[8]));
    histos_QCDFSR_all.push_back(getHisto("MC",file[i],"QCDFSR_mom"+names[8]));
  }
  Compare_3Histos("QCDFSR", histos_QCDFSR, histos_QCDFSR_all,nfiles);
  
  
  /*
  //ISR
  std::vector<TH1F *> histos_ISR;
  std::vector<TH1F *> histos_ISR_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_phi"+names[j]));
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_theta"+names[j]));
      histos_ISR.push_back(getHisto("MC",file[i],"ISR_mom"+names[j]));
    }
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_phi"+names[8]));
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_theta"+names[8]));
    histos_ISR_all.push_back(getHisto("MC",file[i],"ISR_mom"+names[8]));
  }
  Compare_3Histos("ISR", histos_ISR, histos_ISR_all,nfiles);
  
  
  //particle
  std::vector<TH1F *> histos_particle;
  std::vector<TH1F *> histos_particle_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_particle.push_back(getHisto("MC",file[i],"particle_phi"+names[j]));
      histos_particle.push_back(getHisto("MC",file[i],"particle_theta"+names[j]));
      histos_particle.push_back(getHisto("MC",file[i],"particle_mom"+names[j]));
    }
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_phi"+names[8]));
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_theta"+names[8]));
    histos_particle_all.push_back(getHisto("MC",file[i],"particle_mom"+names[8]));
  }
  Compare_3Histos("particle", histos_particle, histos_particle_all,nfiles);

  
  //PFO
  std::vector<TH1F *> histos_PFO;
  std::vector<TH1F *> histos_PFO_all;
  for(int i=0; i<nfiles; i++) {
    for(int j=0; j<6; j++) {
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_phi"+names[j]));
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_theta"+names[j]));
      histos_PFO.push_back(getHisto("reco",file[i],"PFO_mom"+names[j]));
    }
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_phi"+names[8]));
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_theta"+names[8]));
    histos_PFO_all.push_back(getHisto("reco",file[i],"PFO_mom"+names[8]));
  }
  Compare_3Histos("PFO", histos_PFO, histos_PFO_all,nfiles);
  Compare_3HistosEventNorm("PFO",histos_PFO_all, histos_quark_all,nfiles);
  
  
  
  //track
  std::vector<TH1F *> histos_track;
  std::vector<TH1F *> histos_track_all;
  std::vector<TH1F *> histos_track_sec;
  std::vector<TH1F *> histos_track_sec_all;

  for(int i=0; i<nfiles; i++) {
    TString tracktitle="primtrack_";
    TString tracktitle_sec="sectrack_";
    for(int j=0; j<6; j++) {
      histos_track.push_back(getHisto("reco",file[i],tracktitle+"phi"+names[j]));
      histos_track.push_back(getHisto("reco",file[i],tracktitle+"theta"+names[j]));
      histos_track.push_back(getHisto("reco",file[i],tracktitle+"mom"+names[j]));
      histos_track_sec.push_back(getHisto("reco",file[i],tracktitle_sec+"phi"+names[j]));
      histos_track_sec.push_back(getHisto("reco",file[i],tracktitle_sec+"theta"+names[j]));
      histos_track_sec.push_back(getHisto("reco",file[i],tracktitle_sec+"mom"+names[j]));
    }
    histos_track_all.push_back(getHisto("reco",file[i],tracktitle+"phi"+names[8]));
    histos_track_all.push_back(getHisto("reco",file[i],tracktitle+"theta"+names[8]));
    histos_track_all.push_back(getHisto("reco",file[i],tracktitle+"mom"+names[8]));
    histos_track_sec_all.push_back(getHisto("reco",file[i],tracktitle_sec+"phi"+names[8]));
    histos_track_sec_all.push_back(getHisto("reco",file[i],tracktitle_sec+"theta"+names[8]));
    histos_track_sec_all.push_back(getHisto("reco",file[i],tracktitle_sec+"mom"+names[8]));
  }
  Compare_3Histos("track_primary", histos_track, histos_track_all,nfiles);
  Compare_3HistosEventNorm("track_primary",histos_track_all, histos_quark_all,nfiles);
  Compare_3Histos("track_secondary", histos_track_sec, histos_track_sec_all,nfiles);
  Compare_3HistosEventNorm("track_secondary",histos_track_sec_all, histos_quark_all,nfiles);
  */

  /*
  //track d0/z0
  std::vector<TH1F *> histos_track_impact;
  std::vector<TH1F *> histos_track_impact_all;
  std::vector<TH1F *> histos_track_sec_impact;
  std::vector<TH1F *> histos_track_sec_impact_all;
  
  for(int i=0; i<nfiles; i++) {
    TString tracktitle="primtrack_";
    TString tracktitle_sec="sectrack_";
    for(int j=0; j<6; j++) {
      histos_track_impact.push_back(getHisto("reco",file[i],tracktitle+"d0"+names[j]));
      histos_track_impact.push_back(getHisto("reco",file[i],tracktitle+"z0"+names[j]));
      histos_track_sec_impact.push_back(getHisto("reco",file[i],tracktitle_sec+"d0"+names[j]));
      histos_track_sec_impact.push_back(getHisto("reco",file[i],tracktitle_sec+"z0"+names[j]));
    }
    histos_track_impact_all.push_back(getHisto("reco",file[i],tracktitle+"d0"+names[8]));
    histos_track_impact_all.push_back(getHisto("reco",file[i],tracktitle+"z0"+names[8]));
    histos_track_sec_impact_all.push_back(getHisto("reco",file[i],tracktitle_sec+"d0"+names[8]));
    histos_track_sec_impact_all.push_back(getHisto("reco",file[i],tracktitle_sec+"z0"+names[8]));
  }
  Compare_2Histos("track_impact_parameters", histos_track_impact, histos_track_impact_all,nfiles);
  Compare_2Histos("track_sec_impact_parameters", histos_track_sec_impact, histos_track_sec_impact_all,nfiles);
  */  
}
