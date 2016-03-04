
TARGETS := ar7 ar86 wp85 raspi localhost

.PHONY: all $(TARGETS)
all: $(TARGETS)

$(TARGETS):
	mkapp -v -t $@ \
	    -i . \
		relayControl.adef

clean:
	rm -rf _build_* *.update