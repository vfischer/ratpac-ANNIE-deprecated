G4VERSION := $(shell eval geant4-config --version)

all:
ifeq ($(G4VERSION), 10.1.2)
	@echo 'Your geant4 version is $(G4VERSION). Using "scons" to build'
	scons -j4
	@echo 'You can run "scons" to build RAT'
else 
ifeq ($(G4VERSION), 10.2.3)
	@echo 'Your geant4 version is $(G4VERSION). Using "scons" with extra arguments to build'
	scons -j4 -Q cppjailbreak="" -Q CXXFLAGS="-std=c++11 -w -O3 -lxerces-c"
	@echo 'You can run "scons -Q cppjailbreak="" -Q CXXFLAGS="-std=c++11 -w -O3"" to build RAT'
else
	@echo '**** Your geant4 version $(G4VERSION) is unsupported ****'
endif
endif

installdata:
	scons installdata
	@echo 'You can run "scons installdata" directly to copy neutron files.'

doc:
	scons doc
	@echo 'You can run "scons doc" directly to extract/generate docs.'

clean:
	scons -c
	@echo 'You can run "scons -c" directly to clean build.'

clean_log:
	rm rat.*.log
	@echo 'Cleaning the rat log files'
	
.PHONY: doc clean installdata all

