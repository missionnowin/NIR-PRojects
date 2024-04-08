
#include <Riostream.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>

void Deposit_energy() {
    // read a raw file and convert it to a plot
    
    double Emax = 50.;
    TString filepath = "spectrum.dat";
    ifstream rawfile(filepath.Data());
    if(!rawfile.good()) {
        cout << "File not found!" << endl;
        return;
    }

    TH1F *h1 = new TH1F("h1", "Bremsstrahlung spectrum", 100, 0.52, 51.48);
    h1->SetStats(1);
    h1->GetXaxis()->SetTitle("E, MeV");
    h1->GetYaxis()->SetTitle("N");

    TH1F *h2 = new TH1F("h2", "Normalized bremsstrahlung spectrum", 99, 0.010296*2, 1.0296);
    h2->SetStats(1);
    h2->GetXaxis()->SetTitle("E/T");
    h2->GetYaxis()->SetTitle("N");

    TH1F *h3 = new TH1F("h3", "Bremsstrahlung spectrum", 20, 0.5, 10.5);
    h3->SetStats(1);
    h3->GetXaxis()->SetTitle("E, MeV");
    h3->GetYaxis()->SetTitle("N");

    double bin1,bin2;
    int count;

    while(rawfile >> bin1 >> count && rawfile.good()) 
    {cout << bin1 << " " << count << endl;
        h1->Fill(bin1, count);
        bin2=bin1/Emax;
        h2->Fill(bin2, count);
        h3->Fill(bin1, count);
     }
  
    TCanvas *c1 = new TCanvas("c1", "Canvas 1", 0, 0, 1024, 512);
    c1->Divide (2,1);
    c1->cd(1);
    h1->Draw();
    c1->cd(2);
    h2->Draw();
 
    TCanvas *c2 = new TCanvas("c2", "Canvas 1", 0, 0, 1024, 512);
    c2->cd();
    h3->Draw(); 

  cout << "Done!" << endl;
   
}
