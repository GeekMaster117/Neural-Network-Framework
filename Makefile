CXX = g++
CXXFLAGS = -Wall -g

INCLUDE_PATH = ./include
CONFIG_H = ${INCLUDE_PATH}/config.h
UTILS_H = ${INCLUDE_PATH}/utils.h

SRC_PATH = ./src
MATRIX_CPP = ${SRC_PATH}/matrix.cpp
CONFIG_CPP = ${SRC_PATH}/config.cpp
UTILS_CPP = ${SRC_PATH}/utils.cpp

OBJ_PATH = ./bin/obj
MATRIX_O = ${OBJ_PATH}/matrix.o
CONFIG_O = ${OBJ_PATH}/config.o
UTILS_O = ${OBJ_PATH}/utils.o
OBJS = ${MATRIX_O} ${CONFIG_O} ${UTILS_O}

OUT_PATH = ./bin/out
TARGET = ${OUT_PATH}/nnfs

$(TARGET): $(OBJ_PATH) $(OUT_PATH) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) ${OBJS}

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OUT_PATH):
	mkdir -p $(OUT_PATH)

${MATRIX_O}: ${MATRIX_CPP} ${UTILS_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${MATRIX_CPP} -o ${MATRIX_O}

${CONFIG_O}: ${CONFIG_CPP} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${CONFIG_CPP} -o ${CONFIG_O}

${UTILS_O}: ${UTILS_CPP} ${UTILS_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${UTILS_CPP} -o ${UTILS_O}

run:
	${TARGET}

clean:
	rm -f $(TARGET) $(OBJS)

debug-run:
	gdb -ex run --args ${TARGET}