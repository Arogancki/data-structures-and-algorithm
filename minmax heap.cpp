// min-max heap
// by Artur Ziemba

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <sstream> 
#include <vector>
#include <cmath>
#include <math.h> 

double log2( double n )  
{  
    // log(n)/log(2) is log2.  
    return log( n ) / log( 2 );  
}

using namespace std;

class Kopiec
{
	// wartosci
	int klucz;
	int ilosc_elementow;
	Kopiec *left, *right;

	// metody
	string desc();
	void ustawilosc(int);
	void remove_min2();
	void remove_first();
public:
	Kopiec();
	void wstaw(int);
	void wstaw2(int);
	void wstaw_wiele(int); 
	string show_max(); 
	string show_min(); 
	void remove_max();
	void remove_min();
	void remove_all(); 
	void remove_all2();
	string show_4lv(); 
	int GiveHeight();
	string GivePreorder();
	int ile(); 
};

void Kopiec::remove_all2()
{
	cout << "Usuwanie wszystkich elementow\n";
	if (klucz == NULL)
	{
		cout << "Brak elementow\n";
		return;
	}
	Kopiec *aktualny = this, *parent = NULL, *grandparent = NULL;
	while (left != NULL || right != NULL) // dopoki nie usunie referenji
	{
		//cout << ile()<<endl;
		while (aktualny != NULL) // dopoki nie usunie referenji
		{
			grandparent = parent;
			parent = aktualny;
			if (aktualny->left != NULL)
				aktualny = aktualny->left;
			else
				aktualny = aktualny->right;
		}
		if (grandparent->left==parent) // decyzja ktora "reke" odciac grandfatherowi
			grandparent->left = NULL;
		else
			grandparent->right = NULL;
		delete parent;
		parent = this; // pomaga w obsludze przypadku kiedy nie ma dziadka a trzeba zdecydowac ktora reke uciac (dziadek==root)
		if (left != NULL)
			aktualny = left;
		else
			aktualny = right;
	}
	// czyszczebue na NULL thsia
	klucz = NULL;
	left = NULL;
	right = NULL;
	ilosc_elementow = 0;
	cout << "Usunieto wszystkie elementy\n";
}

void Kopiec::ustawilosc(int liczba)
{
	this->ilosc_elementow = liczba;
	if (left != NULL)
		left->ustawilosc(liczba-1);
	if (right != NULL)
		right->ustawilosc(liczba-1);
}

Kopiec::Kopiec()
{
	klucz = NULL;
	ilosc_elementow = 0;
	left = NULL;
	right = NULL;
}

string Kopiec::show_max()
{
	if (klucz == NULL)
		return("Brak elementow\n");
	if (left == NULL)
		if (right==NULL)
			return(std::to_string(klucz)); // brak poddrzew
		else
			return(std::to_string(right->klucz)); // tylko prawe
	else
		if (right == NULL)
			return(std::to_string(left->klucz)); // tylko lewe
	// sa oba
	if (left->klucz > right->klucz)
		return(std::to_string(left->klucz));
	return(std::to_string(right->klucz));
}

string Kopiec::show_min()
{
	if (klucz == NULL)
		return("Brak elementow\n");
	return(std::to_string(klucz));
}

string Kopiec::show_4lv()
{	
	stringstream retunr;
	retunr.str("");
	if (klucz!=NULL)
	{
		retunr << "MIN "<<klucz;
		retunr << "\n";
		if (left!=NULL)
		{
			retunr << "MAX " << left->klucz;
			if (right != NULL)
			{
				retunr << " ";
				retunr << right->klucz;
				retunr << "\n";
				// 3 rzad
				if (left->left != NULL)
				{
					retunr << "MIN " << left->left->klucz;
					if (left->right != NULL)
					{
						retunr << " ";
						retunr << left->right->klucz;
						if (right->left != NULL)
						{
							retunr << " ";
							retunr << right->left->klucz;
							if (right->right != NULL)
							{
								retunr << " ";
								retunr << right->right->klucz;
								retunr << "\n";
								// 4 rzad
								if (left->left->left != NULL)
								{
									retunr << "MAX " << left->left->left->klucz;
									if (left->left->right != NULL)
									{
										retunr << " ";
										retunr << left->left->right->klucz;
										if (left->right->left != NULL)
										{
											retunr << " ";
											retunr << left->right->left->klucz;
											if (left->right->right != NULL)
											{
												retunr << " ";
												retunr << left->right->right->klucz;
												if (right->left->left != NULL)
												{
													retunr << " ";
													retunr << right->left->left->klucz;
													if (right->left->right != NULL)
													{
														retunr << " ";
														retunr << right->left->right->klucz;
														if (right->right->left != NULL)
														{
															retunr << " ";
															retunr << right->right->left->klucz;
															if (right->right->right != NULL)
															{
																retunr << " ";
																retunr << right->right->right->klucz;
															}
																return(retunr.str());
														}
														else
															return(retunr.str());
													}
													else
														return(retunr.str());
												}
												else
													return(retunr.str());
											}
											else
												return(retunr.str());
										}
										else
											return(retunr.str());
									}
									else
										return(retunr.str());
								}
								else
									return(retunr.str());
							}
							else
								return(retunr.str());
						}
						else
							return(retunr.str());
					}
					else
						return(retunr.str());
				}
				else
					return(retunr.str());
			}
			else
				return(retunr.str());
		}
		else
			return(retunr.str());
	}
	else
		retunr << "Brak elementow\n";
	return(retunr.str());
}

string Kopiec::desc()
{
	string retunr;
	retunr="Klucz - " + to_string(klucz) + "\n";
	if (left != NULL)
		retunr += "lewo - " + to_string(left->klucz) + "\n";
	if (right!=NULL)
		retunr += "prawo - " + to_string(right->klucz) + "\n";
	return(retunr+"\n");
}

void Kopiec::remove_all()
{
	cout << "Usuwanie wszystkich elementow\n";
	if (klucz==NULL)
	{
		cout << "Brak elementow\n";
		return;
	}
	int koniec = ile();
	for (int i = 0; i < koniec;i++)
	{
		if (!(i % 1000))
			cout << "\tusunieto " << i + 1 << " elementow" << endl;
		remove_first();
	}
	cout << "Usunieto wszystkie elementy\n";
}

void Kopiec::wstaw_wiele(int ilosc)
{
	cout << "Dodawanie "<<ilosc<<" elementow\n";
	if (ilosc < 1)
	{
		cout << "Bledna ilosc elementow - " << ilosc << "\n";
		return;
	}
	for (int i = 0; i < ilosc; i++)
	{
		wstaw2(((((rand()*rand()) + (rand() % 2)) % 999991)) + 10);
		if (!(i%1000))
			cout <<"\tdodano "<<i+1<<" elementow" << endl;
	}
	cout << "Zakonczono dodawanie " << ilosc << " elementow\n";
}

void Kopiec::wstaw2(int nowyklucz)
{
	// nowy root
	if (ilosc_elementow == 0)
	{
		klucz = nowyklucz;
		ilosc_elementow++;
		return;
	}
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow + 1;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie - 1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
								//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// wsadzenie nowego elementu i zbudowanie drogi powrotu
	vector <Kopiec*> powrot;
	Kopiec  *aktualny = this;
	powrot.push_back(aktualny);
	for (int i = droga.size() - 1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
		powrot.push_back(aktualny);
	}
	// stworzenie nowego elementu
	if (droga[0] == 0) // po prawo bedzie nowy
	{
		aktualny->right = new Kopiec;
		aktualny = aktualny->right;
	}
	else // po lewo bedzie nowy
	{
		aktualny->left = new Kopiec;
		aktualny = aktualny->left;
	}
	powrot.push_back(aktualny);
	aktualny->klucz = nowyklucz;

	int i = powrot.size() - 1; // przywracamy porzadek
	int wysokosc = ceil(log2(ilosc_elementow + 2));// poziom wezla - czy min czy max - np - min, p- max
	wysokosc %= 2;
	// II faza
	if (wysokosc) // min
	{
		if (i - 1 >= 0 && powrot[i]->klucz > powrot[i - 1]->klucz) // czy dobrze z max
		{
			int temp = powrot[i]->klucz;
			powrot[i]->klucz = powrot[i - 1]->klucz;
			powrot[i - 1]->klucz = temp;
			i -= 1;
			wysokosc = 0;
		}
		else
			if (i - 2 >= 0 && powrot[i]->klucz < powrot[i - 2]->klucz)  // czy dobrze z min
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 2]->klucz;
				powrot[i - 2]->klucz = temp;
				i -= 2;
			}
			else
			{
				ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
				return;
			}
	}
	else // maks
	{
		if (i - 1 >= 0 && powrot[i]->klucz < powrot[i - 1]->klucz) // czy dobrze z min
		{
			int temp = powrot[i]->klucz;
			powrot[i]->klucz = powrot[i - 1]->klucz;
			powrot[i - 1]->klucz = temp;
			i -= 1;
			wysokosc = 1;
		}
		else
			if (i - 2 >= 0 && powrot[i]->klucz > powrot[i - 2]->klucz) // czy dobrze z max
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 2]->klucz;
				powrot[i - 2]->klucz = temp;
				i -= 2;
			}
			else
			{
				ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
				return;
			}
	}
	// faza III
	while (i >= 0)
	{
		if (wysokosc) // min
		{
			if (i - 2 >= 0 && powrot[i]->klucz < powrot[i - 2]->klucz)  // czy dobrze z min
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 2]->klucz;
				powrot[i - 2]->klucz = temp;
				i -= 2;
			}
			else
			{
				ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
				return;
			}
		}
		else // maks
		{
			if (i - 2 >= 0 && powrot[i]->klucz > powrot[i - 2]->klucz) // czy dobrze z max
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 2]->klucz;
				powrot[i - 2]->klucz = temp;
				i -= 2;
			}
			else
			{
				ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
				return;
			}
		}
	}
	ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
}

void Kopiec::wstaw(int nowyklucz)
{
	// nowy root
	if (ilosc_elementow==0)
	{
		klucz = nowyklucz;
		ilosc_elementow++;
		cout << "Wstawiono korzen o wartosci " << nowyklucz << "\n";
		return;
	}
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow + 1;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie-1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
		//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// wsadzenie nowego elementu i zbudowanie drogi powrotu
	vector <Kopiec*> powrot;
	Kopiec  *aktualny = this;
	powrot.push_back(aktualny);
	for (int i = droga.size()-1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
		powrot.push_back(aktualny);
	}
	// stworzenie nowego elementu
	if (droga[0] == 0) // po prawo bedzie nowy
	{
		aktualny->right = new Kopiec;
		aktualny = aktualny->right;
	}
	else // po lewo bedzie nowy
	{
		aktualny->left = new Kopiec;
		aktualny = aktualny->left;
	}
	powrot.push_back(aktualny);
	aktualny->klucz = nowyklucz;

	int i = powrot.size()-1; // przywracamy porzadek
	int wysokosc = ceil(log2(ilosc_elementow+2));// poziom wezla - czy min czy max - np - min, p- max
	wysokosc %= 2;
	cout << "Wstawiono wezel o wartosci " << nowyklucz << "\n";
	// II faza
		if (wysokosc) // min
		{
			if (i - 1 >= 0 && powrot[i]->klucz > powrot[i - 1]->klucz) // czy dobrze z max
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 1]->klucz;
				powrot[i - 1]->klucz = temp;
				i -= 1;
				wysokosc =0;
			}
			else
				if (i - 2 >= 0 && powrot[i]->klucz < powrot[i - 2]->klucz)  // czy dobrze z min
				{
					int temp = powrot[i]->klucz;
					powrot[i]->klucz = powrot[i - 2]->klucz;
					powrot[i - 2]->klucz = temp;
					i -= 2;
				}
				else
				{
					ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
					return;
				}
		}
		else // maks
		{
			if (i - 1 >= 0 && powrot[i]->klucz < powrot[i - 1]->klucz) // czy dobrze z min
			{
				int temp = powrot[i]->klucz;
				powrot[i]->klucz = powrot[i - 1]->klucz;
				powrot[i - 1]->klucz = temp;
				i -= 1;
				wysokosc = 1;
			}
			else
				if (i - 2 >= 0 && powrot[i]->klucz > powrot[i - 2]->klucz) // czy dobrze z max
				{
					int temp = powrot[i]->klucz;
					powrot[i]->klucz = powrot[i - 2]->klucz;
					powrot[i - 2]->klucz = temp;
					i -= 2;
				}
				else
				{
					ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
					return;
				}
		}
		// faza III
		while (i>=0)
		{
			if (wysokosc) // min
			{
					if (i - 2 >= 0 && powrot[i]->klucz < powrot[i - 2]->klucz)  // czy dobrze z min
					{
						int temp = powrot[i]->klucz;
						powrot[i]->klucz = powrot[i - 2]->klucz;
						powrot[i - 2]->klucz = temp;
						i -= 2;
					}
					else
					{
						ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
						return;
					}
			}
			else // maks
			{
					if (i - 2 >= 0 && powrot[i]->klucz > powrot[i - 2]->klucz) // czy dobrze z max
					{
						int temp = powrot[i]->klucz;
						powrot[i]->klucz = powrot[i - 2]->klucz;
						powrot[i - 2]->klucz = temp;
						i -= 2;
					}
					else
					{
						ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
						return;
					}
			}
		}
		ustawilosc(ilosc_elementow + 1); // ustawienie ilosci elementow dla kazdego
}

void Kopiec::remove_first()
{
	if (left == NULL)
	{
		klucz = NULL;
		ilosc_elementow = 0;
		return;
	}
	// znalezienie skrajnego elementu
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie - 1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
								//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// znalezienie elementu
	Kopiec *aktualny = this;
	for (int i = droga.size() - 1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	int stara_ilosc_elementow = ilosc_elementow;
	if (droga[0] == 0)
	{
		klucz = aktualny->right->klucz;
		delete aktualny->right;
		aktualny->right = NULL;
	}
	else
	{
		klucz = aktualny->left->klucz;
		delete aktualny->left;
		aktualny->left = NULL;
	}
	ustawilosc(stara_ilosc_elementow - 1);
}

void Kopiec::remove_min2()
{
	if (left == NULL)
	{
		klucz = NULL;
		ilosc_elementow = 0;
		return;
	}
	// znalezienie skrajnego elementu
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie - 1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
								//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// znalezienie elementu
	Kopiec *aktualny = this;
	for (int i = droga.size() - 1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	int stara_ilosc_elementow = ilosc_elementow;
	if (droga[0] == 0)
	{
		klucz = aktualny->right->klucz;
		delete aktualny->right;
		aktualny->right = NULL;
	}
	else
	{
		klucz = aktualny->left->klucz;
		delete aktualny->left;
		aktualny->left = NULL;
	}
	ustawilosc(stara_ilosc_elementow - 1);
	// zamiana wartosci - przywracanie zalozen
	aktualny = this;
	Kopiec *p1, *p2, *p3, *p4, *przodek = NULL;
	while (1)
	{
		if (aktualny->GiveHeight() > 2) // innaczej faza III - przedostatni lub ostatni poziom
		{
			przodek = NULL;
			p1 = aktualny->left->left;
			p2 = aktualny->left->right;
			p3 = aktualny->right->left;
			p4 = aktualny->right->right;

			// sprawdzenie i ewentualne podmienienie z p1234
			int koniec = 1;
			// znalezienie najmniejszego posrod potomkow w tym samym poziomie
			Kopiec *min = p1, *przodek2 = NULL;
			przodek2 = aktualny->left;
			if (p2 != NULL)
				if (min->klucz > p2->klucz)
					min = p2;
			if (p3 != NULL)
				if (min->klucz > p3->klucz)
				{
					min = p3;
					przodek2 = aktualny->right;
				}
			if (p4 != NULL)
				if (min->klucz > p4->klucz)
				{
					min = p4;
					przodek2 = aktualny->right;
				}

			// jesli min mniejszy zamiana
			if (min->klucz < aktualny->klucz)
			{
				int temp = aktualny->klucz;
				aktualny->klucz = min->klucz;
				min->klucz = temp;
				przodek = przodek2;
				aktualny = min;
				koniec = 0;
				ustawilosc(ilosc_elementow);
			}

			if (koniec)
			{
				ustawilosc(ilosc_elementow);
				return;// osiagnieto porzadek
			}
		}
		else // faza III
		{
			int wysokosc = ceil(log2(ilosc_elementow + 1));// poziom ostatniego - czy min czy max - np - min, p- max
			wysokosc %= 2; // nadanie poziomu domyslnie jak wysokosc drzewa

			if (wysokosc) // ostatni wezel na min
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na min
				{
					if (przodek != NULL)
						if (aktualny->klucz > przodek->klucz)
						{
							int temp = aktualny->klucz;
							aktualny->klucz = przodek->klucz;
							przodek->klucz = temp;
							ustawilosc(ilosc_elementow);
						}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na max
				if (przodek != NULL)
					if (przodek->klucz > aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz < aktualny->left->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->klucz < aktualny->right->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
							{
								int temp = aktualny->klucz;
								aktualny->klucz = aktualny->right->klucz;
								aktualny->right->klucz = temp;
								ustawilosc(ilosc_elementow);
								return;
							}
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz < aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz < aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
			else// ostatni wezel na max
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na max
				{
					if (aktualny->klucz < przodek->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						return;
					}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na min
				if (przodek != NULL)
					if (przodek->klucz < aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz > aktualny->left->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->right != NULL)
								if (aktualny->klucz > aktualny->right->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
								{
									int temp = aktualny->klucz;
									aktualny->klucz = aktualny->right->klucz;
									aktualny->right->klucz = temp;
								}
								else
								{
									if (aktualny->klucz > aktualny->left->klucz)
									{
										int temp = aktualny->klucz;
										aktualny->klucz = aktualny->left->klucz;
										aktualny->left->klucz = temp;
									}
								}
							ustawilosc(ilosc_elementow);
							return;
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz > aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz > aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
		}
	}
}

void Kopiec::remove_min()
{
	if (left == NULL)
	{
		if (klucz == NULL)
			cout << "Brak elementow\n";
		cout << "Usunieto korzen " << std::to_string(klucz) << endl;
		klucz = NULL;
		ilosc_elementow = 0;
		return;
	}
	// znalezienie skrajnego elementu
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie - 1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
								//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// znalezienie elementu
	Kopiec *aktualny = this;
	for (int i = droga.size() - 1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	int stara_ilosc_elementow = ilosc_elementow;
	if (droga[0] == 0)
	{
		cout << "Usunieto wezel o wartosci min " << std::to_string(klucz) << endl;
		klucz = aktualny->right->klucz;
		delete aktualny->right;
		aktualny->right = NULL;
	}
	else
	{
		cout << "Usunieto wezel o wartosci min " << std::to_string(klucz) << endl;
		klucz = aktualny->left->klucz;
		delete aktualny->left;
		aktualny->left = NULL;
	}
	ustawilosc(stara_ilosc_elementow - 1);
	// zamiana wartosci - przywracanie zalozen
	aktualny = this;
	Kopiec *p1, *p2, *p3, *p4, *przodek = NULL;
	while (1)
	{
		//cout << "\npoprawka\n" << show_4lv() << endl;
		if (aktualny->GiveHeight() > 2) // innaczej faza III - przedostatni lub ostatni poziom
		{
			przodek = NULL;
			p1 = aktualny->left->left;
			p2 = aktualny->left->right;
			p3 = aktualny->right->left;
			p4 = aktualny->right->right;

			// sprawdzenie i ewentualne podmienienie z p1234
			int koniec = 1;
			// znalezienie najmniejszego posrod potomkow w tym samym poziomie
			Kopiec *min = p1, *przodek2 = NULL;
			przodek2 = aktualny->left;
			if (p2 != NULL)
				if (min->klucz > p2->klucz)
					min = p2;
			if (p3 != NULL)
				if (min->klucz > p3->klucz)
				{
					min = p3;
					przodek2 = aktualny->right;
				}
			if (p4 != NULL)
				if (min->klucz > p4->klucz)
				{
					min = p4;
					przodek2 = aktualny->right;
				}

			// jesli min mniejszy zamiana
			if (min->klucz < aktualny->klucz)
			{
				int temp = aktualny->klucz;
				aktualny->klucz = min->klucz;
				min->klucz = temp;
				przodek = przodek2;
				aktualny = min;
				koniec = 0;
				ustawilosc(ilosc_elementow);
			}

			if (koniec)
			{
				ustawilosc(ilosc_elementow);
				return;// osiagnieto porzadek
			}
		}
		else // faza III
		{
			int wysokosc = ceil(log2(ilosc_elementow + 1));// poziom ostatniego - czy min czy max - np - min, p- max
			wysokosc %= 2; // nadanie poziomu domyslnie jak wysokosc drzewa

			if (wysokosc) // ostatni wezel na min
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na min
				{
					if (przodek != NULL)
						if (aktualny->klucz > przodek->klucz)
						{
							int temp = aktualny->klucz;
							aktualny->klucz = przodek->klucz;
							przodek->klucz = temp;
							ustawilosc(ilosc_elementow);
						}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na max
				if (przodek != NULL)
					if (przodek->klucz > aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz < aktualny->left->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->klucz < aktualny->right->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
							{
								int temp = aktualny->klucz;
								aktualny->klucz = aktualny->right->klucz;
								aktualny->right->klucz = temp;
								ustawilosc(ilosc_elementow);
								return;
							}
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz < aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz < aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
			else// ostatni wezel na max
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na max
				{
					if (aktualny->klucz < przodek->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						return;
					}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na min
				if (przodek != NULL)
					if (przodek->klucz < aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz > aktualny->left->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->right != NULL)
							if (aktualny->klucz > aktualny->right->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
							{
								int temp = aktualny->klucz;
								aktualny->klucz = aktualny->right->klucz;
								aktualny->right->klucz = temp;
							}
							else
							{
								if (aktualny->klucz > aktualny->left->klucz)
								{
									int temp = aktualny->klucz;
									aktualny->klucz = aktualny->left->klucz;
									aktualny->left->klucz = temp;
								}
							}
							ustawilosc(ilosc_elementow);
							return;
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz > aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz > aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
		}
	}
}

void Kopiec::remove_max()
{
	Kopiec *max; // znalezienie max
	if (left != NULL)
		if (right != NULL)
			if (left->klucz > right->klucz)
				max = left;
			else
				max = right;
		else
			max = left;
	else // usuwanie roota
	{
		if (klucz==NULL)
			cout << "Brak elementow\n";
		klucz = NULL;
		ilosc_elementow = 0;
		cout << "Usunieto korzen "<< std::to_string(klucz) << endl;
		return;
	}
	// znalezienie skrajnego elementu
	vector <int> droga;
	int aktualny_polozenie = ilosc_elementow;
	int rodzic;
	if (aktualny_polozenie % 2 == 0) // jest lewym dzieckiem
		rodzic = aktualny_polozenie / 2;
	else // jest prawym potomkiem
		rodzic = (aktualny_polozenie - 1) / 2;

	while (aktualny_polozenie != 1)
	{
		if (aktualny_polozenie == (2 * rodzic) + 1) // nowy po prawo od rodzica
			droga.push_back(0);
		else
			droga.push_back(1); // nowy po lewo od rodzica
								//przejscie w gore drzewa
		aktualny_polozenie = rodzic;
		if (aktualny_polozenie % 2 == 0) // jest lewym potomkiem
			rodzic = aktualny_polozenie / 2;
		else // jest prawym potomkiem
			rodzic = (aktualny_polozenie - 1) / 2;
	}
	// znalezienie elementu
	Kopiec *aktualny = this;
	for (int i = droga.size() - 1; i > 0; i--)
	{
		if (droga[i] == 0)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}

	if (droga[0] == 0)
	{
		cout << "Usunieto wezel max " << std::to_string(max->klucz) << endl;
		if (aktualny->right==max) // ostatnio dodany element jest rownierz najwieszky
		{
			delete max;
			aktualny->right = NULL;
			ustawilosc(ilosc_elementow - 1);
			return;
		}
		max->klucz = aktualny->right->klucz;
		aktualny->right = NULL;
		delete aktualny->right;
	}
	else
	{
		cout << "Usunieto wezel max " << std::to_string(max->klucz) << endl;
		if (aktualny->left == max) // ostatnio dodany element jest rownierz najwieszky
		{
			delete max;
			aktualny->left = NULL;
			ustawilosc(ilosc_elementow - 1);
			return;
		}
		max->klucz = aktualny->left->klucz;
		aktualny->left = NULL;
		delete aktualny->left;
	}
	ustawilosc(ilosc_elementow - 1);
	aktualny = max;
	Kopiec *p1, *p2, *p3, *p4, *przodek = NULL;
	while (1)
	{
		//cout << "\npoprawka\n" << show_4lv() << endl;
		if (aktualny->GiveHeight() > 2) // innaczej faza III - przedostatni lub ostatni poziom
		{
			przodek = NULL;
			p1 = aktualny->left->left;
			p2 = aktualny->left->right;
			p3 = aktualny->right->left;
			p4 = aktualny->right->right;

			// sprawdzenie i ewentualne podmienienie z p1234
			int koniec = 1;
			// znalezienie najmniejszego posrod potomkow w tym samym poziomie
			Kopiec *max = p1, *przodek2 = NULL;
			przodek2 = aktualny->left;
			if (p2 != NULL)
				if (max->klucz < p2->klucz)
					max = p2;
			if (p3 != NULL)
				if (max->klucz < p3->klucz)
				{
					max = p3;
					przodek2 = aktualny->right;
				}
			if (p4 != NULL)
				if (max->klucz < p4->klucz)
				{
					max = p4;
					przodek2 = aktualny->right;
				}

			// jesli max wiekszy zamiana
			if (max->klucz > aktualny->klucz)
			{
				int temp = aktualny->klucz;
				aktualny->klucz = max->klucz;
				max->klucz = temp;
				przodek = przodek2;
				aktualny = max;
				koniec = 0;
				ustawilosc(ilosc_elementow);
			}

			if (koniec)
			{
				ustawilosc(ilosc_elementow);
				return;// osiagnieto porzadek
			}
		}
		else // faza III
		{
			int wysokosc = ceil(log2(ilosc_elementow + 1));// poziom ostatniego - czy min czy max - np - min, p- max
			wysokosc %= 2; // nadanie poziomu domyslnie jak wysokosc drzewa

			if (wysokosc) // ostatni wezel na min
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na min
				{
					if (przodek != NULL)
						if (aktualny->klucz < przodek->klucz)
						{
							int temp = aktualny->klucz;
							aktualny->klucz = przodek->klucz;
							przodek->klucz = temp;
							ustawilosc(ilosc_elementow);
						}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na max
				if (przodek != NULL)
					if (przodek->klucz < aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz > aktualny->left->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->right!=NULL)
							if (aktualny->klucz > aktualny->right->klucz) // przodek znalazl sie na max sprawdzam czy jego dzieci nie sa wieksze
							{
								int temp = aktualny->klucz;
								aktualny->klucz = aktualny->right->klucz;
								aktualny->right->klucz = temp;
								ustawilosc(ilosc_elementow);
								return;
							}
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz > aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz > aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
			else// ostatni wezel na max
			{
				if (aktualny->left == NULL)// jest tylko rodzic , wezel jest na max
				{
					if (przodek!=NULL)
					if (aktualny->klucz > przodek->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						return;
					}
					return;
				}
				// jest rodzic (moze, nie dla korzenia), potomkowie , wezel jest na min
				if (przodek != NULL)
					if (przodek->klucz > aktualny->klucz) // zamiana z przodkiem
					{
						int temp = aktualny->klucz;
						aktualny->klucz = przodek->klucz;
						przodek->klucz = temp;
						ustawilosc(ilosc_elementow);
						if (aktualny->klucz < aktualny->left->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
						{
							int temp = aktualny->klucz;
							aktualny->klucz = aktualny->left->klucz;
							aktualny->left->klucz = temp;
							ustawilosc(ilosc_elementow);
							return;
						}
						else
						{
							if (aktualny->right != NULL)
								if (aktualny->klucz < aktualny->right->klucz) // przodek znalazl sie na min sprawdzam czy jego dzieci nie sa mniejsze
								{
									int temp = aktualny->klucz;
									aktualny->klucz = aktualny->right->klucz;
									aktualny->right->klucz = temp;
								}
								else
								{
									if (aktualny->klucz < aktualny->left->klucz)
									{
										int temp = aktualny->klucz;
										aktualny->klucz = aktualny->left->klucz;
										aktualny->left->klucz = temp;
									}
								}
							ustawilosc(ilosc_elementow);
							return;
						}
						return;
					}
				// sprawdzenie z potomstwem
				if (aktualny->right != NULL)
				{
					if (aktualny->klucz < aktualny->right->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->right->klucz;
						aktualny->right->klucz = temp;
					}
				}
				else
				{
					if (aktualny->klucz < aktualny->left->klucz)
					{
						int temp = aktualny->klucz;
						aktualny->klucz = aktualny->left->klucz;
						aktualny->left->klucz = temp;
					}
				}
				ustawilosc(ilosc_elementow);
				return;
			}
		}
	}
}

string Kopiec::GivePreorder()
{
	stringstream descr;
	Kopiec *aktualny = this;
	if (aktualny->klucz == NULL)
		return("Brak elementow\n");
	descr << aktualny->klucz << " ";
	//descr<< aktualny->key << " w"<<aktualny->waga<<"\n";
	if (aktualny->left != NULL)
		descr << aktualny->left->GivePreorder();
	if (aktualny->right != NULL)
		descr << aktualny->right->GivePreorder();
	return(descr.str());
}

int Kopiec::ile()
{
	if (klucz == NULL)
		return(0);
	int ile = 1;
	if (left != NULL)
		ile += left->ile();
	if (right != NULL)
		ile += right->ile();
	return(ile);
}

int Kopiec::GiveHeight()
{
	if (klucz == NULL) // brak elemetow zworcenie wysokosci jako 0
		return((0)); // jesli h(root)=1 to return 0 
	int hl = 0, hr = 0;
	if (left != NULL)
		hl = left->GiveHeight(); // wysokosc lewego poddrzewa
	if (right != NULL)
		hr = right->GiveHeight(); // wysokosc prawego poddrzewa 
	if (hl>hr)
		return(++hl); // jesli h(root)=1 to return ++hl 
	else
		return(++hr); // jesli h(root)=1 to return ++hr 
}

int main()
{
	srand(time(NULL));
	// ladowanie pliku
#pragma warning (disable : 4996)
	FILE* fp = fopen("inlab06.txt", "r");
	if (fp == NULL)
		return -1;
	int x1, x2, k1, k2;
	fscanf(fp, "%d %d %d %d", &x1, &x2, &k1, &k2);
	fclose(fp);

	// czas start
	clock_t begin, end;
	double time_spent;
	begin = clock();

	// zajecia
	Kopiec kopiec; cout << "Stworzono Kopiec MinMax\n"; //zainicjuj kopiec;
	kopiec.wstaw_wiele(x1); //? wstaw X1 elementów do kopca;
	kopiec.wstaw(k1); //? wstaw element o warto?ci klucza k1;
	kopiec.wstaw(k2); //? wstaw element o warto?ci klucza k2;
	cout << endl<<kopiec.show_4lv() << endl<<endl; //? wy?wietl 4 pierwsze poziomy kopca;
	kopiec.remove_min();//? usuñ minimum;
	kopiec.remove_max(); //? usuñ maksimum;
	cout << endl<<kopiec.show_4lv()<<endl<<endl; //? wy?wietl 4 pierwsze poziomy kopca;
	kopiec.remove_all2(); //? usuñ wszystkie elementy z kopca;
	kopiec.wstaw_wiele(x2);	//? wstaw X2 elementów do kopca;
	kopiec.remove_min();//? usuñ minimum;
	kopiec.remove_max(); //? usuñ maksimum;
	kopiec.wstaw(k1); //? wstaw element o warto?ci klucza k1;
	kopiec.wstaw(k2); //? wstaw element o warto?ci klucza k2;
	cout << "Najwieksza wartosc - " << kopiec.show_max() << "\nNajmniejsza wartosc - " << kopiec.show_min() << "\n"; //? wy?wietl najwiêkszš i najmniejszš warto?æ;
	kopiec.remove_all2(); //? usuñ wszystkie elementy z kopca;
	cout << "Najwieksza wartosc - " << kopiec.show_max() << "\nNajmniejsza wartosc - " << kopiec.show_min() << "\n"; //? wy?wietl najwiêkszš i najmniejszš warto?æ; // powinno wypisaæ, ¿e kopiec jest pusty

	//czas stop
	end = clock();
	time_spent = (double)(end - begin);
	printf("czas wykonywania - %f\n", time_spent);
	getchar();
}