// -------------------------------------------------------------------------------
// Filename:            Maze.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// MazeSolver: Simulates a mouse searching through a maze for some cheese.
// -------------------------------------------------------------------------------

#ifndef MAZE_H_
#define MAZE_H_

// #define DEBUG

#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

// Documentation Located In MazeDocs.h
#include "MazeDocs.h"

using namespace std;

// -------------------------------------------------------------------------------
// MazeCell: Represents A Room In The Maze
// -------------------------------------------------------------------------------
class MazeCell
{
    public:
        char m_cell_marker;
        bool m_visited;
        int m_parent_row;
        int m_parent_col;
};


// -------------------------------------------------------------------------------
// Cell Position: X(Row), Y(Col) Coordinates In The Maze
// -------------------------------------------------------------------------------
class CellPosition
{
    public:
        char m_cell_marker;
        int m_row;
        int m_col;
};


// -------------------------------------------------------------------------------
//	Maze Class
// -------------------------------------------------------------------------------
class Maze
{
    public:

        // Member Variables
        // -------------------
        int m_menu_choice;								// Option Choice
        int m_maze_choice;								// Maze Choice
        int m_maze_rows;								// Maze Rows
        int m_maze_cols;								// Maze Columns
        int m_mouse_row;								// Mouse Row Position
        int m_mouse_col;								// Mouse Col Position
        int m_cheese_row;								// Cheese Row Position
        int m_cheese_col;								// Cheese Col Position
        int m_moves_to_goal;							// Moves To Reach Goal			
        bool m_maze_solved;								// Is The Maze Solved?
        bool m_maze_loaded;								// Is The Maze Loaded?
        bool m_maze_not_solvable;						// Can The Maze Be Solved?
        string m_maze_name;								// Name Of The Maze
        string m_maze_type;								// Type Of Maze (ASCII or BIT)
        string m_solve_type;							// Solve With A? (Stack/Queue)

        // Member Functions
        // -------------------
        void ToggleSolveType();											// Toggle Solve Type (Stack/Queue)
        void DisplayMenu();												// Display User Menu
        void DisplayMazeMenu();											// Display Maze Menu
        void PrintSolution();											// Print Maze/Solution
        void ReadMaze(const string& filename, const string& format);	// Read Maze
        void Solve();													// Solve The Maze
        void SolveStack();												// Use A Stack Solve
        void SolveQueue();												// Use A Queue Solve

    private:

        // Member Classes
        // -------------------
        CellPosition position;						// Maze Position
        vector<vector<MazeCell> > maze_vector;		// Maze Room
        vector<CellPosition> mouse_moves;
};

#endif