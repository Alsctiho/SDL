CXX = g++
CXXFLAGS = -c -Wall

OBJS = main.o game.o gameObject.o

main: $(OBJS)
	$(CXX) -o main $(OBJS) -L./lib -lmingw32 -lSDL2main -lSDL2

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $<

game.o: game.cpp
	$(CXX) $(CXXFLAGS) $<

gameObject.o: gameObject.cpp
	$(CXX) $(CXXFLAGS) $<

clean:
	del $(OBJS)
	del main.exe