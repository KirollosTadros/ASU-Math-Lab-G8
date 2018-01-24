CC = g++
#not using c++11, because old g++ compiler on server
CFLAGS = -std=c++0x
LDFLAGS =
EXE = matrix

#########################

SRC = $(wildcard *.cpp)
_OBJ = $(SRC:%.cpp=%.o)
OBJDIR = obj
OBJ = $(_OBJ:%=$(OBJDIR)/%)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $(EXE)
	
$(OBJDIR)/%.o: %.cpp %.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# rule for .cpp file that has no .h file
# i.e. main.cpp
# (note the missing %.h in pre-requisites)
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJ) *.out

test:
	@echo SRC = $(SRC)
	@echo _OBJ = $(_OBJ)
	@echo OBJ = $(OBJ)
