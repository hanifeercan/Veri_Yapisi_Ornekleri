#include<stdio.h>    //Tek bilinmeyenli P(x) polinomuna ait x bagımsız  degiskeninin derecelerini ve katsayilarini tamsayi 
#include<conio.h>  // olarak tutacak tek yonlu bagli liste yapisi olusturuyoruz.
#include<stdlib.h>
#include<math.h>

struct Dugum {
 int derece;
 int katSayi;
 struct Dugum* sonraki;
};

struct Dugum *ilk=NULL;
struct Dugum *son=NULL;
struct Dugum *gecici=NULL;
struct Dugum *birOnceki=NULL;

void Ekleme();
void Silme();
int Yazdirma();
int Hesapla();
int Cikis();
void Menu();

void Menu(){
	int secim;
	do{
		printf("\n1-Ekleme\n2-Silme\n3-Yazdirma\n4-Hesapla\n5-Cikis\n");
		printf("Lutfen yapmak istediginiz islemin numarasini giriniz (1-5): ");
		scanf("%d",&secim);
		if(secim>5 || secim <1){
			printf("Lutfen 1-5 arasinda bir sayi giriniz!");
		}
	}while(secim>5 || secim<1);
	
	switch(secim){
		case 1: 
			Ekleme();
			break;
		case 2:
			Silme();
			break;
		case 3: 
			Yazdirma();
			break;
		case 4:
			Hesapla();
			break;
		case 5:
			Cikis();
			break;
		default:
			printf("Lutfen 1-5 arasinda bir deger giriniz!");
	}
}

void Ekleme(){//Ekleme islemi derece buyuklugune gore yapilir(buyukten kucuge).
	int derece,kat_sayi,kontrol=0;
	struct Dugum *yeni=(Dugum *)malloc(sizeof(Dugum));
	printf("x'in kat sayisini giriniz: ");
	scanf("%d",&kat_sayi);
	printf("x'in derecesini giriniz: ");
	scanf("%d",&derece);
	yeni->derece=derece;
	yeni->katSayi=kat_sayi;
	yeni->sonraki=NULL;
	
	gecici=ilk;
	while(gecici!=NULL){
		if(gecici->derece==derece){
			kontrol=1;
			break;
		}
		gecici=gecici->sonraki;
	}
	if(kontrol==1){//Eklemeye calistigimiz derece bilgisine sahip elemanimiz varsa ekleme gerceklesmeyecektir.
		printf("Eklemeye calistiginiz %d. derece x degiskeni zaten mevcuttur!\n",derece);
	}
	else{
		if(ilk==NULL){
			ilk=yeni;
			son=ilk;
		}
		else if(ilk->derece<yeni->derece){
			yeni->sonraki=ilk;
			ilk=yeni;
		}
		else{
			birOnceki=ilk;
			gecici=ilk->sonraki;
			while(gecici!=NULL){
				if(gecici->derece>yeni->derece){
					birOnceki=birOnceki->sonraki;
					gecici=gecici->sonraki;
				}
				else break;
			}
			if(gecici==NULL){
				birOnceki->sonraki=yeni;
			}
			else{
				birOnceki->sonraki=yeni;
				yeni->sonraki=gecici;
			}
		}
	}
	Menu();
}

void Silme(){//Derece bilgisi girilen eleman bagli listeden silinir.
	struct Dugum *gecici1=ilk;
	birOnceki=NULL;
	int sil,kontrol=0;
	printf("\nSilmek istediginiz x bagımsız degiskeninin derecesini giriniz: ");
	scanf("%d",&sil);
	
	while(gecici1!=NULL){
		if(gecici1->derece==sil){
			kontrol=1;
			break;
		}
		gecici1=gecici1->sonraki;
	}
	if(kontrol!=1){
		printf("Silmek istediginiz %d. derece x degiskeni zaten mevcut degildir!\n",sil);
	}
	else{
		gecici1=ilk;
		while(gecici1){
			if(gecici1->derece==sil) break;
			birOnceki=gecici1;
			gecici1=gecici1->sonraki;
		}
		if(gecici1!=NULL){
			if(gecici1==ilk){
				if(ilk==son){
					ilk=NULL;
					son=NULL;
				}
				else{
					ilk=ilk->sonraki;
				}
			}
			else{
				if(gecici1==son){
					birOnceki->sonraki=NULL;
					son=birOnceki;
				}
				else{
					birOnceki->sonraki=gecici1->sonraki;
				}
			}
		}
		printf("Silmek istediginiz %d. derece x degiskeni silinmistir!\n",sil);
	}
	free(gecici1);
	Menu();
}


int Yazdirma(){ // P(x) polinomu yazdirilir.
	gecici=ilk;
	if(gecici==NULL){
		return 0;
	}
	printf("\n");
	while(gecici){
		printf("%dx^%d",gecici->katSayi,gecici->derece);
		gecici=gecici->sonraki;
		if(gecici!=NULL){
			if(gecici->katSayi>0){
				printf("+");
			}
		}
	}
	Menu();
}
int Hesapla(){//X degiskenine değer vererek P(x) polinomu hesaplaiır.
	int x,sonuc=0;
	printf("\nx degiskeni icin bir deger giriniz: ");
	scanf("%d",&x);
	gecici=ilk;
	while(gecici){
		sonuc=sonuc+(gecici->katSayi*(pow(x,gecici->derece)));
		gecici=gecici->sonraki;
	}
	printf("\nP(x)=%d\n ",sonuc);
	Menu();
}
int Cikis(){
	return 0;
}

int main(){
	Menu();
}

