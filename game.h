#ifndef GAME_H
#define GAME_H

#include "oldprint.h"

#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//This is essentially the enum for the character select screen
//should add more for artistic purposes
typedef enum{
	US,
	USSR
} PlayerNation;



//enum for actions, think steal or not steal, rock paper scissors
typedef enum{
	Cooperate,
	Revolt
} PlayerActions;

//the enum for round results outcome matrix 
typedef enum{
	Player1Wins,
	Player2Wins,
	BothWin,
	BothLose,
	Invalid	//added to handle a control flow warning
} RoundResults;

//Would do a class but instead we are using a player struct
typedef struct{
	PlayerNation m_PlayerNation;
	int points;
	PlayerActions m_lastRoundAction;
} Player;

//player constructor
Player initPlayer(PlayerNation nation);

//ought to consider passing these parameters by pointer
char* getPlayerNationString(PlayerNation nation);

//initalizes the players and begins the game loop
void game(const unsigned int DELAY);

//produces the string to announce who won the game
char* resultOfGame(Player* player1, Player* player2);

//produces the string to announce who won the round
char* announceRoundResults(RoundResults round);

//evaluations the player actions to decide a winner of the round, and returns the enum of such result
RoundResults resultOfRound(Player* player1, Player* player2, PlayerActions* player1Action, PlayerActions* player2Action);

//shows previous round results, prompts players for answer
//main bulk of the game is done here
void gameRound(unsigned int DELAY, Player* player1, Player* player2, int roundCount);

//takes the players actions and by chance flips them to the opposite action
void messWithActions(PlayerActions* player1Action, PlayerActions* player2Action, int roundCount);

//stringifies the player action enum
char* getPlayerActionString(PlayerActions* playerAction);

//logs place choices and what actions were ultimately taken
void logCurrentState(PlayerActions* player1Action, PlayerActions* player2Action, PlayerActions* player1ActionAfter, PlayerActions* player2ActionAfter, int roundCount);

#endif
