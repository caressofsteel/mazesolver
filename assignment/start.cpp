#include <string>
typedef struct
{
    short int doorEncoding; // Range 0..15.
            // north = doorEncoding & 0x01
            // east  = doorEncoding & 0x02
            // south = doorEncoding & 0x04
            // west  = doorEncoding & 0x08
            // Note that the result of these operations is not
            // necessarily 1, but some non-zero value if there
            // is in that particular direction. 0 else.
    bool      visited;
    int       parentRow;
    int       parentCol;
    char      direction; // From parent.
} MazeCell;




typedef struct
{
    int row;
    int col;
} CellPosition; // useful as StackItem or QueueItem.






class Maze
{
public:
    Maze(const string& fileName); // Load from file.
    void Solve(); // Solve the maze.
    void PrintSolution();
private:
    vector<vector<MazeCell> > maze; // maze square
    int rows;                        // number of rows
    int cols;                        // number of columns
    int mouseRow;                    // row position of mouse
    int mouseCol;                    // col position of mouse
    int cheeseRow;                   // row position of cheese
    int cheeseCol;                   // col position of cheese
    int squaresVisited;
}; 

Maze::Maze(const string& fileName):
            maze(0),   // init maze
            rows(0),
            cols(0),
            mouseRow(0),
            mouseCol(0),
            cheeseRow(0),
            cheeseCol(0),
            squaresVisited(0)
{
    // declare variable to open file etc.
    // read m and n and init rows and cols.
        // read and init mouse and cheese positions.
    // Now we know the size of maze. let us init.
    // Reserve space for rows (= n) many rows.
    maze.reserve(n);
    // reserve space for cols (= n) many columns in each row.
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        maze[rowNum].reserve(cols);
    }
    // Now we can use maze[0][0] ... maze[n-1][m-1].
    // Read and initialize all the cells.
} 

