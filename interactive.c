#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "interactive.h"

#define DELAY 15
#define INIT_SIZE 1024

//volatile char* comment = "Guess who just thought of the WORST way to make a comment";

int main() {
	//prompts user for name
	char name[INIT_SIZE];
	char* question = "Enter your name: ";
	oldSchoolPrint(question, strlen(question), DELAY);

	if (fgets(name, sizeof(name), stdin) == NULL) {
		printf("Error reading input.\n");
       		 return 1;
   	 }

	//greets player by name
   	char greeting[INIT_SIZE] = "Greetings Professor ";
    	strncat(greeting, name, INIT_SIZE);
      	//there is a newline character we get from the fgets we have to remove
	greeting[strcspn(greeting, "\n")] = 0;
	strncat(greeting, ", would you like to a play a game of Global Thermonuclear War? \n", 200);

    	oldSchoolPrint(greeting, sizeof(greeting), DELAY);

	//asks if player wants to play the game
	oldSchoolPrint("[Y]es or [N]o?\n", strlen("[Y]es or [N]o?\n"), DELAY);

	char answer[INIT_SIZE];
	char* reply;

	if(fgets(answer, sizeof(answer), stdin ) != NULL ){
		switch(tolower(answer[0])){
			case 'y':
				game(DELAY);
				break;
			case 'n':
				reply = "Then you should watch Dr. Strangelove so you can learn to love the bomb.\n";
				oldSchoolPrint(reply, strlen(reply), DELAY);
				break;
			default:
				reply = "invalid input\n";
				oldSchoolPrint(reply, strlen(reply), DELAY);
				break;
		}	
	} else {
		fprintf(stderr, "error reading input");
	}
	credits(DELAY);

    return 0;
}
