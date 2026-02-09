CC = gcc
CFLAGS = -std=c99 -ggdb -Wall -fopenmp
CLIBS = -lSDL3
OBJDIR = obj
SRCDIR = src
EXE = qardia

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
HEADERS = $(wildcard $(SRCDIR)/*.h)

.PHONY: all $(EXE) clean

all: $(OBJDIR) $(EXE)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXE)
