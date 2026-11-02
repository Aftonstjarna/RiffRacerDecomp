CXX ?= c++
OUT ?= ../../build/source-first-render
REFERENCE_DIR ?= ../native
# Fixed flags describe the tested GCC/i386 environment, not the original MSVC build.
FLAGS := -std=c++17 -m32 -O0 -Wall -Wextra -Werror -ffreestanding -fno-exceptions -fno-rtti -fno-pie -fno-stack-protector -fno-tree-vectorize -fno-tree-loop-distribute-patterns -fno-fast-math -ffp-contract=off -msse2 -mfpmath=sse -ffunction-sections
REFS := ui_matrix_scale shader_base_ctor shader_binding_cleanup
REF_OBJECTS := $(addprefix $(OUT)/reference_,$(addsuffix .o,$(REFS)))
REF_BINS := $(REF_OBJECTS:.o=.bin)
CPP_BINS := $(addprefix $(OUT)/cpp_,$(addsuffix .bin,$(REFS)))

.PHONY: all test check-reference
all: $(OUT)/test-render.elf $(REF_BINS) $(CPP_BINS)
$(OUT):
	mkdir -p "$@"
$(OUT)/render_helpers.o: render_helpers.cpp render_helpers.hpp Makefile | $(OUT)
	$(CXX) $(FLAGS) -c $< -o $@
$(OUT)/test_render_helpers.o: test_render_helpers.cpp render_helpers.hpp Makefile | $(OUT)
	$(CXX) $(FLAGS) -c $< -o $@
$(OUT)/test_runtime.o: test_runtime.S | $(OUT)
	as --32 $< -o $@
$(OUT)/reference_%.o: $(REFERENCE_DIR)/%.S | $(OUT)
	as --32 $< -o $@
$(OUT)/reference_%.bin: $(OUT)/reference_%.o
	objcopy -O binary --only-section=.text $< $@
$(OUT)/cpp_%.bin: $(OUT)/render_helpers.o
	objcopy -O binary --only-section=.text.recovered_$* $< $@
$(OUT)/test-render.elf: $(OUT)/test_runtime.o $(OUT)/test_render_helpers.o $(OUT)/render_helpers.o $(REF_OBJECTS)
	ld -m elf_i386 -z noexecstack -e _start -o $@ $^
test: all
	$(OUT)/test-render.elf
# Run the existing unchanged verifier against the assembled reference only.
# GAME and MATCHER must be explicitly supplied; no mutable Steam default.
check-reference: $(REF_BINS)
	test -n "$(GAME)" && test -n "$(MATCHER)"
	"$(MATCHER)" native-check "$(GAME)" ui-matrix-scale "$(OUT)/reference_ui_matrix_scale.bin" "$(OUT)/reference-ui-matrix-scale.json"
	"$(MATCHER)" native-check "$(GAME)" shader-base-ctor "$(OUT)/reference_shader_base_ctor.bin" "$(OUT)/reference-shader-base-ctor.json"
	"$(MATCHER)" native-check "$(GAME)" shader-binding-cleanup "$(OUT)/reference_shader_binding_cleanup.bin" "$(OUT)/reference-shader-binding-cleanup.json"
