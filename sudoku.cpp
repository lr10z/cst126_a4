
//
// CST 126 - Assignment #4
//
// Sudoku Game
//
// File: sudoku.cpp
//
// Member definitions for the Sudoku class.
//


#include  <cassert>
#include  <fstream>
#include  <cstdlib>
#include  "sudoku.h"

using  namespace  std;


#ifdef  WIN32
   //
   // These values are special character ASCII values
   // for Microsoft Windows console applications. These
   // values will not be correct on other platforms.
   //
#  define  VERT_NORM   char(179)
#  define  VERT_DBL    char(177)
#  define  HOR_NORM    char(196)
#  define  HOR_DBL     char(177)
#  define  CROSS_NORM  char(197)
#  define  CROSS_DBL   char(177)
#else
   //
   // These characters are used for platforms other
   // than Microsoft's
   //
#  define  VERT_NORM   '|'
#  define  VERT_DBL    '%'
#  define  HOR_NORM    '-'
#  define  HOR_DBL     '%'
#  define  CROSS_NORM  '+'
#  define  CROSS_DBL   '%'
#endif


//
// Construction/Destruction
//

  //
  // Constructor
  //
  // Reads game data file and sets up internal
  // class data structures.
  //
  // The program is terminated if the file open
  // fails or if memory allocation fails.
  //
Sudoku::Sudoku( const char  *filename )  :
  m_numCellsFilled(0),
  m_statNumSetSuccess(0),
  m_statNumSetInvalid(0),
  m_statNumSetLocked(0)
{
  ifstream  in( filename, ios::in );

  if  ( in.fail() )
  {
    cerr  <<  "File open failed: '"
          <<  filename
          <<  '\''
          <<  endl;

    exit( EXIT_FAILURE );
  }

  in  >>  m_base;

  loadDigits( in );
  loadGrid( in );
}


  //
  // Sets up the data structure for the digits and
  // loads the digits from game file.
  //
  // The program is terminated if memory allocation
  // fails.
  //
void  Sudoku::loadDigits( istream  &in )
{
  //
  // Allocate memory for the digits string
  //
  m_digits  =  new  char[numDigits() + 1];

  if  (! m_digits)
  {
    cerr  <<  "Memory allocation failure!"  <<  endl;
    exit( EXIT_FAILURE );
  }


  unsigned  idx;


  //
  // Load the digits from the game data file
  //
  for( idx = 0;  idx < numDigits();  ++idx )
  {
    char  ch;

    in  >>  ch;

    m_digits[idx]  =  ch;
  }

  m_digits[idx]  =  0;
}


  //
  // Sets up the data structure for the game grid and
  // loads the digits from game file.
  //
  // The program is terminated if memory allocation
  // fails.
  //
void  Sudoku::loadGrid( istream  &in )
{
  //
  // Allocate memory for all the cells of the game
  //
  m_grid  =  new  Cell[numRows() * numCols()];

  if  (! m_grid)
  {
    cerr  <<  "Memory allocation failure!"  <<  endl;
    exit( EXIT_FAILURE );
  }


  //
  // Get the empty cell indicator from the data file.
  //
  char  blankChar;

  in  >>  blankChar;


  //
  // Set the initial digit values for the cells
  //
  for( unsigned  row = 0;  row < numRows();  ++row )
    for( unsigned  col = 0;  col < numCols();  ++col )
    {
      char  ch;

      in  >>  ch;

      if  ( ch == blankChar )  continue;
        //
        // Cells default to being empty, so there's nothing
        // to do for cells that start out the game as blank.
        //

      //
      // Cells that are set as part of the beginning state of the
      // game are locked so that they can't be changed.
      //
      m_grid[ gridIdx(row, col) ].set( ch );
      m_grid[ gridIdx(row, col) ].lock();

      ++m_numCellsFilled;
    }
}


  //
  // Destructor
  //
Sudoku::~Sudoku()
{
  //
  // Clean up allocated memory
  //
  delete  []  m_grid;
  delete  []  m_digits;
}


//
// Game cell manipulation
//

  //
  // Sets a specific game grid cell to a specified digit value.
  //
  // The following can be returned:
  //   locked_ - indicates the specified game grid cell can not
  //             be changed.
  //   occupied_ - indicates the specified game grid cell already
  //               contains a value (a cell must be clear before it
  //               can be set).
  //   badDigit_ - an invalid digit was specified
  //   badCoord_ - the row and/or col values specified are outside
  //               the game grid.
  //   invalid_ - the digit can not go in this cell because it
  //              violates a rule of the game. In other words, that
  //              digit already exists in the same row, column, or
  //              square as that specified by the parameters to this
  //              function.
  //   success_ - the digit was put in the specified cell position
  //              on the game grid.
  //
  // Note: the game grid is only changed if success_ is returned.
  //
Sudoku::Result  Sudoku::set( unsigned  row, unsigned  col, char  digit )
{
  //
  // Check for bad coordinates
  //
  if  ( ! validCoordinate( row, col ) )  return  badCoord_;


  //
  // Fetch the cell
  //
  Cell  &c  =  cell(row,col);


  //
  // Determine if the cell is locked or already occupied
  //
  if  ( c.isLocked() )
  {
    ++m_statNumSetLocked;
    return  locked_;
  }

  if  ( c.isSet() )   return  occupied_;


  //
  // Validate the digit and make sure it is allowed to
  // be put in the particular cell based on the current
  // game grid state.
  //
  if  ( ! validDigit( digit ) )  return badDigit_;

  if  ( ! validRow( row, digit )  ||
        ! validCol( col, digit )  ||
        ! validSquare( row, col, digit ) )
  {
    ++m_statNumSetInvalid;
    return  invalid_;
  }


  //
  // Set the cells new digit value, and update the cells-occupied
  // counter.
  //
  c.set( digit );

  ++m_numCellsFilled;
  ++m_statNumSetSuccess;

  return  Sudoku::success_;
}


  //
  // Returns true if the specified digit does not appear
  // in the game grid anywhere on the row specified.
  //  Otherwise false is returned.
  //
bool  Sudoku::validRow( unsigned  row, char  digit )  const
{
  unsigned  col;

  for( col = 0;  col < numCols();  ++col )
    if  ( digit == cell(row, col).get() )
      return  false;

  return  true;
}


  //
  // Returns true if the specified digit does not appear
  // in the game grid anywhere on the column specified.
  //  Otherwise false is returned.
  //
bool  Sudoku::validCol( unsigned  col, char  digit )  const
{
  unsigned  row;

  for( row = 0;  row < numRows();  ++row )
    if  ( digit == cell(row, col).get() )
      return  false;

  return  true;
}


  //
  // Returns true if the specified digit does not appear
  // in the game grid square that corresponds to the
  // specified row/col. Otherwise false is returned.
  //
bool  Sudoku::validSquare( unsigned  row, unsigned  col, char  digit )  const
{
  //
  // Determine the upper-left cell of the square that cooresponds
  // to the row/col values specified as parameters.
  //
  row  =  (row / m_base) * m_base;
  col  =  (col / m_base) * m_base;


  //
  // Look for any cell in the square that matches
  // the digit.
  //
  for( unsigned  r = row;  r < row + m_base; ++r )
    for( unsigned  c = col;  c < col + m_base; ++c )
      if  ( digit == cell(r, c).get() )
        return  false;

  return  true;
}


   //
   // Clears a digit from a specific cell in the game grid.
   //
   // Return values for this function are:
   //   locked_ - indicates the specified game grid cell can not
   //             be changed.
   //   empty_ - indicates the specified game grid cell already
   //            is clear of any digits.
   //   badCoord_ - the row and/or col values specified are outside
   //               the game grid.
   //   success- the existing digit was cleared from the specified
   //            cell position on the game grid.
   //
   // Note: the game grid is only changed if success_ is returned.
   //
Sudoku::Result  Sudoku::clear( unsigned  row, unsigned  col )
{
  //
  // Check for bad coordinates
  //
  if  ( ! validCoordinate( row, col ) )  return  badCoord_;

  //
  // Fetch the cell
  //
  Cell  &c  =  cell(row, col);


  //
  // Determine if the cell is already clear or locked
  //
  if  ( ! c.isSet() )  return  empty_;

  if  ( c.isLocked() )  return  locked_;


  //
  // Clear the cell, and update the cells-occupied
  // counter.
  //
  c.clear();

  --m_numCellsFilled;


  return  Sudoku::success_;
}


  //
  // Returns true if the specified row/col values are within
  // the zero-based bounds of the game grid. Otherwise, false
  // is returned.
  //
bool  Sudoku::validCoordinate( unsigned  row, unsigned  col )  const
{
  return  row >= 0  &&  row < numRows()  &&
          col >= 0  &&  col < numCols();
}


//******************
// Display routines
//******************

#define  SHOW_STAT( os, label, count )   (os)  <<  (label)  <<  ": "  <<  (count)  <<  endl

  //
  // Display statistics
  //
void  Sudoku::stats( ostream  &os )  const
{
  unsigned  total  =  m_statNumSetLocked + m_statNumSetInvalid + m_statNumSetSuccess;

  os  <<  endl;

  SHOW_STAT(os, "    Locked attempts",  m_statNumSetLocked );
  SHOW_STAT(os, "   Invalid attempts",  m_statNumSetInvalid );
  SHOW_STAT(os, "Successful attempts",  m_statNumSetSuccess );

  os  <<  endl;
}


  //
  // Display the entire game grid
  //
void  Sudoku::display( ostream  &os )  const
{
  os  <<  endl;

#ifdef  WIN32
  system("cls");
#endif

  for( unsigned  row = 0;  row < numRows();  ++row )
    displayRow( os, row );

  solidRow( os, true );

  os  <<  endl;
}


//
// Display a single row of the grid
//
void  Sudoku::displayRow( ostream  &os, unsigned  row )  const
{
  solidRow( os, !( row  %  m_base ) );

  dataRow( os, row );
}


//
// Display a data row
//
void  Sudoku::dataRow( ostream  &os, unsigned  row )  const
{
  os  <<  "  ";

  for( unsigned  col = 0;  col < numCols();  ++col )
  {
    if  ( col  %  m_base )
      os  <<  VERT_NORM;
    else
      os  <<  VERT_DBL;

    os  <<  ' ';

    if  ( cell(row, col).isSet() )
      os  <<  cell(row, col).get();
    else
      os  <<  ' ';

    os  <<  ' ';

  }

  os  <<  VERT_DBL  <<  endl;
}


//
// Display a solid row
//
void  Sudoku::solidRow( ostream  &os, bool  dbl )  const
{
  char  cross  =   dbl  ?  CROSS_DBL  :  CROSS_NORM;
  char  hor    =   dbl  ?  HOR_DBL    :  HOR_NORM;

  os  <<  "  ";

  for( unsigned  col = 0;  col < numCols();  ++col )
  {
    if  ( col  %  m_base )
      os  <<  cross;
    else
      os  <<  CROSS_DBL;

    os  <<  hor  <<  hor  <<  hor;
  }

  os  <<  CROSS_DBL  <<  endl;
}
