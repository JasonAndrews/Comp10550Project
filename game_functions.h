/*
 ============================================================================
 Name        : game_functions.h
 Authors     : 
				Jason Andrews
				Jeremiah Wangaruro
				
 Version     : 0.1
 Description : 	This header file contains all the necessary function prototypes 
				for implementing the functionality of the game.
 ============================================================================
*/

#ifndef GAME_FUNCTIONS_H_
#define GAME_FUNCTIONS_H_

#define 	MAX_COLUMN_SIZE		100 // the max column size of each string in the 2D arrays

#define 	EXIT_APPLICATION	'x' // the character required for the main menu loop to break

#define 	MAX_NUM_OF_SLOTS	20

#define 	MAX_PTS				100

#define 	MAX_PLAYERS			6

//definitions
//values are assigned by default from ranging from 0 to 3 (Elf=0, Human=1,etc.)
enum type {
	Elf,
	Human,
	Ogre,
	Wizard
};

// The different types available for a slot
enum SLOT_TYPES {
	LEVEL_GROUND = 1,
	HILL = 2,
	CITY = 3
	
};

struct PLAYER_CAPABILITIES {
	int 
		smartness,
		strength,
		magicSkills,
		luck,
		dexterity;
};

/* 
*	This struct hold the players info
*/
struct PLAYER {
	char name[20];
	enum type playerType;
	int life_pts;
	struct PLAYER_CAPABILITIES caps;
	int position;
};

/*
* This struct will be used to store	
* information about each slot
*
*/
struct SLOT {
	struct PLAYER *player;
	enum SLOT_TYPES slotType;
};
// function prototypes
void setupSlots(unsigned int numSlots, struct SLOT *gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);
void setPlayerPositions(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers);
void sortCap(struct PLAYER *gamePlayers, int i);
void sortPlayers(struct PLAYER *gamePlayers, int *numPlayers);
int getCapabilitySum(struct PLAYER *player);
void nextTurn(unsigned int numSlots, struct SLOT *gameSlots, unsigned numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player);
void move(unsigned int numSlots, struct SLOT *gameSlots, struct PLAYER *player);
void attack(struct PLAYER gamePlayers[], struct PLAYER *player, unsigned int numPlayers);
void updateCapabilities(struct SLOT *gameSlots, struct PLAYER *player, size_t nextSlotType);
char *getPtypeString(enum type playerType);




#endif /* GAME_FUNCTIONS_H_*/