#include <stdio.h>

void showMenu() {
    printf("=== Welcome To BLACKJACK 21 ===\n");
    printf("1. Play Game\n");
    printf("2. How to Play Blackjack\n");
    printf("3. Exit The Game\n");
    printf("Choose: ");
}

int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Starting game...\n");
                break;
            case 2:
                printf("Rules Of The Game:\n");
                printf("Goal Is To Reach 21\n");
                printf("Ace can be 1 or 11\n");
                break;
            case 3:
                printf("Exit game\n");
                break;
            default:
                printf("Invalid choice\n");
        }

        printf("\n");

    } while (choice != 3);

    return 0;
}

