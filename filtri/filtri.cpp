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
    Int_t npoints = 26;
    Float_t nf = 0, nG = 0, nsG = 0;
    Float_t f[npoints];
    Float_t G[npoints];
    Float_t sG[npoints];
    fstream file;
    file.open("dati_filtri_RC_1.txt", ios::in);

    for (int j = 0; j < npoints; j++)
    {
        file >> nf >> nG >> nsG;
        f[j] = nf;
        G[j] = nG;
        sG[j] = nsG;
    }
    file.close();

    Float_t fl_t = 15568; // Hz
    Float_t sfl_t = 7; // Hz

    cout << "\n---------------------------------- Filtro RC passa alto----------------------------------\n"
         << endl;
    for (int j = 0; j < npoints; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t f = (" << f[j] << ") Hz, \t G = (" << G[j] << " +- " << sG[j] << ")" << endl;
        // ----------------------------------------------------------------- //
    }

    // Canvas
    TCanvas *c1 = new TCanvas("c1", "RC passa alto", 200, 10, 600, 400);
    TGraphErrors *g1 = new TGraphErrors(npoints, f, G, 0, sG);
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
    TF1 *funz1 = new TF1("funz1", "x/sqrt([0]+x^2)", 1e2, 1e6);
    funz1->SetLineColor(4);
    g1->Fit(funz1, "RM+");
    gStyle->SetOptFit(1);

    Float_t a = funz1->GetParameter(0);
    Float_t sa = funz1->GetParError(0);
    Float_t fl = sqrt(a);
    Float_t sfl = sa/2/sqrt(a);
    cout << "\nLa frequenza di taglio è pari a: f_L = (" << fl << " +- " << sfl << ") Hz" << endl;

    // Test di Gauss
    Float_t z = abs(fl-fl_t)/sqrt(sfl*sfl+sfl_t*sfl_t);
    cout << "z = " << z << endl;

    // ------------------------------------------- filtro RCL Passa Banda ------------------------------------ //
    Int_t npoints3 = 32;
    Float_t f3[npoints3], G3[npoints3];
    Float_t sG3[npoints3];
    Float_t nf3=0, nG3=0, nsG3=0;

    Float_t R = 154.37; // Ohm

    file.open("dati_filtri_RCL.txt", ios::in);

    for(int j=0; j<npoints3; j++)
    {
        file >> nf3 >> nG3 >> nsG3;
        f3[j] = nf3;
        G3[j] = nG3;
        sG3[j] = nsG3;
    }
    file.close();

    cout << "\n---------------------------------- Filtro RCL passa banda----------------------------------\n"
         << endl;
    for (int j = 0; j < npoints3; j++)
    {
        // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
        cout << "Measurement number " << j << ":\t f = (" << f3[j] << ") Hz, \t G = (" << G3[j] << " +- " << sG3[j] << ")" << endl;
        // ----------------------------------------------------------------- //
    }

    // Grafico
    TCanvas *c3 = new TCanvas("c3", "RCL passa banda", 600, 400);
    TGraphErrors *g3 = new TGraphErrors(npoints3, f3, G3, 0, sG3);
    g3->GetXaxis()->SetTitle("f (Hz)");
    c3->SetLogx(1);
    g3->GetYaxis()->SetTitle("G = |V_o| / |V_i|");
    g3->SetMarkerSize(0.6);
    g3->SetMarkerStyle(21);
    g3->SetTitle("G(f)");
    g3->Draw("AP");

    // Fit
    TF1 *funz3 = new TF1("funz1", "154.37/sqrt(pow((154.37+pow([0],2)),2) + pow(2*TMath::Pi()*[1]*(pow(x,2)-pow([2],2))/x,2))", 1e2, 1e6);
    funz3->SetParameter(1, 7.265e-3);
    funz3->SetParameter(2, 1874);
    funz3->SetParLimits(2, 0., 1e7);
    TFitResultPtr fitResults = g3->Fit(funz3, "RMS");
    Float_t s01 = fitResults->GetCovarianceMatrix()[0][1]; // Covarianza R_s - L
    Float_t s02 = fitResults->GetCovarianceMatrix()[0][2]; // Covarianza R_s - f_r
    Float_t s12 = fitResults->GetCovarianceMatrix()[1][2]; // Covarianza L - f_r

    Double_t R_s = funz3->GetParameter(0);
    Double_t sR_s = funz3->GetParError(0);
    Double_t L = funz3->GetParameter(1);
    Double_t sL = funz3->GetParError(1);
    Double_t f_r = funz3->GetParameter(2);
    Double_t sf_r = funz3->GetParError(2);
    Double_t C = 1 / pow(2*TMath::Pi()*f_r, 2)/L;
    Double_t sC = sqrt(pow(sL/L,2) + pow(2*sf_r/f_r,2) + 4*s12/f_r/L) / pow(2*TMath::Pi()*f_r,2)/L;

    cout << "R_s = (" << R_s << " +- " << sR_s << ") Ohm" << endl;
    cout << "f_r = (" << f_r << " +- " << sf_r << ") Hz" << endl;
    cout << "L = (" << L << " +- " << sL << ") H" << endl;
    cout << "C = (" << C << " +- " << sC << ") F" << endl;

    Float_t C_m = 9.93E-07; // F
    Float_t sC_m = 1e-10; // F
    Float_t L_m = 7.265e-3; // H
    Float_t sL_m = 1e-6; // H
    Float_t f_r_m = 1 / (2*TMath::Pi()*sqrt(L_m*C_m)); // Hz
    Float_t sf_r_m = sqrt(sL_m*sL_m/(4*C_m*pow(L_m,3)) + sC_m*sC_m/(4*pow(C_m,3)*L_m)) / 2/TMath::Pi(); // Hz

    // Test di Gauss
    cout << "\n---------------------------------- Test di Gauss ----------------------------------\n"
         << endl;
    cout << "C misurato = (" << C_m << " +- " << sC_m << ") F" << endl;
    Float_t z_C = abs(C-C_m)/sqrt(sC*sC+sC_m*sC_m);
    cout << "z = " << z_C << endl;

    cout << "L misurato = (" << L_m << " +- " << sL_m << ") H" << endl;
    Float_t z_L = abs(L-L_m)/sqrt(sL*sL+sL_m*sL_m);
    cout << "z = " << z_L << endl;

    cout << "f_r misurato = (" << f_r_m << " +- " << sf_r_m << ") Hz" << endl;
    Float_t z_f_r = abs(f_r-f_r_m)/sqrt(sf_r*sf_r+sf_r_m*sf_r_m);
    cout << "z = " << z_f_r << endl;
}