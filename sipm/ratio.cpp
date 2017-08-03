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

void ratioplot() {

  // vectors
  float width[8];
  float temp1Bario[8], temp2Bario[8];
  float meanBario[8], scaledMeanBario[8];
  float temp1Stronzio[8], temp2Stronzio[8];
  float meanStronzio[8], scaledMeanStronzio[8];

  // ratios
  float temp1Ratio[8],   temp2Ratio[8],   meanRatio[8],   scaledMeanRatio[8],   err[8];
  float temp1RatioMC[8], temp2RatioMC[8], meanRatioMC[8], scaledMeanRatioMC[8], errMC[8];
  float temp1RatioPC[8], temp2RatioPC[8], meanRatioPC[8], scaledMeanRatioPC[8], errPC[8];
  float widthMC[8], widthPC[8];

  float scaledMeanBarioPC[8], scaledMeanBarioMC[8];
  float scaledMeanStronzioPC[8], scaledMeanStronzioMC[8];

  // scaling factors                       
  float scalingFactorBa = 10./42.6;
  float scalingFactorSr = 10./3.28;

  // hardcoded inputs
  width[0] = 2.2;
  width[1] = 3.2;
  width[2] = 4.1;
  width[3] = 2.0;
  width[4] = 4.2;
  width[5] = 6.0;
  width[6] = 8.0;
  width[7] = 10.2;

  meanBario[0] = 915.768; temp1Bario[0] = 25.6319; temp2Bario[0] = 25.8369;
  meanBario[1] = 1224.15; temp1Bario[1] = 28.7532; temp2Bario[1] = 27.1597;
  meanBario[2] = 1420.46; temp1Bario[2] = 26.7002; temp2Bario[2] = 25.7108; 
  meanBario[3] = 412.029; temp1Bario[3] = 23.8226; temp2Bario[3] = 22.8524; 
  meanBario[4] = 1014.16; temp1Bario[4] = 28.7983; temp2Bario[4] = 27.612; 
  meanBario[5] = 1241.15; temp1Bario[5] = 24.7404; temp2Bario[5] = 24.6973; 
  meanBario[6] = 1407.;   temp1Bario[6] = 24.1892; temp2Bario[6] = 23.9191; 
  meanBario[7] = 1414.24; temp1Bario[7] = 25.7827; temp2Bario[7] = 24.6987; 

  meanStronzio[0] = 2687.99; temp1Stronzio[0] = 23.5845; temp2Stronzio[0] = 22.9093;
  meanStronzio[1] = 2677.63; temp1Stronzio[1] = 24.7032; temp2Stronzio[1] = 23.5938;
  meanStronzio[2] = 2689.;   temp1Stronzio[2] = 24.282;  temp2Stronzio[2] = 23.3902; 
  meanStronzio[3] = 2487.82; temp1Stronzio[3] = 24.2439; temp2Stronzio[3] = 23.3814; 
  meanStronzio[4] = 2691.91; temp1Stronzio[4] = 24.1153; temp2Stronzio[4] = 23.6985; 
  meanStronzio[5] = 2715.42; temp1Stronzio[5] = 23.9028; temp2Stronzio[5] = 23.5048; 
  meanStronzio[6] = 2626.34; temp1Stronzio[6] = 25.3854; temp2Stronzio[6] = 24.4374; 
  meanStronzio[7] = 2563.22; temp1Stronzio[7] = 23.6256; temp2Stronzio[7] = 23.7785; 

  for (int ii=0; ii<8; ii++) {
    scaledMeanBario[ii]    = meanBario[ii]*scalingFactorBa;
    scaledMeanStronzio[ii] = meanStronzio[ii]*scalingFactorSr;
    meanRatio[ii]          = meanBario[ii]/meanStronzio[ii];
    scaledMeanRatio[ii]    = scaledMeanBario[ii]/scaledMeanStronzio[ii];
    temp1Ratio[ii]         = temp1Bario[ii]/temp1Stronzio[ii];
    temp2Ratio[ii]         = temp2Bario[ii]/temp2Stronzio[ii];
    err[ii] = 0.;
    cout << scaledMeanBario[ii] << " " << scaledMeanStronzio[ii] << " " << scaledMeanRatio[ii] << endl;
  }

  for (int ii=0; ii<3; ii++) {     
    scaledMeanBarioPC[ii]    = meanBario[ii]*scalingFactorBa;
    scaledMeanStronzioPC[ii] = meanStronzio[ii]*scalingFactorSr;
    meanRatioPC[ii]          = meanRatio[ii];
    scaledMeanRatioPC[ii]    = scaledMeanBarioPC[ii]/scaledMeanStronzioPC[ii];
    temp1RatioPC[ii]         = temp1Ratio[ii]; 
    temp2RatioPC[ii]         = temp2Ratio[ii]; 
    widthPC[ii]              = width[ii];
  }
  for (int ii=3; ii<8; ii++) {     
    int tii = ii-3;
    scaledMeanBarioMC[tii]    = meanBario[ii]*scalingFactorBa;
    scaledMeanStronzioMC[tii] = meanStronzio[ii]*scalingFactorSr;
    meanRatioMC[tii]          = meanRatio[ii];
    scaledMeanRatioMC[tii]    = scaledMeanBarioMC[tii]/scaledMeanStronzioMC[tii];
    temp1RatioMC[tii]         = temp1Ratio[ii]; 
    temp2RatioMC[tii]         = temp2Ratio[ii]; 
    widthMC[tii]              = width[ii];
  }


  gStyle->SetOptStat(0);
  TGraphErrors *myGSmeanBamc = new TGraphErrors(5,widthMC,scaledMeanBarioMC,err,err);
  TGraphErrors *myGSmeanBapc = new TGraphErrors(5,widthPC,scaledMeanBarioPC,err,err);
  myGSmeanBamc->SetMarkerColor(2);
  myGSmeanBamc->SetMarkerSize(0.9);
  myGSmeanBamc->SetMarkerStyle(20);
  myGSmeanBapc->SetMarkerColor(4);
  myGSmeanBapc->SetMarkerSize(0.9);
  myGSmeanBapc->SetMarkerStyle(21);

  TGraphErrors *myGSmeanSrmc = new TGraphErrors(5,widthMC,scaledMeanStronzioMC,err,err);
  TGraphErrors *myGSmeanSrpc = new TGraphErrors(5,widthPC,scaledMeanStronzioPC,err,err);
  myGSmeanSrmc->SetMarkerColor(2);
  myGSmeanSrmc->SetMarkerSize(0.9);
  myGSmeanSrmc->SetMarkerStyle(20);
  myGSmeanSrpc->SetMarkerColor(4);
  myGSmeanSrpc->SetMarkerSize(0.9);
  myGSmeanSrpc->SetMarkerStyle(21);

  TGraphErrors *myGSRatiomc = new TGraphErrors(5,widthMC,scaledMeanRatioMC,err,err);
  TGraphErrors *myGSRatiopc = new TGraphErrors(5,widthPC,scaledMeanRatioPC,err,err);
  myGSRatiomc->SetMarkerColor(2);
  myGSRatiomc->SetMarkerSize(0.9);
  myGSRatiomc->SetMarkerStyle(20);
  myGSRatiopc->SetMarkerColor(4);
  myGSRatiopc->SetMarkerSize(0.9);
  myGSRatiopc->SetMarkerStyle(21);

  TGraphErrors *myGtemp1mc = new TGraphErrors(5,widthMC,temp1RatioMC,err,err);   
  TGraphErrors *myGtemp1pc = new TGraphErrors(3,widthPC,temp1RatioPC,err,err);   
  myGtemp1mc->SetMarkerColor(2);
  myGtemp1mc->SetMarkerSize(0.9);
  myGtemp1mc->SetMarkerStyle(20);
  myGtemp1pc->SetMarkerColor(4);
  myGtemp1pc->SetMarkerSize(0.9);
  myGtemp1pc->SetMarkerStyle(21);

  TGraphErrors *myGtemp2mc = new TGraphErrors(5,widthMC,temp2RatioMC,err,err);   
  TGraphErrors *myGtemp2pc = new TGraphErrors(3,widthPC,temp2RatioPC,err,err);   
  myGtemp2mc->SetMarkerColor(2);
  myGtemp2mc->SetMarkerSize(0.9);
  myGtemp2mc->SetMarkerStyle(20);
  myGtemp2pc->SetMarkerColor(4);
  myGtemp2pc->SetMarkerSize(0.9);
  myGtemp2pc->SetMarkerStyle(21);

  TH2F *myHGR = new TH2F("myHGR","",100,1.,11.,100,0.,0.1);  // to be changed
  myHGR->GetXaxis()->SetTitle("d [mm]");
  myHGR->GetYaxis()->SetTitle("scaled mean ratio (gamma/ele)");
  TCanvas c4("c4","",1);
  myHGR->Draw();
  myGSRatiomc->Draw("Psame");
  myGSRatiopc->Draw("Psame");
  c4.SaveAs("trendsScaledMeanRatio.png");

  TH2F *myHGSM = new TH2F("myHGSM","",100,1.,11.,100,0.,10000.);  // to be changed
  myHGSM->GetXaxis()->SetTitle("d [mm]");
  myHGSM->GetYaxis()->SetTitle("scaled mean");
  TCanvas c4a("c4a","",1);
  c4a.SetLogy();
  myHGSM->Draw();
  myGSmeanBamc->Draw("Psame");
  myGSmeanSrmc->Draw("Psame");
  myGSmeanBapc->Draw("Psame");
  myGSmeanSrpc->Draw("Psame");
  c4a.SaveAs("trendsScaledMean.png");

  TH2F *myHG2 = new TH2F("myHG2","",100,1.,11.,100,0.5,1.5);  // to be changed
  myHG2->GetXaxis()->SetTitle("d [mm]");
  myHG2->GetYaxis()->SetTitle("temp1 ratio (gamma/ele)");
  TCanvas c4b("c4b","",1);
  myHG2->Draw();
  myGtemp1mc->Draw("Psame");
  myGtemp1pc->Draw("Psame");
  c4b.SaveAs("trendsTemp1Ratio.png");

  TH2F *myHG3 = new TH2F("myHG3","",100,1.,11.,100,0.5,1.5);  // to be changed
  myHG3->GetXaxis()->SetTitle("d [mm]");
  myHG3->GetYaxis()->SetTitle("temp2 ratio (gamma/ele)");
  TCanvas c4c("c4c","",1);
  myHG3->Draw();
  myGtemp2mc->Draw("Psame");
  myGtemp2pc->Draw("Psame");
  c4c.SaveAs("trendsTemp2Ratio.png");
}
