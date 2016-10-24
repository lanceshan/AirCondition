################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/user/commprotocol.c" \
"../Sources/user/error.c" \
"../Sources/user/getSysInfo.c" \
"../Sources/user/globalvars.c" \
"../Sources/user/mode.c" \

C_SRCS += \
../Sources/user/commprotocol.c \
../Sources/user/error.c \
../Sources/user/getSysInfo.c \
../Sources/user/globalvars.c \
../Sources/user/mode.c \

OBJS += \
./Sources/user/commprotocol.o \
./Sources/user/error.o \
./Sources/user/getSysInfo.o \
./Sources/user/globalvars.o \
./Sources/user/mode.o \

OBJS_QUOTED += \
"./Sources/user/commprotocol.o" \
"./Sources/user/error.o" \
"./Sources/user/getSysInfo.o" \
"./Sources/user/globalvars.o" \
"./Sources/user/mode.o" \

C_DEPS += \
./Sources/user/commprotocol.d \
./Sources/user/error.d \
./Sources/user/getSysInfo.d \
./Sources/user/globalvars.d \
./Sources/user/mode.d \

OBJS_OS_FORMAT += \
./Sources/user/commprotocol.o \
./Sources/user/error.o \
./Sources/user/getSysInfo.o \
./Sources/user/globalvars.o \
./Sources/user/mode.o \

C_DEPS_QUOTED += \
"./Sources/user/commprotocol.d" \
"./Sources/user/error.d" \
"./Sources/user/getSysInfo.d" \
"./Sources/user/globalvars.d" \
"./Sources/user/mode.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/user/commprotocol.o: ../Sources/user/commprotocol.c
	@echo 'Building file: $<'
	@echo 'Executing target #39 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/commprotocol.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/commprotocol.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/error.o: ../Sources/user/error.c
	@echo 'Building file: $<'
	@echo 'Executing target #40 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/error.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/error.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/getSysInfo.o: ../Sources/user/getSysInfo.c
	@echo 'Building file: $<'
	@echo 'Executing target #41 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/getSysInfo.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/getSysInfo.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/globalvars.o: ../Sources/user/globalvars.c
	@echo 'Building file: $<'
	@echo 'Executing target #42 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/globalvars.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/globalvars.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user/mode.o: ../Sources/user/mode.c
	@echo 'Building file: $<'
	@echo 'Executing target #43 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user/mode.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user/mode.o"
	@echo 'Finished building: $<'
	@echo ' '


