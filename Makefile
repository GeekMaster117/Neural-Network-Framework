CXX = g++
CXXFLAGS = -Wall

INCLUDE_PATH = ./include
CONFIG_H = ${INCLUDE_PATH}/config.h

SRC_PATH = ./src
MATRIX_CPP = ${SRC_PATH}/matrix.cpp
CONFIG_CPP = ${SRC_PATH}/config.cpp

OBJ_PATH = ./bin/obj
MATRIX_O = ${OBJ_PATH}/matrix.o
CONFIG_O = ${OBJ_PATH}/config.o
OBJS = ${MATRIX_O} ${CONFIG_O}

OUT_PATH = ./bin/out
TARGET = ${OUT_PATH}/nnfs

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) ${OBJS}

${MATRIX_O}: ${MATRIX_CPP} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${MATRIX_CPP} -o ${MATRIX_O}

${CONFIG_O}: ${CONFIG_CPP} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${CONFIG_CPP} -o ${CONFIG_O}

run:
	${TARGET}

clean:
	rm -f $(TARGET) $(OBJS)