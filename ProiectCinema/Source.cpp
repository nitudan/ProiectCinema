#include <iostream>
#include <string>
using namespace std;

class Sala {
private:

	const int idSala;
	int nrMaxLocuri;
	int nrRand;
	int* nrLocuri;
	static int contor;

public: 
	Sala():idSala(++contor)
	{
		nrMaxLocuri = 100;
		nrRand = 0;
		nrLocuri = nullptr;
	}

	Sala(int nrMaxLocuri, int nrRand, int* nrLocuri):idSala(++contor) 
	{
		if (nrMaxLocuri >= 30 && nrMaxLocuri < 100)
		{
			this->nrMaxLocuri = nrMaxLocuri;
		}
		this->nrRand = nrRand;
		this->nrLocuri = new int[nrRand];
		for (int i = 0; i < nrRand; i++) {
			this->nrLocuri[i] = nrLocuri[i];
		}
	}

	Sala(const Sala& c):idSala(c.idSala) 
	{
		this->nrMaxLocuri = c.nrMaxLocuri;
		this->nrRand = c.nrRand;
		this->nrLocuri = new int[c.nrRand];
		for (int i = 0; i < c.nrRand; i++) {
			this->nrLocuri[i] = c.nrLocuri[i];
		}
	}

	Sala& operator=(const Sala& cp) 
	{
		if (this != &cp) {
			if (this->nrLocuri != NULL) {
				delete[] this->nrLocuri;
			}
			this->nrRand = cp.nrRand;
			this->nrLocuri = new int[cp.nrRand];
			for (int i = 0; i < cp.nrRand; i++) {
				this->nrLocuri[i] = cp.nrLocuri[i];
			}
			return *this;
		}
	}

	~Sala()
	{
		if (this->nrLocuri != NULL) {
			delete[] this->nrLocuri;
		}
	}

	int getNrMaxLocuri() 
	{
		return this->nrMaxLocuri;
	}

	int getNrRand() 
	{
		return this->nrRand;
	}

	int* getNrLocuri() 
	{
		return this->nrLocuri;
	}

	void setNrMaxLocuri(int nrMaxLoc) 
	{
		if (nrMaxLoc >= 30 && nrMaxLoc <= 100) {
			this->nrMaxLocuri = nrMaxLoc;
		}
	}

	void setNrLocuri(int nrRand, int* nrLocuri) 
	{
		if (this->nrLocuri != NULL) {
			delete[] this->nrLocuri;
		}
		if (nrRand > 0 && nrLocuri != NULL) {
			this->nrRand = nrRand;
			this->nrLocuri = new int[nrRand];
			for (int i = 0; i < nrRand; i++) {
				this->nrLocuri[i] = nrLocuri[i];
			}
		}
	}

	int operator[] (int index)
	{
		if (index >= 0 && index < nrRand) 
		{
			return nrLocuri[index];
		}
	}

	Sala operator+(int valoare) 
	{
		Sala copie = *this;
		for (int i = 0 ; i < copie.nrRand; i++)
		{
			copie.nrLocuri[i] = nrLocuri[i] + valoare;
		}
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
		return nrRand;
	}

	bool operator!=(const Sala& s)
	{
		return this->nrMaxLocuri != s.nrMaxLocuri;
	}

	bool operator>(const Sala& s)
	{
		float suma = 0;
		float suma1 = 0;
		for (int i = 0; i < this->nrRand; i++)
		{
			suma+=this->nrLocuri[i];
		}
		for (int i = 0; i < s.nrRand; i++)
		{
			suma1+= s.nrLocuri[i];
		}
		return suma > suma1;
	}

	bool operator==(const Sala& s)
	{
		return this->nrRand == s.nrRand;
	}
	//<<, >>, unul din + - * /, [], unul din ++ -- cu 2 forme, un cast, !, unul din < > =< =>, ==
	friend ostream& operator <<(ostream& o, Sala s);
	friend istream& operator >>(istream& i, Sala& s);
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

	Program(string zi, double ora)
	{
		this->zi = zi;
		this->ora = ora;
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
};

class Film
{
private:

	char* nume;
	string tipFilm;
	int durata;
	float pret;
	int nrDifuzari;
	Program* program;
public:

	Film()
	{
		this->nume = nullptr;
		this->tipFilm = "Necunoscut";
		this->durata = 0;
		this->pret = 0;
		this->nrDifuzari = 0;
		this->program = new Program[0];
	}

	Film(char* nume, string tipFilm, int durata, float pret, int nrDifuzari, Program* program)
	{
		this->nume = new char[strlen(nume)+1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
		this->tipFilm = tipFilm;
		this->durata = durata;
		this->pret = pret;
		this->nrDifuzari = nrDifuzari;
		program = new Program[nrDifuzari];
		for (int i = 0; i < nrDifuzari;i++)
		{
			this->program[i] = program[i];
		}
	}

	~Film()
	{
		if (this->nume != NULL)
		{
			delete[]this->nume;
		}

		if (this->program != NULL)
		{
			delete[]this->program;
		}
	}

	Film(const Film& f)
	{
		this->nume = new char[strlen(f.nume) + 1];
		strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
		this->tipFilm = f.tipFilm;
		this->durata = f.durata;
		this->pret = f.pret;
		this->nrDifuzari = f.nrDifuzari;
		program = new Program[f.nrDifuzari];
		for (int i = 0; i < f.nrDifuzari;i++)
		{
			this->program[i] = f.program[i];
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
			this->nume = new char[strlen(f.nume) + 1];
			strcpy_s(this->nume, strlen(f.nume) + 1, f.nume);
			this->tipFilm = f.tipFilm;
			this->durata = f.durata;
			this->pret = f.pret;
			this->nrDifuzari = f.nrDifuzari;
			program = new Program[f.nrDifuzari];
			for (int i = 0; i < f.nrDifuzari;i++)
			{
				this->program[i] = f.program[i];
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
		if (this->nume != NULL)
		{
			delete[]this->nume;
		}
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
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

	Program* getProgram()
	{
		return program;
	}

	void setProgram(int nrDifuzari, Program* program)
	{
		if (this->program != NULL)
		{
			delete[]this->program;
		}
		if (nrDifuzari > 0 && program != NULL)
		{
			this->nrDifuzari = nrDifuzari;
			this->program = new Program[nrDifuzari];
			for (int i = 0; i < nrDifuzari;i++)
			{
				this->program[i] = program[i];
			}
		}
	}

	Program operator [](int index)
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

};

class Reducere
{
public:
	enum TipReducere { adult = 0, elev = 50, student = 50, pensionar = 50 };
private:
	string denumire;
	TipReducere reducere;
public:
	Reducere() {
		reducere = adult;
		denumire = "Necunoscut";
	}
	Reducere(string denumire, TipReducere reducere) {
		this->denumire = denumire;
		this->reducere = reducere;
	}

	string getDenumire() {
		return this->denumire;
	}
	TipReducere getReducere() {
		return this->reducere;
	}

	void setDenumire(string denumire) {
		if (denumire.length() > 1) {
			this->denumire = denumire;
		}
	}
	void setTipReducere(TipReducere reducere) {
		if ( reducere == elev || reducere == student || reducere == pensionar)
		{
			this->reducere = reducere;
		}
	}

	friend ostream& operator<<(ostream& out, Reducere r);
	friend istream& operator>>(istream& in, Reducere& r);

	TipReducere operator [](int index)
	{
		return reducere;
	}

	//operator ++ post-incrementat
	/*Reducere operator++(int)
	{
		Reducere copie = *this;
		this->denumire++;
		return copie;
	}*/
	//operator ++ pre-incrementat
	/*Reducere& operator++()
	{
		this->reducere++;
		return *this;
	}*/

	explicit operator string()
	{
		return denumire;
	}

	bool operator!=(const Reducere& p)
	{
		return this->denumire != p.denumire;
	}

	bool operator<(const Reducere& p)
	{
		return this->reducere < p.reducere;
	}

	bool operator==(const Reducere& p)
	{
		return this->denumire == p.denumire;
	}

};

class Client: public Reducere {
private:
	string nume;
public:

	Client():Reducere() {
		nume = "Necunoscut";
	}

	Client(string denumire, TipReducere reducere, string nume) :Reducere(denumire, reducere)
	{
		this->nume = nume;
	}
	string getNume() {

		return this->nume;
	}
	void setNume(string nume) {
		if (nume.length() > 3) {
			this->nume = nume;
		}
	}

	friend ostream& operator<<(ostream& out, Client c);
	friend istream& operator>>(istream& in, Client& c);

	string operator [](int index)
	{
		return nume;
	}

	//operator ++ post-incrementat
	/*Reducere operator++(int)
	{
		Reducere copie = *this;
		this->denumire++;
		return copie;
	}*/
	//operator ++ pre-incrementat
	/*Reducere& operator++()
	{
		this->reducere++;
		return *this;
	}*/

	explicit operator string()
	{
		return nume;
	}

	bool operator!=(const Client& p)
	{
		return this->nume != p.nume;
	}

	bool operator<(const Client& p)
	{
		return this->nume < p.nume;
	}

	bool operator==(const Client&p)
	{
		return this->nume == p.nume;
	}
};

class Bilet: public Film, public Sala 
{
	Film film;
	Sala sala; 
	int nrClienti; 
	Client* clienti; 
	//Program program;
	float pretTotal;

	Bilet():Film(), Sala()
	{
		this->nrClienti = 0;
		this->clienti = new Client[0];
		this->pretTotal = 0;
	}

	Bilet(char* nume, string tipFilm, int durata, float pret, int nrDifuzari, Program* program, int nrMaxLocuri, int randuri, int* nrLocuri, int nrClienti, Client* clienti, float pretTotal) :Film(nume, tipFilm, durata, pret, nrDifuzari, program), Sala(nrMaxLocuri, randuri, nrLocuri)
	{
		this->nrClienti = nrClienti;
		this->clienti = new Client[nrClienti];
		for (int i = 0; i < nrClienti;i++)
		{
			this->clienti[i] = clienti[i];
		}
		this->pretTotal = pretTotal;
	}

	Bilet(const Bilet& b) :Film(b), Sala(b)
	{
		this->nrClienti = b.nrClienti;
		this->clienti = new Client[nrClienti];
		for (int i = 0; i < nrClienti;i++)
		{
			this->clienti[i] = b.clienti[i];
		}
		this->pretTotal = b.pretTotal;
	}

	~Bilet()
	{
		if (this->clienti != NULL)
		{
			delete[]this->clienti;
		}
	}

	Bilet& operator=(const Bilet& b)
	{
		if (this != &b)
		{
			if (this->clienti != NULL)
			{
				delete[]this->clienti;
			}
			this->nrClienti = b.nrClienti;
			this->clienti = new Client[nrClienti];
			for (int i = 0; i < nrClienti;i++)
			{
				this->clienti[i] = b.clienti[i];
			}
			this->pretTotal = b.pretTotal;
			return *this;
		}
	}

	Client operator [](int index)
	{
		if (index >= 0 && index < nrClienti)
		{
			return clienti[index];
		}
	}

	//operator ++ post-incrementat
	Bilet operator++(int)
	{
		Bilet copie = *this;
		this->pretTotal++;
		return copie;
	}

	//operator ++ pre-incrementat
	Bilet& operator++()
	{
		this->pretTotal++;
		return *this;
	}

	explicit operator int()
	{
		return nrClienti;
	}

	bool operator!=(const Bilet& b)
	{
		return this->pretTotal != b.pretTotal;
	}

	bool operator<(const Bilet& b)
	{
		return this->nrClienti < b.nrClienti;
	}

	bool operator==(const Bilet& b)
	{
		return this->pretTotal == b.pretTotal;
	}

	friend ostream& operator<<(ostream& out, Bilet b);
	friend istream& operator>>(istream& in, Bilet& b);
};

ostream& operator<<(ostream& out, Bilet b)
{
	out << (Film)b << endl;
	out << (Sala)b << endl;
	out << b.nrClienti << endl;
	for (int i = 0; i < b.nrClienti;i++)
	{
		out << b.clienti[i] << "\n" << endl;
	}
	out << endl;
	out << b.pretTotal << endl;
	return out;
}

istream& operator>>(istream& in, Bilet& b)
{
	in >> (Film&)b;
	cout << endl;
	in >> (Sala&)b;
	cout << endl;
	in >> b.nrClienti;
	cout << endl;
	for (int i = 0; i < b.nrClienti; i++)
	{
		in >> b.clienti[i];
	}
	cout << endl;
	in >> b.pretTotal;
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, Client c) {
	out << c.nume << endl;
	out << (Reducere)c << endl;
	return out;
}
istream& operator>>(istream& in, Client& c) {
	in >> c.nume;
	cout << endl;
	in >> (Reducere&)c;
	cout << endl;
	return in;
 }
ostream& operator<<(ostream& out, Reducere r)
{
	out << r.reducere << endl;
	out << r.denumire << endl;
	return out;
}



istream& operator>>(istream& in, Reducere& r)
{
	in >> r.denumire;
	cout << endl;
	int val;
	if (in >> val) 
	{
		switch (val) 
		{
		case 0: case 50:
			r.reducere = Reducere::TipReducere(val); break;
		default:
			throw out_of_range("Nu este o reducere valida!");
		}
	}
	cout << endl;
	return in;
}

ostream& operator<<(ostream& o, Film f)
{
	o << f.nume << endl;
	o << f.tipFilm << endl;
	o << f.durata << endl;
	o << f.pret << endl;
	o << f.nrDifuzari << endl;
	for (int i = 0; i < f.nrDifuzari;i++)
	{
		o << f.program[i] << "\n" << endl;
	}
	o << endl;
	return o;
}

istream& operator>>(istream& in, Film& f)
{
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	f.nume = new char[strlen(buffer) + 1];
	strcpy_s(f.nume, strlen(buffer) + 1, buffer);
	cout << endl;
	in >> f.tipFilm;
	cout << endl;
	in >> f.durata;
	cout << endl;
	in >> f.pret;
	cout << endl;
	in >> f.nrDifuzari;
	cout << endl;
	if (f.program != NULL)
	{
		delete[]f.program;
	}
	f.program = new Program[f.nrDifuzari];
	for (int i = 0; i < f.nrDifuzari;i++)
	{
		in >>f.program[i];
	}
	cout << endl;
	return in;
}
ostream& operator<<(ostream& out, Program p)
{
	out << p.zi << endl;
	out << p.ora << endl;
	return out;
}



istream& operator>>(istream& in, Program& p)
{
	in >> p.zi;
	cout << endl;
	in >> p.ora;
	cout << endl;
	return in;
}
int Sala::contor = 0;

ostream& operator << (ostream& o, Sala s) 
{
	o << s.nrMaxLocuri << endl;
	o << s.nrRand << endl;
	for (int i = 0; i < s.nrRand; i++) {
		o << s.nrLocuri[i] << " ";
	}
	o << endl;
	return o;
}

istream& operator >>(istream& i, Sala& s) 
{
	i >> s.nrMaxLocuri;
	cout << endl;
	i >> s.nrRand;
	cout << endl;
	for (int i = 0; i < s.nrRand; i++) {
		i >> s.nrLocuri[i]; 
	}
	cout << endl;

	return i;
}

int main()
{
	int nrlocuri[] = { 10, 20 };
	Sala s1(30, 2, nrlocuri);
	cout << s1[0] << endl;
	int valoare = 50;
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
	}
	
	//de testat
}