#include "parse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
/*
 * test.c
 *
 *  Created on: 15 mar 2016
 *      Author: albert
 */
void testCutFirstWord() {

	char *s2 = "Piotr Adrian Albert Filip";
	char *s = malloc(50*sizeof(char));
	char *sStatic = s;
	s = strcpy(s,s2);

	assert (strcmp("Piotr", cutFirstWord(&s)) == 0);

	assert (strcmp("Adrian", cutFirstWord(&s)) == 0);
	assert (strcmp("Albert", cutFirstWord(&s)) == 0);
	assert (strcmp("Filip", cutFirstWord(&s)) == 0);

	free(sStatic);
}

void debugInputStruct(InputStruct *i) {

	assert (i != NULL);
//	assert (i->name != NULL);
//	assert (i->diseaseDescription != NULL);
//	assert (i->nameToCopy != NULL);
	fprintf(stderr,"name: %s nameToCopy: %s diseaseDescription: %s "
			"operationType: %d number: %d \n\n",i->name,
		i->nameToCopy,i->diseaseDescription, i->operationType, i->number);
}
void defaultContructorInputStruct(InputStruct *i) {
	i->name="";
	i->diseaseDescription="";
	i->nameToCopy="";

//	i->name=NULL;
//	i->diseaseDescription=NULL;
//	i->nameToCopy=NULL;
}
void testLoadArgumentsOfNewDiseaseEnter () {

	char * arguments2 = "Kamil Nerwica";
	char * arguments = malloc(50*sizeof(char));
	strcpy(arguments,arguments2);
	InputStruct* i = malloc(sizeof(InputStruct));
	//defaultContructorInputStruct(i);

	debugInputStruct(i);
	loadArgumentsOfNewDiseaseEnter(i,arguments);
	debugInputStruct(i);
	assert(strcmp(i->name,"Kamil") == 0);
	assert(strcmp(i->diseaseDescription,"Nerwica") == 0 );
	assert(i->nameToCopy == NULL);
	assert(i->number == 0);
	assert(i->operationType == new_disease_enter_description);

	free(arguments);
	free(i->name);
	free(i->diseaseDescription);
	free(i);
}
void testParse() {

	InputStruct *myInputStruct=loadInputToInputStruct();
	debugInputStruct(myInputStruct);
	free(myInputStruct->name);
	free(myInputStruct->diseaseDescription);
	free(myInputStruct);
}


