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
	ifstream be(fnev, ios::binary); // binaris fajl megnyitása olvasásra
    if (be.fail()) { // ha nem sikerült megnyitni a fájlt
	   cerr << "Nem lehet megnyitni a fajlt!\n";
	   exit(1);
    }
    int szam = 0;
    Kocsi kocsi;

    while (!be.eof()) { // amíg nem érünk a fájl végére
		be.read((char*)&kocsi, sizeof(Kocsi)); // beolvasunk egy rekordot
	    if (!be.eof()) szam++; // ha nem értünk a fájl végére, akkor növeljük a számot
	}
    be.clear(); // beállítjuk a hibajelzõt üresre
    be.seekg(0, ios::beg); // a fájl elejére ugrunk
    db = szam; // a számot eltároljuk a db változóban
    kocsik = new Kocsi[db]; // lefoglalunk egy tömböt a kocsiknak
    int i = 0; // ciklusváltozó
    while (!be.eof())
    {
        be.read((char*)&kocsi, sizeof(Kocsi)); // beolvasunk egy rekordot
        if (!be.eof()) {
			kocsik[i] = kocsi; // eltároljuk a kocsit a tömbben
			i++; // növeljük a ciklusváltozót
		}
    }
	be.close(); // bezárjuk a fájlt
}

int Kereskedes::Kiir() {
    cout.setf(ios::left); // balra igazítás
    cout << setw(25) << "Nev" << setw(10) << "Kor" << setw(10) << "Ar" << endl; // fejléc kiírása
    for (int i = 0; i < db; i++) {
        cout << setw(25) << kocsik[i].nev << setw(10) << kocsik[i].kor << setw(10) << kocsik[i].ar << endl;
    }
    return db; // visszaadjuk a kocsik számát
};

Kocsi Kereskedes::Legfiatalabb() {
    Kocsi min = kocsik[0]; // az elsõ kocsi a legfiatalabb
    for (int i = 1; i < db; i++) {
		if (min.kor < kocsik[i].kor) min = kocsik[i]; // ha a kocsi korábbi, mint a min, akkor a min lesz az adott kocsi
	}
	return min; // visszaadjuk a legfiatalabb kocsit
};

double Kereskedes::Atlagar() {
	double osszeg = 0; // összeg változó
    for (int i = 0; i < db; i++) {
		osszeg += kocsik[i].ar; // hozzáadjuk az árat az összeghez
	}
    return osszeg / db; // visszaadjuk az átlagárat
};