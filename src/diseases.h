/*
 * diseases.h
 *
 *  Created on: 20 mar 2016
 *      Author: albert
 */

#ifndef DISEASES_H_
#define DISEASES_H_

#include "structure.h"
typedef struct DiseaseDescription {
	char *description;
	int  counter;
} DiseaseDescription;
typedef struct Disease {
	struct Disease* previousDisease;
	DiseaseDescription* myDescription;
} Disease;
void destructDiseaseDescription(DiseaseDescription* diseaseDescription);
void addDiseaseWithCopiedDescription(Patient *myPatient, DiseaseDescription *description);
Disease* nthDisease(Disease* disease,int n);
void addDisease(Patient *myPatient, char *description);
void destructDiseaseRecursive(Disease* disease);
void addDiseaseWithCopiedDescription(Patient *myPatient, DiseaseDescription *description);
DiseaseDescription* ConstructDiseaseDescription(char* description);
Disease* nthLastDisease(Disease* disease,int n);
void PrintNumberOfDescriptions();

#endif /* DISEASES_H_ */
