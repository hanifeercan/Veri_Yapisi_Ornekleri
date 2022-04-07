#include<stdio.h>      //Txt dosyasindaki komsuluk matrisini cekerek grafin ozelliklerini listeleyen program.
#include <stdlib.h>   
#include<string.h>
#define matris_boyutu 5
int matris[matris_boyutu][matris_boyutu];

void Listele(int matris[matris_boyutu][matris_boyutu]);
void Graf_olustur();
void Dugum_bilgileri_getir();
void Toplam_kenar_hesapla();
void Kenar_maliyetleri();
void Komsu_bilgileri_getir();
void Graf_turu();

void Menu(){
	int secim;
	printf("1-Graf Olustur\n2-Listele\n3-Dugum Bilgilerini Ogren\n4-Komsu Bilgilerini Ogren\n5-Toplam Kenar Sayisini Ogren\n");
	printf("6-Toplam Kenar Maliyetini Ogren\n7-Graf Turunu Ogren\n8-Cikis\n");
	printf("Lutfen yapmak istediginiz islemin numarasini giriniz: ");
	scanf("%d",&secim);
	switch(secim){
		case 1:
			Graf_olustur();
			break;
		case 2:
			Listele(matris);
			break;
		case 3:
			Dugum_bilgileri_getir();
			break;
		case 4:
			Komsu_bilgileri_getir();
			break;
		case 5:
			Toplam_kenar_hesapla();
			break;
		case 6:
			Kenar_maliyetleri();
			break;
		case 7:
			Graf_turu();
			break;
		case 8:
			exit(0);
		default:
            printf("Lutfen 1-8 arasýnda bir sayi giriniz!\n");
			
	}
}


void Listele(int matris[matris_boyutu][matris_boyutu]){ //Komsuluk matrisini listeler.
	printf("\n");
	for(int i=0;i<matris_boyutu;i++){
		for(int j=0;j<matris_boyutu;j++){
			printf("%d ",matris[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	Menu();
}

void Graf_olustur(){  // Graf.txt dosyasindan bilgi cekerek komsuluk matrisini olusturur. 
	FILE *fp;
	char satir[50],satir2[10];
	if ((fp = fopen("Graf.txt", "r")) == NULL) {
      printf("Dosya açma hatasý!\n");
      exit(0);
  }
  int m_satir=0,m_sutun=0;
  while(fgets(satir, matris_boyutu*sizeof(int) ,fp)) {
    m_sutun=0;
    int satir_uzunlugu=0;
	for(int i=0;satir[i]!='\0';i++){
    	satir_uzunlugu++;
	}
	int sutun_indis=0,sayi=0;
	
    for(int i=0;i<matris_boyutu;i++){
    	int j=0;
      	while(satir[sutun_indis]!=' ' && sutun_indis<=satir_uzunlugu){
  			satir2[j]=satir[sutun_indis];
  			j++;
  			sutun_indis++;
  		}
  		sutun_indis++;
  		sayi=atoi(satir2);
  		memset(satir2,'\0',sizeof(satir2));
  		matris[m_satir][m_sutun]=sayi;
  		m_sutun++;
	}
	m_satir++;
	
}
  
	fclose(fp);
	printf("\n");
	Menu(); 
}

void Dugum_bilgileri_getir(){ // Kullanicinin girdigi dügüm numarasinin giris ve cikis degerlerini ekrana yazdirir.
	
	printf("\n");
	int dugum,giris_derecesi=0,cikis_derecesi=0;
	printf("Giris cikis derecelerini ogrenmek istediginiz dugumun numarasini giriniz: ");
	scanf("%d",&dugum);
	
	for(int i=0;i<matris_boyutu;i++){
		if(matris[i][dugum]!=0){
			giris_derecesi++;
		}
	}
	for(int i=0;i<matris_boyutu;i++){
		if(matris[dugum][i]!=0){
			cikis_derecesi++;
		}
	}
	printf("%d. dugumun giris derecesi: %d,cikis derecesi: %d\n",dugum,giris_derecesi,cikis_derecesi);
	printf("\n");
	Menu();
}

void Toplam_kenar_hesapla(){ // Graftaki toplam kenar sayýsýný hesaplar.
	printf("\n");
	int kenar_sayisi=0;
	for(int i=0;i<matris_boyutu;i++){
		for(int j=0;j<matris_boyutu;j++){
			if(matris[i][j]!=0){
				kenar_sayisi++;
			}
		}
	}
	printf("Graftaki toplam kenar sayisi: %d\n",kenar_sayisi);
	printf("\n");
	Menu();
}
void Kenar_maliyetleri(){ //Graftaki kenarlarin toplam maliyetini hesaplar.
	printf("\n");
	int kenar_maliyeti=0;
	for(int i=0;i<matris_boyutu;i++){
		for(int j=0;j<matris_boyutu;j++){
			if(matris[i][j]!=0){
				kenar_maliyeti=kenar_maliyeti+matris[i][j];
			}
		}
	}
	printf("Graftaki toplam kenar maliyeti: %d\n",kenar_maliyeti);
	printf("\n");
	Menu();

}
void Komsu_bilgileri_getir(){ //Kullanicinin girdigi dügümün komsu dügümlerinin maliyetlerini ekrana yazdirir.
	printf("\n");
	int dugum,giris_derecesi=0,cikis_derecesi=0;
	printf("Komsu bilgilerini ogrenmek istediginiz dugumun numarasini giriniz: ");
	scanf("%d",&dugum);
	for(int i=0;i<matris_boyutu;i++){
		if(matris[dugum][i]!=0){
			printf("%d. dugum, maliyet: %d\n",i,matris[dugum][i]);
		}
	}
	printf("\n");
	Menu();
}

void Graf_turu(){
	printf("\n");
	int kontrol=1,kontrol1=0;
	for(int i=0;i<matris_boyutu;i++){   //Graf yonlu mu yonsuz mu?
		for(int j=0;j<matris_boyutu;j++){
			if(matris[i][j]!=matris[j][i]){
				kontrol=0;
			}
		}
	}
	if(kontrol==1){ //Graf simetriktir.
		printf("Graf yonsuzdur!\n");	
	}
	else{ //Graf simetrik degildir.
		printf("Graf yonludur!\n");
	}
	printf("\n");
	for(int i=0;i<matris_boyutu;i++){  //Tam bagli graf mi degil mi?
		kontrol1=0;
		for(int j=0;j<matris_boyutu;j++){
			if(matris[i][j]!=0){
				kontrol1++;
			}
		}
		if(matris[i][i]==0){
			kontrol1++;
		}
		if(kontrol1!=matris_boyutu){
			kontrol1=0;
			break;
		}
	}
	if(kontrol1==0){
		printf("Tam bagli graf degildir!\n");
	}
	else{
		printf("Tam bagli graftir!\n");
	}
	printf("\n");
	Menu();
}

int main(){
	Menu();
}
