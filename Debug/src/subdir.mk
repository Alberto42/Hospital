################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/diseases.c \
../src/hospital.c \
../src/parse.c \
../src/structure.c \
../src/structure_test.c \
../src/test.c 

OBJS += \
./src/diseases.o \
./src/hospital.o \
./src/parse.o \
./src/structure.o \
./src/structure_test.o \
./src/test.o 

C_DEPS += \
./src/diseases.d \
./src/hospital.d \
./src/parse.d \
./src/structure.d \
./src/structure_test.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


