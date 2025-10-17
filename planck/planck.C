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

using namespace std;
void AddZero(float zero, float errZero) {
    fstream file;
    file.open("dati_zeri.txt", ios::out);
    file << zero << errZero << endl;
}

float CalcoloZero(AnalisiDati* classe, int nPoints) {
    float q = classe->GetParameter(0);
    float m = classe->GetParameter(1);
    float* x = classe->GetData("x");
    float* y = classe->GetData("y");
    float* sy = classe->GetData("err y");
    for (int i = nPoints-1; i > 0; i--) {
        float z = abs(q+m*x[i]-y[i])/sy[i];
        // cout << x[i] << " " << z << endl;
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
    AnalisiDati* lambda655 = new AnalisiDati(33, "dati_655.txt", "655", "V [mv]", "I [pA]", "[0]+[1]*x", "I(V) - #lambda = 655 nm", 1300, 2050);
    lambda655->DisegnaGrafico(1);
    // lambda655->CalcoloFit();
    // float zero655 = CalcoloZero(lambda655, 33);
    // cout << "\nIl potenziale di arresto corrispondente a 655nm è: " << zero655 << endl;
    
    //------------------------------------------ 635 nm -------------------------------------------------//
    AnalisiDati* lambda635 = new AnalisiDati(28, "dati_635.txt", "635", "V[mV]", "I [pA]", "[0]+[1]*x", "I(V) - #lambda = 635 nm", 1200, 1550);
    lambda635->DisegnaGrafico(1);
    // lambda635->CalcoloFit();
    // float zero635 = CalcoloZero(lambda635, 28);
    // cout << "\nIl potenziale di arresto corrispondente a 635nm è: " << zero635 << endl;

    //------------------------------------------ 590 nm -------------------------------------------------//
    AnalisiDati* lambda590 = new AnalisiDati(28, "dati_590.txt", "590", "V [mV]", "I [pA]", "[0]+[1]*x", "I(V) - #lambda=590 nm", 1370, 1550);
    lambda590->DisegnaGrafico(1);
    // lambda590->CalcoloFit();
    // float zero590 = CalcoloZero(lambda590, 28);
    // cout << "\nIl potenziale di arresto corrispondente a 590nm è: " << zero590 << endl;

    //------------------------------------------ 467 nm -------------------------------------------------//
    AnalisiDati* lambda467 = new AnalisiDati(33, "dati_467.txt", "467", "V [mV]", "I [pA]", "[0]+[1]*x", "I(V) - #lambda=467 nm", 1300, 2150);
    lambda467->DisegnaGrafico(1);
    // lambda467->CalcoloFit();
    // float zero467 = CalcoloZero(lambda467, 33);
    // cout << "\nIl potenziale di arresto corrispondente a 467nm è: " << zero467 << endl;

    //------------------------------------------ 459 nm -------------------------------------------------//
    AnalisiDati* lambda459 = new AnalisiDati(36, "dati_459.txt", "459", "V [mV]", "I [pA]", "[0]+[1]*x", "I(V) - #lambda=459 nm", 1700, 2150);
    lambda459->DisegnaGrafico(1);
    // lambda459->CalcoloFit();
    // float zero459 = CalcoloZero(lambda459, 36);
    // cout << "\nIl potenziale di arresto corrispondente a 459nm è: " << zero459 << endl;

    //------------------------------------- Misura Costante di Planck -----------------------------------//
    AnalisiDati* costante = new AnalisiDati(3, "dati_zeri.txt", "costante", "#nu [x10^{12} Hz]", "V [mV]", "[0]+[1]*x", "V(#nu)", 450, 700);
    costante->DisegnaGrafico();
    costante->SetParameter(1, 6.626e-34/9.1e-34);
    costante->CalcoloFit();
    double pendenza = costante->GetParameter(1);
    double errPendenza = costante->GetParError(1);
    double h = pendenza * 9.1e-19*1e-15;
    double errh = errPendenza * 9.1e-19*1e-15;
    cout << "\nLa costante di Planck risulta essere h = (" << h << " +/- " << errh << ") Js" << endl;

    double hTeorica = 6.626e-34;
    double z = abs(h-hTeorica)/errh;
    cout << "\nLo z calcolato è: " << z << endl;
}