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

void diodi()
{
    AnalisiDati *silicio = new AnalisiDati(20, "dati_silicio.txt", "silicio", "V_{d} (V)", "I_{d} (mA)",
                                           "[0]*(TMath::Exp(x/[1]/0.026)-1)", "Caratteristica I-V silicio",
                                           0.450, 0.63);
    /*AnalisiDati silicio(20, "dati_silicio.txt", "silicio", "V_{d} (V)", "I_{d} (mA)",
                                           "[0]*(TMath::Exp(x/[1]/0.026)-1)", "Caratteristica I-V silicio",
                                           0.450, 0.63);*/
    silicio->DisegnaGrafico();
    silicio->SetParameter(0, 1e-8); // da trovare parametro ottimale per far convergere il fit
    silicio->SetParLimits(0, 0, 1);
    silicio->SetParameter(1, 2);
    silicio->SetParLimits(1, 1.5, 2.5);
    silicio->CalcoloFit();

    AnalisiDati *ledIV = new AnalisiDati(20, "dati_ledIV.txt", "LED", "V_{d} (V)", "I_{d} (mA)",
                                         "[0]*(TMath::Exp(x/[1]/0.026)-1)", "Caratteristica I-V LED", 0.8, 2);
    ledIV->DisegnaGrafico();
    ledIV->SetParameter(0, 1e-15);
    ledIV->SetParLimits(0, -1, 1);
    ledIV->SetParameter(1, 2);
    ledIV->SetParLimits(1, 1, 2.5);
    ledIV->CalcoloFit();


    AnalisiDati *ledVI = new AnalisiDati(20, "dati_ledVI.txt", "LED2", "I_{d} (#muA)", "V_{d} (V)",
                                         "[1]*0.026*TMath::Log(x/[0]+1)+[2]*x", "Caratteristica V-I LED", 0, 5000);
    ledVI->DisegnaGrafico();
    // INUTILE, TANTO IL LOG NATURALE DEVE PASSARE DALL'ORIGINE, QUINDI NON FITTERA' MAI. L'unico modo è di aggiungere un parametro di traslazione verso l'alto (sistematico?)
    ledVI->SetParameter(0, 1e-12);
    ledVI->SetParLimits(0, -1, 1);
    ledVI->SetParameter(1, 2);
    ledVI->SetParLimits(1, 1, 2.5);
    ledVI->SetParameter(2, 0);
    // ledVI->SetParLimits(2, -1, 1);
    ledVI->CalcoloFit();
}