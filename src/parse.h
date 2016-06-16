/*
 * parse.h
 *
 *  Created on: 15 mar 2016
 *      Author: albert
 */
#ifndef PARSE_H_
#define PARSE_H_


extern const int LINE_MAX_SIZE;



char* cutFirstWord(char **str);

typedef enum  {
	new_disease_enter_description,
	new_disease_copy_description,
	change_description ,
	print_description ,
	delete_patient_data ,
} OperationType ;

typedef struct InputStruct {
	char *name, *nameToCopy, *diseaseDescription;
	int number;
	OperationType operationType;
} InputStruct;
typedef void (*LoadDataFunction)(InputStruct*,char *Arguments);

InputStruct* loadInputToInputStruct(void);

void loadArgumentsOfNewDiseaseEnter(InputStruct* MyInputStruct,
		char *Arguments);
void loadArgumentsOfNewDiseaseCopy(InputStruct* MyInputStruct,
		char *Arguments);
void loadArgumentsOfChangeDescription(InputStruct* MyInputStruct,
		char *Arguments);
void loadArgumentsOfPrintDescription(InputStruct* MyInputStruct,
		char *Arguments);
void loadArgumentsOfDeletePatient(InputStruct* MyInputStruct,
		char *Arguments);
#endif /* PARSE_H_ */
