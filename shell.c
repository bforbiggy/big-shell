#include "shell.h"

void processLine(char *line){
	printf("This yo line??%s\n", line);
}

int main(){
	// Automatic flushing
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	// Shell initialization
	buffer = malloc(sizeof(char) * MAX_BUFFER);
	dir = malloc(sizeof(char) * (PATH_MAX+1));
	getcwd(dir, PATH_MAX);

	while(true){
		// Display shell prefix and get user input
		printf("[bish %s]$ ", dir);
		fgets(buffer, MAX_BUFFER, stdin);

		// Sanitize and run input
		buffer[strlen(buffer) - 1] = '\0';
		processLine(buffer);
	}
	return 0;
}