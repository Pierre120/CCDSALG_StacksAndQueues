/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/

typedef struct {
	int n;
	int nCount;
	sNode *pTop;
} stack;

stack* createStack(int n) {
  // allocate memory for stack
	stack* pNewStack = (stack*)malloc(sizeof(stack));
  pNewStack->n = n; // assign size
  pNewStack->nCount = 0; // initialize num of elements
  pNewStack->pTop = NULL; // no address yet

  return pNewStack;
}

int stackEmpty(stack *s) {
	// empty if num of elements is 0
  if(s->nCount == 0)
    return 1;
  
  return 0;
}

int stackFull(stack *s) {
	// full if size and num of elements is equal
  if(s->nCount == s->n)
    return 1;
  
  return 0;
}

void push(stack **s, char *data) {
  // checks if stack is already full
  if(!stackFull(*s))
  {
    (*s)->nCount++;
    // allocates new node for top
    // since if it is locally declared
    // the allocated memory might be for temporary 
    // only and might be used by other processes
    sNode* pNewTop = (sNode*)malloc(sizeof(sNode));
    pNewTop->data = (char*)calloc(strlen(data) + 1, sizeof(char));
    strcpy(pNewTop->data, data); // new node stores data
    pNewTop->pLink = (*s)->pTop; // new node stores old top node in pLink

    (*s)->pTop = pNewTop; // assign new top node in stack
  }
}

char* pop(stack **s) {
	char* cToPop = (char*)calloc(1, 1);
  cToPop[0] = '\0';
  // checks if the stack is already empty
  if(!stackEmpty(*s))
  {
    // reallocate memory of cToPop to have same size as data member of pTop
    cToPop = (char*)realloc(cToPop, strlen((*s)->pTop->data) + 1); 
    // store data to return
    strcpy(cToPop, (*s)->pTop->data);
    (*s)->nCount--; // decrement num of elements
    // move top node one link/node back 
    (*s)->pTop = (*s)->pTop->pLink;
  }
  return cToPop;
}

void displayStack(stack *s) {
	// temporary node for display
  sNode* pContents = s->pTop;

  // continues to print or go back
  // one node up to the very first
  // node in the stack
  while(pContents != NULL)
  {
    printf("%s ", pContents->data);
    // goes back one node back
    pContents = pContents->pLink;
  }

  //DEBUGGING PURPOSES
  printf("\n");
}

char* top(stack *s) {
  // checks if stack is empty
  if(!stackEmpty(s))
    return s->pTop->data;
  
  return "\0";
}
