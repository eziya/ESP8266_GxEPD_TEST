################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
..\sloeber.ino.cpp 

LINK_OBJ += \
.\sloeber.ino.cpp.o 

CPP_DEPS += \
.\sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
sloeber.ino.cpp.o: ..\sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"D:\sloeber\arduinoPlugin\packages\esp8266\tools\xtensa-lx106-elf-gcc\1.20.0-26-gb404fb9-2/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ "-ID:\sloeber\/arduinoPlugin/packages/esp8266/hardware/esp8266/2.4.2/tools/sdk/include" "-ID:\sloeber\/arduinoPlugin/packages/esp8266/hardware/esp8266/2.4.2/tools/sdk/lwip2/include" "-ID:\sloeber\/arduinoPlugin/packages/esp8266/hardware/esp8266/2.4.2/tools/sdk/libc/xtensa-lx106-elf/include" "-ID:/Workspace/Arduino/ESP8266_GxEPD_TEST/Release/core" -c -Wall -Wextra  -Os -g -mlongcalls -mtext-section-literals -fno-exceptions -fno-rtti -falign-functions=4 -std=c++11 -MMD -ffunction-sections -fdata-sections -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536   -DARDUINO=10802 -DARDUINO_ESP8266_NODEMCU -DARDUINO_ARCH_ESP8266 -DARDUINO_BOARD="\"ESP8266_NODEMCU\""   -DESP8266   -I"D:\sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\2.4.2\cores\esp8266" -I"D:\sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\2.4.2\variants\nodemcu" -I"D:\sloeber\arduinoPlugin\libraries\Adafruit_GFX_Library\1.2.9" -I"C:\Users\kiki\Documents\Arduino\libraries\GxEPD-master\src" -I"D:\sloeber\arduinoPlugin\packages\esp8266\hardware\esp8266\2.4.2\libraries\SPI" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"

	@echo 'Finished building: $<'
	@echo ' '


