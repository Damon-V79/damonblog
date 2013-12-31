project_name   := pwm_dma
source_dirs    := common/scmRTOS/Common common/scmRTOS/CortexM3 common/scmRTOS/SamplesCommon src/$(project_name)
compile_flags  := 
link_flags     := 
toolchain_path := /home/damon/ProgramFiles/cortex-toolchain/bin/
include_path   := common common/scmRTOS/Common common/scmRTOS/CortexM3 common/SamplesCommon 
local_inc_path := src/$(project_name) 
libraryes      := opencm3_stm32f4 gcc stdc++ c nosys
library_path   := 
LDSCRIPT       := lib/ldscripts/stm32f4-discovery.ld
cpp_compiler   := arm-none-eabi-g++
c_compiler     := arm-none-eabi-gcc
assembler      := arm-none-eabi-gcc -x assembler-with-cpp
linker         := arm-none-eabi-gcc
size           := arm-none-eabi-size
ragel_compiler := ragel
cuda_compiler  := nvcc

CCC  := $(toolchain_path)$(c_compiler)
CPP  := $(toolchain_path)$(cpp_compiler)
ASM  := $(toolchain_path)$(assembler)
LD   := $(toolchain_path)$(linker)
SIZE := $(toolchain_path)$(size)
NVCC := $(cuda_compiler)
RL   := $(ragel_compiler)

ECHO := echo

 GENDEPFLAGS = -Wp,-MM,-MP,-MT,$@,-MF,$(@:.o=.d)
 ASMFLAGS    += -Os -g -Wall -Wextra  -I$(toolchain_path)include -I./$(local_inc_path) \
                   -fno-common -mcpu=cortex-m4 -mthumb -msoft-float -MD -DSTM32F4
 CFLAGS  += $(ASMFLAGS) $(GENDEPFLAGS)
 CPPFLAGS  += $(CFLAGS) -std=gnu++0x
 LDFLAGS   += $(link_flags) -Os -Wl,--start-group -Wl,--end-group \
                   -L$(toolchain_path)lib -L$(toolchain_path)lib/stm32/f4 \
                   -T$(LDSCRIPT) -Wl,--gc-sections \
                   -mthumb -march=armv7 -msoft-float
 CUDAFLAGS += --compiler-options -fno-strict-aliasing -DUNIX -O3 
 RLFLAGS   += -G2 

# GENDEPFLAGS = -Wp,-MM,-MP,-MT,$@,-MF,$(@:.o=.d)
# CFLAGS    += -O3 -march=i586 $(GENDEPFLAGS)
# CPPFLAGS  += -O3 -march=i586 $(GENDEPFLAGS) -std=gnu++0x
# ASMFLAGS  += -O3 -march=i586 $(GENDEPFLAGS)
# LDFLAGS   += -O3 -march=i586 -static
# CUDAFLAGS += --compiler-options -fno-strict-aliasing -DUNIX -O3 
# RLFLAGS   += -G2 

libraryes    := $(addprefix -l,$(libraryes))
library_path := $(addprefix -L,$(library_path))

include_path := $(addprefix -I,$(include_path))

