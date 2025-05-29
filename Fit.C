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

#define MAX_DATI_DIM 128

using namespace std;

class AnalisiDati {
    TGraphErrors* grafico;
    TF1* funzioneFit;
    float markerSize = 0.6;
    int markerStyle = 21;
    int nPoints;
    char* nomeFile;
    char* nomeAsseX, *nomeAsseY;
    char* nomeGrafico;
    char* funzione;
    float* datiX;
    float* datiY;
    float* errDatiX;
    float* errDatiY;

    public:
    AnalisiDati(int _nPoints, const char* _nomeFile, const char* _nomeAsseX, const char* _nomeAsseY,
                const char* _funzione, const char* _nomeGrafico, float minX, float maxX) {
        nPoints = _nPoints;
        nomeFile = new char[32];
        nomeAsseX = new char[32];
        nomeAsseY = new char[32];
        funzione = new char[32];
        nomeGrafico = new char[32];

        CopiaStringhe(nomeFile, _nomeFile);
        CopiaStringhe(nomeAsseX, _nomeAsseX);
        CopiaStringhe(nomeAsseY, _nomeAsseY);
        CopiaStringhe(funzione, _funzione);
        CopiaStringhe(nomeGrafico, _nomeGrafico);

        datiX = new float[nPoints];
        datiY = new float[nPoints];
        errDatiX = new float[nPoints];
        errDatiY = new float[nPoints];

        funzioneFit = new TF1("funzioneFit", funzione, minX, maxX);

        LeggiFile();
    }

    private:
    void LeggiFile() {
        fstream file;
        file.open(nomeFile, ios::in);

        float nX, nY, nsX, nsY;
        for(int j = 0; j < nPoints; j++) {
            file >> nX >> nsX >> nY >> nsY;
            datiX[j] = nX;
            errDatiX[j] = nsX;
            datiY[j] = nY;
            errDatiY[j] = nsY;
        }

        file.close();
    }

    void CopiaStringhe(char* str1, const char* str2) {
        int i=0;
        for (i=0; str2[i] != 0; i++) {
            str1[i] = str2[i];
        }
        str1[i] = 0;
    }

    public:
    void SetParLimits(int parameter, float min, float max) {
        funzioneFit->SetParLimits(parameter, min, max);
    }

    void SetParameter(int parameter, float value) {
        funzioneFit->SetParameter(parameter, value);
    }

    void DisegnaGrafico() {
        TCanvas *c1 = new TCanvas("c1", "Silicio", 600, 400);
        grafico = new TGraphErrors(nPoints, datiX, datiY, errDatiX, errDatiY);
        grafico->SetMarkerSize(markerSize);
        grafico->SetMarkerStyle(markerStyle);
        grafico->GetXaxis()->SetTitle(nomeAsseX);
        grafico->GetYaxis()->SetTitle(nomeAsseY);
        grafico->SetTitle(nomeGrafico);
        grafico->Draw("AP");
    }

    void CalcoloFit() {
        funzioneFit->SetLineColor(4);
        grafico->Fit(funzioneFit, "RM+");
        gStyle->SetOptFit(1);
    }

    float GetParameter(int parameter) {
        return funzioneFit->GetParameter(parameter);
    }

    float GetParError(int parameter) {
        return funzioneFit->GetParError(parameter);
    }

    void GetParameters(double* parameterArray) {
        return funzioneFit->GetParameters(parameterArray);
    }
};