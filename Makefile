# swig -c++ -python src/hough.i
# g++ -fPIC -c src/hough.cxx -o src/hough.o
# g++ -fPIC -c src/hough_wrap.cxx -I/usr/include/python3.11m -o src/hough_wrap.o
# g++ -shared src/hough_wrap.o src/hough.o -o src/_hough.so

CC = g++
INCLUDES = -I/usr/include/python3.11 -I/usr/lib/python3/dist-packages/numpy/core/include/
CFLAGS = -fPIC -c
SWIG = swig
SWIGFLAGS = -c++ -python
PYTHON = python3

SRCDIR = src
BUILDDIR = build
ONAME = hough
TARGET = $(SRCDIR)/$(ONAME)

DOCDIR = docs
INSTALLDIR = /usr/local/lib/python3.11/dist-packages

all: $(TARGET)

$(TARGET): $(TARGET).cxx
	$(SWIG) $(SWIGFLAGS) $(TARGET).i
	$(CC) $(CFLAGS) $(TARGET).cxx -o $(TARGET).o
	$(CC) $(CFLAGS) $(TARGET)_wrap.cxx $(INCLUDES) -o $(TARGET)_wrap.o
	$(CC) -shared $(TARGET)_wrap.o $(TARGET).o -o $(SRCDIR)/_$(ONAME).so

.PHONY: clean

clean:
	rm -f $(TARGET)_wrap.cxx $(TARGET)_wrap.o $(TARGET).o $(SRCDIR)/_$(ONAME).so $(TARGET).py $(SRCDIR)/documentation.i 
	rm -rf $(DOCDIR)

# docs:
# 	mkdir -p $(DOCDIR)
# 	doxygen Doxyfile
# 	$(PYTHON) ./doxy2swig.py $(DOCDIR)/xml/index.xml $(SRCDIR)/documentation.i

install:
	sudo mv $(TARGET).py $(INSTALLDIR)
	sudo mv $(SRCDIR)/_$(ONAME).so $(INSTALLDIR)

