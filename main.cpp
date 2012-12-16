#include <iostream>
#include <cstdlib>
#include <ctime>
//#include "red_polje.h"
#include "red_pokazivac.h"
using namespace std;

void sortiranje(klijentBanke p[], int no) {
    for(int i=no-1; i>0; i--)
        for(int j=0; j<i; j++) 
            if(p[j].ci > p[i].ci) {
                klijentBanke tmpV = p[j];
                p[j] = p[i];
                p[i] = tmpV;
            }
} 

void ispisReda(jedanRed ai,int no) {
   
    cout<<"Ispis reda"<<endl;
    for(int i=0; i<no; i++) {
        klijentBanke jedanKlijentBanke = FrontQ(ai);
        switch(jedanKlijentBanke.ci) {
            case 1: cout<<"Prioritet: Umirovljenik ";break;
            case 2: cout<<"Prioritet: Invalid ";break;
            case 3: cout<<"Prioritet: Trudnica ";break;
            case 4: cout<<"Prioritet: VIP klijent ";break;
            case 5: cout<<"Prioritet: Ostali klijent ";break;
            case 6: cout<<"Prioritet: Nije klijent ";break;
        }
        cout<<"\nIme i prezime: "<<jedanKlijentBanke.imeIPrezime<<"\nDatum: "<<jedanKlijentBanke.datum.dan<<"."<<jedanKlijentBanke.datum.mjesec<<"."<<jedanKlijentBanke.datum.godina<<".\nStanje tekuceg: "<<jedanKlijentBanke.tekuci<<" kn"<<"\nStanje deviznog: "<<jedanKlijentBanke.devizni<<" GBP\n----------"<<endl;
        DeQueueQ(ai);
        EnQueueQ(jedanKlijentBanke,ai);
    }
}

void generiraj() {
    cout<<"Broj klijenata? ";
    do {
        cin>>no;
    } 
    while(no<0 || no>1000); 
    for(int i=0; i<no; i++) {
        klijentBanke jedanKlijentBanke;
        jedanKlijentBanke.ai = rand() % 401 + 100;
        jedanKlijentBanke.bi = rand() % 401 + 100;            
        if(i==0 || i==3 || i==4 || i==11 || i==13) jedanKlijentBanke.di = 1;
        else if(i==2 || i==7 || i==14 || i==17 || i==19) jedanKlijentBanke.di = 2;
        else if(i==1 || i==9 || i==12 || i==15 || i==16) jedanKlijentBanke.di = 3;
        else if(i==5 || i==6 || i==8 || i==10 || i==18) jedanKlijentBanke.di = 4;
        else jedanKlijentBanke.di = rand() % 4 + 1;          
        if(jedanKlijentBanke.di==1 || jedanKlijentBanke.di==2) jedanKlijentBanke.ci = rand() % 5 + 1;
        else if(jedanKlijentBanke.di == 4) jedanKlijentBanke.ci = rand() % 5 + 2;
        else jedanKlijentBanke.ci = rand() % 6 + 1;    
        if(jedanKlijentBanke.di == 3) placanje++;
        switch(jedanKlijentBanke.ci) {
            case 1: cout<<i+1<<" Umirovljenik\n";break;
            case 2: cout<<i+1<<" Invalid\n";break;
            case 3: cout<<i+1<<" Trudnica\n";break;
            case 4: cout<<i+1<<" VIP klijent\n";break;
            case 5: cout<<i+1<<" Ostali klijent\n";break;
            case 6: cout<<i+1<<" Nije klijent\n";break;
        }                                   
        EnQueueQ(jedanKlijentBanke,pomocniRed);
    }
} 
     
void upisPodatakaKlijenata() {
    klijentBanke jedanKlijentBanke;
    int vrijeme = 0;
    int p[7];
    for(int i=0; i<7; i++) p[i] = 0;
    for(int i=0; i<no; i++) {
        jedanKlijentBanke = FrontQ(pomocniRed);
        vrijeme += jedanKlijentBanke.ai;
        p[jedanKlijentBanke.ci]++;
        cout<<endl;
        switch(jedanKlijentBanke.ci) {
            case 1: cout<<"Klijent umirovljenik. Prioritet 1. \n"; break;
            case 2: cout<<"Klijent invalid.  Prioritet 2. \n"; break;
            case 3: cout<<"Klijent trudnica.  Prioritet 3. \n"; break;
            case 4: cout<<"Klijent VIP.  Prioritet 4. \n"; break;
            case 5: cout<<"Klijent ostali.  Prioritet 5. \n"; break;
            case 6: cout<<"Nije klijent.  Prioritet 6. \n"; break;
        }
        cout<<"Dolazak u banku "<<vrijeme<<" min nakon otvaranja.\n";
        
        cout<<"Ime i prezime: ";
        cin.ignore();
        cin.getline(jedanKlijentBanke.imeIPrezime, 35);
             
        jedanKlijentBanke.datum.godina = 1982 + rand() % 30; //vratiti natrag
        jedanKlijentBanke.datum.mjesec = rand() % 12 + 1;
        if(jedanKlijentBanke.datum.mjesec == 2) 
            if(jedanKlijentBanke.datum.godina%100!=0 && jedanKlijentBanke.datum.godina%4==0) jedanKlijentBanke.datum.dan = rand() % 29+1;
            else if(jedanKlijentBanke.datum.godina%400==0) jedanKlijentBanke.datum.dan=rand()%29+1;
                 else jedanKlijentBanke.datum.dan=rand()%28 + 1;
        else jedanKlijentBanke.datum.dan=rand()%31 + 1;
             
        cout<<"Datum rodjenja: "<<jedanKlijentBanke.datum.dan<<"."<<jedanKlijentBanke.datum.mjesec<<"."<<jedanKlijentBanke.datum.godina<<endl;
        cout<<"Stanje tekuceg: ";
        cin>>jedanKlijentBanke.tekuci;
        cout<<"Stanje deviznog(GBP): ";
        cin>>jedanKlijentBanke.devizni;
             
        DeQueueQ(pomocniRed);
        EnQueueQ(jedanKlijentBanke, pomocniRed);
        EnQueueQ(jedanKlijentBanke, salter);
    }
     
    cout<<endl<<endl;    
    for(int i=1;i<7;i++) 
        if(p[i]>0) 
            while(p[i]!=0) {
                jedanKlijentBanke=FrontQ(salter);
                if(jedanKlijentBanke.ci==i) {
                    cout<<"NA SALTERU: ";
                    switch(jedanKlijentBanke.ci) {
                        case 1: cout<<"Umirovljenik "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                        case 2: cout<<"Invalid "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                        case 3: cout<<"Trudnica "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                        case 4: cout<<"VIP klijent "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                        case 5: cout<<"Ostali klijent "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                        case 6: cout<<"Nije klijent "<<jedanKlijentBanke.imeIPrezime<<endl;break;
                    }
                                                 
                    cout<<"TRANSAKCIJA: ";
                    switch(jedanKlijentBanke.di) {
                        case 1: cout<<"Uplata\n";break;
                        case 2: cout<<"Isplata\n";break;
                        case 3: cout<<"Placanje racuna\n";break;
                        case 4: cout<<"Krediti\n";break;
                    }
                                                  
                    cout<<"Trajanje: "<<jedanKlijentBanke.bi<<" min\n";
                                                 
                    if(jedanKlijentBanke.devizni*9.270504 > 10000.00) cout<<"\nStanje deviznih racuna s vise od: 10 000kn: "<<jedanKlijentBanke.devizni<<" GBP "<<endl;
                    cout<<endl;
                                                  
                    p[i]--;
                    DeQueueQ(salter);
                }
                else {
                    DeQueueQ(salter);
                    EnQueueQ(jedanKlijentBanke,salter);
                }
            }
}

void redBrzihTransakcija() {
    klijentBanke tmpV[placanje];
    int tz=0;
     
    while(!IsEmptyQ(pomocniRed)) {
        klijentBanke jedanKlijentBanke = FrontQ(pomocniRed);
        DeQueueQ(pomocniRed);
        if(jedanKlijentBanke.di == 3) {
            tmpV[tz++] = jedanKlijentBanke;
            no--;
        }
        else EnQueueQ(jedanKlijentBanke, salter);     
    }
     
    sortiranje(tmpV, tz);
    for(int i=0; i<tz; i++) EnQueueQ(tmpV[i], brziRed);
     
    cout<<"\nStanje brzog reda:\n-----------------------------\n";
    if(IsEmptyQ(brziRed)) cout<<"Red je prazan.\n";
    else ispisReda(brziRed, placanje);
             
    InitQ(brziRed);
     
    while(!IsEmptyQ(salter)) {
        klijentBanke jedanKlijentBanke = FrontQ(salter);
        DeQueueQ(salter);
        EnQueueQ(jedanKlijentBanke, pomocniRed);
    }
     
    cout<<"\nStanje glavnog reda:\n-----------------------------\n";
    if(IsEmptyQ(pomocniRed)) cout<<"Red je prazan.\n";
    else ispisReda(pomocniRed, no);
}     

void brisanjeVipUmirovljenici() {
    int tz = no;
    cout<<"Obrisani:\n------------------------\n";
    for(int i=0; i<tz; i++) {
        klijentBanke jedanKlijentBanke = FrontQ(pomocniRed);
        if((jedanKlijentBanke.ci==4 && jedanKlijentBanke.datum.godina>1982 && jedanKlijentBanke.di==1 && jedanKlijentBanke.tekuci<100) || (jedanKlijentBanke.ci==1 && jedanKlijentBanke.di==2 && jedanKlijentBanke.tekuci>5000)) {                                    
            switch(jedanKlijentBanke.ci) {
                case 1: cout<<"UMIROVLJENIK "<<jedanKlijentBanke.imeIPrezime<<"\nTRANSAKCIJA: Isplata"<<endl;break;
                case 4: cout<<"VIP KLIJENT "<<jedanKlijentBanke.imeIPrezime<<"\nTRANSAKCIJA: Uplata"<<endl;break;
            }
            cout<<"TEKUCI RACUN (kn): "<<jedanKlijentBanke.tekuci<<endl<<endl;
             
            DeQueueQ(pomocniRed);
            no--;
        }
        else {
            DeQueueQ(pomocniRed);
            EnQueueQ(jedanKlijentBanke,pomocniRed);
        }                                                                 
    }
    cout<<"\nStanje reda:\n\n";
    ispisReda(pomocniRed, no);
}
          
void brisanje(int tz,int uz) {
    klijentBanke jedanKlijentBanke = FrontQ(pomocniRed);
    DeQueueQ(pomocniRed);
    tz--; 
    if(!IsEmptyQ(pomocniRed)) brisanje(tz,uz);
    if(tz <= uz) EnQueueQ(jedanKlijentBanke, novi);
    else EnQueueQ(jedanKlijentBanke, pomocniRed);
}

void rekurzija(jedanRed ai) {
    klijentBanke jedanKlijentBanke = FrontQ(ai);
    DeQueueQ(ai);
    if(!IsEmptyQ(ai)) rekurzija(ai);
    EnQueueQ(jedanKlijentBanke, ai);
}
     
void noviSalter() {
    InitQ(novi);
    float p = no * 0.3;
    int uz = int(p);
    brisanje(no+1, uz);
    rekurzija(pomocniRed);
    no = no - uz;
    cout<<"Stanje novog reda:\n\n";
    ispisReda(novi, uz);
    cout<<"\nStanje glavnog reda:\n\n";
    ispisReda(pomocniRed, no);
}

int main() {
    int izbornik;
    srand(time(0));
    rand();
    
    InitQ(pomocniRed);
    InitQ(salter);
    InitQ(brziRed);
    InitQ(novi);
    
    generiraj();
    upisPodatakaKlijenata();
    
    do {
        cout<<"0. Kraj.\n";
        cout<<"1. Otvoriti novi red brzih transakcija.\n";    
        cout<<"2. Brisanje VIP klijenata mladjih od 30 godina za uplatu s stanjem tekuceg manje od 100 kn i umirovljenika za isplatu s stanjem tekuceg vise od 5000 kn.\n";
        cout<<"3. Otvoriti novi saltera u koji ide 30% klijenata  \n"; 
                  
        cin>>izbornik;
        switch(izbornik) {
            case 1: redBrzihTransakcija();break;
            case 2: brisanjeVipUmirovljenici();break;
            case 3: noviSalter();
        }
    }
    while(izbornik != 0);
    
    system("pause");
    return 0;
}
