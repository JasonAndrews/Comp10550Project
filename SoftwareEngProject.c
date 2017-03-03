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

