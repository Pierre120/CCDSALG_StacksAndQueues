/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/

/*
Group #6:
  TOLENTINO, John Enrico
  CRUZ, Airon John
  HERNANDEZ, Pierre Vincent
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "stack.h"
#include "queue.h"
#include "algorithms.h"
// typedef of String is in algorithms.h


int scanString(char* dest)
{
  char cIn = '\0';
  int c = 0;

  do
  {
    
    // scans the string character by character
    scanf("%c", &cIn);

    // store in dest if cIn has not reached newline
    if(cIn != '\n')
    {
      dest[c] = cIn;
      c++;
    }
  } while(cIn != '\n');
  // scans until newline character is reached

  dest[c] = '\0';

  // if dest is not "QUIT"
  if(strcmp(dest, "QUIT"))
    c = 0; // false

  return c; // true
}


int main() {
	
	String strInfix, strPostfix;
  int bQuit = 0, nOutput;

  while(!bQuit)
  {
    bQuit = scanString(strInfix);

    if(!bQuit)
    {
      // change infix to postfix expression
      infixToPostfix(strInfix, strPostfix);
      // display postfix expression
      printf("%s\n", strPostfix);

      // evaluate postfix expression
      nOutput = evaluatePostfix(strPostfix);
      // uses the strPostfix to see if there
      // is a division by zero error

      // checks if there is a division by zero error
      if(!strcmp(strPostfix, "Division by zero error!"))
        printf("%s\n\n", strPostfix); // displays error
      else
        printf("%d\n\n", nOutput); // displays result
    }
  }
	
	return 0;
}

