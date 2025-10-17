#include <iostream>       // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h> // ci serve per istanziare grafici
#include <TAxis.h>        // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>      // ci serve per disegnare i grafici
#include <TF1.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include <TH1.h>
#include <TMath.h>
#include <fstream>
#define N_DATI 60

using namespace std;

void polarimetro()
{
    Float_t ntheta = 0;
    Float_t theta[N_DATI];

    fstream file;
    file.open("dati_polarimetro_1.txt", ios::in);

    for (int j = 0; j < N_DATI; j++)
    {
        file >> ntheta;
        theta[j] = ntheta;
    }
    file.close();

    TCanvas *c1 = new TCanvas("c1", "Fruttosio", 800, 600);

    // ampiezza classe, numero di classi
    Float_t amp1 = 0.05;
    Float_t dispmax1 = TMath::MaxElement(N_DATI, theta) - TMath::MinElement(N_DATI, theta);
    Float_t classi1 = dispmax1 / amp1;
    Int_t nbin1;
    for (Int_t i = 0; i < N_DATI; i++)
    {
        if (i < classi1)
            nbin1 = i + 1;
    }

    Float_t largh1 = nbin1 * amp1;
    cout << "\nla dispersione dell'istogramma è " << dispmax1 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh1 << endl;
    cout << "\nil numero di classi con ampiezza " << amp1 << " è " << nbin1 << "\n"
         << endl;

    TH1F *h1 = new TH1F("h1", "Fruttosio", nbin1, 162.955 - largh1/2 - 2*amp1, 162.955 + largh1/2);
    for (int i = 0; i < N_DATI; i++)
        h1->Fill(theta[i], 1);
    
    h1->Draw();


    Float_t ntheta2 = 0;
    Float_t theta2[N_DATI];

    file.open("dati_polarimetro_2.txt", ios::in);

    for (int j = 0; j < N_DATI; j++)
    {
        file >> ntheta2;
        theta2[j] = ntheta2;
    }
    file.close();

    TCanvas *c2 = new TCanvas("c2", "Fruttosio", 800, 600);

    // ampiezza classe, numero di classi
    Float_t amp2 = 0.05;
    Float_t dispmax2 = TMath::MaxElement(N_DATI, theta2) - TMath::MinElement(N_DATI, theta2);
    Float_t classi2 = dispmax2 / amp2;
    Int_t nbin2;
    for (Int_t i = 0; i < N_DATI; i++)
    {
        if (i < classi2)
            nbin2 = i + 1;
    }

    Float_t largh2 = nbin2 * amp2;
    cout << "\nla dispersione dell'istogramma è " << dispmax2 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh2 << endl;
    cout << "\nil numero di classi con ampiezza " << amp2 << " è " << nbin2 << "\n"
         << endl;

    TH1F *h2 = new TH1F("h2", "Fruttosio", nbin2, 12.0, 12.50);
    for (int i = 0; i < N_DATI; i++)
        h2->Fill(theta2[i], 1);
    TF1 *fit2 = new TF1("fit2", "gaus", 12., 13.);
    h2->Fit("fit2", "LR");
    h2->Draw();
}