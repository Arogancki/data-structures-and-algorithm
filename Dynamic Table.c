//SDIZO IS1 211A LAB01
//Artur Ziemba
//aziemba@wi.zut.edu.pl


#include <time.h>
#include <stdio.h>

// struktura
struct Lab1
{
	int liczba;
	char znak;
	double przecinek;
};

struct Lab1** losowanie(int ilosc_struktur)
{
    struct Lab1 **tablica;
	tablica = (struct Lab1**)malloc(ilosc_struktur*sizeof(struct Lab1));
	srand(time(NULL));
	int count;
	for (count = 0; count < ilosc_struktur; count++)
	{
		tablica[count] = (struct Lab1*)malloc(sizeof(struct Lab1));
		tablica[count]->liczba = (((rand()*rand()) + (rand() % 2)) % 10000001);
		tablica[count]->przecinek = 8;
		tablica[count]->znak = (rand() % 26) + 97;
	}
	return(tablica);
}

struct Lab1** sortowanie(struct Lab1**tablica, int ilosc_struktur)
{
	int i, j, najmniejszy;
	struct Lab1 *temp;
	// sortowanie przez wybieranie
	for (i = 0; i < ilosc_struktur; i++)
	{
		najmniejszy = i;
		for (j = i + 1; j < ilosc_struktur; j++)
			if (tablica[j]->liczba < tablica[najmniejszy]->liczba)
				najmniejszy = j;
		// sprawdzenie i zamiana miejsc
		if (i != najmniejszy)
		{
			temp = tablica[i];
			tablica[i] = tablica[najmniejszy];
			tablica[najmniejszy] = temp;
		}
	}
	return(tablica);
}

int szukanie_znaku(struct Lab1**tablica, int ilosc_struktur, char szukany_znak)
{
	int ilosc_znakow = 0, count;
	for (count = 0; count < ilosc_struktur; count++)
	{
		if (tablica[count]->znak == szukany_znak)
		{
			ilosc_znakow++;
		}
	}
	return(ilosc_znakow);
}

void kasowanie(struct Lab1**tablica, int ilosc_struktur)
{
	int count;
	for (count = 0; count < ilosc_struktur; count++)
		free(tablica[count]);
	free(tablica);
}

int main()
{
    // ladowanie pliku
	int ilosc_struktur;
	char szukany_znak;
	FILE *file;
	file= fopen("inlab01.txt", "r");
	if (file == NULL)
	{
		return -1;
	}
	fscanf(file, "%d %c", &ilosc_struktur, &szukany_znak);
	fclose(file);
	// czas start
	clock_t start, stop;
	double czas;
	start = clock();

	// dzialania
    struct Lab1 **tablica;
	tablica = sortowanie(losowanie(ilosc_struktur), ilosc_struktur);
	int znalezione;
	znalezione = szukanie_znaku(tablica, ilosc_struktur, szukany_znak);
	printf("Znaleziono %d poszukiwanych znakow \"%c\" w %d utworzonych strukturach\n", znalezione, szukany_znak, ilosc_struktur);

    // drukowanie struktur.
	// Jesli program ma pytac o drukowanie to zanegowac 1 w ponizszym if'ie
	if (1)
	{
		//printf("Jesli chcesz wydrukowac pierwsze ");
		if (ilosc_struktur <= 30)
			printf("%d", ilosc_struktur);
		else
			printf("30");
		//printf(" struktur podaj \"p\"\n");
		char p='p';
		//scanf("%c", &p, 1);
		printf("\n");
		int i = 1;
		getchar();
		while ((p == 80 || p == 112) && i <= ilosc_struktur)
		{

			printf("Struktura nr %d.\n\tliczba naturalna to \"%d\"\n\t\liczba wymierna to \"%f\"\n\tznak to \"%c\"\n\n", i, tablica[i - 1]->liczba, tablica[i - 1]->przecinek, tablica[i - 1]->znak);

		    if (i % 30 == 0)
			{
				if (i != ilosc_struktur)
				{
					//printf("Jesli chcesz wydrukowac ");
					if (i + 30 > ilosc_struktur)
						printf("%d", ilosc_struktur - i);
					else
						printf("30");
					//printf(" kolejnych struktur podaj \"p\"\n");
					//scanf("%c", &p, 1);
					printf("\n");
				}
			}
			i++;
		}
	}

    // kasowanie struktury
	kasowanie(tablica, ilosc_struktur);

	//czas stop
	stop = clock();
	czas = (double)(stop - start);
	printf("czas = %f\n", czas);
}
