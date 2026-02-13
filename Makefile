# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2

# Target executable
TARGET_DIR = bin
TARGET = $(TARGET_DIR)/cpu_monitor

# Source files
SOURCES = main.cpp cputil.cpp
# This transforms 'main.cpp' into 'bin/main.o'
OBJECTS = $(addprefix $(TARGET_DIR)/, $(SOURCES:.cpp=.o))

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile .cpp to .o and place them in bin/
# The 'mkdir' ensures the directory exists before compiling
$(TARGET_DIR)/%.o: %.cpp
	@mkdir -p $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(TARGET_DIR)

# Phony targets
.PHONY: all clean run
