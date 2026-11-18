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

# Reviewed cycle reference: byte-range-compare (assembly evidence only).
$(OUT)/byte_range_compare.bin: native/byte_range_compare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/byte_range_compare.o
	ld -m elf_i386 -Ttext=0x4225c0 -e original_byte_range_compare $(OUT)/byte_range_compare.o -o $(OUT)/byte_range_compare.elf
	objcopy -O binary --only-section=.text $(OUT)/byte_range_compare.elf $@

test-cycle-byte-range-compare: $(OUT)/reriff-match $(OUT)/byte_range_compare.bin
	$(OUT)/reriff-match native-check "$(GAME)" byte-range-compare $(OUT)/byte_range_compare.bin $(OUT)/byte-range-compare-comparison.json

test-recovered: test-cycle-byte-range-compare
.PHONY: test-cycle-byte-range-compare

# Reviewed cycle reference: narrow-find-substring (assembly evidence only).
$(OUT)/narrow_find_substring.bin: native/narrow_find_substring.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_find_substring.o
	ld -m elf_i386 -Ttext=0x440b90 -e original_narrow_find_substring $(OUT)/narrow_find_substring.o -o $(OUT)/narrow_find_substring.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_find_substring.elf $@

test-cycle-narrow-find-substring: $(OUT)/reriff-match $(OUT)/narrow_find_substring.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-find-substring $(OUT)/narrow_find_substring.bin $(OUT)/narrow-find-substring-comparison.json

test-recovered: test-cycle-narrow-find-substring
.PHONY: test-cycle-narrow-find-substring

# Reviewed cycle reference: initterm-import (assembly evidence only).
$(OUT)/initterm_import.bin: native/initterm_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/initterm_import.o
	ld -m elf_i386 -Ttext=0x8f9c82 -e original_initterm_import $(OUT)/initterm_import.o -o $(OUT)/initterm_import.elf
	objcopy -O binary --only-section=.text $(OUT)/initterm_import.elf $@

test-cycle-initterm-import: $(OUT)/reriff-match $(OUT)/initterm_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" initterm-import $(OUT)/initterm_import.bin $(OUT)/initterm-import-comparison.json

test-recovered: test-cycle-initterm-import
.PHONY: test-cycle-initterm-import

# Reviewed cycle reference: memchr-import (assembly evidence only).
$(OUT)/memchr_import.bin: native/memchr_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/memchr_import.o
	ld -m elf_i386 -Ttext=0x8f8d8a -e original_memchr_import $(OUT)/memchr_import.o -o $(OUT)/memchr_import.elf
	objcopy -O binary --only-section=.text $(OUT)/memchr_import.elf $@

test-cycle-memchr-import: $(OUT)/reriff-match $(OUT)/memchr_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" memchr-import $(OUT)/memchr_import.bin $(OUT)/memchr-import-comparison.json

test-recovered: test-cycle-memchr-import
.PHONY: test-cycle-memchr-import

# Reviewed cycle reference: device-clear-texture-cache (assembly evidence only).
$(OUT)/device_clear_texture_cache.bin: native/device_clear_texture_cache.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_clear_texture_cache.o
	ld -m elf_i386 -Ttext=0x4add20 -e original_device_clear_texture_cache $(OUT)/device_clear_texture_cache.o -o $(OUT)/device_clear_texture_cache.elf
	objcopy -O binary --only-section=.text $(OUT)/device_clear_texture_cache.elf $@

test-cycle-device-clear-texture-cache: $(OUT)/reriff-match $(OUT)/device_clear_texture_cache.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-clear-texture-cache $(OUT)/device_clear_texture_cache.bin $(OUT)/device-clear-texture-cache-comparison.json

test-recovered: test-cycle-device-clear-texture-cache
.PHONY: test-cycle-device-clear-texture-cache

# Reviewed cycle reference: narrow-construct-terminated (assembly evidence only).
$(OUT)/narrow_construct_terminated.bin: native/narrow_construct_terminated.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_construct_terminated.o
	ld -m elf_i386 -Ttext=0x415b00 -e original_narrow_construct_terminated $(OUT)/narrow_construct_terminated.o -o $(OUT)/narrow_construct_terminated.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_construct_terminated.elf $@

test-cycle-narrow-construct-terminated: $(OUT)/reriff-match $(OUT)/narrow_construct_terminated.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-construct-terminated $(OUT)/narrow_construct_terminated.bin $(OUT)/narrow-construct-terminated-comparison.json

test-recovered: test-cycle-narrow-construct-terminated
.PHONY: test-cycle-narrow-construct-terminated

# Reviewed cycle reference: device-sampler-bias-update (assembly evidence only).
$(OUT)/device_sampler_bias_update.bin: native/device_sampler_bias_update.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_sampler_bias_update.o
	ld -m elf_i386 -Ttext=0x4adb10 -e original_device_sampler_bias_update $(OUT)/device_sampler_bias_update.o -o $(OUT)/device_sampler_bias_update.elf
	objcopy -O binary --only-section=.text $(OUT)/device_sampler_bias_update.elf $@

test-cycle-device-sampler-bias-update: $(OUT)/reriff-match $(OUT)/device_sampler_bias_update.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-sampler-bias-update $(OUT)/device_sampler_bias_update.bin $(OUT)/device-sampler-bias-update-comparison.json

test-recovered: test-cycle-device-sampler-bias-update
.PHONY: test-cycle-device-sampler-bias-update

# Reviewed cycle reference: narrow-record40-range-destroy (assembly evidence only).
$(OUT)/narrow_record40_range_destroy.bin: native/narrow_record40_range_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_record40_range_destroy.o
	ld -m elf_i386 -Ttext=0x507f60 -e original_narrow_record40_range_destroy $(OUT)/narrow_record40_range_destroy.o -o $(OUT)/narrow_record40_range_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_record40_range_destroy.elf $@

test-cycle-narrow-record40-range-destroy: $(OUT)/reriff-match $(OUT)/narrow_record40_range_destroy.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-record40-range-destroy $(OUT)/narrow_record40_range_destroy.bin $(OUT)/narrow-record40-range-destroy-comparison.json

test-recovered: test-cycle-narrow-record40-range-destroy
.PHONY: test-cycle-narrow-record40-range-destroy

# Reviewed cycle reference: pool32-table-initialize (assembly evidence only).
$(OUT)/pool32_table_initialize.bin: native/pool32_table_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pool32_table_initialize.o
	ld -m elf_i386 -Ttext=0x41cd30 -e original_pool32_table_initialize $(OUT)/pool32_table_initialize.o -o $(OUT)/pool32_table_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/pool32_table_initialize.elf $@

test-cycle-pool32-table-initialize: $(OUT)/reriff-match $(OUT)/pool32_table_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" pool32-table-initialize $(OUT)/pool32_table_initialize.bin $(OUT)/pool32-table-initialize-comparison.json

test-recovered: test-cycle-pool32-table-initialize
.PHONY: test-cycle-pool32-table-initialize

# Reviewed cycle reference: sqrt-float-bridge (assembly evidence only).
$(OUT)/sqrt_float_bridge.bin: native/sqrt_float_bridge.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sqrt_float_bridge.o
	ld -m elf_i386 -Ttext=0x426d60 -e original_sqrt_float_bridge $(OUT)/sqrt_float_bridge.o -o $(OUT)/sqrt_float_bridge.elf
	objcopy -O binary --only-section=.text $(OUT)/sqrt_float_bridge.elf $@

test-cycle-sqrt-float-bridge: $(OUT)/reriff-match $(OUT)/sqrt_float_bridge.bin
	$(OUT)/reriff-match native-check "$(GAME)" sqrt-float-bridge $(OUT)/sqrt_float_bridge.bin $(OUT)/sqrt-float-bridge-comparison.json

test-recovered: test-cycle-sqrt-float-bridge
.PHONY: test-cycle-sqrt-float-bridge

# Reviewed cycle reference: tree-rightmost (assembly evidence only).
$(OUT)/tree_rightmost.bin: native/tree_rightmost.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_rightmost.o
	ld -m elf_i386 -Ttext=0x423240 -e original_tree_rightmost $(OUT)/tree_rightmost.o -o $(OUT)/tree_rightmost.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_rightmost.elf $@

test-cycle-tree-rightmost: $(OUT)/reriff-match $(OUT)/tree_rightmost.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-rightmost $(OUT)/tree_rightmost.bin $(OUT)/tree-rightmost-comparison.json

test-recovered: test-cycle-tree-rightmost
.PHONY: test-cycle-tree-rightmost

# Reviewed cycle reference: narrow-prefix-move-construct (assembly evidence only).
$(OUT)/narrow_prefix_move_construct.bin: native/narrow_prefix_move_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_prefix_move_construct.o
	ld -m elf_i386 -Ttext=0x4b2d20 -e original_narrow_prefix_move_construct $(OUT)/narrow_prefix_move_construct.o -o $(OUT)/narrow_prefix_move_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_prefix_move_construct.elf $@

test-cycle-narrow-prefix-move-construct: $(OUT)/reriff-match $(OUT)/narrow_prefix_move_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-prefix-move-construct $(OUT)/narrow_prefix_move_construct.bin $(OUT)/narrow-prefix-move-construct-comparison.json

test-recovered: test-cycle-narrow-prefix-move-construct
.PHONY: test-cycle-narrow-prefix-move-construct

# Reviewed cycle reference: narrow-fill-range (assembly evidence only).
$(OUT)/narrow_fill_range.bin: native/narrow_fill_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_fill_range.o
	ld -m elf_i386 -Ttext=0x44fae0 -e original_narrow_fill_range $(OUT)/narrow_fill_range.o -o $(OUT)/narrow_fill_range.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_fill_range.elf $@

test-cycle-narrow-fill-range: $(OUT)/reriff-match $(OUT)/narrow_fill_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-fill-range $(OUT)/narrow_fill_range.bin $(OUT)/narrow-fill-range-comparison.json

test-recovered: test-cycle-narrow-fill-range
.PHONY: test-cycle-narrow-fill-range

# Reviewed cycle reference: narrow-move-construct (assembly evidence only).
$(OUT)/narrow_move_construct.bin: native/narrow_move_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_move_construct.o
	ld -m elf_i386 -Ttext=0x416af0 -e original_narrow_move_construct $(OUT)/narrow_move_construct.o -o $(OUT)/narrow_move_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_move_construct.elf $@

test-cycle-narrow-move-construct: $(OUT)/reriff-match $(OUT)/narrow_move_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-move-construct $(OUT)/narrow_move_construct.bin $(OUT)/narrow-move-construct-comparison.json

test-recovered: test-cycle-narrow-move-construct
.PHONY: test-cycle-narrow-move-construct

# Reviewed cycle reference: tree-rotate-right (assembly evidence only).
$(OUT)/tree_rotate_right.bin: native/tree_rotate_right.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_rotate_right.o
	ld -m elf_i386 -Ttext=0x4231e0 -e original_tree_rotate_right $(OUT)/tree_rotate_right.o -o $(OUT)/tree_rotate_right.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_rotate_right.elf $@

test-cycle-tree-rotate-right: $(OUT)/reriff-match $(OUT)/tree_rotate_right.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-rotate-right $(OUT)/tree_rotate_right.bin $(OUT)/tree-rotate-right-comparison.json

test-recovered: test-cycle-tree-rotate-right
.PHONY: test-cycle-tree-rotate-right

# Reviewed cycle reference: runtime-accessor-thunk (assembly evidence only).
$(OUT)/runtime_accessor_thunk.bin: native/runtime_accessor_thunk.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/runtime_accessor_thunk.o
	ld -m elf_i386 -Ttext=0x6d86bb -e original_runtime_accessor_thunk $(OUT)/runtime_accessor_thunk.o -o $(OUT)/runtime_accessor_thunk.elf
	objcopy -O binary --only-section=.text $(OUT)/runtime_accessor_thunk.elf $@

test-cycle-runtime-accessor-thunk: $(OUT)/reriff-match $(OUT)/runtime_accessor_thunk.bin
	$(OUT)/reriff-match native-check "$(GAME)" runtime-accessor-thunk $(OUT)/runtime_accessor_thunk.bin $(OUT)/runtime-accessor-thunk-comparison.json

test-recovered: test-cycle-runtime-accessor-thunk
.PHONY: test-cycle-runtime-accessor-thunk

# Reviewed cycle reference: crt-exception-filter-thunk (assembly evidence only).
$(OUT)/crt_exception_filter_thunk.bin: native/crt_exception_filter_thunk.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_exception_filter_thunk.o
	ld -m elf_i386 -Ttext=0x8f9a16 -e original_crt_exception_filter_thunk $(OUT)/crt_exception_filter_thunk.o -o $(OUT)/crt_exception_filter_thunk.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_exception_filter_thunk.elf $@

test-cycle-crt-exception-filter-thunk: $(OUT)/reriff-match $(OUT)/crt_exception_filter_thunk.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-exception-filter-thunk $(OUT)/crt_exception_filter_thunk.bin $(OUT)/crt-exception-filter-thunk-comparison.json

test-recovered: test-cycle-crt-exception-filter-thunk
.PHONY: test-cycle-crt-exception-filter-thunk

# Reviewed cycle reference: crt-runtime-error-import (assembly evidence only).
$(OUT)/crt_runtime_error_import.bin: native/crt_runtime_error_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_runtime_error_import.o
	ld -m elf_i386 -Ttext=0x8f9a1c -e original_crt_runtime_error_import $(OUT)/crt_runtime_error_import.o -o $(OUT)/crt_runtime_error_import.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_runtime_error_import.elf $@

test-cycle-crt-runtime-error-import: $(OUT)/reriff-match $(OUT)/crt_runtime_error_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-runtime-error-import $(OUT)/crt_runtime_error_import.bin $(OUT)/crt-runtime-error-import-comparison.json

test-recovered: test-cycle-crt-runtime-error-import
.PHONY: test-cycle-crt-runtime-error-import

# Reviewed cycle reference: dynamic-cast-import (assembly evidence only).
$(OUT)/dynamic_cast_import.bin: native/dynamic_cast_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/dynamic_cast_import.o
	ld -m elf_i386 -Ttext=0x8f8d84 -e original_dynamic_cast_import $(OUT)/dynamic_cast_import.o -o $(OUT)/dynamic_cast_import.elf
	objcopy -O binary --only-section=.text $(OUT)/dynamic_cast_import.elf $@

test-cycle-dynamic-cast-import: $(OUT)/reriff-match $(OUT)/dynamic_cast_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" dynamic-cast-import $(OUT)/dynamic_cast_import.bin $(OUT)/dynamic-cast-import-comparison.json

test-recovered: test-cycle-dynamic-cast-import
.PHONY: test-cycle-dynamic-cast-import

# Reviewed cycle reference: pe-section-lookup (assembly evidence only).
$(OUT)/pe_section_lookup.bin: native/pe_section_lookup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pe_section_lookup.o
	ld -m elf_i386 -Ttext=0x8f9a30 -e original_pe_section_lookup $(OUT)/pe_section_lookup.o -o $(OUT)/pe_section_lookup.elf
	objcopy -O binary --only-section=.text $(OUT)/pe_section_lookup.elf $@

test-cycle-pe-section-lookup: $(OUT)/reriff-match $(OUT)/pe_section_lookup.bin
	$(OUT)/reriff-match native-check "$(GAME)" pe-section-lookup $(OUT)/pe_section_lookup.bin $(OUT)/pe-section-lookup-comparison.json

test-recovered: test-cycle-pe-section-lookup
.PHONY: test-cycle-pe-section-lookup

# Reviewed cycle reference: tree-rotate-left (assembly evidence only).
$(OUT)/tree_rotate_left.bin: native/tree_rotate_left.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_rotate_left.o
	ld -m elf_i386 -Ttext=0x423180 -e original_tree_rotate_left $(OUT)/tree_rotate_left.o -o $(OUT)/tree_rotate_left.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_rotate_left.elf $@

test-cycle-tree-rotate-left: $(OUT)/reriff-match $(OUT)/tree_rotate_left.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-rotate-left $(OUT)/tree_rotate_left.bin $(OUT)/tree-rotate-left-comparison.json

test-recovered: test-cycle-tree-rotate-left
.PHONY: test-cycle-tree-rotate-left

# Reviewed cycle reference: sse2-log10-precise-import (assembly evidence only).
$(OUT)/sse2_log10_precise_import.bin: native/sse2_log10_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_log10_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8f46 -e original_sse2_log10_precise_import $(OUT)/sse2_log10_precise_import.o -o $(OUT)/sse2_log10_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_log10_precise_import.elf $@

test-cycle-sse2-log10-precise-import: $(OUT)/reriff-match $(OUT)/sse2_log10_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-log10-precise-import $(OUT)/sse2_log10_precise_import.bin $(OUT)/sse2-log10-precise-import-comparison.json

test-recovered: test-cycle-sse2-log10-precise-import
.PHONY: test-cycle-sse2-log10-precise-import

# Reviewed cycle reference: pe32-image-validate (assembly evidence only).
$(OUT)/pe32_image_validate.bin: native/pe32_image_validate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pe32_image_validate.o
	ld -m elf_i386 -Ttext=0x8f9b40 -e original_pe32_image_validate $(OUT)/pe32_image_validate.o -o $(OUT)/pe32_image_validate.elf
	objcopy -O binary --only-section=.text $(OUT)/pe32_image_validate.elf $@

test-cycle-pe32-image-validate: $(OUT)/reriff-match $(OUT)/pe32_image_validate.bin
	$(OUT)/reriff-match native-check "$(GAME)" pe32-image-validate $(OUT)/pe32_image_validate.bin $(OUT)/pe32-image-validate-comparison.json

test-recovered: test-cycle-pe32-image-validate
.PHONY: test-cycle-pe32-image-validate

# Reviewed cycle reference: u64-shift-left (assembly evidence only).
$(OUT)/u64_shift_left.bin: native/u64_shift_left.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u64_shift_left.o
	ld -m elf_i386 -Ttext=0x8f99a0 -e original_u64_shift_left $(OUT)/u64_shift_left.o -o $(OUT)/u64_shift_left.elf
	objcopy -O binary --only-section=.text $(OUT)/u64_shift_left.elf $@

test-cycle-u64-shift-left: $(OUT)/reriff-match $(OUT)/u64_shift_left.bin
	$(OUT)/reriff-match native-check "$(GAME)" u64-shift-left $(OUT)/u64_shift_left.bin $(OUT)/u64-shift-left-comparison.json

test-recovered: test-cycle-u64-shift-left
.PHONY: test-cycle-u64-shift-left

# Reviewed cycle reference: error-code-narrow-construct (assembly evidence only).
$(OUT)/error_code_narrow_construct.bin: native/error_code_narrow_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/error_code_narrow_construct.o
	ld -m elf_i386 -Ttext=0x44f380 -e original_error_code_narrow_construct $(OUT)/error_code_narrow_construct.o -o $(OUT)/error_code_narrow_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/error_code_narrow_construct.elf $@

test-cycle-error-code-narrow-construct: $(OUT)/reriff-match $(OUT)/error_code_narrow_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" error-code-narrow-construct $(OUT)/error_code_narrow_construct.bin $(OUT)/error-code-narrow-construct-comparison.json

test-recovered: test-cycle-error-code-narrow-construct
.PHONY: test-cycle-error-code-narrow-construct

# Reviewed cycle reference: type-info-destructor-import (assembly evidence only).
$(OUT)/type_info_destructor_import.bin: native/type_info_destructor_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/type_info_destructor_import.o
	ld -m elf_i386 -Ttext=0x8f99c0 -e original_type_info_destructor_import $(OUT)/type_info_destructor_import.o -o $(OUT)/type_info_destructor_import.elf
	objcopy -O binary --only-section=.text $(OUT)/type_info_destructor_import.elf $@

test-cycle-type-info-destructor-import: $(OUT)/reriff-match $(OUT)/type_info_destructor_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" type-info-destructor-import $(OUT)/type_info_destructor_import.bin $(OUT)/type-info-destructor-import-comparison.json

test-recovered: test-cycle-type-info-destructor-import
.PHONY: test-cycle-type-info-destructor-import

# Reviewed cycle reference: signed64-arithmetic-shift-right (assembly evidence only).
$(OUT)/signed64_arithmetic_shift_right.bin: native/signed64_arithmetic_shift_right.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/signed64_arithmetic_shift_right.o
	ld -m elf_i386 -Ttext=0x8fc260 -e original_signed64_arithmetic_shift_right $(OUT)/signed64_arithmetic_shift_right.o -o $(OUT)/signed64_arithmetic_shift_right.elf
	objcopy -O binary --only-section=.text $(OUT)/signed64_arithmetic_shift_right.elf $@

test-cycle-signed64-arithmetic-shift-right: $(OUT)/reriff-match $(OUT)/signed64_arithmetic_shift_right.bin
	$(OUT)/reriff-match native-check "$(GAME)" signed64-arithmetic-shift-right $(OUT)/signed64_arithmetic_shift_right.bin $(OUT)/signed64-arithmetic-shift-right-comparison.json

test-recovered: test-cycle-signed64-arithmetic-shift-right
.PHONY: test-cycle-signed64-arithmetic-shift-right

# Reviewed cycle reference: tree-sentinel-allocate (assembly evidence only).
$(OUT)/tree_sentinel_allocate.bin: native/tree_sentinel_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_sentinel_allocate.o
	ld -m elf_i386 -Ttext=0x423260 -e original_tree_sentinel_allocate $(OUT)/tree_sentinel_allocate.o -o $(OUT)/tree_sentinel_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_sentinel_allocate.elf $@

test-cycle-tree-sentinel-allocate: $(OUT)/reriff-match $(OUT)/tree_sentinel_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-sentinel-allocate $(OUT)/tree_sentinel_allocate.bin $(OUT)/tree-sentinel-allocate-comparison.json

test-recovered: test-cycle-tree-sentinel-allocate
.PHONY: test-cycle-tree-sentinel-allocate

# Reviewed cycle reference: tree-iterator-decrement (assembly evidence only).
$(OUT)/tree_iterator_decrement.bin: native/tree_iterator_decrement.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_iterator_decrement.o
	ld -m elf_i386 -Ttext=0x4235a0 -e original_tree_iterator_decrement $(OUT)/tree_iterator_decrement.o -o $(OUT)/tree_iterator_decrement.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_iterator_decrement.elf $@

test-cycle-tree-iterator-decrement: $(OUT)/reriff-match $(OUT)/tree_iterator_decrement.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-iterator-decrement $(OUT)/tree_iterator_decrement.bin $(OUT)/tree-iterator-decrement-comparison.json

test-recovered: test-cycle-tree-iterator-decrement
.PHONY: test-cycle-tree-iterator-decrement

# Reviewed cycle reference: tree-node-allocate-links (assembly evidence only).
$(OUT)/tree_node_allocate_links.bin: native/tree_node_allocate_links.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_node_allocate_links.o
	ld -m elf_i386 -Ttext=0x423560 -e original_tree_node_allocate_links $(OUT)/tree_node_allocate_links.o -o $(OUT)/tree_node_allocate_links.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_node_allocate_links.elf $@

test-cycle-tree-node-allocate-links: $(OUT)/reriff-match $(OUT)/tree_node_allocate_links.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-node-allocate-links $(OUT)/tree_node_allocate_links.bin $(OUT)/tree-node-allocate-links-comparison.json

test-recovered: test-cycle-tree-node-allocate-links
.PHONY: test-cycle-tree-node-allocate-links

# Reviewed cycle reference: tree-iterator-increment (assembly evidence only).
$(OUT)/tree_iterator_increment.bin: native/tree_iterator_increment.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_iterator_increment.o
	ld -m elf_i386 -Ttext=0x422e20 -e original_tree_iterator_increment $(OUT)/tree_iterator_increment.o -o $(OUT)/tree_iterator_increment.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_iterator_increment.elf $@

test-cycle-tree-iterator-increment: $(OUT)/reriff-match $(OUT)/tree_iterator_increment.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-iterator-increment $(OUT)/tree_iterator_increment.bin $(OUT)/tree-iterator-increment-comparison.json

test-recovered: test-cycle-tree-iterator-increment
.PHONY: test-cycle-tree-iterator-increment

# Reviewed cycle reference: tree-node-dispose-narrow (assembly evidence only).
$(OUT)/tree_node_dispose_narrow.bin: native/tree_node_dispose_narrow.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_node_dispose_narrow.o
	ld -m elf_i386 -Ttext=0x423520 -e original_tree_node_dispose_narrow $(OUT)/tree_node_dispose_narrow.o -o $(OUT)/tree_node_dispose_narrow.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_node_dispose_narrow.elf $@

test-cycle-tree-node-dispose-narrow: $(OUT)/reriff-match $(OUT)/tree_node_dispose_narrow.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-node-dispose-narrow $(OUT)/tree_node_dispose_narrow.bin $(OUT)/tree-node-dispose-narrow-comparison.json

test-recovered: test-cycle-tree-node-dispose-narrow
.PHONY: test-cycle-tree-node-dispose-narrow

# Reviewed cycle reference: tree-node-construct-narrow-move (assembly evidence only).
$(OUT)/tree_node_construct_narrow_move.bin: native/tree_node_construct_narrow_move.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_node_construct_narrow_move.o
	ld -m elf_i386 -Ttext=0x423290 -e original_tree_node_construct_narrow_move $(OUT)/tree_node_construct_narrow_move.o -o $(OUT)/tree_node_construct_narrow_move.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_node_construct_narrow_move.elf $@

test-cycle-tree-node-construct-narrow-move: $(OUT)/reriff-match $(OUT)/tree_node_construct_narrow_move.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-node-construct-narrow-move $(OUT)/tree_node_construct_narrow_move.bin $(OUT)/tree-node-construct-narrow-move-comparison.json

test-recovered: test-cycle-tree-node-construct-narrow-move
.PHONY: test-cycle-tree-node-construct-narrow-move

# Reviewed cycle reference: resource-table-acquire (assembly evidence only).
$(OUT)/resource_table_acquire.bin: native/resource_table_acquire.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_table_acquire.o
	ld -m elf_i386 -Ttext=0x421dc0 -e original_resource_table_acquire $(OUT)/resource_table_acquire.o -o $(OUT)/resource_table_acquire.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_table_acquire.elf $@

test-cycle-resource-table-acquire: $(OUT)/reriff-match $(OUT)/resource_table_acquire.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-table-acquire $(OUT)/resource_table_acquire.bin $(OUT)/resource-table-acquire-comparison.json

test-recovered: test-cycle-resource-table-acquire
.PHONY: test-cycle-resource-table-acquire

# Reviewed cycle reference: nested-record-count (assembly evidence only).
$(OUT)/nested_record_count.bin: native/nested_record_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/nested_record_count.o
	ld -m elf_i386 -Ttext=0x490e60 -e original_nested_record_count $(OUT)/nested_record_count.o -o $(OUT)/nested_record_count.elf
	objcopy -O binary --only-section=.text $(OUT)/nested_record_count.elf $@

test-cycle-nested-record-count: $(OUT)/reriff-match $(OUT)/nested_record_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" nested-record-count $(OUT)/nested_record_count.bin $(OUT)/nested-record-count-comparison.json

test-recovered: test-cycle-nested-record-count
.PHONY: test-cycle-nested-record-count

# Reviewed cycle reference: nested-record-pair-copy (assembly evidence only).
$(OUT)/nested_record_pair_copy.bin: native/nested_record_pair_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/nested_record_pair_copy.o
	ld -m elf_i386 -Ttext=0x490e70 -e original_nested_record_pair_copy $(OUT)/nested_record_pair_copy.o -o $(OUT)/nested_record_pair_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/nested_record_pair_copy.elf $@

test-cycle-nested-record-pair-copy: $(OUT)/reriff-match $(OUT)/nested_record_pair_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" nested-record-pair-copy $(OUT)/nested_record_pair_copy.bin $(OUT)/nested-record-pair-copy-comparison.json

test-recovered: test-cycle-nested-record-pair-copy
.PHONY: test-cycle-nested-record-pair-copy

# Reviewed cycle reference: nested-primary-record-count (assembly evidence only).
$(OUT)/nested_primary_record_count.bin: native/nested_primary_record_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/nested_primary_record_count.o
	ld -m elf_i386 -Ttext=0x490e50 -e original_nested_primary_record_count $(OUT)/nested_primary_record_count.o -o $(OUT)/nested_primary_record_count.elf
	objcopy -O binary --only-section=.text $(OUT)/nested_primary_record_count.elf $@

test-cycle-nested-primary-record-count: $(OUT)/reriff-match $(OUT)/nested_primary_record_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" nested-primary-record-count $(OUT)/nested_primary_record_count.bin $(OUT)/nested-primary-record-count-comparison.json

test-recovered: test-cycle-nested-primary-record-count
.PHONY: test-cycle-nested-primary-record-count

# Reviewed cycle reference: stack-allocate-align16 (assembly evidence only).
$(OUT)/stack_allocate_align16.bin: native/stack_allocate_align16.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/stack_allocate_align16.o
	ld -m elf_i386 -Ttext=0x8fc230 -e original_stack_allocate_align16 $(OUT)/stack_allocate_align16.o -o $(OUT)/stack_allocate_align16.elf
	objcopy -O binary --only-section=.text $(OUT)/stack_allocate_align16.elf $@

test-cycle-stack-allocate-align16: $(OUT)/reriff-match $(OUT)/stack_allocate_align16.bin
	$(OUT)/reriff-match native-check "$(GAME)" stack-allocate-align16 $(OUT)/stack_allocate_align16.bin $(OUT)/stack-allocate-align16-comparison.json

test-recovered: test-cycle-stack-allocate-align16
.PHONY: test-cycle-stack-allocate-align16

# Reviewed cycle reference: narrow-tree-key-less (assembly evidence only).
$(OUT)/narrow_tree_key_less.bin: native/narrow_tree_key_less.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_tree_key_less.o
	ld -m elf_i386 -Ttext=0x422c50 -e original_narrow_tree_key_less $(OUT)/narrow_tree_key_less.o -o $(OUT)/narrow_tree_key_less.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_tree_key_less.elf $@

test-cycle-narrow-tree-key-less: $(OUT)/reriff-match $(OUT)/narrow_tree_key_less.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-tree-key-less $(OUT)/narrow_tree_key_less.bin $(OUT)/narrow-tree-key-less-comparison.json

test-recovered: test-cycle-narrow-tree-key-less
.PHONY: test-cycle-narrow-tree-key-less

# Reviewed cycle reference: narrow-compare-range (assembly evidence only).
$(OUT)/narrow_compare_range.bin: native/narrow_compare_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_compare_range.o
	ld -m elf_i386 -Ttext=0x422be0 -e original_narrow_compare_range $(OUT)/narrow_compare_range.o -o $(OUT)/narrow_compare_range.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_compare_range.elf $@

test-cycle-narrow-compare-range: $(OUT)/reriff-match $(OUT)/narrow_compare_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-compare-range $(OUT)/narrow_compare_range.bin $(OUT)/narrow-compare-range-comparison.json

test-recovered: test-cycle-narrow-compare-range
.PHONY: test-cycle-narrow-compare-range

# Reviewed cycle reference: sse2-cos-precise-import (assembly evidence only).
$(OUT)/sse2_cos_precise_import.bin: native/sse2_cos_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_cos_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8f22 -e original_sse2_cos_precise_import $(OUT)/sse2_cos_precise_import.o -o $(OUT)/sse2_cos_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_cos_precise_import.elf $@

test-cycle-sse2-cos-precise-import: $(OUT)/reriff-match $(OUT)/sse2_cos_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-cos-precise-import $(OUT)/sse2_cos_precise_import.bin $(OUT)/sse2-cos-precise-import-comparison.json

test-recovered: test-cycle-sse2-cos-precise-import
.PHONY: test-cycle-sse2-cos-precise-import

# Reviewed cycle reference: byte-range-transform-callback (assembly evidence only).
$(OUT)/byte_range_transform_callback.bin: native/byte_range_transform_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/byte_range_transform_callback.o
	ld -m elf_i386 -Ttext=0x5c2740 -e original_byte_range_transform_callback $(OUT)/byte_range_transform_callback.o -o $(OUT)/byte_range_transform_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/byte_range_transform_callback.elf $@

test-cycle-byte-range-transform-callback: $(OUT)/reriff-match $(OUT)/byte_range_transform_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" byte-range-transform-callback $(OUT)/byte_range_transform_callback.bin $(OUT)/byte-range-transform-callback-comparison.json

test-recovered: test-cycle-byte-range-transform-callback
.PHONY: test-cycle-byte-range-transform-callback

# Reviewed cycle reference: tree-subtree-destroy-narrow (assembly evidence only).
$(OUT)/tree_subtree_destroy_narrow.bin: native/tree_subtree_destroy_narrow.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/tree_subtree_destroy_narrow.o
	ld -m elf_i386 -Ttext=0x423110 -e original_tree_subtree_destroy_narrow $(OUT)/tree_subtree_destroy_narrow.o -o $(OUT)/tree_subtree_destroy_narrow.elf
	objcopy -O binary --only-section=.text $(OUT)/tree_subtree_destroy_narrow.elf $@

test-cycle-tree-subtree-destroy-narrow: $(OUT)/reriff-match $(OUT)/tree_subtree_destroy_narrow.bin
	$(OUT)/reriff-match native-check "$(GAME)" tree-subtree-destroy-narrow $(OUT)/tree_subtree_destroy_narrow.bin $(OUT)/tree-subtree-destroy-narrow-comparison.json

test-recovered: test-cycle-tree-subtree-destroy-narrow
.PHONY: test-cycle-tree-subtree-destroy-narrow

# Reviewed cycle reference: matrix64-copy (assembly evidence only).
$(OUT)/matrix64_copy.bin: native/matrix64_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix64_copy.o
	ld -m elf_i386 -Ttext=0x426fd0 -e original_matrix64_copy $(OUT)/matrix64_copy.o -o $(OUT)/matrix64_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix64_copy.elf $@

test-cycle-matrix64-copy: $(OUT)/reriff-match $(OUT)/matrix64_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix64-copy $(OUT)/matrix64_copy.bin $(OUT)/matrix64-copy-comparison.json

test-recovered: test-cycle-matrix64-copy
.PHONY: test-cycle-matrix64-copy

# Reviewed cycle reference: u64-multiply-low (assembly evidence only).
$(OUT)/u64_multiply_low.bin: native/u64_multiply_low.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u64_multiply_low.o
	ld -m elf_i386 -Ttext=0x8fc1f0 -e original_u64_multiply_low $(OUT)/u64_multiply_low.o -o $(OUT)/u64_multiply_low.elf
	objcopy -O binary --only-section=.text $(OUT)/u64_multiply_low.elf $@

test-cycle-u64-multiply-low: $(OUT)/reriff-match $(OUT)/u64_multiply_low.bin
	$(OUT)/reriff-match native-check "$(GAME)" u64-multiply-low $(OUT)/u64_multiply_low.bin $(OUT)/u64-multiply-low-comparison.json

test-recovered: test-cycle-u64-multiply-low
.PHONY: test-cycle-u64-multiply-low

# Reviewed cycle reference: owner-slot214-assign (assembly evidence only).
$(OUT)/owner_slot214_assign.bin: native/owner_slot214_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/owner_slot214_assign.o
	ld -m elf_i386 -Ttext=0x490eb0 -e original_owner_slot214_assign $(OUT)/owner_slot214_assign.o -o $(OUT)/owner_slot214_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/owner_slot214_assign.elf $@

test-cycle-owner-slot214-assign: $(OUT)/reriff-match $(OUT)/owner_slot214_assign.bin
	$(OUT)/reriff-match native-check "$(GAME)" owner-slot214-assign $(OUT)/owner_slot214_assign.bin $(OUT)/owner-slot214-assign-comparison.json

test-recovered: test-cycle-owner-slot214-assign
.PHONY: test-cycle-owner-slot214-assign

# Reviewed cycle reference: unsigned64-divide (assembly evidence only).
$(OUT)/unsigned64_divide.bin: native/unsigned64_divide.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/unsigned64_divide.o
	ld -m elf_i386 -Ttext=0x8fc290 -e original_unsigned64_divide $(OUT)/unsigned64_divide.o -o $(OUT)/unsigned64_divide.elf
	objcopy -O binary --only-section=.text $(OUT)/unsigned64_divide.elf $@

test-cycle-unsigned64-divide: $(OUT)/reriff-match $(OUT)/unsigned64_divide.bin
	$(OUT)/reriff-match native-check "$(GAME)" unsigned64-divide $(OUT)/unsigned64_divide.bin $(OUT)/unsigned64-divide-comparison.json

test-recovered: test-cycle-unsigned64-divide
.PHONY: test-cycle-unsigned64-divide

# Reviewed cycle reference: unsigned64-logical-shift-right (assembly evidence only).
$(OUT)/unsigned64_logical_shift_right.bin: native/unsigned64_logical_shift_right.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/unsigned64_logical_shift_right.o
	ld -m elf_i386 -Ttext=0x8fc380 -e original_unsigned64_logical_shift_right $(OUT)/unsigned64_logical_shift_right.o -o $(OUT)/unsigned64_logical_shift_right.elf
	objcopy -O binary --only-section=.text $(OUT)/unsigned64_logical_shift_right.elf $@

test-cycle-unsigned64-logical-shift-right: $(OUT)/reriff-match $(OUT)/unsigned64_logical_shift_right.bin
	$(OUT)/reriff-match native-check "$(GAME)" unsigned64-logical-shift-right $(OUT)/unsigned64_logical_shift_right.bin $(OUT)/unsigned64-logical-shift-right-comparison.json

test-recovered: test-cycle-unsigned64-logical-shift-right
.PHONY: test-cycle-unsigned64-logical-shift-right

# Reviewed cycle reference: unsigned64-remainder (assembly evidence only).
$(OUT)/unsigned64_remainder.bin: native/unsigned64_remainder.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/unsigned64_remainder.o
	ld -m elf_i386 -Ttext=0x8fc300 -e original_unsigned64_remainder $(OUT)/unsigned64_remainder.o -o $(OUT)/unsigned64_remainder.elf
	objcopy -O binary --only-section=.text $(OUT)/unsigned64_remainder.elf $@

test-cycle-unsigned64-remainder: $(OUT)/reriff-match $(OUT)/unsigned64_remainder.bin
	$(OUT)/reriff-match native-check "$(GAME)" unsigned64-remainder $(OUT)/unsigned64_remainder.bin $(OUT)/unsigned64-remainder-comparison.json

test-recovered: test-cycle-unsigned64-remainder
.PHONY: test-cycle-unsigned64-remainder

# Reviewed cycle reference: double-integer-parity (assembly evidence only).
$(OUT)/double_integer_parity.bin: native/double_integer_parity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/double_integer_parity.o
	ld -m elf_i386 -Ttext=0x8fc420 -e original_double_integer_parity $(OUT)/double_integer_parity.o -o $(OUT)/double_integer_parity.elf
	objcopy -O binary --only-section=.text $(OUT)/double_integer_parity.elf $@

test-cycle-double-integer-parity: $(OUT)/reriff-match $(OUT)/double_integer_parity.bin
	$(OUT)/reriff-match native-check "$(GAME)" double-integer-parity $(OUT)/double_integer_parity.bin $(OUT)/double-integer-parity-comparison.json

test-recovered: test-cycle-double-integer-parity
.PHONY: test-cycle-double-integer-parity

# Reviewed cycle reference: arena-initialize-once (assembly evidence only).
$(OUT)/arena_initialize_once.bin: native/arena_initialize_once.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/arena_initialize_once.o
	ld -m elf_i386 -Ttext=0x452d30 -e original_arena_initialize_once $(OUT)/arena_initialize_once.o -o $(OUT)/arena_initialize_once.elf
	objcopy -O binary --only-section=.text $(OUT)/arena_initialize_once.elf $@

test-cycle-arena-initialize-once: $(OUT)/reriff-match $(OUT)/arena_initialize_once.bin
	$(OUT)/reriff-match native-check "$(GAME)" arena-initialize-once $(OUT)/arena_initialize_once.bin $(OUT)/arena-initialize-once-comparison.json

test-recovered: test-cycle-arena-initialize-once
.PHONY: test-cycle-arena-initialize-once

# Reviewed cycle reference: arena-build-initial-block (assembly evidence only).
$(OUT)/arena_build_initial_block.bin: native/arena_build_initial_block.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/arena_build_initial_block.o
	ld -m elf_i386 -Ttext=0x4b4380 -e original_arena_build_initial_block $(OUT)/arena_build_initial_block.o -o $(OUT)/arena_build_initial_block.elf
	objcopy -O binary --only-section=.text $(OUT)/arena_build_initial_block.elf $@

test-cycle-arena-build-initial-block: $(OUT)/reriff-match $(OUT)/arena_build_initial_block.bin
	$(OUT)/reriff-match native-check "$(GAME)" arena-build-initial-block $(OUT)/arena_build_initial_block.bin $(OUT)/arena-build-initial-block-comparison.json

test-recovered: test-cycle-arena-build-initial-block
.PHONY: test-cycle-arena-build-initial-block

# Reviewed cycle reference: shader-boolean-callback (assembly evidence only).
$(OUT)/shader_boolean_callback.bin: native/shader_boolean_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_boolean_callback.o
	ld -m elf_i386 -Ttext=0x510ec0 -e original_shader_boolean_callback $(OUT)/shader_boolean_callback.o -o $(OUT)/shader_boolean_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_boolean_callback.elf $@

test-cycle-shader-boolean-callback: $(OUT)/reriff-match $(OUT)/shader_boolean_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-boolean-callback $(OUT)/shader_boolean_callback.bin $(OUT)/shader-boolean-callback-comparison.json

test-recovered: test-cycle-shader-boolean-callback
.PHONY: test-cycle-shader-boolean-callback

# Reviewed cycle reference: record56-float44-less (assembly evidence only).
$(OUT)/record56_float44_less.bin: native/record56_float44_less.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record56_float44_less.o
	ld -m elf_i386 -Ttext=0x426ee0 -e original_record56_float44_less $(OUT)/record56_float44_less.o -o $(OUT)/record56_float44_less.elf
	objcopy -O binary --only-section=.text $(OUT)/record56_float44_less.elf $@

test-cycle-record56-float44-less: $(OUT)/reriff-match $(OUT)/record56_float44_less.bin
	$(OUT)/reriff-match native-check "$(GAME)" record56-float44-less $(OUT)/record56_float44_less.bin $(OUT)/record56-float44-less-comparison.json

test-recovered: test-cycle-record56-float44-less
.PHONY: test-cycle-record56-float44-less

# Reviewed cycle reference: matrix-column3-extract (assembly evidence only).
$(OUT)/matrix_column3_extract.bin: native/matrix_column3_extract.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix_column3_extract.o
	ld -m elf_i386 -Ttext=0x426fa0 -e original_matrix_column3_extract $(OUT)/matrix_column3_extract.o -o $(OUT)/matrix_column3_extract.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix_column3_extract.elf $@

test-cycle-matrix-column3-extract: $(OUT)/reriff-match $(OUT)/matrix_column3_extract.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix-column3-extract $(OUT)/matrix_column3_extract.bin $(OUT)/matrix-column3-extract-comparison.json

test-recovered: test-cycle-matrix-column3-extract
.PHONY: test-cycle-matrix-column3-extract

# Reviewed cycle reference: utf16-terminated-length (assembly evidence only).
$(OUT)/utf16_terminated_length.bin: native/utf16_terminated_length.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/utf16_terminated_length.o
	ld -m elf_i386 -Ttext=0x425bc0 -e original_utf16_terminated_length $(OUT)/utf16_terminated_length.o -o $(OUT)/utf16_terminated_length.elf
	objcopy -O binary --only-section=.text $(OUT)/utf16_terminated_length.elf $@

test-cycle-utf16-terminated-length: $(OUT)/reriff-match $(OUT)/utf16_terminated_length.bin
	$(OUT)/reriff-match native-check "$(GAME)" utf16-terminated-length $(OUT)/utf16_terminated_length.bin $(OUT)/utf16-terminated-length-comparison.json

test-recovered: test-cycle-utf16-terminated-length
.PHONY: test-cycle-utf16-terminated-length

# Reviewed cycle reference: owner-slot58-acquire (assembly evidence only).
$(OUT)/owner_slot58_acquire.bin: native/owner_slot58_acquire.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/owner_slot58_acquire.o
	ld -m elf_i386 -Ttext=0x48fc70 -e original_owner_slot58_acquire $(OUT)/owner_slot58_acquire.o -o $(OUT)/owner_slot58_acquire.elf
	objcopy -O binary --only-section=.text $(OUT)/owner_slot58_acquire.elf $@

test-cycle-owner-slot58-acquire: $(OUT)/reriff-match $(OUT)/owner_slot58_acquire.bin
	$(OUT)/reriff-match native-check "$(GAME)" owner-slot58-acquire $(OUT)/owner_slot58_acquire.bin $(OUT)/owner-slot58-acquire-comparison.json

test-recovered: test-cycle-owner-slot58-acquire
.PHONY: test-cycle-owner-slot58-acquire

# Reviewed cycle reference: matrix3-construct-refs (assembly evidence only).
$(OUT)/matrix3_construct_refs.bin: native/matrix3_construct_refs.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix3_construct_refs.o
	ld -m elf_i386 -Ttext=0x426f30 -e original_matrix3_construct_refs $(OUT)/matrix3_construct_refs.o -o $(OUT)/matrix3_construct_refs.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix3_construct_refs.elf $@

test-cycle-matrix3-construct-refs: $(OUT)/reriff-match $(OUT)/matrix3_construct_refs.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix3-construct-refs $(OUT)/matrix3_construct_refs.bin $(OUT)/matrix3-construct-refs-comparison.json

test-recovered: test-cycle-matrix3-construct-refs
.PHONY: test-cycle-matrix3-construct-refs

# Reviewed cycle reference: resource-index-acquire (assembly evidence only).
$(OUT)/resource_index_acquire.bin: native/resource_index_acquire.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/resource_index_acquire.o
	ld -m elf_i386 -Ttext=0x511e90 -e original_resource_index_acquire $(OUT)/resource_index_acquire.o -o $(OUT)/resource_index_acquire.elf
	objcopy -O binary --only-section=.text $(OUT)/resource_index_acquire.elf $@

test-cycle-resource-index-acquire: $(OUT)/reriff-match $(OUT)/resource_index_acquire.bin
	$(OUT)/reriff-match native-check "$(GAME)" resource-index-acquire $(OUT)/resource_index_acquire.bin $(OUT)/resource-index-acquire-comparison.json

test-recovered: test-cycle-resource-index-acquire
.PHONY: test-cycle-resource-index-acquire

# Reviewed cycle reference: record12-default-initialize (assembly evidence only).
$(OUT)/record12_default_initialize.bin: native/record12_default_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_default_initialize.o
	ld -m elf_i386 -Ttext=0x41db10 -e original_record12_default_initialize $(OUT)/record12_default_initialize.o -o $(OUT)/record12_default_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_default_initialize.elf $@

test-cycle-record12-default-initialize: $(OUT)/reriff-match $(OUT)/record12_default_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-default-initialize $(OUT)/record12_default_initialize.bin $(OUT)/record12-default-initialize-comparison.json

test-recovered: test-cycle-record12-default-initialize
.PHONY: test-cycle-record12-default-initialize

# Reviewed cycle reference: shader-boolean-register (assembly evidence only).
$(OUT)/shader_boolean_register.bin: native/shader_boolean_register.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_boolean_register.o
	ld -m elf_i386 -Ttext=0x510ee0 -e original_shader_boolean_register $(OUT)/shader_boolean_register.o -o $(OUT)/shader_boolean_register.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_boolean_register.elf $@

test-cycle-shader-boolean-register: $(OUT)/reriff-match $(OUT)/shader_boolean_register.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-boolean-register $(OUT)/shader_boolean_register.bin $(OUT)/shader-boolean-register-comparison.json

test-recovered: test-cycle-shader-boolean-register
.PHONY: test-cycle-shader-boolean-register

# Reviewed cycle reference: u32-vector-reallocate (assembly evidence only).
$(OUT)/u32_vector_reallocate.bin: native/u32_vector_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_reallocate.o
	ld -m elf_i386 -Ttext=0x426800 -e original_u32_vector_reallocate $(OUT)/u32_vector_reallocate.o -o $(OUT)/u32_vector_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_reallocate.elf $@

test-cycle-u32-vector-reallocate: $(OUT)/reriff-match $(OUT)/u32_vector_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-reallocate $(OUT)/u32_vector_reallocate.bin $(OUT)/u32-vector-reallocate-comparison.json

test-recovered: test-cycle-u32-vector-reallocate
.PHONY: test-cycle-u32-vector-reallocate

# Reviewed cycle reference: narrow-record24-default-initialize (assembly evidence only).
$(OUT)/narrow_record24_default_initialize.bin: native/narrow_record24_default_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_record24_default_initialize.o
	ld -m elf_i386 -Ttext=0x4268c0 -e original_narrow_record24_default_initialize $(OUT)/narrow_record24_default_initialize.o -o $(OUT)/narrow_record24_default_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_record24_default_initialize.elf $@

test-cycle-narrow-record24-default-initialize: $(OUT)/reriff-match $(OUT)/narrow_record24_default_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-record24-default-initialize $(OUT)/narrow_record24_default_initialize.bin $(OUT)/narrow-record24-default-initialize-comparison.json

test-recovered: test-cycle-narrow-record24-default-initialize
.PHONY: test-cycle-narrow-record24-default-initialize

# Reviewed cycle reference: narrow-element-destroy-callback (assembly evidence only).
$(OUT)/narrow_element_destroy_callback.bin: native/narrow_element_destroy_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_element_destroy_callback.o
	ld -m elf_i386 -Ttext=0x426930 -e original_narrow_element_destroy_callback $(OUT)/narrow_element_destroy_callback.o -o $(OUT)/narrow_element_destroy_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_element_destroy_callback.elf $@

test-cycle-narrow-element-destroy-callback: $(OUT)/reriff-match $(OUT)/narrow_element_destroy_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-element-destroy-callback $(OUT)/narrow_element_destroy_callback.bin $(OUT)/narrow-element-destroy-callback-comparison.json

test-recovered: test-cycle-narrow-element-destroy-callback
.PHONY: test-cycle-narrow-element-destroy-callback

# Reviewed cycle reference: u32-allocate (assembly evidence only).
$(OUT)/u32_allocate.bin: native/u32_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_allocate.o
	ld -m elf_i386 -Ttext=0x426880 -e original_u32_allocate $(OUT)/u32_allocate.o -o $(OUT)/u32_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_allocate.elf $@

test-cycle-u32-allocate: $(OUT)/reriff-match $(OUT)/u32_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-allocate $(OUT)/u32_allocate.bin $(OUT)/u32-allocate-comparison.json

test-recovered: test-cycle-u32-allocate
.PHONY: test-cycle-u32-allocate

# Reviewed cycle reference: narrow-range-move-construct (assembly evidence only).
$(OUT)/narrow_range_move_construct.bin: native/narrow_range_move_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_range_move_construct.o
	ld -m elf_i386 -Ttext=0x426960 -e original_narrow_range_move_construct $(OUT)/narrow_range_move_construct.o -o $(OUT)/narrow_range_move_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_range_move_construct.elf $@

test-cycle-narrow-range-move-construct: $(OUT)/reriff-match $(OUT)/narrow_range_move_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-range-move-construct $(OUT)/narrow_range_move_construct.bin $(OUT)/narrow-range-move-construct-comparison.json

test-recovered: test-cycle-narrow-range-move-construct
.PHONY: test-cycle-narrow-range-move-construct

# Reviewed cycle reference: cp1252-wide-construct (assembly evidence only).
$(OUT)/cp1252_wide_construct.bin: native/cp1252_wide_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/cp1252_wide_construct.o
	ld -m elf_i386 -Ttext=0x44f3e0 -e original_cp1252_wide_construct $(OUT)/cp1252_wide_construct.o -o $(OUT)/cp1252_wide_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/cp1252_wide_construct.elf $@

test-cycle-cp1252-wide-construct: $(OUT)/reriff-match $(OUT)/cp1252_wide_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" cp1252-wide-construct $(OUT)/cp1252_wide_construct.bin $(OUT)/cp1252-wide-construct-comparison.json

test-recovered: test-cycle-cp1252-wide-construct
.PHONY: test-cycle-cp1252-wide-construct

# Reviewed cycle reference: record12-zero-initialize (assembly evidence only).
$(OUT)/record12_zero_initialize.bin: native/record12_zero_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_zero_initialize.o
	ld -m elf_i386 -Ttext=0x437ed0 -e original_record12_zero_initialize $(OUT)/record12_zero_initialize.o -o $(OUT)/record12_zero_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_zero_initialize.elf $@

test-cycle-record12-zero-initialize: $(OUT)/reriff-match $(OUT)/record12_zero_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-zero-initialize $(OUT)/record12_zero_initialize.bin $(OUT)/record12-zero-initialize-comparison.json

test-recovered: test-cycle-record12-zero-initialize
.PHONY: test-cycle-record12-zero-initialize

# Reviewed cycle reference: record24-ensure-spare (assembly evidence only).
$(OUT)/record24_ensure_spare.bin: native/record24_ensure_spare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_ensure_spare.o
	ld -m elf_i386 -Ttext=0x4b28d0 -e original_record24_ensure_spare $(OUT)/record24_ensure_spare.o -o $(OUT)/record24_ensure_spare.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_ensure_spare.elf $@

test-cycle-record24-ensure-spare: $(OUT)/reriff-match $(OUT)/record24_ensure_spare.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-ensure-spare $(OUT)/record24_ensure_spare.bin $(OUT)/record24-ensure-spare-comparison.json

test-recovered: test-cycle-record24-ensure-spare
.PHONY: test-cycle-record24-ensure-spare

# Reviewed cycle reference: record24-reallocate (assembly evidence only).
$(OUT)/record24_reallocate.bin: native/record24_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record24_reallocate.o
	ld -m elf_i386 -Ttext=0x4b2840 -e original_record24_reallocate $(OUT)/record24_reallocate.o -o $(OUT)/record24_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/record24_reallocate.elf $@

test-cycle-record24-reallocate: $(OUT)/reriff-match $(OUT)/record24_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" record24-reallocate $(OUT)/record24_reallocate.bin $(OUT)/record24-reallocate-comparison.json

test-recovered: test-cycle-record24-reallocate
.PHONY: test-cycle-record24-reallocate

# Reviewed cycle reference: narrow-tree-lower-bound (assembly evidence only).
$(OUT)/narrow_tree_lower_bound.bin: native/narrow_tree_lower_bound.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_tree_lower_bound.o
	ld -m elf_i386 -Ttext=0x422d40 -e original_narrow_tree_lower_bound $(OUT)/narrow_tree_lower_bound.o -o $(OUT)/narrow_tree_lower_bound.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_tree_lower_bound.elf $@

test-cycle-narrow-tree-lower-bound: $(OUT)/reriff-match $(OUT)/narrow_tree_lower_bound.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-tree-lower-bound $(OUT)/narrow_tree_lower_bound.bin $(OUT)/narrow-tree-lower-bound-comparison.json

test-recovered: test-cycle-narrow-tree-lower-bound
.PHONY: test-cycle-narrow-tree-lower-bound

# Reviewed cycle reference: byte-widen-terminated (assembly evidence only).
$(OUT)/byte_widen_terminated.bin: native/byte_widen_terminated.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/byte_widen_terminated.o
	ld -m elf_i386 -Ttext=0x425c40 -e original_byte_widen_terminated $(OUT)/byte_widen_terminated.o -o $(OUT)/byte_widen_terminated.elf
	objcopy -O binary --only-section=.text $(OUT)/byte_widen_terminated.elf $@

test-cycle-byte-widen-terminated: $(OUT)/reriff-match $(OUT)/byte_widen_terminated.bin
	$(OUT)/reriff-match native-check "$(GAME)" byte-widen-terminated $(OUT)/byte_widen_terminated.bin $(OUT)/byte-widen-terminated-comparison.json

test-recovered: test-cycle-byte-widen-terminated
.PHONY: test-cycle-byte-widen-terminated

# Reviewed cycle reference: record36-copy-range (assembly evidence only).
$(OUT)/record36_copy_range.bin: native/record36_copy_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record36_copy_range.o
	ld -m elf_i386 -Ttext=0x422580 -e original_record36_copy_range $(OUT)/record36_copy_range.o -o $(OUT)/record36_copy_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record36_copy_range.elf $@

test-cycle-record36-copy-range: $(OUT)/reriff-match $(OUT)/record36_copy_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record36-copy-range $(OUT)/record36_copy_range.bin $(OUT)/record36-copy-range-comparison.json

test-recovered: test-cycle-record36-copy-range
.PHONY: test-cycle-record36-copy-range

# Reviewed cycle reference: record68-range-copy (assembly evidence only).
$(OUT)/record68_range_copy.bin: native/record68_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record68_range_copy.o
	ld -m elf_i386 -Ttext=0x509e60 -e original_record68_range_copy $(OUT)/record68_range_copy.o -o $(OUT)/record68_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record68_range_copy.elf $@

test-cycle-record68-range-copy: $(OUT)/reriff-match $(OUT)/record68_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record68-range-copy $(OUT)/record68_range_copy.bin $(OUT)/record68-range-copy-comparison.json

test-recovered: test-cycle-record68-range-copy
.PHONY: test-cycle-record68-range-copy

# Reviewed cycle reference: record68-copy-construct (assembly evidence only).
$(OUT)/record68_copy_construct.bin: native/record68_copy_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record68_copy_construct.o
	ld -m elf_i386 -Ttext=0x509ef0 -e original_record68_copy_construct $(OUT)/record68_copy_construct.o -o $(OUT)/record68_copy_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/record68_copy_construct.elf $@

test-cycle-record68-copy-construct: $(OUT)/reriff-match $(OUT)/record68_copy_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" record68-copy-construct $(OUT)/record68_copy_construct.bin $(OUT)/record68-copy-construct-comparison.json

test-recovered: test-cycle-record68-copy-construct
.PHONY: test-cycle-record68-copy-construct

# Reviewed cycle reference: vector3-dot-sse (assembly evidence only).
$(OUT)/vector3_dot_sse.bin: native/vector3_dot_sse.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/vector3_dot_sse.o
	ld -m elf_i386 -Ttext=0x4383e0 -e original_vector3_dot_sse $(OUT)/vector3_dot_sse.o -o $(OUT)/vector3_dot_sse.elf
	objcopy -O binary --only-section=.text $(OUT)/vector3_dot_sse.elf $@

test-cycle-vector3-dot-sse: $(OUT)/reriff-match $(OUT)/vector3_dot_sse.bin
	$(OUT)/reriff-match native-check "$(GAME)" vector3-dot-sse $(OUT)/vector3_dot_sse.bin $(OUT)/vector3-dot-sse-comparison.json

test-recovered: test-cycle-vector3-dot-sse
.PHONY: test-cycle-vector3-dot-sse

# Reviewed cycle reference: shader-slot-select (assembly evidence only).
$(OUT)/shader_slot_select.bin: native/shader_slot_select.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shader_slot_select.o
	ld -m elf_i386 -Ttext=0x5301b0 -e original_shader_slot_select $(OUT)/shader_slot_select.o -o $(OUT)/shader_slot_select.elf
	objcopy -O binary --only-section=.text $(OUT)/shader_slot_select.elf $@

test-cycle-shader-slot-select: $(OUT)/reriff-match $(OUT)/shader_slot_select.bin
	$(OUT)/reriff-match native-check "$(GAME)" shader-slot-select $(OUT)/shader_slot_select.bin $(OUT)/shader-slot-select-comparison.json

test-recovered: test-cycle-shader-slot-select
.PHONY: test-cycle-shader-slot-select

# Reviewed cycle reference: vector3-normalize (assembly evidence only).
$(OUT)/vector3_normalize.bin: native/vector3_normalize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/vector3_normalize.o
	ld -m elf_i386 -Ttext=0x426d90 -e original_vector3_normalize $(OUT)/vector3_normalize.o -o $(OUT)/vector3_normalize.elf
	objcopy -O binary --only-section=.text $(OUT)/vector3_normalize.elf $@

test-cycle-vector3-normalize: $(OUT)/reriff-match $(OUT)/vector3_normalize.bin
	$(OUT)/reriff-match native-check "$(GAME)" vector3-normalize $(OUT)/vector3_normalize.bin $(OUT)/vector3-normalize-comparison.json

test-recovered: test-cycle-vector3-normalize
.PHONY: test-cycle-vector3-normalize

# Reviewed cycle reference: u32-vector-growth-capacity (assembly evidence only).
$(OUT)/u32_vector_growth_capacity.bin: native/u32_vector_growth_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_growth_capacity.o
	ld -m elf_i386 -Ttext=0x50dfe0 -e original_u32_vector_growth_capacity $(OUT)/u32_vector_growth_capacity.o -o $(OUT)/u32_vector_growth_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_growth_capacity.elf $@

test-cycle-u32-vector-growth-capacity: $(OUT)/reriff-match $(OUT)/u32_vector_growth_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-growth-capacity $(OUT)/u32_vector_growth_capacity.bin $(OUT)/u32-vector-growth-capacity-comparison.json

test-recovered: test-cycle-u32-vector-growth-capacity
.PHONY: test-cycle-u32-vector-growth-capacity

# Reviewed cycle reference: owner-handle5c-acquire (assembly evidence only).
$(OUT)/owner_handle5c_acquire.bin: native/owner_handle5c_acquire.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/owner_handle5c_acquire.o
	ld -m elf_i386 -Ttext=0x43f250 -e original_owner_handle5c_acquire $(OUT)/owner_handle5c_acquire.o -o $(OUT)/owner_handle5c_acquire.elf
	objcopy -O binary --only-section=.text $(OUT)/owner_handle5c_acquire.elf $@

test-cycle-owner-handle5c-acquire: $(OUT)/reriff-match $(OUT)/owner_handle5c_acquire.bin
	$(OUT)/reriff-match native-check "$(GAME)" owner-handle5c-acquire $(OUT)/owner_handle5c_acquire.bin $(OUT)/owner-handle5c-acquire-comparison.json

test-recovered: test-cycle-owner-handle5c-acquire
.PHONY: test-cycle-owner-handle5c-acquire

# Reviewed cycle reference: matrix64-initialize-basis (assembly evidence only).
$(OUT)/matrix64_initialize_basis.bin: native/matrix64_initialize_basis.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix64_initialize_basis.o
	ld -m elf_i386 -Ttext=0x438480 -e original_matrix64_initialize_basis $(OUT)/matrix64_initialize_basis.o -o $(OUT)/matrix64_initialize_basis.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix64_initialize_basis.elf $@

test-cycle-matrix64-initialize-basis: $(OUT)/reriff-match $(OUT)/matrix64_initialize_basis.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix64-initialize-basis $(OUT)/matrix64_initialize_basis.bin $(OUT)/matrix64-initialize-basis-comparison.json

test-recovered: test-cycle-matrix64-initialize-basis
.PHONY: test-cycle-matrix64-initialize-basis

# Reviewed cycle reference: matrix-row-pointer (assembly evidence only).
$(OUT)/matrix_row_pointer.bin: native/matrix_row_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix_row_pointer.o
	ld -m elf_i386 -Ttext=0x438410 -e original_matrix_row_pointer $(OUT)/matrix_row_pointer.o -o $(OUT)/matrix_row_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix_row_pointer.elf $@

test-cycle-matrix-row-pointer: $(OUT)/reriff-match $(OUT)/matrix_row_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix-row-pointer $(OUT)/matrix_row_pointer.bin $(OUT)/matrix-row-pointer-comparison.json

test-recovered: test-cycle-matrix-row-pointer
.PHONY: test-cycle-matrix-row-pointer

# Reviewed cycle reference: matrix48-initialize-basis (assembly evidence only).
$(OUT)/matrix48_initialize_basis.bin: native/matrix48_initialize_basis.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix48_initialize_basis.o
	ld -m elf_i386 -Ttext=0x438420 -e original_matrix48_initialize_basis $(OUT)/matrix48_initialize_basis.o -o $(OUT)/matrix48_initialize_basis.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix48_initialize_basis.elf $@

test-cycle-matrix48-initialize-basis: $(OUT)/reriff-match $(OUT)/matrix48_initialize_basis.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix48-initialize-basis $(OUT)/matrix48_initialize_basis.bin $(OUT)/matrix48-initialize-basis-comparison.json

test-recovered: test-cycle-matrix48-initialize-basis
.PHONY: test-cycle-matrix48-initialize-basis

# Reviewed cycle reference: record32-index-reference (assembly evidence only).
$(OUT)/record32_index_reference.bin: native/record32_index_reference.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record32_index_reference.o
	ld -m elf_i386 -Ttext=0x41dfb0 -e original_record32_index_reference $(OUT)/record32_index_reference.o -o $(OUT)/record32_index_reference.elf
	objcopy -O binary --only-section=.text $(OUT)/record32_index_reference.elf $@

test-cycle-record32-index-reference: $(OUT)/reriff-match $(OUT)/record32_index_reference.bin
	$(OUT)/reriff-match native-check "$(GAME)" record32-index-reference $(OUT)/record32_index_reference.bin $(OUT)/record32-index-reference-comparison.json

test-recovered: test-cycle-record32-index-reference
.PHONY: test-cycle-record32-index-reference

# Reviewed cycle reference: affine48-to-matrix64 (assembly evidence only).
$(OUT)/affine48_to_matrix64.bin: native/affine48_to_matrix64.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/affine48_to_matrix64.o
	ld -m elf_i386 -Ttext=0x4271a0 -e original_affine48_to_matrix64 $(OUT)/affine48_to_matrix64.o -o $(OUT)/affine48_to_matrix64.elf
	objcopy -O binary --only-section=.text $(OUT)/affine48_to_matrix64.elf $@

test-cycle-affine48-to-matrix64: $(OUT)/reriff-match $(OUT)/affine48_to_matrix64.bin
	$(OUT)/reriff-match native-check "$(GAME)" affine48-to-matrix64 $(OUT)/affine48_to_matrix64.bin $(OUT)/affine48-to-matrix64-comparison.json

test-recovered: test-cycle-affine48-to-matrix64
.PHONY: test-cycle-affine48-to-matrix64

# Reviewed cycle reference: device-bind-pending-targets (assembly evidence only).
$(OUT)/device_bind_pending_targets.bin: native/device_bind_pending_targets.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_bind_pending_targets.o
	ld -m elf_i386 -Ttext=0x4a4f30 -e original_device_bind_pending_targets $(OUT)/device_bind_pending_targets.o -o $(OUT)/device_bind_pending_targets.elf
	objcopy -O binary --only-section=.text $(OUT)/device_bind_pending_targets.elf $@

test-cycle-device-bind-pending-targets: $(OUT)/reriff-match $(OUT)/device_bind_pending_targets.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-bind-pending-targets $(OUT)/device_bind_pending_targets.bin $(OUT)/device-bind-pending-targets-comparison.json

test-recovered: test-cycle-device-bind-pending-targets
.PHONY: test-cycle-device-bind-pending-targets

# Reviewed cycle reference: device-pending-targets-cleanup (assembly evidence only).
$(OUT)/device_pending_targets_cleanup.bin: native/device_pending_targets_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_pending_targets_cleanup.o
	ld -m elf_i386 -Ttext=0x4a4ea0 -e original_device_pending_targets_cleanup $(OUT)/device_pending_targets_cleanup.o -o $(OUT)/device_pending_targets_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/device_pending_targets_cleanup.elf $@

test-cycle-device-pending-targets-cleanup: $(OUT)/reriff-match $(OUT)/device_pending_targets_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-pending-targets-cleanup $(OUT)/device_pending_targets_cleanup.bin $(OUT)/device-pending-targets-cleanup-comparison.json

test-recovered: test-cycle-device-pending-targets-cleanup
.PHONY: test-cycle-device-pending-targets-cleanup

# Reviewed cycle reference: device-pending-targets-prepare (assembly evidence only).
$(OUT)/device_pending_targets_prepare.bin: native/device_pending_targets_prepare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_pending_targets_prepare.o
	ld -m elf_i386 -Ttext=0x4a4d80 -e original_device_pending_targets_prepare $(OUT)/device_pending_targets_prepare.o -o $(OUT)/device_pending_targets_prepare.elf
	objcopy -O binary --only-section=.text $(OUT)/device_pending_targets_prepare.elf $@

test-cycle-device-pending-targets-prepare: $(OUT)/reriff-match $(OUT)/device_pending_targets_prepare.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-pending-targets-prepare $(OUT)/device_pending_targets_prepare.bin $(OUT)/device-pending-targets-prepare-comparison.json

test-recovered: test-cycle-device-pending-targets-prepare
.PHONY: test-cycle-device-pending-targets-prepare

# Reviewed cycle reference: matrix-scaled-vector-accumulate (assembly evidence only).
$(OUT)/matrix_scaled_vector_accumulate.bin: native/matrix_scaled_vector_accumulate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix_scaled_vector_accumulate.o
	ld -m elf_i386 -Ttext=0x4385f0 -e original_matrix_scaled_vector_accumulate $(OUT)/matrix_scaled_vector_accumulate.o -o $(OUT)/matrix_scaled_vector_accumulate.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix_scaled_vector_accumulate.elf $@

test-cycle-matrix-scaled-vector-accumulate: $(OUT)/reriff-match $(OUT)/matrix_scaled_vector_accumulate.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix-scaled-vector-accumulate $(OUT)/matrix_scaled_vector_accumulate.bin $(OUT)/matrix-scaled-vector-accumulate-comparison.json

test-recovered: test-cycle-matrix-scaled-vector-accumulate
.PHONY: test-cycle-matrix-scaled-vector-accumulate

# Reviewed cycle reference: body-vector-pair-accumulate (assembly evidence only).
$(OUT)/body_vector_pair_accumulate.bin: native/body_vector_pair_accumulate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/body_vector_pair_accumulate.o
	ld -m elf_i386 -Ttext=0x4386f0 -e original_body_vector_pair_accumulate $(OUT)/body_vector_pair_accumulate.o -o $(OUT)/body_vector_pair_accumulate.elf
	objcopy -O binary --only-section=.text $(OUT)/body_vector_pair_accumulate.elf $@

test-cycle-body-vector-pair-accumulate: $(OUT)/reriff-match $(OUT)/body_vector_pair_accumulate.bin
	$(OUT)/reriff-match native-check "$(GAME)" body-vector-pair-accumulate $(OUT)/body_vector_pair_accumulate.bin $(OUT)/body-vector-pair-accumulate-comparison.json

test-recovered: test-cycle-body-vector-pair-accumulate
.PHONY: test-cycle-body-vector-pair-accumulate

# Reviewed cycle reference: box-support-without-margin (assembly evidence only).
$(OUT)/box_support_without_margin.bin: native/box_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_support_without_margin.o
	ld -m elf_i386 -Ttext=0x4389b0 -e original_box_support_without_margin $(OUT)/box_support_without_margin.o -o $(OUT)/box_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/box_support_without_margin.elf $@

test-cycle-box-support-without-margin: $(OUT)/reriff-match $(OUT)/box_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-support-without-margin $(OUT)/box_support_without_margin.bin $(OUT)/box-support-without-margin-comparison.json

test-recovered: test-cycle-box-support-without-margin
.PHONY: test-cycle-box-support-without-margin

# Reviewed cycle reference: record12-copy-assign-range (assembly evidence only).
$(OUT)/record12_copy_assign_range.bin: native/record12_copy_assign_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_copy_assign_range.o
	ld -m elf_i386 -Ttext=0x43e7a0 -e original_record12_copy_assign_range $(OUT)/record12_copy_assign_range.o -o $(OUT)/record12_copy_assign_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_copy_assign_range.elf $@

test-cycle-record12-copy-assign-range: $(OUT)/reriff-match $(OUT)/record12_copy_assign_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-copy-assign-range $(OUT)/record12_copy_assign_range.bin $(OUT)/record12-copy-assign-range-comparison.json

test-recovered: test-cycle-record12-copy-assign-range
.PHONY: test-cycle-record12-copy-assign-range

# Reviewed cycle reference: box-batched-support-without-margin (assembly evidence only).
$(OUT)/box_batched_support_without_margin.bin: native/box_batched_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_batched_support_without_margin.o
	ld -m elf_i386 -Ttext=0x438a20 -e original_box_batched_support_without_margin $(OUT)/box_batched_support_without_margin.o -o $(OUT)/box_batched_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/box_batched_support_without_margin.elf $@

test-cycle-box-batched-support-without-margin: $(OUT)/reriff-match $(OUT)/box_batched_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-batched-support-without-margin $(OUT)/box_batched_support_without_margin.bin $(OUT)/box-batched-support-without-margin-comparison.json

test-recovered: test-cycle-box-batched-support-without-margin
.PHONY: test-cycle-box-batched-support-without-margin

# Reviewed cycle reference: box-vertex-without-margin (assembly evidence only).
$(OUT)/box_vertex_without_margin.bin: native/box_vertex_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_vertex_without_margin.o
	ld -m elf_i386 -Ttext=0x438d30 -e original_box_vertex_without_margin $(OUT)/box_vertex_without_margin.o -o $(OUT)/box_vertex_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/box_vertex_without_margin.elf $@

test-cycle-box-vertex-without-margin: $(OUT)/reriff-match $(OUT)/box_vertex_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-vertex-without-margin $(OUT)/box_vertex_without_margin.bin $(OUT)/box-vertex-without-margin-comparison.json

test-recovered: test-cycle-box-vertex-without-margin
.PHONY: test-cycle-box-vertex-without-margin

# Reviewed cycle reference: convex-internal-shape-serialize (assembly evidence only).
$(OUT)/convex_internal_shape_serialize.bin: native/convex_internal_shape_serialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_serialize.o
	ld -m elf_i386 -Ttext=0x438870 -e original_convex_internal_shape_serialize $(OUT)/convex_internal_shape_serialize.o -o $(OUT)/convex_internal_shape_serialize.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_serialize.elf $@

test-cycle-convex-internal-shape-serialize: $(OUT)/reriff-match $(OUT)/convex_internal_shape_serialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-serialize $(OUT)/convex_internal_shape_serialize.bin $(OUT)/convex-internal-shape-serialize-comparison.json

test-recovered: test-cycle-convex-internal-shape-serialize
.PHONY: test-cycle-convex-internal-shape-serialize

# Reviewed cycle reference: box-point-inside-tolerance (assembly evidence only).
$(OUT)/box_point_inside_tolerance.bin: native/box_point_inside_tolerance.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_point_inside_tolerance.o
	ld -m elf_i386 -Ttext=0x438fe0 -e original_box_point_inside_tolerance $(OUT)/box_point_inside_tolerance.o -o $(OUT)/box_point_inside_tolerance.elf
	objcopy -O binary --only-section=.text $(OUT)/box_point_inside_tolerance.elf $@

test-cycle-box-point-inside-tolerance: $(OUT)/reriff-match $(OUT)/box_point_inside_tolerance.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-point-inside-tolerance $(OUT)/box_point_inside_tolerance.bin $(OUT)/box-point-inside-tolerance-comparison.json

test-recovered: test-cycle-box-point-inside-tolerance
.PHONY: test-cycle-box-point-inside-tolerance

# Reviewed cycle reference: shape-scaled-margin (assembly evidence only).
$(OUT)/shape_scaled_margin.bin: native/shape_scaled_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shape_scaled_margin.o
	ld -m elf_i386 -Ttext=0x4391c0 -e original_shape_scaled_margin $(OUT)/shape_scaled_margin.o -o $(OUT)/shape_scaled_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/shape_scaled_margin.elf $@

test-cycle-shape-scaled-margin: $(OUT)/reriff-match $(OUT)/shape_scaled_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" shape-scaled-margin $(OUT)/shape_scaled_margin.bin $(OUT)/shape-scaled-margin-comparison.json

test-recovered: test-cycle-shape-scaled-margin
.PHONY: test-cycle-shape-scaled-margin

# Reviewed cycle reference: four-record20-initialize (assembly evidence only).
$(OUT)/four_record20_initialize.bin: native/four_record20_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/four_record20_initialize.o
	ld -m elf_i386 -Ttext=0x439220 -e original_four_record20_initialize $(OUT)/four_record20_initialize.o -o $(OUT)/four_record20_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/four_record20_initialize.elf $@

test-cycle-four-record20-initialize: $(OUT)/reriff-match $(OUT)/four_record20_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" four-record20-initialize $(OUT)/four_record20_initialize.bin $(OUT)/four-record20-initialize-comparison.json

test-recovered: test-cycle-four-record20-initialize
.PHONY: test-cycle-four-record20-initialize

# Reviewed cycle reference: collision-shape-vtable-reset (assembly evidence only).
$(OUT)/collision_shape_vtable_reset.bin: native/collision_shape_vtable_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_vtable_reset.o
	ld -m elf_i386 -Ttext=0x4391d0 -e original_collision_shape_vtable_reset $(OUT)/collision_shape_vtable_reset.o -o $(OUT)/collision_shape_vtable_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_vtable_reset.elf $@

test-cycle-collision-shape-vtable-reset: $(OUT)/reriff-match $(OUT)/collision_shape_vtable_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-vtable-reset $(OUT)/collision_shape_vtable_reset.bin $(OUT)/collision-shape-vtable-reset-comparison.json

test-recovered: test-cycle-collision-shape-vtable-reset
.PHONY: test-cycle-collision-shape-vtable-reset

# Reviewed cycle reference: named-record-narrow-data (assembly evidence only).
$(OUT)/named_record_narrow_data.bin: native/named_record_narrow_data.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/named_record_narrow_data.o
	ld -m elf_i386 -Ttext=0x44bf30 -e original_named_record_narrow_data $(OUT)/named_record_narrow_data.o -o $(OUT)/named_record_narrow_data.elf
	objcopy -O binary --only-section=.text $(OUT)/named_record_narrow_data.elf $@

test-cycle-named-record-narrow-data: $(OUT)/reriff-match $(OUT)/named_record_narrow_data.bin
	$(OUT)/reriff-match native-check "$(GAME)" named-record-narrow-data $(OUT)/named_record_narrow_data.bin $(OUT)/named-record-narrow-data-comparison.json

test-recovered: test-cycle-named-record-narrow-data
.PHONY: test-cycle-named-record-narrow-data

# Reviewed cycle reference: triangle-info-map-serialized-size (assembly evidence only).
$(OUT)/triangle_info_map_serialized_size.bin: native/triangle_info_map_serialized_size.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/triangle_info_map_serialized_size.o
	ld -m elf_i386 -Ttext=0x4393e0 -e original_triangle_info_map_serialized_size $(OUT)/triangle_info_map_serialized_size.o -o $(OUT)/triangle_info_map_serialized_size.elf
	objcopy -O binary --only-section=.text $(OUT)/triangle_info_map_serialized_size.elf $@

test-cycle-triangle-info-map-serialized-size: $(OUT)/reriff-match $(OUT)/triangle_info_map_serialized_size.bin
	$(OUT)/reriff-match native-check "$(GAME)" triangle-info-map-serialized-size $(OUT)/triangle_info_map_serialized_size.bin $(OUT)/triangle-info-map-serialized-size-comparison.json

test-recovered: test-cycle-triangle-info-map-serialized-size
.PHONY: test-cycle-triangle-info-map-serialized-size

# Reviewed cycle reference: narrow-path-slashes-normalize (assembly evidence only).
$(OUT)/narrow_path_slashes_normalize.bin: native/narrow_path_slashes_normalize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_path_slashes_normalize.o
	ld -m elf_i386 -Ttext=0x43fd50 -e original_narrow_path_slashes_normalize $(OUT)/narrow_path_slashes_normalize.o -o $(OUT)/narrow_path_slashes_normalize.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_path_slashes_normalize.elf $@

test-cycle-narrow-path-slashes-normalize: $(OUT)/reriff-match $(OUT)/narrow_path_slashes_normalize.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-path-slashes-normalize $(OUT)/narrow_path_slashes_normalize.bin $(OUT)/narrow-path-slashes-normalize-comparison.json

test-recovered: test-cycle-narrow-path-slashes-normalize
.PHONY: test-cycle-narrow-path-slashes-normalize

# Reviewed cycle reference: box-shape-name (assembly evidence only).
$(OUT)/box_shape_name.bin: native/box_shape_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_name.o
	ld -m elf_i386 -Ttext=0x439080 -e original_box_shape_name $(OUT)/box_shape_name.o -o $(OUT)/box_shape_name.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_name.elf $@

test-cycle-box-shape-name: $(OUT)/reriff-match $(OUT)/box_shape_name.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-name $(OUT)/box_shape_name.bin $(OUT)/box-shape-name-comparison.json

test-recovered: test-cycle-box-shape-name
.PHONY: test-cycle-box-shape-name

# Reviewed cycle reference: box-shape-construct (assembly evidence only).
$(OUT)/box_shape_construct.bin: native/box_shape_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_construct.o
	ld -m elf_i386 -Ttext=0x438ab0 -e original_box_shape_construct $(OUT)/box_shape_construct.o -o $(OUT)/box_shape_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_construct.elf $@

test-cycle-box-shape-construct: $(OUT)/reriff-match $(OUT)/box_shape_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-construct $(OUT)/box_shape_construct.bin $(OUT)/box-shape-construct-comparison.json

test-recovered: test-cycle-box-shape-construct
.PHONY: test-cycle-box-shape-construct

# Reviewed cycle reference: convex-internal-shape-margin (assembly evidence only).
$(OUT)/convex_internal_shape_margin.bin: native/convex_internal_shape_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_margin.o
	ld -m elf_i386 -Ttext=0x438850 -e original_convex_internal_shape_margin $(OUT)/convex_internal_shape_margin.o -o $(OUT)/convex_internal_shape_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_margin.elf $@

test-cycle-convex-internal-shape-margin: $(OUT)/reriff-match $(OUT)/convex_internal_shape_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-margin $(OUT)/convex_internal_shape_margin.bin $(OUT)/convex-internal-shape-margin-comparison.json

test-recovered: test-cycle-convex-internal-shape-margin
.PHONY: test-cycle-convex-internal-shape-margin

# Reviewed cycle reference: convex-internal-shape-scaling-pointer (assembly evidence only).
$(OUT)/convex_internal_shape_scaling_pointer.bin: native/convex_internal_shape_scaling_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_scaling_pointer.o
	ld -m elf_i386 -Ttext=0x438820 -e original_convex_internal_shape_scaling_pointer $(OUT)/convex_internal_shape_scaling_pointer.o -o $(OUT)/convex_internal_shape_scaling_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_scaling_pointer.elf $@

test-cycle-convex-internal-shape-scaling-pointer: $(OUT)/reriff-match $(OUT)/convex_internal_shape_scaling_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-scaling-pointer $(OUT)/convex_internal_shape_scaling_pointer.bin $(OUT)/convex-internal-shape-scaling-pointer-comparison.json

test-recovered: test-cycle-convex-internal-shape-scaling-pointer
.PHONY: test-cycle-convex-internal-shape-scaling-pointer

# Reviewed cycle reference: convex-internal-shape-serialized-size (assembly evidence only).
$(OUT)/convex_internal_shape_serialized_size.bin: native/convex_internal_shape_serialized_size.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_serialized_size.o
	ld -m elf_i386 -Ttext=0x438860 -e original_convex_internal_shape_serialized_size $(OUT)/convex_internal_shape_serialized_size.o -o $(OUT)/convex_internal_shape_serialized_size.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_serialized_size.elf $@

test-cycle-convex-internal-shape-serialized-size: $(OUT)/reriff-match $(OUT)/convex_internal_shape_serialized_size.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-serialized-size $(OUT)/convex_internal_shape_serialized_size.bin $(OUT)/convex-internal-shape-serialized-size-comparison.json

test-recovered: test-cycle-convex-internal-shape-serialized-size
.PHONY: test-cycle-convex-internal-shape-serialized-size

# Reviewed cycle reference: convex-internal-shape-set-margin (assembly evidence only).
$(OUT)/convex_internal_shape_set_margin.bin: native/convex_internal_shape_set_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_set_margin.o
	ld -m elf_i386 -Ttext=0x438830 -e original_convex_internal_shape_set_margin $(OUT)/convex_internal_shape_set_margin.o -o $(OUT)/convex_internal_shape_set_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_set_margin.elf $@

test-cycle-convex-internal-shape-set-margin: $(OUT)/reriff-match $(OUT)/convex_internal_shape_set_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-set-margin $(OUT)/convex_internal_shape_set_margin.bin $(OUT)/convex-internal-shape-set-margin-comparison.json

test-recovered: test-cycle-convex-internal-shape-set-margin
.PHONY: test-cycle-convex-internal-shape-set-margin

# Reviewed cycle reference: record-pointer-stack-recycle (assembly evidence only).
$(OUT)/record_pointer_stack_recycle.bin: native/record_pointer_stack_recycle.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record_pointer_stack_recycle.o
	ld -m elf_i386 -Ttext=0x548b30 -e original_record_pointer_stack_recycle $(OUT)/record_pointer_stack_recycle.o -o $(OUT)/record_pointer_stack_recycle.elf
	objcopy -O binary --only-section=.text $(OUT)/record_pointer_stack_recycle.elf $@

test-cycle-record-pointer-stack-recycle: $(OUT)/reriff-match $(OUT)/record_pointer_stack_recycle.bin
	$(OUT)/reriff-match native-check "$(GAME)" record-pointer-stack-recycle $(OUT)/record_pointer_stack_recycle.bin $(OUT)/record-pointer-stack-recycle-comparison.json

test-recovered: test-cycle-record-pointer-stack-recycle
.PHONY: test-cycle-record-pointer-stack-recycle

# Reviewed cycle reference: box-shape-count-six (assembly evidence only).
$(OUT)/box_shape_count_six.bin: native/box_shape_count_six.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_count_six.o
	ld -m elf_i386 -Ttext=0x438d00 -e original_box_shape_count_six $(OUT)/box_shape_count_six.o -o $(OUT)/box_shape_count_six.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_count_six.elf $@

test-cycle-box-shape-count-six: $(OUT)/reriff-match $(OUT)/box_shape_count_six.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-count-six $(OUT)/box_shape_count_six.bin $(OUT)/box-shape-count-six-comparison.json

test-recovered: test-cycle-box-shape-count-six
.PHONY: test-cycle-box-shape-count-six

# Reviewed cycle reference: box-shape-vertex-count (assembly evidence only).
$(OUT)/box_shape_vertex_count.bin: native/box_shape_vertex_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_vertex_count.o
	ld -m elf_i386 -Ttext=0x438d10 -e original_box_shape_vertex_count $(OUT)/box_shape_vertex_count.o -o $(OUT)/box_shape_vertex_count.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_vertex_count.elf $@

test-cycle-box-shape-vertex-count: $(OUT)/reriff-match $(OUT)/box_shape_vertex_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-vertex-count $(OUT)/box_shape_vertex_count.bin $(OUT)/box-shape-vertex-count-comparison.json

test-recovered: test-cycle-box-shape-vertex-count
.PHONY: test-cycle-box-shape-vertex-count

# Reviewed cycle reference: box-shape-edge-count (assembly evidence only).
$(OUT)/box_shape_edge_count.bin: native/box_shape_edge_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_edge_count.o
	ld -m elf_i386 -Ttext=0x438d20 -e original_box_shape_edge_count $(OUT)/box_shape_edge_count.o -o $(OUT)/box_shape_edge_count.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_edge_count.elf $@

test-cycle-box-shape-edge-count: $(OUT)/reriff-match $(OUT)/box_shape_edge_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-edge-count $(OUT)/box_shape_edge_count.bin $(OUT)/box-shape-edge-count-comparison.json

test-recovered: test-cycle-box-shape-edge-count
.PHONY: test-cycle-box-shape-edge-count

# Reviewed cycle reference: body-construction-record-initialize (assembly evidence only).
$(OUT)/body_construction_record_initialize.bin: native/body_construction_record_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/body_construction_record_initialize.o
	ld -m elf_i386 -Ttext=0x438560 -e original_body_construction_record_initialize $(OUT)/body_construction_record_initialize.o -o $(OUT)/body_construction_record_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/body_construction_record_initialize.elf $@

test-cycle-body-construction-record-initialize: $(OUT)/reriff-match $(OUT)/body_construction_record_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" body-construction-record-initialize $(OUT)/body_construction_record_initialize.bin $(OUT)/body-construction-record-initialize-comparison.json

test-recovered: test-cycle-body-construction-record-initialize
.PHONY: test-cycle-body-construction-record-initialize

# Reviewed cycle reference: box-support-with-margin (assembly evidence only).
$(OUT)/box_support_with_margin.bin: native/box_support_with_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_support_with_margin.o
	ld -m elf_i386 -Ttext=0x4388f0 -e original_box_support_with_margin $(OUT)/box_support_with_margin.o -o $(OUT)/box_support_with_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/box_support_with_margin.elf $@

test-cycle-box-support-with-margin: $(OUT)/reriff-match $(OUT)/box_support_with_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-support-with-margin $(OUT)/box_support_with_margin.bin $(OUT)/box-support-with-margin-comparison.json

test-recovered: test-cycle-box-support-with-margin
.PHONY: test-cycle-box-support-with-margin

# Reviewed cycle reference: box-local-inertia (assembly evidence only).
$(OUT)/box_local_inertia.bin: native/box_local_inertia.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_local_inertia.o
	ld -m elf_i386 -Ttext=0x47b070 -e original_box_local_inertia $(OUT)/box_local_inertia.o -o $(OUT)/box_local_inertia.elf
	objcopy -O binary --only-section=.text $(OUT)/box_local_inertia.elf $@

test-cycle-box-local-inertia: $(OUT)/reriff-match $(OUT)/box_local_inertia.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-local-inertia $(OUT)/box_local_inertia.bin $(OUT)/box-local-inertia-comparison.json

test-recovered: test-cycle-box-local-inertia
.PHONY: test-cycle-box-local-inertia

# Reviewed cycle reference: convex-internal-shape-set-scaling (assembly evidence only).
$(OUT)/convex_internal_shape_set_scaling.bin: native/convex_internal_shape_set_scaling.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_set_scaling.o
	ld -m elf_i386 -Ttext=0x47b100 -e original_convex_internal_shape_set_scaling $(OUT)/convex_internal_shape_set_scaling.o -o $(OUT)/convex_internal_shape_set_scaling.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_set_scaling.elf $@

test-cycle-convex-internal-shape-set-scaling: $(OUT)/reriff-match $(OUT)/convex_internal_shape_set_scaling.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-set-scaling $(OUT)/convex_internal_shape_set_scaling.bin $(OUT)/convex-internal-shape-set-scaling-comparison.json

test-recovered: test-cycle-convex-internal-shape-set-scaling
.PHONY: test-cycle-convex-internal-shape-set-scaling

# Reviewed cycle reference: convex-internal-shape-aabb (assembly evidence only).
$(OUT)/convex_internal_shape_aabb.bin: native/convex_internal_shape_aabb.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_internal_shape_aabb.o
	ld -m elf_i386 -Ttext=0x47b040 -e original_convex_internal_shape_aabb $(OUT)/convex_internal_shape_aabb.o -o $(OUT)/convex_internal_shape_aabb.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_internal_shape_aabb.elf $@

test-cycle-convex-internal-shape-aabb: $(OUT)/reriff-match $(OUT)/convex_internal_shape_aabb.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-internal-shape-aabb $(OUT)/convex_internal_shape_aabb.bin $(OUT)/convex-internal-shape-aabb-comparison.json

test-recovered: test-cycle-convex-internal-shape-aabb
.PHONY: test-cycle-convex-internal-shape-aabb

# Reviewed cycle reference: transform-half-extents-aabb (assembly evidence only).
$(OUT)/transform_half_extents_aabb.bin: native/transform_half_extents_aabb.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/transform_half_extents_aabb.o
	ld -m elf_i386 -Ttext=0x47aec0 -e original_transform_half_extents_aabb $(OUT)/transform_half_extents_aabb.o -o $(OUT)/transform_half_extents_aabb.elf
	objcopy -O binary --only-section=.text $(OUT)/transform_half_extents_aabb.elf $@

test-cycle-transform-half-extents-aabb: $(OUT)/reriff-match $(OUT)/transform_half_extents_aabb.bin
	$(OUT)/reriff-match native-check "$(GAME)" transform-half-extents-aabb $(OUT)/transform_half_extents_aabb.bin $(OUT)/transform-half-extents-aabb-comparison.json

test-recovered: test-cycle-transform-half-extents-aabb
.PHONY: test-cycle-transform-half-extents-aabb

# Reviewed cycle reference: matrix3-absolute (assembly evidence only).
$(OUT)/matrix3_absolute.bin: native/matrix3_absolute.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix3_absolute.o
	ld -m elf_i386 -Ttext=0x47ad90 -e original_matrix3_absolute $(OUT)/matrix3_absolute.o -o $(OUT)/matrix3_absolute.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix3_absolute.elf $@

test-cycle-matrix3-absolute: $(OUT)/reriff-match $(OUT)/matrix3_absolute.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix3-absolute $(OUT)/matrix3_absolute.bin $(OUT)/matrix3-absolute-comparison.json

test-recovered: test-cycle-matrix3-absolute
.PHONY: test-cycle-matrix3-absolute

# Reviewed cycle reference: collision-shape-contact-threshold (assembly evidence only).
$(OUT)/collision_shape_contact_threshold.bin: native/collision_shape_contact_threshold.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_contact_threshold.o
	ld -m elf_i386 -Ttext=0x47c190 -e original_collision_shape_contact_threshold $(OUT)/collision_shape_contact_threshold.o -o $(OUT)/collision_shape_contact_threshold.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_contact_threshold.elf $@

test-cycle-collision-shape-contact-threshold: $(OUT)/reriff-match $(OUT)/collision_shape_contact_threshold.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-contact-threshold $(OUT)/collision_shape_contact_threshold.bin $(OUT)/collision-shape-contact-threshold-comparison.json

test-recovered: test-cycle-collision-shape-contact-threshold
.PHONY: test-cycle-collision-shape-contact-threshold

# Reviewed cycle reference: random-range-inclusive (assembly evidence only).
$(OUT)/random_range_inclusive.bin: native/random_range_inclusive.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/random_range_inclusive.o
	ld -m elf_i386 -Ttext=0x478850 -e original_random_range_inclusive $(OUT)/random_range_inclusive.o -o $(OUT)/random_range_inclusive.elf
	objcopy -O binary --only-section=.text $(OUT)/random_range_inclusive.elf $@

test-cycle-random-range-inclusive: $(OUT)/reriff-match $(OUT)/random_range_inclusive.bin
	$(OUT)/reriff-match native-check "$(GAME)" random-range-inclusive $(OUT)/random_range_inclusive.bin $(OUT)/random-range-inclusive-comparison.json

test-recovered: test-cycle-random-range-inclusive
.PHONY: test-cycle-random-range-inclusive

# Reviewed cycle reference: shared-noop-pop4 (assembly evidence only).
$(OUT)/shared_noop_pop4.bin: native/shared_noop_pop4.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shared_noop_pop4.o
	ld -m elf_i386 -Ttext=0x4141c0 -e original_shared_noop_pop4 $(OUT)/shared_noop_pop4.o -o $(OUT)/shared_noop_pop4.elf
	objcopy -O binary --only-section=.text $(OUT)/shared_noop_pop4.elf $@

test-cycle-shared-noop-pop4: $(OUT)/reriff-match $(OUT)/shared_noop_pop4.bin
	$(OUT)/reriff-match native-check "$(GAME)" shared-noop-pop4 $(OUT)/shared_noop_pop4.bin $(OUT)/shared-noop-pop4-comparison.json

test-recovered: test-cycle-shared-noop-pop4
.PHONY: test-cycle-shared-noop-pop4

# Reviewed cycle reference: record12-range-copy-construct (assembly evidence only).
$(OUT)/record12_range_copy_construct.bin: native/record12_range_copy_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_range_copy_construct.o
	ld -m elf_i386 -Ttext=0x437fe0 -e original_record12_range_copy_construct $(OUT)/record12_range_copy_construct.o -o $(OUT)/record12_range_copy_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_range_copy_construct.elf $@

test-cycle-record12-range-copy-construct: $(OUT)/reriff-match $(OUT)/record12_range_copy_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-range-copy-construct $(OUT)/record12_range_copy_construct.bin $(OUT)/record12-range-copy-construct-comparison.json

test-recovered: test-cycle-record12-range-copy-construct
.PHONY: test-cycle-record12-range-copy-construct

# Reviewed cycle reference: box-shape-set-scaling (assembly evidence only).
$(OUT)/box_shape_set_scaling.bin: native/box_shape_set_scaling.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_set_scaling.o
	ld -m elf_i386 -Ttext=0x438b40 -e original_box_shape_set_scaling $(OUT)/box_shape_set_scaling.o -o $(OUT)/box_shape_set_scaling.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_set_scaling.elf $@

test-cycle-box-shape-set-scaling: $(OUT)/reriff-match $(OUT)/box_shape_set_scaling.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-set-scaling $(OUT)/box_shape_set_scaling.bin $(OUT)/box-shape-set-scaling-comparison.json

test-recovered: test-cycle-box-shape-set-scaling
.PHONY: test-cycle-box-shape-set-scaling

# Reviewed cycle reference: convex-aabb-caching-shape-construct (assembly evidence only).
$(OUT)/convex_aabb_caching_shape_construct.bin: native/convex_aabb_caching_shape_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_aabb_caching_shape_construct.o
	ld -m elf_i386 -Ttext=0x47b640 -e original_convex_aabb_caching_shape_construct $(OUT)/convex_aabb_caching_shape_construct.o -o $(OUT)/convex_aabb_caching_shape_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_aabb_caching_shape_construct.elf $@

test-cycle-convex-aabb-caching-shape-construct: $(OUT)/reriff-match $(OUT)/convex_aabb_caching_shape_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-aabb-caching-shape-construct $(OUT)/convex_aabb_caching_shape_construct.bin $(OUT)/convex-aabb-caching-shape-construct-comparison.json

test-recovered: test-cycle-convex-aabb-caching-shape-construct
.PHONY: test-cycle-convex-aabb-caching-shape-construct

# Reviewed cycle reference: box-shape-deleting-destructor (assembly evidence only).
$(OUT)/box_shape_deleting_destructor.bin: native/box_shape_deleting_destructor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_shape_deleting_destructor.o
	ld -m elf_i386 -Ttext=0x439180 -e original_box_shape_deleting_destructor $(OUT)/box_shape_deleting_destructor.o -o $(OUT)/box_shape_deleting_destructor.elf
	objcopy -O binary --only-section=.text $(OUT)/box_shape_deleting_destructor.elf $@

test-cycle-box-shape-deleting-destructor: $(OUT)/reriff-match $(OUT)/box_shape_deleting_destructor.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-shape-deleting-destructor $(OUT)/box_shape_deleting_destructor.bin $(OUT)/box-shape-deleting-destructor-comparison.json

test-recovered: test-cycle-box-shape-deleting-destructor
.PHONY: test-cycle-box-shape-deleting-destructor

# Reviewed cycle reference: triangle-info-map-destruct (assembly evidence only).
$(OUT)/triangle_info_map_destruct.bin: native/triangle_info_map_destruct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/triangle_info_map_destruct.o
	ld -m elf_i386 -Ttext=0x4391e0 -e original_triangle_info_map_destruct $(OUT)/triangle_info_map_destruct.o -o $(OUT)/triangle_info_map_destruct.elf
	objcopy -O binary --only-section=.text $(OUT)/triangle_info_map_destruct.elf $@

test-cycle-triangle-info-map-destruct: $(OUT)/reriff-match $(OUT)/triangle_info_map_destruct.bin
	$(OUT)/reriff-match native-check "$(GAME)" triangle-info-map-destruct $(OUT)/triangle_info_map_destruct.bin $(OUT)/triangle-info-map-destruct-comparison.json

test-recovered: test-cycle-triangle-info-map-destruct
.PHONY: test-cycle-triangle-info-map-destruct

# Reviewed cycle reference: polyhedral-convex-aabb-construct (assembly evidence only).
$(OUT)/polyhedral_convex_aabb_construct.bin: native/polyhedral_convex_aabb_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/polyhedral_convex_aabb_construct.o
	ld -m elf_i386 -Ttext=0x47bec0 -e original_polyhedral_convex_aabb_construct $(OUT)/polyhedral_convex_aabb_construct.o -o $(OUT)/polyhedral_convex_aabb_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/polyhedral_convex_aabb_construct.elf $@

test-cycle-polyhedral-convex-aabb-construct: $(OUT)/reriff-match $(OUT)/polyhedral_convex_aabb_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" polyhedral-convex-aabb-construct $(OUT)/polyhedral_convex_aabb_construct.bin $(OUT)/polyhedral-convex-aabb-construct-comparison.json

test-recovered: test-cycle-polyhedral-convex-aabb-construct
.PHONY: test-cycle-polyhedral-convex-aabb-construct

# Reviewed cycle reference: polyhedral-cached-aabb-recalculate (assembly evidence only).
$(OUT)/polyhedral_cached_aabb_recalculate.bin: native/polyhedral_cached_aabb_recalculate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/polyhedral_cached_aabb_recalculate.o
	ld -m elf_i386 -Ttext=0x47bf40 -e original_polyhedral_cached_aabb_recalculate $(OUT)/polyhedral_cached_aabb_recalculate.o -o $(OUT)/polyhedral_cached_aabb_recalculate.elf
	objcopy -O binary --only-section=.text $(OUT)/polyhedral_cached_aabb_recalculate.elf $@

test-cycle-polyhedral-cached-aabb-recalculate: $(OUT)/reriff-match $(OUT)/polyhedral_cached_aabb_recalculate.bin
	$(OUT)/reriff-match native-check "$(GAME)" polyhedral-cached-aabb-recalculate $(OUT)/polyhedral_cached_aabb_recalculate.bin $(OUT)/polyhedral-cached-aabb-recalculate-comparison.json

test-recovered: test-cycle-polyhedral-cached-aabb-recalculate
.PHONY: test-cycle-polyhedral-cached-aabb-recalculate

# Reviewed cycle reference: physics-allocation-release (assembly evidence only).
$(OUT)/physics_allocation_release.bin: native/physics_allocation_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/physics_allocation_release.o
	ld -m elf_i386 -Ttext=0x438540 -e original_physics_allocation_release $(OUT)/physics_allocation_release.o -o $(OUT)/physics_allocation_release.elf
	objcopy -O binary --only-section=.text $(OUT)/physics_allocation_release.elf $@

test-cycle-physics-allocation-release: $(OUT)/reriff-match $(OUT)/physics_allocation_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" physics-allocation-release $(OUT)/physics_allocation_release.bin $(OUT)/physics-allocation-release-comparison.json

test-recovered: test-cycle-physics-allocation-release
.PHONY: test-cycle-physics-allocation-release

# Reviewed cycle reference: signed64-divide (assembly evidence only).
$(OUT)/signed64_divide.bin: native/signed64_divide.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/signed64_divide.o
	ld -m elf_i386 -Ttext=0x8f9830 -e original_signed64_divide $(OUT)/signed64_divide.o -o $(OUT)/signed64_divide.elf
	objcopy -O binary --only-section=.text $(OUT)/signed64_divide.elf $@

test-cycle-signed64-divide: $(OUT)/reriff-match $(OUT)/signed64_divide.bin
	$(OUT)/reriff-match native-check "$(GAME)" signed64-divide $(OUT)/signed64_divide.bin $(OUT)/signed64-divide-comparison.json

test-recovered: test-cycle-signed64-divide
.PHONY: test-cycle-signed64-divide

# Reviewed cycle reference: box-plane-equation (assembly evidence only).
$(OUT)/box_plane_equation.bin: native/box_plane_equation.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/box_plane_equation.o
	ld -m elf_i386 -Ttext=0x438df0 -e original_box_plane_equation $(OUT)/box_plane_equation.o -o $(OUT)/box_plane_equation.elf
	objcopy -O binary --only-section=.text $(OUT)/box_plane_equation.elf $@

test-cycle-box-plane-equation: $(OUT)/reriff-match $(OUT)/box_plane_equation.bin
	$(OUT)/reriff-match native-check "$(GAME)" box-plane-equation $(OUT)/box_plane_equation.bin $(OUT)/box-plane-equation-comparison.json

test-recovered: test-cycle-box-plane-equation
.PHONY: test-cycle-box-plane-equation

# Reviewed cycle reference: random-sign-float (assembly evidence only).
$(OUT)/random_sign_float.bin: native/random_sign_float.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/random_sign_float.o
	ld -m elf_i386 -Ttext=0x478810 -e original_random_sign_float $(OUT)/random_sign_float.o -o $(OUT)/random_sign_float.elf
	objcopy -O binary --only-section=.text $(OUT)/random_sign_float.elf $@

test-cycle-random-sign-float: $(OUT)/reriff-match $(OUT)/random_sign_float.bin
	$(OUT)/reriff-match native-check "$(GAME)" random-sign-float $(OUT)/random_sign_float.bin $(OUT)/random-sign-float-comparison.json

test-recovered: test-cycle-random-sign-float
.PHONY: test-cycle-random-sign-float

# Reviewed cycle reference: random-unit-float (assembly evidence only).
$(OUT)/random_unit_float.bin: native/random_unit_float.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/random_unit_float.o
	ld -m elf_i386 -Ttext=0x4787b0 -e original_random_unit_float $(OUT)/random_unit_float.o -o $(OUT)/random_unit_float.elf
	objcopy -O binary --only-section=.text $(OUT)/random_unit_float.elf $@

test-cycle-random-unit-float: $(OUT)/reriff-match $(OUT)/random_unit_float.bin
	$(OUT)/reriff-match native-check "$(GAME)" random-unit-float $(OUT)/random_unit_float.bin $(OUT)/random-unit-float-comparison.json

test-recovered: test-cycle-random-unit-float
.PHONY: test-cycle-random-unit-float

# Reviewed cycle reference: packed-double-floor-sse2 (assembly evidence only).
$(OUT)/packed_double_floor_sse2.bin: native/packed_double_floor_sse2.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/packed_double_floor_sse2.o
	ld -m elf_i386 -Ttext=0x8fc3c0 -e original_packed_double_floor_sse2 $(OUT)/packed_double_floor_sse2.o -o $(OUT)/packed_double_floor_sse2.elf
	objcopy -O binary --only-section=.text $(OUT)/packed_double_floor_sse2.elf $@

test-cycle-packed-double-floor-sse2: $(OUT)/reriff-match $(OUT)/packed_double_floor_sse2.bin
	$(OUT)/reriff-match native-check "$(GAME)" packed-double-floor-sse2 $(OUT)/packed_double_floor_sse2.bin $(OUT)/packed-double-floor-sse2-comparison.json

test-recovered: test-cycle-packed-double-floor-sse2
.PHONY: test-cycle-packed-double-floor-sse2

# Reviewed cycle reference: packed-double-floor-sse41 (assembly evidence only).
$(OUT)/packed_double_floor_sse41.bin: native/packed_double_floor_sse41.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/packed_double_floor_sse41.o
	ld -m elf_i386 -Ttext=0x8fc410 -e original_packed_double_floor_sse41 $(OUT)/packed_double_floor_sse41.o -o $(OUT)/packed_double_floor_sse41.elf
	objcopy -O binary --only-section=.text $(OUT)/packed_double_floor_sse41.elf $@

test-cycle-packed-double-floor-sse41: $(OUT)/reriff-match $(OUT)/packed_double_floor_sse41.bin
	$(OUT)/reriff-match native-check "$(GAME)" packed-double-floor-sse41 $(OUT)/packed_double_floor_sse41.bin $(OUT)/packed-double-floor-sse41-comparison.json

test-recovered: test-cycle-packed-double-floor-sse41
.PHONY: test-cycle-packed-double-floor-sse41

# Reviewed cycle reference: ray-callback-filter-test (assembly evidence only).
$(OUT)/ray_callback_filter_test.bin: native/ray_callback_filter_test.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/ray_callback_filter_test.o
	ld -m elf_i386 -Ttext=0x4270e0 -e original_ray_callback_filter_test $(OUT)/ray_callback_filter_test.o -o $(OUT)/ray_callback_filter_test.elf
	objcopy -O binary --only-section=.text $(OUT)/ray_callback_filter_test.elf $@

test-cycle-ray-callback-filter-test: $(OUT)/reriff-match $(OUT)/ray_callback_filter_test.bin
	$(OUT)/reriff-match native-check "$(GAME)" ray-callback-filter-test $(OUT)/ray_callback_filter_test.bin $(OUT)/ray-callback-filter-test-comparison.json

test-recovered: test-cycle-ray-callback-filter-test
.PHONY: test-cycle-ray-callback-filter-test

# Reviewed cycle reference: nested-resource44-count (assembly evidence only).
$(OUT)/nested_resource44_count.bin: native/nested_resource44_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/nested_resource44_count.o
	ld -m elf_i386 -Ttext=0x512c80 -e original_nested_resource44_count $(OUT)/nested_resource44_count.o -o $(OUT)/nested_resource44_count.elf
	objcopy -O binary --only-section=.text $(OUT)/nested_resource44_count.elf $@

test-cycle-nested-resource44-count: $(OUT)/reriff-match $(OUT)/nested_resource44_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" nested-resource44-count $(OUT)/nested_resource44_count.bin $(OUT)/nested-resource44-count-comparison.json

test-recovered: test-cycle-nested-resource44-count
.PHONY: test-cycle-nested-resource44-count

# Reviewed cycle reference: packed-double-floor-dispatch (assembly evidence only).
$(OUT)/packed_double_floor_dispatch.bin: native/packed_double_floor_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/packed_double_floor_dispatch.o
	ld -m elf_i386 -Ttext=0x8fc1b0 -e original_packed_double_floor_dispatch $(OUT)/packed_double_floor_dispatch.o -o $(OUT)/packed_double_floor_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/packed_double_floor_dispatch.elf $@

test-cycle-packed-double-floor-dispatch: $(OUT)/reriff-match $(OUT)/packed_double_floor_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" packed-double-floor-dispatch $(OUT)/packed_double_floor_dispatch.bin $(OUT)/packed-double-floor-dispatch-comparison.json

test-recovered: test-cycle-packed-double-floor-dispatch
.PHONY: test-cycle-packed-double-floor-dispatch

# Reviewed cycle reference: shared-zero-return (assembly evidence only).
$(OUT)/shared_zero_return.bin: native/shared_zero_return.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shared_zero_return.o
	ld -m elf_i386 -Ttext=0x4142f0 -e original_shared_zero_return $(OUT)/shared_zero_return.o -o $(OUT)/shared_zero_return.elf
	objcopy -O binary --only-section=.text $(OUT)/shared_zero_return.elf $@

test-cycle-shared-zero-return: $(OUT)/reriff-match $(OUT)/shared_zero_return.bin
	$(OUT)/reriff-match native-check "$(GAME)" shared-zero-return $(OUT)/shared_zero_return.bin $(OUT)/shared-zero-return-comparison.json

test-recovered: test-cycle-shared-zero-return
.PHONY: test-cycle-shared-zero-return

# Reviewed cycle reference: collision-shape-angular-motion-disc (assembly evidence only).
$(OUT)/collision_shape_angular_motion_disc.bin: native/collision_shape_angular_motion_disc.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_angular_motion_disc.o
	ld -m elf_i386 -Ttext=0x47c1b0 -e original_collision_shape_angular_motion_disc $(OUT)/collision_shape_angular_motion_disc.o -o $(OUT)/collision_shape_angular_motion_disc.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_angular_motion_disc.elf $@

test-cycle-collision-shape-angular-motion-disc: $(OUT)/reriff-match $(OUT)/collision_shape_angular_motion_disc.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-angular-motion-disc $(OUT)/collision_shape_angular_motion_disc.bin $(OUT)/collision-shape-angular-motion-disc-comparison.json

test-recovered: test-cycle-collision-shape-angular-motion-disc
.PHONY: test-cycle-collision-shape-angular-motion-disc

# Reviewed cycle reference: convex-callback-filter-test (assembly evidence only).
$(OUT)/convex_callback_filter_test.bin: native/convex_callback_filter_test.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_callback_filter_test.o
	ld -m elf_i386 -Ttext=0x427110 -e original_convex_callback_filter_test $(OUT)/convex_callback_filter_test.o -o $(OUT)/convex_callback_filter_test.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_callback_filter_test.elf $@

test-cycle-convex-callback-filter-test: $(OUT)/reriff-match $(OUT)/convex_callback_filter_test.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-callback-filter-test $(OUT)/convex_callback_filter_test.bin $(OUT)/convex-callback-filter-test-comparison.json

test-recovered: test-cycle-convex-callback-filter-test
.PHONY: test-cycle-convex-callback-filter-test

# Reviewed cycle reference: convex-hull-shape-serialized-size (assembly evidence only).
$(OUT)/convex_hull_shape_serialized_size.bin: native/convex_hull_shape_serialized_size.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_shape_serialized_size.o
	ld -m elf_i386 -Ttext=0x47cd30 -e original_convex_hull_shape_serialized_size $(OUT)/convex_hull_shape_serialized_size.o -o $(OUT)/convex_hull_shape_serialized_size.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_shape_serialized_size.elf $@

test-cycle-convex-hull-shape-serialized-size: $(OUT)/reriff-match $(OUT)/convex_hull_shape_serialized_size.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-shape-serialized-size $(OUT)/convex_hull_shape_serialized_size.bin $(OUT)/convex-hull-shape-serialized-size-comparison.json

test-recovered: test-cycle-convex-hull-shape-serialized-size
.PHONY: test-cycle-convex-hull-shape-serialized-size

# Reviewed cycle reference: sse2-log-precise-import (assembly evidence only).
$(OUT)/sse2_log_precise_import.bin: native/sse2_log_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_log_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8f28 -e original_sse2_log_precise_import $(OUT)/sse2_log_precise_import.o -o $(OUT)/sse2_log_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_log_precise_import.elf $@

test-cycle-sse2-log-precise-import: $(OUT)/reriff-match $(OUT)/sse2_log_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-log-precise-import $(OUT)/sse2_log_precise_import.bin $(OUT)/sse2-log-precise-import-comparison.json

test-recovered: test-cycle-sse2-log-precise-import
.PHONY: test-cycle-sse2-log-precise-import

# Reviewed cycle reference: convex-hull-shape-name (assembly evidence only).
$(OUT)/convex_hull_shape_name.bin: native/convex_hull_shape_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_shape_name.o
	ld -m elf_i386 -Ttext=0x47cd20 -e original_convex_hull_shape_name $(OUT)/convex_hull_shape_name.o -o $(OUT)/convex_hull_shape_name.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_shape_name.elf $@

test-cycle-convex-hull-shape-name: $(OUT)/reriff-match $(OUT)/convex_hull_shape_name.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-shape-name $(OUT)/convex_hull_shape_name.bin $(OUT)/convex-hull-shape-name-comparison.json

test-recovered: test-cycle-convex-hull-shape-name
.PHONY: test-cycle-convex-hull-shape-name

# Reviewed cycle reference: dispatcher-manifold-index (assembly evidence only).
$(OUT)/dispatcher_manifold_index.bin: native/dispatcher_manifold_index.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/dispatcher_manifold_index.o
	ld -m elf_i386 -Ttext=0x4270a0 -e original_dispatcher_manifold_index $(OUT)/dispatcher_manifold_index.o -o $(OUT)/dispatcher_manifold_index.elf
	objcopy -O binary --only-section=.text $(OUT)/dispatcher_manifold_index.elf $@

test-cycle-dispatcher-manifold-index: $(OUT)/reriff-match $(OUT)/dispatcher_manifold_index.bin
	$(OUT)/reriff-match native-check "$(GAME)" dispatcher-manifold-index $(OUT)/dispatcher_manifold_index.bin $(OUT)/dispatcher-manifold-index-comparison.json

test-recovered: test-cycle-dispatcher-manifold-index
.PHONY: test-cycle-dispatcher-manifold-index

# Reviewed cycle reference: collision-shape-serialize (assembly evidence only).
$(OUT)/collision_shape_serialize.bin: native/collision_shape_serialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_serialize.o
	ld -m elf_i386 -Ttext=0x47c220 -e original_collision_shape_serialize $(OUT)/collision_shape_serialize.o -o $(OUT)/collision_shape_serialize.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_serialize.elf $@

test-cycle-collision-shape-serialize: $(OUT)/reriff-match $(OUT)/collision_shape_serialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-serialize $(OUT)/collision_shape_serialize.bin $(OUT)/collision-shape-serialize-comparison.json

test-recovered: test-cycle-collision-shape-serialize
.PHONY: test-cycle-collision-shape-serialize

# Reviewed cycle reference: motion-state-base-destruct (assembly evidence only).
$(OUT)/motion_state_base_destruct.bin: native/motion_state_base_destruct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/motion_state_base_destruct.o
	ld -m elf_i386 -Ttext=0x4384f0 -e original_motion_state_base_destruct $(OUT)/motion_state_base_destruct.o -o $(OUT)/motion_state_base_destruct.elf
	objcopy -O binary --only-section=.text $(OUT)/motion_state_base_destruct.elf $@

test-cycle-motion-state-base-destruct: $(OUT)/reriff-match $(OUT)/motion_state_base_destruct.bin
	$(OUT)/reriff-match native-check "$(GAME)" motion-state-base-destruct $(OUT)/motion_state_base_destruct.bin $(OUT)/motion-state-base-destruct-comparison.json

test-recovered: test-cycle-motion-state-base-destruct
.PHONY: test-cycle-motion-state-base-destruct

# Reviewed cycle reference: sse2-pow-precise-import (assembly evidence only).
$(OUT)/sse2_pow_precise_import.bin: native/sse2_pow_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_pow_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8f2e -e original_sse2_pow_precise_import $(OUT)/sse2_pow_precise_import.o -o $(OUT)/sse2_pow_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_pow_precise_import.elf $@

test-cycle-sse2-pow-precise-import: $(OUT)/reriff-match $(OUT)/sse2_pow_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-pow-precise-import $(OUT)/sse2_pow_precise_import.bin $(OUT)/sse2-pow-precise-import-comparison.json

test-recovered: test-cycle-sse2-pow-precise-import
.PHONY: test-cycle-sse2-pow-precise-import

# Reviewed cycle reference: collision-shape-serialize-single (assembly evidence only).
$(OUT)/collision_shape_serialize_single.bin: native/collision_shape_serialize_single.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_serialize_single.o
	ld -m elf_i386 -Ttext=0x47c270 -e original_collision_shape_serialize_single $(OUT)/collision_shape_serialize_single.o -o $(OUT)/collision_shape_serialize_single.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_serialize_single.elf $@

test-cycle-collision-shape-serialize-single: $(OUT)/reriff-match $(OUT)/collision_shape_serialize_single.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-serialize-single $(OUT)/collision_shape_serialize_single.bin $(OUT)/collision-shape-serialize-single-comparison.json

test-recovered: test-cycle-collision-shape-serialize-single
.PHONY: test-cycle-collision-shape-serialize-single

# Reviewed cycle reference: sse2-sin-precise-import (assembly evidence only).
$(OUT)/sse2_sin_precise_import.bin: native/sse2_sin_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_sin_precise_import.o
	ld -m elf_i386 -Ttext=0x8f8f34 -e original_sse2_sin_precise_import $(OUT)/sse2_sin_precise_import.o -o $(OUT)/sse2_sin_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_sin_precise_import.elf $@

test-cycle-sse2-sin-precise-import: $(OUT)/reriff-match $(OUT)/sse2_sin_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-sin-precise-import $(OUT)/sse2_sin_precise_import.bin $(OUT)/sse2-sin-precise-import-comparison.json

test-recovered: test-cycle-sse2-sin-precise-import
.PHONY: test-cycle-sse2-sin-precise-import

# Reviewed cycle reference: collision-shape-deleting-destructor (assembly evidence only).
$(OUT)/collision_shape_deleting_destructor.bin: native/collision_shape_deleting_destructor.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_deleting_destructor.o
	ld -m elf_i386 -Ttext=0x47c2b0 -e original_collision_shape_deleting_destructor $(OUT)/collision_shape_deleting_destructor.o -o $(OUT)/collision_shape_deleting_destructor.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_deleting_destructor.elf $@

test-cycle-collision-shape-deleting-destructor: $(OUT)/reriff-match $(OUT)/collision_shape_deleting_destructor.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-deleting-destructor $(OUT)/collision_shape_deleting_destructor.bin $(OUT)/collision-shape-deleting-destructor-comparison.json

test-recovered: test-cycle-collision-shape-deleting-destructor
.PHONY: test-cycle-collision-shape-deleting-destructor

# Reviewed cycle reference: crt-purecall-import (assembly evidence only).
$(OUT)/crt_purecall_import.bin: native/crt_purecall_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_purecall_import.o
	ld -m elf_i386 -Ttext=0x8f893a -e original_crt_purecall_import $(OUT)/crt_purecall_import.o -o $(OUT)/crt_purecall_import.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_purecall_import.elf $@

test-cycle-crt-purecall-import: $(OUT)/reriff-match $(OUT)/crt_purecall_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-purecall-import $(OUT)/crt_purecall_import.bin $(OUT)/crt-purecall-import-comparison.json

test-recovered: test-cycle-crt-purecall-import
.PHONY: test-cycle-crt-purecall-import

# Reviewed cycle reference: sse2-tan-precise-import (assembly evidence only).
$(OUT)/sse2_tan_precise_import.bin: native/sse2_tan_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_tan_precise_import.o
	ld -m elf_i386 -Ttext=0x8f93d2 -e original_sse2_tan_precise_import $(OUT)/sse2_tan_precise_import.o -o $(OUT)/sse2_tan_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_tan_precise_import.elf $@

test-cycle-sse2-tan-precise-import: $(OUT)/reriff-match $(OUT)/sse2_tan_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-tan-precise-import $(OUT)/sse2_tan_precise_import.bin $(OUT)/sse2-tan-precise-import-comparison.json

test-recovered: test-cycle-sse2-tan-precise-import
.PHONY: test-cycle-sse2-tan-precise-import

# Reviewed cycle reference: sse2-exp-precise-import (assembly evidence only).
$(OUT)/sse2_exp_precise_import.bin: native/sse2_exp_precise_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse2_exp_precise_import.o
	ld -m elf_i386 -Ttext=0x8f93cc -e original_sse2_exp_precise_import $(OUT)/sse2_exp_precise_import.o -o $(OUT)/sse2_exp_precise_import.elf
	objcopy -O binary --only-section=.text $(OUT)/sse2_exp_precise_import.elf $@

test-cycle-sse2-exp-precise-import: $(OUT)/reriff-match $(OUT)/sse2_exp_precise_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse2-exp-precise-import $(OUT)/sse2_exp_precise_import.bin $(OUT)/sse2-exp-precise-import-comparison.json

test-recovered: test-cycle-sse2-exp-precise-import
.PHONY: test-cycle-sse2-exp-precise-import

# Reviewed cycle reference: object-field78-present (assembly evidence only).
$(OUT)/object_field78_present.bin: native/object_field78_present.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/object_field78_present.o
	ld -m elf_i386 -Ttext=0x438530 -e original_object_field78_present $(OUT)/object_field78_present.o -o $(OUT)/object_field78_present.elf
	objcopy -O binary --only-section=.text $(OUT)/object_field78_present.elf $@

test-cycle-object-field78-present: $(OUT)/reriff-match $(OUT)/object_field78_present.bin
	$(OUT)/reriff-match native-check "$(GAME)" object-field78-present $(OUT)/object_field78_present.bin $(OUT)/object-field78-present-comparison.json

test-recovered: test-cycle-object-field78-present
.PHONY: test-cycle-object-field78-present

# Reviewed cycle reference: convex-hull-shape-set-scaling (assembly evidence only).
$(OUT)/convex_hull_shape_set_scaling.bin: native/convex_hull_shape_set_scaling.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_shape_set_scaling.o
	ld -m elf_i386 -Ttext=0x47cfd0 -e original_convex_hull_shape_set_scaling $(OUT)/convex_hull_shape_set_scaling.o -o $(OUT)/convex_hull_shape_set_scaling.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_shape_set_scaling.elf $@

test-cycle-convex-hull-shape-set-scaling: $(OUT)/reriff-match $(OUT)/convex_hull_shape_set_scaling.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-shape-set-scaling $(OUT)/convex_hull_shape_set_scaling.bin $(OUT)/convex-hull-shape-set-scaling-comparison.json

test-recovered: test-cycle-convex-hull-shape-set-scaling
.PHONY: test-cycle-convex-hull-shape-set-scaling

# Reviewed cycle reference: dispatcher-manifold-array-pointer (assembly evidence only).
$(OUT)/dispatcher_manifold_array_pointer.bin: native/dispatcher_manifold_array_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/dispatcher_manifold_array_pointer.o
	ld -m elf_i386 -Ttext=0x427090 -e original_dispatcher_manifold_array_pointer $(OUT)/dispatcher_manifold_array_pointer.o -o $(OUT)/dispatcher_manifold_array_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/dispatcher_manifold_array_pointer.elf $@

test-cycle-dispatcher-manifold-array-pointer: $(OUT)/reriff-match $(OUT)/dispatcher_manifold_array_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" dispatcher-manifold-array-pointer $(OUT)/dispatcher_manifold_array_pointer.bin $(OUT)/dispatcher-manifold-array-pointer-comparison.json

test-recovered: test-cycle-dispatcher-manifold-array-pointer
.PHONY: test-cycle-dispatcher-manifold-array-pointer

# Reviewed cycle reference: object-flags-channel-enabled (assembly evidence only).
$(OUT)/object_flags_channel_enabled.bin: native/object_flags_channel_enabled.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/object_flags_channel_enabled.o
	ld -m elf_i386 -Ttext=0x443110 -e original_object_flags_channel_enabled $(OUT)/object_flags_channel_enabled.o -o $(OUT)/object_flags_channel_enabled.elf
	objcopy -O binary --only-section=.text $(OUT)/object_flags_channel_enabled.elf $@

test-cycle-object-flags-channel-enabled: $(OUT)/reriff-match $(OUT)/object_flags_channel_enabled.bin
	$(OUT)/reriff-match native-check "$(GAME)" object-flags-channel-enabled $(OUT)/object_flags_channel_enabled.bin $(OUT)/object-flags-channel-enabled-comparison.json

test-recovered: test-cycle-object-flags-channel-enabled
.PHONY: test-cycle-object-flags-channel-enabled

# Reviewed cycle reference: convex-hull-support-without-margin (assembly evidence only).
$(OUT)/convex_hull_support_without_margin.bin: native/convex_hull_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_support_without_margin.o
	ld -m elf_i386 -Ttext=0x47cff0 -e original_convex_hull_support_without_margin $(OUT)/convex_hull_support_without_margin.o -o $(OUT)/convex_hull_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_support_without_margin.elf $@

test-cycle-convex-hull-support-without-margin: $(OUT)/reriff-match $(OUT)/convex_hull_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-support-without-margin $(OUT)/convex_hull_support_without_margin.bin $(OUT)/convex-hull-support-without-margin-comparison.json

test-recovered: test-cycle-convex-hull-support-without-margin
.PHONY: test-cycle-convex-hull-support-without-margin

# Reviewed cycle reference: narrow-append-substring (assembly evidence only).
$(OUT)/narrow_append_substring.bin: native/narrow_append_substring.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/narrow_append_substring.o
	ld -m elf_i386 -Ttext=0x4420b0 -e original_narrow_append_substring $(OUT)/narrow_append_substring.o -o $(OUT)/narrow_append_substring.elf
	objcopy -O binary --only-section=.text $(OUT)/narrow_append_substring.elf $@

test-cycle-narrow-append-substring: $(OUT)/reriff-match $(OUT)/narrow_append_substring.bin
	$(OUT)/reriff-match native-check "$(GAME)" narrow-append-substring $(OUT)/narrow_append_substring.bin $(OUT)/narrow-append-substring-comparison.json

test-recovered: test-cycle-narrow-append-substring
.PHONY: test-cycle-narrow-append-substring

# Reviewed cycle reference: convex-hull-vertex-without-margin (assembly evidence only).
$(OUT)/convex_hull_vertex_without_margin.bin: native/convex_hull_vertex_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_vertex_without_margin.o
	ld -m elf_i386 -Ttext=0x47d280 -e original_convex_hull_vertex_without_margin $(OUT)/convex_hull_vertex_without_margin.o -o $(OUT)/convex_hull_vertex_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_vertex_without_margin.elf $@

test-cycle-convex-hull-vertex-without-margin: $(OUT)/reriff-match $(OUT)/convex_hull_vertex_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-vertex-without-margin $(OUT)/convex_hull_vertex_without_margin.bin $(OUT)/convex-hull-vertex-without-margin-comparison.json

test-recovered: test-cycle-convex-hull-vertex-without-margin
.PHONY: test-cycle-convex-hull-vertex-without-margin

# Reviewed cycle reference: convex-hull-batched-support-without-margin (assembly evidence only).
$(OUT)/convex_hull_batched_support_without_margin.bin: native/convex_hull_batched_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_batched_support_without_margin.o
	ld -m elf_i386 -Ttext=0x47d0c0 -e original_convex_hull_batched_support_without_margin $(OUT)/convex_hull_batched_support_without_margin.o -o $(OUT)/convex_hull_batched_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_batched_support_without_margin.elf $@

test-cycle-convex-hull-batched-support-without-margin: $(OUT)/reriff-match $(OUT)/convex_hull_batched_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-batched-support-without-margin $(OUT)/convex_hull_batched_support_without_margin.bin $(OUT)/convex-hull-batched-support-without-margin-comparison.json

test-recovered: test-cycle-convex-hull-batched-support-without-margin
.PHONY: test-cycle-convex-hull-batched-support-without-margin

# Reviewed cycle reference: convex-hull-edge-without-margin (assembly evidence only).
$(OUT)/convex_hull_edge_without_margin.bin: native/convex_hull_edge_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_edge_without_margin.o
	ld -m elf_i386 -Ttext=0x47d1d0 -e original_convex_hull_edge_without_margin $(OUT)/convex_hull_edge_without_margin.o -o $(OUT)/convex_hull_edge_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_edge_without_margin.elf $@

test-cycle-convex-hull-edge-without-margin: $(OUT)/reriff-match $(OUT)/convex_hull_edge_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-edge-without-margin $(OUT)/convex_hull_edge_without_margin.bin $(OUT)/convex-hull-edge-without-margin-comparison.json

test-recovered: test-cycle-convex-hull-edge-without-margin
.PHONY: test-cycle-convex-hull-edge-without-margin

# Reviewed cycle reference: convex-hull-vertex-edge-count (assembly evidence only).
$(OUT)/convex_hull_vertex_edge_count.bin: native/convex_hull_vertex_edge_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_vertex_edge_count.o
	ld -m elf_i386 -Ttext=0x47d1c0 -e original_convex_hull_vertex_edge_count $(OUT)/convex_hull_vertex_edge_count.o -o $(OUT)/convex_hull_vertex_edge_count.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_vertex_edge_count.elf $@

test-cycle-convex-hull-vertex-edge-count: $(OUT)/reriff-match $(OUT)/convex_hull_vertex_edge_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-vertex-edge-count $(OUT)/convex_hull_vertex_edge_count.bin $(OUT)/convex-hull-vertex-edge-count-comparison.json

test-recovered: test-cycle-convex-hull-vertex-edge-count
.PHONY: test-cycle-convex-hull-vertex-edge-count

# Reviewed cycle reference: sphere-support-without-margin (assembly evidence only).
$(OUT)/sphere_support_without_margin.bin: native/sphere_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sphere_support_without_margin.o
	ld -m elf_i386 -Ttext=0x47d530 -e original_sphere_support_without_margin $(OUT)/sphere_support_without_margin.o -o $(OUT)/sphere_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/sphere_support_without_margin.elf $@

test-cycle-sphere-support-without-margin: $(OUT)/reriff-match $(OUT)/sphere_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" sphere-support-without-margin $(OUT)/sphere_support_without_margin.bin $(OUT)/sphere-support-without-margin-comparison.json

test-recovered: test-cycle-sphere-support-without-margin
.PHONY: test-cycle-sphere-support-without-margin

# Reviewed cycle reference: sphere-batched-support-without-margin (assembly evidence only).
$(OUT)/sphere_batched_support_without_margin.bin: native/sphere_batched_support_without_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sphere_batched_support_without_margin.o
	ld -m elf_i386 -Ttext=0x47d560 -e original_sphere_batched_support_without_margin $(OUT)/sphere_batched_support_without_margin.o -o $(OUT)/sphere_batched_support_without_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/sphere_batched_support_without_margin.elf $@

test-cycle-sphere-batched-support-without-margin: $(OUT)/reriff-match $(OUT)/sphere_batched_support_without_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" sphere-batched-support-without-margin $(OUT)/sphere_batched_support_without_margin.bin $(OUT)/sphere-batched-support-without-margin-comparison.json

test-recovered: test-cycle-sphere-batched-support-without-margin
.PHONY: test-cycle-sphere-batched-support-without-margin

# Reviewed cycle reference: sphere-local-inertia (assembly evidence only).
$(OUT)/sphere_local_inertia.bin: native/sphere_local_inertia.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sphere_local_inertia.o
	ld -m elf_i386 -Ttext=0x47d7e0 -e original_sphere_local_inertia $(OUT)/sphere_local_inertia.o -o $(OUT)/sphere_local_inertia.elf
	objcopy -O binary --only-section=.text $(OUT)/sphere_local_inertia.elf $@

test-cycle-sphere-local-inertia: $(OUT)/reriff-match $(OUT)/sphere_local_inertia.bin
	$(OUT)/reriff-match native-check "$(GAME)" sphere-local-inertia $(OUT)/sphere_local_inertia.bin $(OUT)/sphere-local-inertia-comparison.json

test-recovered: test-cycle-sphere-local-inertia
.PHONY: test-cycle-sphere-local-inertia

# Reviewed cycle reference: sphere-aabb (assembly evidence only).
$(OUT)/sphere_aabb.bin: native/sphere_aabb.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sphere_aabb.o
	ld -m elf_i386 -Ttext=0x47d710 -e original_sphere_aabb $(OUT)/sphere_aabb.o -o $(OUT)/sphere_aabb.elf
	objcopy -O binary --only-section=.text $(OUT)/sphere_aabb.elf $@

test-cycle-sphere-aabb: $(OUT)/reriff-match $(OUT)/sphere_aabb.bin
	$(OUT)/reriff-match native-check "$(GAME)" sphere-aabb $(OUT)/sphere_aabb.bin $(OUT)/sphere-aabb-comparison.json

test-recovered: test-cycle-sphere-aabb
.PHONY: test-cycle-sphere-aabb

# Reviewed cycle reference: handle-record-flag10-present (assembly evidence only).
$(OUT)/handle_record_flag10_present.bin: native/handle_record_flag10_present.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/handle_record_flag10_present.o
	ld -m elf_i386 -Ttext=0x499e40 -e original_handle_record_flag10_present $(OUT)/handle_record_flag10_present.o -o $(OUT)/handle_record_flag10_present.elf
	objcopy -O binary --only-section=.text $(OUT)/handle_record_flag10_present.elf $@

test-cycle-handle-record-flag10-present: $(OUT)/reriff-match $(OUT)/handle_record_flag10_present.bin
	$(OUT)/reriff-match native-check "$(GAME)" handle-record-flag10-present $(OUT)/handle_record_flag10_present.bin $(OUT)/handle-record-flag10-present-comparison.json

test-recovered: test-cycle-handle-record-flag10-present
.PHONY: test-cycle-handle-record-flag10-present

# Reviewed cycle reference: compound-shape-margin (assembly evidence only).
$(OUT)/compound_shape_margin.bin: native/compound_shape_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/compound_shape_margin.o
	ld -m elf_i386 -Ttext=0x47d8e0 -e original_compound_shape_margin $(OUT)/compound_shape_margin.o -o $(OUT)/compound_shape_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/compound_shape_margin.elf $@

test-cycle-compound-shape-margin: $(OUT)/reriff-match $(OUT)/compound_shape_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" compound-shape-margin $(OUT)/compound_shape_margin.bin $(OUT)/compound-shape-margin-comparison.json

test-recovered: test-cycle-compound-shape-margin
.PHONY: test-cycle-compound-shape-margin

# Reviewed cycle reference: compound-shape-scaling-pointer (assembly evidence only).
$(OUT)/compound_shape_scaling_pointer.bin: native/compound_shape_scaling_pointer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/compound_shape_scaling_pointer.o
	ld -m elf_i386 -Ttext=0x47d8b0 -e original_compound_shape_scaling_pointer $(OUT)/compound_shape_scaling_pointer.o -o $(OUT)/compound_shape_scaling_pointer.elf
	objcopy -O binary --only-section=.text $(OUT)/compound_shape_scaling_pointer.elf $@

test-cycle-compound-shape-scaling-pointer: $(OUT)/reriff-match $(OUT)/compound_shape_scaling_pointer.bin
	$(OUT)/reriff-match native-check "$(GAME)" compound-shape-scaling-pointer $(OUT)/compound_shape_scaling_pointer.bin $(OUT)/compound-shape-scaling-pointer-comparison.json

test-recovered: test-cycle-compound-shape-scaling-pointer
.PHONY: test-cycle-compound-shape-scaling-pointer

# Reviewed cycle reference: transform64-serialize-copy (assembly evidence only).
$(OUT)/transform64_serialize_copy.bin: native/transform64_serialize_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/transform64_serialize_copy.o
	ld -m elf_i386 -Ttext=0x47d840 -e original_transform64_serialize_copy $(OUT)/transform64_serialize_copy.o -o $(OUT)/transform64_serialize_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/transform64_serialize_copy.elf $@

test-cycle-transform64-serialize-copy: $(OUT)/reriff-match $(OUT)/transform64_serialize_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" transform64-serialize-copy $(OUT)/transform64_serialize_copy.bin $(OUT)/transform64-serialize-copy-comparison.json

test-recovered: test-cycle-transform64-serialize-copy
.PHONY: test-cycle-transform64-serialize-copy

# Reviewed cycle reference: pointer-slot-range-zero-initialize (assembly evidence only).
$(OUT)/pointer_slot_range_zero_initialize.bin: native/pointer_slot_range_zero_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pointer_slot_range_zero_initialize.o
	ld -m elf_i386 -Ttext=0x458100 -e original_pointer_slot_range_zero_initialize $(OUT)/pointer_slot_range_zero_initialize.o -o $(OUT)/pointer_slot_range_zero_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/pointer_slot_range_zero_initialize.elf $@

test-cycle-pointer-slot-range-zero-initialize: $(OUT)/reriff-match $(OUT)/pointer_slot_range_zero_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" pointer-slot-range-zero-initialize $(OUT)/pointer_slot_range_zero_initialize.bin $(OUT)/pointer-slot-range-zero-initialize-comparison.json

test-recovered: test-cycle-pointer-slot-range-zero-initialize
.PHONY: test-cycle-pointer-slot-range-zero-initialize

# Reviewed cycle reference: compound-shape-set-margin (assembly evidence only).
$(OUT)/compound_shape_set_margin.bin: native/compound_shape_set_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/compound_shape_set_margin.o
	ld -m elf_i386 -Ttext=0x47d8c0 -e original_compound_shape_set_margin $(OUT)/compound_shape_set_margin.o -o $(OUT)/compound_shape_set_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/compound_shape_set_margin.elf $@

test-cycle-compound-shape-set-margin: $(OUT)/reriff-match $(OUT)/compound_shape_set_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" compound-shape-set-margin $(OUT)/compound_shape_set_margin.bin $(OUT)/compound-shape-set-margin-comparison.json

test-recovered: test-cycle-compound-shape-set-margin
.PHONY: test-cycle-compound-shape-set-margin

# Reviewed cycle reference: matrix3-copy-storage (assembly evidence only).
$(OUT)/matrix3_copy_storage.bin: native/matrix3_copy_storage.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix3_copy_storage.o
	ld -m elf_i386 -Ttext=0x467e10 -e original_matrix3_copy_storage $(OUT)/matrix3_copy_storage.o -o $(OUT)/matrix3_copy_storage.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix3_copy_storage.elf $@

test-cycle-matrix3-copy-storage: $(OUT)/reriff-match $(OUT)/matrix3_copy_storage.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix3-copy-storage $(OUT)/matrix3_copy_storage.bin $(OUT)/matrix3-copy-storage-comparison.json

test-recovered: test-cycle-matrix3-copy-storage
.PHONY: test-cycle-matrix3-copy-storage

# Reviewed cycle reference: sphere-support-with-margin (assembly evidence only).
$(OUT)/sphere_support_with_margin.bin: native/sphere_support_with_margin.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sphere_support_with_margin.o
	ld -m elf_i386 -Ttext=0x47d5a0 -e original_sphere_support_with_margin $(OUT)/sphere_support_with_margin.o -o $(OUT)/sphere_support_with_margin.elf
	objcopy -O binary --only-section=.text $(OUT)/sphere_support_with_margin.elf $@

test-cycle-sphere-support-with-margin: $(OUT)/reriff-match $(OUT)/sphere_support_with_margin.bin
	$(OUT)/reriff-match native-check "$(GAME)" sphere-support-with-margin $(OUT)/sphere_support_with_margin.bin $(OUT)/sphere-support-with-margin-comparison.json

test-recovered: test-cycle-sphere-support-with-margin
.PHONY: test-cycle-sphere-support-with-margin

# Reviewed cycle reference: collision-shape-bounding-sphere (assembly evidence only).
$(OUT)/collision_shape_bounding_sphere.bin: native/collision_shape_bounding_sphere.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_shape_bounding_sphere.o
	ld -m elf_i386 -Ttext=0x47c060 -e original_collision_shape_bounding_sphere $(OUT)/collision_shape_bounding_sphere.o -o $(OUT)/collision_shape_bounding_sphere.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_shape_bounding_sphere.elf $@

test-cycle-collision-shape-bounding-sphere: $(OUT)/reriff-match $(OUT)/collision_shape_bounding_sphere.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-shape-bounding-sphere $(OUT)/collision_shape_bounding_sphere.bin $(OUT)/collision-shape-bounding-sphere-comparison.json

test-recovered: test-cycle-collision-shape-bounding-sphere
.PHONY: test-cycle-collision-shape-bounding-sphere

# Reviewed cycle reference: request-buffers-ensure-capacity (assembly evidence only).
$(OUT)/request_buffers_ensure_capacity.bin: native/request_buffers_ensure_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_buffers_ensure_capacity.o
	ld -m elf_i386 -Ttext=0x509be0 -e original_request_buffers_ensure_capacity $(OUT)/request_buffers_ensure_capacity.o -o $(OUT)/request_buffers_ensure_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/request_buffers_ensure_capacity.elf $@

test-cycle-request-buffers-ensure-capacity: $(OUT)/reriff-match $(OUT)/request_buffers_ensure_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-buffers-ensure-capacity $(OUT)/request_buffers_ensure_capacity.bin $(OUT)/request-buffers-ensure-capacity-comparison.json

test-recovered: test-cycle-request-buffers-ensure-capacity
.PHONY: test-cycle-request-buffers-ensure-capacity

# Reviewed cycle reference: record68-reallocate (assembly evidence only).
$(OUT)/record68_reallocate.bin: native/record68_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record68_reallocate.o
	ld -m elf_i386 -Ttext=0x509dc0 -e original_record68_reallocate $(OUT)/record68_reallocate.o -o $(OUT)/record68_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/record68_reallocate.elf $@

test-cycle-record68-reallocate: $(OUT)/reriff-match $(OUT)/record68_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" record68-reallocate $(OUT)/record68_reallocate.bin $(OUT)/record68-reallocate-comparison.json

test-recovered: test-cycle-record68-reallocate
.PHONY: test-cycle-record68-reallocate

# Reviewed cycle reference: lua-constant-string-name (assembly evidence only).
$(OUT)/lua_constant_string_name.bin: native/lua_constant_string_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/lua_constant_string_name.o
	ld -m elf_i386 -Ttext=0x486650 -e original_lua_constant_string_name $(OUT)/lua_constant_string_name.o -o $(OUT)/lua_constant_string_name.elf
	objcopy -O binary --only-section=.text $(OUT)/lua_constant_string_name.elf $@

test-cycle-lua-constant-string-name: $(OUT)/reriff-match $(OUT)/lua_constant_string_name.bin
	$(OUT)/reriff-match native-check "$(GAME)" lua-constant-string-name $(OUT)/lua_constant_string_name.bin $(OUT)/lua-constant-string-name-comparison.json

test-recovered: test-cycle-lua-constant-string-name
.PHONY: test-cycle-lua-constant-string-name

# Reviewed cycle reference: array-construct-with-cleanup (assembly evidence only).
$(OUT)/array_construct_with_cleanup.bin: native/array_construct_with_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_construct_with_cleanup.o
	ld -m elf_i386 -Ttext=0x8f94bf -e original_array_construct_with_cleanup $(OUT)/array_construct_with_cleanup.o -o $(OUT)/array_construct_with_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/array_construct_with_cleanup.elf $@

test-cycle-array-construct-with-cleanup: $(OUT)/reriff-match $(OUT)/array_construct_with_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-construct-with-cleanup $(OUT)/array_construct_with_cleanup.bin $(OUT)/array-construct-with-cleanup-comparison.json

test-recovered: test-cycle-array-construct-with-cleanup
.PHONY: test-cycle-array-construct-with-cleanup

# Reviewed cycle reference: crt-terminate-import (assembly evidence only).
$(OUT)/crt_terminate_import.bin: native/crt_terminate_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_terminate_import.o
	ld -m elf_i386 -Ttext=0x8f9522 -e original_crt_terminate_import $(OUT)/crt_terminate_import.o -o $(OUT)/crt_terminate_import.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_terminate_import.elf $@

test-cycle-crt-terminate-import: $(OUT)/reriff-match $(OUT)/crt_terminate_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-terminate-import $(OUT)/crt_terminate_import.bin $(OUT)/crt-terminate-import-comparison.json

test-recovered: test-cycle-crt-terminate-import
.PHONY: test-cycle-crt-terminate-import

# Reviewed cycle reference: array-destroy-with-exception-filter (assembly evidence only).
$(OUT)/array_destroy_with_exception_filter.bin: native/array_destroy_with_exception_filter.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_destroy_with_exception_filter.o
	ld -m elf_i386 -Ttext=0x8f9461 -e original_array_destroy_with_exception_filter $(OUT)/array_destroy_with_exception_filter.o -o $(OUT)/array_destroy_with_exception_filter.elf
	objcopy -O binary --only-section=.text $(OUT)/array_destroy_with_exception_filter.elf $@

test-cycle-array-destroy-with-exception-filter: $(OUT)/reriff-match $(OUT)/array_destroy_with_exception_filter.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-destroy-with-exception-filter $(OUT)/array_destroy_with_exception_filter.bin $(OUT)/array-destroy-with-exception-filter-comparison.json

test-recovered: test-cycle-array-destroy-with-exception-filter
.PHONY: test-cycle-array-destroy-with-exception-filter

# Reviewed cycle reference: stream-append-u16-be (assembly evidence only).
$(OUT)/stream_append_u16_be.bin: native/stream_append_u16_be.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/stream_append_u16_be.o
	ld -m elf_i386 -Ttext=0x5cc7a0 -e original_stream_append_u16_be $(OUT)/stream_append_u16_be.o -o $(OUT)/stream_append_u16_be.elf
	objcopy -O binary --only-section=.text $(OUT)/stream_append_u16_be.elf $@

test-cycle-stream-append-u16-be: $(OUT)/reriff-match $(OUT)/stream_append_u16_be.bin
	$(OUT)/reriff-match native-check "$(GAME)" stream-append-u16-be $(OUT)/stream_append_u16_be.bin $(OUT)/stream-append-u16-be-comparison.json

test-recovered: test-cycle-stream-append-u16-be
.PHONY: test-cycle-stream-append-u16-be

# Reviewed cycle reference: crt-seh-dispatch (assembly evidence only).
$(OUT)/crt_seh_dispatch.bin: native/crt_seh_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_seh_dispatch.o
	ld -m elf_i386 -Ttext=0x8f9ce9 -e original_crt_seh_dispatch $(OUT)/crt_seh_dispatch.o -o $(OUT)/crt_seh_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_seh_dispatch.elf $@

test-cycle-crt-seh-dispatch: $(OUT)/reriff-match $(OUT)/crt_seh_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-seh-dispatch $(OUT)/crt_seh_dispatch.bin $(OUT)/crt-seh-dispatch-comparison.json

test-recovered: test-cycle-crt-seh-dispatch
.PHONY: test-cycle-crt-seh-dispatch

# Reviewed cycle reference: crt-except-handler4-common-import (assembly evidence only).
$(OUT)/crt_except_handler4_common_import.bin: native/crt_except_handler4_common_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_except_handler4_common_import.o
	ld -m elf_i386 -Ttext=0x8f9ef4 -e original_crt_except_handler4_common_import $(OUT)/crt_except_handler4_common_import.o -o $(OUT)/crt_except_handler4_common_import.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_except_handler4_common_import.elf $@

test-cycle-crt-except-handler4-common-import: $(OUT)/reriff-match $(OUT)/crt_except_handler4_common_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-except-handler4-common-import $(OUT)/crt_except_handler4_common_import.bin $(OUT)/crt-except-handler4-common-import-comparison.json

test-recovered: test-cycle-crt-except-handler4-common-import
.PHONY: test-cycle-crt-except-handler4-common-import

# Reviewed cycle reference: array-copy-construct-with-cleanup (assembly evidence only).
$(OUT)/array_copy_construct_with_cleanup.bin: native/array_copy_construct_with_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_copy_construct_with_cleanup.o
	ld -m elf_i386 -Ttext=0x8f977e -e original_array_copy_construct_with_cleanup $(OUT)/array_copy_construct_with_cleanup.o -o $(OUT)/array_copy_construct_with_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/array_copy_construct_with_cleanup.elf $@

test-cycle-array-copy-construct-with-cleanup: $(OUT)/reriff-match $(OUT)/array_copy_construct_with_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-copy-construct-with-cleanup $(OUT)/array_copy_construct_with_cleanup.bin $(OUT)/array-copy-construct-with-cleanup-comparison.json

test-recovered: test-cycle-array-copy-construct-with-cleanup
.PHONY: test-cycle-array-copy-construct-with-cleanup

# Reviewed cycle reference: crt-controlfp-s-import (assembly evidence only).
$(OUT)/crt_controlfp_s_import.bin: native/crt_controlfp_s_import.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_controlfp_s_import.o
	ld -m elf_i386 -Ttext=0x8f9eee -e original_crt_controlfp_s_import $(OUT)/crt_controlfp_s_import.o -o $(OUT)/crt_controlfp_s_import.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_controlfp_s_import.elf $@

test-cycle-crt-controlfp-s-import: $(OUT)/reriff-match $(OUT)/crt_controlfp_s_import.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-controlfp-s-import $(OUT)/crt_controlfp_s_import.bin $(OUT)/crt-controlfp-s-import-comparison.json

test-recovered: test-cycle-crt-controlfp-s-import
.PHONY: test-cycle-crt-controlfp-s-import

# Reviewed cycle reference: array-reverse-destroy-with-cleanup (assembly evidence only).
$(OUT)/array_reverse_destroy_with_cleanup.bin: native/array_reverse_destroy_with_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/array_reverse_destroy_with_cleanup.o
	ld -m elf_i386 -Ttext=0x8f93f2 -e original_array_reverse_destroy_with_cleanup $(OUT)/array_reverse_destroy_with_cleanup.o -o $(OUT)/array_reverse_destroy_with_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/array_reverse_destroy_with_cleanup.elf $@

test-cycle-array-reverse-destroy-with-cleanup: $(OUT)/reriff-match $(OUT)/array_reverse_destroy_with_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" array-reverse-destroy-with-cleanup $(OUT)/array_reverse_destroy_with_cleanup.bin $(OUT)/array-reverse-destroy-with-cleanup-comparison.json

test-recovered: test-cycle-array-reverse-destroy-with-cleanup
.PHONY: test-cycle-array-reverse-destroy-with-cleanup

# Reviewed cycle reference: crt-callback-storage-validate (assembly evidence only).
$(OUT)/crt_callback_storage_validate.bin: native/crt_callback_storage_validate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/crt_callback_storage_validate.o
	ld -m elf_i386 -Ttext=0x8f9a80 -e original_crt_callback_storage_validate $(OUT)/crt_callback_storage_validate.o -o $(OUT)/crt_callback_storage_validate.elf
	objcopy -O binary --only-section=.text $(OUT)/crt_callback_storage_validate.elf $@

test-cycle-crt-callback-storage-validate: $(OUT)/reriff-match $(OUT)/crt_callback_storage_validate.bin
	$(OUT)/reriff-match native-check "$(GAME)" crt-callback-storage-validate $(OUT)/crt_callback_storage_validate.bin $(OUT)/crt-callback-storage-validate-comparison.json

test-recovered: test-cycle-crt-callback-storage-validate
.PHONY: test-cycle-crt-callback-storage-validate

# Reviewed cycle reference: node-chain-terminal-vector (assembly evidence only).
$(OUT)/node_chain_terminal_vector.bin: native/node_chain_terminal_vector.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/node_chain_terminal_vector.o
	ld -m elf_i386 -Ttext=0x457f70 -e original_node_chain_terminal_vector $(OUT)/node_chain_terminal_vector.o -o $(OUT)/node_chain_terminal_vector.elf
	objcopy -O binary --only-section=.text $(OUT)/node_chain_terminal_vector.elf $@

test-cycle-node-chain-terminal-vector: $(OUT)/reriff-match $(OUT)/node_chain_terminal_vector.bin
	$(OUT)/reriff-match native-check "$(GAME)" node-chain-terminal-vector $(OUT)/node_chain_terminal_vector.bin $(OUT)/node-chain-terminal-vector-comparison.json

test-recovered: test-cycle-node-chain-terminal-vector
.PHONY: test-cycle-node-chain-terminal-vector

# Reviewed cycle reference: reference-slot-vector-remove-tail (assembly evidence only).
$(OUT)/reference_slot_vector_remove_tail.bin: native/reference_slot_vector_remove_tail.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/reference_slot_vector_remove_tail.o
	ld -m elf_i386 -Ttext=0x4580a0 -e original_reference_slot_vector_remove_tail $(OUT)/reference_slot_vector_remove_tail.o -o $(OUT)/reference_slot_vector_remove_tail.elf
	objcopy -O binary --only-section=.text $(OUT)/reference_slot_vector_remove_tail.elf $@

test-cycle-reference-slot-vector-remove-tail: $(OUT)/reriff-match $(OUT)/reference_slot_vector_remove_tail.bin
	$(OUT)/reriff-match native-check "$(GAME)" reference-slot-vector-remove-tail $(OUT)/reference_slot_vector_remove_tail.bin $(OUT)/reference-slot-vector-remove-tail-comparison.json

test-recovered: test-cycle-reference-slot-vector-remove-tail
.PHONY: test-cycle-reference-slot-vector-remove-tail

# Reviewed cycle reference: render-target-dimensions-initialize (assembly evidence only).
$(OUT)/render_target_dimensions_initialize.bin: native/render_target_dimensions_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/render_target_dimensions_initialize.o
	ld -m elf_i386 -Ttext=0x53d2d0 -e original_render_target_dimensions_initialize $(OUT)/render_target_dimensions_initialize.o -o $(OUT)/render_target_dimensions_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/render_target_dimensions_initialize.elf $@

test-cycle-render-target-dimensions-initialize: $(OUT)/reriff-match $(OUT)/render_target_dimensions_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" render-target-dimensions-initialize $(OUT)/render_target_dimensions_initialize.bin $(OUT)/render-target-dimensions-initialize-comparison.json

test-recovered: test-cycle-render-target-dimensions-initialize
.PHONY: test-cycle-render-target-dimensions-initialize

# Reviewed cycle reference: reference-slot-assign-range (assembly evidence only).
$(OUT)/reference_slot_assign_range.bin: native/reference_slot_assign_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/reference_slot_assign_range.o
	ld -m elf_i386 -Ttext=0x43efd0 -e original_reference_slot_assign_range $(OUT)/reference_slot_assign_range.o -o $(OUT)/reference_slot_assign_range.elf
	objcopy -O binary --only-section=.text $(OUT)/reference_slot_assign_range.elf $@

test-cycle-reference-slot-assign-range: $(OUT)/reriff-match $(OUT)/reference_slot_assign_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" reference-slot-assign-range $(OUT)/reference_slot_assign_range.bin $(OUT)/reference-slot-assign-range-comparison.json

test-recovered: test-cycle-reference-slot-assign-range
.PHONY: test-cycle-reference-slot-assign-range

# Reviewed cycle reference: sse-raise-invalid (assembly evidence only).
$(OUT)/sse_raise_invalid.bin: native/sse_raise_invalid.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse_raise_invalid.o
	ld -m elf_i386 -Ttext=0x8fc990 -e original_sse_raise_invalid $(OUT)/sse_raise_invalid.o -o $(OUT)/sse_raise_invalid.elf
	objcopy -O binary --only-section=.text $(OUT)/sse_raise_invalid.elf $@

test-cycle-sse-raise-invalid: $(OUT)/reriff-match $(OUT)/sse_raise_invalid.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse-raise-invalid $(OUT)/sse_raise_invalid.bin $(OUT)/sse-raise-invalid-comparison.json

test-recovered: test-cycle-sse-raise-invalid
.PHONY: test-cycle-sse-raise-invalid

# Reviewed cycle reference: pointer-slot-range-copy-retain (assembly evidence only).
$(OUT)/pointer_slot_range_copy_retain.bin: native/pointer_slot_range_copy_retain.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pointer_slot_range_copy_retain.o
	ld -m elf_i386 -Ttext=0x44be60 -e original_pointer_slot_range_copy_retain $(OUT)/pointer_slot_range_copy_retain.o -o $(OUT)/pointer_slot_range_copy_retain.elf
	objcopy -O binary --only-section=.text $(OUT)/pointer_slot_range_copy_retain.elf $@

test-cycle-pointer-slot-range-copy-retain: $(OUT)/reriff-match $(OUT)/pointer_slot_range_copy_retain.bin
	$(OUT)/reriff-match native-check "$(GAME)" pointer-slot-range-copy-retain $(OUT)/pointer_slot_range_copy_retain.bin $(OUT)/pointer-slot-range-copy-retain-comparison.json

test-recovered: test-cycle-pointer-slot-range-copy-retain
.PHONY: test-cycle-pointer-slot-range-copy-retain

# Reviewed cycle reference: page-header-stream-id-le32 (assembly evidence only).
$(OUT)/page_header_stream_id_le32.bin: native/page_header_stream_id_le32.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/page_header_stream_id_le32.o
	ld -m elf_i386 -Ttext=0x59b370 -e original_page_header_stream_id_le32 $(OUT)/page_header_stream_id_le32.o -o $(OUT)/page_header_stream_id_le32.elf
	objcopy -O binary --only-section=.text $(OUT)/page_header_stream_id_le32.elf $@

test-cycle-page-header-stream-id-le32: $(OUT)/reriff-match $(OUT)/page_header_stream_id_le32.bin
	$(OUT)/reriff-match native-check "$(GAME)" page-header-stream-id-le32 $(OUT)/page_header_stream_id_le32.bin $(OUT)/page-header-stream-id-le32-comparison.json

test-recovered: test-cycle-page-header-stream-id-le32
.PHONY: test-cycle-page-header-stream-id-le32

# Reviewed cycle reference: random-range-float (assembly evidence only).
$(OUT)/random_range_float.bin: native/random_range_float.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/random_range_float.o
	ld -m elf_i386 -Ttext=0x478890 -e original_random_range_float $(OUT)/random_range_float.o -o $(OUT)/random_range_float.elf
	objcopy -O binary --only-section=.text $(OUT)/random_range_float.elf $@

test-cycle-random-range-float: $(OUT)/reriff-match $(OUT)/random_range_float.bin
	$(OUT)/reriff-match native-check "$(GAME)" random-range-float $(OUT)/random_range_float.bin $(OUT)/random-range-float-comparison.json

test-recovered: test-cycle-random-range-float
.PHONY: test-cycle-random-range-float

# Reviewed cycle reference: convex-hull-shape-serialize (assembly evidence only).
$(OUT)/convex_hull_shape_serialize.bin: native/convex_hull_shape_serialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/convex_hull_shape_serialize.o
	ld -m elf_i386 -Ttext=0x47d2e0 -e original_convex_hull_shape_serialize $(OUT)/convex_hull_shape_serialize.o -o $(OUT)/convex_hull_shape_serialize.elf
	objcopy -O binary --only-section=.text $(OUT)/convex_hull_shape_serialize.elf $@

test-cycle-convex-hull-shape-serialize: $(OUT)/reriff-match $(OUT)/convex_hull_shape_serialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" convex-hull-shape-serialize $(OUT)/convex_hull_shape_serialize.bin $(OUT)/convex-hull-shape-serialize-comparison.json

test-recovered: test-cycle-convex-hull-shape-serialize
.PHONY: test-cycle-convex-hull-shape-serialize

# Reviewed cycle reference: record40-copy-assign (assembly evidence only).
$(OUT)/record40_copy_assign.bin: native/record40_copy_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record40_copy_assign.o
	ld -m elf_i386 -Ttext=0x434320 -e original_record40_copy_assign $(OUT)/record40_copy_assign.o -o $(OUT)/record40_copy_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/record40_copy_assign.elf $@

test-cycle-record40-copy-assign: $(OUT)/reriff-match $(OUT)/record40_copy_assign.bin
	$(OUT)/reriff-match native-check "$(GAME)" record40-copy-assign $(OUT)/record40_copy_assign.bin $(OUT)/record40-copy-assign-comparison.json

test-recovered: test-cycle-record40-copy-assign
.PHONY: test-cycle-record40-copy-assign

# Reviewed cycle reference: record88-copy-construct (assembly evidence only).
$(OUT)/record88_copy_construct.bin: native/record88_copy_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record88_copy_construct.o
	ld -m elf_i386 -Ttext=0x542120 -e original_record88_copy_construct $(OUT)/record88_copy_construct.o -o $(OUT)/record88_copy_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/record88_copy_construct.elf $@

test-cycle-record88-copy-construct: $(OUT)/reriff-match $(OUT)/record88_copy_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" record88-copy-construct $(OUT)/record88_copy_construct.bin $(OUT)/record88-copy-construct-comparison.json

test-recovered: test-cycle-record88-copy-construct
.PHONY: test-cycle-record88-copy-construct

# Reviewed cycle reference: record32-copy-construct-range (assembly evidence only).
$(OUT)/record32_copy_construct_range.bin: native/record32_copy_construct_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record32_copy_construct_range.o
	ld -m elf_i386 -Ttext=0x520c40 -e original_record32_copy_construct_range $(OUT)/record32_copy_construct_range.o -o $(OUT)/record32_copy_construct_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record32_copy_construct_range.elf $@

test-cycle-record32-copy-construct-range: $(OUT)/reriff-match $(OUT)/record32_copy_construct_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record32-copy-construct-range $(OUT)/record32_copy_construct_range.bin $(OUT)/record32-copy-construct-range-comparison.json

test-recovered: test-cycle-record32-copy-construct-range
.PHONY: test-cycle-record32-copy-construct-range

# Reviewed cycle reference: shape-serialization-size24 (assembly evidence only).
$(OUT)/shape_serialization_size24.bin: native/shape_serialization_size24.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/shape_serialization_size24.o
	ld -m elf_i386 -Ttext=0x415c10 -e original_shape_serialization_size24 $(OUT)/shape_serialization_size24.o -o $(OUT)/shape_serialization_size24.elf
	objcopy -O binary --only-section=.text $(OUT)/shape_serialization_size24.elf $@

test-cycle-shape-serialization-size24: $(OUT)/reriff-match $(OUT)/shape_serialization_size24.bin
	$(OUT)/reriff-match native-check "$(GAME)" shape-serialization-size24 $(OUT)/shape_serialization_size24.bin $(OUT)/shape-serialization-size24-comparison.json

test-recovered: test-cycle-shape-serialization-size24
.PHONY: test-cycle-shape-serialization-size24

# Reviewed cycle reference: nested-vector12-range-assign (assembly evidence only).
$(OUT)/nested_vector12_range_assign.bin: native/nested_vector12_range_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/nested_vector12_range_assign.o
	ld -m elf_i386 -Ttext=0x43e7d0 -e original_nested_vector12_range_assign $(OUT)/nested_vector12_range_assign.o -o $(OUT)/nested_vector12_range_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/nested_vector12_range_assign.elf $@

test-cycle-nested-vector12-range-assign: $(OUT)/reriff-match $(OUT)/nested_vector12_range_assign.bin
	$(OUT)/reriff-match native-check "$(GAME)" nested-vector12-range-assign $(OUT)/nested_vector12_range_assign.bin $(OUT)/nested-vector12-range-assign-comparison.json

test-recovered: test-cycle-nested-vector12-range-assign
.PHONY: test-cycle-nested-vector12-range-assign

# Reviewed cycle reference: u32-vector-copy-assign (assembly evidence only).
$(OUT)/u32_vector_copy_assign.bin: native/u32_vector_copy_assign.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_copy_assign.o
	ld -m elf_i386 -Ttext=0x43e240 -e original_u32_vector_copy_assign $(OUT)/u32_vector_copy_assign.o -o $(OUT)/u32_vector_copy_assign.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_copy_assign.elf $@

test-cycle-u32-vector-copy-assign: $(OUT)/reriff-match $(OUT)/u32_vector_copy_assign.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-copy-assign $(OUT)/u32_vector_copy_assign.bin $(OUT)/u32-vector-copy-assign-comparison.json

test-recovered: test-cycle-u32-vector-copy-assign
.PHONY: test-cycle-u32-vector-copy-assign

# Reviewed cycle reference: u32-range-memmove-end (assembly evidence only).
$(OUT)/u32_range_memmove_end.bin: native/u32_range_memmove_end.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_range_memmove_end.o
	ld -m elf_i386 -Ttext=0x43e770 -e original_u32_range_memmove_end $(OUT)/u32_range_memmove_end.o -o $(OUT)/u32_range_memmove_end.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_range_memmove_end.elf $@

test-cycle-u32-range-memmove-end: $(OUT)/reriff-match $(OUT)/u32_range_memmove_end.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-range-memmove-end $(OUT)/u32_range_memmove_end.bin $(OUT)/u32-range-memmove-end-comparison.json

test-recovered: test-cycle-u32-range-memmove-end
.PHONY: test-cycle-u32-range-memmove-end

# Reviewed cycle reference: u32-vector-initialize-capacity (assembly evidence only).
$(OUT)/u32_vector_initialize_capacity.bin: native/u32_vector_initialize_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_initialize_capacity.o
	ld -m elf_i386 -Ttext=0x43e630 -e original_u32_vector_initialize_capacity $(OUT)/u32_vector_initialize_capacity.o -o $(OUT)/u32_vector_initialize_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_initialize_capacity.elf $@

test-cycle-u32-vector-initialize-capacity: $(OUT)/reriff-match $(OUT)/u32_vector_initialize_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-initialize-capacity $(OUT)/u32_vector_initialize_capacity.bin $(OUT)/u32-vector-initialize-capacity-comparison.json

test-recovered: test-cycle-u32-vector-initialize-capacity
.PHONY: test-cycle-u32-vector-initialize-capacity

# Reviewed cycle reference: u32-vector-cleanup-element (assembly evidence only).
$(OUT)/u32_vector_cleanup_element.bin: native/u32_vector_cleanup_element.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_cleanup_element.o
	ld -m elf_i386 -Ttext=0x43e850 -e original_u32_vector_cleanup_element $(OUT)/u32_vector_cleanup_element.o -o $(OUT)/u32_vector_cleanup_element.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_cleanup_element.elf $@

test-cycle-u32-vector-cleanup-element: $(OUT)/reriff-match $(OUT)/u32_vector_cleanup_element.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-cleanup-element $(OUT)/u32_vector_cleanup_element.bin $(OUT)/u32-vector-cleanup-element-comparison.json

test-recovered: test-cycle-u32-vector-cleanup-element
.PHONY: test-cycle-u32-vector-cleanup-element

# Reviewed cycle reference: u32-vector-range-cleanup (assembly evidence only).
$(OUT)/u32_vector_range_cleanup.bin: native/u32_vector_range_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/u32_vector_range_cleanup.o
	ld -m elf_i386 -Ttext=0x43e800 -e original_u32_vector_range_cleanup $(OUT)/u32_vector_range_cleanup.o -o $(OUT)/u32_vector_range_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/u32_vector_range_cleanup.elf $@

test-cycle-u32-vector-range-cleanup: $(OUT)/reriff-match $(OUT)/u32_vector_range_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" u32-vector-range-cleanup $(OUT)/u32_vector_range_cleanup.bin $(OUT)/u32-vector-range-cleanup-comparison.json

test-recovered: test-cycle-u32-vector-range-cleanup
.PHONY: test-cycle-u32-vector-range-cleanup

# Reviewed cycle reference: pointer-range-has-state-six-or-seven (assembly evidence only).
$(OUT)/pointer_range_has_state_six_or_seven.bin: native/pointer_range_has_state_six_or_seven.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pointer_range_has_state_six_or_seven.o
	ld -m elf_i386 -Ttext=0x53c7c0 -e original_pointer_range_has_state_six_or_seven $(OUT)/pointer_range_has_state_six_or_seven.o -o $(OUT)/pointer_range_has_state_six_or_seven.elf
	objcopy -O binary --only-section=.text $(OUT)/pointer_range_has_state_six_or_seven.elf $@

test-cycle-pointer-range-has-state-six-or-seven: $(OUT)/reriff-match $(OUT)/pointer_range_has_state_six_or_seven.bin
	$(OUT)/reriff-match native-check "$(GAME)" pointer-range-has-state-six-or-seven $(OUT)/pointer_range_has_state_six_or_seven.bin $(OUT)/pointer-range-has-state-six-or-seven-comparison.json

test-recovered: test-cycle-pointer-range-has-state-six-or-seven
.PHONY: test-cycle-pointer-range-has-state-six-or-seven

# Reviewed cycle reference: matrix3-identity-initialize (assembly evidence only).
$(OUT)/matrix3_identity_initialize.bin: native/matrix3_identity_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/matrix3_identity_initialize.o
	ld -m elf_i386 -Ttext=0x422700 -e original_matrix3_identity_initialize $(OUT)/matrix3_identity_initialize.o -o $(OUT)/matrix3_identity_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/matrix3_identity_initialize.elf $@

test-cycle-matrix3-identity-initialize: $(OUT)/reriff-match $(OUT)/matrix3_identity_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" matrix3-identity-initialize $(OUT)/matrix3_identity_initialize.bin $(OUT)/matrix3-identity-initialize-comparison.json

test-recovered: test-cycle-matrix3-identity-initialize
.PHONY: test-cycle-matrix3-identity-initialize

# Reviewed cycle reference: virtual-base-reference-slot-release (assembly evidence only).
$(OUT)/virtual_base_reference_slot_release.bin: native/virtual_base_reference_slot_release.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/virtual_base_reference_slot_release.o
	ld -m elf_i386 -Ttext=0x41d590 -e original_virtual_base_reference_slot_release $(OUT)/virtual_base_reference_slot_release.o -o $(OUT)/virtual_base_reference_slot_release.elf
	objcopy -O binary --only-section=.text $(OUT)/virtual_base_reference_slot_release.elf $@

test-cycle-virtual-base-reference-slot-release: $(OUT)/reriff-match $(OUT)/virtual_base_reference_slot_release.bin
	$(OUT)/reriff-match native-check "$(GAME)" virtual-base-reference-slot-release $(OUT)/virtual_base_reference_slot_release.bin $(OUT)/virtual-base-reference-slot-release-comparison.json

test-recovered: test-cycle-virtual-base-reference-slot-release
.PHONY: test-cycle-virtual-base-reference-slot-release

# Reviewed cycle reference: record520-range-copy (assembly evidence only).
$(OUT)/record520_range_copy.bin: native/record520_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record520_range_copy.o
	ld -m elf_i386 -Ttext=0x416a20 -e original_record520_range_copy $(OUT)/record520_range_copy.o -o $(OUT)/record520_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record520_range_copy.elf $@

test-cycle-record520-range-copy: $(OUT)/reriff-match $(OUT)/record520_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record520-range-copy $(OUT)/record520_range_copy.bin $(OUT)/record520-range-copy-comparison.json

test-recovered: test-cycle-record520-range-copy
.PHONY: test-cycle-record520-range-copy

# Reviewed cycle reference: pointer-slot-zero-construct (assembly evidence only).
$(OUT)/pointer_slot_zero_construct.bin: native/pointer_slot_zero_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pointer_slot_zero_construct.o
	ld -m elf_i386 -Ttext=0x4223a0 -e original_pointer_slot_zero_construct $(OUT)/pointer_slot_zero_construct.o -o $(OUT)/pointer_slot_zero_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/pointer_slot_zero_construct.elf $@

test-cycle-pointer-slot-zero-construct: $(OUT)/reriff-match $(OUT)/pointer_slot_zero_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" pointer-slot-zero-construct $(OUT)/pointer_slot_zero_construct.bin $(OUT)/pointer-slot-zero-construct-comparison.json

test-recovered: test-cycle-pointer-slot-zero-construct
.PHONY: test-cycle-pointer-slot-zero-construct

# Reviewed cycle reference: pool32-chain-set-bitmap (assembly evidence only).
$(OUT)/pool32_chain_set_bitmap.bin: native/pool32_chain_set_bitmap.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/pool32_chain_set_bitmap.o
	ld -m elf_i386 -Ttext=0x453580 -e original_pool32_chain_set_bitmap $(OUT)/pool32_chain_set_bitmap.o -o $(OUT)/pool32_chain_set_bitmap.elf
	objcopy -O binary --only-section=.text $(OUT)/pool32_chain_set_bitmap.elf $@

test-cycle-pool32-chain-set-bitmap: $(OUT)/reriff-match $(OUT)/pool32_chain_set_bitmap.bin
	$(OUT)/reriff-match native-check "$(GAME)" pool32-chain-set-bitmap $(OUT)/pool32_chain_set_bitmap.bin $(OUT)/pool32-chain-set-bitmap-comparison.json

test-recovered: test-cycle-pool32-chain-set-bitmap
.PHONY: test-cycle-pool32-chain-set-bitmap

# Reviewed cycle reference: record52-default-initialize (assembly evidence only).
$(OUT)/record52_default_initialize.bin: native/record52_default_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record52_default_initialize.o
	ld -m elf_i386 -Ttext=0x568200 -e original_record52_default_initialize $(OUT)/record52_default_initialize.o -o $(OUT)/record52_default_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/record52_default_initialize.elf $@

test-cycle-record52-default-initialize: $(OUT)/reriff-match $(OUT)/record52_default_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" record52-default-initialize $(OUT)/record52_default_initialize.bin $(OUT)/record52-default-initialize-comparison.json

test-recovered: test-cycle-record52-default-initialize
.PHONY: test-cycle-record52-default-initialize

# Reviewed cycle reference: record513-range-copy (assembly evidence only).
$(OUT)/record513_range_copy.bin: native/record513_range_copy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record513_range_copy.o
	ld -m elf_i386 -Ttext=0x416aa0 -e original_record513_range_copy $(OUT)/record513_range_copy.o -o $(OUT)/record513_range_copy.elf
	objcopy -O binary --only-section=.text $(OUT)/record513_range_copy.elf $@

test-cycle-record513-range-copy: $(OUT)/reriff-match $(OUT)/record513_range_copy.bin
	$(OUT)/reriff-match native-check "$(GAME)" record513-range-copy $(OUT)/record513_range_copy.bin $(OUT)/record513-range-copy-comparison.json

test-recovered: test-cycle-record513-range-copy
.PHONY: test-cycle-record513-range-copy

# Reviewed cycle reference: record520-range-copy-construct (assembly evidence only).
$(OUT)/record520_range_copy_construct.bin: native/record520_range_copy_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record520_range_copy_construct.o
	ld -m elf_i386 -Ttext=0x416a60 -e original_record520_range_copy_construct $(OUT)/record520_range_copy_construct.o -o $(OUT)/record520_range_copy_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/record520_range_copy_construct.elf $@

test-cycle-record520-range-copy-construct: $(OUT)/reriff-match $(OUT)/record520_range_copy_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" record520-range-copy-construct $(OUT)/record520_range_copy_construct.bin $(OUT)/record520-range-copy-construct-comparison.json

test-recovered: test-cycle-record520-range-copy-construct
.PHONY: test-cycle-record520-range-copy-construct

# Reviewed cycle reference: script-table-get-integer (assembly evidence only).
$(OUT)/script_table_get_integer.bin: native/script_table_get_integer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_get_integer.o
	ld -m elf_i386 -Ttext=0x4f0ae0 -e original_script_table_get_integer $(OUT)/script_table_get_integer.o -o $(OUT)/script_table_get_integer.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_get_integer.elf $@

test-cycle-script-table-get-integer: $(OUT)/reriff-match $(OUT)/script_table_get_integer.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-get-integer $(OUT)/script_table_get_integer.bin $(OUT)/script-table-get-integer-comparison.json

test-recovered: test-cycle-script-table-get-integer
.PHONY: test-cycle-script-table-get-integer

# Reviewed cycle reference: script-table-get-string (assembly evidence only).
$(OUT)/script_table_get_string.bin: native/script_table_get_string.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_get_string.o
	ld -m elf_i386 -Ttext=0x4f0b70 -e original_script_table_get_string $(OUT)/script_table_get_string.o -o $(OUT)/script_table_get_string.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_get_string.elf $@

test-cycle-script-table-get-string: $(OUT)/reriff-match $(OUT)/script_table_get_string.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-get-string $(OUT)/script_table_get_string.bin $(OUT)/script-table-get-string-comparison.json

test-recovered: test-cycle-script-table-get-string
.PHONY: test-cycle-script-table-get-string

# Reviewed cycle reference: script-table-numeric-bucket (assembly evidence only).
$(OUT)/script_table_numeric_bucket.bin: native/script_table_numeric_bucket.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_numeric_bucket.o
	ld -m elf_i386 -Ttext=0x4f00c0 -e original_script_table_numeric_bucket $(OUT)/script_table_numeric_bucket.o -o $(OUT)/script_table_numeric_bucket.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_numeric_bucket.elf $@

test-cycle-script-table-numeric-bucket: $(OUT)/reriff-match $(OUT)/script_table_numeric_bucket.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-numeric-bucket $(OUT)/script_table_numeric_bucket.bin $(OUT)/script-table-numeric-bucket-comparison.json

test-recovered: test-cycle-script-table-numeric-bucket
.PHONY: test-cycle-script-table-numeric-bucket

# Reviewed cycle reference: script-table-length (assembly evidence only).
$(OUT)/script_table_length.bin: native/script_table_length.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_length.o
	ld -m elf_i386 -Ttext=0x4f0e90 -e original_script_table_length $(OUT)/script_table_length.o -o $(OUT)/script_table_length.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_length.elf $@

test-cycle-script-table-length: $(OUT)/reriff-match $(OUT)/script_table_length.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-length $(OUT)/script_table_length.bin $(OUT)/script-table-length-comparison.json

test-recovered: test-cycle-script-table-length
.PHONY: test-cycle-script-table-length

# Reviewed cycle reference: script-table-hash-boundary (assembly evidence only).
$(OUT)/script_table_hash_boundary.bin: native/script_table_hash_boundary.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_hash_boundary.o
	ld -m elf_i386 -Ttext=0x4f0d80 -e original_script_table_hash_boundary $(OUT)/script_table_hash_boundary.o -o $(OUT)/script_table_hash_boundary.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_hash_boundary.elf $@

test-cycle-script-table-hash-boundary: $(OUT)/reriff-match $(OUT)/script_table_hash_boundary.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-hash-boundary $(OUT)/script_table_hash_boundary.bin $(OUT)/script-table-hash-boundary-comparison.json

test-recovered: test-cycle-script-table-hash-boundary
.PHONY: test-cycle-script-table-hash-boundary

# Reviewed cycle reference: script-table-choose-array-capacity (assembly evidence only).
$(OUT)/script_table_choose_array_capacity.bin: native/script_table_choose_array_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_choose_array_capacity.o
	ld -m elf_i386 -Ttext=0x4f0370 -e original_script_table_choose_array_capacity $(OUT)/script_table_choose_array_capacity.o -o $(OUT)/script_table_choose_array_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_choose_array_capacity.elf $@

test-cycle-script-table-choose-array-capacity: $(OUT)/reriff-match $(OUT)/script_table_choose_array_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-choose-array-capacity $(OUT)/script_table_choose_array_capacity.bin $(OUT)/script-table-choose-array-capacity-comparison.json

test-recovered: test-cycle-script-table-choose-array-capacity
.PHONY: test-cycle-script-table-choose-array-capacity

# Reviewed cycle reference: script-table-main-bucket (assembly evidence only).
$(OUT)/script_table_main_bucket.bin: native/script_table_main_bucket.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_main_bucket.o
	ld -m elf_i386 -Ttext=0x4f0110 -e original_script_table_main_bucket $(OUT)/script_table_main_bucket.o -o $(OUT)/script_table_main_bucket.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_main_bucket.elf $@

test-cycle-script-table-main-bucket: $(OUT)/reriff-match $(OUT)/script_table_main_bucket.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-main-bucket $(OUT)/script_table_main_bucket.bin $(OUT)/script-table-main-bucket-comparison.json

test-recovered: test-cycle-script-table-main-bucket
.PHONY: test-cycle-script-table-main-bucket

# Reviewed cycle reference: script-table-get-value (assembly evidence only).
$(OUT)/script_table_get_value.bin: native/script_table_get_value.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_get_value.o
	ld -m elf_i386 -Ttext=0x4f0bb0 -e original_script_table_get_value $(OUT)/script_table_get_value.o -o $(OUT)/script_table_get_value.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_get_value.elf $@

test-cycle-script-table-get-value: $(OUT)/reriff-match $(OUT)/script_table_get_value.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-get-value $(OUT)/script_table_get_value.bin $(OUT)/script-table-get-value-comparison.json

test-recovered: test-cycle-script-table-get-value
.PHONY: test-cycle-script-table-get-value

# Reviewed cycle reference: script-table-count-array-histogram (assembly evidence only).
$(OUT)/script_table_count_array_histogram.bin: native/script_table_count_array_histogram.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_count_array_histogram.o
	ld -m elf_i386 -Ttext=0x4f03e0 -e original_script_table_count_array_histogram $(OUT)/script_table_count_array_histogram.o -o $(OUT)/script_table_count_array_histogram.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_count_array_histogram.elf $@

test-cycle-script-table-count-array-histogram: $(OUT)/reriff-match $(OUT)/script_table_count_array_histogram.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-count-array-histogram $(OUT)/script_table_count_array_histogram.bin $(OUT)/script-table-count-array-histogram-comparison.json

test-recovered: test-cycle-script-table-count-array-histogram
.PHONY: test-cycle-script-table-count-array-histogram

# Reviewed cycle reference: script-table-count-hash-histogram (assembly evidence only).
$(OUT)/script_table_count_hash_histogram.bin: native/script_table_count_hash_histogram.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_count_hash_histogram.o
	ld -m elf_i386 -Ttext=0x4f0460 -e original_script_table_count_hash_histogram $(OUT)/script_table_count_hash_histogram.o -o $(OUT)/script_table_count_hash_histogram.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_count_hash_histogram.elf $@

test-cycle-script-table-count-hash-histogram: $(OUT)/reriff-match $(OUT)/script_table_count_hash_histogram.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-count-hash-histogram $(OUT)/script_table_count_hash_histogram.bin $(OUT)/script-table-count-hash-histogram-comparison.json

test-recovered: test-cycle-script-table-count-hash-histogram
.PHONY: test-cycle-script-table-count-hash-histogram

# Reviewed cycle reference: script-format-variadic-bridge (assembly evidence only).
$(OUT)/script_format_variadic_bridge.bin: native/script_format_variadic_bridge.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_format_variadic_bridge.o
	ld -m elf_i386 -Ttext=0x4eff40 -e original_script_format_variadic_bridge $(OUT)/script_format_variadic_bridge.o -o $(OUT)/script_format_variadic_bridge.elf
	objcopy -O binary --only-section=.text $(OUT)/script_format_variadic_bridge.elf $@

test-cycle-script-format-variadic-bridge: $(OUT)/reriff-match $(OUT)/script_format_variadic_bridge.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-format-variadic-bridge $(OUT)/script_format_variadic_bridge.bin $(OUT)/script-format-variadic-bridge-comparison.json

test-recovered: test-cycle-script-format-variadic-bridge
.PHONY: test-cycle-script-format-variadic-bridge

# Reviewed cycle reference: script-table-resize-array (assembly evidence only).
$(OUT)/script_table_resize_array.bin: native/script_table_resize_array.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_resize_array.o
	ld -m elf_i386 -Ttext=0x4f0520 -e original_script_table_resize_array $(OUT)/script_table_resize_array.o -o $(OUT)/script_table_resize_array.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_resize_array.elf $@

test-cycle-script-table-resize-array: $(OUT)/reriff-match $(OUT)/script_table_resize_array.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-resize-array $(OUT)/script_table_resize_array.bin $(OUT)/script-table-resize-array-comparison.json

test-recovered: test-cycle-script-table-resize-array
.PHONY: test-cycle-script-table-resize-array

# Reviewed cycle reference: script-reallocate (assembly evidence only).
$(OUT)/script_reallocate.bin: native/script_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_reallocate.o
	ld -m elf_i386 -Ttext=0x4f7d10 -e original_script_reallocate $(OUT)/script_reallocate.o -o $(OUT)/script_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/script_reallocate.elf $@

test-cycle-script-reallocate: $(OUT)/reriff-match $(OUT)/script_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-reallocate $(OUT)/script_reallocate.bin $(OUT)/script-reallocate-comparison.json

test-recovered: test-cycle-script-reallocate
.PHONY: test-cycle-script-reallocate

# Reviewed cycle reference: script-table-initialize-hash-storage (assembly evidence only).
$(OUT)/script_table_initialize_hash_storage.bin: native/script_table_initialize_hash_storage.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_initialize_hash_storage.o
	ld -m elf_i386 -Ttext=0x4f0580 -e original_script_table_initialize_hash_storage $(OUT)/script_table_initialize_hash_storage.o -o $(OUT)/script_table_initialize_hash_storage.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_initialize_hash_storage.elf $@

test-cycle-script-table-initialize-hash-storage: $(OUT)/reriff-match $(OUT)/script_table_initialize_hash_storage.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-initialize-hash-storage $(OUT)/script_table_initialize_hash_storage.bin $(OUT)/script-table-initialize-hash-storage-comparison.json

test-recovered: test-cycle-script-table-initialize-hash-storage
.PHONY: test-cycle-script-table-initialize-hash-storage

# Reviewed cycle reference: script-allocation-too-large (assembly evidence only).
$(OUT)/script_allocation_too_large.bin: native/script_allocation_too_large.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_allocation_too_large.o
	ld -m elf_i386 -Ttext=0x4f7cf0 -e original_script_allocation_too_large $(OUT)/script_allocation_too_large.o -o $(OUT)/script_allocation_too_large.elf
	objcopy -O binary --only-section=.text $(OUT)/script_allocation_too_large.elf $@

test-cycle-script-allocation-too-large: $(OUT)/reriff-match $(OUT)/script_allocation_too_large.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-allocation-too-large $(OUT)/script_allocation_too_large.bin $(OUT)/script-allocation-too-large-comparison.json

test-recovered: test-cycle-script-allocation-too-large
.PHONY: test-cycle-script-allocation-too-large

# Reviewed cycle reference: script-table-destroy (assembly evidence only).
$(OUT)/script_table_destroy.bin: native/script_table_destroy.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_destroy.o
	ld -m elf_i386 -Ttext=0x4f0980 -e original_script_table_destroy $(OUT)/script_table_destroy.o -o $(OUT)/script_table_destroy.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_destroy.elf $@

test-cycle-script-table-destroy: $(OUT)/reriff-match $(OUT)/script_table_destroy.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-destroy $(OUT)/script_table_destroy.bin $(OUT)/script-table-destroy-comparison.json

test-recovered: test-cycle-script-table-destroy
.PHONY: test-cycle-script-table-destroy

# Reviewed cycle reference: script-table-construct (assembly evidence only).
$(OUT)/script_table_construct.bin: native/script_table_construct.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_construct.o
	ld -m elf_i386 -Ttext=0x4f0900 -e original_script_table_construct $(OUT)/script_table_construct.o -o $(OUT)/script_table_construct.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_construct.elf $@

test-cycle-script-table-construct: $(OUT)/reriff-match $(OUT)/script_table_construct.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-construct $(OUT)/script_table_construct.bin $(OUT)/script-table-construct-comparison.json

test-recovered: test-cycle-script-table-construct
.PHONY: test-cycle-script-table-construct

# Reviewed cycle reference: script-table-ensure-integer-slot (assembly evidence only).
$(OUT)/script_table_ensure_integer_slot.bin: native/script_table_ensure_integer_slot.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_ensure_integer_slot.o
	ld -m elf_i386 -Ttext=0x4f0cc0 -e original_script_table_ensure_integer_slot $(OUT)/script_table_ensure_integer_slot.o -o $(OUT)/script_table_ensure_integer_slot.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_ensure_integer_slot.elf $@

test-cycle-script-table-ensure-integer-slot: $(OUT)/reriff-match $(OUT)/script_table_ensure_integer_slot.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-ensure-integer-slot $(OUT)/script_table_ensure_integer_slot.bin $(OUT)/script-table-ensure-integer-slot-comparison.json

test-recovered: test-cycle-script-table-ensure-integer-slot
.PHONY: test-cycle-script-table-ensure-integer-slot

# Reviewed cycle reference: script-table-new-key (assembly evidence only).
$(OUT)/script_table_new_key.bin: native/script_table_new_key.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_new_key.o
	ld -m elf_i386 -Ttext=0x4f09e0 -e original_script_table_new_key $(OUT)/script_table_new_key.o -o $(OUT)/script_table_new_key.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_new_key.elf $@

test-cycle-script-table-new-key: $(OUT)/reriff-match $(OUT)/script_table_new_key.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-new-key $(OUT)/script_table_new_key.bin $(OUT)/script-table-new-key-comparison.json

test-recovered: test-cycle-script-table-new-key
.PHONY: test-cycle-script-table-new-key

# Reviewed cycle reference: script-table-resize (assembly evidence only).
$(OUT)/script_table_resize.bin: native/script_table_resize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_resize.o
	ld -m elf_i386 -Ttext=0x4f0660 -e original_script_table_resize $(OUT)/script_table_resize.o -o $(OUT)/script_table_resize.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_resize.elf $@

test-cycle-script-table-resize: $(OUT)/reriff-match $(OUT)/script_table_resize.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-resize $(OUT)/script_table_resize.bin $(OUT)/script-table-resize-comparison.json

test-recovered: test-cycle-script-table-resize
.PHONY: test-cycle-script-table-resize

# Reviewed cycle reference: script-table-ensure-value-slot (assembly evidence only).
$(OUT)/script_table_ensure_value_slot.bin: native/script_table_ensure_value_slot.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_ensure_value_slot.o
	ld -m elf_i386 -Ttext=0x4f0c50 -e original_script_table_ensure_value_slot $(OUT)/script_table_ensure_value_slot.o -o $(OUT)/script_table_ensure_value_slot.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_ensure_value_slot.elf $@

test-cycle-script-table-ensure-value-slot: $(OUT)/reriff-match $(OUT)/script_table_ensure_value_slot.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-ensure-value-slot $(OUT)/script_table_ensure_value_slot.bin $(OUT)/script-table-ensure-value-slot-comparison.json

test-recovered: test-cycle-script-table-ensure-value-slot
.PHONY: test-cycle-script-table-ensure-value-slot

# Reviewed cycle reference: script-table-rehash (assembly evidence only).
$(OUT)/script_table_rehash.bin: native/script_table_rehash.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_rehash.o
	ld -m elf_i386 -Ttext=0x4f0800 -e original_script_table_rehash $(OUT)/script_table_rehash.o -o $(OUT)/script_table_rehash.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_rehash.elf $@

test-cycle-script-table-rehash: $(OUT)/reriff-match $(OUT)/script_table_rehash.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-rehash $(OUT)/script_table_rehash.bin $(OUT)/script-table-rehash-comparison.json

test-recovered: test-cycle-script-table-rehash
.PHONY: test-cycle-script-table-rehash

# Reviewed cycle reference: script-runtime-error-variadic-bridge (assembly evidence only).
$(OUT)/script_runtime_error_variadic_bridge.bin: native/script_runtime_error_variadic_bridge.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_runtime_error_variadic_bridge.o
	ld -m elf_i386 -Ttext=0x486ab0 -e original_script_runtime_error_variadic_bridge $(OUT)/script_runtime_error_variadic_bridge.o -o $(OUT)/script_runtime_error_variadic_bridge.elf
	objcopy -O binary --only-section=.text $(OUT)/script_runtime_error_variadic_bridge.elf $@

test-cycle-script-runtime-error-variadic-bridge: $(OUT)/reriff-match $(OUT)/script_runtime_error_variadic_bridge.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-runtime-error-variadic-bridge $(OUT)/script_runtime_error_variadic_bridge.bin $(OUT)/script-runtime-error-variadic-bridge-comparison.json

test-recovered: test-cycle-script-runtime-error-variadic-bridge
.PHONY: test-cycle-script-runtime-error-variadic-bridge

# Reviewed cycle reference: script-frame-current-line (assembly evidence only).
$(OUT)/script_frame_current_line.bin: native/script_frame_current_line.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_frame_current_line.o
	ld -m elf_i386 -Ttext=0x485cd0 -e original_script_frame_current_line $(OUT)/script_frame_current_line.o -o $(OUT)/script_frame_current_line.elf
	objcopy -O binary --only-section=.text $(OUT)/script_frame_current_line.elf $@

test-cycle-script-frame-current-line: $(OUT)/reriff-match $(OUT)/script_frame_current_line.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-frame-current-line $(OUT)/script_frame_current_line.bin $(OUT)/script-frame-current-line-comparison.json

test-recovered: test-cycle-script-frame-current-line
.PHONY: test-cycle-script-frame-current-line

# Reviewed cycle reference: script-error-dispatch (assembly evidence only).
$(OUT)/script_error_dispatch.bin: native/script_error_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_error_dispatch.o
	ld -m elf_i386 -Ttext=0x486a30 -e original_script_error_dispatch $(OUT)/script_error_dispatch.o -o $(OUT)/script_error_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/script_error_dispatch.elf $@

test-cycle-script-error-dispatch: $(OUT)/reriff-match $(OUT)/script_error_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-error-dispatch $(OUT)/script_error_dispatch.bin $(OUT)/script-error-dispatch-comparison.json

test-recovered: test-cycle-script-error-dispatch
.PHONY: test-cycle-script-error-dispatch

# Reviewed cycle reference: script-stack-relocate-pointers (assembly evidence only).
$(OUT)/script_stack_relocate_pointers.bin: native/script_stack_relocate_pointers.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stack_relocate_pointers.o
	ld -m elf_i386 -Ttext=0x4f4e60 -e original_script_stack_relocate_pointers $(OUT)/script_stack_relocate_pointers.o -o $(OUT)/script_stack_relocate_pointers.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stack_relocate_pointers.elf $@

test-cycle-script-stack-relocate-pointers: $(OUT)/reriff-match $(OUT)/script_stack_relocate_pointers.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stack-relocate-pointers $(OUT)/script_stack_relocate_pointers.bin $(OUT)/script-stack-relocate-pointers-comparison.json

test-recovered: test-cycle-script-stack-relocate-pointers
.PHONY: test-cycle-script-stack-relocate-pointers

# Reviewed cycle reference: script-throw-status (assembly evidence only).
$(OUT)/script_throw_status.bin: native/script_throw_status.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_throw_status.o
	ld -m elf_i386 -Ttext=0x4f4d80 -e original_script_throw_status $(OUT)/script_throw_status.o -o $(OUT)/script_throw_status.elf
	objcopy -O binary --only-section=.text $(OUT)/script_throw_status.elf $@

test-cycle-script-throw-status: $(OUT)/reriff-match $(OUT)/script_throw_status.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-throw-status $(OUT)/script_throw_status.bin $(OUT)/script-throw-status-comparison.json

test-recovered: test-cycle-script-throw-status
.PHONY: test-cycle-script-throw-status

# Reviewed cycle reference: script-error-add-location (assembly evidence only).
$(OUT)/script_error_add_location.bin: native/script_error_add_location.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_error_add_location.o
	ld -m elf_i386 -Ttext=0x4869a0 -e original_script_error_add_location $(OUT)/script_error_add_location.o -o $(OUT)/script_error_add_location.elf
	objcopy -O binary --only-section=.text $(OUT)/script_error_add_location.elf $@

test-cycle-script-error-add-location: $(OUT)/reriff-match $(OUT)/script_error_add_location.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-error-add-location $(OUT)/script_error_add_location.bin $(OUT)/script-error-add-location-comparison.json

test-recovered: test-cycle-script-error-add-location
.PHONY: test-cycle-script-error-add-location

# Reviewed cycle reference: script-stack-resize (assembly evidence only).
$(OUT)/script_stack_resize.bin: native/script_stack_resize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stack_resize.o
	ld -m elf_i386 -Ttext=0x4f4ef0 -e original_script_stack_resize $(OUT)/script_stack_resize.o -o $(OUT)/script_stack_resize.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stack_resize.elf $@

test-cycle-script-stack-resize: $(OUT)/reriff-match $(OUT)/script_stack_resize.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stack-resize $(OUT)/script_stack_resize.bin $(OUT)/script-stack-resize-comparison.json

test-recovered: test-cycle-script-stack-resize
.PHONY: test-cycle-script-stack-resize

# Reviewed cycle reference: script-stack-push-terminated (assembly evidence only).
$(OUT)/script_stack_push_terminated.bin: native/script_stack_push_terminated.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stack_push_terminated.o
	ld -m elf_i386 -Ttext=0x4efab0 -e original_script_stack_push_terminated $(OUT)/script_stack_push_terminated.o -o $(OUT)/script_stack_push_terminated.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stack_push_terminated.elf $@

test-cycle-script-stack-push-terminated: $(OUT)/reriff-match $(OUT)/script_stack_push_terminated.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stack-push-terminated $(OUT)/script_stack_push_terminated.bin $(OUT)/script-stack-push-terminated-comparison.json

test-recovered: test-cycle-script-stack-push-terminated
.PHONY: test-cycle-script-stack-push-terminated

# Reviewed cycle reference: script-source-name-format (assembly evidence only).
$(OUT)/script_source_name_format.bin: native/script_source_name_format.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_source_name_format.o
	ld -m elf_i386 -Ttext=0x4eff60 -e original_script_source_name_format $(OUT)/script_source_name_format.o -o $(OUT)/script_source_name_format.elf
	objcopy -O binary --only-section=.text $(OUT)/script_source_name_format.elf $@

test-cycle-script-source-name-format: $(OUT)/reriff-match $(OUT)/script_source_name_format.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-source-name-format $(OUT)/script_source_name_format.bin $(OUT)/script-source-name-format-comparison.json

test-recovered: test-cycle-script-source-name-format
.PHONY: test-cycle-script-source-name-format

# Reviewed cycle reference: script-stream-refill (assembly evidence only).
$(OUT)/script_stream_refill.bin: native/script_stream_refill.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stream_refill.o
	ld -m elf_i386 -Ttext=0x4f5ff0 -e original_script_stream_refill $(OUT)/script_stream_refill.o -o $(OUT)/script_stream_refill.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stream_refill.elf $@

test-cycle-script-stream-refill: $(OUT)/reriff-match $(OUT)/script_stream_refill.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stream-refill $(OUT)/script_stream_refill.bin $(OUT)/script-stream-refill-comparison.json

test-recovered: test-cycle-script-stream-refill
.PHONY: test-cycle-script-stream-refill

# Reviewed cycle reference: script-table-cached-event-lookup (assembly evidence only).
$(OUT)/script_table_cached_event_lookup.bin: native/script_table_cached_event_lookup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_cached_event_lookup.o
	ld -m elf_i386 -Ttext=0x4f5ca0 -e original_script_table_cached_event_lookup $(OUT)/script_table_cached_event_lookup.o -o $(OUT)/script_table_cached_event_lookup.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_cached_event_lookup.elf $@

test-cycle-script-table-cached-event-lookup: $(OUT)/reriff-match $(OUT)/script_table_cached_event_lookup.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-cached-event-lookup $(OUT)/script_table_cached_event_lookup.bin $(OUT)/script-table-cached-event-lookup-comparison.json

test-recovered: test-cycle-script-table-cached-event-lookup
.PHONY: test-cycle-script-table-cached-event-lookup

# Reviewed cycle reference: script-string-intern (assembly evidence only).
$(OUT)/script_string_intern.bin: native/script_string_intern.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_string_intern.o
	ld -m elf_i386 -Ttext=0x4f5e40 -e original_script_string_intern $(OUT)/script_string_intern.o -o $(OUT)/script_string_intern.elf
	objcopy -O binary --only-section=.text $(OUT)/script_string_intern.elf $@

test-cycle-script-string-intern: $(OUT)/reriff-match $(OUT)/script_string_intern.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-string-intern $(OUT)/script_string_intern.bin $(OUT)/script-string-intern-comparison.json

test-recovered: test-cycle-script-string-intern
.PHONY: test-cycle-script-string-intern

# Reviewed cycle reference: script-string-buckets-resize (assembly evidence only).
$(OUT)/script_string_buckets_resize.bin: native/script_string_buckets_resize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_string_buckets_resize.o
	ld -m elf_i386 -Ttext=0x4f5d70 -e original_script_string_buckets_resize $(OUT)/script_string_buckets_resize.o -o $(OUT)/script_string_buckets_resize.elf
	objcopy -O binary --only-section=.text $(OUT)/script_string_buckets_resize.elf $@

test-cycle-script-string-buckets-resize: $(OUT)/reriff-match $(OUT)/script_string_buckets_resize.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-string-buckets-resize $(OUT)/script_string_buckets_resize.bin $(OUT)/script-string-buckets-resize-comparison.json

test-recovered: test-cycle-script-string-buckets-resize
.PHONY: test-cycle-script-string-buckets-resize

# Reviewed cycle reference: script-value-raw-equal (assembly evidence only).
$(OUT)/script_value_raw_equal.bin: native/script_value_raw_equal.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_value_raw_equal.o
	ld -m elf_i386 -Ttext=0x4ef9a0 -e original_script_value_raw_equal $(OUT)/script_value_raw_equal.o -o $(OUT)/script_value_raw_equal.elf
	objcopy -O binary --only-section=.text $(OUT)/script_value_raw_equal.elf $@

test-cycle-script-value-raw-equal: $(OUT)/reriff-match $(OUT)/script_value_raw_equal.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-value-raw-equal $(OUT)/script_value_raw_equal.bin $(OUT)/script-value-raw-equal-comparison.json

test-recovered: test-cycle-script-value-raw-equal
.PHONY: test-cycle-script-value-raw-equal

# Reviewed cycle reference: script-string-parse-number (assembly evidence only).
$(OUT)/script_string_parse_number.bin: native/script_string_parse_number.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_string_parse_number.o
	ld -m elf_i386 -Ttext=0x4ef9f0 -e original_script_string_parse_number $(OUT)/script_string_parse_number.o -o $(OUT)/script_string_parse_number.elf
	objcopy -O binary --only-section=.text $(OUT)/script_string_parse_number.elf $@

test-cycle-script-string-parse-number: $(OUT)/reriff-match $(OUT)/script_string_parse_number.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-string-parse-number $(OUT)/script_string_parse_number.bin $(OUT)/script-string-parse-number-comparison.json

test-recovered: test-cycle-script-string-parse-number
.PHONY: test-cycle-script-string-parse-number

# Reviewed cycle reference: script-stream-peek (assembly evidence only).
$(OUT)/script_stream_peek.bin: native/script_stream_peek.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stream_peek.o
	ld -m elf_i386 -Ttext=0x4f6040 -e original_script_stream_peek $(OUT)/script_stream_peek.o -o $(OUT)/script_stream_peek.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stream_peek.elf $@

test-cycle-script-stream-peek: $(OUT)/reriff-match $(OUT)/script_stream_peek.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stream-peek $(OUT)/script_stream_peek.bin $(OUT)/script-stream-peek-comparison.json

test-recovered: test-cycle-script-stream-peek
.PHONY: test-cycle-script-stream-peek

# Reviewed cycle reference: script-value-metamethod-lookup (assembly evidence only).
$(OUT)/script_value_metamethod_lookup.bin: native/script_value_metamethod_lookup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_value_metamethod_lookup.o
	ld -m elf_i386 -Ttext=0x4f5d00 -e original_script_value_metamethod_lookup $(OUT)/script_value_metamethod_lookup.o -o $(OUT)/script_value_metamethod_lookup.elf
	objcopy -O binary --only-section=.text $(OUT)/script_value_metamethod_lookup.elf $@

test-cycle-script-value-metamethod-lookup: $(OUT)/reriff-match $(OUT)/script_value_metamethod_lookup.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-value-metamethod-lookup $(OUT)/script_value_metamethod_lookup.bin $(OUT)/script-value-metamethod-lookup-comparison.json

test-recovered: test-cycle-script-value-metamethod-lookup
.PHONY: test-cycle-script-value-metamethod-lookup

# Reviewed cycle reference: script-buffer-ensure-capacity (assembly evidence only).
$(OUT)/script_buffer_ensure_capacity.bin: native/script_buffer_ensure_capacity.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_buffer_ensure_capacity.o
	ld -m elf_i386 -Ttext=0x4f6140 -e original_script_buffer_ensure_capacity $(OUT)/script_buffer_ensure_capacity.o -o $(OUT)/script_buffer_ensure_capacity.elf
	objcopy -O binary --only-section=.text $(OUT)/script_buffer_ensure_capacity.elf $@

test-cycle-script-buffer-ensure-capacity: $(OUT)/reriff-match $(OUT)/script_buffer_ensure_capacity.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-buffer-ensure-capacity $(OUT)/script_buffer_ensure_capacity.bin $(OUT)/script-buffer-ensure-capacity-comparison.json

test-recovered: test-cycle-script-buffer-ensure-capacity
.PHONY: test-cycle-script-buffer-ensure-capacity

# Reviewed cycle reference: script-stream-read-block (assembly evidence only).
$(OUT)/script_stream_read_block.bin: native/script_stream_read_block.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_stream_read_block.o
	ld -m elf_i386 -Ttext=0x4f60a0 -e original_script_stream_read_block $(OUT)/script_stream_read_block.o -o $(OUT)/script_stream_read_block.elf
	objcopy -O binary --only-section=.text $(OUT)/script_stream_read_block.elf $@

test-cycle-script-stream-read-block: $(OUT)/reriff-match $(OUT)/script_stream_read_block.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-stream-read-block $(OUT)/script_stream_read_block.bin $(OUT)/script-stream-read-block-comparison.json

test-recovered: test-cycle-script-stream-read-block
.PHONY: test-cycle-script-stream-read-block

# Reviewed cycle reference: script-number-to-string (assembly evidence only).
$(OUT)/script_number_to_string.bin: native/script_number_to_string.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_number_to_string.o
	ld -m elf_i386 -Ttext=0x4f25c0 -e original_script_number_to_string $(OUT)/script_number_to_string.o -o $(OUT)/script_number_to_string.elf
	objcopy -O binary --only-section=.text $(OUT)/script_number_to_string.elf $@

test-cycle-script-number-to-string: $(OUT)/reriff-match $(OUT)/script_number_to_string.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-number-to-string $(OUT)/script_number_to_string.bin $(OUT)/script-number-to-string-comparison.json

test-recovered: test-cycle-script-number-to-string
.PHONY: test-cycle-script-number-to-string

# Reviewed cycle reference: script-error-reset-state (assembly evidence only).
$(OUT)/script_error_reset_state.bin: native/script_error_reset_state.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_error_reset_state.o
	ld -m elf_i386 -Ttext=0x4f4d00 -e original_script_error_reset_state $(OUT)/script_error_reset_state.o -o $(OUT)/script_error_reset_state.elf
	objcopy -O binary --only-section=.text $(OUT)/script_error_reset_state.elf $@

test-cycle-script-error-reset-state: $(OUT)/reriff-match $(OUT)/script_error_reset_state.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-error-reset-state $(OUT)/script_error_reset_state.bin $(OUT)/script-error-reset-state-comparison.json

test-recovered: test-cycle-script-error-reset-state
.PHONY: test-cycle-script-error-reset-state

# Reviewed cycle reference: script-callinfo-resize (assembly evidence only).
$(OUT)/script_callinfo_resize.bin: native/script_callinfo_resize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_callinfo_resize.o
	ld -m elf_i386 -Ttext=0x4f4f50 -e original_script_callinfo_resize $(OUT)/script_callinfo_resize.o -o $(OUT)/script_callinfo_resize.elf
	objcopy -O binary --only-section=.text $(OUT)/script_callinfo_resize.elf $@

test-cycle-script-callinfo-resize: $(OUT)/reriff-match $(OUT)/script_callinfo_resize.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-callinfo-resize $(OUT)/script_callinfo_resize.bin $(OUT)/script-callinfo-resize-comparison.json

test-recovered: test-cycle-script-callinfo-resize
.PHONY: test-cycle-script-callinfo-resize

# Reviewed cycle reference: script-close-upvalues (assembly evidence only).
$(OUT)/script_close_upvalues.bin: native/script_close_upvalues.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_close_upvalues.o
	ld -m elf_i386 -Ttext=0x4f49b0 -e original_script_close_upvalues $(OUT)/script_close_upvalues.o -o $(OUT)/script_close_upvalues.elf
	objcopy -O binary --only-section=.text $(OUT)/script_close_upvalues.elf $@

test-cycle-script-close-upvalues: $(OUT)/reriff-match $(OUT)/script_close_upvalues.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-close-upvalues $(OUT)/script_close_upvalues.bin $(OUT)/script-close-upvalues-comparison.json

test-recovered: test-cycle-script-close-upvalues
.PHONY: test-cycle-script-close-upvalues

# Reviewed cycle reference: script-error-object-set (assembly evidence only).
$(OUT)/script_error_object_set.bin: native/script_error_object_set.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_error_object_set.o
	ld -m elf_i386 -Ttext=0x4f4c90 -e original_script_error_object_set $(OUT)/script_error_object_set.o -o $(OUT)/script_error_object_set.elf
	objcopy -O binary --only-section=.text $(OUT)/script_error_object_set.elf $@

test-cycle-script-error-object-set: $(OUT)/reriff-match $(OUT)/script_error_object_set.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-error-object-set $(OUT)/script_error_object_set.bin $(OUT)/script-error-object-set-comparison.json

test-recovered: test-cycle-script-error-object-set
.PHONY: test-cycle-script-error-object-set

# Reviewed cycle reference: script-gc-forward-barrier (assembly evidence only).
$(OUT)/script_gc_forward_barrier.bin: native/script_gc_forward_barrier.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_forward_barrier.o
	ld -m elf_i386 -Ttext=0x4f2560 -e original_script_gc_forward_barrier $(OUT)/script_gc_forward_barrier.o -o $(OUT)/script_gc_forward_barrier.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_forward_barrier.elf $@

test-cycle-script-gc-forward-barrier: $(OUT)/reriff-match $(OUT)/script_gc_forward_barrier.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-forward-barrier $(OUT)/script_gc_forward_barrier.bin $(OUT)/script-gc-forward-barrier-comparison.json

test-recovered: test-cycle-script-gc-forward-barrier
.PHONY: test-cycle-script-gc-forward-barrier

# Reviewed cycle reference: script-gc-separate-finalizable (assembly evidence only).
$(OUT)/script_gc_separate_finalizable.bin: native/script_gc_separate_finalizable.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_separate_finalizable.o
	ld -m elf_i386 -Ttext=0x4f1090 -e original_script_gc_separate_finalizable $(OUT)/script_gc_separate_finalizable.o -o $(OUT)/script_gc_separate_finalizable.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_separate_finalizable.elf $@

test-cycle-script-gc-separate-finalizable: $(OUT)/reriff-match $(OUT)/script_gc_separate_finalizable.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-separate-finalizable $(OUT)/script_gc_separate_finalizable.bin $(OUT)/script-gc-separate-finalizable-comparison.json

test-recovered: test-cycle-script-gc-separate-finalizable
.PHONY: test-cycle-script-gc-separate-finalizable

# Reviewed cycle reference: script-call-with-depth-guard (assembly evidence only).
$(OUT)/script_call_with_depth_guard.bin: native/script_call_with_depth_guard.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_call_with_depth_guard.o
	ld -m elf_i386 -Ttext=0x4f5830 -e original_script_call_with_depth_guard $(OUT)/script_call_with_depth_guard.o -o $(OUT)/script_call_with_depth_guard.elf
	objcopy -O binary --only-section=.text $(OUT)/script_call_with_depth_guard.elf $@

test-cycle-script-call-with-depth-guard: $(OUT)/reriff-match $(OUT)/script_call_with_depth_guard.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-call-with-depth-guard $(OUT)/script_call_with_depth_guard.bin $(OUT)/script-call-with-depth-guard-comparison.json

test-recovered: test-cycle-script-call-with-depth-guard
.PHONY: test-cycle-script-call-with-depth-guard

# Reviewed cycle reference: float-pow-precise-bridge (assembly evidence only).
$(OUT)/float_pow_precise_bridge.bin: native/float_pow_precise_bridge.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/float_pow_precise_bridge.o
	ld -m elf_i386 -Ttext=0x4f2590 -e original_float_pow_precise_bridge $(OUT)/float_pow_precise_bridge.o -o $(OUT)/float_pow_precise_bridge.elf
	objcopy -O binary --only-section=.text $(OUT)/float_pow_precise_bridge.elf $@

test-cycle-float-pow-precise-bridge: $(OUT)/reriff-match $(OUT)/float_pow_precise_bridge.bin
	$(OUT)/reriff-match native-check "$(GAME)" float-pow-precise-bridge $(OUT)/float_pow_precise_bridge.bin $(OUT)/float-pow-precise-bridge-comparison.json

test-recovered: test-cycle-float-pow-precise-bridge
.PHONY: test-cycle-float-pow-precise-bridge

# Reviewed cycle reference: script-table-ensure-string-slot (assembly evidence only).
$(OUT)/script_table_ensure_string_slot.bin: native/script_table_ensure_string_slot.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_table_ensure_string_slot.o
	ld -m elf_i386 -Ttext=0x4f0d10 -e original_script_table_ensure_string_slot $(OUT)/script_table_ensure_string_slot.o -o $(OUT)/script_table_ensure_string_slot.elf
	objcopy -O binary --only-section=.text $(OUT)/script_table_ensure_string_slot.elf $@

test-cycle-script-table-ensure-string-slot: $(OUT)/reriff-match $(OUT)/script_table_ensure_string_slot.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-table-ensure-string-slot $(OUT)/script_table_ensure_string_slot.bin $(OUT)/script-table-ensure-string-slot-comparison.json

test-recovered: test-cycle-script-table-ensure-string-slot
.PHONY: test-cycle-script-table-ensure-string-slot

# Reviewed cycle reference: script-prototype-local-name (assembly evidence only).
$(OUT)/script_prototype_local_name.bin: native/script_prototype_local_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_prototype_local_name.o
	ld -m elf_i386 -Ttext=0x4f4c40 -e original_script_prototype_local_name $(OUT)/script_prototype_local_name.o -o $(OUT)/script_prototype_local_name.elf
	objcopy -O binary --only-section=.text $(OUT)/script_prototype_local_name.elf $@

test-cycle-script-prototype-local-name: $(OUT)/reriff-match $(OUT)/script_prototype_local_name.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-prototype-local-name $(OUT)/script_prototype_local_name.bin $(OUT)/script-prototype-local-name-comparison.json

test-recovered: test-cycle-script-prototype-local-name
.PHONY: test-cycle-script-prototype-local-name

# Reviewed cycle reference: script-callinfo-grow (assembly evidence only).
$(OUT)/script_callinfo_grow.bin: native/script_callinfo_grow.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_callinfo_grow.o
	ld -m elf_i386 -Ttext=0x4f4fd0 -e original_script_callinfo_grow $(OUT)/script_callinfo_grow.o -o $(OUT)/script_callinfo_grow.elf
	objcopy -O binary --only-section=.text $(OUT)/script_callinfo_grow.elf $@

test-cycle-script-callinfo-grow: $(OUT)/reriff-match $(OUT)/script_callinfo_grow.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-callinfo-grow $(OUT)/script_callinfo_grow.bin $(OUT)/script-callinfo-grow-comparison.json

test-recovered: test-cycle-script-callinfo-grow
.PHONY: test-cycle-script-callinfo-grow

# Reviewed cycle reference: script-prototype-dispose (assembly evidence only).
$(OUT)/script_prototype_dispose.bin: native/script_prototype_dispose.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_prototype_dispose.o
	ld -m elf_i386 -Ttext=0x4f4bb0 -e original_script_prototype_dispose $(OUT)/script_prototype_dispose.o -o $(OUT)/script_prototype_dispose.elf
	objcopy -O binary --only-section=.text $(OUT)/script_prototype_dispose.elf $@

test-cycle-script-prototype-dispose: $(OUT)/reriff-match $(OUT)/script_prototype_dispose.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-prototype-dispose $(OUT)/script_prototype_dispose.bin $(OUT)/script-prototype-dispose-comparison.json

test-recovered: test-cycle-script-prototype-dispose
.PHONY: test-cycle-script-prototype-dispose

# Reviewed cycle reference: script-lua-closure-allocate (assembly evidence only).
$(OUT)/script_lua_closure_allocate.bin: native/script_lua_closure_allocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_lua_closure_allocate.o
	ld -m elf_i386 -Ttext=0x4f4800 -e original_script_lua_closure_allocate $(OUT)/script_lua_closure_allocate.o -o $(OUT)/script_lua_closure_allocate.elf
	objcopy -O binary --only-section=.text $(OUT)/script_lua_closure_allocate.elf $@

test-cycle-script-lua-closure-allocate: $(OUT)/reriff-match $(OUT)/script_lua_closure_allocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-lua-closure-allocate $(OUT)/script_lua_closure_allocate.bin $(OUT)/script-lua-closure-allocate-comparison.json

test-recovered: test-cycle-script-lua-closure-allocate
.PHONY: test-cycle-script-lua-closure-allocate

# Reviewed cycle reference: simplex-solver-reset (assembly evidence only).
$(OUT)/simplex_solver_reset.bin: native/simplex_solver_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/simplex_solver_reset.o
	ld -m elf_i386 -Ttext=0x546240 -e original_simplex_solver_reset $(OUT)/simplex_solver_reset.o -o $(OUT)/simplex_solver_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/simplex_solver_reset.elf $@

test-cycle-simplex-solver-reset: $(OUT)/reriff-match $(OUT)/simplex_solver_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" simplex-solver-reset $(OUT)/simplex_solver_reset.bin $(OUT)/simplex-solver-reset-comparison.json

test-recovered: test-cycle-simplex-solver-reset
.PHONY: test-cycle-simplex-solver-reset

# Reviewed cycle reference: simplex-solver-contains-vertex (assembly evidence only).
$(OUT)/simplex_solver_contains_vertex.bin: native/simplex_solver_contains_vertex.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/simplex_solver_contains_vertex.o
	ld -m elf_i386 -Ttext=0x546a30 -e original_simplex_solver_contains_vertex $(OUT)/simplex_solver_contains_vertex.o -o $(OUT)/simplex_solver_contains_vertex.elf
	objcopy -O binary --only-section=.text $(OUT)/simplex_solver_contains_vertex.elf $@

test-cycle-simplex-solver-contains-vertex: $(OUT)/reriff-match $(OUT)/simplex_solver_contains_vertex.bin
	$(OUT)/reriff-match native-check "$(GAME)" simplex-solver-contains-vertex $(OUT)/simplex_solver_contains_vertex.bin $(OUT)/simplex-solver-contains-vertex-comparison.json

test-recovered: test-cycle-simplex-solver-contains-vertex
.PHONY: test-cycle-simplex-solver-contains-vertex

# Reviewed cycle reference: simplex-solver-reduce-vertices (assembly evidence only).
$(OUT)/simplex_solver_reduce_vertices.bin: native/simplex_solver_reduce_vertices.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/simplex_solver_reduce_vertices.o
	ld -m elf_i386 -Ttext=0x546130 -e original_simplex_solver_reduce_vertices $(OUT)/simplex_solver_reduce_vertices.o -o $(OUT)/simplex_solver_reduce_vertices.elf
	objcopy -O binary --only-section=.text $(OUT)/simplex_solver_reduce_vertices.elf $@

test-cycle-simplex-solver-reduce-vertices: $(OUT)/reriff-match $(OUT)/simplex_solver_reduce_vertices.bin
	$(OUT)/reriff-match native-check "$(GAME)" simplex-solver-reduce-vertices $(OUT)/simplex_solver_reduce_vertices.bin $(OUT)/simplex-solver-reduce-vertices-comparison.json

test-recovered: test-cycle-simplex-solver-reduce-vertices
.PHONY: test-cycle-simplex-solver-reduce-vertices

# Reviewed cycle reference: collision-face-list-unlink (assembly evidence only).
$(OUT)/collision_face_list_unlink.bin: native/collision_face_list_unlink.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_face_list_unlink.o
	ld -m elf_i386 -Ttext=0x549780 -e original_collision_face_list_unlink $(OUT)/collision_face_list_unlink.o -o $(OUT)/collision_face_list_unlink.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_face_list_unlink.elf $@

test-cycle-collision-face-list-unlink: $(OUT)/reriff-match $(OUT)/collision_face_list_unlink.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-face-list-unlink $(OUT)/collision_face_list_unlink.bin $(OUT)/collision-face-list-unlink-comparison.json

test-recovered: test-cycle-collision-face-list-unlink
.PHONY: test-cycle-collision-face-list-unlink

# Reviewed cycle reference: simplex-result-reset (assembly evidence only).
$(OUT)/simplex_result_reset.bin: native/simplex_result_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/simplex_result_reset.o
	ld -m elf_i386 -Ttext=0x546100 -e original_simplex_result_reset $(OUT)/simplex_result_reset.o -o $(OUT)/simplex_result_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/simplex_result_reset.elf $@

test-cycle-simplex-result-reset: $(OUT)/reriff-match $(OUT)/simplex_result_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" simplex-result-reset $(OUT)/simplex_result_reset.bin $(OUT)/simplex-result-reset-comparison.json

test-recovered: test-cycle-simplex-result-reset
.PHONY: test-cycle-simplex-result-reset

# Reviewed cycle reference: device-indexed-handle-select (assembly evidence only).
$(OUT)/device_indexed_handle_select.bin: native/device_indexed_handle_select.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/device_indexed_handle_select.o
	ld -m elf_i386 -Ttext=0x536320 -e original_device_indexed_handle_select $(OUT)/device_indexed_handle_select.o -o $(OUT)/device_indexed_handle_select.elf
	objcopy -O binary --only-section=.text $(OUT)/device_indexed_handle_select.elf $@

test-cycle-device-indexed-handle-select: $(OUT)/reriff-match $(OUT)/device_indexed_handle_select.bin
	$(OUT)/reriff-match native-check "$(GAME)" device-indexed-handle-select $(OUT)/device_indexed_handle_select.bin $(OUT)/device-indexed-handle-select-comparison.json

test-recovered: test-cycle-device-indexed-handle-select
.PHONY: test-cycle-device-indexed-handle-select

# Reviewed cycle reference: collision-workspace-link-free-records (assembly evidence only).
$(OUT)/collision_workspace_link_free_records.bin: native/collision_workspace_link_free_records.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/collision_workspace_link_free_records.o
	ld -m elf_i386 -Ttext=0x5497b0 -e original_collision_workspace_link_free_records $(OUT)/collision_workspace_link_free_records.o -o $(OUT)/collision_workspace_link_free_records.elf
	objcopy -O binary --only-section=.text $(OUT)/collision_workspace_link_free_records.elf $@

test-cycle-collision-workspace-link-free-records: $(OUT)/reriff-match $(OUT)/collision_workspace_link_free_records.bin
	$(OUT)/reriff-match native-check "$(GAME)" collision-workspace-link-free-records $(OUT)/collision_workspace_link_free_records.bin $(OUT)/collision-workspace-link-free-records-comparison.json

test-recovered: test-cycle-collision-workspace-link-free-records
.PHONY: test-cycle-collision-workspace-link-free-records

# Reviewed cycle reference: flag-selected-product (assembly evidence only).
$(OUT)/flag_selected_product.bin: native/flag_selected_product.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/flag_selected_product.o
	ld -m elf_i386 -Ttext=0x55d190 -e original_flag_selected_product $(OUT)/flag_selected_product.o -o $(OUT)/flag_selected_product.elf
	objcopy -O binary --only-section=.text $(OUT)/flag_selected_product.elf $@

test-cycle-flag-selected-product: $(OUT)/reriff-match $(OUT)/flag_selected_product.bin
	$(OUT)/reriff-match native-check "$(GAME)" flag-selected-product $(OUT)/flag_selected_product.bin $(OUT)/flag-selected-product-comparison.json

test-recovered: test-cycle-flag-selected-product
.PHONY: test-cycle-flag-selected-product

# Reviewed cycle reference: script-remove-active-locals (assembly evidence only).
$(OUT)/script_remove_active_locals.bin: native/script_remove_active_locals.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_remove_active_locals.o
	ld -m elf_i386 -Ttext=0x557510 -e original_script_remove_active_locals $(OUT)/script_remove_active_locals.o -o $(OUT)/script_remove_active_locals.elf
	objcopy -O binary --only-section=.text $(OUT)/script_remove_active_locals.elf $@

test-cycle-script-remove-active-locals: $(OUT)/reriff-match $(OUT)/script_remove_active_locals.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-remove-active-locals $(OUT)/script_remove_active_locals.bin $(OUT)/script-remove-active-locals-comparison.json

test-recovered: test-cycle-script-remove-active-locals
.PHONY: test-cycle-script-remove-active-locals

# Reviewed cycle reference: buffer-pack-high-three-bytes (assembly evidence only).
$(OUT)/buffer_pack_high_three_bytes.bin: native/buffer_pack_high_three_bytes.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/buffer_pack_high_three_bytes.o
	ld -m elf_i386 -Ttext=0x55d1c0 -e original_buffer_pack_high_three_bytes $(OUT)/buffer_pack_high_three_bytes.o -o $(OUT)/buffer_pack_high_three_bytes.elf
	objcopy -O binary --only-section=.text $(OUT)/buffer_pack_high_three_bytes.elf $@

test-cycle-buffer-pack-high-three-bytes: $(OUT)/reriff-match $(OUT)/buffer_pack_high_three_bytes.bin
	$(OUT)/reriff-match native-check "$(GAME)" buffer-pack-high-three-bytes $(OUT)/buffer_pack_high_three_bytes.bin $(OUT)/buffer-pack-high-three-bytes-comparison.json

test-recovered: test-cycle-buffer-pack-high-three-bytes
.PHONY: test-cycle-buffer-pack-high-three-bytes

# Reviewed cycle reference: record48-default-construct-range (assembly evidence only).
$(OUT)/record48_default_construct_range.bin: native/record48_default_construct_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record48_default_construct_range.o
	ld -m elf_i386 -Ttext=0x541f40 -e original_record48_default_construct_range $(OUT)/record48_default_construct_range.o -o $(OUT)/record48_default_construct_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record48_default_construct_range.elf $@

test-cycle-record48-default-construct-range: $(OUT)/reriff-match $(OUT)/record48_default_construct_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record48-default-construct-range $(OUT)/record48_default_construct_range.bin $(OUT)/record48-default-construct-range-comparison.json

test-recovered: test-cycle-record48-default-construct-range
.PHONY: test-cycle-record48-default-construct-range

# Reviewed cycle reference: block64-zero-initialize (assembly evidence only).
$(OUT)/block64_zero_initialize.bin: native/block64_zero_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/block64_zero_initialize.o
	ld -m elf_i386 -Ttext=0x41e770 -e original_block64_zero_initialize $(OUT)/block64_zero_initialize.o -o $(OUT)/block64_zero_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/block64_zero_initialize.elf $@

test-cycle-block64-zero-initialize: $(OUT)/reriff-match $(OUT)/block64_zero_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" block64-zero-initialize $(OUT)/block64_zero_initialize.bin $(OUT)/block64-zero-initialize-comparison.json

test-recovered: test-cycle-block64-zero-initialize
.PHONY: test-cycle-block64-zero-initialize

# Reviewed cycle reference: audio-sample-rate-index (assembly evidence only).
$(OUT)/audio_sample_rate_index.bin: native/audio_sample_rate_index.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_sample_rate_index.o
	ld -m elf_i386 -Ttext=0x55c9f0 -e original_audio_sample_rate_index $(OUT)/audio_sample_rate_index.o -o $(OUT)/audio_sample_rate_index.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_sample_rate_index.elf $@

test-cycle-audio-sample-rate-index: $(OUT)/reriff-match $(OUT)/audio_sample_rate_index.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-sample-rate-index $(OUT)/audio_sample_rate_index.bin $(OUT)/audio-sample-rate-index-comparison.json

test-recovered: test-cycle-audio-sample-rate-index
.PHONY: test-cycle-audio-sample-rate-index

# Reviewed cycle reference: audio-configuration-select (assembly evidence only).
$(OUT)/audio_configuration_select.bin: native/audio_configuration_select.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_configuration_select.o
	ld -m elf_i386 -Ttext=0x55ca20 -e original_audio_configuration_select $(OUT)/audio_configuration_select.o -o $(OUT)/audio_configuration_select.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_configuration_select.elf $@

test-cycle-audio-configuration-select: $(OUT)/reriff-match $(OUT)/audio_configuration_select.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-configuration-select $(OUT)/audio_configuration_select.bin $(OUT)/audio-configuration-select-comparison.json

test-recovered: test-cycle-audio-configuration-select
.PHONY: test-cycle-audio-configuration-select

# Reviewed cycle reference: audio-bitstream-read16 (assembly evidence only).
$(OUT)/audio_bitstream_read16.bin: native/audio_bitstream_read16.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_bitstream_read16.o
	ld -m elf_i386 -Ttext=0x58eab0 -e original_audio_bitstream_read16 $(OUT)/audio_bitstream_read16.o -o $(OUT)/audio_bitstream_read16.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_bitstream_read16.elf $@

test-cycle-audio-bitstream-read16: $(OUT)/reriff-match $(OUT)/audio_bitstream_read16.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-bitstream-read16 $(OUT)/audio_bitstream_read16.bin $(OUT)/audio-bitstream-read16-comparison.json

test-recovered: test-cycle-audio-bitstream-read16
.PHONY: test-cycle-audio-bitstream-read16

# Reviewed cycle reference: audio-frame-header-plausible (assembly evidence only).
$(OUT)/audio_frame_header_plausible.bin: native/audio_frame_header_plausible.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_frame_header_plausible.o
	ld -m elf_i386 -Ttext=0x58eb00 -e original_audio_frame_header_plausible $(OUT)/audio_frame_header_plausible.o -o $(OUT)/audio_frame_header_plausible.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_frame_header_plausible.elf $@

test-cycle-audio-frame-header-plausible: $(OUT)/reriff-match $(OUT)/audio_frame_header_plausible.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-frame-header-plausible $(OUT)/audio_frame_header_plausible.bin $(OUT)/audio-frame-header-plausible-comparison.json

test-recovered: test-cycle-audio-frame-header-plausible
.PHONY: test-cycle-audio-frame-header-plausible

# Reviewed cycle reference: audio-frame-headers-compatible (assembly evidence only).
$(OUT)/audio_frame_headers_compatible.bin: native/audio_frame_headers_compatible.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_frame_headers_compatible.o
	ld -m elf_i386 -Ttext=0x58f460 -e original_audio_frame_headers_compatible $(OUT)/audio_frame_headers_compatible.o -o $(OUT)/audio_frame_headers_compatible.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_frame_headers_compatible.elf $@

test-cycle-audio-frame-headers-compatible: $(OUT)/reriff-match $(OUT)/audio_frame_headers_compatible.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-frame-headers-compatible $(OUT)/audio_frame_headers_compatible.bin $(OUT)/audio-frame-headers-compatible-comparison.json

test-recovered: test-cycle-audio-frame-headers-compatible
.PHONY: test-cycle-audio-frame-headers-compatible

# Reviewed cycle reference: audio-frame-reuse-buffered (assembly evidence only).
$(OUT)/audio_frame_reuse_buffered.bin: native/audio_frame_reuse_buffered.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_frame_reuse_buffered.o
	ld -m elf_i386 -Ttext=0x58f4a0 -e original_audio_frame_reuse_buffered $(OUT)/audio_frame_reuse_buffered.o -o $(OUT)/audio_frame_reuse_buffered.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_frame_reuse_buffered.elf $@

test-cycle-audio-frame-reuse-buffered: $(OUT)/reriff-match $(OUT)/audio_frame_reuse_buffered.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-frame-reuse-buffered $(OUT)/audio_frame_reuse_buffered.bin $(OUT)/audio-frame-reuse-buffered-comparison.json

test-recovered: test-cycle-audio-frame-reuse-buffered
.PHONY: test-cycle-audio-frame-reuse-buffered

# Reviewed cycle reference: audio-buffer-adjust-position (assembly evidence only).
$(OUT)/audio_buffer_adjust_position.bin: native/audio_buffer_adjust_position.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_adjust_position.o
	ld -m elf_i386 -Ttext=0x58e330 -e original_audio_buffer_adjust_position $(OUT)/audio_buffer_adjust_position.o -o $(OUT)/audio_buffer_adjust_position.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_adjust_position.elf $@

test-cycle-audio-buffer-adjust-position: $(OUT)/reriff-match $(OUT)/audio_buffer_adjust_position.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-adjust-position $(OUT)/audio_buffer_adjust_position.bin $(OUT)/audio-buffer-adjust-position-comparison.json

test-recovered: test-cycle-audio-buffer-adjust-position
.PHONY: test-cycle-audio-buffer-adjust-position

# Reviewed cycle reference: audio-buffer-advance-position (assembly evidence only).
$(OUT)/audio_buffer_advance_position.bin: native/audio_buffer_advance_position.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_advance_position.o
	ld -m elf_i386 -Ttext=0x58e2d0 -e original_audio_buffer_advance_position $(OUT)/audio_buffer_advance_position.o -o $(OUT)/audio_buffer_advance_position.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_advance_position.elf $@

test-cycle-audio-buffer-advance-position: $(OUT)/reriff-match $(OUT)/audio_buffer_advance_position.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-advance-position $(OUT)/audio_buffer_advance_position.bin $(OUT)/audio-buffer-advance-position-comparison.json

test-recovered: test-cycle-audio-buffer-advance-position
.PHONY: test-cycle-audio-buffer-advance-position

# Reviewed cycle reference: audio-unavailable-callback (assembly evidence only).
$(OUT)/audio_unavailable_callback.bin: native/audio_unavailable_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_unavailable_callback.o
	ld -m elf_i386 -Ttext=0x58e5b0 -e original_audio_unavailable_callback $(OUT)/audio_unavailable_callback.o -o $(OUT)/audio_unavailable_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_unavailable_callback.elf $@

test-cycle-audio-unavailable-callback: $(OUT)/reriff-match $(OUT)/audio_unavailable_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-unavailable-callback $(OUT)/audio_unavailable_callback.bin $(OUT)/audio-unavailable-callback-comparison.json

test-recovered: test-cycle-audio-unavailable-callback
.PHONY: test-cycle-audio-unavailable-callback

# Reviewed cycle reference: audio-input-read-dispatch (assembly evidence only).
$(OUT)/audio_input_read_dispatch.bin: native/audio_input_read_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_input_read_dispatch.o
	ld -m elf_i386 -Ttext=0x58d830 -e original_audio_input_read_dispatch $(OUT)/audio_input_read_dispatch.o -o $(OUT)/audio_input_read_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_input_read_dispatch.elf $@

test-cycle-audio-input-read-dispatch: $(OUT)/reriff-match $(OUT)/audio_input_read_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-input-read-dispatch $(OUT)/audio_input_read_dispatch.bin $(OUT)/audio-input-read-dispatch-comparison.json

test-recovered: test-cycle-audio-input-read-dispatch
.PHONY: test-cycle-audio-input-read-dispatch

# Reviewed cycle reference: script-call-result-finish (assembly evidence only).
$(OUT)/script_call_result_finish.bin: native/script_call_result_finish.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_call_result_finish.o
	ld -m elf_i386 -Ttext=0x4f57a0 -e original_script_call_result_finish $(OUT)/script_call_result_finish.o -o $(OUT)/script_call_result_finish.elf
	objcopy -O binary --only-section=.text $(OUT)/script_call_result_finish.elf $@

test-cycle-script-call-result-finish: $(OUT)/reriff-match $(OUT)/script_call_result_finish.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-call-result-finish $(OUT)/script_call_result_finish.bin $(OUT)/script-call-result-finish-comparison.json

test-recovered: test-cycle-script-call-result-finish
.PHONY: test-cycle-script-call-result-finish

# Reviewed cycle reference: audio-memory-seek-callback (assembly evidence only).
$(OUT)/audio_memory_seek_callback.bin: native/audio_memory_seek_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_memory_seek_callback.o
	ld -m elf_i386 -Ttext=0x55dd90 -e original_audio_memory_seek_callback $(OUT)/audio_memory_seek_callback.o -o $(OUT)/audio_memory_seek_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_memory_seek_callback.elf $@

test-cycle-audio-memory-seek-callback: $(OUT)/reriff-match $(OUT)/audio_memory_seek_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-memory-seek-callback $(OUT)/audio_memory_seek_callback.bin $(OUT)/audio-memory-seek-callback-comparison.json

test-recovered: test-cycle-audio-memory-seek-callback
.PHONY: test-cycle-audio-memory-seek-callback

# Reviewed cycle reference: audio-memory-read-callback (assembly evidence only).
$(OUT)/audio_memory_read_callback.bin: native/audio_memory_read_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_memory_read_callback.o
	ld -m elf_i386 -Ttext=0x55dd50 -e original_audio_memory_read_callback $(OUT)/audio_memory_read_callback.o -o $(OUT)/audio_memory_read_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_memory_read_callback.elf $@

test-cycle-audio-memory-read-callback: $(OUT)/reriff-match $(OUT)/audio_memory_read_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-memory-read-callback $(OUT)/audio_memory_read_callback.bin $(OUT)/audio-memory-read-callback-comparison.json

test-recovered: test-cycle-audio-memory-read-callback
.PHONY: test-cycle-audio-memory-read-callback

# Reviewed cycle reference: audio-buffer-commit-consumed (assembly evidence only).
$(OUT)/audio_buffer_commit_consumed.bin: native/audio_buffer_commit_consumed.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_commit_consumed.o
	ld -m elf_i386 -Ttext=0x58e180 -e original_audio_buffer_commit_consumed $(OUT)/audio_buffer_commit_consumed.o -o $(OUT)/audio_buffer_commit_consumed.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_commit_consumed.elf $@

test-cycle-audio-buffer-commit-consumed: $(OUT)/reriff-match $(OUT)/audio_buffer_commit_consumed.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-commit-consumed $(OUT)/audio_buffer_commit_consumed.bin $(OUT)/audio-buffer-commit-consumed-comparison.json

test-recovered: test-cycle-audio-buffer-commit-consumed
.PHONY: test-cycle-audio-buffer-commit-consumed

# Reviewed cycle reference: audio-backend-reset (assembly evidence only).
$(OUT)/audio_backend_reset.bin: native/audio_backend_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_backend_reset.o
	ld -m elf_i386 -Ttext=0x58e6f0 -e original_audio_backend_reset $(OUT)/audio_backend_reset.o -o $(OUT)/audio_backend_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_backend_reset.elf $@

test-cycle-audio-backend-reset: $(OUT)/reriff-match $(OUT)/audio_backend_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-backend-reset $(OUT)/audio_backend_reset.bin $(OUT)/audio-backend-reset-comparison.json

test-recovered: test-cycle-audio-backend-reset
.PHONY: test-cycle-audio-backend-reset

# Reviewed cycle reference: audio-stream-commit-position (assembly evidence only).
$(OUT)/audio_stream_commit_position.bin: native/audio_stream_commit_position.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stream_commit_position.o
	ld -m elf_i386 -Ttext=0x58e3d0 -e original_audio_stream_commit_position $(OUT)/audio_stream_commit_position.o -o $(OUT)/audio_stream_commit_position.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stream_commit_position.elf $@

test-cycle-audio-stream-commit-position: $(OUT)/reriff-match $(OUT)/audio_stream_commit_position.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stream-commit-position $(OUT)/audio_stream_commit_position.bin $(OUT)/audio-stream-commit-position-comparison.json

test-recovered: test-cycle-audio-stream-commit-position
.PHONY: test-cycle-audio-stream-commit-position

# Reviewed cycle reference: audio-callback-table-contains (assembly evidence only).
$(OUT)/audio_callback_table_contains.bin: native/audio_callback_table_contains.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_callback_table_contains.o
	ld -m elf_i386 -Ttext=0x58e7e0 -e original_audio_callback_table_contains $(OUT)/audio_callback_table_contains.o -o $(OUT)/audio_callback_table_contains.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_callback_table_contains.elf $@

test-cycle-audio-callback-table-contains: $(OUT)/reriff-match $(OUT)/audio_callback_table_contains.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-callback-table-contains $(OUT)/audio_callback_table_contains.bin $(OUT)/audio-callback-table-contains-comparison.json

test-recovered: test-cycle-audio-callback-table-contains
.PHONY: test-cycle-audio-callback-table-contains

# Reviewed cycle reference: audio-stream-query-position (assembly evidence only).
$(OUT)/audio_stream_query_position.bin: native/audio_stream_query_position.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stream_query_position.o
	ld -m elf_i386 -Ttext=0x58dc90 -e original_audio_stream_query_position $(OUT)/audio_stream_query_position.o -o $(OUT)/audio_stream_query_position.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stream_query_position.elf $@

test-cycle-audio-stream-query-position: $(OUT)/reriff-match $(OUT)/audio_stream_query_position.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stream-query-position $(OUT)/audio_stream_query_position.bin $(OUT)/audio-stream-query-position-comparison.json

test-recovered: test-cycle-audio-stream-query-position
.PHONY: test-cycle-audio-stream-query-position

# Reviewed cycle reference: audio-stream-read-exact (assembly evidence only).
$(OUT)/audio_stream_read_exact.bin: native/audio_stream_read_exact.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stream_read_exact.o
	ld -m elf_i386 -Ttext=0x58dc60 -e original_audio_stream_read_exact $(OUT)/audio_stream_read_exact.o -o $(OUT)/audio_stream_read_exact.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stream_read_exact.elf $@

test-cycle-audio-stream-read-exact: $(OUT)/reriff-match $(OUT)/audio_stream_read_exact.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stream-read-exact $(OUT)/audio_stream_read_exact.bin $(OUT)/audio-stream-read-exact-comparison.json

test-recovered: test-cycle-audio-stream-read-exact
.PHONY: test-cycle-audio-stream-read-exact

# Reviewed cycle reference: audio-unity-arrays-initialize (assembly evidence only).
$(OUT)/audio_unity_arrays_initialize.bin: native/audio_unity_arrays_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_unity_arrays_initialize.o
	ld -m elf_i386 -Ttext=0x58a120 -e original_audio_unity_arrays_initialize $(OUT)/audio_unity_arrays_initialize.o -o $(OUT)/audio_unity_arrays_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_unity_arrays_initialize.elf $@

test-cycle-audio-unity-arrays-initialize: $(OUT)/reriff-match $(OUT)/audio_unity_arrays_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-unity-arrays-initialize $(OUT)/audio_unity_arrays_initialize.bin $(OUT)/audio-unity-arrays-initialize-comparison.json

test-recovered: test-cycle-audio-unity-arrays-initialize
.PHONY: test-cycle-audio-unity-arrays-initialize

# Reviewed cycle reference: audio-buffer-read-range (assembly evidence only).
$(OUT)/audio_buffer_read_range.bin: native/audio_buffer_read_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_read_range.o
	ld -m elf_i386 -Ttext=0x58e0d0 -e original_audio_buffer_read_range $(OUT)/audio_buffer_read_range.o -o $(OUT)/audio_buffer_read_range.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_read_range.elf $@

test-cycle-audio-buffer-read-range: $(OUT)/reriff-match $(OUT)/audio_buffer_read_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-read-range $(OUT)/audio_buffer_read_range.bin $(OUT)/audio-buffer-read-range-comparison.json

test-recovered: test-cycle-audio-buffer-read-range
.PHONY: test-cycle-audio-buffer-read-range

# Reviewed cycle reference: audio-selected-callback-validate (assembly evidence only).
$(OUT)/audio_selected_callback_validate.bin: native/audio_selected_callback_validate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_selected_callback_validate.o
	ld -m elf_i386 -Ttext=0x58e820 -e original_audio_selected_callback_validate $(OUT)/audio_selected_callback_validate.o -o $(OUT)/audio_selected_callback_validate.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_selected_callback_validate.elf $@

test-cycle-audio-selected-callback-validate: $(OUT)/reriff-match $(OUT)/audio_selected_callback_validate.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-selected-callback-validate $(OUT)/audio_selected_callback_validate.bin $(OUT)/audio-selected-callback-validate-comparison.json

test-recovered: test-cycle-audio-selected-callback-validate
.PHONY: test-cycle-audio-selected-callback-validate

# Reviewed cycle reference: audio-synthesis-window-initialize (assembly evidence only).
$(OUT)/audio_synthesis_window_initialize.bin: native/audio_synthesis_window_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_synthesis_window_initialize.o
	ld -m elf_i386 -Ttext=0x590c40 -e original_audio_synthesis_window_initialize $(OUT)/audio_synthesis_window_initialize.o -o $(OUT)/audio_synthesis_window_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_synthesis_window_initialize.elf $@

test-cycle-audio-synthesis-window-initialize: $(OUT)/reriff-match $(OUT)/audio_synthesis_window_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-synthesis-window-initialize $(OUT)/audio_synthesis_window_initialize.bin $(OUT)/audio-synthesis-window-initialize-comparison.json

test-recovered: test-cycle-audio-synthesis-window-initialize
.PHONY: test-cycle-audio-synthesis-window-initialize

# Reviewed cycle reference: audio-input-read-loop (assembly evidence only).
$(OUT)/audio_input_read_loop.bin: native/audio_input_read_loop.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_input_read_loop.o
	ld -m elf_i386 -Ttext=0x58d880 -e original_audio_input_read_loop $(OUT)/audio_input_read_loop.o -o $(OUT)/audio_input_read_loop.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_input_read_loop.elf $@

test-cycle-audio-input-read-loop: $(OUT)/reriff-match $(OUT)/audio_input_read_loop.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-input-read-loop $(OUT)/audio_input_read_loop.bin $(OUT)/audio-input-read-loop-comparison.json

test-recovered: test-cycle-audio-input-read-loop
.PHONY: test-cycle-audio-input-read-loop

# Reviewed cycle reference: audio-buffer-dispose-cached (assembly evidence only).
$(OUT)/audio_buffer_dispose_cached.bin: native/audio_buffer_dispose_cached.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_dispose_cached.o
	ld -m elf_i386 -Ttext=0x58de70 -e original_audio_buffer_dispose_cached $(OUT)/audio_buffer_dispose_cached.o -o $(OUT)/audio_buffer_dispose_cached.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_dispose_cached.elf $@

test-cycle-audio-buffer-dispose-cached: $(OUT)/reriff-match $(OUT)/audio_buffer_dispose_cached.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-dispose-cached $(OUT)/audio_buffer_dispose_cached.bin $(OUT)/audio-buffer-dispose-cached-comparison.json

test-recovered: test-cycle-audio-buffer-dispose-cached
.PHONY: test-cycle-audio-buffer-dispose-cached

# Reviewed cycle reference: audio-buffer-rebalance-cache (assembly evidence only).
$(OUT)/audio_buffer_rebalance_cache.bin: native/audio_buffer_rebalance_cache.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_rebalance_cache.o
	ld -m elf_i386 -Ttext=0x58deb0 -e original_audio_buffer_rebalance_cache $(OUT)/audio_buffer_rebalance_cache.o -o $(OUT)/audio_buffer_rebalance_cache.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_rebalance_cache.elf $@

test-cycle-audio-buffer-rebalance-cache: $(OUT)/reriff-match $(OUT)/audio_buffer_rebalance_cache.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-rebalance-cache $(OUT)/audio_buffer_rebalance_cache.bin $(OUT)/audio-buffer-rebalance-cache-comparison.json

test-recovered: test-cycle-audio-buffer-rebalance-cache
.PHONY: test-cycle-audio-buffer-rebalance-cache

# Reviewed cycle reference: audio-buffer-reset (assembly evidence only).
$(OUT)/audio_buffer_reset.bin: native/audio_buffer_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_reset.o
	ld -m elf_i386 -Ttext=0x58df50 -e original_audio_buffer_reset $(OUT)/audio_buffer_reset.o -o $(OUT)/audio_buffer_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_reset.elf $@

test-cycle-audio-buffer-reset: $(OUT)/reriff-match $(OUT)/audio_buffer_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-reset $(OUT)/audio_buffer_reset.bin $(OUT)/audio-buffer-reset-comparison.json

test-recovered: test-cycle-audio-buffer-reset
.PHONY: test-cycle-audio-buffer-reset

# Reviewed cycle reference: audio-metadata-state-initialize (assembly evidence only).
$(OUT)/audio_metadata_state_initialize.bin: native/audio_metadata_state_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_metadata_state_initialize.o
	ld -m elf_i386 -Ttext=0x58b2c0 -e original_audio_metadata_state_initialize $(OUT)/audio_metadata_state_initialize.o -o $(OUT)/audio_metadata_state_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_metadata_state_initialize.elf $@

test-cycle-audio-metadata-state-initialize: $(OUT)/reriff-match $(OUT)/audio_metadata_state_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-metadata-state-initialize $(OUT)/audio_metadata_state_initialize.bin $(OUT)/audio-metadata-state-initialize-comparison.json

test-recovered: test-cycle-audio-metadata-state-initialize
.PHONY: test-cycle-audio-metadata-state-initialize

# Reviewed cycle reference: audio-buffer-append (assembly evidence only).
$(OUT)/audio_buffer_append.bin: native/audio_buffer_append.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffer_append.o
	ld -m elf_i386 -Ttext=0x58dfc0 -e original_audio_buffer_append $(OUT)/audio_buffer_append.o -o $(OUT)/audio_buffer_append.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffer_append.elf $@

test-cycle-audio-buffer-append: $(OUT)/reriff-match $(OUT)/audio_buffer_append.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffer-append $(OUT)/audio_buffer_append.bin $(OUT)/audio-buffer-append-comparison.json

test-recovered: test-cycle-audio-buffer-append
.PHONY: test-cycle-audio-buffer-append

# Reviewed cycle reference: record12-copy-range (assembly evidence only).
$(OUT)/record12_copy_range.bin: native/record12_copy_range.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_copy_range.o
	ld -m elf_i386 -Ttext=0x42bb40 -e original_record12_copy_range $(OUT)/record12_copy_range.o -o $(OUT)/record12_copy_range.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_copy_range.elf $@

test-cycle-record12-copy-range: $(OUT)/reriff-match $(OUT)/record12_copy_range.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-copy-range $(OUT)/record12_copy_range.bin $(OUT)/record12-copy-range-comparison.json

test-recovered: test-cycle-record12-copy-range
.PHONY: test-cycle-record12-copy-range

# Reviewed cycle reference: audio-coefficient-rows-initialize (assembly evidence only).
$(OUT)/audio_coefficient_rows_initialize.bin: native/audio_coefficient_rows_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_coefficient_rows_initialize.o
	ld -m elf_i386 -Ttext=0x596390 -e original_audio_coefficient_rows_initialize $(OUT)/audio_coefficient_rows_initialize.o -o $(OUT)/audio_coefficient_rows_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_coefficient_rows_initialize.elf $@

test-cycle-audio-coefficient-rows-initialize: $(OUT)/reriff-match $(OUT)/audio_coefficient_rows_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-coefficient-rows-initialize $(OUT)/audio_coefficient_rows_initialize.bin $(OUT)/audio-coefficient-rows-initialize-comparison.json

test-recovered: test-cycle-audio-coefficient-rows-initialize
.PHONY: test-cycle-audio-coefficient-rows-initialize

# Reviewed cycle reference: audio-coefficient-row-generate (assembly evidence only).
$(OUT)/audio_coefficient_row_generate.bin: native/audio_coefficient_row_generate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_coefficient_row_generate.o
	ld -m elf_i386 -Ttext=0x5963d0 -e original_audio_coefficient_row_generate $(OUT)/audio_coefficient_row_generate.o -o $(OUT)/audio_coefficient_row_generate.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_coefficient_row_generate.elf $@

test-cycle-audio-coefficient-row-generate: $(OUT)/reriff-match $(OUT)/audio_coefficient_row_generate.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-coefficient-row-generate $(OUT)/audio_coefficient_row_generate.bin $(OUT)/audio-coefficient-row-generate-comparison.json

test-recovered: test-cycle-audio-coefficient-row-generate
.PHONY: test-cycle-audio-coefficient-row-generate

# Reviewed cycle reference: audio-index-compact-even (assembly evidence only).
$(OUT)/audio_index_compact_even.bin: native/audio_index_compact_even.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_index_compact_even.o
	ld -m elf_i386 -Ttext=0x5960b0 -e original_audio_index_compact_even $(OUT)/audio_index_compact_even.o -o $(OUT)/audio_index_compact_even.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_index_compact_even.elf $@

test-cycle-audio-index-compact-even: $(OUT)/reriff-match $(OUT)/audio_index_compact_even.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-index-compact-even $(OUT)/audio_index_compact_even.bin $(OUT)/audio-index-compact-even-comparison.json

test-recovered: test-cycle-audio-index-compact-even
.PHONY: test-cycle-audio-index-compact-even

# Reviewed cycle reference: audio-buffered-read-exact-callback (assembly evidence only).
$(OUT)/audio_buffered_read_exact_callback.bin: native/audio_buffered_read_exact_callback.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffered_read_exact_callback.o
	ld -m elf_i386 -Ttext=0x58e2a0 -e original_audio_buffered_read_exact_callback $(OUT)/audio_buffered_read_exact_callback.o -o $(OUT)/audio_buffered_read_exact_callback.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffered_read_exact_callback.elf $@

test-cycle-audio-buffered-read-exact-callback: $(OUT)/reriff-match $(OUT)/audio_buffered_read_exact_callback.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffered-read-exact-callback $(OUT)/audio_buffered_read_exact_callback.bin $(OUT)/audio-buffered-read-exact-callback-comparison.json

test-recovered: test-cycle-audio-buffered-read-exact-callback
.PHONY: test-cycle-audio-buffered-read-exact-callback

# Reviewed cycle reference: audio-buffered-backend-initialize (assembly evidence only).
$(OUT)/audio_buffered_backend_initialize.bin: native/audio_buffered_backend_initialize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_buffered_backend_initialize.o
	ld -m elf_i386 -Ttext=0x58e1f0 -e original_audio_buffered_backend_initialize $(OUT)/audio_buffered_backend_initialize.o -o $(OUT)/audio_buffered_backend_initialize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_buffered_backend_initialize.elf $@

test-cycle-audio-buffered-backend-initialize: $(OUT)/reriff-match $(OUT)/audio_buffered_backend_initialize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-buffered-backend-initialize $(OUT)/audio_buffered_backend_initialize.bin $(OUT)/audio-buffered-backend-initialize-comparison.json

test-recovered: test-cycle-audio-buffered-backend-initialize
.PHONY: test-cycle-audio-buffered-backend-initialize

# Reviewed cycle reference: audio-resample-phase-at-count (assembly evidence only).
$(OUT)/audio_resample_phase_at_count.bin: native/audio_resample_phase_at_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_resample_phase_at_count.o
	ld -m elf_i386 -Ttext=0x5908d0 -e original_audio_resample_phase_at_count $(OUT)/audio_resample_phase_at_count.o -o $(OUT)/audio_resample_phase_at_count.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_resample_phase_at_count.elf $@

test-cycle-audio-resample-phase-at-count: $(OUT)/reriff-match $(OUT)/audio_resample_phase_at_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-resample-phase-at-count $(OUT)/audio_resample_phase_at_count.bin $(OUT)/audio-resample-phase-at-count-comparison.json

test-recovered: test-cycle-audio-resample-phase-at-count
.PHONY: test-cycle-audio-resample-phase-at-count

# Reviewed cycle reference: audio-stream-shift-byte (assembly evidence only).
$(OUT)/audio_stream_shift_byte.bin: native/audio_stream_shift_byte.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stream_shift_byte.o
	ld -m elf_i386 -Ttext=0x58dad0 -e original_audio_stream_shift_byte $(OUT)/audio_stream_shift_byte.o -o $(OUT)/audio_stream_shift_byte.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stream_shift_byte.elf $@

test-cycle-audio-stream-shift-byte: $(OUT)/reriff-match $(OUT)/audio_stream_shift_byte.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stream-shift-byte $(OUT)/audio_stream_shift_byte.bin $(OUT)/audio-stream-shift-byte-comparison.json

test-recovered: test-cycle-audio-stream-shift-byte
.PHONY: test-cycle-audio-stream-shift-byte

# Reviewed cycle reference: audio-stream-append-buffer (assembly evidence only).
$(OUT)/audio_stream_append_buffer.bin: native/audio_stream_append_buffer.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stream_append_buffer.o
	ld -m elf_i386 -Ttext=0x58e250 -e original_audio_stream_append_buffer $(OUT)/audio_stream_append_buffer.o -o $(OUT)/audio_stream_append_buffer.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stream_append_buffer.elf $@

test-cycle-audio-stream-append-buffer: $(OUT)/reriff-match $(OUT)/audio_stream_append_buffer.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stream-append-buffer $(OUT)/audio_stream_append_buffer.bin $(OUT)/audio-stream-append-buffer-comparison.json

test-recovered: test-cycle-audio-stream-append-buffer
.PHONY: test-cycle-audio-stream-append-buffer

# Reviewed cycle reference: audio-decoder-close-reset (assembly evidence only).
$(OUT)/audio_decoder_close_reset.bin: native/audio_decoder_close_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_decoder_close_reset.o
	ld -m elf_i386 -Ttext=0x55c990 -e original_audio_decoder_close_reset $(OUT)/audio_decoder_close_reset.o -o $(OUT)/audio_decoder_close_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_decoder_close_reset.elf $@

test-cycle-audio-decoder-close-reset: $(OUT)/reriff-match $(OUT)/audio_decoder_close_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-decoder-close-reset $(OUT)/audio_decoder_close_reset.bin $(OUT)/audio-decoder-close-reset-comparison.json

test-recovered: test-cycle-audio-decoder-close-reset
.PHONY: test-cycle-audio-decoder-close-reset

# Reviewed cycle reference: audio-decoder-reset-state (assembly evidence only).
$(OUT)/audio_decoder_reset_state.bin: native/audio_decoder_reset_state.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_decoder_reset_state.o
	ld -m elf_i386 -Ttext=0x58a500 -e original_audio_decoder_reset_state $(OUT)/audio_decoder_reset_state.o -o $(OUT)/audio_decoder_reset_state.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_decoder_reset_state.elf $@

test-cycle-audio-decoder-reset-state: $(OUT)/reriff-match $(OUT)/audio_decoder_reset_state.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-decoder-reset-state $(OUT)/audio_decoder_reset_state.bin $(OUT)/audio-decoder-reset-state-comparison.json

test-recovered: test-cycle-audio-decoder-reset-state
.PHONY: test-cycle-audio-decoder-reset-state

# Reviewed cycle reference: audio-decoder-reset-buffers (assembly evidence only).
$(OUT)/audio_decoder_reset_buffers.bin: native/audio_decoder_reset_buffers.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_decoder_reset_buffers.o
	ld -m elf_i386 -Ttext=0x58a410 -e original_audio_decoder_reset_buffers $(OUT)/audio_decoder_reset_buffers.o -o $(OUT)/audio_decoder_reset_buffers.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_decoder_reset_buffers.elf $@

test-cycle-audio-decoder-reset-buffers: $(OUT)/reriff-match $(OUT)/audio_decoder_reset_buffers.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-decoder-reset-buffers $(OUT)/audio_decoder_reset_buffers.bin $(OUT)/audio-decoder-reset-buffers-comparison.json

test-recovered: test-cycle-audio-decoder-reset-buffers
.PHONY: test-cycle-audio-decoder-reset-buffers

# Reviewed cycle reference: audio-record32-array-clear (assembly evidence only).
$(OUT)/audio_record32_array_clear.bin: native/audio_record32_array_clear.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record32_array_clear.o
	ld -m elf_i386 -Ttext=0x58b3c0 -e original_audio_record32_array_clear $(OUT)/audio_record32_array_clear.o -o $(OUT)/audio_record32_array_clear.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record32_array_clear.elf $@

test-cycle-audio-record32-array-clear: $(OUT)/reriff-match $(OUT)/audio_record32_array_clear.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record32-array-clear $(OUT)/audio_record32_array_clear.bin $(OUT)/audio-record32-array-clear-comparison.json

test-recovered: test-cycle-audio-record32-array-clear
.PHONY: test-cycle-audio-record32-array-clear

# Reviewed cycle reference: audio-decoder-metadata-clear (assembly evidence only).
$(OUT)/audio_decoder_metadata_clear.bin: native/audio_decoder_metadata_clear.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_decoder_metadata_clear.o
	ld -m elf_i386 -Ttext=0x58b220 -e original_audio_decoder_metadata_clear $(OUT)/audio_decoder_metadata_clear.o -o $(OUT)/audio_decoder_metadata_clear.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_decoder_metadata_clear.elf $@

test-cycle-audio-decoder-metadata-clear: $(OUT)/reriff-match $(OUT)/audio_decoder_metadata_clear.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-decoder-metadata-clear $(OUT)/audio_decoder_metadata_clear.bin $(OUT)/audio-decoder-metadata-clear-comparison.json

test-recovered: test-cycle-audio-decoder-metadata-clear
.PHONY: test-cycle-audio-decoder-metadata-clear

# Reviewed cycle reference: audio-callback-backend-select (assembly evidence only).
$(OUT)/audio_callback_backend_select.bin: native/audio_callback_backend_select.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_callback_backend_select.o
	ld -m elf_i386 -Ttext=0x58e750 -e original_audio_callback_backend_select $(OUT)/audio_callback_backend_select.o -o $(OUT)/audio_callback_backend_select.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_callback_backend_select.elf $@

test-cycle-audio-callback-backend-select: $(OUT)/reriff-match $(OUT)/audio_callback_backend_select.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-callback-backend-select $(OUT)/audio_callback_backend_select.bin $(OUT)/audio-callback-backend-select-comparison.json

test-recovered: test-cycle-audio-callback-backend-select
.PHONY: test-cycle-audio-callback-backend-select

# Reviewed cycle reference: audio-decoder-reset-stream (assembly evidence only).
$(OUT)/audio_decoder_reset_stream.bin: native/audio_decoder_reset_stream.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_decoder_reset_stream.o
	ld -m elf_i386 -Ttext=0x58a550 -e original_audio_decoder_reset_stream $(OUT)/audio_decoder_reset_stream.o -o $(OUT)/audio_decoder_reset_stream.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_decoder_reset_stream.elf $@

test-cycle-audio-decoder-reset-stream: $(OUT)/reriff-match $(OUT)/audio_decoder_reset_stream.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-decoder-reset-stream $(OUT)/audio_decoder_reset_stream.bin $(OUT)/audio-decoder-reset-stream-comparison.json

test-recovered: test-cycle-audio-decoder-reset-stream
.PHONY: test-cycle-audio-decoder-reset-stream

# Reviewed cycle reference: audio-record36-array-clear (assembly evidence only).
$(OUT)/audio_record36_array_clear.bin: native/audio_record36_array_clear.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record36_array_clear.o
	ld -m elf_i386 -Ttext=0x58b460 -e original_audio_record36_array_clear $(OUT)/audio_record36_array_clear.o -o $(OUT)/audio_record36_array_clear.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record36_array_clear.elf $@

test-cycle-audio-record36-array-clear: $(OUT)/reriff-match $(OUT)/audio_record36_array_clear.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record36-array-clear $(OUT)/audio_record36_array_clear.bin $(OUT)/audio-record36-array-clear-comparison.json

test-recovered: test-cycle-audio-record36-array-clear
.PHONY: test-cycle-audio-record36-array-clear

# Reviewed cycle reference: audio-stereo-callback-bridge (assembly evidence only).
$(OUT)/audio_stereo_callback_bridge.bin: native/audio_stereo_callback_bridge.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_stereo_callback_bridge.o
	ld -m elf_i386 -Ttext=0x58e7a0 -e original_audio_stereo_callback_bridge $(OUT)/audio_stereo_callback_bridge.o -o $(OUT)/audio_stereo_callback_bridge.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_stereo_callback_bridge.elf $@

test-cycle-audio-stereo-callback-bridge: $(OUT)/reriff-match $(OUT)/audio_stereo_callback_bridge.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-stereo-callback-bridge $(OUT)/audio_stereo_callback_bridge.bin $(OUT)/audio-stereo-callback-bridge-comparison.json

test-recovered: test-cycle-audio-stereo-callback-bridge
.PHONY: test-cycle-audio-stereo-callback-bridge

# Reviewed cycle reference: audio-record32-dispose-buffers (assembly evidence only).
$(OUT)/audio_record32_dispose_buffers.bin: native/audio_record32_dispose_buffers.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record32_dispose_buffers.o
	ld -m elf_i386 -Ttext=0x58b300 -e original_audio_record32_dispose_buffers $(OUT)/audio_record32_dispose_buffers.o -o $(OUT)/audio_record32_dispose_buffers.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record32_dispose_buffers.elf $@

test-cycle-audio-record32-dispose-buffers: $(OUT)/reriff-match $(OUT)/audio_record32_dispose_buffers.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record32-dispose-buffers $(OUT)/audio_record32_dispose_buffers.bin $(OUT)/audio-record32-dispose-buffers-comparison.json

test-recovered: test-cycle-audio-record32-dispose-buffers
.PHONY: test-cycle-audio-record32-dispose-buffers

# Reviewed cycle reference: audio-record36-dispose-buffers (assembly evidence only).
$(OUT)/audio_record36_dispose_buffers.bin: native/audio_record36_dispose_buffers.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record36_dispose_buffers.o
	ld -m elf_i386 -Ttext=0x58b360 -e original_audio_record36_dispose_buffers $(OUT)/audio_record36_dispose_buffers.o -o $(OUT)/audio_record36_dispose_buffers.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record36_dispose_buffers.elf $@

test-cycle-audio-record36-dispose-buffers: $(OUT)/reriff-match $(OUT)/audio_record36_dispose_buffers.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record36-dispose-buffers $(OUT)/audio_record36_dispose_buffers.bin $(OUT)/audio-record36-dispose-buffers-comparison.json

test-recovered: test-cycle-audio-record36-dispose-buffers
.PHONY: test-cycle-audio-record36-dispose-buffers

# Reviewed cycle reference: audio-record32-append (assembly evidence only).
$(OUT)/audio_record32_append.bin: native/audio_record32_append.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record32_append.o
	ld -m elf_i386 -Ttext=0x58b510 -e original_audio_record32_append $(OUT)/audio_record32_append.o -o $(OUT)/audio_record32_append.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record32_append.elf $@

test-cycle-audio-record32-append: $(OUT)/reriff-match $(OUT)/audio_record32_append.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record32-append $(OUT)/audio_record32_append.bin $(OUT)/audio-record32-append-comparison.json

test-recovered: test-cycle-audio-record32-append
.PHONY: test-cycle-audio-record32-append

# Reviewed cycle reference: audio-record36-append (assembly evidence only).
$(OUT)/audio_record36_append.bin: native/audio_record36_append.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record36_append.o
	ld -m elf_i386 -Ttext=0x58b5a0 -e original_audio_record36_append $(OUT)/audio_record36_append.o -o $(OUT)/audio_record36_append.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record36_append.elf $@

test-cycle-audio-record36-append: $(OUT)/reriff-match $(OUT)/audio_record36_append.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record36-append $(OUT)/audio_record36_append.bin $(OUT)/audio-record36-append-comparison.json

test-recovered: test-cycle-audio-record36-append
.PHONY: test-cycle-audio-record36-append

# Reviewed cycle reference: audio-record32-remove-last (assembly evidence only).
$(OUT)/audio_record32_remove_last.bin: native/audio_record32_remove_last.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record32_remove_last.o
	ld -m elf_i386 -Ttext=0x58b640 -e original_audio_record32_remove_last $(OUT)/audio_record32_remove_last.o -o $(OUT)/audio_record32_remove_last.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record32_remove_last.elf $@

test-cycle-audio-record32-remove-last: $(OUT)/reriff-match $(OUT)/audio_record32_remove_last.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record32-remove-last $(OUT)/audio_record32_remove_last.bin $(OUT)/audio-record32-remove-last-comparison.json

test-recovered: test-cycle-audio-record32-remove-last
.PHONY: test-cycle-audio-record32-remove-last

# Reviewed cycle reference: audio-record36-remove-last (assembly evidence only).
$(OUT)/audio_record36_remove_last.bin: native/audio_record36_remove_last.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_record36_remove_last.o
	ld -m elf_i386 -Ttext=0x58b6b0 -e original_audio_record36_remove_last $(OUT)/audio_record36_remove_last.o -o $(OUT)/audio_record36_remove_last.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_record36_remove_last.elf $@

test-cycle-audio-record36-remove-last: $(OUT)/reriff-match $(OUT)/audio_record36_remove_last.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-record36-remove-last $(OUT)/audio_record36_remove_last.bin $(OUT)/audio-record36-remove-last-comparison.json

test-recovered: test-cycle-audio-record36-remove-last
.PHONY: test-cycle-audio-record36-remove-last

# Reviewed cycle reference: record12-capacity-growth (assembly evidence only).
$(OUT)/record12_capacity_growth.bin: native/record12_capacity_growth.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record12_capacity_growth.o
	ld -m elf_i386 -Ttext=0x5a95f0 -e original_record12_capacity_growth $(OUT)/record12_capacity_growth.o -o $(OUT)/record12_capacity_growth.elf
	objcopy -O binary --only-section=.text $(OUT)/record12_capacity_growth.elf $@

test-cycle-record12-capacity-growth: $(OUT)/reriff-match $(OUT)/record12_capacity_growth.bin
	$(OUT)/reriff-match native-check "$(GAME)" record12-capacity-growth $(OUT)/record12_capacity_growth.bin $(OUT)/record12-capacity-growth-comparison.json

test-recovered: test-cycle-record12-capacity-growth
.PHONY: test-cycle-record12-capacity-growth

# Reviewed cycle reference: audio-resample-output-count (assembly evidence only).
$(OUT)/audio_resample_output_count.bin: native/audio_resample_output_count.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_resample_output_count.o
	ld -m elf_i386 -Ttext=0x5909e0 -e original_audio_resample_output_count $(OUT)/audio_resample_output_count.o -o $(OUT)/audio_resample_output_count.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_resample_output_count.elf $@

test-cycle-audio-resample-output-count: $(OUT)/reriff-match $(OUT)/audio_resample_output_count.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-resample-output-count $(OUT)/audio_resample_output_count.bin $(OUT)/audio-resample-output-count-comparison.json

test-recovered: test-cycle-audio-resample-output-count
.PHONY: test-cycle-audio-resample-output-count

# Reviewed cycle reference: audio-storage-resize (assembly evidence only).
$(OUT)/audio_storage_resize.bin: native/audio_storage_resize.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/audio_storage_resize.o
	ld -m elf_i386 -Ttext=0x5ae020 -e original_audio_storage_resize $(OUT)/audio_storage_resize.o -o $(OUT)/audio_storage_resize.elf
	objcopy -O binary --only-section=.text $(OUT)/audio_storage_resize.elf $@

test-cycle-audio-storage-resize: $(OUT)/reriff-match $(OUT)/audio_storage_resize.bin
	$(OUT)/reriff-match native-check "$(GAME)" audio-storage-resize $(OUT)/audio_storage_resize.bin $(OUT)/audio-storage-resize-comparison.json

test-recovered: test-cycle-audio-storage-resize
.PHONY: test-cycle-audio-storage-resize

# Reviewed cycle reference: record6-capacity-growth (assembly evidence only).
$(OUT)/record6_capacity_growth.bin: native/record6_capacity_growth.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record6_capacity_growth.o
	ld -m elf_i386 -Ttext=0x5a9680 -e original_record6_capacity_growth $(OUT)/record6_capacity_growth.o -o $(OUT)/record6_capacity_growth.elf
	objcopy -O binary --only-section=.text $(OUT)/record6_capacity_growth.elf $@

test-cycle-record6-capacity-growth: $(OUT)/reriff-match $(OUT)/record6_capacity_growth.bin
	$(OUT)/reriff-match native-check "$(GAME)" record6-capacity-growth $(OUT)/record6_capacity_growth.bin $(OUT)/record6-capacity-growth-comparison.json

test-recovered: test-cycle-record6-capacity-growth
.PHONY: test-cycle-record6-capacity-growth

# Reviewed cycle reference: script-gc-mark-object (assembly evidence only).
$(OUT)/script_gc_mark_object.bin: native/script_gc_mark_object.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_mark_object.o
	ld -m elf_i386 -Ttext=0x4f0ef0 -e original_script_gc_mark_object $(OUT)/script_gc_mark_object.o -o $(OUT)/script_gc_mark_object.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_mark_object.elf $@

test-cycle-script-gc-mark-object: $(OUT)/reriff-match $(OUT)/script_gc_mark_object.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-mark-object $(OUT)/script_gc_mark_object.bin $(OUT)/script-gc-mark-object-comparison.json

test-recovered: test-cycle-script-gc-mark-object
.PHONY: test-cycle-script-gc-mark-object

# Reviewed cycle reference: graphics-frame-interval (assembly evidence only).
$(OUT)/graphics_frame_interval.bin: native/graphics_frame_interval.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/graphics_frame_interval.o
	ld -m elf_i386 -Ttext=0x4a5b00 -e original_graphics_frame_interval $(OUT)/graphics_frame_interval.o -o $(OUT)/graphics_frame_interval.elf
	objcopy -O binary --only-section=.text $(OUT)/graphics_frame_interval.elf $@

test-cycle-graphics-frame-interval: $(OUT)/reriff-match $(OUT)/graphics_frame_interval.bin
	$(OUT)/reriff-match native-check "$(GAME)" graphics-frame-interval $(OUT)/graphics_frame_interval.bin $(OUT)/graphics-frame-interval-comparison.json

test-recovered: test-cycle-graphics-frame-interval
.PHONY: test-cycle-graphics-frame-interval

# Reviewed cycle reference: sse-double-to-integer-dispatch (assembly evidence only).
$(OUT)/sse_double_to_integer_dispatch.bin: native/sse_double_to_integer_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/sse_double_to_integer_dispatch.o
	ld -m elf_i386 -Ttext=0x8f9131 -e original_sse_double_to_integer_dispatch $(OUT)/sse_double_to_integer_dispatch.o -o $(OUT)/sse_double_to_integer_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/sse_double_to_integer_dispatch.elf $@

test-cycle-sse-double-to-integer-dispatch: $(OUT)/reriff-match $(OUT)/sse_double_to_integer_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" sse-double-to-integer-dispatch $(OUT)/sse_double_to_integer_dispatch.bin $(OUT)/sse-double-to-integer-dispatch-comparison.json

test-recovered: test-cycle-sse-double-to-integer-dispatch
.PHONY: test-cycle-sse-double-to-integer-dispatch

# Reviewed cycle reference: script-gc-scan-linked-values (assembly evidence only).
$(OUT)/script_gc_scan_linked_values.bin: native/script_gc_scan_linked_values.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_scan_linked_values.o
	ld -m elf_i386 -Ttext=0x4f2150 -e original_script_gc_scan_linked_values $(OUT)/script_gc_scan_linked_values.o -o $(OUT)/script_gc_scan_linked_values.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_scan_linked_values.elf $@

test-cycle-script-gc-scan-linked-values: $(OUT)/reriff-match $(OUT)/script_gc_scan_linked_values.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-scan-linked-values $(OUT)/script_gc_scan_linked_values.bin $(OUT)/script-gc-scan-linked-values-comparison.json

test-recovered: test-cycle-script-gc-scan-linked-values
.PHONY: test-cycle-script-gc-scan-linked-values

# Reviewed cycle reference: request-resource-prepare (assembly evidence only).
$(OUT)/request_resource_prepare.bin: native/request_resource_prepare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/request_resource_prepare.o
	ld -m elf_i386 -Ttext=0x528d10 -e original_request_resource_prepare $(OUT)/request_resource_prepare.o -o $(OUT)/request_resource_prepare.elf
	objcopy -O binary --only-section=.text $(OUT)/request_resource_prepare.elf $@

test-cycle-request-resource-prepare: $(OUT)/reriff-match $(OUT)/request_resource_prepare.bin
	$(OUT)/reriff-match native-check "$(GAME)" request-resource-prepare $(OUT)/request_resource_prepare.bin $(OUT)/request-resource-prepare-comparison.json

test-recovered: test-cycle-request-resource-prepare
.PHONY: test-cycle-request-resource-prepare

# Reviewed cycle reference: record20-append (assembly evidence only).
$(OUT)/record20_append.bin: native/record20_append.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record20_append.o
	ld -m elf_i386 -Ttext=0x52c610 -e original_record20_append $(OUT)/record20_append.o -o $(OUT)/record20_append.elf
	objcopy -O binary --only-section=.text $(OUT)/record20_append.elf $@

test-cycle-record20-append: $(OUT)/reriff-match $(OUT)/record20_append.bin
	$(OUT)/reriff-match native-check "$(GAME)" record20-append $(OUT)/record20_append.bin $(OUT)/record20-append-comparison.json

test-recovered: test-cycle-record20-append
.PHONY: test-cycle-record20-append

# Reviewed cycle reference: record20-ensure-spare (assembly evidence only).
$(OUT)/record20_ensure_spare.bin: native/record20_ensure_spare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record20_ensure_spare.o
	ld -m elf_i386 -Ttext=0x52c7e0 -e original_record20_ensure_spare $(OUT)/record20_ensure_spare.o -o $(OUT)/record20_ensure_spare.elf
	objcopy -O binary --only-section=.text $(OUT)/record20_ensure_spare.elf $@

test-cycle-record20-ensure-spare: $(OUT)/reriff-match $(OUT)/record20_ensure_spare.bin
	$(OUT)/reriff-match native-check "$(GAME)" record20-ensure-spare $(OUT)/record20_ensure_spare.bin $(OUT)/record20-ensure-spare-comparison.json

test-recovered: test-cycle-record20-ensure-spare
.PHONY: test-cycle-record20-ensure-spare

# Reviewed cycle reference: record20-reallocate (assembly evidence only).
$(OUT)/record20_reallocate.bin: native/record20_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/record20_reallocate.o
	ld -m elf_i386 -Ttext=0x52c750 -e original_record20_reallocate $(OUT)/record20_reallocate.o -o $(OUT)/record20_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/record20_reallocate.elf $@

test-cycle-record20-reallocate: $(OUT)/reriff-match $(OUT)/record20_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" record20-reallocate $(OUT)/record20_reallocate.bin $(OUT)/record20-reallocate-comparison.json

test-recovered: test-cycle-record20-reallocate
.PHONY: test-cycle-record20-reallocate

# Reviewed cycle reference: application-worker-stop (assembly evidence only).
$(OUT)/application_worker_stop.bin: native/application_worker_stop.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/application_worker_stop.o
	ld -m elf_i386 -Ttext=0x491f50 -e original_application_worker_stop $(OUT)/application_worker_stop.o -o $(OUT)/application_worker_stop.elf
	objcopy -O binary --only-section=.text $(OUT)/application_worker_stop.elf $@

test-cycle-application-worker-stop: $(OUT)/reriff-match $(OUT)/application_worker_stop.bin
	$(OUT)/reriff-match native-check "$(GAME)" application-worker-stop $(OUT)/application_worker_stop.bin $(OUT)/application-worker-stop-comparison.json

test-recovered: test-cycle-application-worker-stop
.PHONY: test-cycle-application-worker-stop

# Reviewed cycle reference: worker-stop-cleanup (assembly evidence only).
$(OUT)/worker_stop_cleanup.bin: native/worker_stop_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_stop_cleanup.o
	ld -m elf_i386 -Ttext=0x498e00 -e original_worker_stop_cleanup $(OUT)/worker_stop_cleanup.o -o $(OUT)/worker_stop_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_stop_cleanup.elf $@

test-cycle-worker-stop-cleanup: $(OUT)/reriff-match $(OUT)/worker_stop_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-stop-cleanup $(OUT)/worker_stop_cleanup.bin $(OUT)/worker-stop-cleanup-comparison.json

test-recovered: test-cycle-worker-stop-cleanup
.PHONY: test-cycle-worker-stop-cleanup

# Reviewed cycle reference: worker-prepare-cleanup (assembly evidence only).
$(OUT)/worker_prepare_cleanup.bin: native/worker_prepare_cleanup.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_prepare_cleanup.o
	ld -m elf_i386 -Ttext=0x498f50 -e original_worker_prepare_cleanup $(OUT)/worker_prepare_cleanup.o -o $(OUT)/worker_prepare_cleanup.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_prepare_cleanup.elf $@

test-cycle-worker-prepare-cleanup: $(OUT)/reriff-match $(OUT)/worker_prepare_cleanup.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-prepare-cleanup $(OUT)/worker_prepare_cleanup.bin $(OUT)/worker-prepare-cleanup-comparison.json

test-recovered: test-cycle-worker-prepare-cleanup
.PHONY: test-cycle-worker-prepare-cleanup

# Reviewed cycle reference: worker-flush-slot (assembly evidence only).
$(OUT)/worker_flush_slot.bin: native/worker_flush_slot.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_flush_slot.o
	ld -m elf_i386 -Ttext=0x492730 -e original_worker_flush_slot $(OUT)/worker_flush_slot.o -o $(OUT)/worker_flush_slot.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_flush_slot.elf $@

test-cycle-worker-flush-slot: $(OUT)/reriff-match $(OUT)/worker_flush_slot.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-flush-slot $(OUT)/worker_flush_slot.bin $(OUT)/worker-flush-slot-comparison.json

test-recovered: test-cycle-worker-flush-slot
.PHONY: test-cycle-worker-flush-slot

# Reviewed cycle reference: worker-record-range-clear (assembly evidence only).
$(OUT)/worker_record_range_clear.bin: native/worker_record_range_clear.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_record_range_clear.o
	ld -m elf_i386 -Ttext=0x49a940 -e original_worker_record_range_clear $(OUT)/worker_record_range_clear.o -o $(OUT)/worker_record_range_clear.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_record_range_clear.elf $@

test-cycle-worker-record-range-clear: $(OUT)/reriff-match $(OUT)/worker_record_range_clear.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-record-range-clear $(OUT)/worker_record_range_clear.bin $(OUT)/worker-record-range-clear-comparison.json

test-recovered: test-cycle-worker-record-range-clear
.PHONY: test-cycle-worker-record-range-clear

# Reviewed cycle reference: worker-collect-slot (assembly evidence only).
$(OUT)/worker_collect_slot.bin: native/worker_collect_slot.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_collect_slot.o
	ld -m elf_i386 -Ttext=0x492610 -e original_worker_collect_slot $(OUT)/worker_collect_slot.o -o $(OUT)/worker_collect_slot.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_collect_slot.elf $@

test-cycle-worker-collect-slot: $(OUT)/reriff-match $(OUT)/worker_collect_slot.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-collect-slot $(OUT)/worker_collect_slot.bin $(OUT)/worker-collect-slot-comparison.json

test-recovered: test-cycle-worker-collect-slot
.PHONY: test-cycle-worker-collect-slot

# Reviewed cycle reference: worker-slot-reset (assembly evidence only).
$(OUT)/worker_slot_reset.bin: native/worker_slot_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_slot_reset.o
	ld -m elf_i386 -Ttext=0x490d30 -e original_worker_slot_reset $(OUT)/worker_slot_reset.o -o $(OUT)/worker_slot_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_slot_reset.elf $@

test-cycle-worker-slot-reset: $(OUT)/reriff-match $(OUT)/worker_slot_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-slot-reset $(OUT)/worker_slot_reset.bin $(OUT)/worker-slot-reset-comparison.json

test-recovered: test-cycle-worker-slot-reset
.PHONY: test-cycle-worker-slot-reset

# Reviewed cycle reference: worker-record-reset (assembly evidence only).
$(OUT)/worker_record_reset.bin: native/worker_record_reset.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_record_reset.o
	ld -m elf_i386 -Ttext=0x4909e0 -e original_worker_record_reset $(OUT)/worker_record_reset.o -o $(OUT)/worker_record_reset.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_record_reset.elf $@

test-cycle-worker-record-reset: $(OUT)/reriff-match $(OUT)/worker_record_reset.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-record-reset $(OUT)/worker_record_reset.bin $(OUT)/worker-record-reset-comparison.json

test-recovered: test-cycle-worker-record-reset
.PHONY: test-cycle-worker-record-reset

# Reviewed cycle reference: worker-reference-range-clear (assembly evidence only).
$(OUT)/worker_reference_range_clear.bin: native/worker_reference_range_clear.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_reference_range_clear.o
	ld -m elf_i386 -Ttext=0x499710 -e original_worker_reference_range_clear $(OUT)/worker_reference_range_clear.o -o $(OUT)/worker_reference_range_clear.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_reference_range_clear.elf $@

test-cycle-worker-reference-range-clear: $(OUT)/reriff-match $(OUT)/worker_reference_range_clear.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-reference-range-clear $(OUT)/worker_reference_range_clear.bin $(OUT)/worker-reference-range-clear-comparison.json

test-recovered: test-cycle-worker-reference-range-clear
.PHONY: test-cycle-worker-reference-range-clear

# Reviewed cycle reference: script-gc-step (assembly evidence only).
$(OUT)/script_gc_step.bin: native/script_gc_step.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_step.o
	ld -m elf_i386 -Ttext=0x4f2330 -e original_script_gc_step $(OUT)/script_gc_step.o -o $(OUT)/script_gc_step.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_step.elf $@

test-cycle-script-gc-step: $(OUT)/reriff-match $(OUT)/script_gc_step.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-step $(OUT)/script_gc_step.bin $(OUT)/script-gc-step-comparison.json

test-recovered: test-cycle-script-gc-step
.PHONY: test-cycle-script-gc-step

# Reviewed cycle reference: script-prepare-callable (assembly evidence only).
$(OUT)/script_prepare_callable.bin: native/script_prepare_callable.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_prepare_callable.o
	ld -m elf_i386 -Ttext=0x4f5380 -e original_script_prepare_callable $(OUT)/script_prepare_callable.o -o $(OUT)/script_prepare_callable.elf
	objcopy -O binary --only-section=.text $(OUT)/script_prepare_callable.elf $@

test-cycle-script-prepare-callable: $(OUT)/reriff-match $(OUT)/script_prepare_callable.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-prepare-callable $(OUT)/script_prepare_callable.bin $(OUT)/script-prepare-callable-comparison.json

test-recovered: test-cycle-script-prepare-callable
.PHONY: test-cycle-script-prepare-callable

# Reviewed cycle reference: script-pre-call (assembly evidence only).
$(OUT)/script_pre_call.bin: native/script_pre_call.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_pre_call.o
	ld -m elf_i386 -Ttext=0x4f54a0 -e original_script_pre_call $(OUT)/script_pre_call.o -o $(OUT)/script_pre_call.elf
	objcopy -O binary --only-section=.text $(OUT)/script_pre_call.elf $@

test-cycle-script-pre-call: $(OUT)/reriff-match $(OUT)/script_pre_call.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-pre-call $(OUT)/script_pre_call.bin $(OUT)/script-pre-call-comparison.json

test-recovered: test-cycle-script-pre-call
.PHONY: test-cycle-script-pre-call

# Reviewed cycle reference: script-hook-dispatch (assembly evidence only).
$(OUT)/script_hook_dispatch.bin: native/script_hook_dispatch.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_hook_dispatch.o
	ld -m elf_i386 -Ttext=0x4f5020 -e original_script_hook_dispatch $(OUT)/script_hook_dispatch.o -o $(OUT)/script_hook_dispatch.elf
	objcopy -O binary --only-section=.text $(OUT)/script_hook_dispatch.elf $@

test-cycle-script-hook-dispatch: $(OUT)/reriff-match $(OUT)/script_hook_dispatch.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-hook-dispatch $(OUT)/script_hook_dispatch.bin $(OUT)/script-hook-dispatch-comparison.json

test-recovered: test-cycle-script-hook-dispatch
.PHONY: test-cycle-script-hook-dispatch

# Reviewed cycle reference: script-return-hook (assembly evidence only).
$(OUT)/script_return_hook.bin: native/script_return_hook.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_return_hook.o
	ld -m elf_i386 -Ttext=0x4f5680 -e original_script_return_hook $(OUT)/script_return_hook.o -o $(OUT)/script_return_hook.elf
	objcopy -O binary --only-section=.text $(OUT)/script_return_hook.elf $@

test-cycle-script-return-hook: $(OUT)/reriff-match $(OUT)/script_return_hook.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-return-hook $(OUT)/script_return_hook.bin $(OUT)/script-return-hook-comparison.json

test-recovered: test-cycle-script-return-hook
.PHONY: test-cycle-script-return-hook

# Reviewed cycle reference: script-gc-shrink-buffers (assembly evidence only).
$(OUT)/script_gc_shrink_buffers.bin: native/script_gc_shrink_buffers.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_shrink_buffers.o
	ld -m elf_i386 -Ttext=0x4f1b50 -e original_script_gc_shrink_buffers $(OUT)/script_gc_shrink_buffers.o -o $(OUT)/script_gc_shrink_buffers.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_shrink_buffers.elf $@

test-cycle-script-gc-shrink-buffers: $(OUT)/reriff-match $(OUT)/script_gc_shrink_buffers.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-shrink-buffers $(OUT)/script_gc_shrink_buffers.bin $(OUT)/script-gc-shrink-buffers-comparison.json

test-recovered: test-cycle-script-gc-shrink-buffers
.PHONY: test-cycle-script-gc-shrink-buffers

# Reviewed cycle reference: script-gc-begin-mark (assembly evidence only).
$(OUT)/script_gc_begin_mark.bin: native/script_gc_begin_mark.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_begin_mark.o
	ld -m elf_i386 -Ttext=0x4f20e0 -e original_script_gc_begin_mark $(OUT)/script_gc_begin_mark.o -o $(OUT)/script_gc_begin_mark.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_begin_mark.elf $@

test-cycle-script-gc-begin-mark: $(OUT)/reriff-match $(OUT)/script_gc_begin_mark.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-begin-mark $(OUT)/script_gc_begin_mark.bin $(OUT)/script-gc-begin-mark-comparison.json

test-recovered: test-cycle-script-gc-begin-mark
.PHONY: test-cycle-script-gc-begin-mark

# Reviewed cycle reference: script-gc-scan-roots (assembly evidence only).
$(OUT)/script_gc_scan_roots.bin: native/script_gc_scan_roots.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_scan_roots.o
	ld -m elf_i386 -Ttext=0x4f1fe0 -e original_script_gc_scan_roots $(OUT)/script_gc_scan_roots.o -o $(OUT)/script_gc_scan_roots.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_scan_roots.elf $@

test-cycle-script-gc-scan-roots: $(OUT)/reriff-match $(OUT)/script_gc_scan_roots.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-scan-roots $(OUT)/script_gc_scan_roots.bin $(OUT)/script-gc-scan-roots-comparison.json

test-recovered: test-cycle-script-gc-scan-roots
.PHONY: test-cycle-script-gc-scan-roots

# Reviewed cycle reference: worker-pointer-ensure-spare (assembly evidence only).
$(OUT)/worker_pointer_ensure_spare.bin: native/worker_pointer_ensure_spare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_pointer_ensure_spare.o
	ld -m elf_i386 -Ttext=0x429ce0 -e original_worker_pointer_ensure_spare $(OUT)/worker_pointer_ensure_spare.o -o $(OUT)/worker_pointer_ensure_spare.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_pointer_ensure_spare.elf $@

test-cycle-worker-pointer-ensure-spare: $(OUT)/reriff-match $(OUT)/worker_pointer_ensure_spare.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-pointer-ensure-spare $(OUT)/worker_pointer_ensure_spare.bin $(OUT)/worker-pointer-ensure-spare-comparison.json

test-recovered: test-cycle-worker-pointer-ensure-spare
.PHONY: test-cycle-worker-pointer-ensure-spare

# Reviewed cycle reference: script-type-error (assembly evidence only).
$(OUT)/script_type_error.bin: native/script_type_error.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_type_error.o
	ld -m elf_i386 -Ttext=0x4868c0 -e original_script_type_error $(OUT)/script_type_error.o -o $(OUT)/script_type_error.elf
	objcopy -O binary --only-section=.text $(OUT)/script_type_error.elf $@

test-cycle-script-type-error: $(OUT)/reriff-match $(OUT)/script_type_error.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-type-error $(OUT)/script_type_error.bin $(OUT)/script-type-error-comparison.json

test-recovered: test-cycle-script-type-error
.PHONY: test-cycle-script-type-error

# Reviewed cycle reference: script-debug-name (assembly evidence only).
$(OUT)/script_debug_name.bin: native/script_debug_name.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_debug_name.o
	ld -m elf_i386 -Ttext=0x486680 -e original_script_debug_name $(OUT)/script_debug_name.o -o $(OUT)/script_debug_name.elf
	objcopy -O binary --only-section=.text $(OUT)/script_debug_name.elf $@

test-cycle-script-debug-name: $(OUT)/reriff-match $(OUT)/script_debug_name.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-debug-name $(OUT)/script_debug_name.bin $(OUT)/script-debug-name-comparison.json

test-recovered: test-cycle-script-debug-name
.PHONY: test-cycle-script-debug-name

# Reviewed cycle reference: script-operand-validate (assembly evidence only).
$(OUT)/script_operand_validate.bin: native/script_operand_validate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_operand_validate.o
	ld -m elf_i386 -Ttext=0x486180 -e original_script_operand_validate $(OUT)/script_operand_validate.o -o $(OUT)/script_operand_validate.elf
	objcopy -O binary --only-section=.text $(OUT)/script_operand_validate.elf $@

test-cycle-script-operand-validate: $(OUT)/reriff-match $(OUT)/script_operand_validate.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-operand-validate $(OUT)/script_operand_validate.bin $(OUT)/script-operand-validate-comparison.json

test-recovered: test-cycle-script-operand-validate
.PHONY: test-cycle-script-operand-validate

# Reviewed cycle reference: script-gc-propagate-one (assembly evidence only).
$(OUT)/script_gc_propagate_one.bin: native/script_gc_propagate_one.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_propagate_one.o
	ld -m elf_i386 -Ttext=0x4f16f0 -e original_script_gc_propagate_one $(OUT)/script_gc_propagate_one.o -o $(OUT)/script_gc_propagate_one.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_propagate_one.elf $@

test-cycle-script-gc-propagate-one: $(OUT)/reriff-match $(OUT)/script_gc_propagate_one.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-propagate-one $(OUT)/script_gc_propagate_one.bin $(OUT)/script-gc-propagate-one-comparison.json

test-recovered: test-cycle-script-gc-propagate-one
.PHONY: test-cycle-script-gc-propagate-one

# Reviewed cycle reference: script-gc-visit-prototype (assembly evidence only).
$(OUT)/script_gc_visit_prototype.bin: native/script_gc_visit_prototype.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_visit_prototype.o
	ld -m elf_i386 -Ttext=0x4f1320 -e original_script_gc_visit_prototype $(OUT)/script_gc_visit_prototype.o -o $(OUT)/script_gc_visit_prototype.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_visit_prototype.elf $@

test-cycle-script-gc-visit-prototype: $(OUT)/reriff-match $(OUT)/script_gc_visit_prototype.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-visit-prototype $(OUT)/script_gc_visit_prototype.bin $(OUT)/script-gc-visit-prototype-comparison.json

test-recovered: test-cycle-script-gc-visit-prototype
.PHONY: test-cycle-script-gc-visit-prototype

# Reviewed cycle reference: script-instruction-open-result (assembly evidence only).
$(OUT)/script_instruction_open_result.bin: native/script_instruction_open_result.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_instruction_open_result.o
	ld -m elf_i386 -Ttext=0x486150 -e original_script_instruction_open_result $(OUT)/script_instruction_open_result.o -o $(OUT)/script_instruction_open_result.elf
	objcopy -O binary --only-section=.text $(OUT)/script_instruction_open_result.elf $@

test-cycle-script-instruction-open-result: $(OUT)/reriff-match $(OUT)/script_instruction_open_result.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-instruction-open-result $(OUT)/script_instruction_open_result.bin $(OUT)/script-instruction-open-result-comparison.json

test-recovered: test-cycle-script-instruction-open-result
.PHONY: test-cycle-script-instruction-open-result

# Reviewed cycle reference: worker-resource-state-update (assembly evidence only).
$(OUT)/worker_resource_state_update.bin: native/worker_resource_state_update.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_resource_state_update.o
	ld -m elf_i386 -Ttext=0x59efd0 -e original_worker_resource_state_update $(OUT)/worker_resource_state_update.o -o $(OUT)/worker_resource_state_update.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_resource_state_update.elf $@

test-cycle-worker-resource-state-update: $(OUT)/reriff-match $(OUT)/worker_resource_state_update.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-resource-state-update $(OUT)/worker_resource_state_update.bin $(OUT)/worker-resource-state-update-comparison.json

test-recovered: test-cycle-worker-resource-state-update
.PHONY: test-cycle-worker-resource-state-update

# Reviewed cycle reference: worker-byte-vector-append (assembly evidence only).
$(OUT)/worker_byte_vector_append.bin: native/worker_byte_vector_append.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_byte_vector_append.o
	ld -m elf_i386 -Ttext=0x5c20e0 -e original_worker_byte_vector_append $(OUT)/worker_byte_vector_append.o -o $(OUT)/worker_byte_vector_append.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_byte_vector_append.elf $@

test-cycle-worker-byte-vector-append: $(OUT)/reriff-match $(OUT)/worker_byte_vector_append.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-byte-vector-append $(OUT)/worker_byte_vector_append.bin $(OUT)/worker-byte-vector-append-comparison.json

test-recovered: test-cycle-worker-byte-vector-append
.PHONY: test-cycle-worker-byte-vector-append

# Reviewed cycle reference: worker-byte-vector-ensure-spare (assembly evidence only).
$(OUT)/worker_byte_vector_ensure_spare.bin: native/worker_byte_vector_ensure_spare.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_byte_vector_ensure_spare.o
	ld -m elf_i386 -Ttext=0x519d50 -e original_worker_byte_vector_ensure_spare $(OUT)/worker_byte_vector_ensure_spare.o -o $(OUT)/worker_byte_vector_ensure_spare.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_byte_vector_ensure_spare.elf $@

test-cycle-worker-byte-vector-ensure-spare: $(OUT)/reriff-match $(OUT)/worker_byte_vector_ensure_spare.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-byte-vector-ensure-spare $(OUT)/worker_byte_vector_ensure_spare.bin $(OUT)/worker-byte-vector-ensure-spare-comparison.json

test-recovered: test-cycle-worker-byte-vector-ensure-spare
.PHONY: test-cycle-worker-byte-vector-ensure-spare

# Reviewed cycle reference: worker-byte-vector-reallocate (assembly evidence only).
$(OUT)/worker_byte_vector_reallocate.bin: native/worker_byte_vector_reallocate.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/worker_byte_vector_reallocate.o
	ld -m elf_i386 -Ttext=0x51a450 -e original_worker_byte_vector_reallocate $(OUT)/worker_byte_vector_reallocate.o -o $(OUT)/worker_byte_vector_reallocate.elf
	objcopy -O binary --only-section=.text $(OUT)/worker_byte_vector_reallocate.elf $@

test-cycle-worker-byte-vector-reallocate: $(OUT)/reriff-match $(OUT)/worker_byte_vector_reallocate.bin
	$(OUT)/reriff-match native-check "$(GAME)" worker-byte-vector-reallocate $(OUT)/worker_byte_vector_reallocate.bin $(OUT)/worker-byte-vector-reallocate-comparison.json

test-recovered: test-cycle-worker-byte-vector-reallocate
.PHONY: test-cycle-worker-byte-vector-reallocate

# Reviewed cycle reference: script-gc-finish-mark (assembly evidence only).
$(OUT)/script_gc_finish_mark.bin: native/script_gc_finish_mark.S
	mkdir -p $(OUT)
	as --32 $< -o $(OUT)/script_gc_finish_mark.o
	ld -m elf_i386 -Ttext=0x4f2190 -e original_script_gc_finish_mark $(OUT)/script_gc_finish_mark.o -o $(OUT)/script_gc_finish_mark.elf
	objcopy -O binary --only-section=.text $(OUT)/script_gc_finish_mark.elf $@

test-cycle-script-gc-finish-mark: $(OUT)/reriff-match $(OUT)/script_gc_finish_mark.bin
	$(OUT)/reriff-match native-check "$(GAME)" script-gc-finish-mark $(OUT)/script_gc_finish_mark.bin $(OUT)/script-gc-finish-mark-comparison.json

test-recovered: test-cycle-script-gc-finish-mark
.PHONY: test-cycle-script-gc-finish-mark
