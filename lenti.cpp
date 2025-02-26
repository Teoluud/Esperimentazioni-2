#include <iostream>       // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h> // ci serve per istanziare grafici
#include <TAxis.h>        // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>      // ci serve per disegnare i grafici
#include <TF1.h>          // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>        // ci serve per manipolare l'output a video
#include <TH1.h>
#include <TMath.h>

using namespace std;

void lenti()
{
  TH1::AddDirectory(false);

  cout << "\nLENTE BICONVESSA - PARTE1" << endl;

  // INPUT DATI DA FILE
  Char_t filnamres[100];
  sprintf(filnamres, "dati_lente_biconvessa.txt"); // nome del file che contiene i dati
  FILE *input = fopen(filnamres, "r");             // apertura file in input

  Float_t nx1 = 0;    // definizione della variabile "dato"
  Float_t x1[70];     // definizione del vettore "dato_in_formato_vettore"
  Int_t npoints1 = 0; // numero di punti nel vettore

  Float_t p1 = 140;
  Float_t errp1 = 2;

  if (!input)
  {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // inizio lettura file di input
  while (!feof(input))
  {
    fscanf(input, "%f\n", &nx1); // scan del file di input, riga per riga
    x1[npoints1] = nx1;          // riempimento del vettore
    ++npoints1;                  // incremento della variabile numero punto
  }

  fclose(input); // chiusura del file di input
  cout << "\nil numero totale di dati è: " << npoints1 << endl;

  // Genero una finestra "TCanvas" su cui stampero' l'istogramma
  TCanvas *histo1 = new TCanvas("histo1", "histo1", 800, 600); // definizione delle caratteristiche del TCanvas
  histo1->Clear();

  // ampiezza classe, numero di classi
  Float_t amp1 = 3;
  Float_t dispmax1 = 398 - 370;
  Float_t classi1 = dispmax1 / amp1;
  Int_t nbin1;

  for (Int_t i = 0; i < npoints1; i++)
  {
    if (classi1 > i)
      nbin1 = i + 1;
  }

  Float_t largh1 = amp1 * nbin1;
  cout << "\nla dispersione dell'istogramma è " << dispmax1 << ", arrotondando per eccesso, in modo da avere un numero intero di classi " << largh1 << endl;
  cout << "\nil numero di classi con ampiezza " << amp1 << " è " << nbin1 << "\n"
       << endl;

  // GENERO ISTOGRAMMA

  // TH1F("nome histo","titolo histo", numero classi, valore minimo, valore massimo)
  TH1F *biconvessa1 = new TH1F("biconvessa1", "Lente Biconvessa", nbin1, 384.6 - largh1 / 2, 384.6 + largh1 / 2);
  TF1 *g1 = new TF1("g1", "gaus", 300, 500); // definisco la funzione di fit g1 come gaussiana:[0]=normalizzazione - [1]=media - [2]=sigma
  for (Int_t i = 0; i < npoints1; i++)
    biconvessa1->Fill(x1[i], 1);                   // riempie l'istogramma incrementando di 1 ciascun bin
  biconvessa1->GetXaxis()->SetTitle("x(mm)");      // titolo dell'asse X
  biconvessa1->GetYaxis()->SetTitle("N");          // titolo dell'asse Y
  biconvessa1->GetXaxis()->SetRangeUser(250, 600); // range lungo asse X
  biconvessa1->GetYaxis()->SetRangeUser(0, 40);    // range lungo asse Y
  biconvessa1->Fit("g1", "L");
  biconvessa1->Draw(); // disegna l'istogramma

  // provate a estrarre e stampare la media, la deviazione standard, l'errore sulla media e il chi quadro
  Double_t media1 = biconvessa1->GetMean();   // prende il valore medio dell'HISTO
  Double_t errmedia1 = biconvessa1->GetRMS(); // prende l'RMS dell'HISTO
  // Double_t chisquare=funz->GetChisquare();
  cout << "\nmedia = " << media1 << " errmedia = " << errmedia1 << "\n\n"
       << endl;
  Float_t mediafit = g1->GetParameter(1);
  Float_t sigmafit = g1->GetParameter(2);
  cout << "\nmediafit = " << mediafit << " sigmafit " << sigmafit << endl;
  Float_t q1 = mediafit;
  Float_t errq1 = sigmafit / sqrt(npoints1);
  // provate a mettere qui il calcolo del fuoco
  Float_t f1 = (p1 * q1) / (p1 + q1);
  Float_t errf1 = 1 / (p1 + q1) / (p1 + q1) * sqrt(pow(q1, 4) * errp1 * errp1 + pow(p1, 4) * errq1 * errq1);

  cout << "q = " << q1 << " +/- " << errq1 << endl;

  cout << "\nil fuoco è: " << f1 << " +/- " << errf1 << " mm" << endl;

  // INGRANDIMENTO
  Float_t G1 = q1 / p1;
  Float_t errG1 = sqrt(errq1 * errq1 / p1 / p1 + errp1 * errp1 * q1 * q1 / pow(p1, 4));

  cout << "\nl'ingrandimento è: " << G1 << " +/- " << errG1 << endl;

  //-----------------------------------------------------------------------------//

  cout << "\n\n--- LENTE BICONVESSA - PARTE2 ---" << endl;

  FILE *input2 = fopen("dati_lente_biconvessa_2.txt", "r");

  Float_t nx2 = 0;
  Float_t x2[70];
  Int_t npoints2 = 0;

  Float_t p2 = p1;
  Float_t errp2 = errp1;

  if (!input2)
  {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // inizio lettura file di input
  while (!feof(input2))
  {
    fscanf(input2, "%f\n", &nx2); // scan del file di input, riga per riga
    x2[npoints2] = nx2;           // riempimento del vettore
    ++npoints2;                   // incremento della variabile numero punto
  }

  fclose(input2); // chiusura del file di input
  cout << "\nil numero totale di dati è: " << npoints2 << endl;

  TCanvas *histo2 = new TCanvas("histo2", "histo2", 800, 600);
  histo2->Clear();

  Float_t amp2 = 3;
  Float_t dispmax2 = 404 - 381;
  Float_t classi2 = dispmax2 / amp2;
  Int_t nbin2;

  for (Int_t i = 0; i < npoints2; i++)
  {
    if (i < classi2)
      nbin2 = i + 1;
  }

  Float_t largh2 = nbin2 * amp2;
  cout << "\nla dispersione dell'istogramma è " << dispmax2 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh2 << endl;
  cout << "\nil numero di classi con ampiezza " << amp2 << " è " << nbin2 << "\n"
       << endl;

  TH1F *biconvessa2 = new TH1F("biconvessa2", "Lente Biconvessa Ruotata", nbin2, 392.59 - largh2 / 2, 392.59 + largh2 / 2);
  TF1 *g2 = new TF1("g2", "gaus", 300, 500);

  for (Int_t i = 0; i < npoints2; i++)
    biconvessa2->Fill(x2[i], 1);
  biconvessa2->GetXaxis()->SetTitle("x(mm)");
  biconvessa2->GetYaxis()->SetTitle("N");
  biconvessa2->GetXaxis()->SetRangeUser(300, 500);
  biconvessa2->GetYaxis()->SetRangeUser(0, 40);
  biconvessa2->Fit("g2", "L");
  biconvessa2->Draw();

  Double_t media2 = biconvessa2->GetMean();   // prende il valore medio dell'HISTO
  Double_t errmedia2 = biconvessa2->GetRMS(); // prende l'RMS dell'HISTO
  // Double_t chisquare=funz->GetChisquare();
  cout << "\nmedia = " << media2 << " errmedia = " << errmedia2 << "\n\n"
       << endl;
  mediafit = g2->GetParameter(1);
  sigmafit = g2->GetParameter(2);
  cout << "\nmediafit = " << mediafit << " sigmafit " << sigmafit << endl;
  Float_t q2 = mediafit;
  Float_t errq2 = sigmafit / sqrt(npoints2);
  // provate a mettere qui il calcolo del fuoco
  Float_t f2 = (p2 * q2) / (p2 + q2);
  Float_t errf2 = 1 / (p2 + q2) / (p2 + q2) * sqrt(pow(q2, 4) * errp2 * errp2 + pow(p2, 4) * errq2 * errq2);

  cout << "q = " << q2 << " +/- " << errq2 << endl;

  cout << "\nil fuoco è: " << f2 << " +/- " << errf2 << " mm" << endl;

  //-------------------------------Test di Gauss--------------------------------//
  cout << "\nTEST DI GAUSS" << endl;
  Float_t z = abs(f1 - f2) / sqrt(errf1 * errf1 + errf2 * errf2);
  cout << "z = " << z << endl;
  if (z <= 1.96)
    cout << "Valori compatibili" << endl;
  else
    cout << "Valori non compatibili" << endl;

  //--------------------------------LENTE PIANO CONVESSA-------------------------------------//

  cout << "\n\n--- LENTE PIANO CONVESSA ---" << endl;

  FILE *input3 = fopen("dati_lente_pianoconvessa.txt", "r");

  Float_t nx3 = 0;
  Float_t x3[70];
  Int_t npoints3 = 0;

  Float_t p3 = 130;
  Float_t errp3 = errp1;

  if (!input3)
  {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // inizio lettura file di input
  while (!feof(input3))
  {
    fscanf(input3, "%f\n", &nx3); // scan del file di input, riga per riga
    x3[npoints3] = nx3;           // riempimento del vettore
    npoints3++;                   // incremento della variabile numero punto
  }

  fclose(input3); // chiusura del file di input
  cout << "\nil numero totale di dati è: " << npoints3 << endl;

  TCanvas *histo3 = new TCanvas("histo3", "histo3", 800, 600);
  histo3->Clear();

  Float_t amp3 = 1.5;
  Float_t dispmax3 = TMath::MaxElement(npoints3, x3) - TMath::MinElement(npoints3, x3);
  Float_t classi3 = dispmax3 / amp3;
  Int_t nbin3;

  for (Int_t i = 0; i < npoints3; i++)
  {
    if (i < classi3)
      nbin3 = i + 1;
  }

  Float_t largh3 = nbin3 * amp3;
  cout << "\nla dispersione dell'istogramma è " << dispmax3 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh3 << endl;
  cout << "\nil numero di classi con ampiezza " << amp3 << " è " << nbin3 << "\n"
       << endl;
  
  histo3->cd();

  TH1F *pianoconvessa = new TH1F("pianoconvessa", "Lente Piano Convessa", nbin3, 204.07 - largh3 / 2 , 204.07 + largh3 / 2);
  TF1 *g3 = new TF1("g3", "gaus", 100, 300);

  for (Int_t i = 0; i < npoints3; i++)
    pianoconvessa->Fill(x3[i], 1);
  pianoconvessa->GetXaxis()->SetTitle("x(mm)");
  pianoconvessa->GetYaxis()->SetTitle("N");
  pianoconvessa->GetXaxis()->SetRangeUser(0, 400);
  pianoconvessa->GetYaxis()->SetRangeUser(0, 40);
  pianoconvessa->Fit("g3", "L");
  pianoconvessa->Draw();

  Double_t media3 = pianoconvessa->GetMean();   // prende il valore medio dell'HISTO
  Double_t errmedia3 = pianoconvessa->GetRMS(); // prende l'RMS dell'HISTO
  // Double_t chisquare=funz->GetChisquare();
  cout << "\nmedia = " << media3 << " errmedia = " << errmedia3 << "\n\n"
       << endl;
  mediafit = g3->GetParameter(1);
  sigmafit = g3->GetParameter(2);
  cout << "\nmediafit = " << mediafit << " sigmafit " << sigmafit << endl;
  Float_t q3 = mediafit;
  Float_t errq3 = sigmafit / sqrt(npoints3);
  // provate a mettere qui il calcolo del fuoco
  Float_t f3 = (p3 * q3) / (p3 + q3);
  Float_t errf3 = 1 / (p3 + q3) / (p3 + q3) * sqrt(pow(q3, 4) * errp3 * errp3 + pow(p3, 4) * errq3 * errq3);

  cout << "q = " << q3 << " +/- " << errq3 << endl;

  //-------------------------------LENTE DIVERGENTE------------------------------//
  cout << "\n\n--- LENTE DIVERGENTE ---" << endl;

  FILE *input4 = fopen("dati_lente_divergente.txt", "r");
  Float_t nx4 = 0;
  Float_t x4[70];
  Int_t npoints4 = 0;

  if (!input4)
  {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }

  while (!feof(input4))
  {
    fscanf(input4, "%f\n", &nx4);
    x4[npoints4] = nx4;
    npoints4++;
  }

  fclose(input4);
  cout << "\nIl numero totale di dati è: " << npoints4 << endl;

  // Creazione tela
  TCanvas *histo4 = new TCanvas("histo4", "histo4", 800, 600);
  histo4->Clear();

  Float_t amp4 = 2;
  Float_t dispmax4 = TMath::MaxElement(npoints4, x4) - TMath::MinElement(npoints4, x4);
  Float_t classi4 = dispmax4 / amp4;
  Int_t nbin4;

  for (Int_t i = 0; i < npoints4; i++)
  {
    if (i < classi4)
      nbin4 = i + 1;
  }

  Float_t largh4 = nbin4 * amp4;
  cout << "\nla dispersione dell'istogramma è " << dispmax4 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh4 << endl;
  cout << "\nil numero di classi con ampiezza " << amp4 << " è " << nbin4 << "\n"
       << endl;
  
  TH1F *divergente = new TH1F("divergente", "Lente Divergente", nbin4, 274 - largh4 / 2, 274 + largh4 / 2);
  TF1 *g4 = new TF1("g4", "gaus", 200, 600);

  for(Int_t i = 0; i < npoints4; i++)
    divergente->Fill(x4[i], 1);
  divergente->GetXaxis()->SetTitle("x(mm)");
  divergente->GetYaxis()->SetTitle("N");
  divergente->GetXaxis()->SetRangeUser(200, 600);
  divergente->GetYaxis()->SetRangeUser(0, 40);
  divergente->Fit("g4", "L");
  divergente->Draw();

  mediafit = g4->GetParameter(1);
  sigmafit = g4->GetParameter(2);

  cout << "\nmediafit = " << mediafit << " sigmafit " << sigmafit << endl;
  Float_t q4 = mediafit;
  Float_t errq4 = sigmafit / sqrt(npoints4);

  cout << "q = " << q4 << " +/- " << errq4 << endl;

  //--------------------------------SISTEMA DI LENTI-------------------------------------//
  cout << "\n\n--- SISTEMA DI LENTI ---" << endl;

  FILE *input5 = fopen("dati_sistema_lenti.txt", "r");

  Float_t nx5 = 0;
  Float_t x5[10];
  Int_t npoints5 = 0;

  if(!input5)
  {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }

  while(!feof(input5))
  {
    fscanf(input5, "%f\n", &nx5);
    x5[npoints5] = nx5;
    npoints5++;
  }

  fclose(input5);
  cout << "\nIl numero totale di dati è: " << npoints5 << endl;

  TCanvas *histo5 = new TCanvas("histo5", "histo5", 800, 600);
  histo5->Clear();

  Float_t amp5 = 2;
  Float_t dispmax5 = TMath::MaxElement(10, x5) - TMath::MinElement(10,x5);
  Float_t classi5 = dispmax5 / amp5;
  Int_t nbin5 = 0;

  for(Int_t i = 0; i < npoints5; i++)
  {
    if(i < classi5)
      nbin5 = i + 1;
  }

  Float_t largh5 = nbin5 * amp5;
  cout << "\nla dispersione dell'istogramma è " << dispmax5 << ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh5 << endl;
  cout << "\nil numero di classi con ampiezza " << amp5 << " è " << nbin5 << "\n"
       << endl;

  TH1F *sistema = new TH1F("sistema", "Sistema di Lenti", nbin5, 318 - largh5 / 2, 318 + largh5 / 2);
  TF1 *g5 = new TF1("g5", "gaus", 250, 450);

  for(Int_t i = 0; i < npoints5; i++)
    sistema->Fill(x5[i], 1);
  sistema->GetXaxis()->SetTitle("x(mm)");
  sistema->GetYaxis()->SetTitle("N");
  sistema->GetXaxis()->SetRangeUser(250, 450);
  sistema->GetYaxis()->SetRangeUser(0, 6);
  sistema->Fit("g5", "L");
  sistema->Draw();

  mediafit = g5->GetParameter(1);
  sigmafit = g5->GetParameter(2);

  cout << "\nmediafit = " << mediafit << " sigmafit " << sigmafit << endl;
  Float_t q5 = mediafit;
  Float_t errq5 = sigmafit / sqrt(npoints5);

  cout << "q = " << q5 << " +/- " << errq5 << endl;
}
