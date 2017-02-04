//SDIZO IS1 211A LAB02
//Artur Ziemba
//aziemba@wi.zut.edu.pl

#include <time.h>
#include <stdio.h>

// struktura
struct Lab2
{
	int klucz;
	double pierwsza, druga, trzecia;
	struct Lab2 *nastepny;
	struct Lab2 *poprzedni;
};

void wypisz_dtu(struct Lab2 *aktualny)
{
   printf("Wcisnij \"enter\" aby rozpoczac drukowanie\n\tod pierwszego do ostatniego elementu\n");
	getchar();
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
        printf("Brak elementow do wyswietlenia\n");
	else
	{
		struct Lab2 *temp = aktualny;
		int count = 1;
        printf("Wezel numer %d wynosi %d\n", count, aktualny->klucz);
		aktualny = aktualny->nastepny;
		count++;
		while (aktualny != temp)
		{
			printf("Wezel numer %d wynosi %d\n", count, aktualny->klucz);
			count++;
			aktualny = aktualny->nastepny;
		}
	}
}

void wypisz_utd(struct Lab2 *aktualny)
{
    printf("Wcisnij \"enter\" aby rozpoczac drukowanie\n\tod ostatniego do pierwszewgo elementu\n");
	getchar();
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
        printf("Brak elementow do wyswietlenia\n");
	else
	{
		struct Lab2 *temp = aktualny;
		aktualny = aktualny->poprzedni;
		int count = 1;
		while (aktualny != temp)
		{
			count++;
			aktualny = aktualny->poprzedni;
		}
		aktualny = aktualny->poprzedni;
		while (aktualny != temp)
		{
			printf("Wezel numer %d wynosi %d\n", count, aktualny->klucz);
			count--;
			aktualny = aktualny->poprzedni;
		}
		printf("Wezel numer %d wynosi %d\n", count, aktualny->klucz);
	}
}

struct Lab2* zainicjuj()
{
	struct Lab2*head = (struct Lab2*)malloc(sizeof(struct Lab2));
	head->nastepny = NULL;
	head->poprzedni = NULL;
	head->klucz = NULL;
	printf("Zainiciowano liste\n");
	return(head);
}

struct Lab2* usun_wszystko(struct Lab2 *aktualny)
{
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
	{
	    printf("Brak elementow do usuniecia\n");
		return(aktualny);
	}
	else
	{
		aktualny->poprzedni->nastepny = NULL;
		while (aktualny->nastepny != NULL)
		{
			aktualny = aktualny->nastepny;
			free(aktualny->poprzedni);
		}
		free(aktualny);
		printf("Usunieto cala liste\n");
		return(NULL);
	}
}

struct Lab2* wstaw_element(struct Lab2 *aktualny, int nowa)
{
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
	{
		if (aktualny == NULL)
		{
		    printf("Najpierw zainiciuj liste\n");
			return(NULL);
		}
		aktualny->klucz = nowa;
		aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->nastepny = aktualny;
		aktualny->poprzedni = aktualny;
		printf("Dodano element Head\n");
		return(aktualny);
	}
	struct Lab2 *temp = aktualny;
	if (aktualny->klucz > nowa)
	{
		aktualny->poprzedni->nastepny = (struct Lab2*)malloc(sizeof(struct Lab2));;
		aktualny->poprzedni->nastepny->nastepny = aktualny;
		aktualny->poprzedni->nastepny->poprzedni = aktualny->poprzedni;
		aktualny->poprzedni = aktualny->poprzedni->nastepny;
		aktualny = aktualny->poprzedni;
		aktualny->klucz = nowa;
		aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		printf("Dodano nowy element Head\n");
		return(aktualny);
	}
	while (1)
	{
		if (nowa == aktualny->klucz)
		{
		    printf("Nie mozna dodac, podana wartosc kluczowa jest juz zajeta\n");
			return(temp);
		}
		if (aktualny->klucz > nowa)
		{
			aktualny->poprzedni->nastepny = (struct Lab2*)malloc(sizeof(struct Lab2));;
			aktualny->poprzedni->nastepny->poprzedni = aktualny->poprzedni;
			aktualny->poprzedni->nastepny->nastepny = aktualny;
			aktualny = aktualny->poprzedni->nastepny;
			aktualny->nastepny->poprzedni = aktualny;
			aktualny->klucz = nowa;
			aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			printf("Element zostal wstawiony miedzy elementy listy\n");
			return(temp);
		}
		if (aktualny->nastepny == temp)
		{
			aktualny->nastepny->poprzedni = (struct Lab2*)malloc(sizeof(struct Lab2));;
			aktualny->nastepny->poprzedni->nastepny = aktualny->nastepny;
			aktualny->nastepny->poprzedni->poprzedni = aktualny;
			aktualny->nastepny = aktualny->nastepny->poprzedni;
			aktualny = aktualny->nastepny;
			aktualny->klucz = nowa;
			aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			printf("Wstawiono na koniec\n");
			aktualny = aktualny->nastepny;
			return(aktualny);
		}
		aktualny = aktualny->nastepny;
	}
}

void wyszukaj(struct Lab2 *aktualny, int szukana)
{
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
		printf("Brak jakichkolwiek elementow\n");
	else
	{
		struct Lab2*temp = aktualny;
		do{
			if (szukana == temp->klucz)
			{
				printf("Znaleziono wezel\n\tWartosci to:\n\t%d\n\t%f\n\t%f\n\t%f\n", temp->klucz, temp->pierwsza, temp->druga, temp->trzecia);
				temp = NULL;
				break;
			}
			temp = temp->nastepny;
		} while (temp != aktualny);
		if (temp == aktualny)
			printf("Wartosc kluczowa %d nie zostala znaleziona\n", szukana);
	}
}

struct Lab2* usun_element(struct Lab2 *aktualny, int szukana)
{
	if ((aktualny->nastepny == NULL && aktualny->poprzedni == NULL) || aktualny == NULL)
	{
		printf("Brak elementow do usuniecia\n");
		return(aktualny);
	}
	if (aktualny == aktualny->nastepny)
	{
		free(aktualny);
		printf("Usunieto jedyny element listy %d\n", szukana);
		return(zainicjuj());
	}
	struct Lab2 *temp = aktualny;
	if (szukana == temp->klucz)
	{
		struct Lab2* tokill = aktualny;
		aktualny = aktualny->nastepny;
		aktualny->poprzedni->poprzedni->nastepny = aktualny;
		aktualny->poprzedni = aktualny->poprzedni->poprzedni;
		printf("Usunieto element %d\n", szukana);
		free(tokill);
		return(aktualny);
	}
	do{
		if (aktualny->klucz == szukana)
		{
			struct Lab2* tokill = aktualny;
			aktualny = aktualny->poprzedni;
			aktualny->nastepny->nastepny->poprzedni = aktualny;
			aktualny->nastepny = aktualny->nastepny->nastepny;
			printf("Usunieto element %d\n", szukana);
			free(tokill);
			return(temp);
		}
		aktualny = aktualny->nastepny;
	} while (aktualny != temp);
	printf("Nie mozna usunac - brak elementu\n");
	return(aktualny);
}

struct Lab2* wstaw_element2(struct Lab2 *aktualny, int nowa)
{
	if (aktualny == NULL || (aktualny->nastepny == NULL && aktualny->poprzedni == NULL))
	{
		aktualny->klucz = nowa;
		aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->nastepny = aktualny;
		aktualny->poprzedni = aktualny;
		return(aktualny);
	}
	struct Lab2 *temp = aktualny;
	if (aktualny->klucz > nowa)
	{
		aktualny->poprzedni->nastepny = (struct Lab2*)malloc(sizeof(struct Lab2));;
		aktualny->poprzedni->nastepny->nastepny = aktualny;
		aktualny->poprzedni->nastepny->poprzedni = aktualny->poprzedni;
		aktualny->poprzedni = aktualny->poprzedni->nastepny;
		aktualny = aktualny->poprzedni;
		aktualny->klucz = nowa;
		aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
		return(aktualny);
	}
	while (1)
	{
		if (nowa == aktualny->klucz)
		{
			int opa = ((((rand()*rand()) + (rand() % 2)) % 100001))+10;
			temp = wstaw_element2(temp, opa);
			return(temp);
		}
		if (aktualny->klucz > nowa)
		{
			aktualny->poprzedni->nastepny = (struct Lab2*)malloc(sizeof(struct Lab2));;
			aktualny->poprzedni->nastepny->poprzedni = aktualny->poprzedni;
			aktualny->poprzedni->nastepny->nastepny = aktualny;
			aktualny = aktualny->poprzedni->nastepny;
			aktualny->nastepny->poprzedni = aktualny;
			aktualny->klucz = nowa;
			aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			return(temp);
		}
		if (aktualny->nastepny == temp)
		{
			aktualny->nastepny->poprzedni = (struct Lab2*)malloc(sizeof(struct Lab2));;
			aktualny->nastepny->poprzedni->nastepny = aktualny->nastepny;
			aktualny->nastepny->poprzedni->poprzedni = aktualny;
			aktualny->nastepny = aktualny->nastepny->poprzedni;
			aktualny = aktualny->nastepny;
			aktualny->klucz = nowa;
			aktualny->pierwsza = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->druga = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny->trzecia = (100001 * ((float)rand() + (rand() % 2) / (float)rand() + (rand() % 2))) + 10;
			aktualny = aktualny->nastepny;
			return(aktualny);
		}
		aktualny = aktualny->nastepny;
	}
}

struct Lab2* wstaw_elementy(struct Lab2 *aktualny, int ilosc_elemetow)
{
	if (aktualny == NULL)
	{
	    printf("Najpierw zainiciuj liste\n");
		return(NULL);
	}
	for (int count = 0; count < ilosc_elemetow; count++)
	{
		int opa = ((((rand()*rand()) + (rand() % 2)) % 100001))+10;
		aktualny = wstaw_element2(aktualny, opa);
	}
	printf("Wstawiono %d elementow\n", ilosc_elemetow);
	return(aktualny);
}

int main()
{
	srand(time(NULL));
	// ladowanie pliku
#pragma warning (disable : 4996)
	FILE* fp = fopen("inlab02.txt", "r");
	if (fp == NULL)
		return -1;
	int ilosc_elemetow, k1, k2, k3, k4;
	fscanf(fp, "%d %d %d %d %d", &ilosc_elemetow, &k1, &k2, &k3, &k4);
	fclose(fp);
	if (ilosc_elemetow <= 0)
		return(-1); //Ilosc struktur nie moze byc mniejsz niz 0
	// czas start
	clock_t begin, end;
	double time_spent;
	begin = clock();
	// dzialania
	struct Lab2 *pointer;
	pointer = zainicjuj();
	pointer = usun_element(pointer, k1); // powinno zwrocic blad
	pointer = wstaw_elementy(pointer, ilosc_elemetow);
	pointer = wstaw_element(pointer, k2);
	pointer = usun_element(pointer, k2);
	wyszukaj(pointer, k3); // moze zwrocic blad
	pointer = wstaw_element(pointer, k4);
	pointer = usun_element(pointer, k4);
	wypisz_dtu(pointer);
	wypisz_utd(pointer);
	usun_wszystko(pointer);
	//czas stop
	end = clock();
	time_spent = (double)(end - begin);
	printf("czas wykonywania - %.2f\n", time_spent);
}

