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
//include header file
#include "game_functions.h"
#include "game_functions.c"


// main function
int main(void) {

	size_t 
		i;
	unsigned int 
		numSlots, // the number of slots in the game, entered by the user
		numPlayers, // the number of players in the game, entered by the user
		turnChoice; // the 
	
	//global variable used in sortPlayers (PLANNING ON CHANGING IT FROM A GLOBAL TO A LOCAL SOMEHOW)
	struct PLAYER 
				gamePlayers[MAX_PLAYERS];	
	struct SLOT
				*gameSlots; // a pointer to a struct SLOT object (the first one in the array)
				
	time_t
			currentTime;
	
	srand((unsigned) time(&currentTime));
	
	sortPlayers(gamePlayers, &numPlayers);
	
	
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
	setPlayerPositions(numSlots, gameSlots, numPlayers, gamePlayers);

	// start the game - Player1 -> PlayerN will have a turn
	for (i = 0; i < numPlayers; i++) {		
		nextTurn(numSlots, gameSlots, numPlayers, gamePlayers, &gamePlayers[i]);
	}
	
	printf("\n\nGame Over!\nHere are the end-game stats for every player!\n");


	//prints out <player name> (<player Type>, <life_pts>)
	for(i = 0; i < numPlayers; i++)
	{
		printf("\n%s (%s, %d)", gamePlayers[i].name, getPtypeString(gamePlayers[i].playerType), gamePlayers[i].life_pts);
	}
	printf("\n\nEND OF APP EXECUTION!\n");

	return EXIT_SUCCESS;
}

