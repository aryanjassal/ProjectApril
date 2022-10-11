# The name of the module that we are currently compiling
MODULE := unnamed

# The directory where the source files are located (here)
MOD_SRC_DIR := $(CURDIR)

# The sub-directory where the compiled files will be stored (defaulted to the module name)
OUT_SUB_DIR := $(MODULE)
MOD_OUT_DIR := $(OUT_DIR)/$(OUT_SUB_DIR)

# Some command variables
ECHO := @echo
MKDIR := @mkdir -p

# The build recipie compiles all the source files into object files
build:
	$(MKDIR) $(MOD_OUT_DIR)
	$(ASMC) -o $(MOD_OUT_DIR)/stage_one.bin -f bin $(MOD_SRC_DIR)/stage_one.asm
	$(ASMC) $(ASMFLAGS) -o $(MOD_OUT_DIR)/stage_two.asmo $(MOD_SRC_DIR)/stage_two.asm

	$(ECHO) "Successfully compiled module [$(MODULE)]"