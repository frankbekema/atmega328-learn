#
# Script for building all the tools
#
# Made by Frank Bekema
#

DIRECTORY=$(shell pwd)

MODULES=avrdude avr-gnu-toolchain

AVRDUDE_URL=http://download.savannah.gnu.org/releases/avrdude/avrdude-6.3.tar.gz
AVRDUDE_OUTDIR=avrdude

AVR_GNU_ARCHIVE=$(DIRECTORY)/sources/avr8-gnu-toolchain-3.6.2.1759-linux.any.x86_64.tar.gz

TMPDIR=tmp

define check_exists
	if [ -n "which $(1) | grep \"^which: no.* in (.*)\"" ]:
		echo 
		exit
	fi
endef

.PHONY: all avrdude avr-gnu-toolchain init hard_clean clean

all: hard_clean avrdude avr-gnu-toolchain

avr-gnu-toolchain:	
	@echo "Started build process for avr-gnu-toolchain"
	pushd ${TMPDIR}; \
        mkdir -p avr-gnu-toolchain; \
        tar -xf ${AVR_GNU_ARCHIVE} -C avr-gnu-toolchain; \
	pushd avr-gnu-toolchain; \
	pushd $$(find -maxdepth 1 -mindepth 1 -type d -print -quit); \
	mkdir -p ${DIRECTORY}/avr-gnu-toolchain; \
	mv -f * ${DIRECTORY}/avr-gnu-toolchain; \
	popd; \
	popd; \
	rm -Rf avr-gnu-toolchain; \
	popd;
	@echo "Done building avr-gnu-toolchain!"

avrdude:
	@echo "Starting build process for avrdude"
	mkdir -p $(TMPDIR)/avrdude; \
	pushd $(TMPDIR)/avrdude; \
	wget -O avrdude.tar.gz "$(AVRDUDE_URL)"; \
	tar -xf avrdude.tar.gz -C .; \
	AVR_DIR=$$(find . -maxdepth 1 -mindepth 1 -name '*avrdude*' -type d | cut -c3-); \
	pushd $$AVR_DIR; \
	./configure; \
	make; \
	popd; \
	popd; \
	mkdir -p $(AVRDUDE_OUTDIR)/bin; \
	cp $(TMPDIR)/avrdude/$$AVR_DIR/avrdude $(AVRDUDE_OUTDIR)/bin/avrdude; \
	rm -Rf tmp/avrdude
	@echo "Done building avrdude!"

init:
	@echo "Initializing all modules"
	for module in $(MODULES); do \
		mkdir $$module/*; \
	done
	@echo "Done intializing directories"


hard_clean: clean
	@echo "Hardcleaning all modules"
	for module in $(MODULES); do \
		rm -Rf $$module; \
	done;
	@echo "Done hardcleaning all modules"


clean:
	@echo "Soft cleaning"
	rm -Rf tmp
	@echo "Soft cleaning done"
