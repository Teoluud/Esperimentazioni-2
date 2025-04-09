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

void malus()
{
    Int_t npoints = 37;
    Float_t theta[npoints];
    Float_t ntheta = 0;
    Float_t I[npoints];
    Float_t nI = 0;
    Float_t stheta[npoints];
    Float_t nstheta = 0.03;
    Float_t sI[npoints];

    fstream file;
    file.open("dati_malus.txt", ios::in);

    for (int j = 0; j < npoints; j++)
    {
        file >> ntheta >> nI;
        theta[j] = ntheta;
        I[j] = nI;
    }
    file.close();

    for(int j = 0; j < npoints; j++)
    {
        stheta[j] = nstheta;

        sI[j] = 0.005*I[j] + 0.1;
    }

    for (int j = 0; j < npoints; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t theta = (" << theta[j] << " +- " << stheta[j] << ") rad, \t I = (" << I[j] << " +- " << sI[j] << ") microA" << endl;
        // ----------------------------------------------------------------- //
    }

    TCanvas *c1 = new TCanvas("c1", "Malus", 600, 400);
    TGraphErrors *g1 = new TGraphErrors(npoints, theta, I, stheta, sI);
    g1->SetTitle("Legge di Malus");
    g1->GetXaxis()->SetTitle("#theta (rad)");
    g1->GetYaxis()->SetTitle("I (#muA)");
    g1->SetMarkerSize(0.6);
    g1->SetMarkerStyle(21);
    gStyle->SetOptFit(1);
    g1->Draw("AP");

    TF1 *fit = new TF1("fit", "[a]*pow(TMath::Cos(x+[b]),2) + [c]", -0.5, 7.);
    fit->SetParameter("a", 10.);
    fit->SetParameter("b", 1.5);
    //fit->SetParameter("c", 0.);
    g1->Fit(fit, "RM+");

}