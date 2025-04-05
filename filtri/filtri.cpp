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
#include <TFitResult.h>
#include <TFitResultPtr.h>

using namespace std;

void filtri()
{
    // ------------------------------------------- filtro RC Passa Alto ------------------------------------ //
    Int_t npoints = 2;
    Float_t nf = 0, nG = 0, nsf = 0, nsG = 0;
    Float_t f[npoints];
    Float_t sf[npoints];
    Float_t G[npoints];
    Float_t sG[npoints];
    fstream file;
    file.open("dati_filtri_RC_1.txt", ios::in);

    for (int j = 0; j < npoints; j++)
    {
        file >> nf >> nsf >> nG >> nsG;
        f[j] = nf;
        sf[j] = nsf;
        G[j] = nG;
        sG[j] = nsG;
    }
    file.close();

    cout << "\n---------------------------------- Filtro RC passa alto----------------------------------\n"
         << endl;
    for (int j = 0; j < npoints; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t f = (" << f[j] << " +- " << sf[j] << ") Hz, \t G = (" << G[j] << " +- " << sG[j] << ")" << endl;
        // ----------------------------------------------------------------- //
    }

    // Canvas
    TCanvas *c1 = new TCanvas("c1", "RC passa alto", 200, 10, 600, 400);
    TGraphErrors *g1 = new TGraphErrors(npoints, f, G, sf, sG);
    g1->SetMarkerSize(0.6);
    g1->SetMarkerStyle(21);
    g1->GetXaxis()->SetTitle("f (Hz)");
    c1->SetLogx(1);
    g1->GetYaxis()->SetTitle("G = |V_o| / |V_i|");
    g1->SetTitle("G(f)");
    g1->Draw("AP");

    // Fit della funzione
    cout << "\n\n --- Ipotesi:G = f/([0]+f^2) --- \n"
         << endl;
    TF1 *funz1 = new TF1("funz1", "x/sqrt([0]+x^2)", 0., 1e5);
    funz1->SetLineColor(4);
    g1->Fit(funz1, "RM+");
    gStyle->SetOptFit(1);

    Float_t fl1 = funz1->GetParameter(0);
    Float_t sfl1 = funz1->GetParError(0);
    cout << "\nLa frequenza di taglio è pari a: f_L = (" << setprecision(3) << fl1 << " +- " << sfl1 << ") Hz" << endl;

    // ------------------------------------------- filtro RC Passa Basso ------------------------------------ //

    Int_t npoints2 = 2;
    Float_t nf2 = 0, nG2 = 0, nsf2 = 0, nsG2 = 0;
    Float_t f2[npoints];
    Float_t sf2[npoints];
    Float_t G2[npoints];
    Float_t sG2[npoints];

    file.open("dati_filtri_RC_2.txt", ios::in);

    for (int j = 0; j < npoints; j++)
    {
        file >> nf2 >> nsf2 >> nG2 >> nsG2;
        f2[j] = nf2;
        sf2[j] = nsf2;
        G2[j] = nG2;
        sG2[j] = nsG2;
    }
    file.close();

    cout << "\n---------------------------------- Filtro RC passa basso----------------------------------\n"
         << endl;
    for (int j = 0; j < npoints2; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t f = (" << f2[j] << " +- " << sf2[j] << ") Hz, \t G = (" << G2[j] << " +- " << sG2[j] << ")" << endl;
        // ----------------------------------------------------------------- //
    }

    // Canvas
    TCanvas *c2 = new TCanvas("c2", "RC passa basso", 400, 10, 600, 400);
    TGraphErrors *g2 = new TGraphErrors(npoints2, f2, G2, sf2, sG2);
    g2->SetMarkerSize(0.6);
    g2->SetMarkerStyle(21);
    g2->GetXaxis()->SetTitle("f (Hz)");
    c2->SetLogx(1);
    g2->GetYaxis()->SetTitle("G = |V_o| / |V_i|");
    g2->SetTitle("G(f)");
    g2->Draw("AP");

    // Fit della funzione
    cout << "\n\n --- Ipotesi:G = f/([0]+f^2) --- \n"
         << endl;
    TF1 *funz2 = new TF1("funz2", "x/sqrt([0]+x^2)", 0., 1e5);
    funz2->SetLineColor(4);
    g2->Fit(funz2, "RM+");

    Float_t fl2 = funz2->GetParameter(0);
    Float_t sfl2 = funz2->GetParError(0);
    cout << "\nLa frequenza di taglio è pari a: f_L = (" << setprecision(3) << fl2 << " +- " << sfl2 << ") Hz" << endl;

    // ------------------------------------------- filtro RCL Passa Banda ------------------------------------ //
    Int_t npoints3 = 3;
    Float_t f3[npoints3], G3[npoints3];
    Float_t sf3[npoints3], sG3[npoints3];
    Float_t nf3=0, nsf3=0, nG3=0, nsG3=0;

    Float_t R = 100; // Ohm
    Float_t V_i; // V

    file.open("dati_filtri_RCL.txt", ios::in);

    for(int j=0; j<npoints3; j++)
    {
        file >> nf3 >> nsf3 >> nG3 >> nsG3;
        f3[j] = nf3;
        sf3[j] = nsf3;
        G3[j] = nG3;
        sG3[j] = nsG3;
    }
    file.close();

    cout << "\n---------------------------------- Filtro RCL passa banda----------------------------------\n"
         << endl;
    for (int j = 0; j < npoints3; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t f = (" << f3[j] << " +- " << sf3[j] << ") Hz, \t G = (" << G3[j] << " +- " << sG3[j] << ")" << endl;
        // ----------------------------------------------------------------- //
    }

    // Grafico
    TCanvas *c3 = new TCanvas("c3", "RCL passa banda", 600, 400);
    TGraphErrors *g3 = new TGraphErrors(npoints3, f3, G3, sf3, sG3);
    g3->GetXaxis()->SetTitle("f (Hz)");
    c3->SetLogx(1);
    g3->GetYaxis()->SetTitle("G = |V_o| / |V_i|");
    g3->SetMarkerSize(0.6);
    g3->SetMarkerStyle(21);
    g3->SetTitle("G(f)");
    g3->Draw("AP");

    // Fit
    TF1 *funz3 = new TF1("funz1", "100/sqrt(pow((100+pow([0],2)),2) + pow(2*TMath::Pi()*(pow(x,2)-pow([1],2))/(x*[2]),2))", 0., 1e5);
    TFitResultPtr fitResults = g3->Fit(funz3, "RMS");
    Float_t s01 = fitResults->GetCovarianceMatrix()[0][1]; // Covarianza R_s - f_r
    Float_t s02 = fitResults->GetCovarianceMatrix()[0][2]; // Covarianza R_s - L
    Float_t s12 = fitResults->GetCovarianceMatrix()[1][2]; // Covarianza f_r - L

    Double_t R_s = funz3->GetParameter(0);
    Double_t sR_s = funz3->GetParError(0);
    Double_t f_r = funz3->GetParameter(1);
    Double_t sf_r = funz3->GetParError(1);
    Double_t L = funz3->GetParameter(2);
    Double_t sL = funz3->GetParError(2);
    Double_t C = L / pow(2*TMath::Pi()*f_r, 2);
    Double_t sC = 1/pow(2*TMath::Pi()*f_r,2)*sqrt(sL*sL + pow(2*L/f_r*sf_r,2) - 4*L/f_r*s12);

    cout << "R_s = (" << R_s << " +- " << sR_s << ") Ohm" << endl;
    cout << "f_r = (" << f_r << " +- " << sf_r << ") Hz" << endl;
    cout << "L = (" << L << " +- " << sL << ") H" << endl;
    cout << "C = (" << C << " +- " << sC << ") F" << endl; 
}