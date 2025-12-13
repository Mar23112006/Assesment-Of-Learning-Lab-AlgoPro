#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxP 10
#define deck 52

//banner
const char *BANNER =
"=================================\n"
"   BLACKJACK676767 PASTI GACOR\n"
"=================================\n";

//swap
void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//sorting
void sortLeaderboard(int player[], int playerCount){
    for(int i = 0; i < playerCount - 1; i++){
        for(int j = 0; j < playerCount - 1; j++){
            if(player[j] < player[j + 1]){
                swap(&player[j], &player[j + 1]);
            }
        }
    }
}

int main (){

printf("%s", BANNER);

int playerCount;
scanf("%d", &playerCount);
if(playerCount > maxP){
    playerCount = maxP;
}

//input player
int player[maxP];
    for(int i = 0; i < playerCount; i++){
        scanf("%d", &player[i]);
    }

sortLeaderboard(player, playerCount);

//print leaderboard
    for(int i = 0; i < playerCount; i++){
        printf("%d ", player[i]);
    }

    return 0;
}