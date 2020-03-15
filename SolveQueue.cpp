// -------------------------------------------------------------------------------
// Filename:            SolveQueue.cpp
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// MazeSolver: Simulation of a mouse searching a maze for a piece of cheese.
// -------------------------------------------------------------------------------

#include <queue>

#include "maze.h"
#include "console.h"
#include "textcolor.h"

void Maze::SolveQueue()
{
    // If Maze Is Loaded
    if (m_maze_loaded == true)
    {
        // And Maze Has Not Been Solved
        if (m_maze_solved == false)
        {
            // Set Maze State
            m_maze_not_solvable = false;
            
            // Initialize The Stack To Track The Mouse's Movement
            queue<CellPosition> moves;

            // Add Starting Position To The Stack
            moves.push(position);
            
            // Set Parent Row/Col To -1. This Acts As A Sentinel. 
            if (m_maze_type == "BIT")
            {
                maze_vector[(m_mouse_row * 2) + 1][(m_mouse_col * 2) + 1].m_parent_row = -1;
                maze_vector[(m_mouse_row * 2) + 1][(m_mouse_col * 2) + 1].m_parent_col = -1;
            }
            else
            {
                // ASCII
                maze_vector[m_mouse_row][m_mouse_col].m_parent_row = -1;
                maze_vector[m_mouse_row][m_mouse_col].m_parent_col = -1;
            }

            // While The Mouse Has Not Located The Cheese, Keep Trying To Solve The Maze
            while(position.m_cell_marker != 'C' && !m_maze_not_solvable)
            {
                // Check For A Doorway In The Maze. If A Door Is Found, Mark The Current Position
                // Set Current Marker To Next Rooms Marker, Move The Mouse Into The Next Room, 
                // Add That Move To The Stack, Increment Moves, Set The Parent Row/Col To The Previous 
                // Room, And Mark The Current Room Visited.
                            
                // Look NORTH
                if(maze_vector[position.m_row - 1][position.m_col].m_cell_marker != '#' 
                &&  maze_vector[position.m_row - 1][position.m_col].m_visited != true)
                {
                    // Mark Current Position
                    maze_vector[position.m_row][position.m_col].m_cell_marker = 'x';
                    
                    // Set Current Cell Marker To New Position Cell Marker (Should Be A Blank)
                    position.m_cell_marker = maze_vector[position.m_row - 1][position.m_col].m_cell_marker;
                    
                    // Move Mouse To New Position
                    position.m_row -= 1;
                    
                    // Push New Position On Stack
                    moves.push(position);
                    
                    // Increment Moves To Goal
                    m_moves_to_goal++;
                    
                    // Set Parent Row To Mouse's Previous Row				
                    maze_vector[position.m_row][position.m_col].m_parent_row = position.m_row + 1;
                    
                    // Set Parent Col To Mouse's Previous Col					
                    maze_vector[position.m_row][position.m_col].m_parent_col = position.m_col;
                    
                    // Mark Current Position As Visited
                    maze_vector[position.m_row][position.m_col].m_visited = true;
                }
                
                // Look EAST
                else if(maze_vector[position.m_row][position.m_col + 1].m_cell_marker != '#' 
                     && maze_vector[position.m_row][position.m_col + 1].m_visited != true)
                {	
                    maze_vector[position.m_row][position.m_col].m_cell_marker = 'x';
                    position.m_cell_marker = maze_vector[position.m_row][position.m_col + 1].m_cell_marker;
                    position.m_col += 1;
                    moves.push(position);
                    m_moves_to_goal++;
                    maze_vector[position.m_row][position.m_col].m_parent_row = position.m_row;
                    maze_vector[position.m_row][position.m_col].m_parent_col = position.m_col - 1;
                    maze_vector[position.m_row][position.m_col].m_visited = true;
                }

                // Look SOUTH
                else if(maze_vector[position.m_row + 1][position.m_col].m_cell_marker != '#' 
                     && maze_vector[position.m_row + 1][position.m_col].m_visited != true)
                {	
                    maze_vector[position.m_row][position.m_col].m_cell_marker = 'x';
                    position.m_cell_marker = maze_vector[position.m_row + 1][position.m_col].m_cell_marker;
                    position.m_row += 1;
                    moves.push(position);
                    m_moves_to_goal++;
                    maze_vector[position.m_row][position.m_col].m_parent_row = position.m_row - 1;
                    maze_vector[position.m_row][position.m_col].m_parent_col = position.m_col;
                    maze_vector[position.m_row][position.m_col].m_visited = true;
                }

                // Look WEST
                else if(maze_vector[position.m_row][position.m_col - 1].m_cell_marker != '#' 
                     && maze_vector[position.m_row][position.m_col - 1].m_visited != true)
                {	
                    maze_vector[position.m_row][position.m_col].m_cell_marker = 'x';
                    position.m_cell_marker = maze_vector[position.m_row][position.m_col - 1].m_cell_marker;
                    position.m_col -= 1;
                    moves.push(position);
                    m_moves_to_goal++;
                    maze_vector[position.m_row][position.m_col].m_parent_row = position.m_row;
                    maze_vector[position.m_row][position.m_col].m_parent_col = position.m_col + 1;
                    maze_vector[position.m_row][position.m_col].m_visited = true;
                }

                // If The Stack Is Empty The Maze Cannot Be Solved
                else if(moves.empty())
                {
                    // Flag Maze As Unsolvable
                    m_maze_not_solvable = true;
                    
                    // Mark Point Of Failure
                    maze_vector[position.m_row][position.m_col].m_cell_marker = '?';
                }

                // If There Is No Valid Move, Pop Moves From The Stack, Add BackTrack Marker,
                // And Arrive At Location Of A Valid Move.
                else
                {
                    maze_vector[position.m_row][position.m_col].m_cell_marker = 'x';
                    position = moves.front();
                    moves.pop();
                }
            }

            // Flag Maze As Solved
            if(!m_maze_not_solvable)
            {
                m_maze_solved = true;
            }
        }
    }
}