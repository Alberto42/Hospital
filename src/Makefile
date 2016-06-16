flags = -Wall -O2
hospital : hospital.o parse.o structure.o test.o diseases.o structure_test.o
	gcc   $(flags)  hospital.o parse.o structure.o test.o diseases.o structure_test.o -o hospital
	
debug : hospital.o parse.o structure.o test.o diseases.o structure_test.o
	gcc   $(flags) -g  hospital.o parse.o structure.o test.o diseases.o structure_test.o -o hospital.dbg
	
hostpital.o: hospital.c hospital.h parse.h test.h structure_test.h
	gcc -c  hospital.c

structure.o : structure.c structure.h parse.h 
	gcc -c structure.c

parse.o : parse.c parse.h
	gcc -c parse.c

test.o : test.c parse.h test.h 
	gcc -c test.c

diseases.o : diseases.c diseases.h 
	gcc -c diseases.c

structure_test.o : structure_test.c structure_test.h 
	gcc -c structure_test.c
	
clear: 
	-rm *.o 
	-rm *.h.gch
	-rm hospital
	-rm hospital.dbg

