#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <sstream>
using namespace sf;
int size = 56;

Sprite f[30]; //figures
Sprite posibleMoves[3];//posibleMoves
Sprite dice[6]; //dice with dots
Sprite dice2[6]; //dice with dots
Sprite deleteButton;

bool winCondition(int arr[10][12] , int* whiteCount, int* blackCount) {
    int whiteCount2 = 0, blackCount2 = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            if (arr[i][j] > 0) {
                whiteCount2++;
            }
            if (arr[i][j] < 0) {
                blackCount2++;
            }
        }
    }

    (*whiteCount) = whiteCount2;
    (*blackCount) = blackCount2;
    if ((*whiteCount) == 0) {
       // std::cout << "white wins";
        return true;
    }
    else if ((*blackCount) == 0) {
       // std::cout << "black wins";
        return true;
    }
    return false;
}

int findMoves(int arr[10][12], Vector2f oldPos, Vector2f newPos) {
    int moves = 0;
    if (oldPos.y / size < 5) {
        moves =  oldPos.x / size;
        moves += 1;
        moves +=  newPos.x / size;
    }
    else {
        moves = 11-oldPos.x / size;
        moves += 1;
        moves += 11-newPos.x / size;
    }
    return moves;
}

void random(int* arr[]) {
    for (int k = 0; k < 2;k++) {
        int num = 1 + rand() % 6; 
            (*arr)[k] = num;
    }
    
}

void findPosibles(int arr[10][12], int* xPose, int* yPose, int diceRoll) {
    //std::cout << "pose/size is" << (*xPose) / size<<std::endl;
    //std::cout << "yPose/size is" << (*yPose) / size << std::endl;
    if (diceRoll > 0) {
        int oldX = (*xPose), oldY = (*yPose);
        ///////////////top coords/////////////////////////
        if ((*xPose) / size - diceRoll >= 0 && (*yPose) / size < 5) {
            (*xPose) -= diceRoll * size;
            int i = 0;
            for (; i < 5; i++) {
                if (arr[i][(*xPose) / size] == 0) {
                    (*yPose) = i * size;//test
                    break;
                }
                if (arr[i][(*xPose) / size] * arr[oldY / size][oldX / size] < 0) {
                    (*xPose) = -100;
                    (*yPose) = -100;
                    // std::cout << "this place is incorrect";
                    break;
                }
            }
            if (i == 5) {
                (*xPose) = -100;
                (*yPose) = -100;
                //std::cout << "this place is incorrect";
            }
        }

        ////////////////////bottom coords////////////////////////
        else if ((*xPose) / size + diceRoll <= 11 && (*yPose) / size >= 5) {
            (*xPose) += diceRoll * size;
            int i = 9;
            for (; i >= 5; i--) {
                if (arr[i][(*xPose) / size] == 0) {
                    (*yPose) = i * size;//test
                    break;
                }
                if (arr[i][(*xPose) / size] * arr[oldY / size][oldX / size] < 0) {
                    (*xPose) = -100;
                    (*yPose) = -100;
                    //std::cout << "this place is incorrect";
                    break;
                }
            }
            if (i == 4) {
                (*xPose) = -100;
                (*yPose) = -100;
                // std::cout << "this place is incorrect";
            }
        }

        //////////////////top to bottom coords////////////////////
        else if ((*xPose) / size - diceRoll < 0 && (*yPose) / size < 5) {
            (*xPose) = (abs((*xPose) - diceRoll * size) - 1 * size);
            int i = 9;
            for (; i >= 5; i--) {
                if (arr[i][(*xPose) / size] == 0) {
                    (*yPose) = i * size;//test
                    break;
                }
                if (arr[i][(*xPose) / size] * arr[oldY / size][oldX / size] < 0) {
                    (*xPose) = -100;
                    (*yPose) = -100;
                    //  std::cout << "this place is incorrect";
                    break;
                }
            }
            if (i == 4) {
                (*xPose) = -100;
                (*yPose) = -100;
                // std::cout << "this place is incorrect";
            }
            //(*yPose) = 8 * size;
        }

        ////////////////bottom to top////////////////////////
        else if ((*xPose) / size + diceRoll > 11 && (*yPose) / size >= 5) {
            for (; (*xPose) / size < 11; (*xPose) += size) {
                diceRoll--;
            }
            for (; diceRoll != 1; (*xPose) -= size) {
                diceRoll--;
            }
            int i = 0;
            for (; i < 5; i++) {
                if (arr[i][(*xPose) / size] == 0) {
                    (*yPose) = i * size;//test
                    break;
                }

                if (arr[i][(*xPose) / size] * arr[oldY / size][oldX / size] < 0) {
                    (*xPose) = -100;
                    (*yPose) = -100;
                    // std::cout << "this place is incorrect";
                    break;
                }
            }
            if (i == 5) {
                (*xPose) = -100;
                (*yPose) = -100;
                // std::cout << "this place is incorrect";
            }
            //(*yPose) = 2 * size;
        }

        ////////////////////fix/////////////////////////
    }
}

/*void findPosible(int arr[10][12], int* xPose, int* yPose) {
    if ((*yPose)/size < 5&&(*xPose)/size!=0) {
        for (int i = (*xPose) / size; i > -1; i--) {
            if (arr[0][i] == 0) {
                (*xPose) = i * size;
                (*yPose) = 0;
                break;
            }

        }
    }
    else if((*xPose)!=11*size) {
        for (int i = (*xPose) / size; i < 12; i++) {
            if (arr[9][i] == 0) {
                (*xPose) = i * size;
                    (*yPose) = 9 * size;
                break;
            }

        }
    }
    else {
        for (int i = (*xPose) / size; i > -1; i--) {
            if (arr[0][i] == 0) {
                (*xPose) = i * size;
                (*yPose) = 0;
                break;
            }

        }
    }
}*/

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

bool move(std::string str, int n, int* moves, int arr[10][12]) {
    Vector2f oldPos = toCoord(str[0], str[1]);
    Vector2f newPos = toCoord(str[2], str[3]);
    bool isAble = true;
    for (int i = 0; i < 30; i++) {
        if (f[i].getPosition() == newPos) {
            f[n].setPosition(oldPos);
            isAble = false;
        }
    }
    int actions = 0;
    for (int j = 0; j < 3; j++) {
        //std::cout << "x:" << posibleMoves[j].getPosition().x<<"and"<< f[n].getPosition().x;
        if (newPos==posibleMoves[j].getPosition()) {
            f[n].setPosition(newPos);
            actions++;
            if ((oldPos.y/size < 5 && newPos.y/size >= 5) || (newPos.y/size < 5 && oldPos.y/size >= 5)) {
                (*moves) -= findMoves(arr, oldPos, newPos);
            }
            else {
                (*moves) -= abs(newPos.x - oldPos.x) / size;
                if (abs(newPos.y - oldPos.y) / size >= 5) {
                    (*moves) -= 1;
                }
            }

            
            //std::cout << "moves" << (*moves);
            //std::cout << "CORRECT PLACE";
            return true;
        }
    }
    if (!isAble||actions==0) {
        f[n].setPosition(oldPos);
        return false;
    }

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
    ////////////////////////////////////Инициализация Строк/////////////////////////////
    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text deleteText("", font, 24);
    Text colorText("",font,24);
    Text whiteCountText("", font, 24);
    Text blackCountText("", font, 24);
    deleteText.setStyle(Text::Bold);
    colorText.setStyle(Text::Bold);
    whiteCountText.setStyle(Text::Bold);
    blackCountText.setStyle(Text::Bold);
    //////////////////////////////////////////////////////////////////////////////////

    int whiteCount = 15, blackCount = 15;
    srand(time(NULL));
    RenderWindow window(VideoMode(820, 560), "Backgammon");

    ///////////////////////////////Инициализация Текстур////////////////////////////////
    Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("images/figures.png");
    t2.loadFromFile("images/board_pic1.png");
    t3.loadFromFile("images/figures.png");
    t4.loadFromFile("images/dice.png");
    t5.loadFromFile("images/delete.png");
    deleteButton.setTexture(t5);
    deleteButton.setTextureRect(IntRect(0,0,size,size));
    deleteButton.setPosition(673,2*size);
    deleteButton.setColor(Color::Red);
    ////////////////////////////////////////////////////////////////////////////////////

    int checkMassive[10][12] ;
    bool isTurn = true;
    bool isOld = false;
    int color = 1;
    bool isColor = false;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            checkMassive[i][j] = board[i][j];
        }
    }

    //////////////////dice 1////////////////////////
    for (int i = 0; i < 6; i++) {
        dice[i].setTexture(t4);
        if (i < 4) {
            dice[i].setTextureRect(IntRect(size * i, size * 1,size,size));
        }
        else if (i == 4) {
            dice[i].setTextureRect(IntRect(size * 1, size * 0, size, size));
        }
        else {

            dice[i].setTextureRect(IntRect(size * 1, size * 2, size, size));
        }
        dice[i].setPosition(673, size * i);
        dice[i].setPosition(-100, -100);
    }
    //////////////////end dice 1////////////////////

    /////////////////dice2/////////////////////////
    for (int i = 0; i < 6; i++) {
        dice2[i].setTexture(t4);
        if (i < 4) {
            dice2[i].setTextureRect(IntRect(size * i, size * 1, size, size));
        }
        else if (i == 4) {
            dice2[i].setTextureRect(IntRect(size * 1, size * 0, size, size));
        }
        else {

            dice2[i].setTextureRect(IntRect(size * 1, size * 2, size, size));
        }
        dice2[i].setPosition(673, size * i);
        dice2[i].setPosition(-100, -100);
    }
    //////////////end dice 2 ////////////////////////

    Sprite sBoard(t2);    
    /////////////figure texture ////////////////////
    for (int i = 0; i < 30; i++) {
        f[i].setTexture(t1); 
    }
    ///////////figure posible move texture/////////
    for (int i = 0; i < 3; i++) {
        posibleMoves[i].setTexture(t1);
        posibleMoves[i].setTextureRect(IntRect(size *0, size * 0, size, size));
        posibleMoves[i].setPosition(-100,-100);
        posibleMoves[i].setColor(Color::Red);
    }
    loadPosition();
    ///////////end figure texture////////////////

    bool isMove = false , isDelete = false;
    float dx = 0, dy = 0;
    int x=0;
    int y=0;
    Vector2f firstClick;
    Vector2f oldPos, newPos;
    std::string str;
    int n = 0;
    int moves = 0;
    int* diceRoll = (int*)malloc(sizeof(int)*2);
    int deleteRoll;
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
                if(event.key.code == Mouse::Left){
                    if (deleteButton.getGlobalBounds().contains(pos.x, pos.y)) {
                        if (deleteButton.getColor() == Color::White) {
                            f[n].setPosition(-100, -100);
                            isDelete = true;
                            moves -= deleteRoll;
                            for (int i = 0; i < 2; i++) {
                                if (diceRoll[i] == deleteRoll) {
                                    diceRoll[i] = -1;
                                }
                            }
                            if (diceRoll[0] + diceRoll[1] == deleteRoll && diceRoll[0] != -1&& diceRoll[1] != -1) {
                                diceRoll[0] = -1;
                                diceRoll[1] = -1;
                            }
                            deleteButton.setColor(Color::Red);
                            checkMassive[int(oldPos.y) / size][int(oldPos.x) / size] = 0;
                        }
                        else {
                            isDelete = false;
                        }
                    }
                    else {
                        isDelete = false;
                        for (int i = 0; i < 30; i++) {

                            int xPose = f[i].getPosition().x / size;
                            int yPose = f[i].getPosition().y / size;
                            // std::cout << "this elem is" << checkMassive[yPose][xPose];


                            if (f[i].getGlobalBounds().contains(pos.x, pos.y) && checkMassive[yPose][xPose] * color >= 1) {
                               // std::cout << "here";
                                isMove = true;
                                isColor = true;
                                n = i;
                                dx = pos.x - f[i].getPosition().x;
                                dy = pos.y - f[i].getPosition().y;
                                oldPos = f[i].getPosition();
                                x = oldPos.x;
                                y = oldPos.y;
                                if (firstClick == oldPos) {
                                    isOld = true;
                                }
                                else {
                                    isOld = false;
                                    deleteButton.setColor(Color::Red);
                                }
                            }

                        }

                        if (isColor) {
                            if (!isOld) {
                                firstClick = Vector2f(pos);
                                isOld = false;
                            }
                            else {
                                isOld = true;
                            }
                            if (isTurn) {
                                diceRoll[0] = -1;
                                diceRoll[1] = -1;
                            }


                            ///////////////////here we start work with dices//////////////
                            if (isTurn) {
                                //generating dices rolls and hide every dices//
                                random(&diceRoll);
                                for (int l = 0; l < 6; l++) {
                                    dice[l].setPosition(-100, -100);
                                    dice2[l].setPosition(-100, -100);
                                }
                                ////////////////////////////////////////////////

                                ////////////////////here we roll dices and set their position on window////////
                                int firstRoll = diceRoll[0] - 1;

                                int secondRoll = diceRoll[1] - 1;
                                moves = firstRoll + secondRoll + 2;
                                dice[firstRoll].setPosition(673, size * 0);
                                dice2[secondRoll].setPosition(673, size * 1);

                                ///////////////////////////////////////////////////////////////////////////////

                                /////////here we find posible turns and show them/////////////////////////////
                                //findPosible(checkMassive, &x, &y);
                                for (int l = 0; l < 3; l++) {
                                    //std::cout << "diceRoll[l]= " << diceRoll[l] << " ";
                                    if (diceRoll[l] > 0 || l == 2) {
                                        int x1 = f[n].getPosition().x;
                                        int y1 = f[n].getPosition().y;
                                        if (abs(checkMassive[int(oldPos.y) / size][int(oldPos.x) / size]) >= 13 && diceRoll[l] == oldPos.x / size + 1) {
                                            //std::cout << "delete it now" << "";
                                            deleteButton.setColor(Color::White);
                                            deleteRoll = diceRoll[l];
                                        }
                                        else if (abs(checkMassive[int(oldPos.y) / size][int(oldPos.x) / size]) >= 13 && diceRoll[1] + diceRoll[0] == oldPos.x / size + 1) {
                                            //std::cout << "delete it now" << "";
                                            deleteButton.setColor(Color::White);
                                            deleteRoll = diceRoll[1] + diceRoll[0];

                                        }
                                        if (l != 2) {
                                            findPosibles(checkMassive, &x1, &y1, diceRoll[l]);
                                        }
                                        else {
                                            int sum = 0;
                                            if (diceRoll[0] > 0) {
                                                sum += diceRoll[0];

                                            }
                                            if (diceRoll[1] > 0) {
                                                sum += diceRoll[1];

                                            }
                                            findPosibles(checkMassive, &x1, &y1, sum);
                                        }
                                        posibleMoves[l].setPosition(x1, y1);
                                    }
                                }
                            }
                            ////////////////////////////////////////////////////////////////////////////////////

                            /////////////////////////if player diceded to make move with different figure//////////////////
                            if (!isOld) {
                                //findPosible(checkMassive, &x, &y);
                                for (int l = 0; l < 3; l++) {
                                   // std::cout << "diceRoll[l]= " << diceRoll[l] << " ";
                                    if (diceRoll[l] > 0 || l == 2) {
                                        int x1 = f[n].getPosition().x;
                                        int y1 = f[n].getPosition().y;
                                        if (abs(checkMassive[int(oldPos.y) / size][int(oldPos.x) / size]) >= 13 && diceRoll[l] == oldPos.x / size + 1) {
                                            //std::cout << "delete it now" << "";
                                            deleteButton.setColor(Color::White);
                                            deleteRoll = diceRoll[l];
                                        }
                                        else if (abs(checkMassive[int(oldPos.y) / size][int(oldPos.x) / size]) >= 13 && diceRoll[1] + diceRoll[0] == oldPos.x / size + 1) {
                                           // std::cout << "delete it now" << "";
                                            deleteButton.setColor(Color::White);
                                            deleteRoll = diceRoll[1] + diceRoll[0];

                                        }

                                        if (l != 2) {
                                            findPosibles(checkMassive, &x1, &y1, diceRoll[l]);
                                        }
                                        else {
                                            int sum = 0;
                                            if (diceRoll[0] > 0) {
                                                sum += diceRoll[0];

                                            }
                                            if (diceRoll[1] > 0) {
                                                sum += diceRoll[1];

                                            }
                                            findPosibles(checkMassive, &x1, &y1, sum);
                                        }
                                        posibleMoves[l].setPosition(x1, y1);
                                    }
                                }
                            }
                            //////////////////////////////////////////////////////////////////////////////////////////////
                        }
                    }
                    }
            if (event.type == Event::MouseButtonReleased)
                if (event.key.code == Mouse::Left) {
                    if (isColor&&!isDelete) {
                        isMove = false;
                        Vector2f p = f[n].getPosition() + Vector2f(size / 2, size / 2);
                        newPos = Vector2f(size * int(p.x / size), size * int(p.y / size));
                        str = toFigureNote(oldPos) + toFigureNote(newPos);
                        isTurn = move(str, n,&moves,checkMassive);
                        if (moves != 0&&isTurn) {
                            int nowMoves;

                            if ((oldPos.y/size < 5 && newPos.y/size >= 5) || (newPos.y/size < 5 && oldPos.y/size >= 5)) {
                                nowMoves = findMoves(checkMassive, oldPos, newPos);
                            }
                            else {
                                

                                nowMoves = abs(newPos.x - oldPos.x) / size;
                                if (abs(newPos.y - oldPos.y) / size >= 5) {
                                    nowMoves += 1;
                                }
                            }

                            //std::cout << "moves is" << moves << std::endl;
                            for (int i = 0; i < 2; i++) {
                                if (diceRoll[i] == nowMoves) {
                                   // std::cout << "fix moves";
                                    diceRoll[i] = -1;
                                    break;
                                }
                            }
                            if (nowMoves == diceRoll[0] + diceRoll[1]&&diceRoll[0]!=-1&&diceRoll[1]!=-1) {
                                diceRoll[0] = -1;
                                diceRoll[1] = -1;
                            }
                        }
                        ////////////////check if there are posible turn///////////////////////
                        int err = 0;
                        for (int i = 0; i < 3; i++) {
                            if (posibleMoves[i].getPosition().x == -100 && posibleMoves[i].getPosition().y == -100) {
                                err++;
                            }
                        }
                        //////////////////////////////////////////////////////////////////////
                        if (isTurn) {
                            //std::cout<<std::endl;
                            std::swap(checkMassive[int(newPos.y) / size][int(newPos.x) / size], checkMassive[int(oldPos.y) / size][int(oldPos.x) / size]);
                            if (checkMassive[int(newPos.y) / size][int(newPos.x) / size] > 0) {
                                checkMassive[int(newPos.y) / size][int(newPos.x) / size] += abs(int(newPos.x) / size - oldPos.x / size)+1;
                            }
                            else {
                                checkMassive[int(newPos.y) / size][int(newPos.x) / size] -= abs(int(newPos.x) / size - oldPos.x / size)+1;
                            }
                             /* for (int i = 0; i < 10; i++) {
                                  for (int j = 0; j < 12; j++) {
                                      std::cout<<checkMassive[i][j]<<" " ;
                                  }
                                  std::cout<<std::endl;
                              }
                            std::cout << str << std::endl;*/
                                for (int i = 0; i < 3; i++) {
                                    posibleMoves[i].setPosition(-100, -100);
                                }
                                if (moves != 0) {
                                    isTurn = false;
                                }
                                else{
                                    color *= -1;

                                }
                                isColor = false;
                        }
                        /*if (err == 3) {
                            isTurn = true;
                        }*/
                    }
                    if (winCondition(checkMassive, &whiteCount, &blackCount)) {
                        break;
                    }
                    
                }
        }
        
        if (isMove) {f[n].setPosition(pos.x - dx, pos.y - dy); }

        window.clear();
        window.draw(sBoard);
        std::ostringstream whiteCountString;
        whiteCountString << whiteCount;
        std::ostringstream blackCountString;
        blackCountString << blackCount;
        whiteCountText.setString("Белых:"+ whiteCountString.str());
        blackCountText.setString("Черных:" + blackCountString.str());
        whiteCountText.setPosition(673, 3 * size + 30 * 2);
        blackCountText.setPosition(673, 3 * size + 30 * 3);
        window.draw(whiteCountText);
        window.draw(blackCountText);
        deleteText.setString("Удалить");
        deleteText.setPosition(673, 3 * size);
        if (color > 0) {
            colorText.setString("Ход:Белые");
        }
        else {
            colorText.setString("Ход:Черные");
        }
        colorText.setPosition(673, 3 * size + 30 * 1);
        window.draw(deleteText);
        window.draw(colorText);
        for (int i = 0; i < 30; i++) window.draw(f[i]);
        for (int i = 0; i < 6; i++) {
            window.draw(dice[i]);
            window.draw(dice2[i]);
        } 
        for (int i = 0; i < 3; i++) window.draw(posibleMoves[i]);
        window.draw(deleteButton);
        window.display();
    }

    return 0;
}