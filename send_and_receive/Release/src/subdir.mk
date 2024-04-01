################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/buttons.c \
../src/can.c \
../src/commands.c \
../src/configuration.c \
../src/conversion.c \
../src/data.c \
../src/gpio.c \
../src/i2c_access.c \
../src/iic_phyreset.c \
../src/main.c \
../src/pcb2.c \
../src/platform.c \
../src/platform_mb.c \
../src/platform_ppc.c \
../src/platform_zynq.c \
../src/platform_zynqmp.c \
../src/sfp.c \
../src/si5324.c \
../src/tcp.c \
../src/udp.c 

OBJS += \
./src/buttons.o \
./src/can.o \
./src/commands.o \
./src/configuration.o \
./src/conversion.o \
./src/data.o \
./src/gpio.o \
./src/i2c_access.o \
./src/iic_phyreset.o \
./src/main.o \
./src/pcb2.o \
./src/platform.o \
./src/platform_mb.o \
./src/platform_ppc.o \
./src/platform_zynq.o \
./src/platform_zynqmp.o \
./src/sfp.o \
./src/si5324.o \
./src/tcp.o \
./src/udp.o 

C_DEPS += \
./src/buttons.d \
./src/can.d \
./src/commands.d \
./src/configuration.d \
./src/conversion.d \
./src/data.d \
./src/gpio.d \
./src/i2c_access.d \
./src/iic_phyreset.d \
./src/main.d \
./src/pcb2.d \
./src/platform.d \
./src/platform_mb.d \
./src/platform_ppc.d \
./src/platform_zynq.d \
./src/platform_zynqmp.d \
./src/sfp.d \
./src/si5324.d \
./src/tcp.d \
./src/udp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O2 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/home/silvermight/zturn_real_gpio/zturn_real_gpio.sdk/wanda_gpio_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


