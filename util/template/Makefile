CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra -DLOCAL -I${CP_UTILS}/cpp

TARGET=exec
SRC_CODE=src.cc

all: run

$(TARGET): $(SRC_CODE)
	@if [ -f "$(SRC_CODE)" ]; then \
		$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_CODE); \
	else \
		echo "Source file $(SRC_CODE) not found."; \
	fi

run: $(TARGET)
	@if ls *.in 1> /dev/null 2>&1; then \
		for infile in *.in; do \
			base=$$(basename $$infile .in); \
			echo "\033[1;30m--- CASE $$base ---\033[0m"; \
			./$(TARGET) < $$infile; \
		done; \
	else \
		echo "No input files (*.in) found. Nothing to run against."; \
	fi

test: $(TARGET)
	@if ls *.in 1> /dev/null 2>&1; then \
		for infile in *.in; do \
			base=$$(basename $$infile .in); \
			outfile=$$base.out; \
			if [ ! -f $$outfile ]; then \
				echo "Error: Output file '$$outfile' not found for input '$$infile'"; \
				continue; \
			fi; \
			./$(TARGET) < $$infile > output.out 2> /dev/null; \
			if diff -q output.out $$outfile > /dev/null; then \
				echo "TEST: $$base \033[0;32mOK\033[0m"; \
			else \
				echo "TEST: $$base \033[0;31mFAILED\033[0m"; \
				diff -u $$outfile output.out | ydiff -s; \
			fi; \
		done; \
		rm -f output.out; \
	else \
		echo "No input files (*.in) found. No tests to run."; \
	fi

clean:
	@rm -f $(TARGET)
