// Macros to draw source hitmap
// Created by VK 23.12.14

#include <Riostream.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH2F.h>

//#include "helpers.h"

void dblcol_adr_to_col_row(Int_t doublecol, Int_t address, Int_t &col, Int_t &row) {
    col = doublecol*2 + (address%4 < 2 ? 1 : 0);
    row = 2*(address/4) + 1-(address%2);
}

Bool_t SourceHitMap(TString filepath) {
    // read a raw palpide file and convert it to a plot

    ifstream rawfile(filepath.Data());
    if(!rawfile.good()) {
        cout << "File not found!" << endl;
        return kFALSE;
    }

//    TH2F *h = new TH2F("hplot", "pALPIDEfs generic plot;Column;Row", 1024, -0.5, 1024.-0.5, 512, -0.5, 512.-0.5);
    TH2F *h = new TH2F("hplot", "Radioactive source hitmap;Column;Row", 1024, -0.5, 1024.-0.5, 512, -0.5, 512.-0.5);

 
 
    Int_t dblcol, adr, nhits, col, row;

    while(rawfile >> dblcol >> adr >> nhits && rawfile.good()) {
        dblcol_adr_to_col_row(dblcol, adr, col, row);
        cout << dblcol << " " << adr << " " << col << " " << row << " " << nhits << endl;
    if (nhits < 1000)    h->Fill(col, row, nhits);
    }
  
    TCanvas *c1 = new TCanvas("c1", "Canvas 1", 0, 0, 1024, 512);
    c1->cd();
 
    h->SetStats(0);
    h->SetMarkerStyle(21);
    h->SetMarkerSize(0.5); 
 
    h->DrawCopy("COLZ");
//    h->DrawCopy();
    delete h;
  
    cout << "Done!" << endl;
    return kTRUE;
// exit(0);
}

  
