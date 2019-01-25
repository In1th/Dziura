#ifndef loveanime
#include <iostream>
#include <vector>
#define loveanime
#endif

using namespace std;

/** -------------------------------------------------
  * W tym pliku znajdują się wszystkie definicje klas
  * przedmiotów,ekwipunków oraz sklepów
  * -------------------------------------------------
  * Wersja 1.01.1 (01/25/2019 r.)
  * -------------------------------------------------
  * Autor pliku nagłówkowego - Mateusz Kruk
  */

class Item //klasa opisująca dowolny inny przedmiot niż te poniżej
{
public:
    string name;
    int cost;
    int quantity;
    Item(string,int,int);
    void change_quantity(int ammout);
    void inspect();
};

class Weapon :public Item //klasa opisująca broń
{
public:
    int damage;
    unsigned char type;
    Weapon(string,int,int,int,unsigned char);
    void inspect();
};

class Armor :public Item //klasa opisująca element pancerza
{
public:
    int defence;
    unsigned char type;
    /* TYPY ZBROI
     * 0 - Hełm
     * 1 - Rękawice
     * 2 - Pancerz
     * 3 - Buty
     * 4 - Naszyjnik
     */
    Armor(string,int,int,unsigned char);
    void inspect();
};

class Potion :public Item //klasa opisująca mikturę
{
public:
    unsigned char effect;
    Potion(string,int,int,unsigned char);
    void inspect();
};

class Ekwipunek   //klasa opisująca ekwipunek
{

    int potki_max;
    int przedmioty_max;

public:

    int ilosc_zlota;

    Armor pancerz[5];
    Weapon bron[2]; //2 bronie (podstawowa oraz boczna)

    vector<Potion> potki;
    vector<Item> przedmioty;


    Ekwipunek(int,int,int); //Kontruktor klasy

    bool czy_pelen(bool ktory); //fałsz dla przedmiotów, prawda dla mikstur
    bool czy_bedzie_pelen(bool ktory,int ile_dodane);

    bool zmien_ilosc_zlota(int wartosc);

    void wypisz_ekwipunek();

    //Dodawanie elemetów ekwipunku
    void dodaj_przedmiot(string nazwa,int cena,int ilosc);
    void dodaj_potke(string nazwa,int cena,unsigned char efekt,int ilosc);
    void dodaj_bron(string nazwa,int cena,unsigned char typ,int obrazenia);
    void dodaj_pancerz(string nazwa,int cena,unsigned char typ,int obrona);

    //Usuwanie elementów ekwipunku
    bool usun_przedmiot(string nazwa,int ilosc);
    bool usun_bron(string nazwa);
    bool usun_potke(string nazwa,int ilosc);
    bool usun_pancerz(string nazwa);

    void zapisz_ekwipunek();
};

class Sklep :public Ekwipunek
{
public:
    string name;

    vector<Weapon> bronie;
    vector<Armor> zbroje;

    Sklep(int);

    void wypisz_ekwipunek();

    void dodaj_bron(string nazwa,int cena,unsigned char typ,int obrazenia);
    void dodaj_pancerz(string nazwa,int cena,unsigned char typ,int obrona);

    bool usun_bron(string nazwa);
    bool usun_pancerz(string nazwa);
};
