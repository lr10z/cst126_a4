
//
// CST 126 - Assignment #4
//
// Sudoku Game
//
// File: sudoku.h
//
// Declaration for Sudoku game engine class.
//


#ifndef  sudoku_H
#define  sudoku_H


#include  <iostream>
#include  <cstring>
#include  <cstdlib>
#include  "cell.h"

using  namespace  std;


class  Sudoku
{
  public  :

    //
    // Data types
    //

    enum  Result  {
                    success_,
                    occupied_,
                    empty_,
                    locked_,
                    badDigit_,
                    badCoord_,
                    invalid_
                  };


    //
    // Construction/destruction
    //

    Sudoku( const char  *filename );

    ~Sudoku();


    //
    // Accessors
    //

    const  char  *digits()  const    { return  m_digits; }

    unsigned  numDigits()  const     { return  m_base * m_base; }

    unsigned  numRows()  const       { return  m_base * m_base; }
    unsigned  numCols()  const       { return  m_base * m_base; }

    bool  complete()  const
           { return  m_numCellsFilled == numRows() * numCols(); }



    //
    // Game cell manipulation
    //

    Result  set( unsigned  row, unsigned  col, char  digit );

    Result  clear( unsigned  row, unsigned  col );


    //
    // Display routines
    //

    void  display( ostream  &os )  const;

    void  stats( ostream  &os )  const;

  private  :

    unsigned   m_base;
    Cell      *m_grid;
    char      *m_digits;
    unsigned   m_numCellsFilled;

    unsigned   m_statNumSetSuccess;
    unsigned   m_statNumSetInvalid;
    unsigned   m_statNumSetLocked;

    const Cell  &cell( unsigned  row, unsigned  col )  const
                                       { return  m_grid[ gridIdx(row,col) ]; }

    Cell  &cell( unsigned  row, unsigned  col )
                                       { return  m_grid[ gridIdx(row,col) ]; }

    bool  validDigit( char  digit )  const
                                   { return  (digit) > 0 && strchr( m_digits, digit ) != 0; }

    unsigned  gridIdx( unsigned  row, unsigned  col )  const
                                            { return  row * numCols() + col; }

    void  loadDigits( istream  &in );
    void  loadGrid( istream  &in );

    bool  validCoordinate( unsigned  row, unsigned  col )  const;
    bool  validRow( unsigned  row, char digit )  const;
    bool  validCol( unsigned  col, char digit )  const;
    bool  validSquare( unsigned  row, unsigned  col, char digit )  const;

    void  displayRow( ostream  &os, unsigned  row )  const;
    void  dataRow( ostream  &os, unsigned  row )  const;
    void  solidRow( ostream  &os, bool  dbl )  const;


    //
    // Copying/assignment for this class not supported.
    //
    Sudoku( const Sudoku  & );
    const Sudoku  &operator=( const Sudoku  & );
};


#endif
