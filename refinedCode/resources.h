#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED


//VARIABLES
//NOTE screen needs to be created via the .create() method
#include "SFML/Graphics.hpp"

sf::View v_active();
//sf::Texture tiles[15];
//FUNCTIONS
void loadGraphics();
void initiate();//needs to be called first

void renderWindow(sf::RenderWindow * screen);
void handleEvents(sf::Event event, sf::RenderWindow * screen);

#endif // RESOURCES_H_INCLUDED
