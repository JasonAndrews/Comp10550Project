/*
 ============================================================================
 Name        : SoftwareEngProject.c
 Module		 : COMP10550
 Group		 : 4	
 Authors     : 
				Jason Andrews
				Jeremiah Wangaruro	the cool guy
				
 Version     : 0.1
 Description : 	This file contains the code necessary for Assignment Two.
				Assignment two tasks us with developing the early stages of the game.
				This includes:
					Setting up the necessary structs.
					Setting up the necessary enums.
					Populating the structs.
					Implementing some auto character creation.
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
*/
struct SLOT {
	struct PLAYER player;
	enum SLOT_TYPES slotType;
};

// function prototypes
void setupSlots(unsigned int numSlots, struct SLOT *gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);

// main function
int main(void) {

	unsigned int 
		numSlots; // the number of slots in the game, entered by the user
		
	struct SLOT
				*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
				
	time_t
			currentTime;
	
	srand((unsigned) time(&currentTime));
	
	char name[20];
	
	printf("\nEnter a name: ");
	fgets(name, 20, stdin);
	
	do {
		// prompt for, and capture the number of slots for the game
		printf("\nPlease enter the number of slots for the game (max = %d): ", MAX_NUM_OF_SLOTS);
		scanf("%d", &numSlots);
		
		if (numSlots < 1 || numSlots > MAX_NUM_OF_SLOTS)
			printf("\nERROR - Please enter a valid value for the number of slots!");
		
	} while (numSlots < 1 || numSlots > MAX_NUM_OF_SLOTS);
	
	// allocate the required amount of memory for a numSlots sized array of type struct SLOT
	gameSlots = (struct SLOT * const) malloc(sizeof(struct SLOT) * numSlots);
	
	setupSlots(numSlots, gameSlots);
	printf("Size of gameSlots = %d | 1 slot = %d\n", sizeof(*gameSlots), sizeof(struct SLOT));
	
	for (int i = 0; i < numSlots; i++) {
		printf("\nSlot index %d = %s", i, getSlotString(gameSlots[i].slotType));
	}
	
	printf("\n\nEND OF APP EXECUTION!\n");

	return EXIT_SUCCESS;
}



/* Function: 	setupSlots
 * Description:
 * 				Set up the array of slots. 
 *	Parameters:
 *		numSlots : uint - The size of the array.
 *
 *	Returns:
 *		gameSlots : pointer to struct SLOT - The array of slots (the memory of the first element of the array)
 */
void setupSlots(unsigned int numSlots, struct SLOT *gameSlots) {
	
	for (int i = 0; i < numSlots; i++) {
		
		// assign a different slot type
		gameSlots[i].slotType = (rand() % 3 /* number of different slots.. */) + 1;
		
	}
	
}


/* Function Name: 	getSlotString
 * Description:
 * 				Set up the array of slots. 
 *	Parameters:
 *		numSlots : uint - The size of the array.
 *
 *	Returns:
 *		gameSlots : pointer to struct SLOT - The array of slots (the memory of the first element of the array)
 */
char* getSlotString(enum SLOT_TYPES slotType) {
	
	char *slotString = "";
	
	switch (slotType) {
		case LEVEL_GROUND: {
			strcpy(slotString, "Level Ground");
			break;
		}
		case HILL: {
			strcpy(slotString, "Hill");
			break;
		}
		case CITY: {
			strcpy(slotString, "City");
			break;
		}
		default: {
			strcpy(slotString, "Invalid..");
			break;
		}
	}
	return slotString;	
}