
PROJ_NAME 		:= uart_driver
PROJ_DIR 		:= .
PATH_OUTPUT		:= $(PROJ_DIR)/Output

INC_DIR 		:= $(PROJ_DIR)/Core/Inc
INC_DIR 		+= $(PROJ_DIR)/Driver/Inc

SRC_DIR 		:= $(PROJ_DIR)/Core/Src
SRC_DIR 		+= $(PROJ_DIR)/Driver/Src

INC_FILES		:= $(foreach inc_dir, $(INC_DIR), $(wildcard $(inc_dir)/*))
SRC_FILES		:= $(foreach src_dir, $(SRC_DIR), $(wildcard $(src_dir)/*.c))

LINKER_FILE		:= $(PROJ_DIR)/Linker/gcc_arm.ld

COMPILER_DIR	:= D:/Embedded/Embedded_SW/gcc-arm-none-eabi-10.3-2021.10
PREFIX_COMPILER	:= arm-none-eabi

CC				:= $(COMPILER_DIR)/bin/$(PREFIX_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_COMPILER)-ld
SZ 				:= $(COMPILER_DIR)/bin/$(PREFIX_COMPILER)-size

INC_DIRS_OPT	:=  $(foreach inc_dir, $(INC_DIR), -I$(inc_dir))

CC_OPT			:= -mcpu=cortex-m4 -c -O0 -g -std=gnu11 -mthumb $(INC_DIRS_OPT) 
ASM_OPT			:= -mcpu=cortex-m4 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(PATH_OUTPUT)/$(PROJ_NAME).map

OBJ_FILES		:= $(notdir $(SRC_FILES))
OBJ_FILES		:= $(subst .c,.o,$(OBJ_FILES))

PATH_OBJS		:= $(foreach obj_file, $(OBJ_FILES), $(PATH_OUTPUT)/$(obj_file))

vpath %.c $(SRC_DIR)
vpath %.h $(INC_DIR)

build: $(OBJ_FILES) $(LINKER_FILE) $(PATH_OUTPUT)/startup_ARMCM4.o
	@echo "....Linking...."
	$(LD) $(LD_OPT) $(PATH_OBJS) $(PATH_OUTPUT)/startup_ARMCM4.o -o $(PATH_OUTPUT)/$(PROJ_NAME).elf
	@$(SZ) $(PATH_OUTPUT)/$(PROJ_NAME).elf
	@echo                      BUILD SUCCESSFULLY                           

%.o : %.c $(INC_FILES)
	@echo "build $< to $@"
	$(CC) $(CC_OPT) $< -o $(PATH_OUTPUT)/$@
	
$(PATH_OUTPUT)/startup_ARMCM4.o : $(PROJ_DIR)/Core/Src/startup_ARMCM4.S
	$(ASM) $(ASM_OPT) $(PROJ_DIR)/Core/Src/startup_ARMCM4.S -o $(PATH_OUTPUT)/startup_ARMCM4.o
	
clean: 
	del /q /f /s Output\*