#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "parse.h"
#include <string.h>
/*
 * parse.c
 *
 *  Created on: 15 mar 2016
 *      Author: albert
 */
const int LINE_MAX_SIZE = 1000000;

char* cutFirstWord(char **str) {

	char* s = *str;
	assert(s[0] != ' ' && s[0] != 0);
	int i=0;
	while(s[i] != ' ' && s[i]!='\n' &&  s[i] != 0) {
		i++;
	}

	if (s[i] == ' ' || s[i] == '\n') {
		s[i]=0;
		*str = s+i+1;
		return s;
	}
	if (s[i] == 0) {
		*str = 0;
		return s;
	}
	else assert(0);
	return 0;
}
char* CopyString(char* s) {
	char *s2 = malloc(strlen(s)+1);
	strcpy(s2,s);
	return s2;
}
char* cutAndCopyFirstWord(char **str) {
	char *s = cutFirstWord(str);
	return CopyString(s);
}
void loadArgumentsOfNewDiseaseEnter(InputStruct* inputStruct,
		char *arguments) {

	inputStruct->name = cutAndCopyFirstWord(&arguments);
	inputStruct->diseaseDescription = CopyString(arguments);
	inputStruct->operationType = new_disease_enter_description;
}
void loadArgumentsOfNewDiseaseCopy(InputStruct* inputStruct,
		char *arguments) {

	inputStruct->name = cutAndCopyFirstWord(&arguments);
	inputStruct->nameToCopy = cutAndCopyFirstWord(&arguments);
	inputStruct->operationType = new_disease_copy_description;
}
void loadArgumentsOfChangeDescription(InputStruct* inputStruct,
		char *arguments) {

	inputStruct->name = cutAndCopyFirstWord(&arguments);
	inputStruct->number=atoi(cutFirstWord(&arguments));
	inputStruct->diseaseDescription = CopyString(arguments);
	inputStruct->operationType = change_description;
}
void loadArgumentsOfPrintDescription(InputStruct* inputStruct,
		char *arguments) {

	inputStruct->name = cutAndCopyFirstWord(&arguments);
	inputStruct->number=atoi(cutFirstWord(&arguments));
	inputStruct->operationType = print_description;
}
void loadArgumentsOfDeletePatient(InputStruct* inputStruct,
		char *arguments) {

	inputStruct->name = cutAndCopyFirstWord(&arguments);
	inputStruct->operationType = delete_patient_data;
}

LoadDataFunction identifyLoadDataFunctionByString(char *function) {

	const int numberOfFunctions=5;
	static LoadDataFunction functionsPointers[] = {
		loadArgumentsOfNewDiseaseEnter,
		loadArgumentsOfNewDiseaseCopy,
		loadArgumentsOfChangeDescription,
		loadArgumentsOfPrintDescription,
		loadArgumentsOfDeletePatient
	};
	char * functionStrings [] = {
		"NEW_DISEASE_ENTER_DESCRIPTION",
		"NEW_DISEASE_COPY_DESCRIPTION",
		"CHANGE_DESCRIPTION",
		"PRINT_DESCRIPTION",
		"DELETE_PATIENT_DATA"
	};
	int i;
	for(i=0;i<numberOfFunctions;i++)
		if (strcmp(functionStrings[i],function) == 0)
			return functionsPointers[i];
	assert(0);
}
void initInputStruct(InputStruct *inputStruct) {
	inputStruct->diseaseDescription = NULL;
	inputStruct->name = NULL;
	inputStruct->nameToCopy = NULL;
	inputStruct->number = 0;
	inputStruct->operationType = 42;
}
InputStruct* loadInputToInputStruct(void) {

	InputStruct* inputStruct = malloc(sizeof(InputStruct));
	initInputStruct(inputStruct);
	char *lineStatic = NULL;
	size_t len = 0;
	if (getline(&lineStatic,&len,stdin) == -1) {
		free(inputStruct);
		free(lineStatic);
		return NULL;
	}
	char *line = lineStatic;
	char *functionName = cutFirstWord(&line);
	char *arguments = line;
	identifyLoadDataFunctionByString(functionName)(inputStruct,arguments);

	free(lineStatic);
	return inputStruct;
}
