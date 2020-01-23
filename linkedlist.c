#include "main.h"

extern boolean DEBUG;

/* Initializes linked list to null */
void init(list *line)
{
    line->head = NULL;
    line->tail = NULL;
}

/* Returns TRUE if name is already in list. FALSE otherwise*/
boolean doesNameExist(list *line, char* name)
{
    node* tmp = line->head;
    //Loop through entire list looking for name
    while(tmp != NULL)
    {
        if(DEBUG == TRUE)
            displayNode(tmp);
        if(strcmp(tmp->name, name) == 0)
            return TRUE;
        tmp = tmp->next;
    }
    return FALSE;
}

/* Adds new node to list. If name exists returns an error*/
void addToList(list *line, boolean inRest, int burgers, int salads, char* name)
{
    //Checks if name is in line
    if(doesNameExist(line, name) == TRUE)
    {
        printf("Error: Name already exists in line\n");
        return;
    }
    //Creates new node and copies data
    node* tmpNode = (node*) malloc(sizeof(node));
    tmpNode->name = name;
    tmpNode->burgers = burgers;
    tmpNode->salads = salads;
    tmpNode->inRest = inRest;
    tmpNode->next = NULL;
    //Checks if node is empty
    if(line->tail == NULL)
    {
        line->head = tmpNode;
        line->tail = tmpNode;
        return;
    }
    //updates list
    line->tail->next = tmpNode;
    line->tail = tmpNode;
    
}

/* Sets given name inRest status to TRUE. Returns TRUE if name is in line and is not inRest.
 * Returns FALSE otherwise */
boolean updateStatus(list *line, char* name)
{
    //Checks if name exists
    if(doesNameExist(line, name) == FALSE)
        return FALSE;
    //Find node with name
    node* tmpNode = line->head;
    while(strcmp(tmpNode->name, name) != 0)
    {
        if(DEBUG == TRUE)
            displayNode(tmpNode);
        tmpNode = tmpNode->next;
    }
    //Check if already in restaurant
    if(tmpNode->inRest == TRUE)
        return FALSE;
    //Sets inRest to TRUE and returns TRUE
    tmpNode->inRest = TRUE;
    return TRUE;
}

//Finds the first node with burgers and salads less than the given amount
//returns the name of the node found or error if not found
char* retrieveAndRemove(list *line, int burgers, int salads)
{
    char* name;
    node* tmpNode = line->head;
    //check if line is empty
    if(tmpNode == NULL)
    {
        printf("Error: Line is empty\n");
        return "error";
    }
    //Debug
    if(DEBUG == TRUE)
        displayNode(tmpNode);
    
    //First element meets requirements
    if(tmpNode->burgers <= burgers && tmpNode->salads <= salads && tmpNode->inRest == TRUE)
    {
        
        //update linked list
        line->head = tmpNode->next;
        if(line->head == NULL)
            line->tail = NULL;
        name = tmpNode->name;
        free(tmpNode);
        return name;
    }
    
    //Single element in list
    if(line->head->next == NULL)
    {
        printf("Error: Not enough burgers or salads\n");
        return "error";
    }
    
    //Finds the node that has less burgers/salads then what is available
    while(tmpNode->next != NULL)
    {
        if(DEBUG == TRUE)
            displayNode(tmpNode->next);
        if(tmpNode->next->burgers <= burgers && tmpNode->next->salads <= salads && tmpNode->next->inRest == TRUE)
            break;
        tmpNode = tmpNode->next;
    }
    //No node found
    if(tmpNode->next == NULL)
    {
        printf("Error: Not enough burgers or salads or no one in restaurant\n");
        return "error";
    }

    //Updates linked list, returns name
    node* delNode = tmpNode->next;
    name = delNode->name;
    tmpNode->next = delNode->next;
    if(line->tail == delNode)
        line->tail = tmpNode;
    free(delNode);
    return name;
}

/* Returns number of ordres ahead of name. Returns -1 if name is not in line */
int countOrdersAhead(list *line, char* name)
{
    //Check if name is in line
    if(doesNameExist(line, name) == FALSE)
        return -1;
    
    int orders = 0;
    node* tmpNode = line->head;
    //Loops through list counting orders until name is find
    while(strcmp(tmpNode->name, name) != 0)
    {
        if(DEBUG == TRUE)
            displayNode(tmpNode);
        tmpNode = tmpNode->next;
        orders++;
    }
    return orders;
}

/* Returns the waiting time in mintues -1 if name not in line */
int displayWaitingTime(list *line, char* name)
{
    //Check if name is in line
    if(doesNameExist(line, name) == FALSE)
    {
        printf("Error: Name not in line\n");
        return -1;
    }
    
    int waitTime = 0;
    node* tmpNode = line->head;
    //Loops through list adding to wait time
    while(strcmp(tmpNode->name, name) != 0)
    {
        if(DEBUG == TRUE)
            displayNode(tmpNode);
        //Add time
        waitTime += tmpNode->burgers * 10;
        waitTime += tmpNode->salads * 5;
        //Breaks if name matches
        if(strcmp(tmpNode->name, name) == 0)
            break;
        
        tmpNode = tmpNode->next;
    }
    return waitTime;
}

/* Displays orders ahead of the given name. Return error if name isn't in line */
void displayOrdersAhead(list *line, char* name)
{
    //Check if name is in line
    if(doesNameExist(line, name) == FALSE)
    {
        printf("Error: Name not in line\n");
        return;
    }
    node* tmpNode = line->head;
    //Loops through displaying each order
    while(strcmp(tmpNode->name, name) != 0)
    {
        if(DEBUG == TRUE)
            displayNode(tmpNode);
        
        printf("Burgers: %d, Salads: %d\n", tmpNode->burgers, tmpNode->salads);
        tmpNode = tmpNode->next;
    }
    printf ("Order for \"%s\" is behind %d orders\n", name, countOrdersAhead(line, name));
}
/* Displays all list information beginningt to end */
void displayListInformation(list *line)
{
    node* tmpNode = line->head;
    //Check if line is empty
    if(tmpNode == NULL)
    {
        printf("Line empty.\n");
        return;
    }
    //Displays entire list
    while(tmpNode != NULL)
    {
        printf("Name: %s, Burgers: %d, Salads: %d ", tmpNode->name, tmpNode->burgers, tmpNode->salads);
        if(tmpNode->inRest == TRUE)
            printf("In Restaurant\n");
        else
            printf("Not in Restaurant\n");
        tmpNode = tmpNode->next;
    }
}
/* Displays node for debugging */
void displayNode(node* node)
{
    if(node == NULL)
    {
        printf("NULL NODE \n");
        return;
    }
    printf("DEBUG Name: %s, Burgers: %d, Salads: %d, ", node->name, node->burgers, node->salads);
    
    if(node->inRest == TRUE)
        printf("In Restaurant\n");
    else
        printf("Not in Restaurant\n");
    
}