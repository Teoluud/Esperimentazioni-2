#include <iostream>       // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TF1.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include "/home/matteo/uni/esp-2/Fit.C"

void filtri()
{
    AnalisiDati *passa_banda = new AnalisiDati(32, "RCL passa banda", 
    "154.37/sqrt(pow((154.37+[0]),2) + pow(2*TMath::Pi()*[1]*x-1/(2*TMath::Pi()*[2]*x),2))", 1e1, 1e6);
    bool showXAxis = false;
    bool logaritmicScale = true;
    passa_banda->LeggiFile("/home/matteo/uni/esp-2/filtri/dati_filtri_RCL.txt", 0.);
    passa_banda->DisegnaGrafico("G(#nu)", "#nu [Hz]", "G = #frac{|V_{o}|}{|V_{i}|}", showXAxis, logaritmicScale);
    passa_banda->SetParameterName(0, "R_s");
    passa_banda->SetParameterName(1, "L");
    passa_banda->SetParameterName(2, "C");
    passa_banda->SetParameter(1, 7.265e-3);
    passa_banda->SetParameter(2, 1e-6);
    passa_banda->SetParLimits(2, 0., 1);

    passa_banda->CalcoloFit();
}