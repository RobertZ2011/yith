ARCH ?= x86

# See this link for why the below is required
# https://github.com/japaric/xargo/issues/186#issuecomment-354008950
RUST_TARGET_PATH = $(shell pwd)
export RUST_TARGET_PATH

TARGET := $(ARCH)-yith

all: $(TARGET).json
	make -C arch "ARCH=$(ARCH)"
	xargo build --target=$(TARGET)
	mv target/$(TARGET)/debug/libkernel.a ../build/libkernel.a

$(TARGET).json:
	ln -s arch/$(ARCH)/$(TARGET).json $(TARGET).json
