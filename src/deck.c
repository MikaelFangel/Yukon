#include "deck.h"
#include "view.h"

Card clubs[SUIT_SIZE];
Card diamonds[SUIT_SIZE];
Card hearts[SUIT_SIZE];
Card spades[SUIT_SIZE];

Card *deck[4] = {clubs, diamonds, hearts, spades};

/**
 * @authors s215797 Mikael Fangel (45%), s215812 Silja Ye-Chi Sandersen (45%), s215805 Mads Sørensen (10%)
 */
void fillSuits() {
    char suits[4] = {'C', 'D', 'H', 'S'};

    for (int i = 0; i < 4; i++) {
        deck[i][0].value = 'A';
        deck[i][0].suit = suits[i];

        for (int j = 1; j < 10; ++j) {
            deck[i][j].value = (j + 1) + '0';
            deck[i][j].suit = suits[i];
        }

        deck[i][9].value = 'T';
        deck[i][9].suit = suits[i];
        deck[i][10].value = 'J';
        deck[i][10].suit = suits[i];
        deck[i][11].value = 'Q';
        deck[i][11].suit = suits[i];
        deck[i][12].value = 'K';
        deck[i][12].suit = suits[i];
    }
}

/**
 * @authors s215805 Mads Sørensen (60%), s215812 Silja Ye-Chi Sandersen (40%)
 * @param deck_card
 * @return if duplicate card returns 1. If invalid card returns 2. If existing card returns 0
 */
int checkCard(struct ListCard *deck_card) {
    int suit;
    switch (deck_card->suit) {
        case 'C' :
            suit = 0;
            break;
        case 'D' :
            suit = 1;
            break;
        case 'H' :
            suit = 2;
            break;
        case 'S' :
            suit = 3;
            break;
        default:
            return 2;
    }

    int value;
    switch (deck_card->value) {
        case 'A':
            value = 0;
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // Calculates the corresponding number of its ASCII value
            value = deck_card->value - 49;
            break;
        case 'T':
            value = 9;
            break;
        case 'J':
            value = 10;
            break;
        case 'Q':
            value = 11;
            break;
        case 'K':
            value = 12;
            break;
        default:
            return 2;
    }

    if (!deck[suit][value].existsInGame) {
        deck[suit][value].existsInGame = true;
        deck_card->existsInGame = true;
        return 0;
    } else return 1;
}

/**
 * Load a deck from a file. File must be a list of cards represented with 2 characters
 * eg. Ace of Hearts - "AH" with newline after each card. Returns the deck in a linked list
 * Used in LD command
 * @author s215805 Mads Sørensen
 * @param fptr
 * @return cardDeck
 */
Linked_list *loadDeck(FILE *fptr) {
    fillSuits();
    char line[4];
    Linked_list *cardDeck = createLinkedList();
    // While file not empty, read a line, create a card, and add it to linked list.
    int lineNum = 1;
    while (fgets(line, sizeof(line), fptr) != NULL) {
        struct ListCard newCard;
        newCard.value = line[0];
        newCard.suit = line[1];

        char buffer[40];
        char *num;

        int check = checkCard(&newCard);

        if (check != 0 && asprintf(&num, "%d", lineNum) != -1) {
            if (check == 1)
                strcat(strcpy(buffer, "ERROR! Duplicate card found on line "), num);
            else {
                strcat(strcpy(buffer, "ERROR! Invalid card found on line "), num);
            }
            generateEmptyView("LD", buffer);
            deleteLinkedList(cardDeck);
            return NULL;
        } else {
            appendCard(cardDeck, newCard);
            ++lineNum;
        }
    }
    return cardDeck;
}

/**
 * Save deck to a file
 * Used in SD command
 * @author s215805 Mads Sørensen
 * @param list
 */
void saveDeck(Linked_list *list, FILE *fptr) {
    char line[3];
    line[2] = '\n';
    struct ListCard *node = list->head;
    // While linked list not null, write a card to the file.
    while (node != NULL) {
        struct ListCard *card = node;
        line[0] = card->value;
        line[1] = card->suit;
        fwrite(line, 1, sizeof line, fptr);
        node = node->next;
    }
}

// int checkIfFileExists(const char * filename) {
//     FILE* file;
//     if (file = fopen(filename, "r")) {
//         fclose(file);
//         return 1;
//     }
//     return 0;
// }