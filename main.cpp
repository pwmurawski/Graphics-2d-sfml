#include <iostream>
#include <SFML/Graphics.hpp>
#include "gra.h"

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow W;

    W.create(VideoMode(1200,700,32),"Okno");
    W.setActive(true);
    W.setKeyRepeatEnabled(false);
    W.setPosition(Vector2i(250,150));

    RectangleShape niebo(Vector2f(1200,300));
    niebo.setFillColor(Color(60,60,255));
    niebo.setOrigin(0,0);
    niebo.setPosition(0,0);

    CircleShape slonce(80,100);
    slonce.setPosition(1000,20);
    slonce.setFillColor(Color(255,255,0));

    RectangleShape R(Vector2f(300,200));
    R.setFillColor(Color(255,255,100));
    R.setOrigin(0,0);
    R.setPosition(200,350);

    RectangleShape door(Vector2f(30,55));
    door.setFillColor(Color(150,80,0));
    door.setOrigin(0,0);
    door.setPosition(250,495);

    RectangleShape okno(Vector2f(55,55));
    okno.setFillColor(Color(0,80,255));
    okno.setOrigin(0,0);
    okno.setPosition(250,400);

    RectangleShape okno2(Vector2f(55,55));
    okno2.setFillColor(Color(0,80,255));
    okno2.setOrigin(0,0);
    okno2.setPosition(400,400);

    CircleShape dach(180,3);
    dach.setPosition(170,80);
    dach.setFillColor(Color(100,50,0));

    CircleShape glowa(40,100);
    glowa.setPosition(800,250);
    glowa.setFillColor(Color(255,203,152));

    CircleShape oko(7,100);
    oko.setPosition(815,275);
    oko.setFillColor(Color(0,0,0));

    CircleShape oko2(7,100);
    oko2.setPosition(850,275);
    oko2.setFillColor(Color(0,0,0));

    RectangleShape usta(Vector2f(25,2));
    usta.setFillColor(Color(255,0,0));
    usta.setOrigin(0,0);
    usta.setPosition(825,305);

    RectangleShape cialo(Vector2f(100,150));
    cialo.setFillColor(Color(255,0,0));
    cialo.setOrigin(0,0);
    cialo.setPosition(790,330);

    RectangleShape noga(Vector2f(40,100));
    noga.setFillColor(Color(0,0,250));
    noga.setOrigin(0,0);
    noga.setPosition(790,480);

    RectangleShape noga2(Vector2f(40,100));
    noga2.setFillColor(Color(0,0,250));
    noga2.setOrigin(0,0);
    noga2.setPosition(850,480);

    RectangleShape reka(Vector2f(40,100));
    reka.setFillColor(Color(180,0,0));
    reka.setOrigin(0,0);
    reka.setPosition(755,330);

    RectangleShape reka2(Vector2f(40,100));
    reka2.setFillColor(Color(180,0,0));
    reka2.setOrigin(0,0);
    reka2.setPosition(885,330);

    Event e;

    while(W.isOpen())
    {
        while(W.pollEvent(e))
        {
            if(e.type == Event::Closed) W.close();
        }

        W.clear(Color(50,110,50));
        W.draw(R);
        W.draw(niebo);
        W.draw(door);
        W.draw(dach);
        W.draw(slonce);
        W.draw(okno);
        W.draw(okno2);
        W.draw(glowa);
        W.draw(oko);
        W.draw(oko2);
        W.draw(usta);
        W.draw(cialo);
        W.draw(noga);
        W.draw(noga2);
        W.draw(reka);
        W.draw(reka2);
        W.display();
    }
    return 0;
}
