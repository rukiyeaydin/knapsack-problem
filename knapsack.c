#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int canta(int kapasite, int agirliklar[], int degerler[], int n)
{
    int i, j;
    int onceki[kapasite + 1];
    int suAn[kapasite + 1];

    for (j = 0; j <= kapasite; j++)
    {
    	onceki[j] = 0;
	} 
    for (i = 1; i <= n; i++)
    {
        for (j = 0; j <= kapasite; j++)
        {
            if (agirliklar[i - 1] <= j)
            
                if((degerler[i - 1] + onceki[j - agirliklar[i - 1]]) > onceki[j])
                {
                	suAn[j] = degerler[i - 1] + onceki[j - agirliklar[i - 1]];
				}
				else
				{
					suAn[j] = onceki[j];
				}
            else
                suAn[j] = onceki[j];
        }
        for (j = 0; j <= kapasite; j++)
            onceki[j] = suAn[j];
    }

    return suAn[kapasite];
}


double sure(struct timespec basla, struct timespec bit)
{
    return (double)(bit.tv_sec - basla.tv_sec) + (double)(bit.tv_nsec - basla.tv_nsec) / 1e9;
}

int main()
{
    int kapasite, n = 0, m = 0;
    int *agirliklar = NULL, *degerler = NULL;

    int secim = 0;
    do
    {
        printf("MENU\n");
        printf("Seceneginizi girin..\n");
        printf("1) Yeni knapsack problemi gir:\n");
        printf("2) Cikis\n");

        if (n>0)
        {
            printf("3) Var olan cantaya yeni esya ekle\n");
        }

        scanf("%d", &secim);
        
        if(secim != 3){
        	
		}
        switch (secim)
        {
        case 1:
            printf("Cantanin kapasitesini girin: ");
            scanf("%d", &kapasite);

            printf("Esya sayisini girin: ");
            scanf("%d", &n);

            agirliklar = (int *)malloc(n * sizeof(int));
            degerler = (int *)malloc(n * sizeof(int));

            int i;
            for (i = 0; i < n; i++)
            {
                printf("Esya %d'in agirligini gir: ", i + 1);
                scanf("%d", &agirliklar[i]);
                printf("Esya %d'in degerini gir: ", i + 1);
                scanf("%d", &degerler[i]);
            }

            struct timespec basla, bit;
            clock_gettime(CLOCK_MONOTONIC, &basla); 

            int cantaKapasitesi = canta(kapasite, agirliklar, degerler, n);

            clock_gettime(CLOCK_MONOTONIC, &bit);
            double gecenSure = sure(basla, bit);

            printf("Elde edilebilecek maksimum deger: %d\n", cantaKapasitesi);
            printf("Calisma zamani: %.8f saniye\n\n", gecenSure);

            break;

        case 2:
                printf("Cikis yaptiniz.\n");
                break;
                
        case 3:
	            if(n>0){
		            printf("Kac tane yeni esya eklemek istersiniz? ");
		            scanf("%d", &m);
		
		            if(m > 0) {
		                agirliklar = realloc(agirliklar, (n+m)*sizeof(int));
		                degerler = realloc(degerler, (n+m)*sizeof(int));
		
		                int i;
		                for (i = n; i < n+m; i++) {
		                    printf("Esya %d'in agirligini gir: ", i + 1);
		                    scanf("%d", &agirliklar[i]);
		                    printf("Esya %d'in degerini gir: ", i + 1);
		                    scanf("%d", &degerler[i]);
		                }
		
		                n = n + m;
		            }
		
		            int yeniCantaKapasitesi = canta(kapasite, agirliklar, degerler, n);
		            printf("Elde edilebilecek yeni maksimum deger: %d\n\n", yeniCantaKapasitesi);
		
		            break;
				}
        default:
            printf("Gecersiz bir secim yaptiniz.\n\n");
            break;
        }
    } while (secim != 2);

    free(agirliklar);
    free(degerler);

    return 0;
}
