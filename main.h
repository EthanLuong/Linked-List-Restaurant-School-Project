#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

typedef struct listNode{
    char *name;
    boolean inRest;
    int burgers;
    int salads;
    struct listNode *next;
} node;

typedef struct linkedList{
    struct listNode *head;
    struct listNode *tail;
} list;

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v, 
 *      form feed \f, and carriage return \r
 */ 
int getNextNWSChar ();

/* read in the next Positive Integer or error:    */
/*    we can count zero as a positive number */ 
int getPosInt ();


/* read in the name until the end of the input */
char *getName();

/* Clear input until next End of Line Character - \n */
void clearToEoln();

/* Print out a list of the commands for this program */
void printCommands();

/* Adds node to a linked list */
void doAdd (list* line);

void doCallAhead ();

void doWaiting ();

void doRetrieve ();

void doList ();

void doDisplay ();

void doEstimateTime();

/* linked list functions */
void init(list *line);
boolean doesNameExist(list *line, char* name);
void addToList(list *line, boolean inRest, int burgers, int salads, char* name);
boolean updateStatus(list *line, char* name);
char* retrieveAndRemove(list *line, int burgers, int salads);
int countOrdersAhead(list *line, char* name);
int displayWaitingTime(list *line, char* name);
void displayOrdersAhead(list *line, char* name);
void displayListInformation(list *line);
void displayNode(node* node);
