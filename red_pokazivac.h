struct tdatum{
    int dan, mjesec, godina;
};
struct klijentBanke {
    char pre_ime[35];
    tdatum datum;
    float tekuci, devizni;
    int ai, bi, ci, di;
};     
struct redU {
    klijentBanke klijent;
    redU *sljedeci;
};     
struct red {
    redU *front, *rear;
};
       
red pomocniRed, salter, brzi, novi;
int n, placanje = 0;
typedef red& jedanRed;

klijentBanke FrontQ(red& pomocniRed) {
    if(pomocniRed.front == pomocniRed.rear) exit(0);
    return (pomocniRed.front->sljedeci)->klijent;
}     
void EnQueueQ(klijentBanke x,red& pomocniRed) {
    redU *zadnji = pomocniRed.front,*novi;
    while(zadnji->sljedeci) zadnji = zadnji->sljedeci;
    novi = new redU;
    novi->sljedeci = NULL;
    novi->klijent = x;
    zadnji->sljedeci = novi;
    pomocniRed.rear = novi;
}    
void DeQueueQ(red& pomocniRed) {
    if(pomocniRed.front == pomocniRed.rear) return;
    redU *brisi = pomocniRed.front;
    pomocniRed.front = brisi->sljedeci;
    delete brisi;
}
bool IsEmptyQ(red& pomocniRed) {
    if(pomocniRed.front == pomocniRed.rear) return true;
    else return false;
}    
void InitQ(red& pomocniRed) {
    redU* novi = new redU;
    novi->sljedeci = NULL;
    pomocniRed.rear = novi;
    pomocniRed.front = novi;
}
