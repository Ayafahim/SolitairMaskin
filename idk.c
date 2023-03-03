#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CARDS 52

// Structure for a card
typedef struct card
{
    char suit;
    char rank;
    char value[2];
    struct card *next;
} card;

typedef struct pile
{
    card *head;
    int num_cards;
} pile;

// Function to create a new card
struct card *new_card(char suit, char rank)
{
    struct card *new_card = (struct card *)malloc(sizeof(struct card));
    new_card->suit = suit;
    new_card->rank = rank;
    new_card->value[0] = suit;
    new_card->value[1] = rank;
    new_card->next = NULL;
    return new_card;
};

// remove a card from the beginning of the list
card *shift(pile *pile)
{
    pile->num_cards--;
    card *old_head = pile->head;
    pile->head = old_head->next;

    card *card = old_head->value;
    free(old_head);
    return card;
}

void *deleteNode(struct pile *pile)
{

    if (pile == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // Traverse the linked list to find the node before the specified position
    pile->num_cards--;
    card *old_head = pile->head;

    // Check if the specified position is valid
    if (old_head == NULL)
    {
        printf("Invalid position\n");
    }

    pile->head = old_head->next;
    card *card = old_head;
    free(old_head);
    printf(card->value);
}

// append to the beginning of the list
void unshift(pile *pile, card *card)
{
    struct card *new_head = card;
    new_head->next = pile->head;
    pile->head = new_head;
    pile->num_cards++;
}

// Function to create a new deck of cards
void create_deck(struct card **deck)
{

    struct card *curr_card, *prev_card;

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
        char line[3];
        fgets(line, 3, fp);
        if (strlen(line) == 2)
        {
            curr_card = new_card(line[0], line[1]);
            if (*deck == NULL)
            {
                *deck = curr_card;
                prev_card = curr_card;
            }
            else
            {
                prev_card->next = curr_card;
                prev_card = curr_card;
            }
        }
    }

    fclose(fp);
}

// void shuffle_pile(pile *pile) {
//   int shuffle_times = pile->num_cards * 10;
//   for (int i = 0; i < shuffle_times; i++) {
//     // unshift a card and insert to random place
//     int idx = rand() % pile->num_cards - 1;
//     card *card = shift(pile);
//     insert(pile, card, idx);
//   }
// }

// Function to deal the cards into 7 piles based on Yukon solitaire setup
void deal_cards(struct card **deck, struct card **piles)
{
    int i, j;
    struct card *curr_card, *prev_card;

    for (i = 0; i < 7; i++)
    {
        curr_card = *deck;
        prev_card = NULL;
        for (j = 0; j <= i; j++)
        {
            prev_card = curr_card;
            curr_card = curr_card->next;
        }
        prev_card->next = NULL;
        piles[i] = curr_card;
    }
}

// Function to print the contents of a pile
void print_pile(struct card *pile)
{
    struct card *curr_card = pile;
    while (curr_card != NULL)
    {
        printf("%c%c ", curr_card->suit, curr_card->rank);
        curr_card = curr_card->next;
    }
    printf("\n");
}

void printCard(const struct card *node)
{
    if (node == NULL)
    {
        printf("List is null\n");
    }
    else
    {
        printf("%s\n",
               node->value);
    }
}

void printDeck(struct card *deck)
{
    printf("Printing list:\n");
    const struct card *t;
    t = deck;
    if (t == NULL)
    { // if the list is empty, print a message indicating that
        printf("list is empty");
    }
    else
    {
        while (t)
        {
            printCard(t); // print out the current person in line
            t = t->next;  // move to the next person in line
        }
    }
}

int main()
{
    // Initialize variables
    struct card *deck = NULL;
    struct card *piles[7] = {NULL};

    // Create a deck of cards and shuffle it
    create_deck(&deck);
    struct pile *pile = &deck;

    if (deck == NULL)
    {
        printf("Deck is empty\n");
    }
    else
    {
        printf("Deck is not empty\n");
        printDeck(deck);
        // shuffle_deck(&deck);
        deleteNode(pile);
    }

    // Deal the cards into seven piles
    // deal_cards(&deck, piles);

    // Print out the contents of each pile
    // for (int i = 0; i < 7; i++) {
    //     printf("Pile %d: ", i + 1);
    //     print_pile(piles[i]);
    // }

    return 0;
}
