#include "Labyrinth.h"
#include <fstream>
using std::ifstream;


///constructor
///complexity:Θ(rows*cols), worst case: Θ(rows*cols) , average case: Θ(rows*cols), best case: Θ(rows*cols)
Labyrinth::Labyrinth(const string &fileName)
{
    robotPosition = -1;
    rows = 0;
    cols = 0;
    ifstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file - '";
        return;
    }
    file >> rows;
    file >> cols;
    labyrinth = new char[rows*cols]; // Labyrinth is saved as a matrix on array
    int elemNr = 0;
    while (!file.eof())
    {
        char c;
        file >> c;
        // Save labyrinth as matrix on array of chars
        if (c == '*' || c == 'X' || c == 'R')
        {
            if (c == 'X')
            {
                labyrinth[elemNr] = 'X';
            }
            else if (c == 'R')
            {
                labyrinth[elemNr] = 'R';
                robotPosition = elemNr;
            }
            else if (c == '*')
            {
                if (elemNr / rows == 0) // North border
                    labyrinth[elemNr] = 'E'; //NOLINT
                else if (elemNr % cols == cols-1) // East border
                    labyrinth[elemNr] = 'E';
                else if (elemNr / cols  == rows -1) // South border
                    labyrinth[elemNr] = 'E';
                else if (elemNr % cols == 0) // West border
                    labyrinth[elemNr] = 'E';
                else
                    labyrinth[elemNr] = '*';
            }
            elemNr++;
        }
    }
}

///method for checking if a valid path exists
///complexity:O(rows*cols), worst case: Θ(rows*cols) , average case: Θ(rows*cols), best case: Θ(1)
bool Labyrinth::pathExistenceCheck()
{
    Queue bfs;
    bool found = false;
    int x, y;

    // If robot does not exist
    if (robotPosition == -1)
        return false;

    // If Robot on edge
    x = robotPosition / cols;
    y = robotPosition % cols;
    if (x == 0 || x == rows -1 || y == cols-1 || y == 0)
        found = true;

    // Mark visited position
    bool visited[rows*cols];
    for (auto& i : visited)
        i = false;

    // Start
    bfs.push(robotPosition);
    visited[robotPosition] = true;
    int current;
    while (!bfs.isEmpty() && !found)
    {
        current = bfs.pop();
        x = current / cols;
        y = current % cols;
        int north = (x-1) * cols + (y);
        int east = x * cols + (y+1);
        int south = (x+1) * cols + (y);
        int west = (x) * cols + (y-1);

        // Puts coordinates in a queue
        Queue NESW; // North, East, South, West
        NESW.push(north);
        NESW.push(east);
        NESW.push(south);
        NESW.push(west);

        // Check for the four coordinates
        while (!NESW.isEmpty())
        {
            int coordinate = NESW.pop();
            if (!visited[coordinate])
            {
                visited[coordinate] = true;
                if (labyrinth[coordinate] == '*')
                {
                    bfs.push(coordinate);
                }
                else if (labyrinth[coordinate] == 'E')
                {
                    found = true;
                }
            }
        }
    }
    return found;
}

///method for printing the labyrinth
///complexity:Θ(rows*cols), worst case: Θ(rows*cols) , average case: Θ(rows*cols), best case: Θ(rows*cols)
void Labyrinth::printLabyrinth()
{
    int elemNr = 0;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cout << labyrinth[elemNr] << ' ';
            elemNr++;
        }
        cout << endl;
    }
}

///complexity:Θ(rows*cols), worst case: Θ(rows*cols) , average case: Θ(rows*cols), best case: Θ(rows*cols)
void Labyrinth::shortestPath()
{
    Queue bfs;
    bool found = false;
    int exitPosition;
    int x, y;

    // If robot does not exist
    if (robotPosition == -1)
        return;

    // If Robot on edge
    x = robotPosition / cols;
    y = robotPosition % cols;
    if (x == 0 || x == rows -1 || y == cols-1 || y == 0)
    {
        found = true;
        exitPosition = robotPosition;
    }

    // Mark visited position
    bool visited[rows*cols];
    for (auto& i : visited)
        i = false;

    // Road back
    int parents[rows*cols];
    for (auto& child : parents)
        child = -1;

    // Start
    bfs.push(robotPosition);
    visited[robotPosition] = true;
    int current;
    while (!bfs.isEmpty() && !found)
    {
        current = bfs.pop();
        x = current / cols;
        y = current % cols;
        int north = (x-1) * cols + (y);
        int east = x * cols + (y+1);
        int south = (x+1) * cols + (y);
        int west = (x) * cols + (y-1);
        Queue NESW; // North, East, South, West
        NESW.push(north);
        NESW.push(east);
        NESW.push(south);
        NESW.push(west);
        while (!NESW.isEmpty())
        {
            int coordinate = NESW.pop();
            if (!visited[coordinate])
            {
                parents[coordinate] = current;
                visited[coordinate] = true;
                if (labyrinth[coordinate] == '*')
                {
                    bfs.push(coordinate);
                }
                else if (labyrinth[coordinate] == 'E')
                {
                    found = true;
                    exitPosition = coordinate;
                }
            }
        }
    }
    if(!found)
    {
        cout << "Es gibt keninen Pfad";
    }
    else
    {
        // Go back
        Stack s;
        current = exitPosition;
        while (current != robotPosition)
        {
            s.push(current);
            current = parents[current];
        }
        s.push(current);

        // Output the positions
        cout << "Robot starts here: " << (robotPosition / cols) << ", " << (robotPosition % cols) << " and exits the labyrinth here: " << (exitPosition / cols) << ", " << (exitPosition % cols) << endl;


        while (!s.isEmpty())
        {
            int position = s.pop();
            cout << "Position visited: " << (position / cols) << ", " << (position % cols) << endl;
        }
    }
}
///destructor
///complexity: Θ(1) worst, average and best
Labyrinth::~Labyrinth()
{
    delete[] labyrinth;
}
