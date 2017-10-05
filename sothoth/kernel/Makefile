ARCH ?= x86

TARGET := $(ARCH)-yith

all: $(TARGET).json
	make -C arch "ARCH=$(ARCH)"
	xargo build --target=$(TARGET)
	mv target/$(TARGET)/debug/libkernel.a ../build

$(TARGET).json:
	ln -s arch/$(ARCH)/$(TARGET).json $(TARGET).json
