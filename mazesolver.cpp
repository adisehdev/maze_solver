//-------------------MAZE SOLVER PROGRAM-------------------
//Made by : Paras Roy [https:github.com/paras-roy]
//Date of creation : 16/05/2023
//Work done under : Team Kalpana, NSUT

// ------------------Header Files--------------------------

#include <iostream>

// ------------------Class Definitions---------------------

class Cell
{
    public:
    // ------------------Public Variables---------------------
        int x, y;
        int dist;
        int wallCode; // wallCode is a 4 bit binary number, where each bit represents the presence of a wall in the direction of North, East, South and West respectively.
        bool visited;

    // ------------------Public Functions---------------------

        Cell()
        {
            x = 0;
            y = 0;
            dist = 0;
            wallCode = 0;
            visited = false;
        }

        Cell(int x, int y, int dist, int wallCode)
        {
            this->x = x;
            this->y = y;
            this->dist = dist;
            this->wallCode = wallCode;
            visited = false;
        }

        void setWallCode(int wallCode)
        {
            this->wallCode = wallCode;
        }

        void setDist(int dist)
        {
            this->dist = dist;
        }
};

class Maze
{
    public:
    // ------------------Public Variables---------------------
        Cell cells[16][16];


    // ------------------Public Functions---------------------
        Maze()
        {
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    cells[i][j] = Cell(i, j, 255, 0);
                }
            }

            //set wallcode for cells on the edges
            for(int i = 0; i < 16; i++)
            {
                cells[i][0].setWallCode(cells[i][0].wallCode | 8);
                cells[i][15].setWallCode(cells[i][15].wallCode | 2);
                cells[0][i].setWallCode(cells[0][i].wallCode | 1);
                cells[15][i].setWallCode(cells[15][i].wallCode | 4);
            }

        }

        void printMazeWalls()
        {
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    std::cout << cells[i][j].wallCode << " ";
                }
                std::cout << std::endl;
            }
        }

        void printMazeDist()
        {
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    std::cout << cells[i][j].dist << " ";
                }
                std::cout << std::endl;
            }
        }

        void updateWall(int x, int y, int wallCode)
        {
            //add new walls to current cell
            cells[x][y].setWallCode(cells[x][y].wallCode | wallCode);

            if((wallCode & 1) == 1)
            {
                if(x+1 <= 15)
                {
                    cells[x+1][y].setWallCode(cells[x+1][y].wallCode | 1);
                }
            }

            if((wallCode & 2) == 2)
            {
                if(y-1 >= 0)
                {
                    cells[x][y-1].setWallCode(cells[x][y-1].wallCode | 2);
                }
            }

            if((wallCode & 4) == 4)
            {
                if(x-1 >= 0)
                {
                    cells[x-1][y].setWallCode(cells[x-1][y].wallCode | 4);
                }
            }

            if((wallCode & 8) == 8)
            {
                if(y+1 <= 15)
                {
                    cells[x][y+1].setWallCode(cells[x][y+1].wallCode | 8);
                }
            }
        }

        //function to print walls in the form of lines and proper spacing
        void printMaze()
        {
            for(int i = 0; i < 16; i++)
            {
                std::cout << "+";
                for(int j = 0; j < 16; j++)
                {
                    if((cells[i][j].wallCode & 1) == 1)
                    {
                        std::cout << "---";
                    }
                    else
                    {
                        std::cout << "   ";
                    }
                    std::cout << "+";
                }
                std::cout << std::endl;
                for(int j = 0; j < 16; j++)
                {
                    if((cells[i][j].wallCode & 8) == 8)
                    {
                        std::cout << "|";
                    }
                    else
                    {
                        std::cout << " ";
                    }
                    std::cout << "   ";
                }
                std::cout << "|" << std::endl;
            }
            std::cout << "+";
            for(int j = 0; j < 16; j++)
            {
                std::cout << "---+";
            }
            std::cout << std::endl;
        }


};

class Bot
{
    public: 
    // ------------------Public Variables---------------------
        int x, y;
        int dir; // 0 for North, 1 for East, 2 for South, 3 for West
        int frontSensor, leftSensor, rightSensor;


    // ------------------Public Functions---------------------
    
            Bot()
            {
                x = 0;
                y = 0;
                dir = 0;
            }
    
            Bot(int x, int y, int dir)
            {
                this->x = x;
                this->y = y;
                this->dir = dir;
            }
    
            void moveForward()
            {
                //mech function to move forward
                switch(dir)
                {
                    case 0:
                        y++;
                        break;
                    case 1:
                        x++;
                        break;
                    case 2:
                        y--;
                        break;
                    case 3:
                        x--;
                        break;
                }
            }

            void turnLeft()
            {
                //mech function to rotate left

                dir = (dir + 3) % 4;
            }

            void turnRight()
            {
                //mech function to rotate right

                dir = (dir + 1) % 4;
            }

            int getWallCode()
            {
                return 0;
            }
};

// ------------------Global Variables----------------------

Bot bot(0, 0, 0);




// ------------------Function Definitions------------------


// ------------------Main Function-------------------------

int main()
{
    Maze maze;
    maze.printMazeWalls();
    std::cout << std::endl;
    maze.updateWall(8,8,15);
    maze.printMazeWalls();
    std::cout << std::endl;
    maze.printMaze();
    return 0;
}


// ------------------End of Program------------------------