#include<stdio.h>		//Txt dosyasindan matris cekip komsuluk listesi olusturan ve garfi Breadth-First Search ile gezen program
#include <stdlib.h>
#include<string.h>
#define matris_boyutu 9

int matris[matris_boyutu][matris_boyutu];
int visit[matris_boyutu]; //hic ugranilmamis: -1  bir kere ugranilmis:0  iki kere ugranilmis:1  Dugumun ugranilma durumunu tutar.
int number_of_step[matris_boyutu];//Dugume kac adimda ulasildigini tutar.
int parent[matris_boyutu]; //Dugumun parentini tutar.

typedef struct dugum{//Komsuluk listesi icin dugum yapsý olusturulur.
	int dugum_no;
	struct dugum *sonraki;
}Dugumler;

typedef struct liste{//Komsuluk listesi icin dugum yapisinddan bir liste olusturulur.
	Dugumler satir[matris_boyutu];
}Listeler;

Listeler Liste;

typedef struct Kuyruk{//BFS icin kuyruk (ilk giren ilk cikar) yapýsý olusturulur.
	int indis;
	int dugum_no[matris_boyutu];
}Kuyruklar;

Kuyruklar Yeni_Kuyruk;

int Kuyruk_Bosmu();
void Kuyruga_Ekle(int sayi);
int Kuyruktan_Cikar();
void BFSearch(int dugum_no);
void sifirla();
void collision(Dugumler *kayit,Dugumler *satir_basi);
void Liste_olustur();
void Liste_Listele();
void Graf_olustur();
void Matris_Listele(int matris[matris_boyutu][matris_boyutu]);

int Kuyruk_Bosmu(){ 
	if (Yeni_Kuyruk.indis==-1) //Kuyruk boþ.
		return -1;
	else      //Kuyruk boþ deðil.
		return 1;
}

void Kuyruga_Ekle(int sayi){
    Yeni_Kuyruk.indis++; 
 	Yeni_Kuyruk.dugum_no[Yeni_Kuyruk.indis]=sayi;
}

int Kuyruktan_Cikar(){ 
	int cikan_dugum;
	int i;
    cikan_dugum=Yeni_Kuyruk.dugum_no[0]; 
	for(i=1;i<=Yeni_Kuyruk.indis;i++) {
		Yeni_Kuyruk.dugum_no[i-1]=Yeni_Kuyruk.dugum_no[i];
	}
	Yeni_Kuyruk.indis--; 
	return cikan_dugum;
}

void BFSearch(int dugum_no){
	
	printf("Grafin cikisi ararken izledigi yol:\n\n");
	int ilk_dugum; //Kuyruktaki ilk dugumu temsil eder.
	visit[dugum_no]=0;// Baslangýc dugumune 1 kere ugranildi.
	number_of_step[dugum_no]=0; //Baslangýc dugumunun adim sayisi 0 olarak girilir.
 	Kuyruga_Ekle(dugum_no);//Baslangic dugumu kuyruga eklenir
	while(Kuyruk_Bosmu()!=-1){
		ilk_dugum=Kuyruktan_Cikar();//Esas dugum kuyruktan cýkarýlýr.
		printf("%d. dugume ugrandi.\n",ilk_dugum);
		Dugumler *gecici;
		gecici=Liste.satir[ilk_dugum].sonraki;
		while(gecici!=NULL){
			if(visit[gecici->dugum_no]==-1){//Esas dugumun komsu dugumune daha once ugranilmamis ise.
				visit[gecici->dugum_no]=0; //Esas dugumun komsu dugumunun visiti 0 (1 kere ugrandý) olarak guncellendi.
				number_of_step[gecici->dugum_no]=number_of_step[ilk_dugum]+1;//Esas dugumun komsu dugumunun adim sayisi parentinin 1 fazlasi olarak güncellendi.
				parent[gecici->dugum_no]=ilk_dugum;//Esas dugumun komsu dugumunun parentina kuyruktan cikan ilk dugum verildi.
				Kuyruga_Ekle(gecici->dugum_no);//Esas dugumun komsu dugumu kuyruga eklendi.
			}
			gecici=gecici->sonraki;
		}
		visit[ilk_dugum]=1;//Kuyruktan aldigimiz ilk dugumun visiti, butun komsulari gezildikten sonra 1 (2 kez ugrandi) olarak guncellendi.
	}
	
}

void sifirla(){//Hem liste hemde BFS elemanlari ilk kullanim icin sifirlanirlar.
	for(int i=0;i<matris_boyutu;i++){
		Liste.satir[i].dugum_no=-1;
		Liste.satir[i].sonraki=NULL;
		visit[i]=-1;
		number_of_step[i]=NULL;
		parent[i]=NULL;
	}
}

void collision(Dugumler *kayit,Dugumler *satir_basi){
	Dugumler *gecici;
	gecici=satir_basi;
	while(gecici->sonraki!=NULL){//En son komsuya gelene kadar devam eder.
		gecici=gecici->sonraki;
	}
	gecici->sonraki=kayit;//En son komsunun sonuna ekler.
	kayit->sonraki=NULL;
}


void Graf_olustur(){  // Graf.txt dosyasindan bilgi cekerek komsuluk matrisini olusturur. 
	FILE *fp;
	char satir[50],satir2[10];
	if ((fp = fopen("Graf.txt", "r")) == NULL) { //Okumak icin dosya acýlýr.
      printf("Dosya açma hatasý!\n");
      exit(0);
  }
  int matris_satir=0,matris_sutun=0;
  while(fgets(satir, matris_boyutu*sizeof(int) ,fp)) { //txt dosyasi satir satir okunur. Parcalanip matrise atilir.
    matris_sutun=0;
    int satir_uzunlugu=0;
	for(int i=0;satir[i]!='\0';i++){//Dosyadan okunan satirin uzunlugu hesaplanir.
    	satir_uzunlugu++;
	}
	int sutun_indis=0,sayi=0;
	
    for(int i=0;i<matris_boyutu;i++){
    	int c=0;
      	while(satir[sutun_indis]!=' ' && sutun_indis<=satir_uzunlugu){//Ilk bosluga ve satirin sonuna ulasana kadar devam eder ve sayiyi satir2 degiskeninde saklar.
  			satir2[c]=satir[sutun_indis];
  			c++;
  			sutun_indis++;
  		}
  		sutun_indis++;//Bosluga ulastiginda bir sonraki sayiya gecebilmesi icin sutun_indisini arttirir.
  		sayi=atoi(satir2);//satir2 de tutulan string turundeki sayiyi integera cevirir.
  		memset(satir2,'\0',sizeof(satir2));//satir2 yi sifirlar.
  		matris[matris_satir][matris_sutun]=sayi;//sayi matrisin belli indisine verilir.
  		matris_sutun++;
	}
	matris_satir++;
	
}
	fclose(fp);
	printf("\n");
}

void Matris_Listele(int matris[matris_boyutu][matris_boyutu]){ //Komsuluk matrisini listeler.
	printf("Komsuluk Matrisi:\n\n");
	for(int i=0;i<matris_boyutu;i++){
		for(int j=0;j<matris_boyutu;j++){
			printf("%d ",matris[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void Liste_olustur(){ // Graf_olusturla olusturulan komsuluk matrisini kullanarak komsuluk listesi olusturulur.
	Dugumler *kayit;
	for(int i=0;i<matris_boyutu;i++){
		Liste.satir[i].dugum_no=i;  //Esas dugumler listenin en basina yerlestirilir.
		for(int j=0;j<matris_boyutu;j++){
			if(matris[i][j]==1){
				kayit=(Dugumler *) malloc(sizeof(Dugumler));
				if(kayit==NULL){
					printf("Yeterli bellek yok");
					exit(0);
				}
				kayit->dugum_no=j;
				collision(kayit, &Liste.satir[i]);//Esas dugumun devamina komsu dugumlerini eklemek icin kullanilir.
			}
		}
	}
}

void Liste_Listele(){//Komþuluk Listesini listeler

	printf("Komsuluk Listesi:\n\n");
	Dugumler *gecici;
	for(int i=0;i<matris_boyutu;i++){//Listenin ilk basindaki esas dugum yazdirilir.
		printf("%d -> ",Liste.satir[i].dugum_no);
		gecici=Liste.satir[i].sonraki;
		while(gecici!=NULL){//Esas dugumun komsulari yazdirilir.
			printf("%d -> ",gecici->dugum_no);
			gecici=gecici->sonraki;
		}
		printf(" / \n\n");
	}
}

int main(){
	Yeni_Kuyruk.indis=-1;
	Graf_olustur();
	Matris_Listele(matris);
	sifirla();
	Liste_olustur();
	Liste_Listele();
	BFSearch(8);
	
}
