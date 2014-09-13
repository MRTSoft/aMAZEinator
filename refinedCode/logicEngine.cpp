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
#include "resources.h"
#include <iostream>
void handleEvents(sf::Event ev)
{
    switch(ev.type)
    {
        case sf::Event::Closed:
            screen.close();
            break;

        case sf::Event::Resized:
            {
                float w = ev.size.width, h = ev.size.height;
                /*
                //first get the smallest size of the window
                float minSize = w < h ? w : h;
                //set the view on the center of the window
                v_active.setCenter(w/2, h/2);//set to be the center of the maze
                //unsigned cmx, cmy;
                v_active.setSize(w, h);
                //*/
                //v_active.setSize(w,h);
                sf::FloatRect vArea (-10,-10,w,h);
                v_active = sf::View(vArea);
                //v_active.setViewport(sf::FloatRect(0,0,w,h));
            }
            break;

        default://do nothing
            break;
    }
}

//TILE SET DEFINITION
bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if(!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for(unsigned int i = 0; i < width; ++i)
        for(unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];
            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();
    // apply the tileset texture
    states.texture = &m_tileset;
    // draw the vertex array
    target.draw(m_vertices, states);
}
