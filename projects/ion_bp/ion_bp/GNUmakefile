name := ion_bp
G4TARGET := $(name)
G4EXLIB := true

.PHONY: all

# ROOT support
CPPFLAGS += -I$(shell root-config --incdir) 
EXTRALIBS = $(shell root-config --glibs)

all : lib bin
include $(G4INSTALL)/config/binmake.gmk


