// -------------------------------------------------------------------------------
// Filename:            MazeSolver.cpp
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// MazeSolver: Simulation of a mouse searching a maze for a piece of cheese.
// -------------------------------------------------------------------------------
//   _  _ ____ ___ ____   /
//   |\ | |  |  |  |___  /    AT THE MOMENT (Thursday, February 28, 2008) You
//   | \| |__|  |  |___ .     must add /FORCE:MULTIPLE to the Maze Solver
//                            Project's Linker options to avoid the LNK2005 Error!
//
// For More Info: http://msdn2.microsoft.com/en-us/library/70abkas3(vs.80).aspx
// -------------------------------------------------------------------------------

#include "maze.h"

int main()
{
    // Initialize Maze
    Maze maze;
    maze.m_solve_type = "Stack";
    maze.m_maze_loaded = false;

    // While Exit Has Not Been Chosen
    while (maze.m_menu_choice != 5)
    {
        // Display Main Menu
        maze.DisplayMenu();

        // Process Input
        switch ( maze.m_menu_choice )
        {	
            // --------------------------------------------------------------------
            // LOAD A MAZE
            // --------------------------------------------------------------------
            case 1:
            {
                // Display Maze Choice Menu
                maze.DisplayMazeMenu();
                
                switch ( maze.m_maze_choice )
                {
                    // ------------------------------------------------------------
                    // MAZE: VERTIGO
                    // ------------------------------------------------------------
                    case 0:					
                        maze.ReadMaze("MazeA1.txt", "ASCII");
                        break;

                    // ------------------------------------------------------------
                    // MAZE: ARCHON
                    // ------------------------------------------------------------
                    case 1:
                        maze.ReadMaze("MazeA2.txt", "ASCII");
                        break;

                    // ------------------------------------------------------------
                    // MAZE: DAEDALUS
                    // ------------------------------------------------------------
                    case 2:
                        maze.ReadMaze("MazeB1.txt", "BIT");
                        break;
                    
                    // ------------------------------------------------------------
                    // MAZE: ICARUS
                    // ------------------------------------------------------------		
                    case 3:
                        maze.ReadMaze("MazeB2.txt", "BIT");						
                        break;		
                    
                    // ------------------------------------------------------------
                    // MAZE: MINOS
                    // ------------------------------------------------------------
                    case 4:
                        maze.ReadMaze("MazeB3.txt", "BIT");						
                        break;						
                    
                    // ------------------------------------------------------------
                    // MAZE: KNOSSOS
                    // ------------------------------------------------------------
                    case 5:
                        maze.ReadMaze("MazeB4.txt", "BIT");					
                        break;

                    // ------------------------------------------------------------
                    // MAZE: THESEUS
                    // ------------------------------------------------------------
                    case 6:
                        maze.ReadMaze("MazeB5.txt", "BIT");
                        break;

                    // ------------------------------------------------------------
                    // DEFAULT
                    // ------------------------------------------------------------
                    default: 
                        break;
                }
            }

            // --------------------------------------------------------------------
            // TOGGLE THE SOLVE TYPE (Stack or Queue)
            // --------------------------------------------------------------------		
            case 2:					
                maze.ToggleSolveType();
                break;				
            
            // --------------------------------------------------------------------	
            // SOLVE THE MAZE
            // --------------------------------------------------------------------	
            case 3:
                maze.Solve();
        
            // --------------------------------------------------------------------	
            // PRINT THE CURRENT MAZE
            // --------------------------------------------------------------------	
            case 4:
                maze.PrintSolution();
                break;
            
            // --------------------------------------------------------------------	
            // EXIT THE PROGRAM
            // --------------------------------------------------------------------		
            case 5:
                maze.m_menu_choice = 5;
                break;
        }
    }
}