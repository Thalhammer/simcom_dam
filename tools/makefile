DEP_DIR = .deps

FLAGS = -Wall -I deps/libopenpst/include -I deps/libopenpst/lib/serial/include
CXXFLAGS = -std=c++14
TOOLS = upload efs hexcheck hex2bin log

.PHONY: all dependencies clean dist-clean

all: $(TOOLS)

dependencies: deps/.done

clean:
	@rm -rf $(TOOLS)

dist-clean: clean
	@rm -rf deps

$(TOOLS): % : %.cpp | dependencies
	@mkdir -p `dirname $(DEP_DIR)/$@.d`
	@echo Building $<
	@$(CXX) $(FLAGS) $(CXXFLAGS) $< -Ldeps/libopenpst/build/release -lopenpst -o $@

dependencies/.done:
	@mkdir deps
	@(cd deps && git clone https://github.com/openpst/libopenpst.git)
	+make -C deps/libopenpst
	@touch deps/.done