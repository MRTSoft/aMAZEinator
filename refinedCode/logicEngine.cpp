/* COPYRIGHT (C) Marcu Tudor 2014 MR
 * This work is licensed under the
 * Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 * or read the license offline in the License folder
 */

/*
* LOGIC ENGINE
* Contains the functions needed for game logistic:
*     -> Generating the maze
*     -> Reward system and others
*/

//INCLUDE LIBRARIES
#include <iostream>// cerr, cin and cout
#include <stdlib.h>//srand() and rand() functions
#include "maze.h"
// using namespace std; //do we need this?

//variables, constants and data types
//define directions as integers
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
//define constrains
#define MAX_H 50  //depends....
#define MAX_W 100 //depends....
//define data types (cell)
struct Cell//(*)
{
    bool u, d, l, r;//the walls of the cell (up, down, left, right)
    int val; //the value of the cell
    char flag; // flag - can be used to symbol all sorts of things
};
#define CELL_NULL ' '
#define CELL_VISITED 'v'

// in the C array we have all the possible arrangements  of 4
//const unsigned C[24] = {1234, 1243, 1324, 1342, 1423, 1432, 2134, 2143, 2314, 2341, 2413, 2431, 3124, 3142, 3214, 3241, 3412, 3421, 4123, 4132, 4213, 4231, 4312, 4321}; //initial ordered array
const unsigned C[24] = {1423, 1324, 3214, 4231, 4132, 2341, 4123, 3142, 1342, 3421, 1432, 4213, 2143, 4321, 2431, 3124, 2314, 4312, 3241, 1234, 2413, 3412, 1243, 2134}; //final randomized array
int mW, mH;// globally stores the maze Width (mW) and Height (mH)

//Function prototypes
//NOTE - to be moved into a header file function marked with (*)
Cell * generateMaze(int, int);//(*)
void breakInto(Cell *, int, int, int);
void goUp(Cell *, int, int);
void goDown(Cell *, int, int);
void goLeft(Cell *, int, int);
void goRight(Cell *, int, int);
//Function definition
Cell * generateMaze(int width, int height)//the main function of the file
{
    //validate the parameters
    if(width < 1 || width > MAX_W)
    {
        std::cerr << "ERROR: Width out of bounds!\n";
        return NULL;
    }
    if(height < 1 || height > MAX_H)
    {
        std::cerr << "ERROR: Height out of bounds!\n";
        return NULL;
    }
    //if everything is OK start generating the maze
    //store the dimensions
    mW = width;
    mH = height;
    //Allocate memory
    Cell * M = new(std::nothrow) Cell [mH * mW];
    //Verify if the memory was allocated
    if(M == NULL)
    {
        std::cerr << "ERROR: Memory could not be allocated!\n";
        return NULL;
    }
    //Initiate the maze with default values
    for(int i = 0; i < mH * mW; i++)
    {
        M[i].u = M[i].d = M[i].l = M[i].r = true; //Initially all cells have all walls
        M[i].val = 0;  //Initiate the value of the cell
        M[i].flag = CELL_NULL;
    }
    //Select a random cell to start
    char * a = new(std::nothrow) char;
    srand((unsigned)a);
    breakInto(M, rand() % mH, rand() % mW, 5);// 5 = no direction
    //Create the entrance in the top left
    M[0].l = false;
    //Create an exit in the bottom right
    M[mH * mW - 1].r = false;
    delete a;
    return M;//finally return the generated maze
}

void breakInto(Cell * M, int x, int y, int dir)
{
    /* PARAMETERS:
     * M - the maze  | x,y - the coordinates of the maze cell
     *    (I use standard display coordinates where (0,0) is in the top left corner
     *     and the X axis goes towards left and the Y axis goes downward)
     * dir - the direction from where we entered in the cell
     */
    //If the cell was already visited stop the function
    if(M[y * mW + x].flag == CELL_VISITED) return;
    //Mark the cell as visited
    M[mW * y + x].flag = CELL_VISITED;
    //Break down the wall used to enter in the cell
    switch(dir)
    {
    case UP:
        M[y * mW + x].u = false;
        break;
    case DOWN:
        M[y * mW + x].d = false;
        break;
    case LEFT:
        M[y * mW + x].l = false;
        break;
    case RIGHT:
        M[y * mW + x].r = false;
        break;
    default:
        ;//do nothing
    }
    //get a random combination of directions to go
    unsigned comb = C[rand() % 24];
    while(comb != 0)
    {
        switch((comb % 10) - 1)
        {
        case UP:
            goUp(M, x, y);
            break;
        case DOWN:
            goDown(M, x, y);
            break;
        case LEFT:
            goLeft(M, x, y);
            break;
        case RIGHT:
            goRight(M, x, y);
            break;
        }
        comb = comb / 10;
    }
}

void goUp(Cell * M , int x, int y)
{
    //try to go up
    if(y - 1 >= 0 && M[(y - 1)*mW + x].flag != CELL_VISITED)
    {
        M[y * mW + x].u = false;
        breakInto(M, x, y - 1, DOWN);
    }
}
void goDown(Cell * M , int x, int y)
{
    //try to go down
    if(y + 1 < mW && M[(y + 1)*mW + x].flag != CELL_VISITED)
    {
        M[y * mW + x].d = false;
        breakInto(M, x, y + 1, UP);
    }
}
void goLeft(Cell * M , int x, int y)
{
    //try to go left
    if(x - 1 >= 0 && M[y * mW + x - 1].flag != CELL_VISITED)
    {
        M[y * mW + x].l = false;
        breakInto(M, x - 1, y, RIGHT);
    }
}
void goRight(Cell * M , int x, int y)
{
    //try to go right
    if(x + 1 < mH && M[y * mW + x + 1].flag != CELL_VISITED)
    {
        M[y * mW + x].r = false;
        breakInto(M, x + 1, y, LEFT);
    }
}



/*
 * TESTING FUNCTION (will not be included in the release code)

void display(Cell * L)
{
    bool buff1[4 * mW];
    bool buff2[4 * mW];
    bool buff3[4 * mW];
    char dChar = '*';//display char
    std::cout << '\n';
    for(int i = 0; i < mH; i++)//for 1
    {
        for(int j = 0; j < mH; j++)//for 2
        {
            buff1[4 * j] = buff1[4 * j + 3] = true;
            buff1[4 * j + 1] = buff1[4 * j + 2] = L[j + i * mW].u;
            buff3[4 * j] = buff3[4 * j + 3] = true;
            buff3[4 * j + 1] = buff3[4 * j + 2] = L[j + i * mW].d;

            buff2[4 * j + 1] = buff2[4 * j + 2] = false; //center is always empty
            buff2[4 * j] = L[j + i * mW].l;
            buff2[4 * j + 3] = L[j + i * mW].r;
        }//end for 2
        for(int k = 0; k < 4 * mW; k++)
        {
            if(buff1[k]) std::cout << dChar;
            else std::cout << " ";
        }
        std::cout << '\n';
        for(int k = 0; k < 4 * mW; k++)
        {
            if(buff2[k]) std::cout << dChar;
            else std::cout << " ";
        }
        std::cout << '\n';
        for(int k = 0; k < 4 * mW; k++)
        {
            if(buff3[k]) std::cout << dChar;
            else std::cout << " ";
        }
        std::cout << '\n';
    }
}
int main(int argNr, char * args[])
{
    Cell * Maze = generateMaze(10, 10);
    display(Maze);
    return 0;
}

*/
