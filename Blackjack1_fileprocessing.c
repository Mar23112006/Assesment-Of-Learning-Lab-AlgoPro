#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXP 10
#define DECKSIZE 52
#define DATA_FILE "players.txt"

typedef struct {
    char name[100];
    int win;
    int lose;
    int draw;
} Player;

const char *BANNER =
"===========================================\n"
"      BLACKJACK 676767 PASTI GACOR\n"
"===========================================\n";

void showMenu() {
    printf("\n=== BLACKJACK MENU ===\n");
    printf("1. Play Game\n");
    printf("2. How to Play\n");
    printf("3. Search Player\n");
    printf("4. Show Leaderboard\n");
    printf("5. Save & Exit\n");
    printf("Choose: ");
}

void swap(Player *a, Player *b) {
    Player temp = *a;
    *a = *b;
    *b = temp;
}

void sortLeaderboard(Player players[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (players[j].win < players[j + 1].win) {
                swap(&players[j], &players[j + 1]);
            }
        }
    }
}

int searchPlayer(Player players[], int count, const char key[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, key) == 0) return i;
    }
    return -1;
}

int loadPlayers(Player players[], int *playerCount) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) return 0;

    int n = 0;
    if (fscanf(fp, "%d", &n) != 1) {
        fclose(fp);
        return 0;
    }

    if (n < 0) n = 0;
    if (n > MAXP) n = MAXP;

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%99s %d %d %d",
                   players[i].name,
                   &players[i].win,
                   &players[i].lose,
                   &players[i].draw) != 4) {
            n = i;
            break;
        }
    }

    fclose(fp);
    *playerCount = n;
    return 1;
}

void savePlayers(Player players[], int playerCount) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (!fp) {
        printf("ERROR FILE NOT FOUND.\n");
        return;
    }

    fprintf(fp, "%d\n", playerCount);
    for (int i = 0; i < playerCount; i++) {
        fprintf(fp, "%s %d %d %d\n",
                players[i].name,
                players[i].win,
                players[i].lose,
                players[i].draw);
    }

    fclose(fp);
    printf("Data saved to '%s'.\n", DATA_FILE);
}

void Deck(char deck[]) {
    char values[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
    int idx = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            deck[idx++] = values[j];
        }
    }
}

void shuffleDeck(char deck[]) {
    for (int i = 0; i < DECKSIZE; i++) {
        int r = rand() % DECKSIZE;
        char temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }
}

char drawCard(char deck[], int *top) {
    char card = deck[*top];
    (*top)++;
    return card;
}

int cardValue(char c) {
    if (c >= '2' && c <= '9') return c - '0';
    if (c == 'T' || c == 'J' || c == 'Q' || c == 'K') return 10;
    if (c == 'A') return 11;
    return 0;
}

int main() {
    Player players[MAXP];
    int playerCount = 0;
    int choice;

    printf("%s", BANNER);

    if (loadPlayers(players, &playerCount) && playerCount > 0) {
        printf("Loaded player data from '%s' (total: %d)\n", DATA_FILE, playerCount);
    } else {
        printf("No player data found. Creating new players.\n");
        printf("Input number of players (max %d): ", MAXP);
        scanf("%d", &playerCount);

        if (playerCount < 1) playerCount = 1;
        if (playerCount > MAXP) playerCount = MAXP;

        for (int i = 0; i < playerCount; i++) {
            printf("Player %d name: ", i + 1);
            scanf("%99s", players[i].name);
            players[i].win = 0;
            players[i].lose = 0;
            players[i].draw = 0;
        }

        savePlayers(players, playerCount);
    }

    do {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            continue;
        }

        switch (choice) {
            case 1: {
                int cur;
                printf("\nChoose player (1-%d): ", playerCount);
                scanf("%d", &cur);
                cur--;

                if (cur < 0 || cur >= playerCount) {
                    printf("Invalid player!\n");
                    break;
                }

                char deck[DECKSIZE];
                int top = 0;
                int score = 0;
                char choiceHS;
                char card;

                srand((unsigned)time(NULL));
                Deck(deck);
                shuffleDeck(deck);

                printf("\n[Play Game]\nYour cards:\n");
                for (int i = 0; i < 2; i++) {
                    card = drawCard(deck, &top);
                    score += cardValue(card);
                    printf("%c ", card);
                }
                printf("\nScore: %d\n", score);

                while (1) {
                    if (score > 21) {
                        printf("BUST! You lose.\n");
                        players[cur].lose++;
                        break;
                    }

                    printf("\nHit (H) or Stand (S)? ");
                    scanf(" %c", &choiceHS);

                    if (choiceHS == 'H' || choiceHS == 'h') {
                        card = drawCard(deck, &top);
                        score += cardValue(card);
                        printf("You draw: %c\n", card);
                        printf("Score: %d\n", score);
                    } else if (choiceHS == 'S' || choiceHS == 's') {
                        int dealerScore = 0;

                        printf("You stand with score %d\n", score);
                        printf("\nDealer's turn:\n");

                        while (dealerScore < 17) {
                            card = drawCard(deck, &top);
                            dealerScore += cardValue(card);
                            printf("Dealer draws: %c\n", card);
                        }

                        printf("Dealer score: %d\n", dealerScore);

                        if (dealerScore > 21) {
                            printf("Dealer BUST! YOU WIN!\n");
                            players[cur].win++;
                        } else if (score > dealerScore) {
                            printf("YOU WIN!\n");
                            players[cur].win++;
                        } else if (score < dealerScore) {
                            printf("YOU LOSE!\n");
                            players[cur].lose++;
                        } else {
                            printf("DRAW!\n");
                            players[cur].draw++;
                        }
                        break;
                    } else {
                        printf("Invalid choice!\n");
                    }
                }

                savePlayers(players, playerCount);
                break;
            }

            case 2:
                printf("\n[How to Play]\n");
                printf("- Goal: Reach total card value as close to 21 as possible\n");
                printf("- Number cards 2-10 are worth their face value\n");
                printf("- Jack (J), Queen (Q), King (K) are worth 10\n");
                printf("- Ace (A) in this program is worth 11 (versi simple)\n");
                printf("- Cards are taken randomly from the deck\n");
                printf("- More than 21 = You Lose\n");
                break;

            case 3: {
                char key[100];
                printf("\nSearch player name: ");
                scanf("%99s", key);

                int idx = searchPlayer(players, playerCount, key);
                if (idx == -1) {
                    printf("Player not found.\n");
                } else {
                    printf("Player found!\n");
                    printf("Name: %s\n", players[idx].name);
                    printf("Win : %d\n", players[idx].win);
                    printf("Lose: %d\n", players[idx].lose);
                    printf("Draw: %d\n", players[idx].draw);
                }
                break;
            }

            case 4:
                sortLeaderboard(players, playerCount);
                printf("\n=== LEADERBOARD ===\n");
                for (int i = 0; i < playerCount; i++) {
                    printf("%d. %s - Win: %d - Lose: %d - Draw: %d\n",
                           i + 1,
                           players[i].name,
                           players[i].win,
                           players[i].lose,
                           players[i].draw);
                }
                break;

            case 5:
                printf("\nSaving & Exit...\n");
                savePlayers(players, playerCount);
                printf("Thank you!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
