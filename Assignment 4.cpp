//
// CST 126 - Assignment #4
//
// Author: Leander Rodriguez
//
// File: cycleComputer.cpp
//
// Due date:  Monday, March 4th at 11:59pm
//
// Client program for automatically solving a Soduko puzzle.
//



#include  <iostream>
#include  <cassert>
#include  <cstdlib>
#include "sudoku.h"


using namespace std;


//
// Constants
//
#define BUFFER_SZ		10
#define MAX_FILE_SIZE   255



//
// Recursive algorithm to solve Sudoku puzzle automatically
//
void solveCell( Sudoku &game, unsigned row, unsigned col )
{
	
	char digit;


	//
	// Cell selection wraps around if number of columns is 
	// exceeded; game continues on the next row down
	//

	if( col+1 > game.numCols() )
	{
		col = 0;
		++row;
	}
	
	
	//
	// Enumerated values are introduced into the program
	//

	Sudoku::Result r;


	//
	// Loops through possible digits for current selected cell
	//

	for( unsigned idx = 0; idx < strlen( game.digits() ); ++idx )
	{
		
		//
		// Determine cell digit to test
		//

		digit = game.digits()[idx];


		//
		// Enumerated value is determined based on digit set at
		// current cell
		//

		r = game.set( row, col, digit );


		//
		// Current enumerated value is checked and processed
		//

		if( r == Sudoku::success_  )
		{
			solveCell( game, row, col+1 );

			if( game.complete() )
			{
				return;
			}

			else
			{
				game.clear( row, col );
			}

		}


		if(  r == Sudoku::locked_ )
		{
			
			solveCell( game, row, col+1 );
			return;
		}

	}

}



//
// Waits for user to press 'Enter'
//
void userRecognition()
{

	cout  <<  "Press any key to continue . . . ";

	char buffer[BUFFER_SZ];

	cin.ignore();
	cin.getline( buffer, BUFFER_SZ );

}



//
// Prompt user to enter filename
//
void getFilename( char *filename )
{

	cout  <<  "Enter game filename: ";

	cin  >>  filename;

}



//
// Main program
//
int main()
{

	//
	// Row and Column initialized
	//

	unsigned row = 0,
			 col = 0;
	

	//
	// Get the game data file name from the user
	//
	char  filename[MAX_FILE_SIZE];

	getFilename( filename );


	//
	// Sudoku object is created
	//
	Sudoku game( filename );


	//
	// Game grid displayed in its initial state
	//
	game.display( cout );


	//
	// Waits for user to press enter
	//
	userRecognition();


	//
	//  Solves Sudoku puzzle with recursive algorithm
	//
	solveCell( game, row, col );


	//
	// Game grid displayed in its final state
	//
	game.display( cout );

	
	//
	// Waits for user to press enter
	//
	userRecognition();


	//
	// Displays game statistics
	//
	game.stats( cout );


	return 0;
}