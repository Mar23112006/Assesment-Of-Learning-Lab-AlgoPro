#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//max player 10
#define maxP 10

//jumlah kartu dalam 1 deck ada 52
#define deck 52

typedef struct {
char name[100];
int win;
} Player;

//banner
const char *BANNER =
"=================================\n"
"   BLACKJACK676767 PASTI GACOR\n"
"=================================\n";

//swap
void swap(Player *a, Player *b){
    Player temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//sorting
void sortLeaderboard(Player player[], int playerCount){
    for(int i = 0; i < playerCount - 1; i++){
        for(int j = 0; j < playerCount - 1; j++){
            if(player[j].win < player[j + 1].win){ //sorting secara descending
                swap(&player[j], &player[j + 1]);
            }
        }
    }
}

//searching
int searchPlayer(Player players[], int playerCount, char key[]){
    for(int i = 0; i < playerCount; i++){
        if(strcmp(players[i].name, key) == 0){
            return i;
        }
    }
    return -1;
}


int main (){

printf("%s", BANNER);

int playerCount;
scanf("%d", &playerCount); //input jumlah player
if(playerCount > maxP){
    playerCount = maxP;
}

//input player
Player player[maxP];
    for(int i = 0; i < playerCount; i++){
        scanf("%s", player[i].name);
        player[i].win = 0;   
    }

//main blackjack

//searching
char key[100];
    printf("\nSearch player name: ");
    scanf("%s", key);

    int idx = searchPlayer(player, playerCount, key);

    if(idx == -1){
        printf("Player not found.\n");
    } else {
        printf("Player found!\n");
        printf("Nama: %s\n", player[idx].name);
        printf("Win : %d\n", player[idx].win);
    }
    
sortLeaderboard(player, playerCount);

//print leaderboard
    for(int i = 0; i < playerCount; i++){
    printf("%d. %s - Win: %d\n", i+1, player[i].name, player[i].win);
    }

    return 0;
}