################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/driver/adc.c" \
"../Sources/driver/can.c" \

C_SRCS += \
../Sources/driver/adc.c \
../Sources/driver/can.c \

OBJS += \
./Sources/driver/adc.o \
./Sources/driver/can.o \

OBJS_QUOTED += \
"./Sources/driver/adc.o" \
"./Sources/driver/can.o" \

C_DEPS += \
./Sources/driver/adc.d \
./Sources/driver/can.d \

OBJS_OS_FORMAT += \
./Sources/driver/adc.o \
./Sources/driver/can.o \

C_DEPS_QUOTED += \
"./Sources/driver/adc.d" \
"./Sources/driver/can.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/driver/adc.o: ../Sources/driver/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #46 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/adc.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/driver/can.o: ../Sources/driver/can.c
	@echo 'Building file: $<'
	@echo 'Executing target #47 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/driver/can.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/driver/can.o"
	@echo 'Finished building: $<'
	@echo ' '


