#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Ornek {
    int puan;
    struct Ornek* next;
} Ornek;

typedef struct Kuyruk {
    Ornek* bas;
    Ornek* son;
    int N;
    int boyut;
} Kuyruk;

Kuyruk* yenikuyruk(int N) {
    Kuyruk* kuyruk = (Kuyruk*)malloc(sizeof(Kuyruk));
    kuyruk->bas = NULL;
    kuyruk->son = NULL;
    kuyruk->N = N;
    kuyruk->boyut = 0;
    return kuyruk;
}
int kuyrukdolu(Kuyruk* k) {
    return (k->boyut >= k->N);
}
int kuyrukbos(Kuyruk* k) {
    return (k->boyut == 0);
}
void kuyrugaekle(Kuyruk* k, int puan) {
    if (!kuyrukdolu(k)) {
        Ornek* yeni = (Ornek*)malloc(sizeof(Ornek));
        yeni->puan = puan;
        yeni->next = NULL;

        if (kuyrukbos(k)) {
            k->bas = yeni;
            k->son = yeni;
            k->son->next = k->bas;
        }
        else {
            k->son->next = yeni;
            k->son = yeni;
            k->son->next = k->bas;
        }
        k->boyut++;
    }
}
int kuyruksil(Kuyruk* k) {
    int silinenpuan = -1;
    if (!kuyrukbos(k)) {
        Ornek* silinen = k->bas;
        silinenpuan = silinen->puan;

        if (k->boyut == 1) {
            k->bas = NULL;
            k->son = NULL;
        }
        else {
            k->bas = k->bas->next;
            k->son->next = k->bas;
        }
        k->boyut--;
    }
    return silinenpuan;
}
int main() {
    srand(time(NULL)); //rastgele sayı üretimi 
    Kuyruk* kuyruk = yenikuyruk(5);
    int puan = 0; 
    int atis = 1; 
    int atislar[] = {11, 21, 27, 33, 36}; //hedef tahtasından rastgele atış seçimi için
    while (puan < 99) { 
        int secilenatis = atislar[rand() % 5]; //rastgele atış seçimi
        kuyrugaekle(kuyruk, secilenatis); 
        printf("Atış %d: %d puan aldınız.\n", atis, secilenatis);
        puan += secilenatis ;
        if (puan >= 100) {
            printf("Toplam puanınız 100'ü aştı. Kaybettiniz.\n");
            break; 
        }
        printf("toplam puan : %d\n", puan);
        atis++ ; 
    }
    if (puan == 99) {
        printf("hedefe ulaşıldı.\n");
    }
    return 0;     }