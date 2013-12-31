project_name   := tests
source_dirs    := tests common common/FSM/States
compile_flags  := -pthread
link_flags     := -pthread
toolchain_path := 
include_path   := common src/serial_bson_test/settings 
libraryes      := stdc++ gtest_main gtest gmock_main gmock pthread
library_path   := 
cpp_compiler   := g++
c_compiler     := gcc
assembler      := gas
linker         := gcc
size           := size
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
 CFLAGS    += -g -O0 $(GENDEPFLAGS)
 CPPFLAGS  += -g -O0 $(GENDEPFLAGS) -std=gnu++0x
 ASMFLAGS  += -g -O0 $(GENDEPFLAGS)
 LDFLAGS   += -g -O0 
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

