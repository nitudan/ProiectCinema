#include <iostream>
#include <string>
#include <fstream>
#include <process.h>
#include <conio.h>
#include <vector>

using namespace std;

bool running = true;
int nrArticole;
char currentFile[256];

// FAZA 3 - 1) definirea metodelor virtuale pure
// Printare - clasa abstracta ce contine 2 metode virtuale pure
class Printare
{
public:
	virtual void print() = 0;

	virtual int locuriLibere() = 0;
};

// ################################## FAZA 1 ##################################

// Faza 3 - 2) utilizarea mostenirii - clasa Sala (clasa copil) este derivata clasei Printare (clasa parinte)
class Sala : public Printare {
private:

	const int idSala;
	int nrMaxLocuri;
	int nrRanduri;
	int nrLocuri;
	static int contor;

public:
	Sala() :idSala(++contor)
	{
		nrMaxLocuri = 0;
		nrRanduri = 0;
		nrLocuri = 0;
	}

	// constructor
	Sala(int nrMaxLocuri, int nrRanduri, int nrLocuri) :idSala(++contor)
	{
		if (nrRanduri > 0 && nrLocuri > 0)
		{
			this->nrMaxLocuri = nrMaxLocuri;
		}
		this->nrRanduri = nrRanduri;
		this->nrLocuri = nrLocuri;
	}

	// Faza3 - 3) utilizarea celor 2 metode virtuale (impure)
	// clasa Sala derivata din clasa abstracta Printare, are 2 metode virtuale impure ce fac override (prin implementare) la cele pure
	void print() override
	{
		cout << "Numar maxim locuri: " << nrMaxLocuri;
		cout << "Numar locuri: " << nrLocuri;
		cout << "Numar randuri: " << nrRanduri;
	}

	int locuriLibere() override
	{
		int locuriLibere = nrMaxLocuri - nrLocuri;

		return locuriLibere;
	}

	// constructor de copiere
	Sala(const Sala& c) :idSala(c.idSala)
	{
		this->nrMaxLocuri = c.nrMaxLocuri;
		this->nrRanduri = c.nrRanduri;
		this->nrLocuri = c.nrLocuri;
	}

	// operator egal
	Sala& operator=(const Sala& cp)
	{
		if (this != &cp)
		{
			if (cp.nrRanduri > 0 && cp.nrLocuri > 0)
			{
				this->nrMaxLocuri = cp.nrMaxLocuri;
			}
			this->nrRanduri = cp.nrRanduri;
			this->nrLocuri = cp.nrLocuri;
		}
		return *this;
	}

	// destructor
	~Sala()
	{
	}

	// getteri 

	int getIdSala() const
	{
		return this->idSala;
	}

	int getNrMaxLocuri()
	{
		return this->nrMaxLocuri;
	}

	int getNrRand()
	{
		return this->nrRanduri;
	}

	int getNrLocuri()
	{
		return this->nrLocuri;
	}

	// setteri
	void setNrMaxLocuri(int nrMaxLoc)
	{
		if (nrMaxLoc > 0)
		{
			this->nrMaxLocuri = nrMaxLoc;
		}
	}

	void setNrRanduri(int nrRanduri)
	{
		if (this->nrRanduri > 0)
		{
			this->nrRanduri = nrRanduri;
		}
	}

	void setNrLocuri(int nrLocuri)
	{
		if (this->nrLocuri > 0)
		{
			this->nrLocuri = nrLocuri;
		}
	}

	// operator de indexare
	/*int operator[] (int index)
	{
		if (index >= 0 && index < nrRand && nrLocuri != nullptr)
		{
			return nrLocuri[index];
		}
	}*/

	Sala operator+(int valoare)
	{
		Sala copie = *this;
		copie.nrRanduri += valoare;
		return copie;
	}

	//operator ++ post-incrementat
	Sala operator++(int)
	{
		Sala copie = *this;
		this->nrMaxLocuri++;
		return copie;
	}
	//operator ++ pre-incrementat
	Sala& operator++()
	{
		this->nrMaxLocuri++;
		return *this;
	}

	explicit operator int()
	{
		return nrRanduri;
	}

	bool operator!=(const Sala& s)
	{
		return this->nrMaxLocuri != s.nrMaxLocuri;
	}

	bool operator>(const Sala& s)
	{
		int nrMax1 = this->nrLocuri * this->nrRanduri;
		int nrMax2 = s.nrLocuri * s.nrRanduri;
		return nrMax1 > nrMax2;
	}

	bool operator==(const Sala& s)
	{
		return this->nrRanduri == s.nrRanduri;
	}
	//<<, >>, unul din + - * /, [], unul din ++ -- cu 2 forme, un cast, !, unul din < > =< =>, ==
	friend ostream& operator<<(ostream& o, Sala s);
	friend istream& operator>>(istream& i, Sala& s);


	void serializare(string numeFisier) //scriere in fisier
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		if (!f) {
			cout << "Cannot open file!" << endl;
		}
		cout << "Nr de locuri maxim este: " << endl;
		cin >> nrMaxLocuri;
		cout << "Cu un numar de randuri: " << endl;
		cin >> nrRanduri;
		cout << "Avand un numar de locuri pe rand egal cu: " << endl;
		cin >> nrLocuri;
		f.write((char*)&nrMaxLocuri, sizeof(nrMaxLocuri));
		f.write((char*)&nrRanduri, sizeof(nrRanduri));
		f.write((char*)&nrLocuri, sizeof(nrLocuri));
		f.close();
	}

	void deserializare(string numeFisier) //citire din fisier
	{
		ifstream f(numeFisier, ios::out | ios::binary);
		if (!f) {
			cout << "Cannot open file!" << endl;
		}
		f.read((char*)&nrMaxLocuri, sizeof(nrMaxLocuri));
		f.read((char*)&nrRanduri, sizeof(nrRanduri));
		f.read((char*)&nrLocuri, sizeof(nrLocuri));

		f.close();

		if (!f.good()) {
			cout << "Error occurred at reading time!" << endl;
		}
	}

	void afisareSala()
	{
		cout << "\nNr de locuri maxim: \n" << nrMaxLocuri << endl;
		cout << "\nNr de randuri: \n" << nrRanduri << endl;
		cout << "\nNr de locuri: \n" << nrLocuri << endl;
	}

	// Faza 3 - 4) Utilizarea sablonurilor (template)
	// functie sablon
	template <typename T>
	T comparatie(T nrMaxLocuri1, T nrMaxLocuri2)
	{
		return (nrMaxLocuri1 > nrMaxLocuri2) ? nrMaxLocuri1 : nrMaxLocuri2;
	}

};
int Sala::contor = 0;

// Faza 3 - 5) Utilizarea clasei sablon Array
template <class T>
class Array
{
private:
	T* pointer;
	int size;
public:
	Array()
	{
		pointer = nullptr;
		size = 0;
	}

	Array(unsigned size)
	{
		pointer = new T[size];
		this->size = size;
	}

	Array(const Array& arr)
	{
		if (arr.size > 0) {
			size = arr.size;
			pointer = new T[size];
			for (int i = 0; i < size; i++) {
				pointer[i] = arr.pointer[i];
			}
		}
		else {
			pointer = nullptr;
			size = 0;
		}
	}

	~Array()
	{
		delete[] pointer;
	}

	Array& operator=(const Array& arr)
	{
		delete[] pointer;
		if (arr.size > 0) {
			pointer = arr.pointer;
			for (int i = 0; i < size; i++) {
				pointer[i] = arr.pointer[i];
			}
		}
		else {
			pointer = nullptr;
			size = 0;
		}

		return *this;
	}

	T& operator[](int index)
	{
		if (index >= 0 && index < size) {
			return pointer[index];
		}
	}

	int getSize()
	{
		return size;
	}

	T* getPointer()
	{
		return pointer;
	}

	int setSize()
	{
		if (size > 0) {
			this->size = size;
		}
	}

	T* setPointer()
	{
		if (pointer != nullptr) {
			delete[] this->pointer;
		}
		if (this->size > 0) {
			this->size = size;
			this->pointer = new T[size];
			for (int i = 0; i < size; i++) {
				this->pointer[i] = pointer[i];
			}
		}
	}
};


class vectorSali
{
private:

	int nrSali;
	// Faza 3 - 5) Utilizarea compunerii a clasei Sala
	Sala* sali;
public:
	vectorSali()
	{
		nrSali = 0;
		sali = nullptr;
	}

	vectorSali(int nrSali, Sala* sali)
	{
		this->nrSali = nrSali;
		this->sali = new Sala[nrSali];
		for (int i = 0; i < nrSali; i++)
		{
			this->sali[i] = sali[i];
		}
	}

	vectorSali(const vectorSali& s)
	{
		this->nrSali = s.nrSali;
		this->sali = new Sala[s.nrSali];
		for (int i = 0; i < s.nrSali; i++)
		{
			this->sali[i] = s.sali[i];
		}
	}

	~vectorSali()
	{
		if (this->sali != NULL)
		{
			delete[]this->sali;
		}
	}

	vectorSali& operator=(const vectorSali& s)
	{
		if (this != &s)
		{
			if (this->sali != NULL)
			{
				delete[]this->sali;
			}
			this->nrSali = s.nrSali;
			this->sali = new Sala[s.nrSali];
			for (int i = 0; i < s.nrSali; i++)
			{
				this->sali[i] = s.sali[i];
			}
		}
		return *this;
	}

	int getNrSali()
	{
		return this->nrSali;
	}

	Sala* getSali()
	{
		if (this->sali != NULL)
		{
			Sala* copie = new Sala[this->nrSali];
			for (int i = 0; i < this->nrSali; i++)
			{
				copie[i] = this->sali[i];
			}
			return copie;
		}
		else
		{
			return NULL;
		}
	}

	void setSali(int nrSali, Sala* sali)
	{
		if (this->sali != NULL)
		{
			delete[]this->sali;
		}
		if (nrSali > 0 && sali != NULL)
		{
			this->nrSali = nrSali;
			this->sali = new Sala[nrSali];
			for (int i = 0; i < nrSali; i++)
			{
				this->sali[i] = sali[i];
			}
		}
		else
		{
			cout << "Intampinam o problema in setarea salilor!" << endl;
		}
	}


	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::app | ios::binary);
		//scrierea in fisier binar a unui numeric
		f.write((char*)&nrSali, sizeof(int));
		//scrierea in fisier binar a unui int*
		for (int i = 0; i < nrSali; i++)
		{
			f.write((char*)&sali[i], sizeof(Sala));
		}
		f.close();
	}

	void deserializare(string numeFisier)
	{
		ifstream f(numeFisier, ios::in | ios::binary);
		if (!f) {
			cout << "Cannot open file!" << endl;
		}
		f.read((char*)&nrSali, sizeof(int));
		if (sali != NULL)
		{
			delete[]sali;
		}
		sali = new Sala[nrSali];
		for (int i = 0; i < nrSali; i++)
		{
			f.read((char*)&sali[i], sizeof(Sala));
		}
		f.close();
		if (!f.good())
		{
			cout << "Error occurred at reading time!" << endl;
		}
	}

	vectorSali& operator+=(Sala& sala)
	{
		Sala* copie = new Sala[this->nrSali];
		for (int i = 0; i < this->nrSali; i++)
		{
			copie[i] = this->sali[i];
		}

		this->sali = new Sala[this->nrSali + 1];
		for (int i = 0; i < this->nrSali; i++)
		{
			this->sali[i] = copie[i];
		}
		this->sali[this->nrSali] = sala;
		this->nrSali++;
		delete[]copie;
		return *this;
	}

	void addSala(Sala sala)
	{
		vectorSali copie = *this;
		delete[]this->sali;
		this->nrSali++;
		this->sali = new Sala[this->nrSali];
		for (int i = 0; i < copie.nrSali; i++)
		{
			this->sali[i] = copie.sali[i];
		}
		for (int i = copie.nrSali; i < this->nrSali; i++)
		{
			this->sali[i] = sala;
		}
	}

	void afisareSali()
	{
		int nr = 1;
		this->deserializare("Sali.bin");
		cout << "Avem disponibile urmatoare sali: " << endl;
		for (int i = 0; i < nrSali; i++)
		{

			cout << "\nSala: " << nr << "\n";
			cout << this->sali[i] << endl;
			nr++;
		}
		cout << endl;
	}


	friend ostream& operator << (ostream& out, vectorSali vs);

	friend istream& operator >>(istream& in, vectorSali& vs);

	void adaugareSali()
	{
		Sala s;
		deserializare("Sali.bin");
		//int nr = 0;
		//cout << "Cate sali ai dori sa adaugi?" << endl;
		//cin >> nr;
		//for (int i = 0;i < nr; i++)
		//{
		cout << "\nTe rugam sa introduci datele: " << endl;
		cin >> s;
		addSala(s);
		cout << "\nSala a fost adaugata!\n" << endl;
		//}
		remove("Sali.bin");
		serializare("Sali.bin");
	}

	void stergereSala(int nrCurent)
	{
		deserializare("Sali.bin");
		int nr = 0;
		Sala* copie = new Sala[this->nrSali];
		for (int i = 0; i < this->nrSali; i++)
		{
			if (i != (nrCurent - 1))
			{
				copie[nr] = this->sali[i];
				nr++;
			}
		}
		delete[] this->sali;
		this->nrSali = nr;
		this->sali = new Sala[nr];
		for (int i = 0; i < nr; i++)
		{
			this->sali[i] = copie[i];
		}
		remove("Sali.bin");
		serializare("Sali.bin");
	}

	void modificareSali()
	{
		afisareSali();
		int nrCurent;
		cout << "\nSelectati numarul salii: " << endl;
		cin >> nrCurent;
		stergereSala(nrCurent);
		this->adaugareSali();
		remove("Sali.bin");
		this->serializare("Sali.bin");
	}
};

class Program
{
public:
	//enum Zile { luni = 1, marti = 2, miercuri = 3, joi = 4, vineri = 5, sambata = 6, duminica=7 };
	//enum Ore { interval1 = 10-13, interval2 = 13-16, interval3 = 16-19, interval4 = 19-22 };
private:
	//Zile zi;
	//Ore ora;
	string zi;
	double ora;

public:
	Program()
	{
		zi = "";
		ora = 0;
	}

	//constructor
	Program(string zi, double ora)
	{
		if (zi.length() > 0) {
			this->zi = zi;
		}

		if (ora > 0) {
			this->ora = ora;
		}
	}


	string getZi()
	{
		return zi;
	}

	double getOra()
	{
		return ora;
	}

	void setZi(string zi)
	{
		if (zi.length() >= 3)
		{
			//if (zi >= 1 && zi <= 7)
			//{
			this->zi = zi;
			//}
		}
	}

	void setOra(double ora)
	{
		if (ora >= 10 && ora <= 22)
		{
			this->ora = ora;
		}
	}

	float operator [](float index)
	{
		return ora;
	}

	//operator ++ post-incrementat
	Program operator--(int)
	{
		Program copie = *this;
		this->ora--;
		return copie;
	}
	//operator ++ pre-incrementat
	Program& operator--()
	{
		this->ora--;
		return *this;
	}

	explicit operator string()
	{
		return zi;
	}

	bool operator!=(const Program& p)
	{
		return this->zi != p.zi;
	}

	bool operator>(const Program& p)
	{
		return this->ora > p.ora;
	}

	bool operator==(const Program& p)
	{
		return this->ora == p.ora;
	}
	//<<, >>, unul din + - * /, [], unul din ++ -- cu 2 forme, un cast, !, unul din < > =< =>, ==
	friend ostream& operator<<(ostream& o, Program p);
	friend istream& operator>>(istream& i, Program& p);

	//fisierele binare
	//nu scriem/citim din fisier variabilele constante sau statice, niciodata!!
	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		int dimZi = this->zi.size();
		f.write((char*)&dimZi, sizeof(dimZi));
		f.write(this->zi.c_str(), dimZi + 1);
		f.write((char*)&ora, sizeof(ora));

	}
	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in | ios::binary);
		//asa citim string in binar
		int dimZi = 0;
		f.read((char*)&dimZi, sizeof(dimZi));
		char* aux;
		aux = new char[dimZi + 1];
		f.read(aux, dimZi + 1);
		this->zi = aux;
		delete[]aux;
		//asa citim int in binar
		f.read((char*)&ora, sizeof(ora));
	}

};

class Film
{
private:

	char* nume;
	string tipFilm;
	int durata;
	float pret;
	int nrDifuzari;
	Program** program;
public:

	Film()
	{
		nume = nullptr;
		tipFilm = "Necunoscut";
		durata = 0;
		pret = 0;
		nrDifuzari = 0;
		program = new Program * [0];
	}

	Film(char* nume, string tipFilm, int durata, float pret, int nrDifuzari, Program** program)
	{
		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		if (tipFilm.length() > 0) {
			this->tipFilm = tipFilm;
		}

		if (durata > 0) {
			this->durata = durata;
		}

		this->pret = pret;


		if (program != nullptr && nrDifuzari > 0)
		{
			this->nrDifuzari = nrDifuzari;
			this->program = new Program * [nrDifuzari];
			for (int i = 0; i < nrDifuzari; i++)
			{
				this->program[i] = program[i];
			}
		}
		else {
			this->program = nullptr;
			this->nrDifuzari = 0;
		}

	}

	~Film()
	{
		if (this->nume != NULL)
		{
			delete[]this->nume;
		}

		/*	if (this->program != NULL)
			{
				delete[]this->program;
			}*/
	}

	Film(const Film& f)
	{
		if (f.nume != nullptr) {
			nume = new char[strlen(f.nume) + 1];
			strcpy_s(nume, strlen(f.nume) + 1, f.nume);
		}
		else {
			nume = nullptr;
		}

		tipFilm = f.tipFilm;
		durata = f.durata;
		pret = f.pret;

		if (f.program != nullptr && f.nrDifuzari > 0) {
			nrDifuzari = f.nrDifuzari;
			program = new Program * [f.nrDifuzari];
			for (int i = 0; i < f.nrDifuzari; i++)
			{
				program[i] = f.program[i];
			}
		}
		else {
			program = nullptr;
			nrDifuzari = 0;
		}
	}

	Film operator=(const Film& f)
	{
		if (this != &f)
		{
			if (this->nume != NULL)
			{
				delete[]this->nume;
			}

			if (this->program != NULL)
			{
				delete[]this->program;
			}

			if (f.nume != nullptr) {
				nume = new char[strlen(f.nume) + 1];
				strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
			}
			else {
				nume = nullptr;
			}

			tipFilm = f.tipFilm;
			durata = f.durata;
			pret = f.pret;

			if (f.program != nullptr && f.nrDifuzari > 0) {
				nrDifuzari = f.nrDifuzari;
				program = new Program * [f.nrDifuzari];
				for (int i = 0; i < f.nrDifuzari; i++)
				{
					program[i] = f.program[i];
				}
			}
			else {
				nrDifuzari = 0;
				program = nullptr;
			}

			return *this;
		}
	}

	char* getNume()
	{
		return nume;
	}

	void setNume(const char* nume)
	{
		if (this->nume != nullptr)
		{
			delete[]this->nume;
		}

		if (nume != nullptr) {
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			nume = nullptr;
		}
	}

	string getTipFilm()
	{
		return tipFilm;
	}

	void setTipFilm(string tipFilm)
	{
		if (tipFilm.length() > 0)
		{
			this->tipFilm = tipFilm;
		}
	}

	int getDurata()
	{
		return durata;
	}

	void setDurata(int durata)
	{
		if (durata > 0)
		{
			this->durata = durata;
		}
	}

	float getPret()
	{
		return pret;
	}

	void setPret(float pret)
	{
		if (pret > 0)
		{
			this->pret = pret;
		}
	}

	int getNrDifuzari()
	{
		return nrDifuzari;
	}

	Program** getProgram()
	{
		return program;
	}

	void setProgram(int nrDifuzari, Program** program)
	{
		if (this->program != nullptr)
		{
			delete[]this->program;
		}
		if (nrDifuzari > 0 && program != nullptr)
		{
			this->nrDifuzari = nrDifuzari;
			this->program = new Program * [nrDifuzari];
			for (int i = 0; i < nrDifuzari; i++)
			{
				this->program[i] = program[i];
			}
		}
		else {
			this->program = nullptr;
			this->nrDifuzari = 0;

		}
	}

	Program* operator [](int index)
	{
		if (index >= 0 && index < nrDifuzari)
		{
			return this->program[index];
		}
	}

	//operator ++ post-incrementat
	Film operator++(int)
	{
		Film copie = *this;
		this->pret++;
		return copie;
	}
	//operator ++ pre-incrementat
	Film& operator++()
	{
		this->pret++;
		return *this;
	}

	explicit operator string()
	{
		return tipFilm;
	}

	bool operator!=(const Film& p)
	{
		return this->durata != p.durata;
	}

	bool operator<(const Film& p)
	{
		return this->pret < p.pret;
	}

	bool operator==(const Film& p)
	{
		return this->nrDifuzari == p.nrDifuzari;
	}
	//<<, >>, unul din + - * /, [], unul din ++ -- cu 2 forme, un cast, !, unul din < > =< =>, ==
	friend ostream& operator<<(ostream& o, Film f);
	friend istream& operator>>(istream& i, Film& f);

	Film& operator+=(Program& p)
	{
		Program** copie = new Program * [this->nrDifuzari];
		for (int i = 0; i < this->nrDifuzari; i++)
			copie[i] = this->program[i];

		this->program = new Program * [this->nrDifuzari + 1];
		for (int i = 0; i < this->nrDifuzari; i++)
			this->program[i] = copie[i];

		this->program[this->nrDifuzari] = &p;

		this->nrDifuzari++;

		delete[] copie;
		return *this;
	}
	//fisierele binare
	//nu scriem/citim din fisier variabilele constante sau statice, niciodata!!
	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		//la char* respectiv string trebuie sa dam mai intai dimensiunea
		//scrierea in fisier binar a unuichar*
		int dimensiuneNume = strlen(this->nume);
		f.write((char*)&dimensiuneNume, sizeof(dimensiuneNume));
		f.write(this->nume, dimensiuneNume + 1);
		//scrierea in fisier binar a unui string
		int dimTipFilm = this->tipFilm.size();
		f.write((char*)&dimTipFilm, sizeof(dimTipFilm));
		f.write(this->tipFilm.c_str(), dimTipFilm + 1);
		//functia c_str() --- converste string-ul intr-un const char* si ii adauga la final si terminatorul \0

		//scrierea in fisier binar a unui numeric
		f.write((char*)&durata, sizeof(durata));
		f.write((char*)&pret, sizeof(pret));
		f.write((char*)&nrDifuzari, sizeof(nrDifuzari));
		//scrierea in fisier binar a unui int*
		for (int i = 0; i < nrDifuzari; i++)
		{
			f.write((char*)&program[i], sizeof(program[i]));
		}
	}
	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in | ios::binary);
		//asa citim char* din binar
		int dimNume = 0;
		f.read((char*)&dimNume, sizeof(dimNume));
		delete[]nume;
		nume = new char[dimNume + 1];
		f.read(this->nume, dimNume + 1);
		//asa citim string in binar
		int dimTipFilm = 0;
		f.read((char*)&dimTipFilm, sizeof(dimTipFilm));
		char* aux;
		aux = new char[dimTipFilm + 1];
		f.read(aux, dimTipFilm + 1);
		this->tipFilm = aux;
		delete[]aux;

		//asa citim int in binar

		f.read((char*)&durata, sizeof(durata));
		f.read((char*)&pret, sizeof(pret));
		f.read((char*)&nrDifuzari, sizeof(nrDifuzari));
		delete[]this->program;
		this->program = new Program * [this->nrDifuzari];
		for (int i = 0; i < nrDifuzari; i++)
		{
			f.read((char*)&program[i], sizeof(program[i]));
		}
	}

};

class vectorFilme
{
private:
	int nrFilme;
	Film* filme;
public:
	vectorFilme()
	{
		nrFilme = 0;
		filme = nullptr;
	}

	vectorFilme(int nrFilme, Film* filme)
	{
		this->nrFilme = nrFilme;
		this->filme = new Film[nrFilme];
		for (int i = 0; i < nrFilme; i++)
		{
			this->filme[i] = filme[i];
		}
	}

	vectorFilme(const vectorFilme& vf)
	{
		this->nrFilme = vf.nrFilme;
		this->filme = new Film[vf.nrFilme];
		for (int i = 0; i < vf.nrFilme; i++)
		{
			this->filme[i] = vf.filme[i];
		}
	}

	~vectorFilme()
	{
		if (this->filme != NULL)
		{
			delete[]this->filme;
		}
	}

	vectorFilme& operator=(const vectorFilme& vf)
	{
		if (this != &vf)
		{
			if (this->filme != NULL)
			{
				delete[]this->filme;
			}
			this->nrFilme = vf.nrFilme;
			this->filme = new Film[vf.nrFilme];
			for (int i = 0; i < vf.nrFilme; i++)
			{
				this->filme[i] = vf.filme[i];
			}
		}
		return *this;
	}

	int getNrFilme()
	{
		return this->nrFilme;
	}

	Film* getFilme()
	{
		return this->filme;
	}

	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		//scrierea in fisier binar a unui numeric
		f.write((char*)&nrFilme, sizeof(int));
		//scrierea in fisier binar a unui int*

		filme = new Film[nrFilme];
		int length = sizeof(filme);
		f.write((char*)&length, sizeof(int));
		for (int i = 0; i < nrFilme; i++)
		{
			f.write((char*)&filme[i], length);
		}
		f.close();
	}

	void deserializare(string numeFisier)
	{
		ifstream f(numeFisier, ios::in | ios::binary);
		if (!f) {
			cout << "Cannot open file!" << endl;
		}
		int length = 0;
		f.read((char*)&length, sizeof(int));
		f.read((char*)&nrFilme, sizeof(int));
		if (filme != nullptr)
		{
			delete[]filme;
		}
		filme = new Film[nrFilme];
		for (int i = 0; i < nrFilme; i++)
		{
			f.read((char*)&filme[i], length);
		}
		f.close();
		if (!f.good()) {
			cout << "Error occurred at reading time!" << endl;
		}
	}

	vectorFilme& operator+=(Film& film)
	{
		Film* copie = new Film[this->nrFilme];
		for (int i = 0; i < this->nrFilme; i++)
		{
			copie[i] = this->filme[i];
		}

		this->filme = new Film[this->nrFilme + 1];
		for (int i = 0; i < this->nrFilme; i++)
		{
			this->filme[i] = copie[i];
		}
		this->filme[this->nrFilme] = film;
		this->nrFilme++;
		delete[]copie;
		return *this;
	}

	void addFilm(Film film)
	{
		vectorFilme copie = *this;
		delete[]this->filme;
		this->nrFilme++;
		this->filme = new Film[this->nrFilme];
		for (int i = 0; i < copie.nrFilme; i++)
		{
			this->filme[i] = copie.filme[i];
		}
		for (int i = copie.nrFilme; i < this->nrFilme; i++)
		{
			this->filme[i] = film;
		}
	}

	void afisareFilme()
	{
		int nr = 1;
		this->deserializare("Film.bin");
		cout << "Avem disponibile urmatoare filme: " << endl;
		for (int i = 0; i < nrFilme; i++)
		{

			cout << "\nFilm: " << nr << "\n";
			cout << this->filme[i] << endl;
			nr++;
		}
		cout << endl;

		/*cout << "Urmatoarele filme ruleaza in cinematograful nostru: " << endl;
		for (int i = 0; i < nrFilme; i++)
		{
			cout << *filme[i] << endl;
		}
		cout << endl;*/
	}

	void adaugareFilme()
	{
		Film f;
		//deserializare("Film.bin");
		cout << "\nTe rugam sa introduci datele: " << endl;
		cin >> f;
		addFilm(f);
		cout << "\nFilmul a fost adaugat!\n" << endl;
		remove("Film.bin");
		serializare("Film.bin");
		afisareFilme();
	}

	friend ostream& operator << (ostream& out, vectorFilme vf);

	friend istream& operator >>(istream& in, vectorFilme& vf);

};

//class Reducere
//{
//public:
//	enum TipReducere { adult = 0, elev = 50, student = 50, pensionar = 50 };
//private:
//	string denumire;
//	TipReducere reducere;
//public:
//	Reducere() {
//		reducere = adult;
//		denumire = "Necunoscut";
//	}
//	Reducere(string denumire, TipReducere reducere) {
//		this->denumire = denumire;
//		this->reducere = reducere;
//	}
//
//	string getDenumire() {
//		return this->denumire;
//	}
//	TipReducere getReducere() {
//		return this->reducere;
//	}
//
//	void setDenumire(string denumire) {
//		if (denumire.length() > 1) {
//			this->denumire = denumire;
//		}
//	}
//	void setTipReducere(TipReducere reducere) {
//		if (reducere == elev || reducere == student || reducere == pensionar)
//		{
//			this->reducere = reducere;
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, Reducere r);
//	friend istream& operator>>(istream& in, Reducere& r);
//
//	TipReducere operator [](int index)
//	{
//		return reducere;
//	}
//
//	//operator ++ post-incrementat
//	/*Reducere operator++(int)
//	{
//		Reducere copie = *this;
//		this->denumire++;
//		return copie;
//	}*/
//	//operator ++ pre-incrementat
//	/*Reducere& operator++()
//	{
//		this->reducere++;
//		return *this;
//	}*/
//
//	explicit operator string()
//	{
//		return denumire;
//	}
//
//	bool operator!=(const Reducere& p)
//	{
//		return this->denumire != p.denumire;
//	}
//
//	bool operator<(const Reducere& p)
//	{
//		return this->reducere < p.reducere;
//	}
//
//	bool operator==(const Reducere& p)
//	{
//		return this->denumire == p.denumire;
//	}
//
//};
//
//class Client : public Reducere {
//private:
//	string nume;
//public:
//
//	Client() :Reducere() {
//		nume = "Necunoscut";
//	}
//
//	Client(string denumire, TipReducere reducere, string nume) :Reducere(denumire, reducere)
//	{
//		this->nume = nume;
//	}
//	string getNume() {
//
//		return this->nume;
//	}
//	void setNume(string nume) {
//		if (nume.length() > 3) {
//			this->nume = nume;
//		}
//	}
//
//	friend ostream& operator<<(ostream& out, Client c);
//	friend istream& operator>>(istream& in, Client& c);
//
//	string operator [](int index)
//	{
//		return nume;
//	}
//
//	//operator ++ post-incrementat
//	/*Reducere operator++(int)
//	{
//		Reducere copie = *this;
//		this->denumire++;
//		return copie;
//	}*/
//	//operator ++ pre-incrementat
//	/*Reducere& operator++()
//	{
//		this->reducere++;
//		return *this;
//	}*/
//
//	explicit operator string()
//	{
//		return nume;
//	}
//
//	bool operator!=(const Client& p)
//	{
//		return this->nume != p.nume;
//	}
//
//	bool operator<(const Client& p)
//	{
//		return this->nume < p.nume;
//	}
//
//	bool operator==(const Client& p)
//	{
//		return this->nume == p.nume;
//	}
//};

class Bilet : public Film, public Sala
{
private:

	Film film;
	Sala sala;
	string tipClient;
	float reducere;
	//Program program;
	float pretTotal;
public:


	Bilet() :Film(), Sala()
	{
		this->tipClient = "Necunoscut";
		this->reducere = 0;
		this->pretTotal = 0;
	}

	Bilet(char* nume, string tipFilm, int durata, float pret, int nrDifuzari, Program** program, int nrMaxLocuri, int nrRanduri, int nrLocuri, string tipClient, float reducere, float pretTotal) :Film(nume, tipFilm, durata, pret, nrDifuzari, program), Sala(nrMaxLocuri, nrRanduri, nrLocuri)
	{
		if (tipClient == "adult" || tipClient == "elev" || tipClient == "student" || tipClient == "pensionar")
		{
			this->tipClient = tipClient;
		}
		else
		{
			cout << "Trebuie sa selectati una din urmatoare optiuni: adult | elev | student | pensionar";
		}
		if (reducere >= 0 && reducere <= 100)
		{
			this->reducere = reducere;
		}
		else
		{
			cout << "Va rugam sa aplicati o reducere viabila!";
		}
		this->pretTotal = pretTotal;
	}

	Bilet(const Bilet& b) :Film(b), Sala(b)
	{
		if (b.tipClient == "adult" || b.tipClient == "elev" || b.tipClient == "student" || b.tipClient == "pensionar")
		{
			this->tipClient = b.tipClient;
		}
		else
		{
			cout << "Trebuie sa selectati una din urmatoare optiuni: adult | elev | student | pensionar";
		}
		if (b.reducere >= 0 && b.reducere <= 100)
		{
			this->reducere = b.reducere;
		}
		else
		{
			cout << "Va rugam sa aplicati o reducere viabila!";
		}
		this->pretTotal = b.pretTotal;
	}



	Bilet& operator=(const Bilet& b)
	{
		if (this != &b) {
			if (b.tipClient == "adult" || b.tipClient == "elev" || b.tipClient == "student" || b.tipClient == "pensionar")
			{
				this->tipClient = b.tipClient;
			}
			else
			{
				cout << "Trebuie sa selectati una din urmatoare optiuni: adult | elev | student | pensionar";
			}
			if (b.reducere >= 0 && b.reducere <= 100)
			{
				this->reducere = b.reducere;
			}
			else
			{
				cout << "Va rugam sa aplicati o reducere viabila!";
			}
			this->pretTotal = b.pretTotal;
		}
		return *this;
	}

	/*float operator [](int index)
	{
		if (index >= 0 && index < 100)
		{
			return reducere;
		}
	}*/

	//operator ++ post-incrementat
	Bilet operator++(int)
	{
		Bilet copie = *this;
		this->reducere++;
		return copie;
	}

	//operator ++ pre-incrementat
	Bilet& operator++()
	{
		this->reducere++;
		return *this;
	}

	explicit operator float()
	{
		return pretTotal;
	}

	bool operator!=(const Bilet& b)
	{
		return this->pretTotal != b.pretTotal;
	}

	bool operator<(const Bilet& b)
	{
		return this->reducere < b.reducere;
	}

	bool operator==(const Bilet& b)
	{
		return this->tipClient == b.tipClient;
	}

	friend ostream& operator<<(ostream& out, Bilet b);
	friend istream& operator>>(istream& in, Bilet& b);

	//Film film;
	//Sala sala;
	//string tipClient;
	//float reducere;
	////Program program;
	//float pretTotal;

	//fisierele binare
	//nu scriem/citim din fisier variabilele constante sau statice, niciodata!!
	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		f.write((char*)&film, sizeof(film));
		f.write((char*)&sala, sizeof(sala));
		int dimTipClient = this->tipClient.size();
		f.write((char*)&dimTipClient, sizeof(dimTipClient));
		f.write(this->tipClient.c_str(), dimTipClient + 1);
		f.write((char*)&reducere, sizeof(reducere));
		f.write((char*)&pretTotal, sizeof(pretTotal));
	}

	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in | ios::binary);
		f.read((char*)&film, sizeof(film));
		f.read((char*)&sala, sizeof(sala));
		//asa citim string in binar
		int dimTipClient = 0;
		f.read((char*)&dimTipClient, sizeof(dimTipClient));
		char* aux;
		aux = new char[dimTipClient + 1];
		f.read(aux, dimTipClient + 1);
		this->tipClient = aux;
		delete[]aux;
		f.read((char*)&reducere, sizeof(reducere));
		f.read((char*)&pretTotal, sizeof(pretTotal));
	}

	/*void adaugareBilet()
	{
		Bilet copie = *this;

		cout << "\nIntroduceti filmul pe care doriti sa il vizionati : \n\n";
		cout << "\t1)Home Alone\n";
		cout << "\t2)Harry Potter\n";
		cout << "\t3)The Lord of the Rings\n";
		cin >> film;
		cout << "filmul ales" << film << endl;

		cout << "Introduceti sala in care doriti sa vizionati filmul. Salile sunt numerotate de la A la E.\n";
		cin >> sala;
		cout << "sala aleasa" << sala;

		cout << "Preturile sunt urmatoarele in functie de varsta: \n";
		cout << "- Copil: 18 lei";
		cout << "- Adult: 28 lei";
		cout << "- Pensionar: 18 lei";
		cin >> pretTotal;
		cout << "pret total" << pretTotal << endl;


	}*/
};


class Cinematograf
{
private:

	string nume;
	int nrSali;
	Sala* sali;
	int nrFilme;
	Film* filme;
	int nrBilete;
	Bilet* bilete;

public:

	Cinematograf()
	{
		nume = "Necunoscut";
		nrSali = 0;
		sali = nullptr;
		nrFilme = 0;
		filme = nullptr;
		nrBilete = 0;
		bilete = nullptr;
	}

	Cinematograf(string nume, int nrSali, Sala* sali, int nrFilme, Film* filme, int nrBilete, Bilet* bilete)
	{
		this->nume = nume;
		this->nrSali = nrSali;
		this->sali = new Sala[nrSali];
		for (int i = 0; i < nrSali; i++)
		{
			this->sali[i] = sali[i];
		}
		this->filme = filme;
		this->filme = new Film[nrSali];
		for (int i = 0; i < nrSali; i++)
		{
			this->filme[i] = filme[i];
		}
		this->nrBilete = nrBilete;
		this->bilete = new Bilet[nrBilete];
		for (int i = 0; i < nrBilete; i++)
		{
			this->bilete[i] = bilete[i];
		}
	}

	Cinematograf(const Cinematograf& c)
	{
		this->nume = c.nume;
		this->nrSali = c.nrSali;
		this->sali = new Sala[c.nrSali];
		for (int i = 0; i < c.nrSali; i++)
		{
			this->sali[i] = c.sali[i];
		}
		this->filme = c.filme;
		this->filme = new Film[c.nrSali];
		for (int i = 0; i < c.nrSali; i++)
		{
			this->filme[i] = c.filme[i];
		}
		this->nrBilete = c.nrBilete;
		this->bilete = new Bilet[c.nrBilete];
		for (int i = 0; i < c.nrBilete; i++)
		{
			this->bilete[i] = c.bilete[i];
		}
	}

	~Cinematograf()
	{
		if (this->sali != NULL)
		{
			delete[]this->sali;
		}
		if (this->filme != NULL)
		{
			delete[]this->filme;
		}
		if (this->bilete != NULL)
		{
			delete[]this->bilete;
		}
	}

	Cinematograf& operator=(const Cinematograf& c)
	{
		if (this != &c)
		{
			if (this->sali != NULL)
			{
				delete[]this->sali;
			}
			if (this->filme != NULL)
			{
				delete[]this->filme;
			}
			if (this->bilete != NULL)
			{
				delete[]this->bilete;
			}
			this->nume = c.nume;
			this->nrSali = c.nrSali;
			this->sali = new Sala[c.nrSali];
			for (int i = 0; i < c.nrSali; i++)
			{
				this->sali[i] = c.sali[i];
			}
			this->filme = c.filme;
			this->filme = new Film[c.nrSali];
			for (int i = 0; i < c.nrSali; i++)
			{
				this->filme[i] = c.filme[i];
			}
			this->nrBilete = c.nrBilete;
			this->bilete = new Bilet[c.nrBilete];
			for (int i = 0; i < c.nrBilete; i++)
			{
				this->bilete[i] = c.bilete[i];
			}
		}
		return *this;
	}

	Sala* getSali()
	{
		if (this->sali != NULL)
		{
			Sala* copie = new Sala[this->nrSali];
			for (int i = 0; i < nrSali; i++)
			{
				copie[i] = this->sali[i];
			}
			return copie;
		}
		else
		{
			return NULL;
		}
	}

	int getNrSali()
	{
		return nrSali;
	}

	/*float operator [](int index)
	{
		if (index >= 0 && index < 100)
		{
			return reducere;
		}
	}*/

	//operator ++ post-incrementat
	Cinematograf operator++(int)
	{
		Cinematograf copie = *this;
		this->nrSali++;
		return copie;
	}

	//operator ++ pre-incrementat
	Cinematograf& operator++()
	{
		this->nrFilme++;
		return *this;
	}

	explicit operator int()
	{
		return nrBilete;
	}

	bool operator!=(const Cinematograf& b)
	{
		return this->nrFilme != b.nrFilme;
	}

	bool operator<(const Cinematograf& b)
	{
		return this->nrSali < b.nrSali;
	}

	bool operator==(const Cinematograf& b)
	{
		return this->nume == b.nume;
	}

	friend ostream& operator<<(ostream& out, Cinematograf c);
	friend istream& operator>>(istream& in, Cinematograf& c);

	void serializare(string numeFisier)
	{
		ofstream f(numeFisier, ios::out | ios::binary);
		//scrierea in fisier binar a unui string
		int dimensiuneNume = this->nume.size();
		f.write((char*)&dimensiuneNume, sizeof(dimensiuneNume));
		f.write(this->nume.c_str(), dimensiuneNume + 1);
		//functia c_str() --- converste string-ul intr-un const char* si ii adauga la final si terminatorul \0
		//scrierea in fisier binar a unui numeric
		f.write((char*)&nrSali, sizeof(nrSali));
		for (int i = 0; i < nrSali; i++)
		{
			f.write((char*)&sali[i], sizeof(sali[i]));
		}
		f.write((char*)&nrFilme, sizeof(nrFilme));
		//scrierea in fisier binar a unui int*
		for (int i = 0; i < nrFilme; i++)
		{
			f.write((char*)&filme[i], sizeof(filme[i]));
		}
		f.write((char*)&nrBilete, sizeof(nrBilete));
		//scrierea in fisier binar a unui int*
		for (int i = 0; i < nrBilete; i++)
		{
			f.write((char*)&bilete[i], sizeof(bilete[i]));
		}
	}

	void deserializare(string numeFile)
	{
		ifstream f(numeFile, ios::in | ios::binary);
		//asa citim string in binar
		int dimNume = 0;
		f.read((char*)&dimNume, sizeof(dimNume));
		char* aux;
		aux = new char[dimNume + 1];
		f.read(aux, dimNume + 1);
		this->nume = aux;
		delete[]aux;
		//asa citim int in binar
		f.read((char*)&nrSali, sizeof(nrSali));
		delete[]this->sali;
		this->sali = new Sala[this->nrSali];
		for (int i = 0; i < nrSali; i++)
		{
			f.read((char*)&sali[i], sizeof(sali[i]));
		}
		f.read((char*)&nrFilme, sizeof(nrFilme));
		delete[]this->filme;
		this->filme = new Film[this->nrFilme];
		for (int i = 0; i < nrFilme; i++)
		{
			f.read((char*)&filme[i], sizeof(filme[i]));
		}
		f.read((char*)&nrBilete, sizeof(nrBilete));
		delete[]this->bilete;
		this->bilete = new Bilet[this->nrBilete];
		for (int i = 0; i < nrBilete; i++)
		{
			f.read((char*)&bilete[i], sizeof(bilete[i]));
		}
	}

	/*void adaugareSalainCinematograf(Sala& sala)
	{
		Cinematograf copie = *this;
		delete[]this->sali;
		this->nrSali++;
		this->sali = new Sala[this->nrSali];
		for (int i = 0; i < copie.nrSali; i++)
		{
			this->sali[i] = copie.sali[i];
		}
		for (int i = copie.nrSali; i < this->nrSali; i++)
		{
			this->sali[i] = sala;
		}
	}*/

	void addSala(Sala sala)
	{
		this->nrSali++;
		Sala* aux = new Sala[nrSali];
		if (this->sali != NULL)
		{
			for (int i = 0; i < nrSali - 1; i++)
				aux[i] = this->sali[i];
		}
		delete[]this->sali;
		aux[nrSali - 1] = sala;
		this->sali = aux;
	}
	/*void adaugaSuprafata(float valoare)
	{
		Apartament copie = *this;
		delete[] this->suprafataCamere;
		this->nrCamere++;
		this->suprafataCamere = new float[this->nrCamere];
		for (int i = 0; i < copie.nrCamere; i++)
		{
			this->suprafataCamere[i] = copie.suprafataCamere[i];
		}

		for (int i = copie.nrCamere; i < this->nrCamere; i++)
		{
			this->suprafataCamere[i] = valoare;
		}
	}*/
};



ostream& operator<<(ostream& out, Cinematograf c)
{
	out << c.nume << endl;
	out << c.nrSali << endl;
	if (c.sali != nullptr)
	{
		for (int i = 0; i < c.nrSali; i++)
		{
			out << c.sali[i] << " | ";
		}
		out << endl;
	}
	out << c.nrFilme << endl;
	if (c.filme != nullptr)
	{
		for (int i = 0; i < c.nrFilme; i++)
		{
			out << c.filme[i] << " | ";
		}
		out << endl;
	}
	out << c.nrBilete << endl;
	if (c.bilete != nullptr)
	{
		for (int i = 0; i < c.nrBilete; i++)
		{
			out << c.bilete[i] << " | ";
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, Cinematograf& c)
{
	in >> c.nume;
	cout << endl;
	in >> c.nrSali;
	cout << endl;
	for (int i = 0; i < c.nrSali; i++)
	{
		in >> c.sali[i];
	}
	cout << endl;
	in >> c.nrFilme;
	cout << endl;
	for (int i = 0; i < c.nrFilme; i++)
	{
		in >> c.filme[i];
	}
	cout << endl;
	in >> c.nrBilete;
	cout << endl;
	for (int i = 0; i < c.nrBilete; i++)
	{
		in >> c.bilete[i];
	}
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, Bilet b)
{
	out << (Film)b << endl;
	out << (Sala)b << endl;
	out << b.tipClient << endl;
	out << b.reducere << endl;
	out << b.pretTotal << endl;
	return out;
}

istream& operator>>(istream& in, Bilet& b)
{
	in >> (Film&)b;
	cout << endl;
	in >> (Sala&)b;
	cout << endl;
	in >> b.tipClient;
	cout << endl;
	in >> b.reducere;
	cout << endl;
	in >> b.pretTotal;
	cout << endl;
	return in;
}

//ostream& operator<<(ostream& out, Client c) {
//	out << c.nume << endl;
//	out << (Reducere)c << endl;
//	return out;
//}
//istream& operator>>(istream& in, Client& c) {
//	in >> c.nume;
//	cout << endl;
//	in >> (Reducere&)c;
//	cout << endl;
//	return in;
//}

//ostream& operator<<(ostream& out, Reducere r)
//{
//	out << r.reducere << endl;
//	out << r.denumire << endl;
//	return out;
//}

//istream& operator>>(istream& in, Reducere& r)
//{
//	in >> r.denumire;
//	cout << endl;
//	int val;
//	if (in >> val)
//	{
//		switch (val)
//		{
//		case 0: case 50:
//			r.reducere = Reducere::TipReducere(val); break;
//		default:
//			throw out_of_range("Nu este o reducere valida!");
//		}
//	}
//	cout << endl;
//	return in;
//}

ostream& operator<<(ostream& o, Film f)
{
	if (f.nume != nullptr) {
		o << "Numele filmului: " << f.nume << endl;
	}

	o << "Tipul filmului: " << f.tipFilm << endl;
	o << "Durata filmului: " << f.durata << endl;
	o << "Pretul filmului: " << f.pret << endl;
	o << "Numarul difuzarilor al filmului: " << f.nrDifuzari << endl;

	//if (f.program != nullptr) {
	//	for (int i = 0; i < f.nrDifuzari; i++)
	//	{
	//		o << *f.program[i] << "\n" << endl;
	//	}
	//}
	o << endl;
	return o;
}

istream& operator>>(istream& in, Film& f)
{
	delete[] f.nume;
	cout << "Introduceti numele filmului: " << endl;
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	f.nume = new char[strlen(buffer) + 1];
	strcpy_s(f.nume, strlen(buffer) + 1, buffer);
	cout << "Introduceti tipul filmului: " << endl;
	cout << endl;
	in >> f.tipFilm;
	cout << "Introduceti durata filmului: " << endl;
	cout << endl;
	in >> f.durata;
	cout << endl;
	cout << "Introduceti pretul filmului: " << endl;
	in >> f.pret;
	cout << endl;
	cout << "Introduceti nr difuzarilor: " << endl;
	in >> f.nrDifuzari;
	cout << endl;
	if (f.program != NULL)
	{
		delete[]f.program;
	}
	//if (f.nrDifuzari > 0) {
	//	f.program = new Program*[f.nrDifuzari];
	//	for (int i = 0; i < f.nrDifuzari; i++)
	//	{
	//		//Program p;
	//		//string zi = p.setZi();
	//		//float ora = p.setOra();
	//		//cout << "Adaugati ziua: " << p.getZi();
	//		//cout << "Adaugati ora: " << p.getOra();
	//		//f.setProgram(nrDifuzari, p);
	//		in >> *f.program[i];
	//	}
	//}
	//else {
	//	f.nrDifuzari = 0;
	//	f.program = nullptr;
	//}

	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, Program p)
{
	out << "Ziua este: " << p.zi << endl;
	out << "Ora este: " << p.ora << endl;
	return out;
}

istream& operator>>(istream& in, Program& p)
{
	cout << "Va rugam sa introduceti ziua: " << endl;
	in >> p.zi;
	cout << endl;
	cout << "Va rugam sa introduceri si ora: " << endl;
	in >> p.ora;
	cout << endl;
	return in;
}



ostream& operator << (ostream& out, Sala s)
{
	out << "Nr maxim de locuri al salii: " << s.nrMaxLocuri << endl;
	out << "Nr de randuri al salii: " << s.nrRanduri << endl;
	out << "Nr de locuri pe fiecare rand: " << s.nrLocuri << endl;
	return out;
}

istream& operator >>(istream& in, Sala& s)
{
	cout << "Introduceti nr maxim de locuri: " << endl;
	in >> s.nrMaxLocuri;
	cout << endl;
	cout << "Introduceti numarul de randuri: " << endl;
	in >> s.nrRanduri;
	cout << endl;
	cout << "Adaugati numarul de locuri de pe fiecare rand: " << endl;
	in >> s.nrLocuri;
	return in;
}

ostream& operator << (ostream& out, vectorSali vs)
{
	out << "Numarul de sali disponibile este: " << vs.nrSali << endl;
	out << "Salile din acest cinematograf dupa cum urmeaza: " << endl;
	if (vs.sali != nullptr) {
		for (int i = 0; i < vs.nrSali; i++) {
			out << vs.sali[i] << " \n";
		}
	}
	out << endl;
	return out;
}

istream& operator >>(istream& in, vectorSali& vs)
{
	cout << "Introduceti nr de sali: " << endl;
	in >> vs.nrSali;
	cout << endl;
	cout << "Introduceti salile: " << endl;
	for (int i = 0; i < vs.nrSali; i++)
	{
		in >> vs.sali[i];
		cout << "\n";
	}
	cout << endl;
	return in;
}

ostream& operator << (ostream& out, vectorFilme vf)
{
	out << "Numarul de filme disponibile este: " << vf.nrFilme << endl;
	out << "Filmele ce ruleaza in cinematograf dupa cum urmeaza: " << endl;
	if (vf.filme != nullptr) {
		for (int i = 0; i < vf.nrFilme; i++) {
			out << vf.filme[i] << " \n";
		}
	}
	out << endl;
	return out;
}

istream& operator >>(istream& in, vectorFilme& vf)
{
	cout << "Introduceti nr de filme: " << endl;
	in >> vf.nrFilme;
	cout << endl;
	cout << "Introduceti filmele: " << endl;
	for (int i = 0; i < vf.nrFilme; i++)
	{
		in >> vf.filme[i];
		cout << "\n";
	}
	cout << endl;
	return in;
}

// ################################## FAZA 2 ##################################

void emitereBilet(int step)
{
	system("cls");

	int film = step;

	// Introducerea datelor de catre utilizator: numar randului, numarul locului dorit si numele filmului din cele 3 disponibile
	// Dupa introducerea acestora, elementele sunt bagate intr-un singur fisier text, fara a face override
	//cout << "Randurile sunt numerotate de la 1 la 10." << endl;
	//cout << "Introduceti randul dorit: " << endl;
	//cin >> nrRand;
	//cout << "\tRandul dorit este: " << nrRand << ", fiind afisat in bilet." << endl;

	//cout << "\nLocurile sunt numerotate de la 1 la 10." << endl;
	//cout << "Introduceti numarul locului dorit: " << endl;
	//cin >> nrLoc;
	/*cin >> numarLocDorit;
	int* nrLocuri = &numarLocDorit;
	cout << "\tLocul dorit este: " << *nrLocuri << ", fiind afisat in bilet." << endl;*/


	//sala1.setNrLocuri(nrLoc);
	/*int* nrLocFinal = sala1.getNrLocuri();*/

	fstream fisier;
	Sala s;
	vectorSali vs;
	cin >> s; // luarea datelor de la utilizator din operatorul >>
	vs.addSala(s);
	fisier.open("emitere_bilet1.txt", fstream::app);
	//fisier << "\n\tNumarul locului emis pe acest bilet: " << *nrLocFinal << endl;
	fisier << "\n\tNumarul locului emis pe acest bilet: " << s.getNrLocuri() << endl;
	fisier << "\tNumarul randului emis pe acest bilet: " << s.getNrRand() << endl;

	Film filmul;

	cout << "\nAlegeti filmul pe care doriti sa il vizionati:\n\n";
	const char* numeFilm[] = { "Film1", "Film2", "Film3" };
	filmul.setNume(numeFilm[0]);
	cout << "\t1)" << filmul.getNume() << endl;
	filmul.setNume(numeFilm[1]);
	cout << "\t2)" << filmul.getNume() << endl;
	filmul.setNume(numeFilm[2]);
	cout << "\t3)" << filmul.getNume() << endl;

	cin >> film;
	if (film == 1) {
		cout << "\tFilmul ales este: " << numeFilm[0] << ". Acesta va fi afisat in bilet.\n";
		fisier << "\tFilmul ales este : " << numeFilm[0] << endl;
	}
	else if (film == 2) {
		cout << "\tFilmul ales este: " << numeFilm[1] << ". Acesta va fi afisat in bilet.\n";
		fisier << "\tFilmul ales este : " << numeFilm[1] << endl;
	}
	else {
		cout << "\tFilmul ales este: " << numeFilm[2] << ". Acesta va fi afisat in bilet.\n";
		fisier << "\tFilmul ales este: " << numeFilm[2] << endl;
	}

	fisier.close();
}

//void modificareBilet()
//{
//	string search;
//	string line;
//	ifstream file;
//	string nrLocFinal;
//	file.open("emitere_bilet1.txt", ifstream::in);
//
//	if (!file) {
//		cout << "Fisierul nu s-a putut deschide";
//	}
//	cout << "Introduceti numarul locului pe care doriti sa il modificati.";
//	cin >> search;
//
//	size_t pozitie;
//	while (file.good())
//	{
//		getline(file, line); // get line from file
//		pozitie = line.find(search); // search
//		if (pozitie != string::npos) // string::npos is returned if string is not found
//		{
//			cout << "Locul cu numarul " << search << " a fost gasit!" << endl;
//			_getch();
//
//		}
//	}
//	cout << "Introduceti numarul locului pe care il doriti pentru a-l modifica pe cel vechi." << endl;
//	cin >> nrLocFinal;
//
//	if (pozitie != string::npos) {
//		line.replace(pozitie, search.length(), string(nrLocFinal));
//	}
//
//	file.close();
//
//	ofstream f("emitere_biletModificare.txt", ofstream::out);
//	f << "\tLocul in sala a fost schimbat de la numarul " << search << " la numarul: " << nrLocFinal << endl;
//
//	f.close();
//}
//
//void stergereBilet()
//{
//	char fileName[] = "emitere_bilet1.txt";
//	if (remove(fileName) != 0) {
//		cout << "Fisierul cu numele " << fileName << " nu a putut fi sters.\n";
//		_getch();
//	}
//	else {
//		cout << "Fisierul " << fileName << " a fost sters cu succes.\n";
//		_getch();
//	}
//}

// Faza 3 - 6) Utilizarea STL-urilor pentru a refactoriza codul
// functia printSali() este o refactorizare pentru afisaresali()
void printSali(vector<vectorSali> arr)
{
	vectorSali ar;
	int nr = 1;
	ar.deserializare("Sali.bin");
	cout << "Avem disponibile urmatoare sali: " << endl;
	int nrSali = ar.getNrSali();
	Sala* sali = ar.getSali();
	for (int i = 0; i < nrSali; i++)
	{

		cout << "\nSala: " << nr << "\n";
		cout << sali[i] << endl;
		nr++;
	}
	cout << endl;
}

vectorSali vs;
vectorFilme vf;
void showMenu(int step) {
	//Cinematograf c;
	system("cls");
	cout << "Alegeti o optiune:\n\n";
	cout << "\t1)Emitere bilet\n";
	cout << "\t2)Situatie locuri libere\n";
	cout << "\t3)Situatie filme\n";
	cout << "\t4)Adaugare bilet\n";
	cout << "\t5)Modificare bilet\n";
	cout << "\t6)Stergere bilet\n";
	cout << "\t7)Adaugare sala\n";
	cout << "\t8)Modificare sala\n";
	cout << "\t9)Stergere sala\n";
	cout << "\t10)Adaugare film\n";
	cout << "\t11)Modificare film\n";
	cout << "\t12)Stergere film\n";
	cout << "\t13)Afisare sali\n";
	cout << "\t14)Afisare filme\n";
	cout << "\t15)Afisare programe\n";
	cout << "\t0)Iesire\n\n\n";

	if (step == 0)
	{
		//vs.serializare("Sali.bin");
		//vf.serializare("Filme.bin");

	}

	if (step == 1)
	{
		/*cout << "\t\tBiletul este: ";*/
		//Bilet::emitereBilet();
		emitereBilet(step);

	}

	if (step == 2)
	{
		cout << "\t\tSituatia locurilor libere: ";
		//situatieLocuriLibere();
	}

	if (step == 3)
	{
		cout << "Situatie filme: ";
		//situatieFilme();
	}

	if (step == 4)
	{
		cout << "Adaugare bilet!\n";
		//adaugareBilet();
	}

	if (step == 5)
	{
		cout << "\tNoul bilet modificat este: ";
		//alegereBilet();
		//modificareBilet();
	}

	if (step == 6)
	{
		//alegereBilet();
		//stergereBilet();
	}

	if (step == 7)
	{
		//c1..adaugasali(sala2);
		vs.adaugareSali();
	}

	if (step == 8)
	{
		vs.modificareSali();
	}

	if (step == 9)
	{
		int nrCurent;
		vs.afisareSali();
		cout << "Selecteaza sala pe care doresti sa o stergi!" << endl;
		cin >> nrCurent;
		vs.stergereSala(nrCurent);
		//afisareFisierSala();
		//c.stergereSala();
	}

	if (step == 10)
	{
		vectorFilme vf;
		vf.adaugareFilme();
		//cin >> f;
		//vf += f;
		//vf.addFilm(vf);
		//vf.serializare("Filme.bin");
		cout << "Filmul a fost adaugat!";
	}

	if (step == 11)
	{
		//vectorFilme vf;
		//vf.deserializare("Filme.bin");
		for (int i = 0; i < vf.getNrFilme(); i++)
		{
			cout << vf.getFilme()[i] << "\n";
		}
		//alegereFilm();
		//modificareFilm();
		//cout << "Filmul a fost modificat";
	}

	if (step == 12)
	{
		//alegereFilm();
		//stergereFilm();
		cout << "Filmul a fost sters!";
	}

	if (step == 13)
	{
		vectorSali vs;
		vs.afisareSali();
		//adaugareClient();
	}

	if (step == 14)
	{
		vectorFilme vf;
		vf.afisareFilme();
	}

	if (step == 15)
	{
		//alegereClient();
		//stergereClient();
		cout << "Clientul a fost sters!";
	}

}

void procesBilet(int option) {

	switch (option) {
	case 1:
		//emitereBilet(1);
		_getch();
		break;
	case 2:
		//emitereBilet(2);
		_getch();
		break;
	case 3:
		//emitereBilet(3);
		_getch();
		break;
	case 0:
		running = false;
		break;
	default:
		break;
	}
}

void process(int option) {

	/*vectorSali vs;
	Sala s;
	int nr = 0;*/
	//deserializare Cinamatograf
	//Cinematograf c;
	//string Fisier = "Cinematograf.bin";
	//c.deserializare(Fisier);

	switch (option) {
	case 1: // Emitere bilet
		showMenu(1);
		//Bilet::emitereBilet();
		break;
	case 2: // Situatie locuri libere
		showMenu(2);
		break;
	case 3: // Situatie filme
		showMenu(3);
		break;
	case 4: // Modificare bilet
		showMenu(4);
		break;
	case 5: // Stergere bilet
		showMenu(5);
		break;
	case 6: // Adaugare sala
		showMenu(6);
		system("pause");
		break;
	case 7: // Modificare sala
		showMenu(7);
		system("pause");
		break;
	case 8: // Stergere sala
		showMenu(8);
		system("pause");
		break;
	case 9: // Adaugare film
		showMenu(9);
		system("pause");
		break;
	case 10: // Modificare film
		showMenu(10);
		system("pause");
		break;
	case 11: // Stergere film
		showMenu(11);
		system("pause");
		break;
	case 12: // Adaugare client
		showMenu(12);
		system("pause");
		break;
	case 13: // Modificare client
		showMenu(13);
		system("pause");
		break;
	case 14: // Stergere client
		showMenu(14);
		system("pause");
		break;
	case 0:
		running = false;
		break;
	default:
		break;
	}

}


int main()
{


	int option = -1;

	while (running) {
		showMenu(0);
		cin >> option;
		process(option);
	}
	//Sala s1(10, 2, 5);
	//Sala s2(30, 3, 10);
	//Sala s3(24, 4, 6);
	//Sala** sali = new Sala * [3];
	//sali[0] = &s1;
	//sali[1] = &s2;
	//sali[2] = &s3;
	//vectorSali vs1(3, sali);
	//vs1+=s1;
	//cout << vs1.afisareSali() << endl;
	//vectorSali vs1;
	//int nr = 10;
	//Sala* sali = new Sala[nr];
	//Sala s1, s2;
	//cin >> s1;
	//cout << "\n\nSala s1: \n";
	//cout << s1 << "\n\n";
	//cin >> s2;
	//cout << "\n\nSala s2: \n";
	//cout << s2 << "\n\n";
	//vs1.addSala(s1);
	//vs1.addSala(s2);
	//cout << "Afisare sali disponibile: \n\n";
	//vs1.setSali(nr, sali);
	//for (int i = 0;i < vs1.getNrSali();i++)
	//{
	//	cout << vs1.getSali()[i] << "\n\n";
	//}
	//vs1 += s2;
	//cout << &vs1 << endl;
	/*Program p1("luni", 14);
	Program p2("marti", 12);
	Program p3("miercuri", 19);
	Program** listaProgram = new Program * [3];
	listaProgram[0] = &p1;
	listaProgram[1] = &p2;
	listaProgram[2] = &p3;
	char numeFilm[] = "Insomnia";
	Film f1(numeFilm, "Horror", 3600, 1000.50, 3, listaProgram);*/
	//f1 += p1;
	//f1 += p2;
	//for (int i = 0; i < f1.getNrDifuzari(); i++)
	//{
	//	cout << *f1.getProgram()[i] << "\n\n";
	//}
	//cout << f1 << endl;
	//Cinematograf c;
	//Sala s;
	//int valoare = 20;
	//cin >> s;
	//cout << "\nSala adaugata are urmatoare caracteristici: ";
	//cout << s << "\n\n" << endl;
	//s.addNewRow(valoare);
	//cout << "\nAdaugand un nou rand cu 20 de locuri obtinem: " << endl;
	//cout << s << endl;
	//SaliCinematograf sc;
	//Sala s, s1;
	//cin >> s;
	//cout << "\n";
	//sc.addSala(s);
	//sc.afisareSali();
	//cin >> s;
	//cout << s;
	//cin >> s1;
	//cout << s1;
	//sc.addSala(s);
	//sc.addSala(s1);
	////sc += s;
	//cout << sc << endl;

	//c.adaugareSalainCinematograf(s);
	//c.addSala(s);
	//cout << *c.getSali() << endl;

	//while (running) {
	//	emitereBilet(0);
	//	cin >> option;
	//	procesBilet(option);
	//}
	/*int nrlocuri[] = { 10, 20 };
	Sala s1(30, 2, nrlocuri);
	cout << s1[1] << endl;*/
	/*int valoare = 50;
	cout << s1 + valoare << endl;
	int nrlocuri2[] = { 10, 20, 20};
	Sala s2(50, 3, nrlocuri2);
	cout << s2 << endl;
	s1 = ++s2;
	cout << s1 << endl;
	s2 = s1++;
	cout << s2 << endl;
	int nrMaxLocuri = (int)s2;
	cout << nrMaxLocuri << endl;
	if (s1 != s2)
	{
		cout << "Nu au acelasi nr max de locuri" << endl;
	}
	else
	{
		cout << "Au acelasi nr max de locuri" << endl;
	}
	if (s1 > s2)
	{
		cout << "S1 are un nr de locuri mai mare" << endl;
	}
	else
	{
		cout << "S1 are un nr de locuri mai mare" << endl;
	}
	if (s1 == s2)
	{
		cout << "S1 si S2 au acelasi nr de randuri" << endl;
	}
	else
	{
		cout << "S1 si S2 nu au acelasi nr de randuri" << endl;
	}*/

	//de testat

// Faza 3 verificare refactorizare prin STL
	vector<vectorSali> toateSalile;
	printSali(toateSalile);
}


/*

 Bilet b;
 deserializare b; ai grijha sa lucrezi pe original b
 ai grija sa deschizi fisierul si dupa serilizare sa il inchizi


 acum faci meniu...
 si toate  fucntiile din mebiu le apelezi pt B ...
 atentite B original /// toate functiile care lucreaza cu b ....
 sa lucreze pe b original

 nu trebuie in fiecare fucntie din meniu seriaolizare ...



 b serializare   deschizi fiser si inchizi ...
 */
