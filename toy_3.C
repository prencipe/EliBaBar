#include "TMath.h"
#include "TFile.h"
#include <fstream.h>

//Define the ascii file to be saved after 1000 toy experiment
ofstream ofs("gamma_3.dat");

//define now many experiment to run
Double_t Nexp=1000;

//Here is the main macro
//It basically run for 3 rb case
//rb=0.08,0.12,0.15
//If you need other rb number please feel free to change it

toy_3()
{
  //  toy(0.08);
  //  toy(0.2);
  toy(0.5);
  //toy(0.125);
}


void toy(Double_t rb) {
  //The number of signal,background events are defined here
  //Please change the number for different selections cut
  //Here we assumed 200ifb-1 sceniaro
  
  
  
  Double_t nSig_average(26*2.0);
  Double_t nCont_average(11*2.0+20*2.0);
  Double_t nDPi_average(1*2.0);
  Double_t nbb_average(4*2.0);
  RooRealVar
    nSig("nSig", "Number of Signal Events", nSig_average, 0.0, 10000.0),
    nDpi("nDPi","Number of Dpi events", nDPi_average),
    nbb("nbb","number of BB events", nbb_average),
    nCont("nCont","Number of cc events", nCont_average);
  
  
  //Define the value of pi and the initial seed for the toy experiment
  Double_t pi;Double_t bb;
  Int_t seed;
  seed=7;
  pi=180.0;
  
  //Now define our observable, which is m^12 = Ks pi+
  //                                    m^13 = Ks pi-
  
  RooRealVar mass12("mass12","Invariant mass^2 for Ks pi+",0.98286,1.87675);
  RooRealVar mass13("mass13","Invariant mass^2 for Ks pi-",0.98286,1.87675);
  
  
  //Now read in the dalitz pdf shape for the udsc and bb events
  //They are obtained from MC with VT Kaon selection and good D veto
  //For the good D we will use our CLEO D-decay model
  // RooDataSet* contin = RooDataSet::read("../RooFitDalitz/pdfshape/uds_new.dat",RooArgSet(mass12,mass13));
  // RooDataSet* bbflat = RooDataSet::read("../RooFitDalitz/pdfshape/bb_new.dat",RooArgSet(mass12,mass13));
  RooDataSet* contin = RooDataSet::read("../RooFitDalitz/pdfshape/flat.dat",RooArgSet(mass12,mass13));
  RooDataSet* bbflat = RooDataSet::read("../RooFitDalitz/pdfshape/flat.dat",RooArgSet(mass12,mass13));
  
  //convert into binned Histrogram
  RooDataHist udschist("udschist","Histrogram for the udsc combinatorics events",RooArgList(mass12,mass13),*contin);
  RooDataHist bbhist("bbhist","Histogram for the bb combinatorics events",RooArgList(mass12,mass13),*bbflat);
  
  
  
  //**********************************************************************
  //Now start our toy experiments!
  //**********************************************************************
  
  
  for (int i=0; i< Nexp; i++) {
    cout << "**********************************************" << endl;
    cout << "Now doing the experiment    " << i << endl;
    cout << "**********************************************" << endl;
    bb=0;

    
    //Each experiment using different seed!
    RooRandom::randomGenerator()->SetSeed(seed+(i*1000));
    
    
    
    //**********************************************************************
    //Signal Dalitz pdf
    //**********************************************************************
    //amp is the rb
    //Here we assume \gamma=70.0, \delta=180.0
    RooRealVar amp("amp","amp",rb,0.0,10.0); 
    RooRealVar plusphase("plusphase","The plus phase",70.0+180.0, -360.0,360.0); //70+180-180,70+180+180);
    RooRealVar minusphase("minusphase","The minus phase",-70+180, -360.0,360.0);//-70+180-180,-70+180+180);
    
    
    
    //Define a cat variable to distinguish B+ and B-
    RooCategory charge("charge","charge of the B meson");
    charge.defineType("Bplus",1);
    charge.defineType("Bminus",-1);
    
    //Now construct our pdf
    //one for B+ -> D0bar K+ (RooDKplus)
    //another one for B- ->D0 K- (RooDKminus)
    RooDKplus sigplus("sigplus","Signal pdf for the B+ events",mass12,mass13,amp,plusphase);
    RooDKminus sigminus("sigminus","Signal pdf for the B- events",mass12,mass13,amp,minusphase);
    
    //Construct the Simultaneous pdf to fit B+ and B- simultaneously
    RooSimultaneous sigPdf("sigPdf","The signal pdf",charge);
    sigPdf.addPdf(sigplus,"Bplus");
    sigPdf.addPdf(sigminus,"Bminus");
    
    //Construct our prototype dataset for the toy
    //Here we simply assume 50% are B+ and 50% are B-
    // Poissonian number extraction 
    
    Int_t nSig_actual = RooRandom::randomGenerator()->Poisson(nSig_average);
    RooDataSet proto("pD","pD",charge);
    charge = "Bplus"; 
    for (int j=0;j<(nSig_actual)/2.0;j++) {
      proto.add(charge);
    }
    charge = "Bminus"; 
    for (int j=0;j<(nSig_actual)/2.0;j++) {
      proto.add(charge);
    }
    
    
    //**********************************************************************
    //B->Dpi background Dalitz pdf
    //**********************************************************************
    //Here we define all the phase and rb to be zero
    //Therefore, the D-decay will lack of the opposite flavor
    RooRealVar zeroamp("zeroamp","zeroamp",0.0);
    RooRealVar zerophase("zerophase","The phase value is zero",0.0);
    
    //notice amp1=0.0, a pure D-decay model without opposite flavour
    RooDKplus dpiplus("dpiplus","dpiplus",mass12,mass13,zeroamp,zerophase);
    RooDKminus dpiminus("dpiminus","dpiminus",mass12,mass13,zeroamp,zerophase);
    
    //Again, construct the simultaneous pdf
    RooSimultaneous dpipdf("dpipdf","dpipdf",charge);
    dpipdf.addPdf(dpiplus,"Bplus");
    dpipdf.addPdf(dpiminus,"Bminus");
    
    //We need a prototype dataset for Dpi events
    RooDataSet proto1("pD","pD",charge);
    Int_t nDPi_actual = nDPi_average;//RooRandom::randomGenerator()->Poisson(nDPi_average);
    
    charge = "Bplus"; 
    for (int j=0;j<(nDPi_actual)/2.0;j++) {
      proto1.add(charge);
    }
    charge = "Bminus"; 
    for (int j=0;j<(nDPi_actual)/2.0;j++) {
      proto1.add(charge);
    }
    
    //   //**********************************************************************
    //   // uds continuum background Dalitz pdf
    //   // For uds, there is only combinatorics events 
    //   //**********************************************************************
    // //Construct the RooHistogram pdf using the binned Histogram
    // RooHistPdf uds("uds", "uds", RooArgList(mass12,mass13), udschist);
    
    
    // RooSimultaneous udspdf("udspdf","udspdf",charge);
    // udspdf.addPdf(uds,"Bplus");
    // udspdf.addPdf(uds,"Bminus");
    
    // //again, assume 50% are Bplus and 50% are B-
    // RooDataSet proto2("pD","pD",charge);
    // charge = "Bplus";
    // for (int j=0;j<(nUDS->getVal())/2.0;j++) {
    // proto2.add(charge);
    // }
    // charge = "Bminus";
    // for (int j=0;j<(nUDS->getVal())/2.0;j++) {
    // proto2.add(charge);
    // }
    
    
    //**********************************************************************
    // ccbar continuum background Dalitz pdf
    // For cc, there are 3 components, good D,good Dbar,pure combinatorics
    // The situation is complicated here since there is a correlation between
    // Flavour of D and the charge of the Kaon.
    //**********************************************************************
    
    //Construct our D-decay pdf
    RooDKplus D0bar("D0bar","D0bar dalitz model",mass12,mass13,zeroamp,zerophase);  //assoicated with K+
    RooDKminus D0("D0","D0 dalitz model",mass12,mass13,zeroamp,zerophase);       //assoicated with K-
    //Constructed pdf for the combinatorics events
    RooHistPdf cc("cc", "continuum combinatorics events", RooArgList(mass12,mass13), udschist);
    
    
    //define fraction of D0K- events in genuine D, which is called R in Achille's BAD note
    RooRealVar Rminus("Rminus", "fraction of D0K- in genuine D", 0.213);
    RooRealVar Rplus("Rplus", "fraction of D0K+ in genuine D", 1-(Rminus->getVal()));
    
    //define fraction of good D and bad D in the cc events
    RooRealVar fgood("fgood", "fraction of the good D events", 0.21);
    RooRealVar fbad("fbad", "fraction of the bad D events", 1.0-(fgood->getVal()));
    
    //we have 88 cc events in 200ifb-1
    
    //  //Calculate number of goodD and badD events
    // RooRealVar nDplus("nDplus","Number of D events", TMath::Nint(Rminus->getVal()*fgood->getVal()*nCC->getVal()));  //larger number
    // RooRealVar nDminus("nDminus","Number of good D events", TMath::Nint(Rplus->getVal()*fgood->getVal()*nCC->getVal())); //smaller number
    // RooRealVar badD("badD","Number of bad D events", TMath::Nint(fbad->getVal()*nCC->getVal()));
    
    
    
    // //Construct the total pdf according to the fraction of good D and bad D
    //  RooAddPdf ccplus("ccplus","ccplus",RooArgList(D0,D0bar,cc),RooArgList(nDminus,nDplus,badD)); //pdf for the K+ events
    //  RooAddPdf ccminus("ccminus","ccminus",RooArgList(D0,D0bar,cc),RooArgList(nDplus,nDminus,badD)); //pdf for K- events
    
    //Calculate number of goodD and badD event
    RooRealVar nDplus("nDplus","Number of D events", Rminus->getVal()*fgood->getVal()*nCont->getVal());  //larger number
    RooRealVar fDplus("nDplus","Number of D events", Rminus->getVal()*fgood->getVal());  //larger number
    RooRealVar nDminus("nDminus","Number of good D events", Rplus->getVal()*fgood->getVal()*nCont->getVal()); //smaller number
    RooRealVar fDminus("nDminus","Number of good D events", Rplus->getVal()*fgood->getVal()); //smaller number
    RooRealVar badD("badD","Number of bad D events", fbad->getVal()*nCont->getVal());
    RooRealVar fbadD("badD","Number of bad D events", fbad->getVal());
    cout << "check ccbar "<< nDplus->getVal() << " " << nDminus->getVal() <<" " << badD->getVal() << endl; 
    
    //Construct the total pdf according to the fraction of good D and bad D
    RooAddPdf ccplus("ccplus","ccplus",RooArgList(D0,D0bar,cc),RooArgList(fDminus,fDplus,fbadD)); //pdf for the K+ events
    RooAddPdf ccminus("ccminus","ccminus",RooArgList(D0,D0bar,cc),RooArgList(fDplus,fDminus,fbadD)); //pdf for K- events
    
    //Our simultaneous pdf
    RooSimultaneous ccpdf("ccpdf","ccpdf",charge);
    ccpdf.addPdf(ccplus,"Bplus");
    ccpdf.addPdf(ccminus,"Bminus");
    
    
    //The prototype dataset for the simultaneous pdf
    RooDataSet proto3("pD","pD",charge);
    Int_t nCont_actual = nCont_average; //RooRandom::randomGenerator()->Poisson(nCont_average);
    charge = "Bplus";
    for (int j=0;j<nCont_actual/2.0;j++) {
      proto3.add(charge);
    }
    charge = "Bminus";
    for (int j=0;j<nCont_actual/2.0;j++) {
      proto3.add(charge);
    }
    
    
    
    
    //**********************************************************************
    // B+/B0 admixture background Dalitz pdf
    // We simply use combinatorics pdf only, coz true D0 events is little
    //**********************************************************************
    RooHistPdf bbcon("bbcon", "bbcon", RooArgList(mass12,mass13), bbhist);
    //we have total 24 events in 200ifb-1
    //
    
    RooSimultaneous bbpdf("bbpdf","bbpdf",charge);
    bbpdf.addPdf(bbcon,"Bplus");
    bbpdf.addPdf(bbcon,"Bminus");
    
    
    
    RooDataSet proto4("pD","pD",charge);
    Int_t nbb_actual = nbb_average;//RooRandom::randomGenerator()->Poisson(nbb_average);
    
    charge = "Bplus";
    for (int j=0;j<(nbb_actual)/2.0;j++) {
      proto4.add(charge);
    }
    charge = "Bminus";
    for (int j=0;j<(nbb_actual)/2.0;j++) {
      proto4.add(charge);
    }
    
    
    //*******************************************************************
    //Print out the information as a final cross check
    //User should always check the number themselves!
    //*******************************************************************
    cout << "The number of signal candidate" << "  " << nSig->getVal() << " " << proto->numEntries() << endl;
    cout << "The number of BBbar candidate" << "  " << nbb->getVal() << " " << proto4->numEntries() <<endl;
    cout << "The number of Dpi candidate" << "  " << nDpi->getVal() << " " << proto1->numEntries() << endl;
    //  cout << "The number of uds candidate" << " " << nUDS->getVal() << " " << proto2->numEntries() << endl;
    //  cout << "The number of good D events in ccbar" << "  " << nDminus->getVal()+nDplus->getVal() << endl;
    //  cout << "The number of combinatorics ccbar events" << "  " << nDminus->getVal()+nDplus->getVal()+badD->getVal() << " " << proto3->numEntries() << endl;
    cout << "The number of continuum events " << " " << nCont->getVal() << " " << proto3->numEntries() << endl;
    
    
    
    
    
    //**********************************************************************
    //Now construct the mES pdf
    //**********************************************************************
    // variables and parameters for mES:
    RooRealVar
      mES("mES","m_{ES}", 5.2, 5.2895, "GeV"),
      mESMean("mESMean", "mean mES", 5.280,"GeV"),
      mESSigma("mESSigma", "mES resolution", 0.00276518, "GeV"),
      
      m0("m0", "ARGUS end point", 5.2895, "GeV"),
      argPar("argPar", "background shape parameter", -23.2),
      argPar1("argPar1", "background shape parameter 1", -52.3);
    
    
    RooGaussian sigMES("sigMES","signal mES Gaussian", mES, mESMean, mESSigma);  //signal mES is a gaussian
    RooArgusBG bkgMES("bkgMES","mES ARGUS background shape", mES, m0, argPar);  //combinatorics bkg is a ARGUS function
    RooArgusBG bkg1MES("bkg1MES","mES ARGUS background shape1", mES, m0, argPar1);  //combinatorics bkg is a ARGUS function
    
    
    //**********************************************************************
    //Now construct the Fisher pdf
    //**********************************************************************
    // variables and parameters for Fisher:
    
    RooRealVar
      F("F","Fisher", -3.0, 3.0),
      sigFMean("sigFMean", "signal mean F", 0.277119),
      sigFSigmaL("sigFSigmaL", "signal sigma F left", 0.361352),
      sigFSigmaR("sigFSigmaR", "signal sigma F right", 0.223747),
      bkgFMean("bkgFMean", "bkg mean of F", 0.0435914, "GeV"),
      bkgFSigmaL("bkgFSigmaL", "sigma left F resolution", 0.484346, "GeV"),
      bkgFSigmaR("bkgFSigmaR", "sigma right F resolution", 0.283364, "GeV");
    
    
    
    
    // PDFs for Fisher:
    // single gaussian for signal and background
    RooBifurGauss sigF("sigF","signal Fisher Bifurcated Gaussian",
		       F, sigFMean, sigFSigmaL, sigFSigmaR);
    
    RooBifurGauss bkgF("bkgF", "bkg Fisher Bifurcated Gaussian",
		       F, bkgFMean, bkgFSigmaL, bkgFSigmaR);
    
    
    
    
    
    //**********************************************************************
    //Constuct the RooProdPdf
    //**********************************************************************
    RooProdPdf SigDalitzPdf("SigDalitzPdf","SigDalitzPdf",RooArgList(sigMES,sigPdf,sigF));
    RooProdPdf dpiDalitzPdf("dpiDalitzPdf","dpiDalitzPdf",RooArgList(sigMES,dpipdf,sigF));
    RooProdPdf contDalitzPdf("contDalitzPdf","contDalitzPdf",RooArgList(bkgMES,ccpdf,bkgF));
    RooProdPdf bbDalitzPdf("bbDalitzPdf","bbDalitzPdf",RooArgList(bkg1MES,bbpdf,sigF));
    
    
    
    RooProdPdf SigNoDalitzPdf("SigNoDalitzPdf","SigNoDalitzPdf",RooArgList(sigMES,sigF));
    RooProdPdf dpiNoDalitzPdf("dpiNoDalitzPdf","dpiNoDalitzPdf",RooArgList(sigMES,sigF));
    RooProdPdf contNoDalitzPdf("contNoDalitzPdf","contNoDalitzPdf",RooArgList(bkgMES,bkgF));
    RooProdPdf bbNoDalitzPdf("bbNoDalitzPdf","bbNoDalitzPdf",RooArgList(bkg1MES,sigF));
    
    //Now construct the total pdf
    //**********************************************************************
    
    RooAddPdf model("model", "Model", RooArgList(SigDalitzPdf,dpiDalitzPdf,contDalitzPdf,bbDalitzPdf), RooArgList(nSig,nDpi,nCont,nbb));
    
    
    RooAddPdf modelNoDalitz("modelNoD", "ModelNoD", RooArgList(SigNoDalitzPdf,dpiNoDalitzPdf,contNoDalitzPdf,bbNoDalitzPdf), RooArgList(nSig,nDpi,nCont,nbb));
    
    
    
    RooAddPdf modelNoDalitzNobb("modelNoDNobb", "ModelNoDNobb", RooArgList(SigNoDalitzPdf,contNoDalitzPdf), RooArgList(nSig,nCont));
    
    RooAddPdf modelDalitz("model", "Model", RooArgList(sigPdf,dpipdf,ccpdf,bbpdf), RooArgList(nSig,nDpi,nCont,nbb));
    
    
    //   //**********************************************************************
    //   //Now construct the total pdf
    //   //**********************************************************************
    
    // //  RooAddPdf model("model", "Model", RooArgList(sigPdf,dpipdf,udspdf,ccpdf,bbpdf), RooArgList(nSig,nDpi,nUDS,nCC,nbb));
    //  //RooAddPdf model("model", "Model", RooArgList(sigPdf), RooArgList(nSig));
    //  RooAddPdf model("model", "Model", RooArgList(sigPdf,dpipdf,ccpdf,bbpdf), RooArgList(nSig,nDpi,nCont,nbb));
    
    
    
    //**********************************************************************
    //Now generate the dataset
    //**********************************************************************
//     RooDataSet* data = sigPdf.generate(RooArgSet(mass12,mass13),proto);
//     RooDataSet* data1 = dpipdf.generate(RooArgSet(mass12,mass13),proto1);
//     //RooDataSet* data2 = udspdf.generate(RooArgSet(mass12,mass13),proto2);
//     RooDataSet* data3 = ccpdf.generate(RooArgSet(mass12,mass13),proto3);
//     RooDataSet* data4 = bbpdf.generate(RooArgSet(mass12,mass13),proto4); 
    
//     RooDataSet* data = sigPdf.generate(RooArgSet(mass12,mass13,mES,F),proto);
//     RooDataSet* data1 = dpipdf.generate(RooArgSet(mass12,mass13,mES,F),proto1);
//     RooDataSet* data3 = ccpdf.generate(RooArgSet(mass12,mass13,mES,F),proto3);
//     RooDataSet* data4 = bbpdf.generate(RooArgSet(mass12,mass13,mES,F),proto4); 
    

    RooDataSet* data = SigDalitzPdf.generate(RooArgSet(mES,F,mass12,mass13),proto);
    //RooDataSet* data = sigplus.generate(RooArgSet(mass12,mass13),proto);
    //RooDataSet* data = sigPdf.generate(RooArgSet(mass12,mass13),proto);
    RooDataSet* data1 = dpiDalitzPdf.generate(RooArgSet(mES,F,mass12,mass13),proto1);
    RooDataSet* data4 = bbDalitzPdf.generate(RooArgSet(mES,F,mass12,mass13),proto4); 
    RooDataSet* data3 = contDalitzPdf.generate(RooArgSet(mES,F,mass12,mass13),proto3);




    //append all the dataset into one for final fit
    data.append(*data1);
    //data.append(*data2);   
    data.append(*data3);
    data.append(*data4);
    
    
    
    //Fit pdf to toy
    RooFitResult* fitRes = model.fitTo(*data,"2hrmtve");
    //RooFitResult* fitRes = modelDalitz.fitTo(*data,"2hrmtve");
   
    
    //Check the quality of the fit, reject the fit
    //with bad error matrix or migrad failed
    if (fitRes->status()!=0 || fitRes->covQual()!=3)   { 
      cout << "The Fit is NOT successful" << endl;
      bb=1;
    }
    else {
      cout << "This is a good fit" << endl;
      
      
      //******************************************************
      //Get the value of the fit, and dump into a ASCII file
      //So people can read it in either PAW or ROOT very easily
      //*******************************************************
      
      double ampfit = ((RooRealVar*)fitRes->floatParsFinal()->find("amp"))->getVal();
      double ampint = ((RooRealVar*)fitRes->floatParsInit()->find("amp"))->getVal();
      double amperror = ((RooRealVar*)fitRes->floatParsFinal()->find("amp"))->getError();
      
      
      double plusfit = ((RooRealVar*)fitRes->floatParsFinal()->find("plusphase"))->getVal();
      double plusint = ((RooRealVar*)fitRes->floatParsInit()->find("plusphase"))->getVal();
      double pluserror = ((RooRealVar*)fitRes->floatParsFinal()->find("plusphase"))->getError();
      
      double minusfit = ((RooRealVar*)fitRes->floatParsFinal()->find("minusphase"))->getVal();
      double minusint = ((RooRealVar*)fitRes->floatParsInit()->find("minusphase"))->getVal();
      double minuserror = ((RooRealVar*)fitRes->floatParsFinal()->find("minusphase"))->getError();
      
      double amppull = (ampfit-ampint)/amperror;
      double pluspull = (plusfit-plusint)/pluserror;
      double minuspull = (minusfit-minusint)/minuserror;
      
      //Now convert back to \gamma and \delta value
      double gammafit = 0.5*(plusfit - minusfit);
      double gammaint = 0.5*(plusint - minusint);
      double gammaerr = 0.5*pow(pluserror*pluserror+minuserror*minuserror,0.5);
      double gammapull = (gammafit-gammaint)/gammaerr;
      
      double deltafit = 0.5*(plusfit + minusfit);
      double deltaint = 0.5*(plusint + minusint);
      double deltaerr = 0.5*pow(pluserror*pluserror+minuserror*minuserror,0.5);
      double deltapull = (deltafit - deltaint)/deltaerr;
      
      //double nSigfit = ((RooRealVar*)fitRes->floatParsFinal()->find("nSig"))->getVal();
      //double nSiginit  = ((RooRealVar*)fitRes->floatParsInit()->find("nSig"))->getVal();
      //double nSigerror = ((RooRealVar*)fitRes->floatParsFinal()->find("nSig"))->getError();
      
      
      //double nContfit = ((RooRealVar*)fitRes->floatParsFinal()->find("nCont"))->getVal();
      //double nContinit  = ((RooRealVar*)fitRes->floatParsInit()->find("nCont"))->getVal();
      //double nConterror = ((RooRealVar*)fitRes->floatParsFinal()->find("nCont"))->getError();
      
      
      
   
      //double nSigpull = (nSigfit-nSig_average)/nSigerror;
      //double nContpull = (nContfit-nCont_average)/nConterror;
      
      
      
      //      ofs << i << " " << ampint << " " << ampfit << " " << amperror << " " << amppull << " " << plusint << " " << plusfit << " " << pluserror << " " << pluspull << " " << minusint << " " << minusfit << " " << minuserror << " " << minuspull << " " << gammafit << " " << gammaint << " " << gammaerr << " " << gammapull << " " << deltafit << " " << deltaint << " " << deltaerr << " " << deltapull <<" "<< << nSigfit << " " << nSigerror << " " << nSigpull << " " << nSig_actual << " " << nContfit << " " << nConterror << " " << nContpull<< " " << nCont_actual <<  endl;
      ofs << i << " " << ampint << " " << ampfit << " " << amperror << " " << amppull << " " << plusint << " " << plusfit << " " << pluserror << " " << pluspull << " " << minusint << " " << minusfit << " " << minuserror << " " << minuspull << " " << gammafit << " " << gammaint << " " << gammaerr << " " << gammapull << " " << deltafit << " " << deltaint << " " << deltaerr << " " << deltapull << endl;
      
      
      cout << 12345678 << " " << i << " " << ampint << " " << ampfit << " " << amperror << " " << amppull << " " << plusint << " " << plusfit << " " << pluserror << " " << pluspull << " " << minusint << " " << minusfit << " " << minuserror << " " << minuspull << " " << gammafit << " " << gammaint << " " << gammaerr << " " << gammapull << " " << deltafit << " " << deltaint << " " << deltaerr << " " << deltapull << endl;
      
    }  //end the else loop
    
 
    //Plot the pdf for the B+ -> D0bar K+ events
    //If you want to make a pdf projection plot, uncomment the model->plotOn line
    //Caution: Since it require normalization during the projection, it can be slow
    //sometimes
    
    if(Nexp==1 && bb!=1){

      RooPlot* xframe = mass12.frame();
      data->plotOn(xframe,Cut("charge==charge::Bplus"));
      charge="Bplus";
      // model->plotOn(xframe,Slice(charge),ProjWData(charge,*data));
      
      RooPlot* yframe = mass13.frame();
      data->plotOn(yframe,Cut("charge==charge::Bplus"));
      // model->plotOn(yframe,Slice(charge),ProjWData(charge,*data));
      
      RooDataSet* dataplus = data.reduce("charge==charge::Bplus");
    
      TCanvas *c1 = new TCanvas("c1","RooPlot for B+ -> D0bar K+",1200,400);
      c1->Divide(3,1);
      c1->cd(1);xframe->Draw();
      c1->cd(2);yframe->Draw();
      c1->cd(3);dataplus->tree()->Draw("mass12:mass13");
    
      //Plot the pdf for the B- -> D0 K- events
      
      RooPlot* xframe = mass12.frame();
      data->plotOn(xframe,Cut("charge==charge::Bminus"));
      charge="Bminus";
      // model->plotOn(xframe,Slice(charge),ProjWData(charge,*data));
      
      RooPlot* yframe = mass13.frame();
      data->plotOn(yframe,Cut("charge==charge::Bminus"));
      // model->plotOn(yframe,Slice(charge),ProjWData(charge,*data));
      
      RooDataSet* dataminus = data.reduce("charge==charge::Bminus");
      
      TCanvas *d1 = new TCanvas("d1","RooPlot for B- -> D0 K-",1200,400);
      d1->Divide(3,1);
      d1->cd(1);xframe->Draw();
      d1->cd(2);yframe->Draw();
      d1->cd(3);dataminus->tree()->Draw("mass12:mass13");
      
    }
   
    //cleanup
    delete fitRes;
    delete contin;
    delete data;
    delete data1;
    //delete data2;
    delete data3;
    delete data4;
    
  } //end the for loop
  
  
  
}
























