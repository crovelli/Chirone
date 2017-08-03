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

void spettriTriggerDebug() {

  gStyle->SetOptStat(0);

  // Loop over files
  for (int iFile=0; iFile<7; iFile++) {

    TString measName;
    if (iFile==0) measName = "esteso";
    if (iFile==1) measName = "giallo"; 
    if (iFile==2) measName = "gialloPb"; 
    if (iFile==3) measName = "gialloAlluminum"; 
    if (iFile==4) measName = "esteso3sipm";
    if (iFile==5) measName = "esteso2sipm";
    if (iFile==6) measName = "esteso1sipm";

    // -------------------------
    // Reading from input files
    TString filename = TString("testDebug/F1sr")+measName+TString("00000.txt");
    cout << "Reading file: " << filename << endl;

    ifstream *intxt = new ifstream(filename);
    char Buffer[10000];
    float myboh[10000], myEntries[10000];
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
      if (myEntries[ii]>-1 && myEntries[ii]<500000) H_spectrum -> SetBinContent(ii,myEntries[ii]);
      else countBad++;
    }
    cout << "bad: " << countBad << endl;

    // -------------------------
    // Plots
    TCanvas c1("c1","",1);
    if (iFile<4)  H_spectrum->SetLineColor(iFile+1);
    if (iFile>=4) H_spectrum->SetLineColor(iFile-2);
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
  TH1F *Hr_spectrum_Esteso      = (TH1F*)fileIn->Get("H_spectrum_esteso");
  TH1F *Hr_spectrum_Giallo      = (TH1F*)fileIn->Get("H_spectrum_giallo");
  TH1F *Hr_spectrum_GialloPb    = (TH1F*)fileIn->Get("H_spectrum_gialloPb");
  TH1F *Hr_spectrum_GialloAl    = (TH1F*)fileIn->Get("H_spectrum_gialloAlluminum");
  TH1F *Hr_spectrum_Esteso3sipm = (TH1F*)fileIn->Get("H_spectrum_esteso3sipm");
  TH1F *Hr_spectrum_Esteso2sipm = (TH1F*)fileIn->Get("H_spectrum_esteso2sipm");
  TH1F *Hr_spectrum_Esteso1sipm = (TH1F*)fileIn->Get("H_spectrum_esteso1sipm");


  TCanvas c3("c3","",1);
  Hr_spectrum_Giallo->Scale(685./(Hr_spectrum_Giallo->Integral()));            // normalizzati all'attivita' misurata
  Hr_spectrum_GialloPb->Scale(846./(Hr_spectrum_GialloPb->Integral()));
  Hr_spectrum_GialloAl->Scale(740./(Hr_spectrum_GialloAl->Integral()));
  Hr_spectrum_GialloPb->Draw();
  Hr_spectrum_Giallo->Draw("same");
  Hr_spectrum_GialloAl->Draw("same");
  c3.SaveAs("allSpectraDebugSrNormActivity.png");

  TCanvas c4("c4","",1);
  Hr_spectrum_Esteso->Scale(2514./(Hr_spectrum_Esteso->Integral()));
  Hr_spectrum_Esteso3sipm->Scale(2483./(Hr_spectrum_Esteso3sipm->Integral()));
  Hr_spectrum_Esteso2sipm->Scale(2332./(Hr_spectrum_Esteso2sipm->Integral()));
  Hr_spectrum_Esteso1sipm->Scale(2306./(Hr_spectrum_Esteso1sipm->Integral()));
  Hr_spectrum_Esteso1sipm->Draw();
  //Hr_spectrum_Esteso2sipm->Draw("same");
  //Hr_spectrum_Esteso3sipm->Draw("same");
  Hr_spectrum_Esteso->Draw("same");
  c4.SaveAs("allSpectraDebugSrNormActivityNSipm.png");

}
