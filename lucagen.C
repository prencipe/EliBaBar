//This very simply macro is intent to 
//extract the signal and background yields
//of B->DK using Generic BBbar Monte Carlo Events.
//written by Ben Lau

// Last update: Feb 04, 2004

void lucagen()
{
  //define momentum variables for the bachlor's Kaon tracks
  RooRealVar px1 ("px1"         , "p_{x,1}"                , -5, 5, "GeV");        
  RooRealVar py1 ("py1"         , "p_{y,1}"                , -5, 5, "GeV");        
  RooRealVar pz1 ("pz1"         , "p_{z,1}"                , -5, 5, "GeV");        

  //Define some constants here
  RooRealVar kMass  ("kMass"     , "Kaon Mass"          , 0.493677, "GeV");
  RooRealVar piMass ("piMass"    , "Pion Mass"          , 0.13957 , "GeV");
  RooRealVar bMass  ("bMass"     , "B Mass"            , 5.279   , "GeV");
  RooRealVar p00 ("p00","p0 continuum",-1.17478e+00);
  RooRealVar p0 ("p0","p0 D0K bkg",-1.97);
  RooRealVar tau ("tau","tau for DeltaE D0Pi",-2.22132e+00);
  RooRealVar tau2 ("tau2","tau for generic",-5.27188e+00);
  RooRealVar tau3 ("tau3","tau for D0K",-2.21367e+00);//-2.30919e+00
  RooRealVar fracgen("fracgen","frazione gaussiana for generic",0.899923);
  RooRealVar frac3("frac3","frazione gaussiana for DeltaE of D0K bkg",1.63642e-01);
  RooRealVar coreFrac1("coreFrac1","frazione gaussiana DeltaE D0Pi",7.66752e-01);
  // RooRealVar coreFrac11("coreFrac11","frazione gaussiana D0Pi",7.66752e-01);//per tagli stretti
  RooRealVar coreFrac2("coreFrac2","frazione gaussiana D0K",9.60159e-01);
  RooRealVar coreFracbkg("coreFracbkg", "fraction of core Gaussian for continuum bkgF ",9.18549e-01);

  // The momentum magnitude is used by Delta E
  RooFormulaVar p1     ("p1", "p1", "sqrt(px1*px1+py1*py1+pz1*pz1)", RooArgList(px1, py1, pz1)); //momentum magnitude
  RooFormulaVar offset ("offset", "offset", "((piMass*piMass-kMass*kMass)/(2*p1))*((piMass*piMass-kMass*kMass)/(2*p1))", RooArgList(piMass,kMass,p1)); 

  float nSig_val = 10000;
  float nDpi_val = 10000;
  float nGen_val = 10000;
  float nCont_val = 10000;
  float nD0K_val = 10000;

  // define the variables (to be fitted):
  RooRealVar nSig("nSig", "Number of Signal Events", nSig_val, -1000000, 1000000.);
  RooRealVar nDpi("nDpi", "Number of Background Pi Events", nDpi_val, -1000000, 1000000);  
  RooRealVar nGen("nGen", "Number of Background Generic Events", nGen_val, -1000000, 1000000); 
  RooRealVar nCont("nCont", "Number of Background Continuum Events", nCont_val, -1000000, 1000000); 
  RooRealVar nD0K("nD0K", "Number of Background D0K Events", nD0K_val, -1000000, 1000000);  
  // variables and parameters for mES:
  RooRealVar
    mES("mES","m_{ES}", 5.2, 5.29, "GeV"),
    mESMean("mESMean", "mean mES", 5.27925,"GeV"),
    mESSigma("mESSigma", "mES resolution",0.0025068 , "GeV"),
    mESargPi("mESargPi", "argus for DPI",-48.4675),
    mESfracPi("mESfracPi", "mES fraction for DPI",3.19989e-01),
    mESMeanGen("mESMeanGen", "mean mES for generic",5.27708e+00),
    mESSigmaGen("mESSigmaGen", "mES fraction for generic",6.18495e-03),
    mESMeanPi("mESMeanPi", "mean mES for DPI",5.27905e+00),
    mESSigmaPi("mESSigmaPi", "mES fraction for DPI",3.00093e-03),
    mESMeanOther("mESMeanOther", "mean mES for D0K bkg",5.28054e+00,"GeV"),
    mESSigmaOther("mESSigmaOther", "mES for D0K bkg",3.75317e-03,"GeV"),

    m0("m0", "ARGUS end point", 5.28984, "GeV"),
    argParCont("argParCont", "background shape parameter",-20.),
    argParGen("argParGen", "background shape parameter", -45.56),
    argParOther("argParOther", "background shape parameter for D0K bkg",-7.98795e+01);

  RooArgusBG argMESGen("argMESGen","mES ARGUS background shape", mES, m0, argParGen);
  RooArgusBG argMESCont("argMESCont","mES ARGUS background shape", mES, m0, argParCont);
  RooArgusBG argMESOther("argMESOther","mES ARGUS background shape", mES, m0, argParOther);
  RooArgusBG argMESPi("argMESPi","mES ARGUS background shape", mES, m0, mESargPi);
  RooGaussian sigMES("sigMES","signal mES Gaussian", mES, mESMean, mESSigma);
  RooGaussian sigMESGen("sigMESGen","signal mES Gaussian", mES, mESMeanGen, mESSigmaGen);
  RooGaussian sigMESPi("sigMESPi","signal mES Gaussian for DPi", mES, mESMeanPi, mESSigmaPi);
  RooGaussian sigOther("sigOther","signal mES Gaussian for DK", mES, mESMeanOther, mESSigmaOther);
  RooAddPdf sigpiMES("sigpiMES","D0Pi mES Gaussian",sigMESPi, argMESPi, mESfracPi);

  // variables and parameters for (D0K) deltaE:
  RooRealVar
    deltaE("deltaE","#DeltaE", -0.1, 0.2, "GeV"),  // cut lower delta_E with -0.1 to remove background from D*
    deltaEMean("deltaEMean", "mean delta E",4.25061e-02,"GeV"),
    deltaEMeanOther("deltaEMeanOther", "mean delta E",-1.25622e-03,"GeV"),
    deltaEPiSigma("deltaEPiSigma","delta E sigma for D0pi",2.01154e-02,"GeV");
  RooExponential exp("exp","exp",deltaE,tau);
  RooExponential exp2("exp2","exp2",deltaE,tau2);//deltae  pdf for generic
  RooExponential exp3("exp3","exp3",deltaE,tau3);
  RooPolynomial pol3("pol3","pol3",deltaE,p0);
  RooFormulaVar meanpi("meanpi" , "DeltaE mean for Dpi", "(deltaEMean+offset)",RooArgList(offset, deltaEMean));
  RooGaussian sigDeltaEPi("sigDeltaEPi", "sigDeltaEPi", deltaE, meanpi , deltaEPiSigma);
  RooPolynomial bkgDeltaE_pol1("bkgDeltaE_pol1","pol1",deltaE,p00);//deltae pdf for continuum
  RooAddPdf bkgPi("bkgPi","bkgPi",sigDeltaEPi,exp,coreFrac1);//deltae pdf for D0Pi
//DeltaE for signal
  RooRealVar
    sigDeltaEMeanC("sigDeltaEMeanC", "core mean of F",5.11598e-04),
    sigDeltaESigmaC("sigDeltaESigmaC", "core F resolution",1.46737e-02),
    sigDeltaEMeanT("sigDeltaEMeanT", "tail mean of F",-3.67512e-02),
    sigDeltaESigmaT("sigDeltaESigmaT", "tail sigma of F",1.29516e-01);
  RooGaussian sigDeltaEKFC("sigDeltaEKFC", "bkg F core Gaussian", deltaE,sigDeltaEMeanC, sigDeltaESigmaC);
  RooGaussian sigDeltaEKFT("sigDeltaEFT", "bkg F tail Gaussian", deltaE,sigDeltaEMeanT, sigDeltaESigmaT);
  RooAddPdf sigDeltaEK("sigDeltaEK", "sig F D0K",sigDeltaEKFC, sigDeltaEKFT, coreFrac2);     
    
  // variables and parameters for Fisher:
    // The paramerization are copying from ppbar analysis.
    // Please parameterized your fisher before fitting

  //     bkgFMean("bkgFMean", "bkg mean F", 0.0435914, "GeV"),
//       bkgFSigmaL("bkgFSigmaL", "bkg sigma F left", 0.484346),
//       bkgFSigmaR("bkgFSigmaR", "bkg sigma F right",0.283364);
  RooRealVar
    F("F","Fisher", -2.0, 3.0),
    sigFMean("sigFMean", "signal mean F",5.82783e-01),
    sigFSigmaL("sigFSigmaL", "signal sigma F left",2.99313e-01),
    sigFSigmaR("sigFSigmaR", "signal sigma F right",5.08398e-01),
    bkgFMeanC("bkgFMeanC", "core mean of F",3.58660e-01),
    bkgFSigmaC("bkgFSigmaC", "core F resolution",2.66577e-01),
    bkgFMeanT("bkgFMeanT", "tail mean of F",8.93821e-01),
    bkgFSigmaT("bkgFSigmaT", "tail sigma of F",4.70094e-01);   

  RooBifurGauss sigF("sigF","signal Fisher Bifurcated Gaussian", F, sigFMean, sigFSigmaL, sigFSigmaR); 
  RooGaussian bkgFC("bkgFC", "bkg F core Gaussian", F, bkgFMeanC, bkgFSigmaC);
  RooGaussian bkgFT("bkgFT", "bkg F tail Gaussian", F, bkgFMeanT, bkgFSigmaT);
  RooAddPdf bkgF("bkgF", "bkg F double Gaussian", bkgFC, bkgFT, coreFracbkg); 
  //--------------------------------------------------------------------------------------------------//

  //PDF
  RooProdPdf DKPdf("DKPdf", "Signal DK PDF", RooArgList(sigMES,sigDeltaEK,sigF));   //pdf for the DK events
  RooProdPdf DpiPdf("DpiPdf", "Signal Dpi PDF", RooArgList(sigMES,bkgPi,sigF)); //pdf for the Dpi events
  RooProdPdf BkgPdfCont("BkgPdfCont", "Continuum Bkg PDF", RooArgList(argMESCont,bkgDeltaE_pol1,bkgF)); //pdf for the continuum
  RooProdPdf BkgPdfGen("BkgPdfGen", "Generic Bkg PDF", RooArgList(argMESGen,exp2,sigF));//pdf for the generic
  RooProdPdf BkgPdfOther("BkgPdfOther", "D0K Bkg PDF", RooArgList(sigMES,exp3,sigF));//pdf for the generic


 
     // define the datasets
     RooDataSet *toyDK  = DKPdf.generate(RooArgSet(mES,deltaE,F),nSig_val);
     RooDataSet *toyDpi = DpiPdf.generate(RooArgSet(mES,deltaE,F),nDpi_val);
     RooDataSet *toyGen = BkgPdfGen.generate(RooArgSet(mES,deltaE,F),nGen_val);
     RooDataSet *toyCont = BkgPdfCont.generate(RooArgSet(mES,deltaE,F),nCont_val);
     RooDataSet *toyD0K = BkgPdfOther.generate(RooArgSet(mES,deltaE,F),nD0K_val);




     char ss[100];
     float eff_s[100], eff_b1[100], eff_b2[100], eff_b3[100],eff_b4[100] ;
     for(int i=0; i< 100; i++) {
       double fisher_cut = -3 + ((double) i/100)*6.;
       sprintf(ss,"F>%f",fisher_cut);
       eff_s[i] = toyDK->tree().Project("","mES",ss)/nSig_val;
       eff_b1[i] = toyDpi->tree().Project("","mES",ss)/nDpi_val;
       eff_b2[i] = toyGen->tree().Project("","mES",ss)/nGen_val;
       eff_b3[i] = toyCont->tree().Project("","mES",ss)/nCont_val;
       eff_b4[i] = toyD0K->tree().Project("","mES",ss)/nD0K_val;
     }
     
     TCanvas c1;
     TGraph *histo1 = new TGraph(100,eff_b1,eff_s);
     histo1->Draw("AP");
     histo1->GetXaxis()->SetTitle("Bkg");
     histo1->GetYaxis()->SetTitle("Sig");
     histo1->SetMarkerColor(1);
     histo1->SetMarkerStyle(8);
     histo1->SetMarkerSize(.5);
     histo1->Draw("AP");
     //     c1->SaveAs("fisher_selezioneD0k.eps");
     TCanvas c2;
     TGraph *histo2 = new TGraph(100,eff_b2,eff_s);
     histo2->Draw("AP");
     histo2->GetXaxis()->SetTitle("Bkg");
     histo2->GetYaxis()->SetTitle("Sig");
     histo2->SetMarkerColor(2);
     histo2->SetMarkerStyle(8);
     histo2->SetMarkerSize(.5);
     histo2->Draw("AP");
     TCanvas c3;
     TGraph *histo3 = new TGraph(100,eff_b3,eff_s);
     histo3->Draw("AP");
     histo3->GetXaxis()->SetTitle("Bkg");
     histo3->GetYaxis()->SetTitle("Sig");
     histo3->SetMarkerColor(3);
     histo3->SetMarkerStyle(8);
     histo3->SetMarkerSize(.5);
     histo3->Draw("AP");
     c3->SaveAs("fisher_toy.eps");
     TCanvas c4;
     TGraph *histo4 = new TGraph(100,eff_b4,eff_s);
     histo4->Draw("AP");
     histo4->GetXaxis()->SetTitle("Bkg");
     histo4->GetYaxis()->SetTitle("Sig");
     histo4->SetMarkerColor(4);
     histo4->SetMarkerStyle(8);
     histo4->SetMarkerSize(.5);
     histo4->Draw("AP");

     TCanvas c10;
     TMultiGraph *multi0 = new TMultiGraph();
     multi0->Add(histo1);
     multi0->Add(histo2);
     multi0->Add(histo3);
     multi0->Add(histo4);
     multi0->Draw("A*");
     multi0->GetXaxis()->SetTitle("bkg");
     multi0->GetYaxis()->SetTitle("sig");
     multi0->Draw("A*");
     c10->SaveAs("sovrapposizione-finale.eps");

     TFile outfile("outfile-fisher.root","recreate");
     histo3->Write();
     outfile.Close();
  
     ////////////////////////////////////////////////    

  //    gROOT->SetStyle("Plain");
//      gStyle->SetOptStat(0);

//      float contasiglep[100];float contabkglep[100]; int j,jj; int n=100;
//      float contasigall[100];float contabkgall[100];
//      float contasigother[100];float contabkgother[100];
//      float contasigbest[100];float contabkgbest[100];
//      int nsigl; int nbkgl;
//      int nsiga; int nbkga;
//      int nsigo; int nbkgo;
//      int nsigba; int nbkgba;
    
//      TFile ff("tagliultimi_sig.root");
//      TFile fff("tagliultimi_udsc.root");
//      ff.cd("BRECO");
//      nsigl=h973->GetEntries();
//      h973->Scale(1./nsigl);
//      for(j=0; j<100;j++){
//        contasiglep[j]=h973->GetBinContent(j+1)/h973->GetBinContent(1);
//      }
//      //FONDO
//      fff.cd("BRECO");
//      nbkgl=h973->GetEntries();
//      h973->Scale(1./nbkgl);
//      for(j=0; j<100;j++){
//        contabkglep[j]=h973->GetBinContent(j+1)/h973->GetBinContent(1);
//      }

//      TGraph *histo1=new TGraph(n,contabkglep,contasiglep);
//      histo1->Draw("AP");
//      // histo1->GetXaxis()->SetTitle("fondo");
//      // histo1->GetYaxis()->SetTitle("segnale");
//      histo1->SetMarkerStyle(8);
//      histo1->SetMarkerSize(.5);
//      histo1->SetMarkerColor(2);
//      //     histo1->SetTitle("Plot efficienza lep");
//      TCanvas c2;
//      histo1->Draw("AP");
//      c2->SaveAs("outfile-fishereli.eps");
// //       c1->SaveAs("outfile-fisher.eps");
// //       TFile outfile("outfile-fisher.root","recreate");
// //       histo1->Write();
// //       outfile.Close();
  
//      TCanvas c3;
//      TMultiGraph *multi0 = new TMultiGraph();
//      multi0->Add(histo1);
//      multi0->Add(histo);
//      multi0->Draw("A*");
//      c3->SaveAs("sovrapposizione-fisher.eps");


// ////////////Fisher best//////////////////////////////////////
// // int j,jj; int n=100;
// // int nsiglep; int nbkglep;
// // int nsigall; int nbkgall;
// // int nsigother; int nbkgother;
// // int nsigbest; int nbkgbest;
// // float contsiglep[100]; float contbkglep[100];
// // float contsigother[100]; float contbkgother[100];
// // float contsigall[100]; float contbkgall[100];
// // float contsigbest[100]; float contbkgbest[100];

// // float contsiglep[100]; float contbkglep[100];
// // float contsigother[100]; float contbkgother[100];
// // float contsigall[100]; float contbkgall[100];
// // float contsigbest[100]; float contbkgbest[100];
// // float contsigall4[100]; float contbkgall4[100];
// // float contsigall10[100]; float contbkgall10[100];
// // float contsigaall10;float contbkgaall10;
// // float contsigaall4;float contbkgaall4;
// // float contsigalep;float contbkgalep;
// // float contsigaall;float contbkgaall;
// // float contsigaother;float contbkgaother;
// // float contsigabest;float contbkgabest;

// // ff.cd("BRECO");
// // nsiglep=h874->GetEntries();
// // nsigall=h873->GetEntries();
// // nsigbest=h872->GetEntries();
// // nsigother=h875->GetEntries();
// // fff.cd("BRECO");
// // nbkglep=h874->GetEntries();
// // nbkgall=h873->GetEntries();
// // nbkgbest=h872->GetEntries();
// // nbkgother=h875->GetEntries();


// // ////SEGNALE
// // ff.cd("BRECO");
// // for(j=0; j<100;j++){
// //   contsigalep=0;
// //   for(jj=j;jj<100; jj++){
// //     contsigalep=contsigalep+h874->GetBinContent(jj+1);
// //   }
// //   contsiglep[j]=contsigalep;
// // }
// // for(j=0; j<100;j++){
// //   contsigaall=0;
// //   for(jj=j;jj<100; jj++){
// //     contsigaall=contsigaall+h873->GetBinContent(jj+1);
// //   }
// //   contsigall[j]=contsigaall;
// // }

// // for(j=0; j<100;j++){
// //   contsigaother=0;
// //   for(jj=j;jj<100; jj++){
// //     contsigaother=contsigaother+h875->GetBinContent(jj+1);
// //   }
// //   contsigother[j]=contsigaother;
// // }

// // for(j=0; j<100;j++){
// //   contsigabest=0;
// //   for(jj=j;jj<100; jj++){
// //     contsigabest=contsigabest+h872->GetBinContent(jj+1);
// //   }
// //   contsigbest[j]=contsigabest;
// // }


// // //FONDO
// // fff.cd("BRECO");
// // for(j=0; j<100;j++){
// //   contbkgalep=0;
// //   for(jj=j;jj<100; jj++){
// //     contbkgalep=contbkgalep+h874->GetBinContent(jj+1);
// //   }
// //   contbkglep[j]=contbkgalep;
// // }
// // for(j=0; j<100;j++){
// //   contbkgaall=0;
// //   for(jj=j;jj<100; jj++){
// //     contbkgaall=contbkgaall+h873->GetBinContent(jj+1);
// //   }
// //   contbkgall[j]=contbkgaall;
// // }
// // for(j=0; j<100;j++){
// //   contbkgaother=0;
// //   for(jj=j;jj<100; jj++){
// //     contbkgaother=contbkgaother+h875->GetBinContent(jj+1);
// //   }
// //   contbkgother[j]=contbkgaother;
// // }
// // for(j=0; j<100;j++){
// //   contbkgabest=0;
// //   for(jj=j;jj<100; jj++){
// //     contbkgabest=contbkgabest+h872->GetBinContent(jj+1);
// //   }
// //   contbkgbest[j]=contbkgabest;
// // }

// // for(j=0; j<100;j++){
// //   contsigaall4=0;
// //   contsigaall4=contsigaall4+nsiglep+contsigother[j]+contsigbest[66];
// //   float normsig4=nsiglep+contsigother[0]+contsigbest[66];
// //   contsigall4[j]=contsigaall4/normsig4;
// //   contbkgaall4=0;
// //   contbkgaall4=contbkgaall4+nbkglep+contbkgother[j]+contbkgbest[66];
// //   float normbkg4=nbkglep+contbkgother[0]+contbkgbest[66];
// //   contbkgall4[j]=contbkgaall4/normbkg4;
// // }

// // TCanvas c2;
// // TGraph *histosum4=new TGraph(n,contbkgall4,contsigall4);
// // histosum4->GetXaxis()->SetTitle("Nbkgd");
// // histosum4->GetYaxis()->SetTitle("Nsig");
// // histosum4->SetMarkerStyle(8);
// // histosum4->SetMarkerSize(.5);
// // histosum4->SetMarkerColor(12);
// // histosum4->SetTitle("Somma categorie");
// // histosum4->Draw("AP*");


// // ff.cd("BRECO");
// // for(j=0; j<100;j++){
// //   contsigaall10=0;
// //   for(jj=j;jj<100; jj++){
// //     contsigaall10=contsigaall10+h873->GetBinContent(jj+1);
// //   }
// //   contsigall10[j]=contsigaall10/nsigall;
// // }
// // fff.cd("BRECO");
// // for(j=0; j<100;j++){
// //   contbkgaall10=0;
// //   for(jj=j;jj<100; jj++){
// //     contbkgaall10=contbkgaall10+h873->GetBinContent(jj+1);
// //   }
// //   contbkgall10[j]=contbkgaall10/nbkgall;

// // }


// // TGraph *histosum10=new TGraph(n,contbkgall10,contsigall10);
// // histosum10->GetXaxis()->SetTitle("Nbkgd");
// // histosum10->GetYaxis()->SetTitle("Nsig");
// // histosum10->SetMarkerStyle(8);
// // histosum10->SetMarkerSize(.5);
// // histosum10->SetMarkerColor(65);
// // histosum10->SetTitle("Somma categorie");

// // TCanvas c4;
// // TMultiGraph *multi = new TMultiGraph();
// // multi->Add(histosum4);
// // multi->Add(histosum10);
// // multi->Add(histo0);
// // multi->Draw("A*");
// // multi->GetXaxis()->SetTitle("bkg");
// // multi->GetYaxis()->SetTitle("sig");
// // multi->Draw("A*");
// // c4->SaveAs("sovrapposizione-fisher-finale.eps");
 }
