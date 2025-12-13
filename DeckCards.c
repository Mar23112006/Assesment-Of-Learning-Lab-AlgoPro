#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK 52

int i;


void initDeck(char deck[]){
    int index = 0;

    for(i = 0; i < 13; i++) deck[index++] = 'A';
    for(i = 0; i < 13; i++) deck[index++] = 'J';
    for(i = 0; i < 13; i++) deck[index++] = 'Q';
    for(i = 0; i < 13; i++) deck[index++] = 'K';
}


void shuffleDeck(char deck[]){
    for(i = 0; i < DECK; i++){
        int r = rand() % DECK;
        char temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}


int getCardValue(char card){
    if(card == 'A')
        return 1;
    else
        return 10;
}

int main(){
    char deckCards[DECK];
    int pickCount;
    int total = 0;

    srand(time(NULL));

    initDeck(deckCards);
    shuffleDeck(deckCards);

    
    printf("How many cards do you want to pick? ");
    scanf("%d", &pickCount);

    
    if(pickCount <= 0 || pickCount > DECK){
        printf("Invalid number of cards!\n");
        return 0;
    }

    printf("Cards drawn (numeric values):\n");

    for(i = 0; i < pickCount; i++){
        int value = getCardValue(deckCards[i]);
        printf("%d ", value);
        total += value;
    }

    printf("\nTotal value: %d\n", total);

    return 0;
}

