#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxP 10
#define deck 52

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int i,r,j;
void sortLeaderboard(int player[], int playerCount){
    for(i = 0; i < playerCount - 1; i++){
        for(j = 0; j < playerCount - 1; j++){
            if(player[j] > player[j + 1]){
                swap(&player[j], &player[j + 1]);
            }
        }
    }
}

void initDeck(int cards[]){
    int index = 0;
    for(i = 0; i < 4; i++){           
        cards[index++] = 11;              
        for(j = 2; j <= 10; j++){     
            cards[index++] = j;
        }
        cards[index++] = 10;              
        cards[index++] = 10;              
        cards[index++] = 10;              
    }
}

void shuffleDeck(int cards[]){
    for(i = 0; i < deck; i++){
        int r = rand() % deck;
        swap(&cards[i], &cards[r]);
    }
} 

int main (){
	
int playerCount;
scanf("%d", &playerCount);
int player[playerCount];
int deckCards[deck];

    if(playerCount <= 0 || playerCount > maxP){
        printf("Too many Players\n");
        return 0;
    }

initDeck(deckCards);
shuffleDeck(deckCards);


    return 0;
}
