//This very simply macro is intent to 
//extract the signal and background yields
//of B->DK using Generic BBbar Monte Carlo Events.
//written by Ben Lau and Elisabetta

// Last update: Feb 04, 2004

luca()
{
  //define momentum variables for the bachlor's Kaon tracks
  RooRealVar px1 ("px1"         , "p_{x,1}"                , -5, 5, "GeV");        
  RooRealVar py1 ("py1"         , "p_{y,1}"                , -5, 5, "GeV");        
  RooRealVar pz1 ("pz1"         , "p_{z,1}"                , -5, 5, "GeV");        

  //Define some constants here
  RooRealVar kMass  ("kMass"     , "Kaon Mass"          , 0.493677, "GeV");
  RooRealVar piMass ("piMass"    , "Pion Mass"          , 0.13957 , "GeV");
  RooRealVar bMass  ("bMass"     , "B Mass"            , 5.279   , "GeV");
  RooRealVar p00 ("p00","p00",-1.06301);
  RooRealVar p0 ("p0","p0",-1.17409);
  RooRealVar p2 ("p2","p2",-11.8237);
  RooRealVar frazione ("frazione","frazione",0.729393);

  // The momentum magnitude is used by Delta E
  RooFormulaVar p1     ("p1", "p1", "sqrt(px1*px1+py1*py1+pz1*pz1)", RooArgList(px1, py1, pz1));

  RooRealVar nSig("nSig", "Number of Signal Events", 2700,-1000000,1000000);
  RooRealVar nDPi("nDPi","Number of Dpi events", 30000,-1000000,1000000);
  RooRealVar nBkg("nBkg", "Number of Background Kaon Events", 160000,-1000000,1000000);   

  RooRealVar mES("mES","m_{ES}", 5.2, 5.29, "GeV");
  RooRealVar mESMean("mESMean", "mean mES", 5.27923,"GeV");
  RooRealVar mESSigma("mESSigma", "mES resolution", 0.00264071, "GeV");
    
  RooRealVar m0("m0", "ARGUS end point", 5.28984, "GeV");
  RooRealVar argPar("argPar", "background shape parameter", -21.5466);

  RooRealVar mESMeanbkg("mESMeanbkg", "mean mES",5.27927,"GeV");
  RooRealVar mESSigmabkg("mESSigmabkg", "mES ",0.00293502);
  RooRealVar frac("frac","fraction gauss/argus",0.848840);
		  
  RooGaussian gausMES("gausMES","mES gaussianbackground shape", mES,mESMeanbkg,mESSigmabkg);
  RooArgusBG argMES("argMES","mES ARGUS background shape", mES, m0, argPar);
  RooGaussian sigMES("sigMES","signal mES Gaussian", mES, mESMean, mESSigma);
  RooAddPdf bkgMES("bkgMES", "bkg MES argus+Gaussian",argMES ,gausMES,frac );
  // RooArgusBG bkgMES("bkgMES","mES ARGUS background shape", mES, m0, argPar);   //bkg is a ARGUS function
  
  RooRealVar deltaE("deltaE","#DeltaE", -0.1, 0.2, "GeV");  // cut lower delta_E with -0.1 to remove background from D*
  RooRealVar deltaEMean("deltaEMean", "mean delta E",0.000562981,"GeV");
  RooRealVar deltaESigma("deltaESigma", "delta E resolution",0.0149007,"GeV");
  RooRealVar deltaEPiSigma("deltaEPiSigma","delta E sigma for Dpi",0.0170132,"GeV"); // sigma for the Dpi events

  RooRealVar deltaEMean1("deltaEMean1", "mean delta E",-0.000575906,"GeV");
  RooRealVar deltaESigma1("deltaESigma1", "delta E resolution",0.0170132,"GeV");
  RooFormulaVar deltaEPiMean("deltaEPiMean" , "DeltaE mean for Dpi", "1.14*(sqrt(kMass*kMass+p1*p1)-sqrt(piMass*piMass+p1*p1))+deltaEMean",RooArgList(p1, kMass, piMass, deltaEMean));

    //Construct the pdf for delta_E
    RooGaussian sigDeltaEK("sigDeltaEK", "signal Delta E Gaussian for DK", deltaE, deltaEMean, deltaESigma);  //signal DK is a gaussian
    RooGaussian sigDeltaEPi("sigDeltaEPi","signal Delta E Gaussian for Dpi",deltaE,deltaEPiMean,deltaEPiSigma);
    RooPolynomial bkgDeltaE_pol1("bkgDeltaE_pol1","pol1",deltaE,p00);
    RooPolynomial bkgDeltaE_pol2("bkgDeltaE_pol2","pol2",deltaE,RooArgList(p0,p2));
    RooAddPdf bkgDeltaPi("bkgDeltaPi","bkgPi",sigDeltaEPi,bkgDeltaE_pol2,frazione);
 
  RooRealVar
    F("F","Fisher", -2.0, 3.0),
    sigFMean("sigFMean", "signal mean F",0.589887),
    sigFSigmaL("sigFSigmaL", "signal sigma F left",0.304565),
    sigFSigmaR("sigFSigmaR", "signal sigma F right",0.489238),
    bkgFMeanC("bkgFMeanC", "core mean of F",0.363245),
    bkgFSigmaC("bkgFSigmaC", "core F resolution",0.273993),
    bkgFMeanT("bkgFMeanT", "tail mean of F",0.884508),
    bkgFSigmaT("bkgFSigmaT", "tail sigma of F",0.463356),
    coreFrac("coreFrac", "fraction of core Gaussian", 0.924445);

  RooBifurGauss sigF("sigF","signal Fisher Bifurcated Gaussian", F, sigFMean, sigFSigmaL, sigFSigmaR); 
  // RooBifurGauss bkgF("bkgF","bkg Fisher Bifurcated Gaussian", F, bkgFMeanC, bkgFSigmaC,bkgFSigmaT); 
  RooGaussian bkgFC("bkgFC", "bkg F core Gaussian", F, bkgFMeanC, bkgFSigmaC);
  RooGaussian bkgFT("bkgFT", "bkg F tail Gaussian", F, bkgFMeanT, bkgFSigmaT);
  RooAddPdf bkgF("bkgF", "bkg F double Gaussian", bkgFC, bkgFT, coreFrac); 
  //RooBifurGauss bkgF("bkgF","bkg Fisher Bifurcated Gaussian", F, bkgFMeanC, bkgFSigmaC, bkgFSigmaT); 
 
  RooProdPdf DKPdf("DKPdf", "Signal DK PDF", RooArgList(sigMES,sigDeltaEK,sigF));   //pdf for the DK events
  // RooProdPdf DKPdf("DKPdf", "Signal DK PDF", RooArgList(sigMES,sigF));
  RooProdPdf DpiPdf("DpiPdf", "Signal Dpi PDF", RooArgList(sigMES,sigDeltaEPi,sigF)); //pdf for the Dpi events
  RooProdPdf BkgPdf("BkgPdf", "Continuum Bkg PDF", RooArgList(bkgMES,bkgDelta_pol1,bkgF)); //pdf for the combinatorics events
  //  RooProdPdf BkgPdf("BkgPdf", "Continuum Bkg PDF", RooArgList(bkgMES,bkgF));
  // create the model
  RooAddPdf model("model", "Model", RooArgList(DKPdf,DpiPdf,BkgPdf), RooArgList(nSig,nDPi,nBkg));
  // RooAddPdf model("model", "Model", RooArgList(DKPdf,BkgPdf), RooArgList(nSig,nBkg));

       //The format of the flatfile are as follow:
       //mES,delta_E,Fisher,px1,py1,pz1

  RooArgList temp;
  temp.add(RooArgList(mES,deltaE,F));
  temp.add(RooArgList(px1,py1,pz1));
  RooDataSet* data = RooDataSet::read("tot_ks_1.txt",temp);

  // perform the fit
  // (option "e" for extended ML fit!)



    RooArgSet noNormSet(px1,py1,pz1);  //make sure we don't normalize wrt to px1,py1,pz1
    RooFitResult* fitRes = model.fitTo(*data,noNormSet,"emhrtv"); //option e for extended likelihood fit

  
    //RooPlot of mES
	  RooPlot *mESPlot = data->plotOn(mES.frame(100));
	  model->plotOn(mESPlot);
	  model->plotCompOn(mESPlot, BkgPdf);
	  mESPlot->getAttLine()->SetLineStyle(kDashed);


	 //  //RooPlot of Delta_E
	  RooPlot *deltaEPlot = data->plotOn(deltaE.frame(100));
	  model->plotOn(deltaEPlot, ProjWData(noNormSet,*data));
          model->plotOn(deltaEPlot ,ProjWData(noNormSet,*data), Components(sigDeltaEPi));
          deltaEPlot->getAttLine()->SetLineStyle(kDashed);
	  
	  //RooPlot of Fisher
  RooPlot *fisherPlot = data->plotOn(F.frame(100));
  model->plotOn(fisherPlot);
  model->plotCompOn(fisherPlot, BkgPdf);
  fisherPlot->getAttLine()->SetLineStyle(kDashed);
	


  
  
  TCanvas *c1 = new TCanvas("c1","all events",1200, 400);
  c1->Divide(3,1);
  c1->cd(1); mESPlot->Draw();
  c1->cd(3); deltaEPlot->Draw();
  c1->cd(2); fisherPlot->Draw();
  

    
}
















