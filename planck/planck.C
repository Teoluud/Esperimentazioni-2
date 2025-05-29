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
#include "../Fit.C"

using namespace std;

void planck()
{
    //------------------------------------------ 655 nm -------------------------------------------------//
    AnalisiDati* lambda655 = new AnalisiDati(33, "dati_655.txt", "V [mv]", "I [mA]", "[0]+[1]*x", "I(V) - #lambda = 655 nm", 1300, 2050);
    lambda655->DisegnaGrafico();
    lambda655->CalcoloFit();
    double parametri[2];
    lambda655->GetParameters(parametri);
    for (int i = 0; i < 2; i++)
        cout << parametri[i] << endl;
}