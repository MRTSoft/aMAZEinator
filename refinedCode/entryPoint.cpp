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

#include "resources.h"
#include "SFML/Graphics.hpp"
#include "maze.h"
#include <iostream>
#include <string>
#include <sstream>


void loadGraphics();
sf::Texture tiles[15];

int main (int argNr, char* args[])
{
    loadGraphics();
    sf::RenderWindow screen(sf::VideoMode(800,600), "a M A Z E inator");
    //initiate();
    screen.setActive(false);
    sf::Thread renderThread(&renderWindow, &screen);
    renderThread.launch();
    sf::Event event;
    while(screen.isOpen())
    {
        while(screen.pollEvent(event))
        {
            //handle logistic
            handleEvents(event, &screen);
        }
    }
    //*/
    return 0;
}

void renderWindow(sf::RenderWindow * screen)
{
    screen->setActive();
    while(screen->isOpen())
    {
        //first draw everything
        //then display
        screen->display();
    }
}

void pasteString(int x, std::string & orig)
{
    std::stringstream ss;
    ss<<x;
    orig.append(ss.str());
}

void loadGraphics()
{
    std::string fName = "";
    std::string basePath = "Textures/img";
    std::string ext = ".png";

    for (unsigned i=0; i<15; i++)
    {
        fName = basePath;
        pasteString((int)i, fName);
        fName += ext;
        if (!tiles[i].loadFromFile(fName))
            std::cout<<"Fail to load "<<fName<<std::endl;
    }
}
