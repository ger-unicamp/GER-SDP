################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/CameraController.c \
../Sources/Events.c \
../Sources/SerialCommunication.c \
../Sources/main.c 

OBJS += \
./Sources/CameraController.o \
./Sources/Events.o \
./Sources/SerialCommunication.o \
./Sources/main.o 

C_DEPS += \
./Sources/CameraController.d \
./Sources/Events.d \
./Sources/SerialCommunication.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/marcelo/Documentos/GER/SDP/Projeto/SDP_2016/Static_Code/PDD" -I"/home/marcelo/Documentos/GER/SDP/Projeto/SDP_2016/Static_Code/IO_Map" -I"/home/marcelo/Documentos/GER/SDP/Projeto/SDP_2016/Sources" -I"/home/marcelo/Documentos/GER/SDP/Projeto/SDP_2016/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


