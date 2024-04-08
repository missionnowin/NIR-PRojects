/* Written by Miljenko Suljic, m.suljic@cern.ch */

#include <Riostream.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>

Bool_t scanDACs() {
    
    const Int_t   n_dacs = 10;
    const TString filename[n_dacs] = {"VAUX", "VRESET", "VCASN", "VCASP", "VPULSEL", "VPULSEH", "IRESET", "IBIAS", "IDB", "ITHR"};
    const Int_t   n_bits = 255;

    TCanvas *c1 = new TCanvas("cdacs", "pALPIDEfs DACs", 0, 0, 1000, 600);
    c1->Divide(5, 2);
    TGraph *grdac[n_dacs];
    Float_t dac[n_bits], adc[n_bits];

    for(Int_t i=0; i<n_dacs; ++i) {
        TString filepath = "../pALPIDEfs-software/Data/";
        filepath += (filename[i].BeginsWith("V") ? "VDAC" : "IDAC") + filename[i] + ".dat";
        ifstream dacfile(filepath.Data());
        if(!dacfile.good()) { cout << "Cannot find " << filename << endl; return kFALSE; }
        for(Int_t j=0; j<n_bits; ++j) {
            if(!dacfile.good()) { cout << "Problem in " << filename << endl; return kFALSE; }
            dacfile >> dac[j] >> adc[j];
        }
        c1->cd(i+1);
        grdac[i] = new TGraph(n_bits, dac, adc);
        grdac[i]->SetTitle(filename[i] + (filename[i].BeginsWith("V") ? ";DAC;Voltage [V]" : ";DAC;Current [nA]"));
//        grdac[i]->SetMarkerStyle(21);
        grdac[i]->SetMarkerColor(2);
        grdac[i]->SetLineColor(2);
        grdac[i]->Draw("APL");
    }

    cout << "Done!" << endl;
    return kTRUE;
}
