#include<stdio.h>     //Kullanicidan "sayý[string]" girdisi alan ve ekrana sayi kez string yazdiran program.
#include<conio.h>    // Ornegin 3[e2[ab]] =>   babaebabaebabae
#include<string.h>

#define a 50
#define b 50
#define c 100


int sayi_yigini[a];
char string_yigini[b];
char yigin[c];
int sayi_indisi=-1,string_indisi=-1;

int sayi_yiginina_ekle(char sayi);
int string_yiginina_ekle(int string);
void yigina_ekle(char yigin[]);
int sayi_yiginindan_al();
int string_yiginindan_al();
int yigindan_al();

int sayi_yiginina_ekle(char sayi){
	if(sayi_indisi>=a-1){
		printf("Sayi yigini dolu!");
		return -1;
	}
	else{
		sayi_indisi++;
		sayi_yigini[sayi_indisi]=sayi;
	}

}

int string_yiginina_ekle(int string){
	if(string_indisi>=b-1){
		printf("String yigini dolu!");
		return -1;
	}
	else{
		string_indisi++;
		string_yigini[string_indisi]=string;
		
	}
}
void yigina_ekle(char yigin[]){
	
	char katsayi;
    for(int i=0;yigin[i]!='\0';i++){
		if(yigin[i]>'@' && yigin[i]<'{'){
			string_yiginina_ekle(yigin[i]);
		}
		else{
			katsayi=yigin[i];
			katsayi=katsayi-48;
			sayi_yiginina_ekle(katsayi);
		}	
	}
}

int sayi_yiginindan_al(){
	int cikan;
	if(sayi_indisi==-1){
		printf("Sayi yigini bos!\n");
		return -1;
	}
	else{
		cikan=sayi_yigini[sayi_indisi];
		sayi_indisi--;
		return cikan;
	}
}

int string_yiginindan_al(){
	int cikan;
	if(string_indisi==-1){
		printf("String yigini bos!\n");
		return -1;
	}
	else{
		cikan=string_yigini[string_indisi];
		string_indisi--;
		return cikan;
	}
}

int yigindan_al(){
	int katsayi,kontrol=0,kontrol2=0;
	char metin[200],tam_metin[200],karakter;
	int k=0,d;
	do{
		int i=0;
		kontrol=0;
		while(string_yigini[string_indisi]!='['){
			karakter=string_yiginindan_al();
			if(karakter!=']'){
				metin[i]=karakter;
				i++;
			}				
		}
		katsayi=sayi_yiginindan_al();
		string_indisi--;
		if(kontrol2==0){
			while(kontrol<katsayi){
				for(int j=0;j<i;j++){ 
					tam_metin[k]=metin[j];
					k++;
				}
				kontrol++;
			}
		}
		else{
			kontrol=1;
			for(int j=0;j<i;j++){ 
				tam_metin[k]=metin[j];
				k++;
				d=k;
			}
			while(kontrol<katsayi){
				for(int j=0;j<d;j++){
					tam_metin[k]=tam_metin[j];
					k++;
				}
				kontrol++;
			}
		}
		kontrol2=1;
	}while(string_indisi!=-1);
	
	for(int z=0;z<k;z++){
		printf("%c",tam_metin[z]);
	}
}

int main(){
	
	printf("Yapmak istediginiz islemi giriniz: ");
	gets(yigin);
	yigina_ekle(yigin);	
	yigindan_al();
	
	return 0;
}

