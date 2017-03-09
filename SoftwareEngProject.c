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
#include <stdbool.h>

#define 	PLAYERS_FILE_PATH 	"resources\\players.txt"
#define 	SLOTS_FILE_PATH 	"resources\\slots.txt"

#define 	MAX_COLUMN_SIZE		100 // the max column size of each string in the 2D arrays

#define 	EXIT_APPLICATION	'x' // the character required for the main menu loop to break

#define 	MAX_NUM_OF_SLOTS	20

#define 	MAX_PTS				100

#define MAX_PLAYERS				6

//values are assigned by default from ranging from 0 to 3 (Elf=0, Human=1,etc.)
enum type {
	Elf,
	Human,
	Ogre,
	Wizard
};

/*
* The different types available for a slot

*/
enum SLOT_TYPES {
	LEVEL_GROUND = 1,
	HILL = 2,
	CITY = 3
	
};

/* 
*	This struct hold the players capabilities info
	
	Capabilities: 
		Smartness, 
		Strength, 
		Magic Skills, 
		Luck,
		Dexterity
*/
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

//global variable used in sortPlayers (PLANNING ON CHANGING IT FROM A GLOBAL TO A LOCAL SOMEHOW)
struct PLAYER num[MAX_PLAYERS];


// function prototypes
void setupSlots(unsigned int numSlots, struct SLOT *gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);
void sortCap(int i);
void sortPlayers();
int getCapabilitySum(struct PLAYER *player);
void nextTurn(int position, struct PLAYER *player, int numPlayers);
void attack(int position, struct PLAYER *player, int numPlayers);
// main function
int main(void) {

	size_t 
		i;
	unsigned int 
		numSlots, // the number of slots in the game, entered by the user
		numPlayers, // the number of players in the game, entered by the user
		turnChoice; // the 
		
	struct SLOT
				*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
				
	time_t
			currentTime;
	
	srand((unsigned) time(&currentTime));
	
	sortPlayers(&numPlayers);
	
	
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

	// start the game - Player1 -> PlayerN will have a turn
	for (i = 0; i < numPlayers; i++) {		
		nextTurn(0, &num[i]);
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
/* Function Name: sortPlayers
 * Description:
 * 				Set up the struct of players. 
 *	Parameters:
 *		N/A
 *
 *	Returns:
 *		N/A
 */
void sortPlayers(int *numPlayers)
{
	int 
		i=0,
		j=0;
	char 
		ch;
	int choice;
	
	
	printf("Please enter number of players (max. 6 players)\n");
	scanf("%d", numPlayers);

	if(*numPlayers<1 || *numPlayers>MAX_PLAYERS)
	{
		printf("ERROR INVALID ENTRY: Please enter a number between 1 and 6");
	}
	else
	{
		do
		{
			
			
			printf("\nPlease enter player name (20 characers max.)\n");
			fflush(stdin);
			fflush(stdout);
			fgets(num[i].name, 20, stdin);
			// remove the NEWLINE character from the player's name.
			
			for(j = 0; num[i].name[j] != '\0'; j++) { 
				
				if (num[i].name[j] == '\n') {
					num[i].name[j] = '\0'; // set 
					break;
				}
			}
				
			
			printf("\nPlease select player type\n");
			printf("1)Elf\n");
			printf("2)Human\n");
			printf("3)Ogre\n");
			printf("4)Wizard\n");

			scanf("%d", &choice);

			switch(choice)
			{
			case 1:
			num[i].playerType=Elf;
			break;

			case 2:
			num[i].playerType=Human;
			break;

			case 3:
			num[i].playerType=Ogre;
			break;

			case 4:
			num[i].playerType=Wizard;
			break;

			default:
			printf("ERROR INVALID ENTRY:Please enter a number between 1 and 4");
			}
			
			if (choice >= 1 && choice <= 4) {
				
				num[i].life_pts = MAX_PTS;
				i++;		
				
				sortCap(i);			
			}
			
		} while(i < *numPlayers);
		
	}
}
/* Function Name: sortCap
 * Description:
 * 				Assigns values to the player capabilites. 
 *	Parameters:
 *		integer i which represents the player number (i.e. 1st player, 2nd player, etc.)
 *
 *	Returns:
 *		N/A
 */
void sortCap(int i)
{
	int sum,j;
	bool valid;
	time_t currentTime;
	srand((unsigned) time(&currentTime));
	
	if(num[i].playerType==1)
	{
		do {
			
			sum = getCapabilitySum(&num[i]);
			
			if(sum<300)
				valid = true;
			else 
				valid = false;
			
		} while (!valid);
	}
		
	if(num[i].playerType==2)
	{
		do
		{
			num[i].caps.magicSkills=0;
			num[i].caps.smartness=rand()%20;
			num[i].caps.strength=80+rand()%20;
			num[i].caps.dexterity=80+rand()%20;
			
			if((num[i].caps.smartness+num[i].caps.luck)<50)
				valid = true;
			else
				!valid;
			
		}while(!valid);
	}
		
	if(num[i].playerType==0)
	{
		num[i].caps.luck=60+rand()%40;
		num[i].caps.smartness=70+rand()%30;
		num[i].caps.strength=1+rand()%49;
		num[i].caps.magicSkills=51+rand()%29;
		num[i].caps.dexterity=1+rand()%99;
	}
	
	if(num[i].playerType==3)
	{
		num[i].caps.luck=50+rand()%50;
		num[i].caps.smartness=90+rand()%10;
		num[i].caps.strength=1+rand()%19;
		num[i].caps.magicSkills=80+rand()%20;
		num[i].caps.dexterity=1+rand()%99;
	}
}

int getCapabilitySum(struct PLAYER *player) {
	
	int capSum = 0;
	
	capSum += player->caps.smartness;
	capSum += player->caps.strength;
	capSum += player->caps.magicSkills;
	capSum += player->caps.luck;
	capSum += player->caps.dexterity;

	return capSum;
}

/* Function Name: nextTurn
 * Description:
 * 				
 *	Parameters:
 *		
 *
 *	Returns:
 *		N/A
 */
void nextTurn(int position, struct PLAYER *player, int numPlayers) {
	
	// used in Move()
	size_t	
		i,
		currentPosition;
	
	// used in Attack()
	unsigned int 
		turnChoice;

	
	printf("\n%s - it is your turn.\nWhat do you want to do?\n1. Attack.\n2. Move.\nYour choice: ", player->name);
	
	scanf("%d", &turnChoice);
	
	switch (turnChoice) {
		
		case 1: {
			attack(position, player, numPlayers);
			break;
		}
		case 2: {
			//Move();
			break;
		}
	}
	
} // end of nextTurn() function
void attack(int position, struct PLAYER *player, int numPlayers)
{
	size_t i;
	unsigned int distToNextPlayer[2], playerNum, choice;
	
	
	for(i=0;i<=numPlayers;i++)
	{
		distToNextPlayer[i]= position - /*num[i].position*/;
	
		playerNum = i;
		
		distToNextPlayer[i+1]= position - /*num[i+1].position*/;
		
		if(distToNextPlayer[i]<distToNextPlayer[i+1])
		{
			playerNum= i+1;
		}
		else if(distToNextPlayer[i]==distToNextPlayer[i+1])
		{
			printf("Which player do you want to attack.\n1)%s\n2)%s", num[i].name, num[i+].name);
			scanf("%d", choice);
			
			
		}
	}
	
	
	
	
}