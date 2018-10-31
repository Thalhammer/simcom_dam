PROJS=$(shell find . -regextype sed -regex ".*/[0-9][0-9]-[^/]*$$" -type d)

.PHONY: all clean dist-clean common $(PROJS) clean-common $(addprefix clean-, $(PROJS))

all: $(PROJS)
clean: $(addprefix clean-, $(PROJS))
dist-clean: clean clean-common

$(PROJS): %: common
	@+make -C $@ --no-print-directory

$(addprefix clean-, $(PROJS)): %:
	@+make -C $(@:clean-%=%) --no-print-directory clean

common:
	@+make -C $@ --no-print-directory

clean-common:
	@+make -C common --no-print-directory clean
