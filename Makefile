CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Directories
OBJDIR = build

# Targets
TARGETS = $(OBJDIR)/test_matrix $(OBJDIR)/test_node

# Source files per target
MATRIX_SRCS = tests/test_matrix.c dependencies/adts/helpers.c dependencies/adts/matrix.c
NODE_SRCS   = tests/test_node.c dependencies/adts/helpers.c 

# Object files per target
MATRIX_OBJS = $(MATRIX_SRCS:%.c=$(OBJDIR)/%.o)
NODE_OBJS   = $(NODE_SRCS:%.c=$(OBJDIR)/%.o)

# Default rule
all: $(TARGETS)

# Linking rules
$(OBJDIR)/test_matrix: $(MATRIX_OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/test_node: $(NODE_OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile rule
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/ directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR)

.PHONY: all clean
