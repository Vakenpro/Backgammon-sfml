#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
using namespace sf;

int size = 56;

Sprite f[30]; //figures

int board[10][12] = 
{
     1, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 1,
     1, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 1,
     1, 0, 0, 0,-1, 0,-1, 0, 0, 0, 0, 0,
     1, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,
     1, 0, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,-1,
    -1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,-1,
};
std::string toFigureNote(Vector2f p) {
    std::string s = "";
    s += char(p.x / size + 97);
    s += char(7 - p.y / size + 49);
    return s;
}

Vector2f toCoord(char a, char b) {
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return Vector2f(x * size, y * size);
}

void move(std::string str, int n) {
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);
    bool isAble = true;
    for (int i = 0; i < 30; i++) {
        if (f[i].getPosition() == newPos) {
            //f[i].setPosition(oldPos);
            isAble = false;
        }
    }
    if (isAble) {
        f[n].setPosition(newPos);
    }
    else {
        f[n].setPosition(oldPos);
    }

    /*for (int i = 0; i < 30; i++)
        if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);*/
}
void loadPosition() {
    int k = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            int n = board[i][j];
            if (!n) continue;
            int x = 0;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(size * x, size * y, size, size));
            f[k].setPosition(size * j, size * i);
            k++;
        }
    }
}

int main()
{
    RenderWindow window(VideoMode(672, 560), "Backgammon");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);
    Texture t1,t2;
    t1.loadFromFile("images/figures.png");
    t2.loadFromFile("images/board_pic1.png");

    Sprite s(t1),sBoard(t2);

    for (int i = 0; i < 30; i++) f[i].setTexture(t1);

    loadPosition();

    bool isMove = false;
    //bool isAble = false;
    float dx = 0, dy = 0;
    Vector2f oldPos, newPos;
    std::string str;
   // float oldX, oldY;
    int n = 0;
    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            ////////////drag and drop/////////////////
            if(event.type == Event::MouseButtonPressed)
                if(event.key.code == Mouse::Left)
                    for(int i=0;i<30;i++)
                    if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
                        isMove = true;
                       // isAble = true;
                        n = i;
                        dx = pos.x - f[i].getPosition().x;
                        dy = pos.y - f[i].getPosition().y;
                        oldPos = f[i].getPosition();
                        //oldY = f[i].getPosition().y;
                    }
            if (event.type == Event::MouseButtonReleased)
                if (event.key.code == Mouse::Left) {
                    isMove = false;
                    Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
                    newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
                    str = toFigureNote(oldPos)+toFigureNote(newPos);
                    move(str,n);
                    std::cout << str << std::endl;
                    //Vector2f oldPose = f[n].getPosition();
                   /* for (int i = 0; i < 30; i++) {
                        if (i != n) {
                            if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
                                isAble = false;
                            }
                        }
                    }*/
                    //if (isAble) {
                    //f[n].setPosition(newPos);
                    //}
                    /*else {
                        f[n].setPosition(oldPose);
                    }*/

                    
                }

        }
        
        if (isMove/*&& isAble*/) {f[n].setPosition(pos.x - dx, pos.y - dy); }
        //else if(isMove) { f[n].setPosition(oldX, oldY); }

        window.clear();
        window.draw(sBoard);
        for (int i = 0; i < 30; i++) window.draw(f[i]);
        window.display();
    }

    return 0;
}