CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

# Directories
OBJDIR = build

# Targets
TARGETS = $(OBJDIR)/test_matrix $(OBJDIR)/test_gnode $(OBJDIR)/test_queue

# Source files per target
MATRIX_SRCS = tests/test_matrix.c dependencies/adts/helpers.c dependencies/adts/matrix.c
NODE_SRCS   = tests/test_gnode.c dependencies/adts/helpers.c dependencies/adts/gnode.c
QUEUE_SRCS  = tests/test_queue.c dependencies/adts/helpers.c dependencies/adts/queue.c dependencies/adts/node.c

# Object files per target
MATRIX_OBJS = $(MATRIX_SRCS:%.c=$(OBJDIR)/%.o)
NODE_OBJS   = $(NODE_SRCS:%.c=$(OBJDIR)/%.o)
QUEUE_OBJS  = $(QUEUE_SRCS:%.c=$(OBJDIR)/%.o)

# Default rule
all: $(TARGETS)

# Linking rules
$(OBJDIR)/test_matrix: $(MATRIX_OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/test_gnode: $(NODE_OBJS) | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/test_queue: $(QUEUE_OBJS) | $(OBJDIR)
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
