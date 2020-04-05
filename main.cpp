#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x,y,dotX,dotY,score,level = 0;
int tailX[100],tailY[100];
int tail=0;
enum direction { stop = 0, Left, Right, Up, Down};
direction dir;

void HideCursor()  //���ù���
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0};
SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Gotoxy(int x, int y){  //��goto��{�M�W
    //int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = x;
    loc.Y=y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}

void Setup(){  //�C����l�]�w
    HideCursor();
    srand( time(NULL) );
    gameOver = false;
    dir = stop;
    x = width/2;
    y = height/2;
    dotX = rand()%width;
    dotY = rand()%height;
    score = 0;
    if(dotX == 0 || dotX >= width-1)
        dotX = width/2+1;
    if(dotY == 0 || dotY >= height-1)
        dotY = height/2;
}
void Lobby(){  //�C���j�U
    Gotoxy(0,0);
    cout << "�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w" << endl;
    for(int i=1;i<19;i++){
        if(!gameOver){
            if(i == 2)
                cout << "|�W�h:             |" << endl;
            else if(i == 3)
                cout << "|wasd�ӱ���g�Y�D��|" << endl;
            else if(i == 4)
                cout << "|��(�^��p�g),esc��|" << endl;
            else if(i == 5)
                cout << "|���C��            |" << endl;
            else if(i == 8)
                cout << "|�п�J���סC      |" << endl;
            else if(i == 9)
                cout << "|1��²��(�i����)   |" << endl;
            else if(i == 10)
                cout << "|2���x��(���i����) |" << endl;
            else if(i == 11)
                cout << "|��L�Ʀr�������C��|" << endl;
            else
                cout << "|                  |" << endl;
        }
        else{
            if(i == 2 && score <10){
                cout << "|score:" << score << "           |" << endl;
                i++;
            }
            else if(i == 2 && score >= 10){
                cout << "|score:" << score << "          |" << endl;
                i++;
            }
            if(i == 8 && score <= 5)
                cout << "|���y:.......�C    |" << endl;
            else if(i == 8 && score <= 10)
                cout << "|���y:�S���~484�C  |" << endl;
            else if(i == 8 && score <= 15 )
                cout << "|���y:�j�j�j�j�C   |" << endl;
            else if(i == 8 && score <= 25 )
                cout << "|���y:�i�C         |" << endl;
            else if(i == 8 && score <= 30 )
                cout << "|���y:���C         |" << endl;
            else if(i == 8 && score >= 50 )
                cout << "|���y:�F�`�F�C     |" << endl;
            else
                cout << "|                  |" << endl;
        }
    }
    cout << "�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w" << endl;
    while(!gameOver && cin >> level){
    system("cls");
    cout << "���Ū����,�еy��...";
    if(level == 1 || level == 2)
        Sleep(3500);
    break;
    }
}
void Map(){  //�a��ø�s
    Gotoxy(0,0);
    //system("cls");
    for(int i = 0 ;i<width;i++)
        cout << "�w";
    cout << endl;

    for(int i = 1;i<height-1;i++){
        for(int j = 0;j<width-1;j++){
            if(i == dotY && j == dotX)
                cout << "F";  //���G
            else if(j == 0)
                cout << "|";  //�a�����
            else if(i == y && j == x)
                cout << "@";  //�D�D
            else{
                bool print = false;
                for(int k=0;k<tail;k++){
                    if(tailX[k] == j && tailY[k] == i){
                    cout << "o";
                    print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }
        }
        cout << "|";
        if(i == 7){
            cout << "   �{�b��ܪ����׬O:" ;
            if(level == 1)
                cout << "²��(�i����)";
            else
                cout << "�x��(���i����)";
        }
        if(i == height/2-1)
            cout << "   score:" << score;
        cout << endl;
    }

    for(int i = 0; i<width ; i++)
        cout << "�w";
}
void Input(){  //���a��J
    if(kbhit()){
        switch(getch()){
            case 'a':
                dir = Left;
                break;
            case 'd':
                dir = Right;
                break;
            case 'w':
                dir = Up;
                break;
            case 's':
                dir = Down;
                break;
            case 27:
                gameOver = true;
                break;
        }
    }
}
void Logic(){
    int prex = tailX[0];
    int prey = tailY[0];
    int prex2,prey2;
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1;i<tail;i++){  //tailXY[i]�Pprexy�洫
        prex2 = tailX[i];
        prey2 = tailY[i];
        tailX[i] = prex;
        tailY[i] = prey;
        prex = prex2;
        prey = prey2;
    }
    switch(dir){
            case Left:
                x--;
                break;
            case Right:
                x++;
                break;
            case Up:
                y--;
                break;
            case Down:
                y++;
                break;
    }
    if((level ==2)&&(x>=width-1 || x<=0 || y>=height-1 || y<=0)){
        gameOver = true;
    }
    else{
        if(x >= width-1)
            x = 1;
        else if(x <= 0)
            x = width-2;
        if(y >= height-1)
            y = 1;
        else if(y <= 0)
            y = height-2;
    }

    for(int i=0;i<tail;i++)
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if(x == dotX && y == dotY){
        score += 1;
        dotX = rand()%width;
        dotY = rand()%height;
       // tailX[tail] = x;
       // tailY[tail] = y;
        tail++;
    }
    if(dotX == 0 || dotX >= width-2)
        dotX = width/2+1;
    if(dotY == 0 || dotY >= height-1)
        dotY = height/2;
}

int main()
{
    Setup();
    Lobby();
    if(level>2 || level<=0 )
        gameOver = true;
    while(!gameOver){
        Map();
        Input();
        Logic();
        Sleep(200-score*3);  //�D���ʳt���H���ƶV���V��
    }
    Lobby();
    //system("pause");
    return 0;
}
