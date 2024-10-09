#include<stdio.h>
#include<stdlib.h>

struct dugum{
	int veri;
	struct dugum* ileri;
};
typedef struct dugum Dugum;
typedef Dugum* Dugumptr;

Dugumptr yeniDugum(int x)
{
	Dugumptr dugum=(Dugumptr)malloc(sizeof(Dugum));
	dugum->veri=x;
	dugum->ileri=NULL;
	return dugum;
}

struct liste{
	Dugumptr bas;
	Dugumptr son;
};
typedef struct liste Liste;
typedef Liste* Listeptr;

Listeptr yeniListe(){
	Listeptr liste=(Listeptr)malloc(sizeof(Liste));
	liste->bas=NULL;
	liste->son=NULL;
	return liste;
}

void listeninBasinaEkle(Listeptr liste, Dugumptr yeni){
	if(liste->bas==NULL)
		liste->son=yeni;
	yeni->ileri=liste->bas;
	liste->bas=yeni;	
}

void listeninSonunaEkle(Listeptr liste, Dugumptr yeni){
	if(liste->bas==NULL)
		liste->bas=yeni;
	else
		liste->son->ileri=yeni;
	liste->son=yeni;
}

void listeArayaElemanEkle(Dugumptr onceki, Dugumptr yeni){
	yeni->ileri=onceki->ileri;
	onceki->ileri=yeni;
}

int listeBoyut(Listeptr liste){
	Dugumptr temp= liste->bas;
	int sayac;
	while(temp){
		sayac++;
		temp=temp->ileri;
	}
	return sayac;
}

void listeOrtayaElemanEkle(Listeptr liste, Dugumptr yeni){
	int x= listeBoyut(liste);
	int orta=x/2;
	
	Dugumptr temp=liste->bas;
	for(int i=0;i<orta;i++)
		temp=temp->ileri;
		
	//printf("neredeyim %d \n", temp->veri);
	
	yeni->ileri=temp->ileri;
	temp->ileri=yeni;	
}

void yazdir(Listeptr liste){
	Dugumptr temp=liste->bas;
	while(temp){
		printf("%d -->", temp->veri);
		temp=temp->ileri;
	}
}

int main()
{
	Dugumptr d1, d2, d3, d4, d5;
	d1=yeniDugum(10);
	d2=yeniDugum(20);
	d3=yeniDugum(30);
	d4=yeniDugum(40);
	d5=yeniDugum(50);
	//printf("%d ", d1->veri);
	Listeptr liste1;
	liste1=yeniListe();
	listeninBasinaEkle(liste1,d1);
	//listeninBasinaEkle(liste1,d2);
	//listeninBasinaEkle(liste1,d3);
	listeninSonunaEkle(liste1,d4);
	listeninSonunaEkle(liste1,d3);
	listeninSonunaEkle(liste1,d2);
	//listeArayaElemanEkle(d3, d5);
	listeOrtayaElemanEkle(liste1, d5);
	yazdir(liste1);
	return 0;
}
