{
  /// Calibration measurements taken in lab - standalone

  gStyle->SetOptStat(0);

  // -----------------------------------------------------------
  // CALIBRAZIONE 

  /*
  // misure prese con viti -> probabilmente poco affidabili (C+E)
  float weight[8]  = { 13.9, 13.9+5.5, 13.9+2.*5.5, 13.9+3.*5.5, 13.9+4.*5.5, 13.9+5.*5.5, 13.9+6.*5.5, 13.9+7.*5.5 };
  float voltageA[8] = { 1.12,  1.18,  1.20,  1.43,  1.44,  1.47,  1.55,  1.54 }; 
  float voltageB[8] = { 1.141, 1.248, 1.258, 1.391, 1.504, 1.600, 1.674, 1.668 };
  float voltageC[8] = { 1.215, 1.254, 1.371, 1.383, 1.526, 1.670, 1.540, 1.604 };
  */

  // misure prese con oggetti piu' pesanti, temperatura 21.8 gradi (C+E)
  float weight2[9]   = { 13.9, 13.9+8.5, 13.9+30.5, 13.9+45.4, 13.9+75., 13.9+120.4, 13.9+150.9, 13.9+159.4, 13.9+322.};
  float voltage2A[9] = { 1.14, 1.22, 1.33, 1.50, 1.80, 2.35, 2.49, 2.81, 3.4};
  float voltage2B[9] = { 1.10, 1.18, 1.42, 1.67, 2.15, 2.50, 2.70, 2.83, 3.56};
  float voltage2C[9] = { 1.143, 1.275, 1.420, 1.610, 1.889, 2.290, 2.455, 2.576, 3.249};
  float voltage2D[9] = { 1.149, 1.192, 1.382, 1.619, 1.768, 2.249, 2.425, 2.694, 3.557};

  // misure prese con oggetti piu' pesanti, temperatura 23.5 gradi (E)
  float voltage3A[9] = { 1.058, 1.28, 1.48, 1.71, 1.99, 2.12, 2.56, 2.60, 3.48 };
  float voltage3B[9] = { 1.150, 1.25, 1.51, 1.64, 1.75, 2.26, 2.58, 2.63, 3.54 };

  // misure prese con oggetti piu' pesanti, temperatura 19.6 gradi (C)
  float voltage4A[9] = { 1.16, 1.26, 1.47, 1.74, 2.18, 2.61, 2.73, 2.78, 3.53 };
  float voltage4B[9] = { 1.23, 1.27, 1.57, 1.79, 1.91, 2.44, 2.61, 2.65, 3.50 };
  float voltage4C[9] = { 1.19, 1.26, 1.53, 1.77, 1.90, 2.41, 2.67, 2.69, 3.53 };
  float voltage4D[9] = { 1.16, 1.22, 1.43, 1.74, 2.12, 2.46, 2.56, 2.65, 3.50 };

  // misure prese con oggetti piu' pesanti e nuovo setup, temperatura 19.6 gradi (C)
  // C'e' sempre una tara che non abbiamo pesato e a cui assegno 20
  float weight5[9]   = { 20., 20.+8.5, 20.+30.5, 20.+30.5+8.5, 20+45.4, 20.+45.4+8.5, 20+75., 20.+75.+8.5, 20.+75.+45.4 };
  float voltage5A[9] = { 1.16, 1.20, 1.42, 1.54, 1.67, 1.73, 2.00, 2.12, 2.50 };
  float voltage5B[9] = { 1.12, 1.20, 1.37, 1.48, 1.60, 1.71, 2.00, 2.10, 2.45 };
  float voltage5C[9] = { 1.16, 1.21, 1.39, 1.51, 1.68, 1.73, 2.08, 2.11, 2.48 };
  float voltage5D[9] = { 1.12, 1.22, 1.39, 1.50, 1.59, 1.74, 1.98, 2.14, 2.40 };

  // -----------------------------------------------------------
  // ISTERESI
  float weightI[9]    = { 13.9, 13.9+8.5, 13.9+8.5+30.5, 13.9+8.5+30.5+45.4, 13.9+8.5+30.5+45.4+75., 13.9+8.5+30.5+45.4, 13.9+8.5+30.5, 13.9+8.5, 13.9 }; 

  // Misure prese senza lasciar stabilizzare. Temp = 19.7
  float voltageI1A[9] = { 1.16, 1.20, 1.45, 1.75, 2.50, 1.93, 1.50, 1.26, 1.17 };
  float voltageI1B[9] = { 1.18, 1.24, 1.50, 1.92, 2.59, 1.89, 1.50, 1.25, 1.19 };
  float voltageI1C[9] = { 1.20, 1.27, 1.50, 1.95, 2.54, 1.99, 1.61, 1.17, 1.10 };
  float voltageI1D[9] = { 1.19, 1.26, 1.44, 1.80, 2.47, 1.85, 1.45, 1.27, 1.15 };

  /*
  // Misure prese lasciando stabilizzare. Temp = 19.7
  float voltageI2A[9] = { 1.15, 1.28, 1.77, 2.00, 2.82, 2.04, 1.63, 1.37, 1.10 };
  float voltageI2B[9] = { 1.10, 1.29, 1.50, 1.95, 2.56, 1.93, 1.51, 1.30, 1.15 };
  float voltageI2C[9] = { 1.15, 1.30, 1.60, 1.95, 2.43, 1.98, 1.46, 1.28, 1.18 };
  */

  // Misure prese senza lasciar stabilizzare con nuovo setup incollato. Temp = 19.6   
  // La tara e' diversa, ma lascio 13.9 nei numeri
  float voltageI3A[9] = { 1.14, 1.18, 1.64, 2.20, 2.71, 2.14, 1.58, 1.22, 1.11 };
  float voltageI3B[9] = { 1.12, 1.18, 1.49, 1.97, 2.80, 2.06, 1.58, 1.23, 1.09 };
  float voltageI3C[9] = { 1.11, 1.20, 1.73, 2.14, 2.87, 2.08, 1.69, 1.24, 1.09 };
  float voltageI3D[9] = { 1.10, 1.21, 1.50, 2.18, 2.72, 2.16, 1.60, 1.20, 1.10 };
  float voltageI3E[9] = { 1.10, 1.21, 1.59, 1.99, 2.59, 1.99, 1.57, 1.20, 1.10 };

  // -------------------------------------
  /*
  // Calibrazione: misure prese con viti 
  TGraph *graphSmallA = new TGraph(8, weight, voltageA);
  graphSmallA->SetMarkerStyle(20);
  graphSmallA->SetMarkerSize(1);
  graphSmallA->SetMarkerColor(2);

  TGraph *graphSmallB = new TGraph(8, weight, voltageB);
  graphSmallB->SetMarkerStyle(21);
  graphSmallB->SetMarkerSize(1);
  graphSmallB->SetMarkerColor(3);

  TGraph *graphSmallC = new TGraph(8, weight, voltageC);
  graphSmallC->SetMarkerStyle(22);
  graphSmallC->SetMarkerSize(1);
  graphSmallC->SetMarkerColor(4);
  */

  // -------------------------------------
  // Calibrazione: misure prese con oggetti piu' pesanti, temperatura 21.8 gradi

  // Per avere una stima dell'errore sui punti: faccio la dispersione dei punti sulle N misure ad un dato peso
  cout << endl;
  cout << "Errore: calib a 21.8" << endl;
  float weight2err[9];
  float voltage2err[9];
  for (int ii=0; ii<9; ii++) {
    TH1F *myH = new TH1F("myH","myH",100,1.,3.7);
    myH->Fill(voltage2A[ii]);
    myH->Fill(voltage2B[ii]);
    myH->Fill(voltage2C[ii]);
    myH->Fill(voltage2D[ii]);
    cout << "ii = " << ii << ", mean = " << myH->GetMean() << ", RMS = " << myH->GetRMS() << " ==> " << 100.*myH->GetRMS()/myH->GetMean() << endl;
    weight2err[ii]  = 0.;
    voltage2err[ii] = myH->GetRMS()/myH->GetMean();
    delete myH;
  }

  TGraphErrors *graphLarge2A = new TGraphErrors(9, weight2, voltage2A, weight2err, voltage2err);
  graphLarge2A->SetMarkerStyle(20);
  graphLarge2A->SetMarkerSize(1);
  graphLarge2A->SetMarkerColor(2);

  TGraphErrors *graphLarge2B = new TGraphErrors(9, weight2, voltage2B, weight2err, voltage2err);
  graphLarge2B->SetMarkerStyle(21);
  graphLarge2B->SetMarkerSize(1);
  graphLarge2B->SetMarkerColor(6);

  TGraphErrors *graphLarge2C = new TGraphErrors(9, weight2, voltage2C, weight2err, voltage2err);
  graphLarge2C->SetMarkerStyle(22);
  graphLarge2C->SetMarkerSize(1);
  graphLarge2C->SetMarkerColor(4);

  TGraphErrors *graphLarge2D = new TGraphErrors(9, weight2, voltage2D, weight2err, voltage2err);
  graphLarge2D->SetMarkerStyle(23);
  graphLarge2D->SetMarkerSize(1);
  graphLarge2D->SetMarkerColor(3);

  // -------------------------------------
  // Calibrazione: misure prese con oggetti piu' pesanti, temperatura 23.5 gradi

  // Per avere una stima dell'errore sui punti: faccio la dispersione dei punti sulle N misure ad un dato peso
  cout << endl;
  cout << "Errore: calib a 23.5" << endl;
  float voltage3err[9];
  for (int ii=0; ii<9; ii++) {
    TH1F *myH = new TH1F("myH","myH",100,1.,3.7);
    myH->Fill(voltage3A[ii]);
    myH->Fill(voltage3B[ii]);
    cout << "ii = " << ii << ", mean = " << myH->GetMean() << ", RMS = " << myH->GetRMS() << " ==> " << 100.*myH->GetRMS()/myH->GetMean() << endl;
    voltage3err[ii] = myH->GetRMS()/myH->GetMean();
    delete myH;
  }

  TGraphErrors *graphLarge3A = new TGraphErrors(9, weight2, voltage3A, weight2err, voltage3err);
  graphLarge3A->SetMarkerStyle(20);
  graphLarge3A->SetMarkerSize(1);
  graphLarge3A->SetMarkerColor(2);

  TGraphErrors *graphLarge3B = new TGraphErrors(9, weight2, voltage3B, weight2err, voltage3err);
  graphLarge3B->SetMarkerStyle(21);
  graphLarge3B->SetMarkerSize(1);
  graphLarge3B->SetMarkerColor(3);

  // -------------------------------------
  // Calibrazione: misure prese con oggetti piu' pesanti, temperatura 19.6 gradi

  // Per avere una stima dell'errore sui punti: faccio la dispersione dei punti sulle N misure ad un dato peso
  cout << endl;
  cout << "Errore: calib a 19.6" << endl;
  float voltage4err[9];
  for (int ii=0; ii<9; ii++) {
    TH1F *myH = new TH1F("myH","myH",100,1.,3.7);
    myH->Fill(voltage4A[ii]);
    myH->Fill(voltage4B[ii]);
    myH->Fill(voltage4C[ii]);
    myH->Fill(voltage4D[ii]);
    cout << "ii = " << ii << ", mean = " << myH->GetMean() << ", RMS = " << myH->GetRMS() << " ==> " << 100.*myH->GetRMS()/myH->GetMean() << endl;
    voltage4err[ii] = myH->GetRMS()/myH->GetMean();
    delete myH;
  }

  TGraphErrors *graphLarge4A = new TGraphErrors(9, weight2, voltage4A, weight2err, voltage4err);
  graphLarge4A->SetMarkerStyle(20);
  graphLarge4A->SetMarkerSize(1);
  graphLarge4A->SetMarkerColor(2);

  TGraphErrors *graphLarge4B = new TGraphErrors(9, weight2, voltage4B, weight2err, voltage4err);
  graphLarge4B->SetMarkerStyle(21);
  graphLarge4B->SetMarkerSize(1);
  graphLarge4B->SetMarkerColor(6);

  TGraphErrors *graphLarge4C = new TGraphErrors(9, weight2, voltage4C, weight2err, voltage4err);
  graphLarge4C->SetMarkerStyle(22);
  graphLarge4C->SetMarkerSize(1);
  graphLarge4C->SetMarkerColor(4);

  TGraphErrors *graphLarge4D = new TGraphErrors(9, weight2, voltage4D, weight2err, voltage4err);
  graphLarge4D->SetMarkerStyle(23);
  graphLarge4D->SetMarkerSize(1);
  graphLarge4D->SetMarkerColor(3);



  // -------------------------------------
  // Calibrazione: misure prese con oggetti piu' pesanti e setup incollato. Temperatura 19.6 gradi

  // Per avere una stima dell'errore sui punti: faccio la dispersione dei punti sulle N misure ad un dato peso
  cout << endl;
  cout << "Errore: calib a 19.6 - new setup" << endl;
  float weight5err[9];
  float voltage5err[9];
  for (int ii=0; ii<9; ii++) {
    TH1F *myH = new TH1F("myH","myH",100,1.,3.7);
    myH->Fill(voltage5A[ii]);
    myH->Fill(voltage5B[ii]);
    myH->Fill(voltage5C[ii]);
    myH->Fill(voltage5D[ii]);
    cout << "ii = " << ii << ", mean = " << myH->GetMean() << ", RMS = " << myH->GetRMS() << " ==> " << 100.*myH->GetRMS()/myH->GetMean() << endl;
    weight5err[ii]  = 0.;
    voltage5err[ii] = myH->GetRMS()/myH->GetMean();
    delete myH;
  }

  TGraphErrors *graphLarge5A = new TGraphErrors(9, weight5, voltage5A, weight5err, voltage5err);
  graphLarge5A->SetMarkerStyle(20);
  graphLarge5A->SetMarkerSize(1);
  graphLarge5A->SetMarkerColor(2);

  TGraphErrors *graphLarge5B = new TGraphErrors(9, weight5, voltage5B, weight5err, voltage5err);
  graphLarge5B->SetMarkerStyle(21);
  graphLarge5B->SetMarkerSize(1);
  graphLarge5B->SetMarkerColor(6);

  TGraphErrors *graphLarge5C = new TGraphErrors(9, weight5, voltage5C, weight5err, voltage5err);
  graphLarge5C->SetMarkerStyle(22);
  graphLarge5C->SetMarkerSize(1);
  graphLarge5C->SetMarkerColor(4);

  TGraphErrors *graphLarge5D = new TGraphErrors(9, weight5, voltage5D, weight5err, voltage5err);
  graphLarge5D->SetMarkerStyle(23);
  graphLarge5D->SetMarkerSize(1);
  graphLarge5D->SetMarkerColor(3);


  // -------------------------------------------------------
  // Calibrazione: plot

  /*
  TCanvas cSmall("cSmall","",1);
  cSmall.SetGrid();
  TH2F *myHSmall = new TH2F("myHSmall","Temperature = 21.8",100,10.,65.,100,0.5,2.);
  myHSmall->GetXaxis()->SetTitle("weight");
  myHSmall->GetYaxis()->SetTitle("Voltage");
  myHSmall->Draw();
  graphSmallA->Draw("Psame");
  graphSmallB->Draw("Psame");
  graphSmallC->Draw("Psame");
  cSmall.SaveAs("smallItems.pdf");
  */

  TCanvas cLarge2("cLarge2","",1);
  cLarge2.SetGrid();
  TH2F *myHLarge2 = new TH2F("myHLarge2","Temperature = 21.8",100,0.,360.,100,0.5,4.);
  myHLarge2->GetXaxis()->SetTitle("weight");
  myHLarge2->GetYaxis()->SetTitle("Voltage");
  myHLarge2->Draw();
  graphLarge2A->Draw("Psame");
  graphLarge2A->Fit("pol1","","",0,100);
  graphLarge2A->GetFunction("pol1")->SetLineColor(2);
  graphLarge2B->Draw("Psame");
  graphLarge2B->Fit("pol1","","",0,100);
  graphLarge2B->GetFunction("pol1")->SetLineColor(6);
  graphLarge2C->Draw("Psame");
  graphLarge2C->Fit("pol1","","",0,100);
  graphLarge2C->GetFunction("pol1")->SetLineColor(4);
  graphLarge2D->Draw("Psame");
  graphLarge2D->Fit("pol1","","",0,100);
  graphLarge2D->GetFunction("pol1")->SetLineColor(3);
  cLarge2.SaveAs("largeItems_temp21d8.pdf");

  TH2F *myHLarge2z = new TH2F("myHLarge2z","Temperature = 21.8",100,0.,100.,100,0.5,2.5);
  myHLarge2z->GetXaxis()->SetTitle("weight");
  myHLarge2z->GetYaxis()->SetTitle("Voltage");
  myHLarge2z->Draw();
  graphLarge2A->Draw("Psame");
  graphLarge2A->Fit("pol1","","",0,100);
  graphLarge2A->GetFunction("pol1")->SetLineColor(2);
  graphLarge2B->Draw("Psame");
  graphLarge2B->Fit("pol1","","",0,100);
  graphLarge2B->GetFunction("pol1")->SetLineColor(6);
  graphLarge2C->Draw("Psame");
  graphLarge2C->Fit("pol1","","",0,100);
  graphLarge2C->GetFunction("pol1")->SetLineColor(4);
  graphLarge2D->Draw("Psame");
  graphLarge2D->Fit("pol1","","",0,100);
  graphLarge2D->GetFunction("pol1")->SetLineColor(3);
  cLarge2.SaveAs("largeItems_temp21d8_zoom.pdf");

  cout << endl;
  cout << endl;
  cout << "============================================" << endl;
  cout << "Temp 21.8 => rosso : " << graphLarge2A->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge2A->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge2A->GetCorrelationFactor() << endl;
  cout << "Temp 21.8 => viola : " << graphLarge2B->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge2B->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge2B->GetCorrelationFactor() << endl;
  cout << "Temp 21.8 => blu : "   << graphLarge2C->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge2C->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge2C->GetCorrelationFactor() << endl;
  cout << "Temp 21.8 => verde : " << graphLarge2D->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge2D->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge2D->GetCorrelationFactor() << endl;
  cout << endl;
  cout << endl;

  TCanvas cLarge3("cLarge3","",1);
  cLarge3.SetGrid();
  TH2F *myHLarge3 = new TH2F("myHLarge3","Temperature = 23.5",100,0.,360.,100,0.5,4.);
  myHLarge3->GetXaxis()->SetTitle("weight");
  myHLarge3->GetYaxis()->SetTitle("Voltage");
  myHLarge3->Draw();
  graphLarge3A->Draw("Psame");
  graphLarge3A->Fit("pol1","","",0,100);
  graphLarge3A->GetFunction("pol1")->SetLineColor(2);
  graphLarge3B->Draw("Psame");
  graphLarge3B->Fit("pol1","","",0,100);
  graphLarge3B->GetFunction("pol1")->SetLineColor(3);
  cLarge3.SaveAs("largeItems_temp23d5.pdf");

  TH2F *myHLarge3z = new TH2F("myHLarge3z","Temperature = 23.5",100,0.,100.,100,0.5,3.);
  myHLarge3z->GetXaxis()->SetTitle("weight");
  myHLarge3z->GetYaxis()->SetTitle("Voltage");
  myHLarge3z->Draw();
  graphLarge3A->Draw("Psame");
  graphLarge3A->Fit("pol1","","",0,100);
  graphLarge3A->GetFunction("pol1")->SetLineColor(2);
  graphLarge3B->Draw("Psame");
  graphLarge3B->Fit("pol1","","",0,100);
  graphLarge3B->GetFunction("pol1")->SetLineColor(3);
  cLarge3.SaveAs("largeItems_temp23d5_zoom.pdf");

  cout << endl;
  cout << endl;
  cout << "============================================" << endl;
  cout << "Temp 23.5 => rosso : " << graphLarge3A->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge3A->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge3A->GetCorrelationFactor() << endl;
  cout << "Temp 23.5 => verde : " << graphLarge3B->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge3B->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge3B->GetCorrelationFactor() << endl;
  cout << endl;
  cout << endl;

  TCanvas cLarge4("cLarge4","",1);
  cLarge4.SetGrid();
  TH2F *myHLarge4 = new TH2F("myHLarge4","Temperature = 19.6",100,0.,360.,100,0.5,4.);
  myHLarge4->GetXaxis()->SetTitle("weight");
  myHLarge4->GetYaxis()->SetTitle("Voltage");
  myHLarge4->Draw();
  graphLarge4A->Draw("Psame");
  graphLarge4A->Fit("pol1","","",0,100);
  graphLarge4A->GetFunction("pol1")->SetLineColor(2);
  graphLarge4B->Draw("Psame");
  graphLarge4B->Fit("pol1","","",0,100);
  graphLarge4B->GetFunction("pol1")->SetLineColor(6);
  graphLarge4C->Draw("Psame");
  graphLarge4C->Fit("pol1","","",0,100);
  graphLarge4C->GetFunction("pol1")->SetLineColor(4);
  graphLarge4D->Draw("Psame");
  graphLarge4D->Fit("pol1","","",0,100);
  graphLarge4D->GetFunction("pol1")->SetLineColor(3);
  cLarge4.SaveAs("largeItems_temp19d6.pdf");

  TH2F *myHLarge4z = new TH2F("myHLarge4z","Temperature = 19.6",100,0.,100.,100,0.5,2.5);
  myHLarge4z->GetXaxis()->SetTitle("weight");
  myHLarge4z->GetYaxis()->SetTitle("Voltage");
  myHLarge4z->Draw();
  graphLarge4A->Draw("Psame");
  graphLarge4A->Fit("pol1","","",0,100);
  graphLarge4A->GetFunction("pol1")->SetLineColor(2);
  graphLarge4B->Draw("Psame");
  graphLarge4B->Fit("pol1","","",0,100);
  graphLarge4B->GetFunction("pol1")->SetLineColor(6);
  graphLarge4C->Draw("Psame");
  graphLarge4C->Fit("pol1","","",0,100);
  graphLarge4C->GetFunction("pol1")->SetLineColor(4);
  graphLarge4D->Draw("Psame");
  graphLarge4D->Fit("pol1","","",0,100);
  graphLarge4D->GetFunction("pol1")->SetLineColor(3);
  cLarge4.SaveAs("largeItems_temp19d6_zoom.pdf");

  cout << endl;
  cout << endl;
  cout << "============================================" << endl;
  cout << "Temp 19.6 => rosso : " << graphLarge4A->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge4A->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge4A->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 => viola : " << graphLarge4B->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge4B->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge4B->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 => blu : "   << graphLarge4C->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge4C->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge4C->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 => verde : " << graphLarge4D->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge4D->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge4D->GetCorrelationFactor() << endl;
  cout << endl;
  cout << endl;


  TCanvas cLarge5("cLarge5","",1);
  cLarge5.SetGrid();
  TH2F *myHLarge5 = new TH2F("myHLarge5","Temperature = 19.6 - new setup",100,0.,360.,100,0.5,4.);
  myHLarge5->GetXaxis()->SetTitle("weight");
  myHLarge5->GetYaxis()->SetTitle("Voltage");
  myHLarge5->Draw();
  graphLarge5A->Draw("Psame");
  graphLarge5A->Fit("pol1","","",0,150);
  graphLarge5A->GetFunction("pol1")->SetLineColor(2);
  graphLarge5B->Draw("Psame");
  graphLarge5B->Fit("pol1","","",0,150);
  graphLarge5B->GetFunction("pol1")->SetLineColor(6);
  graphLarge5C->Draw("Psame");
  graphLarge5C->Fit("pol1","","",0,150);
  graphLarge5C->GetFunction("pol1")->SetLineColor(4);
  graphLarge5D->Draw("Psame");
  graphLarge5D->Fit("pol1","","",0,150);
  graphLarge5D->GetFunction("pol1")->SetLineColor(3);
  cLarge5.SaveAs("largeItems_temp19d6_newsetup.pdf");

  TH2F *myHLarge5z = new TH2F("myHLarge5z","Temperature = 19.6 - new setup",100,0.,150.,100,0.5,3.);
  myHLarge5z->GetXaxis()->SetTitle("weight");
  myHLarge5z->GetYaxis()->SetTitle("Voltage");
  myHLarge5z->Draw();
  graphLarge5A->Draw("Psame");
  graphLarge5A->Fit("pol1","","",0,150);
  graphLarge5A->GetFunction("pol1")->SetLineColor(2);
  graphLarge5B->Draw("Psame");
  graphLarge5B->Fit("pol1","","",0,150);
  graphLarge5B->GetFunction("pol1")->SetLineColor(6);
  graphLarge5C->Draw("Psame");
  graphLarge5C->Fit("pol1","","",0,150);
  graphLarge5C->GetFunction("pol1")->SetLineColor(4);
  graphLarge5D->Draw("Psame");
  graphLarge5D->Fit("pol1","","",0,150);
  graphLarge5D->GetFunction("pol1")->SetLineColor(3);
  cLarge5.SaveAs("largeItems_temp19d6_newsetup_zoom.pdf");

  cout << endl;
  cout << endl;
  cout << "============================================" << endl;
  cout << "Temp 19.6 new => rosso : " << graphLarge5A->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge5A->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge5A->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 new => viola : " << graphLarge5B->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge5B->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge5B->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 new => blu : "   << graphLarge5C->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge5C->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge5C->GetCorrelationFactor() << endl;
  cout << "Temp 19.6 new => verde : " << graphLarge5D->GetFunction("pol1")->GetParameter("p1") << " +- " << graphLarge5D->GetFunction("pol1")->GetParError(1) << "; R = " << graphLarge5D->GetCorrelationFactor() << endl;
  cout << endl;
  cout << endl;


  // -----------------------------------------------------------------------------------
  // Isteresi
  TH2F *myHistIa = new TH2F("myHistIa","Isteresi. Temperature = 19.7",100,0.,200.,100,0.5,3.);
  myHistIa->GetXaxis()->SetTitle("weight");
  myHistIa->GetYaxis()->SetTitle("Voltage");
  TH2F *myHistIb = new TH2F("myHistIb","Isteresi. Temperature = 19.7",100,0.,200.,100,-0.2,0.2);
  myHistIb->GetXaxis()->SetTitle("weight");
  myHistIb->GetYaxis()->SetTitle("(Vup - Vdown) / Vup");


  // Senza lasciar stabilizzare
  TGraph *graph1IAa = new TGraph(9, weightI, voltageI1A);
  graph1IAa->SetMarkerStyle(20);
  graph1IAa->SetMarkerSize(1);
  graph1IAa->SetMarkerColor(2);
  float voltageI1DiffA[5] = { (voltageI1A[0]-voltageI1A[8])/voltageI1A[0], (voltageI1A[1]-voltageI1A[7])/voltageI1A[1], (voltageI1A[2]-voltageI1A[6])/voltageI1A[2], (voltageI1A[3]-voltageI1A[5])/voltageI1A[3], 0. };
  TGraph *graph1IAb = new TGraph(5, weightI, voltageI1DiffA);
  graph1IAb->SetMarkerStyle(20);
  graph1IAb->SetMarkerSize(1);
  graph1IAb->SetMarkerColor(2);

  TGraph *graph1IBa = new TGraph(9, weightI, voltageI1B);
  graph1IBa->SetMarkerStyle(20);
  graph1IBa->SetMarkerSize(1);
  graph1IBa->SetMarkerColor(3);
  float voltageI1DiffB[5] = { (voltageI1B[0]-voltageI1B[8])/voltageI1B[0], (voltageI1B[1]-voltageI1B[7])/voltageI1B[1], (voltageI1B[2]-voltageI1B[6])/voltageI1B[2], (voltageI1B[3]-voltageI1B[5])/voltageI1B[3], 0. };
  TGraph *graph1IBb = new TGraph(5, weightI, voltageI1DiffB);
  graph1IBb->SetMarkerStyle(20);
  graph1IBb->SetMarkerSize(1);
  graph1IBb->SetMarkerColor(3);

  TGraph *graph1ICa = new TGraph(9, weightI, voltageI1C);
  graph1ICa->SetMarkerStyle(20);
  graph1ICa->SetMarkerSize(1);
  graph1ICa->SetMarkerColor(4);
  float voltageI1DiffC[5] = { (voltageI1C[0]-voltageI1C[8])/voltageI1C[0], (voltageI1C[1]-voltageI1C[7])/voltageI1C[1], (voltageI1C[2]-voltageI1C[6])/voltageI1C[2], (voltageI1C[3]-voltageI1C[5])/voltageI1C[3], 0. };
  TGraph *graph1ICb = new TGraph(5, weightI, voltageI1DiffC);
  graph1ICb->SetMarkerStyle(20);
  graph1ICb->SetMarkerSize(1);
  graph1ICb->SetMarkerColor(4);

  TGraph *graph1IDa = new TGraph(9, weightI, voltageI1D);
  graph1IDa->SetMarkerStyle(20);
  graph1IDa->SetMarkerSize(1);
  graph1IDa->SetMarkerColor(6);
  float voltageI1DiffD[5] = { (voltageI1D[0]-voltageI1D[8])/voltageI1D[0], (voltageI1D[1]-voltageI1D[7])/voltageI1D[1], (voltageI1D[2]-voltageI1D[6])/voltageI1D[2], (voltageI1D[3]-voltageI1D[5])/voltageI1D[3], 0. };
  TGraph *graph1IDb = new TGraph(5, weightI, voltageI1DiffD);
  graph1IDb->SetMarkerStyle(20);
  graph1IDb->SetMarkerSize(1);
  graph1IDb->SetMarkerColor(6);

  TCanvas cIst1A("cIst1A","",1);
  cIst1A.Divide(1,2);
  cIst1A.cd(1);
  myHistIa->Draw();
  graph1IAa->Draw("Psame");
  cIst1A.cd(2);
  myHistIb->Draw();
  graph1IAb->Draw("Psame");
  cIst1A.SaveAs("isteresiA.pdf");

  TCanvas cIst1B("cIst1B","",1);
  cIst1B.Divide(1,2);
  cIst1B.cd(1);
  myHistIa->Draw();
  graph1IBa->Draw("Psame");
  cIst1B.cd(2);
  myHistIb->Draw();
  graph1IBb->Draw("Psame");
  cIst1B.SaveAs("isteresiB.pdf");

  TCanvas cIst1C("cIst1C","",1);
  cIst1C.Divide(1,2);
  cIst1C.cd(1);
  myHistIa->Draw();
  graph1ICa->Draw("Psame");
  cIst1C.cd(2);
  myHistIb->Draw();
  graph1ICb->Draw("Psame");
  cIst1C.SaveAs("isteresiC.pdf");

  TCanvas cIst1D("cIst1D","",1);
  cIst1D.Divide(1,2);
  cIst1D.cd(1);
  myHistIa->Draw();
  graph1IDa->Draw("Psame");
  cIst1D.cd(2);
  myHistIb->Draw();
  graph1IDb->Draw("Psame");
  cIst1D.SaveAs("isteresiD.pdf");

  /*
  // Lasciando stabilizzare
  TGraph *graph2IAa = new TGraph(9, weightI, voltageI2A);
  graph2IAa->SetMarkerStyle(20);
  graph2IAa->SetMarkerSize(1);
  graph2IAa->SetMarkerColor(2);
  float voltageI2DiffA[5] = { (voltageI2A[0]-voltageI2A[8])/voltageI2A[0], (voltageI2A[1]-voltageI2A[7])/voltageI2A[1], (voltageI2A[2]-voltageI2A[6])/voltageI2A[2], (voltageI2A[3]-voltageI2A[5])/voltageI2A[3], 0. };
  TGraph *graph2IAb = new TGraph(5, weightI, voltageI2DiffA);
  graph2IAb->SetMarkerStyle(20);
  graph2IAb->SetMarkerSize(1);
  graph2IAb->SetMarkerColor(2);

  TGraph *graph2IBa = new TGraph(9, weightI, voltageI2B);
  graph2IBa->SetMarkerStyle(20);
  graph2IBa->SetMarkerSize(1);
  graph2IBa->SetMarkerColor(3);
  float voltageI2DiffB[5] = { (voltageI2B[0]-voltageI2B[8])/voltageI2B[0], (voltageI2B[1]-voltageI2B[7])/voltageI2B[1], (voltageI2B[2]-voltageI2B[6])/voltageI2B[2], (voltageI2B[3]-voltageI2B[5])/voltageI2B[3], 0. };
  TGraph *graph2IBb = new TGraph(5, weightI, voltageI2DiffB);
  graph2IBb->SetMarkerStyle(20);
  graph2IBb->SetMarkerSize(1);
  graph2IBb->SetMarkerColor(3);

  TGraph *graph2ICa = new TGraph(9, weightI, voltageI2C);
  graph2ICa->SetMarkerStyle(20);
  graph2ICa->SetMarkerSize(1);
  graph2ICa->SetMarkerColor(4);
  float voltageI2DiffC[5] = { (voltageI2C[0]-voltageI2C[8])/voltageI2C[0], (voltageI2C[1]-voltageI2C[7])/voltageI2C[1], (voltageI2C[2]-voltageI2C[6])/voltageI2C[2], (voltageI2C[3]-voltageI2C[5])/voltageI2C[3], 0. };
  TGraph *graph2ICb = new TGraph(5, weightI, voltageI2DiffC);
  graph2ICb->SetMarkerStyle(20);
  graph2ICb->SetMarkerSize(1);
  graph2ICb->SetMarkerColor(4);


  TCanvas cIst2A("cIst2A","",1);
  cIst2A.Divide(1,2);
  cIst2A.cd(1);
  myHistIa->Draw();
  graph2IAa->Draw("Psame");
  cIst2A.cd(2);
  myHistIb->Draw();
  graph2IAb->Draw("Psame");
  cIst2A.SaveAs("isteresiAstab.pdf");

  TCanvas cIst2B("cIst2B","",1);
  cIst2B.Divide(1,2);
  cIst2B.cd(1);
  myHistIa->Draw();
  graph2IBa->Draw("Psame");
  cIst2B.cd(2);
  myHistIb->Draw();
  graph2IBb->Draw("Psame");
  cIst2B.SaveAs("isteresiBstab.pdf");

  TCanvas cIst2C("cIst2C","",1);
  cIst2C.Divide(1,2);
  cIst2C.cd(1);
  myHistIa->Draw();
  graph2ICa->Draw("Psame");
  cIst2C.cd(2);
  myHistIb->Draw();
  graph2ICb->Draw("Psame");
  cIst2C.SaveAs("isteresiCstab.pdf");
  */


  // Senza lasciar stabilizzare - new setup
  TGraph *graph3IAa = new TGraph(9, weightI, voltageI3A);
  graph3IAa->SetMarkerStyle(20);
  graph3IAa->SetMarkerSize(1);
  graph3IAa->SetMarkerColor(2);
  float voltageI3DiffA[5] = { (voltageI3A[0]-voltageI3A[8])/voltageI3A[0], (voltageI3A[1]-voltageI3A[7])/voltageI3A[1], (voltageI3A[2]-voltageI3A[6])/voltageI3A[2], (voltageI3A[3]-voltageI3A[5])/voltageI3A[3], 0. };
  TGraph *graph3IAb = new TGraph(5, weightI, voltageI3DiffA);
  graph3IAb->SetMarkerStyle(20);
  graph3IAb->SetMarkerSize(1);
  graph3IAb->SetMarkerColor(2);

  TGraph *graph3IBa = new TGraph(9, weightI, voltageI3B);
  graph3IBa->SetMarkerStyle(20);
  graph3IBa->SetMarkerSize(1);
  graph3IBa->SetMarkerColor(3);
  float voltageI3DiffB[5] = { (voltageI3B[0]-voltageI3B[8])/voltageI3B[0], (voltageI3B[1]-voltageI3B[7])/voltageI3B[1], (voltageI3B[2]-voltageI3B[6])/voltageI3B[2], (voltageI3B[3]-voltageI3B[5])/voltageI3B[3], 0. };
  TGraph *graph3IBb = new TGraph(5, weightI, voltageI3DiffB);
  graph3IBb->SetMarkerStyle(20);
  graph3IBb->SetMarkerSize(1);
  graph3IBb->SetMarkerColor(3);

  TGraph *graph3ICa = new TGraph(9, weightI, voltageI3C);
  graph3ICa->SetMarkerStyle(20);
  graph3ICa->SetMarkerSize(1);
  graph3ICa->SetMarkerColor(4);
  float voltageI3DiffC[5] = { (voltageI3C[0]-voltageI3C[8])/voltageI3C[0], (voltageI3C[1]-voltageI3C[7])/voltageI3C[1], (voltageI3C[2]-voltageI3C[6])/voltageI3C[2], (voltageI3C[3]-voltageI3C[5])/voltageI3C[3], 0. };
  TGraph *graph3ICb = new TGraph(5, weightI, voltageI3DiffC);
  graph3ICb->SetMarkerStyle(20);
  graph3ICb->SetMarkerSize(1);
  graph3ICb->SetMarkerColor(4);

  TGraph *graph3IDa = new TGraph(9, weightI, voltageI3D);
  graph3IDa->SetMarkerStyle(20);
  graph3IDa->SetMarkerSize(1);
  graph3IDa->SetMarkerColor(6);
  float voltageI3DiffD[5] = { (voltageI3D[0]-voltageI3D[8])/voltageI3D[0], (voltageI3D[1]-voltageI3D[7])/voltageI3D[1], (voltageI3D[2]-voltageI3D[6])/voltageI3D[2], (voltageI3D[3]-voltageI3D[5])/voltageI3D[3], 0. };
  TGraph *graph3IDb = new TGraph(5, weightI, voltageI3DiffD);
  graph3IDb->SetMarkerStyle(20);
  graph3IDb->SetMarkerSize(1);
  graph3IDb->SetMarkerColor(6);

  TGraph *graph3IEa = new TGraph(9, weightI, voltageI3E);
  graph3IEa->SetMarkerStyle(20);
  graph3IEa->SetMarkerSize(1);
  graph3IEa->SetMarkerColor(7);
  float voltageI3DiffE[5] = { (voltageI3E[0]-voltageI3E[8])/voltageI3E[0], (voltageI3E[1]-voltageI3E[7])/voltageI3E[1], (voltageI3E[2]-voltageI3E[6])/voltageI3E[2], (voltageI3E[3]-voltageI3E[5])/voltageI3E[3], 0. };
  TGraph *graph3IEb = new TGraph(5, weightI, voltageI3DiffE);
  graph3IEb->SetMarkerStyle(20);
  graph3IEb->SetMarkerSize(1);
  graph3IEb->SetMarkerColor(7);

  TCanvas cIst3A("cIst3A","",1);
  cIst3A.Divide(1,2);
  cIst3A.cd(1);
  myHistIa->Draw();
  graph3IAa->Draw("Psame");
  cIst3A.cd(2);
  myHistIb->Draw();
  graph3IAb->Draw("Psame");
  cIst3A.SaveAs("isteresiNewA.pdf");

  TCanvas cIst3B("cIst3B","",1);
  cIst3B.Divide(1,2);
  cIst3B.cd(1);
  myHistIa->Draw();
  graph3IBa->Draw("Psame");
  cIst3B.cd(2);
  myHistIb->Draw();
  graph3IBb->Draw("Psame");
  cIst3B.SaveAs("isteresiNewB.pdf");

  TCanvas cIst3C("cIst3C","",1);
  cIst3C.Divide(1,2);
  cIst3C.cd(1);
  myHistIa->Draw();
  graph3ICa->Draw("Psame");
  cIst3C.cd(2);
  myHistIb->Draw();
  graph3ICb->Draw("Psame");
  cIst3C.SaveAs("isteresiNewC.pdf");

  TCanvas cIst3D("cIst3D","",1);
  cIst3D.Divide(1,2);
  cIst3D.cd(1);
  myHistIa->Draw();
  graph3IDa->Draw("Psame");
  cIst3D.cd(2);
  myHistIb->Draw();
  graph3IDb->Draw("Psame");
  cIst3D.SaveAs("isteresiNewD.pdf");

  TCanvas cIst3E("cIst3E","",1);
  cIst3E.Divide(1,2);
  cIst3E.cd(1);
  myHistIa->Draw();
  graph3IDa->Draw("Psame");
  cIst3E.cd(2);
  myHistIb->Draw();
  graph3IDb->Draw("Psame");
  cIst3E.SaveAs("isteresiNewE.pdf");
}
