//-------------------MAZE SOLVER PROGRAM-------------------
//Made by : Paras Roy [https:github.com/paras-roy]
//Date of creation : 16/05/2023
//Work done under : Team Kalpana, NSUT

// ------------------Header Files--------------------------

#include <iostream>
#include <queue>

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
            //inititalize all cells
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

        void updateWall(int x, int y, int wallCode)
        {
            //add new walls to current cell
            cells[x][y].setWallCode(cells[x][y].wallCode | wallCode);

            if((wallCode & 1) == 1)
            {
                if(x-1>=0)
                {
                    //add wall to adjacent cell
                    cells[x-1][y].setWallCode(cells[x-1][y].wallCode | 4);
                }
            }

            if((wallCode & 2) == 2)
            {
                if(y+1<=15)
                {
                    //add wall to adjacent cell
                    cells[x][y+1].setWallCode(cells[x][y+1].wallCode | 8);
                }
            }

            if((wallCode & 4) == 4)
            {
                if(x+1<=15)
                {
                    //add wall to adjacent cell
                    cells[x+1][y].setWallCode(cells[x+1][y].wallCode | 1);
                }
            }

            if((wallCode & 8) == 8)
            {
                if(y-1>=0)
                {
                    //add wall to adjacent cell
                    cells[x][y-1].setWallCode(cells[x][y-1].wallCode | 2);
                }
            }
        }

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
                    std::cout << " ";
                    std::cout << cells[i][j].dist;
                    if(cells[i][j].dist < 10)
                    {
                        std::cout << " ";
                    }
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
        
        void floodFill()
        {
            bool visited[16][16] = {false};
            std::queue<Cell> q;

            floodFillHelper(7, 7, visited, q, 0);
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    visited[i][j] = false;
                }
            }
            floodFillHelper(7, 8, visited, q, 0);
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    visited[i][j] = false;
                }
            }
            floodFillHelper(8, 7, visited, q, 0);
            for(int i = 0; i < 16; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    visited[i][j] = false;
                }
            }
            floodFillHelper(8, 8, visited, q, 0);
        }

        void floodFillHelper(int x, int y, bool visited[16][16], std::queue<Cell> q, int distance)
        {
            visited[x][y] = true;
            cells[x][y].setDist(distance);
            q.push(cells[x][y]);

            while(!q.empty())
            {
                Cell current = q.front();
                q.pop();

                if((current.wallCode & 1) == 0)
                {
                    if(current.x-1 >= 0)
                    {
                        if(!visited[current.x-1][current.y])
                        {
                            visited[current.x-1][current.y] = true;
                            cells[current.x-1][current.y].setDist(std::min(current.dist+1, cells[current.x-1][current.y].dist));
                            q.push(cells[current.x-1][current.y]);
                        }
                    }
                }
                
                if((current.wallCode & 2) == 0)
                {
                    if(current.y+1 <= 15)
                    {
                        if(!visited[current.x][current.y+1])
                        {
                            visited[current.x][current.y+1] = true;
                            cells[current.x][current.y+1].setDist(std::min(current.dist+1, cells[current.x][current.y+1].dist));
                            q.push(cells[current.x][current.y+1]);
                        }
                    }
                }

                if((current.wallCode & 4) == 0)
                {
                    if(current.x+1 <= 15)
                    {
                        if(!visited[current.x+1][current.y])
                        {
                            visited[current.x+1][current.y] = true;
                            cells[current.x+1][current.y].setDist(std::min(current.dist+1, cells[current.x+1][current.y].dist));
                            q.push(cells[current.x+1][current.y]);
                        }
                    }
                }

                if((current.wallCode & 8) == 0)
                {
                    if(current.y-1 >= 0)
                    {
                        if(!visited[current.x][current.y-1])
                        {
                            visited[current.x][current.y-1] = true;
                            cells[current.x][current.y-1].setDist(std::min(current.dist+1, cells[current.x][current.y-1].dist));
                            q.push(cells[current.x][current.y-1]);
                        }
                    }
                }


            }

        }
        
        void printMazeWallCode()
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




// ------------------Function Definitions------------------


// ------------------Main Function-------------------------

int main()
{
    Maze maze;
    maze.updateWall(0,0,2);
    maze.updateWall(1,0,2);
    maze.updateWall(2,0,2);
    maze.updateWall(3,0,2);
    maze.updateWall(4,0,4);
    maze.updateWall(4,1,5);
    maze.updateWall(4,2,5);
    maze.updateWall(4,3,5);
    maze.updateWall(4,4,5);
    maze.updateWall(4,5,6);
    maze.updateWall(3,5,10);
    maze.updateWall(2,5,10);
    maze.updateWall(1,5,9);
    maze.updateWall(1,6,5);
    maze.updateWall(1,7,5);
    maze.updateWall(1,8,3);
    maze.updateWall(2,8,10);
    maze.floodFill();
    // maze.printMaze();
    maze.printMaze();
    std::cout << std::endl;
    maze.printMazeWallCode();
    return 0;
}


// ------------------End of Program------------------------

