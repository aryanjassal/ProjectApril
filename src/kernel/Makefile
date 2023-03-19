# The name of the module that we are currently compiling
MODULE := unnamed

# The directory where the source files are located (here)
MOD_SRC_DIR := $(CURDIR)

# The sub-directory where the compiled files will be stored (defaults to the module name)
OUT_SUB_DIR := $(MODULE)
MOD_OUT_DIR := $(OUT_DIR)/$(OUT_SUB_DIR)

# Compile a list of the C and assembly object files for this module
C_OBJ_FILES := $(patsubst $(MOD_SRC_DIR)%.c, $(MOD_OUT_DIR)%.o, $(realpath $(shell find -name "*.c")))
ASM_OBJ_FILES := $(patsubst $(MOD_SRC_DIR)%.asm, $(MOD_OUT_DIR)%.asmo, $(realpath $(shell find -name "*.asm")))

# Some command variables
ECHO := @echo
MKDIR := @mkdir -p

# Update the compiler flags by appending the include directory
CFLAGS += -I $(INC_DIR)/kernel

# The build recipie compiles all the source files into object files
build: $(C_OBJ_FILES) $(ASM_OBJ_FILES)
	$(ECHO) "Successfully compiled module [$(MODULE)]"

# Compile C source files
$(C_OBJ_FILES): $(MOD_OUT_DIR)%.o : $(MOD_SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# Compile assembly source files
$(ASM_OBJ_FILES): $(MOD_OUT_DIR)%.asmo : $(MOD_SRC_DIR)%.asm
	$(MKDIR) $(dir $@)
	$(ASMC) $(ASMFLAGS) $< -o $@