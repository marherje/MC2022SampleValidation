#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_jettag_new(int G, int R, TString pol, int type, float Kv){
  int bkg=0;
  int selection_type=type;
  TString process="2f_hadronic_NEW_sample_";
  TString s_type=TString::Format("cuts%i_",type);
  TString kvalue=TString::Format("_Kgamma%i",int(Kv));
  
  //TString fileaux1=TString::Format("../../../../Data/ntuples/1/%i", int(G));
  //TString fileaux2=TString::Format("/%i/", int(R));
  //TString file = fileaux1+fileaux2+process+pol+".root";
  
  TString file = "../../../500GeV_NewNTuples2022/"+pol+"_500GeV_NewSamples.root";
  
  QQbarAnalysisClass ss3(file);
  ss3.process=s_type+process+pol+"_"+Kv;

  ss3.JetTag(-1,type,Kv);
  gSystem->Exit(0);

  return 0;
}
