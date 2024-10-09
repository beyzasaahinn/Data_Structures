#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HEAP_SIZE 100 
typedef struct {
    int elements[MAX_HEAP_SIZE];
    int size;    
    int capacity; 
} Heap;

Heap *createHeap() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = MAX_HEAP_SIZE;
    return heap;
}
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapifyDown(Heap *heap, int index) {
    int leftChild, rightChild, smallest;
    while (1) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        smallest = index;
        if (leftChild < heap->size && heap->elements[leftChild] < heap->elements[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < heap->size && heap->elements[rightChild] < heap->elements[smallest]) {
            smallest = rightChild;
        }
        if (smallest != index) {
            swap(&heap->elements[index], &heap->elements[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}
void heapify(Heap *heap) {
    int startIndex = (heap->size - 2) / 2;
    for (int i = startIndex; i >= 0; i--) {
        heapifyDown(heap, i);
    }
}
void insert(Heap *heap, int key) {
    if (heap->size >= heap->capacity) {
        printf("Heap dolu, eleman eklenemiyor.\n");
        return;
    }
    heap->elements[heap->size] = key;
    heap->size++;
    heapifyDown(heap, 0); }

Heap *mergeHeaps(Heap *heap1, Heap *heap2) {
    Heap *mergedHeap = createHeap();
    for (int i = 0; i < heap1->size; i++) {
        insert(mergedHeap, heap1->elements[i]);
    }
    for (int i = 0; i < heap2->size; i++) {
        insert(mergedHeap, heap2->elements[i]);
    }
    return mergedHeap;
}
void printHeap(Heap *heap) {
    printf("Heap elemanlari: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}
int main() {
    srand(time(NULL));
    int childCount;
    printf("Kac cocuk sayisi girilecek: ");
    scanf("%d", &childCount);

    if (childCount <= 0 || childCount > MAX_HEAP_SIZE) {
        printf("Gecersiz cocuk sayisi.\n");
        return 1;    
    }
    Heap *userHeap = createHeap();

    for (int i = 0; i < childCount; i++) {
        int element = rand() % 100; 
        insert(userHeap, element);
    }
    printf("Kullanici Heap:\n");
    printHeap(userHeap);
    heapify(userHeap);
    
    printf("Heapify sonrasi kullanici Heap:\n");
    printHeap(userHeap);

    Heap *duplicatedHeap = createHeap();
    for (int i = 0; i < userHeap->size; i++) {
        insert(duplicatedHeap, userHeap->elements[i]);
    }
    Heap *mergedHeap = mergeHeaps(userHeap, duplicatedHeap);
    printf("Birlestirilmis Heap:\n");
    printHeap(mergedHeap);
    return 0;
}