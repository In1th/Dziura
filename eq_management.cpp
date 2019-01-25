#ifndef loveanime
#include <iostream>
#include <vector>
#include <fstream>
#define loveanime
#endif


#include "eq_management.h"

/** -----------------------------------------------
  * W tym pliku znajdują się wszystkie funckje dot.
  * przedmiotów,ekwipunków, sklepów
  * oraz zarządzania nimi
  * -----------------------------------------------
  * Wersja 1.0 (01/25/2019)
  * -----------------------------------------------
  * Autor modułu - Mateusz Kruk
  */

/* ---------------------------------------------------
 * WAŻNA INFROMACJA - WZÓR ZAPISU EKWIPUNKU DO PLIKU
 * ---------------------------------------------------
 * 1. Maksymalna ilość przedmiotów w ekwipunku
 * 2. Maksymalna ilość mikstur w ekwipunku
 * 3. Ilość złota w ekwipunku
 * 4. Bronie
 *  - Jeżeli nie ma broni to jest wtedy napis "nic"
 * 5. Pancerz
 *  - Jeżeli nie ma pancerzu to jest wtedy napis "nic"
 * 6. Ilość mikstur w ekwipunku
 * 7. Mikstury
 * 8. Ilość przedmiotów w ekwipunku
 * 9. Przedmioty
 */


//Kontruktory

Item::Item(string n = "",int c = 0,int q = 0)
{
 name = n;
 cost = c;
 quantity = q;
}

Weapon::Weapon(string n = "",int c = 0,int q = 0,int dmg = 0,unsigned char t = 0)
{
    name = n;
    cost = c;
    quantity = 0;
    damage = dmg;
    type = t;
}

Potion::Potion(string n = "",int c = 0,int q = 0,unsigned char e = 0)
{
    name = n;
    cost = c;
    quantity = 0;
    effect = e;
}

Armor::Armor(string n = "",int c = 0,int def = 0,unsigned char t = 5)
{
    name = n;
    cost = c;
    defence = def;
    type = t;
}

Ekwipunek::Ekwipunek(int sz = 0,int i_max = 20,int p_max = 5)
{
    ifstream plik("eq_gracza.txt"); //WiP
    if (plik)
        {
        plik >> przedmioty_max;
        plik >> potki_max;
        plik >> ilosc_zlota;
        for(int i = 0;i<2;i++) //Wczytywanie broni
        {
            string nazwa;
            plik >> nazwa;
            if (nazwa != "nic")
            {
                int koszt, obrazenia;
                unsigned char typ;
                plik >> koszt;
                plik >> obrazenia;
                plik >> typ;
                Weapon nowa_bron(nazwa,koszt,1,obrazenia,typ);
                bron[i] = nowa_bron;
            }
        }
        for(int i = 0;i<5;i++) //Wczytywanie zbroi
        {
            string nazwa;
            plik >> nazwa;
            if (nazwa != "nic")
            {
                int koszt, obrona;
                unsigned char typ;
                plik >> koszt;
                plik >> obrona;
                plik >> typ;
                Armor nowy_pancerz(nazwa,koszt,obrona,typ);
                pancerz[i] = nowy_pancerz;
            }
        }
        int ilosc_potek, ilosc_przedmiotow;
        plik >> ilosc_potek;
        for (int i = 0; i < ilosc_potek; i++) //Wczytywanie potek
        {
          string nazwa;
          int koszt, ilosc;
          unsigned char efekt;
          plik >> nazwa;
          plik >> koszt;
          plik >> ilosc;
          plik >> efekt;
          Potion nowa_potka(nazwa,koszt,ilosc,efekt);
          potki.push_back(nowa_potka);
        }
        plik >> ilosc_przedmiotow;
        for (int i = 0; i < ilosc_przedmiotow; i++) //Wczytywanie przedmiotów
        {
          string nazwa;
          int koszt, ilosc;
          plik >> nazwa;
          plik >> koszt;
          plik >> ilosc;
          Item nowy_przedmiot(nazwa,koszt,ilosc);
          przedmioty.push_back(nowy_przedmiot);
        }
        }
    else
        {
        ilosc_zlota = sz;
        przedmioty_max = i_max;
        potki_max = p_max;
        }
}

Sklep::Sklep(int sz = 100)
{
    ilosc_zlota = sz;
}

//Metoda zarządzania przedmiotem

void Item::change_quantity(int ammount)
{
    quantity += ammount;
}

//Zapis ekwipunku

void Ekwipunek::zapisz_ekwipunek()
{
    ofstream plik("eq_gracza.txt");
    if (plik)
    {
        plik << przedmioty_max <<endl;
        plik << potki_max << endl;
        plik << ilosc_zlota << endl;
        for (int i = 0; i < 2; i++)
        {
            if (bron[i].name == "") plik << "nic" << endl;
            else
                {
                plik << bron[i].name << endl;
                plik << bron[i].cost << endl;
                plik << bron[i].damage << endl;
                plik << bron[i].type << endl;
                }
        }
        for (int i = 0; i < 5; i++)
        {
            if (pancerz[i].name == "") plik << "nic" << endl;
            else
                {
                plik << pancerz[i].name << endl;
                plik << pancerz[i].cost << endl;
                plik << pancerz[i].defence << endl;
                plik << pancerz[i].type << endl;
                }
        }
        plik << potki.size() << endl;
        for (int i = 0; i < potki.size();i++)
        {
            plik << potki[i].name << endl;
            plik << potki[i].cost << endl;
            plik << potki[i].quantity << endl;
            plik << potki[i].effect << endl;
        }
        plik << przedmioty.size() << endl;
        for (int i = 0; i < przedmioty.size();i++)
        {
            plik << przedmioty[i].name << endl;
            plik << przedmioty[i].cost << endl;
            plik << przedmioty[i].quantity << endl;
        }

    }
    else
    {
        cout<<"Napotkano blad!"<<endl;
    }
}

//Inspektowanie przedmiotów

void Item::inspect()
{
    cout<<"Nazwa: "<<name<<endl;
    cout<<"Wartosc w zlocie: "<<cost<<endl;
    cout<<"Ilosc: "<<quantity<<endl;
}

void Weapon::inspect()
{
    cout<<"Nazwa: "<<name<<endl;
    cout<<"Typ: "<<type<<endl;
    cout<<"Wartosc w zlocie: "<<cost<<endl;
    cout<<"Obrazenia: "<<damage<<endl;
}

void Armor::inspect()
{
    cout<<"Nazwa: "<<name<<endl;
    cout<<"Typ: "<<type<<endl;
    cout<<"Wartosc w zlocie: "<<cost<<endl;
    cout<<"Obrona: "<<defence<<endl;
}

void Potion::inspect()
{
    cout<<"Nazwa: "<<name<<endl;
    cout<<"Efekt: "<<effect<<endl;
    cout<<"Wartosc w zlocie: "<<cost<<endl;
    cout<<"Ilosc: "<<quantity<<endl;
}

//Metody zarządzania ekwipunkiem

void Ekwipunek::wypisz_ekwipunek()
{
    string typ_zbroi;

    cout<<endl<<"Twoja ilosc zlota: "<<ilosc_zlota<<endl;
    cout<<endl<<"PANCERZ:"<<endl;

    for (int i = 0;i<5;i++)
    {
        switch(i)
        {
        case 0: typ_zbroi = "Helm: "; break;
        case 1: typ_zbroi = "Naszyjnik: "; break;
        case 2: typ_zbroi = "Rekawice: "; break;
        case 3: typ_zbroi = "Zbroja: "; break;
        case 4: typ_zbroi = "Buty: " ; break;
        }
        if (pancerz[i].name == "") cout<<typ_zbroi<<"BRAK"<<endl;
        else cout<<typ_zbroi<<pancerz[i].name<<endl;
    }
    cout<<endl<<"BRONIE: "<<endl;
    for (int i=0; i<2; i++)
    {
        if (bron[i].name == "") cout<<(i+1)<<". Bron: BRAK"<<endl;
        else cout<<(i+1)<<". Bron: "<<bron[i].name<<endl;
    }
    cout<<endl<<"MIKSTORY: "<<endl;
    if (potki.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < potki.size(); i++)cout<<potki[i].name<<" x"<<potki[i].quantity<<endl;

    cout<<endl<<"PRZEDMIOTY: "<<endl;
    if (przedmioty.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < przedmioty.size(); i++)cout<<przedmioty[i].name<<" x"<<przedmioty[i].quantity<<endl;
}

void Sklep::wypisz_ekwipunek()
{
    cout<<endl<<"Witaj w sklepie "<<name<<endl;
    cout<<"Ilosc zlota sprzedawcy: "<<ilosc_zlota<<endl;
    cout<<endl<<"PANCERZ:"<<endl;

    cout<<endl<<"BRONIE: "<<endl;
    if (bronie.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < bronie.size(); i++)cout<<bronie[i].name<<" "<<bronie[i].cost<<" SZ OBR - "<<bronie[i].damage<<endl;

    cout<<endl<<"ZBROJE: "<<endl;
    if (zbroje.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < bronie.size(); i++)cout<<zbroje[i].name<<" "<<zbroje[i].cost<<" SZ DEF - "<<zbroje[i].defence<<endl;

    cout<<endl<<"MIKSTORY: "<<endl;
    if (potki.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < potki.size(); i++)cout<<potki[i].name<<" x"<<potki[i].quantity<<" "<<potki[i].cost<<" SZ EFEKT - "<<potki[i].effect<<endl;

    cout<<endl<<"PRZEDMIOTY: "<<endl;
    if (przedmioty.empty()) cout<<"BRAK"<<endl;
    else for (int i = 0; i < przedmioty.size(); i++)cout<<przedmioty[i].name<<" x"<<przedmioty[i].quantity<<" "<<przedmioty[i].cost<<" SZ"<<endl;
}

bool Ekwipunek::zmien_ilosc_zlota(int wartosc)
{
    if (wartosc < 0 && -wartosc > ilosc_zlota)
    {
        cout<<"Nie masz tylu funduszy."<<endl;
        return false;
    }
    ilosc_zlota += wartosc;
    cout<<endl<<"Wartosc zostala zmieniona"<<endl;
    return true;
}

bool Ekwipunek::czy_pelen(bool ktory)
{
    int obecne_zuzycie_miejsca;

    if (ktory)
    {
        for(int i = 0; i<potki.size(); i++) obecne_zuzycie_miejsca += potki[i].quantity;
        if (obecne_zuzycie_miejsca < potki_max) return false;
        else if (obecne_zuzycie_miejsca == potki_max) return true;
    }
    else
    {
        for(int i = 0; i<przedmioty.size(); i++) obecne_zuzycie_miejsca += przedmioty[i].quantity;
        if (obecne_zuzycie_miejsca < przedmioty_max) return false;
        else if (obecne_zuzycie_miejsca == przedmioty_max) return true;
    }
}

bool Ekwipunek::czy_bedzie_pelen(bool ktory,int ile_dodane)
{
   int obecne_zuzycie_miejsca = ile_dodane;

    if (ktory)
    {
        for(int i = 0; i<potki.size(); i++) obecne_zuzycie_miejsca += potki[i].quantity;
        if (obecne_zuzycie_miejsca < potki_max) return false;
        else if (obecne_zuzycie_miejsca == potki_max) return true;
    }
    else
    {
        for(int i = 0; i<przedmioty.size(); i++) obecne_zuzycie_miejsca += przedmioty[i].quantity;
        if (obecne_zuzycie_miejsca < przedmioty_max) return false;
        else if (obecne_zuzycie_miejsca == przedmioty_max) return true;
    }
}

//Dodawanie i usuwanie przedmiotów z ekwipunku

void Ekwipunek::dodaj_przedmiot(string nazwa,int cena,int ilosc)
{
    bool czy_juz_jest = false;
    int index_p;
    for(int i = 0; i<przedmioty.size(); i++)
    {
        if (przedmioty[i].name == nazwa)
        {
            czy_juz_jest = true;
            index_p = i;
            break;
        }
    }
    if (czy_juz_jest)
    {
        przedmioty[index_p].change_quantity(ilosc);
    }
    else
    {
        Item nowy_przedmiot(nazwa,cena,ilosc);
        przedmioty.push_back(nowy_przedmiot);
    }
}

void Ekwipunek::dodaj_potke(string nazwa,int cena,unsigned char efekt,int ilosc)
{
    bool czy_juz_jest = false;
    int index_p;
    for(int i = 0; i<potki.size(); i++)
    {
        if (potki[i].name == nazwa)
        {
            czy_juz_jest = true;
            index_p = i;
            break;
        }
    }
    if (czy_juz_jest)
    {
        potki[index_p].change_quantity(ilosc);
    }
    else
    {
        Potion nowy_potion(nazwa,cena,ilosc,efekt);
        potki.push_back(nowy_potion);
    }
}

void Ekwipunek::dodaj_bron(string nazwa,int cena,unsigned char typ,int obrazenia)
{
    Weapon nowa_bron(nazwa,cena,obrazenia,typ);
    if (bron[0].name == "") bron[0] = nowa_bron;
    else bron[1] = nowa_bron;
}

void Ekwipunek::dodaj_pancerz(string nazwa,int cena,unsigned char typ,int obrona)
{
    Armor nowy_pancerz(nazwa,cena,obrona,typ);
    for (int i = 0;i<5;i++)
    {
        if (pancerz[i].name == "" && i == typ) pancerz[i] = nowy_pancerz;
        else if (pancerz[i].name != "" && i == typ)
        {
            cout<<"Nie mozesz zalozyc dwoch tych samych typow zbroi!"<<endl;
            return;
        }
    }
}

void Sklep::dodaj_bron(string nazwa,int cena,unsigned char typ,int obrazenia)
{
    Weapon nowa_bron(nazwa,cena,obrazenia,typ);
    bronie.push_back(nowa_bron);
}

void Sklep::dodaj_pancerz(string nazwa,int cena,unsigned char typ,int obrona)
{
    Armor nowy_pancerz(nazwa,cena,obrona,typ);
    zbroje.push_back(nowy_pancerz);
}

bool Ekwipunek::usun_przedmiot(string nazwa,int ilosc)
{
    int index_p = -1;
    for(int i = 0; i<przedmioty.size(); i++)
    {
        if (przedmioty[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1 || ilosc > przedmioty[index_p].quantity) return false;
    else if (przedmioty[index_p].quantity != ilosc) przedmioty[index_p].change_quantity(-ilosc);
    else przedmioty.erase(przedmioty.begin() + index_p);
    return true;
}

bool Ekwipunek::usun_potke(string nazwa,int ilosc)
{
    int index_p = -1;
    for(int i = 0; i<potki.size(); i++)
    {
        if (potki[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1 || ilosc > potki[index_p].quantity) return false;
    else if (potki[index_p].quantity != ilosc) potki[index_p].change_quantity(-ilosc);
    else potki.erase(potki.begin() + index_p);
    return true;
}

bool Ekwipunek::usun_bron(string nazwa)
{
    int index_p = -1;
    for(int i = 0; i<2; i++)
    {
        if (bron[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1) return false;
    else bron[index_p] = Weapon();
    return true;
}

bool Ekwipunek::usun_pancerz(string nazwa)
{
    int index_p = -1;
    for(int i = 0; i<5; i++)
    {
        if (pancerz[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1) return false;
    else pancerz[index_p] = Armor();
    return true;
}

bool Sklep::usun_bron(string nazwa)
{
   int index_p = -1;
    for(int i = 0; i<bronie.size(); i++)
    {
        if (bronie[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1) return false;
    else bronie.erase(bronie.begin() + index_p);
    return true;
}

bool Sklep::usun_pancerz(string nazwa)
{
   int index_p = -1;
    for(int i = 0; i<zbroje.size(); i++)
    {
        if (zbroje[i].name == nazwa)
        {
            index_p = i;
            break;
        }
    }
    if (index_p == -1) return false;
    else zbroje.erase(zbroje.begin() + index_p);
    return true;
}

bool handel(Ekwipunek &kupujacy,Sklep &sprzedajacy,string nazwa,int ilosc)
{
    int index_p;
    int typ = 0;

    for (int i = 0; i<sprzedajacy.bronie.size(); i++)
    {
        if (sprzedajacy.bronie[i].name == nazwa)
        {
            index_p = i;
            typ = 1;
            break;
        }
    }
    if (typ == 0)
    {
        for (int i = 0; i<sprzedajacy.zbroje.size(); i++)
        {
            if (sprzedajacy.zbroje[i].name == nazwa)
            {
                index_p = i;
                typ = 2;
                break;
            }
        }
    }
    if (typ == 0)
    {
        for (int i = 0; i<sprzedajacy.potki.size(); i++)
        {
            if (sprzedajacy.potki[i].name == nazwa)
            {
                index_p = i;
                typ = 3;
                break;
            }
        }
    }
    if (typ == 0)
    {
        for (int i = 0; i<sprzedajacy.przedmioty.size(); i++)
        {
            if (sprzedajacy.przedmioty[i].name == nazwa)
            {
                index_p = i;
                typ = 4;
                break;
            }
        }
    }
    if (typ == 0) return false;

    bool jest_miejsce;

    switch(typ)
    {
    case 3:
    {
        jest_miejsce = kupujacy.czy_pelen(true);
        jest_miejsce = kupujacy.czy_bedzie_pelen(true,ilosc);
    }
    break;
    case 4:
    case 2:
    case 1:
    {
        jest_miejsce = kupujacy.czy_pelen(false);
        jest_miejsce = kupujacy.czy_bedzie_pelen(false,ilosc);
    }
    break;
    }
    if (!jest_miejsce) return false;

    bool sa_fundusze;

 switch(typ)
 {
 case 1:
    {
        Weapon kupowana_bron = sprzedajacy.bronie[index_p];
        sa_fundusze = kupujacy.zmien_ilosc_zlota(-kupowana_bron.cost*ilosc);
        if (sa_fundusze) sprzedajacy.zmien_ilosc_zlota(-kupowana_bron.cost*ilosc);
        else return false;
        sprzedajacy.usun_bron(kupowana_bron.name);
        kupujacy.dodaj_bron(kupowana_bron.name,kupowana_bron.cost,kupowana_bron.type,kupowana_bron.damage);
    } break;
 case 2:
    {
        Armor kupowana_zbroja = sprzedajacy.zbroje[index_p];
        sa_fundusze = kupujacy.zmien_ilosc_zlota(-kupowana_zbroja.cost*ilosc);
        if (sa_fundusze) sprzedajacy.zmien_ilosc_zlota(-kupowana_zbroja.cost*ilosc);
        else return false;
        sprzedajacy.usun_pancerz(kupowana_zbroja.name);
        kupujacy.dodaj_pancerz(kupowana_zbroja.name,kupowana_zbroja.cost,kupowana_zbroja.type,kupowana_zbroja.defence);
    } break;
 case 3:
    {
        Potion kupowana_mikstura = sprzedajacy.potki[index_p];
        sa_fundusze = kupujacy.zmien_ilosc_zlota(-kupowana_mikstura.cost*ilosc);
        if (sa_fundusze) sprzedajacy.zmien_ilosc_zlota(-kupowana_mikstura.cost*ilosc);
        else return false;
        sprzedajacy.usun_potke(kupowana_mikstura.name,ilosc);
        kupujacy.dodaj_potke(kupowana_mikstura.name,kupowana_mikstura.cost,kupowana_mikstura.effect,ilosc);
    } break;
 case 4:
    {
        Item kupowany_przedmiot = sprzedajacy.przedmioty[index_p];
        sa_fundusze = kupujacy.zmien_ilosc_zlota(-kupowany_przedmiot.cost*ilosc);
        if (sa_fundusze) sprzedajacy.zmien_ilosc_zlota(-kupowany_przedmiot.cost*ilosc);
        else return false;
        sprzedajacy.usun_przedmiot(kupowany_przedmiot.name,ilosc);
        kupujacy.dodaj_przedmiot(kupowany_przedmiot.name,kupowany_przedmiot.cost,ilosc);
    } break;
 }

    return true;

}
