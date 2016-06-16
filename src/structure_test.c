/*
 * structure_test.c
 *
 *  Created on: 22 mar 2016
 *      Author: albert
 */
#include "structure_test.h"
#include "structure.h"
#include "parse.h"
#include "diseases.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern Patient* lastPatient;
char* AllocateMemoryForConstString(char* s) {
	char *s2;
	s2 = malloc(strlen(s)+1);
	strcpy(s2,s);
	return s2;
}
void newDiseaseEnterDescriptionTest() {

	assert(lastPatient == NULL);
	InputStruct *i = malloc(sizeof(InputStruct));
	i->name=AllocateMemoryForConstString("Maciek");
	i->diseaseDescription=AllocateMemoryForConstString("Goraczka");

	newDiseaseEnterDescription(i);

	assert(strcmp(lastPatient->name,"Maciek") == 0);
	assert(strcmp(lastPatient->lastDisease->
		myDescription->description,"Goraczka") == 0);
	assert(lastPatient->previousPatient == NULL);
	assert(lastPatient->lastDisease->myDescription->counter == 1);

	i->name=AllocateMemoryForConstString("Filip");
	i->diseaseDescription=AllocateMemoryForConstString("Goraczka");

	newDiseaseEnterDescription(i);

	assert(strcmp(lastPatient->previousPatient->lastDisease->
		myDescription->description,"Goraczka") == 0);

	assert(strcmp(lastPatient->name,"Filip") == 0);

	i->name=AllocateMemoryForConstString("Maciek");
	i->diseaseDescription=AllocateMemoryForConstString("Bialaczka");

	newDiseaseEnterDescription(i);

	assert(strcmp(lastPatient->previousPatient->lastDisease->
		myDescription->description,"Bialaczka") == 0);

	assert(strcmp(lastPatient->previousPatient->lastDisease->
		previousDisease->myDescription->description,"Goraczka") == 0);

	destructor();
	free(i);
}
InputStruct* createSimpleStructure1() {

	assert(lastPatient == NULL);
	InputStruct* i = malloc(sizeof(InputStruct));
	i->name = AllocateMemoryForConstString("Maciek");
	i->diseaseDescription = AllocateMemoryForConstString("Bialaczka");
	newDiseaseEnterDescription(i);
	i->nameToCopy = AllocateMemoryForConstString("Maciek");
	i->name = AllocateMemoryForConstString("Filip");
	newDiseaseCopyDescription(i);
	return i;
}

void newDiseaseCopyDescriptionTest() {

	InputStruct* i = createSimpleStructure1();
	assert(strcmp(lastPatient->name,"Filip") == 0);

	assert(strcmp(lastPatient->lastDisease->myDescription->description,"Bialaczka") == 0);

	assert(strcmp(lastPatient->previousPatient->lastDisease->myDescription->description,"Bialaczka") == 0);

	assert(lastPatient->previousPatient->lastDisease->myDescription->counter == 2);

	destructor();

	free(i);
}
//zakladam w tej funkcji ze poprzednia dziala
void setInputStructChangeDescription(InputStruct* i,char* name,char* diseaseDescription, int number) {
	i->name=AllocateMemoryForConstString(name);
	i->diseaseDescription=AllocateMemoryForConstString(diseaseDescription);
	i->number=number;
	changeDescription(i);
}
void changeDescriptionTest() {
	InputStruct* i = createSimpleStructure1();

	i->name=AllocateMemoryForConstString("Maciek");
	i->diseaseDescription=AllocateMemoryForConstString("Goraczka");

	newDiseaseEnterDescription(i);

	setInputStructChangeDescription(i,"Maciek","Rak",2);

	assert(strcmp(lastPatient->previousPatient->lastDisease->previousDisease
		->myDescription->description,"Rak") == 0);
	assert(lastPatient->lastDisease->myDescription->counter == 1);

	setInputStructChangeDescription(i,"Filip","Rak",2);


	destructor();
	free(i);
}
void deletePatientDataTest() {
	InputStruct* i = createSimpleStructure1();

	i->name=AllocateMemoryForConstString("Maciek");

	deletePatientData(i);

	assert(strcmp(lastPatient->lastDisease->myDescription->description,"Bialaczka") == 0);
	assert(lastPatient->lastDisease->myDescription->counter == 1);

	i->name=AllocateMemoryForConstString("Filip");

	deletePatientData(i);

	assert(lastPatient->lastDisease == NULL);
	assert(lastPatient->previousPatient->lastDisease == NULL);

	destructor();
	free(i);

}


