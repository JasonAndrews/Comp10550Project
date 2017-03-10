/*
 ============================================================================
 Name        : game_functions.c
 Authors     : 
				Jason Andrews
				Jeremiah Wangaruro
				
 Version     : 0.1
 Description : 	This C file contains all the necessary functions for the game
 ============================================================================
*/



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
			slotString = "Level Ground";
			break;
		}
		case HILL: {
			slotString = "Hill";
			break;
		}
		case CITY: {
			slotString = "City";
			break;
		}
		default: {
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
			typeString = "Elf";
			break;
		}
		case Human: {
			typeString = "Human";
			break;
		}
		case Ogre: {
			typeString = "Ogre";
			break;
		}
		case Wizard:{
			typeString = "Wizard";
			break;
		}
		default:{
			typeString = "ERROR";
			break;
		}
	}
	
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
 

void sortPlayers(struct PLAYER *gamePlayers, int *numPlayers)
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
			fgets(gamePlayers[i].name, 20, stdin);
			
			// remove the NEWLINE character from the player's name.
			for(j = 0; gamePlayers[i].name[j] != '\0'; j++) { 				
				if (gamePlayers[i].name[j] == '\n') {
					gamePlayers[i].name[j] = '\0'; // set the current character as the EOS character
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
			gamePlayers[i].playerType=Elf;
			break;

			case 2:
			gamePlayers[i].playerType=Human;
			break;

			case 3:
			gamePlayers[i].playerType=Ogre;
			break;

			case 4:
			gamePlayers[i].playerType=Wizard;
			break;

			default:
			printf("ERROR INVALID ENTRY:Please enter a number between 1 and 4");
			}
			
			if (choice >= 1 && choice <= 4) {
				
				gamePlayers[i].life_pts = MAX_PTS;				
				
				sortCap(gamePlayers, i);			
				
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
void sortCap(struct PLAYER *gamePlayers, int i)
{
	int sum,j;
	bool valid;
	time_t currentTime;
	srand((unsigned) time(&currentTime));
	
	if(gamePlayers[i].playerType==Human)
	{
		do {
			
			gamePlayers[i].caps.smartness = 1 + (rand() % 100);
			gamePlayers[i].caps.luck = 1 + (rand() % 100);
			gamePlayers[i].caps.strength = 1 + (rand() % 100);
			gamePlayers[i].caps.magicSkills = 1 + (rand() % 100);
			gamePlayers[i].caps.dexterity= 1 + (rand() % 100);
			
			sum = getCapabilitySum(&gamePlayers[i]);
			
			if(sum < 300)
				valid = true;
			else 
				valid = false;
			
		} while (!valid);
	}
		
	if(gamePlayers[i].playerType==Ogre)
	{
		do
		{
			gamePlayers[i].caps.magicSkills = 0;
			gamePlayers[i].caps.smartness = rand()%20;
			gamePlayers[i].caps.strength = 80+rand()%20;
			gamePlayers[i].caps.dexterity = 80+rand()%20;
			
			if((gamePlayers[i].caps.smartness + gamePlayers[i].caps.luck) < 50)
				valid = true;
			else
				valid = !false;
			
		} while(!valid);
	}
		
	if(gamePlayers[i].playerType==Elf)
	{
		gamePlayers[i].caps.luck = 60+rand()%40;
		gamePlayers[i].caps.smartness = 70+rand()%30;
		gamePlayers[i].caps.strength = 1+rand()%49;
		gamePlayers[i].caps.magicSkills = 51+rand()%29;
		gamePlayers[i].caps.dexterity = 1+rand()%99;
	}
	
	if(gamePlayers[i].playerType==Wizard)
	{
		
		gamePlayers[i].caps.luck = 50+rand()%50;
		gamePlayers[i].caps.smartness = 90+rand()%10;
		gamePlayers[i].caps.strength = 1+rand()%19;
		gamePlayers[i].caps.magicSkills = 80+rand()%20;
		gamePlayers[i].caps.dexterity = 1+rand()%99;
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

void nextTurn(unsigned int numSlots, struct SLOT *gameSlots, unsigned numPlayers, struct PLAYER *gamePlayers, struct PLAYER *player) {
	
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
			attack(gamePlayers, player, numPlayers);
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

		if (abs(player->position - gamePlayers[i].position) < minDist) {
			minDist = abs(player->position - gamePlayers[i].position);
		}
	}
	
	for (i = 0; i < numPlayers; i++) {
		
		if ((&gamePlayers[i]) == player) {
			continue;
		}
		
		// if the selected player's position MINUS the currently iterated player's position - update minDist
		if (abs(player->position - gamePlayers[i].position) == minDist) {
			closeByPlayers[numClosePlayers] = gamePlayers[i];
			numClosePlayers++;
		}
		
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

	if((gamePlayers[attackedPlayer].caps.strength)<=70)
	{
		gamePlayers[attackedPlayer].life_pts-=(0.5*(gamePlayers[attackedPlayer].caps.strength));
	}
	else{
		player->life_pts-=(0.3*(player->caps.strength));
	}	 
	
	printf("\nYou ATTACKED player %s!\n", closeByPlayers[attackedPlayer].name);
	
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