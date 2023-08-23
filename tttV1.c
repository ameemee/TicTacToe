#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// global constant variables
//     These are verdicts:
const char CAT_GAME = 'C';
const char X_ASCII = 'X';
const char O_ASCII = 'O';
const char NOTHING_YET = 'N';

// global variables
bool stay = true; // true: to stay in the game
int checked_verdict;
int board_size;
char* board_array; // 1D board
//2D board char** board_array;

char checker() {
    // 1D SET UP

    // CHECK HORIZONTALS (ROWS)
        // 3(0)+0, 3(0)+1, .., 3(0)+(board_size -1) equal
        // OR
        // 3(1)+0, 3(1)+1, .., 3(1)+(board_size -1) equal
        // ...
        // 3(board_size -1)+0, 3(board_size -1)+1, .., 3(board_size -1)+(board_size -1) equal

    char first;
    int count = 0;

    for (int row = 0; row < board_size; ++row) {
        count = 0; // reset! don't carry over from previous rows
         // grab the first in row.
        first = board_array[board_size * row + 0];

        // disregard this row if it's clearly not full
        if (first == ' ') {
            continue; // ie. check next row
        }

        // count how many occurances of the first item exist in the row
        for (int col = 0; col < board_size; ++col) {
            // keep comparing said row's entries with first_in_row.
            if (first == board_array[board_size * row + col]) {
                count++;
            }
        }

        // is the row full of the first item?
        if (count == board_size) {
            return first;
        }
    }

    // CHECK VERTICALS (COLS)

    for (int col = 0; col < board_size; ++col) {
        count = 0;
        first = board_array[col]; // always grab the first row (3*0+col)

        if (first == ' ') {
            continue; 
        }

        for (int row = 0; row < board_size; ++row) {
            // keep comparing said row's entries with first_in_col.
            if (first == board_array[board_size * row + col]) {
                count++;
            }
        }

        if (count == board_size) {
            return first;
        }
        // 3(0)+0, 3(1)+0, .. , 3(board_size - 1)+0
        // OR
        // 3(0)+1, 3(1)+1, .. , 3(board_size - 1)+1
        // ...
        // 3(0)+(board_size -1), 3(1)+(board_size -1), .. , 3(board_size - 1)+(board_size -1)
    }

    // CHECK DIAGONALS
    count = 0;
    first = board_array[0];

    for (int i = 0; i < board_size; ++i) {
        /*
        x
         x
          x
        */
        if (first == board_array[board_size * i + i]) {
            count++;
        }
        // 3(0)+0, 3(1)+1, .. , 3(board_size -1)+(board_size -1)
    }
    if (count == board_size && first != ' ') {
        return first;
    }
    
    count = 0;
    first = board_array[board_size * (board_size - 1) + 0];

    for (int i = 0; i < board_size; ++i) {
        /*
          x
         x
        x
        */
        if (board_array[board_size * i + (board_size - 1 - i)] == first) {
            count++;
        }
    }
    if (count == board_size && first != ' ') {
        return first;
    }

    // CHECK CATGAME
    //      ie. entire board full (no ' ' in board_array)
    for (int i = 0; i < board_size * board_size; ++i) {
        
        if (board_array[i] == ' ') {
            return NOTHING_YET;
        }
    }

    return CAT_GAME;
}


void print_board() { // OKAY (b˙◁˙)b
    /*
    example board_size = 3, should print:
    |x|x|x|
    |x|x|x|
    |x|x|x|

    |1.1|1.2|1.3|        // 2D ARRAY
    |2.1|2.2|2.3| ... 
    board_array[2][1] <=> 2.1
    */
    
    // SET UP FOR A 1D ARRAY
    // loop columns

    printf("  ");
    for (int col = 1; col <= board_size; ++col) {
        printf(" %d", col);
    }
    printf("\n");

    for (int row = 0; row < board_size; ++row) {
        printf("%d ", row + 1);
        // loop rows
        for (int col = 0; col < board_size; ++col) {
            printf("|%c", board_array[board_size * row + col]);
        }
        printf("|\n");
    } 

    /*
    // SET UP FOR A 2D ARRAY
    for (int row = 0; row < board_size; ++row) {
        // loop rows
        for (int col = 0; col < board_size; ++col) {
            printf("|%c", board_array[row][col]);
        }
        printf("|\n");
    } 
    */
}


void run_game() {

    char whose_turn = X_ASCII;
    int row_marker;
    int col_marker;

    while (true) {
        
        // check checker's verdict
        checked_verdict = checker();
        if (checked_verdict == X_ASCII 
        || checked_verdict == O_ASCII 
        || checked_verdict == CAT_GAME) {

            if (checked_verdict == CAT_GAME) {
                printf("GAME OVER! YOU ARE BOTH WINNERS. TIME TO FIND A BETTER OPPONENT.\n");
            } else if (checked_verdict == X_ASCII) {
                printf("GAME OVER! CONGRATULATIONS TO X FOR SHOWING THEM WHO'S THE BOSS.\n");
                printf("(ﾉ>ω<)ﾉ :｡･:*:･ﾟ’★,｡･:*:･ﾟ’☆ (don't worry O, there's room for 2 bosses too!)\n");             
            } else {
                printf("GAME OVER! CONGRATULATIONS TO O FOR VANQUISHING THE EVIL (｡•̀ᴗ•́)ﻭ✧ (just kidding! we love you X!)\n");
            }
            print_board();
            system("read -n1 -r -p \"Press Any Key To Continue To A New Game ...\" key");
            system("clear");
            break;
        }

        // print board for players, indicate whose turn it is
        
        printf("%c's MOVE:\n", whose_turn);
        print_board();

        // allow player to place their marker.
        // specifies row:
        if (scanf("%d", &row_marker) != 1) {
            printf("Woah! Be sure to enter a digit- remember, rows and columns can be from 1, ..., %d", board_size);
            continue;
        }
        // specifes column: 
        if (scanf("%d", &col_marker) != 1) {
            printf("Woah! Be sure to enter a digit- remember, rows and columns can be from 1, ..., %d", board_size);
            continue;
        }

        // check the user input is...       
        //  > A VALID NUMBER

        if (row_marker > board_size || row_marker < 1) {
            printf("Oops! Remember, rows can only be from 1, ... ,%d. Not to worry! Enter another one.", board_size);
            continue;
        }
        //  > NOT outside BOUNDS
        if (col_marker > board_size || col_marker < 1) {
            printf("Oops! Remember, col can only be from 1, ... ,%d. Not to worry! Enter another one.", board_size);
            continue;
        }

        //  > NOT already taken
        if (row_marker >= 1 && row_marker <= board_size &&
            col_marker >= 1 && col_marker <= board_size && 
            board_array[board_array[board_size * row_marker + col_marker] == ' ']) {

            printf("Hmm...this spot is already taken :( That's okay, choose another!");
            continue; // doesn't change whose_turn
        }

        


    
        // into array!
        board_array[(board_size * (row_marker - 1)) + (col_marker - 1)] = whose_turn;

        if (whose_turn == X_ASCII) {
            whose_turn = O_ASCII;
        } else {
            whose_turn = X_ASCII;
        }
        system("clear");
    }

    // in which either a win, or cat game- game fin.
    // 1. print winner or cat game.
    // 2. give option to restart (IN)
    //      > yes: alter keepgoing, reset game, etc.
    //      > no: alter endgame
    
}

void clear_board() { // OKAY (b˙◁˙)b
    for (int i = 0; i < (board_size * board_size); ++i) {
        board_array[i] = ' ';
        // *(board_array + i) = ' ';
    }
    // V2: 2D array, use double for loop, board_array[][]
}

int main() {
    system("clear");
    // SET UP TRACKER:
    // > bool keep_playing 
    // > int board_size
    // > board_array (set up in a function?)

    // print an introduction, rules, etc.
    
    //printf("\n==================================================================================\n");
    //printf("\n~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+~+\n");
    //printf("\n**********************************************************************************\n");
    //printf("\n^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-\n");
    printf("\n⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅ ∙ ∘ ☽ ༓ ☾ ∘ ⋅ ⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅   ⋅ \n");
    
    printf("\nHello Friends! Welcome to V1 of Tictactoe.\n");
    printf("On your turn, enter two numbers seperated by a space to place your marker.\n");
    printf("For example, on X's turn, entering \"2 3\" will place an X marker in row 2, column 3.\n");
    printf("Players are able to replay a game.\n");
    printf("To terminate the game, press CTRL+C.\n");
    printf("Enjoy!\n\n");

    // PLAYER SET UP TIME:
    printf("\nPlease Input Your Desired Board Size. For Example if you would like a 3x3 board, enter 3.\n");
    scanf(" %d", &board_size);
    board_array = malloc(board_size * board_size * sizeof(char)); // V2, move this in a loop.

    while (stay) {
        clear_board(); // clear/set up the board (malloc left garbage values)
        run_game();

        /*
        change stay option here
        printf("If you would like to leave, press 1.")
        int they_love_me_they_love_me_not;
        scanf(" %d", &they_love_me_they_love_me_not);
        if (they_love_me_they_love_me_not == 1) {
            stay = false;
        }
        */

        // we get here if we exit run_game (ie. keep_going = false)

        // option to replay board (clears board, same board_size)
        // YES: endgame = false
        // NO: endgame = true.

        // option to quit (quit game, mutate endgame = false to exit loop)
    }

    free(board_array);
    printf("Thank u for playing! <333\n	o(>ω<)o\n");

    return 0; //?
}