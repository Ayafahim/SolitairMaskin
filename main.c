#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum
{
    SUIT_HEART,
    SUIT_SPADE,
    SUIT_CLUB,
    SUIT_DIAMOND // ♥♠♣♦
};

enum
{
    RANK_A,
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_J,
    RANK_Q,
    RANK_K
};

typedef struct card
{
    int suit;
    int rank;
    int revealed;
} card;

typedef struct card_node
{
    card *card;
    struct card_node *next;
} card_node;

typedef struct pile
{
    card_node *head;
    int num_cards;
} pile;

typedef struct game_state
{
    //array of pointers to piles
    pile **piles;
    int pile_count;
} game_state;

// Create a new empty pile
pile *create_pile()
{
    pile *p = malloc(sizeof(pile));
    p->head = NULL;
    p->num_cards = 0;
    return p;
}

// Insert a card into a pile
void insert_card(pile *p, card *c)
{
    card_node *n = malloc(sizeof(card_node));
    n->value = c;
    n->next = p->head;
    p->head = n;
    p->num_cards++;
}

// Shuffle the deck of cards
void shuffle_deck(card **deck, int deck_size)
{
    srand(time(NULL));
    for (int i = deck_size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        card *temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

// Load the card deck from a file
card **read_deck(const char *filename, int *deck_size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: could not open file '%s'\n", filename);
        exit(1);
    }

    // Count the number of lines in the file
    int lines = 0;
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            lines++;
        }
    }

    // Allocate memory for the deck of cards
    card **deck = malloc(lines * sizeof(card *));
    *deck_size = lines;

    // Rewind the file pointer to the beginning
    rewind(file);

    // Read the cards from the file
    for (int i = 0; i < lines; i++)
    {
        char suit;
        char rank;
        fscanf(file, "%c%c\n", &rank, &suit);
        card *c = malloc(sizeof(card));
        switch (suit)
        {
        case 'H':
            c->suit = SUIT_HEART;
            break;
        case 'S':
            c->suit = SUIT_SPADE;
            break;
        case 'C':
            c->suit = SUIT_CLUB;
            break;
        case 'D':
            c->suit = SUIT_DIAMOND;
            break;
        default:
            fprintf(stderr, "Error: invalid suit '%c' in file '%s'\n", suit, filename);
        }
    }
}

int main() {
    // read the deck from a file
    card *deck = read_deck("cardDeck.txt",52);
    if (!deck) {
        printf("Failed to read the deck from file.\n");
        return 1;
    }

    // shuffle the deck
    srand(time(NULL));
    shuffle_deck(deck, 52);

    return 0;
}