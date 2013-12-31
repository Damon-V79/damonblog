
###################################
#
#        Makefile
#

target_project := $(word 1, $(MAKECMDGOALS))
what_todo      := $(word 2, $(MAKECMDGOALS))

make_dir     := $(CURDIR)
all_projects := $(patsubst %.mk, %, $(notdir $(wildcard $(make_dir)/src/*/*.mk)))

.SILENT:
.PHONY: $(target_project) build_rule

$(target_project): build_rule


define echo_usage
    echo "Usage: make cleanall | tests | <project name> [debug | clean]"
    echo "Projects is: $(all_projects)"
    echo
endef

ifeq ($(target_project),cleanall)
build_rule:
	echo Erasing working directories
	rm -rf $(make_dir)/.obj $(make_dir)/bin
else

ifeq ($(target_project),)
build_rule:
	echo "There is no project to build. Stop"
	echo
	$(echo_usage)
else

ifeq ($(target_project), tests)
    include tests/tests.mk
    all_projects += tests
else
    include src/$(target_project)/$(target_project).mk
endif

ifeq ($(findstring $(target_project),$(all_projects)),)
build_rule:
	echo There are no difinitions for project "'"$(target_project)"'". Stop.
	echo
	$(echo_usage)
else

ifeq ($(what_todo), clean)
build_rule:
	@$(ECHO) Erasing $(target_project) directories
	rm -rf $(make_dir)/.obj/$(target_project) $(make_dir)/bin/$(target_project)
else

ifeq ($(what_todo), debug)
    what_todo:=
    CFLAGS   += -D_DEBUG_
    CPPFLAGS += -D_DEBUG_
    ASMFLAGS += -D_DEBUG_
endif

INCDIRS := $(include_path)
LIBS    := $(library_path) $(libraryes)

project_outpath := $(make_dir)/bin
project_objpath := $(make_dir)/.obj/$(target_project)
project_asmpath := $(project_objpath)/asm
project_mappath := $(project_objpath)/map
project_tmppath := $(project_objpath)/tmp
project_lstpath := $(project_objpath)/lst
folders := $(project_outpath) $(project_objpath) $(project_tmppath) $(project_asmpath) $(project_mappath)

project_name := $(addprefix $(project_outpath)/,$(target_project))
object_files += $(notdir $(patsubst %.c,   %.o, $(wildcard $(addsuffix /*.c,   $(source_dirs)))))
object_files += $(notdir $(patsubst %.cpp, %.o, $(wildcard $(addsuffix /*.cpp, $(source_dirs)))))
object_files += $(notdir $(patsubst %.S,   %.o, $(wildcard $(addsuffix /*.S,   $(source_dirs)))))
object_files += $(notdir $(patsubst %.rl,  %.o, $(wildcard $(addsuffix /*.rl,  $(source_dirs)))))
object_files += $(notdir $(patsubst %.cu,  %.o, $(wildcard $(addsuffix /*.cu,  $(source_dirs)))))
object_files := $(addprefix $(project_objpath)/,$(object_files))

VPATH = $(source_dirs)

.PHONY: all build_rule, echo_build, echo_done

all: build_rule

build_rule: echo_build $(folders) $(project_name) echo_done

echo_build:
	@$(ECHO) building "'"$(target_project)"'" $(project_base)
	@$(ECHO) -------------------------------------------

echo_done:
	@$(ECHO) -------------------------------------------
	@$(ECHO) build ok!

$(folders):
	@$(ECHO) making directory $@
	mkdir -p $@

$(project_name): $(object_files)
	@$(ECHO) Link $(project_name)
	$(LD) $^ $(LIBS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(project_objpath)/%.o: %.c
	@$(ECHO) Compile $<
	$(CCC) -c $(CFLAGS) $(INCDIRS) \
	-Wall $< -o $@
	$(SIZE) $@

$(project_objpath)/%.o: %.cpp
	@$(ECHO) Compile $<
	$(CPP) -c $(CPPFLAGS) $(INCDIRS) \
	-Wall $< -o $@
	$(SIZE) $@

$(project_objpath)/%.o: %.S
	@$(ECHO) Compile $<
	$(ASM) -c $(ASMFLAGS) $(INCDIRS) \
	-Wall $< -o $@
	$(SIZE) $@

%.rl:

$(project_objpath)/%.o: %.rl
	@$(ECHO) Compile $<
	$(RL) $(RLFLAGS) $< -o $(project_objpath)/tmp/$(notdir $(patsubst %.rl, %.cpp, $<))
	$(CPP) -c $(CPPFLAGS) $(INCDIRS) \
	-Wall $(project_objpath)/tmp/$(notdir $(patsubst %.rl, %.cpp, $<)) -o $@

%.cu: 

$(project_objpath)/%.o: %.cu
	@$(ECHO) Compile $<
	$(NVCC) -c $(CUDAFLAGS) $(INCDIRS) $< -o $@

%.hpp:

ifeq (,$(findstring clean,$(what_todo)))
 ifeq (,$(findstring cleanall,$(what_todo)))
  ifeq (,$(findstring directories,$(what_todo)))
-include $(shell mkdir $(project_objpath) 2>/dev/null) $(wildcard $(project_objpath)/*.d)
  endif
 endif
endif

endif
endif
endif
endif
