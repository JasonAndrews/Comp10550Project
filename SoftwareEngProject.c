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

#define 	MAX_PLAYERS			6

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

//global variable used in sortPlayers (PLANNING ON CHANGING IT FROM A GLOBAL TO A LOCAL SOMEHOW)
struct PLAYER num[MAX_PLAYERS];


// function prototypes
void setupSlots(unsigned int numSlots, struct SLOT *gameSlots);
char *getSlotString(enum SLOT_TYPES slotType);
void setPlayerPositions(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers);
void sortCap(int i);
void sortPlayers();
int getCapabilitySum(struct PLAYER *player);
void nextTurn(unsigned int numSlots, unsigned numPlayers, struct SLOT *gameSlots, struct PLAYER *player);
void move(unsigned int numSlots, struct SLOT *gameSlots, struct PLAYER *player);
void attack(struct PLAYER gamePlayers[], struct PLAYER *player, unsigned int numPlayers);
void updateCapabilities(struct SLOT *gameSlots, struct PLAYER *player, size_t nextSlotType);
char *getPtypeString(enum type playerType);

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
	setPlayerPositions(numSlots, gameSlots, numPlayers, num);
	// start the game - Player1 -> PlayerN will have a turn
	for (i = 0; i < numPlayers; i++) {		
		nextTurn(numSlots, numPlayers, gameSlots, &num[i]);
	}
	
	printf("\n\nGame Over!\nHere are the end-game stats for every player!\n");
	printf("\nnumPlayers = %d", numPlayers);
	//prints out <player name>( <player Type> , <life_pts> )
	for(i = 0; i < numPlayers; i++)
	{
		printf("\n%s (%s, %d)", num[i].name, getPtypeString(num[i].playerType), num[i].life_pts);
	}
	
	/*
	// print out the each player's name and hitpoints
	for (i = 0; i < numPlayers; i++) {
		printf("\n%d | (%s, %d, %d, %d, %d, %d, %d)", (i+1), num[i].name, num[i].life_pts, 
			num[i].caps.smartness, num[i].caps.strength, num[i].caps.magicSkills, num[i].caps.luck, num[i].caps.dexterity);
	}
	*/
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
		gameSlots[i].player = NULL; 
		
		printf("\nSlot at index %d is of type %s", i, getSlotString(gameSlots[i].slotType));
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
char *getSlotString(enum SLOT_TYPES slotType) {
	
	char *slotString = "";
	
	switch (slotType) {
		case LEVEL_GROUND: {
			//strcpy(slotString, "Level Ground");
			slotString = "Level Ground";
			break;
		}
		case HILL: {
			//strcpy(slotString, "Hill");
			slotString = "Hill";
			break;
		}
		case CITY: {
			//strcpy(slotString, "City");
			slotString = "City";
			break;
		}
		default: {
			//strcpy(slotString, "Invalid..");
			slotString = "ERROR";
			break;
		}
	}
	return slotString;	
}

/* Function Name: 	getPtypeString
 * Description:
 * 		gets name of slot. 
 *	Parameters:
 *		
 *
 *	Returns:
 *		
 */
char* getPtypeString(enum type playerType) {
	
	char *typeString = "";
	
	switch (playerType) {
		case Elf: {
			//strcpy(typeString, "Elf");
			typeString = "Elf";
			break;
		}
		case Human: {
			//strcpy(typeString, "Human");
			typeString = "Human";
			break;
		}
		case Ogre: {
			typeString = "Ogre";
			//strcpy(typeString, "Ogre");
			break;
		}
		case Wizard:{
			//strcpy(typeString, "Wizard");
			typeString = "Wizard";
			break;
		}
		default:{
			typeString = "ERROR";
			//strcpy(typeString, "ERROR");
			break;
		}
	}
	
	printf("\ngetPtypeString -> Type ID:  %d | return value: %s", (int) playerType, typeString);
	return typeString;	
}

 
/* Function Name: 	setPlayerPositions
 * Description:
 * 				Place each player into a random slot position.
 *	Parameters:
 *		numSlots : uint - The size of the slot array.
 * 		gameSlots : pointer to struct SLOT - The array of slots (the memory of the first element of the array)
 * 		numPlayers : uint - The size of the player array.
 *      gamePlayers : pointer to struct PLAYER - The array of players (the memory of the first element of the array)
 *
 *	Returns:
 *		N/A
 */
void setPlayerPositions(unsigned int numSlots, struct SLOT *gameSlots, unsigned int numPlayers, struct PLAYER *gamePlayers) {

	size_t 
		randIndex, // random index 
		i; // current player

	bool 
		placedPlayer = false;
		
	// loop numPlayers times (the number of players in the game)
	for (i = 0; i < numPlayers; i++) {
		
		placedPlayer = false; // reset the variable for the current iteration
		
		// keep looping until the current player is placed in a slot
		while (!placedPlayer) {
			
			// get a random index
			randIndex = (rand() % numSlots);
						
			// if the slot has no player already, set the player in the slot
			if (gameSlots[randIndex].player == NULL) {
				
				// update the slots player variable to the address of the current player
				gameSlots[randIndex].player = &gamePlayers[i];  
				// update the boolean variable so the loop breaks				
				placedPlayer = true; 
				gamePlayers[i].position = randIndex;
				
				updateCapabilities(gameSlots, &gamePlayers[i], gamePlayers[i].position);
				
			} 
		}		
	}
	
}
/* Function Name: sortPlayers
 * Description:
 * 		Set up the struct of players. 
 *	Parameters:
 *		numPlayers: pointer to int numPlayer - returns the user enter number of players in game
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
					num[i].name[j] = '\0'; // set the current character as the EOS character
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
				
				sortCap(i);			
				
				i++;
			}
			
		} while(i < *numPlayers);
		
	}
}
/* Function Name: sortCap
 * Description:
 * 		Assigns values to the player capabilities. 
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
	
	if(num[i].playerType==Human)
	{
		do {
			
			num[i].caps.smartness = 1 + (rand() % 100);
			num[i].caps.luck = 1 + (rand() % 100);
			num[i].caps.strength = 1 + (rand() % 100);
			num[i].caps.magicSkills = 1 + (rand() % 100);
			num[i].caps.dexterity= 1 + (rand() % 100);
			
			sum = getCapabilitySum(&num[i]);
			
			if(sum < 300)
				valid = true;
			else 
				valid = false;
			
		} while (!valid);
	}
		
	if(num[i].playerType==Ogre)
	{
		do
		{
			num[i].caps.magicSkills = 0;
			num[i].caps.smartness = rand()%20;
			num[i].caps.strength = 80+rand()%20;
			num[i].caps.dexterity = 80+rand()%20;
			
			if((num[i].caps.smartness + num[i].caps.luck) < 50)
				valid = true;
			else
				valid = !false;
			
		} while(!valid);
	}
		
	if(num[i].playerType==Elf)
	{
		num[i].caps.luck = 60+rand()%40;
		num[i].caps.smartness = 70+rand()%30;
		num[i].caps.strength = 1+rand()%49;
		num[i].caps.magicSkills = 51+rand()%29;
		num[i].caps.dexterity = 1+rand()%99;
	}
	
	if(num[i].playerType==Wizard)
	{
		
		num[i].caps.luck = 50+rand()%50;
		num[i].caps.smartness = 90+rand()%10;
		num[i].caps.strength = 1+rand()%19;
		num[i].caps.magicSkills = 80+rand()%20;
		num[i].caps.dexterity = 1+rand()%99;
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

void nextTurn(unsigned int numSlots, unsigned numPlayers, struct SLOT *gameSlots, struct PLAYER *player) {
	
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
			attack(num, player, numPlayers);
			break;
		}
		case 2: {	
			move(numSlots, gameSlots, player);
			break;
		}
	}
	
} // end of nextTurn() function

/* Function Name: attack
 * Description:
 * 				
 *	Parameters:
 *		PLAYER :
 *
 *	Returns:
 *		N/A
 */
void attack(struct PLAYER *gamePlayers, struct PLAYER *player, unsigned int numPlayers)
{
	size_t 
		i;
	unsigned int 
			minDist = (20) /*MAX_SLOTS*/,
			numClosePlayers = 0,
			attackedPlayer = -1,
			choice;
	struct 
		PLAYER closeByPlayers[numPlayers];
	bool	
		validChoice = false;
	
	for (i = 0; i < numPlayers; i++) {
		
		if ((&gamePlayers[i]) == player) {
			continue;
		}
		
		// if the selected player's position MINUS the currently iterated player's position - update minDist
		if (abs(player->position - num[i].position) < minDist) {
			minDist = abs(player->position - num[i].position);
			printf("New Min Dist = %d", minDist);
		}
	}
	
	for (i = 0; i < numPlayers; i++) {
		
		if ((&gamePlayers[i]) == player) {
			continue;
		}
		
		// if the selected player's position MINUS the currently iterated player's position - update minDist
		if (abs(player->position - num[i].position) == minDist) {
			closeByPlayers[numClosePlayers] = num[i];
			numClosePlayers++;
		}
		
	}
	
	for (i = 0; i < numClosePlayers; i++) {
		printf("\n%d - %s", (i + 1), closeByPlayers[i].name);
		
	}
	
	attackedPlayer = 0; // set the default target as element 0 of closeByPlayers
	
	// implement the actual attacking of the players
	if (numClosePlayers == 2) {
		// the attacking player has 2 close targets to attack
		
		do {
			
			printf("\nYou are between two players.\nDo you want to attack 1)%s or 2)%s : ", closeByPlayers[0].name, closeByPlayers[1].name);
			
			scanf("%d", &choice);

			if(choice == 1)
			{
				attackedPlayer = 0;
				validChoice = true;
			}
			else if(choice == 2)
			{
				attackedPlayer = 1;
				validChoice = true;
			}
		} while (!validChoice);
	
	
	}

	if((num[attackedPlayer].caps.strength)<=70)
	{
		num[attackedPlayer].life_pts-=(0.5*(num[attackedPlayer].caps.strength));
	}
	else{
		player->life_pts-=(0.3*(player->caps.strength));
	}	 
	
	printf("\nYou ATTACKED player %s!", closeByPlayers[attackedPlayer].name);
	
/*
	size_t
		i,
		j;
		
	bool 
		validChoice = false;
		
	unsigned int
		distToNextPlayer[numPlayers-1],
		choice =0,
		distance,
		attacked;
	
	
	
	//fills array distToNextPlayer with distance to relevant players start with player 2
	for(i=0;i<numPlayers;i++)
	{
		distToNextPlayer[i]= player->position - num[i].position;
	}
	//scans array for largest distance and the corresponding player
	for(i=0;i<numPlayers-1;i++)
	{
		distance=distToNextPlayer[0];
		if(distToNextPlayer[0]<distToNextPlayer[i])
		{
			distance=distToNextPlayer[i];
			attacked=i+2; //because distToNextPlayer[i] refers to distance from player i+2
		}
	}
	
	j=attacked;//holds index of player for reference later.
	//check to see if any other player is the same distance away and make user choose between them.
	for(i=0;i<numPlayers-1 && validChoice;i++)
	{
		if(distance == distToNextPlayer[i])
		{
			do{
				printf("\nYou are between two players.Do you want to attack 1)%s or 2)%s : ",num[j].name ,num[i].name);
				scanf("%d", choice);
				
				if(choice == 1)
				{
					validChoice = true;
				}
				else if(choice == 2)
				{
					attacked = i+2;
					validChoice = true;
				}
			}while(validChoice);
		}
	}
	
	if((num[attacked].caps.strength)<=70)
	{
		num[attacked].life_pts-=(0.5*(num[attacked].caps.strength));
	}
	else{
		player->life_pts-=(0.3*(player->caps.strength));
	}	
*/	
}// end of attack() function.



/* Function Name: move
 * Description:
 * 				
 *	Parameters:
 *		
 *
 *	Returns:
 *		N/A
 */
void move(unsigned int numSlots, struct SLOT *gameSlots, struct PLAYER *player) {
	
	// used in Move()
	size_t	
		i,
		currentPosition;
	
	// used in Attack()
	unsigned int 
		completedMove,
		moveChoice,
		distToNextPlayer;

	for (i = 0; i < numSlots; i++) {
		//printf("\ngameSlots[i].player = %p | player = %p", gameSlots[i].player, player);
		if (gameSlots[i].player == player) {
			currentPosition = i;
			printf("\nCurrent Position for %s is %d.", gameSlots[i].player->name, i);
			break;
		}
	}
	
	do {
		
		currentPosition = player->position;
		printf("\n%s, your location is %d. Please select a direction.\n1. Forward.\n2. Backward\nYour choice: ", player->name, player->position);
		
		scanf("%d", &moveChoice);
	
		switch (moveChoice) {
			
			case 1: {
				// move forward
				if (player->position == (numSlots - 1)) {
					printf("Sorry, you cannot move forward!");
					break;
				}
				
				// check if the next slot is empty
				if (gameSlots[(currentPosition + 1)].player == NULL)  {
					
					updateCapabilities(gameSlots, player, (player->position + 1));
					
					player->position++;
					printf("\n%s, you moved forward to location %d.", player->name, player->position);
					
					gameSlots[player->position].player = player;
					gameSlots[currentPosition].player = NULL;
					
					completedMove = true;
					
				} else {
					// the slot has a player already
					printf("\nYou cannot move to that position because another player is already there!\n");
				}
				
				break;
			}
			case 2: {
				// move backward
				if (player->position == 0) {
					printf("Sorry, you cannot move backwards!");
					break;
				}
				
				// check if the previous slot is empty
				if (gameSlots[(currentPosition - 1)].player == NULL)  {
					
					updateCapabilities(gameSlots, player, (player->position - 1));
					
					player->position--;
					printf("\n%s, you moved backwards to location %d.", player->name, player->position);
					
					gameSlots[player->position].player = player;
					gameSlots[currentPosition].player = NULL;
					
					completedMove = true;
					//updateCapabilities();
				} else {
					// the slot has a player already
					printf("\nYou cannot move to that position because another player is already there!\n");
					
				}
				
				break;
			}
		}
	} while (!completedMove);
	
} // end of move() function

/* Function Name: updateCapabilities
 * Description:
 * 				
 *	Parameters:
 *		
 *
 *	Returns:
 *		N/A
 */
void updateCapabilities(struct SLOT *gameSlots, struct PLAYER *player, size_t nextSlotIndex) {
	
	enum SLOT_TYPES 
			prevSlotType,
			nextSlotType;
	
	prevSlotType = gameSlots[(player->position)].slotType;
	nextSlotType = gameSlots[nextSlotIndex].slotType;
		
		
	// reset the players capabilities only if they came from a DIFFERENT slot type
	if (nextSlotType != prevSlotType) {
		// depending on the next slot type the player will enter, update their capabilities to their previous state
		switch (prevSlotType) {
			case HILL: {
				
				if (player->caps.dexterity < 50) 
					player->caps.strength += 10;
				else if (player->caps.dexterity >= 60)
					player->caps.strength -= 10;
				
				break;
			}
			case CITY: {
				
				if (player->caps.smartness > 60)					
					player->caps.magicSkills -= 10;
				else if (player->caps.smartness <= 50)
					player->caps.dexterity += 10;
				
				break;
			}
		}
	}

	// update the players capabilities if they move to a DIFFERENT slot type
	if (nextSlotType != prevSlotType) {
		
		// depending on the next slot type the player will enter, update their capabilities
		switch (nextSlotType) {
			case HILL: {
				
				if (player->caps.dexterity < 50)  {
					player->caps.strength -= 10;
					
					if (player->caps.strength < 0)
						player->caps.strength = 0;
				} else if (player->caps.dexterity >= 60) {
					player->caps.strength += 10;

					if (player->caps.strength > 100)
						player->caps.strength = 100;
				
				}
				break;
			}
			case CITY: {
				
				if (player->caps.smartness > 60) {		
					player->caps.magicSkills += 10;
					
					if (player->caps.magicSkills > 100)
						player->caps.magicSkills = 100;
					
				} else if (player->caps.smartness <= 50) {
					player->caps.dexterity -= 10;
					
					if (player->caps.dexterity < 0)
						player->caps.magicSkills = 0;
				}
				break;
			}
		}		
	}
	
	
} // end of updateCapabilities() function

