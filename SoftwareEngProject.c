/*
 ============================================================================
 Name        : SoftwareEngProject.c
 Author      : Jason Andrews
 Version     : 0.1
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define 	PLAYERS_FILE_PATH 	"resources\\players.txt"
#define 	SLOTS_FILE_PATH 	"resources\\slots.txt"

#define 	MAX_COLUMN_SIZE		100 // the max column size of each string in the 2D arrays

#define 	EXIT_APPLICATION	'x' // the character required for the main menu loop to break

#define 	MAX_NUM_OF_SLOTS	20

int getFileTotalLines(char *filePath);
void bubbleSort(int rows, int columns, char array[rows][columns]);
void loadFileToArray(int rows, int columns, char array[rows][columns], char *filePath);
void shuffle(int rows, int columns, char array[rows][columns]);
int getTypeFromString(char *typeStr);
int containsConsecutiveTypes(int rows, int columns, char array[rows][columns]);
void sortSlots(int rows, int columns, char array[rows][columns], char passedSortedArray[rows][columns]);

/*
 * To be used in future assignments
enum PLAYER_TYPES {
	INVALID = 0,
	ELF = 1,
	HUMAN = 2,
	OGRE = 3,
	WIZARD = 4
};
*/

/*
* The different types available for a slot

*/
enum SLOT_TYPES {
	LEVEL_GROUND = 1,
	HILL = 2,
	CITY = 3
	
};

struct PLAYER {
	
};

/*
* This struct will be used to store	
* information about each slot
*
*
*/
struct SLOT {
	//struct PLAYER player;
	int slotId;
	enum SLOT_TYPES slotType;
	int playerId;
	
};


int main(void) {

	unsigned int 
		numSlots; // the number of slots in the game, entered by the user
		
	struct SLOT
				*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
				
	time_t
			currentTime;
	
	srand((unsigned) time(&currentTime));
	
	do {
	// prompt for, and capture the number of slots for the game
		printf("\nPlease enter the number of slots for the game (max = %d): ", MAX_NUM_OF_SLOTS);
		scanf("%d", &numSlots);
		
		if (numSlots < 1 || numSlots > MAX_NUM_OF_SLOTS)
			printf("\nERROR - Please enter a valid value for the number of slots!");
		
	} while (numSlots < 1 || numSlots > MAX_NUM_OF_SLOTS);
	
	gameSlots = (struct SLOT * const) malloc(sizeof(struct SLOT) * numSlots);
	
	printf("Size of gameSlots = %d | 1 slot = %d\n", sizeof(*gameSlots), sizeof(struct SLOT));
	
	for (int i = 0; i < numSlots; i++) {
		gameSlots[i].slotId = (i + 1);
		gameSlots[i].slotType = (rand() % 3 /* number of diffent slots.. */) + 1;
		
	}
	for (int i = 0; i < numSlots; i++) {
		printf("\nSlot index %d = %d, %s", i, gameSlots[i].slotId, (gameSlots[i].slotType == LEVEL_GROUND) ? ("LEVEL_GROUND") : ("NOT LEVEL_GROUND"));
	}
	
	printf("\n\nEND OF APP EXECUTION!\n");

	return EXIT_SUCCESS;
}


/* Description:
 * 				Takes in a string as an argument, which should be a valid file path.
 * 				It will then read the file and count the total number of lines (or rows, entries..) and then
 * 				return that number.
 *	Parameters:
 *		filePath : string - The path to the file
 *
 *	Returns:
 *		numLines : int - the number of lines in the file
 */
int getFileTotalLines(char *filePath) {

	int
		numLines = 1; // the number of lines in the file

	FILE *fp = fopen(filePath, "r+");

	if (fp == NULL) {
		printf("\nCould not open the file: %s", filePath);
		return -1;
	} else {

		char ch;

		// loop through a line until the new character line is hit
		while(!feof(fp)) {

			ch = fgetc(fp); // get the next character

			// check if the current character is the new line character
			if(ch == '\n') {
				// the end of a line has been found - increment numLines
				numLines++;
			}
		}

		fclose(fp); // close the file pointer
	}


	return numLines;
}

/*
 * Description:
 * 				Sorts a multi-dimensional array by
 * 				using the bubblesort algorithm. I converted this
 * 				version that originally sorted an integer array
 * 				to a 2d array of strings.
 * Parameters:
 *		rows : int - the dimension of the first index of the array
 * 		columns : int - the dimension of the second index of the array
 * 		array: 2-D char array - the array to be sorted
 *
 */
void bubbleSort(int rows, int columns, char array[rows][columns]){

	int i,j;
	char swap[columns];

	for (i = 0 ; i < ( rows - 1 ); i++)
		{
			for (j = i+1; j < rows; j++)
			{
				if (strcmp(array[i], array[j]) > 0)
				  /* For decreasing order use < */
				{
					// copy the currently iterated string (in the outer loop) to the temporary variable, swap
					strcpy(swap, array[i]);
					// copy the currently iterated string (in the inner loop) to the currently iterated string in the outer loop
					strcpy(array[i], array[j]);
					// copy the string stored in the temporary variable, swap, to the currently iterated inner loop
					strcpy(array[j], swap);

				}
			}
		}
}


/*
 * Description:
 * 				Loads a file, and stores its contents into a multi-dimensional array.
 * Parameters:
 *		rows : int - the dimension of the first index of the array
 * 		columns : int - the dimension of the second index of the array
 * 		array: 2-D char array - the array to be populated
 * 		filePath: string - the file to load
 *
 */
void loadFileToArray(int rows, int columns, char array[rows][columns], char *filePath) {

	FILE* fp = fopen(filePath, "r+");

	int
		currentIndex, // the current index in the array
		i;

	currentIndex = i = 0;

	if (fp == NULL) {
		printf("Could not open the file: %s", filePath);
		return;
	} else {
		while( fgets(array[currentIndex], sizeof(array[currentIndex]), fp) != NULL ) {

			// reset the counter for i, which is used to iterate through the strings
			i = 0;

			// keep looping until the end of the the string is reached
			while (array[currentIndex][i] != '\0') {

				// if the new line character is found, replace it with the end of string character
				if (array[currentIndex][i] == '\n')
					array[currentIndex][i] = '\0';

				// increment i
				i++;
			}

			// increment currentIndex
			currentIndex++;
		}
		fclose(fp);
	}
}

/*
 * Description:
 * 				Shuffles the contents of a 2-D char array.
 * Parameters:
 *		rows : int - the dimension of the first index of the array
 * 		columns : int - the dimension of the second index of the array
 * 		array: 2-D char array - the array to be shuffled
 *
 */
void shuffle(int rows, int columns, char array[rows][columns]) {
	
    int
		i, // index of the array, used in the for loop
		randIndex, // a random integer between 0 and rows, the index the current string will be inserted
		previousType, // the previous player type, used to avoid "same consecutive player types"
		nextType; // the type of the next player, used to avoid "same consecutive player types"

	char
		temp[columns], // temporary string, for switching strings around
		playerType[20]; // the player type of a player

	// randomizes the seed for the rand() function
	srand(time(NULL));

	previousType = 0;

	do {

		// loop through the array
		for (i = (rows - 1); i > 0; i--) {

			// while two types are the same, reshuffle them
			while (nextType == previousType) {

				randIndex = (rand() % i);
				//tmp = array[j];

				sscanf(array[randIndex], "%s ", playerType);
				//printf("\nIndex %d type: %s", i, playerType);

				nextType = getTypeFromString(playerType);

				strcpy(temp, array[randIndex]);
				strcpy(array[randIndex], array[i]);
				strcpy(array[i], temp);
			}

			previousType = nextType;

		}

		// keep reiterating until there are zero repeats
	} while (containsConsecutiveTypes(rows, columns, array));

}


/* Description:
 * 				Converts a player type to an integer representation
 * 				and then returns that integer.
 *	Parameters:
 *		typeStr : string - The player type, as a string
 *
 *	Returns:
 *		playerType : int - the integer representation of a player type
 */
int getTypeFromString(char *typeStr) {

	int
		playerType = 0; // the integer representation of a player type

	// convert the string to all lower case characters
	for (int i = 0; i < strlen(typeStr); i++) {
		if (typeStr[i] >= 'A' && typeStr[i] <= 'Z') {
			typeStr[i] = (typeStr[i] + ('a' - 'A'));
		}
	}

	// find which type the player is
	if (strcmp(typeStr, "elf") == 0) {
		playerType = 1;
	} else if (strcmp(typeStr, "human") == 0) {
		playerType = 2;
	} else if (strcmp(typeStr, "ogre") == 0) {
		playerType = 3;
	} else if (strcmp(typeStr, "wizard") == 0) {
		playerType = 4;
	} else {
		playerType = -1; // invalid type
	}

	// return the value of playerType
	return playerType;
}

/*
 * 	Description:
 * 		Checks whether or not there are
 * 		It will then read the file and count the total number of lines (or rows, entries..) and then
 * 		return that number.
 *
 *	Parameters:
 *		rows : int - the dimension of the first index of the array
 * 		columns : int - the dimension of the second index of the array
 * 		array: 2-D char array - the array to be checked
 *
 *	Returns:
 *		An integer - either 1 or 0, 1 if there are repeats, 0 if not
 */
int containsConsecutiveTypes(int rows, int columns, char array[rows][columns]) {

	int
		prevTypeId = 0, // the previous player type (integer representation)
		currentTypeId = 0; // // the current player type (integer representation)

	char
		currentType[20];

	for (int i = 0; i < rows; i++) {

		// get the player type in the array
		sscanf(array[i], "%s ", currentType);

		// call the getTypeFromString function and store it
		currentTypeId = getTypeFromString(currentType);

		// check consecutive types
		if (currentTypeId == prevTypeId) {
			// consecutive types found - return 1
			return 1;
		}

		// update prevTypeId for the next iteration of the loop
		prevTypeId = currentTypeId;
	}


	return 0;
}

/*
 * 	Description:
 * 		Sorts a list (2-D array) of slots, depending on their slot ID and follow slot ID.
 *
 *	Parameters:
 *		rows : int - the dimension of the first index of the array
 * 		columns : int - the dimension of the second index of the array
 * 		array: 2-D char array - the array to be sorted
 * 		sortedArray: 2-D char array - the resulting sorted array
 *
 */
void sortSlots(int rows, int columns, char array[rows][columns], char sortedArray[rows][columns]) {

	char
		slotType[20], // string containing the slot type / name, the second column in the slots.txt file
		slotStr[3], // a string containing slot ID, the first column in the slots.txt file
		followingSlotStr[3]; // a string containing following slot ID, the third column in the slots.txt file

	int
		i, j, // variables for loops
		prevSlot = 0, // the slot ID (first column of file)
		followSlot = 0, // the follow slot ID (third column of file)
		nextSlotIndex; // the index in the sortedArray for the next string to be inserted

	// set the value to the last index of the array, as they will be sorted from the top-down
	nextSlotIndex = (rows - 1);

	// reset the loop variables
	i = j = 0;

	// loop 'rows' amount of times (or "the amount of slots there are in the file")
	while (i != rows)
	{
		// loop "rows" times
		for (j = 0; j < rows; j++) {
			
			// scan the current row / string and parse it's data to the appropriate strings
			sscanf(array[j],"%s - %s %s", slotStr, slotType, followingSlotStr);
			
			// parse the string to an integer
			followSlot = atoi(followingSlotStr);
			
			// check if the current slot matches
			if (prevSlot == followSlot) {
				strcpy(sortedArray[nextSlotIndex], array[j]);
				prevSlot = atoi(slotStr); // now set the current slot (the slot just loaded) to the prev slot for the next iteration
				break;
			}			
		} // end of inner for loop

		// copy the string to the sorted array, and position it in the correct slot
		strcpy(sortedArray[nextSlotIndex], array[j]);
		
		nextSlotIndex--;
		//printf("Index %d = %s \n", i, numberStr[i] );
		
		// increment i
		i++;
	} // end of outer while loop

}

/*
 * Contents of main() from assignment 1.
 
 
int main(void) {

	char userChoice = 0; // the option the user enters
	
	int
		playerFileLines = 0, // number of lines (or entries) in the players.txt file
		slotFileLines = 0; // number of lines (or entries) in the slots.txt file

	
	// get the number of lines in the players.txt and slots.txt files, and update the appropriate variable
	playerFileLines = getFileTotalLines(PLAYERS_FILE_PATH);
	slotFileLines = getFileTotalLines(SLOTS_FILE_PATH);

	// the two main arrays, which are populated with the contents of the players.txt and slots.txt files
	char playerArr[playerFileLines][MAX_COLUMN_SIZE];
	char slotArr[slotFileLines][MAX_COLUMN_SIZE];
	// an array that contains the sorted contents of the slotArr array
	char sortedSlotArr[slotFileLines][MAX_COLUMN_SIZE];

	// load both files and store their contents in the array(s) passed as an argument
	loadFileToArray(playerFileLines, MAX_COLUMN_SIZE, playerArr, PLAYERS_FILE_PATH);
	loadFileToArray(slotFileLines, MAX_COLUMN_SIZE, slotArr, SLOTS_FILE_PATH);

	do {
		// print out the welcome message, and the options available
		printf("\nWelcome to the early stages of the upcoming game, CrossFire!\n");
		printf("\nTo get started, enter:");
		printf("\nx to exit.");
		printf("\n1 to sort & shuffle the list of players.");
		printf("\n2 to sort the slots.");
		printf("\nYour choice: ");

		// store the user input
		scanf("%c", &userChoice);
		//printf("\nChoice: %d", userChoice);

		if (userChoice == 'X')
			userChoice = 'x';

		switch (userChoice) {

				case 'x': { // exit the application
					printf("\n\nExiting application...\n");
					break;
				}// end case x

				case '1': { // 1 - sort & shuffle the list of players

					// print out the DEFAULT player list
					printf("\n== Default List ==\n");
					for (int i = 0; i < playerFileLines; i++) {
							printf("\n%s", playerArr[i]);
					}

					// call the bubbleSort function, which will sort the array alphabetically
					bubbleSort(playerFileLines, MAX_COLUMN_SIZE, playerArr);

					// print out the SORTED list of players
					printf("\n\n== Sorted Player List ==\n");
					for (int i = 0; i < playerFileLines; i++) {
						printf("\n%s", playerArr[i]);
					}

					// call the shuffle function, which will shuffle the array
					shuffle(playerFileLines, MAX_COLUMN_SIZE, playerArr);

					// print out the SHUFFLED list of players
					printf("\n\n== Shuffled Player List ==\n");
					for (int i = 0; i < playerFileLines; i++) {
						printf("\n%s", playerArr[i]);
					}

					break;
				}// end case 1

				case '2': { // 2 - sort the slots

					char
						slotStr[10], // a string containing slot ID, the first column in the slots.txt file
						slotType[20], // string containing the slot type / name, the second column in the slots.txt file
						followingSlotStr[10]; // a string containing following slot ID, the third column in the slots.txt file

					// print out the DEFAULT list of slots
					printf("\n\n== Default Slots ==\n");
					for (int i = 0; i < slotFileLines; i++) {
						printf("\n%s", slotArr[i]);
					}

					// call the sortSlots function, which sorts the slots in their correct order
					// the last parameter, the array sortedSlotArr, will contain the sorted slots
					sortSlots(slotFileLines, MAX_COLUMN_SIZE, slotArr, sortedSlotArr);

					// print out the SORTED list of slots, in the same format shown in the assignment brief document
					printf("\n\n== Sorted Slots ==\n");
					for (int i = 0; i < slotFileLines; i++) {
						// scan the current string, and then store the formatted tokens in the appropriate strings
						sscanf(sortedSlotArr[i], "%s - %s %s", slotStr, slotType, followingSlotStr);
						printf("(%s,%s)%s", slotStr, slotType, (i != (slotFileLines - 1) ? ("->") : ("")));
					}

					break;
				} // end case 2

				default: { // invalid option entered
					printf("\nInvalid option entered!");
					//printf("\nPress any key to continue..");
					break;
				} // end default
			}

		// implemented for a nice way to return to the main menu
		printf("\n\nPress any key to return to the main menu..\n");
		fflush(stdin);
		getchar();

	} while(userChoice != EXIT_APPLICATION);





	printf("\n\nEND OF APP EXECUTION!\n\n");

	return EXIT_SUCCESS;
}
*/