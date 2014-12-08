################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/node0.c \
../src/node1.c \
../src/node2.c \
../src/node3.c \
../src/project3.c 

OBJS += \
./src/node0.o \
./src/node1.o \
./src/node2.o \
./src/node3.o \
./src/project3.o 

C_DEPS += \
./src/node0.d \
./src/node1.d \
./src/node2.d \
./src/node3.d \
./src/project3.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


