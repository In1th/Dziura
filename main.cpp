#include "eq_management.cpp"

using namespace std;

int main()
{
    Ekwipunek eq_gracza;
    bool czy_aktywne = false;
    int wybor;
    do
      {
        cout<<"MENU"<<endl;
        cout<<"-----------------------------------"<<endl;
        cout<<"0 - Zakoncz"<<endl;
        cout<<"1 - wypisz ekwipunek"<<endl;
        cout<<"2 - dodaj/odejmij zloto"<<endl;
        cout<<"3 - dodaj/usun przedmiot"<<endl;
        cout<<"-----------------------------------"<<endl;
        cin>>wybor;
        switch(wybor)
        {
        case 0: czy_aktywne = true; break;
        case 1: eq_gracza.wypisz_ekwipunek(); break;
        case 2:
            {
                int znak;
                int wartosc;
                cout<<endl<<"Czy mam odjac (-1) czy dodac (1) ilosc zlota?"<<endl;
                cin>>znak;
                cout<<"Wprosze podac ilosc zlota do zmienienia: ";
                cin>>wartosc;
                eq_gracza.zmien_ilosc_zlota(znak*wartosc);
             }break;
        case 3:
           {
            int operacja, typ;
            cout<<endl<<"Czy ma byc dodany (1), czy usuniety (2) przedmiot?"<<endl;
            cin>>operacja;
            cout<<"Czy to ma byc przedmiot (0),mikstura (1), czy bron (2)? "<<endl;
            cin>>typ;
            if (operacja == 1)
            {
                string name;
                int cost, number;
                cout<<"Podaj nazwe:";
                cin>>name;
                cout<<"Podaj wartosc tego przedmiotu w zlocie: ";
                cin>>cost;
                cout<<"Podaj ilosc tego przedmiotu: ";
                cin>>number;
                switch(typ)
                {
                    case 0: eq_gracza.dodaj_przedmiot(name,cost,number); break;
                    case 1:
                        {
                            unsigned char efekt;
                            cout<<"Podaj typ efektu mikstury: ";
                            cin>>efekt;
                            eq_gracza.dodaj_potke(name,cost,efekt,number);

                        }break;
                    case 2:
                        {
                            unsigned char nie_mam_pomyslu_na_nazwe;
                            int ddamage;
                            cout<<"Podaj typ broni: ";
                            cin>>nie_mam_pomyslu_na_nazwe;
                            cout<<"Podaj obrazenia broni: ";
                            cin>>ddamage;
                            eq_gracza.dodaj_bron(name,cost,nie_mam_pomyslu_na_nazwe,ddamage);
                        } break;
                }

            }
            else if (operacja == 2)
            {
                string name;
                int number;
                cout<<endl<<"Podaj nazwe przedmiotu: ";
                cin>>name;
                if (typ == 0 || typ == 1)
                {
                cout<<"Ile przedmiotow ma byc usunietych? ";
                cin>>number;
                if (typ == 0) eq_gracza.usun_przedmiot(name,number);
                else if (typ == 1) eq_gracza.usun_potke(name,number);
                }
                else if (typ == 2) eq_gracza.usun_bron(name);
            }
        } break;
        }
    }while (!czy_aktywne);
}
