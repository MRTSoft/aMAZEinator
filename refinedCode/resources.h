#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include "SFML/Graphics.hpp"
//TILE MAP CLASS
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

//VARIABLES
//NOTE screen needs to be created via the .create() method


sf::View v_active();
//sf::Texture tiles[15];
//FUNCTIONS
void loadGraphics();
void initiate();//needs to be called first

void renderWindow(sf::RenderWindow * screen, TileMap * map);
void handleEvents(sf::Event event, sf::RenderWindow * screen);



#endif // RESOURCES_H_INCLUDED
