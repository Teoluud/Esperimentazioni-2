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
#include <TLine.h>

// #define MAX_DATI_DIM 128

// using namespace std;

class AnalisiDati
{
    TGraphErrors *grafico;
    TF1 *funzioneFit;
    float markerSize = 0.6;
    int markerStyle = 21;
    int nPoints;
    char *nomeCanvas;
    char *funzione;
    float *datiX;
    float *datiY;
    float *errDatiX;
    float *errDatiY;
    float minX, maxX;

public:
    AnalisiDati(int _nPoints, const char *_nomeCanvas,
                const char *_funzione, float _minX, float _maxX)
    {
        nPoints = _nPoints;
        minX = _minX;
        maxX = _maxX;
        // nomeFile = new char[32];
        nomeCanvas = new char[32];
        funzione = new char[128];

        // CopiaStringhe(nomeFile, _nomeFile);
        CopiaStringhe(nomeCanvas, _nomeCanvas);
        CopiaStringhe(funzione, _funzione);
        
        datiX = new float[nPoints];
        datiY = new float[nPoints];
        errDatiX = new float[nPoints];
        errDatiY = new float[nPoints];
        
        funzioneFit = new TF1("funzioneFit", funzione, minX, maxX);
        // LeggiFile();
    }

    void LeggiFile(const char *nomeFile, float nsX = -99, float nsY = -99)
    {
        std::fstream file;
        file.open(nomeFile, std::ios::in);

        float nX, nY, errX = nsX, errY = nsY;
            for (int j = 0; j < nPoints; j++)
            {
                if (nsX == -99 && nsY == -99)
                    file >> nX >> errX >> nY >> errY;
                else if (nsX == -99 && nsY != -99)
                    file >> nX >> errX >> nY;
                else if (nsX != -99 && nsY == -99)
                    file >> nX >> nY >> errY;
                else
                    file >> nX >> nY;
                datiX[j] = nX;
                errDatiX[j] = errX;
                datiY[j] = nY;
                errDatiY[j] = errY;
                //std::cout << nX << " " << errX << " " << nY << " " << errY << std::endl;
            }

        file.close();
        return;
    }

private:
    void CopiaStringhe(char *str1, const char *str2)
    {
        int i = 0;
        for (i = 0; str2[i] != 0; i++)
        {
            str1[i] = str2[i];
        }
        str1[i] = 0; // termine stringa
    }

public:
    void SetParLimits(int parameter, float min, float max)
    {
        funzioneFit->SetParLimits(parameter, min, max);
        return;
    }

    void SetParameter(Int_t parameter, Double_t value)
    {
        funzioneFit->SetParameter(parameter, value);
        return;
    }

    void SetParameterName(Int_t parameterId, const char *parameterName)
    {
        funzioneFit->SetParName(parameterId, parameterName);
        return;
    }

    void DisegnaGrafico(const char *nomeGrafico, const char *nomeAsseX, const char *nomeAsseY, bool xAxis = false, bool logScale = false)
    {
        TCanvas *canvas = new TCanvas(nomeCanvas, nomeCanvas, 600, 400);
        canvas->cd();
        grafico = new TGraphErrors(nPoints, datiX, datiY, errDatiX, errDatiY);
        grafico->SetMarkerSize(markerSize);
        grafico->SetMarkerStyle(markerStyle);
        grafico->GetXaxis()->SetTitle(nomeAsseX);
        grafico->GetYaxis()->SetTitle(nomeAsseY);
        grafico->SetTitle(nomeGrafico);
        grafico->Draw("AP");
        if (xAxis)
        {
            TLine *line = new TLine(0, 0, grafico->GetXaxis()->GetXmax(), 0);
            line->Draw();
        }
        if (logScale)
            canvas->SetLogx(1);
        
        return;
    }

    void CalcoloFit()
    {
        funzioneFit->SetLineColor(4);
        grafico->Fit(funzioneFit, "RM+");
        gStyle->SetOptFit(1);
        return;
    }

    float GetParameter(int parameter)
    {
        return funzioneFit->GetParameter(parameter);
    }

    float GetParameter(const char *parameter)
    {
        return funzioneFit->GetParameter(parameter);
    }

    float GetParError(int parameter)
    {
        return funzioneFit->GetParError(parameter);
    }

    void GetParameters(double *parameterArray)
    {
        return funzioneFit->GetParameters(parameterArray);
    }

    void GetParErrors(double *parErrorsArray)
    {
        // work in progress
        return;
    }

    

    float *GetData(const char *data)
    {
        if (strcmp(data, "x") == 0)
            return datiX;
        else if (strcmp(data, "err x") == 0)
            return errDatiX;
        else if (strcmp(data, "y") == 0)
            return datiY;
        else if (strcmp(data, "err y") == 0)
            return errDatiY;
        else
            return nullptr;
    }
};
