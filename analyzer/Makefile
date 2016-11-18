CXX = g++
CXXFLAGS = -O3 -msse2 -mssse3 -mfpmath=sse -funroll-loops -ffast-math
CXXFLAGS += $(shell root-config --cflags)

# OBJDIR = ./objects
ODIR = ./objects
OBJS = $(addprefix $(ODIR)/, RATPAC_analyzer.o main.o )
SRCDIR = .
CXXFLAGS  += -I./include  -I.
CXXFLAGS  += -I$(RATPAC_PATH)/include/

LIBS += $(shell root-config --libs) -lGeom -lGui -lSpectrum 
LIBS += -L$(RATPAC_PATH)/lib -lRATEvent

	
all: RATPAC_analyzer.exe

$(OBJS): | $(ODIR)
#$(ODIR):
#	@mkdir -p $(ODIR)

$(ODIR)/main.o:main.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR)/%.o:%.cc %.hh
	$(CXX) -c $< -o $@ $(CXXFLAGS) 
	 
RATPAC_analyzer.exe: check_min $(OBJS) 
	$(CXX) $(OBJS) $(CXXFLAGS) $(LIBS) -o $@	
	
clean:
	@rm -f *.exe $(ODIR)/*.o *~ include/*~
	
.PHONY: check_min
check_min::
	@echo "Testing framework configuration:";
	@if test ! -e $$SHELL; \
	then \
		echo " Makefile needs bash and file /bin/bash is missing. Install bash or set proper link."; \
		exit 254; \
	fi;
	@if [ x$(ROOTSYS) = x ] || ! hash root-config 2>&- ; \
	then \
		echo " ROOTSYS not defined or root-config not found. Install or set properly ROOT before installing RAT-PAC framework."; \
		exit 253; \
	else \
		echo " Your ROOT version is: "$(shell root-config --version); \
	fi;
	@if [ x$(RATPAC_PATH) = x ]; \
	then \
		echo " RATPAC_PATH is not defined. Set RATPAC_PATH to your rat-pac directory."; \
		exit 252; \
	fi;	