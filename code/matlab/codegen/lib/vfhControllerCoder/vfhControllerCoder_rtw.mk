###########################################################################
## Makefile generated for component 'vfhControllerCoder'. 
## 
## Makefile     : vfhControllerCoder_rtw.mk
## Generated on : Mon Sep 05 17:56:24 2022
## Final product: .\vfhControllerCoder.lib
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPILER_COMMAND_FILE   Compiler command listing model reference header paths
# CMD_FILE                Command file
# MODELLIB                Static library target

PRODUCT_NAME              = vfhControllerCoder
MAKEFILE                  = vfhControllerCoder_rtw.mk
MATLAB_ROOT               = C:\PROGRA~1\MATLAB\R2022a
MATLAB_BIN                = C:\PROGRA~1\MATLAB\R2022a\bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)\win64
START_DIR                 = C:\Users\Jakob\code\autonomous-wheelchair-thesis\code\matlab
TGT_FCN_LIB               = ISO_C++11
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 
RELATIVE_PATH_TO_ANCHOR   = ..\..\..
COMPILER_COMMAND_FILE     = vfhControllerCoder_rtw_comp.rsp
CMD_FILE                  = vfhControllerCoder_rtw.rsp
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 
NODEBUG                   = 1
MODELLIB                  = vfhControllerCoder.lib

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Microsoft Visual C++ 2022 v17.0 | nmake (64-bit Windows)
# Supported Version(s):    17.0
# ToolchainInfo Version:   2022a
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# NODEBUG
# cvarsdll
# cvarsmt
# conlibsmt
# ldebug
# conflags
# cflags

#-----------
# MACROS
#-----------

MW_EXTERNLIB_DIR    = $(MATLAB_ROOT)\extern\lib\win64\microsoft
MW_LIB_DIR          = $(MATLAB_ROOT)\lib\win64
CPU                 = AMD64
APPVER              = 5.02
CVARSFLAG           = $(cvarsmt)
CFLAGS_ADDITIONAL   = -D_CRT_SECURE_NO_WARNINGS
CPPFLAGS_ADDITIONAL = -EHs -D_CRT_SECURE_NO_WARNINGS /wd4251 /Zc:__cplusplus
LIBS_TOOLCHAIN      = $(conlibs)

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Microsoft Visual C Compiler
CC = cl

# Linker: Microsoft Visual C Linker
LD = link

# C++ Compiler: Microsoft Visual C++ Compiler
CPP = cl

# C++ Linker: Microsoft Visual C++ Linker
CPP_LD = link

# Archiver: Microsoft Visual C/C++ Archiver
AR = lib

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)\mex"

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: NMAKE Utility
MAKE = nmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -Zi
C_OUTPUT_FLAG       = -Fo
LDDEBUG             = /DEBUG
OUTPUT_FLAG         = -out:
CPPDEBUG            = -Zi
CPP_OUTPUT_FLAG     = -Fo
CPPLDDEBUG          = /DEBUG
OUTPUT_FLAG         = -out:
ARDEBUG             =
STATICLIB_OUTPUT_FLAG = -out:
MEX_DEBUG           = -g
RM                  = @del
ECHO                = @echo
MV                  = @ren
RUN                 = @cmd /C

#--------------------------------------
# "Faster Runs" Build Configuration
#--------------------------------------

ARFLAGS              = /nologo
CFLAGS               = $(cflags) $(CVARSFLAG) $(CFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPPFLAGS             = /TP $(cflags) $(CVARSFLAG) $(CPPFLAGS_ADDITIONAL) \
                       /O2 /Oy-
CPP_LDFLAGS          = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
CPP_SHAREDLIB_LDFLAGS  = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                         -dll -def:$(DEF_FILE)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN)
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = $(ldebug) $(conflags) $(LIBS_TOOLCHAIN) \
                       -dll -def:$(DEF_FILE)



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = .\vfhControllerCoder.lib
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = 

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_CUSTOM = 
DEFINES_STANDARD = -DMODEL=vfhControllerCoder

DEFINES = $(DEFINES_CUSTOM) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_data.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\rt_nonfinite.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\rtGetNaN.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\rtGetInf.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_initialize.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_terminate.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\minOrMax.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\raycast.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\raycastInternal.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\eps.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\bsxfun.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\randn.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\mod.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\angdiff.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\cross.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar_stateful.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\intersectLines.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\wrapToPi.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\unsafeSxfun.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\linePosition.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\VectorFieldHistogramBase.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\eml_mtimes_helper.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\div.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\wrapTo2Pi.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\nullAssignment.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\lidarScan.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\controllerVFH.cpp $(START_DIR)\codegen\lib\vfhControllerCoder\RangeSensorBase.cpp

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = vfhControllerCoder_data.obj rt_nonfinite.obj rtGetNaN.obj rtGetInf.obj vfhControllerCoder_initialize.obj vfhControllerCoder_terminate.obj vfhControllerCoder.obj minOrMax.obj raycast.obj raycastInternal.obj eps.obj bsxfun.obj randn.obj mod.obj angdiff.obj cross.obj eml_rand_mt19937ar_stateful.obj intersectLines.obj eml_rand_mt19937ar.obj wrapToPi.obj unsafeSxfun.obj linePosition.obj VectorFieldHistogramBase.obj eml_mtimes_helper.obj div.obj wrapTo2Pi.obj nullAssignment.obj lidarScan.obj controllerVFH.obj RangeSensorBase.obj

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_ = /source-charset:utf-8
CFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CFLAGS = $(CFLAGS) $(CFLAGS_) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_ = /source-charset:utf-8
CPPFLAGS_BASIC = $(DEFINES) @$(COMPILER_COMMAND_FILE)

CPPFLAGS = $(CPPFLAGS) $(CPPFLAGS_) $(CPPFLAGS_BASIC)

###########################################################################
## INLINED COMMANDS
###########################################################################


!include $(MATLAB_ROOT)\rtw\c\tools\vcdefs.mak


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute set_environment_variables


all : build
	@cmd /C "@echo ### Successfully generated all binary outputs."


build : set_environment_variables prebuild $(PRODUCT)


prebuild : 


download : $(PRODUCT)


execute : download


set_environment_variables : 
	@set INCLUDE=$(INCLUDES);$(INCLUDE)
	@set LIB=$(LIB)


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@cmd /C "@echo ### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS) -out:$(PRODUCT) @$(CMD_FILE)
	@cmd /C "@echo ### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(RELATIVE_PATH_TO_ANCHOR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\vfhControllerCoder}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)\codegen\lib\vfhControllerCoder}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.c.obj :
	$(CC) $(CFLAGS) -Fo"$@" "$<"


{$(START_DIR)}.cpp.obj :
	$(CPP) $(CPPFLAGS) -Fo"$@" "$<"


vfhControllerCoder_data.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_data.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_data.cpp"


rt_nonfinite.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\rt_nonfinite.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\rt_nonfinite.cpp"


rtGetNaN.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\rtGetNaN.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\rtGetNaN.cpp"


rtGetInf.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\rtGetInf.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\rtGetInf.cpp"


vfhControllerCoder_initialize.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_initialize.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_initialize.cpp"


vfhControllerCoder_terminate.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_terminate.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder_terminate.cpp"


vfhControllerCoder.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\vfhControllerCoder.cpp"


minOrMax.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\minOrMax.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\minOrMax.cpp"


raycast.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\raycast.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\raycast.cpp"


raycastInternal.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\raycastInternal.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\raycastInternal.cpp"


eps.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\eps.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\eps.cpp"


bsxfun.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\bsxfun.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\bsxfun.cpp"


randn.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\randn.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\randn.cpp"


mod.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\mod.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\mod.cpp"


angdiff.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\angdiff.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\angdiff.cpp"


cross.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\cross.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\cross.cpp"


eml_rand_mt19937ar_stateful.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar_stateful.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar_stateful.cpp"


intersectLines.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\intersectLines.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\intersectLines.cpp"


eml_rand_mt19937ar.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_rand_mt19937ar.cpp"


wrapToPi.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\wrapToPi.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\wrapToPi.cpp"


unsafeSxfun.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\unsafeSxfun.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\unsafeSxfun.cpp"


linePosition.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\linePosition.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\linePosition.cpp"


VectorFieldHistogramBase.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\VectorFieldHistogramBase.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\VectorFieldHistogramBase.cpp"


eml_mtimes_helper.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_mtimes_helper.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\eml_mtimes_helper.cpp"


div.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\div.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\div.cpp"


wrapTo2Pi.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\wrapTo2Pi.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\wrapTo2Pi.cpp"


nullAssignment.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\nullAssignment.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\nullAssignment.cpp"


lidarScan.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\lidarScan.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\lidarScan.cpp"


controllerVFH.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\controllerVFH.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\controllerVFH.cpp"


RangeSensorBase.obj : "$(START_DIR)\codegen\lib\vfhControllerCoder\RangeSensorBase.cpp"
	$(CPP) $(CPPFLAGS) -Fo"$@" "$(START_DIR)\codegen\lib\vfhControllerCoder\RangeSensorBase.cpp"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(COMPILER_COMMAND_FILE) $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@cmd /C "@echo ### PRODUCT = $(PRODUCT)"
	@cmd /C "@echo ### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@cmd /C "@echo ### BUILD_TYPE = $(BUILD_TYPE)"
	@cmd /C "@echo ### INCLUDES = $(INCLUDES)"
	@cmd /C "@echo ### DEFINES = $(DEFINES)"
	@cmd /C "@echo ### ALL_SRCS = $(ALL_SRCS)"
	@cmd /C "@echo ### ALL_OBJS = $(ALL_OBJS)"
	@cmd /C "@echo ### LIBS = $(LIBS)"
	@cmd /C "@echo ### MODELREF_LIBS = $(MODELREF_LIBS)"
	@cmd /C "@echo ### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@cmd /C "@echo ### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@cmd /C "@echo ### CFLAGS = $(CFLAGS)"
	@cmd /C "@echo ### LDFLAGS = $(LDFLAGS)"
	@cmd /C "@echo ### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### CPPFLAGS = $(CPPFLAGS)"
	@cmd /C "@echo ### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@cmd /C "@echo ### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@cmd /C "@echo ### ARFLAGS = $(ARFLAGS)"
	@cmd /C "@echo ### MEX_CFLAGS = $(MEX_CFLAGS)"
	@cmd /C "@echo ### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@cmd /C "@echo ### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@cmd /C "@echo ### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@cmd /C "@echo ### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@cmd /C "@echo ### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@cmd /C "@echo ### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	@if exist $(PRODUCT) $(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


