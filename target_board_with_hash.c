#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
typedef struct Ornek {
    int toplam;
    char *path;
    struct Ornek *next;
} Ornek;
typedef struct Kuyruk {
    Ornek *front;
    Ornek *rear;
    int size;
} Kuyruk;
#define HASH_SIZE 101
typedef struct HashTable {
    Ornek *table[HASH_SIZE];
} HashTable;
Ornek *newOrnek(int toplam, char *path) {
    Ornek *new_node = (Ornek *)malloc(sizeof(Ornek));
    new_node->toplam = toplam;
    new_node->path = strdup(path);
    new_node->next = NULL;
    return new_node;
}
Kuyruk *newKuyruk() {
    Kuyruk *queue = (Kuyruk *)malloc(sizeof(Kuyruk));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}
bool kuyrukBos(Kuyruk *queue) {
    return (queue->size == 0);
}
void kuyrugaEkle(Kuyruk *queue, int toplam, char *path) {
    Ornek *new_node = newOrnek(toplam, path);
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}
void kuyruktanSil(Kuyruk *queue) {
    if (!kuyrukBos(queue)) {
        Ornek *temp = queue->front;
        queue->front = queue->front->next;
        free(temp->path);
        free(temp);
        if (queue->front == NULL) {
            queue->rear = NULL;
        }
        queue->size--;
    }
}
int hashfonksiyonu(int toplam) {
    return toplam % HASH_SIZE;
}
Ornek *karmaAra(HashTable *hash_table, int toplam) {
    int index = hashfonksiyonu(toplam);
    Ornek *current = hash_table->table[index];
    while (current != NULL) {
        if (current->toplam == toplam) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void karmaEkle(HashTable *hash_table, int toplam, char *path) {
    int index = hashfonksiyonu(toplam);
    Ornek *new_node = newOrnek(toplam, path);
    if (hash_table->table[index] == NULL) {
        hash_table->table[index] = new_node;
    } else {
        Ornek *current = hash_table->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
void karmaTemizle(HashTable *hash_table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        Ornek *current = hash_table->table[i];
        while (current != NULL) {
            Ornek *temp = current;
            current = current->next;
            free(temp->path);
            free(temp);
        }
    }
    free(hash_table);
}
int hedefal() {
    int hedefler[] = {11, 21, 27, 33, 36};
    return hedefler[rand() % 5];
}
void hedeftahtasi() {
    srand(time(NULL));
    int score = 0;
    int atislar = 1;
    Kuyruk *queue = newKuyruk();
    HashTable *hash_table = (HashTable *)malloc(sizeof(HashTable));
    for (int i = 0; i < HASH_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
    while (score < 99) {
        int hedef = hedefal();
        char target_str[5];
        sprintf(target_str, "%d", hedef);

        Ornek *gecerli = karmaAra(hash_table, score + hedef);
        if (gecerli != NULL) {
            printf("Geçersiz atış kombinasyonu! Oyun sona eriyor.\n");
            printf("En iyi yol: %s\n", gecerli->path);
            break;
        }
        kuyrugaEkle(queue, score + hedef, target_str);
        if (score + 11 >= 100) {
            printf("toplam puanınız 100'ü aşacak. Kaybettiniz.\n");
            break;
        }
        printf("Atış %d: %d puan aldınız.\n", atislar, hedef);
        printf("toplam puan: %d\n", score + hedef);
//toplam puan 100'ü aştığı an otomatik atış yapmayı bırakıyor
        Ornek *node = newOrnek(score + hedef, "");
        strcpy(node->path, target_str);
        karmaEkle(hash_table, score + hedef, node->path);
        score += hedef;
        atislar++;
    }
    if (score == 99) {
        printf("Hedefe ulaşıldı.\n");
    }
    printf("Hash Tablosu:\n");
    for (int i = 0; i < atislar; i++) {
        printf("Index %d: ", i);
        Ornek *temp = hash_table->table[i];
        while (temp != NULL) {
            printf("(%d, %s) ", temp->toplam, temp->path);
            temp = temp->next;
        }
        printf("\n");
    }
    karmaTemizle(hash_table);
    while (!kuyrukBos(queue)) {
        kuyruktanSil(queue);
    }
    free(queue);
}
int main() {
    hedeftahtasi();
    return 0;
}