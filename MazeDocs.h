/*
// -------------------------------------------------------------------------------
// Filename:            MazeDocs.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// MazeSolver: Simulation of a mouse searching a maze for a piece of cheese.
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// DESCRIPTION
// -------------------------------------------------------------------------------
    This program simulates a mouse searching a maze for some cheese. The user is
    presented with a menu that prompts to load 1 of 5 different mazes each named
    after a famous maze oriented deity. Once a maze is selected, the user can view 
    the unsolved maze, solve the maze using either a queue or a stack, load a new 
    maze, or exit the program.

// -------------------------------------------------------------------------------
// CONTENTS
// -------------------------------------------------------------------------------

   /-------------------------------------------------------------------------------\
     Program Files
   \-------------------------------------------------------------------------------/

    MazeDocs.h
    Documentation for the Maze Solver program. You're Reading It!
    
    MazeSolver.cpp
    This is the main program. There are no functions defined in this file.

    Maze.h
    This includes the main maze classes, member function prototypes, and member 
    variables.

    Maze.cpp
    This contains most of the functions defined in Maze.h as well as menu logic
    and file i/o.

    SolveQueue.cpp
    This file implements the complete queue solving function. It is called from
    the Solve() function in Maze.cpp.

    SolveStack.cpp
    This file implements the complete stack solving function. It is called from
    the Solve() function in Maze.cpp.

    Console.h & Console.cpp
    Includes various functions for console manipulation. These include clearing 
    the screen, placing the cursor at a specific x,y coordinate, and adding
    color to text strings.

    TextColor.h
    Allows for console text coloration within the cout function by overloading the
    >> operator to include colors based on types defined in the ColorHandle class.
    
    DevCode.txt
    Contains code snippets of debug and testing code.

    DevNotes.txt
    This contains program notes including TODO items, Bugs, and other information
    about the current state of the program.
    
    MazeCheck.txt
    This is used to verify the proper coordinates in ASCII maze files.

   /---------------------\
     File: MazeA#.txt
   \---------------------/
    This filename denotes as ASCII formatted maze. This file must be in a specific
    format:

    ROW 1: X, Y Dimensions of the maze
    ROW 2: X, Y Location of the mouse
    ROW 3: X, Y Location of the cheese
    ROW 4: ASCII characters that make up the maze itself. This format allows a 
           visual approach to design of the maze. The values are designated by 
           the following:

    # - Wall 
    This character is for all walls that make up the maze.

    . - Maze Support
    This character acts as a corridor buffer so the maze can be read properly. Every 
    instance of this character is replaced by a blank space once the maze file is read 
    into the maze vector.

    M - Mouse Location
    This is a place marker. It is placed in the maze once a file has been loaded
    according to the coordinates in the maze file.
    
    C - Cheese Location
    This is a place marker. It is placed in the maze once a file has been loaded
    according to the coordinates in the maze file.

   /---------------------\
     File: MazeB#.txt
   \---------------------/
    This filename denotes as BIT formatted maze. This file must be in a specific
    format:

    ROW 1: X, Y Dimensions of the maze
    ROW 2: X, Y Location of the mouse
    ROW 3: X, Y Location of the cheese
    ROW 4: From here there are bit values representing the valid doorways for each
    given cell of the vector. These doorways create a traversable path through the 
    maze, and are stored as a representation of bits which are designated by the 
    following:

    Direction -----> NESW
    Bit Value -----> 8421
    ----------------------
    short door = 0000; // No Doors!
    short door = 0110; // Doors To The East and West

    Once this file format is read into the maze vector, it then gets converted to a
    readable maze of ASCII characters by the ReadMaze() function in Maze.cpp. This
    newly converted maze is identical to a maze in the ASCII format.

   /-------------------------------------------------------------------------------\
     CLASSES
   \-------------------------------------------------------------------------------/

   /---------------------\
    Vector: maze_vector
   \---------------------/
    This is the data structure that holds all of the maze values and marker locations.
    If the maze is represented as bits (MazeB#.txt), a maze of 3x3 rooms made up of 
    ASCII characters is constructed from the maze input file. If the input file is
    an ASCII representation (MazeA#.txt), the maze_vector is populated based on the 
    file contents.
    
    ASCII formatted mazes are constructed with the following characters:
    
    # : Wall		-> A Wall In The Maze
    . : Support		-> This separates walls in the maze to preserve spacing. They are 
                       then replaced with a space ' ' once the maze is loaded.
    
    The ASCII maze format(MazeA#.txt) must incorporate the above characters. Other 
    characters may be used to style the maze (ie - MAZEA1.TXT), but walls and supports 
    should use the characters above. Misplaced characters will most likely cause the 
    program to behave erratically or crash!
    
    During the MazeRead() and Solve() operations, the following markers are placed and 
    color coded as follows:

    M : Mouse				-> Light Gray
    C : Cheese				-> Yellow
    # : Wall				-> Dark Gray
    x : Backtrack			-> Red
    ? : Failure				-> Light Green
    . : Path of Travel		-> Light Red

   /---------------------\
    Class: MazeCell
   \---------------------/
    This class represents a room in the maze. It has the following attributes:

    char m_cell_marker	// This holds the type of marker that occupies the room.
    bool m_visited;		// Marks if the mouse has been to the room
    int m_parent_row;	// A tracking variable to determine the solution path
    int m_parent_col;	// A tracking variable to determine the solution path

   /---------------------\
    Class: CellPosition
   \---------------------/
    This class represents a position in the maze. It has the following attributes:
    
    char m_cell_marker		// This holds the type of marker at the position.
    int m_row				// X Coordinate in the maze
    int m_col				// Y Coordinate in the maze

   /---------------------\
    Class: Maze
   \---------------------/
    This is the mothership class of the program. It holds most of the information 
    used to build and keep track of the maze. It contains the following:

    Member Variables: See Below
        All of the member variable descriptions located in the Maze class below.

    Constructor: Maze
        This creates a vector of vectors where the maze will be stored as it is
        read in from the maze files.
        Big O: O(n^2)

        PreCondition: The file must be in either the specified vector or ASCII
        format.
        
    Function: ToggleSolveType
        This function determines if a stack or a queue should be employed to solve
        the maze.
    
    Function: DisplayMenu
        Displays the main program menu which allows specific option depending on
        the current state of the maze.

    Function: DisplayMazeMenu
        Displays a list of mazes to choose from. When a choice is maze the
        ReadMaze function is called and a maze is then loaded into a vector
        and transformed into an ASCII maze.

    Function: PrintSolution
        This prints out the contents of maze_vector. It then color codes each
        marker in the maze to enhance readability and coolness. 
        Big O: O(n)

        PreConditions: A maze must be loaded.

    Function: ReadMaze
        This is the main file i/o routine that reads in the maze files and
        computes them into ASCII mazes. It also sets specific maze attributes
        and accepts the option of an ASCII based maze or a BIT based maze. The
        type is denoted by an argument called 'format' which is a string called
        "ASCII" or "BIT". This format variable is CASE SENSITIVE! The actual 
        maze file is indicated by an argument called "filename".

        PreConditions: Maze must be in the specified BIT or ASCII format. The
                       proper argument "ASCII" or "BIT" must be passed with a 
                       valid filename. The format variable must be passed in
                       the proper case.

    Function: Solve
        This determines which type of solution will be employed based on the
        state of m_solve_type. m_solve_type is manipulated via the main menu by
        invoking the ToggleSolveType function. Solutions can be vastly different
        depending on the paths in the maze. In rare instances, larger maps may
        produce a faild effort even when valid moves still exist. If the maze
        cannot be solved a '?' marker is placed where the mouse decide to quit.

        PreConditions: A maze must be loaded and unsolved.

    Function: SolveStack
        This invokes the stack based solution of the maze located in SolveStack.cpp
        Big O: O(n)

        PreConditions: A maze must be loaded, unsolved, and stack chosen from menu.

    Function: SolveQueue
        This invokes the queue based solution of the maze located in SolveQueue.cpp
        Big O: O(n)

        PreConditions: A maze must be loaded, unsolved, and queue chosen from menu.

// -------------------------------------------------------------------------------
*/