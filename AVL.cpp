// AVL tree data struct by Artur Ziemba

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <sstream> 
#include <vector>
#include <cmath>

using namespace std;

class AVL_Tree
{
public:
	int ile(); // zwraca ilosc elementow w drzewie
	AVL_Tree(); 
	~AVL_Tree();
	void Set(int);  // nie ustawaia wagi - funkcja give waga zwraca ja!
	void Find(int); 
	void RemoveAll();
	string GivePreorder();
	string GivePostorder();
	string GiveInorder();
	int GiveHeight(); 
	AVL_Tree* Kopiuj(); 

	// nowe funkcje - dsw
	AVL_Tree* Remove(int);
	AVL_Tree* Wstaw_Element(int);
	AVL_Tree* Wstaw_Elementy(int);

private:
	// wartosci
	int key;
	int waga; // mowi o tym ktora wysokosc poddrzewa jest wyzzsza
	AVL_Tree *left, *right;
	char tab[16]; // wartosci znakow ASCII = od 32 do 126

	// metody
	int GiveWaga(); // zwraca wage wezla
	AVL_Tree* rot_r(AVL_Tree *, AVL_Tree *, AVL_Tree *);
	AVL_Tree* rot_l(AVL_Tree *, AVL_Tree *, AVL_Tree *);
};

int AVL_Tree::ile()
{
	if (key == NULL)
		return(0);
	int ile = 1;
	if (left != NULL)
		ile += left->ile();
	if (right != NULL)
		ile +=right->ile();
	return(ile);
}

int AVL_Tree::GiveWaga()
{
	if (left == NULL && right == NULL) // brak lewego poddrzewa
		return(0);
	if (left==NULL) // brak lewego poddrzewa
		return(1);
	if (right == NULL) // brak prawego poddrzewa
		return(-1);

	// sa oba poddrzewa
	int l = left->GiveHeight(), r = right->GiveHeight();
	if (l==r)
		return(0);
	if (l>r)
		return(-1);
	else
		return(1);
}

AVL_Tree* AVL_Tree::Kopiuj()
{
	AVL_Tree *root = new AVL_Tree;
	*root = *this; // kopiowanie aktualnego wezla
	if (this->left != NULL)
		root->left = root->left->Kopiuj();
	else
		root->left = NULL;
	if (this->right != NULL)
		root->right = root->right->Kopiuj();
	else
		root->right = NULL;
	return(root);
}

AVL_Tree* AVL_Tree::rot_r(AVL_Tree *dziadek, AVL_Tree *rodzic, AVL_Tree* rotowany)
{
	AVL_Tree*temproot = NULL; // zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
	if (rodzic == NULL)
		return(NULL); // korzen nie moze byc rotowany! nie da sie isc wyzej
	if (dziadek != NULL)
	{
		if (dziadek->left == rodzic)
			dziadek->left = rotowany;
		else
			dziadek->right = rotowany;
	}
	else
		temproot = rotowany;
	AVL_Tree *temp = rotowany->right;
	rotowany->right = rodzic;
	rodzic->left = temp;
	return(temproot);// zwracam npwego korzenia jestli sie zmienil jesli nie - NULL
}

AVL_Tree* AVL_Tree::rot_l(AVL_Tree *dziadek, AVL_Tree *rodzic, AVL_Tree*rotowany)
{
	AVL_Tree*temproot = NULL; // zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
	if (rodzic == NULL)
		return(NULL); // korzen nie moze byc rotowany! nie da sie isc wyzej
	if (dziadek != NULL)
	{
		if (dziadek->left == rodzic)
			dziadek->left = rotowany;
		else
			dziadek->right = rotowany;
	}
	else
		temproot = rotowany;
	AVL_Tree *temp = rotowany->left;
	rotowany->left = rodzic;
	rodzic->right = temp;
	return(temproot);// zwracam npwego rodzica jestli sie zmienil jesli nie - NULL
}

int AVL_Tree::GiveHeight()
{
	if (this->key == NULL) // brak elemetow zworcenie wysokosci jako 0
		return((0)); 
	int hl = 0, hr = 0;
	if (this->left != NULL)
		hl = this->left->GiveHeight(); // wysokosc lewego poddrzewa
	if (this->right != NULL)
		hr = this->right->GiveHeight(); // wysokosc prawego poddrzewa 
	if (hl>hr)
		return(++hl); 
	else
		return(++hr); 
}

AVL_Tree* AVL_Tree::Remove(int szukana)
{
	int notfound = 1;
	AVL_Tree*aktualny = this, *parent = this, *root=this;
	vector<AVL_Tree *> droga; // inicjacia drogi po wezlach
	while ((aktualny != NULL) && (notfound))
	{
		droga.push_back(aktualny);
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
	if (notfound == 1) {
		cout << "Nie znaleziono wezla o wartosci klucza - " << szukana << endl;
		return(root);
	}
	else
		// usuwanie akualnego
	{
		cout << "Usunieto wezel o wartosci klucza - " << szukana << endl;

		if (aktualny->left==NULL && aktualny->right==NULL) // lisc
		{
			if (aktualny == parent) // usuwanie roota z referencjami na NULL
			{
				key = NULL;
				for (int count = 0; count < 15; count++)
					tab[count] = NULL;
				waga = NULL;
				return(root);
			}
			// korygowanie drogi
			for (int count = droga.size() - 2; count >= 0; count--)
			{
				if (droga[count]->left == droga[count + 1])
					droga[count]->waga += 1; // zmiana wagi elementu lewego poddrzewa
				else
					droga[count]->waga -= 1; // zmiana wagi elementu prawego poddrzewa

				if (count== droga.size() - 2) // realne usuniecie wezla po skorygowaniu 1 na drodze- parenta
				{
					if (parent->key > szukana)
						parent->left = NULL;
					else
						parent->right = NULL;
				delete aktualny;
				}

				if (droga[count]->waga == -1 || droga[count]->waga == 1) // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					return(root); 
				if (droga[count]->waga == 2)// ma za duzo w prawym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->right->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->right->waga == 1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}

					else // (droga[count]->right->waga == -1)
					{
						AVL_Tree *bohater = droga[count]->right->left, *srodek = droga[count]->right;
						rot_r(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_l(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
				if (droga[count]->waga == -2) // ma za duzo w lewym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->left->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->left->waga == -1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
					else // (droga[count]->left->waga == 1)
					{
						AVL_Tree *bohater = droga[count]->left->right, *srodek = droga[count]->left;
						rot_l(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_r(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
			}
			return(root);
		}  // end lisc


		// usuwany ma tylko jedno poddrzewo
		if (aktualny->left == NULL) // tylko prawe
		{
			if (parent==aktualny) // usuwanie roota
			{
				root = aktualny->right;
				delete aktualny;
				return(root);
			}
			if (parent->key > aktualny->key) // podwiazanie do rodzica potomka aktualnego
			{
				parent->left = parent->left->right;
				droga[droga.size() - 1] = parent->left;
				delete aktualny;
			}
			else
			{
				parent->right = parent->right->right;
				droga[droga.size() - 1] = parent->right;
				delete aktualny;
			}
			// korygowanie drogi
			for (int count = droga.size() - 2; count >= 0; count--)
			{
				if (droga[count]->left == droga[count + 1])
					droga[count]->waga += 1; // zmiana wagi elementu lewego poddrzewa
				else
					droga[count]->waga -= 1; // zmiana wagi elementu prawego poddrzewa

				if (droga[count]->waga == -1 || droga[count]->waga == 1) // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					return(root);
				if (droga[count]->waga == 2)// ma za duzo w prawym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->right->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->right->waga == 1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}

					else // (droga[count]->right->waga == -1)
					{
						AVL_Tree *bohater = droga[count]->right->left, *srodek = droga[count]->right;
						rot_r(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_l(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
				if (droga[count]->waga == -2) // ma za duzo w lewym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->left->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->left->waga == -1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
					else // (droga[count]->left->waga == 1)
					{
						AVL_Tree *bohater = droga[count]->left->right, *srodek = droga[count]->left;
						rot_l(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_r(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
			}
			return(root);
		} // end tylko prawe

		if (aktualny->right == NULL) // tylko lewe
		{
			if (parent == aktualny) // usuwanie roota
			{
				root = aktualny->left;
				delete aktualny;
				return(root);
			}
			if (parent->key > aktualny->key) // podwiazanie do rodzica potomka aktualnego
			{
				parent->left = parent->left->left;
				droga[droga.size() - 1] = parent->left;
				delete aktualny;
			}
			else
			{
				parent->right = parent->right->left;
				droga[droga.size() - 1] = parent->right;
				delete aktualny;
			}
			// korygowanie drogi
			for (int count = droga.size() - 2; count >= 0; count--)
			{
				if (droga[count]->left == droga[count + 1])
					droga[count]->waga += 1; // zmiana wagi elementu lewego poddrzewa
				else
					droga[count]->waga -= 1; // zmiana wagi elementu prawego poddrzewa

				if (droga[count]->waga == -1 || droga[count]->waga == 1) // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					return(root);
				if (droga[count]->waga == 2)// ma za duzo w prawym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->right->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->right->waga == 1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}

					else // (droga[count]->right->waga == -1)
					{
						AVL_Tree *bohater = droga[count]->right->left, *srodek = droga[count]->right;
						rot_r(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_l(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
				if (droga[count]->waga == -2) // ma za duzo w lewym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->left->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->left->waga == -1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
					else // (droga[count]->left->waga == 1)
					{
						AVL_Tree *bohater = droga[count]->left->right, *srodek = droga[count]->left;
						rot_l(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_r(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
			}
			return(root);
		}// end tylko lewe
		 // end usuwany ma tylko jedno poddrzewo

		// ma oba poddrzewa
		// znajdujemy poprzednika

		AVL_Tree *temp3=aktualny;
		parent = aktualny;
		aktualny = aktualny->left;
		droga.push_back(aktualny);
		while (aktualny->right!=NULL)
		{
			parent = aktualny;
			aktualny = aktualny->right;
			droga.push_back(aktualny);
		}
		// zamiana wartosci z poprzendikiem - kluczowa nastepuje przy usuwaniu (aby przy sprawdzeniu parent ->strona == aktualny dobrze wyszlo)
		for (int count = 0; count < 16; count++)
			temp3->tab[count] = aktualny->tab[count];
		// ostatni na stosie jest poprzenik - usuwamy go 
		// fragment funkcji - odpowiedzialny za usuwanie liscia - (poprzednika)
			// korygowanie drogi
			for (int count = droga.size() - 2; count >= 0; count--)
			{
				if (droga[count]->left == droga[count + 1])
					droga[count]->waga += 1; // zmiana wagi elementu lewego poddrzewa
				else
					droga[count]->waga -= 1; // zmiana wagi elementu prawego poddrzewa

				if (count == droga.size() - 2) // realne usuniecie wezla po skorygowaniu 1 na drodze- parenta
				{
					if (parent->key > aktualny->key)
					{
						temp3->key = aktualny->key;
						parent->left = NULL;
					}
					else
					{
						temp3->key = aktualny->key;
						parent->right = NULL;
					}
					delete aktualny;
				}

				if (droga[count]->waga == -1 || droga[count]->waga == 1) // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					return(root);
				if (droga[count]->waga == 2)// ma za duzo w prawym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->right->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->right->waga == 1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->right;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w lewo
						temp = rot_l(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}

					else // (droga[count]->right->waga == -1)
					{
						AVL_Tree *bohater = droga[count]->right->left, *srodek = droga[count]->right;
						rot_r(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_l(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
				if (droga[count]->waga == -2) // ma za duzo w lewym poddrzewie - korygujemy zaleznie od jego wartosci
				{
					if (droga[count]->left->waga == 0)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
					}

					if (droga[count]->left->waga == -1)
					{
						AVL_Tree *dziadek = NULL, *temp = NULL, *bohater_rotacji = droga[count]->left;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						// rotacja w prawo 
						temp = rot_r(dziadek, droga[count], bohater_rotacji);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						droga[count]->waga = droga[count]->GiveWaga();
						bohater_rotacji->waga = bohater_rotacji->GiveWaga();
						droga[count] = bohater_rotacji; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
					else // (droga[count]->left->waga == 1)
					{
						AVL_Tree *bohater = droga[count]->left->right, *srodek = droga[count]->left;
						rot_l(droga[count], srodek, bohater); // nie moze nastapic zmiana roota
						AVL_Tree *dziadek = NULL, *temp = NULL;
						if (count - 1 >= 0) // czy istnieje dziadek
							dziadek = droga[count - 1];
						temp = rot_r(dziadek, droga[count], bohater);
						if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
							root = temp;
						srodek->waga = srodek->GiveWaga();
						droga[count]->waga = droga[count]->GiveWaga();
						bohater->waga = bohater->GiveWaga();
						droga[count] = bohater; // podmiana aby dobrze ustawic droga[count-1]-wspolczynik (zalezy od ktorej storny)
					}
				}
		}  // end lisc
		return(root);
	}
}

void AVL_Tree::Find(int szukana)
{
	int notfound = 1;
	AVL_Tree *aktualny = this;
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

void AVL_Tree::Set(int wylosowana)
{
	key = wylosowana;
	for (int count = 0; count < 16; count++)
		tab[count] = ((rand() % 94) + 32);
}

AVL_Tree::AVL_Tree()
{
	key = NULL;
	left = NULL;
	right = NULL;
	tab[0] = NULL;
	waga = NULL;
}

AVL_Tree::~AVL_Tree()
{

}

void AVL_Tree::RemoveAll()
{
	if (this->key == NULL)
	{
		cout << "Brak elementow do usuniecia\n";
		return;
	}
	AVL_Tree *aktualny = this, *parent = NULL, *grandparent = NULL;
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
	for (int i = 0; i < 15; i++)
		this->tab[i] = NULL;
	cout << "Usunieto wszystkie elementy \n";
	return;
}

AVL_Tree* AVL_Tree::Wstaw_Elementy(int ilosc_elementow)
{
	AVL_Tree* root = this; // potrzebny do zmiany korzenia podczas rotacji
	for (int counter = 0; counter < ilosc_elementow; counter++)
	{
		start:
		int newkey = ((((rand()*rand()) + (rand() % 2)) % 1000003)) + 10;

		vector<AVL_Tree *> droga; // inicjacia drogi po wezlach

		if (this->key == NULL) // brak korzenia
		{
			this->Set(newkey);
			this->waga = 0;
			goto end;
		}

		AVL_Tree *newnode = new AVL_Tree, *aktualny = root, *parent = NULL;
		newnode->Set(newkey); // ustawienie wartosci nowego wezla
		newnode->waga = 0; // ustawienie wysokosci startowej (domyslnie doczepiamy jako lisc o wysokosci 0)
		while (aktualny != NULL)
		{
			droga.push_back(aktualny);
			if (aktualny->key == newkey)
			{
				goto start; // powtorka
			}
			parent = aktualny;
			if (aktualny->key < newkey)
				aktualny = aktualny->right;
			else
				aktualny = aktualny->left;
		}
		if (parent->key > newkey)  // wstawienie w lewo
			parent->left = newnode;
		else // wstawienie w prawo
			parent->right = newnode;

		droga.push_back(newnode);
		// korygowanie wagi wezlow na drodze do korzenia
		for (int count = droga.size() - 2; count >= 0; count--)
		{
			if (droga[count]->left == droga[count + 1])
				droga[count]->waga -= 1; // zmiana wagi elementu lewego poddrzewa
			else
				droga[count]->waga += 1; // zmiana wagi elementu prawego poddrzewa

			if (droga[count]->waga == 0)
				goto end; // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
			if (droga[count]->waga == -2)  // wezel 
			{
				// konfiguracja jednorodna - (...)
				if (droga[count + 1]->waga == -1)
				{
					AVL_Tree *dziadek = NULL, *temp = NULL;
					if (count - 1 >= 0) // czy istnieje dziadek
						dziadek = droga[count - 1];
					// rotacja w prawo 
					temp = rot_r(dziadek, droga[count], droga[count + 1]);
					if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
						root = temp;
					droga[count]->waga = droga[count]->GiveWaga();
					droga[count + 1]->waga = droga[count + 1]->GiveWaga();
					goto end;
				}
				// konfiguracja niejednorodna - (...) ktory ma potomka tylko prawego
				else // droga[count + 1]->waga == 1
				{
					rot_l(droga[count], droga[count + 1], droga[count + 2]); // nie moze nastapic zmiana roota
					AVL_Tree *dziadek = NULL, *temp = NULL;
					if (count - 1 >= 0) // czy istnieje dziadek
						dziadek = droga[count - 1];
					temp = rot_r(dziadek, droga[count], droga[count + 2]);
					if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
						root = temp;
					droga[count + 1]->waga = droga[count + 1]->GiveWaga();
					droga[count]->waga = droga[count]->GiveWaga();
					droga[count + 2]->waga = droga[count + 2]->GiveWaga();
					goto end;
				}
			}
			if (droga[count]->waga == 2) // wezel ma potomka tylko prawego...
			{
				// konfiguracja jednorodna - (...) ktory ma potomka tylko prawego
				if (droga[count + 1]->waga == 1)
				{
					AVL_Tree *dziadek = NULL, *temp = NULL;
					if (count - 1 >= 0) // czy istnieje dziadek
						dziadek = droga[count - 1];
					// rotacja w prawo 
					temp = rot_l(dziadek, droga[count], droga[count + 1]);
					if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
						root = temp;
					droga[count]->waga = droga[count]->GiveWaga();
					droga[count + 1]->waga = droga[count + 1]->GiveWaga();
					goto end;
				}
				// konfiguracja niejednorodna - (...) ktory ma potomka tylko lewego
				else // droga[count + 1]->waga == -1
				{
					rot_r(droga[count], droga[count + 1], droga[count + 2]); // nie moze nastapic zmiana roota
					AVL_Tree *dziadek = NULL, *temp = NULL;
					if (count - 1 >= 0) // czy istnieje dziadek
						dziadek = droga[count - 1];
					temp = rot_l(dziadek, droga[count], droga[count + 2]);
					if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
						root = temp;
					droga[count + 1]->waga = droga[count + 1]->GiveWaga();
					droga[count]->waga = droga[count]->GiveWaga();
					droga[count + 2]->waga = droga[count + 2]->GiveWaga();
					goto end;
				}
			}
		}
	end:;
	}
	cout << "Wstawiono " << ilosc_elementow << " elementow\n";
	return(root);
}

AVL_Tree* AVL_Tree::Wstaw_Element(int newkey)
{
	AVL_Tree* root = this; // potrzebny do zmiany korzenia podczas rotacji
	if (this->key == NULL)
	{
		this->Set(newkey);
		this->waga = 0;
		cout << "Dodano korzen o wartosci kluczowej " << newkey << endl;
		return(root);
	}
	AVL_Tree *newnode = new AVL_Tree, *aktualny = this, *parent = NULL;
	newnode->Set(newkey); // ustawienie wartosci nowego wezla
	newnode->waga = 0; // ustawienie wysokosci startowej (domyslnie doczepiamy jako lisc o wysokosci 0)
	vector<AVL_Tree *> droga; // inicjacia drogi po wezlach
	while (aktualny != NULL)
	{
		droga.push_back(aktualny);
		if (aktualny->key == newkey)
		{
			cout << "Element o wartosci kluczowej " << newkey << " znajduje sie juz w drzewie\n";
			return(root);
		}
		parent = aktualny;
		if (aktualny->key < newkey)
			aktualny = aktualny->right;
		else
			aktualny = aktualny->left;
	}
	if (parent->key > newkey)  // wstawienie w lewo
		parent->left = newnode;
	else // wstawienie w prawo
		parent->right = newnode;
	cout << "Dodano element o wartosci kluczowej " << newkey << endl;
	droga.push_back(newnode);
	// korygowanie wagi wezlow na drodze do korzenia
	for (int count = droga.size() - 2; count >= 0; count--)
	{
		if (droga[count]->left == droga[count+1])
			droga[count]->waga -= 1; // zmiana wagi elementu lewego poddrzewa
		else
			droga[count]->waga += 1; // zmiana wagi elementu prawego poddrzewa

		if (droga[count]->waga == 0)
			return(root); // brak potrzeby korygowania dalej - wlasnosci lokalne = wlasnosci globalne
		if (droga[count]->waga == -2)  // wezel 
		{
			// konfiguracja jednorodna - (...)
			if (droga[count + 1]->waga == -1)
			{
				AVL_Tree *dziadek = NULL, *temp = NULL;
				if (count - 1 >= 0) // czy istnieje dziadek
					dziadek = droga[count - 1];
				// rotacja w prawo 
				temp = rot_r(dziadek, droga[count], droga[count + 1]);
				if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
					root = temp;
				droga[count]->waga = droga[count]->GiveWaga();
				droga[count + 1]->waga = droga[count + 1]->GiveWaga();
				return(root);
			}
			// konfiguracja niejednorodna - (...) ktory ma potomka tylko prawego
			else // droga[count + 1]->waga == 1
			{
				rot_l(droga[count], droga[count + 1], droga[count + 2]); // nie moze nastapic zmiana roota
				AVL_Tree *dziadek = NULL, *temp = NULL;
				if (count - 1 >= 0) // czy istnieje dziadek
					dziadek = droga[count - 1];
				temp = rot_r(dziadek, droga[count], droga[count + 2]);
				if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
					root = temp;
				droga[count + 1]->waga = droga[count + 1]->GiveWaga();
				droga[count]->waga = droga[count]->GiveWaga();
				droga[count + 2]->waga = droga[count + 2]->GiveWaga();
				return(root);
			}
		}
		if (droga[count]->waga == 2) // wezel ma potomka tylko prawego...
		{
			// konfiguracja jednorodna - (...) ktory ma potomka tylko prawego
			if (droga[count + 1]->waga == 1)
			{
				AVL_Tree *dziadek = NULL, *temp = NULL;
				if (count - 1 >= 0) // czy istnieje dziadek
					dziadek = droga[count - 1];
				// rotacja w prawo 
				temp = rot_l(dziadek, droga[count], droga[count + 1]);
				if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
					root = temp;
				droga[count]->waga = droga[count]->GiveWaga();
				droga[count + 1]->waga = droga[count + 1]->GiveWaga();
				return(root);
			}
			// konfiguracja niejednorodna - (...) ktory ma potomka tylko lewego
			else // droga[count + 1]->waga == -1
			{
				rot_r(droga[count], droga[count + 1], droga[count + 2]); // nie moze nastapic zmiana roota
				AVL_Tree *dziadek = NULL, *temp = NULL;
				if (count - 1 >= 0) // czy istnieje dziadek
					dziadek = droga[count - 1];
				temp = rot_l(dziadek, droga[count], droga[count + 2]);
				if (temp != NULL) // jesli temp sie zmienil - zmienil sie korzen
					root = temp;
				droga[count + 1]->waga = droga[count + 1]->GiveWaga();
				droga[count]->waga = droga[count]->GiveWaga();
				droga[count + 2]->waga = droga[count + 2]->GiveWaga();
				return(root);
			}
		}
	}
	return(root);
}

string AVL_Tree::GivePreorder()
{
	stringstream descr;
	AVL_Tree *aktualny = this;
	if (aktualny->key == NULL)
		return("Brak elementow\n");
	descr << aktualny->key << " ";
	//descr<< aktualny->key << " w"<<aktualny->waga<<"\n";
	if (aktualny->left != NULL)
		descr << aktualny->left->GivePreorder();
	if (aktualny->right != NULL)
		descr << aktualny->right->GivePreorder();
	return(descr.str());
}

string AVL_Tree::GiveInorder()
{
	stringstream descr;
	AVL_Tree *aktualny = this;
	if (aktualny->key == NULL)
		return("Brak elementow\n");
	if (aktualny->left != NULL)
		descr << aktualny->left->GiveInorder();
	descr << aktualny->key << " ";
	if (aktualny->right != NULL)
		descr << aktualny->right->GiveInorder();
	return(descr.str());
}

string AVL_Tree::GivePostorder()
{
	stringstream descr;
	AVL_Tree *aktualny = this;
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
	FILE* fp = fopen("inlab05.txt", "r");
	if (fp == NULL)
		return -1;
	int x1, k1, k2, k3, k4;
	fscanf(fp, "%d %d %d %d %d", &x1, &k1, &k2, &k3, &k4);
	fclose(fp);
	if (x1 < 0)
		return(-1); //Ilosc struktur nie moze byc mniejsz niz 0
	// czas start
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//TEST
	/*
	AVL_Tree *drzewo = new AVL_Tree;
		AVL_Tree *drzewo = new AVL_Tree;
		system("cls");
		drzewo = drzewo->Wstaw_Element(1000000);
		drzewo = drzewo->Wstaw_Element(1);
		drzewo = drzewo->Wstaw_Element(10000);
		drzewo = drzewo->Wstaw_Elementy(5);
		drzewo=drzewo->Remove(1);
		drzewo = drzewo->Remove(1000000);
		drzewo = drzewo->Remove(10000);
		cout << drzewo->ile()<<std::endl;
		cout << drzewo->GiveInorder()<<endl;
		if (5 != drzewo->ile())
			getchar();

	*/


	// dzialania
	cout << "Inicjacja drzewa AVL\n";
	AVL_Tree *drzewo = new AVL_Tree;
	drzewo = drzewo->Wstaw_Elementy(x1);
	cout << "Wysokosc drzewa to " << drzewo->GiveHeight() << endl;
	drzewo = drzewo->Wstaw_Element(k1);
	drzewo = drzewo->Wstaw_Element(k2);
	drzewo = drzewo->Wstaw_Element(k3);
	drzewo = drzewo->Wstaw_Element(k4);
	cout << "Wysokosc drzewa to " << drzewo->GiveHeight() << endl;
	drzewo->Find(k2);
	drzewo=drzewo->Remove(k1);
	cout << "Ilosc elementow w drzewie to " << drzewo->ile() << endl;
	cout << "Wysokosc drzewa to " << drzewo->GiveHeight() << endl;
	cout << "Drukowanie w kolejnosc Inorder (rosnacej)\n";
	getchar();
	//cout << drzewo->GiveInorder();

	//czas stop
	end = clock();
	time_spent = (double)(end - begin);
	printf("\nczas wykonywania - %f\n", time_spent);
	getchar();
}
