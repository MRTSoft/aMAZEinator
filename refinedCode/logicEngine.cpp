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

void handleEvents(sf::Event ev, sf::RenderWindow * screen)
{
    switch (ev.type)
    {
    case sf::Event::Closed:
        screen->close();
        break;
    case sf::Event::Resized:
        break;

    }
}
