void lenti()
{
TH1::AddDirectory(false);

cout << "\nLENTE BICONVESSA - PARTE1" << endl;

//INPUT DATI DA FILE
  Char_t filnamres[100];
  sprintf(filnamres,"dati_lente_biconvessa.txt"); // nome del file che contiene i dati
  FILE *input = fopen(filnamres, "r" ); // apertura file in input

  Float_t nx1=0; // definizione della variabile "dato"
  Float_t x1[70]; // definizione del vettore "dato_in_formato_vettore"
  Int_t npoints1=0; //numero di punti nel vettore

  Float_t p1 = 140;
  Float_t errp1 = 2;
 
  if(!input) {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
  }
  //inizio lettura file di input
    while(!feof(input)) {
      fscanf(input,"%f\n",&nx1); //scan del file di input, riga per riga
      x1[npoints1]=nx1; // riempimento del vettore
      ++npoints1; //incremento della variabile numero punto
    }

    fclose(input); // chiusura del file di input
cout<<"\nil numero totale di dati è: " <<npoints1<<endl;

//Genero una finestra "TCanvas" su cui stampero' l'istogramma
 TCanvas *histo1= new TCanvas("histo1","histo1",800,600); //definizione delle caratteristiche del TCanvas
histo1->Clear();

//ampiezza classe, numero di classi
Float_t amp1=3;
Float_t dispmax1=398-370;
Float_t classi1=dispmax1/amp1;
Int_t nbin1;

for(Int_t i=0;i<npoints1;i++)
 {
     if(classi1>i)
     nbin1=i+1;
 }

Float_t largh1=amp1*nbin1;
cout << "\nla dispersione dell'istogramma è " <<dispmax1<< ", arrotondando per eccesso, in modo da avere un numero intero di classi " << largh1 <<endl;
cout << "\nil numero di classi con ampiezza " <<amp1<< " è " <<nbin1 << "\n" << endl;

//GENERO ISTOGRAMMA

// TH1F("nome histo","titolo histo", numero classi, valore minimo, valore massimo)
 TH1F *biconvessa1= new TH1F("biconvessa1","lente biconvessa",nbin1, 384.6-largh1/2,384.6+largh1/2);
 TF1 *g1 = new TF1("g1", "gaus",300,500); // definisco la funzione di fit g1 come gaussiana:[0]=normalizzazione - [1]=media - [2]=sigma 
for(Int_t i=0;i<npoints1;i++)
  biconvessa1->Fill(x1[i],1); // riempie l'istogramma incrementando di 1 ciascun bin
 biconvessa1->GetXaxis()->SetTitle("x(mm)"); // titolo dell'asse X
 biconvessa1->GetYaxis()->SetTitle("N"); // titolo dell'asse Y
 biconvessa1->GetXaxis()->SetRangeUser(250,600);  //range lungo asse X
 biconvessa1->GetYaxis()->SetRangeUser(0,40); // range lungo asse Y
 biconvessa1->Fit("g1","L");
 biconvessa1->Draw(); // disegna l'istogramma
 

// provate a estrarre e stampare la media, la deviazione standard, l'errore sulla media e il chi quadro 
 Double_t media1= biconvessa1->GetMean(); // prende il valore medio dell'HISTO
 Double_t errmedia1 = biconvessa1->GetRMS(); //prende l'RMS dell'HISTO
 //Double_t chisquare=funz->GetChisquare();
cout << "\nmedia = " << media1 << " errmedia = " << errmedia1 << "\n\n" << endl; 
 Float_t mediafit= g1->GetParameter(1);
  Float_t sigmafit= g1->GetParameter(2);
  cout << "\nmediafit = " << mediafit <<" sigmafit "<< sigmafit<<  endl; 
  Float_t q1 = mediafit;
  Float_t errq1 = sigmafit;
//provate a mettere qui il calcolo del fuoco
Float_t f1 = (p1*q1)/(p1+q1);
Float_t errf1 = 1/(p1+q1)/(p1+q1)*sqrt(q1*q1*errp1*errp1+p1*p1*errq1*errq1);

cout << "q = " <<q1<< " +/- " << errq1<<endl;

cout << "\nil fuoco è: " << f1 <<" +/- " << errf1 << " mm" << endl;

//-----------------------------------------------------------------------------//

cout << "\n\n--- LENTE BICONVESSA - PARTE2 ---" << endl;

FILE *input2 = fopen("dati_lente_biconvessa_2.txt", "r");

Float_t nx2 = 0;
Float_t x2[70];
Int_t npoints2 = 0;

Float_t p2 = p1;
Float_t errp2 = errp1;

if(!input2) {
      cerr << "Error: file could not be opened" << endl;
      exit(1);
  }
  //inizio lettura file di input
    while(!feof(input2)) {
      fscanf(input2,"%f\n",&nx2); //scan del file di input, riga per riga
      x2[npoints2]=nx2; // riempimento del vettore
      ++npoints2; //incremento della variabile numero punto
    }

    fclose(input2); // chiusura del file di input
cout<<"\nil numero totale di dati è: " <<npoints2<<endl;

TCanvas *histo2 = new TCanvas("histo2", "histo2", 800, 600);
histo2->Clear();

Float_t amp2 = 3;
Float_t dispmax2 = 404 - 381;
Float_t classi2 = dispmax2/amp2;
Int_t nbin2;

for(Int_t i=0; i<npoints2; i++) {
  if(i<classi2) nbin2 = i+1;
}

Float_t largh2 = nbin2*amp2;
cout << "\nla dispersione dell'istogramma è " <<dispmax2<< ", arrotondando per eccesso, in modo da avere un numero intero di classi: " << largh2 <<endl;
cout << "\nil numero di classi con ampiezza " <<amp2<< " è " <<nbin2 << "\n" << endl;

TH1F *biconvessa2 = new TH1F("biconvessa2", "Lente Biconvessa Ruotata", nbin2, 392.59-largh2/2, 392.59+largh2/2);
TF1 *g2 = new TF1("g2", "gaus", 300, 500);

for(Int_t i=0; i<npoints2; i++) biconvessa2->Fill(x2[i], 1);
biconvessa2->GetXaxis()->SetTitle("x(mm)");
biconvessa2->GetYaxis()->SetTitle("N"); 
biconvessa2->GetXaxis()->SetRangeUser(250,600);
biconvessa2->GetYaxis()->SetRangeUser(0,40);
biconvessa2->Fit("g2","L");
biconvessa2->Draw();

Double_t media2= biconvessa2->GetMean(); // prende il valore medio dell'HISTO
Double_t errmedia2 = biconvessa2->GetRMS(); //prende l'RMS dell'HISTO
//Double_t chisquare=funz->GetChisquare();
cout << "\nmedia = " << media2 << " errmedia = " << errmedia2 << "\n\n" << endl; 
mediafit= g2->GetParameter(1);
sigmafit= g2->GetParameter(2);
cout << "\nmediafit = " << mediafit <<" sigmafit "<< sigmafit<<  endl; 
Float_t q2 = mediafit;
Float_t errq2 = sigmafit;
//provate a mettere qui il calcolo del fuoco
Float_t f2 = (p2*q2)/(p2+q2);
Float_t errf2 = 1/(p2+q2)/(p2+q2)*sqrt(q2*q2*errp2*errp2+p2*p2*errq2*errq2);

cout << "q = " <<q2<< " +/- " << errq2<<endl;

cout << "\nil fuoco è: " << f2 <<" +/- " << errf2 << " mm" << endl;

//-------------------------------Test di Gauss--------------------------------//
cout << "\nTEST DI GAUSS" << endl;
Float_t z = abs(f1-f2)/sqrt(errf1*errf1+errf2*errf2);
cout << "z = " << z << endl;
if(z<=1.96) cout << "Valori compatibili" << endl;
else cout << "Valori non compatibili" << endl;
}