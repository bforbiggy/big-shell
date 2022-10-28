#include "util.h"

// Splits string using delim and stores in args
void split(char **args, char* string, const char delim[]){
	char *token = strtok(string, delim);

	int i;
	for (i = 0; i < 200; i++){
		args[i] = token;
		token = strtok(NULL, delim);
		if(token == NULL)
			break;
	}

	// Null terminate
	args[i + 1] = NULL;
}

/**
 * @brief Returns whether or not a character is an operator
 * 
 * @param c The character to compare
 * @return Whether c is an operator character.
 */
bool isOperator(char c){
	return c == '<' || c == '>';
}

/**
 * @brief Returns the last index of target in string or -1 if not found.
 * 
 * @param str string to search through
 * @param c the character to find
 * @return Last location of target in string.
 */
int lastIndex(const char str[], char target){
	int loc = -1;
	for (int i = 0; str[i] != '\0'; i++){
		if(str[i] == target)
			loc = i;
	}
	return loc;
}

/**
 * @brief Detects whether or not a file exists based on an input path.
 * This does not check true existence but whether the file is accessible, which is what is practically required.
 * 
 * @param path The path to the target file. Accepts absolute paths, relative paths and base name paths.
 * @return Whether the file exists
 */
bool exists(const char *path){
  FILE *file = fopen(path, "r");
  if (file){
  	fclose(file);
    return true;
  }
  return false;
}