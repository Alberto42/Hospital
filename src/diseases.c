/*
 * diseases.c
 *
 *  Created on: 20 mar 2016
 *      Author: albert
 */
#include "diseases.h"
#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

DiseaseDescription* lastDiseaseDescription;
int NumberOfDiseaseDescriptions;
void destructDiseaseDescription(DiseaseDescription* diseaseDescription) {
	if (diseaseDescription->counter > 1)
		diseaseDescription->counter--;
	else {
		free(diseaseDescription->description);
		free(diseaseDescription);
		NumberOfDiseaseDescriptions--;
		assert(NumberOfDiseaseDescriptions >= 0);
	}
}
void destructDiseaseRecursive(Disease* disease) {

	if (disease == NULL)
		return;
	if (disease->previousDisease != NULL) {
		destructDiseaseRecursive(disease->previousDisease);
	}
	destructDiseaseDescription(disease->myDescription);
	free(disease);
}

DiseaseDescription* ConstructDiseaseDescription(char* description) {
	DiseaseDescription* newDiseaseDescription = malloc(
			sizeof(DiseaseDescription));
	newDiseaseDescription->description = description;
	newDiseaseDescription->counter = 1;
	NumberOfDiseaseDescriptions++;
	return newDiseaseDescription;
}

void PrintNumberOfDescriptions() {
	fprintf(stderr,"%s%d\n","DESCRIPTIONS: ",NumberOfDiseaseDescriptions);
}
void addDisease(Patient *myPatient, char *description) {

	Disease *newDisease = malloc(sizeof(Disease));
	newDisease->myDescription = ConstructDiseaseDescription(description);

	newDisease->previousDisease=myPatient->lastDisease;
	myPatient->lastDisease=newDisease;
}
void addDiseaseWithCopiedDescription(Patient *myPatient, DiseaseDescription *description) {
	Disease *newDisease = malloc(sizeof(Disease));
	newDisease->myDescription=description;
	description->counter++;
	newDisease->previousDisease=myPatient->lastDisease;
	myPatient->lastDisease=newDisease;
}
//passed disease is included
int NumberOfDiseases(Disease* disease) {
	int result=0;
	while(disease != NULL) {
		disease = disease->previousDisease;
		result++;
	}
	return result;
}

Disease* nthDisease(Disease* disease,int n) {
	assert(disease != NULL);
	if (n <= 0)
		return NULL;
	int i=0;
	for(i=0;i<n-1;i++) {
		if (disease->previousDisease == NULL)
			return NULL;
		disease=disease->previousDisease;
	}

	return disease;
}
Disease* nthLastDisease(Disease* disease,int n) {
	assert(disease != NULL);
	return nthDisease(disease, NumberOfDiseases(disease) - n + 1);
}
