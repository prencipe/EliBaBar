#include "allinc.h"
#include "fit_meslh.h"
void final(){
  //MesKKK.root
  // TFile *bfile=new TFile("./mumukai.root");
  //TFile *bfile=new TFile("./MesPlotKKK.root");
  // TFile *bfile=new TFile("../../NTUPLEpad2014/total20nb.root");
  //TFile *bfile=new TFile("../../NTUPLEpad2014/BKG/myargus2.root");
  TFile *bfile=new TFile("../../NTUPLEpad2014/SIG/referencesig.root");
  TCanvas *c1=new TCanvas("c1","c1",1);
  //TH1D *h=(TH1D*) bfile->Get("histo_a");
  TH1D *h=(TH1D*) bfile->Get("mass");
  
  //h.SetMaximum(4000);
  h.SetXTitle("m_{ES} (GeV/c^{2})");
  h.SetYTitle("Evt/2 (MeV/c^{2})");
  h.Draw();
  TF1 *f=new TF1();
  int fix[6]={1,1,0,0,1};
  //double ini[6]={100,0,30,0.0027663,5.2794};

  double ini[6]={0,0,20,0.0000133,4.286}; 
 double res[6],eresp[6],eresn[6];
 
  f=fit_meslh(h,"sig",fix,ini,res,eresp,eresn);
  cout<<"res = "<<res[2]<<"  - "<<eresn[2]<<"  +  "<<eresp[2]<<endl;
  c1->SaveAs("histo.eps"); 
  //Nbkg
  //argus
  //Nsig
  //sigma gaus
  //average gaus

}
