PROGNAME= Brownie
CC=g++
CFLAGS= -std=c++11 -Wall
SOURCE= main.o stringj.o keyboard.o
BINNAME= brownie
SOURCEFILES:=$(wildcard *.cpp)
HEADERFILES:=$(wildcard *.h)
OBJECTFILES=$(patsubst %.cpp,%.o,$(SOURCEFILES))

$(BINNAME): $(OBJECTFILES) $(HEADERFILES)
	$(CC) $(CFLAGS) -o $(BINNAME) $(OBJECTFILES)

# $(OBJECTFILES) : $(HEADER_FILES) $(SOURCEFILES)
# 		$(CC) -c $(CFLAGS) $(OBJECTFILES)

e:
	$(EDITOR) main.cpp
clean:
	rm -f $(BINNAME); rm -f *.o;
run: $(BINNAME)
	./$(BINNAME)
debug:
	./$(BINNAME) --debug
redebug: $(BINNAME)  
	./$(BINNAME) --debug
