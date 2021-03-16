#include <iostream>
#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include <vector>
#include <cstdlib>
using namespace rapidxml;


using namespace std;
using namespace sf;

class Deska;
class Pilka;
class Button;
class TextInput;
class MojXML;

class Okno
{
    RenderWindow okno;
    unsigned int rozmiarX, rozmiarY;
    int pozycjaX, pozycjaY;
    string nazwa;

    void initOknoGry();
public:
    int punktyGracz1, punktyGracz2;
    bool uruchomGreJedenGracz;
    bool uruchomGreDwochGraczy;
    bool uruchomGreDwiePilki;
    bool uruchomGreDwiePilkiDwochGraczy;
    bool uruchomWyswietl;

    Okno(unsigned int=500,unsigned int=600,int=600,int=100,string="Gra");
    ~Okno();
    void petlaGlowna(Deska,Pilka,Button);
    void petlaGlowna(Deska,Pilka,Pilka,Button);
    void petlaGlowna(Deska,Deska,Pilka,Button);
    void petlaGlowna(Deska,Deska,Pilka,Pilka,Button);
    void menu(Button,Button,Button,Button,Button);
    string logowanie();
    void punkty(Deska,Pilka,int,int,int,int);
    void punkty(Deska,Pilka,Pilka,int,int,int,int);
    void punkty(Deska,Deska,Pilka,int,int,int,int);
    void punkty(Deska,Deska,Pilka,Pilka,int,int,int,int);
    void zapisz(MojXML,xml_node<> *);
};
class Deska
{
    float dlugosc;
    float szerokosc;
    int x, y;
    int zx, zy;
    float szybkosc;
    Color kolor;
    Vector2f vectorRuch;

    void initDeska();
public:
    RectangleShape gracz;

    Deska(float=80.f,float=5.f,int=250,int=550,int=40,int=2.5,float=5.f,Color=Color(0,255,0));
    ~Deska();
    void sterowanieDeska(Event,string);
    void movementDeska();
};
class Pilka
{
    float promien;
    int x, y;
    int zx, zy;
    Color kolor;
    float speedX, speedY;

    void initPilka();
public:
    CircleShape pilka;

    Pilka(float=8.f,int=250,int=300,int=8,int=8,float=5.f,float=2.f,Color=Color(255,0,0));
    ~Pilka();
    void movementPilka(Deska);
    void movementPilka(Deska,Deska);
};
class Button
{
    float dlugosc;
    float szerokosc;
    int x, y;
    int zx, zy;
    Color kolor;
    int rozmiarText;
    int zxText, zyText;
    string text;
    Font ttf;

    void initButton();
public:
    RectangleShape button;
    Text napis;

    Button(int=250,int=300,string="Button",int=25,int=60,int=15,Color=Color(0,255,0),float=50.f,float=200.f,int=100,int=25);
    ~Button();
};
class TextInput
{
    Font ttf;
    string text ,textF;
    Color kolor;
    int rozmiarText;
    int x, y;
    int zxText, zyText;

    void initText();
public:
    Text napis;
    string textWpisany;

    TextInput(string="Podaj imie: ",int=250,int=300,int=25,int=60,int=15,Color=Color(0,0,0));
    ~TextInput();
    void keyboard(Event);
};
class MojXML
{
public :
    string imie;
    string iloscPunktow;
    string id;
    xml_document<> * XML;
    vector<char> * XMLvect;
    MojXML(char * nazwa,char * rozszezenie)
    {
       XML = new xml_document<>();
       if (!pobierz(XML,nazwa,rozszezenie,&XMLvect))
            {cout << "cos poszlo nie tak" << nazwa<< ".xml";exit(1);}

        srand(time(NULL));
        int i = rand();
        ostringstream temp;
        temp<<i;
        id=temp.str();

    }
    ~MojXML()
    {
        XML->clear();
        delete XML;
        delete XMLvect;
    }
    xml_node <>* utworz_wierzcholek(string name)
      {
          char *Name = XML->allocate_string(name.c_str());
          return XML->allocate_node( node_element,Name);
      }
    void dodaj_atrybut(xml_node<>* W,string attr, string value)
      {
          char *Attr = XML->allocate_string(attr.c_str());
          char *Value = XML->allocate_string(value.c_str());
          W->append_attribute(XML->allocate_attribute(Attr,Value));
      }
    void Zapisz_do_pliku(char * nazwa,char * rozszezenie)
    {
        string nazwa_doc = string(nazwa) + string(rozszezenie);
        char *cstr = new char[nazwa_doc.length() + 1];
        strcpy(cstr, nazwa_doc.c_str());
        ofstream File;
        File.open(cstr);
        File << *XML;
        File.flush();
        File.close();
        delete cstr;
    }
    void drukuj()
    {
        xml_node<>* temp = XML->first_node();
      if (!temp) {cout << 1;exit(1);}
       temp = temp->first_node();
       while (temp)
         {
           cout << * temp;
           temp = temp->next_sibling();
         }
    }
    string IntToString (int a)
{
    ostringstream temp;
    temp<<a;
    return temp.str();
}

bool pobierz(xml_document <> *doc,char * Nazwa, char * rozszezenie,vector<char> ** buffer)
{
    string nazwa_doc = string(Nazwa) + string(rozszezenie);
    char *cstr = new char[nazwa_doc.length() + 1];
    strcpy(cstr, nazwa_doc.c_str());

    ifstream XmlF (cstr);
    if (!XmlF.good()){cout << "file no exists"; exit(1);}
	vector<char> *B =new vector<char>((istreambuf_iterator<char>(XmlF)), istreambuf_iterator<char>());
	B->push_back('\0');
	try{
	  doc->parse<0>(&(*B)[0]);
	}
     catch( parse_error p )
    {
        cout <<"|" <<p.what()<<"|";
        cout << p.where<char>();
        exit(1);
        return false;
    }
    (*buffer) = B;
    delete cstr;
    return true;
}
void WyswietlAtrybuty(xml_node <> * N )
{
    //cout << "<" << N->name() <<">";

    for( xml_attribute <>* atrybut = N->first_attribute(); atrybut; atrybut = atrybut->next_attribute() )
    {

        if(imie == atrybut->value() || iloscPunktow == atrybut->value())
        {
            cout << "<" << N->name() <<">";
            for( xml_attribute <>* atrybut = N->first_attribute(); atrybut; atrybut = atrybut->next_attribute() ) // (7)
            {
                string name (atrybut->name(),atrybut->name_size());
                string value (atrybut->value(),atrybut->value_size());
                cout << "|" << name << "=" << value << "| ";
            }
        }
    }
}
/*
void WyswietlAtrybuty(xml_node <> * N )
{
    cout << "<" << N->name() <<">";
    for( xml_attribute <>* atrybut = N->first_attribute(); atrybut; atrybut = atrybut->next_attribute() ) // (7)
    {
        string name (atrybut->name(),atrybut->name_size());
        string value (atrybut->value(),atrybut->value_size());
        cout << "|" << name << "=" << value << "| ";
    }
}
*/
void WyswietlPotomkow(xml_node <> * N)
{
    for( xml_node <>* node = N->first_node(); node; node = node->next_sibling() ) // (7)
    {
        //cout << "<" << node->name() <<" ";
        WyswietlAtrybuty(node);

        //cout << ">" << endl;
    }
}
void DrukujAll(xml_node <> * N)
    {
        for( xml_node <>* node = N->first_node(); node; node = node->next_sibling() )
        {
            cout << "<" << node->name() <<">";
            for( xml_attribute <>* atrybut = node->first_attribute(); atrybut; atrybut = atrybut->next_attribute() )
            {
                string name (atrybut->name(),atrybut->name_size());
                string value (atrybut->value(),atrybut->value_size());
                cout << "|" << name << "=" << value << "| ";
            }
        }
    }
};
