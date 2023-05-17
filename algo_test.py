class Cell:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        #wallcode is a 4 bit binary number where the first bit is the north wall, second is east, third is south, and fourth is west
        self.wallCode = 0
        self.distance = 255
        self.id = 0
        
    def setWall(self, wall):
        self.wallCode = wall

    def setDistance(self, distance):
        self.distance = distance

    def createID(self, width, height):
        self.id = self.x + self.y * width
    
class Maze:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.cells = []
        for i in range(width):
            self.cells.append([])
            for j in range(height):
                self.cells[i].append(Cell(i, j))
                self.cells[i][j].createID(width, height)
        

    
    def setWall(self, x, y, wall):
        #set the wall of the cell at x, y to the wall code and also handle the walls of the adjacent cells
        self.cells[x][y].setWall(wall)
        if wall & 1 == 1:
            if(y-1 >= 0):
                self.cells[x][y-1].setWall(self.cells[x][y-1].wallCode | 4)
        if wall & 2 == 2:
            if(x+1 < self.width):
                self.cells[x+1][y].setWall(self.cells[x+1][y].wallCode | 8)
        if wall & 4 == 4:
            if(y+1 < self.height):
                self.cells[x][y+1].setWall(self.cells[x][y+1].wallCode | 1)
        if wall & 8 == 8:
            if(x-1 >= 0):
                self.cells[x-1][y].setWall(self.cells[x-1][y].wallCode | 2)

    
    def setDistance(self, x, y, distance):
        self.cells[x][y].setDistance(distance)

    def getAccessibleCells(self, x, y):
        accessibleCells = []
        if self.cells[x][y].wallCode & 1 == 0:
            if(y-1 >= 0):
                accessibleCells.append(self.cells[x][y-1])
        if self.cells[x][y].wallCode & 2 == 0:
            if(x+1 < self.width):
                accessibleCells.append(self.cells[x+1][y])
        if self.cells[x][y].wallCode & 4 == 0:
            if(y+1 < self.height):
                accessibleCells.append(self.cells[x][y+1])
        if self.cells[x][y].wallCode & 8 == 0:
            if(x-1 >= 0):
                accessibleCells.append(self.cells[x-1][y])
        return accessibleCells
    
    def floodFill(self, x, y):
        visited = []
        queue = []
        for i in range(self.width):
            visited.append([])
            for j in range(self.height):
                visited[i].append(False)
        self.floodFillHelper(x, y, visited, queue, 0)

    def floodFillHelper(self, x, y, visited, queue, distance):
        #standard BFS algorithm
        visited[x][y] = True
        self.cells[x][y].setDistance(distance)
        queue.append(self.cells[x][y])
        while len(queue) > 0:
            currentCell = queue.pop(0)
            accessibleCells = self.getAccessibleCells(currentCell.x, currentCell.y)
            for cell in accessibleCells:
                if visited[cell.x][cell.y] == False:
                    visited[cell.x][cell.y] = True
                    cell.setDistance(currentCell.distance + 1)
                    queue.append(cell)

    def floodFillHere(self, x, y):
        #add current cell to queue
        queue = []
        queue.append(self.cells[x][y])
        #while queue is not empty
        while len(queue) > 0:
            #pop first cell in queue
            firstCell = queue.pop(0)
            #get accessible cells
            accessibleCells = self.getAccessibleCells(firstCell.x, firstCell.y)
            #get minimum distance of accessible cells
            minDistance = 255
            for cell in accessibleCells:
                if cell.distance < minDistance:
                    minDistance = cell.distance
            #if first cell distance is less than or equal to minimum distance of accessible cells
            if firstCell.distance <= minDistance:
                #set first cell distance to minimum distance of accessible cells + 1
                firstCell.setDistance(minDistance + 1)
                #add accessible cells to queue
                for cell in accessibleCells:
                    queue.append(cell)
            #else
            #nothing

    
    def printCellID(self, x, y):
        print("Cell ID at " + str(x) + ", " + str(y) + ": " + str(self.cells[x][y].id))

    def printMazeByID(self):
        print("ID Maze")
        for i in range(self.height):
            for j in range(self.width):
                print(self.cells[j][i].id, end = " ")
            print()

    def printMazeByWall(self):
        print("Wall Maze")
        for i in range(self.height):
            for j in range(self.width):
                print(self.cells[j][i].wallCode, end = " ")
            print()

    def printFloodMaze(self):
        print("Flood Maze")
        for i in range(self.height):
            for j in range(self.width):
                print(self.cells[j][i].distance, end = " ")
            print()


maze = Maze(5, 5)
maze.printMazeByID()
maze.floodFill(2,2) 
print()
maze.printFloodMaze()
print()
maze.floodFill(2,2)
maze.setWall(0, 4, 14)
maze.setWall(0, 3, 10)
maze.setWall(0, 2, 1)
maze.setWall(1, 2, 2)

maze.printMazeByWall()
print()
maze.floodFill(2, 2)
maze.printFloodMaze()

#graphical representation of maze
# 0  1  2  3  4
# 5  6  7  8  9

import pygame
pygame.init()

screen = pygame.display.set_mode((500, 500))
pygame.display.set_caption("Maze")

running = True
while running:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    for i in range(maze.height):
        for j in range(maze.width):
            if maze.cells[j][i].wallCode & 1 == 1:
                pygame.draw.line(screen, (255, 255, 255), (j*100, i*100), (j*100 + 100, i*100))
            if maze.cells[j][i].wallCode & 2 == 2:
                pygame.draw.line(screen, (255, 255, 255), (j*100 + 100, i*100), (j*100 + 100, i*100 + 100))
            if maze.cells[j][i].wallCode & 4 == 4:
                pygame.draw.line(screen, (255, 255, 255), (j*100, i*100 + 100), (j*100 + 100, i*100 + 100))
            if maze.cells[j][i].wallCode & 8 == 8:
                pygame.draw.line(screen, (255, 255, 255), (j*100, i*100), (j*100, i*100 + 100))
            font = pygame.font.SysFont('Arial', 30)
            text = font.render(str(maze.cells[j][i].distance), True, (255, 255, 255))
            screen.blit(text, (j*100 + 30, i*100 + 30))

    pygame.display.update()

pygame.quit()
