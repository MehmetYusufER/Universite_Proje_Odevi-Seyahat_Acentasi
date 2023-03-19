#include <stdio.h>


char *filename = "Acenta.txt";
char *t_filename = "temp.txt";


void arac_kayit();
void arac_duzenleme();
void arac_listeleme();
void arac_sorgulama();
void arac_silme();

unsigned int isDigit(char c);
int string_lenght(char metin[]);
int kontrol(char plaka[]);		
void new_line(char arr[]);

struct pl{
	char sehir_kodu[10];
	char harf_kodu[10];
	char seri_kodu[10];
}plaka;

struct bilgi{
	char plaka[50];
	char marka[50];
	char sofor_adi[50];
	char sofor_soyadi[50];
	int model;
	float motor_hacmi;
	int yolcu_kapasitesi;
}arac;

int main(){

	int islem , exit = 0;

	printf("Hosgeldiniz!");
	printf("\nYapmak istediginiz islemi seciniz");
	
	do{	
		printf("\n#####################");
		printf("\n1.Arac Kayit\n2.Arac Duzenleme\n3.Arac Listeleme\n4.Arac Sorgulama\n5.Arac Silme\n6.Cikis\n");
		
		fflush(stdin);
		scanf("%d", &islem);
		
	
		switch(islem){
			case 1: 
				arac_kayit();
				break;
			case 2:	
				arac_duzenleme();
				break;
			case 3:
				arac_listeleme();
				break;
			case 4:
				arac_sorgulama();
				break;
			case 5:
				arac_silme();
				break;
			case 6:
				exit = 1;					
		}		
	}while(exit != 1);

	return 0;
}



void arac_kayit(){
	
	int i = 0, j = 0, adim = 1 , toplam = 0, flag = 1, len = 0;
	char arac_plaka[50];
	char plaka_dizisi[10];
	
	FILE *fptr;
	
	fptr = fopen(filename , "ab"); 
		
	printf("\n###############");
	printf("\nArac Kayit");
	printf("\n\nAracin Plakasini Giriniz: ");

	ITER:
		fflush(stdin);
		fgets(arac_plaka, 50 , stdin);
		
	for(i = 0; i < 10; i++){
		plaka.sehir_kodu[i] = '\0';
		plaka.harf_kodu[i] = '\0';
		plaka.seri_kodu[i] = '\0';
 	}
	
	i = 0;
	j = 0; 	// sehir plaka kodunu takip eder
	adim = 1;

	while(arac_plaka[i] != '\0'){	
		if(arac_plaka[i] == ' '){
			i++;
			continue;
		}
		if(adim == 1){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0 || isDigit(arac_plaka[i]) != -1 && j ==2){	 //yersiz sayilarý tespit eder
				printf("Hatali plaka! Lutfen tekrar griniz: ");
				goto ITER;		
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){ 										//yersiz harfleri tespit eder
				adim++;
				j = 0;
			}
			else{
				plaka.sehir_kodu[j] = arac_plaka[i];
				j++;
			}
		}				
		if(adim == 2){
		
			if(isDigit(arac_plaka[i]) != -1 && j == 0){				
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) != -1 && j >= 1){				   
				adim++;	
				j = 0;
			}
			else{
				plaka.harf_kodu[j] = arac_plaka[i];
				j++;
			}	
		}	
		if(adim == 3){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0){
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){
				j = 0;
			}
			else{
				plaka.seri_kodu[j] = arac_plaka[i];
				j++;
			}
		}
		i++;
	}



	if(kontrol(arac_plaka) != 0){
		printf("Arac zaten mevcut! Lutfen tekrar giriniz: ");
		goto ITER;
	}

	len = string_lenght(arac_plaka);
	
	for(i = 0; i < len; i++){
		arac.plaka[i] = arac_plaka[i];
	}

	arac.plaka[len] = '\0';
	

	printf("\nAracin markasi: ");
	fgets(arac.marka, 50 , stdin);
	
	printf("\nArac soforunun adi:");
	fgets(arac.sofor_adi, 50 , stdin);
	
	printf("\nArac soforunun soyadi:");	
	fgets(arac.sofor_soyadi, 50 , stdin);
	
	printf("\nAracin Modeli: ");
	scanf(" %d", &arac.model);
	
	printf("\nAracin silindir hacmi: ");
	scanf(" %f", &arac.motor_hacmi);
	
	printf("\nArac yolcu kapasitesi: ");
	scanf(" %d", &arac.yolcu_kapasitesi);

	
	new_line(arac.plaka);
	new_line(arac.marka);
	new_line(arac.sofor_adi);
	new_line(arac.sofor_soyadi);
	
	
	printf("Plaka: %s\nMarka: %s\nSofor Adi: %s\nSofor Soyadi: %s\nModel: %d\nMotor Hacmi: %f\nYolcu Kapasitesi: %d\n" ,arac.plaka, arac.marka, arac.sofor_adi, arac.sofor_soyadi, arac.model, arac.motor_hacmi, arac.yolcu_kapasitesi);
	
	fwrite(&arac, sizeof(struct bilgi), 1, fptr);

	

	fclose(fptr);
}
 
 


void arac_duzenleme(){

	FILE *fptr;
	FILE *fptr2;
	

	int i = 0 , j = 0 , adim = 1, c = 0;
	char arac_plaka[50];
	
	fptr = fopen(filename, "rb+");
	
	printf("#############\n");
	printf("Arac Duzenleme");
	printf("\nAracin plakasini giriniz: ");


	ITER:
		fflush(stdin);
		fgets(arac_plaka, 50, stdin);
	
	i = 0;
	j = 0; 	// sehir plaka kodunu takip eder

	while(arac_plaka[i] != '\0'){
		
		if(arac_plaka[i] == ' '){
			i++;
			continue;
		}
		
		if(adim == 1){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0 || isDigit(arac_plaka[i]) != -1 && j ==2){						 //yersiz sayilarý tespit eder
				printf("Hatali plaka! Lutfen tekrar griniz: ");
				goto ITER;		
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){ 				//yersiz harfleri tespit eder
				adim++;
				j = 0;
			}
			else{
				plaka.sehir_kodu[j] = arac_plaka[i];
				j++;
			}
		}			
		
		if(adim == 2){
		
			if(isDigit(arac_plaka[i]) != -1 && j == 0){				
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) != -1 && j >= 1){				   
				adim++;	
				j = 0;
			}
			else{
				plaka.harf_kodu[j] = arac_plaka[i];
				j++;
			}	
		}
		
		if(adim == 3){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0){
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){
				j = 0;
			}
			else{
				plaka.seri_kodu[j] = arac_plaka[i];
				j++;
			}
		}
		
		
		i++;
	}

	int select = 0;
	int exit1 = 0;
	int flag = 1;
	
	fseek(fptr, 0, SEEK_SET);
	c = kontrol(arac_plaka);
	
		if(c != 0){
			
			do{		
			printf("\n1.Plaka: %s\n2.Marka: %s\n3.Sofor Adi: %s\n4.Sofor Soyadi: %s\n5.Model: %d\n6.Motor Hacmi: %f\n7.Yolcu Kapasitesi: %d\n8.Tamam\n" ,arac.plaka, arac.marka, arac.sofor_adi, arac.sofor_soyadi, arac.model, arac.motor_hacmi, arac.yolcu_kapasitesi);
			printf("\nDegistermek istediginiz bolumu seciniz: ");

			fflush(stdin);
			scanf("%d", &select);
		
			switch(select){
				case 1: 
					printf("###############\nPlaka Giriniz\n");
					fflush(stdin);
					fgets(arac.plaka, 50, stdin);
					new_line(arac.plaka);
					break;
				case 2:	
					printf("###############\nMarka Giriniz\n");
					fflush(stdin);
					fgets(arac.marka, 50, stdin);
					new_line(arac.marka);
					break;
				case 3:
					printf("###############\nSofor Adi Giriniz\n");
					fflush(stdin);
					fgets(arac.sofor_adi, 50, stdin);
					new_line(arac.sofor_adi);
					break;
				case 4:
					printf("###############\nSofor Soyadi Giriniz\n");
					fflush(stdin);
					fgets(arac.sofor_soyadi, 50, stdin);
					new_line(arac.sofor_soyadi);
					break;
				case 5:
					printf("###############\nModeli Giriniz\n");
					fflush(stdin);
					scanf("%d", &arac.model);
					break;
				case 6:
					printf("###############\nMotor Hacmi Giriniz\n");
					fflush(stdin);
					scanf("%f", arac.motor_hacmi);
					break;
				case 7:
					printf("###############\nYolcu Kapasitesi Giriniz\n");
					fflush(stdin);
					scanf("%d", arac.yolcu_kapasitesi);
					break;
				case 8:
					exit1 = 1;
					break;	
				}
			}while(exit1 != 1);
		
		rewind(fptr);
		fseek(fptr, (c - 1) * sizeof(arac), SEEK_SET);
		fwrite(&arac, sizeof(arac), 1, fptr);
		
		printf("\n#######\nPlaka: %s\nMarka: %s\nSofor Adi: %s\nSofor Soyadi: %s\nModel: %d\nMotor Hacmi: %f\nYolcu Kapasitesi: %d\n" ,arac.plaka, arac.marka, arac.sofor_adi, arac.sofor_soyadi, arac.model, arac.motor_hacmi, arac.yolcu_kapasitesi);
		}
		else{
			printf("Arac mevcut degil! Lutfen tekrar giriniz: ");
			goto ITER;	
		}


	fclose(fptr);
}


void arac_listeleme(){
	
	FILE *fptr;
	
	int i = 0, flag = 1, found = 0;
	int c;
	char arac_marka[50];
	
	fptr = fopen(filename, "rb");
	
	if(fptr == NULL){
		printf("Error opening file!");
		goto MAIN;
	}
	else{
		printf("\n##############\nArac Listeleme\n\n");
	}

	printf("Arac Markasini Giriniz: ");
	
	fflush(stdin);
	fgets(arac_marka, 50, stdin);
	
	new_line(arac_marka);
	
	fseek(fptr, 0,SEEK_SET);
	
	while(fread(&arac, sizeof(arac), 1, fptr) == 1){
		i = 0;
		flag = 1;
		if(string_lenght(arac_marka) == string_lenght(arac.marka)){
			while(arac_marka[i] != '\0' && flag != 0){
				if(arac.marka[i] != arac_marka[i]){
					flag = 0;
				}	
			i++;
			}
			if(flag != 0){
				printf("Plaka: %s\nMarka: %s\nSofor Adi: %s\nSoyadi: %s\nModeli: %d\nMotor Hacmi: %f\nYolcu Kapasitesi: %d\n\n" ,arac.plaka, arac.marka, arac.sofor_adi, arac.sofor_soyadi, arac.model, arac.motor_hacmi, arac.yolcu_kapasitesi);
				found = 1;				
			}		
		}
	}
	
	if(found == 0){
		printf("%s markaya sahip arac yok!", arac_marka);
	}
	
	
MAIN:	
	fclose(fptr);
}


void arac_sorgulama(){

	FILE *fptr;
	
	int i = 0, j = 0, adim = 1 , toplam = 0, flag = 1, len = 0, counter = 0, found = 0;
	char arac_plaka[50];
	
	fptr = fopen(filename , "rb");
	
	printf("\n##############\nArac Sorgulama\n");
	printf("Plakayi Giriniz: ");
	
ITER:	
	fflush(stdin);
	fgets(arac_plaka, 50, stdin);
	
	i = 0;
	j = 0; 	// sehir plaka kodunu takip eder
	adim = 1;

	while(arac_plaka[i] != '\0'){
		
		if(arac_plaka[i] == ' '){
			i++;
			continue;
		}
		
		if(adim == 1){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0 || isDigit(arac_plaka[i]) != -1 && j ==2){						 //yersiz sayilarý tespit eder
				printf("Hatali plaka! Lutfen tekrar griniz: ");
				goto ITER;		
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){ 				//yersiz harfleri tespit eder
				adim++;
				j = 0;
			}
			else{
				plaka.sehir_kodu[j] = arac_plaka[i];
				j++;
			}
		}			
		
		if(adim == 2){
		
			if(isDigit(arac_plaka[i]) != -1 && j == 0){				
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) != -1 && j >= 1){				   
				adim++;	
				j = 0;
			}
			else{
				plaka.harf_kodu[j] = arac_plaka[i];
				j++;
			}	
		}
		
		if(adim == 3){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0){
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){
				j = 0;
			}
			else{
				plaka.seri_kodu[j] = arac_plaka[i];
				j++;
			}
		}
		
		
		i++;
	}
	
 	new_line(arac_plaka);
	
	fseek(fptr, 0, SEEK_SET);
	while(fread(&arac, sizeof(arac), 1, fptr) == 1){
		counter++;
		i = 0;
		flag = 1;
		if(string_lenght(arac_plaka) == string_lenght(arac.plaka)){
			while(arac_plaka[i] != '\0' && flag != 0){
				if(arac.plaka[i] != arac_plaka[i]){
					flag = 0;
				}	
			i++;
			}
			if(flag != 0){
				printf("Plaka Sistemde Mevcut");
				printf("Plaka: %s\nMarka: %s\nSofor Adi: %s\nSofor Soyadi: %s\nModel: %d\nMotor Hacmi: %f\nYolcu Kapasitesi: %d\n" ,arac.plaka, arac.marka, arac.sofor_adi, arac.sofor_soyadi, arac.model, arac.motor_hacmi, arac.yolcu_kapasitesi);
				found = 1;
			}		
		}
	}
	
	if(found != 0){
		printf("Plaka Sistemde Mevcut Degil!");
	}
		
	
	fclose(fptr);	
}


void arac_silme(){
	
	FILE *fptr;
	FILE *temp_fptr;
		
	int found = 0 , i = 0, j = 0, adim = 1, flag = 0, s = 0, c, re;
	char arac_plaka[50];

	fptr = fopen(filename, "rb+");
	temp_fptr = fopen(t_filename, "wb");
	
	if(fptr == NULL && temp_fptr == NULL){
		printf("Error openin file!");
		flag = 1;
		goto MAIN;
	}
		
	printf("\n##############\nArac Silme\n");
	printf("Silinecek olan plakayi Giriniz: ");

ITER:		
	fflush(stdin);
	fgets(arac_plaka, 50, stdin);	
	
	i = 0;
	j = 0; 	// sehir plaka kodunu takip eder

	while(arac_plaka[i] != '\0'){
		
		if(arac_plaka[i] == ' '){
			i++;
			continue;
		}
		
		if(adim == 1){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0 || isDigit(arac_plaka[i]) != -1 && j ==2){						 //yersiz sayilarý tespit eder
				printf("Hatali plaka! Lutfen tekrar griniz: ");
				goto ITER;		
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){ 				//yersiz harfleri tespit eder
				adim++;
				j = 0;
			}
			else{
				plaka.sehir_kodu[j] = arac_plaka[i];
				j++;
			}
		}			
		
		if(adim == 2){
		
			if(isDigit(arac_plaka[i]) != -1 && j == 0){				
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) != -1 && j >= 1){				   
				adim++;	
				j = 0;
			}
			else{
				plaka.harf_kodu[j] = arac_plaka[i];
				j++;
			}	
		}
		
		if(adim == 3){
			
			if(isDigit(arac_plaka[i]) == -1 && j == 0){
				printf("Hatali plaka! Lutfen tekrar giriniz: ");
				goto ITER;
			}
			else if(isDigit(arac_plaka[i]) == -1 && j >= 1){
				j = 0;
			}
			else{
				plaka.seri_kodu[j] = arac_plaka[i];
				j++;
			}
		}
		 
		
		i++;
	}
	
	c = kontrol(arac_plaka);
	
	fseek(fptr, 0, SEEK_SET);
	
	if(c != 0){
		
		while(fread(&arac, sizeof(arac), 1, fptr) == 1){
			s++;
			printf("s:%d c:%d  ",s ,c);
			if(s == c){
				printf("\n%s plakali arac sistemden basariyla silindi!\n", arac.plaka);
				found = 1;
			}
			else{
				fwrite(&arac, sizeof(arac), 1, temp_fptr);
			}
		}
				
		if(found != 1){
			printf("\n%s plakali arac silinirken hata olustu!\n", arac.plaka);
		}
				
	}
	else{
		printf("\nPlaka mevcut degil! Lutfen tekrar giriniz: ");
		goto ITER;
	}

MAIN:	
	fclose(fptr);
	fclose(temp_fptr);
	
	if(flag != 1){
		remove(filename);
		rename(t_filename, filename);
	}
	
}


int kontrol(char arac_plaka[]){
	
	FILE *fptr;
	
	int i = 0, j = 0, adim = 1 , toplam = 0, flag = 1, len = 0, counter = 0;
	
	fptr = fopen(filename , "rb");
	
 	new_line(arac_plaka);
	
	fseek(fptr, 0, SEEK_SET);
	while(fread(&arac, sizeof(arac), 1, fptr) == 1){
		counter++;
		i = 0;
		flag = 1;
		if(string_lenght(arac_plaka) == string_lenght(arac.plaka)){
			while(arac_plaka[i] != '\0' && flag != 0){
				if(arac.plaka[i] != arac_plaka[i]){
					flag = 0;
				}	
			i++;
			}
			if(flag != 0){
				return counter;		//plaka var
			}		
		}
	}
	
	return 0;	//plaka yok
}


int string_lenght(char metin[]){
	
	int i = 0;
	
	
	while(metin[i] != '\0'){
		i++;
	}
	
	return i;
}


void new_line(char arr[]){
	
	int i = 0 , ln;

	ln = string_lenght(arr) - 1;	//AB\n\0   A: 0   B: 1   \n: 2   \0:  3     strlen() = 3-1=2 
	
	if (*arr && arr[ln] == '\n'){
		arr[ln] = '\0';
	} 
}

unsigned int isDigit(char c){
	
	switch(c){
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;		
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case '0':
			return 0;
		default:
			return -1;						
	}	
}

