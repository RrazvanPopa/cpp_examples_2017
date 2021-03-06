#include "stdafx.h"
#include<iostream>

using namespace std;

template <typename T>
bool compare(T val1, T val2) {
	return val1 == val2;
}
//specializare cu char*
template <typename T=char*>
bool compare(char* val1, char* val2) {
	return _stricmp(val1, val2)==0;
}

template <typename T>
T multiply(T val1, T val2) {
	return val1 * val2;
}

//specializare pentru char*
template <typename T=char*>
char* multiply(char* val1, char* val2) {
	char* rezultat = new char[strlen(val1) + strlen(val2) + 1];
	if (strlen(val1) >= strlen(val2)) {
		strcpy(rezultat, val1);
		strcat(rezultat, val2);
	}
	else {
		strcpy(rezultat, val2);
		strcat(rezultat, val1);
	}
	return rezultat;
}
char* asChars(int i) {
	return (i == 0 ? "false" : "true");
}

enum Culoare {
	ROSU = 0,
	ALBASTRU=1,
	VERDE=2
};

template <typename T>
class Cutie {
private:
	Culoare culoare;
	int nr_obiecte;
	T* obiecte;

public:
	Cutie(Culoare v_culoare, int v_nr_obiecte, T* v_obiecte) {
		this->culoare = v_culoare;
		this->nr_obiecte = v_nr_obiecte;
		this->obiecte = new T[this->nr_obiecte];
		for (int i = 0; i < this->nr_obiecte; i++) {
			this->obiecte[i] = v_obiecte[i];
		}
	}
	~Cutie() {
		if (this->obiecte != NULL) {
			delete[] this->obiecte;
		}
	}

	Cutie(const Cutie& sursa) {
		this->culoare = sursa.culoare;
		this->nr_obiecte = sursa.nr_obiecte;
		this->obiecte = new T[this->nr_obiecte];
		for (int i = 0; i < this->nr_obiecte; i++) {
			this->obiecte[i] = sursa.obiecte[i];
		}
	}

	Cutie& operator=(const Cutie& sursa) {
		if (this->obiecte != NULL) {
			delete[] this->obiecte;
		}
		this->culoare = sursa.culoare;
		this->nr_obiecte = sursa.nr_obiecte;
		this->obiecte = new T[this->nr_obiecte];
		for (int i = 0; i < this->nr_obiecte; i++) {
			this->obiecte[i] = sursa.obiecte[i];
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, Cutie& c) {
		out <<"Culoare: "<< c.getCuloare() << endl;
		out << "Nr obiecte: " << c.nr_obiecte << endl;
		for (int i = 0; i < c.nr_obiecte; i++) {
			out << c.obiecte[i];
		}
		return out;
	}

	char* getCuloare() {
		switch (this->culoare) {
		case ROSU:
			return "rosu"; break;
		case VERDE:
			return "verde"; break;
		case ALBASTRU:
			return "albastru"; break;
		default:
			return "necunoscut";
		}
	}

	friend bool operator==(Cutie& c1, Cutie& c2) {
		return (c1.culoare == c2.culoare) && (c1.nr_obiecte == c2.nr_obiecte);
	}
};

class Jucarie {
private:
	char nume[50];
public:
	Jucarie() {
		strcpy(this->nume, "Lipsa");
	}
	Jucarie(char* v_nume) {
		strcpy(this->nume, v_nume);
	}

	friend ostream& operator<<(ostream& out, Jucarie& j) {
		out << "Nume: " << j.nume << endl;
		return out;
	}
};

class Carte {
private:
	char nume[25];
	int nr_pagini;

public:
	Carte(char v_nume[25], int v_nr_pagini) {
		strcpy(this->nume, v_nume);
		this->nr_pagini = v_nr_pagini;
	}

	friend ostream& operator<<(ostream& out, Carte* c) {
		out << "Nume: " << c->nume << ". " << "Nr pagini: " << c->nr_pagini << endl;
		return out;
	}
};

void main()
{
	cout << asChars(compare<int>(5, 6))  << endl;
	cout << asChars(compare<int>(5, 5)) << endl;
	cout << asChars(compare<float>(5.6f, 6.7f))  << endl;
	cout << asChars(compare<float>(5.6f, 5.6f)) << endl;
	cout << asChars(compare<char*>("IrIna", "irina")) << endl;
	cout << multiply<double>(5.2, 5) << endl;
	cout << multiply<int>(5, 10) << endl;
	cout << multiply<char*>("Irina", "Mihaela") << endl;

	Jucarie jucarii[2] = {Jucarie("Papusa"),Jucarie("Soldat")};
	Cutie<Jucarie> cutie1(ROSU, 2, jucarii);
	cout << cutie1;

	Jucarie jucarii2[2] = { Jucarie("Minge"),Jucarie("Ursulet") };
	Cutie<Jucarie> cutie2(ROSU, 2, jucarii2);
	cout << cutie2;

	cout << asChars(cutie1 == cutie2) << endl;

	Carte* carti[2] = { new Carte("Morometii", 500), new Carte("O noapte de vara", 655)};
	Cutie<Carte*> cutie3(ALBASTRU, 2, carti);
	cout << cutie3;
}

