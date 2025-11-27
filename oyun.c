/* Visual Studio ve bazi derleyicilerdeki scanf hatasini kapatir */
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h> // rand() ve srand() icin
#include <time.h>   // time() icin
#include <ctype.h>  // toupper() icin

int main() {
    /* [cite: 1-5] Rastgele sayi uretimi icin cekirdek */
    srand((unsigned int)time(0));

    /* [cite: 22-26] Durum Degiskenleri */
    int saglik = 100;
    int enerji = 100;
    int yemek = 0;
    int siginak = 0; /* 0: Yok, 1: Var */
    
    char komut;
    int oyunDevam = 1;
    
    /* Degiskenleri en basta tanimlamak (C89 uyumlulugu icin) */
    int i; 
    int hasar;
    int girilenSifre;
    int gercekSifre = 1234;
    int sans;
    int siginakSans;
    int sonuc; /* scanf kontrolu icin */

    printf("--- KARAKTER TABANLI HAYATTA KALMA SIMULATORU ---\n");
    printf("Komutlar: [A]vlan, [S]iginak, [E]nvanter, [R]Dinlen, [F]Tehlike, [P]Sifre, [X]Cikis\n");
    printf("----------------------------------------------------------\n");

    /* [cite: 7, 19] OYUN DONGUSU (DO-WHILE) */
    do {
        printf("\nNe yapmak istersin? (Komut giriniz): ");
        /* Bosluk birakmak enter tusunun tamponda kalmasini engeller */
        scanf(" %c", &komut); 
        komut = toupper(komut); /* Kucuk harfi buyuge cevir */

        printf("\n> ISLEM SONUCU:\n"); 

        /* [cite: 9] KOMUT SISTEMI (SWITCH-CASE) */
        switch (komut) {
            
            case 'A': /* Avlanma */
                /*  Aritmetik ve Mantiksal Operatorler (&&, ||) */
                if (enerji >= 15) {
                    printf("Avlanmaya ciktin... ");
                    enerji -= 15; /* Enerji harca */
                    sans = rand() % 100 + 1;

                    /* HOCANIN ISTEDIGI MANTIKSAL OPERATORLER (&&, ||) BURADA: */
                    /* Eger sans 50'den buyukse VEYA (||) enerji 80'den fazlaysa (dincksen) avlanma basarili */
                    if (sans > 50 || (enerji > 80 && sans > 30)) { 
                        printf("Basarili! Guclu hissettigin icin av yakaladin (+1 Yemek).\n");
                        yemek++;
                    } 
                    /* Eger sans cok dusukse (20 alti) VE (&&) siginagin yoksa yaralanirsin */
                    else if (sans <= 20 && siginak == 0) { 
                        printf("Dikkat! Korunmasiz oldugun icin vahsi hayvan saldirdi (-15 Saglik).\n");
                        saglik -= 15;
                    } 
                    else {
                        printf("Hicbir sey bulamadan bos dondun.\n");
                    }
                } else {
                    printf("Avlanmak icin yeterli enerjin yok! (Gereken: 15)\n");
                }
                break;

            case 'S': /* Siginak Arama */
                /* [cite: 14] IF-ELSE Yapilari */
                if (siginak == 1) {
                    printf("Zaten guvenli bir siginagin var.\n");
                } else {
                    if (enerji >= 10) {
                        enerji -= 10;
                        siginakSans = rand() % 100;
                        /* Basit bir ihtimal kontrolu */
                        if (siginakSans > 50) {
                            siginak = 1;
                            printf("Tebrikler! Guvenli bir siginak buldun (Durum: 1).\n");
                        } else {
                            printf("Uygun bir yer bulamadin.\n");
                        }
                    } else {
                        printf("Aramak icin cok yorgunsun.\n");
                    }
                }
                break;

            case 'E': /* Envanter */
                printf("Cantanizi kontrol ediyorsunuz...\n");
                /* Durum raporu asagida otomatik yazilacak */
                break;

            case 'R': /* Dinlenme */
                printf("Dinleniyorsun... ");
                /* [cite: 14] Aritmetik islemlerle saglik/enerji artisi */
                if (siginak == 1) {
                    enerji += 30;
                    saglik += 10;
                    printf("Siginakta guvende uyudun (+30 Enerji, +10 Saglik).\n");
                } else {
                    enerji += 15;
                    printf("Disarida riskli uyku (+15 Enerji).\n");
                }
                
                /* 100 sinirini asmamasi icin kontrol */
                if (enerji > 100) enerji = 100;
                if (saglik > 100) saglik = 100;
                break;

            case 'F': /* [cite: 16-18] Tehlike Dalgasi (FOR Dongusu) */
                printf("!!! TEHLIKE DALGASI BASLIYOR !!!\n");
                for (i = 1; i <= 3; i++) {
                    hasar = rand() % 10 + 5; 
                    printf("%d. Dalga: Saldiri! %d hasar aldin.\n", i, hasar);
                    saglik -= hasar;
                    /* Olurse donguden cik */
                    if (saglik <= 0) break;
                }
                break;

            case 'P': /* [cite: 19-20] Sifreli Gecis (DO-WHILE) */
                printf("Kilitli kapi. Sifreyi cozmelisin.\n");
                do {
                    printf("Sifreyi giriniz (1234): ");
                    /* Sayi disinda harf girilirse sonsuz donguyu onlemek icin kontrol: */
                    if (scanf("%d", &girilenSifre) != 1) {
                        printf("Hatali giris! Lutfen sayi giriniz.\n");
                        /* Tamponu temizle (harfleri yut) */
                        while(getchar() != '\n'); 
                        girilenSifre = 0; /* Dongu devam etsin diye yanlis deger ata */
                        continue;
                    }

                    if (girilenSifre != gercekSifre) {
                        printf("Hatali sifre! Tekrar dene.\n");
                    }
                } while (girilenSifre != gercekSifre);
                
                printf("Sifre Dogru! Kapi acildi (+2 Yemek).\n");
                yemek += 2;
                break;

            case 'X': /* Cikis */
                printf("Oyundan cikiliyor...\n");
                oyunDevam = 0;
                break;

            default:
                printf("Gecersiz komut! [A, S, E, R, F, P, X] kullanin.\n");
        }

        /* Canin eksiye dusmesini gorsel olarak duzelt (Program mantigi icin degil, ekran icin) */
        if (saglik < 0) saglik = 0;

        /* --- DURUMU HER TUR GOSTER --- */
        if (oyunDevam == 1 && komut != 'X') {
            printf("---------------------------------\n");
            printf("[ DURUM RAPORU ]\n");
            printf(" Saglik : %-3d  |  Yemek Sayisi: %d\n", saglik, yemek);
            /* Siginak durumu 1 ise VAR, 0 ise YOK yazar */
            printf(" Enerji : %-3d  |  Siginak     : %s\n", enerji, siginak ? "VAR (1)" : "YOK (0)");
            printf("---------------------------------\n");
        }

        /* Oyun Sonu Kontrolü */
        if (saglik <= 0) {
            printf("\n--- OYUN BITTI ---\n");
            printf("Hayatta kalamadin. Sagligin tukendi.\n");
            oyunDevam = 0;
        }
    } while (oyunDevam == 1);

    printf("\nCikmak icin Enter'a basiniz...");
    /* Pencerenin hemen kapanmamasi icin */
    getchar(); 
    getchar();

    return 0;
}
