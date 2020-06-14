#
# Script for building all the tools
#
# Made by Frank Bekema
#

MODULES=avrdude avr-gcc

AVRDUDE_URL=http://download.savannah.gnu.org/releases/avrdude/avrdude-6.3.tar.gz
AVRDUDE_OUTDIR=avrdude

TMPDIR=tmp

define check_exists
	if [ -n "which $(1) | grep \"^which: no.* in (.*)\"" ]:
		echo 
		exit
	fi
endef

.PHONY: all avrdude init hard_clean clean

all: hard_clean avrdude


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
		rm -Rf $$module/*; \
	done;
	@echo "Done hardcleaning all modules"


clean:
	@echo "Soft cleaning"
	rm -Rf tmp
	@echo "Soft cleaning done"
