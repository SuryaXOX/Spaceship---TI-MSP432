################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
lcd.obj: C:/Users/13478/Desktop/ece353/ICE_11/lcd.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --include_path="C:/Users/13478/Desktop/ece353/codeFreeRTOS/FreeRTOSv202012.00/FreeRTOSv202012.00/FreeRTOS/Source/include" --include_path="C:/Users/13478/Desktop/ece353/codeFreeRTOS/FreeRTOSv202012.00/FreeRTOSv202012.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Homework 4" --include_path="C:/Users/13478/Desktop/ece353/ICE_11" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Homework 4/HW4" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="lcd.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include" --include_path="C:/Users/13478/Desktop/ece353/ccs/ccs_base/arm/include/CMSIS" --include_path="C:/Users/13478/Desktop/ece353/ccs/tools/compiler/ti-cgt-arm_20.2.4.LTS/include" --include_path="C:/Users/13478/Desktop/ece353/codeFreeRTOS/FreeRTOSv202012.00/FreeRTOSv202012.00/FreeRTOS/Source/include" --include_path="C:/Users/13478/Desktop/ece353/codeFreeRTOS/FreeRTOSv202012.00/FreeRTOSv202012.00/FreeRTOS/Source/portable/CCS/ARM_CM4F" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Homework 4" --include_path="C:/Users/13478/Desktop/ece353/ICE_11" --include_path="C:/Users/13478/Desktop/ece353/Free-RTOS/Homework 4/HW4" --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


