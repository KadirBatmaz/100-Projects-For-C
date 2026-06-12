#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void hesapla( char *soru)
{

    char *ptr= soru;
    char islem;
    double sonuc= strtod(soru,&ptr);
    double sayi;
    while(*ptr!='\0')
    {
        while(*ptr==' ') ptr++;
        islem = *ptr;
        ptr++;
        sayi = strtod(ptr, &ptr);
        switch(islem) {
        case '+': sonuc += sayi; break;
        case '-': sonuc -= sayi; break;
        case '*': sonuc *= sayi; break;
        case '/': if(sayi == 0) printf("Bolen sifir olamaz");
            else sonuc /= sayi;
            break;
        default : printf("Gecersiz islem");
    }
}

printf("= %lf\n", sonuc);
        
    
}

int main()
{
    char soru[100];
    int ch=1;
    
    printf("\n\nWelcome to basic calculator\n");
    printf("---------------------------\n\n\n");
    while(ch==1){
    printf("islem:");
    scanf(" %[^\n]", soru);
    hesapla(soru);

    printf("Devam etmek icin 1 cikmak icin 0:");
    scanf("%d",&ch);
    if (ch==1)
    {
        printf("Yeni ");//Geri donuste tekrar islem yazacagi icin sadece yeni yazdirdim
    }
    }
    return 0;
}