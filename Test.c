/*
 ============================================================================
 Name        : HtmlSrcList.c
 Author      : Me
 Version     :
 Copyright   : Your copyright notice
 Description : HTMLSrcList program in C that analyze the content of HTML files
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function pointer to count the white space Src matches
int countWhiteSpaceSrcMatches(char* content) {

	char* find = "src=\"";
	int findLength = strlen(find);
	if (strlen(content) == 0) {
		return 0;
	}

	int count = 0;
	char* cursor = content;

	while ((cursor = strstr(cursor, find))) {

		char prevChar = *(cursor - 1);

		if (prevChar == ' ' || prevChar == '\t' || prevChar == '\n') {
			count++;
		}

		cursor += findLength;
	}

	return count;

}
// function pointer to print the Src tag names
void printSrcTagNames(char* content) {

	char* find = "src=\"";
	int findLength = strlen(find);

	char* cursor = content;

	while ((cursor = strstr(cursor, find))) {

		char prevChar = *(cursor - 1);

		if (prevChar != ' ' && prevChar != '\t' && prevChar != '\n'
				&& prevChar != '\r') {
			cursor += findLength;
			continue;
		}

		char tagBuffer[100];

		char* reverseCursor = cursor;
		while (*(--reverseCursor) != '<')
			;

		int i = 0;
		while (1) {

			char nextChar = *(reverseCursor + ++i);
			if (nextChar == ' ' || nextChar == '\t' || nextChar == '\r'
					|| nextChar == '\n') {
				break;
			}
			//memset(tagBuffer, *nextCharPtr, 1);
		}

		strncpy(tagBuffer, reverseCursor + 1, i - 1);

		printf("%s\n", tagBuffer);

		memset(tagBuffer, 0, strlen(tagBuffer));

		cursor += findLength;
	}
}
// function to print the Urls
void printUrls(char* content) {

	char* find = "src=\"";
	int findLength = strlen(find);

	char* cursor = content;

	while ((cursor = strstr(cursor, find))) {

		char prevChar = *(cursor - 1);

		if (prevChar != ' ' && prevChar != '\t' && prevChar != '\n'
				&& prevChar != '\r') {
			cursor += findLength;
			continue;
		}

		int i = 0;
		char urlBuffer[1000];
		for (i = 0; i < 1000; i++) {
			urlBuffer[i] = '\0';
		}
		i = 0;
		while (*(cursor + findLength + i++) != '\"')
			;

		memset(urlBuffer, 0, strlen(urlBuffer));

//			char tagBuffer[100];
//
//			char* reverseCursor = cursor;
//			while (*(reverseCursor++) != '>')
//				;
//
//			int i = 0;
//			while (1) {
//
//				char nextChar = *(reverseCursor + ++i);
//				if (nextChar == " " || nextChar == '\t' || nextChar == '\r'
//						|| nextChar == '\n') {
//					break;
//				}
//				//memset(tagBuffer, *nextCharPtr, 1);
//			}

		strncpy(urlBuffer, cursor + findLength, i - 1);

		printf("%s\n", urlBuffer);

		memset(urlBuffer, 0, strlen(urlBuffer));

		cursor += findLength;
	}
}
// function pointer to print the frequencies
void printFrequencies(char *content) {

	char* find = "src=\"";
	int findLength = strlen(find);

	char* cursor = content;

	while ((cursor = strstr(cursor, find))) {

		char prevChar = *(cursor - 1);

		if (prevChar != ' ' && prevChar != '\t' && prevChar != '\n'
				&& prevChar != '\r') {
			cursor += findLength;
			continue;
		}

		char tagBuffer[100];

		char* reverseCursor = cursor;
		while (*(--reverseCursor) != '<')
			;

		int i = 0;
		while (1) {

			char nextChar = *(reverseCursor + ++i);
			if (nextChar == ' ' || nextChar == '\t' || nextChar == '\r'
					|| nextChar == '\n') {
				break;
			}
			//memset(tagBuffer, *nextCharPtr, 1);
		}

		strncpy(tagBuffer, reverseCursor + 1, i - 1);

		printf("%s\n", tagBuffer);

		memset(tagBuffer, 0, strlen(tagBuffer));

		cursor += findLength;
	}
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); // Turn off output buffering. Required for automated testing.

	char buffer[BUFSIZ];
	char input[100];
	char curlCommand[100]; // char array initialization
	strcpy(curlCommand, "curl -s ");

	printf("URL:\n"); // prompt
	scanf("%s", input);

	strcat(curlCommand, input);

	FILE *file;
	file = popen(curlCommand, "r"); // write into a file
	if (file == NULL) {
		printf("File could not be created!\n");
		return 1;
	}

	char html[100000];

	char* line;
	while ((line = fgets(buffer, BUFSIZ, file)) != 0) {
		strcat(html, line);
	}

	fgetc(stdin); //swallow trailing newline

	char nextChar;
	do {
		printf("Ready\n");
		nextChar = fgetc(stdin);
		fgetc(stdin); //swallow trailing newline

		switch (nextChar) {
		case 'c':
			printf("%d\n", countWhiteSpaceSrcMatches(html));
			break;
		case 't':
			printSrcTagNames(html);
			break;
		case 'u':
			printUrls(html);
			break;
		case 'f':
			printFrequencies(html);
			break;
		default:
			break;
		}

	} while (nextChar != 'q');

	return 0;
}

