CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -fPIC -Iinclude
LDFLAGS := -shared
BUILD   := build
REPORTS := reports

LIB_SRC := src/stack_lib.c
LIB_OBJ := $(BUILD)/stack_lib.o
LIB_SO  := $(BUILD)/libstack.so

APP_SRC := demo/main.c
APP_BIN := $(BUILD)/stack_demo

TEST_SRC:= tests/test_stack.c
TEST_BIN:= $(BUILD)/test_stack

.PHONY: all clean shared app run test py-test syntax analyze sanitize docs-html docs-pdf

all: shared app

$(BUILD) $(REPORTS):
	mkdir -p $@

shared: $(LIB_SO)
$(LIB_SO): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(LIB_OBJ): $(LIB_SRC) include/stack_lib.h | $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

app: $(APP_BIN)
$(APP_BIN): $(APP_SRC) $(LIB_SO) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< -L$(BUILD) -lstack -Wl,-rpath,$(CURDIR)/$(BUILD)

run: app
	./$(APP_BIN)

test: $(TEST_BIN)
	LD_LIBRARY_PATH=$(BUILD) ./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(LIB_SO) | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< -L$(BUILD) -lstack -Wl,-rpath,$(CURDIR)/$(BUILD)

py-test: shared
	cd tests && python3 test_stack.py

syntax: | $(BUILD)
	$(CC) -fsyntax-only $(CFLAGS) $(LIB_SRC) $(TEST_SRC) $(APP_SRC)
	@echo "[OK] Syntax check passed."

analyze: | $(BUILD) $(REPORTS)
	$(CC) -fanalyzer $(CFLAGS) -o /dev/null $(LIB_SRC) 2> $(REPORTS)/gcc_analyzer.log || true
	@echo "[INFO] GCC Analyzer log -> $(REPORTS)/gcc_analyzer.log"
	-cppcheck --enable=all --inconclusive --quiet src include 2> $(REPORTS)/cppcheck.log || true
	@echo "[INFO] Cppcheck log -> $(REPORTS)/cppcheck.log"

sanitize: $(TEST_BIN) | $(BUILD)
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o $(BUILD)/test_san $(TEST_SRC) -L$(BUILD) -lstack -Wl,-rpath,$(CURDIR)/$(BUILD)
	LD_LIBRARY_PATH=$(BUILD) ./$(BUILD)/test_san
	@echo "[OK] Sanitizers passed."

docs-html:
	doxygen Doxyfile
	@echo "[OK] HTML docs -> docs/html/index.html"

docs-pdf: docs-html
	@cd docs/latex && make pdf >/dev/null 2>&1 || echo "[WARN] PDF requires pdflatex"
	@echo "[INFO] PDF docs -> docs/latex/refman.pdf"

clean:
	rm -rf $(BUILD) $(REPORTS) docs
	find . -type f -name "*.pyc" -delete
	find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null || true