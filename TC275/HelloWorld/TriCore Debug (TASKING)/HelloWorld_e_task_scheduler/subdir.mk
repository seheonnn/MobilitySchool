################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
"C:/Users/USER/Documents/카카오톡 받은 파일/HelloWorld_e_task_scheduler/Cpu0_Main.c" \
"C:/Users/USER/Documents/카카오톡 받은 파일/HelloWorld_e_task_scheduler/Driver_Stm.c" 

COMPILED_SRCS += \
"HelloWorld_e_task_scheduler/Cpu0_Main.src" \
"HelloWorld_e_task_scheduler/Driver_Stm.src" 

C_DEPS += \
"./HelloWorld_e_task_scheduler/Cpu0_Main.d" \
"./HelloWorld_e_task_scheduler/Driver_Stm.d" 

OBJS += \
"HelloWorld_e_task_scheduler/Cpu0_Main.o" \
"HelloWorld_e_task_scheduler/Driver_Stm.o" 


# Each subdirectory must supply rules for building sources it contributes
"HelloWorld_e_task_scheduler/Cpu0_Main.src":"C:/Users/USER/Documents/카카오톡 받은 파일/HelloWorld_e_task_scheduler/Cpu0_Main.c" "HelloWorld_e_task_scheduler/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"HelloWorld_e_task_scheduler/Cpu0_Main.o":"HelloWorld_e_task_scheduler/Cpu0_Main.src" "HelloWorld_e_task_scheduler/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
"HelloWorld_e_task_scheduler/Driver_Stm.src":"C:/Users/USER/Documents/카카오톡 받은 파일/HelloWorld_e_task_scheduler/Driver_Stm.c" "HelloWorld_e_task_scheduler/subdir.mk"
	cctc -cs --dep-file="$*.d" --misrac-version=2004 -D__CPU__=tc27xd "-fC:/Users/USER/AURIX-v1.10.6-workspace/HelloWorld/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<"
"HelloWorld_e_task_scheduler/Driver_Stm.o":"HelloWorld_e_task_scheduler/Driver_Stm.src" "HelloWorld_e_task_scheduler/subdir.mk"
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-HelloWorld_e_task_scheduler

clean-HelloWorld_e_task_scheduler:
	-$(RM) ./HelloWorld_e_task_scheduler/Cpu0_Main.d ./HelloWorld_e_task_scheduler/Cpu0_Main.o ./HelloWorld_e_task_scheduler/Cpu0_Main.src ./HelloWorld_e_task_scheduler/Driver_Stm.d ./HelloWorld_e_task_scheduler/Driver_Stm.o ./HelloWorld_e_task_scheduler/Driver_Stm.src

.PHONY: clean-HelloWorld_e_task_scheduler

