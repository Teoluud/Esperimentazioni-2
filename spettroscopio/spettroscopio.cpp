#include <iostream>       // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h> // ci serve per istanziare grafici
#include <TAxis.h>        // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>      // ci serve per disegnare i grafici
#include <TF1.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include <TH1.h>
#include <TMath.h>
#include <fstream>
#include <TLatex.h>
#include <TStyle.h>

using namespace std;

void spettroscopio()
{
  Int_t npoints = 10;
  Float_t nn = 0, nl = 0, nsn = 0, nsl = 0;
  Float_t n[npoints];
  Float_t sn[npoints];
  Float_t l[npoints];
  Float_t sl[npoints];
  fstream file;
  file.open("dati_spettroscopio.txt", ios::in);

  for (int j = 0; j < npoints; j++)
  {
    file >> nl >> nsl >> nn >> nsn;
    n[j] = nn;
    sn[j] = nsn;
    l[j] = nl*1e9;
    sl[j] = nsl*1e9;
  }
  file.close();
  for (int j = 0; j < npoints; j++)
  {
    // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
    cout << "Measurement number " << j << ":\t lambda = (" << l[j] << " +- " << sl[j] << ") nm, \t n = (" << n[j] << " +- " << sn[j] << ")" << endl;
    // ----------------------------------------------------------------- //
  }
  
  // Canvas
  TCanvas *c1 = new TCanvas("c1", "c1", 200, 10, 600, 400);
  TGraphErrors *g1 = new TGraphErrors(npoints, l, n, sl, sn);
  g1->SetMarkerSize(0.6);
  g1->SetMarkerStyle(21);
  g1->GetXaxis()->SetTitle("#lambda (nm)");
  g1->GetYaxis()->SetTitle("n");
  g1->SetTitle("n(#lambda)");
  g1->Draw("AP");

  // Fit della funzione
  cout << "\n\n --- Legge di Cauchy: [0]+[1]/x^2) --- \n"
       << endl;
  TF1 *f1 = new TF1("f1", "[0]+[1]/x/x", 0, 1e3);
  f1->SetLineColor(4);
  f1->SetParameter(0, 1);
  f1->SetParameter(1, 1e4);
  g1->Fit(f1, "RM+");
  gStyle->SetOptFit(1);


}