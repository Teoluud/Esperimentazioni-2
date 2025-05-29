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
#include "../Fit.C"

using namespace std;

/* void diodi()
{
    Int_t npoints = 20;
    Float_t I[npoints];
    Float_t nI = 0;
    Float_t V[npoints];
    Float_t nV = 0;
    Float_t sI[npoints];
    Float_t nsI = 0;
    Float_t sV[npoints];
    Float_t nsV = 0;

    fstream file;
    file.open("dati_diodi.txt", ios::in);

    for(int j = 0; j < npoints; j++)
    {
        file >> nV >> nsV >> nI >> nsI;
        I[j] = nI*1e3;
        sI[j] = nsI*1e3;
        V[j] = nV*1e3;
        sV[j] = nsV*1e3;
    }
    file.close();

    TCanvas *c1 = new TCanvas("c1", "Silicio", 600, 400);
    TGraphErrors *g1 = new TGraphErrors(npoints, V, I, sV, sI);
    g1->SetMarkerSize(0.6);
    g1->SetMarkerStyle(21);
    g1->GetXaxis()->SetTitle("V_{d} (mV)");
    g1->GetYaxis()->SetTitle("I_{d} (mA)");
    g1->SetTitle("Caratteristica I-V silicio");
    g1->Draw("AP");

    cout << "\n\n --- Equazione di Shockley: --- \n" << endl;
    TF1 *f1 = new TF1("f1", "[0]*(TMath::Exp(x/[1]/26)-1)", 400, 700);
    f1->SetLineColor(4);
    f1->SetParLimits(0, 0, 1e8);
    f1->SetParameter(0, 1e-6);
    f1->SetParameter(1, 2);
    g1->Fit(f1, "RM+");
    gStyle->SetOptFit(1);
} */

void diodi() {
    AnalisiDati* silicio = new AnalisiDati(20, "dati_diodi.txt", "V_{d} (V)", "I_{d} (mA)",
                                            "[0]*(TMath::Exp(x/[1]/0.026)-1)", "Caratteristica I-V silicio",
                                            0.450, 0.63);
    
    silicio->DisegnaGrafico();
    silicio->SetParameter(0, 1e-5);
    silicio->SetParLimits(0, 0., 1e6);
    silicio->SetParameter(1, 2);
    silicio->CalcoloFit();
}