void printNodeBoard(node **column, int i) {
    if (*column == NULL || *column + i == NULL) {
        printf("[]");
    } else {
        if ((*column + i)->card->revealed == false) {
            printf("[]");
        } else {
            printf("%c%c", (*column + i)->card->rank, (*column + i)->card->suit);
        }
    }
}