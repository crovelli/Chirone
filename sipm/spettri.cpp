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
#include "TH1.h"
#include "TCanvas.h"

using namespace std;

void spettri() {

  gStyle->SetOptStat();

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
    TString filename = TString("testSodio/spettriChiara/F1spettrochiaraSodioMisura")+measName+TString("00000.txt");
    cout << "Reading file: " << filename << endl;

    ifstream *intxt = new ifstream(filename);
    char Buffer[10000];
    float myboh[5000], myEntries[5000];
    int IFC=0;
    while( !(intxt->eof()) ){
      intxt->getline(Buffer,10000);
      if (!strstr(Buffer,"#") && !(strspn(Buffer," ") == strlen(Buffer))){
	sscanf(Buffer,"%f %f", &myboh[IFC], &myEntries[IFC]);
      }
      IFC++;
    }
    intxt->close();
    delete intxt;

    // -------------------------
    // Filling histo with distributions
    TString countName = TString("H_spectrum_")+measName;    
    float xmin = 0.;
    float xmax = (float)(IFC-1);
    int binNum = IFC-1;
    int countBad = 0;
    TH1F *H_spectrum = new TH1F(countName,countName,binNum,xmin, xmax);
    for (int ii=1; ii<=binNum; ii++) {
      if (myEntries[ii]>-1 && myEntries[ii]<10000) H_spectrum -> SetBinContent(ii,myEntries[ii]);
      else countBad++;
    }
    cout << "bad: " << countBad << endl;

    // -------------------------
    // Plots
    TCanvas c1("c1","",1);
    H_spectrum->SetLineColor(iFile+1);
    H_spectrum->SetLineWidth(2);
    H_spectrum->Draw();
    TString plotCountName = TString("spettro_")+measName+(".png");        
    c1.SaveAs(plotCountName);

    // Output
    TFile *outFile;
    if (iFile==0) outFile = new TFile ("output.root","RECREATE","histoSiPm");
    else outFile = new TFile ("output.root","UPDATE","histoSiPm");
    outFile->cd();
    H_spectrum->Write();
    outFile->Close();
    delete outFile;

    // Deletion
    delete H_spectrum;

  } // loop over files


  // Now reading histos
  TFile *fileIn = new TFile ("output.root");
  TH1F *Hr_spectrum_A  = (TH1F*)fileIn->Get("H_spectrum_A");
  TH1F *Hr_spectrum_B1 = (TH1F*)fileIn->Get("H_spectrum_B1");
  TH1F *Hr_spectrum_B2 = (TH1F*)fileIn->Get("H_spectrum_B2");
  TH1F *Hr_spectrum_C1 = (TH1F*)fileIn->Get("H_spectrum_C1");
  TH1F *Hr_spectrum_C2 = (TH1F*)fileIn->Get("H_spectrum_C2");
  TH1F *Hr_spectrum_D  = (TH1F*)fileIn->Get("H_spectrum_D");
  TH1F *Hr_spectrum_E  = (TH1F*)fileIn->Get("H_spectrum_E");
  TH1F *Hr_spectrum_F  = (TH1F*)fileIn->Get("H_spectrum_F");

  TCanvas c2("c2","",1);
  Hr_spectrum_A->Draw();
  Hr_spectrum_B1->Draw("same");
  Hr_spectrum_B2->Draw("same");
  Hr_spectrum_C1->Draw("same");
  Hr_spectrum_C2->Draw("same");
  Hr_spectrum_D->Draw("same");
  Hr_spectrum_E->Draw("same");
  Hr_spectrum_F->Draw("same");
  c2.SaveAs("allSpectra.png");

  TCanvas c3("c3","",1);
  Hr_spectrum_A->DrawNormalized();
  Hr_spectrum_B1->DrawNormalized("same");
  Hr_spectrum_B2->DrawNormalized("same");
  Hr_spectrum_C1->DrawNormalized("same");
  Hr_spectrum_C2->DrawNormalized("same");
  Hr_spectrum_D->DrawNormalized("same");
  Hr_spectrum_E->DrawNormalized("same");
  Hr_spectrum_F->DrawNormalized("same");
  c3.SaveAs("allSpectraNorm.png");
  
}
