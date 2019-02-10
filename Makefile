# swig -c++ -python hough.i
# g++ -fPIC -c hough.cxx
# g++ -fPIC -c hough_wrap.cxx -I/usr/include/python3.5m
# g++ -shared hough_wrap.o hough.o -o _hough.so

CC = g++
INCLUDES = -I/usr/include/python3.5m
CFLAGS = -fPIC -c
SWIG = swig
SWIGFLAGS = -c++ -python

SRCDIR = src
ONAME = hough
TARGET = $(SRCDIR)/$(ONAME)

all: $(TARGET)

$(TARGET): $(TARGET).cxx
	$(SWIG) $(SWIGFLAGS) $(TARGET).i
	$(CC) $(CFLAGS) $(TARGET).cxx -o $(TARGET).o
	$(CC) $(CFLAGS) $(TARGET)_wrap.cxx $(INCLUDES) -o $(TARGET)_wrap.o
	$(CC) -shared $(TARGET)_wrap.o $(TARGET).o -o $(SRCDIR)/_$(ONAME).so

.PHONY: clean

clean:
	rm -f $(TARGET)_wrap.cxx $(TARGET)_wrap.o $(TARGET).o $(SRCDIR)/_$(ONAME).so $(TARGET).py
