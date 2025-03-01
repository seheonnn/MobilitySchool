################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"../Modules/FNDSPI/FNDSPI.c" 

COMPILED_SRCS += \
"Modules/FNDSPI/FNDSPI.src" 

C_DEPS += \
"./Modules/FNDSPI/FNDSPI.d" 

OBJS += \
"Modules/FNDSPI/FNDSPI.o" 


# Each subdirectory must supply rules for building sources it contributes
"Modules/FNDSPI/FNDSPI.src":"../Modules/FNDSPI/FNDSPI.c" "Modules/FNDSPI/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld2/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"Modules/FNDSPI/FNDSPI.o":"Modules/FNDSPI/FNDSPI.src" "Modules/FNDSPI/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-Modules-2f-FNDSPI

clean-Modules-2f-FNDSPI:
	-$(RM) ./Modules/FNDSPI/FNDSPI.d ./Modules/FNDSPI/FNDSPI.o ./Modules/FNDSPI/FNDSPI.src

.PHONY: clean-Modules-2f-FNDSPI

