
TARGETS := wp85

export MANGOH_ROOT ?= $(PWD)/../..

.PHONY: all $(TARGETS)
all: $(TARGETS)

$(TARGETS):
	mkapp -v -t $@ \
	    -i . \
	    -i ../../apps/DataRouter \
		relayControl.adef

clean:
	rm -rf _build_* *.update
