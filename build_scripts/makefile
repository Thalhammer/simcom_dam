PROJS=$(shell find . -regextype sed -regex ".*/[0-9][0-9]-[^/]*$$" -type d)

.PHONY: all clean dist-clean api $(PROJS) clean-api $(addprefix clean-, $(PROJS))

TYPE ?= gcc

all: $(PROJS)
clean: $(addprefix clean-, $(PROJS))
dist-clean: clean clean-api

$(PROJS): %: api
	@+make TYPE=$(TYPE) -C $@ --no-print-directory

$(addprefix clean-, $(PROJS)): %:
	@+make TYPE=$(TYPE) -C $(@:clean-%=%) --no-print-directory clean

api:
	@+make TYPE=$(TYPE) -C ../api --no-print-directory

clean-api:
	@+make TYPE=$(TYPE) -C ../api --no-print-directory clean
