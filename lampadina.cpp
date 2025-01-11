/*  PROGRAMMA LAMPADINA
Programma di base per l'analisi dati della caratteristica della lampadina.
Il programma va modificato per poter completare l'analisi.
In particolare, il seguente programma fa:
Grafico della curva I(V)
    --> si richiede di implementare la regressione con la curva teorica (vedi schede)
Grafico e una regressione della curva P(R)
    --> si richiede di implementare anche una regressione con una polinomiale di ordine 4

Le incertezze sulle misure sono indicative e vanno calcolate opportunamente in base al modello di tester adottato
La propagazione degli errori sulle quantità derivate va effettuata

Indicativamente, nel testo è presente dove [modificare] il programma.

per eseguire il programma adottare uno dei due seguenti metodi alternativi:
1- da riga dei comandi (shell) digitare    root -l lampadina.C++
2- da riga dei comandi (shell) digitare    root -l    e una volta dentro a root digitare   .x lampadina.C++
*/


#include <iostream>           // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video

using namespace std;


// Corpo del programma. La funzione qui sotto deve avere lo stesso nome del file .C
void lampadina()
{

  // --------------------------- DATI ------------------------------- //
  // Resistenza della lampadina, misurata in laboratorio con il multimetro
  const float R20 = 12.6; const float sR20 = 0.005*12.6 + 0.8; // ESEMPIO calcolo incertezza! Dipende dal modello!! Modificato

  // numero misure prese
  const int nmisure = 24;


  // Dati presi in laboratorio: V = tensione, sV = incertezza tensione, i = intensità di corrente, si = incertezza intensità di corrente
  // consiglio di non mettere il valore per V = 0 V altrimenti si avranno problemi nella parte in cui si calcolano i logaritmi
  Float_t ni = 0;
  Float_t nV = 0;
  Float_t i[nmisure]; //mA
  Float_t V[nmisure]; //V

  fstream file;
  file.open("dati_lampadina.txt", ios::in);

  for(int j = 0; j < nmisure; j++)
  {
    file >> nV >> ni;
    V[j] = nV;
    i[j] = ni;
  }
  file.close();


  // ---------------------------------------------------------------- //


  // ---------------------- Quantità derivate ----------------------- //

  // Array che conterà incertezze su i e V
  float sV[nmisure];
  float si[nmisure];

  // Array che conterrà i valori calcolati delle resistenze e loro incertezze
  float R[nmisure];
  float sR[nmisure];

  // Array che conterrà i valori calcolati delle potenze e loro incertezze
  float P[nmisure];
  float sP[nmisure];

  // ciclo for (loop) sulle misure
  for(int j=0; j<nmisure;++j){

    // Calcolo incertezza! Dipende dal modello!! [Modificato]
    if      (V[j] < 1)  sV[j] = V[j]*0.001 + 5e-4;
    else if (V[j] < 10) sV[j] = V[j]*0.001 + 5e-3;
    else                sV[j] = V[j]*0.001 + 5e-2;

    // Calcolo incertezza! Dipende dal modello!! [Modificato]
    if (i[j] < 400) si[j] = i[j]*0.005 + 5e-1;
    else            si[j] = i[j]*0.015 + 10;

    R[j]  = V[j]/i[j]*1000;  // in ohm
    sR[j] = 1000/i[j] * sqrt(sV[j]*sV[j] + pow(V[j]/i[j]*si[j], 2)); // Effettuare la propagazione degli errori!! [Modificato]
    P[j]  = V[j] * i[j];
    sP[j] = sqrt(pow(i[j]*sV[j], 2) + pow(V[j]*si[j], 2)); // Effettuare la propagazione degli errori!! [Modificato]

    // Stampa a video dei valori. \t inserisce un tab nel print out. Mettendo \n si va a capo invece
    cout << "Measurement number " << j << ":\t V = (" << V[j] << " +- " << sV[j] << ") V, \t i = (" << i[j] << " +- " << si[j] << ") mA,  \t R = ("
	 << setprecision(4) << R[j] << " +- " << sR[j] << ") ohm, \t P = ("	 << P[j] << " +- " << sP[j] << ") mW." << endl;
  }
  // ----------------------------------------------------------------- //




  // --------------------- Grafico i(V) ------------------------------ //
  // Creo il canvas (la tela) su cui disegnare il grafico. "ciV" è il il suo nome in memoria
  // è bene che sia unico dentro al programma. "i(v)" è semplicemente il titolo del canvas
  // le due coppie di numeri che seguono sono le coordinate dell'angolo superiore sinistro e le seconde
  // la dimensione in pixel lungo x e lungo y
  TCanvas *ciV = new TCanvas("ciV","i(v)",200,10,600,400);
  // Mi assicuro che la tela sia bianca (0 corrisponde al bianco, per altri colori vedi https://root.cern.ch/doc/master/classTColor.html)
  ciV->SetFillColor(0);
  // Mi assicuro che disegni su questa tela e non su un altra. Ciò è particolarmente importante quando ho tanti canvas aperti.
  ciV->cd();
  // Istanzio il grafico. Il costruttore che noi usiamo prende come argomenti:
  // il numero di misure da disegnare, l'array di misure x (=V), l'array di misure y (=i), e gli
  // array delle  rispettive incertezze
  TGraphErrors *giV = new TGraphErrors(nmisure,V,i,sV,si);
  // Nelle due righe successive disegno i punti del grafico con lo stile che più mi piace.
  // Vedi anche https://root.cern.ch/doc/master/classTAttMarker.html
  giV->SetMarkerSize(0.6);
  giV->SetMarkerStyle(21);

  // Titolo del grafico
  giV->SetTitle("i(V)");
  // Titoli degli assi
  giV->GetXaxis()->SetTitle("V [V]");
  giV->GetYaxis()->SetTitle("i [mA]");

  //Per impostare scala logaritmica:
  //su asse x:
 //ciV->SetLogx(1);
 //su asse y:
//ciV->SetLogy(1);

  // Dò istruzioni al grafico di disegnarsi sul canvas che ho selezionato preventivamente con cd() (vedi linea 103: ciV->cd();)
  // Esistono diverse opzioni di disegno, vedi anche https://root.cern.ch/doc/master/classTGraphPainter.html
  // "AP" è molto semplice, gli stiamo chiedendo di disegnare gli assi (A) e i punti (P)
  giV->Draw("AP");
  // ----------------------------------------------------------------- //



  // --------------------- Grafico P(R) ------------------------------ //
  TCanvas *cPR = new TCanvas("cPR","P(R)",200,10,600,400);
  cPR->SetFillColor(0);
  cPR->cd();
  TGraphErrors *gPR = new TGraphErrors(nmisure,R,P,sR,sP);
  gPR->SetMarkerSize(0.6);
  gPR->SetMarkerStyle(21);
  gPR->SetTitle("P(R)");
  gPR->GetXaxis()->SetTitle("R [#Omega]");
  gPR->GetYaxis()->SetTitle("P [mW]");
  gPR->Draw("AP");

  // ----------------------------------------------------------------- //


  cout << "\n\n --- Ipotesi  [0]*pow(x + [1],[2]) --- \n" <<endl;
  TF1 *funz1 = new TF1("funz1","[0]*pow(x + [1],[2])",0,30);
  // Le tre seguenti linee servono per inizializzare i parametri della funzione.
  funz1->SetParameter(0,pow(10,-7));
  funz1->SetParameter(1,0);
  funz1->SetParameter(2,4);
  // Talvolta è necessario imporre che un determinato parametro sia in un intervallo di validità definito. Usare
  // questa funzione solo se con SetParameter il fit non converge o se il fit converge per un valore del parametro che esce dall'intervallo
  // con significato fisico (e.g., una temperatura assoluta < 0 K).
  funz1->SetParLimits(0,0,1);
  funz1->SetParLimits(1,-1e3,0); // se lo commento viene 3.9+-0.4 e q = 4.69+-0.16, chi-quadro=2.85
  // cambio colore alla linea della funzione in modo da distinguerla dalla polinomiale di ordine 4 quando la andrò a disegnare
  funz1->SetLineColor(4); // Blu
  // Istruzione per fare il fit ai dati usando la funzione funz1 sopra definita
  // + significa che voglio aggiungere la funzione funz1 alla lista delle funzioni già disegnate sul canvas
  // R significa che voglio fare il fit solo in un determinato range, definito quando ho creato funz1. Quindi in questo caso (0-30) Ohm
  // In questo caso, mettere o non mettere l'opzione R è equivalente, visto che 0-130 copre tutto il range delle misure.
  // M dice di usare Hesse che fa una stima più accurata delle incertezze sui parametri. Nel caso di problemi rimuovere l'opzione.
  gPR->Fit(funz1,"RM+");
  gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph

  cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;


  cout << "\n\n --- Ipotesi  [0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x --- \n" <<endl;
  // Provare a fare fit a P(R) con polinomiale di ordine 4. [Modificare]
  TF1 *funz2 = new TF1("funz2","[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x",0,30);

  gPR->Fit(funz2, "RM+");

  cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;


  cout << "\n\n --- Ipotesi  [0]*pow(x+[1],4) --- \n" <<endl;
  // Provare a fare fit a P(R) con funzione quartica: funz2 = [0]*pow(x,4) [Modificare]
  TF1 *funz3 = new TF1("funz3", "[0]*pow(x+[1],4)",0,30);
  funz3->SetLineColor(3);

  gPR->Fit(funz3,"RM+");

  cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;



  cout << "\n\n --- Relazione tra i e V---" <<endl;
  // Mettere qui l'analisi della curva i(V).
  TF1 *funz4 = new TF1("funz4", "[0] * pow(x+[1], ([2]-1)/([2]+1))", 0,20);
  funz4->SetParameter(1,0);
  funz4->SetParameter(2,4);

  giV->Fit(funz4,"RM+");
  gStyle->SetOptFit(1);

  cout << "Chi^2:" << funz4->GetChisquare() << ", number of DoF: " << funz4->GetNDF() << " (Probability: " << funz4->GetProb() << ")." << endl;
  cout << "--------------------------------------------------------------------------------------------------------" << endl;
}
