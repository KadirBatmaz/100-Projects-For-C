#include <stdio.h>
#include <string.h>

struct ogrenci
{
    char isim[50];
    int numara;
    float vize;
    float final;
    float ortalama;
};


int main()
{
    int secim=1, adet = 0,i=0;
    struct ogrenci o[30];
    char silinecek_isim[50];
    FILE *fp = fopen("ogrenciler.txt", "a+");
    if (fp == NULL)
    {
        printf("Dosya acilamadi!\n");
        return 1;
    }
    rewind(fp);//Dosya imlecini en başa alıyormuş düzgün çalışması için
    while (fscanf(fp, "%[^,], %d,%f, %f, %f", o[adet].isim, &o[adet].numara, &o[adet].vize, &o[adet].final, &o[adet].ortalama) != EOF)
    {
        adet++;
    }
    fclose(fp);
    while(secim!=0)
    {   
        switch (secim){
        case 1:
            printf("\n\nMENU\n----------------\n");
            printf("Ogrenci bilgilerini silmek icin 3:\n");
            printf("Ogrenci eklemek icin 2:\n");
            printf("Menuye donmek icin 1:\n");
            printf("Cikmak icin 0:\n");
            printf("Sizin seciminiz:");
            scanf("%d",&secim);
            break;
        case 2:
            printf("Ogrencinin ismini giriniz:");
            while (getchar() != '\n');
            fgets(o[adet].isim, 50, stdin);
            o[adet].isim[strcspn(o[adet].isim, "\n")] = '\0';
            printf("%s adli ogrencinin numarasini giriniz:", o[adet].isim);
            scanf("%d", &o[adet].numara);
            printf("%s adli ogrencinin vizesini giriniz:", o[adet].isim);
            scanf("%f", &o[adet].vize);
            printf("%s adli ogrencinin finalini giriniz:", o[adet].isim);
            scanf("%f", &o[adet].final);
            o[adet].ortalama = o[adet].final * 0.6 + o[adet].vize * 0.4;
            fp = fopen("ogrenciler.txt", "a");
            fprintf(fp, "%s, %d, %.2f, %.2f, %.2f\n", o[adet].isim, o[adet].numara,o[adet].vize, o[adet].final, o[adet].ortalama);
            fclose(fp);
            adet++;
            printf("Ogrenci eklemeye devam etmek icin 2 menuye donmek icin 1:");
            scanf("%d", &secim);
            break;
        case 3:
            printf("Silmek istediginiz kisinin ismini giriniz:");
            while (getchar() != '\n');
            fgets(silinecek_isim, 50, stdin); 
            silinecek_isim[strcspn(silinecek_isim, "\n")] = '\0';
            FILE *gecici = fopen("gecici.txt", "w");
            for (int j = 0; j < adet; j++) {
                if (strcmp(o[j].isim, silinecek_isim) != 0) {
                    fprintf(gecici, "%s, %d, %.2f, %.2f, %.2f\n",
                            o[j].isim, o[j].numara,
                            o[j].vize, o[j].final, o[j].ortalama);
                } else {
                    for (int k = j; k < adet - 1; k++)
                        o[k] = o[k + 1];
                    adet--;
                    j--;
                }
            }
            fclose(gecici);
            remove("ogrenciler.txt");
            rename("gecici.txt","ogrenciler.txt");
           

            printf("Ogrenci silmeye devam etmek icin 3 menuye donmek icin 1:");
            scanf("%d", &secim);
            break;
        }
    }
    return 0;
}