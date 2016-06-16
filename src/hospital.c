#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"
#include "parse.h"
#include "structure.h"
#include "test.h"
#include "structure_test.h"
void unitTests() {
	testCutFirstWord();
	testLoadArgumentsOfNewDiseaseEnter();
	newDiseaseEnterDescriptionTest();
	newDiseaseCopyDescriptionTest();
	changeDescriptionTest();
	deletePatientDataTest();
}
int main(int argc,char** argv) {
	if (argc > 2 || (argc == 2 && strcmp(argv[1],"-v") != 0 )) {
				printf("%s","ERROR");
				return 1;
	}
	constructor();
	while(1) {
		InputStruct* inputStruct = loadInputToInputStruct();
		if (inputStruct == NULL) {
			destructor();
			return EXIT_SUCCESS;
		}
		modifyPatientData(inputStruct);

		if (argc == 2 && strcmp(argv[1],"-v") == 0)
			PrintNumberOfDescriptions();

		free(inputStruct);
	}
	destructor();
	return EXIT_SUCCESS;
}
