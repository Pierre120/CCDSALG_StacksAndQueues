/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/

typedef char String[256];
typedef char cOperator[3];


typedef struct
{
  int num; // num of operators
  cOperator arrOperator[4];
} sPrecedence;


void instantiateOperators(sPrecedence* ops)
{
  /*
  ORDER OF PRECEDENCE:
  Index    Precedence    Operator/s
  [0]      1             !, ++, --, ()
  [1]      2             *, /, %
  [2]      3             +, -
  [3]      4             <, >, <=, >=
  [4]      5             ==, !=
  [5]      6             &&
  [6]      7             ||
  */

  ops[0].num = 1;
  strcpy(ops[0].arrOperator[0], "!");

  ops[1].num = 3;
  strcpy(ops[1].arrOperator[0], "*");
  strcpy(ops[1].arrOperator[1], "/");
  strcpy(ops[1].arrOperator[2], "%");

  ops[2].num = 2;
  strcpy(ops[2].arrOperator[0], "+");
  strcpy(ops[2].arrOperator[1], "-");

  ops[3].num = 4;
  strcpy(ops[3].arrOperator[0], ">");
  strcpy(ops[3].arrOperator[1], "<");
  strcpy(ops[3].arrOperator[2], ">=");
  strcpy(ops[3].arrOperator[3], "<=");

  ops[4].num = 2;
  strcpy(ops[4].arrOperator[0], "==");
  strcpy(ops[4].arrOperator[1], "!=");

  ops[5].num = 1;
  strcpy(ops[5].arrOperator[0], "&&");

  ops[6].num = 1;
  strcpy(ops[6].arrOperator[0], "||");
 
}

void extractExpression(queue *q, char *infix)
{
  int c, bEnqueued;
  String tmp;

  while(strlen(infix))
  {
    bEnqueued = 0; // no enqueues yet

    for(c = 0; c < strlen(infix) && !bEnqueued; c++)
      if(infix[c] == ' ')
      {
        infix[c] = '\0'; // set space as end of String
        // copy operand/operator to tmp
        strcpy(tmp, infix);
        enqueue(&q, tmp); // enqueue tmp value in q
        bEnqueued = 1; // enqueue happened
      }

    // if last operand it will reach
    // up to the last element that precedes 
    // the null char of tmp
    if(!bEnqueued)
    {
      // copy remaining string value
      strcpy(tmp, infix);
      enqueue(&q, tmp); // enqueue tmp value in q
    }
    
    // move the string
    strcpy(infix, &infix[c]);
  }
}

int isOperator(char* str)
{
  if(!strcmp(str, "(") || !strcmp(str, ")") || 
    !strcmp(str, "+") || !strcmp(str, "-") || 
    !strcmp(str, "*") || !strcmp(str, "/") || 
    !strcmp(str, "!") || !strcmp(str, "!=") || 
    !strcmp(str, "<") || !strcmp(str, ">") || 
    !strcmp(str, "<=") || !strcmp(str, ">=") || 
    !strcmp(str, "==") || !strcmp(str, "&&") || 
    !strcmp(str, "||") || !strcmp(str, "%"))
    return 1;

  return 0;
}


int isGreater(char* top, char* head, sPrecedence* ops)
{
  int nTopRank = 0, nHeadRank = 0, col, row;

  // determine rank of top in operator stack 
  // and rank of head in infix queue
  for(row = 0; strcmp(top, "(") && strcmp(head, "(") && (!nTopRank || !nHeadRank) && row < 7; row++)
    for(col = 0; (!nTopRank || !nHeadRank) && col < ops[row].num; col++)
    {
      // if top is found in the current precedence level
      if(!nTopRank && !strcmp(top, ops[row].arrOperator[col]))
        nTopRank = row + 1;
      
      // if head is found in the current precedence level
      if(!nHeadRank && !strcmp(head, ops[row].arrOperator[col]))
        nHeadRank = row + 1;
    }

  // Precedence level of head is top priority
  if(!strcmp(top, "(") || !strcmp(head, "(") || nHeadRank < nTopRank)
    return 1;

  return 0;
}


int parseInt(char* strNum)
{
  int nPlaceVal = 1, nVal = 0, c;

  for(c = strlen(strNum) - 1; c >= 0; c--)
  {
    nVal += (strNum[c] - 48) * nPlaceVal;
    nPlaceVal *= 10;
  }

  return nVal;
}


void toString(char* dest, int num)
{
  int j, c, nPlaceVal = 1, tmp = num;

  for(j = 1; num / (nPlaceVal * 10) != 0; j++)
    nPlaceVal *= 10;
  
  for(c = 0; c < j; c++)
  {
    dest[c] = tmp / nPlaceVal + 48;
    tmp %= nPlaceVal;
    nPlaceVal /= 10;
  }

  dest[c] = '\0';
}


int countOps(char* expression)
{
  int size = 0, z;

  // count number of spaces in expression]
  for(z = 0; z < strlen(expression); z++)
    if(expression[z] == ' ')
      size++;

  // increment by 1 since the number of spaces
  // in expression is <number-of-expression> - 1
  // expression: operands, and operators
  size++;

  return size;
}


void getOperatorRank(char* sOperator, sPrecedence* sOps, int nInd[])
{
  int r, c;

  for(r = 0; r < 7; r++)
    for(c = 0; c < sOps[r].num; c++)
      if(!strcmp(sOps[r].arrOperator[c], sOperator))
      {
        nInd[0] = r + 1;
        nInd[1] = c + 1;
      }
}


int evalExpression(int operand_2, int operand_1, 
  char* sOperator, sPrecedence* sOps, int *bError)
{
  int nInd[2], nResult = 0;
  getOperatorRank(sOperator, sOps, nInd); //calls the getOperatorRank function

  switch(nInd[0])
  {
    case 1: // "!"
      if(operand_1 == 0)
        nResult = 1;
      break;

    case 2:
      switch(nInd[1])
      {
        case 1: // "*"
          nResult = operand_2 * operand_1;
          break;

        case 2: // "/"
          if(operand_1 == 0)
            *bError = 1;
          else
            nResult = operand_2 / operand_1;
          break;

        case 3: // "%"
          if(operand_1 == 0)
            *bError = 1;
          else
            nResult = operand_2 % operand_1;
          break;
      }
      break;

    case 3:
      switch(nInd[1])
      {
        case 1: // "+"
          nResult = operand_2 + operand_1;
          break;

        case 2: // "-"
          nResult = operand_2 - operand_1;
          break;
      }
      break;

    case 4:
      switch(nInd[1])
      {
        case 1: // ">"
          if(operand_2 > operand_1)
            nResult = 1;
          break;

        case 2: // "<"
          if(operand_2 < operand_1)
            nResult = 1;
          break;
        
        case 3: // ">="
          if(operand_2 >= operand_1)
            nResult = 1;
          break;

        case 4: // "<="
          if(operand_2 <= operand_1)
            nResult = 1;
          break;
      }
      break;

    case 5:
      switch(nInd[1])
      {
        case 1: // "=="
          if(operand_2 == operand_1)
            nResult = 1;
          break;

        case 2: // "!="
          if(operand_2 != operand_1)
            nResult = 1;
          break;
      }
      break;

    case 6: // "&&"
      if(operand_2 && operand_1)
            nResult = 1;
      break;

    case 7: // "||"
      if(operand_2 || operand_1)
            nResult = 1;
      break;
  }

  return nResult;
}



void infixToPostfix(char *infix, char *postfix) {
	// count total number of Ops
  // Ops = Operands, Operators and grouping symbols
  int size = countOps(infix);
  //String tmp;
  stack* s;
  queue* qInput;
  queue* qOutput;

  // 1ST VERSION FOR OPERATOR
  //sPrecedence* sOp = (sPrecedence*)calloc(7, sizeof(sPrecedence)); // array of Operator struct

  // 2ND VERSION FOR OPERATOR
  sPrecedence sOp[7];

  instantiateOperators(sOp);

  // create stack for operators
  s = createStack(size);
  // create queue for input and output
  qInput = createQueue(size + 1); // input infix
  qOutput = createQueue(size + 1); // output postfix
  // + 1 allowance for size in queues

  // stores infix in qInput
  extractExpression(qInput, infix);
  
  // continuously dequeue infix queue until
  // it is empty and operands/operators are 
  // in their respective storages
  while(!queueEmpty(qInput))
  {
    // dequeue qInput and determine if operand or operator
    //strcpy(tmp, dequeue(&qInput));

    // store operator in stack (s)
    if(isOperator(head(qInput))) // tmp
    {
      if(stackEmpty(s))
        push(&s, dequeue(&qInput)); // push operator when stack is empty //tmp
      
      // checks if closing parenthesis
      else if(!strcmp(head(qInput), ")"))
      {
        dequeue(&qInput); // dequeues the close parenthesis ")"

        // pops stack until current top is "("
        while(!stackEmpty(s) && strcmp(top(s), "("))
          enqueue(&qOutput, pop(&s));
          
        pop(&s); // pops open parenthesis "("
      }

      // checks if operator from infix is greater than
      // the one in the stack
      else if(isGreater(top(s), head(qInput), sOp))
        push(&s, dequeue(&qInput)); // pushes head of qInput when it is greater than the top

      else
      {
        // pops all the operator that is greater than or equal to the operator stored in the head of qInput
        while(!stackEmpty(s) && !isGreater(top(s), head(qInput), sOp))
          enqueue(&qOutput, pop(&s)); //pop from a stack
            
        // pushes head of qInput after popping said operators
        push(&s, dequeue(&qInput)); //push to a stack
      }
    }

    else // store operand in qOutput (digits)
      enqueue(&qOutput, dequeue(&qInput)); 
  }

  // pops the contents in stack (s)
  while(!stackEmpty(s))
    enqueue(&qOutput, pop(&s));

  // dequeue qOutput and place it in postfix
  strcpy(postfix, dequeue(&qOutput));

  // continuously dequeue qOutput and append it to postfix
  while(!queueEmpty(qOutput))
  {
    strcat(postfix, " ");
    strcat(postfix, dequeue(&qOutput));
  }

  free(s);
  free(qInput);
  free(qOutput);
}

//---------------------------------------------------------------------------------

int evaluatePostfix(char *postfix) {
  int size = countOps(postfix);
  int bError = 0;
  String tmp;
  stack* sTmpResult = createStack(size);
  queue* qPost = createQueue(size + 1);
  sPrecedence sOp[7];

  instantiateOperators(sOp);

  // stores postfix in qPost
  extractExpression(qPost, postfix);

  while(!queueEmpty(qPost) && !bError)
  {
    // evaluates 2 top values in sTmpResult if operator is encountered
    if(isOperator(head(qPost)))
    {
      // evaluates the sub-expression in sTmpResult
      // & changes evaluated int value to string
      toString(tmp, evalExpression(
              parseInt(pop(&sTmpResult)), parseInt(pop(&sTmpResult)),
              dequeue(&qPost), sOp, &bError));
      // pushes the string to sTmpResult
      push(&sTmpResult, tmp);
    }
    else // push to stack if operand
      push(&sTmpResult, dequeue(&qPost));
    
  }

  // track error via the postfix param
  if(bError)
    strcpy(postfix, "Division by zero error!");
  
  // return the top of sTmpResult
  return parseInt(pop(&sTmpResult));
}
