#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARDS 52


typedef struct card
{
    char suit;
    char rank;
} card;

typedef struct node{

    struct card *card;
    struct node *next;
} node;


struct card *createNewCard(char suit, char rank);
struct node *createNewNode(struct card *card);
void insertNode(node** headRef, card* card);
void createDeck(node** deck);
void printNode(const struct node *node);
void printDeck(const struct node *list);
int countNodes(const struct node *list);
node* removeFirstNode(node** head);
void insertRandomPosition(node** head, node* newNode);
void shuffleList(node** head);




int main() {
    node* head = NULL;
    createDeck(&head);
    printDeck(head);
    countNodes(head);
  //  node* firstNode = removeFirstNode(&head);
    printf("Shuffeling...\n");
    shuffleList(&head);
  //  insertRandomPosition(&head, firstNode);
    printDeck(head);
    printf("Shuffeling Again...\n");
    shuffleList(&head);
    printDeck(head);
    return 0;
}

struct card *createNewCard(char suit, char rank)
{
    struct card *new_card = (struct card *)malloc(sizeof(struct card));
    new_card->suit = suit;
    new_card->rank = rank;
    return new_card;
};

struct node *createNewNode(struct card *card)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->card = card;
    new_node->next = NULL;
    return new_node;
};

void insertNode(node** headRef, card* card) {
    node* newNode = createNewNode(card);
    node* temp = *headRef;
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void createDeck(node** deck) {
    card* curr_card, *prev_card;

    FILE* fp;
    fp = fopen("cardDeck.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    } else {
        printf("File opened successfully\n");
    }

    while (!feof(fp)) {
        char line[4];
        fgets(line, 4, fp);
        if (strlen(line) == 2) {
            curr_card = (card*)malloc(sizeof(card));
            curr_card->suit = line[0];
            curr_card->rank = line[1];
            if (*deck == NULL) {
                *deck = createNewNode(curr_card);
                prev_card = curr_card;
            } else {
                insertNode(deck, curr_card);
                prev_card = curr_card;
            }
        } else if (strlen(line) == 3) {
            line[2] = '\0';
            curr_card = (card*)malloc(sizeof(card));
            curr_card->suit = line[0];
            curr_card->rank = line[1];
            if (*deck == NULL) {
                *deck = createNewNode(curr_card);
                prev_card = curr_card;
            } else {
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
        printf("List is null\n");
    }
    else
    {
        printf("%c%c\n",
               node->card->rank,
               node->card->suit);
    }
}

void printDeck(const struct node *list)
{
    printf("Printing list:\n");
    const struct node *t;
    t = list;
    if (t == NULL)
    { // if the list is empty, print a message indicating that
        printf("list is empty");
    }
    else
    {
        while (t)
        {
            printNode(t);      // print out the current person in line
            t = t->next; // move to the next person in line
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
        
    printf("The amount of nodes is %d\n", count);
    return count;
}

node* removeFirstNode(node** head) {
    if (*head == NULL) {
        // list is empty
        return NULL;
    }

    node* firstNode = *head;
    *head = (*head)->next;
    firstNode->next = NULL;
    return firstNode;
}

void insertRandomPosition(node** head, node* newNode) {
    if (*head == NULL) {
        // list is empty, insert at head
        *head = newNode;
        return;
    }

    int listLength = 0;
    node* current = *head;
    while (current != NULL) {
        listLength++;
        current = current->next;
    }

    int randomIndex = rand() % listLength;
    if (randomIndex == 0) {
        // insert at head
        newNode->next = *head;
        *head = newNode;
        return;
    }

    current = *head;
    for (int i = 0; i < randomIndex - 1; i++) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void shuffleList(node** head) {
    // Create a new empty list to hold shuffled nodes
    node* shuffledList = NULL;

    // Repeat 52 times
    for (int i = 0; i < NUM_CARDS; i++) {
        // Remove the first node from the original list
        node* removedNode = removeFirstNode(head);

        // Insert the removed node at a random position in the shuffled list
        insertRandomPosition(&shuffledList, removedNode);
    }

    // Update the original list with the shuffled nodes
    *head = shuffledList;
}

