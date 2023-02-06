#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "TGraph.h"
#include "TAxis.h"
#include "../../../style/Style.C"
#include "../../../style/Labels.C"

// Labels copiado de Adrián, tomar como referencia
// -----------------------------------------------
// -----------------------------------------------
void Labels(int i, TString pol){

  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, " K_{reco} veto",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco} veto& m_{j_{1},j_{2}}>140 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>140 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>140 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 1 ",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>140 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 1 & y_{23}<0.015",kOrange+3);
  }
  if(i==6) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>140 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 1 & y_{23}<0.015 & Charge Likeness Veto ",kOrange+3);
  }
 if(i==7) {
    QQBARLabel2(0.04,0.082, "K_{reco}<35 GeV & m_{j_{1},j_{2}}>140 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Photon Veto 2 & y_{23}<0.015 & Charge Likeness Veto  ",kOrange+3);
  }
 
   

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, XX fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, XX fb^{-1}",kGray+2);

}


// ------------------------------------------------------------
// ------------------------------------------------------------
void AFB_kgamma_values(int size) {

// Escribo los vectores de las eficiencias:
  double K[]={10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500};

  
  TString filenamecut[2][size];
  TString filenameaux[2];
  filenameaux[0]=("../output/selection_cuts0_2f_hadronic_sample_eL_pR_");
  filenameaux[1]=("../output/selection_cuts0_2f_hadronic_sample_eR_pL_");
  TFile *fcut[2][size];
  TH1F *h_mc_costheta_bb_cut[2][size];
  TH1F *h_mc_costheta_bb_isr_cut[2][size];
  TH1F *h_mc_com_costheta_bb_cut[2][size];
  TH1F *h_mc_com_costheta_bb_isr_cut[2][size];
  TH1F *h_mc_costheta_cc_cut[2][size];
  TH1F *h_mc_costheta_cc_isr_cut[2][size];
  TH1F *h_mc_com_costheta_cc_cut[2][size];
  TH1F *h_mc_com_costheta_cc_isr_cut[2][size];
  
  
  for(int pol=0;pol<2;pol++){
    for(int i=0;i<size;i++) {
      int kvalue=10*i+10;  
      filenamecut[pol][i]=filenameaux[pol]+TString::Format("Kgamma%i_500GeV.root",kvalue);
      fcut[pol][i]=new TFile(filenamecut[pol][i]);
      h_mc_costheta_bb_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_costheta_bb");
      h_mc_costheta_bb_isr_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_costheta_bb_isr");
      h_mc_com_costheta_bb_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_com_costheta_bb");
      h_mc_com_costheta_bb_isr_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_com_costheta_bb_isr");
      h_mc_costheta_cc_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_costheta_cc");
      h_mc_costheta_cc_isr_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_costheta_cc_isr");
      h_mc_com_costheta_cc_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_com_costheta_cc");
      h_mc_com_costheta_cc_isr_cut[pol][i]=(TH1F*)fcut[pol][i]->Get("h_mc_com_costheta_cc_isr");
    }
  }
  
  int bin_B = h_mc_costheta_bb_cut[0][0]->GetXaxis()->FindBin(-0.99999999);
  int bin_0 = h_mc_costheta_bb_cut[0][0]->GetXaxis()->FindBin(-0.00000001);
  int bin_F = h_mc_costheta_bb_cut[0][0]->GetXaxis()->FindBin(+0.99999999);
  int NBINS= h_mc_costheta_bb_cut[0][0]->GetNbinsX();
  
  double AFB_bb_lab[2][size];
  double AFB_bb_com[2][size];
  double AFB_bb_isr_lab[2][size];
  double AFB_bb_isr_com[2][size];
  double AFB_cc_lab[2][size];
  double AFB_cc_com[2][size];
  double AFB_cc_isr_lab[2][size];
  double AFB_cc_isr_com[2][size];
  
  double stat_error_AFB_bb_lab[2][size];
  double stat_error_AFB_bb_com[2][size];
  double stat_error_AFB_bb_isr_lab[2][size];
  double stat_error_AFB_bb_isr_com[2][size];
  double stat_error_AFB_cc_lab[2][size];
  double stat_error_AFB_cc_com[2][size];
  double stat_error_AFB_cc_isr_lab[2][size];
  double stat_error_AFB_cc_isr_com[2][size];

  float NF;
  float NB;
  
  for(int pol=0;pol<2;pol++){
    for(int i=0;i<size;i++) {
      NF=h_mc_costheta_bb_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_costheta_bb_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_bb_lab[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_bb_lab[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_com_costheta_bb_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_com_costheta_bb_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_bb_com[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_bb_com[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_costheta_bb_isr_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_costheta_bb_isr_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_bb_isr_lab[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_bb_isr_lab[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_com_costheta_bb_isr_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_com_costheta_bb_isr_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_bb_isr_com[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_bb_isr_com[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_costheta_cc_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_costheta_cc_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_cc_lab[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_cc_lab[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_com_costheta_cc_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_com_costheta_cc_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_cc_com[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_cc_com[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_costheta_cc_isr_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_costheta_cc_isr_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_cc_isr_lab[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_cc_isr_lab[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
      NF=h_mc_com_costheta_cc_isr_cut[pol][i]->Integral(bin_0+1,bin_F);
      NB=h_mc_com_costheta_cc_isr_cut[pol][i]->Integral(bin_B,bin_0);
      AFB_cc_isr_com[pol][i]=(NF-NB)/(NF+NB);
      stat_error_AFB_cc_isr_com[pol][i]=pow(pow(pow(NF,0.5)*((2*NB)/(pow(NF+NB,2))),2)+pow(pow(NB,0.5)*((2*NF)/(pow(NF+NB,2))),2),0.5);
    }
  }
  
  double AFB_bb_lab_eLpR[size];
  double AFB_bb_com_eLpR[size];
  double AFB_bb_isr_lab_eLpR[size];
  double AFB_bb_isr_com_eLpR[size];
  double AFB_cc_lab_eLpR[size];
  double AFB_cc_com_eLpR[size];
  double AFB_cc_isr_lab_eLpR[size];
  double AFB_cc_isr_com_eLpR[size];
  
  double stat_error_AFB_bb_lab_eLpR[size];
  double stat_error_AFB_bb_com_eLpR[size];
  double stat_error_AFB_bb_isr_lab_eLpR[size];
  double stat_error_AFB_bb_isr_com_eLpR[size];
  double stat_error_AFB_cc_lab_eLpR[size];
  double stat_error_AFB_cc_com_eLpR[size];
  double stat_error_AFB_cc_isr_lab_eLpR[size];
  double stat_error_AFB_cc_isr_com_eLpR[size];
  
  double AFB_bb_lab_eRpL[size];
  double AFB_bb_com_eRpL[size];
  double AFB_bb_isr_lab_eRpL[size];
  double AFB_bb_isr_com_eRpL[size];
  double AFB_cc_lab_eRpL[size];
  double AFB_cc_com_eRpL[size];
  double AFB_cc_isr_lab_eRpL[size];
  double AFB_cc_isr_com_eRpL[size];
  
  double stat_error_AFB_bb_lab_eRpL[size];
  double stat_error_AFB_bb_com_eRpL[size];
  double stat_error_AFB_bb_isr_lab_eRpL[size];
  double stat_error_AFB_bb_isr_com_eRpL[size];
  double stat_error_AFB_cc_lab_eRpL[size];
  double stat_error_AFB_cc_com_eRpL[size];
  double stat_error_AFB_cc_isr_lab_eRpL[size];
  double stat_error_AFB_cc_isr_com_eRpL[size];


  for(int i=0;i<size;i++) {
    
  AFB_bb_lab_eLpR[i]=AFB_bb_lab[0][i];
  AFB_bb_com_eLpR[i]=AFB_bb_com[0][i];
  AFB_bb_isr_lab_eLpR[i]=AFB_bb_isr_lab[0][i] ;
  AFB_bb_isr_com_eLpR[i]=AFB_bb_isr_com[0][i] ;
  AFB_cc_lab_eLpR[i]=AFB_cc_lab[0][i] ;
  AFB_cc_com_eLpR[i]=AFB_cc_com[0][i] ;
  AFB_cc_isr_lab_eLpR[i]=AFB_cc_isr_lab[0][i] ;
  AFB_cc_isr_com_eLpR[i]=AFB_cc_isr_com[0][i] ;
  
  stat_error_AFB_bb_lab_eLpR[i]=stat_error_AFB_bb_lab[0][i];
  stat_error_AFB_bb_com_eLpR[i]=stat_error_AFB_bb_com[0][i];
  stat_error_AFB_bb_isr_lab_eLpR[i]=stat_error_AFB_bb_isr_lab[0][i];
  stat_error_AFB_bb_isr_com_eLpR[i]=stat_error_AFB_bb_isr_com[0][i];
  stat_error_AFB_cc_lab_eLpR[i]=stat_error_AFB_cc_lab[0][i];
  stat_error_AFB_cc_com_eLpR[i]=stat_error_AFB_cc_com[0][i];
  stat_error_AFB_cc_isr_lab_eLpR[i]=stat_error_AFB_cc_isr_lab[0][i];
  stat_error_AFB_cc_isr_com_eLpR[i]=stat_error_AFB_cc_isr_com[0][i];
  
  AFB_bb_lab_eRpL[i]=AFB_bb_lab[1][i];
  AFB_bb_com_eRpL[i]=AFB_bb_com[1][i];
  AFB_bb_isr_lab_eRpL[i]=AFB_bb_isr_lab[1][i];
  AFB_bb_isr_com_eRpL[i]=AFB_bb_isr_com[1][i];
  AFB_cc_lab_eRpL[i]= AFB_cc_lab[1][i];
  AFB_cc_com_eRpL[i]=AFB_cc_com[1][i];
  AFB_cc_isr_lab_eRpL[i]=AFB_cc_isr_lab[1][i];
  AFB_cc_isr_com_eRpL[i]=AFB_cc_isr_com[1][i];
  
  stat_error_AFB_bb_lab_eRpL[i]=stat_error_AFB_bb_lab[1][i];
  stat_error_AFB_bb_com_eRpL[i]=stat_error_AFB_bb_com[1][i];
  stat_error_AFB_bb_isr_lab_eRpL[i]=stat_error_AFB_bb_isr_lab[1][i];
  stat_error_AFB_bb_isr_com_eRpL[i]=stat_error_AFB_bb_isr_com[1][i];
  stat_error_AFB_cc_lab_eRpL[i]=stat_error_AFB_cc_lab[1][i];
  stat_error_AFB_cc_com_eRpL[i]=stat_error_AFB_cc_com[1][i];
  stat_error_AFB_cc_isr_lab_eRpL[i]=stat_error_AFB_cc_isr_lab[1][i];
  stat_error_AFB_cc_isr_com_eRpL[i]=stat_error_AFB_cc_isr_com[1][i];
  }

  
  //eLpR
  //b
  //double AFB_bb_lab_eLpR[]={0.688777,0.68796,0.688386,0.688643,0.688522,0.689056,0.687829,0.688771,0.689263,0.688982,0.688999,0.689556,0.689614,0.68952,0.689568,0.689029,0.689109,0.688338,0.686931,0.685089 }; 
  // double AFB_bb_isr_lab_eLpR[]={0.602961,0.601726,0.600752,0.600011,0.599517,0.598933,0.598784,0.59815,0.597598,0.597237,0.596859,0.596335,0.595945,0.595605,0.595236,0.594976,0.594378,0.593848,0.593232,0.592271 }; 
  // double AFB_bb_com_eLpR[]={0.688821,0.688042,0.688464,0.688718,0.688595,0.689127,0.687935,0.688874,0.689432,0.68918,0.689259,0.689812,0.68993,0.689832,0.689844,0.689422,0.689641,0.689231,0.688349,0.687122 }; 
  // double AFB_bb_isr_com_eLpR[]={0.625308,0.624428,0.623687,0.623126,0.622767,0.622304,0.62226,0.621733,0.621276,0.621019,0.620721,0.620295,0.619984,0.619738,0.619468,0.61928,0.618787,0.61834,0.617824,0.617046 };
  // //c
  // double AFB_cc_lab_eLpR[]={0.599096,0.598114,0.597761,0.598557,0.598786,0.598764,0.598632,0.598132,0.598053,0.598382,0.597826,0.59775,0.597532,0.597814,0.597696,0.597072,0.596863,0.596037,0.59472,0.592848 };
  // double AFB_cc_isr_lab_eLpR[]={0.449526,0.445761,0.443212,0.440873,0.439038,0.437564,0.436235,0.43517,0.43395,0.432663,0.43177,0.430689,0.429685,0.428505,0.427456,0.426595,0.425224,0.423733,0.42197,0.419748 }; 
  // double AFB_cc_com_eLpR[]={0.599096,0.598088,0.597736,0.598533,0.598763,0.598741,0.59861,0.59811,0.598031,0.598382,0.597868,0.597812,0.597634,0.597955,0.597835,0.597229,0.597075,0.596434,0.595272,0.59363 };  
  // double AFB_cc_isr_com_eLpR[]={0.462802,0.459409,0.4571,0.454944,0.453265,0.451922,0.450716,0.449766,0.448658,0.447464,0.446654,0.445663,0.444739,0.443633,0.442684,0.441918,0.44065,0.439232,0.437601,0.435533 };

  // Plots:

    gStyle->SetOptFit(0); 
    gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
  
    //gStyle->SetTitleBorderSize(0);
    //gStyle->SetTitleStyle(0);
    //gStyle->SetTitleX(0.2);
    //gStyle->SetMarkerSize(1.5);

  //gStyle->SetLabelOffset(1.2);
  gStyle->SetTitleSize(1.1);
  gStyle->SetTitleXSize(0.045);
  gStyle->SetTitleYSize(0.045);
  gStyle->SetLegendFont(42);
  gStyle->SetLegendTextSize(0.04);
  
  //eLpR plots:
  //bb plots
  //bb_lab_eLpR
  auto Canvas_AFB_bb_lab_eLpR = new TCanvas("Canvas_AFB_bb_lab_eLpR","Canvas_AFB_bb_lab_eLpR",700,500);
  Canvas_AFB_bb_lab_eLpR->SetGrid();
  TGraph *bb_lab_eLpR=new TGraphErrors(size,K,AFB_bb_lab_eLpR,0,stat_error_AFB_bb_lab_eLpR);
  bb_lab_eLpR->SetMarkerStyle(33);
  bb_lab_eLpR->SetMarkerColor(226);
  bb_lab_eLpR->SetMarkerSize(1);
  bb_lab_eLpR->SetLineWidth(2);
  bb_lab_eLpR->SetLineColor(226);
  bb_lab_eLpR->SetTitle("K_{ISR} < K (lab frame)");
  bb_lab_eLpR->GetXaxis()->SetTitle("K (GeV)");
  bb_lab_eLpR->GetYaxis()->SetTitle("A_{FB}");
  bb_lab_eLpR->GetYaxis()->SetTitleOffset(1);
  bb_lab_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  bb_lab_eLpR->Draw("apl");

      //Add Legend 
   TLegend *bb_lab_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_lab_eLpR_leg->AddEntry(bb_lab_eLpR," b #bar{b}","p");
   //bb_lab_eLpR_leg->SetFillStyle(0);
   bb_lab_eLpR_leg->SetLineWidth(1);
   bb_lab_eLpR_leg->SetLineColor(1);
   bb_lab_eLpR_leg->SetBorderSize(0);
   bb_lab_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);
   //QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, XX fb^{-1}",kGray+2);
   
  //bb_com_eLpR
  auto Canvas_AFB_bb_com_eLpR = new TCanvas("Canvas_AFB_bb_com_eLpR","Canvas_AFB_bb_com_eLpR",700,500);
  Canvas_AFB_bb_com_eLpR->SetGrid();
  TGraph *bb_com_eLpR=new TGraphErrors(size,K,AFB_bb_com_eLpR,0,stat_error_AFB_bb_com_eLpR);
  bb_com_eLpR->SetMarkerStyle(33);
  bb_com_eLpR->SetMarkerColor(52);
  bb_com_eLpR->SetMarkerSize(1);
  bb_com_eLpR->SetLineWidth(2);
  bb_com_eLpR->SetLineColor(52);
  bb_com_eLpR->SetTitle("K_{ISR} < K (com frame)");
  bb_com_eLpR->GetXaxis()->SetTitle("K (GeV)");
  bb_com_eLpR->GetYaxis()->SetTitle("A_{FB}");
  bb_com_eLpR->GetYaxis()->SetTitleOffset(1);
  bb_com_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  bb_com_eLpR->Draw("apl");

      //Add Legend 
   TLegend *bb_com_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_com_eLpR_leg->AddEntry(bb_com_eLpR," b #bar{b}","p");
   //bb_com_eLpR_leg->SetFillStyle(0);
   bb_com_eLpR_leg->SetLineWidth(1);
   bb_com_eLpR_leg->SetLineColor(1);
   bb_com_eLpR_leg->SetBorderSize(0);
   bb_com_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);

   
  //bb_isr_lab_isr_eLpR
  auto Canvas_AFB_bb_isr_lab_eLpR = new TCanvas("Canvas_AFB_bb_isr_lab_eLpR","Canvas_AFB_bb_isr_lab_eLpR",700,500);
  Canvas_AFB_bb_isr_lab_eLpR->SetGrid();
  TGraph *bb_isr_lab_eLpR=new TGraphErrors(size,K,AFB_bb_isr_lab_eLpR,0,stat_error_AFB_bb_isr_lab_eLpR);
  bb_isr_lab_eLpR->SetMarkerStyle(33);
  bb_isr_lab_eLpR->SetMarkerColor(92);
  bb_isr_lab_eLpR->SetMarkerSize(1);
  bb_isr_lab_eLpR->SetLineWidth(2);
  bb_isr_lab_eLpR->SetLineColor(92);
  bb_isr_lab_eLpR->SetTitle("K_{ISR} > K (lab frame)");
  bb_isr_lab_eLpR->GetXaxis()->SetTitle("K (GeV)");
  bb_isr_lab_eLpR->GetYaxis()->SetTitle("A_{FB}");
  bb_isr_lab_eLpR->GetYaxis()->SetTitleOffset(1);
  bb_isr_lab_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  bb_isr_lab_eLpR->Draw("apl");

      //Add Legend 
   TLegend *bb_isr_lab_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_isr_lab_eLpR_leg->AddEntry(bb_isr_lab_eLpR," b #bar{b}","p");
   //bb_isr_lab_eLpR_leg->SetFillStyle(0);
   bb_isr_lab_eLpR_leg->SetLineWidth(1);
   bb_isr_lab_eLpR_leg->SetLineColor(1);
   bb_isr_lab_eLpR_leg->SetBorderSize(0);
   bb_isr_lab_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);
   
  //bb_isr_com_eLpR
  auto Canvas_AFB_bb_isr_com_eLpR = new TCanvas("Canvas_AFB_bb_isr_com_eLpR","Canvas_AFB_bb_isr_com_eLpR",700,500);
  Canvas_AFB_bb_isr_com_eLpR->SetGrid();
  TGraph *bb_isr_com_eLpR=new TGraphErrors(size,K,AFB_bb_isr_com_eLpR,0,stat_error_AFB_bb_isr_com_eLpR);
  bb_isr_com_eLpR->SetMarkerStyle(33);
  bb_isr_com_eLpR->SetMarkerColor(97);
  bb_isr_com_eLpR->SetMarkerSize(1);
  bb_isr_com_eLpR->SetLineWidth(2);
  bb_isr_com_eLpR->SetLineColor(97);
  bb_isr_com_eLpR->SetTitle("K_{ISR} > K (com frame)");
  bb_isr_com_eLpR->GetXaxis()->SetTitle("K (GeV)");
  bb_isr_com_eLpR->GetYaxis()->SetTitle("A_{FB}");
  bb_isr_com_eLpR->GetYaxis()->SetTitleOffset(1);
  bb_isr_com_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  bb_isr_com_eLpR->Draw("apl");

      //Add Legend 
   TLegend *bb_isr_com_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_isr_com_eLpR_leg->AddEntry(bb_isr_com_eLpR," b #bar{b}","p");
   //bb_isr_com_eLpR_leg->SetFillStyle(0);
   bb_isr_com_eLpR_leg->SetLineWidth(1);
   bb_isr_com_eLpR_leg->SetLineColor(1);
   bb_isr_com_eLpR_leg->SetBorderSize(0);
   bb_isr_com_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);

   //cc plots:
   
  //cc_lab_eLpR
  auto Canvas_AFB_cc_lab_eLpR = new TCanvas("Canvas_AFB_cc_lab_eLpR","Canvas_AFB_cc_lab_eLpR",700,500);
  Canvas_AFB_cc_lab_eLpR->SetGrid();
  TGraph *cc_lab_eLpR=new TGraphErrors(size,K,AFB_cc_lab_eLpR,0,stat_error_AFB_cc_lab_eLpR);
  cc_lab_eLpR->SetMarkerStyle(34);
  cc_lab_eLpR->SetMarkerColor(226);
  cc_lab_eLpR->SetMarkerSize(1);
  cc_lab_eLpR->SetLineWidth(2);
  cc_lab_eLpR->SetLineColor(226);
  cc_lab_eLpR->SetTitle("K_{ISR} < K (lab frame)");
  cc_lab_eLpR->GetXaxis()->SetTitle("K (GeV)");
  cc_lab_eLpR->GetYaxis()->SetTitle("A_{FB}");
  cc_lab_eLpR->GetYaxis()->SetTitleOffset(1);
  cc_lab_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  cc_lab_eLpR->Draw("apl");

      //Add Legend 
   TLegend *cc_lab_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_lab_eLpR_leg->AddEntry(cc_lab_eLpR," c #bar{c}","lp");
   //cc_lab_eLpR_leg->SetFillStyle(0);
   cc_lab_eLpR_leg->SetLineWidth(1);
   cc_lab_eLpR_leg->SetLineColor(1);
   cc_lab_eLpR_leg->SetBorderSize(0);
   cc_lab_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);
   
  //cc_com_eLpR
  auto Canvas_AFB_cc_com_eLpR = new TCanvas("Canvas_AFB_cc_com_eLpR","Canvas_AFB_cc_com_eLpR",700,500);
  Canvas_AFB_cc_com_eLpR->SetGrid();
  TGraph *cc_com_eLpR=new TGraphErrors(size,K,AFB_cc_com_eLpR,0,stat_error_AFB_cc_com_eLpR);
  cc_com_eLpR->SetMarkerStyle(34);
  cc_com_eLpR->SetMarkerColor(52);
  cc_com_eLpR->SetMarkerSize(1);
  cc_com_eLpR->SetLineWidth(2);
  cc_com_eLpR->SetLineColor(52);
  cc_com_eLpR->SetTitle("K_{ISR} < K (com frame)");
  cc_com_eLpR->GetXaxis()->SetTitle("K (GeV)");
  cc_com_eLpR->GetYaxis()->SetTitle("A_{FB}");
  cc_com_eLpR->GetYaxis()->SetTitleOffset(1);
  cc_com_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  cc_com_eLpR->Draw("apl");

      //Add Legend 
   TLegend *cc_com_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_com_eLpR_leg->AddEntry(cc_com_eLpR,"c #bar{c}","p");
   //cc_com_eLpR_leg->SetFillStyle(0);
   cc_com_eLpR_leg->SetLineWidth(1);
   cc_com_eLpR_leg->SetLineColor(1);
   cc_com_eLpR_leg->SetBorderSize(0);
   cc_com_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);

   
  //cc_isr_lab_isr_eLpR
  auto Canvas_AFB_cc_isr_lab_eLpR = new TCanvas("Canvas_AFB_cc_isr_lab_eLpR","Canvas_AFB_cc_isr_lab_eLpR",700,500);
  Canvas_AFB_cc_isr_lab_eLpR->SetGrid();
  TGraph *cc_isr_lab_eLpR=new TGraphErrors(size,K,AFB_cc_isr_lab_eLpR,0,stat_error_AFB_cc_isr_lab_eLpR);
  cc_isr_lab_eLpR->SetMarkerStyle(34);
  cc_isr_lab_eLpR->SetMarkerColor(92);
  cc_isr_lab_eLpR->SetMarkerSize(1);
  cc_isr_lab_eLpR->SetLineWidth(2);
  cc_isr_lab_eLpR->SetLineColor(92);
  cc_isr_lab_eLpR->SetTitle("K_{ISR} > K (lab frame)");
  cc_isr_lab_eLpR->GetXaxis()->SetTitle("K (GeV)");
  cc_isr_lab_eLpR->GetYaxis()->SetTitle("A_{FB}");
  cc_isr_lab_eLpR->GetYaxis()->SetTitleOffset(1);
  cc_isr_lab_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  cc_isr_lab_eLpR->Draw("apl");

      //Add Legend 
   TLegend *cc_isr_lab_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_isr_lab_eLpR_leg->AddEntry(cc_isr_lab_eLpR," c #bar{c}","p");
   //cc_isr_lab_eLpR_leg->SetFillStyle(0);
   cc_isr_lab_eLpR_leg->SetLineWidth(1);
   cc_isr_lab_eLpR_leg->SetLineColor(1);
   cc_isr_lab_eLpR_leg->SetBorderSize(0);
   cc_isr_lab_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);
   
  //cc_isr_com_eLpR
  auto Canvas_AFB_cc_isr_com_eLpR = new TCanvas("Canvas_AFB_cc_isr_com_eLpR","Canvas_AFB_cc_isr_com_eLpR",700,500);
  Canvas_AFB_cc_isr_com_eLpR->SetGrid();
  TGraph *cc_isr_com_eLpR=new TGraphErrors(size,K,AFB_cc_isr_com_eLpR,0,stat_error_AFB_cc_isr_com_eLpR);
  cc_isr_com_eLpR->SetMarkerStyle(34);
  cc_isr_com_eLpR->SetMarkerColor(97);
  cc_isr_com_eLpR->SetMarkerSize(1);
  cc_isr_com_eLpR->SetLineWidth(2);
  cc_isr_com_eLpR->SetLineColor(97);
  cc_isr_com_eLpR->SetTitle("K_{ISR} > K (com frame)");
  cc_isr_com_eLpR->GetXaxis()->SetTitle("K (GeV)");
  cc_isr_com_eLpR->GetYaxis()->SetTitle("A_{FB}");
  cc_isr_com_eLpR->GetYaxis()->SetTitleOffset(1);
  cc_isr_com_eLpR->GetYaxis()->SetRangeUser(-1,+1);
  cc_isr_com_eLpR->Draw("apl");

      //Add Legend 
   TLegend *cc_isr_com_eLpR_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_isr_com_eLpR_leg->AddEntry(cc_isr_com_eLpR," c #bar{c}","p");
   //cc_isr_com_eLpR_leg->SetFillStyle(0);
   cc_isr_com_eLpR_leg->SetLineWidth(1);
   cc_isr_com_eLpR_leg->SetLineColor(1);
   cc_isr_com_eLpR_leg->SetBorderSize(0);
   cc_isr_com_eLpR_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 46.4 fb^{-1}",kOrange+3);

   
  //eRpL plots:
  //bb plots
  //bb_lab_eRpL
  auto Canvas_AFB_bb_lab_eRpL = new TCanvas("Canvas_AFB_bb_lab_eRpL","Canvas_AFB_bb_lab_eRpL",700,500);
  Canvas_AFB_bb_lab_eRpL->SetGrid();
  TGraph *bb_lab_eRpL=new TGraphErrors(size,K,AFB_bb_lab_eRpL,0,stat_error_AFB_bb_lab_eRpL);
  bb_lab_eRpL->SetMarkerStyle(33);
  bb_lab_eRpL->SetMarkerColor(226);
  bb_lab_eRpL->SetMarkerSize(1);
  bb_lab_eRpL->SetLineWidth(2);
  bb_lab_eRpL->SetLineColor(226);
  bb_lab_eRpL->SetTitle("K_{ISR} < K (lab frame)");
  bb_lab_eRpL->GetXaxis()->SetTitle("K (GeV)");
  bb_lab_eRpL->GetYaxis()->SetTitle("A_{FB}");
  bb_lab_eRpL->GetYaxis()->SetTitleOffset(1);
  bb_lab_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  bb_lab_eRpL->Draw("apl");

      //Add Legend 
   TLegend *bb_lab_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_lab_eRpL_leg->AddEntry(bb_lab_eRpL," b #bar{b}","p");
   //bb_lab_eRpL_leg->SetFillStyle(0);
   bb_lab_eRpL_leg->SetLineWidth(1);
   bb_lab_eRpL_leg->SetLineColor(1);
   bb_lab_eRpL_leg->SetBorderSize(0);
   bb_lab_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);
   
  //bb_com_eRpL
  auto Canvas_AFB_bb_com_eRpL = new TCanvas("Canvas_AFB_bb_com_eRpL","Canvas_AFB_bb_com_eRpL",700,500);
  Canvas_AFB_bb_com_eRpL->SetGrid();
  TGraph *bb_com_eRpL=new TGraphErrors(size,K,AFB_bb_com_eRpL,0,stat_error_AFB_bb_com_eRpL);
  bb_com_eRpL->SetMarkerStyle(33);
  bb_com_eRpL->SetMarkerColor(52);
  bb_com_eRpL->SetMarkerSize(1);
  bb_com_eRpL->SetLineWidth(2);
  bb_com_eRpL->SetLineColor(52);
  bb_com_eRpL->SetTitle("K_{ISR} < K (com frame)");
  bb_com_eRpL->GetXaxis()->SetTitle("K (GeV)");
  bb_com_eRpL->GetYaxis()->SetTitle("A_{FB}");
  bb_com_eRpL->GetYaxis()->SetTitleOffset(1);
  bb_com_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  bb_com_eRpL->Draw("apl");

      //Add Legend 
   TLegend *bb_com_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_com_eRpL_leg->AddEntry(bb_com_eRpL," b #bar{b}","p");
   //bb_com_eRpL_leg->SetFillStyle(0);
   bb_com_eRpL_leg->SetLineWidth(1);
   bb_com_eRpL_leg->SetLineColor(1);
   bb_com_eRpL_leg->SetBorderSize(0);
   bb_com_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);

   
  //bb_isr_lab_isr_eRpL
  auto Canvas_AFB_bb_isr_lab_eRpL = new TCanvas("Canvas_AFB_bb_isr_lab_eRpL","Canvas_AFB_bb_isr_lab_eRpL",700,500);
  Canvas_AFB_bb_isr_lab_eRpL->SetGrid();
  TGraph *bb_isr_lab_eRpL=new TGraphErrors(size,K,AFB_bb_isr_lab_eRpL,0,stat_error_AFB_bb_isr_lab_eRpL);
  bb_isr_lab_eRpL->SetMarkerStyle(33);
  bb_isr_lab_eRpL->SetMarkerColor(92);
  bb_isr_lab_eRpL->SetMarkerSize(1);
  bb_isr_lab_eRpL->SetLineWidth(2);
  bb_isr_lab_eRpL->SetLineColor(92);
  bb_isr_lab_eRpL->SetTitle("K_{ISR} > K (lab frame)");
  bb_isr_lab_eRpL->GetXaxis()->SetTitle("K (GeV)");
  bb_isr_lab_eRpL->GetYaxis()->SetTitle("A_{FB}");
  bb_isr_lab_eRpL->GetYaxis()->SetTitleOffset(1);
  bb_isr_lab_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  bb_isr_lab_eRpL->Draw("apl");

      //Add Legend 
   TLegend *bb_isr_lab_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_isr_lab_eRpL_leg->AddEntry(bb_isr_lab_eRpL," b #bar{b}","p");
   //bb_isr_lab_eRpL_leg->SetFillStyle(0);
   bb_isr_lab_eRpL_leg->SetLineWidth(1);
   bb_isr_lab_eRpL_leg->SetLineColor(1);
   bb_isr_lab_eRpL_leg->SetBorderSize(0);
   bb_isr_lab_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);
   
  //bb_isr_com_eRpL
  auto Canvas_AFB_bb_isr_com_eRpL = new TCanvas("Canvas_AFB_bb_isr_com_eRpL","Canvas_AFB_bb_isr_com_eRpL",700,500);
  Canvas_AFB_bb_isr_com_eRpL->SetGrid();
  TGraph *bb_isr_com_eRpL=new TGraphErrors(size,K,AFB_bb_isr_com_eRpL,0,stat_error_AFB_bb_isr_com_eRpL);
  bb_isr_com_eRpL->SetMarkerStyle(33);
  bb_isr_com_eRpL->SetMarkerColor(97);
  bb_isr_com_eRpL->SetMarkerSize(1);
  bb_isr_com_eRpL->SetLineWidth(2);
  bb_isr_com_eRpL->SetLineColor(97);
  bb_isr_com_eRpL->SetTitle("K_{ISR} > K (com frame)");
  bb_isr_com_eRpL->GetXaxis()->SetTitle("K (GeV)");
  bb_isr_com_eRpL->GetYaxis()->SetTitle("A_{FB}");
  bb_isr_com_eRpL->GetYaxis()->SetTitleOffset(1);
  bb_isr_com_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  bb_isr_com_eRpL->Draw("apl");

      //Add Legend 
   TLegend *bb_isr_com_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   bb_isr_com_eRpL_leg->AddEntry(bb_isr_com_eRpL," b #bar{b}","p");
   //bb_isr_com_eRpL_leg->SetFillStyle(0);
   bb_isr_com_eRpL_leg->SetLineWidth(1);
   bb_isr_com_eRpL_leg->SetLineColor(1);
   bb_isr_com_eRpL_leg->SetBorderSize(0);
   bb_isr_com_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);

   //cc plots:
   
  //cc_lab_eRpL
  auto Canvas_AFB_cc_lab_eRpL = new TCanvas("Canvas_AFB_cc_lab_eRpL","Canvas_AFB_cc_lab_eRpL",700,500);
  Canvas_AFB_cc_lab_eRpL->SetGrid();
  TGraph *cc_lab_eRpL=new TGraphErrors(size,K,AFB_cc_lab_eRpL,0,stat_error_AFB_cc_lab_eRpL);
  cc_lab_eRpL->SetMarkerStyle(34);
  cc_lab_eRpL->SetMarkerColor(226);
  cc_lab_eRpL->SetMarkerSize(1);
  cc_lab_eRpL->SetLineWidth(2);
  cc_lab_eRpL->SetLineColor(226);
  cc_lab_eRpL->SetTitle("K_{ISR} < K (lab frame)");
  cc_lab_eRpL->GetXaxis()->SetTitle("K (GeV)");
  cc_lab_eRpL->GetYaxis()->SetTitle("A_{FB}");
  cc_lab_eRpL->GetYaxis()->SetTitleOffset(1);
  cc_lab_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  cc_lab_eRpL->Draw("apl");

      //Add Legend 
   TLegend *cc_lab_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_lab_eRpL_leg->AddEntry(cc_lab_eRpL," c #bar{c}","lp");
   //cc_lab_eRpL_leg->SetFillStyle(0);
   cc_lab_eRpL_leg->SetLineWidth(1);
   cc_lab_eRpL_leg->SetLineColor(1);
   cc_lab_eRpL_leg->SetBorderSize(0);
   cc_lab_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);
   
  //cc_com_eRpL
  auto Canvas_AFB_cc_com_eRpL = new TCanvas("Canvas_AFB_cc_com_eRpL","Canvas_AFB_cc_com_eRpL",700,500);
  Canvas_AFB_cc_com_eRpL->SetGrid();
  TGraph *cc_com_eRpL=new TGraphErrors(size,K,AFB_cc_com_eRpL,0,stat_error_AFB_cc_com_eRpL);
  cc_com_eRpL->SetMarkerStyle(34);
  cc_com_eRpL->SetMarkerColor(52);
  cc_com_eRpL->SetMarkerSize(1);
  cc_com_eRpL->SetLineWidth(2);
  cc_com_eRpL->SetLineColor(52);
  cc_com_eRpL->SetTitle("K_{ISR} < K (com frame)");
  cc_com_eRpL->GetXaxis()->SetTitle("K (GeV)");
  cc_com_eRpL->GetYaxis()->SetTitle("A_{FB}");
  cc_com_eRpL->GetYaxis()->SetTitleOffset(1);
  cc_com_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  cc_com_eRpL->Draw("apl");

      //Add Legend 
   TLegend *cc_com_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_com_eRpL_leg->AddEntry(cc_com_eRpL,"c #bar{c}","p");
   //cc_com_eRpL_leg->SetFillStyle(0);
   cc_com_eRpL_leg->SetLineWidth(1);
   cc_com_eRpL_leg->SetLineColor(1);
   cc_com_eRpL_leg->SetBorderSize(0);
   cc_com_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);

   
  //cc_isr_lab_isr_eRpL
  auto Canvas_AFB_cc_isr_lab_eRpL = new TCanvas("Canvas_AFB_cc_isr_lab_eRpL","Canvas_AFB_cc_isr_lab_eRpL",700,500);
  Canvas_AFB_cc_isr_lab_eRpL->SetGrid();
  TGraph *cc_isr_lab_eRpL=new TGraphErrors(size,K,AFB_cc_isr_lab_eRpL,0,stat_error_AFB_cc_isr_lab_eRpL);
  cc_isr_lab_eRpL->SetMarkerStyle(34);
  cc_isr_lab_eRpL->SetMarkerColor(92);
  cc_isr_lab_eRpL->SetMarkerSize(1);
  cc_isr_lab_eRpL->SetLineWidth(2);
  cc_isr_lab_eRpL->SetLineColor(92);
  cc_isr_lab_eRpL->SetTitle("K_{ISR} > K (lab frame)");
  cc_isr_lab_eRpL->GetXaxis()->SetTitle("K (GeV)");
  cc_isr_lab_eRpL->GetYaxis()->SetTitle("A_{FB}");
  cc_isr_lab_eRpL->GetYaxis()->SetTitleOffset(1);
  cc_isr_lab_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  cc_isr_lab_eRpL->Draw("apl");

      //Add Legend 
   TLegend *cc_isr_lab_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_isr_lab_eRpL_leg->AddEntry(cc_isr_lab_eRpL," c #bar{c}","p");
   //cc_isr_lab_eRpL_leg->SetFillStyle(0);
   cc_isr_lab_eRpL_leg->SetLineWidth(1);
   cc_isr_lab_eRpL_leg->SetLineColor(1);
   cc_isr_lab_eRpL_leg->SetBorderSize(0);
   cc_isr_lab_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);
   
  //cc_isr_com_eRpL
  auto Canvas_AFB_cc_isr_com_eRpL = new TCanvas("Canvas_AFB_cc_isr_com_eRpL","Canvas_AFB_cc_isr_com_eRpL",700,500);
  Canvas_AFB_cc_isr_com_eRpL->SetGrid();
  TGraph *cc_isr_com_eRpL=new TGraphErrors(size,K,AFB_cc_isr_com_eRpL,0,stat_error_AFB_cc_isr_com_eRpL);
  cc_isr_com_eRpL->SetMarkerStyle(34);
  cc_isr_com_eRpL->SetMarkerColor(97);
  cc_isr_com_eRpL->SetMarkerSize(1);
  cc_isr_com_eRpL->SetLineWidth(2);
  cc_isr_com_eRpL->SetLineColor(97);
  cc_isr_com_eRpL->SetTitle("K_{ISR} > K (com frame)");
  cc_isr_com_eRpL->GetXaxis()->SetTitle("K (GeV)");
  cc_isr_com_eRpL->GetYaxis()->SetTitle("A_{FB}");
  cc_isr_com_eRpL->GetYaxis()->SetTitleOffset(1);
  cc_isr_com_eRpL->GetYaxis()->SetRangeUser(-1,+1);
  cc_isr_com_eRpL->Draw("apl");

      //Add Legend 
   TLegend *cc_isr_com_eRpL_leg = new TLegend(0.5,0.3,0.58,0.35);
   cc_isr_com_eRpL_leg->AddEntry(cc_isr_com_eRpL," c #bar{c}","p");
   //cc_isr_com_eRpL_leg->SetFillStyle(0);
   cc_isr_com_eRpL_leg->SetLineWidth(1);
   cc_isr_com_eRpL_leg->SetLineColor(1);
   cc_isr_com_eRpL_leg->SetBorderSize(0);
   cc_isr_com_eRpL_leg->Draw();
   QQBARLabel2(0.005,0.04, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 47 fb^{-1}",kOrange+3);
   
    // auto Canvas_AFB_b_lab = new TCanvas("Canvas_AFB_b_lab","Canvas_AFB_b_lab",700,500);
    // Canvas_AFB_b_lab->SetGrid();
    // auto mg = new TMultiGraph();    
    // mg->Add(b_lab_eLpR);
    // mg->GetXaxis()->SetTitle("K value (GeV)");
    // mg->GetYaxis()->SetTitle("A_{FB}");
    // mg->GetHistogram()->SetTitle("A_{FB} (K_{ISR}<K) - lab");
    // mg->Draw("apl");

    


 
}
