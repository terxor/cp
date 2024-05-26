# Compiler and flags for C++ source
CXX = g++
CXXFLAGS = -std=c++11 -O2

# Default target
all: run

# Compile C++ source
compile: src.cpp
	@if [ -f "src.cpp" ]; then \
		$(CXX) $(CXXFLAGS) -o program src.cpp; \
	else \
		echo "No C++ source file found."; \
	fi

# Run the compiled program
run: compile
	@echo "Running the compiled program"
	@if [ -f "program" ]; then \
		./program; \
	else \
		echo "No program to run."; \
	fi

# Test the compiled program
test: compile
	@if [ ! -f '*.in' ] || [ ! -f '*.out' ]; then \
		echo "No tests to run."; \
		exit 0; \
	fi
	@echo "Running tests for C++ source"
	@for infile in *.in; do \
		base=$$(basename $$infile .in); \
		outfile=$$base.out; \
		if [ ! -f $$outfile ]; then \
			echo "Error: Output file '$$outfile' not found for input '$$infile'"; \
			continue; \
		fi; \
		echo "Running test $$base"; \
		./program < $$infile > output.out; \
		if diff -q output.out $$outfile > /dev/null; then \
			echo "Test $$base passed"; \
		else \
			echo "Test $$base failed"; \
			diff output.out $$outfile; \
		fi; \
	done; \
	rm -f output.out

# Clean up generated files
clean:
	@rm -f program
