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
#include <TLegend.h>

using namespace std;

void counts() {

  // to be changed
  bool isStronzio = false;
  bool isBario    = true;

  // vectors
  float temp1V[8], temp2V[8];
  float meanV[8],  meanErrV[8];
  float sigmaV[8], sigmaErrV[8];
  float width[8],  widthErr[8];

  // Loop over files
  for (int iFile=0; iFile<8; iFile++) { widthErr[iFile] = 0.; }

  for (int iFile=0; iFile<8; iFile++) {

    // -------------------------
    TString scintName;
    if (iFile==0) { scintName = "2d2pc";  width[iFile] = 2.2; }
    if (iFile==1) { scintName = "3d2pc";  width[iFile] = 3.2; }
    if (iFile==2) { scintName = "4d1pc";  width[iFile] = 4.1; }
    if (iFile==3) { scintName = "2mc";    width[iFile] = 2.0; }
    if (iFile==4) { scintName = "4d2mc";  width[iFile] = 4.2; }
    if (iFile==5) { scintName = "6mc";    width[iFile] = 6.0; }
    if (iFile==6) { scintName = "8mc";    width[iFile] = 8.0; }
    if (iFile==7) { scintName = "10d2mc"; width[iFile] = 10.2; }

    // -------------------------
    // Reading from input files
    TString filename;
    if (isStronzio) filename = TString("stronzio/chiara")+scintName+TString(".txt");
    if (isBario)    filename = TString("bario/chiara")+scintName+TString(".txt");
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
    TString countName = TString("H_counts_")+scintName;    
    TString temp1Name = TString("H_temp1_")+scintName;    
    TString temp2Name = TString("H_temp2_")+scintName;    
    float xmin = 2400.;
    float xmax = 3000.;
    if (isStronzio) { xmin = 2200.; xmax = 3000.; }  
    if (isBario)    { xmin = 300.;  xmax = 1700.; }   
    TH1F *H_counts = new TH1F(countName,countName,100,xmin, xmax);
    TH1F *H_T1     = new TH1F(temp1Name,temp1Name, 50,22.,30.);
    TH1F *H_T2     = new TH1F(temp2Name,temp2Name, 50,22.,30.);
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

    // -------------------------
    // Plots
    gStyle->SetOptStat(111111);

    TCanvas c1("c1","",1);
    H_counts->SetLineColor(4);
    H_counts->SetLineWidth(2);
    H_counts->Draw();
    TString plotCountName = TString("counts_")+scintName+(".png");        
    c1.SaveAs(plotCountName);
    
    TCanvas c2("c2","",1);
    H_T1->SetLineColor(4);
    H_T1->SetLineWidth(2);
    H_T1->Draw();
    TString plotTemp1Name = TString("temp1_")+scintName+(".png");        
    c2.SaveAs(plotTemp1Name);

    TCanvas c3("c3","",1);
    H_T2->SetLineColor(4);
    H_T2->SetLineWidth(2);
    H_T2->Draw();
    TString plotTemp2Name = TString("temp2_")+scintName+(".png");        
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

  TLegend *leg = new TLegend(0.60,0.65,0.90,0.90);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->AddEntry(myGmeanmc, "Monocristallino", "lp");
  leg->AddEntry(myGmeanpc, "Policristallino", "lp");

  TH2F *myHG;
  if (isStronzio) myHG = new TH2F("myHG","",100,1.,11.,100,2400.,2750.);
  if (isBario)    myHG = new TH2F("myHG","",100,1.,11.,100, 300.,1700.);  
  myHG->GetXaxis()->SetTitle("d [mm]");
  myHG->GetYaxis()->SetTitle("mean");
  TCanvas c4("c4","",1);
  myHG->Draw();
  myGmeanmc->Draw("Psame");
  myGmeanpc->Draw("Psame");
  leg->Draw();
  if (isStronzio) c4.SaveAs("trendsMeanSrEstesa.png");
  if (isBario)    c4.SaveAs("trendsMeanBa.png");

  TH2F *myHG2;
  if (isStronzio) myHG2 = new TH2F("myHG2","",100,1.,11.,100,40.,60.);
  if (isBario)    myHG2 = new TH2F("myHG2","",100,1.,11.,100,15.,45.);  
  myHG2->GetXaxis()->SetTitle("d [mm]");
  myHG2->GetYaxis()->SetTitle("sigma");
  TCanvas c42("c42","",1);
  myHG2->Draw();
  myGsigmamc->Draw("Psame");
  myGsigmapc->Draw("Psame");
  leg->Draw();
  if (isStronzio) c42.SaveAs("trendsSigmaSrEstesa.png");
  if (isBario)    c42.SaveAs("trendsSigmaBa.png");

  TH2F *myHG3 = new TH2F("myHG3","",100,1.,11.,100,22.,30.);
  myHG3->GetXaxis()->SetTitle("d [mm]");
  myHG3->GetYaxis()->SetTitle("temp1");
  TCanvas c43("c43","",1);
  myHG3->Draw();
  myGtemp1mc->Draw("Psame");
  myGtemp1pc->Draw("Psame");
  leg->Draw();
  if (isStronzio) c43.SaveAs("trendsTemp1SrEstesa.png");
  if (isBario)    c43.SaveAs("trendsTemp1Ba.png");

  TH2F *myHG4 = new TH2F("myHG4","",100,1.,11.,100,22.,30.);
  myHG4->GetXaxis()->SetTitle("d [mm]");
  myHG4->GetYaxis()->SetTitle("temp2");
  TCanvas c44("c44","",1);
  myHG4->Draw();
  myGtemp2mc->Draw("Psame");
  myGtemp2pc->Draw("Psame");
  leg->Draw();
  if (isStronzio) c44.SaveAs("trendsTemp2SrEstesa.png");
  if (isBario)    c44.SaveAs("trendsTemp2Ba.png");

  
  // Saving infos

}
