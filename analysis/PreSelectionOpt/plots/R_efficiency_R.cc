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
 
   

  if(pol=="eL")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, XX fb^{-1}",kGray+2);
  if(pol=="eR")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, XX fb^{-1}",kGray+2);

}


// ------------------------------------------------------------
// ------------------------------------------------------------
void R_efficiency_R() {

// Escribo los vectores de las eficiencias:
  double R[]={0.5,0.75,1.0,1.25,1.5};
  double efb[]={}; 
  double efc[]={}; 
  double efq[]={}; 
  double efr[]={}; 

  double Lefb[]={}; 
  double Lefc[]={}; 
  double Lefq[]={}; 
  double Lefr[]={}; 


  double cos90p[]={};
  double cos85p[]={};

  double slopeB[]={};
  double slopeBerror[]={};
  
  double slopeR[]={};
  double slopeRerror[]={};

  double fakexerror[]={0,0,0,0,0};

  double SoB[]={10.0, 9.4, 8.1, 7.0, 6.1};
  double SoBL[]={10.1, 9.6, 8.5, 7.4, 6.5};


  // Plots:
    SetQQbarStyle();
    gStyle->SetOptFit(0); 
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetTitleX(0.2);
     gStyle->SetMarkerSize(1.5);
    
    auto SelectionEfficiency = new TCanvas("SelectionEfficiency","Selection Efficiency",700,500);
    SelectionEfficiency->SetGrid();
    auto mg = new TMultiGraph();
    
    auto gc=new TGraph(7,R,efc);
    gc->SetMarkerStyle(20);
    gc->SetMarkerColor(3);
    gc->SetMarkerSize(1.2);
    gc->SetLineWidth(0);
    gc->SetTitle("c quark");
    auto gb=new TGraph(7,R,efb);
    gb->SetMarkerStyle(22);
    gb->SetMarkerColor(2);
    gb->SetMarkerSize(1.2);
    gb->SetTitle("b quark");
    gb->SetLineWidth(0);
    auto gq=new TGraph(7,R,efq);
    gq->SetMarkerStyle(23);
    gq->SetMarkerColor(4);
    gq->SetMarkerSize(1.2);
    gq->SetLineWidth(0);
    gq->SetTitle("uds quarks");
    
    auto gcL=new TGraph(7,R,Lefc);
    gcL->SetMarkerStyle(24);
    gcL->SetMarkerColor(8);
    gcL->SetMarkerSize(1.2);
    gcL->SetLineWidth(0);
    gcL->SetTitle("c quark");
    auto gbL=new TGraph(7,R,Lefb);
    gbL->SetMarkerStyle(26);
    gbL->SetMarkerColor(6);
    gbL->SetMarkerSize(1.2);
    gbL->SetTitle("b quark");
    gbL->SetLineWidth(0);
    //gbL->Fit("pol1","q");
    auto gqL=new TGraph(7,R,Lefq);
    gqL->SetMarkerStyle(32);
    gqL->SetMarkerColor(9);
    gqL->SetMarkerSize(1.2);
    gqL->SetLineWidth(0);
    gqL->SetTitle("uds quarks");

    mg->Add(gb);
    mg->Add(gc);
    mg->Add(gq);
    mg->Add(gbL);
    mg->Add(gcL);
    mg->Add(gqL);
    
    mg->GetXaxis()->SetTitle("R value");
    mg->GetYaxis()->SetTitle("Efficiency (%)");
    mg->Draw("ap");

    //gPad->BuildLegend();

   gStyle->SetLegendFont(42);
   gStyle->SetLegendTextSize(0.03);
      //Add Legend 
   TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
   //legend->SetHeader("Header","C"); 				// option "C" allows to center the header
   legend->AddEntry(gb,"b quark","p");
   legend->AddEntry(gc,"c quark","p");
   legend->AddEntry(gq,"uds quarks","p");
   legend->AddEntry(gbL,"b quark (|cos#theta|<0.9)","p");
   legend->AddEntry(gcL,"c quark (|cos#theta|<0.9)","p");
   legend->AddEntry(gqL,"uds quarks (|cos#theta|<0.9)","p");
   legend->Draw();


    auto RejectionEfficiency = new TCanvas("RejectionEfficiency","Rejection efficiency",700,500);
    RejectionEfficiency->SetGrid();
    auto mgR = new TMultiGraph();
 
    auto gr=new TGraph(7,R,efr);
    gr->SetMarkerStyle(21);
    gr->SetMarkerColor(2);
    gr->SetMarkerSize(1.2);
    gr->SetLineWidth(0);
    gr->SetTitle("ISR");
    
    auto grL=new TGraph(7,R,Lefr);
    grL->SetMarkerStyle(22);
    grL->SetMarkerColor(3);
    grL->SetMarkerSize(1.2);
    grL->SetLineWidth(0);
    grL->SetTitle("ISR"); 
    
    mgR->Add(gr);
    mgR->Add(grL);

    
    mgR->GetXaxis()->SetTitle("R value");
    mgR->GetYaxis()->SetTitle("Rejection power (%)");
    mgR->Draw("ap");

    //gPad->BuildLegend();

   gStyle->SetLegendFont(42);
   gStyle->SetLegendTextSize(0.03);
      //Add Legend 
   TLegend *legendR = new TLegend(0.1,0.7,0.48,0.9);
   //legendR->SetHeader("Header","C"); 				// option "C" allows to center the header
   
   legendR->AddEntry(gr,"ISR","p");
   legendR->AddEntry(grL,"ISR (|cos#theta|<0.9)","p");
   legendR->Draw();

   
    auto AngularLoss = new TCanvas("AngularLoss","skewness (uds)",700,500);
    AngularLoss->SetGrid();
    auto mg2 = new TMultiGraph();

    auto sb90=new TGraph(7,R,cos90p);
    sb90->SetMarkerStyle(21);
    sb90->SetMarkerColor(4);
    sb90->SetMarkerSize(1.2);
    sb90->SetTitle("90%");
    sb90->SetLineWidth(0);

    auto sb85=new TGraph(7,R,cos85p);
    sb85->SetMarkerStyle(22);
    sb85->SetMarkerColor(2);
    sb85->SetMarkerSize(1.2);
    sb85->SetTitle("85%");
    sb85->SetLineWidth(0);
     
    mg2->Add(sb90);
    mg2->Add(sb85);
    
    mg2->GetXaxis()->SetTitle("R value");
    mg2->GetYaxis()->SetTitle("|cos#theta|");
    mg2->Draw("ap");
    
    TLegend *legend2 = new TLegend(0.1,0.7,0.48,0.9);
    legend2->AddEntry(sb90,"90% of max. efficiency","p");
    legend2->AddEntry(sb85,"85% of max. efficiency","p");
    legend2->Draw();


    auto slopes = new TCanvas("slopes","slopes",700,500);
    slopes->SetGrid();
     
    auto slpB =new TGraphErrors(7,R,slopeB, fakexerror, slopeBerror);
    slpB->SetMarkerStyle(21);
    slpB->SetMarkerColor(4);
    slpB->SetMarkerSize(1.2);
    slpB->SetTitle("B quark");
    //slpB->SetLineWidth(0);

    auto slpR =new TGraphErrors(7,R,slopeR, fakexerror, slopeRerror);
    slpR->SetMarkerStyle(22);
    slpR->SetMarkerColor(2);
    slpR->SetMarkerSize(1.2);
    slpR->SetTitle("Radiative Return");
    //slpR->SetLineWidth(0);
        
     
    auto mg3 = new TMultiGraph();
    mg3->Add(slpB);
    mg3->Add(slpR);
    mg3->GetXaxis()->SetTitle("R value");
    mg3->GetYaxis()->SetTitle("slope");
    mg3->Draw("ap");
    
    TLegend *legend3 = new TLegend(0.1,0.7,0.48,0.9);
    legend3->AddEntry(slpB,"B quark","p");
    legend3->AddEntry(slpR,"Radiative Return","p");
    legend3->Draw();


    auto SignalBackground = new TCanvas("SignalBackground","Signal/Background",700,500);
    SignalBackground->SetGrid();
    auto mg4 = new TMultiGraph();

    auto sob =new TGraph(5,R,SoB);
    sob->SetMarkerStyle(21);
    sob->SetMarkerColor(4);
    sob->SetMarkerSize(1.2);
    sob->SetTitle("B quark");
    sob->SetLineWidth(0);

    auto sobL =new TGraph(5,R,SoBL);
    sobL->SetMarkerStyle(22);
    sobL->SetMarkerColor(2);
    sobL->SetMarkerSize(1.2);
    sobL->SetTitle("Radiative Return");
    sobL->SetLineWidth(0);
        
     
    mg4->Add(sob);
    mg4->Add(sobL);
    
    mg4->GetXaxis()->SetTitle("R value");
    mg4->GetYaxis()->SetTitle("Signal/Background");
    mg4->Draw("ap");
    
    TLegend *legend4 = new TLegend(0.1,0.7,0.48,0.9);
    legend4->AddEntry(sob,"Signal/Background (total)","p");
    legend4->AddEntry(sobL,"Signal/Background (|cos#theta|<0.9)","p");
    legend4->Draw();

 
}
