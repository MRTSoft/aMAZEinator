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
// #include <iostream> // do we need this?
#include <stdlib.h>
#include <time.h>
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
struct Cell
{
    bool u, d, l, r;//the walls of the cell (up, down, left, right)
    int val; //the value of the cell
};

// in the C array we have all the possible arrangements  of 4
//const unsigned C[24] = {1234, 1243, 1324, 1342, 1423, 1432, 2134, 2143, 2314, 2341, 2413, 2431, 3124, 3142, 3214, 3241, 3412, 3421, 4123, 4132, 4213, 4231, 4312, 4321}; //initial ordered array
  const unsigned C[24] = {1423, 1324, 3214, 4231, 4132, 2341, 4123, 3142, 1342, 3421, 1432, 4213, 2143, 4321, 2431, 3124, 2314, 4312, 3241, 1234, 2413, 3412, 1243, 2134}; //final randomized array
int mW, mH;// globally stores the maze Width (mW) and Height (mH)

//Function prototypes

//Function definition
Cell * generateMaze(int width, int height)//the main function of the file
{
    //validate the parameters
    if (width < 1 || width > MAX_W)
    {
        std::cerr<<"ERROR: Width out of bounds!\n";
        return NULL;
    }
    if (height < 1 || height > MAX_H)
    {
        std::cerr<<"ERROR: Height out of bounds!\n";
        return NULL;
    }
    //if everything is OK start generating the maze
        //store the dimensions
        mW = width;
        mH = height;
    //Allocate memory
    Cell * M = new (nothrow) Cell [mH*mW];
    //Verify if the memory was allocated
    if (M == NULL)
    {
        std::cerr<<"ERROR: Memory could not be allocated!\n"
    }
}


