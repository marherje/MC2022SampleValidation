#include <TPaveStats.h>
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
#include "../../../style/Style.C"
#include "../../../style/Labels.C"




void Labels(TString pol){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eL")
    QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
  else 
    if(pol=="eR")
      QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
    else 
      QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow q#bar{q} mc-2020",kGray+2);

  //QQBARLabel2(0.2,0.22, "Secondary Tracks in c-jets",kGray+4);

}


void JetTag_Comparison(int cut,TString kvalue) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString cutname=TString::Format("cuts%i",cut);
  TString filename = "../results/jettag_"+cutname+"_2f_hadronic_sample_eL_pR_"+kvalue+"_500GeV.root";
  TFile *f = new TFile(filename);
  TH1F*  btag[40][2];
  TH1F*  ctag[40][2];
  for(int i=0; i<40; i++) {
    btag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_ctag_%i",i));
  }

  TString filename2 = "../results/jettag_"+cutname+"_2f_hadronic_sample_eR_pL_"+kvalue+"_500GeV.root";
  TFile *f2 = new TFile(filename2);

  for(int i=0; i<40; i++) {
    btag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_ctag_%i",i));
  }

  float x[40], eff_b[2][3][40], eff_c[2][3][40];
  float eff2_b[2][3][40], eff2_c[2][3][40];
  float pur_b[2][40], pur_c[2][40];

  float eff_b_error[2][3][40], eff_c_error[2][3][40];
  float pur_b_error[2][40], pur_c_error[2][40], pur_b_error2[2][40], pur_c_error2[2][40];

  int n=0;
  for(int i=0;i<40; i++) {
    x[i]=i*0.025;
    float ntotal[3];
    float nb[3];
    float nc[3];
    
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;

      for(int ipol=0; ipol<2; ipol++){
	ntotal[iflav]=btag[0][ipol]->GetBinContent(quark+1);
	
	nb[iflav]=btag[i][ipol]->GetBinContent(quark+1);
	nc[iflav]=ctag[i][ipol]->GetBinContent(quark+1);

	eff_b[ipol][iflav][i]=100.*nb[iflav]/ntotal[iflav];
	eff_c[ipol][iflav][i]=100.*nc[iflav]/ntotal[iflav];
	eff2_b[ipol][iflav][i]=100.-100.*nb[iflav]/ntotal[iflav];
	eff2_c[ipol][iflav][i]=100.-100.*nc[iflav]/ntotal[iflav];

	eff_b_error[ipol][iflav][i]=(100./ntotal[iflav])*pow(nb[iflav]+(nb[iflav]*nb[iflav])/ntotal[iflav],0.5);
	eff_c_error[ipol][iflav][i]=(100./ntotal[iflav])*pow(nc[iflav]+(nc[iflav]*nc[iflav])/ntotal[iflav],0.5);
      }
    }
    // ev_mal/ev_bien
    for(int ipol=0; ipol<2; ipol++){
      pur_b[ipol][i]=100*(eff_b[ipol][0][i]+eff_b[ipol][1][i])/(eff_b[ipol][2][i]+eff_b[ipol][1][i]+eff_b[ipol][0][i]);
      pur_c[ipol][i]=100*(eff_c[ipol][0][i]+eff_c[ipol][2][i])/(eff_c[ipol][2][i]+eff_c[ipol][1][i]+eff_c[ipol][0][i]);

      pur_b_error2[ipol][i]=pow((eff_b[ipol][0][i]+eff_b[ipol][1][i])/(pow(eff_b[ipol][0][i]+eff_b[ipol][1][i]+eff_b[ipol][2][i],2)),2)*eff_b_error[ipol][2][i]*eff_b_error[ipol][2][i]+
	pow(eff_b[ipol][1][i]/(pow(eff_b[ipol][0][i]+eff_b[ipol][1][i]+eff_b[ipol][2][i],2)),2)*eff_b_error[ipol][1][i]*eff_b_error[ipol][1][i]+
				 pow(eff_b[ipol][0][i]/(pow(eff_b[ipol][0][i]+eff_b[ipol][1][i]+eff_b[ipol][2][i],2)),2)*eff_b_error[ipol][0][i]*eff_b_error[ipol][0][i];
      pur_b_error[ipol][i]=100*pow(pur_b_error2[ipol][i],0.5);
  
      pur_c_error2[ipol][i]=pow((eff_c[ipol][0][i]+eff_c[ipol][2][i])/(pow(eff_c[ipol][0][i]+eff_c[ipol][1][i]+eff_c[ipol][2][i],2)),2)*eff_c_error[ipol][1][i]*eff_c_error[ipol][1][i]+
	pow(eff_c[ipol][2][i]/(pow(eff_c[ipol][0][i]+eff_c[ipol][1][i]+eff_c[ipol][2][i],2)),2)*eff_c_error[ipol][2][i]*eff_c_error[ipol][2][i]+
	pow(eff_c[ipol][0][i]/(pow(eff_c[ipol][0][i]+eff_c[ipol][1][i]+eff_c[ipol][2][i],2)),2)*eff_c_error[ipol][0][i]*eff_c_error[ipol][0][i];
      pur_c_error[ipol][i]=100*pow(pur_c_error2[ipol][i],0.5);
    }
    
    n++;
  }
	
  TGraph* puroveref_b_eL=new TGraphErrors(n,eff_b[0][2],pur_b[0],eff_b_error[0][2],pur_b_error[0]);
  TGraph* puroveref_c_eL=new TGraphErrors(n,eff_c[0][1],pur_c[0],eff_c_error[0][1],pur_c_error[0]);
  TGraph* puroveref_b_eR=new TGraphErrors(n,eff_b[1][2],pur_b[1],eff_b_error[1][2],pur_b_error[1]);
  TGraph* puroveref_c_eR=new TGraphErrors(n,eff_c[1][1],pur_c[1],eff_c_error[1][1],pur_c_error[1]);
      


  
  TGraph* efficiency_b_b_eL = new TGraphErrors(n,x,eff_b[0][2],0,eff_b_error[0][2]);
  TGraph* efficiency_c_b_eL = new TGraphErrors(n,x,eff2_b[0][1],0,eff_b_error[0][1]);
  TGraph* efficiency_uds_b_eL = new TGraphErrors(n,x,eff2_b[0][0],0,eff_b_error[0][0]);

  TGraph* efficiency_b_b_eR = new TGraphErrors(n,x,eff_b[1][2],0,eff_b_error[1][2]);
  TGraph* efficiency_c_b_eR = new TGraphErrors(n,x,eff2_b[1][1],0,eff_b_error[1][1]);
  TGraph* efficiency_uds_b_eR = new TGraphErrors(n,x,eff2_b[1][0],0,eff_b_error[1][0]);

  TCanvas* c_eff_b = new TCanvas("c_eff_b","c_eff_b",800,800);
  c_eff_b->cd(1);
  c_eff_b->SetGrid();
  efficiency_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  efficiency_b_b_eL->GetYaxis()->SetTitle("[%]");
  efficiency_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_b_b_eL->GetYaxis()->SetRangeUser(0,100);

  efficiency_b_b_eL->SetLineColor(4);
  efficiency_b_b_eL->SetLineWidth(2);
  efficiency_b_b_eL->SetLineStyle(1);
  efficiency_b_b_eL->Draw("alp");

  efficiency_c_b_eL->SetLineColor(1);
  efficiency_c_b_eL->SetLineWidth(2);
  efficiency_c_b_eL->SetLineStyle(1);
  efficiency_c_b_eL->Draw("lp");

  efficiency_uds_b_eL->SetLineColor(2);
  efficiency_uds_b_eL->SetLineWidth(2);
  efficiency_uds_b_eL->SetLineStyle(1);
  efficiency_uds_b_eL->Draw("lp");

  efficiency_b_b_eR->SetLineColor(4);
  efficiency_b_b_eR->SetLineWidth(3);
  efficiency_b_b_eR->SetLineStyle(2);
  efficiency_b_b_eR->Draw("lp");

  efficiency_c_b_eR->SetLineColor(1);
  efficiency_c_b_eR->SetLineWidth(3);
  efficiency_c_b_eR->SetLineStyle(2);
  efficiency_c_b_eR->Draw("lp");

  efficiency_uds_b_eR->SetLineColor(2);
  efficiency_uds_b_eR->SetLineWidth(3);
  efficiency_uds_b_eR->SetLineStyle(2);
  efficiency_uds_b_eR->Draw("lp");
  
  
  //Labels("");
  
  TLegend *leg_b = new TLegend(0.4,0.25,0.6,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(efficiency_b_b_eL,"#varepsilon_{b}","lp");
  leg_b->AddEntry(efficiency_c_b_eL,"1-#varepsilon_{c}","lp");
  leg_b->AddEntry(efficiency_uds_b_eL,"1-#varepsilon_{uds}","lp");
  leg_b->AddEntry(efficiency_c_b_eL,"Left Pol","lp");
  leg_b->AddEntry(efficiency_c_b_eR,"Right Pol","lp");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  //c_eff_b->SaveAs("c_eff_b.png");

  ///---------------------------------------------
  TGraph* efficiency_c_c_eL = new TGraphErrors(n,x,eff_c[0][1],0,eff_c_error[0][1]);
  TGraph* efficiency_b_c_eL = new TGraphErrors(n,x,eff2_c[0][2],0,eff_c_error[0][2]);
  TGraph* efficiency_uds_c_eL = new TGraphErrors(n,x,eff2_c[0][0],0,eff_c_error[0][0]);

  TGraph* efficiency_c_c_eR = new TGraphErrors(n,x,eff_c[1][1],0,eff_c_error[1][1]);
  TGraph* efficiency_b_c_eR = new TGraphErrors(n,x,eff2_c[1][2],0,eff_c_error[1][2]);
  TGraph* efficiency_uds_c_eR = new TGraphErrors(n,x,eff2_c[1][0],0,eff_c_error[1][0]);

  TCanvas* c_eff_c = new TCanvas("c_eff_c","c_eff_c",800,800);
  c_eff_c->cd(1);
  c_eff_c->SetGrid();
  efficiency_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  efficiency_c_c_eL->GetYaxis()->SetTitle("[%]");
  efficiency_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_c_c_eL->GetYaxis()->SetRangeUser(0,100);

  efficiency_c_c_eL->SetLineColor(4);
  efficiency_c_c_eL->SetLineWidth(2);
  efficiency_c_c_eL->SetLineStyle(1);
  efficiency_c_c_eL->Draw("alp");

  efficiency_b_c_eL->SetLineColor(1);
  efficiency_b_c_eL->SetLineWidth(2);
  efficiency_b_c_eL->SetLineStyle(1);
  efficiency_b_c_eL->Draw("lp");

  efficiency_uds_c_eL->SetLineColor(2);
  efficiency_uds_c_eL->SetLineWidth(2);
  efficiency_uds_c_eL->SetLineStyle(1);
  efficiency_uds_c_eL->Draw("lp");

  efficiency_c_c_eR->SetLineColor(4);
  efficiency_c_c_eR->SetLineWidth(3);
  efficiency_c_c_eR->SetLineStyle(2);
  efficiency_c_c_eR->Draw("lp");

  efficiency_b_c_eR->SetLineColor(1);
  efficiency_b_c_eR->SetLineWidth(3);
  efficiency_b_c_eR->SetLineStyle(2);
  efficiency_b_c_eR->Draw("lp");

  efficiency_uds_c_eR->SetLineColor(2);
  efficiency_uds_c_eR->SetLineWidth(3);
  efficiency_uds_c_eR->SetLineStyle(2);
  efficiency_uds_c_eR->Draw("lp");
  
  
  //Labels("");
  
  TLegend *leg_c = new TLegend(0.4,0.25,0.6,0.45);
  leg_c->SetTextSize(0.035);
  leg_c->SetTextFont(42);
  leg_c->AddEntry(efficiency_c_c_eL,"#varepsilon_{c}","lp");
  leg_c->AddEntry(efficiency_b_c_eL,"1-#varepsilon_{b}","lp");
  leg_c->AddEntry(efficiency_uds_c_eL,"1-#varepsilon_{uds}","lp");
  leg_c->AddEntry(efficiency_b_c_eL,"Left Pol","lp");
  leg_c->AddEntry(efficiency_b_c_eR,"Right Pol","lp");
  leg_c->SetFillColor(0);
  leg_c->SetLineColor(0);
  leg_c->SetShadowColor(0);
  leg_c->Draw();

  
  //c_eff_c->SaveAs("c_eff_c.png");


  //----------------------------------------
  //Retraining
  //----------------------------------------



  TString cutnameR=TString::Format("cuts%i",cut);
  TString filenameR = "../Retraining_Results/jettag_"+cutname+"_"+"2f250"+"_eL_pR_"+kvalue+"_500GeV.root";
  TFile *fR = new TFile(filenameR);
  TH1F*  btagR[40][2];
  TH1F*  ctagR[40][2];
  for(int i=0; i<40; i++) {
    btagR[i][0]= (TH1F*)fR->Get(TString::Format("h_jet_btag_%i",i));
    ctagR[i][0]= (TH1F*)fR->Get(TString::Format("h_jet_ctag_%i",i));
  }

  TString filenameR2 = "../Retraining_Results/jettag_"+cutname+"_"+"2f250"+"_eR_pL_"+kvalue+"_500GeV.root";
  TFile *fR2 = new TFile(filenameR2);

  for(int i=0; i<40; i++) {
    btagR[i][1]= (TH1F*)fR2->Get(TString::Format("h_jet_btag_%i",i));
    ctagR[i][1]= (TH1F*)fR2->Get(TString::Format("h_jet_ctag_%i",i));
  }

  float xR[40], eff_bR[2][3][40], eff_cR[2][3][40];
  float eff2_bR[2][3][40], eff2_cR[2][3][40];
  float pur_bR[2][40], pur_cR[2][40];

  float eff_bR_error[2][3][40], eff_cR_error[2][3][40];
  float pur_bR_error[2][40], pur_cR_error[2][40], pur_bR_error2[2][40], pur_cR_error2[2][40];


  int nR=0;
  for(int i=0;i<40; i++) {
    xR[i]=i*0.025;
    float ntotalR[3];
    float nbR[3];
    float ncR[3];
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;

      for(int ipol=0; ipol<2; ipol++){
	ntotalR[iflav]=btagR[0][ipol]->GetBinContent(quark+1);
	
	nbR[iflav]=btagR[i][ipol]->GetBinContent(quark+1);
	ncR[iflav]=ctagR[i][ipol]->GetBinContent(quark+1);

	eff_bR[ipol][iflav][i]=100.*nbR[iflav]/ntotalR[iflav];
	eff_cR[ipol][iflav][i]=100.*ncR[iflav]/ntotalR[iflav];
	eff2_bR[ipol][iflav][i]=100.-100.*nbR[iflav]/ntotalR[iflav];
	eff2_cR[ipol][iflav][i]=100.-100.*ncR[iflav]/ntotalR[iflav];
	
	eff_bR_error[ipol][iflav][i]=(100./ntotalR[iflav])*pow(nbR[iflav]+(nbR[iflav]*nbR[iflav])/ntotalR[iflav],0.5);
	eff_cR_error[ipol][iflav][i]=(100./ntotalR[iflav])*pow(ncR[iflav]+(ncR[iflav]*ncR[iflav])/ntotalR[iflav],0.5);
      }
    }

    for(int ipol=0; ipol<2; ipol++){

      pur_bR[ipol][i]=100*(eff_bR[ipol][0][i]+eff_bR[ipol][1][i])/(eff_bR[ipol][2][i]+eff_bR[ipol][1][i]+eff_bR[ipol][0][i]);
      pur_cR[ipol][i]=100*(eff_cR[ipol][0][i]+eff_cR[ipol][2][i])/(eff_cR[ipol][2][i]+eff_cR[ipol][1][i]+eff_cR[ipol][0][i]);

      
      pur_bR_error2[ipol][i]=pow((eff_bR[ipol][0][i]+eff_bR[ipol][1][i])/(pow(eff_bR[ipol][0][i]+eff_bR[ipol][1][i]+eff_bR[ipol][2][i],2)),2)*eff_bR_error[ipol][2][i]*eff_bR_error[ipol][2][i]+
	pow(eff_bR[ipol][1][i]/(pow(eff_bR[ipol][0][i]+eff_bR[ipol][1][i]+eff_bR[ipol][2][i],2)),2)*eff_bR_error[ipol][1][i]*eff_bR_error[ipol][1][i]+
	pow(eff_bR[ipol][0][i]/(pow(eff_bR[ipol][0][i]+eff_bR[ipol][1][i]+eff_bR[ipol][2][i],2)),2)*eff_bR_error[ipol][0][i]*eff_bR_error[ipol][0][i];
      pur_bR_error[ipol][i]=100*pow(pur_bR_error2[ipol][i],0.5);

      
      pur_cR_error2[ipol][i]=pow((eff_cR[ipol][0][i]+eff_cR[ipol][2][i])/(pow(eff_cR[ipol][0][i]+eff_cR[ipol][1][i]+eff_cR[ipol][2][i],2)),2)*eff_cR_error[ipol][1][i]*eff_cR_error[ipol][1][i]+
	pow(eff_cR[ipol][2][i]/(pow(eff_cR[ipol][0][i]+eff_cR[ipol][1][i]+eff_cR[ipol][2][i],2)),2)*eff_cR_error[ipol][2][i]*eff_cR_error[ipol][2][i]+
	pow(eff_cR[ipol][0][i]/(pow(eff_cR[ipol][0][i]+eff_cR[ipol][1][i]+eff_cR[ipol][2][i],2)),2)*eff_cR_error[ipol][0][i]*eff_cR_error[ipol][0][i];
      pur_cR_error[ipol][i]=100*pow(pur_cR_error2[ipol][i],0.5);
    }
    
    nR++;
  }
	
  TGraph* Rpuroveref_b_eL=new TGraphErrors(n,eff_bR[0][2],pur_bR[0],eff_bR_error[0][2],pur_bR_error[0]);
  TGraph* Rpuroveref_c_eL=new TGraphErrors(n,eff_cR[0][1],pur_cR[0],eff_cR_error[0][1],pur_cR_error[0]);
  TGraph* Rpuroveref_b_eR=new TGraphErrors(n,eff_bR[1][2],pur_bR[1],eff_bR_error[1][2],pur_bR_error[1]);
  TGraph* Rpuroveref_c_eR=new TGraphErrors(n,eff_cR[1][1],pur_cR[1],eff_cR_error[1][1],pur_cR_error[1]);
  
  TGraph* Refficiency_b_b_eL = new TGraphErrors(n,x,eff_bR[0][2],0,eff_bR_error[0][2]);
  TGraph* Refficiency_c_b_eL = new TGraphErrors(n,x,eff2_bR[0][1],0,eff_bR_error[0][1]);
  TGraph* Refficiency_uds_b_eL = new TGraphErrors(n,x,eff2_bR[0][0],0,eff_bR_error[0][0]);

  TGraph* Refficiency_b_b_eR = new TGraphErrors(n,x,eff_bR[1][2],0,eff_bR_error[1][2]);
  TGraph* Refficiency_c_b_eR = new TGraphErrors(n,x,eff2_bR[1][1],0,eff_bR_error[1][1]);
  TGraph* Refficiency_uds_b_eR = new TGraphErrors(n,x,eff2_bR[1][0],0,eff_bR_error[1][0]);

  TCanvas* c_eff_bR = new TCanvas("c_eff_bR","c_eff_bR",800,800);
  c_eff_bR->cd(1);
  c_eff_bR->SetGrid();
  Refficiency_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  Refficiency_b_b_eL->GetYaxis()->SetTitle("[%]");
  Refficiency_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  Refficiency_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  Refficiency_b_b_eL->GetYaxis()->SetRangeUser(0,100);

  Refficiency_b_b_eL->SetLineColor(4);
  Refficiency_b_b_eL->SetLineWidth(2);
  Refficiency_b_b_eL->SetLineStyle(1);
  Refficiency_b_b_eL->Draw("alp");

  Refficiency_c_b_eL->SetLineColor(1);
  Refficiency_c_b_eL->SetLineWidth(2);
  Refficiency_c_b_eL->SetLineStyle(1);
  Refficiency_c_b_eL->Draw("lp");

  Refficiency_uds_b_eL->SetLineColor(2);
  Refficiency_uds_b_eL->SetLineWidth(2);
  Refficiency_uds_b_eL->SetLineStyle(1);
  Refficiency_uds_b_eL->Draw("lp");

  Refficiency_b_b_eR->SetLineColor(4);
  Refficiency_b_b_eR->SetLineWidth(3);
  Refficiency_b_b_eR->SetLineStyle(2);
  Refficiency_b_b_eR->Draw("lp");

  Refficiency_c_b_eR->SetLineColor(1);
  Refficiency_c_b_eR->SetLineWidth(3);
  Refficiency_c_b_eR->SetLineStyle(2);
  Refficiency_c_b_eR->Draw("lp");

  Refficiency_uds_b_eR->SetLineColor(2);
  Refficiency_uds_b_eR->SetLineWidth(3);
  Refficiency_uds_b_eR->SetLineStyle(2);
  Refficiency_uds_b_eR->Draw("lp");
  
  
  //Labels("");
  
  TLegend *leg_bR = new TLegend(0.4,0.25,0.6,0.45);
  leg_bR->SetTextSize(0.035);
  leg_bR->SetTextFont(42);
  leg_bR->AddEntry(efficiency_b_b_eL,"#varepsilon_{b}","lp");
  leg_bR->AddEntry(efficiency_c_b_eL,"1-#varepsilon_{c}","lp");
  leg_bR->AddEntry(efficiency_uds_b_eL,"1-#varepsilon_{uds}","lp");
  leg_bR->AddEntry(efficiency_c_b_eL,"Left Pol","lp");
  leg_bR->AddEntry(efficiency_c_b_eR,"Right Pol","lp");
  leg_bR->SetFillColor(0);
  leg_bR->SetLineColor(0);
  leg_bR->SetShadowColor(0);
  leg_bR->Draw();

  //c_eff_bR->SaveAs("c_eff_bR.png");

  ///---------------------------------------------
  TGraph* Refficiency_c_c_eL = new TGraphErrors(n,x,eff_cR[0][1],0,eff_cR_error[0][1]);
  TGraph* Refficiency_b_c_eL = new TGraphErrors(n,x,eff2_cR[0][2],0,eff_cR_error[0][2]);
  TGraph* Refficiency_uds_c_eL = new TGraphErrors(n,x,eff2_cR[0][0],0,eff_cR_error[0][0]);

  TGraph* Refficiency_c_c_eR = new TGraphErrors(n,x,eff_cR[1][1],0,eff_cR_error[1][1]);
  TGraph* Refficiency_b_c_eR = new TGraphErrors(n,x,eff2_cR[1][2],0,eff_cR_error[1][2]);
  TGraph* Refficiency_uds_c_eR = new TGraphErrors(n,x,eff2_cR[1][0],0,eff_cR_error[1][0]);

  TCanvas* c_eff_cR = new TCanvas("c_eff_cR","c_eff_cR",800,800);
  c_eff_cR->cd(1);
  c_eff_cR->SetGrid();
  Refficiency_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  Refficiency_c_c_eL->GetYaxis()->SetTitle("[%]");
  Refficiency_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  Refficiency_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  Refficiency_c_c_eL->GetYaxis()->SetRangeUser(0,100);

  Refficiency_c_c_eL->SetLineColor(4);
  Refficiency_c_c_eL->SetLineWidth(2);
  Refficiency_c_c_eL->SetLineStyle(1);
  Refficiency_c_c_eL->Draw("alp");

  Refficiency_b_c_eL->SetLineColor(1);
  Refficiency_b_c_eL->SetLineWidth(2);
  Refficiency_b_c_eL->SetLineStyle(1);
  Refficiency_b_c_eL->Draw("lp");

  Refficiency_uds_c_eL->SetLineColor(2);
  Refficiency_uds_c_eL->SetLineWidth(2);
  Refficiency_uds_c_eL->SetLineStyle(1);
  Refficiency_uds_c_eL->Draw("lp");

  Refficiency_c_c_eR->SetLineColor(4);
  Refficiency_c_c_eR->SetLineWidth(3);
  Refficiency_c_c_eR->SetLineStyle(2);
  Refficiency_c_c_eR->Draw("lp");

  Refficiency_b_c_eR->SetLineColor(1);
  Refficiency_b_c_eR->SetLineWidth(3);
  Refficiency_b_c_eR->SetLineStyle(2);
  Refficiency_b_c_eR->Draw("lp");

  Refficiency_uds_c_eR->SetLineColor(2);
  Refficiency_uds_c_eR->SetLineWidth(3);
  Refficiency_uds_c_eR->SetLineStyle(2);
  Refficiency_uds_c_eR->Draw("lp");
  
  
  //Labels("");
  
  TLegend *leg_cR = new TLegend(0.4,0.25,0.6,0.45);
  leg_cR->SetTextSize(0.035);
  leg_cR->SetTextFont(42);
  leg_cR->AddEntry(efficiency_c_c_eL,"#varepsilon_{c}","lp");
  leg_cR->AddEntry(efficiency_b_c_eL,"1-#varepsilon_{b}","lp");
  leg_cR->AddEntry(efficiency_uds_c_eL,"1-#varepsilon_{uds}","lp");
  leg_cR->AddEntry(efficiency_b_c_eL,"Left Pol","lp");
  leg_cR->AddEntry(efficiency_b_c_eR,"Right Pol","lp");
  leg_cR->SetFillColor(0);
  leg_cR->SetLineColor(0);
  leg_cR->SetShadowColor(0);
  leg_cR->Draw();

  
  //c_eff_cR->SaveAs("c_eff_cR.png");



  TCanvas* pur_over_ef_b = new TCanvas("pur_over_ef_b","pur_over_ef_b",800,800);
  pur_over_ef_b->cd(1);
  pur_over_ef_b->SetGrid();
  puroveref_b_eL->GetXaxis()->SetTitle("ef_{b} (%)");
  puroveref_b_eL->GetYaxis()->SetTitle("100 - purity (%)");
  puroveref_b_eL->GetYaxis()->SetTitleOffset(1.25);
  puroveref_b_eL->GetXaxis()->SetTitleOffset(1.);
  puroveref_b_eL->GetYaxis()->SetRangeUser(0,100);
  puroveref_b_eL->SetLineColor(4);
  puroveref_b_eL->SetLineWidth(2);
  puroveref_b_eL->SetLineStyle(1);
  puroveref_b_eL->Draw("alp");
  Rpuroveref_b_eL->SetLineColor(4);
  Rpuroveref_b_eL->SetLineWidth(2);
  Rpuroveref_b_eL->SetLineStyle(2);
  Rpuroveref_b_eL->Draw("same");
  puroveref_b_eR->SetLineColor(2);
  puroveref_b_eR->SetLineWidth(2);
  puroveref_b_eR->SetLineStyle(1);
  puroveref_b_eR->Draw("same");
  Rpuroveref_b_eR->SetLineColor(2);
  Rpuroveref_b_eR->SetLineWidth(2);
  Rpuroveref_b_eR->SetLineStyle(2);
  Rpuroveref_b_eR->Draw("same");
  
  TLegend *leg_poef_b = new TLegend(0.2,0.45,0.6,0.65);
  leg_poef_b->SetTextSize(0.025);
  leg_poef_b->SetTextFont(42);
  leg_poef_b->AddEntry(puroveref_b_eL,"b-tag e^{-}_{L}e^{+}_{R} (old)","lp");
  leg_poef_b->AddEntry(Rpuroveref_b_eL,"b-tag e^{-}_{L}e^{+}_{R} (Re-Training)","lp");
  leg_poef_b->AddEntry(puroveref_b_eR,"b-tag e^{-}_{R}e^{+}_{L} (old)","lp");
  leg_poef_b->AddEntry(Rpuroveref_b_eR,"b-tag e^{-}_{R}e^{+}_{L} (Re-Training)","lp");
  leg_poef_b->SetFillColor(0);
  leg_poef_b->SetLineColor(0);
  leg_poef_b->SetShadowColor(0);
  leg_poef_b->Draw();

  
  TCanvas* pur_over_ef_c = new TCanvas("pur_over_ef_c","pur_over_ef_c",800,800);
  pur_over_ef_c->cd(1);
  pur_over_ef_c->SetGrid();
  puroveref_c_eL->GetXaxis()->SetTitle("ef_{c} (%)");
  puroveref_c_eL->GetYaxis()->SetTitle("100 - purity (%)");
  puroveref_c_eL->GetYaxis()->SetTitleOffset(1.25);
  puroveref_c_eL->GetXaxis()->SetTitleOffset(1.);
  puroveref_c_eL->GetYaxis()->SetRangeUser(0,100);
  puroveref_c_eL->SetLineColor(4);
  puroveref_c_eL->SetLineWidth(2);
  puroveref_c_eL->SetLineStyle(1);
  puroveref_c_eL->Draw("alp");
  Rpuroveref_c_eL->SetLineColor(4);
  Rpuroveref_c_eL->SetLineWidth(2);
  Rpuroveref_c_eL->SetLineStyle(2);
  Rpuroveref_c_eL->Draw("same");
  puroveref_c_eR->SetLineColor(2);
  puroveref_c_eR->SetLineWidth(2);
  puroveref_c_eR->SetLineStyle(1);
  puroveref_c_eR->Draw("same");
  Rpuroveref_c_eR->SetLineColor(2);
  Rpuroveref_c_eR->SetLineWidth(2);
  Rpuroveref_c_eR->SetLineStyle(2);
  Rpuroveref_c_eR->Draw("same");
  
  TLegend *leg_poef_c = new TLegend(0.2,0.45,0.6,0.65);
  leg_poef_c->SetTextSize(0.025);
  leg_poef_c->SetTextFont(42);
  leg_poef_c->AddEntry(puroveref_c_eL,"c-tag e^{-}_{L}e^{+}_{R} (old)","lp");
  leg_poef_c->AddEntry(Rpuroveref_c_eL,"c-tag e^{-}_{L}e^{+}_{R} (Re-Training)","lp");
  leg_poef_c->AddEntry(puroveref_c_eR,"c-tag e^{-}_{R}e^{+}_{L} (old)","lp");
  leg_poef_c->AddEntry(Rpuroveref_c_eR,"c-tag e^{-}_{R}e^{+}_{L} (Re-Training)","lp");
  leg_poef_c->SetFillColor(0);
  leg_poef_c->SetLineColor(0);
  leg_poef_c->SetShadowColor(0);
  leg_poef_c->Draw();
}
