################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DLCarHUDUI.cpp \
../src/Guage.cpp \
../src/Guage_test.cpp \
../src/OBJParser.cpp \
../src/OBJParser_test.cpp \
../src/TerrainTile.cpp \
../src/x5car.cpp 

OBJS += \
./src/DLCarHUDUI.o \
./src/Guage.o \
./src/Guage_test.o \
./src/OBJParser.o \
./src/OBJParser_test.o \
./src/TerrainTile.o \
./src/x5car.o 

CPP_DEPS += \
./src/DLCarHUDUI.d \
./src/Guage.d \
./src/Guage_test.d \
./src/OBJParser.d \
./src/OBJParser_test.d \
./src/TerrainTile.d \
./src/x5car.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/freetype2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


