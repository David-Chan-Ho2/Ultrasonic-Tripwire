################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
GrLib/fonts/%.obj: ../GrLib/fonts/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ti/ccstheia151/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmsp -O3 --use_hw_mpy=none --include_path="/Applications/ti/ccstheia151/ccs/ccs_base/msp430/include" --include_path="/Users/empireamusement/workspace_ccstheia/lab4" --include_path="/Users/empireamusement/workspace_ccstheia/lab4/GrLib/grlib" --include_path="/Users/empireamusement/workspace_ccstheia/lab4/GrLib/fonts" --include_path="/Applications/ti/ccstheia151/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power="none" --define=__MSP430G2553__ -g --gcc --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="GrLib/fonts/$(basename $(<F)).d_raw" --obj_directory="GrLib/fonts" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


