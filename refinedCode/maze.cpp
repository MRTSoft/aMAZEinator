#include "maze.h"
#include <stdexcept>
#include <stdlib.h>
Maze::Maze()
{
    //By default create a void maze
    m_height = m_width = 0;
    m_data = 0;
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

Maze& Maze::operator = (const Maze& other)
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
unsigned char Maze::getCell(unsigned x, unsigned y)
{
    if(x >= m_width) throw std::out_of_range("x is larger than the width of the maze!");
    if(y >= m_height) throw std::out_of_range("y is larger than the height of the maze!");
    return m_data[y * m_width + x];
    //NOTE getCell throws exceptions
}

bool Maze::setWall(unsigned x, unsigned y, Wall w, bool v)
{
    if(x >= m_width) throw std::out_of_range("x is larger than the width of the maze!");
    if(y >= m_height) throw std::out_of_range("y is larger than the height of the maze!");
    if (m_data[y*m_width+x] & (char)w)//bit is true
    {
        if (!v)//if we need to set it to false
            m_data[y*m_width+x] = m_data[y*m_width+x] ^ (unsigned char) w;//XOR
    }
    else//bit is false
    {
        if (v)//and we need it to be true
            m_data[y*m_width+x] = m_data[y*m_width+x] | (unsigned char) w;//AND
    }
}

void Maze::genMaze()//generate the maze
{
    unsigned int *a;
    a = new unsigned int;
    srand(*a);
    delete a;
    this->breakInto(0, (unsigned) (rand()%m_height), Right);//create an entry
    this->setWall(m_width-1, (unsigned) (rand()%m_height), false);//create an exit

}

void Maze::breakInto(unsigned x, unsigned y, Wall direction)
{
    if (getCell(x,y)!=0)//if the cell was not visited
    {
        //break the entry wall
        Wall rev = Left;
        if (direction == Up) rev = Down;
        else if (direction == DOWN) rev = Up;
        else if (direction == Left) rev = Right;
        this->setWall(x,y,rev,false);
        //select a random direction
    }
}
