#include <iostream>
/*
Zad. 6.4.
Utworzyć tablicę struktur zawierającą podstawowe dane o 3 markach samochodów (renault, peugeot i opel) takie jak:
- model
- rodzaj (osobowy, dostawczy)-
- typ nadwozia (kombi, hatchback, liftback itd.).
- rok produkcji
- przebieg
- pojemność silnika
Umożliwić dodawanie dowolnej liczby rekordów użytkownikowi jak również wyświetlanie listy aut każdej marki.  (rozszerzyć program o usuwanie i dla chętnych zastosować funkcje)

*/

using namespace std;

string Marka[] = {"Renault","Peugeot","Opel"};
string TypNadwozia[]  = {"kombi","hatchback","liftback"};
string Rodzaj[] = {"osobowy","dostawczy"};
string Modele[3][3] = {   {"Clio", "Megane", "Kangoo" },
                        {"206", "306", "Partner"},
                        {"Corsa", "Astra", "Combo"}
                        };
struct Samochod {
    int IMarka;
    int IRodzaj;
    string Model;
    int ITypNadwozia;
    int RokProdukcji;
    int Przebieg;
    int PojemnoscSilnika;
  };

const int SamochodTabPrzyrost = 20000; // o ile powiekszamy tablice samochodow
Samochod * SamochodTab = new Samochod[SamochodTabPrzyrost];
int SamochodTabWielkosc = 0; // aktualna wielkosc tablicy samochodow
int ISamochodOstatni=-1; // wskaźnik na aktualnie ostatni samochod w tablicy


void  SamochodyZrobMiejsce(void){
    int i;
    Samochod * SamochodTab1;

    // jeśli nie mamy miejsca to dodajemy
    if (SamochodTabWielkosc==ISamochodOstatni) {

        SamochodTab1 = new Samochod[SamochodTabWielkosc+SamochodTabPrzyrost];
        for (i=0;i<SamochodTabWielkosc;i++){
            SamochodTab1[i]=SamochodTab[i];
        }

        delete [] SamochodTab;
        SamochodTabWielkosc+=SamochodTabPrzyrost;
        SamochodTab=SamochodTab1;
    }
}

void SamochodyZamienZOstatnim(int n){
    Samochod a,b;

    a=SamochodTab[n];
    b=SamochodTab[ISamochodOstatni];

    SamochodTab[n]=b;
    SamochodTab[ISamochodOstatni]=a;
}

void SamochodyZwolnijPuste(void){
    // zwalnia pamiec
    Samochod * SamochodTab1;

    SamochodTabWielkosc=ISamochodOstatni+1;
    SamochodTab1 = new Samochod[SamochodTabWielkosc+SamochodTabPrzyrost];
    for (int i=0;i<=ISamochodOstatni;i++){
        SamochodTab1[i]=SamochodTab[i];
    }

    delete [] SamochodTab;
    SamochodTab=SamochodTab1;
}

void SamochodySkasuj(int aKtoreAuto) {
    if (aKtoreAuto>0 && aKtoreAuto<=ISamochodOstatni) {
        SamochodyZamienZOstatnim(aKtoreAuto);
        ISamochodOstatni--;
    }
    SamochodyZwolnijPuste();
}

void SamochodyWylistuj(int aMarka) {
    cout << "Marka\tModel\tNadwozie\tPoj\tPrzebieg" << endl;
    for (int i=0;i<=ISamochodOstatni;i++){
        if (aMarka==SamochodTab[i].IMarka)
        cout << i << " " << Marka[SamochodTab[i].IMarka]
        << "\t"<< SamochodTab[i].Model
        << "\t"<< TypNadwozia[SamochodTab[i].ITypNadwozia]
        << "\t" << SamochodTab[i].PojemnoscSilnika
        << "\t" << SamochodTab[i].Przebieg
        << endl;
    }
    cout << endl;
}

void SamochodyDodaj(void){
    int aMarka;
    int aRodzaj, aModel;
    ISamochodOstatni++;
    SamochodyZrobMiejsce();
    aMarka = rand() % 3;
    aModel = rand()%3;
    aRodzaj = rand()%2;
    SamochodTab[ISamochodOstatni].IMarka= aMarka;
    SamochodTab[ISamochodOstatni].Model= Modele[aMarka][aModel];
    SamochodTab[ISamochodOstatni].IRodzaj=aRodzaj;
    SamochodTab[ISamochodOstatni].ITypNadwozia=rand() % 3;
    SamochodTab[ISamochodOstatni].RokProdukcji=1990+rand() % 30;
    SamochodTab[ISamochodOstatni].Przebieg=100+rand() % 200000;
    SamochodTab[ISamochodOstatni].PojemnoscSilnika=900+rand() % 2000;

}

string Menu[] = { "Dodaj samochód", "Wyświetl samochody", "Usuń samochód", "Zwolnij miejsce", "Wyjście"};
const int MenuMax = 4; //

int MenuWyswietl(string aMenu[], int aMenuMax) {
    int res;
    cout << "Liczba samochodów: " << ISamochodOstatni+1 << "\t Miejsca w tabeli: " << SamochodTabWielkosc << endl;

    do {
        for (int i=0;i<=aMenuMax;i++) {
            cout << i <<  " : " << aMenu[i] <<  endl;
        }
        cin >> res;
    } while (res < 0 || res > aMenuMax);
    return res;
}

int MenuGlowne(void) {
    int Wybor;
    while ((Wybor=MenuWyswietl(Menu, MenuMax))!=MenuMax) {
        if (Wybor==0){
            for (int i=0;i<10000;i++)
                SamochodyDodaj();
        } else
        if (Wybor==1){
                cout << "Wybierz markę do wyświetlenia:" << endl;
                SamochodyWylistuj(MenuWyswietl(Marka,2));
        } else
        if (Wybor==2){
            int KtoreAuto;
            cout << "Podaj numer samochodu do usunięcia:" << endl;
            cin >> KtoreAuto;
            SamochodySkasuj(KtoreAuto);

        } else
        if (Wybor==3){
            int IleZostawic;
            cout << "Podaj ile samochodów zostawić:" << endl;
            cin >> IleZostawic;
            if (IleZostawic<=ISamochodOstatni && IleZostawic>0)
                ISamochodOstatni=IleZostawic-1;
            SamochodyZwolnijPuste();
        }
    };
    return Wybor;
}


int main()
{
    //cout << "SamochodTabWielkosc:" << SamochodTabWielkosc << endl;
    MenuGlowne();

    return 0;
}
