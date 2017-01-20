AUTOMAKE_OPTIONS=foreign subdir-objects
CURRENTPATH=$(shell /bin/pwd)
AM_CPPFLAGS=--std=c++11 -I$(CURRENTPATH)/src
#noinst_LIBRARIES=libgpio.a
#libgpio_a_SOURCES=src/gpio.cpp

bin_PROGRAMS=ppmdecode
ppmdecode_SOURCES=src/main.cpp
ppmdecode_LDFLAGS=-L/usr/lib -lrt -lpigpio -lpthread
