CXX ?= c++
CXXFLAGS ?= -O2 -g
CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic -Werror
OUT ?= ../build/decomp
GAME ?= $(HOME)/.local/share/Steam/steamapps/common/Riff Racer/Game.exe

all: $(OUT)/reriff-match

$(OUT)/draft-assembly: draft_assembly.cpp
	mkdir -p $(OUT)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OUT)/reriff-match: main.cpp matching.hpp build_evidence.hpp native_blocks.hpp coverage.hpp support/native_common.hpp support/archive.hpp
	mkdir -p $(OUT)
	$(CXX) $(CXXFLAGS) main.cpp -o $@ -lz -lcrypto

$(OUT)/test-matching: test_matching.cpp matching.hpp build_evidence.hpp native_blocks.hpp coverage.hpp support/native_common.hpp support/archive.hpp
	mkdir -p $(OUT)
	$(CXX) $(CXXFLAGS) test_matching.cpp -o $@ -lz -lcrypto

test: $(OUT)/test-matching
	$(OUT)/test-matching

$(OUT)/exe_entry.bin: native/exe_entry.S
	mkdir -p $(OUT)
	as --32 native/exe_entry.S -o $(OUT)/exe_entry.o
	objcopy -O binary --only-section=.text $(OUT)/exe_entry.o $@

test-entry: $(OUT)/reriff-match $(OUT)/exe_entry.bin
	$(OUT)/reriff-match entry-check "$(GAME)" $(OUT)/exe_entry.bin $(OUT)/entry-comparison.json

.PHONY: all test test-entry

$(OUT)/security_cookie.bin: native/security_cookie.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/security_cookie.o
	objcopy -O binary --only-section=.text $(OUT)/security_cookie.o $@

$(OUT)/crt_entry.bin: native/crt_entry.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_entry.o
	ld -m elf_i386 -Ttext=0x008F8A84 -e original_crt_entry --defsym=original_security_cookie_init=0x008F9B78 --defsym=original_crt_startup_common=0x008F8A8E $(OUT)/crt_entry.o -o $(OUT)/crt_entry.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_entry.elf $@

$(OUT)/crt_startup.bin: native/crt_startup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_startup.o
	ld -m elf_i386 -Ttext=0x008F8A8E -e original_crt_startup_common $(OUT)/crt_startup.o -o $(OUT)/crt_startup.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_startup.elf $@

$(OUT)/crt_seh.bin: native/crt_seh.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_seh.o
	objcopy -O binary --only-section=.text $(OUT)/crt_seh.o $@

$(OUT)/crt_scope.bin: native/crt_scope.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_scope.o
	objcopy -O binary --only-section=.rodata $(OUT)/crt_scope.o $@

test-startup: $(OUT)/reriff-match $(OUT)/security_cookie.bin $(OUT)/crt_entry.bin $(OUT)/crt_startup.bin $(OUT)/crt_seh.bin $(OUT)/crt_scope.bin
	$(OUT)/reriff-match native-check "$(GAME)" security-cookie $(OUT)/security_cookie.bin $(OUT)/security-cookie-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" crt-entry $(OUT)/crt_entry.bin $(OUT)/crt-entry-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" crt-startup $(OUT)/crt_startup.bin $(OUT)/crt-startup-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" crt-seh $(OUT)/crt_seh.bin $(OUT)/crt-seh-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" crt-scope $(OUT)/crt_scope.bin $(OUT)/crt-scope-comparison.json

.PHONY: test-startup

$(OUT)/application_entry.bin: native/application_entry.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/application_entry.o
	ld -m elf_i386 -Ttext=0x005CFC90 -e original_application_entry $(OUT)/application_entry.o -o $(OUT)/application_entry.elf
	objcopy -O binary --only-section=.text $(OUT)/application_entry.elf $@

test-application: $(OUT)/reriff-match $(OUT)/application_entry.bin
	$(OUT)/reriff-match native-check "$(GAME)" application-entry $(OUT)/application_entry.bin $(OUT)/application-entry-comparison.json

.PHONY: test-application

$(OUT)/startup_objects.elf: native/startup_objects.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/startup_objects.o
	ld -m elf_i386 -e object_5cfb10 --section-start=.object_5cfb10=0x005CFB10 --section-start=.object_5cfb60=0x005CFB60 --section-start=.object_5cfbe0=0x005CFBE0 --section-start=.object_5cfc60=0x005CFC60 $(OUT)/startup_objects.o -o $@

$(OUT)/object_%.bin: $(OUT)/startup_objects.elf
	objcopy -O binary --only-section=.object_$* $< $@

test-objects: $(OUT)/reriff-match $(OUT)/object_5cfb10.bin $(OUT)/object_5cfb60.bin $(OUT)/object_5cfbe0.bin $(OUT)/object_5cfc60.bin
	$(OUT)/reriff-match native-check "$(GAME)" object-5cfb10 $(OUT)/object_5cfb10.bin $(OUT)/object-5cfb10-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" object-5cfb60 $(OUT)/object_5cfb60.bin $(OUT)/object-5cfb60-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" object-5cfbe0 $(OUT)/object_5cfbe0.bin $(OUT)/object-5cfbe0-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" object-5cfc60 $(OUT)/object_5cfc60.bin $(OUT)/object-5cfc60-comparison.json

.PHONY: test-objects

$(OUT)/message_pump.bin: native/message_pump.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/message_pump.o
	objcopy -O binary --only-section=.text $(OUT)/message_pump.o $@

$(OUT)/worker_thread.elf: native/worker_thread.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_thread.o
	ld -m elf_i386 -e original_worker_delete --section-start=.worker_delete=0x0048DB80 --section-start=.worker_destroy=0x0048DBB0 --section-start=.worker_start=0x0048DBC0 --section-start=.worker_dispatch=0x0048DC50 $(OUT)/worker_thread.o -o $@

$(OUT)/worker_%.bin: $(OUT)/worker_thread.elf
	objcopy -O binary --only-section=.worker_$* $< $@

test-worker: $(OUT)/reriff-match $(OUT)/message_pump.bin $(OUT)/worker_delete.bin $(OUT)/worker_destroy.bin $(OUT)/worker_start.bin $(OUT)/worker_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" message-pump $(OUT)/message_pump.bin $(OUT)/message-pump-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" worker-delete $(OUT)/worker_delete.bin $(OUT)/worker-delete-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" worker-destroy $(OUT)/worker_destroy.bin $(OUT)/worker-destroy-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" worker-start $(OUT)/worker_start.bin $(OUT)/worker-start-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" worker-dispatch $(OUT)/worker_dispatch.bin $(OUT)/worker-dispatch-comparison.json

.PHONY: test-worker

$(OUT)/worker_request.bin: native/worker_request.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_request.o
	objcopy -O binary --only-section=.text $(OUT)/worker_request.o $@

test-request: $(OUT)/reriff-match $(OUT)/worker_request.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-request $(OUT)/worker_request.bin $(OUT)/worker-request-comparison.json

.PHONY: test-request

$(OUT)/request_dispatch.bin: native/request_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_dispatch.o
	ld -m elf_i386 -Ttext=0x004A1900 -e original_request_dispatch $(OUT)/request_dispatch.o -o $(OUT)/request_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/request_dispatch.elf $@

test-dispatch: $(OUT)/reriff-match $(OUT)/request_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-dispatch $(OUT)/request_dispatch.bin $(OUT)/request-dispatch-comparison.json

.PHONY: test-dispatch

$(OUT)/request_cleanup.bin: native/request_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_cleanup.o
	objcopy -O binary --only-section=.text $(OUT)/request_cleanup.o $@

test-cleanup: $(OUT)/reriff-match $(OUT)/request_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-cleanup $(OUT)/request_cleanup.bin $(OUT)/request-cleanup-comparison.json

test-recovered: test test-entry test-startup test-application test-objects test-worker test-request test-dispatch test-cleanup test-case3 test-case2 test-window test-secondary-window

.PHONY: test-cleanup test-recovered

$(OUT)/request_case3.bin: native/request_case3.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_case3.o
	ld -m elf_i386 -Ttext=0x004A2130 -e original_request_case3 $(OUT)/request_case3.o -o $(OUT)/request_case3.elf
	objcopy -O binary --only-section=.text $(OUT)/request_case3.elf $@

test-case3: $(OUT)/reriff-match $(OUT)/request_case3.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-case3 $(OUT)/request_case3.bin $(OUT)/request-case3-comparison.json

.PHONY: test-case3

$(OUT)/request_case2.bin: native/request_case2.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_case2.o
	ld -m elf_i386 -Ttext=0x004A1CD0 -e original_request_case2 $(OUT)/request_case2.o -o $(OUT)/request_case2.elf
	objcopy -O binary --only-section=.text $(OUT)/request_case2.elf $@

test-case2: $(OUT)/reriff-match $(OUT)/request_case2.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-case2 $(OUT)/request_case2.bin $(OUT)/request-case2-comparison.json

.PHONY: test-case2

$(OUT)/window_mode.bin: native/window_mode.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/window_mode.o
	ld -m elf_i386 -Ttext=0x0048CB30 -e original_window_mode $(OUT)/window_mode.o -o $(OUT)/window_mode.elf
	objcopy -O binary --only-section=.text $(OUT)/window_mode.elf $@

$(OUT)/cookie_check.bin: native/cookie_check.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/cookie_check.o
	ld -m elf_i386 -Ttext=0x008F8958 -e original_cookie_check $(OUT)/cookie_check.o -o $(OUT)/cookie_check.elf
	objcopy -O binary --only-section=.text $(OUT)/cookie_check.elf $@

test-window: $(OUT)/reriff-match $(OUT)/window_mode.bin $(OUT)/cookie_check.bin
	$(OUT)/reriff-match native-check "$(GAME)" window-mode $(OUT)/window_mode.bin $(OUT)/window-mode-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" cookie-check $(OUT)/cookie_check.bin $(OUT)/cookie-check-comparison.json

.PHONY: test-window

$(OUT)/secondary_window.bin: native/secondary_window.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/secondary_window.o
	ld -m elf_i386 -Ttext=0x0048CC70 -e original_secondary_window $(OUT)/secondary_window.o -o $(OUT)/secondary_window.elf
	objcopy -O binary --only-section=.text $(OUT)/secondary_window.elf $@

test-secondary-window: $(OUT)/reriff-match $(OUT)/secondary_window.bin
	$(OUT)/reriff-match native-check "$(GAME)" secondary-window $(OUT)/secondary_window.bin $(OUT)/secondary-window-comparison.json

.PHONY: test-secondary-window

$(OUT)/window_frame.bin: native/window_frame.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/window_frame.o
	ld -m elf_i386 -Ttext=0x0048CAB0 -e original_window_frame $(OUT)/window_frame.o -o $(OUT)/window_frame.elf
	objcopy -O binary --only-section=.text $(OUT)/window_frame.elf $@

test-window-frame: $(OUT)/reriff-match $(OUT)/window_frame.bin
	$(OUT)/reriff-match native-check "$(GAME)" window-frame $(OUT)/window_frame.bin $(OUT)/window-frame-comparison.json

test-recovered: test-window-frame
.PHONY: test-window-frame

$(OUT)/viewport_size.bin: native/viewport_size.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/viewport_size.o
	ld -m elf_i386 -Ttext=0x004A22E0 -e original_viewport_size $(OUT)/viewport_size.o -o $(OUT)/viewport_size.elf
	objcopy -O binary --only-section=.text $(OUT)/viewport_size.elf $@

$(OUT)/fit_dimensions.bin: native/fit_dimensions.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/fit_dimensions.o
	ld -m elf_i386 -Ttext=0x004A1C30 -e original_fit_dimensions $(OUT)/fit_dimensions.o -o $(OUT)/fit_dimensions.elf
	objcopy -O binary --only-section=.text $(OUT)/fit_dimensions.elf $@

test-viewport: $(OUT)/reriff-match $(OUT)/viewport_size.bin $(OUT)/fit_dimensions.bin
	$(OUT)/reriff-match native-check "$(GAME)" viewport-size $(OUT)/viewport_size.bin $(OUT)/viewport-size-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" fit-dimensions $(OUT)/fit_dimensions.bin $(OUT)/fit-dimensions-comparison.json

test-recovered: test-viewport
.PHONY: test-viewport

$(OUT)/floor_float.bin: native/floor_float.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/floor_float.o
	ld -m elf_i386 -Ttext=0x00426D20 -e original_floor_float $(OUT)/floor_float.o -o $(OUT)/floor_float.elf
	objcopy -O binary --only-section=.text $(OUT)/floor_float.elf $@

$(OUT)/remove_registered.bin: native/remove_registered.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/remove_registered.o
	objcopy -O binary --only-section=.text $(OUT)/remove_registered.o $@

test-native-helpers: $(OUT)/reriff-match $(OUT)/floor_float.bin $(OUT)/remove_registered.bin
	$(OUT)/reriff-match native-check "$(GAME)" floor-float $(OUT)/floor_float.bin $(OUT)/floor-float-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" remove-registered $(OUT)/remove_registered.bin $(OUT)/remove-registered-comparison.json

test-recovered: test-native-helpers
.PHONY: test-native-helpers

$(OUT)/load_graphics.bin: native/load_graphics.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/load_graphics.o
	ld -m elf_i386 -Ttext=0x004A2460 -e original_load_graphics $(OUT)/load_graphics.o -o $(OUT)/load_graphics.elf
	objcopy -O binary --only-section=.text $(OUT)/load_graphics.elf $@

test-load-graphics: $(OUT)/reriff-match $(OUT)/load_graphics.bin
	$(OUT)/reriff-match native-check "$(GAME)" load-graphics $(OUT)/load_graphics.bin $(OUT)/load-graphics-comparison.json

test-recovered: test-load-graphics
.PHONY: test-load-graphics

$(OUT)/resize_resources.bin: native/resize_resources.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resize_resources.o
	ld -m elf_i386 -Ttext=0x00528F80 -e original_resize_resources $(OUT)/resize_resources.o -o $(OUT)/resize_resources.elf
	objcopy -O binary --only-section=.text $(OUT)/resize_resources.elf $@

test-resize-resources: $(OUT)/reriff-match $(OUT)/resize_resources.bin
	$(OUT)/reriff-match native-check "$(GAME)" resize-resources $(OUT)/resize_resources.bin $(OUT)/resize-resources-comparison.json

test-recovered: test-resize-resources
.PHONY: test-resize-resources

$(OUT)/save_graphics.bin: native/save_graphics.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_graphics.o
	ld -m elf_i386 -Ttext=0x004A2640 -e original_save_graphics $(OUT)/save_graphics.o -o $(OUT)/save_graphics.elf
	objcopy -O binary --only-section=.text $(OUT)/save_graphics.elf $@

test-save-graphics: $(OUT)/reriff-match $(OUT)/save_graphics.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-graphics $(OUT)/save_graphics.bin $(OUT)/save-graphics-comparison.json

test-recovered: test-save-graphics
.PHONY: test-save-graphics

$(OUT)/save_device_ctor.bin: native/save_device_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_ctor.o
	objcopy -O binary --only-section=.text $(OUT)/save_device_ctor.o $@

test-save-device: $(OUT)/reriff-match $(OUT)/save_device_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-ctor $(OUT)/save_device_ctor.bin $(OUT)/save-device-ctor-comparison.json

test-recovered: test-save-device
.PHONY: test-save-device

$(OUT)/save_device_close.bin: native/save_device_close.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_close.o
	objcopy -O binary --only-section=.text $(OUT)/save_device_close.o $@

$(OUT)/save_device_delete.bin: native/save_device_delete.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_delete.o
	ld -m elf_i386 -Ttext=0x00535CC0 -e original_save_device_delete $(OUT)/save_device_delete.o -o $(OUT)/save_device_delete.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_delete.elf $@

test-save-device-operations: $(OUT)/reriff-match $(OUT)/save_device_close.bin $(OUT)/save_device_delete.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-close $(OUT)/save_device_close.bin $(OUT)/save-device-close-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" save-device-delete $(OUT)/save_device_delete.bin $(OUT)/save-device-delete-comparison.json

test-recovered: test-save-device-operations
.PHONY: test-save-device-operations

$(OUT)/save_device_io.o: native/save_device_io.S
	mkdir -p $(OUT)
	as --32 $< -o $@

$(OUT)/save_device_read.bin: $(OUT)/save_device_io.o
	objcopy -O binary --only-section=.read $< $@

$(OUT)/save_device_write.bin: $(OUT)/save_device_io.o
	objcopy -O binary --only-section=.write $< $@

test-save-device-io: $(OUT)/reriff-match $(OUT)/save_device_read.bin $(OUT)/save_device_write.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-read $(OUT)/save_device_read.bin $(OUT)/save-device-read-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" save-device-write $(OUT)/save_device_write.bin $(OUT)/save-device-write-comparison.json

test-recovered: test-save-device-io
.PHONY: test-save-device-io

$(OUT)/save_device_open.bin: native/save_device_open.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_open.o
	ld -m elf_i386 -Ttext=0x00535B10 -e original_save_device_open $(OUT)/save_device_open.o -o $(OUT)/save_device_open.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_open.elf $@

test-save-device-open: $(OUT)/reriff-match $(OUT)/save_device_open.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-open $(OUT)/save_device_open.bin $(OUT)/save-device-open-comparison.json

test-recovered: test-save-device-open
.PHONY: test-save-device-open

coverage: test-recovered
	$(OUT)/reriff-match coverage "$(GAME)" $(OUT) $(OUT)/coverage.json

.PHONY: coverage

# UTF-16 storage dependencies, mechanically transcribed reference assembly.
# Keep complete function extents and compare at their original addresses.
define wide_reference
$(OUT)/$(1).bin: native/$(1).S
	mkdir -p $(OUT)
	as --32 $$< -o $(OUT)/$(1).o
	ld -m elf_i386 -Ttext=$(2) -e original_$(1) $(OUT)/$(1).o -o $(OUT)/$(1).elf
	objcopy -O binary --only-section=.text $(OUT)/$(1).elf $$@

test-$(subst _,-,$(1)): $(OUT)/reriff-match $(OUT)/$(1).bin
	$(OUT)/reriff-match native-check "$(GAME)" $(subst _,-,$(1)) $(OUT)/$(1).bin $(OUT)/$(subst _,-,$(1))-comparison.json

test-recovered: test-$(subst _,-,$(1))
.PHONY: test-$(subst _,-,$(1))
endef
$(eval $(call wide_reference,wide_move_construct,0x0044f6f0))
$(eval $(call wide_reference,wide_destroy,0x0044f760))
$(eval $(call wide_reference,wide_assign_pointer,0x0044f790))
$(eval $(call wide_reference,wide_move_storage,0x0044f890))
$(eval $(call wide_reference,wide_set_length,0x0044fab0))

$(OUT)/save_device_exists.bin: native/save_device_exists.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_exists.o
	ld -m elf_i386 -Ttext=0x00535810 -e original_save_device_exists $(OUT)/save_device_exists.o -o $(OUT)/save_device_exists.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_exists.elf $@

$(OUT)/save_device_create.bin: native/save_device_create.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_create.o
	ld -m elf_i386 -Ttext=0x005358F0 -e original_save_device_create $(OUT)/save_device_create.o -o $(OUT)/save_device_create.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_create.elf $@

test-save-device-create: $(OUT)/reriff-match $(OUT)/save_device_exists.bin $(OUT)/save_device_create.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-exists $(OUT)/save_device_exists.bin $(OUT)/save-device-exists-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" save-device-create $(OUT)/save_device_create.bin $(OUT)/save-device-create-comparison.json

test-recovered: test-save-device-create
.PHONY: test-save-device-create

test-draft: $(OUT)/draft-assembly
	bash test-draft.sh $(OUT)/draft-assembly

.PHONY: test-draft

$(OUT)/save_device_size.bin: native/save_device_size.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_size.o
	objcopy -O binary --only-section=.text $(OUT)/save_device_size.o $@

test-save-device-size: $(OUT)/reriff-match $(OUT)/save_device_size.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-size $(OUT)/save_device_size.bin $(OUT)/save-device-size-comparison.json

test-recovered: test-save-device-size
.PHONY: test-save-device-size

$(OUT)/application_worker.bin: native/application_worker.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/application_worker.o
	ld -m elf_i386 -Ttext=0x005282E0 -e original_application_worker $(OUT)/application_worker.o -o $(OUT)/application_worker.elf
	objcopy -O binary --only-section=.text $(OUT)/application_worker.elf $@

test-application-worker: $(OUT)/reriff-match $(OUT)/application_worker.bin
	$(OUT)/reriff-match native-check "$(GAME)" application-worker $(OUT)/application_worker.bin $(OUT)/application-worker-comparison.json

test-recovered: test-application-worker
.PHONY: test-application-worker

$(OUT)/worker_queue.bin: native/worker_queue.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_queue.o
	ld -m elf_i386 -Ttext=0x00528930 -e original_worker_queue $(OUT)/worker_queue.o -o $(OUT)/worker_queue.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_queue.elf $@

test-worker-queue: $(OUT)/reriff-match $(OUT)/worker_queue.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-queue $(OUT)/worker_queue.bin $(OUT)/worker-queue-comparison.json

test-recovered: test-worker-queue
.PHONY: test-worker-queue

$(OUT)/application_frame.bin: native/application_frame.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/application_frame.o
	ld -m elf_i386 -Ttext=0x004A0AF0 -e original_application_frame $(OUT)/application_frame.o -o $(OUT)/application_frame.elf
	objcopy -O binary --only-section=.text $(OUT)/application_frame.elf $@

test-application-frame: $(OUT)/reriff-match $(OUT)/application_frame.bin
	$(OUT)/reriff-match native-check "$(GAME)" application-frame $(OUT)/application_frame.bin $(OUT)/application-frame-comparison.json

test-recovered: test-application-frame
.PHONY: test-application-frame

$(OUT)/device_release.bin: native/device_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_release.o
	ld -m elf_i386 -Ttext=0x004A6330 -e original_device_release $(OUT)/device_release.o -o $(OUT)/device_release.elf
	objcopy -O binary --only-section=.text $(OUT)/device_release.elf $@

$(OUT)/device_restore.bin: native/device_restore.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_restore.o
	ld -m elf_i386 -Ttext=0x004A6560 -e original_device_restore $(OUT)/device_restore.o -o $(OUT)/device_restore.elf
	objcopy -O binary --only-section=.text $(OUT)/device_restore.elf $@

test-device-recovery: $(OUT)/reriff-match $(OUT)/device_release.bin $(OUT)/device_restore.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-release $(OUT)/device_release.bin $(OUT)/device-release-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" device-restore $(OUT)/device_restore.bin $(OUT)/device-restore-comparison.json

test-recovered: test-device-recovery
.PHONY: test-device-recovery

$(OUT)/query_create.bin: native/query_create.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/query_create.o
	ld -m elf_i386 -Ttext=0x004A4C50 -e original_query_create $(OUT)/query_create.o -o $(OUT)/query_create.elf
	objcopy -O binary --only-section=.text $(OUT)/query_create.elf $@

$(OUT)/query_release.bin: native/query_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/query_release.o
	objcopy -O binary --only-section=.text $(OUT)/query_release.o $@

test-query-resources: $(OUT)/reriff-match $(OUT)/query_create.bin $(OUT)/query_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" query-create $(OUT)/query_create.bin $(OUT)/query-create-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" query-release $(OUT)/query_release.bin $(OUT)/query-release-comparison.json

test-recovered: test-query-resources
.PHONY: test-query-resources

$(OUT)/colour_targets.bin: native/colour_targets.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/colour_targets.o
	ld -m elf_i386 -Ttext=0x4a5240 -e original_colour_targets $(OUT)/colour_targets.o -o $(OUT)/colour_targets.elf
	objcopy -O binary --only-section=.text $(OUT)/colour_targets.elf $@

$(OUT)/effect_target.bin: native/effect_target.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/effect_target.o
	ld -m elf_i386 -Ttext=0x4a5530 -e original_effect_target $(OUT)/effect_target.o -o $(OUT)/effect_target.elf
	objcopy -O binary --only-section=.text $(OUT)/effect_target.elf $@

$(OUT)/aux_target_a.bin: native/aux_target_a.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/aux_target_a.o
	ld -m elf_i386 -Ttext=0x4a56c0 -e original_aux_target_a $(OUT)/aux_target_a.o -o $(OUT)/aux_target_a.elf
	objcopy -O binary --only-section=.text $(OUT)/aux_target_a.elf $@

$(OUT)/aux_target_b.bin: native/aux_target_b.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/aux_target_b.o
	ld -m elf_i386 -Ttext=0x4a5850 -e original_aux_target_b $(OUT)/aux_target_b.o -o $(OUT)/aux_target_b.elf
	objcopy -O binary --only-section=.text $(OUT)/aux_target_b.elf $@

test-target-creation: $(OUT)/reriff-match $(OUT)/colour_targets.bin $(OUT)/effect_target.bin $(OUT)/aux_target_a.bin $(OUT)/aux_target_b.bin
	$(OUT)/reriff-match native-check "$(GAME)" colour-targets $(OUT)/colour_targets.bin $(OUT)/colour-targets-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" effect-target $(OUT)/effect_target.bin $(OUT)/effect-target-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" aux-target-a $(OUT)/aux_target_a.bin $(OUT)/aux-target-a-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" aux-target-b $(OUT)/aux_target_b.bin $(OUT)/aux-target-b-comparison.json

test-recovered: test-target-creation
.PHONY: test-target-creation

$(OUT)/device_defaults.bin: native/device_defaults.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_defaults.o
	objcopy -O binary --only-section=.text $(OUT)/device_defaults.o $@

test-device-defaults: $(OUT)/reriff-match $(OUT)/device_defaults.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-defaults $(OUT)/device_defaults.bin $(OUT)/device-defaults-comparison.json

test-recovered: test-device-defaults
.PHONY: test-device-defaults

$(OUT)/buffer_allocate.bin: native/buffer_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/buffer_allocate.o
	objcopy -O binary --only-section=.text $(OUT)/buffer_allocate.o $@

test-buffer-allocate: $(OUT)/reriff-match $(OUT)/buffer_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" buffer-allocate $(OUT)/buffer_allocate.bin $(OUT)/buffer-allocate-comparison.json

test-recovered: test-buffer-allocate
.PHONY: test-buffer-allocate

$(OUT)/device_create.bin: native/device_create.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_create.o
	ld -m elf_i386 -Ttext=0x004a3630 -e original_device_create $(OUT)/device_create.o -o $(OUT)/device_create.elf
	objcopy -O binary --only-section=.text $(OUT)/device_create.elf $@

test-device-create: $(OUT)/reriff-match $(OUT)/device_create.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-create $(OUT)/device_create.bin $(OUT)/device-create-comparison.json

test-recovered: test-device-create
.PHONY: test-device-create

$(OUT)/device_destroy.bin: native/device_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_destroy.o
	ld -m elf_i386 -Ttext=0x004a5c40 -e original_device_destroy $(OUT)/device_destroy.o -o $(OUT)/device_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/device_destroy.elf $@

test-device-destroy: $(OUT)/reriff-match $(OUT)/device_destroy.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-destroy $(OUT)/device_destroy.bin $(OUT)/device-destroy-comparison.json

test-recovered: test-device-destroy
.PHONY: test-device-destroy

$(OUT)/presentation_parameters.bin: native/presentation_parameters.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/presentation_parameters.o
	ld -m elf_i386 -Ttext=0x4a33f0 -e original_presentation_parameters $(OUT)/presentation_parameters.o -o $(OUT)/presentation_parameters.elf
	objcopy -O binary --only-section=.text $(OUT)/presentation_parameters.elf $@

$(OUT)/vertex_declarations.bin: native/vertex_declarations.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/vertex_declarations.o
	ld -m elf_i386 -Ttext=0x4a3a40 -e original_vertex_declarations $(OUT)/vertex_declarations.o -o $(OUT)/vertex_declarations.elf
	objcopy -O binary --only-section=.text $(OUT)/vertex_declarations.elf $@

test-presentation-resources: $(OUT)/reriff-match $(OUT)/presentation_parameters.bin $(OUT)/vertex_declarations.bin
	$(OUT)/reriff-match native-check "$(GAME)" presentation-parameters $(OUT)/presentation_parameters.bin $(OUT)/presentation-parameters-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" vertex-declarations $(OUT)/vertex_declarations.bin $(OUT)/vertex-declarations-comparison.json

test-recovered: test-presentation-resources
.PHONY: test-presentation-resources

$(OUT)/graphics_startup.bin: native/graphics_startup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_startup.o
	ld -m elf_i386 -Ttext=0x4a0480 -e original_graphics_startup $(OUT)/graphics_startup.o -o $(OUT)/graphics_startup.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_startup.elf $@

$(OUT)/graphics_shutdown.bin: native/graphics_shutdown.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_shutdown.o
	ld -m elf_i386 -Ttext=0x4a08e0 -e original_graphics_shutdown $(OUT)/graphics_shutdown.o -o $(OUT)/graphics_shutdown.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_shutdown.elf $@

test-graphics-lifetime: $(OUT)/reriff-match $(OUT)/graphics_startup.bin $(OUT)/graphics_shutdown.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-startup $(OUT)/graphics_startup.bin $(OUT)/graphics-startup-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" graphics-shutdown $(OUT)/graphics_shutdown.bin $(OUT)/graphics-shutdown-comparison.json

test-recovered: test-graphics-lifetime
.PHONY: test-graphics-lifetime

$(OUT)/graphics_capabilities.bin: native/graphics_capabilities.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_capabilities.o
	ld -m elf_i386 -Ttext=0x4a2be0 -e original_graphics_capabilities $(OUT)/graphics_capabilities.o -o $(OUT)/graphics_capabilities.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_capabilities.elf $@

$(OUT)/graphics_options.bin: native/graphics_options.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_options.o
	ld -m elf_i386 -Ttext=0x4a27d0 -e original_graphics_options $(OUT)/graphics_options.o -o $(OUT)/graphics_options.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_options.elf $@

test-graphics-capabilities: $(OUT)/reriff-match $(OUT)/graphics_capabilities.bin $(OUT)/graphics_options.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-capabilities $(OUT)/graphics_capabilities.bin $(OUT)/graphics-capabilities-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" graphics-options $(OUT)/graphics_options.bin $(OUT)/graphics-options-comparison.json

test-recovered: test-graphics-capabilities
.PHONY: test-graphics-capabilities

$(OUT)/minimum_caps.bin: native/minimum_caps.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/minimum_caps.o
	ld -m elf_i386 -Ttext=0x4a59e0 -e original_minimum_caps $(OUT)/minimum_caps.o -o $(OUT)/minimum_caps.elf
	objcopy -O binary --only-section=.text $(OUT)/minimum_caps.elf $@

$(OUT)/display_modes.bin: native/display_modes.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/display_modes.o
	ld -m elf_i386 -Ttext=0x4a29d0 -e original_display_modes $(OUT)/display_modes.o -o $(OUT)/display_modes.elf
	objcopy -O binary --only-section=.text $(OUT)/display_modes.elf $@

test-capability-helpers: $(OUT)/reriff-match $(OUT)/minimum_caps.bin $(OUT)/display_modes.bin
	$(OUT)/reriff-match native-check "$(GAME)" minimum-caps $(OUT)/minimum_caps.bin $(OUT)/minimum-caps-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" display-modes $(OUT)/display_modes.bin $(OUT)/display-modes-comparison.json

test-recovered: test-capability-helpers
.PHONY: test-capability-helpers

$(OUT)/shader_setup.bin: native/shader_setup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_setup.o
	ld -m elf_i386 -Ttext=0x52db30 -e original_shader_setup $(OUT)/shader_setup.o -o $(OUT)/shader_setup.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_setup.elf $@

test-shader-setup: $(OUT)/reriff-match $(OUT)/shader_setup.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-setup $(OUT)/shader_setup.bin $(OUT)/shader-setup-comparison.json

test-recovered: test-shader-setup
.PHONY: test-shader-setup

$(OUT)/shader_pair_create.bin: native/shader_pair_create.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_pair_create.o
	ld -m elf_i386 -Ttext=0x52d840 -e original_shader_pair_create $(OUT)/shader_pair_create.o -o $(OUT)/shader_pair_create.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_pair_create.elf $@

$(OUT)/shader_release.bin: native/shader_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_release.o
	ld -m elf_i386 -Ttext=0x52f4c0 -e original_shader_release $(OUT)/shader_release.o -o $(OUT)/shader_release.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_release.elf $@

$(OUT)/shader_binding_cleanup.bin: native/shader_binding_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_binding_cleanup.o
	ld -m elf_i386 -Ttext=0x52f5b0 -e original_shader_binding_cleanup $(OUT)/shader_binding_cleanup.o -o $(OUT)/shader_binding_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_binding_cleanup.elf $@

test-shader-lifetime: $(OUT)/reriff-match $(OUT)/shader_pair_create.bin $(OUT)/shader_release.bin $(OUT)/shader_binding_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-pair-create $(OUT)/shader_pair_create.bin $(OUT)/shader-pair-create-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-release $(OUT)/shader_release.bin $(OUT)/shader-release-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-binding-cleanup $(OUT)/shader_binding_cleanup.bin $(OUT)/shader-binding-cleanup-comparison.json

test-recovered: test-shader-lifetime
.PHONY: test-shader-lifetime

$(OUT)/shader_finalize.bin: native/shader_finalize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_finalize.o
	ld -m elf_i386 -Ttext=0x530200 -e original_shader_finalize $(OUT)/shader_finalize.o -o $(OUT)/shader_finalize.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_finalize.elf $@

test-shader-finalize: $(OUT)/reriff-match $(OUT)/shader_finalize.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-finalize $(OUT)/shader_finalize.bin $(OUT)/shader-finalize-comparison.json

test-recovered: test-shader-finalize
.PHONY: test-shader-finalize

$(OUT)/shader_basic2d_ctor.bin: native/shader_basic2d_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_basic2d_ctor.o
	ld -m elf_i386 -Ttext=0x52ca50 -e original_shader_basic2d_ctor $(OUT)/shader_basic2d_ctor.o -o $(OUT)/shader_basic2d_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_basic2d_ctor.elf $@

$(OUT)/shader_finalize_handler.bin: native/shader_finalize_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_finalize_handler.o
	ld -m elf_i386 -Ttext=0x906264 -e original_shader_finalize_handler $(OUT)/shader_finalize_handler.o -o $(OUT)/shader_finalize_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_finalize_handler.elf $@

test-shader-dependencies: $(OUT)/reriff-match $(OUT)/shader_basic2d_ctor.bin $(OUT)/shader_finalize_handler.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-basic2d-ctor $(OUT)/shader_basic2d_ctor.bin $(OUT)/shader-basic2d-ctor-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-finalize-handler $(OUT)/shader_finalize_handler.bin $(OUT)/shader-finalize-handler-comparison.json

test-recovered: test-shader-dependencies
.PHONY: test-shader-dependencies

$(OUT)/shader_base_ctor.bin: native/shader_base_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_base_ctor.o
	ld -m elf_i386 -Ttext=0x5421b0 -e original_shader_base_ctor $(OUT)/shader_base_ctor.o -o $(OUT)/shader_base_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_base_ctor.elf $@

$(OUT)/shader_parameter_lookup.bin: native/shader_parameter_lookup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_parameter_lookup.o
	ld -m elf_i386 -Ttext=0x542340 -e original_shader_parameter_lookup $(OUT)/shader_parameter_lookup.o -o $(OUT)/shader_parameter_lookup.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_parameter_lookup.elf $@

$(OUT)/shader_basic2d_handler.bin: native/shader_basic2d_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_basic2d_handler.o
	ld -m elf_i386 -Ttext=0x905468 -e original_shader_basic2d_handler $(OUT)/shader_basic2d_handler.o -o $(OUT)/shader_basic2d_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_basic2d_handler.elf $@

test-shader-base: $(OUT)/reriff-match $(OUT)/shader_base_ctor.bin $(OUT)/shader_parameter_lookup.bin $(OUT)/shader_basic2d_handler.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-base-ctor $(OUT)/shader_base_ctor.bin $(OUT)/shader-base-ctor-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-parameter-lookup $(OUT)/shader_parameter_lookup.bin $(OUT)/shader-parameter-lookup-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-basic2d-handler $(OUT)/shader_basic2d_handler.bin $(OUT)/shader-basic2d-handler-comparison.json

test-recovered: test-shader-base
.PHONY: test-shader-base

$(OUT)/shader_common_parameters.bin: native/shader_common_parameters.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_common_parameters.o
	ld -m elf_i386 -Ttext=0x542230 -e original_shader_common_parameters $(OUT)/shader_common_parameters.o -o $(OUT)/shader_common_parameters.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_common_parameters.elf $@

$(OUT)/shader_drawprim_ctor.bin: native/shader_drawprim_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_drawprim_ctor.o
	ld -m elf_i386 -Ttext=0x5675a0 -e original_shader_drawprim_ctor $(OUT)/shader_drawprim_ctor.o -o $(OUT)/shader_drawprim_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_drawprim_ctor.elf $@

test-shader-drawprim: $(OUT)/reriff-match $(OUT)/shader_common_parameters.bin $(OUT)/shader_drawprim_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-common-parameters $(OUT)/shader_common_parameters.bin $(OUT)/shader-common-parameters-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-drawprim-ctor $(OUT)/shader_drawprim_ctor.bin $(OUT)/shader-drawprim-ctor-comparison.json

test-recovered: test-shader-drawprim
.PHONY: test-shader-drawprim

$(OUT)/shader_shadowdraw_ctor.bin: native/shader_shadowdraw_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_shadowdraw_ctor.o
	ld -m elf_i386 -Ttext=0x576c20 -e original_shader_shadowdraw_ctor $(OUT)/shader_shadowdraw_ctor.o -o $(OUT)/shader_shadowdraw_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_shadowdraw_ctor.elf $@

$(OUT)/shader_carlights_ctor.bin: native/shader_carlights_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_carlights_ctor.o
	ld -m elf_i386 -Ttext=0x576f00 -e original_shader_carlights_ctor $(OUT)/shader_carlights_ctor.o -o $(OUT)/shader_carlights_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_carlights_ctor.elf $@

test-shader-shadow-lights: $(OUT)/reriff-match $(OUT)/shader_shadowdraw_ctor.bin $(OUT)/shader_carlights_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-shadowdraw-ctor $(OUT)/shader_shadowdraw_ctor.bin $(OUT)/shader-shadowdraw-ctor-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-carlights-ctor $(OUT)/shader_carlights_ctor.bin $(OUT)/shader-carlights-ctor-comparison.json

test-recovered: test-shader-shadow-lights
.PHONY: test-shader-shadow-lights

$(OUT)/shader_sea_ctor.bin: native/shader_sea_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_sea_ctor.o
	ld -m elf_i386 -Ttext=0x577320 -e original_shader_sea_ctor $(OUT)/shader_sea_ctor.o -o $(OUT)/shader_sea_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_sea_ctor.elf $@

test-shader-sea: $(OUT)/reriff-match $(OUT)/shader_sea_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-sea-ctor $(OUT)/shader_sea_ctor.bin $(OUT)/shader-sea-ctor-comparison.json

test-recovered: test-shader-sea
.PHONY: test-shader-sea

$(OUT)/shader_depthwrite_ctor.bin: native/shader_depthwrite_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_depthwrite_ctor.o
	ld -m elf_i386 -Ttext=0x577f00 -e original_shader_depthwrite_ctor $(OUT)/shader_depthwrite_ctor.o -o $(OUT)/shader_depthwrite_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_depthwrite_ctor.elf $@

$(OUT)/shader_carglass_ctor.bin: native/shader_carglass_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_carglass_ctor.o
	ld -m elf_i386 -Ttext=0x578350 -e original_shader_carglass_ctor $(OUT)/shader_carglass_ctor.o -o $(OUT)/shader_carglass_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_carglass_ctor.elf $@

test-shader-depth-glass: $(OUT)/reriff-match $(OUT)/shader_depthwrite_ctor.bin $(OUT)/shader_carglass_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-depthwrite-ctor $(OUT)/shader_depthwrite_ctor.bin $(OUT)/shader-depthwrite-ctor-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" shader-carglass-ctor $(OUT)/shader_carglass_ctor.bin $(OUT)/shader-carglass-ctor-comparison.json

test-recovered: test-shader-depth-glass
.PHONY: test-shader-depth-glass

$(OUT)/shader_drift_ctor.bin: native/shader_drift_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_drift_ctor.o
	ld -m elf_i386 -Ttext=0x5788c0 -e original_shader_drift_ctor $(OUT)/shader_drift_ctor.o -o $(OUT)/shader_drift_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_drift_ctor.elf $@

test-shader-drift: $(OUT)/reriff-match $(OUT)/shader_drift_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-drift-ctor $(OUT)/shader_drift_ctor.bin $(OUT)/shader-drift-ctor-comparison.json

test-recovered: test-shader-drift
.PHONY: test-shader-drift

$(OUT)/shader_normalmapped_ctor.bin: native/shader_normalmapped_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_normalmapped_ctor.o
	ld -m elf_i386 -Ttext=0x5789c0 -e original_shader_normalmapped_ctor $(OUT)/shader_normalmapped_ctor.o -o $(OUT)/shader_normalmapped_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_normalmapped_ctor.elf $@

test-shader-normalmapped: $(OUT)/reriff-match $(OUT)/shader_normalmapped_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-normalmapped-ctor $(OUT)/shader_normalmapped_ctor.bin $(OUT)/shader-normalmapped-ctor-comparison.json

test-recovered: test-shader-normalmapped
.PHONY: test-shader-normalmapped

$(OUT)/shader_fxaa_ctor.bin: native/shader_fxaa_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_fxaa_ctor.o
	ld -m elf_i386 -Ttext=0x5794f0 -e original_shader_fxaa_ctor $(OUT)/shader_fxaa_ctor.o -o $(OUT)/shader_fxaa_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_fxaa_ctor.elf $@

test-shader-fxaa: $(OUT)/reriff-match $(OUT)/shader_fxaa_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-fxaa-ctor $(OUT)/shader_fxaa_ctor.bin $(OUT)/shader-fxaa-ctor-comparison.json

test-recovered: test-shader-fxaa
.PHONY: test-shader-fxaa

$(OUT)/shader_glass_ctor.bin: native/shader_glass_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_glass_ctor.o
	ld -m elf_i386 -Ttext=0x579860 -e original_shader_glass_ctor $(OUT)/shader_glass_ctor.o -o $(OUT)/shader_glass_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_glass_ctor.elf $@

test-shader-glass: $(OUT)/reriff-match $(OUT)/shader_glass_ctor.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-glass-ctor $(OUT)/shader_glass_ctor.bin $(OUT)/shader-glass-ctor-comparison.json

test-recovered: test-shader-glass
.PHONY: test-shader-glass

$(OUT)/save_device_destruct.elf: native/save_device_destruct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_destruct.o
	ld -m elf_i386 -e original_save_device_dispose --section-start=.save_device_dispose=0x00535770 --section-start=.save_device_destruct=0x005357A0 $(OUT)/save_device_destruct.o -o $@

$(OUT)/save_device_dispose.bin: $(OUT)/save_device_destruct.elf
	objcopy -O binary --only-section=.save_device_dispose $< $@

$(OUT)/save_device_destruct.bin: $(OUT)/save_device_destruct.elf
	objcopy -O binary --only-section=.save_device_destruct $< $@

test-save-device-destruct: $(OUT)/reriff-match $(OUT)/save_device_dispose.bin $(OUT)/save_device_destruct.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-dispose $(OUT)/save_device_dispose.bin $(OUT)/save-device-dispose-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" save-device-destruct $(OUT)/save_device_destruct.bin $(OUT)/save-device-destruct-comparison.json

test-recovered: test-save-device-destruct
.PHONY: test-save-device-destruct

$(OUT)/path_compose.bin: native/path_compose.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/path_compose.o
	ld -m elf_i386 -Ttext=0x00536220 -e original_path_compose $(OUT)/path_compose.o -o $(OUT)/path_compose.elf
	objcopy -O binary --only-section=.text $(OUT)/path_compose.elf $@

$(OUT)/wide_prepend.bin: native/wide_prepend.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_prepend.o
	ld -m elf_i386 -Ttext=0x00536250 -e original_wide_prepend $(OUT)/wide_prepend.o -o $(OUT)/wide_prepend.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_prepend.elf $@

test-path-composition: $(OUT)/reriff-match $(OUT)/path_compose.bin $(OUT)/wide_prepend.bin
	$(OUT)/reriff-match native-check "$(GAME)" path-compose $(OUT)/path_compose.bin $(OUT)/path-compose-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-prepend $(OUT)/wide_prepend.bin $(OUT)/wide-prepend-comparison.json

test-recovered: test-path-composition
.PHONY: test-path-composition

$(OUT)/runtime_fp_convert.bin: native/runtime_fp_convert.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/runtime_fp_convert.o
	ld -m elf_i386 -Ttext=0x008f9320 -e original_runtime_fp_convert $(OUT)/runtime_fp_convert.o -o $(OUT)/runtime_fp_convert.elf
	objcopy -O binary --only-section=.text $(OUT)/runtime_fp_convert.elf $@

test-runtime-fp-convert: $(OUT)/reriff-match $(OUT)/runtime_fp_convert.bin
	$(OUT)/reriff-match native-check "$(GAME)" runtime-fp-convert $(OUT)/runtime_fp_convert.bin $(OUT)/runtime-fp-convert-comparison.json

test-recovered: test-runtime-fp-convert
.PHONY: test-runtime-fp-convert

$(OUT)/wide_append_substring.bin: native/wide_append_substring.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_append_substring.o
	ld -m elf_i386 -Ttext=0x5360b0 -e original_wide_append_substring $(OUT)/wide_append_substring.o -o $(OUT)/wide_append_substring.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_append_substring.elf $@

$(OUT)/wide_append_pointer.bin: native/wide_append_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_append_pointer.o
	ld -m elf_i386 -Ttext=0x536160 -e original_wide_append_pointer $(OUT)/wide_append_pointer.o -o $(OUT)/wide_append_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_append_pointer.elf $@

test-wide-append: $(OUT)/reriff-match $(OUT)/wide_append_substring.bin $(OUT)/wide_append_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-append-substring $(OUT)/wide_append_substring.bin $(OUT)/wide-append-substring-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-append-pointer $(OUT)/wide_append_pointer.bin $(OUT)/wide-append-pointer-comparison.json

test-recovered: test-wide-append
.PHONY: test-wide-append

$(OUT)/save_device_set_name.bin: native/save_device_set_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_set_name.o
	ld -m elf_i386 -Ttext=0x535e30 -e original_save_device_set_name $(OUT)/save_device_set_name.o -o $(OUT)/save_device_set_name.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_set_name.elf $@

$(OUT)/wide_assign.bin: native/wide_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_assign.o
	ld -m elf_i386 -Ttext=0x536030 -e original_wide_assign $(OUT)/wide_assign.o -o $(OUT)/wide_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_assign.elf $@

$(OUT)/wide_prefix_construct.bin: native/wide_prefix_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_prefix_construct.o
	ld -m elf_i386 -Ttext=0x536070 -e original_wide_prefix_construct $(OUT)/wide_prefix_construct.o -o $(OUT)/wide_prefix_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_prefix_construct.elf $@

test-save-string-helpers: $(OUT)/reriff-match $(OUT)/save_device_set_name.bin $(OUT)/wide_assign.bin $(OUT)/wide_prefix_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-set-name $(OUT)/save_device_set_name.bin $(OUT)/save-device-set-name-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-assign $(OUT)/wide_assign.bin $(OUT)/wide-assign-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-prefix-construct $(OUT)/wide_prefix_construct.bin $(OUT)/wide-prefix-construct-comparison.json

test-recovered: test-save-string-helpers
.PHONY: test-save-string-helpers

$(OUT)/save_device_refresh.bin: native/save_device_refresh.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/save_device_refresh.o
	ld -m elf_i386 -Ttext=0x535ec0 -e original_save_device_refresh $(OUT)/save_device_refresh.o -o $(OUT)/save_device_refresh.elf
	objcopy -O binary --only-section=.text $(OUT)/save_device_refresh.elf $@

$(OUT)/wide_append_char.bin: native/wide_append_char.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_append_char.o
	ld -m elf_i386 -Ttext=0x44f8f0 -e original_wide_append_char $(OUT)/wide_append_char.o -o $(OUT)/wide_append_char.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_append_char.elf $@

$(OUT)/wide_assign_range.bin: native/wide_assign_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_assign_range.o
	ld -m elf_i386 -Ttext=0x44f9b0 -e original_wide_assign_range $(OUT)/wide_assign_range.o -o $(OUT)/wide_assign_range.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_assign_range.elf $@

test-path-refresh: $(OUT)/reriff-match $(OUT)/save_device_refresh.bin $(OUT)/wide_append_char.bin $(OUT)/wide_assign_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" save-device-refresh $(OUT)/save_device_refresh.bin $(OUT)/save-device-refresh-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-append-char $(OUT)/wide_append_char.bin $(OUT)/wide-append-char-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-assign-range $(OUT)/wide_assign_range.bin $(OUT)/wide-assign-range-comparison.json

test-recovered: test-path-refresh
.PHONY: test-path-refresh

$(OUT)/wide_assign_substring.bin: native/wide_assign_substring.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_assign_substring.o
	ld -m elf_i386 -Ttext=0x44fb30 -e original_wide_assign_substring $(OUT)/wide_assign_substring.o -o $(OUT)/wide_assign_substring.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_assign_substring.elf $@

$(OUT)/wide_truncate.bin: native/wide_truncate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_truncate.o
	ld -m elf_i386 -Ttext=0x44fcf0 -e original_wide_truncate $(OUT)/wide_truncate.o -o $(OUT)/wide_truncate.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_truncate.elf $@

$(OUT)/wide_erase.bin: native/wide_erase.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_erase.o
	ld -m elf_i386 -Ttext=0x44fd30 -e original_wide_erase $(OUT)/wide_erase.o -o $(OUT)/wide_erase.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_erase.elf $@

$(OUT)/wide_grow.bin: native/wide_grow.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_grow.o
	ld -m elf_i386 -Ttext=0x44fde0 -e original_wide_grow $(OUT)/wide_grow.o -o $(OUT)/wide_grow.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_grow.elf $@

$(OUT)/wide_allocate.bin: native/wide_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_allocate.o
	ld -m elf_i386 -Ttext=0x44ff40 -e original_wide_allocate $(OUT)/wide_allocate.o -o $(OUT)/wide_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_allocate.elf $@

test-wide-storage: $(OUT)/reriff-match $(OUT)/wide_assign_substring.bin $(OUT)/wide_truncate.bin $(OUT)/wide_erase.bin $(OUT)/wide_grow.bin $(OUT)/wide_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-assign-substring $(OUT)/wide_assign_substring.bin $(OUT)/wide-assign-substring-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-truncate $(OUT)/wide_truncate.bin $(OUT)/wide-truncate-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-erase $(OUT)/wide_erase.bin $(OUT)/wide-erase-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-grow $(OUT)/wide_grow.bin $(OUT)/wide-grow-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-allocate $(OUT)/wide_allocate.bin $(OUT)/wide-allocate-comparison.json

test-recovered: test-wide-storage
.PHONY: test-wide-storage

$(OUT)/wide_growth_runtime.elf: native/wide_growth_runtime.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_growth_runtime.o
	ld -m elf_i386 -e original_wide_grow_handler --section-start=.wide_grow_handler=0x8ffa00 --section-start=.cxx_frame_handler_import=0x8f8968 --section-start=.cxx_throw_import=0x8f8d5a --section-start=.memcpy_import=0x8f8d66 $(OUT)/wide_growth_runtime.o -o $@

$(OUT)/wide_grow_handler.bin: $(OUT)/wide_growth_runtime.elf
	objcopy -O binary --only-section=.wide_grow_handler $< $@

$(OUT)/cxx_frame_handler_import.bin: $(OUT)/wide_growth_runtime.elf
	objcopy -O binary --only-section=.cxx_frame_handler_import $< $@

$(OUT)/cxx_throw_import.bin: $(OUT)/wide_growth_runtime.elf
	objcopy -O binary --only-section=.cxx_throw_import $< $@

$(OUT)/memcpy_import.bin: $(OUT)/wide_growth_runtime.elf
	objcopy -O binary --only-section=.memcpy_import $< $@

test-wide-growth-runtime: $(OUT)/reriff-match $(OUT)/wide_grow_handler.bin $(OUT)/cxx_frame_handler_import.bin $(OUT)/cxx_throw_import.bin $(OUT)/memcpy_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-grow-handler $(OUT)/wide_grow_handler.bin $(OUT)/wide-grow-handler-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" cxx-frame-handler-import $(OUT)/cxx_frame_handler_import.bin $(OUT)/cxx-frame-handler-import-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" cxx-throw-import $(OUT)/cxx_throw_import.bin $(OUT)/cxx-throw-import-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" memcpy-import $(OUT)/memcpy_import.bin $(OUT)/memcpy-import-comparison.json

test-recovered: test-wide-growth-runtime
.PHONY: test-wide-growth-runtime

$(OUT)/wide_reserve.bin: native/wide_reserve.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_reserve.o
	ld -m elf_i386 -Ttext=0x44fc30 -e original_wide_reserve $(OUT)/wide_reserve.o -o $(OUT)/wide_reserve.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_reserve.elf $@

$(OUT)/wide_append_range.bin: native/wide_append_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_append_range.o
	ld -m elf_i386 -Ttext=0x44ff80 -e original_wide_append_range $(OUT)/wide_append_range.o -o $(OUT)/wide_append_range.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_append_range.elf $@

$(OUT)/wide_append_range_handler.bin: native/wide_append_range_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_append_range_handler.o
	ld -m elf_i386 -Ttext=0x8ffa20 -e original_wide_append_range_handler $(OUT)/wide_append_range_handler.o -o $(OUT)/wide_append_range_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_append_range_handler.elf $@

test-wide-range: $(OUT)/reriff-match $(OUT)/wide_reserve.bin $(OUT)/wide_append_range.bin $(OUT)/wide_append_range_handler.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-reserve $(OUT)/wide_reserve.bin $(OUT)/wide_reserve-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-append-range $(OUT)/wide_append_range.bin $(OUT)/wide_append_range-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" wide-append-range-handler $(OUT)/wide_append_range_handler.bin $(OUT)/wide_append_range_handler-comparison.json

test-recovered: test-wide-range
.PHONY: test-wide-range

$(OUT)/lifetime_adjust16.bin: native/lifetime_adjust16.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/lifetime_adjust16.o
	ld -m elf_i386 -Ttext=0x45004f -e original_lifetime_adjust16 $(OUT)/lifetime_adjust16.o -o $(OUT)/lifetime_adjust16.elf
	objcopy -O binary --only-section=.text $(OUT)/lifetime_adjust16.elf $@

$(OUT)/lifetime_adjust20.bin: native/lifetime_adjust20.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/lifetime_adjust20.o
	ld -m elf_i386 -Ttext=0x450057 -e original_lifetime_adjust20 $(OUT)/lifetime_adjust20.o -o $(OUT)/lifetime_adjust20.elf
	objcopy -O binary --only-section=.text $(OUT)/lifetime_adjust20.elf $@

$(OUT)/lifetime_dispose.bin: native/lifetime_dispose.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/lifetime_dispose.o
	ld -m elf_i386 -Ttext=0x44eae0 -e original_lifetime_dispose $(OUT)/lifetime_dispose.o -o $(OUT)/lifetime_dispose.elf
	objcopy -O binary --only-section=.text $(OUT)/lifetime_dispose.elf $@

$(OUT)/lifetime_destruct.bin: native/lifetime_destruct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/lifetime_destruct.o
	ld -m elf_i386 -Ttext=0x44eb10 -e original_lifetime_destruct $(OUT)/lifetime_destruct.o -o $(OUT)/lifetime_destruct.elf
	objcopy -O binary --only-section=.text $(OUT)/lifetime_destruct.elf $@

test-lifetime: $(OUT)/reriff-match $(OUT)/lifetime_adjust16.bin $(OUT)/lifetime_adjust20.bin $(OUT)/lifetime_dispose.bin $(OUT)/lifetime_destruct.bin
	$(OUT)/reriff-match native-check "$(GAME)" lifetime-adjust16 $(OUT)/lifetime_adjust16.bin $(OUT)/lifetime-adjust16-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" lifetime-adjust20 $(OUT)/lifetime_adjust20.bin $(OUT)/lifetime-adjust20-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" lifetime-dispose $(OUT)/lifetime_dispose.bin $(OUT)/lifetime-dispose-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" lifetime-destruct $(OUT)/lifetime_destruct.bin $(OUT)/lifetime-destruct-comparison.json

test-recovered: test-lifetime
.PHONY: test-lifetime

$(OUT)/ui_matrix_scale.bin: native/ui_matrix_scale.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/ui_matrix_scale.o
	ld -m elf_i386 -Ttext=0x00458810 -e original_ui_matrix_scale $(OUT)/ui_matrix_scale.o -o $(OUT)/ui_matrix_scale.elf
	objcopy -O binary --only-section=.text $(OUT)/ui_matrix_scale.elf $@

test-ui-matrix-scale: $(OUT)/reriff-match $(OUT)/ui_matrix_scale.bin
	$(OUT)/reriff-match native-check "$(GAME)" ui-matrix-scale $(OUT)/ui_matrix_scale.bin $(OUT)/ui-matrix-scale-comparison.json

test-recovered: test-ui-matrix-scale
.PHONY: test-ui-matrix-scale

$(OUT)/member_cleanup.bin: native/member_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/member_cleanup.o
	ld -m elf_i386 -Ttext=0x48d800 -e original_member_cleanup $(OUT)/member_cleanup.o -o $(OUT)/member_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/member_cleanup.elf $@

$(OUT)/narrow_range_destroy.bin: native/narrow_range_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_range_destroy.o
	ld -m elf_i386 -Ttext=0x4268f0 -e original_narrow_range_destroy $(OUT)/narrow_range_destroy.o -o $(OUT)/narrow_range_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_range_destroy.elf $@

test-cleanup-dependencies: $(OUT)/reriff-match $(OUT)/member_cleanup.bin $(OUT)/narrow_range_destroy.bin
	$(OUT)/reriff-match native-check "$(GAME)" member-cleanup $(OUT)/member_cleanup.bin $(OUT)/member-cleanup-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-range-destroy $(OUT)/narrow_range_destroy.bin $(OUT)/narrow-range-destroy-comparison.json

test-recovered: test-cleanup-dependencies
.PHONY: test-cleanup-dependencies

$(OUT)/decode_worker_ctor.bin: native/decode_worker_ctor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/decode_worker_ctor.o
	ld -m elf_i386 -Ttext=0x48d6e0 -e original_decode_worker_ctor $(OUT)/decode_worker_ctor.o -o $(OUT)/decode_worker_ctor.elf
	objcopy -O binary --only-section=.text $(OUT)/decode_worker_ctor.elf $@

$(OUT)/decode_worker_dispatch.bin: native/decode_worker_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/decode_worker_dispatch.o
	ld -m elf_i386 -Ttext=0x48d9c0 -e original_decode_worker_dispatch $(OUT)/decode_worker_dispatch.o -o $(OUT)/decode_worker_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/decode_worker_dispatch.elf $@

test-decode-worker: $(OUT)/reriff-match $(OUT)/decode_worker_ctor.bin $(OUT)/decode_worker_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" decode-worker-ctor $(OUT)/decode_worker_ctor.bin $(OUT)/decode-worker-ctor-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" decode-worker-dispatch $(OUT)/decode_worker_dispatch.bin $(OUT)/decode-worker-dispatch-comparison.json

test-recovered: test-decode-worker
.PHONY: test-decode-worker

$(OUT)/decode_request_prepare.bin: native/decode_request_prepare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/decode_request_prepare.o
	ld -m elf_i386 -Ttext=0x48d870 -e original_decode_request_prepare $(OUT)/decode_request_prepare.o -o $(OUT)/decode_request_prepare.elf
	objcopy -O binary --only-section=.text $(OUT)/decode_request_prepare.elf $@

$(OUT)/decode_request_unwind.bin: native/decode_request_unwind.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/decode_request_unwind.o
	ld -m elf_i386 -Ttext=0x901770 -e original_decode_request_unwind $(OUT)/decode_request_unwind.o -o $(OUT)/decode_request_unwind.elf
	objcopy -O binary --only-section=.text $(OUT)/decode_request_unwind.elf $@

$(OUT)/decode_request_handler.bin: native/decode_request_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/decode_request_handler.o
	ld -m elf_i386 -Ttext=0x901778 -e original_decode_request_handler $(OUT)/decode_request_handler.o -o $(OUT)/decode_request_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/decode_request_handler.elf $@

$(OUT)/resource_reference_release.bin: native/resource_reference_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_reference_release.o
	ld -m elf_i386 -Ttext=0x41cd10 -e original_resource_reference_release $(OUT)/resource_reference_release.o -o $(OUT)/resource_reference_release.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_reference_release.elf $@

test-decode-request: $(OUT)/reriff-match $(OUT)/decode_request_prepare.bin $(OUT)/decode_request_unwind.bin $(OUT)/decode_request_handler.bin $(OUT)/resource_reference_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" decode-request-prepare $(OUT)/decode_request_prepare.bin $(OUT)/decode-request-prepare-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" decode-request-unwind $(OUT)/decode_request_unwind.bin $(OUT)/decode-request-unwind-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" decode-request-handler $(OUT)/decode_request_handler.bin $(OUT)/decode-request-handler-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" resource-reference-release $(OUT)/resource_reference_release.bin $(OUT)/resource-reference-release-comparison.json

test-recovered: test-decode-request
.PHONY: test-decode-request

$(OUT)/narrow_string_reset.bin: native/narrow_string_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_string_reset.o
	ld -m elf_i386 -Ttext=0x48d630 -e original_narrow_string_reset $(OUT)/narrow_string_reset.o -o $(OUT)/narrow_string_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_string_reset.elf $@

$(OUT)/narrow_storage_swap.bin: native/narrow_storage_swap.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_storage_swap.o
	ld -m elf_i386 -Ttext=0x451b60 -e original_narrow_storage_swap $(OUT)/narrow_storage_swap.o -o $(OUT)/narrow_storage_swap.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_storage_swap.elf $@

$(OUT)/narrow_inline_swap.bin: native/narrow_inline_swap.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_inline_swap.o
	ld -m elf_i386 -Ttext=0x451d10 -e original_narrow_inline_swap $(OUT)/narrow_inline_swap.o -o $(OUT)/narrow_inline_swap.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_inline_swap.elf $@

$(OUT)/narrow_reset_handler.bin: native/narrow_reset_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_reset_handler.o
	ld -m elf_i386 -Ttext=0x901748 -e original_narrow_reset_handler $(OUT)/narrow_reset_handler.o -o $(OUT)/narrow_reset_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_reset_handler.elf $@

test-narrow-reset: $(OUT)/reriff-match $(OUT)/narrow_string_reset.bin $(OUT)/narrow_storage_swap.bin $(OUT)/narrow_inline_swap.bin $(OUT)/narrow_reset_handler.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-string-reset $(OUT)/narrow_string_reset.bin $(OUT)/narrow-string-reset-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-storage-swap $(OUT)/narrow_storage_swap.bin $(OUT)/narrow-storage-swap-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-inline-swap $(OUT)/narrow_inline_swap.bin $(OUT)/narrow-inline-swap-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-reset-handler $(OUT)/narrow_reset_handler.bin $(OUT)/narrow-reset-handler-comparison.json

test-recovered: test-narrow-reset
.PHONY: test-narrow-reset

$(OUT)/narrow_destroy.bin: native/narrow_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_destroy.o
	ld -m elf_i386 -Ttext=0x415b60 -e original_narrow_destroy $(OUT)/narrow_destroy.o -o $(OUT)/narrow_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_destroy.elf $@

$(OUT)/narrow_reset_unwind.bin: native/narrow_reset_unwind.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_reset_unwind.o
	ld -m elf_i386 -Ttext=0x901740 -e original_narrow_reset_unwind $(OUT)/narrow_reset_unwind.o -o $(OUT)/narrow_reset_unwind.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_reset_unwind.elf $@

$(OUT)/narrow_assign_substring.bin: native/narrow_assign_substring.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_assign_substring.o
	ld -m elf_i386 -Ttext=0x415fe0 -e original_narrow_assign_substring $(OUT)/narrow_assign_substring.o -o $(OUT)/narrow_assign_substring.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_assign_substring.elf $@

test-narrow-dependencies: $(OUT)/reriff-match $(OUT)/narrow_destroy.bin $(OUT)/narrow_reset_unwind.bin $(OUT)/narrow_assign_substring.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-destroy $(OUT)/narrow_destroy.bin $(OUT)/narrow-destroy-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-reset-unwind $(OUT)/narrow_reset_unwind.bin $(OUT)/narrow-reset-unwind-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-assign-substring $(OUT)/narrow_assign_substring.bin $(OUT)/narrow-assign-substring-comparison.json

test-recovered: test-narrow-dependencies
.PHONY: test-narrow-dependencies

$(OUT)/narrow_erase.bin: native/narrow_erase.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_erase.o
	ld -m elf_i386 -Ttext=0x416660 -e original_narrow_erase $(OUT)/narrow_erase.o -o $(OUT)/narrow_erase.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_erase.elf $@

$(OUT)/narrow_grow.bin: native/narrow_grow.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_grow.o
	ld -m elf_i386 -Ttext=0x416890 -e original_narrow_grow $(OUT)/narrow_grow.o -o $(OUT)/narrow_grow.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_grow.elf $@

$(OUT)/narrow_handler.bin: native/narrow_handler.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_handler.o
	ld -m elf_i386 -Ttext=0x8fd780 -e original_narrow_handler $(OUT)/narrow_handler.o -o $(OUT)/narrow_handler.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_handler.elf $@

test-narrow-growth: $(OUT)/reriff-match $(OUT)/narrow_erase.bin $(OUT)/narrow_grow.bin $(OUT)/narrow_handler.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-erase $(OUT)/narrow_erase.bin $(OUT)/narrow-erase-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-grow $(OUT)/narrow_grow.bin $(OUT)/narrow-grow-comparison.json
	$(OUT)/reriff-match native-check "$(GAME)" narrow-handler $(OUT)/narrow_handler.bin $(OUT)/narrow-handler-comparison.json

test-recovered: test-narrow-growth
.PHONY: test-narrow-growth

# Reviewed cycle reference: narrow-assign-terminated (assembly evidence only).
$(OUT)/narrow_assign_terminated.bin: native/narrow_assign_terminated.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_assign_terminated.o
	ld -m elf_i386 -Ttext=0x415b90 -e original_narrow_assign_terminated $(OUT)/narrow_assign_terminated.o -o $(OUT)/narrow_assign_terminated.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_assign_terminated.elf $@

test-cycle-narrow-assign-terminated: $(OUT)/reriff-match $(OUT)/narrow_assign_terminated.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-assign-terminated $(OUT)/narrow_assign_terminated.bin $(OUT)/narrow-assign-terminated-comparison.json

test-recovered: test-cycle-narrow-assign-terminated
.PHONY: test-cycle-narrow-assign-terminated

# Reviewed cycle reference: narrow-assign-range (assembly evidence only).
$(OUT)/narrow_assign_range.bin: native/narrow_assign_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_assign_range.o
	ld -m elf_i386 -Ttext=0x416520 -e original_narrow_assign_range $(OUT)/narrow_assign_range.o -o $(OUT)/narrow_assign_range.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_assign_range.elf $@

test-cycle-narrow-assign-range: $(OUT)/reriff-match $(OUT)/narrow_assign_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-assign-range $(OUT)/narrow_assign_range.bin $(OUT)/narrow-assign-range-comparison.json

test-recovered: test-cycle-narrow-assign-range
.PHONY: test-cycle-narrow-assign-range

# Reviewed cycle reference: narrow-append-terminated (assembly evidence only).
$(OUT)/narrow_append_terminated.bin: native/narrow_append_terminated.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_append_terminated.o
	ld -m elf_i386 -Ttext=0x441f70 -e original_narrow_append_terminated $(OUT)/narrow_append_terminated.o -o $(OUT)/narrow_append_terminated.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_append_terminated.elf $@

test-cycle-narrow-append-terminated: $(OUT)/reriff-match $(OUT)/narrow_append_terminated.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-append-terminated $(OUT)/narrow_append_terminated.bin $(OUT)/narrow-append-terminated-comparison.json

test-recovered: test-cycle-narrow-append-terminated
.PHONY: test-cycle-narrow-append-terminated

# Reviewed cycle reference: stack-probe (assembly evidence only).
$(OUT)/stack_probe.bin: native/stack_probe.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/stack_probe.o
	ld -m elf_i386 -Ttext=0x8f9800 -e original_stack_probe $(OUT)/stack_probe.o -o $(OUT)/stack_probe.elf
	objcopy -O binary --only-section=.text $(OUT)/stack_probe.elf $@

test-cycle-stack-probe: $(OUT)/reriff-match $(OUT)/stack_probe.bin
	$(OUT)/reriff-match native-check "$(GAME)" stack-probe $(OUT)/stack_probe.bin $(OUT)/stack-probe-comparison.json

test-recovered: test-cycle-stack-probe
.PHONY: test-cycle-stack-probe

# Reviewed cycle reference: graphics-entry-release-all (assembly evidence only).
$(OUT)/graphics_entry_release_all.bin: native/graphics_entry_release_all.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_entry_release_all.o
	ld -m elf_i386 -Ttext=0x4b2400 -e original_graphics_entry_release_all $(OUT)/graphics_entry_release_all.o -o $(OUT)/graphics_entry_release_all.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_entry_release_all.elf $@

test-cycle-graphics-entry-release-all: $(OUT)/reriff-match $(OUT)/graphics_entry_release_all.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-entry-release-all $(OUT)/graphics_entry_release_all.bin $(OUT)/graphics-entry-release-all-comparison.json

test-recovered: test-cycle-graphics-entry-release-all
.PHONY: test-cycle-graphics-entry-release-all

# Reviewed cycle reference: graphics-entry-release (assembly evidence only).
$(OUT)/graphics_entry_release.bin: native/graphics_entry_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_entry_release.o
	ld -m elf_i386 -Ttext=0x49ca20 -e original_graphics_entry_release $(OUT)/graphics_entry_release.o -o $(OUT)/graphics_entry_release.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_entry_release.elf $@

test-cycle-graphics-entry-release: $(OUT)/reriff-match $(OUT)/graphics_entry_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-entry-release $(OUT)/graphics_entry_release.bin $(OUT)/graphics-entry-release-comparison.json

test-recovered: test-cycle-graphics-entry-release
.PHONY: test-cycle-graphics-entry-release

# Reviewed cycle reference: graphics-table-dispose-438 (assembly evidence only).
$(OUT)/graphics_table_dispose_438.bin: native/graphics_table_dispose_438.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_table_dispose_438.o
	ld -m elf_i386 -Ttext=0x4b2ba0 -e original_graphics_table_dispose_438 $(OUT)/graphics_table_dispose_438.o -o $(OUT)/graphics_table_dispose_438.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_table_dispose_438.elf $@

test-cycle-graphics-table-dispose-438: $(OUT)/reriff-match $(OUT)/graphics_table_dispose_438.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-table-dispose-438 $(OUT)/graphics_table_dispose_438.bin $(OUT)/graphics-table-dispose-438-comparison.json

test-recovered: test-cycle-graphics-table-dispose-438
.PHONY: test-cycle-graphics-table-dispose-438

# Reviewed cycle reference: buffer-release (assembly evidence only).
$(OUT)/buffer_release.bin: native/buffer_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/buffer_release.o
	ld -m elf_i386 -Ttext=0x542a40 -e original_buffer_release $(OUT)/buffer_release.o -o $(OUT)/buffer_release.elf
	objcopy -O binary --only-section=.text $(OUT)/buffer_release.elf $@

test-cycle-buffer-release: $(OUT)/reriff-match $(OUT)/buffer_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" buffer-release $(OUT)/buffer_release.bin $(OUT)/buffer-release-comparison.json

test-recovered: test-cycle-buffer-release
.PHONY: test-cycle-buffer-release

# Reviewed cycle reference: graphics-table-dispose-430 (assembly evidence only).
$(OUT)/graphics_table_dispose_430.bin: native/graphics_table_dispose_430.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_table_dispose_430.o
	ld -m elf_i386 -Ttext=0x4b2c00 -e original_graphics_table_dispose_430 $(OUT)/graphics_table_dispose_430.o -o $(OUT)/graphics_table_dispose_430.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_table_dispose_430.elf $@

test-cycle-graphics-table-dispose-430: $(OUT)/reriff-match $(OUT)/graphics_table_dispose_430.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-table-dispose-430 $(OUT)/graphics_table_dispose_430.bin $(OUT)/graphics-table-dispose-430-comparison.json

test-recovered: test-cycle-graphics-table-dispose-430
.PHONY: test-cycle-graphics-table-dispose-430

# Reviewed cycle reference: graphics-range-destroy-430 (assembly evidence only).
$(OUT)/graphics_range_destroy_430.bin: native/graphics_range_destroy_430.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_range_destroy_430.o
	ld -m elf_i386 -Ttext=0x49d820 -e original_graphics_range_destroy_430 $(OUT)/graphics_range_destroy_430.o -o $(OUT)/graphics_range_destroy_430.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_range_destroy_430.elf $@

test-cycle-graphics-range-destroy-430: $(OUT)/reriff-match $(OUT)/graphics_range_destroy_430.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-range-destroy-430 $(OUT)/graphics_range_destroy_430.bin $(OUT)/graphics-range-destroy-430-comparison.json

test-recovered: test-cycle-graphics-range-destroy-430
.PHONY: test-cycle-graphics-range-destroy-430

# Reviewed cycle reference: graphics-range-destroy-438 (assembly evidence only).
$(OUT)/graphics_range_destroy_438.bin: native/graphics_range_destroy_438.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_range_destroy_438.o
	ld -m elf_i386 -Ttext=0x49d6b0 -e original_graphics_range_destroy_438 $(OUT)/graphics_range_destroy_438.o -o $(OUT)/graphics_range_destroy_438.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_range_destroy_438.elf $@

test-cycle-graphics-range-destroy-438: $(OUT)/reriff-match $(OUT)/graphics_range_destroy_438.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-range-destroy-438 $(OUT)/graphics_range_destroy_438.bin $(OUT)/graphics-range-destroy-438-comparison.json

test-recovered: test-cycle-graphics-range-destroy-438
.PHONY: test-cycle-graphics-range-destroy-438

# Reviewed cycle reference: resource-manager-construct (assembly evidence only).
$(OUT)/resource_manager_construct.bin: native/resource_manager_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_manager_construct.o
	ld -m elf_i386 -Ttext=0x417810 -e original_resource_manager_construct $(OUT)/resource_manager_construct.o -o $(OUT)/resource_manager_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_manager_construct.elf $@

test-cycle-resource-manager-construct: $(OUT)/reriff-match $(OUT)/resource_manager_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-manager-construct $(OUT)/resource_manager_construct.bin $(OUT)/resource-manager-construct-comparison.json

test-recovered: test-cycle-resource-manager-construct
.PHONY: test-cycle-resource-manager-construct

# Reviewed cycle reference: pool-slot-release (assembly evidence only).
$(OUT)/pool_slot_release.bin: native/pool_slot_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pool_slot_release.o
	ld -m elf_i386 -Ttext=0x426be0 -e original_pool_slot_release $(OUT)/pool_slot_release.o -o $(OUT)/pool_slot_release.elf
	objcopy -O binary --only-section=.text $(OUT)/pool_slot_release.elf $@

test-cycle-pool-slot-release: $(OUT)/reriff-match $(OUT)/pool_slot_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" pool-slot-release $(OUT)/pool_slot_release.bin $(OUT)/pool-slot-release-comparison.json

test-recovered: test-cycle-pool-slot-release
.PHONY: test-cycle-pool-slot-release

# Reviewed cycle reference: pool-block-commit (assembly evidence only).
$(OUT)/pool_block_commit.bin: native/pool_block_commit.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pool_block_commit.o
	ld -m elf_i386 -Ttext=0x426af0 -e original_pool_block_commit $(OUT)/pool_block_commit.o -o $(OUT)/pool_block_commit.elf
	objcopy -O binary --only-section=.text $(OUT)/pool_block_commit.elf $@

test-cycle-pool-block-commit: $(OUT)/reriff-match $(OUT)/pool_block_commit.bin
	$(OUT)/reriff-match native-check "$(GAME)" pool-block-commit $(OUT)/pool_block_commit.bin $(OUT)/pool-block-commit-comparison.json

test-recovered: test-cycle-pool-block-commit
.PHONY: test-cycle-pool-block-commit

# Reviewed cycle reference: pool-string-allocate (assembly evidence only).
$(OUT)/pool_string_allocate.bin: native/pool_string_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pool_string_allocate.o
	ld -m elf_i386 -Ttext=0x426a30 -e original_pool_string_allocate $(OUT)/pool_string_allocate.o -o $(OUT)/pool_string_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/pool_string_allocate.elf $@

test-cycle-pool-string-allocate: $(OUT)/reriff-match $(OUT)/pool_string_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" pool-string-allocate $(OUT)/pool_string_allocate.bin $(OUT)/pool-string-allocate-comparison.json

test-recovered: test-cycle-pool-string-allocate
.PHONY: test-cycle-pool-string-allocate

# Reviewed cycle reference: memset-import (assembly evidence only).
$(OUT)/memset_import.bin: native/memset_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/memset_import.o
	ld -m elf_i386 -Ttext=0x8f8d7e -e original_memset_import $(OUT)/memset_import.o -o $(OUT)/memset_import.elf
	objcopy -O binary --only-section=.text $(OUT)/memset_import.elf $@

test-cycle-memset-import: $(OUT)/reriff-match $(OUT)/memset_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" memset-import $(OUT)/memset_import.bin $(OUT)/memset-import-comparison.json

test-recovered: test-cycle-memset-import
.PHONY: test-cycle-memset-import

# Reviewed cycle reference: operator-new-import (assembly evidence only).
$(OUT)/operator_new_import.bin: native/operator_new_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/operator_new_import.o
	ld -m elf_i386 -Ttext=0x8f8c42 -e original_operator_new_import $(OUT)/operator_new_import.o -o $(OUT)/operator_new_import.elf
	objcopy -O binary --only-section=.text $(OUT)/operator_new_import.elf $@

test-cycle-operator-new-import: $(OUT)/reriff-match $(OUT)/operator_new_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" operator-new-import $(OUT)/operator_new_import.bin $(OUT)/operator-new-import-comparison.json

test-recovered: test-cycle-operator-new-import
.PHONY: test-cycle-operator-new-import

# Reviewed cycle reference: array-new-forward (assembly evidence only).
$(OUT)/array_new_forward.bin: native/array_new_forward.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_new_forward.o
	ld -m elf_i386 -Ttext=0x8f87c8 -e original_array_new_forward $(OUT)/array_new_forward.o -o $(OUT)/array_new_forward.elf
	objcopy -O binary --only-section=.text $(OUT)/array_new_forward.elf $@

test-cycle-array-new-forward: $(OUT)/reriff-match $(OUT)/array_new_forward.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-new-forward $(OUT)/array_new_forward.bin $(OUT)/array-new-forward-comparison.json

test-recovered: test-cycle-array-new-forward
.PHONY: test-cycle-array-new-forward

# Reviewed cycle reference: abs-float (assembly evidence only).
$(OUT)/abs_float.bin: native/abs_float.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/abs_float.o
	ld -m elf_i386 -Ttext=0x426cf0 -e original_abs_float $(OUT)/abs_float.o -o $(OUT)/abs_float.elf
	objcopy -O binary --only-section=.text $(OUT)/abs_float.elf $@

test-cycle-abs-float: $(OUT)/reriff-match $(OUT)/abs_float.bin
	$(OUT)/reriff-match native-check "$(GAME)" abs-float $(OUT)/abs_float.bin $(OUT)/abs-float-comparison.json

test-recovered: test-cycle-abs-float
.PHONY: test-cycle-abs-float

# Reviewed cycle reference: window-handles-cleanup (assembly evidence only).
$(OUT)/window_handles_cleanup.bin: native/window_handles_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/window_handles_cleanup.o
	ld -m elf_i386 -Ttext=0x48c690 -e original_window_handles_cleanup $(OUT)/window_handles_cleanup.o -o $(OUT)/window_handles_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/window_handles_cleanup.elf $@

test-cycle-window-handles-cleanup: $(OUT)/reriff-match $(OUT)/window_handles_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" window-handles-cleanup $(OUT)/window_handles_cleanup.bin $(OUT)/window-handles-cleanup-comparison.json

test-recovered: test-cycle-window-handles-cleanup
.PHONY: test-cycle-window-handles-cleanup

# Reviewed cycle reference: floor-import (assembly evidence only).
$(OUT)/floor_import.bin: native/floor_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/floor_import.o
	ld -m elf_i386 -Ttext=0x8f8f40 -e original_floor_import $(OUT)/floor_import.o -o $(OUT)/floor_import.elf
	objcopy -O binary --only-section=.text $(OUT)/floor_import.elf $@

test-cycle-floor-import: $(OUT)/reriff-match $(OUT)/floor_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" floor-import $(OUT)/floor_import.bin $(OUT)/floor-import-comparison.json

test-recovered: test-cycle-floor-import
.PHONY: test-cycle-floor-import

# Reviewed cycle reference: narrow-storage-pointer (assembly evidence only).
$(OUT)/narrow_storage_pointer.bin: native/narrow_storage_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_storage_pointer.o
	ld -m elf_i386 -Ttext=0x416160 -e original_narrow_storage_pointer $(OUT)/narrow_storage_pointer.o -o $(OUT)/narrow_storage_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_storage_pointer.elf $@

test-cycle-narrow-storage-pointer: $(OUT)/reriff-match $(OUT)/narrow_storage_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-storage-pointer $(OUT)/narrow_storage_pointer.bin $(OUT)/narrow-storage-pointer-comparison.json

test-recovered: test-cycle-narrow-storage-pointer
.PHONY: test-cycle-narrow-storage-pointer

# Reviewed cycle reference: resource-handle-remove (assembly evidence only).
$(OUT)/resource_handle_remove.bin: native/resource_handle_remove.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_handle_remove.o
	ld -m elf_i386 -Ttext=0x41c090 -e original_resource_handle_remove $(OUT)/resource_handle_remove.o -o $(OUT)/resource_handle_remove.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_handle_remove.elf $@

test-cycle-resource-handle-remove: $(OUT)/reriff-match $(OUT)/resource_handle_remove.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-handle-remove $(OUT)/resource_handle_remove.bin $(OUT)/resource-handle-remove-comparison.json

test-recovered: test-cycle-resource-handle-remove
.PHONY: test-cycle-resource-handle-remove

# Reviewed cycle reference: u16-vector-append-one (assembly evidence only).
$(OUT)/u16_vector_append_one.bin: native/u16_vector_append_one.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u16_vector_append_one.o
	ld -m elf_i386 -Ttext=0x41c290 -e original_u16_vector_append_one $(OUT)/u16_vector_append_one.o -o $(OUT)/u16_vector_append_one.elf
	objcopy -O binary --only-section=.text $(OUT)/u16_vector_append_one.elf $@

test-cycle-u16-vector-append-one: $(OUT)/reriff-match $(OUT)/u16_vector_append_one.bin
	$(OUT)/reriff-match native-check "$(GAME)" u16-vector-append-one $(OUT)/u16_vector_append_one.bin $(OUT)/u16-vector-append-one-comparison.json

test-recovered: test-cycle-u16-vector-append-one
.PHONY: test-cycle-u16-vector-append-one

# Reviewed cycle reference: u16-vector-ensure-spare (assembly evidence only).
$(OUT)/u16_vector_ensure_spare.bin: native/u16_vector_ensure_spare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u16_vector_ensure_spare.o
	ld -m elf_i386 -Ttext=0x41c470 -e original_u16_vector_ensure_spare $(OUT)/u16_vector_ensure_spare.o -o $(OUT)/u16_vector_ensure_spare.elf
	objcopy -O binary --only-section=.text $(OUT)/u16_vector_ensure_spare.elf $@

test-cycle-u16-vector-ensure-spare: $(OUT)/reriff-match $(OUT)/u16_vector_ensure_spare.bin
	$(OUT)/reriff-match native-check "$(GAME)" u16-vector-ensure-spare $(OUT)/u16_vector_ensure_spare.bin $(OUT)/u16-vector-ensure-spare-comparison.json

test-recovered: test-cycle-u16-vector-ensure-spare
.PHONY: test-cycle-u16-vector-ensure-spare

# Reviewed cycle reference: u16-vector-reallocate (assembly evidence only).
$(OUT)/u16_vector_reallocate.bin: native/u16_vector_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u16_vector_reallocate.o
	ld -m elf_i386 -Ttext=0x41c560 -e original_u16_vector_reallocate $(OUT)/u16_vector_reallocate.o -o $(OUT)/u16_vector_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/u16_vector_reallocate.elf $@

test-cycle-u16-vector-reallocate: $(OUT)/reriff-match $(OUT)/u16_vector_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" u16-vector-reallocate $(OUT)/u16_vector_reallocate.bin $(OUT)/u16-vector-reallocate-comparison.json

test-recovered: test-cycle-u16-vector-reallocate
.PHONY: test-cycle-u16-vector-reallocate

# Reviewed cycle reference: operator-delete-import (assembly evidence only).
$(OUT)/operator_delete_import.bin: native/operator_delete_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/operator_delete_import.o
	ld -m elf_i386 -Ttext=0x8f8c48 -e original_operator_delete_import $(OUT)/operator_delete_import.o -o $(OUT)/operator_delete_import.elf
	objcopy -O binary --only-section=.text $(OUT)/operator_delete_import.elf $@

test-cycle-operator-delete-import: $(OUT)/reriff-match $(OUT)/operator_delete_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" operator-delete-import $(OUT)/operator_delete_import.bin $(OUT)/operator-delete-import-comparison.json

test-recovered: test-cycle-operator-delete-import
.PHONY: test-cycle-operator-delete-import

# Reviewed cycle reference: graphics-table-dispose-434 (assembly evidence only).
$(OUT)/graphics_table_dispose_434.bin: native/graphics_table_dispose_434.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_table_dispose_434.o
	ld -m elf_i386 -Ttext=0x4b2c60 -e original_graphics_table_dispose_434 $(OUT)/graphics_table_dispose_434.o -o $(OUT)/graphics_table_dispose_434.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_table_dispose_434.elf $@

test-cycle-graphics-table-dispose-434: $(OUT)/reriff-match $(OUT)/graphics_table_dispose_434.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-table-dispose-434 $(OUT)/graphics_table_dispose_434.bin $(OUT)/graphics-table-dispose-434-comparison.json

test-recovered: test-cycle-graphics-table-dispose-434
.PHONY: test-cycle-graphics-table-dispose-434

# Reviewed cycle reference: graphics-range-destroy-434 (assembly evidence only).
$(OUT)/graphics_range_destroy_434.bin: native/graphics_range_destroy_434.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_range_destroy_434.o
	ld -m elf_i386 -Ttext=0x49d990 -e original_graphics_range_destroy_434 $(OUT)/graphics_range_destroy_434.o -o $(OUT)/graphics_range_destroy_434.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_range_destroy_434.elf $@

test-cycle-graphics-range-destroy-434: $(OUT)/reriff-match $(OUT)/graphics_range_destroy_434.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-range-destroy-434 $(OUT)/graphics_range_destroy_434.bin $(OUT)/graphics-range-destroy-434-comparison.json

test-recovered: test-cycle-graphics-range-destroy-434
.PHONY: test-cycle-graphics-range-destroy-434

# Reviewed cycle reference: record24-growth-capacity (assembly evidence only).
$(OUT)/record24_growth_capacity.bin: native/record24_growth_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_growth_capacity.o
	ld -m elf_i386 -Ttext=0x543310 -e original_record24_growth_capacity $(OUT)/record24_growth_capacity.o -o $(OUT)/record24_growth_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_growth_capacity.elf $@

test-cycle-record24-growth-capacity: $(OUT)/reriff-match $(OUT)/record24_growth_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-growth-capacity $(OUT)/record24_growth_capacity.bin $(OUT)/record24-growth-capacity-comparison.json

test-recovered: test-cycle-record24-growth-capacity
.PHONY: test-cycle-record24-growth-capacity

# Reviewed cycle reference: record24-range-copy (assembly evidence only).
$(OUT)/record24_range_copy.bin: native/record24_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_range_copy.o
	ld -m elf_i386 -Ttext=0x4b3e40 -e original_record24_range_copy $(OUT)/record24_range_copy.o -o $(OUT)/record24_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_range_copy.elf $@

test-cycle-record24-range-copy: $(OUT)/reriff-match $(OUT)/record24_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-range-copy $(OUT)/record24_range_copy.bin $(OUT)/record24-range-copy-comparison.json

test-recovered: test-cycle-record24-range-copy
.PHONY: test-cycle-record24-range-copy

# Reviewed cycle reference: wide-copy-elements (assembly evidence only).
$(OUT)/wide_copy_elements.bin: native/wide_copy_elements.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_copy_elements.o
	ld -m elf_i386 -Ttext=0x44e120 -e original_wide_copy_elements $(OUT)/wide_copy_elements.o -o $(OUT)/wide_copy_elements.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_copy_elements.elf $@

test-cycle-wide-copy-elements: $(OUT)/reriff-match $(OUT)/wide_copy_elements.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-copy-elements $(OUT)/wide_copy_elements.bin $(OUT)/wide-copy-elements-comparison.json

test-recovered: test-cycle-wide-copy-elements
.PHONY: test-cycle-wide-copy-elements

# Reviewed cycle reference: record28-erase-range (assembly evidence only).
$(OUT)/record28_erase_range.bin: native/record28_erase_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record28_erase_range.o
	ld -m elf_i386 -Ttext=0x4b2480 -e original_record28_erase_range $(OUT)/record28_erase_range.o -o $(OUT)/record28_erase_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record28_erase_range.elf $@

test-cycle-record28-erase-range: $(OUT)/reriff-match $(OUT)/record28_erase_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record28-erase-range $(OUT)/record28_erase_range.bin $(OUT)/record28-erase-range-comparison.json

test-recovered: test-cycle-record28-erase-range
.PHONY: test-cycle-record28-erase-range

# Reviewed cycle reference: record24-allocate (assembly evidence only).
$(OUT)/record24_allocate.bin: native/record24_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_allocate.o
	ld -m elf_i386 -Ttext=0x543360 -e original_record24_allocate $(OUT)/record24_allocate.o -o $(OUT)/record24_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_allocate.elf $@

test-cycle-record24-allocate: $(OUT)/reriff-match $(OUT)/record24_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-allocate $(OUT)/record24_allocate.bin $(OUT)/record24-allocate-comparison.json

test-recovered: test-cycle-record24-allocate
.PHONY: test-cycle-record24-allocate

# Reviewed cycle reference: narrow-move-storage (assembly evidence only).
$(OUT)/narrow_move_storage.bin: native/narrow_move_storage.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_move_storage.o
	ld -m elf_i386 -Ttext=0x416fa0 -e original_narrow_move_storage $(OUT)/narrow_move_storage.o -o $(OUT)/narrow_move_storage.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_move_storage.elf $@

test-cycle-narrow-move-storage: $(OUT)/reriff-match $(OUT)/narrow_move_storage.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-move-storage $(OUT)/narrow_move_storage.bin $(OUT)/narrow-move-storage-comparison.json

test-recovered: test-cycle-narrow-move-storage
.PHONY: test-cycle-narrow-move-storage

# Reviewed cycle reference: array-delete-import (assembly evidence only).
$(OUT)/array_delete_import.bin: native/array_delete_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_delete_import.o
	ld -m elf_i386 -Ttext=0x8f8d54 -e original_array_delete_import $(OUT)/array_delete_import.o -o $(OUT)/array_delete_import.elf
	objcopy -O binary --only-section=.text $(OUT)/array_delete_import.elf $@

test-cycle-array-delete-import: $(OUT)/reriff-match $(OUT)/array_delete_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-delete-import $(OUT)/array_delete_import.bin $(OUT)/array-delete-import-comparison.json

test-recovered: test-cycle-array-delete-import
.PHONY: test-cycle-array-delete-import

# Reviewed cycle reference: shader-grid-notify-slot12 (assembly evidence only).
$(OUT)/shader_grid_notify_slot12.bin: native/shader_grid_notify_slot12.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_grid_notify_slot12.o
	ld -m elf_i386 -Ttext=0x52f560 -e original_shader_grid_notify_slot12 $(OUT)/shader_grid_notify_slot12.o -o $(OUT)/shader_grid_notify_slot12.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_grid_notify_slot12.elf $@

test-cycle-shader-grid-notify-slot12: $(OUT)/reriff-match $(OUT)/shader_grid_notify_slot12.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-grid-notify-slot12 $(OUT)/shader_grid_notify_slot12.bin $(OUT)/shader-grid-notify-slot12-comparison.json

test-recovered: test-cycle-shader-grid-notify-slot12
.PHONY: test-cycle-shader-grid-notify-slot12

# Reviewed cycle reference: vector3-construct-refs (assembly evidence only).
$(OUT)/vector3_construct_refs.bin: native/vector3_construct_refs.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/vector3_construct_refs.o
	ld -m elf_i386 -Ttext=0x426f00 -e original_vector3_construct_refs $(OUT)/vector3_construct_refs.o -o $(OUT)/vector3_construct_refs.elf
	objcopy -O binary --only-section=.text $(OUT)/vector3_construct_refs.elf $@

test-cycle-vector3-construct-refs: $(OUT)/reriff-match $(OUT)/vector3_construct_refs.bin
	$(OUT)/reriff-match native-check "$(GAME)" vector3-construct-refs $(OUT)/vector3_construct_refs.bin $(OUT)/vector3-construct-refs-comparison.json

test-recovered: test-cycle-vector3-construct-refs
.PHONY: test-cycle-vector3-construct-refs

# Reviewed cycle reference: shutdown-buffer-records-destroy (assembly evidence only).
$(OUT)/shutdown_buffer_records_destroy.bin: native/shutdown_buffer_records_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shutdown_buffer_records_destroy.o
	ld -m elf_i386 -Ttext=0x49fbd0 -e original_shutdown_buffer_records_destroy $(OUT)/shutdown_buffer_records_destroy.o -o $(OUT)/shutdown_buffer_records_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/shutdown_buffer_records_destroy.elf $@

test-cycle-shutdown-buffer-records-destroy: $(OUT)/reriff-match $(OUT)/shutdown_buffer_records_destroy.bin
	$(OUT)/reriff-match native-check "$(GAME)" shutdown-buffer-records-destroy $(OUT)/shutdown_buffer_records_destroy.bin $(OUT)/shutdown-buffer-records-destroy-comparison.json

test-recovered: test-cycle-shutdown-buffer-records-destroy
.PHONY: test-cycle-shutdown-buffer-records-destroy

# Reviewed cycle reference: narrow-end-pointer (assembly evidence only).
$(OUT)/narrow_end_pointer.bin: native/narrow_end_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_end_pointer.o
	ld -m elf_i386 -Ttext=0x440a60 -e original_narrow_end_pointer $(OUT)/narrow_end_pointer.o -o $(OUT)/narrow_end_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_end_pointer.elf $@

test-cycle-narrow-end-pointer: $(OUT)/reriff-match $(OUT)/narrow_end_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-end-pointer $(OUT)/narrow_end_pointer.bin $(OUT)/narrow-end-pointer-comparison.json

test-recovered: test-cycle-narrow-end-pointer
.PHONY: test-cycle-narrow-end-pointer

# Reviewed cycle reference: wide-move-elements (assembly evidence only).
$(OUT)/wide_move_elements.bin: native/wide_move_elements.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_move_elements.o
	ld -m elf_i386 -Ttext=0x44e140 -e original_wide_move_elements $(OUT)/wide_move_elements.o -o $(OUT)/wide_move_elements.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_move_elements.elf $@

test-cycle-wide-move-elements: $(OUT)/reriff-match $(OUT)/wide_move_elements.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-move-elements $(OUT)/wide_move_elements.bin $(OUT)/wide-move-elements-comparison.json

test-recovered: test-cycle-wide-move-elements
.PHONY: test-cycle-wide-move-elements

# Reviewed cycle reference: record44-copy-range (assembly evidence only).
$(OUT)/record44_copy_range.bin: native/record44_copy_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record44_copy_range.o
	ld -m elf_i386 -Ttext=0x4b31e0 -e original_record44_copy_range $(OUT)/record44_copy_range.o -o $(OUT)/record44_copy_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record44_copy_range.elf $@

test-cycle-record44-copy-range: $(OUT)/reriff-match $(OUT)/record44_copy_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record44-copy-range $(OUT)/record44_copy_range.bin $(OUT)/record44-copy-range-comparison.json

test-recovered: test-cycle-record44-copy-range
.PHONY: test-cycle-record44-copy-range

# Reviewed cycle reference: narrow-append-range (assembly evidence only).
$(OUT)/narrow_append_range.bin: native/narrow_append_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_append_range.o
	ld -m elf_i386 -Ttext=0x442170 -e original_narrow_append_range $(OUT)/narrow_append_range.o -o $(OUT)/narrow_append_range.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_append_range.elf $@

test-cycle-narrow-append-range: $(OUT)/reriff-match $(OUT)/narrow_append_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-append-range $(OUT)/narrow_append_range.bin $(OUT)/narrow-append-range-comparison.json

test-recovered: test-cycle-narrow-append-range
.PHONY: test-cycle-narrow-append-range

# Reviewed cycle reference: narrow-prepare-capacity (assembly evidence only).
$(OUT)/narrow_prepare_capacity.bin: native/narrow_prepare_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_prepare_capacity.o
	ld -m elf_i386 -Ttext=0x416730 -e original_narrow_prepare_capacity $(OUT)/narrow_prepare_capacity.o -o $(OUT)/narrow_prepare_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_prepare_capacity.elf $@

test-cycle-narrow-prepare-capacity: $(OUT)/reriff-match $(OUT)/narrow_prepare_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-prepare-capacity $(OUT)/narrow_prepare_capacity.bin $(OUT)/narrow-prepare-capacity-comparison.json

test-recovered: test-cycle-narrow-prepare-capacity
.PHONY: test-cycle-narrow-prepare-capacity

# Reviewed cycle reference: unsigned64-to-double (assembly evidence only).
$(OUT)/unsigned64_to_double.bin: native/unsigned64_to_double.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/unsigned64_to_double.o
	ld -m elf_i386 -Ttext=0x8f925e -e original_unsigned64_to_double $(OUT)/unsigned64_to_double.o -o $(OUT)/unsigned64_to_double.elf
	objcopy -O binary --only-section=.text $(OUT)/unsigned64_to_double.elf $@

test-cycle-unsigned64-to-double: $(OUT)/reriff-match $(OUT)/unsigned64_to_double.bin
	$(OUT)/reriff-match native-check "$(GAME)" unsigned64-to-double $(OUT)/unsigned64_to_double.bin $(OUT)/unsigned64-to-double-comparison.json

test-recovered: test-cycle-unsigned64-to-double
.PHONY: test-cycle-unsigned64-to-double

# Reviewed cycle reference: worker-state-construct (assembly evidence only).
$(OUT)/worker_state_construct.bin: native/worker_state_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_state_construct.o
	ld -m elf_i386 -Ttext=0x4242e0 -e original_worker_state_construct $(OUT)/worker_state_construct.o -o $(OUT)/worker_state_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_state_construct.elf $@

test-cycle-worker-state-construct: $(OUT)/reriff-match $(OUT)/worker_state_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-state-construct $(OUT)/worker_state_construct.bin $(OUT)/worker-state-construct-comparison.json

test-recovered: test-cycle-worker-state-construct
.PHONY: test-cycle-worker-state-construct

# Reviewed cycle reference: memmove-import (assembly evidence only).
$(OUT)/memmove_import.bin: native/memmove_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/memmove_import.o
	ld -m elf_i386 -Ttext=0x8f8d4e -e original_memmove_import $(OUT)/memmove_import.o -o $(OUT)/memmove_import.elf
	objcopy -O binary --only-section=.text $(OUT)/memmove_import.elf $@

test-cycle-memmove-import: $(OUT)/reriff-match $(OUT)/memmove_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" memmove-import $(OUT)/memmove_import.bin $(OUT)/memmove-import-comparison.json

test-recovered: test-cycle-memmove-import
.PHONY: test-cycle-memmove-import

# Reviewed cycle reference: narrow-move-assign (assembly evidence only).
$(OUT)/narrow_move_assign.bin: native/narrow_move_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_move_assign.o
	ld -m elf_i386 -Ttext=0x440a20 -e original_narrow_move_assign $(OUT)/narrow_move_assign.o -o $(OUT)/narrow_move_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_move_assign.elf $@

test-cycle-narrow-move-assign: $(OUT)/reriff-match $(OUT)/narrow_move_assign.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-move-assign $(OUT)/narrow_move_assign.bin $(OUT)/narrow-move-assign-comparison.json

test-recovered: test-cycle-narrow-move-assign
.PHONY: test-cycle-narrow-move-assign

# Reviewed cycle reference: signed64-to-double (assembly evidence only).
$(OUT)/signed64_to_double.bin: native/signed64_to_double.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/signed64_to_double.o
	ld -m elf_i386 -Ttext=0x8f92ef -e original_signed64_to_double $(OUT)/signed64_to_double.o -o $(OUT)/signed64_to_double.elf
	objcopy -O binary --only-section=.text $(OUT)/signed64_to_double.elf $@

test-cycle-signed64-to-double: $(OUT)/reriff-match $(OUT)/signed64_to_double.bin
	$(OUT)/reriff-match native-check "$(GAME)" signed64-to-double $(OUT)/signed64_to_double.bin $(OUT)/signed64-to-double-comparison.json

test-recovered: test-cycle-signed64-to-double
.PHONY: test-cycle-signed64-to-double

# Reviewed cycle reference: record20-range-copy (assembly evidence only).
$(OUT)/record20_range_copy.bin: native/record20_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record20_range_copy.o
	ld -m elf_i386 -Ttext=0x4b3e80 -e original_record20_range_copy $(OUT)/record20_range_copy.o -o $(OUT)/record20_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record20_range_copy.elf $@

test-cycle-record20-range-copy: $(OUT)/reriff-match $(OUT)/record20_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record20-range-copy $(OUT)/record20_range_copy.bin $(OUT)/record20-range-copy-comparison.json

test-recovered: test-cycle-record20-range-copy
.PHONY: test-cycle-record20-range-copy

# Reviewed cycle reference: narrow-set-length (assembly evidence only).
$(OUT)/narrow_set_length.bin: native/narrow_set_length.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_set_length.o
	ld -m elf_i386 -Ttext=0x416700 -e original_narrow_set_length $(OUT)/narrow_set_length.o -o $(OUT)/narrow_set_length.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_set_length.elf $@

test-cycle-narrow-set-length: $(OUT)/reriff-match $(OUT)/narrow_set_length.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-set-length $(OUT)/narrow_set_length.bin $(OUT)/narrow-set-length-comparison.json

test-recovered: test-cycle-narrow-set-length
.PHONY: test-cycle-narrow-set-length

# Reviewed cycle reference: ceil-import (assembly evidence only).
$(OUT)/ceil_import.bin: native/ceil_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/ceil_import.o
	ld -m elf_i386 -Ttext=0x8f8f3a -e original_ceil_import $(OUT)/ceil_import.o -o $(OUT)/ceil_import.elf
	objcopy -O binary --only-section=.text $(OUT)/ceil_import.elf $@

test-cycle-ceil-import: $(OUT)/reriff-match $(OUT)/ceil_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" ceil-import $(OUT)/ceil_import.bin $(OUT)/ceil-import-comparison.json

test-recovered: test-cycle-ceil-import
.PHONY: test-cycle-ceil-import

# Reviewed cycle reference: record16-range-copy (assembly evidence only).
$(OUT)/record16_range_copy.bin: native/record16_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record16_range_copy.o
	ld -m elf_i386 -Ttext=0x4b3df0 -e original_record16_range_copy $(OUT)/record16_range_copy.o -o $(OUT)/record16_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record16_range_copy.elf $@

test-cycle-record16-range-copy: $(OUT)/reriff-match $(OUT)/record16_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record16-range-copy $(OUT)/record16_range_copy.bin $(OUT)/record16-range-copy-comparison.json

test-recovered: test-cycle-record16-range-copy
.PHONY: test-cycle-record16-range-copy

# Reviewed cycle reference: record48-copy-retain (assembly evidence only).
$(OUT)/record48_copy_retain.bin: native/record48_copy_retain.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record48_copy_retain.o
	ld -m elf_i386 -Ttext=0x4b4310 -e original_record48_copy_retain $(OUT)/record48_copy_retain.o -o $(OUT)/record48_copy_retain.elf
	objcopy -O binary --only-section=.text $(OUT)/record48_copy_retain.elf $@

test-cycle-record48-copy-retain: $(OUT)/reriff-match $(OUT)/record48_copy_retain.bin
	$(OUT)/reriff-match native-check "$(GAME)" record48-copy-retain $(OUT)/record48_copy_retain.bin $(OUT)/record48-copy-retain-comparison.json

test-recovered: test-cycle-record48-copy-retain
.PHONY: test-cycle-record48-copy-retain

# Reviewed cycle reference: graphics-table-dispose-42c (assembly evidence only).
$(OUT)/graphics_table_dispose_42c.bin: native/graphics_table_dispose_42c.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_table_dispose_42c.o
	ld -m elf_i386 -Ttext=0x4b2cc0 -e original_graphics_table_dispose_42c $(OUT)/graphics_table_dispose_42c.o -o $(OUT)/graphics_table_dispose_42c.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_table_dispose_42c.elf $@

test-cycle-graphics-table-dispose-42c: $(OUT)/reriff-match $(OUT)/graphics_table_dispose_42c.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-table-dispose-42c $(OUT)/graphics_table_dispose_42c.bin $(OUT)/graphics-table-dispose-42c-comparison.json

test-recovered: test-cycle-graphics-table-dispose-42c
.PHONY: test-cycle-graphics-table-dispose-42c

# Reviewed cycle reference: sse2-sqrt-precise-import (assembly evidence only).
$(OUT)/sse2_sqrt_precise_import.bin: native/sse2_sqrt_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_sqrt_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8d60 -e original_sse2_sqrt_precise_import $(OUT)/sse2_sqrt_precise_import.o -o $(OUT)/sse2_sqrt_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_sqrt_precise_import.elf $@

test-cycle-sse2-sqrt-precise-import: $(OUT)/reriff-match $(OUT)/sse2_sqrt_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-sqrt-precise-import $(OUT)/sse2_sqrt_precise_import.bin $(OUT)/sse2-sqrt-precise-import-comparison.json

test-recovered: test-cycle-sse2-sqrt-precise-import
.PHONY: test-cycle-sse2-sqrt-precise-import

# Reviewed cycle reference: record24-rotate (assembly evidence only).
$(OUT)/record24_rotate.bin: native/record24_rotate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_rotate.o
	ld -m elf_i386 -Ttext=0x5434f0 -e original_record24_rotate $(OUT)/record24_rotate.o -o $(OUT)/record24_rotate.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_rotate.elf $@

test-cycle-record24-rotate: $(OUT)/reriff-match $(OUT)/record24_rotate.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-rotate $(OUT)/record24_rotate.bin $(OUT)/record24-rotate-comparison.json

test-recovered: test-cycle-record24-rotate
.PHONY: test-cycle-record24-rotate

# Reviewed cycle reference: wide-construct-terminated-register (assembly evidence only).
$(OUT)/wide_construct_terminated_register.bin: native/wide_construct_terminated_register.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/wide_construct_terminated_register.o
	ld -m elf_i386 -Ttext=0x44f490 -e original_wide_construct_terminated_register $(OUT)/wide_construct_terminated_register.o -o $(OUT)/wide_construct_terminated_register.elf
	objcopy -O binary --only-section=.text $(OUT)/wide_construct_terminated_register.elf $@

test-cycle-wide-construct-terminated-register: $(OUT)/reriff-match $(OUT)/wide_construct_terminated_register.bin
	$(OUT)/reriff-match native-check "$(GAME)" wide-construct-terminated-register $(OUT)/wide_construct_terminated_register.bin $(OUT)/wide-construct-terminated-register-comparison.json

test-recovered: test-cycle-wide-construct-terminated-register
.PHONY: test-cycle-wide-construct-terminated-register

# Reviewed cycle reference: ci-fmod-import (assembly evidence only).
$(OUT)/ci_fmod_import.bin: native/ci_fmod_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/ci_fmod_import.o
	ld -m elf_i386 -Ttext=0x8fc1a2 -e original_ci_fmod_import $(OUT)/ci_fmod_import.o -o $(OUT)/ci_fmod_import.elf
	objcopy -O binary --only-section=.text $(OUT)/ci_fmod_import.elf $@

test-cycle-ci-fmod-import: $(OUT)/reriff-match $(OUT)/ci_fmod_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" ci-fmod-import $(OUT)/ci_fmod_import.bin $(OUT)/ci-fmod-import-comparison.json

test-recovered: test-cycle-ci-fmod-import
.PHONY: test-cycle-ci-fmod-import

# Reviewed cycle reference: record24-insert-range (assembly evidence only).
$(OUT)/record24_insert_range.bin: native/record24_insert_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_insert_range.o
	ld -m elf_i386 -Ttext=0x5433a0 -e original_record24_insert_range $(OUT)/record24_insert_range.o -o $(OUT)/record24_insert_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_insert_range.elf $@

test-cycle-record24-insert-range: $(OUT)/reriff-match $(OUT)/record24_insert_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-insert-range $(OUT)/record24_insert_range.bin $(OUT)/record24-insert-range-comparison.json

test-recovered: test-cycle-record24-insert-range
.PHONY: test-cycle-record24-insert-range

# Reviewed cycle reference: resource-record24-construct (assembly evidence only).
$(OUT)/resource_record24_construct.bin: native/resource_record24_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_record24_construct.o
	ld -m elf_i386 -Ttext=0x5436c0 -e original_resource_record24_construct $(OUT)/resource_record24_construct.o -o $(OUT)/resource_record24_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_record24_construct.elf $@

test-cycle-resource-record24-construct: $(OUT)/reriff-match $(OUT)/resource_record24_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-record24-construct $(OUT)/resource_record24_construct.bin $(OUT)/resource-record24-construct-comparison.json

test-recovered: test-cycle-resource-record24-construct
.PHONY: test-cycle-resource-record24-construct

# Reviewed cycle reference: initterm-e-import (assembly evidence only).
$(OUT)/initterm_e_import.bin: native/initterm_e_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/initterm_e_import.o
	ld -m elf_i386 -Ttext=0x8f9c7c -e original_initterm_e_import $(OUT)/initterm_e_import.o -o $(OUT)/initterm_e_import.elf
	objcopy -O binary --only-section=.text $(OUT)/initterm_e_import.elf $@

test-cycle-initterm-e-import: $(OUT)/reriff-match $(OUT)/initterm_e_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" initterm-e-import $(OUT)/initterm_e_import.bin $(OUT)/initterm-e-import-comparison.json

test-recovered: test-cycle-initterm-e-import
.PHONY: test-cycle-initterm-e-import

# Reviewed cycle reference: narrow-allocate (assembly evidence only).
$(OUT)/narrow_allocate.bin: native/narrow_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_allocate.o
	ld -m elf_i386 -Ttext=0x4169f0 -e original_narrow_allocate $(OUT)/narrow_allocate.o -o $(OUT)/narrow_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_allocate.elf $@

test-cycle-narrow-allocate: $(OUT)/reriff-match $(OUT)/narrow_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-allocate $(OUT)/narrow_allocate.bin $(OUT)/narrow-allocate-comparison.json

test-recovered: test-cycle-narrow-allocate
.PHONY: test-cycle-narrow-allocate

# Reviewed cycle reference: sse-conversion-exception (assembly evidence only).
$(OUT)/sse_conversion_exception.bin: native/sse_conversion_exception.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse_conversion_exception.o
	ld -m elf_i386 -Ttext=0x8f90ed -e original_sse_conversion_exception $(OUT)/sse_conversion_exception.o -o $(OUT)/sse_conversion_exception.elf
	objcopy -O binary --only-section=.text $(OUT)/sse_conversion_exception.elf $@

test-cycle-sse-conversion-exception: $(OUT)/reriff-match $(OUT)/sse_conversion_exception.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse-conversion-exception $(OUT)/sse_conversion_exception.bin $(OUT)/sse-conversion-exception-comparison.json

test-recovered: test-cycle-sse-conversion-exception
.PHONY: test-cycle-sse-conversion-exception

# Reviewed cycle reference: sse-float-to-integer (assembly evidence only).
$(OUT)/sse_float_to_integer.bin: native/sse_float_to_integer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse_float_to_integer.o
	ld -m elf_i386 -Ttext=0x8f8f50 -e original_sse_float_to_integer $(OUT)/sse_float_to_integer.o -o $(OUT)/sse_float_to_integer.elf
	objcopy -O binary --only-section=.text $(OUT)/sse_float_to_integer.elf $@

test-cycle-sse-float-to-integer: $(OUT)/reriff-match $(OUT)/sse_float_to_integer.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse-float-to-integer $(OUT)/sse_float_to_integer.bin $(OUT)/sse-float-to-integer-comparison.json

test-recovered: test-cycle-sse-float-to-integer
.PHONY: test-cycle-sse-float-to-integer

# Reviewed cycle reference: except1-import (assembly evidence only).
$(OUT)/except1_import.bin: native/except1_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/except1_import.o
	ld -m elf_i386 -Ttext=0x8f9d1e -e original_except1_import $(OUT)/except1_import.o -o $(OUT)/except1_import.elf
	objcopy -O binary --only-section=.text $(OUT)/except1_import.elf $@

test-cycle-except1-import: $(OUT)/reriff-match $(OUT)/except1_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" except1-import $(OUT)/except1_import.bin $(OUT)/except1-import-comparison.json

test-recovered: test-cycle-except1-import
.PHONY: test-cycle-except1-import

# Reviewed cycle reference: record24-append-one (assembly evidence only).
$(OUT)/record24_append_one.bin: native/record24_append_one.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_append_one.o
	ld -m elf_i386 -Ttext=0x4b2500 -e original_record24_append_one $(OUT)/record24_append_one.o -o $(OUT)/record24_append_one.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_append_one.elf $@

test-cycle-record24-append-one: $(OUT)/reriff-match $(OUT)/record24_append_one.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-append-one $(OUT)/record24_append_one.bin $(OUT)/record24-append-one-comparison.json

test-recovered: test-cycle-record24-append-one
.PHONY: test-cycle-record24-append-one

# Reviewed cycle reference: resource-manager-flush (assembly evidence only).
$(OUT)/resource_manager_flush.bin: native/resource_manager_flush.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_manager_flush.o
	ld -m elf_i386 -Ttext=0x542f80 -e original_resource_manager_flush $(OUT)/resource_manager_flush.o -o $(OUT)/resource_manager_flush.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_manager_flush.elf $@

test-cycle-resource-manager-flush: $(OUT)/reriff-match $(OUT)/resource_manager_flush.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-manager-flush $(OUT)/resource_manager_flush.bin $(OUT)/resource-manager-flush-comparison.json

test-recovered: test-cycle-resource-manager-flush
.PHONY: test-cycle-resource-manager-flush

# Reviewed cycle reference: record48-zero-copy-construct (assembly evidence only).
$(OUT)/record48_zero_copy_construct.bin: native/record48_zero_copy_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record48_zero_copy_construct.o
	ld -m elf_i386 -Ttext=0x427010 -e original_record48_zero_copy_construct $(OUT)/record48_zero_copy_construct.o -o $(OUT)/record48_zero_copy_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/record48_zero_copy_construct.elf $@

test-cycle-record48-zero-copy-construct: $(OUT)/reriff-match $(OUT)/record48_zero_copy_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" record48-zero-copy-construct $(OUT)/record48_zero_copy_construct.bin $(OUT)/record48-zero-copy-construct-comparison.json

test-recovered: test-cycle-record48-zero-copy-construct
.PHONY: test-cycle-record48-zero-copy-construct

# Reviewed cycle reference: narrow-substring-construct (assembly evidence only).
$(OUT)/narrow_substring_construct.bin: native/narrow_substring_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_substring_construct.o
	ld -m elf_i386 -Ttext=0x440a90 -e original_narrow_substring_construct $(OUT)/narrow_substring_construct.o -o $(OUT)/narrow_substring_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_substring_construct.elf $@

test-cycle-narrow-substring-construct: $(OUT)/reriff-match $(OUT)/narrow_substring_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-substring-construct $(OUT)/narrow_substring_construct.bin $(OUT)/narrow-substring-construct-comparison.json

test-recovered: test-cycle-narrow-substring-construct
.PHONY: test-cycle-narrow-substring-construct
