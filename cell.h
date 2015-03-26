
//
// CST 126 - Assignment #4
//
// Sudoku Game
//
// File: cell.h
//
// Declaration for Cell class for the Sudoku game.
//


#ifndef  cell_H
#define  cell_H


class  Cell
{
  public  :

    //
    // Data types, constants
    //

    enum  { noValue_ = ' ' };

    enum  Result  { success_, failure_ };


    //
    // Construction
    //

    Cell();


    //
    // State  manipulators
    //

    Result  set( char  value );
    Result  clear();
    Result  lock();
    Result  unlock();


    //
    // Accessors
    //

    bool    isSet()  const              { return  m_value != noValue_; }

    char  get()  const                  { return  m_value; }

    bool    isLocked()  const           { return  m_locked; }

  private  :

    char      m_value;
    bool      m_locked;

    void  reset();
};


#endif
