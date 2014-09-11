#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

/*!
 \file maze.h
 \brief Contains the maze class definition
*/

/*!
 \brief Defines the maze and Wall class and provides functionalities for them
*/

// TODO write documentation for the Wall class
enum Wall
{
    Down = 1,
    Right = 2,
    Up = 4,
    Left = 8
};

// TODO write documentation for the Maze class
class Maze
{
public:
    enum Wall {Down = 1,    Right = 2,    Up = 4,    Left = 8};
    //CONSTRUCTORS
    Maze();
    Maze(unsigned width, unsigned height);
    //DESTRUCTOR
    ~Maze();
    //FUNCTIONS
    unsigned getH();
    unsigned getW();
    // char operator()(unsigned x, unsigned y);
    unsigned char getCell(unsigned x, unsigned y);
    //
    bool setWall(unsigned x, unsigned y, Wall w, bool v);
    Maze& operator = (const Maze& source);//Prevents shallow copying
    void genMaze();
private:
    /*
    const unsigned m_d_down = 1;
    const unsigned m_d_right = 2;
    const unsigned m_d_up = 4;
    const unsigned m_d_left = 8;
    // */
    unsigned m_width;
    unsigned m_height;
    unsigned char * m_data;
    void breakInto(unsigned x, unsigned y, Wall direction);
    bool setDirection(unsigned& x, unsigned& y, Wall dir);
};


#endif // MAZE_H_INCLUDED
