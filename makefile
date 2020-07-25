# Build macro definition

CXX = g++
CXXFLAGS = -Wall -g -MMD
OBJECTS = block.o blockFactory.o blockSelectionStrategy.o board.o
		  commandInterpreter.o controller.o graphics.o iBlock.o jBlock.o
		  lblock.o level0.o level1.o level1.o level2.o level3.o level4.o
		  oBlock.o observer.o quadris.o sBlock.o subject.o tBlock.o
		  textDisplay.o tile.o zBlock.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}