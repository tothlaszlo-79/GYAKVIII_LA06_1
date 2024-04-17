#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Kocsi {
    char nev[25];
    int kor;
    int ar;
};

class Kereskedes {
    private: Kocsi* kocsik; int db;
    public: Kereskedes(char* fnev);
        int Kiir();
        Kocsi Legfiatalabb();
        double Atlagar();

        ~Kereskedes() { delete[] kocsik; }
};



int main()
{
    char fnev[] = "auto.dat";
    Kereskedes k(fnev);
    cout << "\nA kereskedesben levo autok szama: " << k.Kiir() << endl;
    cout << setprecision(9) << "\nA kereskedesben levo autok atlagara: " << k.Atlagar() << endl;
    cout << "\nA kereskedesben levo legfiatalabb auto adatai: " << endl;
    Kocsi fiatal = k.Legfiatalabb();
    cout << "Nev: " << fiatal.nev << 
         " Gyartasi eve: " << fiatal.kor <<
         " Ara: " << fiatal.ar << endl;
    system("PAUSE");
    return 0;
}

Kereskedes::Kereskedes(char* fnev) {
	ifstream be(fnev, ios::binary); // binaris fajl megnyit�sa olvas�sra
    if (be.fail()) { // ha nem siker�lt megnyitni a f�jlt
	   cerr << "Nem lehet megnyitni a fajlt!\n";
	   exit(1);
    }
    int szam = 0;
    Kocsi kocsi;

    while (!be.eof()) { // am�g nem �r�nk a f�jl v�g�re
		be.read((char*)&kocsi, sizeof(Kocsi)); // beolvasunk egy rekordot
	    if (!be.eof()) szam++; // ha nem �rt�nk a f�jl v�g�re, akkor n�velj�k a sz�mot
	}
    be.clear(); // be�ll�tjuk a hibajelz�t �resre
    be.seekg(0, ios::beg); // a f�jl elej�re ugrunk
    db = szam; // a sz�mot elt�roljuk a db v�ltoz�ban
    kocsik = new Kocsi[db]; // lefoglalunk egy t�mb�t a kocsiknak
    int i = 0; // ciklusv�ltoz�
    while (!be.eof())
    {
        be.read((char*)&kocsi, sizeof(Kocsi)); // beolvasunk egy rekordot
        if (!be.eof()) {
			kocsik[i] = kocsi; // elt�roljuk a kocsit a t�mbben
			i++; // n�velj�k a ciklusv�ltoz�t
		}
    }
	be.close(); // bez�rjuk a f�jlt
}

int Kereskedes::Kiir() {
    cout.setf(ios::left); // balra igaz�t�s
    cout << setw(25) << "Nev" << setw(10) << "Kor" << setw(10) << "Ar" << endl; // fejl�c ki�r�sa
    for (int i = 0; i < db; i++) {
        cout << setw(25) << kocsik[i].nev << setw(10) << kocsik[i].kor << setw(10) << kocsik[i].ar << endl;
    }
    return db; // visszaadjuk a kocsik sz�m�t
};

Kocsi Kereskedes::Legfiatalabb() {
    Kocsi min = kocsik[0]; // az els� kocsi a legfiatalabb
    for (int i = 1; i < db; i++) {
		if (min.kor < kocsik[i].kor) min = kocsik[i]; // ha a kocsi kor�bbi, mint a min, akkor a min lesz az adott kocsi
	}
	return min; // visszaadjuk a legfiatalabb kocsit
};

double Kereskedes::Atlagar() {
	double osszeg = 0; // �sszeg v�ltoz�
    for (int i = 0; i < db; i++) {
		osszeg += kocsik[i].ar; // hozz�adjuk az �rat az �sszeghez
	}
    return osszeg / db; // visszaadjuk az �tlag�rat
};