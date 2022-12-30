void KKK(){
gROOT->Macro("RooLogon.C");
gROOT->SetStyle("BABAR");
//TFile *_file0 = TFile::Open("newB0-123456.root");
TFile *_file0 = TFile::Open("B0tris.root");
//file0-2novembre.root e' il file giusto.

TH1F *hSigMes=new TH1F("hSigMes","",45,5.2,5.29);
TH1F *hBgMes=new TH1F("hBgMes","",45,5.2,5.29);

TH1F *hSigDe=new TH1F("hSigDe","",40,-0.1,0.1);
TH1F *hBgDe=new TH1F("hBgDe","",40,-0.1,0.1);

TH1F *hSigM12e=new TH1F("hSigM12e","",68,4.116371,4.796371);
TH1F *hBgM12e=new TH1F("hBgM12e","",68,4.116371,4.796371);

TH1F *hSigM12m=new TH1F("hSigM12m","",68,4.116371,4.796371);
TH1F *hBgM12m=new TH1F("hBgM12m","",68,4.116371,4.796371);

TH1F *hSigM12=new TH1F("hSigM12","",68,4.116371,4.796371);
TH1F *hBgM12=new TH1F("hBgM12","",68,4.116371,4.796371);

TH1F *hSigM1240=new TH1F("hSigM1240","",17,4.116371,4.796371);
TH1F *hBgM1240=new TH1F("hBgM1240","",17,4.16371,4.796371);


TH1F *hSigPhi=new TH1F("hSigPhi","",60, 0.98, 1.1);
TH1F *hBgPhi=new TH1F("hBgPhi","",60, 0.98, 1.1);


TH1F *hSigM13=new TH1F("hSigM13","",80,3.5,4.3);
TH1F *hBgM13=new TH1F("hBgM13","",80,3.5,4.3);

TH1F *hSigM23=new TH1F("hSigM23","",70,1.5,2.2);
TH1F *hBgM23=new TH1F("hBgM23","",70,1.5,2.2);


hSigPhi->SetXTitle("m(K^{+} K^{-}) (GeV/c^{2})");
hSigPhi->SetYTitle("Events/ 2 MeV/c^{2}");

hSigDe->SetXTitle("#Delta E (GeV/c^{2})");
hSigDe->SetYTitle("Events/ 5 MeV/c^{2}");

hSigMes->SetXTitle("m_{ES} (GeV/c^{2})");
hSigMes->SetYTitle("Events/ 2 MeV/c^{2}");

hSigM12e->SetXTitle("e^{+}e^{-}K^{+}K^{-} (GeV/c^{2})");
hSigM12e->SetYTitle("Events/ 10 MeV/c^{2}");


hSigM12m->SetXTitle("#mu^{+}#mu^{-}K^{+}K^{-} (GeV/c^{2})");
hSigM12m->SetYTitle("Events/ 10 MeV/c^{2}");

hSigM12->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM12->SetYTitle("Events/ 10 MeV/c^{2}");

hSigM1240->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM1240->SetYTitle("Events/ 40 MeV/c^{2}");

hSigM23->SetXTitle("m_{KKK_{S}}(GeV/c^{2})");
hSigM23->SetYTitle("Events/ 10 MeV/c^{2}");



t1->Draw("Mes>>hSigMes", "abs(DeltaE)<0.025&& TMath::Prob(BChi2,B0Ndof)>0.001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("Mes>>hBgMes", "abs(DeltaE)>0.04 && abs(DeltaE)<0.065 &&TMath::Prob(BChi2,B0Ndof)>0.001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("DeltaE>>hSigDe", "abs(DeltaE)<0.1&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("DeltaE>>hBgDe", "Mes<5.254&&Mes<5.265&&abs(DeltaE)<0.1&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)","SAME");

t1->Draw("TMath::Sqrt(BM12)>>hSigM12e", "abs(DeltaE)<0.03&&Mes>5.27&&JPdaughterOne==-11&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)>>hBgM12e", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&JPdaughterOne==-11&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)>>hSigM12m", "abs(DeltaE)<0.03&&Mes>5.27&&JPdaughterOne==-13&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)>>hBgM12m", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&JPdaughterOne==-13&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");


t1->Draw("TMath::Sqrt(BM12)>>hSigM12", "abs(DeltaE)<0.03&&Mes>5.27&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)>>hBgM12", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)>>hSigM1240", "abs(DeltaE)<0.03&&Mes>5.27&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)>>hBgM1240", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM23)-phiMass+1.019455>>hSigM23", "abs(DeltaE)<0.03&&Mes>5.27&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM23)-phiMass+1.019455>>hBgM23", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");


t1->Draw("phiMass>>hSigPhi", "Mes>5.27 && abs(DeltaE)<0.02&&TMath::Prob(BChi2,B0Ndof)>0.001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("phiMass>>hBgPhi", "Mes>5.27 && abs(DeltaE)>0.04 && abs(DeltaE)<0.06&&TMath::Prob(BChi2,B0Ndof)>0.001&&KsMass>0.485&&KsMass<0.515&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

hBgMes->SetFillColor(5);
//hBgMes->SetLineColor(5);
hBgDe->SetFillColor(5);
//hBgDe->SetLineColor(5);
hBgM12e->SetFillColor(5);
//hBgM12e->SetLineColor(5);
hBgM12m->SetFillColor(5);
//hBgM12m->SetLineColor(5);
hBgM12->SetFillColor(5);
hBgM13->SetFillColor(5);
hBgM23->SetFillColor(5);
hBgM1240->SetFillColor(5);
//hBgM12->SetLineColor(5);
hBgPhi->SetFillColor(5);
//hBgPhi->SetLineColor(5);


TCanvas *e1= new TCanvas("e1", "mes",204,49,700,500);
hSigMes->Draw("e");
hBgMes->Draw("same");
hSigMes->Draw("esame");
hSigMes->Draw("Axissame");

TCanvas *e2= new TCanvas("e2", "de",204,49,700,500);
hSigDe->Draw("e");
hBgDe->Draw("same");
hSigDe->Draw("esame");
hSigDe->Draw("Axissame");

TCanvas *e3= new TCanvas("e3", "m12e",204,49,700,500);
hSigM12e->Draw("e");
hBgM12e->Draw("same");
hSigM12e->Draw("esame");
hSigM12e->Draw("Axissame");

TCanvas *e4= new TCanvas("e4", "m12m",204,49,700,500);
hSigM12m->Draw("e");
hBgM12m->Draw("same");
hSigM12m->Draw("esame");
hSigM12m->Draw("Axissame");

TCanvas *e5= new TCanvas("e5", "phi",204,49,700,500);
hSigPhi->Draw("e");
hBgPhi->Draw("same");
hSigPhi->Draw("esame");
hSigPhi->Draw("Axissame");

TCanvas *e6= new TCanvas("e6", "m12-40",204,49,700,500);
hSigM1240->Draw("e");
hBgM1240->Draw("same");
hSigM1240->Draw("esame");
hSigM1240->Draw("Axissame");

TCanvas *e6= new TCanvas("e7", "m23",204,49,700,500);
hSigM23->Draw("e");
hBgM23->Draw("same");
hSigM23->Draw("esame");
hSigM23->Draw("Axissame");


mes->SaveAs("PRL-PLOT/PRL-Mes_SignSideb_B0-nophicut.eps");
de->SaveAs("PRL-PLOT/PRL-De_SignSideb_B0-nophicut.eps");
m12e->SaveAs("PRL-PLOT/PRL-m12_SignSideb_B0-nophicut-E.eps");
m12m->SaveAs("PRL-PLOT/PRL-m12_SignSideb_B0-nophicut-M.eps");
phi->SaveAs("PRL-PLOT/PRL_Phi_SignSideb_B0.eps");





//c1.SaveAs("PLOT-BAD/Mes_SignSideb_Bch.root");

 TCanvas *c10 = new TCanvas("c10","PRL-fig2",1800, 1500);
  c10->Divide(2,3);
  c10->cd(1); hSigMes->Draw("e");
              hBgMes->Draw("same");
              hSigMes->Draw("esame");
              hSigMes->Draw("Axissame");

       c10->cd(2);  
              hSigM12e->Draw("e");
              hBgM12e->Draw("same");
              hSigM12e->Draw("esame");
              hSigM12e->Draw("Axissame");

      c10->cd(3); 
              hSigDe->Draw("e");
              hBgDe->Draw("same");
              hSigDe->Draw("esame");
              hSigDe->Draw("Axissame");

       c10->cd(4);  
              hSigM12m->Draw("e");
              hBgM12m->Draw("same");
              hSigM12m->Draw("esame");
              hSigM12m->Draw("Axissame");
         c10->cd(5);  
              hSigPhi->Draw("e");
              hBgPhi->Draw("same");
              hSigPhi->Draw("esame");
              hSigPhi->Draw("Axissame");

c10->cd(6);

hSigM12->SetYTitle("Events/ 10 MeV/c^{2}");
hSigM12->SetXTitle("J/#psiK^{+}K^{-} (GeV/c^{2})");
hSigM12->Draw("e");
hBgM12->Draw("same");
hSigM12->Draw("esame");
hSigM12->Draw("Axissame");

  
c10->Draw();
c10->SaveAs("PRL-PLOT/PRL-gif1-Bch.eps");
}

void phiKs(){

gROOT->Macro("RooLogon.C");
gROOT->SetStyle("BABAR");
TFile *_file0 = TFile::Open("B0tris.root");

TH1F *hSigMes2=new TH1F("hSigMes2","",45,5.2,5.29);
TH1F *hBgMes2=new TH1F("hBgMes2","",45,5.2,5.29);

TH1F *hSigDe2=new TH1F("hSigDe2","",40,-0.1,0.1);
TH1F *hBgDe2=new TH1F("hBgDe2","",40,-0.1,0.1);

TH1F *hSigM12e2=new TH1F("hSigM12e2","",68,4.1,4.8);
TH1F *hBgM12e2=new TH1F("hBgM12e2","",68,4.1,4.8);

TH1F *hSigM12m2=new TH1F("hSigM12m2","",68,4.1,4.8);
TH1F *hBgM12m2=new TH1F("hBgM12m2","",68,4.1,4.8);

TH1F *hSigM122=new TH1F("hSigM122","",68,4.1,4.8);
TH1F *hBgM122=new TH1F("hBgM122","",68,4.1,4.8);

TH1F *hSigM1240=new TH1F("hSigM1240","",17,4.116371,4.796371);
TH1F *hBgM1240=new TH1F("hBgM1240","",17,4.116371,4.796371);


TH1F *hSigM1240e=new TH1F("hSigM1240e","",17,4.116371,4.796371);
TH1F *hBgM1240e=new TH1F("hBgM1240e","",17,4.116371,4.796371);

TH1F *hSigM1240m=new TH1F("hSigM1240m","",17,4.116371,4.796371);
TH1F *hBgM1240m=new TH1F("hBgM1240m","",17,4.116371,4.796371);



TH1F *hSigPhi2=new TH1F("hSigPhi2","",60, 0.98, 1.1);
TH1F *hBgPhi2=new TH1F("hBgPhi2","",60, 0.98, 1.1);



TH1F *hSigM13=new TH1F("hSigM13","",17,3.6,4.3);
TH1F *hBgM13=new TH1F("hBgM13","",17,3.6,4.3);

TH1F *hSigM23=new TH1F("hSigM23","",17,1.5,2.2);
TH1F *hBgM23=new TH1F("hBgM23","",17,1.5,2.2);


hSigPhi2->SetXTitle("m(K^{+} K^{-}) (GeV/c^{2})");
hSigPhi2->SetYTitle("Events/ 2 MeV/c^{2}");

hSigDe2->SetXTitle("#Delta E (GeV/c^{2})");
hSigDe2->SetYTitle("Events/ 5 MeV/c^{2}");

hSigMes2->SetXTitle("m_{ES} (GeV/c^{2})");
hSigMes2->SetYTitle("Events/ 2 MeV/c^{2}");

hSigM12e2->SetXTitle("e^{+}e^{-}K^{+}K^{-} (GeV/c^{2})");
hSigM12e2->SetYTitle("Events/ 10 MeV/c^{2}");


hSigM12m2->SetXTitle("#mu^{+}#mu^{-}K^{+}K^{-} (GeV/c^{2})");
hSigM12m2->SetYTitle("Events/ 10 MeV/c^{2}");

hSigM122->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM122->SetYTitle("Events/ 10 MeV/c^{2}");


hSigM1240->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM1240->SetYTitle("Events/ 40 MeV/c^{2}");


hSigM1240e->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM1240e->SetYTitle("Events/ 40 MeV/c^{2}");


hSigM1240m->SetXTitle("J/#psi#phi(GeV/c^{2})");
hSigM1240m->SetYTitle("Events/ 40 MeV/c^{2}");

hSigM13->SetXTitle("J/#psiK^{0}_{S}(GeV/c^{2})");
hSigM13->SetYTitle("Events/ 40 MeV/c^{2}");

hSigM23->SetXTitle("#phiK^{0}_{S}(GeV/c^{2})");
hSigM23->SetYTitle("Events/ 40 MeV/c^{2}");



t1->Draw("Mes>>hSigMes2", "abs(DeltaE)<0.015&& TMath::Prob(BChi2,B0Ndof)>0.0001 &&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("Mes>>hBgMes2", "abs(DeltaE)>0.025 && abs(DeltaE)<0.055 &&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("DeltaE>>hSigDe2", "abs(DeltaE)<0.1&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("DeltaE>>hBgDe2", "Mes>5.245&&Mes<5.265&&abs(DeltaE)<0.1&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM12e2", "abs(DeltaE)<0.03&&Mes>5.274&&JPdaughterOne==-11&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM12e2", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&JPdaughterOne==-11&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM12m2", "abs(DeltaE)<0.03&&Mes>5.274&&JPdaughterOne==-13&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM12m2", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&JPdaughterOne==-13&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");


t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM122", "abs(DeltaE)<0.03&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM122", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM1240", "abs(DeltaE)<0.03&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM1240", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM1240e", "abs(DeltaE)<0.03&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM1240e", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");


t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hSigM1240m", "abs(DeltaE)<0.03&&Mes>5.274&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM12)-phiMass+1.019455>>hBgM1240m", "abs(DeltaE)>0.04 && Mes>5.274 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");




t1->Draw("phiMass>>hSigPhi2", "Mes>5.274 && abs(DeltaE)<0.03&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("phiMass>>hBgPhi2", "Mes>5.274 && abs(DeltaE)>0.04 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM13)-KsMass+0.497614>>hSigM13", "abs(DeltaE)<0.03&&Mes>5.27&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM13)-KsMass+0.497614>>hBgM13", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");

t1->Draw("TMath::Sqrt(BM23)-phiMass+1.019455>>hSigM23", "abs(DeltaE)<0.03&&Mes>5.27&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)");
t1->Draw("TMath::Sqrt(BM23)-phiMass+1.019455>>hBgM23", "abs(DeltaE)>0.04 && Mes>5.27 && abs(DeltaE)<0.07&&TMath::Prob(BChi2,B0Ndof)>0.0001&&phiMass>1.004&&phiMass<1.034&&(sMmm<=0||sMmm>3.056&&sMmm<3.14)&&(sMee<=0||sMee>2.97&&sMee<3.14)", "same");





hBgMes2->SetFillColor(5);
//hBgMes2->SetLineColor(5);
hBgDe2->SetFillColor(5);
//hBgDe2->SetLineColor(5);
hBgM12e2->SetFillColor(5);
//hBgM12e2->SetLineColor(5);
hBgM12m2->SetFillColor(5);
//hBgM12m2->SetLineColor(5);
hBgM122->SetFillColor(5);
hBgM1240->SetFillColor(5);
hBgM1240e->SetFillColor(5);
hBgM1240m->SetFillColor(5);
hBgM13->SetFillColor(5);
hBgM23->SetFillColor(5);
//hBgM122->SetLineColor(5);
hBgPhi2->SetFillColor(5);
//hBgPhi2->SetLineColor(5);


TCanvas *e1= new TCanvas("e1", "mes",200,10,700,500);
hSigMes2->Draw("e");
hBgMes2->Draw("same");
hSigMes2->Draw("esame");
hSigMes2->Draw("Axissame");

TCanvas *e2= new TCanvas("e2", "de",200,10,700,500);
hSigDe2->Draw("e");
hBgDe2->Draw("same");
hSigDe2->Draw("esame");
hSigDe2->Draw("Axissame");

TCanvas *e3= new TCanvas("e3", "m12e",200,10,700,500);
hSigM12e2->Draw("e");
hBgM12e2->Draw("same");
hSigM12e2->Draw("esame");
hSigM12e2->Draw("Axissame");

TCanvas *e4= new TCanvas("e4", "m12m",200,10,700,500);
hSigM12m2->Draw("e");
hBgM12m2->Draw("same");
hSigM12m2->Draw("esame");
hSigM12m2->Draw("Axissame");

TCanvas *e5= new TCanvas("e3", "phi",200,10,700,500);
hSigPhi2->Draw("e");
hBgPhi2->Draw("same");
hSigPhi2->Draw("esame");
hSigPhi2->Draw("Axissame");

TCanvas *e6= new TCanvas("e6", "m12-40",200,10,700,500);
hSigM1240->Draw("e");
hBgM1240->Draw("same");
hSigM1240->Draw("esame");
hSigM1240->Draw("Axissame");

TCanvas *e60= new TCanvas("e60", "m12e",200,10,700,500);
hSigM1240e->Draw("e");
hBgM1240e->Draw("same");
hSigM1240e->Draw("esame");
hSigM1240e->Draw("Axissame");

TCanvas *e61= new TCanvas("e61", "m12m",200,10,700,500);
hSigM1240m->Draw("e");
hBgM1240m->Draw("same");
hSigM1240m->Draw("esame");
hSigM1240m->Draw("Axissame");



TCanvas *e7= new TCanvas("e7", "m13",200,10,700,500);
hSigM13->Draw("e");
hBgM13->Draw("same");
hSigM13->Draw("esame");
hSigM13->Draw("Axissame");


TCanvas *e8= new TCanvas("e8", "m23",200,10,700,500);
hSigM23->Draw("e");
hBgM23->Draw("same");
hSigM23->Draw("esame");
hSigM23->Draw("Axissame");




e1->SaveAs("PRL-PLOT/PRL-Mes_SignSideb_B0-phicut.eps");
e2->SaveAs("PRL-PLOT/PRL-De_SignSideb_B0-phicut.eps");
e3->SaveAs("PRL-PLOT/PRL-m12_SignSideb_B0-phicut-E.eps");
e4->SaveAs("PRL-PLOT/PRL-m12_SignSideb_B0-phicut-M.eps");
e5->SaveAs("PRL-PLOT/PRL_Phi_SignSideb_B0-phicut.eps");
e6->SaveAs("PRL-PLOT/PRL-m12_SignSideb_B0-phicut.eps");


  TCanvas *c41 = new TCanvas("c41", "m(J/psi phi, efficiency (electrons)",200,10,700,500);
    TH1F *gre = new TH1F("gre","",70,4.116371,4.796371);
    TH1F *histo_a5 = new TH1F("histo_a5","",70,4.116371,4.796371);

   gre->Fill(4.121371,0.0421);
   gre->Fill(4.131371,0.0429);
   gre->Fill(4.141371,0.0529);
   gre->Fill(4.151371,0.0525);
   gre->Fill(4.161371,0.0711);
   gre->Fill(4.171371,0.0710);
   gre->Fill(4.181371,0.0685);
   gre->Fill(4.191371,0.0649);
   gre->Fill(4.201371,0.0804);
   gre->Fill(4.211371,0.0757);
   gre->Fill(4.221371,0.0849);
   gre->Fill(4.231371,0.0867);
   gre->Fill(4.241371,0.0890);
   gre->Fill(4.251371,0.0898);
   gre->Fill(4.261371,0.0905);
   gre->Fill(4.271371,0.0965);
   gre->Fill(4.281371,0.108);
   gre->Fill(4.291371,0.0987);
   gre->Fill(4.301371,0.10);
   gre->Fill(4.311371,0.10);
   gre->Fill(4.321371,0.109);
   gre->Fill(4.331371,0.109);
   gre->Fill(4.341371,0.107);
   gre->Fill(4.351371,0.11);
   gre->Fill(4.361371,0.114);
   gre->Fill(4.371371,0.109);
   gre->Fill(4.381371,0.113);
   gre->Fill(4.391371,0.114);
   gre->Fill(4.401371,0.109);
   gre->Fill(4.411371,0.113);
   gre->Fill(4.421371,0.114);
   gre->Fill(4.431371,0.117);
   gre->Fill(4.441371,0.112);
   gre->Fill(4.451371,0.127);
   gre->Fill(4.461371,0.119);
   gre->Fill(4.471371,0.125);
   gre->Fill(4.481371,0.118);
   gre->Fill(4.491371,0.127);
   gre->Fill(4.501371,0.120);
   gre->Fill(4.511371,0.127);
   gre->Fill(4.521371,0.126);
   gre->Fill(4.531371,0.120);
   gre->Fill(4.541371,0.123);
   gre->Fill(4.551371,0.126);
   gre->Fill(4.561371,0.131);
   gre->Fill(4.571371,0.122);
   gre->Fill(4.581371,0.132);
   gre->Fill(4.591371,0.125);
   gre->Fill(4.601371,0.138);
   gre->Fill(4.611371,0.131);
   gre->Fill(4.621371,0.128);
   gre->Fill(4.631371,0.132);
   gre->Fill(4.641371,0.137);
   gre->Fill(4.651371,0.135);
   gre->Fill(4.661371,0.134);
   gre->Fill(4.671371,0.130);
   gre->Fill(4.681371,0.133);
   gre->Fill(4.691371,0.138);
   gre->Fill(4.701371,0.129);
   gre->Fill(4.711371,0.124);
   gre->Fill(4.721371,0.140);
   gre->Fill(4.731371,0.04);
   gre->Fill(4.741371,0.04);
   gre->Fill(4.751371,0.04);
   gre->Fill(4.761371,0.04);
   gre->Fill(4.771371,0.04);
   gre->Fill(4.781371,0.01);
   gre->Fill(4.791371,0.01);
   gre->SetLineColor(2);
   gre->GetXaxis()->SetTitle("J/#psi#phi (ee) mass (GeV/c^{2})");
   gre->GetYaxis()->SetTitle("Evt/10 MeV/c^{2}");
   gre->Draw("");
   

   /*
 hSigM12e2->SetStats(0);
  gre->SetStats(0);

  hSigM12e2->SetLineColor(kBlack);
  
  TCanvas *c1 = new TCanvas("c1","transparent pad",200,10,700,500);
   TPad *pad1 = new TPad("pad1","",0,0,1,1);
   TPad *pad2 = new TPad("pad2","",0,0,1,1);
   // pad2->SetFillStyle(4000); //will be transparent
   pad1->Draw();
   pad1->cd();
   
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx();
   c1->SetTicky();
   c1->SetLeftMargin(0.12);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.16);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   hSigM12e2->Draw();
   hSigM12e2->Draw("esame");
   hSigM12e2->SetLabelColor(1);
   c1->cd();
   gStyle->SetOptStat(0);
   Double_t ymin = 0;
   Double_t ymax = gre->GetMaximum()*1.1;
   Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom
   Double_t xmin = hSigM12e2->GetBinLowEdge(1);
   Double_t xmax = hSigM12e2->GetBinLowEdge(hSigM12e2->GetNbinsX())+hSigM12e2->GetBinWidth(1);
   Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
   pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
   pad2->Draw();
   pad2->cd();
   gre->Draw("][sames");
   pad2->Update();
   TGaxis *axis = new TGaxis(xmax,ymin,xmax,ymax,ymin,ymax,50510,"+L");
   axis->SetLabelColor(1);
   axis->Draw();
   */





//hSige->SaveAs("numeriSige.C");
//hSigm->SaveAs("numeriSigm.C");
//hBge->SaveAs("numeriBge.C");
//hBgm->SaveAs("numeriBgm.C");

hSigM12e2->Sumw2();
hBgM12e2->Sumw2();
hSigM12m2->Sumw2();
hBgM12m2->Sumw2();
hSigM12e2->Add(hBgM12e2,-1);
hSigM12m2->Add(hBgM12m2,-1);
hSigM12e2->Draw("e");

c1->SaveAs("PRL-PLOT/PRL_Mx12_PhiCut_Mescut_SidebSubtrac_electrons-Bch2.eps");

hSigM12m2->Draw("e");

c1->SaveAs("PRL-PLOT/PRL_Mx12_PhiCut_Mescut_SidebSubtrac_muons-Bch2.eps");



   TCanvas *c42 = new TCanvas("c42", "m(J/psi phi, efficiency (muons)",204,49,700,500);

     TH1F *histo_grm = new TH1F("grm","",70,4.116371,4.796371); 
   TH1F *histo_a15 = new TH1F("histo_a15","",70,4.116371,4.796371);
   grm->Fill(4.121371,0.0385);
   grm->Fill(4.131371,0.0446);
   grm->Fill(4.141371,0.0494);
   grm->Fill(4.151371,0.0525);
   grm->Fill(4.161371,0.0506);
   grm->Fill(4.171371,0.0535);
   grm->Fill(4.181371,0.0631);
   grm->Fill(4.191371,0.0658);
   grm->Fill(4.201371,0.0653);
   grm->Fill(4.211371,0.0696);
   grm->Fill(4.221371,0.0759);
   grm->Fill(4.231371,0.0823);
   grm->Fill(4.241371,0.0803);
   grm->Fill(4.251371,0.0777);
   grm->Fill(4.261371,0.0709);
   grm->Fill(4.271371,0.0883);
   grm->Fill(4.281371,0.0925);
   grm->Fill(4.291371,0.0918);
   grm->Fill(4.301371,0.0934);
   grm->Fill(4.311371,0.0863);
   grm->Fill(4.321371,0.0945);
   grm->Fill(4.331371,0.104);
   grm->Fill(4.341371,0.102);
   grm->Fill(4.351371,0.103);
   grm->Fill(4.361371,0.109);
   grm->Fill(4.371371,0.1);
   grm->Fill(4.381371,0.0968);
   grm->Fill(4.391371,0.109);
   grm->Fill(4.401371,0.109);
   grm->Fill(4.411371,0.11);
   grm->Fill(4.421371,0.112);
   grm->Fill(4.431371,0.110);
   grm->Fill(4.441371,0.116);
   grm->Fill(4.451371,0.111);
   grm->Fill(4.461371,0.115);
   grm->Fill(4.471371,0.117);
   grm->Fill(4.481371,0.118);
   grm->Fill(4.491371,0.117);
   grm->Fill(4.501371,0.117);
   grm->Fill(4.511371,0.121);
   grm->Fill(4.521371,0.116);
   grm->Fill(4.531371,0.115);
   grm->Fill(4.541371,0.120);
   grm->Fill(4.551371,0.121);
   grm->Fill(4.561371,0.117);
   grm->Fill(4.571371,0.124);
   grm->Fill(4.581371,0.127);
   grm->Fill(4.591371,0.123);
   grm->Fill(4.601371,0.122);
   grm->Fill(4.611371,0.122);
   grm->Fill(4.621371,0.125);
   grm->Fill(4.631371,0.126);
   grm->Fill(4.641371,0.118);
   grm->Fill(4.651371,0.119);
   grm->Fill(4.661371,0.117);
   grm->Fill(4.671371,0.127);
   grm->Fill(4.681371,0.117);
   grm->Fill(4.691371,0.115);
   grm->Fill(4.701371,0.129);
   grm->Fill(4.711371,0.110);
   grm->Fill(4.721371,0.117);
   grm->Fill(4.731371,0.126);
   grm->Fill(4.741371,0.04);
   grm->Fill(4.751371,0.04);
   grm->Fill(4.761371,0.04);
   grm->Fill(4.771371,0.04);
   grm->Fill(4.781371,0.01);
   grm->Fill(4.791371,0.01);


   grm->SetLineColor(2);
   grm->GetXaxis()->SetTitle("J/#psi#phi (mm)mass (GeV/c^{2})");
   grm->GetYaxis()->SetTitle("Evt/10 MeV/c^{2}");
   grm->Draw("");


   //hSigM12e2->Divide(gre);
   //hSigM12m2->Divide(grm);

hSigM1240e->Divide(gre);
hSigM1240m->Divide(grm);
hBgM1240e->Divide(gre);
hBgM1240m->Divide(grm);

TCanvas *c01 = new TCanvas("c01", "(electrons)",204,49,700,500);
hSigM12e2->Draw("e");


 c01->SaveAs("PRL-PLOT/PRL_Mx12_PhiCut_Mescut_SidebSubtrac_re-weight-electrons-B0.eps");


TCanvas *c02 = new TCanvas("c02", "(muons)",204,49,700,500);
hSigM12m2->Draw("e");

c02->SaveAs("PRL-PLOT/PRL_Mx12_PhiCut_Mescut_SidebSubtrac_re-weight-muons-B0.eps");


TCanvas *c03 = new TCanvas("c03", "(electrons+muons)",204,49,700,500);;
hSigM12e2->Add(hSigM12m2);
hSigM12e2->SetXTitle("m_{J/#psi#psi} (GeV/c^{2})");
hSigM12e2->Draw("e");
c03->SaveAs("PRL-PLOT/PRL_Mx12_PhiCut_Mescut_SidebSubtrac_re-weight-total-Bch.eps");

c03->SaveAs("plot-totale-reweight.root");

  hSigM12e2->SetStats(0);
  gre->SetStats(0);

  hSigM12e2->SetLineColor(kBlack);
  
  TCanvas *c1 = new TCanvas("c1","transparent pad",200,10,700,500);
   TPad *pad1 = new TPad("pad1","",0,0,1,1);
   TPad *pad2 = new TPad("pad2","",0,0,1,1);
   pad2->SetFillStyle(4000); //will be transparent
   pad1->Draw();
   pad1->cd();

   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx();
   c1->SetTicky();
   c1->SetLeftMargin(0.12);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.05);
   c1->SetBottomMargin(0.16);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);

   hSigM12e2->Draw();
   hSigM12e2->Draw("esame");
   hSigM12e2->SetLabelColor(1);
   c1->cd();
   gStyle->SetOptStat(0);
   Double_t ymin = 0;
   Double_t ymax = gre->GetMaximum()*1.1;
   Double_t dy = (ymax-ymin)/0.8; //10 per cent margins top and bottom
   Double_t xmin = hSigM12e2->GetBinLowEdge(1);
   Double_t xmax = hSigM12e2->GetBinLowEdge(hSigM12e2->GetNbinsX())+hSigM12e2->GetBinWidth(1);
   Double_t dx = (xmax-xmin)/0.8; //10 per cent margins left and right
   pad2->Range(xmin-0.1*dx,ymin-0.1*dy,xmax+0.1*dx,ymax+0.1*dy);
   pad2->Draw();
   pad2->cd();
   gre->Draw("][sames");
   pad2->Update();
   TGaxis *axis = new TGaxis(xmax,ymin,xmax,ymax,ymin,ymax,50510,"+L");
   axis->SetLabelColor(1);
   axis->Draw();



   /*
 TCanvas *c20 = new TCanvas("c20","PRL-fig1",1800, 1500);
  c20->Divide(2,3);
  c20->cd(1); hSigMes2->Draw("e");
              hBgMes2->Draw("same");
              hSigMes2->Draw("esame");
              hSigMes2->Draw("Axissame");

       c20->cd(2);  
              hSigM12e2->Draw("e");
              hBgM12e2->Draw("same");
              hSigM12e2->Draw("esame");
              hSigM12e2->Draw("Axissame");

      c20->cd(3); 
              hSigDe2->Draw("e");
              hBgDe2->Draw("same");
              hSigDe2->Draw("esame");
              hSigDe2->Draw("Axissame");

       c20->cd(4);  
              hSigM12m2->Draw("e");
              hBgM12m2->Draw("same");
              hSigM12m2->Draw("esame");
              hSigM12m2->Draw("Axissame");
         c20->cd(5);  
              hSigPhi2->Draw("e");
              hBgPhi2->Draw("same");
              hSigPhi2->Draw("esame");
              hSigPhi2->Draw("Axissame");

c20->cd(6);

hSigM122->SetYTitle("Events/ 40 MeV/c^{2}");
hSigM122->SetXTitle("J/#psi#phi (GeV/c^{2})");
hSigM122->Draw("e");
hBgM122->Draw("same");
hSigM122->Draw("esame");
hSigM122->Draw("Axissame");
   */
  
   //c20->Draw();
   //c20->SaveAs("PRL-PLOT/PRL-gif1.eps");



}
