# define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
using namespace std;

//UNIVERSITATE

char d = ','; //despartitor fisier CSV

class IFile
{
public:
	//scriere in fisiere binare
	virtual void writeToFile(ofstream& f) = 0;
	//citire din fisiere binare
	virtual void readFromFile(ifstream& f) = 0;
	//generare raport
	virtual void Raport(ofstream& f) = 0;
	//incarcarea de date din fisiere CSV
	virtual void importCSV(ifstream& f) = 0;
};

class calcul
{
public:
	virtual int salariu() = 0;
	virtual int pensie() = 0;
};

class Camin :public IFile
{
	static int nrmaximpersoanecamera;
	const int nrmaximpersoanecamin;
	int nrcamere;
	float* valoareutilitati;
	char* locatie;
	int nrcamera[1000];

public:
	static int getnrmaximpersoanecamera()
	{
		return Camin::nrmaximpersoanecamera;
	}

	int getnrmaximpersoanecamin()
	{
		return this->nrmaximpersoanecamin;
	}

	float* getvaloareutilitati()
	{
		return this->valoareutilitati;
	}

	int getnrnrcamere()
	{
		return this->nrcamere;
	}

	char* getlocatie()
	{
		return this->locatie;
	}

	int* getnrcamera()
	{
		return this->nrcamera;
	}

	void setlocatie(const char* locatie)
	{
		if (this->locatie)
			delete[] this->locatie;
		this->locatie = new char[strlen(locatie) + 1];
		strcpy(this->locatie, locatie);
	}

	void setnrcamere(int nrcamere)
	{
		if (this->nrcamere > 0)
			this->nrcamere = nrcamere;
		else cout << "Introduceti un numar pozitiv";

	}

	void setvaloareutilitati(int nrcamere, float* valoareutilitati)
	{
		if (this->valoareutilitati)
			delete[] this->valoareutilitati;
		this->nrcamere = nrcamere;
		this->valoareutilitati = new float[nrcamere];
		for (int i = 0;i < this->nrcamere;i++)
			this->valoareutilitati[i] = valoareutilitati[i];
	}

	void setnrcamera(int nrcamera[1000])
	{
		for (int i = 0;i < this->nrcamere;i++)
			if (this->nrcamera[i] > 0)
				this->nrcamera[i] = nrcamera[i];
			else cout << "Introduceti un numar pozitiv";
	}

	float calculareutilitatimedii()
	{
		float m = 0;
		for (int i = 0;i < this->nrcamere;i++)
		{
			m += this->valoareutilitati[i];
		}
		m = m / this->nrcamere;
		return m;
	}

	float calculareregiecamera(int c)
	{
		float s = this->valoareutilitati[c] + this->nrcamera[c];
		return s;
	}

	Camin(int nrcamere, const char* locatie) : nrmaximpersoanecamin(250)
	{
		this->nrcamere = nrcamere;
		this->locatie = new char[strlen(locatie) + 1];
		strcpy(this->locatie, locatie);
		this->valoareutilitati = NULL;
		for (int i = 0;i < this->nrcamere;i++)
			this->nrcamera[i] = 0;
	}


	Camin(int nrmaximpersoanecamin, int nrcamere, float* valoareutilitati, const char* locatie, int nrcamera[1000]) : nrmaximpersoanecamin(nrmaximpersoanecamin)
	{
		this->nrcamere = nrcamere;
		this->valoareutilitati = new float[this->nrcamere];
		for (int i = 0;i < this->nrcamere;i++)
			this->valoareutilitati[i] = valoareutilitati[i];
		this->locatie = new char[strlen(locatie) + 1];
		strcpy(this->locatie, locatie);
		for (int i = 0;i < this->nrcamere;i++)
			this->nrcamera[i] = nrcamera[i];
	}

	Camin(const Camin& c) :nrmaximpersoanecamin(c.nrmaximpersoanecamin)
	{
		this->nrcamere = c.nrcamere;
		this->valoareutilitati = new float[this->nrcamere];
		for (int i = 0;i < this->nrcamere;i++)
			this->valoareutilitati[i] = c.valoareutilitati[i];
		this->locatie = new char[strlen(c.locatie) + 1];
		strcpy(this->locatie, c.locatie);
		for (int i = 0;i < this->nrcamere;i++)
			this->nrcamera[i] = c.nrcamera[i];
	}

	Camin& operator=(const Camin& c)
	{
		if (this != &c)
		{
			this->nrcamere = c.nrcamere;
			this->valoareutilitati = new float[this->nrcamere];
			for (int i = 0;i < this->nrcamere;i++)
				this->valoareutilitati[i] = c.valoareutilitati[i];
			this->locatie = new char[strlen(c.locatie) + 1];
			strcpy(this->locatie, c.locatie);
			for (int i = 0;i < this->nrcamere;i++)
				this->nrcamera[i] = c.nrcamera[i];
		}
		return *this;
	}

	~Camin()
	{
		delete[] this->valoareutilitati;
		delete[] this->locatie;
	}

	friend ostream& operator<<(ostream& out, Camin& c)
	{
		out << Camin::nrmaximpersoanecamera << "\n";
		out << c.nrmaximpersoanecamin << "\n";
		out << c.nrcamere << "\n";
		for (int i = 0;i < c.nrcamere;i++)
			if (c.valoareutilitati[i])
				out << c.valoareutilitati[i] << " ";
		out << "\n" << c.locatie << "\n";
		for (int i = 0;i < c.nrcamere;i++)
			out << c.nrcamera[i] << " ";
		out << "\n------------------------------\n";
		return out;
	}

	friend istream& operator>>(istream& in, Camin& c)
	{
		cout << "Nr camere: ";
		in >> c.nrcamere;
		cout << "Valoare utilitati: ";
		for (int i = 0;i < c.nrcamere;i++)
			in >> c.valoareutilitati[i];
		cout << "Locatie: ";
		char buffer[200];
		in >> buffer;
		delete[] c.locatie;
		c.locatie = new char[strlen(buffer) + 1];
		strcpy(c.locatie, buffer);
		cout << "Nr camere: ";
		for (int i = 0;i < c.nrcamere;i++)
		{
			in >> c.nrcamera[i];
		}
		return in;
	}

	//indexare
	float operator [](int x)
	{
		if (x<0 || x>this->nrcamere)
			cout << "Indexul nu exista";
		return this->valoareutilitati[x];
	}

	Camin& operator+(int valoare)
	{
		if (valoare > 0)
			for (int i = 0;i < this->nrcamere;i++)
				this->valoareutilitati[i] += valoare;
		else
			cout << "Introduceti o valoare valida";
		return *this;
	}

	//preincrementare s2=++s1;
	Camin& operator ++()
	{
		for (int i = 0;i < this->nrcamere;i++)
			this->valoareutilitati[i]++;
		return *this;
	}

	//postincrementare s2=s1++;
	Camin operator ++(int)
	{
		Camin copie = *this;
		for (int i = 0;i < this->nrcamere;i++)
			this->valoareutilitati[i]++;
		return copie;
	}

	//cast la int
	int operator() ()
	{
		return this->nrcamere;
	}

	bool operator==(Camin& v)
	{
		return(this->nrcamere == v.nrcamere);
	}

	bool operator>(Camin& v)
	{
		return(this->nrcamere > v.nrcamere);
	}

	Camin operator !()
	{
		if (this->locatie)
			delete[] this->locatie;
		this->locatie = new char[strlen("AXCB000000000") + 1];
		strcpy(this->locatie, "AXCB000000000");
		return *this;
	}

	void importCSV(ifstream& f)
	{
		string line;

		getline(f, line, d);
		this->nrcamere = stoi(line);

		getline(f, line, d);
		delete[] this->locatie;
		this->locatie = new char[strlen(line.c_str()) + 1];
		strcpy(locatie, line.c_str());

		int i = 0;
		delete[] this->valoareutilitati;
		this->valoareutilitati = new float[this->nrcamere];
		while (i < this->nrcamere)
		{
			getline(f, line, d);
			this->valoareutilitati[i] = stof(line);
			i++;
		}

		i = 0;
		while (i < this->nrcamere)
		{
			getline(f, line, d);
			this->nrcamera[i] = stoi(line);
			i++;
		}
		f.close();
	}

	void Raport(ofstream& o)
	{
		float* aux24 = this->valoareutilitati;
		int* aux25 = this->nrcamera;
		o << this->locatie << endl;
		cout << this->locatie << endl;
		for (int i = 0;i < this->nrcamere;i++)
		{
			o << aux25[i] << ": ";
			o << aux24[i] << endl;
			cout << aux25[i] << ": ";
			cout << aux24[i] << endl;
		}
		o << endl;
		cout << endl;
	}

	void writeToFile(ofstream& o)
	{

		int lungime = strlen(this->locatie) + 1;
		o.write((char*)&lungime, sizeof(int));
		o.write(locatie, sizeof(char) * lungime);

		o.write((char*)&this->nrcamere, sizeof(this->nrcamere));

		for (int i = 0; i < this->nrcamere; i++)
			o.write((char*)&this->valoareutilitati[i], sizeof(this->valoareutilitati[i]));

		for (int i = 0; i < this->nrcamere; i++)
			o.write((char*)&this->nrcamera[i], sizeof(this->nrcamera[i]));
	}

	void readFromFile(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char s[2300];
		in.read(s, lungime);

		this->setlocatie(s);

		in.read((char*)&this->nrcamere, sizeof(this->nrcamere));

		delete[]  this->valoareutilitati;
		this->valoareutilitati = new float[this->nrcamere];
		for (int i = 0; i < this->nrcamere; i++)
			in.read((char*)&this->valoareutilitati[i], sizeof(this->valoareutilitati[i]));

		for (int i = 0; i < this->nrcamere; i++)
			in.read((char*)&this->nrcamera[i], sizeof(this->nrcamera[i]));
	}


};

int Camin::nrmaximpersoanecamera = 3;

class Student :public IFile
{
	static int anstudiu;
	const int codmatricol;
	int nrnote;
	int* note;
	char* nume;
	float medie[3];

public:
	static int getanstudiu()
	{
		return Student::anstudiu;
	}

	int getcodmatricol()
	{
		return this->codmatricol;
	}

	int getnrnote()
	{
		return this->nrnote;
	}

	int* getnote()
	{
		return this->note;
	}

	char* getnume()
	{
		return this->nume;
	}

	float* getmedie()
	{
		return this->medie;
	}

	void setnume(const char* nume)
	{
		delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	void setnrnote(int nrnote)
	{
		if (nrnote > 0)
			this->nrnote = nrnote;
		else cout << "Introduceti un numar de note pozitiv";
	}

	void setnote(int nrnote, int* note)
	{
		delete this->note;
		this->nrnote = nrnote;
		this->note = new int[nrnote];
		for (int i = 0;i < this->nrnote;i++)
			if (note[i] <= 10)
				this->note[i] = note[i];
			else cout << "Introduceti notele pozitive";
	}

	void setmedie(float medie[3])
	{
		for (int i = 0;i < 3;i++)
			if (medie[i] <= 10)
				this->medie[i] = medie[i];
			else cout << "Introduceti mediile pozitive";
	}

	float calcularemedieanuala()
	{
		float m = 0;
		if (this->nrnote > 0)
		{
			for (int i = 0;i < this->nrnote;i++)
			{
				m += this->note[i];
			}
			m = m / this->nrnote;
		}
		return m;
	}

	float calcularemediemultianuala()
	{
		float m = 0;
		int c = 0;
		for (int i = 0;i < 3;i++)
		{
			if (this->medie[i] > 0)
			{
				m += this->medie[i];
				c++;
			}
		}
		m = m / c;
		return m;
	}

	Student(int codmatricol, const char* nume) : codmatricol(0)
	{
		anstudiu++;
		this->nrnote = 0;
		this->note = NULL;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		for (int i = 0;i < 3;i++)
			medie[i] = 0;
	}

	Student(int codmatricol, int nrnote, int* note, const char* nume, float medie[3]) : codmatricol(codmatricol)
	{
		anstudiu++;
		this->nrnote = nrnote;
		this->note = new int[nrnote];
		for (int i = 0;i < this->nrnote;i++)
			this->note[i] = note[i];
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		for (int i = 0;i < 3;i++)
			this->medie[i] = medie[i];
	}

	Student(const Student& s) :codmatricol(s.codmatricol)
	{
		anstudiu++;
		this->nrnote = s.nrnote;
		this->note = new int[s.nrnote];
		for (int i = 0;i < this->nrnote;i++)
			this->note[i] = s.note[i];
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		for (int i = 0;i < 3;i++)
			this->medie[i] = s.medie[i];
	}

	Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			this->nrnote = s.nrnote;
			this->note = new int[s.nrnote];
			for (int i = 0;i < this->nrnote;i++)
				this->note[i] = s.note[i];
			this->nume = new char[strlen(s.nume) + 1];
			strcpy(this->nume, s.nume);
			for (int i = 0;i < 3;i++)
				this->medie[i] = s.medie[i];
		}
		return *this;
	}

	~Student()
	{
		anstudiu--;
		delete[] this->note;
		delete[] this->nume;
	}

	friend ostream& operator<<(ostream& out, const Student& s)
	{
		out << Student::anstudiu << "\n";
		out << s.codmatricol << "\n";
		out << s.nrnote << "\n";
		for (int i = 0;i < s.nrnote;i++)
			out << s.note[i] << " ";
		out << "\n" << s.nume << "\n";
		for (int i = 0;i < 3;i++)
			if (s.medie[i] > 0)
				out << s.medie[i] << " ";
		out << "\n------------------------------\n";
		return out;
	}

	friend istream& operator>>(istream& in, Student& s)
	{
		cout << "Nr note: ";
		in >> s.nrnote;
		cout << "Note: ";
		for (int i = 0;i < s.nrnote;i++)
			in >> s.note[i];
		cout << "Nume: ";
		char buffer[200];
		in >> buffer;
		delete[] s.nume;
		s.nume = new char[strlen(buffer) + 1];
		strcpy(s.nume, buffer);
		for (int i = 0;i < s.nrnote;i++)
		{
			cout << "Media anului: " << i + 1 << ": ";
			in >> s.medie[i];
		}
		return in;
	}

	//indexare
	float operator [](int x)
	{
		if (x < 0 || x >= this->nrnote)
			cout << "Indexul nu exista";
		else
			return this->medie[x - 1];
	}

	Student& operator+(int nota)
	{
		if (nota <= 10)
		{
			int* vn;
			vn = new int[(this->nrnote) + 1];
			for (int i = 0;i < this->nrnote;i++)
				vn[i] = this->note[i];
			vn[this->nrnote] = nota;
			delete[] this->note;
			this->note = new int[(this->nrnote) + 1];
			this->nrnote++;
			for (int i = 0;i < this->nrnote;i++)
				this->note[i] = vn[i];
			delete[] vn;
		}
		return *this;
	}

	//preincrementare s2=++s1;
	Student& operator ++()
	{
		int* vn = new int[(this->nrnote) + 1];
		for (int i = 0;i < this->nrnote;i++)
			vn[i] = this->note[i];
		vn[this->nrnote] = 10;
		delete[] this->note;
		this->note = vn;
		this->nrnote++;
		return *this;
	}

	//postincrementare s2=s1++;
	Student operator ++(int)
	{
		Student copie = *this;
		int* vn = new int[(this->nrnote) + 1];
		for (int i = 0;i < this->nrnote;i++)
			vn[i] = this->note[i];
		vn[this->nrnote] = 10;
		delete[] this->note;
		this->nrnote++;
		this->note = vn;
		return copie;
	}

	//cast la int
	int operator() ()
	{
		return this->codmatricol;
	}

	bool operator==(Student& v)
	{
		return(this->anstudiu == v.anstudiu);
	}

	bool operator>(Student& v)
	{
		return(this->anstudiu > v.anstudiu);
	}

	Student operator !()
	{
		delete[] this->nume;
		this->nume = new char[strlen("AXCB000000000") + 1];
		strcpy(this->nume, "AXCB000000000");
		return *this;
	}

	void importCSV(ifstream& f)
	{
		string line;

		getline(f, line, d);
		this->nrnote = stoi(line);

		getline(f, line, d);
		delete[] this->nume;
		this->nume = new char[strlen(line.c_str()) + 1];
		strcpy(nume, line.c_str());

		int i = 0;
		delete[] this->note;
		this->note = new int[this->nrnote];
		while (i < this->nrnote)
		{
			getline(f, line, d);
			this->note[i] = stoi(line);
			i++;
		}

		i = 0;
		while (i < 3)
		{
			getline(f, line, d);
			this->medie[i] = stof(line);
			i++;
		}
		f.close();
	}

	void Raport(ofstream& o)
	{
		o << this->nume << ": ";
		cout << this->nume << ": ";
		int* aux20 = this->note;
		for (int i = 0;i < this->nrnote;i++)
		{
			o << aux20[i] << " ";
			cout << aux20[i] << " ";
		}
	}

	void writeToFile(ofstream& o)
	{

		int lungime = strlen(this->nume) + 1;
		o.write((char*)&lungime, sizeof(int));
		o.write(nume, sizeof(char) * lungime);

		o.write((char*)&this->nrnote, sizeof(this->nrnote));

		for (int i = 0; i < this->nrnote; i++)
			o.write((char*)&this->note[i], sizeof(this->note[i]));

		for (int i = 0; i < this->nrnote; i++)
			o.write((char*)&this->medie[i], sizeof(this->medie[i]));
	}

	void readFromFile(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char s[2300];
		in.read(s, lungime);

		this->setnume(s);

		in.read((char*)&this->nrnote, sizeof(this->nrnote));

		delete[]  this->note;
		this->note = new int[this->nrnote];
		for (int i = 0; i < this->nrnote; i++)
			in.read((char*)&this->note[i], sizeof(this->note[i]));

		for (int i = 0; i < this->nrnote; i++)
			in.read((char*)&this->medie[i], sizeof(this->medie[i]));
	}

	virtual void print()
	{
		cout << getnume() << " este un student"<<endl;
	}

};

int Student::anstudiu = 0;

class Profesor :public IFile, public calcul
{
	static string domeniu;
	const int codprofesor;
	char* nume;
	int nrmaterii;
	string* materii;
	int nrcredite[100];

public:

	static string getdomeniu()
	{
		return Profesor::domeniu;
	}

	int getcodprofesor()
	{
		return this->codprofesor;
	}

	string* getmaterii()
	{
		return this->materii;
	}

	int getnrmaterii()
	{
		return this->nrmaterii;
	}

	char* getnume()
	{
		return this->nume;
	}

	int* getnrcredite()
	{
		return this->nrcredite;
	}

	void setnume(const char* nume)
	{
		delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	void setnrmaterii(int nrmaterii)
	{
		if (nrmaterii > 0)
			this->nrmaterii = nrmaterii;
		else cout << "Introduceti numarul de materii pozitiv";
	}

	void setmaterii(int nrmaterii, string* materii)
	{
		if (nrmaterii > 0)
		{
			delete[] this->materii;
			this->nrmaterii = nrmaterii;
			this->materii = new string[nrmaterii];
			for (int i = 0;i < this->nrmaterii;i++)
				this->materii[i] = materii[i];
		}
		else cout << "Introduceti numarul de materii pozitiv";
	}

	void setnrcredite(int nrmaterii, int nrcredite[100])
	{
		if (nrmaterii > 0)
		{
			this->nrmaterii = nrmaterii;
			for (int i = 0;i < nrmaterii;i++)
				this->nrcredite[i] = nrcredite[i];
		}
		else cout << "Introduceti numarul de materii pozitiv";

	}

	float calcularenrmediucredite()
	{
		float m = 0;
		if (this->nrmaterii > 0)
		{
			for (int i = 0;i < this->nrmaterii;i++)
			{
				m += this->nrcredite[i];
			}
			m = m / this->nrmaterii;
		}
		return m;
	}

	int calcularenrtotalcredite()
	{
		int m = 0;
		for (int i = 0;i < this->nrmaterii;i++)
		{
			if (this->nrcredite[i] > 0)
				m += this->nrcredite[i];
		}
		return m;
	}

	int salariu() override
	{
		return 200 * calcularenrtotalcredite();
	}

	int pensie() override
	{
		return 0.0225 * salariu();
	}

	Profesor(int codprofesor, const char* nume) : codprofesor(codprofesor)
	{
		this->nrmaterii = 0;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->materii = NULL;
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i] = 0;
	}

	Profesor(int codprofesor, int nrmaterii, string* materii, const char* nume, int nrcredite[100]) : codprofesor(codprofesor)
	{
		this->nrmaterii = nrmaterii;
		this->materii = new string[nrmaterii];
		for (int i = 0;i < this->nrmaterii;i++)
			this->materii[i] = materii[i];
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i] = nrcredite[i];
	}

	Profesor(const Profesor& p) :codprofesor(p.codprofesor)
	{
		this->nrmaterii = p.nrmaterii;
		this->materii = new string[p.nrmaterii];
		for (int i = 0;i < this->nrmaterii;i++)
			this->materii[i] = p.materii[i];
		this->nume = new char[strlen(p.nume) + 1];
		strcpy(this->nume, p.nume);
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i] = p.nrcredite[i];
	}

	Profesor& operator=(const Profesor& p)
	{
		if (this != &p)
		{
			this->nrmaterii = p.nrmaterii;
			this->materii = new string[p.nrmaterii];
			for (int i = 0;i < this->nrmaterii;i++)
				this->materii[i] = p.materii[i];
			this->nume = new char[strlen(p.nume) + 1];
			strcpy(this->nume, p.nume);
			for (int i = 0;i < this->nrmaterii;i++)
				this->nrcredite[i] = p.nrcredite[i];
		}
		return *this;
	}

	~Profesor()
	{
		delete[] this->materii;
		delete[] this->nume;
	}

	friend ostream& operator<<(ostream& out, const Profesor& p)
	{
		out << Profesor::domeniu << "\n";
		out << p.codprofesor << "\n";
		out << p.nrmaterii << "\n";
		for (int i = 0;i < p.nrmaterii;i++)
			out << p.materii[i] << " ";
		out << "\n" << p.nume << "\n";
		for (int i = 0;i < p.nrmaterii;i++)
			if (p.nrcredite[i] > 0)
				out << p.nrcredite[i] << " ";
		out << "\n------------------------------\n";
		return out;
	}

	friend istream& operator>>(istream& in, Profesor& p)
	{
		cout << "Nr materii: ";
		in >> p.nrmaterii;
		cout << "Nr credite: ";
		for (int i = 0;i < p.nrmaterii;i++)
			in >> p.nrcredite[i];
		cout << "Nume: ";
		char buffer[200];
		in >> buffer;
		delete[] p.nume;
		p.nume = new char[strlen(buffer) + 1];
		strcpy(p.nume, buffer);
		cout << "Materii: ";
		for (int i = 0;i < p.nrmaterii;i++)
		{
			in >> p.materii[i];
		}
		return in;
	}

	//indexare
	int operator [](int x)
	{
		if (x < 0 || x >= this->nrmaterii)
			cout << "Indexul nu exista";
		else
			return this->nrcredite[x - 1];
	}

	Profesor& operator-(int valoare)
	{
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i] -= valoare;
		return *this;
	}

	//preincrementare s2=++s1;
	Profesor& operator ++()
	{
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i]++;
		return *this;
	}

	//postincrementare s2=s1++;
	Profesor operator ++(int)
	{
		Profesor copie = *this;
		for (int i = 0;i < this->nrmaterii;i++)
			this->nrcredite[i]++;
		return copie;
	}

	//cast la int
	int operator() ()
	{
		return this->codprofesor;
	}

	bool operator==(Profesor& v)
	{
		return(this->nrmaterii == v.nrmaterii);
	}

	bool operator<(Profesor& v)
	{
		return(this->nrmaterii < v.nrmaterii);
	}

	Profesor operator !()
	{
		delete[] this->nume;
		this->nume = new char[strlen("AXCB000000000") + 1];
		strcpy(this->nume, "AXCB000000000");
		return *this;
	}

	void importCSV(ifstream& f)
	{
		string line;

		getline(f, line, d);
		this->nrmaterii = stoi(line);

		getline(f, line, d);
		delete[] this->nume;
		this->nume = new char[strlen(line.c_str()) + 1];
		strcpy(nume, line.c_str());

		int i = 0;
		delete[] this->materii;
		this->materii = new string[this->nrmaterii];
		while (i < this->nrmaterii)
		{
			getline(f, line, d);
			this->materii[i] = line;
			i++;
		}

		i = 0;
		while (i < this->nrmaterii)
		{
			getline(f, line, d);
			this->nrcredite[i] = stoi(line);
			i++;
		}
		f.close();
	}

	void Raport(ofstream& o) {}

	void writeToFile(ofstream& o) {}

	void readFromFile(ifstream& in) {}

	virtual void print()
	{
		cout << getnume() << " este un profesor"<<endl;
	}

};

string Profesor::domeniu = "Economic";

class Cladire :public IFile
{
	static int nrmaximsali;
	const int codidentificare;
	char* denumire;
	int nrsali;
	int* nrsala;
	int nrlocuri[200];

public:
	static int getnumarmaximsali()
	{
		return Cladire::nrmaximsali;
	}

	int getcodidentificare()
	{
		return this->codidentificare;
	}

	int* getnrsala()
	{
		return this->nrsala;
	}

	int getnrsali()
	{
		return this->nrsali;
	}

	char* getdenumire()
	{
		return this->denumire;
	}

	int* getnrlocuri()
	{
		return this->nrlocuri;
	}

	void setdenumire(const char* denumire)
	{
		delete[] this->denumire;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}

	void setnrsali(int nrsali)
	{
		if (nrsali > 0 && this->nrsali < Cladire::nrmaximsali)
			this->nrsali = nrsali;
		else
			cout << "Introduceti un numar de sali valid";
	}

	void setnrsala(int nrsali, int* nrsala)
	{
		if (nrsali > 0 && this->nrsali < Cladire::nrmaximsali)
		{
			delete[] this->nrsala;
			this->nrsali = nrsali;
			this->nrsala = new int[nrsali];
			for (int i = 0;i < this->nrsali;i++)
				this->nrsala[i] = nrsala[i];
		}
		else
			cout << "Introduceti un numar de sali valid";
	}

	void setnrlocuri(int nrlocuri[200])
	{
		for (int i = 0;i < this->nrsali;i++)
			if (nrlocuri[i] > 0)
				this->nrlocuri[i] = nrlocuri[i];
			else
				cout << "Introduceti un numar de locuri pozitiv";
	}

	float calcularenrmediulocuri()
	{
		float m = 0;
		if (this->nrsali > 0)
		{
			for (int i = 0;i < this->nrsali;i++)
			{
				m += this->nrlocuri[i];
			}
			m = m / this->nrsali;
		}
		return m;
	}

	int calcularenrtotallocuri()
	{
		int s = 0;
		for (int i = 0;i < nrsali;i++)
		{
			if (this->nrlocuri[i] > 0)
				s += this->nrlocuri[i];
		}
		return s;
	}

	Cladire(int codidentificare, const char* denumire) : codidentificare(codidentificare)
	{
		this->nrsali = 0;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->nrsala = NULL;
		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] = 0;
	}

	Cladire(int codidentificare, int nrsali, int* nrsala, const char* denumire, int nrlocuri[200]) : codidentificare(codidentificare)
	{
		if (nrsali <= Cladire::nrmaximsali)
			this->nrsali = nrsali;
		this->nrsala = new int[nrsali];
		for (int i = 0;i < this->nrsali;i++)
			this->nrsala[i] = nrsala[i];
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] = nrlocuri[i];
	}

	Cladire(const Cladire& c) :codidentificare(c.codidentificare)
	{
		if (c.nrsali <= Cladire::nrmaximsali)
			this->nrsali = c.nrsali;
		this->nrsala = new int[c.nrsali];
		for (int i = 0;i < this->nrsali;i++)
			this->nrsala[i] = c.nrsala[i];
		this->denumire = new char[strlen(c.denumire) + 1];
		strcpy(this->denumire, c.denumire);
		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] = c.nrlocuri[i];
	}

	Cladire& operator=(const Cladire& c)
	{
		if (this != &c)
		{
			this->nrsali = c.nrsali;
			this->nrsala = new int[c.nrsali];
			for (int i = 0;i < this->nrsali;i++)
				this->nrsala[i] = c.nrsala[i];
			this->denumire = new char[strlen(c.denumire) + 1];
			strcpy(this->denumire, c.denumire);
			for (int i = 0;i < this->nrsali;i++)
				this->nrlocuri[i] = c.nrlocuri[i];
		}
		return *this;
	}

	~Cladire()
	{
		delete[] this->nrsala;
		delete[] this->denumire;
	}

	friend ostream& operator<<(ostream& out, Cladire& c)
	{
		out << Cladire::nrmaximsali << "\n";
		out << c.codidentificare << "\n";
		out << c.nrsali << "\n";
		for (int i = 0;i < c.nrsali;i++)
			out << c.nrsala[i] << " ";
		out << "\n" << c.denumire << "\n";
		for (int i = 0;i < c.nrsali;i++)
			if (c.nrlocuri[i] > 0)
				out << c.nrlocuri[i] << " ";
		out << "\n------------------------------\n";
		return out;
	}

	friend istream& operator>>(istream& in, Cladire& c)
	{
		cout << "Nr sali: ";
		in >> c.nrsali;
		cout << "Nr locuri: ";
		for (int i = 0;i < c.nrsali;i++)
			in >> c.nrlocuri[i];
		cout << "Denumire: ";
		char buffer[200];
		in >> buffer;
		delete[] c.denumire;
		c.denumire = new char[strlen(buffer) + 1];
		strcpy(c.denumire, buffer);
		cout << "Nr sala: ";
		for (int i = 0;i < c.nrsali;i++)
			in >> c.nrlocuri[i];
		return in;
	}

	//indexare
	int operator [](int x)
	{
		if (x < 0 || x >= this->nrsali)
			cout << "Indexul nu exista";
		else
			return this->nrlocuri[x - 1];
	}

	Cladire& operator-(int nrlocuri)
	{

		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] -= nrlocuri;
		return *this;
	}

	//preincrementare s2=++s1;
	Cladire& operator ++()
	{
		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] += 10;
		return *this;
	}

	//postincrementare s2=s1++;
	Cladire operator ++(int)
	{
		Cladire copie = *this;
		for (int i = 0;i < this->nrsali;i++)
			this->nrlocuri[i] += 10;
		return copie;
	}

	//cast la int
	int operator() ()
	{
		return this->codidentificare;
	}

	bool operator==(Cladire& v)
	{
		return(this->nrsali == v.nrsali);
	}

	bool operator>(Cladire& v)
	{
		return(this->nrsali > v.nrsali);
	}

	Cladire operator !()
	{
		delete[] this->denumire;
		this->denumire = new char[strlen("AXCB000000000") + 1];
		strcpy(this->denumire, "AXCB000000000");
		return *this;
	}

	void importCSV(ifstream& f)
	{
		string line;

		getline(f, line, d);
		this->nrsali = stoi(line);

		getline(f, line, d);
		delete[] this->denumire;
		this->denumire = new char[strlen(line.c_str()) + 1];
		strcpy(denumire, line.c_str());

		int i = 0;
		delete[] this->nrsala;
		this->nrsala = new int[this->nrsali];
		while (i < this->nrsali)
		{
			getline(f, line, d);
			this->nrsala[i] = stoi(line);
			i++;
		}

		i = 0;
		while (i < this->nrsali)
		{
			getline(f, line, d);
			this->nrlocuri[i] = stoi(line);
			i++;
		}
		f.close();
	}

	void writeToFile(ofstream& o)
	{

		int lungime = strlen(this->denumire) + 1;
		o.write((char*)&lungime, sizeof(int));
		o.write(denumire, sizeof(char) * lungime);

		o.write((char*)&this->nrsali, sizeof(this->nrsali));

		for (int i = 0; i < this->nrsali; i++)
			o.write((char*)&this->nrsala[i], sizeof(this->nrsala[i]));

		for (int i = 0; i < this->nrsali; i++)
			o.write((char*)&this->nrlocuri[i], sizeof(this->nrlocuri[i]));
	}

	void readFromFile(ifstream& in)
	{
		int lungime;
		in.read((char*)&lungime, sizeof(int));
		char s[2300];
		in.read(s, lungime);

		this->setdenumire(s);

		in.read((char*)&this->nrsali, sizeof(this->nrsali));

		delete[]  this->nrsala;
		this->nrsala = new int[this->nrsali];
		for (int i = 0; i < this->nrsali; i++)
			in.read((char*)&this->nrsala[i], sizeof(this->nrsala[i]));

		for (int i = 0; i < this->nrsali; i++)
			in.read((char*)&this->nrlocuri[i], sizeof(this->nrlocuri[i]));
	}

	void Raport(ofstream& o) {}


};
int Cladire::nrmaximsali = 195;

//derivare clasa student

class ProfesorDoctorand : public Student
{
	int andoctorat = 0;
	int nrStudCoordonati = 0;

public:

	ProfesorDoctorand(int codmatricol, int nrnote, int* note, const char* nume, float medie[3], int andoctorat, int nrStudCoordonati) :Student(codmatricol, nrnote, note, nume, medie)
	{
		this->andoctorat = andoctorat;
		this->nrStudCoordonati = nrStudCoordonati;
	}

	ProfesorDoctorand(const ProfesorDoctorand& p) :Student(p)
	{
		this->andoctorat = p.andoctorat;
		this->nrStudCoordonati = p.nrStudCoordonati;
	}

	ProfesorDoctorand& operator=(const ProfesorDoctorand& p)
	{
		if (this != &p)
		{
			Student::operator=(p);
			this->andoctorat = p.andoctorat;
			this->nrStudCoordonati = p.nrStudCoordonati;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const ProfesorDoctorand& p)
	{
		out << (Student)p;
		out << "\nAn doctorat: " << p.andoctorat;
		out << "\nNr stud coordonati: " << p.nrStudCoordonati;
		return out;
	}

	~ProfesorDoctorand()
	{
	}

	virtual void print()
	{
		cout << getnume() << " este un profesor doctorand"<<endl;
	}

};

// derivare clasa profesor

class Decan : public Profesor
{
	string facultate;
	int vechime = 0;

public:

	void setfacultate(string facultate)
	{
		this->facultate = facultate;
	}

	string getfacultate()
	{
		return this->facultate;
	}

	Decan(int codprofesor, int nrmaterii, string* materii, const char* nume, int nrcredite[100], string facultate, int vechime) : Profesor(codprofesor, nrmaterii, materii, nume, nrcredite)
	{
		this->facultate = facultate;
		this->vechime = vechime;
	}

	Decan(Profesor p, string facultate, int vechime) :Profesor(p)
	{
		this->facultate = facultate;
		this->vechime = vechime;
	}

	Decan& operator=(const Decan& p)
	{
		if (this != &p)
		{
			Profesor::operator=(p);
			this->facultate = p.facultate;
			this->vechime = p.vechime;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Decan& p)
	{
		out << (Profesor)p;
		out << "\nFacultate: " << p.facultate;
		out << "\nVechime: " << p.vechime;
		return out;
	}

	~Decan()
	{
	}

	virtual void print()
	{
		cout << getnume() << " este decanul" << endl;
	}

};

class Facultate : public IFile
{
	static int nrlocuri;
	const int codfacultate;
	char* denumire;
	int nrspecializari;
	string* specializari;
	int nrstudenti[10000];
	int nrprofesori;
	Profesor** listaprofesori;

public:

	Facultate(int codfacultate, const char* denumire, int nrprofesori, Profesor** listaprofesori) :codfacultate(codfacultate)
	{
		this->denumire = new char[strlen("na") + 1];
		this->nrspecializari = 0;
		strcpy(this->denumire, "na");
		this->nrprofesori = nrprofesori;
		this->listaprofesori = new Profesor * [this->nrprofesori];
		for (int i = 0; i < this->nrprofesori; i++)
			this->listaprofesori[i] = new Profesor(*listaprofesori[i]);
		this->specializari = NULL;
		for (int i = 0; i < this->nrspecializari; i++)
			nrstudenti[i] = 0;
	}

	static int getnrlocuri()
	{
		return Facultate::nrlocuri;
	}

	int getcodfacultate()
	{
		return this->codfacultate;
	}

	string* getspecializari()
	{
		return this->specializari;
	}

	int getnrspecializari()
	{
		return this->nrspecializari;
	}

	char* getdenumire()
	{
		return this->denumire;
	}

	int* getnrstudenti()
	{
		return this->nrstudenti;
	}

	void setdenumire(const char* denumire)
	{
		if (this->denumire)
			delete[] this->denumire;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}

	void setnrspecializari(int nrspecializari)
	{
		if (this->nrspecializari > 0)
			this->nrspecializari = nrspecializari;
		else cout << "Introduceti un numar pozitiv";
	}

	void setspecializari(int nrspecializari, string* specializari)
	{
		if (this->specializari)
			delete[] this->specializari;
		this->nrspecializari = nrspecializari;
		this->specializari = new string[nrspecializari];
		for (int i = 0;i < this->nrspecializari;i++)
			this->specializari[i] = specializari[i];
	}

	void setnrstudenti(int nrstudenti[10000])
	{
		for (int i = 0;i < this->nrspecializari;i++)
			if (nrstudenti[i] <= Facultate::nrlocuri)
				this->nrstudenti[i] = nrstudenti[i];
	}

	float calcularemedienrstudenti()
	{
		float m = 0;
		if (this->nrspecializari > 0)
		{
			for (int i = 0;i < this->nrspecializari;i++)
			{
				m += this->nrstudenti[i];
			}
			m = m / this->nrspecializari;
		}
		return m;
	}

	float calcularerataocupare()
	{
		float m = 0;
		int c = 0;
		for (int i = 0;i < 3;i++)
		{
			if (this->nrstudenti[i] > 0)
				m += this->nrstudenti[i];
		}
		m = m / Facultate::nrlocuri;
		return m;
	}

	Facultate(int codfacultate, int nrspecializari) : codfacultate(codfacultate)
	{
		this->nrspecializari = nrspecializari;
		this->nrprofesori = 0;
		this->denumire = new char[strlen("na") + 1];
		strcpy(this->denumire, "na");
		this->specializari = NULL;
		for (int i = 0;i < this->nrspecializari;i++)
			this->nrstudenti[i] = 0;
		this->listaprofesori = NULL;
	}

	Facultate(int codfacultate, int nrspecializari, string* specializari, const char* denumire, int nrstudenti[10000]) : codfacultate(codfacultate)
	{
		this->nrspecializari = nrspecializari;
		this->specializari = new string[nrspecializari];
		for (int i = 0;i < this->nrspecializari;i++)
			this->specializari[i] = specializari[i];
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		for (int i = 0;i < this->nrspecializari;i++)
			this->nrstudenti[i] = nrstudenti[i];

	}

	Facultate(const Facultate& f) :codfacultate(f.codfacultate)
	{
		this->nrspecializari = f.nrspecializari;
		this->specializari = new string[f.nrspecializari];
		for (int i = 0;i < this->nrspecializari;i++)
			this->specializari[i] = f.specializari[i];
		this->denumire = new char[strlen(f.denumire) + 1];
		strcpy(this->denumire, f.denumire);
		for (int i = 0;i < this->nrspecializari;i++)
			this->nrstudenti[i] = f.nrstudenti[i];
	}

	Facultate& operator=(const Facultate& f)
	{
		if (this != &f)
		{
			this->nrspecializari = f.nrspecializari;
			this->specializari = new string[f.nrspecializari];
			for (int i = 0;i < this->nrspecializari;i++)
				this->specializari[i] = f.specializari[i];
			this->denumire = new char[strlen(f.denumire) + 1];
			strcpy(this->denumire, f.denumire);
			for (int i = 0;i < this->nrspecializari;i++)
				this->nrstudenti[i] = f.nrstudenti[i];
		}
		return *this;
	}

	~Facultate()
	{
		delete[] this->specializari;
		delete[] this->denumire;
	}

	friend ostream& operator<<(ostream& out, Facultate& f)
	{
		out << Facultate::nrlocuri << "\n";
		out << f.codfacultate << "\n";
		out << f.nrspecializari << "\n";
		for (int i = 0;i < f.nrspecializari;i++)
			out << f.specializari[i] << " ";
		out << "\n" << f.denumire << "\n";
		for (int i = 0;i < f.nrspecializari;i++)
			if (f.nrstudenti[i] > 0)
				out << f.nrstudenti[i] << " ";
		out << "\n------------------------------\n";
		return out;
	}

	friend istream& operator>>(istream& in, Facultate& f)
	{
		cout << "Nr specializari: ";
		in >> f.nrspecializari;
		cout << "Nr studenti : ";
		for (int i = 0;i < f.nrspecializari;i++)
			if (f.nrstudenti[i] <= Facultate::nrlocuri)
				in >> f.nrstudenti[i];
		cout << "Denumire: ";
		char buffer[200];
		in >> buffer;
		delete[] f.denumire;
		f.denumire = new char[strlen(buffer) + 1];
		strcpy(f.denumire, buffer);
		cout << "Specializari: ";
		for (int i = 0;i < f.nrspecializari;i++)
		{
			in >> f.specializari[i];
		}
		return in;
	}

	//indexare
	int operator [](int x)
	{
		if (x < 0 || x >= this->nrspecializari)
			cout << "Indexul nu exista";
		else
			return this->nrstudenti[x - 1];
	}

	Facultate& operator+(int nrstudenti)
	{
		this->nrstudenti[nrspecializari - 1] = nrstudenti;
		return *this;
	}

	//preincrementare s2=++s1;
	Facultate& operator ++()
	{
		for (int i = 0;i < this->nrspecializari;i++)
			this->nrstudenti[i] += 10;
		return *this;
	}

	//postincrementare s2=s1++;
	Facultate operator ++(int)
	{
		Facultate copie = *this;
		for (int i = 0;i < this->nrspecializari;i++)
			this->nrstudenti[i] += 10;
		return copie;
	}

	//cast la int
	int operator() ()
	{
		return this->codfacultate;
	}

	bool operator==(Facultate& v)
	{
		return(this->codfacultate == v.codfacultate);
	}

	bool operator>(Facultate& v)
	{
		return(this->codfacultate > v.codfacultate);
	}

	Facultate operator !()
	{
		if (this->denumire)
			delete[] this->denumire;
		this->denumire = new char[strlen("AXCB000000000") + 1];
		strcpy(this->denumire, "AXCB000000000");
		return *this;
	}

	void importCSV(ifstream& f)
	{
		string line;

		getline(f, line, d);
		this->nrspecializari = stoi(line);

		getline(f, line, d);
		delete[] this->denumire;
		this->denumire = new char[strlen(line.c_str()) + 1];
		strcpy(denumire, line.c_str());

		int i = 0;
		delete[] this->specializari;
		this->specializari = new string[this->nrspecializari];
		while (i < this->nrspecializari)
		{
			getline(f, line, d);
			this->specializari[i] = line;
			i++;
		}

		i = 0;
		while (i < this->nrspecializari)
		{
			getline(f, line, d);
			this->nrstudenti[i] = stoi(line);
			i++;
		}
		f.close();
	}

	void Raport(ofstream& o)
	{
		int suma1 = 0;
		int* aux32 = this->nrstudenti;
		for (int i = 0;i < this->nrspecializari;i++)
			suma1 += aux32[i];
		cout << this->denumire << ": ";
		cout << suma1 << endl;
		o << this->denumire << ": ";
		o << suma1 << endl;
	}

	void writeToFile(ofstream& o) {}

	void readFromFile(ifstream& in) {}

	void afisare()
	{
		cout << "Nr profesori: " << this->nrprofesori << endl;
		cout << "Profesori: ";
		for (int i = 0; i < this->nrprofesori; i++)
			cout << *this->listaprofesori[i];
	}

};

int Facultate::nrlocuri = 650;

void meniu()
{
	cout << "Bun gasit pe pagina oficiala CSIE!";
	cout << "Introduceti cifra corespunzatoare meniului unde doriti sa ajungeti " << endl;
	cout << "1. Specializari" << endl;
	cout << "2. Camine" << endl;
	cout << "3. Profesori" << endl;
	cout << "4. Cladiri" << endl;
	cout << "5. Parasire meniu" << endl;
}

int main(int argc, char* argv[])
{
	//Apeluri clasa Student

	Student s1(101, "Alexandru Florian");
	int v11[3] = { 7, 10, 9 };
	float v12[3] = { 8.68, 0, 0 };
	Student s2(102, 3, v11, "Alexandru Isvoranu", v12);
	Student s10(s2);

	//Apeluri clasa Facultate

	Facultate f1(10, 3);
	string v13[3] = { "Cibernetica","Statistica","Informatica economica" };
	int v14[3] = { 540, 430, 610 };
	Facultate f2(11, 3, v13, "CSIE", v14 );
	Facultate f10(f2);

	//Apeluri clasa Camin

	Camin c1(116, "Moxa");
	float v16[3] = { 29.4, 36.5, 44.7 };
	int v17[3] = { 301, 302, 303 };
	Camin c2(426, 3, v16 , "Belvedere", v17 );
	Camin c10(c2);

	//Apeluri clasa Profesor

	Profesor p1(1001, "Bunea Stefan");
	string v18[2] = { "BCO","BCE" };
	int v19[2] = { 4, 5 };
	Profesor p2(1002, 2, v18, "Mitrut Dorin", v19 );
	Profesor p10(p2);

	//Apeluri clasa Cladire

	Cladire cl1(0, "Ion N. Angelescu");
	int v20[3] = { 2101, 2102, 2211 };
	int v21[3] = { 180, 175, 30 };
	Cladire cl2(2, 3, v20, "Virgi Madgearu", v21);
	Cladire cl10(cl2);

	//------------------------------------Apeluri metode------------------------------------

	//Apeluri clasa Student

	cout << s1;
	cout << s2;
	cout << s2.getanstudiu() << endl;
	cout << s2.getcodmatricol() << endl;
	int* aux5 = s2.getnote();
	for (int i = 0;i < s2.getnrnote();i++)
		cout << aux5[i] << " ";
	cout << endl;
	cout << s2.getnrnote() << endl;
	cout << s2.getnume() << endl;
	float* aux6 = s2.getmedie();
	for (int i = 0;i < s2.getnrnote();i++)
		cout << aux6[i] << " ";
	cout << endl;
	cout << s2.calcularemedieanuala() << endl;
	cout << s2.calcularemediemultianuala() << endl;
	cout << endl;
	s2.setmedie(new float[3] {8.75, 0, 0});
	s2.setnote(3, new int[3] {8, 9, 9});
	s2.setnrnote(3);
	s2.setnume("Isvoranu Alexandru");
	cout << endl;
	cout << s2[1];
	cout << endl;
	s2 + 10;
	cout << s2;
	Student s3(s2);
	s3 = s2++;
	s3 = ++s2;
	cout << s2;
	cout << s3;
	cout << s3;
	Student s4(104, "Mihai Udriste");
	s4 = s2;
	cout << s4;
	//cin >> s4;
	cout << s3() << endl;;
	if (s2 == s3)
		cout << "Amandoi stundentii sunt in acelasi an\n";
	else
		cout << "Studentii sunt ani diferiti\n";
	if (s2 > s3)
		cout << "Studentul s2 este mai mare\n";
	else
		cout << "Studentul s3 este mai mare sau acelasi an\n";
	Student s11(s2);
	cout << (!s11).getnume() << endl;


	//Apeluri clasa Facultate

	cout << f2;
	cout << f2.getdenumire() << endl;
	cout << f2.getnrlocuri() << endl;
	cout << f2.getnrspecializari() << endl;
	string* aux = f2.getspecializari();
	for (int i = 0;i < f2.getnrspecializari();i++)
		cout << aux[i] << " ";
	int* aux4 = f2.getnrstudenti();
	for (int i = 0;i < f2.getnrspecializari();i++)
		cout << aux4[i] << " ";
	cout << endl;
	cout << endl;
	f2.setdenumire("CIE");
	f2.setnrspecializari(2);
	int v22[2] = { 580, 620 };
	f2.setnrstudenti(v22);
	string v23[2] = { "Cibernetica","Informatica economica" };
	f2.setspecializari(2, v23);
	cout << f2;
	cout << f2[1];
	cout << endl;
	f2 + 15;
	cout << f2;
	Facultate f3(f2);
	f3 = f2++;
	f3 = ++f2;
	cout << f2;
	cout << f3;
	Facultate f4(12, 4);
	f4 = f2;
	cout << f4;
	//cin >> f4;
	cout << f3() << endl;;
	if (f2 == f3)
		cout << "F2 si F3 au acleasi cod\n";
	else
		cout << "F2 si F3 nu au acleasi cod\n";
	if (f2 > f3)
		cout << "Facultatea f2 are cod mai mare\n";
	else
		cout << "Facultatea f3 are cod mai mare sau egal decat f2\n";

	Facultate f11(f2);
	cout << (!f11).getdenumire() << endl;

	//Apeluri clasa Camin

	cout << c2;
	cout << c2.getlocatie() << endl;
	cout << c2.getnrmaximpersoanecamera() << endl;
	cout << c2.getnrmaximpersoanecamin() << endl;
	cout << c2.getnrnrcamere() << endl;
	float* aux7 = c2.getvaloareutilitati();
	for (int i = 0;i < c2.getnrnrcamere();i++)
		cout << aux7[i] << " ";
	int* aux8 = c2.getnrcamera();
	for (int i = 0;i < c2.getnrnrcamere();i++)
		cout << aux8[i] << " ";
	cout << endl;
	c2.setlocatie("Belvedere Nou");
	c2.setnrcamere(4);
	int v24[4] = { 201, 202, 203, 204 };
	c2.setnrcamera(v24);
	float v25[4] = { 30.1, 35.6, 42.6, 37.8 };
	c2.setvaloareutilitati(4, v25 );
	cout << c2[1];
	c2 + 15;
	cout << c2;
	Camin c3(c2);
	cout << c3;
	Camin c4(140, "Agronomie");
	//cin >> c2;
	c4 = c3;
	c3 = c2++;
	cout << c3 << c2;
	c3 = ++c2;
	cout << c3 << c2;
	cout << c2() << endl;
	if (c1 == c3)
		cout << "C1 si C2 au aclesi nr de camere\n";
	else
		cout << "C1 si C3 nu au aclesi nr de camere\n";
	if (c1 > c3)
		cout << "Caminul c1 are mai multe camere decat C3\n";
	else
		cout << "Caminul c3 are mai multe camere decat C1 sau nr egal\n";
	Camin c11(c2);
	cout << (!c11).getlocatie() << endl;

	//Apeluri clasa Profesor

	cout << p1;
	cout << p2;
	cout << p2.getcodprofesor() << endl;
	cout << p2.getdomeniu() << endl;
	string* aux9 = p2.getmaterii();
	for (int i = 0;i < p2.getnrmaterii();i++)
		cout << aux9[i] << " ";
	cout << endl;
	cout << p2.getnrmaterii() << endl;
	cout << p2.getnume() << endl;
	int* aux10 = p2.getnrcredite();
	for (int i = 0;i < p2.getnrmaterii();i++)
		cout << aux10[i] << " ";
	cout << endl;
	p2.setnrmaterii(3);
	int v26[3] = { 5, 4, 4 };
	p2.setnrcredite(3, v26 );
	string v27[3] = { "BCE","BCO","Statistica" };
	p2.setmaterii(3, v27);
	p2.setnume("Dorin MItrut");
	cout << p2;
	cout << p2[1] << endl;
	p2 - 1;
	cout << p2;
	Profesor p3(p2);
	cout << p3;
	p1 = p3;
	//cin >> p1;
	cout << p1;
	p3 = ++p2;
	if (p1 == p2)
		cout << "P1 si P2 au acelasi nr de materii\n";
	else
		cout << "P1 si P2 nu au acelasi nr de materii\n";
	if (p1 < p2)
		cout << "P2 preda mai multe materii decat P1\n";
	else
		cout << "P1 preda un nr mai mare sau egal de materii decat P2\n";
	Profesor p11(p2);
	cout << (!p11).getnume() << endl;

	//Apeluri clasa Cladire

	cout << cl1;
	cout << cl2;
	cout << cl2.getcodidentificare() << endl;
	cout << cl2.getdenumire() << endl;
	int* aux3 = cl2.getnrsala();
	for (int i = 0;i < cl2.getnrsali();i++)
		cout << aux3[i] << " ";
	cout << endl;
	int* aux2 = cl2.getnrlocuri();
	for (int i = 0;i < cl2.getnrsali();i++)
		cout << aux2[i] << " ";
	cout << endl;
	cout << cl2.getnrsali() << endl;;
	cout << cl2.getnumarmaximsali();
	cl2.setnrsali(4);
	cl2.setdenumire("Virgil Madgearu");
	int v28[4] = { 175, 170, 30, 35 };
	cl2.setnrlocuri(v28);
	int v29[4] = { 2201, 2202, 2211, 2312 };
	cl2.setnrsala(4, v29 );
	cout << cl2;
	cout << cl2[1];
	cl2 - 10;
	cout << cl2;
	Cladire cl3(cl2);
	cl1 = cl3;
	//cin >> cl1;
	cl2 = cl3++;
	cout << c3;
	cl2 = ++cl3;
	cout << cl2;
	cout << cl1;
	if (cl1 == cl2)
		cout << "C1 si C2 au acelasi nr de sali\n";
	else
		cout << "C1 si C2 nu au acelasi nr de materii\n";
	if (cl1 > cl2)
		cout << "C1 are mai multe sali decat C2\n";
	else
		cout << "C2 are mai multe sali decat C1 sau acelasi nr\n";
	Cladire cl11(cl2);
	cout << (!cl11).getdenumire() << endl;

	cout << endl;

	//---------------Fisiere de intrare in argumentele functiei main----------------

	if (argc < 2)
		cout << "Nu a fost furnizat niciun argument." << endl;
	else
		cout << "Primul argument este: " << argv[1] << endl;

	//------------------------------------Meniu------------------------------------

	int m;
	do
	{
		meniu();
		cin >> m;
		if (m == 1)
		{
			cout << "Specializarile sunt:" << endl;
			string* aux = f10.getspecializari();
			for (int i = 0;i < f10.getnrspecializari();i++)
				cout << aux[i] << endl;
			cout << "\nIntroduceti tasta 1 pentru a reveni la meniul principal sau tasta 0 pentru a parasi meniul!" << endl;
			int n;
			cin >> n;
			if (n == 1)
				continue;
			else if (n == 0)
				break;
		}
		else if (m == 2)
		{
			cout << "Caminele sunt:" << endl;
			cout << c10.getlocatie() << endl;
			cout << "Capacitate maxima: " << c10.getnrmaximpersoanecamin() << endl;
			cout << "Numar de persoane in fiecare camera: " << c10.getnrmaximpersoanecamera() << endl;
			cout << "Numar camere: " << c10.getnrnrcamere() << endl;
			cout << "\nIntroduceti tasta 1 pentru a reveni la meniul principal sau tasta 0 pentru a parasi meniul!" << endl;
			int n;
			cin >> n;
			if (n == 1)
				continue;
			else if (n == 0)
				break;
		}
		else if (m == 3)
		{
			cout << "Nume: " << p10.getnume() << endl;
			string* aux9 = p10.getmaterii();
			cout << "Materii predate: ";
			for (int i = 0;i < p10.getnrmaterii();i++)
				cout << aux9[i] << ", ";
			cout << "\nIntroduceti tasta 1 pentru a reveni la meniul principal sau tasta 0 pentru a parasi meniul!" << endl;
			int n;
			cin >> n;
			if (n == 1)
				continue;
			else if (n == 0)
				break;
		}
		else if (m == 4)
		{
			cout << "Cod cladire: " << cl10.getcodidentificare() << endl;
			cout << "Denumire cladire: " << cl10.getdenumire() << endl;
			int* aux3 = cl10.getnrsala();
			int* aux2 = cl10.getnrlocuri();
			for (int i = 0;i < cl10.getnrsali();i++)
				cout << "Sala " << aux3[i] << " are " << aux2[i] << " locuri" << endl;
			cout << "\nIntroduceti tasta 1 pentru a reveni la meniul principal sau tasta 0 pentru a parasi meniul!" << endl;
			int n;
			cin >> n;
			if (n == 1)
				continue;
			else if (n == 0)
				break;
		}
	} while (m >= 1 && m <= 4);
	cout << "Multumim ca ati ales ASE!" << endl;


	//-------------------------------Incarcarea de date din fisiere CSV-------------------------------

	//Facultate
	ifstream cin1;
	cin1.open("Facultate.csv");
	if (cin1.is_open())
	{
		f1.importCSV(cin1);
		cin1.close();
		cout << f1;
	}
	else cout << "Fisierul nu se poate deschide\n";

	//Camin
	ifstream cin2;
	cin2.open("Camin.csv");
	if (cin2.is_open())
	{
		c1.importCSV(cin2);
		cin2.close();
		cout << c1;
	}
	else cout << "Fisierul nu se poate deschide\n";

	//Profesor
	ifstream cin3;
	cin3.open("Profesor.csv");
	if (cin3.is_open())
	{
		p1.importCSV(cin3);
		cin3.close();
		cout << p1;
	}
	else cout << "Fisierul nu se poate deschide\n";

	//Student
	ifstream cin4;
	cin4.open("Student.csv");
	if (cin4.is_open())
	{
		s1.importCSV(cin4);
		cin4.close();
		cout << s1;
	}
	else cout << "Fisierul nu se poate deschide\n";

	//Cladire
	ifstream cin5;
	cin5.open("Cladire.csv");
	if (cin5.is_open())
	{
		cl1.importCSV(cin5);
		cin5.close();
		cout << cl1;
	}
	else cout << "Fisierul nu se poate deschide\n";

	cout << "\n---------------Generare rapoarte---------------\n";

	// Raport 1. 
	cout << "\nSa se afiseze toate notele pentru un student inregistrat.\n";

	ofstream ro1;
	ro1.open("Raport1.txt");
	if (ro1.is_open())
	{
		s2.Raport(ro1);
		ro1.close();
	}

	cout << endl << endl;

	// Raport 2. 
	cout << "\nSa se afiseze numarul fiecarei camere, urmata de valoarea utilitatilor pentru un camin inregistrat.\n";

	ofstream ro2;
	ro2.open("Raport2.txt");
	if (ro2.is_open())
	{
		c2.Raport(ro2);
		ro2.close();
	}

	// Raport 3. 
	cout << "\nSa se afiseze numarul total de studenti pentru o facultate inregistrata.\n";

	ofstream ro3;
	ro3.open("Raport3.txt");
	if (ro3.is_open())
	{
		f2.Raport(ro3);
		ro3.close();
	}

	cout << endl;

	//---------------------------Salvare date aplicatie in fisiere binare---------------------------

	//Camin

	ofstream out1;
	out1.open("Fisierb1.bin", ofstream::binary);
	if (out1.is_open())
	{
		c10.writeToFile(out1);
		out1.close();
	}

	Camin c5(132, "Tei");

	ifstream in1;
	in1.open("Fisierb1.bin", ifstream::binary);
	if (in1.is_open())
	{
		c5.readFromFile(in1);
		in1.close();
	}
	cout << c5;

	//Student

	ofstream out2;
	out2.open("Fisierb2.bin", ofstream::binary);
	if (out2.is_open())
	{
		s10.writeToFile(out2);
		out2.close();
	}

	Student s5(103, "Udriste Mihai");

	ifstream in2;
	in2.open("Fisierb2.bin", ifstream::binary);
	if (in2.is_open())
	{
		s5.readFromFile(in2);
		in2.close();
	}

	cout << s5;

	//Cladire

	ofstream out3;
	out3.open("Fisierb3.bin", ofstream::binary);
	if (out3.is_open())
	{
		cl2.writeToFile(out3);
		out3.close();
	}

	Cladire cl5(2, "Mihai Eminescu");

	ifstream in3;
	in3.open("Fisierb3.bin", ifstream::binary);
	if (in3.is_open())
	{
		cl5.readFromFile(in3);
		in3.close();
	}
	cout << cl5;

	//-----------------------------------Libraria STL-----------------------------------

	cout << "\n---------------STL VECTOR---------------\n";

	vector<int> v1;

	aux5 = s2.getnote();
	for (int i = 0;i < s2.getnrnote();i++)
		v1.push_back(aux5[i]);

	vector<int>::iterator it1;
	for (it1 = v1.begin(); it1 != v1.end(); it1++)
		cout << *it1 << " ";

	cout << "\n---------------STL LIST----------------\n";

	list <float> l2;

	l2.push_back(aux5[0]);
	l2.push_front(aux5[2]);
	l2.push_back(aux5[1]);

	list<float>::reverse_iterator it2;
	for (it2 = l2.rbegin(); it2 != l2.rend(); it2++)
		cout << *it2 << " ";

	cout << "\n---------------STL SET-----------------\n";

	set <string> s9;
	s9.insert(p1.getnume());
	s9.insert(p2.getnume());

	set<string>::iterator it3;
	for (it3 = s9.begin(); it3 != s9.end(); it3++)
		cout << *it3 << endl;

	cout << "\n----------------STL MAP-----------------\n";

	map<int, string> m4;
	m4[10] = cl1.getdenumire();
	m4[100] = cl2.getdenumire();
	m4[21] = c1.getlocatie();
	m4[10] = c2.getlocatie();
	map<int, string>::iterator it4;
	for (it4 = m4.begin(); it4 != m4.end(); it4++)
		cout << it4->first << " " << it4->second << endl;

	cout << "\n---------------Clase derivate---------------\n";

	int v30[3] = { 7, 10, 9 };
	float v31[3] = { 8.68, 0, 0 };
	ProfesorDoctorand pd1(102, 3, v30 , "Alexandru Isvoranu", v31 , 1, 107);
	cout << pd1<<endl;

	string v32[2] = { "BCO","BCE" };
	int v33[2] = { 4,5 };
	Decan d1 (1002, 2, v32, "Mitrut Dorin", v33, "CSIE", 15);
	cout << d1;

	cout << "\n---------------Clasa abstracta---------------\n";

	calcul* p[] = {&p2, &p10};
	cout << endl;
	cout << "Salariul: "<<p[0]->salariu() << endl;
	cout << "Pensia: " << p[0]->pensie() << endl;
	cout << endl;
	cout << "Salariul: " << p[1]->salariu() << endl;
	cout << "Pensia: " << p[1]->pensie() << endl;

	cout << "\n---------------Metode virtuale---------------\n";

	s1.print();
	pd1.print();
	p1.print();
	d1.print();

	cout << "\n------Familie de clase si vector de pointeri------\n";

	Profesor* listaProfesori1[] = { &p1,&p2,&p10 };
	Facultate f5 (11, "CSIE", 3, listaProfesori1);
	f5.afisare();

	cout << "\n------Calea completa catre alte fisiere cu date------\n";

	string cale;
	cout << "Introduceti calea catre fisier: ";
	cin >> cale;

	ifstream fisier(cale);

	string nou;

	while (getline(fisier, nou))
	{
		d1.setfacultate(nou);
		cout << d1.getfacultate();
	}

	fisier.close();
	
	return 0;
}