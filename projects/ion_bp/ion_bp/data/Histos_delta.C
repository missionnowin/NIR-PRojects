//Macros to prepare histos
//VK 30.05.18
   
#include "TH1.h"
#include "TH1D.h"
#include "TMath.h"
#include "TF1.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPaveLabel.h"
#include <iostream>

// Background function 
Double_t background(Double_t *x, Double_t *par) {
   return par[0] + par[1]*x[0] + par[2]*x[0]*x[0] + par[3]*x[0]*x[0]*x[0];
}

// Gaussian function
Double_t signal(Double_t *x, Double_t *par) {
  return par[0] * TMath::Exp(-(x[0]-par[1])*(x[0]-par[1]) / (2.*par[2]*par[2]));
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
//  return background(x,par) + lorentzianPeak(x,&par[3]);
  return background(x,par) + signal(x,&par[4]);
}

void Histos_delta() {

   TCanvas *c1 = new TCanvas("c1","Hit map",10,10,700,500);
//   c1->SetFillColor(33);
//   c1->SetFrameFillColor(41);
   c1->SetGrid();
   
// Get histogram from root file

   TFile *file = new TFile("bp_helium_hist.root");
//    TFile *file = new TFile("bp_test_vacuum.root");
// From tree
//   TTree *t1 = hypers;
//   t1 -> Draw("massh");    
//   TH1D *hist= new TH1D("hist","Lambdas invariant mass spectrum",100,1.07,1.17);
//   t1 -> Project("hist","massh","chi2s[0]>=5.0 && chi2s[1]>=5.0 && chi2h<5. ");  //TPC+ITS(5spd)_ideal

// From histograms list
   TH2D *hist = (TH2D*)file->Get("0;1");
//   TH1D *hist = (TH1D*)file->Get("11;1");

   hist->SetMarkerStyle(21);
   hist->SetMarkerSize(0.8);
   hist->SetStats(1);
//   hist->SetTitle("Delta-electrons hit map in Sts1");
//  hist->SetTitle("Pion number distribution in Sts1");

// Title of x axis
   hist->GetXaxis()->SetTitle("X, mm");
//  hist->GetXaxis()->SetTitle("Number of electrons");// Title of y axis
   hist->GetYaxis()->SetTitle("Y, mm"); 
//  hist->GetYaxis()->SetTitle("Number of events"); 

/*
    Double_t  binCont = 0, xBin, yBin;
    Double_t  xMin=-240., xMax=240., yMin=-200., yMax=200.;
   for (Int_t ix = 0; ix < 5; ++ix){
    xMin+=10*ix;
    xMax-=10*ix;    
    yMin+=10*ix;
    yMax-=10*ix;   
    for (Int_t binx = 0; binx < 101; ++binx) {
     for (Int_t biny = 0; biny < 101; ++biny) {
       TAxis *xaxis = hist->GetXaxis();
       xBin = xaxis->GetBinCenter(binx);
       TAxis *yaxis = hist->GetYaxis();
       yBin = yaxis->GetBinCenter(biny);
       if( xBin<=xMax && xBin>=xMin && yBin<=yMax && yBin>=yMin)
       binCont = binCont + hist->GetCellContent(binx,biny);
//  cout << " XBin number = " << binx << " Bin content = " << binCont << endl;
      }
     }
   cout << "xMin = " << xMin << " xMax = " << xMax << " yMin = " << yMin << " yMax = " << yMax<< " Bin content = " << binCont << endl;
   binCont = 0;
  }
*/

//  hist->Draw();  

//   Double_t xbinMin=0. ,xbinMax=30.;
//   TF1 *fit = new TF1("fit","gauss",xbinMin,xbinMax,2); 
//   h2->Fit("fit","Q","P", xbinMin,xbinMax);
//   fit->Draw("same"); 
//     hist.Fit("gaus");

  hist->Draw("colz");
 
//    hist->GetXaxis()->SetTitleOffset(1.5);
//    hist->GetYaxis()->SetTitleOffset(1.5); 
//    hist->Draw("lego2");
//  hist->Draw("surf2");

  pad1 = new TPad("pad1", "pad1",.01,.01,.99,.99);
     pad1 -> SetFillStyle(4000);
     pad1->Draw();
     pad1->cd();

   TPaveText *pt = new TPaveText(.15,.65,.35,.90);
//   pt->AddText("4DSSD + 7GEM");
//   pt->AddText("Helium beam pipe");
//   pt->AddText("Vacuum beam pipe");
   pt->AddText("Au ion: E=5AGeV");
   pt->Draw();

/*

  for (Int_t evt = 0;  evt < 1; ++evt) {

   TH1D *hx= new TH1D("hx","X",1000, -20.0, 20.0);  
   t1 -> Project("hx","StsHit.fX","","",1,evt);
   TAxis *xaxis = hx->GetXaxis();
   for (Int_t binx = 1; binx < 1000; ++binx) {
     if (hx->GetBinContent(binx) >= 1){ 
        Double_t  xbinMin = xaxis->GetBinCenter(binx-10);
        break;
      }
    }
   for (Int_t binx = 1000; binx >1; --binx) {
     if (hx->GetBinContent(binx) >= 1){ 
        Double_t xbinMax = xaxis->GetBinCenter(binx+10);
        break;
      }
    }
   cout << " Xmin = " << xbinMin << " Xmax = " << xbinMax << endl;


   TH1D *hy= new TH1D("hy","X",1000, -20.0, 20.0);  
   t1 -> Project("hy","StsHit.fY","","",1,evt);
   TAxis *yaxis = hy->GetXaxis();
   for (Int_t biny = 1; biny < 1000; ++biny) {
     if (hy->GetBinContent(biny) >= 1){ 
        Double_t ybinMin = yaxis->GetBinCenter(biny-10);
        break;
      }
    }
   for (Int_t biny = 1000; biny >1; --biny) {
     if (hy->GetBinContent(biny) >= 1){ 
        Double_t ybinMax = yaxis->GetBinCenter(biny+10);
        break;
      }
    }
   cout << " Ymin = " << ybinMin << " Ymax = " << ybinMax << endl;

   TH2D *h1= new TH2D("h1","XY",100, xbinMin, xbinMax,100, ybinMin, ybinMax);  
   t1 -> Project("h1","StsHit.fY:StsHit.fX","","",1,evt);

   Int_t ItsHits = h1-> GetEntries();
   cout << " Number of ITS hits: " << ItsHits << endl;
   TAxis *xaxis = h1->GetXaxis();
   TAxis *yaxis = h1->GetYaxis();
//   t1->Draw("StsHit.fX:StsHit.fY");
//   h1->Draw();

   TH1D *h2= new TH1D("h2","Y=P0+P1*X",1000, xbinMin,xbinMax);
    for (Int_t binx = 0; binx < 1000; ++binx) {
      for (Int_t biny = 0; biny < 1000; ++biny) {
   Double_t xbin = xaxis->GetBinCenter(binx);
   Double_t ybin = yaxis->GetBinCenter(biny); 
   if (h1->GetCellContent(binx,biny) >= 1) h2->Fill(xbin,ybin);
      }
   }

   h2->SetMarkerStyle(21);
   h2->SetMarkerSize(0.8);
   h2->Draw("p");

   TF1 *fit = new TF1("fit",linear,xbinMin,xbinMax,2); 
   h2->Fit("fit","Q","P", xbinMin,xbinMax);
   fit->Draw("same"); 
   Float_t DY = fit->GetParameter(0);
   Float_t sigmaDY = fit->GetParError(0);
   cout << " DY = " << DY << " SigmaDY = " << sigmaDY<< endl;

  hresy->Fill(DY);
 
  delete hx;
  delete hy; 
  delete h1;
  delete h2;
  delete fit;
 } 



// Fit histogram
  gStyle->SetOptFit(011);

// Signal+background
//  TF1 *fit = new TF1("fit",fitFunction,1.095,1.160,7); 
TF1 *fit = new TF1("fit",fitFunction,1.10,1.13,7); 
  fit->SetNpx(500);
  fit->SetLineWidth(3);
  fit->SetLineColor(kMagenta);
  fit->SetParameters(1.,1.,1.,1.,hist->GetMaximum(),1.116,0.002);
// fit->SetParameters(-1.e+6,1.e+6,1.e+6,-1.e+6,2000,1.116,0.001);
//fit->SetParameters(1.,1.,1.,1.,2000,1.116,0.004); // pt >0.6 GeV
//fit->SetParameters(1.,1.,1.,1.,200,1.116,0.002); // pt<0.6 GeV
  hist->Fit("fit","W","EP",1.10,1.13);
  fit->Draw("same");


// Signal  
  TF1 *fit1 = new TF1("fit1",signal,1.10,1.13,3);
  fit1->SetLineColor(kBlue);
  fit1->SetNpx(500);

// Background
  TF1 *fit2 = new TF1("fit2",background,1.10,1.13,4);
  fit2->SetLineColor(kRed); 
 
  Float_t peak = fit->GetParameter(4);
  Float_t mass = fit->GetParameter(5);
  Float_t sigma = fit->GetParameter(6);
  fit1->SetParameters(peak,mass,sigma);
  fit1->Draw("same");

  Float_t par1 = fit->GetParameter(0);
  Float_t par2 = fit->GetParameter(1);
  Float_t par3 = fit->GetParameter(2);
  Float_t par4 = fit->GetParameter(3);
  fit2->SetParameters(par1,par2,par3,par4);
  fit2->Draw("same");

  Float_t sgn = fit1->Integral(mass-2*sigma,mass+2*sigma)/hist->GetBinWidth(1);
  Float_t bkg = fit2->Integral(mass-2*sigma,mass+2*sigma)/hist->GetBinWidth(1);
  cout << " +- 2*sigma: S= " << sgn << " B= " << bkg << " S/B= " << sgn / bkg << " S/sqrt(S+B)= " << sgn/TMath::Sqrt(TMath::Abs(sgn)+TMath::Abs(bkg)) << " Eff= " << sgn*100./MCTrackLamddas << endl;
  
  sgn = fit1->Integral(mass-3*sigma,mass+3*sigma)/hist->GetBinWidth(1);
  bkg = fit2->Integral(mass-3*sigma,mass+3*sigma)/hist->GetBinWidth(1);
  cout << " +- 3*sigma: S=" << sgn << " B= " << bkg << " S/B= " << sgn / bkg << " S/sqrt(S+B)= " << sgn/TMath::Sqrt(TMath::Abs(sgn)+TMath::Abs(bkg)) << " Eff= " << sgn*100./MCTrackLamddas<< endl;


   // draw the legend
   TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
//   TLegend *legend=new TLegend(0.6,0.25,0.88,0.45);
   legend->SetTextFont(72);
   legend->SetTextSize(0.04);
   legend->AddEntry(hist,"Data","lpe");
   legend->AddEntry(fit2,"Background fit","l");
   legend->AddEntry(fit1,"Signal fit","l");
   legend->AddEntry(fit,"Global Fit","l");
   legend->Draw();

     pad1 = new TPad("pad1", "pad1",.01,.01,.99,.99);
     pad1 -> SetFillStyle(4000);
     pad1->Draw();
     pad1->cd();

 
   TPaveText *pt = new TPaveText(.15,.65,.35,.90);
//   pt->AddText(" ");

   pt->AddText("TPC+ITS45ID");
//   pt->AddText("TPC + ITS(2 MAPS + 4 DSSD)");
//   pt->AddText("Ideal hitproducer");
   pt->AddText("Pt < 0.6 GeV");
//   pt->AddText("S = 8168");
//   pt->AddText("B = 83316");
   pt->AddText("S/sqrt(B+S) = 16.9");
   pt->AddText("S/B = 3.9");
   pt->AddText("Eff = 2.54%");
//   pt->AddText("Step = 0.01");
//   pt->AddText("Threshold = 0.001");
//   pt->SetLabel("Parameters");
   pt->Draw();
//   c1->cd();
//   TPaveLabel *pl = new TPaveLabel(0.5,0.5,0.8,0.8, "S/N = 5.39","NDC");
//   pl->SetBorderSize(1);
//   pl->Draw();

*/

 }
 

