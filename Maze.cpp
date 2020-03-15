// -------------------------------------------------------------------------------
// Filename:            Maze.h
// Author:              David Rodgers
// Course:              CS3424 :: Briana Morrison :: Spring 2008
// Assignment Number:   02
// Due Date:            February 28, 2008 @ 11:59:59pm
// -------------------------------------------------------------------------------
// MazeSolver: Simulation of a mouse searching a maze for a piece of cheese.
// -------------------------------------------------------------------------------

#include "maze.h"
#include "console.h"
#include "textcolor.h"

// -------------------------------------------------------------------------------
// DISPLAY PROGRAM MENU
// -------------------------------------------------------------------------------
void Maze::DisplayMenu()
{
		// Set Menu State
		m_menu_choice = 0; 

		// Clear Screen/Input
		ClearScreen();
		cin.clear();
		
		// Display Menu
		SetColor(2);
		cout << LIGHTGREEN  << "Maze Solver" << WHITE << " :: " 
			 << LIGHTGREEN  << "David Rodgers" << WHITE << " :: " 
			 << LIGHTGREEN  << "CS3424" << WHITE << " :: " 
			 << LIGHTGREEN  << "2/28/2008" << endl;
		cout << LIGHTGRAY	<< "---------------------------------------------------" << endl;		
		cout << LIGHTCYAN	<< "["<< WHITE << "1" << LIGHTCYAN << "]: Load A Maze" << endl;

		// If The Maze Is Loaded and Solved, Limit Options
		if (m_maze_loaded == true && m_maze_solved == true)
		{
			cout			<< "["<< WHITE << "4" << LIGHTCYAN << "]: View The Solved Maze (" 
							<< WHITE << m_maze_name << LIGHTCYAN << ")" << endl;
		}
		
		// Otherwise If Loaded And Unsolved, Add Options
		else if (m_maze_loaded == true && m_maze_solved == false && m_maze_not_solvable == false)
		{
			cout			<< "["<< WHITE << "2" << LIGHTCYAN << "]: Toggle Solve Type (" 
							<< WHITE << m_solve_type << LIGHTCYAN << ")" << endl;
			cout			<< "["<< WHITE << "3" << LIGHTCYAN << "]: Solve The Maze" << endl;
			cout			<< "["<< WHITE << "4" << LIGHTCYAN << "]: View The Unsolved Maze (" 
							<< WHITE << m_maze_name << LIGHTCYAN << ")" << endl;

		}
		
		// Otherwise If Loaded And Unsolvable, Limit Options
		else if (m_maze_loaded == true && m_maze_not_solvable == true)
		{
			cout			<< "["<< WHITE << "4" << LIGHTCYAN << "]: View The Unsolvable Maze (" 
							<< WHITE << m_maze_name << LIGHTCYAN << ")" << endl;
		}

		cout				<< "["<< WHITE << "5" << LIGHTCYAN << "]: Exit" << endl;
		cout << LIGHTGRAY	<< "---------------------------------------------------" << endl;
		cout << LIGHTGREEN	<< "Enter Choice" << WHITE << ": ";
		
		// Validate Input
		while(!(cin >> m_menu_choice))						// As Long As cin Is A Valid Choice
		{
			cin.clear();									// Clear failed flag
			while(cin.get() != '\n'){}						// Clean Input Stream
			cout << "Enter Choice: ";						// Re-Prompt
		}
}


// -------------------------------------------------------------------------------
// DISPLAY MAZE CHOICE MENU
// -------------------------------------------------------------------------------
void Maze::DisplayMazeMenu()
{
		// Set Menu State
		m_maze_choice = 0; 

		// Clear Screen/Input
		ClearScreen();
		cin.clear();
		
		// Display Menu
		SetColor(2);
		cout << LIGHTGREEN << "Maze Solver" << WHITE << " :: " 
			 << LIGHTGREEN << "David Rodgers" << WHITE << " :: " 
			 << LIGHTGREEN << "CS3424" << WHITE << " :: " 
			 << LIGHTGREEN << "2/28/2008" << endl;
		cout << LIGHTGRAY	<< "---------------------------------------------------" << endl;		
		cout << YELLOW		<< "Choose A Maze To Load" << endl;
		cout << LIGHTGRAY	<< "---------------------------------------------------" << endl;
		cout << LIGHTCYAN	<< "["<< WHITE << "0" << LIGHTCYAN << "]: Vertigo"  << endl
							<< "["<< WHITE << "1" << LIGHTCYAN << "]: Archon"   << endl
							<< "["<< WHITE << "2" << LIGHTCYAN << "]: Daedalus" << endl
							<< "["<< WHITE << "3" << LIGHTCYAN << "]: Icarus"   << endl
							<< "["<< WHITE << "4" << LIGHTCYAN << "]: Minos"    << endl
							<< "["<< WHITE << "5" << LIGHTCYAN << "]: Knossos"  << endl
							<< "["<< WHITE << "6" << LIGHTCYAN << "]: Theseus"  << endl;
		cout << LIGHTGRAY	<< "---------------------------------------------------" << endl;
		cout << LIGHTGREEN	<< "Enter Choice" << WHITE << ": ";
		
		// Validate Input
		while(!(cin >> m_maze_choice))						// As Long As cin Is A Valid Choice
		{
			cin.clear();									// Clear failed flag
			while(cin.get() != '\n'){}						// Clean Input Stream
			cout << LIGHTGREEN << "Enter Choice: ";			// Re-Prompt
		}
}

// -------------------------------------------------------------------------------
// TOGGLE SOLVE TYPE (Stack or Queue)
// -------------------------------------------------------------------------------
void Maze::ToggleSolveType()
{
	// If No Maze Loaded...
	if (m_maze_loaded == false)
	{
		cout << LIGHTRED << "\nYou Need To Load A Maze First!\n\n";
		SetColor(2);
		system("pause");
	}
	
	// Otherwise Toggle Solve Type
	else
	{
		if (m_solve_type == "Stack")
		{ 
			m_solve_type = "Queue"; 
		}
		else
		{ 
			m_solve_type = "Stack"; 
		}
	}
}

// -------------------------------------------------------------------------------
// READ A BIT OR ASCII MAZE FORMAT
// -------------------------------------------------------------------------------
void Maze::ReadMaze(const string& fileName, const string& format)
{	
	// Set Maze State
	maze_vector.clear();
	m_maze_cols = 0;
	m_maze_rows = 0;
	m_mouse_row = 0;
	m_mouse_col = 0;
	m_cheese_row = 0;
	m_cheese_col = 0;
	m_moves_to_goal = 0;
	m_maze_loaded = false;
	m_maze_solved = false;
	m_maze_not_solvable = false;

	// Set Maze Format (ASCII || BIT)
	m_maze_type = format;

	// Create A File Object
	ifstream file;
	
	// Clear File Object
	file.clear();

	// Open Maze File
	file.open(fileName.c_str());

	// If File Does Not Exist
	if (!file) 
	{ 
		// Print Error And Exit!
		SetColor(1);
		cerr << "\nERROR: File Can't Be Opened! Exiting!" << endl; 
		system("pause"); 
		exit(0); 
	} 

	// If File Exists, Read Name And Dimensions
	file >> m_maze_name;
	file >> m_maze_rows >> m_maze_cols;
	file >> m_mouse_row >> m_mouse_col;
	file >> m_cheese_row >> m_cheese_col;

	// If m_maze_type Is BIT We Need To Transform Maze Into ASCII
	if (m_maze_type == "BIT")
	{
		// Recompute The Maze Into A New Format of 3x3 Rooms.
		// Each Room Is Made Up Of 9 ASCII Characters. This Is 
		// Done By Taking The Initial Dimensions, Multiplying By 
		// Two, and Adding 1 As An Offset. This Effectively Creates 
		// 3x3 Rooms For Each Cell In The Maze Vector.
		m_maze_rows = (m_maze_rows * 2) + 1;
		m_maze_cols = (m_maze_cols * 2) + 1;
	}

	// Resize Maze Vector
	maze_vector.resize(m_maze_rows);
	for (int row = 0; row < m_maze_rows; row++)
	{
		maze_vector[row].resize(m_maze_cols);
	}

	// --------------------------------------------------------------
	// If The Maze Is An ASCII Maze
	// --------------------------------------------------------------
	if (m_maze_type == "ASCII")
	{	
		// Populate maze_vector
		for (int row = 0; row < m_maze_rows; row++)
		{
			for (int col = 0; col < m_maze_cols; col++)
			{
				file >> maze_vector[row][col].m_cell_marker;			
			}
		}
		
		// Replace ASCII Maze Supports '.'
		for (int row = 0; row < m_maze_rows; row++)
		{
			for (int col = 0; col < m_maze_cols; col++)
			{
				if (maze_vector[row][col].m_cell_marker == '.')
				{
					maze_vector[row][col].m_cell_marker = ' ';
				}
			}
		}	
		
		// Assign Start Location
		maze_vector[m_mouse_row - 1][m_mouse_col - 1].m_cell_marker = 'M';
	
		// Assign Cheese Location
		maze_vector[m_cheese_row - 1][m_cheese_col - 1].m_cell_marker = 'C';

		// Set The Start Position To The Mouse Position, 
		position.m_row = m_mouse_row;
		position.m_col = m_mouse_col;
	}		
	
	
	// --------------------------------------------------------------
	// If The Maze Is A BIT Maze
	// --------------------------------------------------------------
	if (m_maze_type == "BIT")
	{
		// Fill The Entire Maze Vector With Wall Characters
		for (int row = 0; row < m_maze_rows; row++)
		{
			for (int col = 0; col < m_maze_cols; col++)
			{
				maze_vector[row][col].m_cell_marker = '#';
			}
		}
	
		// For Each 3x3 Room Of The Maze, Start In The Center And Erase The 
		// Walls Corresponding To The BIT value. 
		for (int row = 1; row < m_maze_rows; row = row + 2)
		{
			for (int col = 1; col < m_maze_cols; col = col + 2)
			{
				// This Variable Reads The BIT Value From The Maze File 
				// Into A Temporary Variable. No Need To Store It Since 
				// We Only Use It During Conversion.
				short int temp;
				file >> temp;
				
				// If Our Current Location Is Not 0, Process It As A Valid
				// Maze Location.
				if(temp != 0)
				{
					maze_vector[row][col].m_cell_marker = ' ';
				}
				
				// For Every Wall Indicated By BIT Value, Erase It
				// Within The Maze Vector. This Creates The Path Of
				// Travel Within The Maze.
				
				// Wall To The North
				if((temp - 8) >= 0)
				{	
					maze_vector[row - 1][col].m_cell_marker = ' ';
					temp = temp - 8;
				}

				// Wall To The East
				if((temp - 4) >= 0)
				{	
					maze_vector[row][col + 1].m_cell_marker = ' ';
					temp = temp - 4;
				}

				// Wall To The South
				if((temp - 2) >= 0)
				{	
					maze_vector[row + 1][col].m_cell_marker = ' ';
					temp = temp - 2;
				}
				
				// Wall To The West
				if((temp - 1) >= 0)
				{	
					maze_vector[row][col - 1].m_cell_marker = ' ';
					temp = temp - 1;
				}
			} 
		}
		
		// Assign Start Location
		maze_vector[(m_mouse_row * 2) + 1][(m_mouse_col * 2) + 1].m_cell_marker = 'M';
	
		// Assign Cheese Location
		maze_vector[(m_cheese_row * 2) + 1][(m_cheese_col * 2) + 1].m_cell_marker = 'C';

		// Set The Start Position To The Mouse Position, 
		position.m_row = (m_mouse_row * 2) + 1;
		position.m_col = (m_mouse_col * 2) + 1;
	}
	
	// Close The File
	file.close();

	// Mark Start/Mouse Position As Visited
	maze_vector[position.m_row][position.m_col].m_visited = true;

	// Successfully Loaded The Maze
	m_maze_loaded = true;

	// Reset Cell Marker To An Unused Character
	position.m_cell_marker = '$';

	// Display The Maze
	PrintSolution();
}

// -------------------------------------------------------------------------------
// SOLVE THE MAZE
// -------------------------------------------------------------------------------
void Maze::Solve()
{
	if (m_solve_type == "Stack")
	{ 
		SolveStack(); 
	}
	else
	{ 
		SolveQueue(); 
	}
}

// -------------------------------------------------------------------------------
// PRINT MAZE/SOLUTION
// -------------------------------------------------------------------------------
void Maze::PrintSolution()
{
	
	// -------------------------------------------\
	// If No Maze Is Loaded...
	// -------------------------------------------/
	if (m_maze_loaded == false)
	{
		cout << LIGHTRED << "\nYou Need To Load A Maze First!\n\n";
		SetColor(2);
		system("pause");
	}
	
	// -------------------------------------------\
	// Otherwise Print The Current Maze (Unsolved)
	// -------------------------------------------/
	else if (m_maze_loaded == true && m_maze_solved == false)
	{
		if (m_maze_type == "ASCII")
		{
			// Print ASCII Maze Information
			cout << WHITE << "\nMaze: " << LIGHTGREEN << m_maze_name << WHITE 
				 << " Type: " << LIGHTGREEN << m_maze_type << WHITE 
				 << " Dimensions: " << LIGHTGREEN << m_maze_rows << "x" 
				 << m_maze_cols << "\n";
			
			// Print ASCII Mouse/Cheese Coordinates
			cout << WHITE << "Mouse At: " << LIGHTGREEN << m_mouse_row 
				 << WHITE << "," << LIGHTGREEN << m_mouse_col << WHITE 
				 << " Cheese At: " << LIGHTGREEN << m_cheese_row << WHITE 
				 << "," << LIGHTGREEN << m_cheese_col << "\n\n";
		}
		else
		{
			// Print Vector Maze Information
			cout << WHITE << "\nMaze: " << LIGHTGREEN << m_maze_name << WHITE 
				 << " Type: " << LIGHTGREEN << m_maze_type << WHITE 
				 << " Dimensions: " << LIGHTGREEN << m_maze_rows << "x" 
				 << m_maze_cols << "\n";
			
			// Print Vector Mouse/Cheese Coordinates
			cout << WHITE << "Mouse At: " << LIGHTGREEN << (m_mouse_row * 2 + 2) 
				 << WHITE << "," << LIGHTGREEN << (m_mouse_col * 2 + 2) << WHITE 
				 << " Cheese At: " << LIGHTGREEN << (m_cheese_row * 2 + 2) 
				 << WHITE << "," << LIGHTGREEN << (m_cheese_col * 2 + 2) << "\n\n";
		}

		// Is The Maze Unsolvable?
		if(m_maze_not_solvable == true)
		{
			cout << LIGHTRED << "Found No Solution In " << WHITE << m_moves_to_goal 
				 << LIGHTRED << " Using A " << WHITE << m_solve_type << LIGHTRED 
				 << "! Fire The Architect!\n" << endl;
		}	

		// Populate Maze Vector And Color Cell Markers
		for (int row = 0; row < m_maze_rows; row++)
		{
			for (int col = 0; col < m_maze_cols; col++)
			{
				
				// Color Path Of Travel Marker
				if (maze_vector[row][col].m_cell_marker == '.')
				{ 
					cout << LIGHTRED; 
				}
		
				// Color Point Of Failure Marker
				else if (maze_vector[row][col].m_cell_marker == '?')
				{ 
					cout << LIGHTGREEN;
				}

				// Color Backtrack Marker
				else if (maze_vector[row][col].m_cell_marker == 'x')
				{ 
					cout << RED; 
				}
				
				// Color Mouse Marker
				else if (maze_vector[row][col].m_cell_marker == 'M')
				{ 
					cout << LIGHTGRAY; 
				}

				// Color Cheese Marker
				else if (maze_vector[row][col].m_cell_marker == 'C')
				{ 
					cout << YELLOW; 
				}
				
				// Otherwise Color Wall Marker
				else
				{ 
					cout << DARKGRAY; 
				}
				cout << maze_vector[row][col].m_cell_marker;
			}
			
			cout << "\n";
		}
		
		cout << LIGHTGREEN << "\n";
		system("pause");
	}
	
	// -------------------------------------------------------------------------------
	// Otherwise Print The Current Maze (Solved)
	// -------------------------------------------------------------------------------
	else
	{
		if (m_maze_type == "ASCII")
		{
			// Print ASCII Maze Information
			cout << WHITE << "\nMaze: " << LIGHTGREEN << m_maze_name << WHITE 
				 << " Type: " << LIGHTGREEN << m_maze_type << WHITE 
				 << " Dimensions: " << LIGHTGREEN << m_maze_rows << "x" 
				 << m_maze_cols << "\n";
			
			// Print ASCII Mouse/Cheese Coordinates
			cout << WHITE << "Mouse At: " << LIGHTGREEN << m_mouse_row 
				 << WHITE << "," << LIGHTGREEN << m_mouse_col << WHITE 
				 << " Cheese At: " << LIGHTGREEN << m_cheese_row << WHITE 
				 << "," << LIGHTGREEN << m_cheese_col << "\n\n";
		}
		else
		{
			// Print Vector Maze Information
			cout << WHITE << "\nMaze: " << LIGHTGREEN << m_maze_name << WHITE 
				 << " Type: " << LIGHTGREEN << m_maze_type << WHITE 
				 << " Dimensions: " << LIGHTGREEN << m_maze_rows << "x" 
				 << m_maze_cols << "\n";
			
			// Print Vector Mouse/Cheese Coordinates
			cout << WHITE << "Mouse At: " << LIGHTGREEN << (m_mouse_row * 2 + 2) 
				 << WHITE << "," << LIGHTGREEN << (m_mouse_col * 2 + 2) << WHITE 
				 << " Cheese At: " << LIGHTGREEN << (m_cheese_row * 2 + 2) 
				 << WHITE << "," << LIGHTGREEN << (m_cheese_col * 2 + 2) << "\n\n";
		}
		
		// Print Solution Information
		cout << LIGHTGREEN << "SUCCESS!!" << WHITE << " Solved In " << LIGHTGREEN 
			 << m_moves_to_goal << WHITE << " Moves Using A " << LIGHTGREEN << m_solve_type 
			 << "\n" << endl;

		// As Long As We Are Not At The Starting Position, Backtrack Through The Maze 
		// Replacing The Solution Path With A Period
		while (position.m_row != -1 && position.m_col != -1)
		{
			int temp1 = maze_vector[position.m_row][position.m_col].m_parent_row;
			int temp2 = maze_vector[position.m_row][position.m_col].m_parent_col;
			
			position.m_row = temp1;
			position.m_col = temp2;
			
			if(position.m_row != -1 && position.m_col != -1)
			{
				maze_vector[position.m_row][position.m_col].m_cell_marker = '.';
			}
		}

		// Replace The Mouse Marker
		if (m_maze_type == "BIT")
		{
			maze_vector[(m_mouse_row * 2) + 1][(m_mouse_col * 2) + 1].m_cell_marker = 'M';
		}
		else
		{
			// Process For ASCII	
			maze_vector[m_mouse_row][m_mouse_col].m_cell_marker = 'M';
		}
		
		// Color Cell Markers
		for (int row = 0; row < m_maze_rows; row++)
		{
			for (int col = 0; col < m_maze_cols; col++)
			{
				// Color Path Of Travel Marker
				if (maze_vector[row][col].m_cell_marker == '.')
				{ 
					cout << LIGHTRED; 
				}
				
				// Color Point Of Failure Marker
				else if (maze_vector[row][col].m_cell_marker == '?')
				{ 
					cout << LIGHTGREEN;
				}

				// Color Backtrack Marker
				else if (maze_vector[row][col].m_cell_marker == 'x')
				{ 
					cout << RED; 
				}
				
				// Color Mouse Marker
				else if (maze_vector[row][col].m_cell_marker == 'M')
				{ 
					cout << LIGHTGRAY; 
				}

				// Color Cheese Marker
				else if (maze_vector[row][col].m_cell_marker == 'C')
				{ 
					cout << YELLOW; 
				}

				// Otherwise Color Wall Marker
				else
				{ 
					cout << DARKGRAY; 
				}
				cout << maze_vector[row][col].m_cell_marker;
			}
			
			cout << "\n";
		}
		
		cout << LIGHTGREEN << "\n";
		system("pause");
	}	
}