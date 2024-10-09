#include<stdio.h>
#include<stdlib.h>

//Tek yonlu bagli liste
//dugum tasarimi
struct node{
	int data;
	struct node* ileri;
};
typedef struct node Node;
typedef Node* Nodeptr;

//Dü?üm olu?utrma
Nodeptr newNode(int veri){
	Nodeptr node = (Nodeptr)malloc(sizeof(Node));
	node->data=veri;
	node->ileri=NULL;
	return node;
}


struct stack{
	Nodeptr bas;
};
typedef struct stack Stack;
typedef Stack* Stackptr;


Stackptr newStack(){
	Stackptr stack=(Stackptr)malloc(sizeof(Stack));
	stack->bas=NULL;
	return stack;
}

//stack basina eleman ekleme O(1)
void push(Stackptr stack, Nodeptr yeni){
	yeni->ileri=stack->bas;
	stack->bas=yeni;
}






//stack eleman sayisina bulma
int stackSize(Stackptr stack){
	Nodeptr temp=stack->bas;
	int sayac=0;
	while(temp){
		sayac++;
		temp=temp->ileri;
	}
	return sayac;
}







//stack ba?yndan eleman silme
void pop(Stackptr stack){
	if(stack->bas != NULL)
		stack->bas=stack->bas->ileri;
}
	
//stack yazdir
void show(Stackptr stack){
	Nodeptr temp = stack->bas;
	while(temp){
		printf("%d --> ", temp->data);
		temp=temp->ileri;
	}
	printf("\n ");
}
int main(){
	Nodeptr n1, n2, n3, n4, n5;
	n1=newNode(10);
	n2=newNode(20);
	n3=newNode(30);
	n4=newNode(40);
	n5=newNode(50);
	Stackptr stack1;
	stack1=newStack();

	push(stack1, n1);
	push(stack1, n2);
	push(stack1, n3);
	show(stack1);
	pop(stack1);
	show(stack1);
	/*
	int sayi=listSize(liste1);
	printf("liste eleman sayisi: %d ", sayi);
	*/
	/*
	if(listSearch(liste1, 300))
		printf("Aranan dugum bulundu\n");
	else 
		printf("Aranan dugum bulunamadi\n");
	*/
	//listSearch2(liste1, 3);
	//removeHead(liste1);
	//removeTailer(liste1);

	
	return 0;
}
