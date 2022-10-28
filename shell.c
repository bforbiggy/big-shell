#include "shell.h"

void processLine(char *line){
	printf("This yo line??%s\n", line);
}

int main(){
	// Shell initialization
	buffer = malloc(sizeof(char) * MAX_BUFFER);
	dir = malloc(sizeof(char) * (PATH_MAX+1));
	getcwd(dir, PATH_MAX);

	while(true){
		// Display shell prefix
		printf("[bish %s]$", dir);
		fflush(stdout);

		// Parse user input
		fgets(buffer, MAX_BUFFER, stdin);
		fflush(stdin);
		printf("Index: %d\n", lastIndex(buffer, '\n'));
		buffer[strlen(buffer) - 1] = '\0';

		// Attempt to run input
		processLine(buffer);
	}
	return 0;
}