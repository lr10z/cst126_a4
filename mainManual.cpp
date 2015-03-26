
//
// CST 126 - Assignment #4
//
// Sudoku Game
//
// File: mainManual.cpp
//
// Client program for manually solving a Soduko puzzle.
//


#include  <iostream>
#include  <cassert>
#include  <cstdlib>
#include  "sudoku.h"

using  namespace  std;

  //
  // Constants
  //
#define  MAX_FILE_SIZE   255
#define  SET_CHAR        's'
#define  CLEAR_CHAR      'c'


//
// Prompt for a filename from the user
//
static void  getFilename( char  *filename )
{
  cout  <<  "Enter game filename: ";

  cin  >>  filename;
}


//
// Determine if the user wants to set or clear a cell
// on the game grid. SET_CHAR is returned if the user
// wants to set a cell value, and CLEAR_CHAR is returned
// if the user wants to clear a cell of it's value.
//
static char  getSetClearChoice(void)
{
  char  choice;
  bool  done  =  false;

  while( ! done )
  {
    cout  <<  endl
          <<  "Set or Clear a cell (s/c): ";

    cin  >>  choice;

    switch( tolower(choice) )
    {
      case  SET_CHAR    :
      case  CLEAR_CHAR  :  done = true;
                           break;

      default           :  cout  <<  "*** Invalid Entry ***"  <<  endl;
    }
  }

  return  choice;
}


//
// Prompt for and process a single user's move.
//
static Sudoku::Result  makeMove( Sudoku  & game )
{
  int             row;
  int             col;
  char            value;
  char            dummy;

  //
  // Determine if the user wants to set or clear a
  // game grid cell.
  //
  char  set  =  ( getSetClearChoice() == SET_CHAR );


  //
  // Give instructions for entering digits and
  // row/col specifiers and prompt for that information.
  //
  cout  <<  endl
        <<  "Valid row/col value are 1-"  <<  game.numRows()
        <<  endl;

  if  ( set )
  {
    cout  <<  "Valid cell value are any of these characters: "
          <<  game.digits()
          <<  endl;
  }

  cout  <<  "Enter row,col"
        <<  ( set  ?  ",value"  :  "" )
        <<  ": ";

  cin  >>  row  >>  dummy  >>  col;


  //
  // Process the user's move
  //

  --row;
  --col;

  if  ( set )
  {
    cin  >>  dummy  >> value;

    return  game.set(row, col, value);
  }


  return  game.clear(row, col);
}


int  main()
{
  //
  // Due to a bug in the Visual C++ 2005 compiler, the following
  // line of code must be done to enable comma-separated integer
  // input.
  //
  cin.imbue(locale("C"));


  //
  // Get the game data file name from the user
  //

  char  filename[MAX_FILE_SIZE];

  getFilename( filename );

  //
  // Create and display the game grid
  //

  Sudoku  game( filename );

  game.display( cout );

  //
  // Loop as long as the puzzle is not completed.
  //
  while( ! game.complete() )
  {
    //
    // Process a user move
    //
    switch  ( makeMove( game ) )
    {
      case  Sudoku::empty_  :
               cout  <<  "*** That's an empty cell ****"  <<  endl;
               break;

      case  Sudoku::locked_  :
               cout  <<  "*** That cell is locked ****"  <<  endl;
               break;

      case  Sudoku::occupied_  :
               cout  <<  "*** That cell is aleady occupied ****"  <<  endl;
               break;

      case  Sudoku::badDigit_  :
               cout  <<  "*** Invalid digit value entered ****"  <<  endl;
               break;

      case  Sudoku::badCoord_  :
               cout  <<  "*** Bad row/col coordinate ****"  <<  endl;
               break;

      case  Sudoku::invalid_   :
               cout  <<  "*** That digit can't go there ****"  <<  endl;
               break;

      case  Sudoku::success_   :
               game.display(cout);
               break;

      default  :  assert(true);
    }
  }


  cout  <<  "*** Yeah!  You solved it ***"  <<  endl  <<  endl;


#ifdef  WIN32
   system("pause");
#else
  system("read -p \"Press any key to continue\"");
#endif


  return  0;
}
