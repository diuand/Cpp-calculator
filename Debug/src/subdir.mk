################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calculations.cpp \
../src/Calculator.cpp \
../src/test2.cpp 

CPP_DEPS += \
./src/Calculations.d \
./src/Calculator.d \
./src/test2.d 

OBJS += \
./src/Calculations.o \
./src/Calculator.o \
./src/test2.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Calculations.d ./src/Calculations.o ./src/Calculator.d ./src/Calculator.o ./src/test2.d ./src/test2.o

.PHONY: clean-src

