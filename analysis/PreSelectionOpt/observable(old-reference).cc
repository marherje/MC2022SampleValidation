#define observable_cxx
#include "observable.h"
#include "TPad.h"


void observable::Selection(int n_entries=-1, int selection_type=0, TString polarization="eL", float Kvcut=2500)
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data()),"RECREATE");
  MyFile->cd();
       
  bbbar_gen=0;
  bbbar_gen_radreturn=0;
  qqbar_gen=0;
  qqbar_gen_radreturn=0;
  ccbar_gen=0;
  ccbar_gen_radreturn=0;
  
  
  TH1F * h_cross_costheta = new TH1F("h_cross_costheta","h_cross_costheta",20,0,1);
  TH1F * h_cross_costheta_bb = new TH1F("h_cross_costheta_bb","h_cross_costheta_bb",20,0,1);
  TH1F * h_cross_costheta_qq = new TH1F("h_cross_costheta_qq","h_cross_costheta_qq",20,0,1);
  TH1F * h_cross_costheta_cc = new TH1F("h_cross_costheta_cc","h_cross_costheta_cc",20,0,1);
  TH1F * h_cross_costheta_radreturn = new TH1F("h_cross_costheta_radreturn","h_cross_costheta_radreturn",20,0,1);
  TH1F * h_cross_costheta_radreturn_bb = new TH1F("h_cross_costheta_radreturn_bb","h_cross_costheta_radreturn_bb",20,0,1);
  TH1F * h_cross_costheta_radreturn_qq = new TH1F("h_cross_costheta_radreturn_qq","h_cross_costheta_radreturn_qq",20,0,1);
  TH1F * h_cross_costheta_radreturn_cc = new TH1F("h_cross_costheta_radreturn_cc","h_cross_costheta_radreturn_cc",20,0,1);
  
  //costheta
  TH1F * h_costheta_bb = new TH1F("h_costheta_bb","h_costheta_bb",20,0,1);
  TH1F * h_costheta_qq = new TH1F("h_costheta_qq","h_costheta_qq",20,0,1);
  TH1F * h_costheta_cc = new TH1F("h_costheta_cc","h_costheta_cc",20,0,1);
  TH1F * h_costheta_radreturn = new TH1F("h_costheta_radreturn","h_costheta_radreturn",20,0,1);
  TH1F * h_costheta_radreturn_bb = new TH1F("h_costheta_radreturn_bb","h_costheta_radreturn_bb",20,0,1);
  TH1F * h_costheta_radreturn_qq = new TH1F("h_costheta_radreturn_qq","h_costheta_radreturn_qq",20,0,1);
  TH1F * h_costheta_radreturn_cc = new TH1F("h_costheta_radreturn_cc","h_costheta_radreturn_cc",20,0,1);
  
  TH1F * h_sintheta_bb = new TH1F("h_sintheta_bb","h_sintheta_bb",20,0,1);
  TH1F * h_sintheta_radreturn = new TH1F("h_sintheta_radreturn","h_sintheta_radreturn",20,0,1);
  TH1F * h_sintheta_qq = new TH1F("h_sintheta_qq","h_sintheta_qq",20,0,1);
  TH1F * h_sintheta_cc = new TH1F("h_sintheta_cc","h_sintheta_cc",20,0,1);
  
  //mass & momentum & angle
  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_mjj_cc = new TH1F("h_mjj_cc","h_mjj_cc",100,0,500);

  TH1F * h_egamma_bb = new TH1F("h_egamma_bb","h_egamma_bb",100,0,500);
  TH1F * h_egamma_radreturn = new TH1F("h_egamma_radreturn","h_egamma_radreturn",100,0,500);
  TH1F * h_egamma_qq = new TH1F("h_egamma_qq","h_egamma_qq",100,0,500);
  TH1F * h_egamma_cc = new TH1F("h_egamma_cc","h_egamma_cc",100,0,500);
  
  TH1F * h_costhetagamma_bb = new TH1F("h_costhetagamma_bb","h_costhetagamma_bb",100,-1,1);
  TH1F * h_costhetagamma_radreturn = new TH1F("h_costhetagamma_radreturn","h_costhetagamma_radreturn",100,-1,1);
  TH1F * h_costhetagamma_qq = new TH1F("h_costhetagamma_qq","h_costhetagamma_qq",100,-1,1);
  TH1F * h_costhetagamma_cc = new TH1F("h_costhetagamma_cc","h_costhetagamma_cc",100,-1,1);

  //
  TH2F * h_e_costheta_gamma_bb = new TH2F("h_e_costheta_gamma_bb","h_e_costheta_gamma_bb",80,-1,1,100,0,500);
  TH2F * h_e_costheta_gamma_radreturn = new TH2F("h_e_costheta_gamma_radreturn","h_e_costheta_gamma_radreturn",80,-1,1,100,0,500);
  TH2F * h_e_costheta_gamma_qq = new TH2F("h_e_costheta_gamma_qq","h_e_costheta_gamma_qq",80,-1,1,100,0,500);
  TH2F * h_e_costheta_gamma_cc = new TH2F("h_e_costheta_gamma_cc","h_e_costheta_gamma_cc",80,-1,1,100,0,500);

  // Parte nueva de adrian
  //------------------------
  TH2F * h_photon_likeness_bb = new TH2F("h_photon_likeness_bb","h_photon_likeness_bb",200,0,1,200,0,1);
  TH2F * h_photon_likeness_radreturn = new TH2F("h_photon_likeness_radreturn","h_photon_likeness_radreturn",200,0,1,200,0,1);
  TH2F * h_photon_likeness_qq = new TH2F("h_photon_likeness_qq","h_photon_likeness_qq",200,0,1,200,0,1);
  TH2F * h_photon_likeness_cc = new TH2F("h_photon_likeness_cc","h_photon_likeness_cc",200,0,1,200,0,1);

  TH2F * h_photon_npfos_bb = new TH2F("h_photon_npfos_bb","h_photon_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_radreturn = new TH2F("h_photon_npfos_radreturn","h_photon_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_qq = new TH2F("h_photon_npfos_qq","h_photon_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_cc = new TH2F("h_photon_npfos_cc","h_photon_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);
  
  TH2F * h_charge_likeness_bb = new TH2F("h_charge_likeness_bb","h_charge_likeness_bb",200,0,1,200,0,1);
  TH2F * h_charge_likeness_radreturn = new TH2F("h_charge_likeness_radreturn","h_charge_likeness_radreturn",200,0,1,200,0,1);
  TH2F * h_charge_likeness_qq = new TH2F("h_charge_likeness_qq","h_charge_likeness_qq",200,0,1,200,0,1);
  TH2F * h_charge_likeness_cc = new TH2F("h_charge_likeness_cc","h_charge_likeness_cc",200,0,1,200,0,1);

  
  TH2F * h_charge_npfos_qq = new TH2F("h_charge_npfos_qq","h_charge_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_cc = new TH2F("h_charge_npfos_cc","h_charge_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);

  TH2F * h_charge_npfos_bb = new TH2F("h_charge_npfos_bb","h_charge_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_radreturn = new TH2F("h_charge_npfos_radreturn","h_charge_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);
 
  TH2F * h_npfos_bb = new TH2F("h_npfos_bb","h_npfos_bb",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_radreturn = new TH2F("h_npfos_radreturn","h_npfos_radreturn",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_qq = new TH2F("h_npfos_qq","h_npfos_qq",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_cc = new TH2F("h_npfos_cc","h_npfos_cc",101,-0.5,100.5,101,-0.5,100.5);
 
  //------------------------
  
  TH2F * h_cos_costheta_gamma_bb = new TH2F("h_cos_costheta_gamma_bb","h_cos_costheta_gamma_bb",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_radreturn = new TH2F("h_cos_costheta_gamma_radreturn","h_cos_costheta_gamma_radreturn",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_qq = new TH2F("h_cos_costheta_gamma_qq","h_cos_costheta_gamma_qq",200,-1,1,200,-1,1);
  TH2F * h_cos_costheta_gamma_cc = new TH2F("h_cos_costheta_gamma_cc","h_cos_costheta_gamma_cc",200,-1,1,200,-1,1);

  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",100,0,500);
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",100,0,500);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",100,0,500);
  TH1F * h_mj1_mj2_cc = new TH1F("h_mj1_mj2_cc","h_mj1_mj2_cc",100,0,500);

  TH1F * h_mjFat_bb = new TH1F("h_mjFat_bb","h_mjFat_bb",100,0,500);
  TH1F * h_mjFat_radreturn = new TH1F("h_mjFat_radreturn","h_mjFat_radreturn",100,0,500);
  TH1F * h_mjFat_qq = new TH1F("h_mjFat_qq","h_mjFat_qq",100,0,500);
  TH1F * h_mjFat_cc = new TH1F("h_mjFat_cc","h_mjFat_cc",100,0,500);

  TH1F * h_mjThin_bb = new TH1F("h_mjThin_bb","h_mjThin_bb",100,0,500);
  TH1F * h_mjThin_radreturn = new TH1F("h_mjThin_radreturn","h_mjThin_radreturn",100,0,500);
  TH1F * h_mjThin_qq = new TH1F("h_mjThin_qq","h_mjThin_qq",100,0,500);
  TH1F * h_mjThin_cc = new TH1F("h_mjThin_cc","h_mjThin_cc",100,0,500);

  TH1F * h_angle_bb = new TH1F("h_angle_bb","h_angle_bb",1000,-7,7);
  TH1F * h_angle_radreturn = new TH1F("h_angle_radreturn","h_angle_radreturn",1000,-7,7);
  TH1F * h_angle_qq = new TH1F("h_angle_qq","h_angle_qq",1000,-7,7);
  TH1F * h_angle_cc = new TH1F("h_angle_cc","h_angle_cc",1000,-7,7);

  TH1F * h_pj1_pj2_bb = new TH1F("h_pj1_pj2_bb","h_pj1_pj2_bb",100,0,500);
  TH1F * h_pj1_pj2_radreturn = new TH1F("h_pj1_pj2_radreturn","h_pj1_pj2_radreturn",100,0,500);
  TH1F * h_pj1_pj2_qq = new TH1F("h_pj1_pj2_qq","h_pj1_pj2_qq",100,0,500);
  TH1F * h_pj1_pj2_cc = new TH1F("h_pj1_pj2_cc","h_pj1_pj2_cc",100,0,500);

  //jet algorithm variables
  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",100,0,500);
  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",100,0,500);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",100,0,500);
  TH1F * h_d23_cc = new TH1F("h_d23_cc","h_d23_cc",100,0,500);

  TH1F * h_d12_bb = new TH1F("h_d12_bb","h_d12_bb",100,0,100000);
  TH1F * h_d12_radreturn = new TH1F("h_d12_radreturn","h_d12_radreturn",100,0,100000);
  TH1F * h_d12_qq = new TH1F("h_d12_qq","h_d12_qq",100,0,100000);
  TH1F * h_d12_cc = new TH1F("h_d12_cc","h_d12_cc",100,0,100000);

  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",400,0,0.25);
  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",400,0,0.25);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",400,0,0.25);
  TH1F * h_y23_cc = new TH1F("h_y23_cc","h_y23_cc",400,0,0.25);

  TH1F * h_y12_bb = new TH1F("h_y12_bb","h_y12_bb",100,0,1);
  TH1F * h_y12_radreturn = new TH1F("h_y12_radreturn","h_y12_radreturn",100,0,1);
  TH1F * h_y12_qq = new TH1F("h_y12_qq","h_y12_qq",100,0,1);
  TH1F * h_y12_cc = new TH1F("h_y12_cc","h_y12_cc",100,0,1);

  //EVENT SHAPE variables
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_oblateness_radreturn = new TH1F("h_oblateness_radreturn","h_oblateness_radreturn",100,0,0.8);
  TH1F * h_oblateness_qq = new TH1F("h_oblateness_qq","h_oblateness_qq",100,0,0.8);
  TH1F * h_oblateness_cc = new TH1F("h_oblateness_cc","h_oblateness_cc",100,0,0.8);

  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_radreturn = new TH1F("h_aplanarity_radreturn","h_aplanarity_radreturn",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_qq = new TH1F("h_aplanarity_qq","h_aplanarity_qq",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_cc = new TH1F("h_aplanarity_cc","h_aplanarity_cc",100,-0.4e-6,0.4e-6);

  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",2000,0,2);
  TH1F * h_sphericity_radreturn = new TH1F("h_sphericity_radreturn","h_sphericity_radreturn",2000,0,2);
  TH1F * h_sphericity_qq = new TH1F("h_sphericity_qq","h_sphericity_qq",2000,0,2);
  TH1F * h_sphericity_cc = new TH1F("h_sphericity_cc","h_sphericity_cc",2000,0,2);

  TH1F * h_acol_bb = new TH1F("h_acol_bb","h_acol_bb",1000,-4,4);
  TH1F * h_acol_radreturn = new TH1F("h_acol_radreturn","h_acol_radreturn",1000,-4,4);
  TH1F * h_acol_qq = new TH1F("h_acol_qq","h_acol_qq",1000,-4,4);
  TH1F * h_acol_cc = new TH1F("h_acol_cc","h_acol_cc",1000,-4,4);

  TH1F * h_sinacol_bb = new TH1F("h_sinacol_bb","h_sinacol_bb",200,0,2);
  TH1F * h_sinacol_radreturn = new TH1F("h_sinacol_radreturn","h_sinacol_radreturn",200,0,2);
  TH1F * h_sinacol_qq = new TH1F("h_sinacol_qq","h_sinacol_qq",200,0,2);
  TH1F * h_sinacol_cc = new TH1F("h_sinacol_cc","h_sinacol_cc",200,0,2);
  
  TH1F * h_K = new TH1F("h_K","h_K",2000,0,200);
  TH1F * h_K_bb = new TH1F("h_K_bb","h_K_bb",2000,0,200);
  TH1F * h_K_radreturn = new TH1F("h_K_radreturn","h_K_radreturn",2000,0,200);
  TH1F * h_K_qq = new TH1F("h_K_qq","h_K_qq",2000,0,200);
  TH1F * h_K_cc = new TH1F("h_K_cc","h_K_cc",2000,0,200);

  TH1F * h_K_parton_bb = new TH1F("h_K_parton_bb","h_K_parton_bb",2000,0,200);
  TH1F * h_K_parton_radreturn = new TH1F("h_K_parton_radreturn","h_K_parton_radreturn",2000,0,200);
  TH1F * h_K_parton_qq = new TH1F("h_K_parton_qq","h_K_parton_qq",2000,0,200);
  TH1F * h_K_parton_cc = new TH1F("h_K_parton_cc","h_K_parton_cc",2000,0,200);

  TH2F * h_K_parton_K_bb = new TH2F("h_K_parton_K_bb","h_K_parton_K_bb",200,0,200,200,0,200);
  TH2F * h_K_parton_K_radreturn = new TH2F("h_K_parton_K_radreturn","h_K_parton_K_radreturn",200,0,200,200,0,200);
  TH2F * h_K_parton_K_qq = new TH2F("h_K_parton_K_qq","h_K_parton_K_qq",200,0,200,200,0,200);
  TH2F * h_K_parton_K_cc = new TH2F("h_K_parton_K_cc","h_K_parton_K_cc",200,0,200,200,0,200);

  TH1F * h_K_res = new TH1F("h_K_res","h_K_res",4000,-200,200);
  TH2F * h_sphericity_cos_bb = new TH2F("h_sphericity_cos_bb","h_sphericity_cos_bb",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_radreturn = new TH2F("h_sphericity_cos_radreturn","h_sphericity_cos_radreturn",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_qq = new TH2F("h_sphericity_cos_qq","h_sphericity_cos_qq",40,-1,1,2000,0,2);
  TH2F * h_sphericity_cos_cc = new TH2F("h_sphericity_cos_cc","h_sphericity_cos_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_cos_bb = new TH2F("h_acol_cos_bb","h_acol_cos_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_radreturn = new TH2F("h_acol_cos_radreturn","h_acol_cos_radreturn",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_qq = new TH2F("h_acol_cos_qq","h_acol_cos_qq",40,-1,1,2000,0,2);
  TH2F * h_acol_cos_cc = new TH2F("h_acol_cos_cc","h_acol_cos_cc",40,-1,1,2000,0,2);

  TH2F * h_sphericity_sin_bb = new TH2F("h_sphericity_sin_bb","h_sphericity_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_radreturn = new TH2F("h_sphericity_sin_radreturn","h_sphericity_sin_radreturn",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_qq = new TH2F("h_sphericity_sin_qq","h_sphericity_sin_qq",40,-1,1,2000,0,2);
  TH2F * h_sphericity_sin_cc = new TH2F("h_sphericity_sin_cc","h_sphericity_sin_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_sin_bb = new TH2F("h_acol_sin_bb","h_acol_sin_bb",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_radreturn = new TH2F("h_acol_sin_radreturn","h_acol_sin_radreturn",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_qq = new TH2F("h_acol_sin_qq","h_acol_sin_qq",40,-1,1,2000,0,2);
  TH2F * h_acol_sin_cc = new TH2F("h_acol_sin_cc","h_acol_sin_cc",40,-1,1,2000,0,2);

  TH2F * h_acol_sphericity_bb = new TH2F("h_acol_sphericity_bb","h_acol_sphericity_bb",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_radreturn = new TH2F("h_acol_sphericity_radreturn","h_acol_sphericity_radreturn",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_qq = new TH2F("h_acol_sphericity_qq","h_acol_sphericity_qq",2000,0,2,2000,0,2);
  TH2F * h_acol_sphericity_cc = new TH2F("h_acol_sphericity_cc","h_acol_sphericity_cc",2000,0,2,2000,0,2);
         
  TH1F * h_thrust_bb = new TH1F("h_thrust_bb","h_thrust_bb",1000,0,1);
  TH1F * h_thrust_radreturn = new TH1F("h_thrust_radreturn","h_thrust_radreturn",1000,0,1);
  TH1F * h_thrust_qq = new TH1F("h_thrust_qq","h_thrust_qq",1000,0,1);
  TH1F * h_thrust_cc = new TH1F("h_thrust_cc","h_thrust_cc",1000,0,1);


  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();

  int bb_counter=0, radreturn_counter=0, qq_counter=0, cc_counter=0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;//sqrt(pow(mc_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;
    
    //-------------------
    //Kv parton
    double b0_p= sqrt(pow(mc_quark_px[0],2)+pow(mc_quark_py[0],2)+pow(mc_quark_pz[0],2));
    double b1_p= sqrt(pow(mc_quark_px[1],2)+pow(mc_quark_py[1],2)+pow(mc_quark_pz[1],2));
    float costheta_b0;
    std::vector<float> p_b0;
    p_b0.push_back(mc_quark_px[0]);
    p_b0.push_back(mc_quark_py[0]);
    p_b0.push_back(mc_quark_pz[0]);
    costheta_b0=fabs(GetCostheta(p_b0));
    float costheta_b1;
    std::vector<float> p_b1;
    p_b1.push_back(mc_quark_px[1]);
    p_b1.push_back(mc_quark_py[1]);
    p_b1.push_back(mc_quark_pz[1]);
    costheta_b1=fabs(GetCostheta(p_b1));
    TVector3 v0_p(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0]);
    TVector3 v1_p(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1]);
    float acol_p=GetSinacol(v0_p,v1_p);
    float Kv_p=250.*acol_p/(acol_p+sqrt(1-costheta_b0*costheta_b0)+sqrt(1-costheta_b1*costheta_b1));

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bbbar_gen++;
      bb_counter++;
    }
    if(gamma_e>Kvcut ) {
      radreturn_counter++;
      if(fabs(mc_quark_pdg[0])==5) bbbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])==4) ccbar_gen_radreturn++;
      if(fabs(mc_quark_pdg[0])<4) qqbar_gen_radreturn++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_counter++;
      ccbar_gen++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_counter++;
      qqbar_gen++;
    }


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));

    float costheta_bbbar;
    std::vector<float> p_bbar;
    p_bbar.push_back(jet_px[0]-jet_px[1]);
    p_bbar.push_back(jet_py[0]-jet_py[1]);
    p_bbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_bbbar=fabs(GetCostheta(p_bbar));

    float costheta_j0;
    std::vector<float> p_j0;
    p_j0.push_back(jet_px[0]);
    p_j0.push_back(jet_py[0]);
    p_j0.push_back(jet_pz[0]);
    costheta_j0=GetCostheta(p_j0);

    float costheta_j1;
    std::vector<float> p_j1;
    p_j1.push_back(jet_px[1]);
    p_j1.push_back(jet_py[1]);
    p_j1.push_back(jet_pz[1]);
    costheta_j1=GetCostheta(p_j1);


    TVector3 v0(jet_px[0],jet_py[0],jet_pz[0]);
    TVector3 v1(jet_px[1],jet_py[1],jet_pz[1]);
    float acol=GetSinacol(v0,v1);
    float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));


    //menos importante
    float thrust=principle_thrust_value;//GetThrust(v0,v1);
 
    double  E_total[2]={0};
    double  photonPFO_ratio[2]={0};

    double  photonjet_E[2]={0};
    double  photonjet_costheta[2];
    photonjet_costheta[0]=-2;
    photonjet_costheta[1]=-2;

   
    //---------------------
    //Radiative return cuts, photon INSIDE the detector
    double npfo[2]={0};
    double npfo_photon[2]={0};
    float costheta=-2;
    float energy=0;
    
    //  for(int ijet=0; ijet<2; ijet++) {
    float costheta_jet_0=0;
    float costheta_jet_1=0;
    std::vector<float> p_pfo_0;
    std::vector<float> p_pfo_1;
    float px_0=0, py_0=0, pz_0=0;
    float px_1=0, py_1=0, pz_1=0;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
      if(pfo_match[ipfo]<0) continue;
      if(pfo_E[ipfo]<1) continue;
  
      npfo[pfo_match[ipfo]]++;
    
      E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
      if( pfo_type[ipfo]==22  || fabs(pfo_type[ipfo])==2112 ) {
      
	npfo_photon[pfo_match[ipfo]]++;

	if(pfo_match[ipfo]==0) {
	  px_0+=pfo_px[ipfo];
	  py_0+=pfo_py[ipfo];
	  pz_0+=pfo_pz[ipfo];
	}
	if(pfo_match[ipfo]==1) {
	  px_1+=pfo_px[ipfo];
	  py_1+=pfo_py[ipfo];
	  pz_1+=pfo_pz[ipfo];
	}
	photonjet_E[pfo_match[ipfo]] += pfo_E[ipfo];
      }
    }//ipfo
  
    p_pfo_0.push_back(px_0);
    p_pfo_0.push_back(py_0);
    p_pfo_0.push_back(pz_0);
    float costheta_pfo_0=GetCostheta(p_pfo_0);
    costheta_jet_0= costheta_pfo_0;

    p_pfo_1.push_back(px_1);
    p_pfo_1.push_back(py_1);
    p_pfo_1.push_back(pz_1);
    float costheta_pfo_1=GetCostheta(p_pfo_1);
    costheta_jet_1= costheta_pfo_1;
  
  
    photonPFO_ratio[0]=photonjet_E[0]/E_total[0];
    photonPFO_ratio[1]=photonjet_E[1]/E_total[1];
    photonjet_costheta[0]=costheta_jet_0;
    photonjet_costheta[1]=costheta_jet_1;

 
   //-------------------
    // LOS CHARGE NPFOS

    double  chargePFO_ratio[2]={0};

    double  chargejet_E[2]={0};
    double  chargejet_costheta[2];
    chargejet_costheta[0]=-2;
    chargejet_costheta[1]=-2;
    
    // double npfo[2]={0};
    //double npfo_photon[2]={0};
    // float costheta=-2;
    //float energy=0;
    Int_t npfo_charge[2]={0};
    //  for(int ijet=0; ijet<2; ijet++) {
    //float costheta_jet_0=0;
    //float costheta_jet_1=0;
    //std::vector<float> p_pfo_0;
    //std::vector<float> p_pfo_1;
    //float px_0=0, py_0=0, pz_0=0;
    //float px_1=0, py_1=0, pz_1=0;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
      if(pfo_match[ipfo]<0) continue;
      if(pfo_E[ipfo]<1) continue;
  
      npfo[pfo_match[ipfo]]++;
    
      E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
      if( pfo_charge[ipfo] != 0  ) {
      
	npfo_charge[pfo_match[ipfo]]++;

	if(pfo_match[ipfo]==0) {
	  px_0+=pfo_px[ipfo];
	  py_0+=pfo_py[ipfo];
	  pz_0+=pfo_pz[ipfo];
	}
	if(pfo_match[ipfo]==1) {
	  px_1+=pfo_px[ipfo];
	  py_1+=pfo_py[ipfo];
	  pz_1+=pfo_pz[ipfo];
	}
	chargejet_E[pfo_match[ipfo]] += pfo_E[ipfo];
      }
    }//ipfo
  
  
    chargePFO_ratio[0]=chargejet_E[0]/E_total[0];
    chargePFO_ratio[1]=chargejet_E[1]/E_total[1];
    chargejet_costheta[0]=costheta_jet_0;
    chargejet_costheta[1]=costheta_jet_1;

    // HASTA AQUI LOS CHARGE NPFOS
     
    // parton level definitions
    if(gamma_e<Kvcut) h_cross_costheta->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) h_cross_costheta_bb->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) h_cross_costheta_cc->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) h_cross_costheta_qq->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==5 && gamma_e>Kvcut) h_cross_costheta_radreturn_bb->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])==4 && gamma_e>Kvcut) h_cross_costheta_radreturn_cc->Fill(costheta_bbbar);
    if(fabs(mc_quark_pdg[0])<4 && gamma_e>Kvcut) h_cross_costheta_radreturn_qq->Fill(costheta_bbbar);
    if(gamma_e>Kvcut) h_cross_costheta_radreturn->Fill(costheta_bbbar);



    //parte importante
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
	  
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {

      h_K_res->Fill(gamma_e-Kv);
      
      h_costheta_bb->Fill(costheta_bbbar);
      
      h_sintheta_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      h_mjj_bb->Fill(reco_bbmass);

      h_egamma_bb->Fill(photonjet_E[0]);
      h_egamma_bb->Fill(photonjet_E[1]);

      h_costhetagamma_bb->Fill(photonjet_costheta[0]);
      h_costhetagamma_bb->Fill(photonjet_costheta[1]);

      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_bb->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_bb->Fill(photonjet_costheta[1],photonjet_E[1]);

      h_photon_likeness_bb->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_photon_npfos_bb->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_bb->Fill(npfo[0],npfo[1]);

      h_charge_likeness_bb->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_charge_npfos_bb->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
    
      h_cos_costheta_gamma_bb->Fill(costheta_j0,photonjet_costheta[1]);
      h_cos_costheta_gamma_bb->Fill(costheta_j1,photonjet_costheta[1]);

      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_bb->Fill(reco_b1mass);
	h_mjThin_bb->Fill(reco_b2mass);
      } else {
	h_mjFat_bb->Fill(reco_b2mass);
	h_mjThin_bb->Fill(reco_b1mass);
      }
      h_pj1_pj2_bb->Fill(jet0_p+jet1_p);
      h_d23_bb->Fill(d23);
      h_d12_bb->Fill(d12);
      h_y23_bb->Fill(d23/pow(reco_bbmass,2));
      h_y12_bb->Fill(d12/pow(reco_bbmass,2));
      h_oblateness_bb->Fill(oblateness);
      h_aplanarity_bb->Fill(aplanarity);

      h_sphericity_bb->Fill(sphericity);
      h_sinacol_bb->Fill(acol);
      h_acol_bb->Fill(TMath::ASin(acol));
      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);
      h_sphericity_cos_bb->Fill(costheta_bbbar,sphericity);
      h_acol_cos_bb->Fill(costheta_bbbar,acol);
      h_sphericity_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_bb->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_bb->Fill(sphericity,acol);
      h_thrust_bb->Fill(thrust);
      
      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_bb->Fill(angle);
    }
    
    if( gamma_e>Kvcut ) {
      h_mjj_radreturn->Fill(reco_bbmass);

      h_egamma_radreturn->Fill(photonjet_E[0]);
      h_egamma_radreturn->Fill(photonjet_E[1]);

      h_costhetagamma_radreturn->Fill(photonjet_costheta[0]);
      h_costhetagamma_radreturn->Fill(photonjet_costheta[1]);

      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_radreturn->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_radreturn->Fill(photonjet_costheta[1],photonjet_E[1]);

      h_photon_likeness_radreturn->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_photon_npfos_radreturn->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_radreturn->Fill(npfo[0],npfo[1]);
      
      h_charge_likeness_radreturn->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_charge_npfos_radreturn->Fill(npfo_charge[0],npfo_charge[1]);
      
      
      // -------------------------

      h_cos_costheta_gamma_radreturn->Fill(costheta_j0,photonjet_costheta[1]);
      h_cos_costheta_gamma_radreturn->Fill(costheta_j1,photonjet_costheta[1]);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);
      
      h_costheta_radreturn->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])==5 ) h_costheta_radreturn_bb->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])==4 ) h_costheta_radreturn_cc->Fill(costheta_bbbar);
      if( fabs(mc_quark_pdg[0])<4 ) h_costheta_radreturn_qq->Fill(costheta_bbbar);

      //Rb/Rc calc.
 
       
      h_sintheta_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_radreturn->Fill(reco_b1mass);
	h_mjThin_radreturn->Fill(reco_b2mass);
      } else {
	h_mjFat_radreturn->Fill(reco_b2mass);
	h_mjThin_radreturn->Fill(reco_b1mass);
      }

      h_pj1_pj2_radreturn->Fill(jet0_p+jet1_p);
      h_d23_radreturn->Fill(d23);
      h_d12_radreturn->Fill(d12);
      h_y23_radreturn->Fill(d23/pow(reco_bbmass,2));
      h_y12_radreturn->Fill(d12/pow(reco_bbmass,2));
      h_oblateness_radreturn->Fill(oblateness);
      h_aplanarity_radreturn->Fill(aplanarity);

      h_sphericity_radreturn->Fill(sphericity);
      h_sinacol_radreturn->Fill(acol);
      h_acol_radreturn->Fill(TMath::ASin(acol));
      h_K_radreturn->Fill(Kv);
      h_K_parton_radreturn->Fill(gamma_e);
      h_K_parton_K_radreturn->Fill(gamma_e,Kv);
      h_sphericity_cos_radreturn->Fill(costheta_bbbar,sphericity);
      h_acol_cos_radreturn->Fill(costheta_bbbar,acol);
      h_sphericity_sin_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_radreturn->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_radreturn->Fill(sphericity,acol);
      h_thrust_radreturn->Fill(thrust);

      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_radreturn->Fill(angle);
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) {
      h_mjj_cc->Fill(reco_bbmass);

      h_egamma_cc->Fill(photonjet_E[0]);
      h_egamma_cc->Fill(photonjet_E[1]);

      h_costhetagamma_cc->Fill(photonjet_costheta[0]);
      h_costhetagamma_cc->Fill(photonjet_costheta[1]);
     

      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_cc->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_cc->Fill(photonjet_costheta[1],photonjet_E[1]);

      h_photon_likeness_cc->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_photon_npfos_cc->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_cc->Fill(npfo[0],npfo[1]);
      
      h_charge_likeness_cc->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_charge_npfos_cc->Fill(npfo_charge[0],npfo_charge[1]);

      
      // -------------------------
      h_cos_costheta_gamma_cc->Fill(costheta_j0,photonjet_costheta[1]);
      h_cos_costheta_gamma_cc->Fill(costheta_j1,photonjet_costheta[1]);
    
      h_mj1_mj2_cc->Fill(reco_b1mass+reco_b2mass);
      h_costheta_cc->Fill(costheta_bbbar);
      //Rb/Rc calc.

    
      h_sintheta_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));
      if(reco_b1mass>reco_b2mass) {
	h_mjFat_cc->Fill(reco_b1mass);
	h_mjThin_cc->Fill(reco_b2mass);
      } else {
	h_mjFat_cc->Fill(reco_b2mass);
	h_mjThin_cc->Fill(reco_b1mass);
      }
      h_pj1_pj2_cc->Fill(jet0_p+jet1_p);
      h_d23_cc->Fill(d23);
      h_d12_cc->Fill(d12);
      h_y23_cc->Fill(d23/pow(reco_bbmass,2));
      h_y12_cc->Fill(d12/pow(reco_bbmass,2));
      h_oblateness_cc->Fill(oblateness);
      h_aplanarity_cc->Fill(aplanarity);
      
      h_sphericity_cc->Fill(sphericity);
      h_sinacol_cc->Fill(acol);
      h_acol_cc->Fill(TMath::ASin(acol));
      h_K_cc->Fill(Kv);
      h_K_parton_cc->Fill(gamma_e);
      h_K_parton_K_cc->Fill(gamma_e,Kv);
      h_sphericity_cos_cc->Fill(costheta_bbbar,sphericity);
      h_acol_cos_cc->Fill(costheta_bbbar,acol);
      h_sphericity_sin_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_cc->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_cc->Fill(sphericity,acol);
      h_thrust_cc->Fill(thrust);
  
      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_cc->Fill(angle);      
    }
    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) {
      h_mjj_qq->Fill(reco_bbmass);

      h_egamma_qq->Fill(photonjet_E[0]);
      h_egamma_qq->Fill(photonjet_E[1]);

      h_costhetagamma_qq->Fill(photonjet_costheta[0]);
      h_costhetagamma_qq->Fill(photonjet_costheta[1]);

      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_qq->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_qq->Fill(photonjet_costheta[1],photonjet_E[1]);

      h_photon_likeness_qq->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_photon_npfos_qq->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_qq->Fill(npfo[0],npfo[1]);
      
      h_charge_likeness_qq->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_charge_npfos_qq->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
      h_cos_costheta_gamma_qq->Fill(costheta_j0,photonjet_costheta[1]);
      h_cos_costheta_gamma_qq->Fill(costheta_j1,photonjet_costheta[1]);
     
      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_costheta_qq->Fill(costheta_bbbar);
      //Rb/Rc calc.
    
      h_sintheta_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar));

      if(reco_b1mass>reco_b2mass) {
	h_mjFat_qq->Fill(reco_b1mass);
	h_mjThin_qq->Fill(reco_b2mass);
      } else {
	h_mjFat_qq->Fill(reco_b2mass);
	h_mjThin_qq->Fill(reco_b1mass);
      }
      h_pj1_pj2_qq->Fill(jet0_p+jet1_p);
      h_d23_qq->Fill(d23);
      h_d12_qq->Fill(d12);
      h_y23_qq->Fill(d23/pow(reco_bbmass,2));
      h_y12_qq->Fill(d12/pow(reco_bbmass,2));
      h_oblateness_qq->Fill(oblateness);
      h_aplanarity_qq->Fill(aplanarity);

      h_sphericity_qq->Fill(sphericity);
      h_sinacol_qq->Fill(acol);
      h_acol_qq->Fill(TMath::ASin(acol));
      h_K_qq->Fill(Kv);
      h_K_parton_qq->Fill(gamma_e);
      h_K_parton_K_qq->Fill(gamma_e,Kv);
      h_sphericity_cos_qq->Fill(costheta_bbbar,sphericity);
      h_acol_cos_qq->Fill(costheta_bbbar,acol);
      h_sphericity_sin_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),sphericity);
      h_acol_sin_qq->Fill(sqrt(1-costheta_bbbar*costheta_bbbar),acol);
      h_acol_sphericity_qq->Fill(sphericity,acol);
      h_thrust_qq->Fill(thrust);
         

      float angle=getAngle2Vec(jet_px[0],jet_py[0],jet_pz[0],jet_E[0],jet_px[1],jet_py[1],jet_pz[1],jet_E[1]);
      h_angle_qq->Fill(angle);      
    }
    
  }
  cout<<TString::Format("selection_%s_250GeV_%s.root",process.Data(),polarization.Data())<<endl;
  cout<<" Total generated events: bb cc qq bb(rad) cc(rad) qq(rad)" <<endl;
  cout<<"                     "<<bbbar_gen<<" "<<ccbar_gen<<" "<<qqbar_gen<<" "<<bbbar_gen_radreturn<<" "<<ccbar_gen_radreturn<<" "<<qqbar_gen_radreturn<<endl;
  //  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
  //cout<<" Total generated qqbar events: " << qq_counter<<endl;
  //cout<<" Total generated ccbar events: " << cc_counter<<endl;

  // save histograms
  h_mjj_bb->Write();
  h_mjj_qq->Write();
  h_mjj_cc->Write();
  h_mjj_radreturn->Write();

  h_costheta_bb->Write();
  h_costheta_qq->Write();
  h_costheta_cc->Write();
  h_costheta_radreturn->Write();
  h_costheta_radreturn_bb->Write();
  h_costheta_radreturn_cc->Write();
  h_costheta_radreturn_qq->Write();

  h_cross_costheta->Write();
  h_cross_costheta_bb->Write();
  h_cross_costheta_qq->Write();
  h_cross_costheta_cc->Write();
  h_cross_costheta_radreturn->Write();
  h_cross_costheta_radreturn_bb->Write();
  h_cross_costheta_radreturn_cc->Write();
  h_cross_costheta_radreturn_qq->Write();

  h_sintheta_bb->Write();
  h_sintheta_qq->Write();
  h_sintheta_cc->Write();
  h_sintheta_radreturn->Write();
  
  h_egamma_bb->Write();
  h_egamma_qq->Write();
  h_egamma_cc->Write();
  h_egamma_radreturn->Write();


  h_costhetagamma_bb->Write();
  h_costhetagamma_qq->Write();
  h_costhetagamma_cc->Write();
  h_costhetagamma_radreturn->Write();

 
  h_e_costheta_gamma_bb->Write();
  h_e_costheta_gamma_qq->Write();
  h_e_costheta_gamma_cc->Write();
  h_e_costheta_gamma_radreturn->Write();

  h_photon_likeness_bb->Write();
  h_photon_likeness_cc->Write();
  h_photon_likeness_qq->Write();
  h_photon_likeness_radreturn->Write();

  h_photon_npfos_bb->Write();
  h_photon_npfos_cc->Write();
  h_photon_npfos_qq->Write();
  h_photon_npfos_radreturn->Write();
  
  h_charge_likeness_bb->Write();
  h_charge_likeness_cc->Write();
  h_charge_likeness_qq->Write();
  h_charge_likeness_radreturn->Write();

  h_charge_npfos_bb->Write();
  h_charge_npfos_cc->Write();
  h_charge_npfos_qq->Write();
  h_charge_npfos_radreturn->Write();

  h_npfos_bb->Write();
  h_npfos_cc->Write();
  h_npfos_qq->Write();
  h_npfos_radreturn->Write();

  h_cos_costheta_gamma_bb->Write();
  h_cos_costheta_gamma_qq->Write();
  h_cos_costheta_gamma_cc->Write();
  h_cos_costheta_gamma_radreturn->Write();
  
  h_mj1_mj2_bb->Write();
  h_mj1_mj2_qq->Write();
  h_mj1_mj2_cc->Write();
  h_mj1_mj2_radreturn->Write();

  h_mjFat_bb->Write();
  h_mjFat_qq->Write();
  h_mjFat_cc->Write();
  h_mjFat_radreturn->Write();

  h_mjThin_bb->Write();
  h_mjThin_qq->Write();
  h_mjThin_cc->Write();
  h_mjThin_radreturn->Write();

  h_angle_bb->Write();
  h_angle_qq->Write();
  h_angle_cc->Write();
  h_angle_radreturn->Write();

  h_pj1_pj2_bb->Write();
  h_pj1_pj2_qq->Write();
  h_pj1_pj2_cc->Write();
  h_pj1_pj2_radreturn->Write();

  h_d23_bb->Write();
  h_d23_qq->Write();
  h_d23_cc->Write();
  h_d23_radreturn->Write();

  h_d12_bb->Write();
  h_d12_qq->Write();
  h_d12_cc->Write();
  h_d12_radreturn->Write();

  h_y23_bb->Write();
  h_y23_qq->Write();
  h_y23_cc->Write();
  h_y23_radreturn->Write();

  h_y12_bb->Write();
  h_y12_qq->Write();
  h_y12_cc->Write();
  h_y12_radreturn->Write();

  h_oblateness_bb->Write();
  h_oblateness_qq->Write();
  h_oblateness_cc->Write();
  h_oblateness_radreturn->Write();

  h_aplanarity_bb->Write();
  h_aplanarity_qq->Write();
  h_aplanarity_cc->Write();
  h_aplanarity_radreturn->Write();

  h_sphericity_bb->Write();
  h_sphericity_qq->Write();
  h_sphericity_cc->Write();
  h_sphericity_radreturn->Write();

  h_sphericity_cos_bb->Write();
  h_sphericity_cos_qq->Write();
  h_sphericity_cos_cc->Write();
  h_sphericity_cos_radreturn->Write();

  h_sphericity_sin_bb->Write();
  h_sphericity_sin_qq->Write();
  h_sphericity_sin_cc->Write();
  h_sphericity_sin_radreturn->Write();
  
  h_acol_bb->Write();
  h_acol_qq->Write();
  h_acol_cc->Write();
  h_acol_radreturn->Write();

  h_sinacol_bb->Write();
  h_sinacol_qq->Write();
  h_sinacol_cc->Write();
  h_sinacol_radreturn->Write();

  h_K->Write();
  h_K_bb->Write();
  h_K_qq->Write();
  h_K_cc->Write();
  h_K_radreturn->Write();
  h_K_res->Write();
  
  h_K_parton_bb->Write();
  h_K_parton_qq->Write();
  h_K_parton_cc->Write();
  h_K_parton_radreturn->Write();

  h_K_parton_K_bb->Write();
  h_K_parton_K_qq->Write();
  h_K_parton_K_cc->Write();
  h_K_parton_K_radreturn->Write();

  h_acol_cos_bb->Write();
  h_acol_cos_qq->Write();
  h_acol_cos_cc->Write();
  h_acol_cos_radreturn->Write();

  h_acol_sin_bb->Write();
  h_acol_sin_qq->Write();
  h_acol_sin_cc->Write();
  h_acol_sin_radreturn->Write();
  
  h_acol_sphericity_bb->Write();
  h_acol_sphericity_qq->Write();
  h_acol_sphericity_cc->Write();
  h_acol_sphericity_radreturn->Write();

  h_thrust_bb->Write();
  h_thrust_qq->Write();
  h_thrust_cc->Write();
  h_thrust_radreturn->Write();

   
}


bool observable::PreSelection(int type=0,float Kvcut=25) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;

  if(type == 0 ) return true;

  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
  TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
  float acol=GetSinacol(v1,v2);
  
  double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
  double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

  
  float costheta_j0;
  std::vector<float> p_j0;
  p_j0.push_back(jet_px[0]);
  p_j0.push_back(jet_py[0]);
  p_j0.push_back(jet_pz[0]);
  costheta_j0=fabs(GetCostheta(p_j0));

  float costheta_j1;
  std::vector<float> p_j1;
  p_j1.push_back(jet_px[1]);
  p_j1.push_back(jet_py[1]);
  p_j1.push_back(jet_pz[1]);
  costheta_j1=fabs(GetCostheta(p_j1));
  
  float Kv=250.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
  float K1=jet0_p*acol/sqrt(1-costheta_j1*costheta_j1);
  float K2=jet1_p*acol/sqrt(1-costheta_j0*costheta_j0);

  //----------------------------------------------------------
  // AQUI METO LO NUEVO PARA CORTA EN LIKENESS
  //----------------------------------------------------------

  //menos importante
  float thrust=principle_thrust_value;//GetThrust(v0,v1);
 
  double  E_total[2]={0};
  double  photonPFO_ratio[2]={0};

  double  photonjet_E[2]={0};
  double  photonjet_costheta[2];
  photonjet_costheta[0]=-2;
  photonjet_costheta[1]=-2;
 
   
  //---------------------
  //Radiative return cuts, photon INSIDE the detector
  double npfo[2]={0};
  double npfo_photon[2]={0};
  float costheta=-2;
  float energy=0;
    
  //  for(int ijet=0; ijet<2; ijet++) {
  float costheta_jet_0=0;
  float costheta_jet_1=0;
  std::vector<float> p_pfo_0;
  std::vector<float> p_pfo_1;
  float px_0=0, py_0=0, pz_0=0;
  float px_1=0, py_1=0, pz_1=0;

  for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
    if(pfo_match[ipfo]<0) continue;
    
    npfo[pfo_match[ipfo]]++;
    
    E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
    if( pfo_type[ipfo]==22  || fabs(pfo_type[ipfo])==2112 ) {
      
      npfo_photon[pfo_match[ipfo]]++;

      if(pfo_match[ipfo]==0) {
	px_0+=pfo_px[ipfo];
	py_0+=pfo_py[ipfo];
	pz_0+=pfo_pz[ipfo];
      }
      if(pfo_match[ipfo]==1) {
	px_1+=pfo_px[ipfo];
	py_1+=pfo_py[ipfo];
	pz_1+=pfo_pz[ipfo];
      }
      photonjet_E[pfo_match[ipfo]] += pfo_E[ipfo];
    }
  }//ipfo
  
  p_pfo_0.push_back(px_0);
  p_pfo_0.push_back(py_0);
  p_pfo_0.push_back(pz_0);
  float costheta_pfo_0=GetCostheta(p_pfo_0);
  costheta_jet_0= costheta_pfo_0;

  p_pfo_1.push_back(px_1);
  p_pfo_1.push_back(py_1);
  p_pfo_1.push_back(pz_1);
  float costheta_pfo_1=GetCostheta(p_pfo_1);
  costheta_jet_1= costheta_pfo_1;
  
  
  photonPFO_ratio[0]=photonjet_E[0]/E_total[0];
  photonPFO_ratio[1]=photonjet_E[1]/E_total[1];
  photonjet_costheta[0]=costheta_jet_0;
  photonjet_costheta[1]=costheta_jet_1;

  // Definiciones para el corte de charge likeness:
  // LOS CHARGE NPFOS

    double  chargePFO_ratio[2]={0};

    double  chargejet_E[2]={0};
    double  chargejet_costheta[2];
    chargejet_costheta[0]=-2;
    chargejet_costheta[1]=-2;
    
    // double npfo[2]={0};
    //double npfo_photon[2]={0};
    // float costheta=-2;
    //float energy=0;
    Int_t npfo_charge[2]={0};
    //  for(int ijet=0; ijet<2; ijet++) {
    //float costheta_jet_0=0;
    //float costheta_jet_1=0;
    //std::vector<float> p_pfo_0;
    //std::vector<float> p_pfo_1;
    //float px_0=0, py_0=0, pz_0=0;
    //float px_1=0, py_1=0, pz_1=0;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
      if(pfo_match[ipfo]<0) continue;
      if(pfo_E[ipfo]<1) continue;
  
      npfo[pfo_match[ipfo]]++;
    
      E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
      if( pfo_charge[ipfo] != 0  ) {
      
	npfo_charge[pfo_match[ipfo]]++;

	if(pfo_match[ipfo]==0) {
	  px_0+=pfo_px[ipfo];
	  py_0+=pfo_py[ipfo];
	  pz_0+=pfo_pz[ipfo];
	}
	if(pfo_match[ipfo]==1) {
	  px_1+=pfo_px[ipfo];
	  py_1+=pfo_py[ipfo];
	  pz_1+=pfo_pz[ipfo];
	}
	chargejet_E[pfo_match[ipfo]] += pfo_E[ipfo];
      }
    }//ipfo
  
  
    chargePFO_ratio[0]=chargejet_E[0]/E_total[0];
    chargePFO_ratio[1]=chargejet_E[1]/E_total[1];
    chargejet_costheta[0]=costheta_jet_0;
    chargejet_costheta[1]=costheta_jet_1;
  
  

  // Variables para corte y23:
    //reco stuff
    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
  double reco_bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

 // variables para cortar gamma_e
 // Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;//sqrt(pow(mc_ISR_px[0]+mc_ISR_px[1],2)+pow(mc_ISR_py[0]+mc_ISR_py[1],2)+pow(mc_ISR_pz[0]+mc_ISR_pz[1],2));//gamma0_e+gamma1_e;


  //----------------------------------------------------------  
  // LOS LIMITES DEL CORTE en bbmass:  
  double bbmasscut=140;

  // LOS LIMITES DEL CORTE en npfos:  
  double NPFOSvar0=5;
  double NPFOSvar1=5;
  
  // LOS LIMITES DEL CORTE en charge_npfos:
  double CNPFOSvar0=0.5;
  double CNPFOSvar1=0.5;
  
  // LOS LIMITES DEL CORTE en h_e_costheta_gamma:
  double xaxisLEFT=-0.95;
  double xaxisRIGHT=+0.95;
  double energy1=90;
  double energy2=120;
  
  // LOS LIMITES DEL CORTE y23:
  double y23cut=0.015;
  
  // // LOS LIMITES DEL CORTE en photon_likeness:  
  // double LKvar0=0.9;
  // double LKvar1=0.9;

  // // LOS LIMITES DEL CORTE en charge likeness:
  // double CLKvar0=0.04;
  // double CLKvar1=0.04;

  // // LOS LIMITES DEL CORTE en mj1+mj2:
  // double mj1mj2limit=100;

  
  //----------------------------------------------------------

  // Corte npfos energy: pfo_E[ipfo]<1

  
  // Corte en K_reco:
  if(type == 1 )  if( Kv < Kvcut ) return true;

  // Corte mjj (bbmass):
  if(type == 2 )  if( Kv < Kvcut && bbmass>bbmasscut )  return true;

  // Corte en charge npfos:
  if(type == 3 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1)  return true;
  
  
  // // Corte en y23:
  // if(type == 4 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && d23/pow(reco_bbmass,2)<y23cut )  return true;

  // Corte en h_e_costheta:
  if(type == 4 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1)if(
											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
 
  // Corte en y23:
  if(type == 5 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && d23/pow(reco_bbmass,2)<y23cut)if(
											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
  
  // // Corte en photon likeness:
  // if(type == 6 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && d23/pow(reco_bbmass,2)<y23cut && photonPFO_ratio[0]<LKvar0 && photonPFO_ratio[1]<LKvar1)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
  // // Corte en y23:
  // if(type == 5 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && d23/pow(reco_bbmass,2)<y23cut)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;

 
  // // Corte en photon likeness:
  // if(type == 5 )  if( Kv < Kvcut && bbmass>bbmasscut && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && photonPFO_ratio[0]<LKvar0 && photonPFO_ratio[1]<LKvar1)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;

  
  
  // // Corte en "photon_likeness":
  // if(type == 7 )  if( Kv < Kvcut && bbmass>bbmasscut && d23/pow(reco_bbmass,2)<y23cut && npfo[0]>NPFOSvar0 && npfo[1]>NPFOSvar1 && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && photonPFO_ratio[0]<LKvar0 && photonPFO_ratio[1]<LKvar1)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
  
  // // Corte en "charge_likeness":
  // if(type == 8 )  if( Kv < Kvcut && bbmass>bbmasscut && d23/pow(reco_bbmass,2)<y23cut && npfo[0]>NPFOSvar0 && npfo[1]>NPFOSvar1 && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && photonPFO_ratio[0]<LKvar0 && photonPFO_ratio[1]<LKvar1 && chargePFO_ratio[0]>CLKvar0 && chargePFO_ratio[1]>CLKvar1)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
    
  // // Corte en "mj1+mj2":
  // if(type == 9 )  if( Kv < Kvcut && bbmass>bbmasscut && d23/pow(reco_bbmass,2)<y23cut && npfo[0]>NPFOSvar0 && npfo[1]>NPFOSvar1 && npfo_charge[0]>CNPFOSvar0 && npfo_charge[1]>CNPFOSvar1 && photonPFO_ratio[0]<LKvar0 && photonPFO_ratio[1]<LKvar1 && chargePFO_ratio[0]>CLKvar0 && chargePFO_ratio[1]>CLKvar1 && reco_b1mass+reco_b2mass<mj1mj2limit)if(
  // 											     ((photonjet_E[0]>photonjet_E[1]) and ( (photonjet_costheta[0]<xaxisLEFT && photonjet_E[0]<energy1) or(photonjet_costheta[0]>=xaxisLEFT && photonjet_costheta[0]<xaxisRIGHT && photonjet_E[0]<energy2) or(photonjet_costheta[0]>=xaxisRIGHT && photonjet_E[0]<energy1)) )
  // 											     or ((photonjet_E[0]<photonjet_E[1]) and ( (photonjet_costheta[1]<xaxisLEFT && photonjet_E[1]<energy1) or(photonjet_costheta[1]>=xaxisLEFT && photonjet_costheta[1]<xaxisRIGHT && photonjet_E[1]<energy2) or(photonjet_costheta[1]>=xaxisRIGHT && photonjet_E[1]<energy1))) ) return true;
  return false;
}
