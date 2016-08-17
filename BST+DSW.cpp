// bst tree data struct
// and DSW balancing algorithm
// by Artur Ziemba

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <sstream> 

using namespace std;

class BST_Tree
{
public:
	BST_Tree();
	~BST_Tree();
	void Wstaw_Element(int);
	void Wstaw_Elementy(int);
	void Set(int);
	void Find(int);
	void Remove(int);
	void RemoveAll();
	string GivePreorder();
	string GivePostorder();
	string GiveInorder();
	int GiveHeight();
	BST_Tree* DSW();
	BST_Tree* Kopiuj();


private:
	// wartosci
	int key;
	BST_Tree *left, *right;
	char tab[256]; // wartosci znakow kodu ascii od 1 do 127

	// metody
	void Wstaw_Element2(int);
	int GiveNumberofRightNoods();
	BST_Tree* in_to_list(); // zamiana drzewa w pesudoliste, zwraca nowy root
	BST_Tree* rot_r(BST_Tree *, BST_Tree *, BST_Tree *);
	BST_Tree* rot_l(BST_Tree *, BST_Tree *, BST_Tree *);
	BST_Tree* Kopiuj2(BST_Tree*);
};

int BST_Tree::GiveNumberofRightNoods()
{
	BST_Tree *aktualny=this;
	int NumberofNoods = 0;
	if (aktualny->key != NULL)
		NumberofNoods++;
	while (aktualny->right != NULL)
	{
		NumberofNoods++;
		aktualny = aktualny->right;
	}
	return(NumberofNoods);
}

BST_Tree* BST_Tree::Kopiuj()
{
	BST_Tree *root = new BST_Tree;
	*root = *this; // kopiowanie aktualnego wezla
	if (this->left != NULL)
		root->left = root->Kopiuj2(this->left);
	else
		root->left = NULL;
	if (this->right != NULL)
		root->right = root->Kopiuj2(this->right);
	else
		root->right = NULL;
	return(root);
}

BST_Tree* BST_Tree::Kopiuj2(BST_Tree* duplikat)
{
	BST_Tree *root = new BST_Tree; // root jest tylko dla lokalnego drzewa!!
	*root = *duplikat;
	if (duplikat->left != NULL)
		root->left = root->Kopiuj2(duplikat->left);
	else
		root->left = NULL;
	if (duplikat->right != NULL)
		root->right = root->Kopiuj2(duplikat->right);
	else
		root->right = NULL;
	return(root);
}

BST_Tree* BST_Tree::DSW()
{
	BST_Tree*root = in_to_list(), *dziadek = NULL, *temp2, *rootchange;
	// rootchange - mowi o zmianie roota przy rotowaniu
	// temp - aby nie stracic roota, temp2 potrzebny przy przerzucaniu (rootowaniu)

	// "druga waza"
	BST_Tree*temp = root;
	// obliczenie wspolczynika mowiacego o "polowie wezlow"
	int liczba_wezlow = root->GiveNumberofRightNoods(), wspolczynnik = 1; // pomaga obliczyc "co drugi"
		// wyliczona z "listy" - idac po prawych 
	while (wspolczynnik <= liczba_wezlow)
		wspolczynnik = 2 * wspolczynnik + 1;
	wspolczynnik = wspolczynnik / 2;
	// rotowanie pierwsszej polowy wezlow w lewo (co 2)
	for (int count = 0; count < (liczba_wezlow - wspolczynnik); count++)
	{
		temp2 = temp->right;
		if (temp2 != NULL) // czy dotarlismy do konca "listy"
		{
			rootchange = rot_l(dziadek, temp, temp->right);
			if (rootchange != NULL)
				root = rootchange;
			dziadek = temp2;
			temp = temp2->right;
		}
	}
	// kolejne rotacje co 2 wezla tym razem juz do osiagniecia wlasciwego stanu drzewa
	while (wspolczynnik>1)
	{
		wspolczynnik = wspolczynnik / 2;
		dziadek = NULL;
		temp = root;
		for (int count = 0; count < wspolczynnik; count++)
		{
			temp2 = temp->right;
			rootchange = rot_l(dziadek, temp, temp->right);
			if (rootchange != NULL)
				root = rootchange;
			dziadek = temp2;
			temp = temp2->right;
		}
	}
	cout << "Wywarzono drzewo\n";
	return(root);
}

BST_Tree* BST_Tree::rot_r(BST_Tree *dziadek, BST_Tree *rodzic, BST_Tree *rotowany)
{
	BST_Tree*temproot = NULL; // zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
	if (rodzic == NULL)
		return(NULL);
	if (dziadek != NULL)
	{
		if (dziadek->left == rodzic)
			dziadek->left = rotowany;
		else
			dziadek->right = rotowany;
	}
	else
		temproot = rotowany;
	BST_Tree *temp = rotowany->right;
	rotowany->right = rodzic;
	rodzic->left = temp;
	return(temproot);// zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
}

BST_Tree* BST_Tree::rot_l(BST_Tree *dziadek, BST_Tree *rodzic, BST_Tree *rotowany)
{
	BST_Tree*temproot = NULL; // zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
	if (rodzic == NULL)
		return(NULL); // korzen nie moze byc rotowany!
	if (dziadek != NULL)
	{
		if (dziadek->left == rodzic)
			dziadek->left = rotowany;
		else
			dziadek->right = rotowany;
	}
	else
		temproot = rotowany;
	BST_Tree *temp = rotowany->left;
	rotowany->left = rodzic;
	rodzic->right = temp;
	return(temproot);// zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
}

BST_Tree* BST_Tree::in_to_list()
{
	BST_Tree* duplikat = this->Kopiuj();
	BST_Tree *dziadek = NULL, *temp = duplikat, *temp2, *rootchange;
	// stworznie "kregoslupa"
	while (temp != NULL)
	{
		// jesli wezel ma lewego rotujemy go
		if (temp->left != NULL)
		{
			temp2 = temp->left;
			rootchange = rot_r(dziadek, temp, temp->left); // jesli zzmienil sie root podczas rotowania (nie zwrocony NULL) ustawiam nowy root
			if (rootchange != NULL)
				duplikat = rootchange;
			temp = temp2;
		}
		// nie ma lewego idziemy "po kregoslupie" w dol
		else
		{
			dziadek = temp;
			temp = temp->right;
		}
	}
	return(duplikat);
}

int BST_Tree::GiveHeight()
{
	if (this->key == NULL) // brak elemetow zworcenie wysokosci jako 0
		return((0)); // jesli h(root)=1 to return 0 
		int hl = 0, hr = 0;
	if (this->left != NULL)
		hl = this->left->GiveHeight(); // wysokosc lewego poddrzewa
	if (this->right != NULL)
		hr = this->right->GiveHeight(); // wysokosc prawego poddrzewa 
	if (hl>hr)
		return(++hl); // jesli h(root)=1 to return ++hl 
	else
		return(++hr); // jesli h(root)=1 to return ++hr 
}

void BST_Tree::Remove(int szukana)
{
	int notfound = 1;
	BST_Tree *aktualny = this, *parent = this;
	while ((aktualny != NULL) && (notfound))
	{
		if (aktualny->key == szukana)
			notfound = 0;
		else
		{
			parent = aktualny;
			if (aktualny->key > szukana)
				aktualny = aktualny->left;
			else
				aktualny = aktualny->right;
		}
	}
	if (notfound == 1)
		cout << "Nie znaleziono wezla o wartosci klucza - " << szukana << endl;
	else
		// usuwanie
	{
		cout << "Usunieto wezel o wartosci klucza - " << szukana << endl;
		// lisc oraz root bez rak
		if (aktualny->left == NULL && aktualny->right == NULL)
		{
			if (parent->key > szukana)
				parent->left = NULL;
			else
				parent->right = NULL;
			if (aktualny == parent) // usuwanie roota z referencjami na NULL
			{
				key = NULL;
				for (int count = 0; count < 256; count++)
					tab[count] = NULL;
				return;
			}
			delete aktualny;
			return;
		}
		// usuwany ma tylko jedno poddrzewo
		if (aktualny->left == NULL)
		{
			if (parent->key > aktualny->key)
				parent->left = parent->left->right;
			else
				parent->right = parent->right->right;
			delete aktualny;
			return;
		}
		if (aktualny->right == NULL)
		{
			if (parent->key > aktualny->key)
				parent->left = aktualny->left;
			else
				parent->right = aktualny->left;
			delete aktualny;
			return;
		}


		// ma oba poddrzewa
		// ustawiam "poprzednika" jako aktualny 
		// znalezienie poprzednika
		// ustawiam na lewy, poniewaz jestem pewny ze jest- reszta przypadkow zostala obsluzona
		BST_Tree *precursor = aktualny->left, *parentprecursor = aktualny;
		while (precursor->right != NULL)
		{
			parentprecursor = precursor;
			precursor = precursor->right;
		}
		if (precursor->left != NULL)
			parentprecursor->right = precursor->left;// poprzednik ma lewe poddrzewo ktore podczepiam do rodzica poprzednika
		else
			parentprecursor->right = NULL; // poprzednik nie ma poddrzewa 
										   // zamiana aktualnego z poprzednikiem
		aktualny->key = precursor->key;
		for (int count = 0; count < 256; count++)
			aktualny->tab[count] = precursor->tab[count];
		// zabicie preprocesora ktory zostal zamieniony a jego wartosci podmienione
		delete(precursor);
		return;
	}
}

void BST_Tree::Find(int szukana)
{
	int notfound = 1;
	BST_Tree *aktualny = this;
	while ((aktualny != NULL) && (notfound))
	{
		if (aktualny->key == szukana)
			notfound = 0;
		else
		{
			if (aktualny->key > szukana)
				aktualny = aktualny->left;
			else
				aktualny = aktualny->right;
		}
	}
	if (notfound == 1)
		cout << "Nie znaleziono wezla o wartosci klucza - " << szukana << endl;
	else
		cout << "Znaleziono! - Klucz - " << aktualny->key << endl;
}

void BST_Tree::Set(int wylosowana)
{
	key = wylosowana;
	for (int count = 0; count < 256; count++)
		tab[count] = ((rand() % 126) + 1);
}

BST_Tree::BST_Tree()
{
	key = NULL;
	left = NULL;
	right = NULL;
	tab[0] = NULL;
}

BST_Tree::~BST_Tree()
{

}

void BST_Tree::RemoveAll()
{
	if (this->key == NULL)
	{
		cout << "Brak elementow do usuniecia\n";
		return;
	}
	BST_Tree *aktualny = this, *parent = NULL, *grandparent = NULL;
	while (this->left != NULL || this->right != NULL) // dopoki nie usunie referenji
	{
		while (aktualny != NULL) // dopoki nie usunie referenji
		{
			grandparent = parent;
			parent = aktualny;
			if (aktualny->left != NULL)
				aktualny = aktualny->left;
			else
				aktualny = aktualny->right;
		}
		if (grandparent->key>parent->key) // decyzja ktora "reke" odciac grandfatherowi
			grandparent->left = NULL;
		else
			grandparent->right = NULL;
		delete parent;
		parent = this; // pomaga w obsludze przypadku kiedy nie ma dziadka a trzeba zdecydowac ktora reke uciac (dziadek==root)
		if (this->left != NULL)
			aktualny = this->left;
		else
			aktualny = this->right;
	}
	aktualny = this; // powrot na biezacy
					 // czyszczebue na NULL thsia
	this->key = NULL;
	this->left = NULL;
	this->right = NULL;
	for (int i = 0; i < 256; i++)
		this->tab[i] = NULL;
	cout << "Usunieto wszystkie elementy \n";
	return;
}

void BST_Tree::Wstaw_Elementy(int ilosc_elementow)
{
	for (int count = 0; count < ilosc_elementow; count++)
	{
		int wylosowano = ((((rand()*rand()) + (rand() % 2)) % 1000003)) + 10;
		Wstaw_Element2(wylosowano);
	}
	cout << "Wstawiono " << ilosc_elementow << " elementow\n";
}

void BST_Tree::Wstaw_Element(int newkey)
{
	if (this->key == NULL)
	{
		this->Set(newkey);
		cout << "Dodano korzen o wartosci kluczowej " << newkey << endl;
		return;
	}
	BST_Tree *newnode = new BST_Tree, *aktualny = this, *parent = NULL;
	newnode->Set(newkey);
	while (aktualny != NULL)
	{
		if (aktualny->key == newkey)
		{
			cout << "Element o wartosci kluczowej " << newkey << " znajduje sie juz w drzewie\n";
			return;
		}
		parent = aktualny;
		if (aktualny->key < newkey)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	if (parent->key > newkey)
		parent->left = newnode;
	else
		parent->right = newnode;
	cout << "Dodano element o wartosci kluczowej " << newkey << endl;
}

void BST_Tree::Wstaw_Element2(int newkey)
{
	// korzen
	if (this->key == NULL)
	{
		this->Set(newkey);
		return;
	}
	BST_Tree *newnode = new BST_Tree, *aktualny = this, *parent = NULL;
	newnode->Set(newkey);
	// szukanie wolnego miesjca
	while (aktualny != NULL)
	{
		// jesli znajduje sie w drzewie losuje nowy
		if (aktualny->key == newkey)
		{
			newkey = ((((rand()*rand()) + (rand() % 2)) % 1000003)) + 10;
			Wstaw_Element2(newkey);
			return;
		}
		parent = aktualny;
		if (aktualny->key < newkey)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	// wstawianie
	if (parent->key > newkey)
		parent->left = newnode;
	else
		parent->right = newnode;
}

string BST_Tree::GivePreorder()
{
	stringstream descr;
	BST_Tree *aktualny = this;
	if (aktualny->key == NULL)
		return("Brak elementow\n");
	descr << aktualny->key << " ";
	if (aktualny->left != NULL)
		descr << aktualny->left->GivePreorder();
	if (aktualny->right != NULL)
		descr << aktualny->right->GivePreorder();
	return(descr.str());
}

string BST_Tree::GiveInorder()
{
	stringstream descr;
	BST_Tree *aktualny = this;
	if (aktualny->key == NULL)
		return("Brak elementow\n");
	if (aktualny->left != NULL)
		descr << aktualny->left->GiveInorder();
	descr << aktualny->key << " ";
	if (aktualny->right != NULL)
		descr << aktualny->right->GiveInorder();
	return(descr.str());
}

string BST_Tree::GivePostorder()
{
	stringstream descr;
	BST_Tree *aktualny = this;
	if (aktualny->key == NULL)
		return("Brak elementow\n");
	if (aktualny->left != NULL)
		descr << aktualny->left->GivePostorder();
	if (aktualny->right != NULL)
		descr << aktualny->right->GivePostorder();
	descr << aktualny->key << " ";
	return(descr.str());
}

int main()
{
	srand(time(NULL));
	// ladowanie pliku
#pragma warning (disable : 4996)
	FILE* fp = fopen("inlab04.txt", "r");
	if (fp == NULL)
		return -1;
	int x1, x2;
	fscanf(fp, "%d %d", &x1, &x2);
	fclose(fp);
	if (x1 < 0)
		return(-1); //Ilosc struktur nie moze byc mniejsz niz 0
	// czas start
	clock_t begin, end;
	double time_spent;
	begin = clock();

	// dzialania
	BST_Tree Drzewo, *Drzewo2, *Drzewo3;
	
	cout << "Zainicjowano drzewo\n";
	Drzewo.Wstaw_Elementy(x1);

	cout << "Wysokosc drzewa = " << Drzewo.GiveHeight() << endl;
	cout << "Zainicjowano drzewo\n";
	Drzewo2 = Drzewo.DSW();
	cout << "Wysokosc drzewa = " << Drzewo2->GiveHeight() << endl;
	Drzewo2->RemoveAll();
	Drzewo2->Wstaw_Elementy(x2);
	cout << "Wysokosc drzewa = " << Drzewo2->GiveHeight() << endl;
	cout << "Zainicjowano drzewo\n";
	Drzewo3 = Drzewo2->DSW();
	cout << "Wysokosc drzewa = " << Drzewo3->GiveHeight() << endl;
	
	/*
	Drzewo.Wstaw_Element(100);
	Drzewo.Wstaw_Element(50);
	Drzewo.Wstaw_Element(150);
	Drzewo.Wstaw_Element(25);
	Drzewo.Wstaw_Element(60);
	Drzewo.Wstaw_Element(90);
	Drzewo.Wstaw_Element(110);

	cout << Drzewo.GivePreorder() << endl << Drzewo.GiveHeight() << endl;
	Drzewo2=Drzewo.DSW();
	cout << Drzewo2->GivePreorder() << endl << Drzewo2->GiveHeight() << endl;
	Drzewo2->RemoveAll();
	cout << Drzewo2->GivePreorder() << endl << Drzewo2->GiveHeight() << endl;
	Drzewo2->Wstaw_Elementy(7);
	Drzewo3 = Drzewo2->DSW();
	cout  << Drzewo3->GivePreorder() << endl << Drzewo3->GiveHeight() << endl;
	*/

	//czas stop
	end = clock();
	time_spent = (double)(end - begin);
	printf("czas wykonywania - %f\n", time_spent);
	getchar();
}
