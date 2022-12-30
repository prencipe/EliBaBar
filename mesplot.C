{
gROOT->Macro("RooLogon.C");
gROOT->SetStyle("BABAR");
TFile *_file0 = TFile::Open("run123456-largephi-noDE.root");

TH1F *hSig=new TH1F("hSig","",90,5.2,5.29);
TH1F *hBg=new TH1F("hBg","",90,5.2,5.29);
hSig->SetXTitle("m_{ES} (GeV/c^{2})");
hSig->SetYTitle("Events/ 1 MeV/c^{2}");
t1.Draw("Mes>>hSig", "abs(DeltaE)<0.03");
t1.Draw("Mes>>hBg", "abs(DeltaE)>0.04 && abs(DeltaE)<0.07", "same");

hBg->SetFillColor(5);
hBg->SetLineColor(5);
hSig.Draw("e");
hBg.Draw("same");
hSig.Draw("esame");
hSig->Draw("Axissame");

c1.SaveAs("PLOT-BAD/PRL_Mes_SignSideb_Bch.eps");
c1.SaveAs("PLOT-BAD/PRL_Mes_SignSideb_Bch.root");

TH1F *hSig=new TH1F("hSig","",60, 0.98, 1.1);
TH1F *hBg=new TH1F("hBg","",60, 0.98, 1.1);
hSig->SetXTitle("m(K^{+} K^{-}) (GeV/c^{2})");
hSig->SetYTitle("Events/ 2 MeV/c^{2}");

t1.Draw("phiMass>>hSig", "Mes>5.27 && abs(DeltaE)<0.03");
t1.Draw("phiMass>>hBg", "Mes>5.27 && abs(DeltaE)>0.04 && abs(DeltaE)<0.07", "same");
hBg->SetFillColor(5);
hBg->SetLineColor(5);
hSig.Draw("e");
hBg.Draw("same");
hSig.Draw("esame");
hSig->Draw("Axissame");

c1.SaveAs("PLOT-BAD/PRL_Phi_SignSideb_Bch.eps");
c1.SaveAs("PLOT-BAD/PRL_Phi_SignSideb_Bch.root");


TH1F *hSig=new TH1F("hSig","",90,5.2,5.29);
TH1F *hBg=new TH1F("hBg","",90,5.2,5.29);
hSig->SetXTitle("m_{ES} (GeV/c^{2})");
hSig->SetYTitle("Events/ 1 MeV/c^{2}");
t1.Draw("Mes>>hSig", "abs(DeltaE)<0.03 && phiMass>1.004 && phiMass<1.034");
t1.Draw("Mes>>hBg", "abs(DeltaE)>0.04 && abs(DeltaE)<0.07 && phiMass>1.004 && phiMass<1.034", "same");

hBg->SetFillColor(5);
hBg->SetLineColor(5);
hSig.Draw("e");
hBg.Draw("same");
hSig.Draw("esame");
hSig->Draw("Axissame");

c1.SaveAs("PLOT-BAD/PRL_Mes_PhiCut_SignSideb_Bch.eps");
c1.SaveAs("PLOT-BAD/PRL_Mes_PhiCut_SignSideb_Bch.root");

}
