#include "util.h"

/**
 * @brief Splits a string into a singly linked list using specified delimiter.
 * 
 * @param string string to split
 * @param delim what to split with
 * @param size a pointer to store size
 * @return Singly linked list of all tokens
 */
Node *split(char* string, const char delim[], int* size){
	char *token = strtok(string, delim);
	*size = 1;

	// Initialize head with token
	Node *head = malloc(sizeof(Node));
	head->val = token;
	head->next = NULL;

	// Parse remaining tokens
	Node *curr = head;
	while((token = strtok(string, delim)) != NULL){
		curr->next = init(token, NULL);
		curr = curr->next;
		(*size)++;
	}
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