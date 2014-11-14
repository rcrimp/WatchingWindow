CC=g++
ARCH=-arch x86_64

OCVDIR=/Users/Reuben/Documents/WatchingWindow/opencv-2.4.9
#/home/cshome/s/steven/Public/COSC450/OpenCV

INCLUDE_FLAGS=-I$(OCVDIR)/include

CFLAGS=-c  $(INCLUDE_FLAGS) 
LDFLAGS= -L$(OCVDIR)/build/lib -lopencv_core -lopencv_highgui -lopencv_imgproc

SOURCES=ww_main.cpp ww_lib.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

default : clean compile

compile : $(SOURCES) $(EXECUTABLE)

clean :
	rm -rf $(OBJECTS) $(EXECUTABLE) *~ core

$(EXECUTABLE): $(OBJECTS) Makefile
	$(CC) $(ARCH) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
