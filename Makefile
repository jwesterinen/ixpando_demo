TARGET = ixpando_demo

LIBS = -lwiringPi
CFLAGS = $(INCLUDES) -O0 -g -Wall
LFLAGS = 

HEADERS = ixpando.h
OBJECTS = ixpando.o main.o

.PHONY: all
all: $(TARGET)

$(TARGET) : $(OBJECTS)
	gcc $(LFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o: %.cpp $(HEADERS)
	gcc $(CFLAGS) -o $@ $<


.PHONY: clean
clean:
	rm -f $(TARGET) *.o 


