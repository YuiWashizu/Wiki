#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <sstream>
#include <TF1.h>
#include <TTree.h>
#include <TStyle.h>
#include <TText.h>
#include <unistd.h>
#include <TGraphErrors.h>
#include <TROOT.h>
#include <TChain.h>

using namespace std;

void check_30ch_fitgauss(int filenum_i, int filenum_n) {


  int ped_min = 750;
  int ped_max = 850;
  int ini_mean = 820;
  int ini_sigma = 7;

  TString name;
  name.Form(Form("fit_gaus_from%d_to%d.pdf", filenum_i, filenum_n));
  TCanvas* c = new TCanvas(name.Data(),name.Data(), 900, 900);
  c->Print(name + "[", "pdf");

  for (int filenum=filenum_i; filenum<filenum_n; filenum++) {
    int i = filenum-filenum_i+1;
    TH1D* adc_hist = new TH1D("adc_hist", Form("adc_hist_%d", filenum), 400, 700, 1100);

    TFile* f = TFile::Open(Form("./sc2018_data8.7/sc0%d.root", filenum));
    TTree* t = dynamic_cast<TTree*>(f->Get("tree"));
    int adc[32];
    t->SetBranchAddress("adc", &adc);
    int nevent = t->GetEntries();
  
    for (int event=0; event<nevent; event++) {
      t->GetEntry(event);
      adc_hist->Fill(adc[30]);
    }

    TF1* fit_gaus = new TF1("fit_gaus", "[0]*TMath::Gaus(x,[1],[2])", 0, 4000);
    fit_gaus->SetParameter(0, 45);
    fit_gaus->SetParameter(1, ini_mean);
    fit_gaus->SetParameter(2, ini_sigma);
    adc_hist->Fit("fit_gaus", "", "", ped_min, ped_max);

    adc_hist->Draw();    
    c->SetLogy();
    c->Print(name, "pdf");
  }
  c->Print(name + "]", "pdf");
}
    
