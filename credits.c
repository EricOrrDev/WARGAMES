#include "credits.h"

#define creditsSize 4
void credits(const unsigned int DELAY){
	char* credits[creditsSize] = {"Credit to geeksforgeeks for the screen clearing regex", "This program is funded by David Haren and the charitable organization for Birds with Heart Disease.", "Credit to ChatGPT for helping me solve a memory leak issue with file handling", "Thank you to Robert Surton for being an excellent instructor"};
	for(int i=0; i<creditsSize;i++){
		oldSchoolPrint(credits[i], strlen(credits[i]), DELAY);
		oldSchoolPrint("\n", strlen("\n"), DELAY);
	}
};
