klijentBanke tdatum{
    int dan, mjesec, godina;
};
klijentBanke elem {
    char imeIPrezime[35];
    tdatum datum;
    float tekuci, devizni;
    int ai, bi, ci, di;
};
klijentBanke red {
    elem klijent[10000];
    int front, rear;
};
       
red pomocniRed, salter, brziRed, novi;
int no,placanje = 0;
typedef red& jedanRed;

int AddOne(int no) {
    return ((no + 1) % 10000); 
}   
elem FrontQ(red& pomocniRed) {
    if(AddOne(pomocniRed.rear) == pomocniRed.front) {
        system("pause");
        exit(0);
    }
    return pomocniRed.klijent[pomocniRed.front];
}     
void EnQueueQ(elem x, red& pomocniRed) {
    if(AddOne(AddOne(pomocniRed.rear)) == pomocniRed.front) return;
    pomocniRed.rear = AddOne(pomocniRed.rear);
    pomocniRed.klijent[pomocniRed.rear] = x;
}     
void DeQueueQ(red& pomocniRed) {
    if(AddOne(pomocniRed.rear) == pomocniRed.front) return;
    pomocniRed.front = AddOne(pomocniRed.front);
}    
void InitQ(red& pomocniRed) {
    pomocniRed.front = 0;
    pomocniRed.rear = 9999;
}     
bool IsEmptyQ(red& pomocniRed) {
    if(AddOne(pomocniRed.rear) == pomocniRed.front) return true;
    else return false;
}
