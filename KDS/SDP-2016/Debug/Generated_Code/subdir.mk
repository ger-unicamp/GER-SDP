################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/CLK.c \
../Generated_Code/ClockInterruption.c \
../Generated_Code/Cpu.c \
../Generated_Code/Enable_Motors.c \
../Generated_Code/ImageConverter.c \
../Generated_Code/Motor_A_In_1.c \
../Generated_Code/Motor_A_In_2.c \
../Generated_Code/Motor_B_In1.c \
../Generated_Code/Motor_B_In2.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/PwmLdd2.c \
../Generated_Code/PwmLdd3.c \
../Generated_Code/PwmLdd4.c \
../Generated_Code/PwmLdd5.c \
../Generated_Code/SI.c \
../Generated_Code/SerialCom.c \
../Generated_Code/Servomotor.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TU3.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/CLK.o \
./Generated_Code/ClockInterruption.o \
./Generated_Code/Cpu.o \
./Generated_Code/Enable_Motors.o \
./Generated_Code/ImageConverter.o \
./Generated_Code/Motor_A_In_1.o \
./Generated_Code/Motor_A_In_2.o \
./Generated_Code/Motor_B_In1.o \
./Generated_Code/Motor_B_In2.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/PwmLdd2.o \
./Generated_Code/PwmLdd3.o \
./Generated_Code/PwmLdd4.o \
./Generated_Code/PwmLdd5.o \
./Generated_Code/SI.o \
./Generated_Code/SerialCom.o \
./Generated_Code/Servomotor.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TU3.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/CLK.d \
./Generated_Code/ClockInterruption.d \
./Generated_Code/Cpu.d \
./Generated_Code/Enable_Motors.d \
./Generated_Code/ImageConverter.d \
./Generated_Code/Motor_A_In_1.d \
./Generated_Code/Motor_A_In_2.d \
./Generated_Code/Motor_B_In1.d \
./Generated_Code/Motor_B_In2.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/PwmLdd2.d \
./Generated_Code/PwmLdd3.d \
./Generated_Code/PwmLdd4.d \
./Generated_Code/PwmLdd5.d \
./Generated_Code/SI.d \
./Generated_Code/SerialCom.d \
./Generated_Code/Servomotor.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TU3.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/marcelo/Documentos/GER/SDP/SDP-2016/KDS/SDP-2016/Static_Code/PDD" -I"/home/marcelo/Documentos/GER/SDP/SDP-2016/KDS/SDP-2016/Static_Code/IO_Map" -I"/home/marcelo/Documentos/GER/SDP/SDP-2016/KDS/SDP-2016/Sources" -I"/home/marcelo/Documentos/GER/SDP/SDP-2016/KDS/SDP-2016/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


