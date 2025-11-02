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
#include <TFile.h>
#include <TSystem.h>

void AddZero(float zero, float errZero) {
    std::fstream file;
    file.open("dati_zeri.txt", std::ios::out);
    file << zero << errZero << std::endl;
}

float CalcoloZero(AnalisiDati* classe, int nPoints) {
    float q = classe->GetParameter(0);
    float m = classe->GetParameter(1);
    float* x = classe->GetData("x");
    float* y = classe->GetData("y");
    float* sy = classe->GetData("err y");
    for (int i = nPoints-1; i > 0; i--) {
        float z = abs(q+m*x[i]-y[i])/sy[i];
        // std::cout << x[i] << " " << z << std::endl;
        if (z > 1)
            return x[i+1];
    }
}

void planck()
{
    /* TString command = "rm dati_zeri.txt";
    gSystem->Exec(command.Data());
    TString filename = "dati_zeri.txt";
    FILE* file = fopen(filename.Data(), "w");
    fclose(file); */

    //------------------------------------------ 655 nm -------------------------------------------------//
    AnalisiDati* lambda655 = new AnalisiDati(33, "655",  "[0]+[1]*x", 1300, 2050);
    lambda655->LeggiFile("dati_655.txt");
    lambda655->DisegnaGrafico("I(V) - #lambda = 655 nm", "V [mv]", "I [pA]", true);
    // lambda655->CalcoloFit();
    // float zero655 = CalcoloZero(lambda655, 33);
    // cout << "\nIl potenziale di arresto corrispondente a 655nm è: " << zero655 << endl;
    
    //------------------------------------------ 635 nm -------------------------------------------------//
    AnalisiDati* lambda635 = new AnalisiDati(28, "635",  "[0]+[1]*x", 1200, 1550);
    lambda635->LeggiFile("dati_635.txt");
    lambda635->DisegnaGrafico("I(V) - #lambda = 635 nm", "V[mV]", "I [pA]", true);
    // lambda635->CalcoloFit();
    // float zero635 = CalcoloZero(lambda635, 28);
    // cout << "\nIl potenziale di arresto corrispondente a 635nm è: " << zero635 << endl;

    //------------------------------------------ 590 nm -------------------------------------------------//
    AnalisiDati* lambda590 = new AnalisiDati(28, "590", "[0]+[1]*x", 1370, 1550);
    lambda590->LeggiFile("dati_590.txt");
    lambda590->DisegnaGrafico("I(V) - #lambda=590 nm", "V[mV]", "I [pA]", true);
    // lambda590->CalcoloFit();
    // float zero590 = CalcoloZero(lambda590, 28);
    // cout << "\nIl potenziale di arresto corrispondente a 590nm è: " << zero590 << endl;

    //------------------------------------------ 467 nm -------------------------------------------------//
    AnalisiDati* lambda467 = new AnalisiDati(33, "467", "[0]+[1]*x", 1300, 2150);
    lambda467->LeggiFile("dati_467.txt");
    lambda467->DisegnaGrafico("I(V) - #lambda=467 nm", "V[mV]", "I [pA]", true);
    // lambda467->CalcoloFit();
    // float zero467 = CalcoloZero(lambda467, 33);
    // cout << "\nIl potenziale di arresto corrispondente a 467nm è: " << zero467 << endl;

    //------------------------------------------ 459 nm -------------------------------------------------//
    AnalisiDati* lambda459 = new AnalisiDati(36, "459", "[0]+[1]*x", 1700, 2150);
    lambda459->LeggiFile("dati_459.txt");
    lambda459->DisegnaGrafico("I(V) - #lambda=459 nm", "V[mV]", "I [pA]", true);
    // lambda459->CalcoloFit();
    // float zero459 = CalcoloZero(lambda459, 36);
    // cout << "\nIl potenziale di arresto corrispondente a 459nm è: " << zero459 << endl;

    //------------------------------------- Misura Costante di Planck -----------------------------------//
    AnalisiDati* costante = new AnalisiDati(3, "costante", "[0]+[1]*x", 450, 700);
    costante->LeggiFile("dati_zeri.txt");
    costante->DisegnaGrafico("V(#nu)", "V [mV]", "#nu [x10^{12} Hz]");
    costante->SetParameter(1, 6.626e-34/9.1e-34);
    costante->CalcoloFit();
    double pendenza = costante->GetParameter(1);
    double errPendenza = costante->GetParError(1);
    double h = pendenza * 9.1e-19*1e-15;
    double errh = errPendenza * 9.1e-19*1e-15;
    std::cout << "\nLa costante di Planck risulta essere h = (" << h << " +/- " << errh << ") Js" << std::endl;

    double hTeorica = 6.626e-34;
    double z = abs(h-hTeorica)/errh;
    std::cout << "\nLo z calcolato è: " << z << std::endl;
}