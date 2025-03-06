/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 10
#define COLS 10

#define EMPTY 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height){
	 int i, j;
    int centerX1 = width / 2;
    int centerY1 = height / 2;
    int centerX2 = centerX1;
    int centerY2 = centerY1;

    // Handle even-sized boxes by adjusting the center positions
    if (width % 2 == 0) {
        centerX2 = centerX1 - 1;
    }

    if (height % 2 == 0) {
        centerY2 = centerY1 - 1;
    }

    int index = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                design[index++] = '#';  // Draw border
            } else if ((i == centerY1 && j == centerX1) || (i == centerY2 && j == centerX2) ||
                       (i == centerY1 && j == centerX2) || (i == centerY2 && j == centerX1)) {
                design[index++] = 'X';  // Draw center 'X'
            } else {
                design[index++] = ' ';  // Draw space inside the box
            }
        }
        design[index++] = '\n';  // Newline at the end of each row
    }
    design[index] = '\0';  // Null-terminate the string
}


void PrintRoom(int room[ROWS][COLS]){
	 // Lookup array to map integers to characters
    char lookup[] = {' ', '#', '*', 'O', '@', 'X', 'X'};
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", lookup[room[i][j]]);
        }
        printf("\n"); // Move to the next row after printing all columns in the current row
    }
}

void InitialiseRoom(int room[ROWS][COLS], char *layout){
	int i, j;
    int index = 0;

    // Loop through each element of the two-dimensional array
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            // If there are still characters left in the layout string, use them
            if (layout[index] != '\0') {
                room[i][j] = layout[index] - '0'; // Convert character to integer
                index++;
            } else {
                // If the layout string is shorter than the array size, set to WALL
                room[i][j] = WALL;
            }
        }
    }
}

void LocatePerson(int room[ROWS][COLS], int *row, int *col){
	for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            // Check if the current cell contains PERSON or PERSON_ON_TARGET
            if (room[i][j] == PERSON || room[i][j] == PERSON_ON_TARGET) {
                *row = i;
                *col = j;
                return; // Exit the function once the person is found
            }
        }
    }
    // If the person is not found, set the row and col to -1 to indicate failure
    *row = -1;
    *col = -1;
}

void UndoMove(int room[ROWS][COLS], char *allMoves)
{
    int len = strlen(allMoves);
    if (len < 2) return;  // No moves to undo
    char lastMove = allMoves[len - 2];
    char boxMoved = allMoves[len - 1];
    int personRow, personCol;
    LocatePerson(room, &personRow, &personCol);
    int newRow = personRow, newCol = personCol, boxRow = -1, boxCol = -1;

    // Reverse the move
    if (lastMove == 'w') {
        newRow += 1;  // Undo up (move down)
        boxRow = personRow - 1;
    } else if (lastMove == 's') {
        newRow -= 1;  // Undo down (move up)
        boxRow = personRow + 1;
    } else if (lastMove == 'a') {
        newCol += 1;  // Undo left (move right)
        boxCol = personCol - 1;
    } else if (lastMove == 'd') {
        newCol -= 1;  // Undo right (move left)
        boxCol = personCol + 1;
    }

    // Restore the player's previous position
    if (room[personRow][personCol] == PERSON_ON_TARGET) {
        room[personRow][personCol] = TARGET;
    } else {
        room[personRow][personCol] = EMPTY;
    }
    if (room[newRow][newCol] == PERSON_ON_TARGET) {
        room[newRow][newCol] = TARGET;
    } else {
        room[newRow][newCol] = PERSON;
    }

    // If a box was moved, undo its movement as well
    if (boxMoved == '1') {
        // Restore the box's previous position
        if (lastMove == 'w' || lastMove == 's') {
            if (room[boxRow][newCol] == BOX_ON_TARGET) {
                room[boxRow][newCol] = TARGET;
            } else {
                room[boxRow][newCol] = EMPTY;
            }
            room[personRow][newCol] = BOX;
        } else if (lastMove == 'a' || lastMove == 'd') {
            if (room[newRow][boxCol] == BOX_ON_TARGET) {
                room[newRow][boxCol] = TARGET;
                
            } else {
                room[newRow][boxCol] = EMPTY;
            }
            room[personRow][newCol] = BOX;
        }
    }

    // Remove the last move from the allMoves string
    allMoves[len - 2] = '\0';

}

void MakeMove(int room[ROWS][COLS], char move, char *allMoves){
	if(move == 'z'){
        UndoMove(room, allMoves);
        return;
    }
    
    int personRow, personCol;
    LocatePerson(room, &personRow, &personCol);

    int newRow = personRow, newCol = personCol;
    int boxRow = -1, boxCol = -1;

    // Determine the new position based on the move
    if (move == 'w') {
        newRow -= 1;  // Move up
        boxRow = newRow - 1;
        boxCol = newCol;
    } else if (move == 's') {
        newRow += 1;  // Move down
        boxRow = newRow + 1;
        boxCol = newCol;
    } else if (move == 'a') {
        newCol -= 1;  // Move left
        boxCol = newCol - 1;
        boxRow = newRow;
    } else if (move == 'd') {
        newCol += 1;  // Move right
        boxCol = newCol + 1;
        boxRow = newRow;
    }

    // Check if the move is valid (inside bounds and not a wall)
    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
        int targetAhead = room[newRow][newCol];
        int targetAfterBox;
        if (boxRow >= 0 && boxRow < ROWS && boxCol >= 0 && boxCol < COLS) {
            targetAfterBox = room[boxRow][boxCol];
        } else {
            targetAfterBox = WALL;
        }

        // Move without a box
        if (targetAhead == EMPTY || targetAhead == TARGET) {
            if (room[personRow][personCol] == PERSON_ON_TARGET) {
                room[personRow][personCol] = TARGET;
            } else {
                room[personRow][personCol] = EMPTY;
            }

            room[newRow][newCol] = PERSON;
            if (targetAhead == TARGET) {
                room[newRow][newCol] = PERSON_ON_TARGET;
            }

            // Record the move
            int len = strlen(allMoves);
            allMoves[len] = move;
            allMoves[len + 1] = '0';  // No box move
            allMoves[len + 2] = '\0';

        } else if (targetAhead == BOX || targetAhead == BOX_ON_TARGET) {
            // Push the box if possible
            if (targetAfterBox == EMPTY || targetAfterBox == TARGET) {
                if (room[personRow][personCol] == PERSON_ON_TARGET) {
                    room[personRow][personCol] = TARGET;
                } else {
                    room[personRow][personCol] = EMPTY;
                }

                room[newRow][newCol] = PERSON;
                if (targetAhead == BOX_ON_TARGET) {
                    room[newRow][newCol] = PERSON_ON_TARGET;
                }

                if (targetAfterBox == TARGET) {
                    room[boxRow][boxCol] = BOX_ON_TARGET;
                } else {
                    room[boxRow][boxCol] = BOX;
                }

                // Record the move
                int len = strlen(allMoves);
                allMoves[len] = move;
                allMoves[len + 1] = '1';  // Box moved
                allMoves[len + 2] = '\0';
            }
        }
    }
}

int CheckGameOver(int room[ROWS][COLS]){
	int hasTarget = 0; // Flag to check if there is at least one target

    // Iterate over the warehouse grid
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (room[i][j] == TARGET) {
                // If any uncovered target is found, the game is not over
                return 0;
            }
            if (room[i][j] == BOX_ON_TARGET) {
                // Mark that at least one target is covered by a box
                hasTarget = 1;
            }
            if (room[i][j] == PERSON_ON_TARGET) {
                // If the person is standing on a target, the game is not over
                return 0;
            }
        }
    }

    // If there were no uncovered targets and at least one target was covered by a box, the game is over
    return hasTarget;
}



// When you have completed all of the functions for the project, place them here:


/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd') && (move != 'z')) {
		scanf("%c", &move);
	}
	return move;
}

/* Boxed In Game */
int main(void)
{
	char layout[200] = "0011111000111005100010032011001002320100111043010000100011000011111000000000000000000000000000000000";
	int room[ROWS][COLS] = {0};
	char allMoves[1000]  = {0};

	printf("ENGGEN131 - C Project 2024\n");
	printf("                          ... presents ...\n");
	printf("   +------+  ____                    _   _____         _ \n");
	printf("  /      /| |  _ \\                  | | |_   _|       | |\n");
	printf(" +------+ | | |_) | _____  _____  __| |   | |  _ __   | |\n");
	printf(" |      | + |  _ < / _ \\ \\/ / _ \\/ _` |   | | | '_ \\  | |\n");
	printf(" |      |/  | |_) | (_) >  <  __/ (_| |  _| |_| | | | |_|\n");
	printf(" +------+   |____/ \\___/_/\\_\\___|\\__,_| |_____|_| |_| (_)\n");
	printf("\n");
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	InitialiseRoom(room, layout);
	PrintRoom(room);
	while (!CheckGameOver(room)) {
		MakeMove(room, GetMove(), allMoves);
		PrintRoom(room);
	}
	printf("\n\nCONGRATULATIONS!\nGame over!\n");
	printf("Moves: %s", allMoves);
	return 0;
}


