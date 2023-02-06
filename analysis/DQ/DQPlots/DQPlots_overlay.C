#include "DQPlots.h"


void DQPlots_overlay(TString file) {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(1.5);

  TString folder="./";
  
  //TString file="../DQ_250GeV_15162.root";

  std::vector<TString> leg;
  leg.push_back("'signal' PFOs");
  leg.push_back("+ISR");
  leg.push_back("+Overlay");

  
  //Nreco
  std::vector<TH1F *> histos_Nreco_rad;
  histos_Nreco_rad.push_back(getHisto("reco",file,"PFO_njet_rad"));
  histos_Nreco_rad.push_back(getHisto("reco",file,"PFOisr_njet_rad"));
  histos_Nreco_rad.push_back(getHisto("reco",file,"PFOoverlay_njet_rad"));

  Compare_3Histos("N-PFOs, RadReturn",histos_Nreco_rad,true,leg);

  /*
  TCanvas *canvas_rad=new TCanvas("canvas_rad","canvas_rad",600,600);
  canvas_rad->cd(1);
  histos_Nreco_rad.at(0)->Draw("histosame");
  */

  //Nreco_
  std::vector<TH1F *> histos_Nreco_signal;
  histos_Nreco_signal.push_back(getHisto("reco",file,"PFO_njet_signal"));
  histos_Nreco_signal.push_back(getHisto("reco",file,"PFOisr_njet_signal"));
  histos_Nreco_signal.push_back(getHisto("reco",file,"PFOoverlay_njet_signal"));

  Compare_3Histos("N-PFOs, signal",histos_Nreco_signal,true,leg);

  std::vector<TString> leg1;
  leg1.push_back("ALL PFOs");
  leg1.push_back("ISR");
  leg1.push_back("Overlay");

  //Nreco_all
  //Nreco_                                                                                                            
  std::vector<TH1F *> histos_Nreco_all;
  histos_Nreco_all.push_back(getHisto("reco",file,"PFO_njet_all"));
  histos_Nreco_all.push_back(getHisto("reco",file,"PFOisr_njet_all"));
  histos_Nreco_all.push_back(getHisto("reco",file,"PFOoverlay_njet_all"));

  Compare_3Histos("N-PFOs, all",histos_Nreco_all,true,leg);

  std::vector<TString> leg2;
  leg2.push_back("ALL PFOs");
  leg2.push_back("ISR");
  leg2.push_back("Overlay");
  
  //momentum PFOs
  std::vector<TH1F *> histos_mom_rad;
  histos_mom_rad.push_back(getHisto("reco",file,"PFO_mom_rad"));
  histos_mom_rad.push_back(getHisto("reco",file,"PFOisr_mom_rad"));
  histos_mom_rad.push_back(getHisto("reco",file,"PFOoverlay_mom_rad"));

  Compare_3Histos2Stack("p_[PFO] RadRet",histos_mom_rad,leg1);

  //mom
  std::vector<TH1F *> histos_mom_signal;
  histos_mom_signal.push_back(getHisto("reco",file,"PFO_mom_signal"));
  histos_mom_signal.push_back(getHisto("reco",file,"PFOisr_mom_signal"));
  histos_mom_signal.push_back(getHisto("reco",file,"PFOoverlay_mom_signal"));

  Compare_3Histos2Stack("p_[PFO] signal",histos_mom_signal,leg1);
  
  std::vector<TH1F *> histos_mom_all;
  histos_mom_all.push_back(getHisto("reco",file,"PFO_mom_all"));
  histos_mom_all.push_back(getHisto("reco",file,"PFOisr_mom_all"));
  histos_mom_all.push_back(getHisto("reco",file,"PFOoverlay_mom_all"));

  Compare_3Histos2Stack("p_[PFO] all",histos_mom_all,leg1);  
}
