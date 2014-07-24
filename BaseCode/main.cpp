#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
//DEFINITIONS
#define SUS 0
#define JOS 1
#define STANGA 2
#define DREAPTA 3
#define MAX_WIDTH 19
#define MAX_HEIGHT 18
struct Cell
{
    bool u, d, l, r;
    bool used;
};

//VARIABLES
int mX, mY; //maximum size of the maze
Cell L[MAX_WIDTH][MAX_HEIGHT];
unsigned int C[24] = {1234, 1243, 1324, 1342, 1423, 1432, 2134, 2143, 2314, 2341, 2413, 2431, 3124, 3142, 3214, 3241, 3412, 3421, 4123, 4132, 4213, 4231, 4312, 4321};
//FUNCTIONS
void create(int, int, int);
void initiate();
void display();
void goUp(int x, int y);
void goDown(int x, int y);
void goLeft(int x, int y);
void goRight(int x, int y);

int main()
{
    cout << "Introduceti dimensiunile labirintului:\n";
    cout << "\tIntroduceti latimea (nu mai mult de "<<MAX_WIDTH<<"):\n\t\t>: ";
    cin >> mX;
    if(mX <= 1 || mX > 80) mX = MAX_WIDTH/2;
    cout << "\tIntroduceti lungimea (nu mai mult de "<<MAX_HEIGHT<<"):\n\t\t>: ";
    cin >> mY;
    if(mY <= 1 || mY > 80) mY = MAX_HEIGHT/2;
    initiate();
    int ix = 0, iy = 0;
    srand(time(NULL));
    ix = rand() % mX;
    iy = rand() % mY;
    create(ix, iy, 10);
    L[0][0].l = false;//create the entrance
    L[mX - 1][mY - 1].r = false; //create the exit
    display();
    return 0;
}

void initiate()
{
    for(int i = 0; i < mX; i++)
    {
        for(int j = 0; j < mY; j++)
        {
            L[i][j].d = L[i][j].l = L[i][j].r = L[i][j].u = true;
            L[i][j].used = false;
        }
    }
}

void create(int x, int y, int dir)
{
    //x - coordonata x a celulei | y - coordonata y a celulei
    //dir - directia prin care s-a intrat in celula (pe unde se intra)
    if(L[x][y].used) return;
    L[x][y].used = true;//mark as used cell
    switch(dir)
    {
    case SUS:
        L[x][y].u = false;
        break;
    case JOS:
        L[x][y].d = false;
        break;
    case STANGA:
        L[x][y].l = false;
        break;
    case DREAPTA:
        L[x][y].r = false;
        break;
    }
    //srand(time(NULL));
    unsigned comb = C[rand() % 24];
    while(comb != 0)
    {
        switch((comb % 10) - 1)
        {
        case SUS:
            goUp(x, y);
            break;
        case JOS:
            goDown(x, y);
            break;
        case STANGA:
            goLeft(x, y);
            break;
        case DREAPTA:
            goRight(x, y);
            break;
        }
        comb = comb / 10;
    }
}

void goUp(int x, int y)
{
    //try to go up
    if(y - 1 >= 0 && !L[x][y - 1].used)
    {
        L[x][y].u = false;
        create(x, y - 1, JOS);
    }
}
void goDown(int x, int y)
{
    //try to go down
    if(y + 1 < mY && !L[x][y + 1].used)
    {
        L[x][y].d = false;
        create(x, y + 1, SUS);
    }
}
void goLeft(int x, int y)
{
    //try to go left
    if(x - 1 >= 0 && !L[x - 1][y].used)
    {
        L[x][y].l = false;
        create(x - 1, y, DREAPTA);
    }
}
void goRight(int x, int y)
{
    //try to go right
    if(x + 1 < mX && !L[x + 1][y].used)
    {
        L[x][y].r = false;
        create(x + 1, y, STANGA);
    }
}


char getDir(Cell c)
{
    if(!c.u) return '^';
    if(!c.d) return 'v';
    if(!c.l) return '<';
    if(!c.r) return '>';
}

void display()
{
    bool buff1[4 * mX];
    bool buff2[4 * mX];
    bool buff3[4 * mX];
    char dChar = '*';//display char
    cout << '\n';
    for(int i = 0; i < mY; i++)//for 1
    {
        for(int j = 0; j < mX; j++)//for 2
        {
            buff1[4 * j] = buff1[4 * j + 3] = true;
            buff1[4 * j + 1] = buff1[4 * j + 2] = L[j][i].u;
            buff3[4 * j] = buff3[4 * j + 3] = true;
            buff3[4 * j + 1] = buff3[4 * j + 2] = L[j][i].d;

            buff2[4 * j + 1] = buff2[4 * j + 2] = false; //center is always empty
            buff2[4 * j] = L[j][i].l;
            buff2[4 * j + 3] = L[j][i].r;
        }//end for 2
        for(int k = 0; k < 4 * mX; k++)
        {
            if(buff1[k]) cout << dChar;
            else cout << " ";
        }
        cout << '\n';
        for(int k = 0; k < 4 * mX; k++)
        {
            if(buff2[k]) cout << dChar;
            else cout << " ";
        }
        cout << '\n';
        for(int k = 0; k < 4 * mX; k++)
        {
            if(buff3[k]) cout << dChar;
            else cout << " ";
        }
        cout << '\n';
    }
}
