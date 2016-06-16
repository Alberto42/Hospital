#!/bin/bash
N="20";

if [[ "$1" == "-v" ]]; then
	directory=$3;
	prog=$2;
	flag="-v"
	isV="true"
else
	directory=$2;
	prog=$1;
	flag=""
	isV="false"
fi
for((i=1;i<= $N;++i)); do
	touch progOutError
	touch progOut

	progOutErrorTest="0"
	./$prog $flag < $directory/test$i.in > progOut 2> /dev/null  
	diff progOut $directory/test$i.out > /dev/null
	progOutTest=$?

	if [[ $isV == "true" ]]; then
	./$prog $flag < $directory/test$i.in 2> progOutError > /dev/null
	diff progOutError $directory/test$i.err > /dev/null
	progOutErrorTest=$?
	fi
		
	if [[ $progOutTest != "0" ]]; then
		echo -e "test $i - FAIL stdout"	
		elif [[ $progOutErrorTest != "0" ]]; then
			echo -e "test $i - FAIL stderr"
	else 
		echo -e "test $i - OK"	
	fi

	rm progOut
	rm progOutError
done
