/*
 * structure.c
 *
 *  Created on: 15 mar 2016
 *      Author: albert
 */
#include "parse.h"
#include "diseases.h"
#include <stdio.h>
#include "structure.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Patient* lastPatient;
Patient* findPatient(char *name) {

	Patient* target = lastPatient;
	while(target!= NULL) {
		if (strcmp(target->name,name) == 0)return target;
		target = target->previousPatient;
	}
	return NULL;
}
void addPatient(char *name) {

	Patient* newPatient = malloc(sizeof(Patient));

	newPatient->name=name;
	newPatient->lastDisease=NULL;
	newPatient->previousPatient=lastPatient;
	lastPatient=newPatient;
}
Patient* findOrCreatePatient(InputStruct* input) {

	Patient* target = findPatient(input->name);
	if (target == NULL) {
		addPatient(input->name);
		target = lastPatient;
	} else {
		free(input->name);
	}
	return target;
}
void ok() {
	printf("%s\n","OK");
}
void newDiseaseEnterDescription(InputStruct *input) {

	Patient* target = findOrCreatePatient(input);
	addDisease(target,input->diseaseDescription);
	ok();
}
void ignore() {
	printf("%s\n","IGNORED");
}

void newDiseaseCopyDescription (InputStruct *input) {
	Patient* patient2 = findPatient(input->nameToCopy);
	free(input->nameToCopy);
	if (patient2 == NULL || patient2->lastDisease == NULL) {
		free(input->name);
		ignore();
		return;
	}
	Patient* patient1 = findOrCreatePatient(input);
	addDiseaseWithCopiedDescription(patient1,
		patient2->lastDisease->myDescription);
	ok();
}
void notFoundInChangeDescription(InputStruct *input) {
	ignore();
	free(input->name);
	free(input->diseaseDescription);
}
Disease* FindPatientNthDisease(char *name, int number) {
	Patient* patient = findPatient(name);
	if (patient == NULL) {
		return NULL;
	}
	if (patient->lastDisease == NULL)
		return NULL;
	Disease* disease = nthLastDisease(patient->lastDisease,number);
	if (disease == NULL) {
		return NULL;
	}
	return disease;
}

void changeDescription (InputStruct *input ) {

	Disease* disease = FindPatientNthDisease(input->name,input->number);
	if (disease == NULL) {
		notFoundInChangeDescription(input);
		return;
	}
	destructDiseaseDescription(disease->myDescription);
	disease->myDescription=
		ConstructDiseaseDescription(input->diseaseDescription);
	free(input->name);
	ok();
}
void printDescription (InputStruct *input) {
	Disease* disease = FindPatientNthDisease(input->name,input->number);
		if (disease == NULL) {
			ignore();
			free(input->name);
			return;
		}
	printf("%s",disease->myDescription->description);
	free(input->name);
}
void deletePatientData (InputStruct *input) {
	Patient* patient = findPatient(input->name);
	if (patient == NULL) {
		ignore();
		free(input->name);
		return;
	}
	destructDiseaseRecursive(patient->lastDisease);
	patient->lastDisease = NULL;

	free(input->name);
	ok();
}
EditPatientsData  recognizeFunction(InputStruct *input) {

	EditPatientsData Functions[] = {
		newDiseaseEnterDescription,
		newDiseaseCopyDescription,
		changeDescription,
		printDescription,
		deletePatientData
	};
	return Functions[input->operationType];
}
void modifyPatientData(InputStruct *input) {

	recognizeFunction(input)(input);
}

void constructor() {
	lastPatient = NULL;
}
void destructPatientRecursive(Patient *patient) {
	if (patient->previousPatient != NULL){
		destructPatientRecursive(patient->previousPatient);
	}
	free(patient->name);
	if (patient->lastDisease != NULL)
		destructDiseaseRecursive((patient->lastDisease));
	free(patient);

}
void destructor() {
	if (lastPatient != NULL)
		destructPatientRecursive(lastPatient);
	lastPatient=NULL;
}

