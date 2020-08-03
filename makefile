# Build macro definition

CXX = g++
CXXFLAGS = -Wall -g -MMD -std=c++14
OBJECTS = main.o block.o blockFactory.o blockSelectionStrategy.o board.o\
		  commandInterpreter.o controller.o  iBlock.o jBlock.o\
		  lblock.o level0.o level1.o level2.o level3.o level4.o\
		  oBlock.o quadris.o sBlock.o subject.o tBlock.o\
		  textDisplay.o tile.o zBlock.o location.o tileBlock.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}
