//! c++ includes
#include <string>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <math.h>

//! ROOT includes
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TGraphErrors.h"

using namespace std;

void testSodio() {

  // vectors
  float temp1V[8], temp2V[8];
  float meanV[8],  meanErrV[8];
  float sigmaV[8], sigmaErrV[8];

  // Loop over files
  for (int iFile=0; iFile<8; iFile++) {

    TString measName;
    if (iFile==0) measName = "A";
    if (iFile==1) measName = "B1"; 
    if (iFile==2) measName = "B2"; 
    if (iFile==3) measName = "C1"; 
    if (iFile==4) measName = "C2"; 
    if (iFile==5) measName = "D"; 
    if (iFile==6) measName = "E"; 
    if (iFile==7) measName = "F"; 

    // -------------------------
    // Reading from input files
    TString filename = TString("testSodio/misura")+measName+TString(".txt");
    cout << "Reading file: " << filename << endl;

    ifstream *intxt = new ifstream(filename);
    char Buffer[2000];
    float counts[1000], T1[1000], T2[1000];
    int IFC=0;
    while( !(intxt->eof()) ){
      intxt->getline(Buffer,2000);
      if (!strstr(Buffer,"#") && !(strspn(Buffer," ") == strlen(Buffer))){
	sscanf(Buffer,"%f %f %f", &counts[IFC], &T1[IFC], &T2[IFC]);
      }
      IFC++;
    }
    intxt->close();
    delete intxt;

    // -------------------------
    // Filling histo with distributions
    TString countName = TString("H_counts_")+measName;    
    TString temp1Name = TString("H_temp1_")+measName;    
    TString temp2Name = TString("H_temp2_")+measName;    
    float xmin = 0.;
    float xmax = 2400.;
    if (iFile==0) { xmin = 1000.; xmax = 2000.; }
    if (iFile==1) { xmin = 400.;  xmax = 1400.; }
    if (iFile==2) { xmin = 200.;  xmax = 1200.; }
    if (iFile==3) { xmin = 400.;  xmax = 1400.; }
    if (iFile==4) { xmin = 200.;  xmax = 1200.; }
    if (iFile==5) { xmin = 300.;  xmax = 1300.; }
    if (iFile==6) { xmin = 3000.; xmax = 4000.; }
    if (iFile==7) { xmin = 0.;    xmax = 50.; }
    TH1F *H_counts = new TH1F(countName,countName,100,xmin, xmax);
    TH1F *H_T1     = new TH1F(temp1Name,temp1Name, 50,20.,27.);
    TH1F *H_T2     = new TH1F(temp2Name,temp2Name, 50,20.,27.);    
    for (int ii=0; ii<IFC; ii++) {
      H_counts -> Fill(counts[ii]);
      H_T1     -> Fill(T1[ii]);
      H_T2     -> Fill(T2[ii]);
    }

    // Temp
    temp1V[iFile] = H_T1->GetMean();
    temp2V[iFile] = H_T2->GetMean();

    // Gaus fit
    TF1 *gausa = new TF1("gausa","[0]*exp(-1*(x-[1])*(x-[1])/2/[2]/[2])",xmin, xmax);
    gausa->SetParameters(H_counts->GetEntries(), H_counts->GetMean(), H_counts->GetRMS());
    H_counts->Fit("gausa");
    meanV[iFile]     = gausa->GetParameter(1);
    sigmaV[iFile]    = gausa->GetParameter(2);
    meanErrV[iFile]  = sigmaV[iFile]/sqrt(H_counts->GetEntries()); 
    sigmaErrV[iFile] = sigmaV[iFile]/sqrt(2*H_counts->GetEntries()); 
    delete gausa;

    // Printout prima dei rescaling
    for (int ii=0; ii<8; ii++) {
      cout << "mean = " << meanV[ii] 
	   << ", sigma = " << sigmaV[ii] 
	   << ", temp1 = " << temp1V[ii] << ", temp2 = " << temp2V[ii] << endl;
    }

    // -------------------------
    // Plots
    gStyle->SetOptStat(111111);
    gStyle->SetOptFit(1111);

    TCanvas c1("c1","",1);
    H_counts->SetLineColor(4);
    H_counts->SetLineWidth(2);
    H_counts->Draw();
    TString plotCountName = TString("counts_")+measName+(".png");        
    c1.SaveAs(plotCountName);
    
    TCanvas c2("c2","",1);
    H_T1->SetLineColor(4);
    H_T1->SetLineWidth(2);
    H_T1->Draw();
    TString plotTemp1Name = TString("temp1_")+measName+(".png");        
    c2.SaveAs(plotTemp1Name);

    TCanvas c3("c3","",1);
    H_T2->SetLineColor(4);
    H_T2->SetLineWidth(2);
    H_T2->Draw();
    TString plotTemp2Name = TString("temp2_")+measName+(".png");        
    c3.SaveAs(plotTemp2Name);


    // -------------------------    
    // Output
    TFile *outFile;
    if (iFile==0) outFile = new TFile ("output.root","RECREATE","histoSiPm");
    else outFile = new TFile ("output.root","UPDATE","histoSiPm");
    outFile->cd();
    H_counts->Write();
    H_T1->Write();
    H_T2->Write();
    outFile->Close();
    delete outFile;

    // Deletion
    delete H_counts;
    delete H_T1;
    delete H_T2;

  } // loop over files


  // scaling factors 
  float scalingFactorNa = 10./60.75;
  float scalingFactorSr = 10./3.28;

  // geometrical efficiency => configurazioni C1/C2/B1/B2
  float geomEff[6];
  geomEff[0] = 0.92252;      // A
  geomEff[1] = 0.78429;      // B1
  geomEff[2] = 0.70156;      // B2
  geomEff[3] = 0.80265;      // C1
  geomEff[4] = 0.75961;      // C2
  geomEff[5] = 0.35414;      // test
  
  // distances corresponding to these efficiencies
  float dist[6];
  float distErr[6];
  dist[0] = 1.5;
  dist[1] = 1.5+2.9;
  dist[2] = 1.5+4.82;
  dist[3] = 1.5+2.46;
  dist[4] = 1.5+3.54;
  dist[5] = 20.;          // test
  for (int ii=0; ii<6; ii++) distErr[ii] = 0.;

  // compute equivalent activity for C1/C2/B1/B2     
  float rescaledMean[8];
  float rescaledMeanErr[8];
  float rescaledMeanSmall[5];
  float rescaledMeanErrSmall[5];
  for (int ii=0; ii<5; ii++) {
    rescaledMean[ii]    = meanV[ii]*scalingFactorNa/geomEff[ii]; 
    rescaledMeanErr[ii] = meanErrV[ii]*scalingFactorNa/geomEff[ii]; 
    cout << "Normalized counts = " << rescaledMean[ii] << " +- " << rescaledMeanErr[ii] << endl;
  }

  // pol2 fit
  TF1 *mypol2  = new TF1("mypol2", "[0]+[1]*x+[2]*x*x",1.,6.5);
  TF1 *mypol2b = new TF1("mypol2b","[0]+[1]*x+[2]*x*x",1.,20.5);
  
  // to interpolate activities
  TGraphErrors *myGrapInt = new TGraphErrors(5, dist, rescaledMean, distErr, rescaledMeanErr);
  myGrapInt->SetMarkerSize(0.9);
  myGrapInt->SetMarkerStyle(20);
  myGrapInt->SetMarkerColor(4);
  myGrapInt->SetTitle("Na - air or plastic");
  myGrapInt->GetXaxis()->SetTitle("distance [mm]");
  myGrapInt->GetYaxis()->SetTitle("Counts");
  mypol2->SetParameters(200,-0.12,0);
  myGrapInt->Fit("mypol2");
  float myValue0 = mypol2->GetParameter(0);
  float myValue1 = mypol2->GetParameter(1);
  float myValue2 = mypol2->GetParameter(2);
  cout << "in 4.5 i conteggi sono " << myValue0+4.5*myValue1+4.5*myValue2*myValue2 << endl;
  TCanvas c4("c4","",1);
  myGrapInt->Draw("AP");
  c4.SaveAs("interpolationYield.png");

  TGraphErrors *myGrapInt2 = new TGraphErrors(6, dist, geomEff, distErr, distErr);
  myGrapInt2->SetMarkerSize(0.9);
  myGrapInt2->SetMarkerStyle(20);
  myGrapInt2->SetMarkerColor(4);
  myGrapInt2->SetTitle("Toy efficiency");
  myGrapInt2->GetXaxis()->SetTitle("distance [mm]");
  myGrapInt2->GetYaxis()->SetTitle("efficiency");
  myGrapInt2->Fit("mypol2b");
  float myValue0b = mypol2b->GetParameter(0);
  float myValue1b = mypol2b->GetParameter(1);
  cout << "in 4.5 l'efficienza e' " << myValue0b+4.5*myValue1b << endl;
  TCanvas c5("c5","",1);
  myGrapInt2->Draw("AP");
  c5.SaveAs("interpolationEfficiency.png");
  
  

  /*
  
  float meanVMC[10], meanErrVMC[10], sigmaVMC[10], sigmaErrVMC[10], widthMC[10], widthErrMC[10];
  float meanVPC[10], meanErrVPC[10], sigmaVPC[10], sigmaErrVPC[10], widthPC[10], widthErrPC[10];
  float temp1VMC[10], temp2VMC[10];
  float temp1VPC[10], temp2VPC[10];
  for (int ii=0; ii<3; ii++) {     
    meanVPC[ii]         = meanV[ii];
    meanErrVPC[ii]      = meanErrV[ii];
    sigmaVPC[ii]        = sigmaV[ii]; 
    sigmaErrVPC[ii]     = sigmaErrV[ii];
    widthPC[ii]         = width[ii];
    widthErrPC[ii]      = widthErr[ii];
    temp1VPC[ii]        = temp1V[ii];
    temp2VPC[ii]        = temp2V[ii];
    cout << "PC: mean = " << meanV[ii] 
	 << ", sigma = " << sigmaV[ii] << ", temp1 = " << temp1V[ii] << ", temp2 = " << temp2V[ii] << endl;
  }
  for (int ii=3; ii<8; ii++) {     
    int tii = ii-3;
    meanVMC[tii]         = meanV[ii];
    meanErrVMC[tii]      = meanErrV[ii];
    sigmaVMC[tii]        = sigmaV[ii]; 
    sigmaErrVMC[tii]     = sigmaErrV[ii];
    widthMC[tii]         = width[ii];
    widthErrMC[tii]      = widthErr[ii];
    temp1VMC[tii]        = temp1V[ii];
    temp2VMC[tii]        = temp2V[ii];
    cout << "MC: mean = " << meanV[ii] 
	 << ", sigma = " << sigmaV[ii] << ", temp1 = " << temp1V[ii] << ", temp2 = " << temp2V[ii] << endl;
  }
  
  gStyle->SetOptStat(0);
  TGraphErrors *myGmeanmc = new TGraphErrors(5,widthMC,meanVMC,widthErrMC,meanErrVMC);   
  TGraphErrors *myGmeanpc = new TGraphErrors(3,widthPC,meanVPC,widthErrPC,meanErrVPC);   
  myGmeanmc->SetMarkerColor(2);
  myGmeanmc->SetMarkerSize(0.9);
  myGmeanmc->SetMarkerStyle(20);
  myGmeanpc->SetMarkerColor(4);
  myGmeanpc->SetMarkerSize(0.9);
  myGmeanpc->SetMarkerStyle(21);

  TGraphErrors *myGsigmamc = new TGraphErrors(5,widthMC,sigmaVMC,widthErrMC,sigmaErrVMC);
  TGraphErrors *myGsigmapc = new TGraphErrors(3,widthPC,sigmaVPC,widthErrPC,sigmaErrVPC);
  myGsigmamc->SetMarkerColor(2);
  myGsigmamc->SetMarkerSize(0.9);
  myGsigmamc->SetMarkerStyle(20);
  myGsigmapc->SetMarkerColor(4);
  myGsigmapc->SetMarkerSize(0.9);
  myGsigmapc->SetMarkerStyle(21);

  TGraphErrors *myGtemp1mc = new TGraphErrors(5,widthMC,temp1VMC,widthErrMC,widthErrMC); 
  TGraphErrors *myGtemp1pc = new TGraphErrors(3,widthPC,temp1VPC,widthErrPC,widthErrPC); 
  myGtemp1mc->SetMarkerColor(2);
  myGtemp1mc->SetMarkerSize(0.9);
  myGtemp1mc->SetMarkerStyle(20);
  myGtemp1pc->SetMarkerColor(4);
  myGtemp1pc->SetMarkerSize(0.9);
  myGtemp1pc->SetMarkerStyle(21);

  TGraphErrors *myGtemp2mc = new TGraphErrors(5,widthMC,temp2VMC,widthErrMC,widthErrMC); 
  TGraphErrors *myGtemp2pc = new TGraphErrors(3,widthPC,temp2VPC,widthErrPC,widthErrPC); 
  myGtemp2mc->SetMarkerColor(2);
  myGtemp2mc->SetMarkerSize(0.9);
  myGtemp2mc->SetMarkerStyle(20);
  myGtemp2pc->SetMarkerColor(4);
  myGtemp2pc->SetMarkerSize(0.9);
  myGtemp2pc->SetMarkerStyle(21);

  TH2F *myHG;
  if (isStronzio) myHG = new TH2F("myHG","",100,1.,11.,100,2400.,2750.);
  if (isBario)    myHG = new TH2F("myHG","",100,1.,11.,100, 300.,1700.);  // to be changed
  myHG->GetXaxis()->SetTitle("d [mm]");
  myHG->GetYaxis()->SetTitle("mean");
  TCanvas c4("c4","",1);
  myHG->Draw();
  myGmeanmc->Draw("Psame");
  myGmeanpc->Draw("Psame");
  c4.SaveAs("trendsMean.png");

  TH2F *myHG2;
  if (isStronzio) myHG2 = new TH2F("myHG2","",100,1.,11.,100,40.,60.);
  if (isBario)    myHG2 = new TH2F("myHG2","",100,1.,11.,100,15.,45.);    // to be changed
  myHG2->GetXaxis()->SetTitle("d [mm]");
  myHG2->GetYaxis()->SetTitle("sigma");
  TCanvas c42("c42","",1);
  myHG2->Draw();
  myGsigmamc->Draw("Psame");
  myGsigmapc->Draw("Psame");
  c42.SaveAs("trendsSigma.png");

  TH2F *myHG3 = new TH2F("myHG3","",100,1.,11.,100,22.,30.);
  myHG3->GetXaxis()->SetTitle("d [mm]");
  myHG3->GetYaxis()->SetTitle("temp1");
  TCanvas c43("c43","",1);
  myHG3->Draw();
  myGtemp1mc->Draw("Psame");
  myGtemp1pc->Draw("Psame");
  c43.SaveAs("trendsTemp1.png");

  TH2F *myHG4 = new TH2F("myHG4","",100,1.,11.,100,22.,30.);
  myHG4->GetXaxis()->SetTitle("d [mm]");
  myHG4->GetYaxis()->SetTitle("temp2");
  TCanvas c44("c44","",1);
  myHG4->Draw();
  myGtemp2mc->Draw("Psame");
  myGtemp2pc->Draw("Psame");
  c44.SaveAs("trendsTemp2.png");

  */
  // Saving infos

}
