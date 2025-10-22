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

void malus()
{
    AnalisiDati *malus = new AnalisiDati(37, "malus", "[a]*pow(TMath::Cos(x+[b]),2) + [c]", -0.5, 7.);
    malus->LeggiFile("/home/matteo/uni/esp-2/malus/dati_malus.txt", 0.03);
    malus->DisegnaGrafico("Legge di Malus", "#theta (rad)", "I (#muA)");
    
    malus->SetParameter(0, 10.);
    malus->SetParameter(1, 1.5);
    malus->CalcoloFit();

}