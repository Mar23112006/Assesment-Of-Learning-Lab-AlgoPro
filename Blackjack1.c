#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//max player 10
#define maxP 10

//jumlah kartu dalam 1 deck ada 52
#define decksize 52

typedef struct {
    char name[100];
    int win;
    int lose;
    int draw;
} Player;

//banner
const char *BANNER =
"=================================\n"
"   BLACKJACK 676767 PASTI GACOR\n"
"=================================\n";

//menu
void showMenu() {
    printf("\n=== BLACKJACK MENU ===\n");
    printf("1. Play Game\n");
    printf("2. How to Play\n");
    printf("3. Search Player\n");
    printf("4. Show Leaderboard\n");
    printf("5. Exit\n");
    printf("Choose: ");
}

//swap
void swap(Player *a, Player *b) {
    Player temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//sorting
void sortLeaderboard(Player players[], int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1; j++) {
            if (players[j].win < players[j + 1].win) {
                swap(&players[j], &players[j + 1]);
            }
        }
    }
}

//searching
int searchPlayer(Player players[], int count, char key[]) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(players[i].name, key) == 0) {
            return i;
        }
    }
    return -1;
}

//inisialisasi deck kartu
void Deck(char deck[]) {
    char values[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int i, j, idx = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 13; j++) {
            deck[idx] = values[j];
            idx++;
        }
    }
}

//shuffle deck
void shuffleDeck(char deck[]) {
    int i, r;
    char temp;

    for (i = 0; i < 52; i++) {
        r = rand() % 52;
        temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

//draw kartu
char drawCard(char deck[], int *top) {
    char card = deck[*top];
    (*top)++;
    return card;
}

//value masing masing kartu di deck
int cardValue(char c) {
    if (c >= '2' && c <= '9') {
        return c - '0';
    }
    if (c == 'T' || c == 'J' || c == 'Q' || c == 'K') {
        return 10;
    }
    if (c == 'A') {
        return 11; 
    }
    return 0;
}



int main() {

    int playerCount;
    int i;
    int choice;

    printf("%s", BANNER); // call bannernya 

    printf("Input number of players (max %d): ", maxP);
    scanf("%d", &playerCount); //input jumlah player

    if (playerCount > maxP) {
        playerCount = maxP;
    }

	//input data players 
    Player players[maxP];
    for (i = 0; i < playerCount; i++) {
        printf("Player %d name: ", i + 1);
        scanf("%s", players[i].name);
        players[i].win = 0;
        players[i].lose = 0;
        players[i].draw = 0;
    }

    //menu loop 
    do {
        showMenu();
        scanf("%d", &choice); 

        switch (choice) { 

            case 1: {
            int cur;
            printf("\nChoose player (1-%d): ", playerCount);
            scanf("%d", &cur);
            cur--; // jadi index array

            if (cur < 0 || cur >= playerCount) {
                printf("Invalid player!\n");
                break;
            }

    			char deck[52];
    			int top = 0;
    			int score = 0;
    			int i;
    			char choiceHS;
    			char card;

    			srand(time(NULL));     // seed random
    			Deck(deck);        // isi deck
    			shuffleDeck(deck);     // acak deck

    			printf("\n[Play Game - Draw Test]\n");
    			printf("Your cards:\n");

    			for (i = 0; i < 2; i++) {
    			card = drawCard(deck, &top);
    			score += cardValue(card);   
    			printf("%c ", card);
			}
				printf("\nScore: %d\n", score);

    			
    			while (1) {
    			if (score > 21) {
            	printf("BUST! You lose.\n");
            	break;
            	
        			}
        		printf("\nHit (H) or Stand (S)? ");
        		scanf(" %c", &choiceHS);   

        		if (choiceHS == 'H' || choiceHS == 'h') {
            	card = drawCard(deck, &top);
				score += cardValue(card);      // <-- TAMBAH
				printf("You draw: %c\n", card);
				printf("Score: %d\n", score);
        			}
        			
        		else if (choiceHS == 'S' || choiceHS == 's') {
            	int dealerScore = 0;

    			printf("You stand with score %d\n", score);
    			printf("\nDealer's turn:\n");

    			// dealer draw sampai >= 17
    			while (dealerScore < 17) {
        		card = drawCard(deck, &top);
        		dealerScore += cardValue(card);
        		printf("Dealer draws: %c\n", card);
    		}

    			printf("Dealer score: %d\n", dealerScore);

    		// kondisi menang / kalah
    			if (dealerScore > 21) {
        		printf("Dealer BUST! YOU WIN!\n");
                players[cur].win++;
    				}
    			else if (score > dealerScore) {
        		printf("YOU WIN!\n");
                players[cur].win++;
    				}
    			else if (score < dealerScore) {
        		printf("YOU LOSE!\n");
                players[cur].lose++;
    				}
    			else {
        		printf("DRAW!\n");
                players[cur].draw++;
    				}
				break;
			}
        		else {
            		printf("Invalid choice!\n");
        			}
   				}

    			printf("\n");
    			break;
			}


            case 2:
                printf("\n[How to Play]\n");
                printf("- Goal: Reach total card value as close to 21 as possible\n");
    			printf("- Number cards 2-10 are worth their face value\n");
    			printf("- Jack (J), Queen (Q), King (K) are worth 10\n");
    			printf("- Ace (A) can be worth 1 or 11\n");
    			printf("- Cards are to be taken randomly from the deck\n");
                printf("- More than 21 = You Lose\n");
                break;

            case 3: {
                char key[100];
                int idx;

                printf("\nSearch player name: ");
                scanf("%s", key);

                idx = searchPlayer(players, playerCount, key);
                if (idx == -1) {
                    printf("Player not found.\n");
                } else {
                    printf("Player found!\n");
                    printf("Name: %s\n", players[idx].name);
                    printf("Win : %d\n", players[idx].win);
                    printf("Win : %d\n", players[idx].lose);
                    printf("Win : %d\n", players[idx].draw);
                }
                break;
            }

            case 4:
                sortLeaderboard(players, playerCount);
                printf("\n=== LEADERBOARD ===\n");
                for (i = 0; i < playerCount; i++) {
                    printf("%d. %s - Win: %d - Lose: %d - Draw: %d\n",
                           i + 1,
                           players[i].name,
                           players[i].win,
                           players[i].lose,
                           players[i].draw);
                }
                break;

            case 5:
                printf("\nExit Game. Thank you!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
