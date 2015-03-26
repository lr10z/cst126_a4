
//
// CST 126 - Recursion illustrator
//
// Author:  Michael Hoffman
//

#include  <iostream>

using  namespace  std;

/*
 * The following macros and funcdtions are used for dealing
 * with the display indentation that illustrates the current
 * state of recursion.
 */
#   define  START_RECURSIVE_FUNCTION  (++level)
#   define  END_RECURSIVE_FUNCTION  (--level)
#   define  INDENT  indent()

static  int  level  =  0;

void  indent()
{
  for( int  i = 0;  i < level;  ++i )
    cout  <<  "****";
}


/*
 * Some helper functions for prompting for values and
 * displaying data.
 */


int  getValue()
{
  INDENT;  cout  <<  "Enter a number: ";

  int  number;

  cin  >>  number;

  return  number;
}


int  promptForAction()
{
  INDENT;  cout  <<  "Do you want to recurse (1) or return (2): ";

  int  choice;

  cin  >>  choice;

  return  choice;
}


void  display( int  inst, int  uv )
{
  INDENT;  cout  <<  "Instance   = "  <<  inst  <<  endl;
  INDENT;  cout  <<  "User value = "  <<  uv  <<  endl;
}


/*
 * The recursive function
 */

void  process( int  instance )
{
  //
  // Just some stuff to make the output look pretty
  //
  START_RECURSIVE_FUNCTION;
  cout  <<  endl;  INDENT;  cout  <<  "BEGIN - process()"  <<  endl;


  //
  // The guts of the function
  //

  int  userValue  =  getValue();

  bool  done  =  false;

  while( ! done )
  {
    display( instance, userValue );

    switch( promptForAction() )
    {
      case  1  :

        process( instance + 1 );
        break;

      case  2  :

        done  =  true;
        break;
    }
  }


  //
  // More some stuff to make the output look pretty
  //
  INDENT;  cout  <<  "END - process()"  <<  endl  <<  endl;
  END_RECURSIVE_FUNCTION;
}


//
// The main program
//
int  main()
{
  cout  <<  endl;  INDENT;  cout  <<  "BEGIN - main()"  <<  endl;

  process(1);

  INDENT;  cout  <<  "END - main()"  <<  endl  <<  endl;

  return  0;
}
