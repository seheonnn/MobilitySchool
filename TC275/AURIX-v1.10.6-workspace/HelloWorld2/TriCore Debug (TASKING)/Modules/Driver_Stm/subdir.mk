################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Modules/Driver_Stm/Driver_Stm.c" 

COMPILED_SRCS += \
"Modules/Driver_Stm/Driver_Stm.src" 

C_DEPS += \
"./Modules/Driver_Stm/Driver_Stm.d" 

OBJS += \
"Modules/Driver_Stm/Driver_Stm.o" 


# Each subdirectory must supply rules for building sources it contributes
"Modules/Driver_Stm/Driver_Stm.src":"../Modules/Driver_Stm/Driver_Stm.c" "Modules/Driver_Stm/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Modules/Driver_Stm/Driver_Stm.o":"Modules/Driver_Stm/Driver_Stm.src" "Modules/Driver_Stm/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules-2f-Driver_Stm

clean-Modules-2f-Driver_Stm:
	-$(RM) ./Modules/Driver_Stm/Driver_Stm.d ./Modules/Driver_Stm/Driver_Stm.o ./Modules/Driver_Stm/Driver_Stm.src

.PHONY: clean-Modules-2f-Driver_Stm

