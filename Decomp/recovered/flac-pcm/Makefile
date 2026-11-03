CXX ?= g++
OUT ?= ../../../build/flac-pcm-recovery
DECOMP ?= ../..
FLAGS := -std=c++17 -m32 -O2 -Wall -Wextra -Werror -ffreestanding -fno-exceptions -fno-rtti -fno-pie -fno-stack-protector -fno-tree-vectorize -fno-tree-loop-distribute-patterns -fno-fast-math -ffp-contract=off -msse2 -mfpmath=sse
.PHONY: test
$(OUT):
	mkdir -p "$@"
$(OUT)/impl.o: impl.cpp impl.hpp | $(OUT)
	$(CXX) $(FLAGS) -c $< -o $@
$(OUT)/test.o: test.cpp impl.hpp | $(OUT)
	$(CXX) $(FLAGS) -c $< -o $@
$(OUT)/reference.o: reference.S | $(OUT)
	as --32 $< -o $@
$(OUT)/runtime.o: $(DECOMP)/recovered/test_runtime.S | $(OUT)
	as --32 $< -o $@
$(OUT)/test.elf: $(OUT)/runtime.o $(OUT)/test.o $(OUT)/impl.o $(OUT)/reference.o
	ld -m elf_i386 -z noexecstack -e _start --section-start=.flac_channel0_loop=0x4f91f0 --section-start=.test_loop_return=0x4f9212 -o $@ $^
$(OUT)/loop.bin: $(OUT)/test.elf
	objcopy -O binary --only-section=.flac_channel0_loop $< $@
$(OUT)/verify: verify.cpp | $(OUT)
	$(CXX) -std=c++20 -O2 -Wall -Wextra -Werror -I $(DECOMP) $< -lcrypto -o $@
test: $(OUT)/test.elf $(OUT)/loop.bin $(OUT)/verify
	test -n "$(GAME)"
	$(OUT)/verify "$(GAME)" $(OUT)/loop.bin > $(OUT)/reference-check.json
	$(OUT)/test.elf > $(OUT)/behavior.log
	cat $(OUT)/behavior.log
