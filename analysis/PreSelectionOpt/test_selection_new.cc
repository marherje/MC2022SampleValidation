#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_selection_new(int G, int R, TString pol, int type, float Kv){
  int bkg=0;
  int selection_type=type;
  TString s_type=TString::Format("cuts%i_",type);
  TString kvalue=TString::Format("_Kgamma%i",int(Kv));
  
  //TString fileaux1=TString::Format("../../../../Data/ntuples/1/%i", int(G));
  //TString fileaux2=TString::Format("/%i/500_mergedfile_", int(R));
  //TString file = fileaux1+fileaux2+pol+".root";
  
  //TString file = "../../../500GeV_NewNTuples2022/"+pol+"_500GeV_NewSamples.root";

  TString file = "/lustre/ific.uv.es/prj/ific/flc/ntuples-2021/500GeV_IDR_signal/"+pol+"_500GeV.root";
  QQbarAnalysisClass ss3(file);

  //ss3.process=s_type+"qqbar_NEW_"+pol+kvalue;
  ss3.process=s_type+"qqbar_"+pol+kvalue;

  ss3.Selection(-1,type,Kv,bkg);
  gSystem->Exit(0);

  return 0;
}
