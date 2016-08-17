// finding the shortest path
// Dijkstra's algorithm
// vs
// Astar algorithm
// by Artur Ziemba

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <vector>
#include "inlab07.h"

class Graf
{
	// zmienne
	int Odleglosc[39][39];
	std::string Miasta[39];
	int Wspolrzedne_Miast[39][2];
	int Wspolrzedne_kraju[20][2];

	// metody
	std::vector <int> Incydent(int); // zwraca stopien wierzcholka, przyjmuje indeks w tablicy
	int Check(std::string); // zwraca indeks tablicy (0/39) -1 w przypadku braku
	bool Connected(int, int);
	int heura(int,int);

public:
	Graf::Graf();
	Graf::~Graf();
	std::string Dijkstra(std::string, std::string); //
	std::string Astar(std::string, std::string); //
};

Graf::Graf()
{
	for (int i = 0; i < 39; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			if (j < 2)
			{
				Wspolrzedne_Miast[i][j] = miasta[i][j];
				if (i < 20)
					Wspolrzedne_kraju[i][j] = polska[i][j];
			}
			Odleglosc[i][j] = distances[i][j];
		}
		Miasta[i] = miastoLabel[i];
	}
}

Graf::~Graf() {}

std::vector <int> Graf::Incydent(int index)
{
	std::vector <int> indexs;
	for (int i = 0; i < 39; i++)
		if (Odleglosc[index][i] != (-10) && Odleglosc[index][i] != 0)
			indexs.push_back(i);
	return(indexs);
}

int Graf::Check(std::string name)
{
	for (int i = 0; i < 39; i++)
		if (Miasta[i] == name)
			return(i);
	return(-1);
}

bool Graf::Connected(int x, int y)
{
	if (Odleglosc[x][y] != (-10))
		return(true);
	return(false);
}

int Graf::heura(int index_start, int index_koniec)
{
	int y = sqrt(pow((Wspolrzedne_Miast[index_koniec][0] - Wspolrzedne_Miast[index_start][0]), 2)
		+ pow((Wspolrzedne_Miast[index_koniec][1] - Wspolrzedne_Miast[index_start][1]), 2));
	return(y);
}

std::string Graf::Dijkstra(std::string from, std::string destination)
{
	// sprawdzenie poprawnosci danych
	int index_from = Check(from);
	if (index_from == (-1))
		return("Miasto 1 nie rozpoznane!\n");
	int index_destination = Check(destination);
	if (index_destination == (-1))
		return("Miasto 2 nie rozpoznane!\n");

	bool S[39]; // odwiedzone
	for (int i = 0; i < 39; i++)
		S[i] = false;
	int D[39]; // waga krawedzi (sumy)
	int P[39]; // z ktorego sie znalazlem (poprzedni)
	S[index_from] = true;
	D[index_from] = 0;
	for (int i = 0; i < 39;i++)
	{
		if (S[i] == 0)
		{
			if (Connected(index_from, i))
			{
				D[i] = Odleglosc[i][index_from];
				P[i] = index_from;
			}
			else
			{
				D[i] = (-10); // reprezetuje nieskaczonosc
				P[i] = 0;
			}
		}
	}

	bool koniec = 0;
	while (!koniec)
	{
			int min = 0;
			int index_min = 0;
			for (int j = 0; j < 39; j++)
			{
				if (S[j] == 0)
				{
					if ((D[j] <= min && D[j] != (-10)) || (min==0 && D[j] != (-10)) )
					{
						min = D[j];
						index_min = j;
					}
				}
			}
			S[index_min] = 1;
			std::vector <int> Incydentne = Incydent(index_min);
			for (int j = 0; j < Incydentne.size(); j++)
			{
				if (S[Incydentne[j]] == 0)
				{
					if (D[index_min] + Odleglosc[index_min][Incydentne[j]] < D[Incydentne[j]] || D[Incydentne[j]] == (-10))
					{
						P[Incydentne[j]] = index_min;
						D[Incydentne[j]] = D[index_min] + Odleglosc[index_min][Incydentne[j]];
					}
				}
			}
			koniec = 1;
			for (int i = 0; i < 39;i++)
			{
				if (S[i]==0)
				{
					koniec = 0;
				}
			}
	}
	return("Najkrotsza droga " + from + " - " + destination + " to " + std::to_string(D[index_destination]));
}

std::string Graf::Astar(std::string from, std::string destination)
{
	// sprawdzenie poprawnosci danych
	int index_from = Check(from);
	if (index_from == (-1))
		return("Miasto 1 nie rozpoznane!\n");
	int index_destination = Check(destination);
	if (index_destination == (-1))
		return("Miasto 2 nie rozpoznane!\n");


	bool OL[39]; // wymagaja rozpatrzenia
	bool CL[39]; // nie wymagaja rozpatrzenia
	for (int i = 0; i < 39;i++)
	{
		OL[i] = false;
		CL[i] = false;
	}
	OL[index_from]=1;

	int g[39]; // odleglosci
	int h[39];// odleglosc w lini prostej
	int f[39]; // wartosci funkcji (prawdopodobne najkrotsze sciezki
	for (int i = 0; i < 39; i++)
	{
		g[i] = Odleglosc[index_from][i];
		h[i] = heura(i,index_destination);
		if (g[i] == (-10))
			f[i] = (-10);
		else
			f[i]=g[i]+h[i];
	}

	bool koniec = 0;
	while (!koniec)
	{
		int min =(-10);
		int index_min = 0;
		for (int i = 0; i < 39; i++)
		{
			if (OL[i]==1)
			{
				if (f[i]!= (-10))
				{
					if (min == (-10) || min > f[i])
					{
						min = f[i];
						index_min = i;
					}
				}
			}
		}


		if (index_min ==index_destination)
			return("Najkrotsza droga " + from + " - " + destination + " to " + std::to_string(g[index_min]));
		
		OL[index_min] = 0;
		CL[index_min]=1;

		std::vector <int> Incydentne = Incydent(index_min);
		for (int y = 0; y < Incydentne.size();y++)
		{
			if (CL[Incydentne[y]]==1) // sasiad zostanie rozpatrzony "sasiada"  w CL
				continue;

				int temp_g = g[index_min] + Odleglosc[index_min][Incydentne[y]]; // nigdy -10
				bool temp_better = false;

				
				if (!OL[Incydentne[y]]) // nie ma "sasiada"  w OL
				{
					OL[Incydentne[y]]=true;
					temp_better = true;
				}
				else
				{
					if (temp_g < g[Incydentne[y]] || g[Incydentne[y]] == (-10))
					{
						temp_better = true; // mamy mniejsza droge niz aktualna
					}
				}
				if (temp_better == true)
				{
					g[Incydentne[y]] = temp_g;
					f[Incydentne[y]] = g[Incydentne[y]] + h[Incydentne[y]];
				}
		}
		koniec = 1;
		for (int i = 0; i < 39;i++)
		{
			if (OL[i]==1)
			{
				koniec = 0;
				break;
			}
		}
	}
	return("Brak drogi pomiedzy "+from+" i "+destination);
}

void test()
{
	Graf PL2;
	for (int i = 0; i < 39; i++)
	{
		for (int k = 0; k < 39; k++)
		{
			std::cout << "A* - " << PL2.Astar(miastoLabel[i], miastoLabel[k]);
			std::cout << "\nDx - " << PL2.Dijkstra(miastoLabel[i], miastoLabel[k]);
			std::cout << "\n\nA* - " << PL2.Astar(miastoLabel[k], miastoLabel[i]);
			std::cout << "\nDx - " << PL2.Dijkstra(miastoLabel[k], miastoLabel[i]);
			getchar();
			system("cls");
		}
	}
	std::cout << "KONIEC TESTOW\n";
	getchar();
}

void main()
{
	clock_t begin, end; // zmienne czasowe
	int j = 1000; // ilosc powtorek dla petli
	Graf PL; // stworzenie grafu

	//test();

	// DIJKSTRA
	std::cout << "DIJKSTRA\n";
	begin = clock(); //czas start;
	std::cout << PL.Dijkstra("Szczecin", "Krakow") <<std::endl;// oblicz i wypisz najkrótszš ?cie¿kê za pomocš algorytmu Dijkstry pomiêdzy Szczecinem a Krakowem
	end = clock(); // czas stop
	printf("czas wykonywania Dijkstry: Szczecin - Krakow - %.2f\n", (double)(end - begin));	// wypisz czas
	
	std::cout << "\nWykonywanie " << j << " razy\n";
	begin = clock(); // czas start
	for (long int i = 0; i < j; i++) // wykonaj 1.000.000 razy
	{
		PL.Dijkstra("Szczecin", "Przemysl"); // oblicz najkrótszš ?cie¿kê za pomocš algorytmu Dijkstry pomiêdzy Szczecinem a Przemy?lem
		if (i%100000==0)
			std::cout<<i<<std::endl;
	}
		std::cout << PL.Dijkstra("Szczecin", "Przemysl") << std::endl;
	end = clock();	// czas stop
	printf("czas wykonywania Dijkstry: Szczecin - Przemysl %d razy - %.2f\n", j, (double)(end - begin)); // wypisz czas
	std::cout << "\n\n";

	// A*
	std::cout << "A*\n";
	begin = clock(); // czas start
	std::cout << PL.Astar("Szczecin", "Krakow") <<std::endl;// oblicz i wypisz najkrótszš ?cie¿kê za pomocš algorytmu A* pomiêdzy Szczecinem a Krakowem
	end = clock(); // czas stop
	printf("czas wykonywania A*: Szczecin - Krakow - %.2f\n", (double)(end - begin)); // wypisz czas

	std::cout << "\nWykonywanie " << j << " razy\n";
	begin = clock(); // czas start
	for (long int i = 0; i < j; i++) // wykonaj 1.000.000 razy
	{
		PL.Astar("Szczecin", "Przemysl"); // oblicz najkrótszš ?cie¿kê za pomocš algorytmu A* pomiêdzy Szczecinem a Przemy?lem
	if (i%100000==0)
			std::cout<<i<<std::endl;
	}
	std::cout << PL.Astar("Szczecin", "Przemysl") << std::endl;
	end = clock(); // czas stop
	printf("czas wykonywania A*: Szczecin - Przemysl %d razy - %.2f\n", j, (double)(end - begin)); // wypisz czas

	getchar();
}