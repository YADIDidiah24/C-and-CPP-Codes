CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 
OBJFILES = computingGPA.o computingGPAFunctions.o
TARGET = computingGPA

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(LDFLAGS) $(OBJFILES) -o $(TARGET)

computingGPA.o: computingGPA.c ComputeGPA.h
	$(CC) $(CFLAGS) -c computingGPA.c

computingGPAFunctions.o: computingGPAFunctions.c ComputeGPA.h
	$(CC) $(CFLAGS) -c computingGPAFunctions.c

clean:
	rm -f $(OBJFILES) $(TARGET)
