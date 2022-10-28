#include "shell.h"

void processLine(char *line){
	printf("This yo line??%s\n", line);
}

int main(){
	// Shell initialization
	buffer = malloc(sizeof(char) * MAX_BUFFER);

	while(true){
		// Display shell prefix
		printf("Shell: ");
		fflush(stdout);

		// Parse user input
		fgets(buffer, MAX_BUFFER, stdin);
		fflush(stdin);
		buffer[strlen(buffer) - 1] = '\0';

		// Attempt to run input
		processLine(buffer);
	}
	return 0;
}