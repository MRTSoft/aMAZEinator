#include "maze.h"
#include <stdexcept>
#include <stdlib.h>
Maze::Maze()
{
    //By default create a void maze
    const unsigned maze_size = 10;
    m_height = m_width = maze_size;
    m_data = new unsigned char [maze_size * maze_size];

    for(unsigned long i = 0; i < maze_size * maze_size; i++)
        m_data[i] = 15;//all wals are set
}

Maze::Maze(unsigned w, unsigned h)
{
    m_height = h;
    m_width = w;
    m_data = new unsigned char [w * h];

    for(unsigned long i = 0; i < w * h; i++)
        m_data[i] = 15;//all wals are set

    //NOTE new throws exceptions
}

Maze::~Maze()
{
    delete[] m_data;
}

Maze & Maze::operator = (const Maze & other)
{
    if(&other == this) return *this;

    delete[] m_data;
    m_height = other.m_height;
    m_width = other.m_width;
    m_data = new unsigned char[m_height * m_width];

    for(unsigned i = 0; i < m_height; i++)
    {
        for(unsigned j = 0; j < m_width; j++)
        {
            m_data[i * m_height + j] = other.m_data[i * m_height + j];
        }
    }

    return *this;
}
//NOTE x and y are zero-based!
unsigned Maze::getH()
{
    return m_height;
}
unsigned Maze::getW()
{
    return m_width;
}
unsigned char Maze::getCell(unsigned x, unsigned y)
{
    if(x >= m_width) throw std::out_of_range("x is larger than the width of the maze!");

    if(y >= m_height) throw std::out_of_range("y is larger than the height of the maze!");

    return m_data[y * m_width + x];
    //NOTE getCell throws exceptions
}

void Maze::toIntArray(int * A)
{
    for(unsigned i = 0; i < m_height; i++)
    {
        for(unsigned j = 0; j < m_width; j++)
            A[i * m_height + j] = (int)m_data[i * m_height + j];
    }
}
bool Maze::setWall(unsigned x, unsigned y, Wall w, bool v)
{
    if(x >= m_width) throw std::out_of_range("x is larger than the width of the maze!");

    if(y >= m_height) throw std::out_of_range("y is larger than the height of the maze!");

    if(m_data[y * m_width + x] & (char)w) //bit is true
    {
        if(!v) //if we need to set it to false
            m_data[y * m_width + x] = m_data[y * m_width + x] ^ (unsigned char) w; //XOR
    }
    else//bit is false
    {
        if(v) //and we need it to be true
            m_data[y * m_width + x] = m_data[y * m_width + x] | (unsigned char) w; //AND
    }
}

void Maze::genMaze()//generate the maze
{
    unsigned int * a;
    a = new unsigned int;
    srand(*a);
    delete a;
    this->breakInto(0, (unsigned)(rand() % m_height), Right); //create an entry
    this->setWall(m_width - 1, (unsigned)(rand() % m_height), Right, false); //create an exit
}
Maze::Wall intToWall(int x)
{
    switch(x)
    {
        case 1:
            return Maze::Down;
            break;

        case 2:
            return Maze::Right;
            break;

        case 4:
            return Maze::Up;
            break;

        case 8:
            return Maze::Left;
            break;

        default:
            return Maze::Down;
    }
}

bool Maze::setDirection(unsigned & x, unsigned & y, Wall dir)
{
    //(0,0) is top left corner
    switch(dir)
    {
        case Down:
            {
                if(y < m_height - 1) y++;
                else return false;
            }
            break;

        case Up:
            {
                if(y >= 1) y--;
                else return false;
            }
            break;

        case Right:
            {
                if(x < m_width - 1) x++;
                else return false;
            }
            break;

        case Left:
            {
                if(x >= 1) x--;
                else return false;
            }
            break;
    }

    if(this->getCell(x, y) == 15) return true;

    return false;
}
const unsigned C[24] = {4281, 8241, 8124, 1428, 2418, 1842, 4218, 2814, 2841, 1284, 2481, 4128, 4812, 1248, 1482, 8214, 8142, 2148, 1824, 8421, 4182, 2184, 4821, 8412}; //final randomized array
void reverseDir(Maze::Wall& dir)
{
    if(dir == Maze::Down) dir = Maze::Up;
    else if(dir == Maze::Up) dir = Maze::Down;
    else if(dir == Maze::Left) dir = Maze::Right;
    else if(dir == Maze::Right) dir = Maze::Left;
}
void Maze::breakInto(unsigned x, unsigned y, Wall direction)
{
    if(getCell(x, y) == 15) //if the cell was not visited
    {
        //break the entry wall
        Wall rev = direction;
        reverseDir(rev);
        this->setWall(x, y, rev, false);
        //select a random direction
        unsigned sec = C[rand() % 24];

        while(sec != 0)
        {
            rev = intToWall((int)sec % 10);
            sec = sec / 10;
            unsigned x1 = x, y1 = y;

            if(this->setDirection(x1, y1, rev))
            {
                //reverseDir(rev);
                this->setWall(x, y, rev, false);
                //reverseDir(rev);
                this->breakInto(x1, y1, rev);
                //revenire pe stiva
            }
        }
    }
}

//TODO order methods alfabatically
