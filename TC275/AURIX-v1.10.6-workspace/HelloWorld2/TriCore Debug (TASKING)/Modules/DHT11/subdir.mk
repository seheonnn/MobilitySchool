################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Modules/DHT11/DHT11.c" \
"../Modules/DHT11/dht11_driver.c" 

COMPILED_SRCS += \
"Modules/DHT11/DHT11.src" \
"Modules/DHT11/dht11_driver.src" 

C_DEPS += \
"./Modules/DHT11/DHT11.d" \
"./Modules/DHT11/dht11_driver.d" 

OBJS += \
"Modules/DHT11/DHT11.o" \
"Modules/DHT11/dht11_driver.o" 


# Each subdirectory must supply rules for building sources it contributes
"Modules/DHT11/DHT11.src":"../Modules/DHT11/DHT11.c" "Modules/DHT11/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Modules/DHT11/DHT11.o":"Modules/DHT11/DHT11.src" "Modules/DHT11/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"Modules/DHT11/dht11_driver.src":"../Modules/DHT11/dht11_driver.c" "Modules/DHT11/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Modules/DHT11/dht11_driver.o":"Modules/DHT11/dht11_driver.src" "Modules/DHT11/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules-2f-DHT11

clean-Modules-2f-DHT11:
	-$(RM) ./Modules/DHT11/DHT11.d ./Modules/DHT11/DHT11.o ./Modules/DHT11/DHT11.src ./Modules/DHT11/dht11_driver.d ./Modules/DHT11/dht11_driver.o ./Modules/DHT11/dht11_driver.src

.PHONY: clean-Modules-2f-DHT11

