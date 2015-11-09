CC = g++
CFLAGS = -c -Wall -std=c++11

TARGET = test
ODIR = ./obj
_OBJS = main.o
OBJS = $(patsubst %, $(ODIR)/%, $(_OBJS))

all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) -o $@ $^


$(ODIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<


.PHONY: clean
clean:
	rm -rf *.o $(ODIR)/*.o $(TARGET)
