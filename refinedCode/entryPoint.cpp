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

#include "resources.h"
#include "SFML/Graphics.hpp"
#include "maze.h"
#include <iostream>

sf::RenderWindow screen;
sf::View v_active;
TileMap mMap;//maze map
Maze M;


//To set global variables in resources.h simply put 'external' before them
//then declare them somewere else
int main (int argNr, char* args[])
{
    initiate();

    screen.setActive(false);
    sf::Thread renderThread(&renderWindow);
    renderThread.launch();

    sf::Event event;
    while(screen.isOpen())
    {
        while(screen.pollEvent(event))
        {
            //handle logistic
            handleEvents(event);
        }
    }
    //*/
    return 0;
}

void renderWindow()
{
    sf::Color bgColor(0xfb, 0xbb, 0x91);
    screen.setActive();
    while(screen.isOpen())
    {
        screen.clear(bgColor);
        //first draw everything
        screen.draw(mMap);
        //then display
        screen.setView(v_active);
        screen.display();
    }
}

//Initiate all the parameters
void initiate()
{
    screen.create(sf::VideoMode(800,600), "a M A Z E inator");

    v_active = screen.getDefaultView();
    unsigned mH = 10, mW = 10;
    Maze M(mW, mH);
    M.genMaze();
    int T[mW*mH];
    M.toIntArray(T);
    mMap.load("Textures/sprite2.png", sf::Vector2u(40,40), T, mW, mH);
}
