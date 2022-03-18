/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/

typedef struct {
	int n;
	int nCount;
	sNode *pHead;
	sNode *pTail;
} queue;

queue* createQueue(int n) {
  //alocate memory for queue
	queue* pNewQueue = (queue*)malloc(sizeof(queue));
  pNewQueue->n = n; // size of queue 
  pNewQueue->nCount = 0; // initialize num of elements
  pNewQueue->pHead = NULL;
  pNewQueue->pTail = NULL;

  return pNewQueue;
}

int queueEmpty(queue *q) {
  // empty if there are no elements yet
	if(q->pHead == NULL && q->pTail == NULL)
    return 1;
  
  return 0;
}

int queueFull(queue *q) {
  // full if num of elements is equal to minus 1 of the size
	if(q->n - 1 == q->nCount)
    return 1;
  
  return 0;
}

void enqueue(queue **q, char *data) {
	// checks if queue is already full
  if(!queueFull(*q))
  {
    if((*q)->nCount == 0)
    {
      (*q)->pHead = (sNode*)malloc(sizeof(sNode));
      (*q)->pTail = (*q)->pHead;
    } 
    else
    {
      (*q)->pTail->pLink = (sNode*)malloc(sizeof(sNode));
      (*q)->pTail = (*q)->pTail->pLink;
    }
       
    // reallocate memory to store data
    (*q)->pTail->data = (char*)calloc(strlen(data) + 1, sizeof(char));
    // copy new data in the current place of tail node
    strcpy((*q)->pTail->data, data);
    (*q)->nCount++; // increment num of elements

    (*q)->pTail->pLink = NULL;
  }
}

char* dequeue(queue **q) {
  char* cToDequeue = (char*)calloc(1, 1);
  cToDequeue[0] = '\0';

  // checks if queue is already empty
  if(!queueEmpty(*q))
  {
    // reallocate memory of cToDequeue to have same size as data member of pHead
    cToDequeue = (char*)realloc(cToDequeue, strlen((*q)->pHead->data) + 1);
    // store data to return
    strcpy(cToDequeue, (*q)->pHead->data);
    (*q)->nCount--; // decrement num of elements

    /*
    Checks if pHead and pTail now has the same address.
    When pHead stores the address of pTail after doing
    pHead->pLink, it can manipulate its members and it will
    reflect in pTail but by the time pHead stores the address
    in pHead->pLink while pHead and pTail stores the same 
    address, then it will not have any effects on pTail but
    rather pHead will just point out to another address.
    Thus, if both have the same address then both of them should
    move to the next node.
    */
    if((*q)->pHead == (*q)->pTail)
      (*q)->pTail = (*q)->pTail->pLink;

    // moves head node to the next linked node
    (*q)->pHead = (*q)->pHead->pLink;
  }
  return cToDequeue;
}

void displayQueue(queue *q) {
  // starting from head
  sNode* pContents = q->pHead; // temporary node for display
 
  while(pContents != NULL)
  {
    printf("%s\n", pContents->data);
    pContents = pContents->pLink; // move to next node
  }
}

char* head(queue *q) {
  // checks if the queue is empty
  if(!queueEmpty(q))
    return q->pHead->data;
  
  return "\0";
}

char* tail(queue *q) {
  // checks if the queue is empty
  if(!queueEmpty(q))
    return q->pTail->data;

  return "\0";
}
