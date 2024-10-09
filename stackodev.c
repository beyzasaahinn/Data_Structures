#include <stdio.h>
#include <stdlib.h>

typedef struct Ornek {
    int tip;
    int islenen;
    char islem;
    int oncelik;
} Ornek;

typedef struct cikin {
    Ornek* veri;
    struct cikin* sonraki;
} cikin;

cikin* yenicikin() {
    return NULL;
}
void cikinekle(cikin** stack, Ornek* yeni) {
    cikin* yeni_cikin = (cikin*)malloc(sizeof(cikin));
    yeni_cikin->veri = yeni;
    yeni_cikin->sonraki = *stack;
    *stack = yeni_cikin;
}
Ornek* cikinsil(cikin** stack) {
    if (*stack == NULL)
        return NULL;
    Ornek* temp = (*stack)->veri;
    cikin* silinecek = *stack;
    *stack = (*stack)->sonraki;
    free(silinecek);
    return temp;
}
int oncelik(char operator) {
    if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '+' || operator == '-')
        return 1;
    else
        return 0; // Parantez
}
void infix_to_postfix(const char* infix) {
    cikin* stack = yenicikin();
    printf("Postfix notasyonu: ");
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] >= '0' && infix[i] <= '9') {
            printf("%c", infix[i]);
 }     else if (infix[i] == '(') {
            Ornek* yeni = (Ornek*)malloc(sizeof(Ornek));
            yeni->islem = '(';
            cikinekle(&stack, yeni);
 } else if (infix[i] == ')') {
            while (stack != NULL && stack->veri->islem != '(') {
                Ornek* temp = cikinsil(&stack);
                printf("%c", temp->islem);
                free(temp); }
            cikinsil(&stack); 
 } else {
            while (stack != NULL && oncelik(infix[i]) <= oncelik(stack->veri->islem)) {
                Ornek* temp = cikinsil(&stack);
                printf("%c", temp->islem);
                free(temp); }
            Ornek* yeni = (Ornek*)malloc(sizeof(Ornek));
            yeni->islem = infix[i];
            cikinekle(&stack, yeni);
        }
    }
    while (stack != NULL) {
        Ornek* temp = cikinsil(&stack);
        printf("%c", temp->islem);
        free(temp);
    }
    printf("\n");
}
int main() {
    char infix[100];
    printf("infix ifadeyi giriniz: ");
    scanf("%s", infix);
    infix_to_postfix(infix);
    return 0;      }