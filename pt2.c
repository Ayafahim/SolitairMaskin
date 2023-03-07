#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_CARDS 52

typedef struct card
{
    char suit;
    char rank;
    bool revealed;
} card;

typedef struct node
{

    struct card *card;
    struct node *prev;
    struct node *next;
} node;

struct card *createNewCard(char suit, char rank);
struct node *createNewNode(struct card *card);
void insertNode(node **headRef, card *card);
void createDeck(node **deck);
void printNode(const struct node *node);
void printList(const struct node *list);
int countNodes(const struct node *list);
node *removeFirstNode(node **head);
void insertRandomPosition(node **head, node *newNode);
void shuffleList(node **head);
void dealCards(node **deck, node **C1, node **C2, node **C3, node **C4, node **C5, node **C6, node **C7);
void printBoard(node **C1, node **C2, node **C3, node **C4, node **C5, node **C6, node **C7);
void moveCard(node *c1, node *c2, node *c3, node *c4, node *c5, node *c6, node *c7, const char *cardString, const char *destString);
void printNodeBoard(node **column, int i);
node *getLastNode(node *head);
node *findCard(const char *cardString, node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7);
void extractStrings(char *left, char *right);
node *findAndRemoveCard(node *c1, node *c2, node *c3, node *c4, node *c5, node *c6, node *c7, const char *cardString);

node *C1 = NULL;
node *C2 = NULL;
node *C3 = NULL;
node *C4 = NULL;
node *C5 = NULL;
node *C6 = NULL;
node *C7 = NULL;
node *F1 = NULL;
node *F2 = NULL;
node *F3 = NULL;
node *F4 = NULL;

int main()
{
    node *head = NULL;
    node *moveHead = NULL;
    char left[256] = {'\0'};
    char right[256] = {'\0'};
    createDeck(&head);
    // printList(head);
    countNodes(head);
    printf("Shuffeling...\n");
    shuffleList(&head);
    // printList(head);
    printf("Dealing cards...\n");
    //  node *piles[7] = {NULL};
    //  dealCards(&head, piles);
    dealCards(&head, &C1, &C2, &C3, &C4, &C5, &C6, &C7);
    printBoard(&C1, &C2, &C3, &C4, &C5, &C6, &C7);
    printf("\nmoving cards...\n");
    // moveCard(&piles[0], &piles[1]);
    // moveCard(&C1, &C6);
    printBoard(&C1, &C2, &C3, &C4, &C5, &C6, &C7);
    getLastNode(C2);
    printf("Type in a card to find: ");
    extractStrings(left, right);
    // printf("Left: %s\nRight: %s\n", left, right);
    // findCard(left, C1, C2, C3, C4, C5, C6, C7);
    moveCard(C1, C2, C3, C4, C5, C6, C7, left, right);
    printBoard(&C1, &C2, &C3, &C4, &C5, &C6, &C7);
    return 0;
}

struct card *createNewCard(char suit, char rank)
{
    struct card *new_card = (struct card *)malloc(sizeof(struct card));
    new_card->suit = suit;
    new_card->rank = rank;
    new_card->revealed = false;
    return new_card;
};

struct node *createNewNode(struct card *card)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->card = card;
    new_node->next = NULL;
    return new_node;
};

void insertNode(node **headRef, card *card)
{
    node *newNode = createNewNode(card);
    node *temp = *headRef;
    if (*headRef == NULL)
    {
        *headRef = newNode;
        return;
    }
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp; // assign the previous node for the new node
}

void createDeck(node **deck)
{
    card *curr_card, *prev_card;

    FILE *fp;
    fp = fopen("cardDeck.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    else
    {
        printf("File opened successfully\n");
    }

    while (!feof(fp))
    {
        char line[4];
        fgets(line, 4, fp);
        if (strlen(line) == 2)
        {
            curr_card = (card *)malloc(sizeof(card));
            curr_card->suit = line[0];
            curr_card->rank = line[1];
            if (*deck == NULL)
            {
                *deck = createNewNode(curr_card);
                prev_card = curr_card;
            }
            else
            {
                insertNode(deck, curr_card);
                prev_card = curr_card;
            }
        }
        else if (strlen(line) == 3)
        {
            line[2] = '\0';
            curr_card = (card *)malloc(sizeof(card));
            curr_card->suit = line[0];
            curr_card->rank = line[1];
            if (*deck == NULL)
            {
                *deck = createNewNode(curr_card);
                prev_card = curr_card;
            }
            else
            {
                insertNode(deck, curr_card);
                prev_card = curr_card;
            }
        }
    }

    fclose(fp);
}

void printNode(const struct node *node)
{
    if (node == NULL)
    {
        printf("Node is null\n");
    }
    else
    {
        if (node->card->revealed == false)
        {
            printf("[]\n");
        }
        else
        {

            printf("%c%c\n",
                   node->card->rank,
                   node->card->suit);
        }
    }
}

void printList(const struct node *list)
{
    printf("Printing list:\n");
    const struct node *t;
    t = list;
    if (t == NULL)
    { // if the list is empty, print a message indicating that
        printf("list is empty\n");
    }
    else
    {
        while (t)
        {
            printNode(t); // print out the current person in line
            t = t->next;  // move to the next person in line
        }
    }
}

int countNodes(const struct node *list)
{
    const struct node *t = list;
    int count = 0;

    while (t != NULL)
    {
        count++;
        t = t->next;
    }

    // printf("The amount of nodes is %d\n", count);
    return count;
}

node *getLastNode(node *head)
{
    node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    printf("Last node is: ");
    printNode(current);
    return current;
}

node *removeFirstNode(node **head)
{
    if (*head == NULL)
    {
        // list is empty
        return NULL;
    }

    node *firstNode = *head;
    *head = (*head)->next;
    firstNode->next = NULL;
    return firstNode;
}

void insertRandomPosition(node **head, node *newNode)
{
    if (*head == NULL)
    {
        // list is empty, insert at head
        *head = newNode;
        return;
    }

    int listLength = 0;
    node *current = *head;
    while (current != NULL)
    {
        listLength++;
        current = current->next;
    }

    int randomIndex = rand() % listLength;
    if (randomIndex == 0)
    {
        // insert at head
        newNode->next = *head;
        *head = newNode;
        return;
    }

    current = *head;
    for (int i = 0; i < randomIndex - 1; i++)
    {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void shuffleList(node **head)
{
    // Create a new empty list to hold shuffled nodes
    node *shuffledList = NULL;

    // Repeat 52 times
    for (int i = 0; i < NUM_CARDS; i++)
    {
        // Remove the first node from the original list
        node *removedNode = removeFirstNode(head);

        // Insert the removed node at a random position in the shuffled list
        insertRandomPosition(&shuffledList, removedNode);
    }

    // Update the original list with the shuffled nodes
    *head = shuffledList;
}

void dealCards(node **deck, node **C1, node **C2, node **C3, node **C4, node **C5, node **C6, node **C7)
{
    int i, j;
    int pileSizes[] = {1, 6, 7, 8, 9, 10, 11};
    int pileIndex = 0;
    int cardsDealt = 0;

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < pileSizes[i]; j++)
        {
            node *node = removeFirstNode(deck);
            switch (pileSizes[i])
            {
            case 1:
                node->card->revealed = true;
                insertNode(C1, node->card);
                break;
            case 6:
                if (j > 0)
                {
                    node->card->revealed = true;
                }
                insertNode(C2, node->card);
                break;
            case 7:
                if (j > 1)
                {
                    node->card->revealed = true;
                }
                insertNode(C3, node->card);
                break;
            case 8:
                if (j > 2)
                {
                    node->card->revealed = true;
                }
                insertNode(C4, node->card);
                break;
            case 9:
                if (j > 3)
                {
                    node->card->revealed = true;
                }
                insertNode(C5, node->card);
                break;

            case 10:
                if (j > 4)
                {
                    node->card->revealed = true;
                }
                insertNode(C6, node->card);
                break;
            case 11:
                if (j > 5)
                {
                    node->card->revealed = true;
                }
                insertNode(C7, node->card);
                break;

            default:
                break;
            }
            cardsDealt++;
        }
    }
}

node *findAndRemoveCard(node *c1, node *c2, node *c3, node *c4, node *c5, node *c6, node *c7, const char *cardString)
{
    // Call findCard() to search for the card
    node *foundNode = findCard(cardString, c1, c2, c3, c4, c5, c6, c7);

    if (foundNode != NULL)
    {
        // Save the head of the list after the found node
        node *nextNode = foundNode->next;

        // Remove the found node and everything after it
        if (foundNode->prev == NULL)
        {
            // The found node is the head of the list
            if (nextNode != NULL)
            {
                nextNode->prev = NULL;
            }
            c1 = nextNode;
            c2 = nextNode;
            c3 = nextNode;
            c4 = nextNode;
            c5 = nextNode;
            c6 = nextNode;
            c7 = nextNode;
            foundNode->next = NULL;
            return foundNode;
        }
        else
        {
            // The found node is not the head of the list
            foundNode->prev->next = NULL;
            foundNode->prev = NULL;
            return foundNode;
        }
    }
    else
    {
        return NULL;
    }
}

void moveCard(node *c1, node *c2, node *c3, node *c4, node *c5, node *c6, node *c7, const char *cardString, const char *destString)
{
    // Call findAndRemoveCard() to search for the card
    node *foundNode = findAndRemoveCard(c1, c2, c3, c4, c5, c6, c7, cardString);
    printf("\nfoundNode: %c%c\n", foundNode->card->rank, foundNode->card->suit);
    printList(foundNode);
    printList(c2);
    node *destNode = NULL;
    node *t = NULL;

    if (foundNode != NULL)
    {
        switch (destString[1])
        {
        case '1':
            destNode = c1;
            break;
        case '2':
            destNode = c2;
            break;
        case '3':
            destNode = c3;
            break;
        case '4':
            destNode = c4;
            break;
        case '5':
            destNode = c5;
            break;
        case '6':
            destNode = c6;
            break;
        case '7':
            destNode = c7;
            break;
        default:
            printf("\nInvalid destination\n");
            return;
        }

        // Insert the found node at the destination
        if (destNode == NULL)
        {
            // Destination not found
            printf("\nDestination not found\n");
        }
        else
        {
            t = destNode;
            while (t->next != NULL)
            {
                t = t->next;
            }
            t->next = foundNode;
            foundNode->prev = t;
            printf("\nCard moved\n");
            printList(c4);
        }
    }
    else
    {
        printf("\nCard not found\n");
    }
}


// node *findCard(const char *cardString, node *headRef) {
//     while (headRef != NULL) {
//         if (headRef->card->rank == toupper(cardString[0]) &&
//             headRef->card->suit == toupper(cardString[1])) {
//             printf("headRef is found and is %c%c", headRef->card->rank, headRef->card->suit); //debugging
//             return headRef;
//         }
//         headRef = headRef->next;
//     }
//     return NULL;
// }

node *findCard(const char *cardString, node *C1, node *C2, node *C3, node *C4, node *C5, node *C6, node *C7)
{
    node *temp;

    // Loop through all columns
    for (int i = 1; i <= 7; i++)
    {
        switch (i)
        {
        case 1:
            temp = C1;
            break;
        case 2:
            temp = C2;
            break;
        case 3:
            temp = C3;
            break;
        case 4:
            temp = C4;
            break;
        case 5:
            temp = C5;
            break;
        case 6:
            temp = C6;
            break;
        case 7:
            temp = C7;
            break;
        default:
            return NULL;
        }

        // Loop through nodes in column
        while (temp != NULL)
        {
            // Check if card matches
            if (temp->card->suit == toupper(cardString[1]) && temp->card->rank == toupper(cardString[0]))
            {
                printf("temp is found and is %c%c", temp->card->rank, temp->card->suit); // debugging
                return temp;
            }
            temp = temp->next;
        }
    }

    // Card not found
    return NULL;
}

void extractStrings(char *left, char *right)
{
    char buffer[256];
    if (fscanf(stdin, "%255s", buffer) == 1)
    {                                       // read up to 255 characters into buffer
        char *arrow = strstr(buffer, "->"); // find the arrow in the buffer
        if (arrow != NULL)
        {
            *arrow = '\0';            // terminate the left string at the arrow
            strcpy(left, buffer);     // copy the left string
            strcpy(right, arrow + 2); // copy the right string
        }
    }
}

void printBoard(node **C1, node **C2, node **C3, node **C4, node **C5, node **C6, node **C7)
{

    node *columns[7] = {*C1, *C2, *C3, *C4, *C5, *C6, *C7};
    char *column_names[7] = {"C1", "C2", "C3", "C4", "C5", "C6", "C7"};
    int max_len = 0;
    for (int i = 0; i < 7; i++)
    {
        int len = countNodes(columns[i]);
        if (len > max_len)
        {
            max_len = len;
        }
    }

    // Print column names
    for (int i = 0; i < 7; i++)
    {
        printf("%s\t", column_names[i]);
    }
    printf("\n");
    printf("------------------------------------------------------------\n");

    // Print nodes in each column
    for (int i = 0; i < max_len; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i < countNodes(columns[j]))
            {
                printNodeBoard(&columns[j], i);
                printf("\t");
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}

void printNodeBoard(node **column, int i)
{
    if (*column == NULL)
    {
        printf("[]");
    }
    else
    {
        node *curr = *column;
        for (int j = 0; j < i; j++)
        {
            if (curr == NULL)
            {
                printf("[]");
                return;
            }
            curr = curr->next;
        }
        if (curr == NULL || curr->card == NULL)
        {
            printf("[]");
        }
        else
        {
            if (curr->card->revealed == false)
            {
                printf("[]");
            }
            else
            {
                printf("%c%c", curr->card->rank, curr->card->suit);
            }
        }
    }
}
