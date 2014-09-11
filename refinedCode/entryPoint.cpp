/* COPYRIGHT (C) Marcu Tudor 2014 MR
 * This work is licensed under the
 * Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
 * To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 * or read the license offline in the License folder
 */

 /*
  * Main entry point of the application
  * Contains the main() functions and functions needed to load the graphics
  */
//LIBRARIES FOR GRAPHICS
//TODO create SFML integration
/*
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
*/
#include "maze.h"
#include <iostream>
    //TODO include custom library for logistic and others
/*
//VARIABLES AND CONSTANTS
#define S_WIDTH 800
#define S_HEIGHT 600
#define S_DEPTH 32
//initial video mode set to 800x600x32
typedef SDL_Surface Surf;
typedef SDL_Rect Rect;
Surf * screen;
Surf * sprite;
Surf * guiSprite;// NOTE Need to figure out how to build the GUI

void applyTo(int, int, surf *, surf *);
void applyTo(int, int, surf *, surf *, int, int);
bool init();
void cleanUp();
bool loadResources();
//FUNCTIONS PROTO
*/

int main (int argNr, char* args[])
{
    Maze M(4,4);
    M.genMaze();
    for (unsigned i=0; i< M.getH(); i++)
    {
        for (unsigned j=0; j<M.getW(); j++)
        {
            std::cout<<(int)M.getCell(j,i)<<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}
