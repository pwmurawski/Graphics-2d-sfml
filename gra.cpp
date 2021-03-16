#include <iostream>
#include <SFML/Graphics.hpp>
#include "gra.h"

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

void Okno::initOknoGry()
{
    okno.create(VideoMode(rozmiarX,rozmiarY,30),nazwa);
    okno.setActive(true);
    okno.setKeyRepeatEnabled(false);
    okno.setFramerateLimit(120);
    okno.setPosition(Vector2i(pozycjaX,pozycjaY));
    uruchomGreJedenGracz=false;
    uruchomGreDwochGraczy=false;
    uruchomGreDwiePilki=false;
    uruchomGreDwiePilkiDwochGraczy=false;
    uruchomWyswietl=false;
    punktyGracz1=0;
    punktyGracz2=0;
}
Okno::Okno(unsigned int RozmiarX,unsigned int RozmiarY,int PozycjaX,int PozycjaY,string Nazwa)
{
    rozmiarX=RozmiarX;
    rozmiarY=RozmiarY;
    pozycjaX=PozycjaX;
    pozycjaY=PozycjaY;
    nazwa=Nazwa;
    initOknoGry();
}
Okno::~Okno()
{

}
void Okno::petlaGlowna(Deska d1,Pilka p1,Button b1)
{
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            if(p1.pilka.getPosition().y >=600)
                okno.close();
            d1.sterowanieDeska(e,"strzalki");
            if(b1.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y) && Mouse::isButtonPressed(Mouse::Left))
                okno.close();
        }
        okno.clear(Color(0,100,150));
        d1.movementDeska();
        p1.movementPilka(d1);
        punkty(d1,p1,25,25,12.5,12.5);
        okno.draw(d1.gracz);
        okno.draw(p1.pilka);
        okno.draw(b1.button);
        okno.draw(b1.napis);
        okno.display();
    }
}
void Okno::petlaGlowna(Deska d1,Pilka p1,Pilka p2,Button b1)
{
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            if(p1.pilka.getPosition().y >=600) okno.close();
            if(p2.pilka.getPosition().y >=600) okno.close();
            d1.sterowanieDeska(e,"strzalki");
            if(b1.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y) && Mouse::isButtonPressed(Mouse::Left)) okno.close();
        }
        okno.clear(Color(0,100,150));
        d1.movementDeska();
        p1.movementPilka(d1);
        p2.movementPilka(d1);
        punkty(d1,p1,p2,25,25,12.5,12.5);
        okno.draw(d1.gracz);
        okno.draw(p1.pilka);
        okno.draw(p2.pilka);
        okno.draw(b1.button);
        okno.draw(b1.napis);
        okno.display();
    }
}
void Okno::petlaGlowna(Deska d1,Deska d2,Pilka p1,Button b1)
{
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            if(p1.pilka.getPosition().y >=600 || p1.pilka.getPosition().y <=0) okno.close();
            d1.sterowanieDeska(e,"strzalki");
            d2.sterowanieDeska(e,"wasd");
            if(b1.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y) && Mouse::isButtonPressed(Mouse::Left)) okno.close();
        }
        okno.clear(Color(0,100,150));
        d1.movementDeska();
        d2.movementDeska();
        p1.movementPilka(d1,d2);
        punkty(d1,d2,p1,25,25,12.5,12.5);
        okno.draw(d1.gracz);
        okno.draw(d2.gracz);
        okno.draw(p1.pilka);
        okno.draw(b1.button);
        okno.draw(b1.napis);
        okno.display();
    }
}
void Okno::petlaGlowna(Deska d1,Deska d2,Pilka p1,Pilka p2,Button b1)
{
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            if(p1.pilka.getPosition().y >=600 || p1.pilka.getPosition().y <=0) okno.close();
            if(p2.pilka.getPosition().y >=600 || p2.pilka.getPosition().y <=0) okno.close();
            d1.sterowanieDeska(e,"strzalki");
            d2.sterowanieDeska(e,"wasd");
            if(b1.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y) && Mouse::isButtonPressed(Mouse::Left)) okno.close();
        }
        okno.clear(Color(0,100,150));
        d1.movementDeska();
        d2.movementDeska();
        p1.movementPilka(d1,d2);
        p2.movementPilka(d1,d2);
        punkty(d1,d2,p1,p2,25,25,12.5,12.5);
        okno.draw(d1.gracz);
        okno.draw(d2.gracz);
        okno.draw(p1.pilka);
        okno.draw(p2.pilka);
        okno.draw(b1.button);
        okno.draw(b1.napis);
        okno.display();
    }
}
void Okno::menu(Button b1,Button b2,Button b3,Button b4,Button b5)
{
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            if (b1.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y)&&Mouse::isButtonPressed(Mouse::Left))
            {
                uruchomGreJedenGracz=true;
                okno.close();
            }
            if (b2.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y)&&Mouse::isButtonPressed(Mouse::Left))
            {
                uruchomGreDwochGraczy=true;
                okno.close();
            }
            if (b3.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y)&&Mouse::isButtonPressed(Mouse::Left))
            {
                uruchomGreDwiePilki=true;
                okno.close();
            }
            if (b4.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y)&&Mouse::isButtonPressed(Mouse::Left))
            {
                uruchomGreDwiePilkiDwochGraczy=true;
                okno.close();
            }
            if (b5.button.getGlobalBounds().contains(Mouse::getPosition(okno).x,Mouse::getPosition(okno).y)&&Mouse::isButtonPressed(Mouse::Left))
            {
                uruchomWyswietl=true;
                okno.close();
            }
        }
        okno.clear(Color(0,100,150));
        okno.draw(b1.button);
        okno.draw(b1.napis);
        okno.draw(b2.button);
        okno.draw(b2.napis);
        okno.draw(b3.button);
        okno.draw(b3.napis);
        okno.draw(b4.button);
        okno.draw(b4.napis);
        okno.draw(b5.button);
        okno.draw(b5.napis);
        okno.display();
    }
}
string Okno::logowanie()
{
    TextInput t1("Podaj imie: ",220);
    Event e;
    while(okno.isOpen())
    {
        while(okno.pollEvent(e))
        {
            if(e.type==Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
            {
                okno.close();
                exit(0);
            }
            t1.keyboard(e);
            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                okno.close();
                return t1.textWpisany;
            }
        }
        okno.clear(Color(0,100,150));
        okno.draw(t1.napis);
        okno.display();
    }
}
void Okno::punkty(Deska d1,Pilka p1,int x,int y,int zx,int zy)
{
    ostringstream temp;
    temp<<punktyGracz1;

    Text napis;
    Font ttf;
    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString("Punkty: "+temp.str());
    napis.setCharacterSize(15);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zx,zy);

    if(d1.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz1 +=1;

    okno.draw(napis);
}
void Okno::punkty(Deska d1,Pilka p1,Pilka p2,int x,int y,int zx,int zy)
{
    ostringstream temp;
    temp<<punktyGracz1;

    Text napis;
    Font ttf;
    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString("Punkty: "+temp.str());
    napis.setCharacterSize(15);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zx,zy);

    if(d1.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz1 +=1;
    if(d1.gracz.getGlobalBounds().intersects(p2.pilka.getGlobalBounds()))
        punktyGracz1 +=1;

    okno.draw(napis);
}
void Okno::punkty(Deska d1,Deska d2,Pilka p1,int x,int y,int zx,int zy)
{
    ostringstream temp;
    temp<<punktyGracz1;

    ostringstream temp2;
    temp2<<punktyGracz2;

    Text napis;
    Font ttf;
    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString("Punkty Gracza 1: "+temp.str()+"\n"+"Punkty Gracza 2: "+temp2.str());
    napis.setCharacterSize(15);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zx,zy);

    if(d1.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz1 +=1;
    if(d2.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz2 +=1;

    okno.draw(napis);
}
void Okno::punkty(Deska d1,Deska d2,Pilka p1,Pilka p2,int x,int y,int zx,int zy)
{
    ostringstream temp;
    temp<<punktyGracz1;

    ostringstream temp2;
    temp2<<punktyGracz2;

    Text napis;
    Font ttf;
    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString("Punkty Gracza 1: "+temp.str()+"\n"+"Punkty Gracza 2: "+temp2.str());
    napis.setCharacterSize(15);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zx,zy);

    if(d1.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz1 +=1;
    if(d1.gracz.getGlobalBounds().intersects(p2.pilka.getGlobalBounds()))
        punktyGracz1 +=1;
    if(d2.gracz.getGlobalBounds().intersects(p1.pilka.getGlobalBounds()))
        punktyGracz2 +=1;
    if(d2.gracz.getGlobalBounds().intersects(p2.pilka.getGlobalBounds()))
        punktyGracz2 +=1;

    okno.draw(napis);
}
void Okno::zapisz(MojXML xml,xml_node<> * salon)
{
    xml_node <>* node = salon->first_node();

    xml_node<> * Add = xml.utworz_wierzcholek("Gracze");
    //cout << *Add;
    xml.dodaj_atrybut(Add,(string)"Rodzaj",(string) "Deska");
    //cout << *Add;
    /// zlapanie nowego atrybutu, wiemy ze jest pierwszy
    xml_attribute<>*attr =Add->first_attribute();
    if (attr) cout <<attr->name()<<endl;
    ///zlapanie nowego atrybutu, po nazwie
    attr =Add->first_attribute("Gracze");
    if (attr) cout <<attr->name()<<endl;
    xml_node<> * Car = xml.utworz_wierzcholek("Gracz");
    xml.dodaj_atrybut(Car,(string)"id",(string) xml.id);
    xml.dodaj_atrybut(Car,(string)"imie",(string) xml.imie);
    xml.dodaj_atrybut(Car,(string)"Punkty",(string) xml.iloscPunktow);

    Add->append_node(Car);
    salon->append_node(Add);
    cout<< "Dodano Gracza."<<endl;
    xml.Zapisz_do_pliku((char*)"xml",(char*)".xml");
}
void Deska::initDeska()
{
    gracz.setSize(Vector2f(dlugosc,szerokosc));
    gracz.setFillColor(kolor);
    gracz.setOrigin(zx,zy);
    gracz.setPosition(x,y);
}
Deska::Deska(float Dlugosc,float Szerokosc,int X,int Y,int ZX,int ZY,float Szybkosc,Color Kolor)
{
    dlugosc=Dlugosc;
    szerokosc=Szerokosc;
    x=X;
    y=Y;
    zx=ZX;
    zy=ZY;
    szybkosc=Szybkosc;
    kolor=Kolor;
    initDeska();
}
Deska::~Deska()
{

}
void Deska::sterowanieDeska(Event z,string sterowanie)
{
    if(sterowanie == "wasd")
    {
        if(z.type==Event::KeyPressed&&z.key.code==Keyboard::A) vectorRuch = Vector2f(-szybkosc,0);
        if(z.type==Event::KeyPressed&&z.key.code==Keyboard::D) vectorRuch = Vector2f(szybkosc,0);
        if(z.type==Event::KeyReleased&&(z.key.code==Keyboard::A || z.key.code==Keyboard::D)) vectorRuch = Vector2f(0,0);
    }
    if(sterowanie == "strzalki")
    {
        if(z.type==Event::KeyPressed&&z.key.code==Keyboard::Left) vectorRuch = Vector2f(-szybkosc,0);
        if(z.type==Event::KeyPressed&&z.key.code==Keyboard::Right) vectorRuch = Vector2f(szybkosc,0);
        if(z.type==Event::KeyReleased&&(z.key.code==Keyboard::Left || z.key.code==Keyboard::Right)) vectorRuch = Vector2f(0,0);
    }
}
void Deska::movementDeska()
{
    gracz.move(vectorRuch);
    if(gracz.getPosition().x <=40 || gracz.getPosition().x >=460)
        vectorRuch = Vector2f(0,0);
}
void Pilka::initPilka()
{
    pilka.setRadius(promien);
    pilka.setPointCount(30);
    pilka.setFillColor(kolor);
    pilka.setOrigin(zx,zy);
    pilka.setPosition(x,y);
}
Pilka::Pilka(float Promien,int X,int Y,int ZX,int ZY,float SpeedX,float SpeedY,Color Kolor)
{
    promien=Promien;
    x=X;
    y=Y;
    zx=ZX;
    zy=ZY;
    speedX=SpeedX;
    speedY=SpeedY;
    kolor=Kolor;
    initPilka();
}
Pilka::~Pilka()
{

}
void Pilka::movementPilka(Deska a)
{
    pilka.move(-speedX,speedY);
    if(pilka.getPosition().x >= 500 || pilka.getPosition().x <=0)
        speedX = -speedX;
    if(pilka.getPosition().y <=0)
        speedY = -speedY;
    if(a.gracz.getGlobalBounds().intersects(this->pilka.getGlobalBounds()))
        speedY = -speedY;
}
void Pilka::movementPilka(Deska a,Deska b)
{
    pilka.move(-speedX,speedY);
    if(pilka.getPosition().x >= 500 || pilka.getPosition().x <=0)
        speedX = -speedX;
    if(a.gracz.getGlobalBounds().intersects(this->pilka.getGlobalBounds()))
        speedY = -speedY;
    if(b.gracz.getGlobalBounds().intersects(this->pilka.getGlobalBounds()))
        speedY = -speedY;
}
void Button::initButton()
{
    button.setSize(Vector2f(dlugosc,szerokosc));
    button.setFillColor(kolor);
    button.setOrigin(zx,zy);
    button.setPosition(x,y);

    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString(text);
    napis.setCharacterSize(rozmiarText);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zxText,zyText);
}
Button::Button(int X,int Y,string Text,int RozmiarText,int ZxText,int ZyText,Color Kolor,float Szerokosc,float Dlugosc,int ZX,int ZY)
{
    szerokosc=Szerokosc;
    dlugosc=Dlugosc;
    x=X;
    y=Y;
    zx=ZX;
    zy=ZY;
    kolor=Kolor;
    text=Text;
    rozmiarText=RozmiarText;
    zxText=ZxText;
    zyText=ZyText;
    initButton();
}
Button::~Button()
{

}
void TextInput::initText()
{
    ttf.loadFromFile("gunplay.ttf");
    napis.setFont(ttf);
    napis.setString(text);
    napis.setCharacterSize(rozmiarText);
    napis.setFillColor(Color(0,0,0));
    napis.setPosition(x,y);
    napis.setOrigin(zxText,zyText);
}
TextInput::TextInput(string Text,int X,int Y,int RozmiarText,int ZxText,int ZyText,Color Kolor)
{
    text=Text;
    textF=Text;
    x=X;
    y=Y;
    rozmiarText=RozmiarText;
    zxText=ZxText;
    zyText=ZyText;
    kolor=Kolor;
    initText();
}
TextInput::~TextInput()
{

}
void TextInput::keyboard(Event e)
{
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::Q)
    {
        text += "Q";
        textWpisany += "Q";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::W)
    {
        text += "W";
        textWpisany += "W";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::E)
    {
        text += "E";
        textWpisany += "E";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::R)
    {
        text += "R";
        textWpisany += "R";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::T)
    {
        text += "T";
        textWpisany += "T";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::Y)
    {
        text += "Y";
        textWpisany += "Y";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::U)
    {
        text += "U";
        textWpisany += "U";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::I)
    {
        text += "I";
        textWpisany += "I";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::O)
    {
        text += "O";
        textWpisany += "O";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::P)
    {
        text += "P";
        textWpisany += "P";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::A)
    {
        text += "A";
        textWpisany += "A";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::S)
    {
        text += "S";
        textWpisany += "S";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::D)
    {
        text += "D";
        textWpisany += "D";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::F)
    {
        text += "F";
        textWpisany += "F";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::G)
    {
        text += "G";
        textWpisany += "G";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::H)
    {
        text += "H";
        textWpisany += "H";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::J)
    {
        text += "J";
        textWpisany += "J";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::K)
    {
        text += "K";
        textWpisany += "K";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::L)
    {
        text += "L";
        textWpisany += "L";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::Z)
    {
        text += "Z";
        textWpisany += "Z";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::X)
    {
        text += "X";
        textWpisany += "X";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::C)
    {
        text += "C";
        textWpisany += "C";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::V)
    {
        text += "V";
        textWpisany += "V";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::B)
    {
        text += "B";
        textWpisany += "B";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::N)
    {
        text += "N";
        textWpisany += "N";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::M)
    {
        text += "M";
        textWpisany += "M";
        napis.setString(text);
    }
    if(e.type==Event::KeyPressed&&e.key.code== Keyboard::BackSpace)
    {
        text = textF;
        textWpisany = "";
        napis.setString(text);
    }
}
