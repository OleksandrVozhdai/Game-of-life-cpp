#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

int rows = 100;
int columns = 100;
int cellSize = 8;
int generations = 0;

vector<vector<int>> grid(rows, vector<int>(columns, 0));

int LiveNeighbors(const vector<vector<int>>& grid, int x, int y)
{
    int count = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            int nx = x + i, ny = y + j;
            if (nx >= 0 && nx < rows && ny >= 0 && ny < columns)
            {
                count += grid[nx][ny];
            }
        }
    }
    return count;
}

void UpdateGrid(vector<vector<int>>& grid)
{
    vector<vector<int>> newGrid = grid;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int neighbors = LiveNeighbors(grid, i, j);
            if (grid[i][j] == 1)
            {
                if (neighbors < 2 || neighbors > 3)
                {   
                    newGrid[i][j] = 0;
                }  
            }
            else
            {
                if (neighbors == 3)
                {
                    newGrid[i][j] = 1;
                }
            }
        }
    }
    grid = newGrid;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(columns * cellSize, rows * cellSize), "Game Of Life (Click!)");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (mousePosition.x >= 0 && mousePosition.y >= 0 &&
            mousePosition.x < columns * cellSize && mousePosition.y < rows * cellSize) {

            int cellX = mousePosition.x / cellSize; 
            int cellY = mousePosition.y / cellSize; 

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                grid[cellY][cellX] = 1;
                grid[cellY+1][cellX] = 1;
                grid[cellY-1][cellX] = 1;
                grid[cellY][cellX+1] = 1;
                grid[cellY][cellX-1] = 1;
            }
        }
        UpdateGrid(grid);

        window.clear(sf::Color::Black);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if (grid[i][j] == 1)
                {
                    sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
                    cell.setPosition(j * cellSize, i * cellSize);
                    cell.setFillColor(sf::Color::Green);
                    window.draw(cell);
                }
            }
        }
        window.display();
        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}