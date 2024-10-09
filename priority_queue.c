#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct TreeNode {
    char data;
    int frekans;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* newNode(char data, int frekans) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->frekans = frekans;
    node->left = node->right = NULL;
    return node;
}
struct onceliklikuyruk { 
    int boyut;
    int kapasite ;
    struct TreeNode** array;
};
struct onceliklikuyruk* createPriorityQueue(int kapasite) {
    struct onceliklikuyruk* pq = (struct onceliklikuyruk*)malloc(sizeof(struct onceliklikuyruk));
    pq->boyut = 0;
    pq->kapasite = kapasite ;
    pq->array = (struct TreeNode*)malloc(pq->kapasite * sizeof(struct TreeNode));
    return pq;
}
void swap(struct TreeNode** a, struct TreeNode** b) { //düğümleri sıralamak içingerekli
    struct TreeNode* temp = *a;
    *a = *b;
    *b = temp;
}
void kuyruktut(struct onceliklikuyruk* pq, int index) { //öncelikli kuyruk yapısının çalışması için 
    int smallest = index; 
    int left = 2 * index + 1; //sol çocuk
    int right = 2 * index + 2; //sağ çocuk

    if (left < pq->boyut && pq->array[left]->frekans < pq->array[smallest]->frekans)
        smallest = left;
    if (right < pq->boyut && pq->array[right]->frekans < pq->array[smallest]->frekans)
        smallest = right;
    if (smallest != index) {
        swap(&pq->array[index], &pq->array[smallest]);
        kuyruktut(pq, smallest);
    }
}
struct TreeNode* minimumcikar(struct onceliklikuyruk* pq) { // en küçük öncelikliyi düğümden çıkar 
    struct TreeNode* minNode = pq->array[0];
    pq->array[0] = pq->array[pq->boyut - 1];
    --pq->boyut;
    kuyruktut(pq, 0);
    return minNode;
}
void ekleme(struct onceliklikuyruk* pq, struct TreeNode* node) { //kuyruğa yeni düğüm ekleme
    ++pq->boyut;
    int i = pq->boyut - 1;
    while (i && node->frekans < pq->array[(i - 1) / 2]->frekans) {
        pq->array[i] = pq->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->array[i] = node;
}
struct onceliklikuyruk* onceliklikuyrukbaslat(char* text) {
    int count[256] = {0};  // ASCII'nin tamamını kapsayan bir dizinin boyutunu 
    for (int i = 0; text[i] != '\0'; ++i)
        ++count[text[i]];
    struct onceliklikuyruk* pq = createPriorityQueue(256);
    for (int i = 0; i < 256; ++i) {
        if (count[i] != 0) {
            struct TreeNode* node = newNode((char)i, count[i]);
            ekleme(pq, node);     }
    }
    return pq;     }
struct TreeNode* agacolusturma(char* text) {
    struct TreeNode *left, *right, *top;
    struct onceliklikuyruk* pq = onceliklikuyrukbaslat(text);
    while (pq->boyut != 1) {
        left = minimumcikar(pq);
        right = minimumcikar(pq);
        top = newNode('$', left->frekans + right->frekans);
        top->left = left;
        top->right = right;
        ekleme(pq, top);
    }
    return minimumcikar(pq);
}
void huffmancode(struct TreeNode* root, int array[], int top) {
    if (root->left) {
        array[top] = 0;
        huffmancode(root->left, array, top + 1);
    }
    if (root->right) {
        array[top] = 1;
        huffmancode(root->right, array, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i)
            printf("%d", array[i]);
        printf("\n");
    }
}
int main() {
    char text[1000]; 
    printf("metni giriniz: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; //amaç klavyeden girilen metnin sonunda yer alan \n kaldırarak metnin sonunu belirtmek
    struct TreeNode* root = agacolusturma(text);
    int array[100], top = 0;
    printf("binary kodları:\n");
    huffmancode(root, array, top);
    return 0;
}