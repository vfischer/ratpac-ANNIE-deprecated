CXX = g++
CXXFLAGS = -O3 -msse2 -mssse3 -mfpmath=sse -funroll-loops -ffast-math
CXXFLAGS += $(shell root-config --cflags)
# CXXFLAGS += -I$(DOGS_PATH)/DCBase
# CXXFLAGS += -I$(DOGS_PATH)/DCDB
# CXXFLAGS += -I$(DOGS_PATH)/DCGeo
# CXXFLAGS += -I$(DOGS_PATH)/DCEvent
# CXXFLAGS += -I$(DOGS_PATH)/DCValidity
# CXXFLAGS += -I$(DOGS_PATH)/DCRegistry
# CXXFLAGS += -I$(DOGS_PATH)/DCDBInterface
# CXXFLAGS += -I$(DOGS_PATH)/DCCalibApply

# OBJDIR = ./objects
ODIR = ./objects
OBJS = $(addprefix $(ODIR)/, RATPAC_analyzer.o main.o )
SRCDIR = .
CXXFLAGS  += -I./include  -I.
CXXFLAGS  += -I$(RATPAC_PATH)/include/

LIBS += $(shell root-config --libs) -lGeom -lGui -lSpectrum 
LIBS += -L$(RATPAC_PATH)/lib -lRATEvent
# LIBS += -L$(DOGS_PATH)/lib
# LIBS += -lDCBase
# LIBS += -lDCDB
# LIBS += -lDCGeo
# LIBS += -lDCEvent
# LIBS += -lDCValidity
# LIBS += -lDCRegistry
# LIBS += -lDCDBInterface
# LIBS += -lDCCalibApply
# LIBS += -lDCUtil

# all: analyzer.exe 
# 
# $(OBJDIR)/%.o:$(SRCDIR)/%.cc
# 	@mkdir -p $(OBJDIR)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<
# 
# $(OBJDIR)/%.o:$(INCDIR)/%.cc
# 	@mkdir -p $(OBJDIR)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<
# 
# $(OBJDIR)/%.o:$(SRCDIR)/%.C
# 	@mkdir -p $(OBJDIR)
# 	$(CXX) $(CXXFLAGS) -c -o $@ $<
# 
# analyzer.exe: $(OBJDIR)/ProgressBar.o $(OBJDIR)/analyzer.o $(OBJDIR)/main.o 
# 	$(CXX) $(CXXFLAGS) -o analyzer.exe $^ $(LIBS) 	
# 	strip analyzer.exe
	
all: RATPAC_analyzer.exe

$(OBJS): | $(ODIR)
#$(ODIR):
#	@mkdir -p $(ODIR)

$(ODIR)/main.o:main.cc
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(ODIR)/%.o:%.cc %.hh
	$(CXX) -c $< -o $@ $(CXXFLAGS) 
	 
RATPAC_analyzer.exe: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LIBS) -o $@
	
# data_mc_plot_2ang_FinalFitTree.exe: $(OBJDIR)/ProgressBar.o $(OBJDIR)/data_mc_plot_2ang_FinalFitTree.o $(OBJDIR)/main.o
# 	$(CXX) $(CXXFLAGS) -o data_mc_plot_2ang_FinalFitTree.exe $^ $(LIBS) 	
# 	strip data_mc_plot_2ang_FinalFitTree.exe	
	
clean:
	@rm -f *.exe $(ODIR)/*.o *~ include/*~