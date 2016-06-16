/*
 * structure.h
 *
 *  Created on: 16 mar 2016
 *      Author: albert
 */
#ifndef STRUCTURE_H_
#define STRUCTURE_H_
#include "parse.h"
typedef void (*EditPatientsData) (InputStruct *input);

typedef struct Patient {
	struct Patient* previousPatient;
	struct Disease* lastDisease;
	char *name;
} Patient;


void newDiseaseEnterDescription(InputStruct *input);
void newDiseaseCopyDescription (InputStruct *input);
void changeDescription (InputStruct *input );
void printDescription (InputStruct *input);
void deletePatientData (InputStruct *input);
void constructor();
void destructor();

EditPatientsData  recognizeFunction(InputStruct *input);
void modifyPatientData(InputStruct *input);


#endif /* STRUCTURE_H_ */
