CSRCS += ls_fs_images.c
CSRCS += ls_ui_common.c

DEPPATH += --dep-path $(LVGL_DIR)/component
VPATH += :$(LVGL_DIR)/component

CFLAGS += "-I$(LVGL_DIR)/component"
