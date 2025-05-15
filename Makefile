CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Directories
OBJDIR = build

# Source files
SRCS = tests/test_matrix.c dependencies/adts/helpers.c dependencies/adts/matrix.c

# Generate object file names in build/ with same basename
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

TARGET = $(OBJDIR)/main

# Default rule
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to build/%.o
$(OBJDIR)/%.c.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Fallback pattern rule for general .c to build/*.o
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/ directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
