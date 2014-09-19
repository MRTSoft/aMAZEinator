#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#define _TILE_W 40
#define _TILE_H 40
#define _PADDING 10
#include "SFML/Graphics.hpp"
#include "maze.h"

//TILE MAP CLASS
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    bool changeTileSet (const std::string& tileset, sf::Vector2u tileSize);
    bool changeTileIcon (unsigned int x, unsigned int y, unsigned int index);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    //added
    sf::Vector2u m_tileSize;
    unsigned int m_width, m_height;

};

//VARIABLES
//NOTE screen needs to be created via the .create() method

extern sf::RenderWindow screen;
extern sf::View v_active;
extern TileMap mMap;//maze map
extern Maze M;

//FUNCTIONS

void initiate();//needs to be called first

void renderWindow();
void handleEvents(sf::Event event);



#endif // RESOURCES_H_INCLUDED
