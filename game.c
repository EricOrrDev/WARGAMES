#include "game.h"
#define INIT_SIZE 1024

Player initPlayer(PlayerNation nation){
	Player newPlayer;
	newPlayer.m_PlayerNation = nation;
	newPlayer.points = 0;
	newPlayer.m_lastRoundAction = Cooperate;
	return newPlayer;
};

char* getPlayerNationString(PlayerNation nation){
	switch (nation){
		case US:
			return "US";
		case USSR:
			return "USSR";
		default:
			return "Nation Unknown";
	}
}

char* resultOfGame(Player* player1, Player* player2){
	//kind of question using a static here, it gets rid of the warning in a way that is somewhat irresponsible
	//honestly thinking about strings as arrays instead of objects is my least favorite thing about C
	static char results[INIT_SIZE]; 
	if(player1->points == player2->points){
		snprintf(results, INIT_SIZE, "It's a tie! Player 1 : %i Points.\nPlayer 2 : %i Points.\n", player1->points, player2->points);
	} else if(player1->points > player2->points){
		snprintf(results, INIT_SIZE, "Player 1 wins!\nPlayer 1 : %i Points.\nPlayer 2 : %i Points.\n", player1->points, player2->points);
	} else if(player1->points < player2->points){
		snprintf(results, INIT_SIZE,"Player 2 wins!\nPlayer 1 : %i Points.\nPlayer 2 : %i Points.\n", player1->points, player2->points);
	}
	return results;
}

RoundResults resultOfRound(Player* player1, Player* player2, PlayerActions* player1Action, PlayerActions* player2Action){
	player1->m_lastRoundAction = *player1Action;
	player2->m_lastRoundAction = *player2Action;

	if( (*player1Action == Cooperate) && (*player2Action == Cooperate) ){
		player1->points += 3;
		player2->points += 3;
		return BothWin;
	} else if( (*player1Action == Cooperate) && (*player2Action == Revolt) ){
		player1->points -= 1;
		player2->points += 2;
		return Player2Wins;
	} else if( (*player1Action == Revolt) && (*player2Action == Cooperate) ){
		player1->points += 2;
		player2->points -= 1;
		return Player1Wins;
	} else if( (*player1Action == Revolt) && (*player2Action == Revolt) ){
		player1->points -= 2;
		player2->points -= 2;
		return BothLose;
	}

		return Invalid;
}

char* announceRoundResults(RoundResults round){
	switch(round){
		case BothWin:
			return "Both Players Cooperated!\n";
		case BothLose:
			return "Both Players Revolted!\n";
		case Player1Wins:
			return "Player 1 Won the Round!\n";
		case Player2Wins:
			return "Player 2 Won the Round!\n";
		default:
			return "There was an error with actions";
	}
}

void messWithActions(PlayerActions* player1Action, PlayerActions* player2Action, int roundCount){
	const int chance = 5;
	//uncomment line below to disable randomization
	//const int chance = 0;
	int randomChance = rand() % 100;

	//hold the actions values before they might get messed with, for logging purposes
	PlayerActions* player1ActionIntended = player1Action;
	PlayerActions* player2ActionIntended = player2Action;
	
	//roll for player 1 randomization
	if(randomChance < chance){
		if( *player1Action == Cooperate){
			*player1Action = Revolt;
		} else {
			*player1Action = Cooperate;
		}
	}
	//reroll for player 2 randomization
	randomChance = rand() % 100;
	if(randomChance < chance){
		if( *player2Action == Cooperate){
			*player2Action = Revolt;
		} else{
			*player2Action = Cooperate;
		}
	}
	logCurrentState(player1ActionIntended, player2ActionIntended,player1Action, player2Action, roundCount);
}

char* getPlayerActionString(PlayerActions* playerAction){
	if(playerAction == Cooperate){
		return "Cooperate";
	} else{
		return "Revolt";
	}
}

void logCurrentState(PlayerActions* player1Action, PlayerActions* player2Action, PlayerActions* player1ActionAfter, PlayerActions* player2ActionAfter, int roundCount){
	const char* fileName = ".GameLog";
	FILE* logFile = fopen(fileName,"a");
	if(!logFile){
		printf("Error logging player actions");
		return;
	}
	char* player1IntendedAction = getPlayerActionString(player1Action);
	char* player2IntendedAction = getPlayerActionString(player2Action);
	char* player1UltimateAction = getPlayerActionString(player1ActionAfter);
	char* player2UltimateAction = getPlayerActionString(player2ActionAfter);


	fprintf(logFile, "Round %i : \n", roundCount);
	
	if(player1IntendedAction == player1UltimateAction){
		fprintf(logFile,"Player 1's action was : %s.\n", player1IntendedAction);
	} else {
		fprintf(logFile,"Player 1 intended to %s but instead they %sed.\n", player1IntendedAction, player1UltimateAction);
	}

	if(player2IntendedAction == player2UltimateAction){
		fprintf(logFile, "Player 2's action was : %s.\n", player2IntendedAction);
	} else {
		fprintf(logFile, "Player 1 intended to %s but instead they %sed.\n", player2IntendedAction, player2UltimateAction);
	}

	

	fclose(logFile);
}

void gameRound(unsigned int DELAY,Player* player1, Player* player2, int roundCount){

	char* player1Question = "Player 1, will you\n[1] Cooperate\nOR\n[2] Revolt\n";
	oldSchoolPrint(player1Question, strlen(player1Question), DELAY);
	
	//get player 1's action
	PlayerActions player1Action;
	char player1Answer[10];
	if(fgets(player1Answer, sizeof(player1Answer), stdin) != NULL){
		switch(tolower(player1Answer[0])){
			case '1':
				player1Action = Cooperate;
				break;
			case '2':
				player1Action = Revolt;
				break;
			default:
				player1Action = Cooperate;
				break;
		}
	}

	//regex to clear screen without being platform specific
	//credit to https://www.geeksforgeeks.org/clear-console-c-language/ for this line
	printf("\e[1;1H\e[2J");

	//get player 2's action
	char* player2Question = "Player 2, will you\n[1] Cooperate\nOR\n[2] Revolt\n";
	oldSchoolPrint(player2Question, strlen(player2Question), DELAY);

	PlayerActions player2Action;
	char player2Answer[10];
	if(fgets(player2Answer, sizeof(player2Answer), stdin) != NULL){
		switch(tolower(player2Answer[0])){
			case '1':
				player2Action = Cooperate;
				break;
			case '2':
				player2Action = Revolt;
				break;
			default:
				player2Action = Cooperate;
				break;
		}
	}
	printf("\e[1;1H\e[2J");

	//possibly randomize player actions
	messWithActions(&player1Action, &player2Action, roundCount);

	//reveal the results of the round
	RoundResults endOfRoundResults = resultOfRound(player1, player2, &player1Action, &player2Action);
	printf("\e[1;1H\e[2J");
	char* announcement = announceRoundResults(endOfRoundResults);
	oldSchoolPrint(announcement, strlen(announcement), DELAY);
}

void game(const unsigned int DELAY){
	//seeding the random num generator for set of options that might get choosen
	srand(time(NULL));
	char* question = "Choose your character :\n[1] RONALD REAGAN : AMERICA\n[2] MIKHAIL GORBACHEV : USSR\n";
	oldSchoolPrint(question, strlen(question), DELAY);

	char answer[10];
	Player player1;
	Player player2;
	//evaluates player character selection
	//in big brother style, only player 1 gets to choose
	if(fgets(answer, sizeof(answer), stdin) != NULL){
		switch(tolower(answer[0])){
			case '1':
				player1 = initPlayer(US);
				player2 = initPlayer(USSR);
			       	break;
			case '2':
				player1 = initPlayer(USSR);
				player2 = initPlayer(US);
				break;
			default:
				player1 = initPlayer(US);
				player2 = initPlayer(USSR);
				break;	
		}
	}

	char reply[INIT_SIZE];
	snprintf(reply, INIT_SIZE, "Player 1 has chosen : %s.\nPlayer 2 has chosen : %s.\n",getPlayerNationString(player1.m_PlayerNation), getPlayerNationString(player2.m_PlayerNation));
	oldSchoolPrint(reply, strlen(reply), DELAY);
	
	//change this varible to choose how many rounds the game plays for
	const int maxNumberRounds = 15;
	const int minNumberRounds = 5;
	const int roundCount = minNumberRounds + rand() % (maxNumberRounds - minNumberRounds + 1);
	int gameLoopCount = 1;
	while(gameLoopCount <= roundCount ){
		gameRound(DELAY, &player1, &player2, gameLoopCount);
		gameLoopCount++;
	}
	char* result = resultOfGame(&player1, &player2);
	oldSchoolPrint(result, strlen(result), DELAY);
}
