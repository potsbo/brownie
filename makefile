PROGNAME = Brownie
CXX = g++
CXXFLAGS= -std=c++11 -O2 -Wall -Wextra -g
BINNAME= brownie
OBJECTFILES= main.o ascii.o game.o keyboard.o pattern.o romajitable.o split.o stringj.o typo.o


$(BINNAME): $(OBJECTFILES)
	$(CXX) $(CXXFLAGS) -o $(BINNAME) $(OBJECTFILES)

e:
	$(EDITOR) main.cpp
clean:
	$(RM) $(BINNAME) $(OBJECTFILES) $(wildcard *.d)
run: $(BINNAME)
	./$(BINNAME)
debug:
	./$(BINNAME) --debug
redebug: $(BINNAME)  
	./$(BINNAME) --debug
%.o: %.cpp
	$(CXX) -MMD $(CXXFLAGS) -c -o $@ $<

-include $(wildcard *.d)
