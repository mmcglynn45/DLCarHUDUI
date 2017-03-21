################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AerialMap.cpp \
../src/AerialTile.cpp \
../src/DLCarHUDUI.cpp \
../src/DataController.cpp \
../src/Guage.cpp \
../src/Guage_test.cpp \
../src/LandingPage.cpp \
../src/MappingPage.cpp \
../src/OBJParser.cpp \
../src/OBJParser_test.cpp \
../src/PageHeader.cpp \
../src/TerrainTile.cpp \
../src/x5car.cpp 

OBJS += \
./src/AerialMap.o \
./src/AerialTile.o \
./src/DLCarHUDUI.o \
./src/DataController.o \
./src/Guage.o \
./src/Guage_test.o \
./src/LandingPage.o \
./src/MappingPage.o \
./src/OBJParser.o \
./src/OBJParser_test.o \
./src/PageHeader.o \
./src/TerrainTile.o \
./src/x5car.o 

CPP_DEPS += \
./src/AerialMap.d \
./src/AerialTile.d \
./src/DLCarHUDUI.d \
./src/DataController.d \
./src/Guage.d \
./src/Guage_test.d \
./src/LandingPage.d \
./src/MappingPage.d \
./src/OBJParser.d \
./src/OBJParser_test.d \
./src/PageHeader.d \
./src/TerrainTile.d \
./src/x5car.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/usr/include/freetype2 -O0 -g3 -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


