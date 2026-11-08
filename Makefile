include prelude.mk

this_dir  := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
src_dir   := $(this_dir)
build_dir := $(this_dir)build

.PHONY: all
all: build

.PHONY: clean
clean:
	rm -rf -- '$(call escape,$(build_dir))'

.PHONY: build
build: build/debug

build/%: DO
	@[ ! -f '$(call escape,$(build_dir))/$*/build.ninja' ] && \
		meson setup \
			'$(call escape,--buildtype=$*)' \
			'$(call escape,$(build_dir))/$*' \
			'$(call escape,$(src_dir))' || true
	ninja -C '$(call escape,$(build_dir))/$*'
