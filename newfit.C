

#include "iostream"
#include "TCut.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TString.h"
#include "TFile.h"

gROOT->SetStyle("Plain");
gStyle->SetOptStat(0);




void polynomial(){
  TFile f("../../myefficiency12.root");
    
  RooRealVar *x = new RooRealVar("x","m_{J/#psi#phi}", 4.1, 4.8,"GeV/c^{2}");
  TH1D* histo_s = (TH1D*) f.Get("gre");
  histo_s->DrawCopy();

  RooDataHist *data= new RooDataHist("data","data",*x,histo_s);



  //Define some constant parameters here
  
  RooRealVar *p0 = new RooRealVar("p0","coefficient 0",0.00002);
  RooRealVar *p1 = new RooRealVar("p1","coefficient 1",0.033);
  RooRealVar *p2 = new RooRealVar("p2","coefficient 2",-1.4);
  RooRealVar *p3 = new RooRealVar("p3","coefficient 3",0.61);
  RooRealVar *p4 = new RooRealVar ("p4","coefficient 4",0.068);
  
  
  // float nSig_val = 10000;
  //float nBkg_val = 10000;
  
  
  // define the variables (to be fitted):
  RooRealVar nSig("nSig", "Number of Signal Events", 0, -1000000, 1000000.);
  RooRealVar nBkg("nBkg", "Number of Background  Events", 0, -1000000, 1000000);  
  
       

  RooPolynomial *pol = new RooPolynomial("pol","3 order polynomial",  *x, RooArgList(*p1,*p2,*p3));
  
  //------------------------------------------------------------------//
  
  RooFitResult* fitResult = pol.fitTo(*data,"m0r");
  RooPlot *effiPlot = data->plotOn(x.frame(68));
  pol->plotOn(effiPlot);
  TCanvas *c1 = new TCanvas("c1","all events",600, 400);
  effiPlot->Draw();

  c1->SaveAs("effi2.eps");

 
  //  RooFitResult* fitResult = pol->fitTo(*data,"m0r");
  //fitResult->Print();

  // f.Close();

  //TCanvas *c1 =new TCanvas();
  //c1->cd();

  
  //RooPlot* xframe2 = x->frame(50);
  //xframe2->Sumw2();
  //data->plotOn(xframe2);
  //pol->plotOn(xframe2);
  //xframe2->Draw("P0");
  //xframe2->Draw("Esame");
  //c1->SaveAs("myplote.eps");


   

}


void breitPol() {
  //TFile f("../../../NTP/Ntuples/MACRO-SLAC/MetricaBchmx2.root");
  //TFile f("../../../NTP/Ntuples/MACRO-SLAC/MassPlot02.root");
  //TFile f("./MassB0Y.root");
  //TFile f("./MetricaB0mx.root");
  // TFile f("../../../NTP/Ntuples/MACRO-SLAC/MyInvMassBch.root");
  //  TFile f("../../../NTP/Ntuples/MACRO-SLAC/MyPlotTotal.root");
  //  TFile f("../../../NTP/Ntuples/MACRO-SLAC/MyPloMuons.root");
  //TFile f("../../../NTP/Ntuples/MACRO-SLAC/MyMasstotal.root");
  //TFile f("./MyPlotMass-23march.root");
  //  TFile f("./Veronique20.root");
  //this is valis to fit the real mx distribution for B0, mx12
  TFile f("./kaiM12solomuon.root");  

  //unbinned m(Jpsi phi) fit


  RooRealVar *x = new RooRealVar("x","m_{J/#psi#phi}", 4.116,4.796,"GeV/c^{2}");
  RooRealVar *x2 = new RooRealVar("x2","m_{J/#psi#phi}", 4.116, 4.787,"GeV/c^{2}");


  RooArgList temp;
  temp.add(RooArgList(*x));
  RooDataSet* data = RooDataSet::read("./file3.txt",temp);



  RooRealVar *mean = new RooRealVar("mean","xm",4.143,4.116,4.25,"GeV/c^{2}");
  RooRealVar *mean2 = new RooRealVar("mean2","xm2",4.156,"GeV/c^{2}");
  RooRealVar *width = new RooRealVar("width","width",0.0153,0.,0.1,"GeV/c^{2}");
  RooRealVar *width2 = new RooRealVar("width2","width2", 0.0332,0.,0.1,"GeV/c^{2}");
  //Define some constant parameters here
  
  RooRealVar massMean("massMean", "mean m",4.285,"GeV/c^{2}");
  RooRealVar massMean2("massMean2", "mean m2",4.156,"GeV/c^{2}");
  RooRealVar massMean3("massMean3", "mean m2",4.465,"GeV/c^{2}");
  RooRealVar massSigma("massSigma", "m resolution",0.0332,"GeV/c^{2}");
  RooRealVar massSigma2("massSigma2", "m2 resolution",0.0117,0.,0.08,"GeV/c^{2}");
  RooRealVar massSigma3("massSigma3", "m3 resolution",0.0153,0.,0.2,"GeV/c^{2}");
  RooGaussian sigMass("sigMass","signal m Gaussian", *x,massMean,massSigma); 
  
  RooRealVar masswidth("masswidth", "#Delta E width",0.0332);
  RooRealVar masswidth2("masswidth2", "#Delta E width",0.0117);
  RooRealVar masswidth3("masswidth3", "#Delta E width",0.0117);

  


  //voigtian function
  RooVoigtian myvog("myvog","myvog",*x,massMean,masswidth,massSigma);
  RooBreitWigner *BW = new RooBreitWigner("BW","Breit Wigner for signal",*x,  massMean, masswidth);  
  RooBreitWigner *BW2 = new RooBreitWigner("BW2","Breit Wigner for signal",*x,  massMean2, masswidth2);
  RooBreitWigner *BW3 = new RooBreitWigner("BW3","Breit Wigner for signal",*x,  massMean3, masswidth3);   

  RooRealVar *bkgFMeanC= new RooRealVar("bkgFMeanC", "core mean of F",4.274);
  RooRealVar *bkgFSigmaC= new RooRealVar("bkgFSigmaC", "core F resolution",0.0332);
  RooRealVar *bkgFMeanT= new RooRealVar("bkgFMeanT", "tail mean of F",4.274);
  RooRealVar *bkgFSigmaT= new RooRealVar("bkgFSigmaT", "tail sigma of F",0.0332);
  RooRealVar *coreFrac= new RooRealVar("coreFrac", "fraction of core Gaussian", 0.1,0.,1.);

  RooGaussian *bkgFC= new RooGaussian("bkgFC", "bkg F core Gaussian", *x, *bkgFMeanC, *bkgFSigmaC);
  RooGaussian *bkgFT= new RooGaussian("bkgFT", "bkg F tail Gaussian", *x, *bkgFMeanT, *bkgFSigmaT);
  RooAddPdf *bkgF= new RooAddPdf("bkgF", "bkg F double Gaussian", *bkgFC, *bkgFT, *coreFrac); 


  RooRealVar *p1e = new RooRealVar("p1e","coefficient 1",321);
  RooRealVar *p2e = new RooRealVar("p2e","coefficient 2",-76);
  RooRealVar *p3e = new RooRealVar("p3e","coefficient 3",-0.177);
  RooRealVar *p4e = new RooRealVar ("p4e","coefficient 4",2.20);
  RooRealVar *p5e = new RooRealVar ("p5e","coefficient 4",-0.021);

  

  RooRealVar *p0 = new RooRealVar("p0","coefficient 0",9.55377e-03,-10,50);
  RooRealVar *p1 = new RooRealVar("p1","coefficient 1",-8.67641e+00,-100,100);
  RooRealVar *p2 = new RooRealVar("p2","coefficient 2",-6.50053e+00,-20,20);
  RooRealVar *p3 = new RooRealVar("p3","coefficient 3",5.20156e+00,-10,10);
  RooRealVar *p4 = new RooRealVar ("p4","coefficient 4",-7.70052e-01,-20,20);
  RooRealVar  *frac = new RooRealVar ("frac","frac",0.2,0.,1.);
  RooRealVar  *frac2 = new RooRealVar ("frac2","frac2",0.2,0.,1.);
  RooRealVar  *frac3 = new RooRealVar ("frac3","frac3",0.2,0.,1.);
  RooRealVar nSig("nSig", "Number of Signal Events", 0.);
  RooRealVar nBkg("nBkg", "Number of Background  Events", 405.);
  RooRealVar nPol("nPol", "Number of Signal Events", 405.);
  RooRealVar nSig2("nSig2", "Number of Signal Events", 10.,-1.,1000);
  RooRealVar nBkg2("nBkg2", "Number of Background  Events", 0, 20, 10000);
  /*
  TH1D* histo_s = (TH1D*) f.Get("hSigM12e2");
  histo_s->DrawCopy();
  histo_s->Scale(0.164);
  histo_s->SetMinimum(0.0); 
  RooDataHist *data= new RooDataHist("data","data",*x,histo_s);
  cout<<histo_s->GetEntries()<<endl;
  */
  //return;

  BWShape *XPdf = BWJP(x, mean, width, 1, 2, false);
  BWShape *XPdf2 = BWJP(x, mean2, width2, 1, 2, false);
  RooPolynomial *pol = new RooPolynomial("pol","3 order polynomial",  *x, RooArgList(*p1,*p2,*p3,*p4, *p0));
  RooPolynomial *pole = new RooPolynomial("pole","5 order polynomial",  *x, RooArgList(*p1e,*p2e,*p3e,*p4e, *p5e));

  RooProdPdf *correctedPdf = new RooProdPdf("correctedPdf", "effi*BW", RooArgList(*pole, *XPdf2));

  RooAddPdf *doubleXPdf = new RooAddPdf("doubleXPdf", "2 XPdf", *XPdf, *XPdf2, *coreFrac);
  RooAddPdf *tris = new RooAddPdf("tris", "2 XPdf + voig.", *XPdf, myvog, *frac2);
  RooAddPdf *quat = new RooAddPdf("quat", "2 XPdf", *doubleXPdf, *BW, *frac);
  RooAddPdf *quat2 = new RooAddPdf("quat2", "2 XPdf", *quat, *BW2, *frac2);
  RooAddPdf *quat3 = new RooAddPdf("quat3", "2 XPdf", *quat2, *BW3, *frac3);
  //RooAddPdf *quatpol = new RooAddPdf("quatpol", "2 XPdf", *quat, *pol, *frac2);
  RooAddPdf *total =
    new RooAddPdf("total", "BW + Polynomial",RooArgList(*correctedPdf,*pol),RooArgList(nSig,nPol));
    //  new RooAddPdf("total", "BW + Polynomial",RooArgList(*XPdf,*pol),RooArgList(nSig,nPol));
    //  new RooAddPdf("total", "BW + PHSP",RooArgList(*pol),RooArgList(nSig));
    //new RooAddPdf("total", "BW + Polynomial",RooArgList(*bkgF,*pol),RooArgList(nSig,nPol));
  //RooFitResult* fitResult = total->fitTo(*data,"me0r");

  RooFitResult* fitResult = total.fitTo(*data,"emhrtv");
  RooPlot *massPlot = data->plotOn(x.frame(68));
  //histo_s->SetMinimum(0.0);
  total->plotOn(massPlot);
  massPlot->SetMinimum(0.);
  TCanvas *c1 = new TCanvas("c1","all events",600, 400);
  massPlot->Draw();

  c1->SaveAs("dati2.eps");

  

}

BWShape*  BWJP(RooRealVar* x, RooRealVar* mean, RooRealVar* width, int l, int typeOfDecay, bool usePhaseSpaceOfB) {

  mass1 = new RooRealVar("mass1","mass1",3.096916);    // Mass of the first product of the resonance
  mass2 = new RooRealVar("mass2","mass2",1.019455);    // Mass of the second product of the resonance
  mass3 = new RooRealVar("mass3","mass3",0.493677);     // Mass of the third particles (not produced by the resonance)
  lOrbital = new RooRealVar("l","l",0);                            // Orbital angular momentum of the daughter particles
  decayType = new RooRealVar("decayType","decayType",1); // Decay type (1 = L -> 0 0 // 2 = L -> 1 0)
  useBPhaseSpace = new RooRealVar("useBPhaseSpace","useBPhaseSpace",0);  // Do we use the B phase space?
  BWShape *XPdf = new
    BWShape("XPdf","Breit-Wigner",*x,*mean,*width,*mass1,*mass2,*mass3,*lOrbital,*decayType,*useBPhaseSpace);
  //  RooPolynomial *pol = 
  //new RooPolynomial("pol","3 order polynomial",  RooRealVar *x, RooArgList(RooRealVar *p1,RooRealVar *p2,RooRealVar *p3));

  return XPdf;
}
