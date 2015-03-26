
//
// CST 126 - Assignment #4
//
// Sudoku Game
//
// File: cell.cpp
//
// Cell class member definitions.
//


#include  "cell.h"


//
// Constructor
//
Cell::Cell()
{
  reset();
}


//
// Clear a cells value. success_ is returned if
// successful, failure_ is returned if the cell
// is locked and can't be changed.
//
Cell::Result  Cell::clear()
{
  if  ( m_locked )  return  failure_;

  m_value  =  noValue_;

  return  success_;
}


//
// Set a cells value to a specific character.
// success_ is returned if successful, failure_
// is returned if the cell is locked and can't
// be changed.
//
Cell::Result  Cell::set( char  value )
{
  if  ( isLocked() )
    return  failure_;

  m_value  =  value;

  return  success_;
}


//
// Lock a cell (prevent it's value from being
// changed). success_ is returned if successful,
// failure_ is returned if the cell currently
// has no value.
//
Cell::Result  Cell::lock()
{
  if  ( ! isSet() )  return  failure_;

  m_locked  =  true;

  return  success_;
}


//
// Unlock a cell. Always returned success_.
//
Cell::Result  Cell::unlock()
{
  m_locked  =  false;

  return  success_;
}


//
// Unlocks and clears a cell's value.
//
void  Cell::reset()
{
  unlock();

  clear();
}
