#include <stdlib.h>
#include <stdio.h>

struct Card{
    //int key;
    char color;
    int e; 
    char* element;
    int number;
    //int dbg;
};
struct Hand{
    struct Card *cards;
};
// ----------------------//
void rand_card(struct Card card){
    int color = (rand() % (4 - 1 + 1)) + 1; // 1-4
    switch(color){
        case 1:
            card.color = 'r';
            break;
        case 2:
            card.color = 'g';
            break;
        case 3:
            card.color = 'b';
            break;
        case 4:
            card.color = 'y';
            break;
    }
    card.e = (rand() % (3 - 1 + 1)) + 1; // 1-3
    switch(card.e){
        case 1:
            card.element = "fire ";
        case 2:
            card.element = "water";
        case 3:
            card.element = "snow ";
    }
    card.number = (rand() % (10 - 1 + 1)) + 1; // 1-10
}


void construct_hand(struct Hand hand){
    
    struct Card* temp = (struct Card*)malloc(sizeof(struct Card) * 5);
    hand.cards = temp;
    for (int i = 0; i<5; i++){
        rand_card(hand.cards[i]);
    }
};

void replace_card(struct Hand hand, int key){
    rand_card( hand.cards[key]);
}

int evaluate_round(struct Card c1, struct Card c2){
    if (c1.e == c2.e){
        if (c1.number == c2.number){
            return 0;
        }
        if (c1.number > c2.number){
            return 1;
        }
        else{
            return 2;
        }
    }
    int e1 = c1.e;
    //int e2 = c2.e
    switch(e1){
        case 1:
            if (c2.e == 3){
                return 1;
            }
            else{
                return 2;
            }
            break;
        case 2:
            if (c2.e == 1){
                return 1;
            }
            else{
                return 2;
            }
            break;
        case 3:
            if (c2.e == 2){
                return 1;
            }
            else{
                return 2;
            }
            break;
    }
}

void print_round(struct Hand p, struct Hand ai, int dbg){
    if(dbg){
        printf("AI hand(hidden):       Your hand:\n");
    }
    else{
        printf("AI hand:               Your hand:\n");
    }
    for (int i = 0; i<5; i++){
        if(dbg){
            printf("%i %s %c", ai.cards[i].number, ai.cards[i].element, ai.cards[i].color);
        }
        else{
            printf("X XX X");
        }
        printf("            ");
        printf("%i %s %c\n", p.cards[i].number, p.cards[i].element, p.cards[i].color);
    }

}

//---------------------//
int main(int argc, char** argv){
    // start game- settings
    printf("\n---------------------\n\n"); 
    printf("Card Jitsu main menu.\n"); 
    char input;
    int dbg;
    int ask = 1;

    while (ask == 1) {
        printf("Type 'd' for debug mode or 'p' to start a game.\n");
        scanf(" %c", &input);
        if (input == 'd'){
            dbg = 1;
            ask = 0;
            //printf("dbgd");
        }
        else if (input == 'p') {
            dbg = 0;
            ask = 0;
            //printf("dbgp");
        }
        else {
            printf("Invalid input.\n");
        }
    }

    printf("\n---------------------\n\n"); 
    printf("Initializing Decks.\n"); 

    // initialize decks
    struct Hand player;
    struct Hand ai;
    construct_hand(player);
    construct_hand(ai);


    printf("\n---------------------\n\n"); 
    printf("Starting Game.\n"); 
    // start turns until win
    int card;
    int ocard;
    int win; // 0 = neither, 1 = player, 2 = ai
    int invalidcard;
    int winner;
    do {
        print_round(player, ai, dbg);
        invalidcard = 1;
        while (invalidcard){
            printf("Which card would you like to play? (input 1-5)\n");
            scanf("%d", &card);
            if(card >= 1 && card <=5){
                invalidcard=0;
            }
            else{
                printf("Input Invalid. Must be integer from 1-5.\n");
            }
        }
        
        printf("You have chosen card: %i %s %c\n", player.cards[card].number, player.cards[card].element, player.cards[card].color);
        printf("Your opponent is thinking.\n");
        printf("Oponent: ...\n");
        ocard = (rand() % (5 - 1 + 1)) + 1;
        printf("Your opponent has chosen card: %i %s %c\n", ai.cards[ocard].number, ai.cards[ocard].element, ai.cards[ocard].color);

        winner = evaluate_round(player.cards[card], ai.cards[ocard]);
        switch(winner){
            case 0:
                printf("It's a tie!\n");
            break;
            case 1:
                printf("You have won the round!\n");
                win = 1;
            break;
            case 2:
                printf("Your opponenet has won the round!\n");
                win = 2;
            break;
        }

    } while (win = 0);
    /*
    for (int i = 0; i<5; i++){
        free(player.cards[i]);
        free(ai.cards[i]);
    }*/
    free(player.cards);
    free(ai.cards);
    printf("The one-round match is now over! Congrats to ");
    switch(win){
        case 1:
            printf("you ");
            break;
        case 2:
            printf("your opponent ");
            break;
    }
    printf("for winning the game. Good night!\n\n");
    return 0;
}
