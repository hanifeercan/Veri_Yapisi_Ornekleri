#include<stdio.h>   // İceriginde "ogrenci_no isim not" seklinde ogrenci bilgileri bulunan txt doyasindan bilgileri cekerek
#include<stdlib.h>  // Hash veri yapisi ile sirali ogrenci not tablosu olusturma.
#include<string.h>
#define boyut 10

typedef struct _Ogrenci{
	int ogr_no;
	char ad[20];
	int notu;
}Ogrenci;

Ogrenci veri_liste[boyut];
int hash_tablo[boyut][2];

int hash(int notu){
	return notu % boyut;
}
void ekle();
void arama();
void listele();
int menu();
void Initalize_Table();
void txt_dosyasindan_hasha_ekle();

void Initalize_Table(){
	for(int i=0;i<boyut;i++){
		for(int j=0;j<2;j++){
			hash_tablo[i][j]=-1;
		}
	}
	memset(veri_liste,'\0',sizeof(veri_liste));
	menu();
}

int menu(){
	int secim;
	printf("\n1-Txt Dosyasindan Ekleme\n2-Kullanici Girisi Ekleme\n3-Arama\n4-Listeleme\n5-Hash Tablosunu ve Veri Listeyi Temizleme\n6-Cikis\n\n");
	printf("Yapmak istediginiz islemin numarasini giriniz: ");
	scanf("%d",&secim);
	switch(secim){
		case 1: 
			txt_dosyasindan_hasha_ekle();
			break;
		case 2: 
			ekle();
			break;
		case 3: 
			arama();
			break;
		case 4:
			listele();
			break;
		case 5:
			Initalize_Table();
			break;
		case 6: 
			return 0;
		default:
			printf("Hatali giris yaptiniz!\n");
	}
}
void txt_dosyasindan_hasha_ekle(){ //txt dosyasindan veri ekleme
	char metin[50],metin2[20];
	int ogr_no,notu,index,kontrol;
	char ad[20];
	FILE *fp;
	fp=fopen("ogrenci_bilgileri.txt","r");
	if(fp==NULL){
		printf("\n\nDosyadan okuma hatasi!\n\n");
		exit(0);
	}
	while(fgets(metin,sizeof(Ogrenci),fp)){
   		
		int j=0;
   		for(int i=0;metin[j]!=' ';i++){
   			metin2[i]=metin[j];
   			j++;
		}
		ogr_no=atoi(metin2);
		j++;
		memset(metin2,'\0',sizeof(metin2));
		for(int i=0;metin[j]!=' ';i++){
	   		ad[i]=metin[j];
	   		j++;
		}
		j++;
		for(int i=0;metin[j]!='\0';i++){
   			metin2[i]=metin[j];
   			j++;
		}
		notu=atoi(metin2);
		memset(metin2,'\0',sizeof(metin2));
		index=hash(notu);
		kontrol=0;
		if(hash_tablo[index][0]==-1){ //Hash tablosunun ilgili indexi bos ise veri listesininde bostur.
			hash_tablo[index][0]=notu;
			for(int i=0;ad[i]!='\0';i++){
				veri_liste[index].ad[i]=ad[i];
			}
			veri_liste[index].notu=notu;
			veri_liste[index].ogr_no=ogr_no;
			kontrol=1;
		}
		else {// Hash tablosunun ilgili indexi dolu ise
			int index2=0;
			for(index2;index2<boyut;index2++){ 
				if(hash_tablo[index2][0]==-1){//Buldugu ilk bos yere ekleme yapar.
					hash_tablo[index2][0]=notu;
					if(hash_tablo[index][1]==-1){//Hash tablosundaki ilgili next kismi bos ise index2 yi ekler. 
						hash_tablo[index][1]=index2;
					}
					else{//Next kismi dolu ise ilk buldugu bos next kisma index2'nin degerini ekler.
						for(int i=0;i<boyut;i++){
							if(hash_tablo[i][1]==-1){
								hash_tablo[i][1]=index2;
								break;
							}		
						}
					}
					if(veri_liste[index2].notu==NULL){//Veri listenin index2 alanı bossa ekleme yapar.
						for(int i=0;ad[i]!='\0';i++){
							veri_liste[index2].ad[i]=ad[i];
						}
						veri_liste[index2].notu=notu;
						veri_liste[index2].ogr_no=ogr_no;
					}			
					else{
						printf("\nVeri listesi dolmustur!\n\n");
					}
					kontrol=1;
					break;
				}
			}
			if(kontrol==0){
				printf("\n\nTablo Dolu!\n\n");	
			}
		}
		memset(metin,'\0',sizeof(metin));
		memset(ad,'\0',sizeof(ad));
	}
	fclose(fp);
	menu();
}

void ekle(){  //Kullanici girisi ile ekleme
	int ogr_no,notu,index,kontrol=0;
	char ad[20];
	printf("\nOgrencinin numarasini giriniz: ");
	scanf("%d",&ogr_no);
	printf("Ogrencinin ismini giriniz: ");
	scanf("%s",ad);
	printf("Ogrencinin notunu giriniz: ");
	scanf("%d",&notu);
	
	index=hash(notu);
	printf("%d\n ",index);
	
	if(hash_tablo[index][0]==-1){ //Hash tablosunun ilgili indexi bos ise veri listesininde bostur.
		hash_tablo[index][0]=notu;
		for(int i=0;ad[i]!='\0';i++){
			veri_liste[index].ad[i]=ad[i];
		}
		veri_liste[index].notu=notu;
		veri_liste[index].ogr_no=ogr_no;
	}
	else {// Hash tablosunun ilgili indexi dolu ise
		int index2=0;
		for(index2;index2<boyut;index2++){ 
			if(hash_tablo[index2][0]==-1){//Buldugu ilk bos yere ekleme yapar.
				hash_tablo[index2][0]=notu;
				if(hash_tablo[index][1]==-1){//Hash tablosundaki ilgili next kismi bos ise index2 yi ekler.
					hash_tablo[index][1]=index2;
				}
				else{//Next kismi dolu ise ilk buldugu bos next kisma index2'nin değerini ekler.
					for(int i=0;i<boyut;i++){
						if(hash_tablo[i][1]==-1){
							hash_tablo[i][1]=index2;
							break;
						}		
					}
				}
				if(veri_liste[index2].notu==NULL){//Veri listenin index2 alani bossa ekleme yapar.
					for(int i=0;ad[i]!='\0';i++){
						veri_liste[index2].ad[i]=ad[i];
					}
					veri_liste[index2].notu=notu;
					veri_liste[index2].ogr_no=ogr_no;
				}			
				else{
					printf("\n\nVeri listesi dolmustur!\n\n");
				}
				kontrol=1;
				break;
			}
		}
		if(kontrol==0){
			printf("\n\nTablo Dolu!\n\n");	
		}
	}
	menu();	
}

void listele(){
	printf("\nHash Tablosu: \n\n");
	for(int i=0;i<boyut;i++){
		for(int j=0;j<2;j++){
			printf("%d  ",hash_tablo[i][j]);
		}
		printf("\n");
	}
	printf("\nVeri Liste:\n\n");
	for(int i=0;i<boyut;i++){
		printf("%d  %s  %d \n ",veri_liste[i].ogr_no,veri_liste[i].ad,veri_liste[i].notu);
	}
	menu();
}

void arama(){
	int notu,sayac=1,index,kontrol=0;
	printf("Bulmak istediginiz ogrencinin notunu giriniz: ");
	scanf("%d",&notu);
	index=hash(notu);
	if(hash_tablo[index][0]==notu){//Aradıgın notu hash indexindeki not ile aynı ise
		printf("%d  %s  %d\n",veri_liste[index].ogr_no,veri_liste[index].ad,veri_liste[index].notu);
		kontrol=1;
	}
	else{//Aynı degil ise
		while(hash_tablo[index][1]!=-1){//Ve Hashin next degeri baska bir indexin degerini tutuyorsa 
			sayac++;
			index=hash_tablo[index][1];
			if(hash_tablo[index][0]==notu){
				printf("%d  %s  %d\n",veri_liste[index].ogr_no,veri_liste[index].ad,veri_liste[index].notu);
				kontrol=1;
				break;
			}		
		}	
	}
	if(kontrol!=0){
		printf("\nVeri %d adimda bulundu!\n",sayac);
	}
	else{
		printf("\nVeri bulunamadi!\n");
	}
	menu();
}

int main(){
	menu();
}
