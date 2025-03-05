CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

INCLUDE_PATH = ./include
MATRIX_HPP = ${INCLUDE_PATH}/matrix.hpp
LAYER_HPP = ${INCLUDE_PATH}/layer.hpp
LAYER_UTILS_H = ${INCLUDE_PATH}/layer_utils.h
CSV_UTILS_HPP = ${INCLUDE_PATH}/csv_utils.hpp
ACTIVATION_H = ${INCLUDE_PATH}/activation.h
CONFIG_H = ${INCLUDE_PATH}/config.h
ERROR_H = ${INCLUDE_PATH}/error.h

SRC_PATH = ./src
TRAIN_CPP = ${SRC_PATH}/train.cpp
TEST_CPP = $(SRC_PATH)/test.cpp
MATRIX_CPP = ${SRC_PATH}/matrix.cpp
LAYER_CPP = ${SRC_PATH}/layer.cpp
LAYER_UTILS_CPP = ${SRC_PATH}/layer_utils.cpp
CSV_UTILS_CPP = ${SRC_PATH}/csv_utils.cpp
ACTIVATION_CPP = ${SRC_PATH}/activation.cpp
CONFIG_CPP = ${SRC_PATH}/config.cpp
ERROR_CPP = ${SRC_PATH}/error.cpp

OBJ_PATH = ./bin/obj
TRAIN_O = ${OBJ_PATH}/train.o
TEST_O = $(OBJ_PATH)/test.o
MATRIX_O = ${OBJ_PATH}/matrix.o
LAYER_O = ${OBJ_PATH}/layer.o
LAYER_UTILS_O = ${OBJ_PATH}/layer_utils.o
CSV_UTILS_O = ${OBJ_PATH}/csv_utils.o
ACTIVATION_O = ${OBJ_PATH}/activation.o
CONFIG_O = ${OBJ_PATH}/config.o
ERROR_O = ${OBJ_PATH}/error.o

OUT_PATH = ./bin/out
TRAIN = ${OUT_PATH}/train
TEST = $(OUT_PATH)/test

PARAMS_PATH = ./data/params

OBJS = ${MATRIX_O} ${LAYER_O} ${LAYER_UTILS_O} ${CSV_UTILS_O} ${ACTIVATION_O} ${CONFIG_O} ${ERROR_O}
TRAIN_OBJS = $(TRAIN_O) $(OBJS)
TEST_OBJS = $(TEST_O) $(OBJS)

compile: $(OBJ_PATH) $(OUT_PATH) ${PARAMS_PATH} $(TRAIN_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TRAIN) $(TRAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(TEST_OBJS)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OUT_PATH):
	mkdir -p $(OUT_PATH)

$(PARAMS_PATH):
	mkdir -p $(PARAMS_PATH)

${TRAIN_O}: ${TRAIN_CPP} ${LAYER_HPP} ${LAYER_UTILS_HPP} ${CSV_UTILS_H} ${ACTIVATION_HPP} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${TRAIN_CPP} -o ${TRAIN_O}

${TEST_O}: $(TEST_CPP) $(CSV_UTILS_H)
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${TEST_CPP} -o ${TEST_O}

${MATRIX_O}: ${MATRIX_CPP} ${MATRIX_HPP} ${ERROR_H} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${MATRIX_CPP} -o ${MATRIX_O}

${LAYER_O}: ${LAYER_CPP} ${LAYER_HPP} ${LAYER_UTILS_H} ${CSV_UTILS_H} ${MATRIX_HPP}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${LAYER_CPP} -o ${LAYER_O}

${LAYER_UTILS_O}: ${LAYER_UTILS_CPP} ${LAYER_UTILS_H} ${CONFIG_H} ${ERROR_H}
	${CXX} ${CXXFLAGS} -I ${INCLUDE_PATH} -c ${LAYER_UTILS_CPP} -o ${LAYER_UTILS_O}

${CSV_UTILS_O}: ${CSV_UTILS_CPP} ${CSV_UTILS_HPP} ${MATRIX_HPP} ${CONFIG_H} ${ERROR_H}
	${CXX} ${CXXFLAGS} -I ${INCLUDE_PATH} -c ${CSV_UTILS_CPP} -o ${CSV_UTILS_O}

${ACTIVATION_O}: ${ACTIVATION_CPP} ${ACTIVATION_H}
	${CXX} ${CXXFLAGS} -I ${INCLUDE_PATH} -c ${ACTIVATION_CPP} -o ${ACTIVATION_O}

${CONFIG_O}: ${CONFIG_CPP} ${CONFIG_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${CONFIG_CPP} -o ${CONFIG_O}

${ERROR_O}: ${ERROR_CPP} ${ERROR_H}
	$(CXX) $(CXXFLAGS) -I $(INCLUDE_PATH) -c ${ERROR_CPP} -o ${ERROR_O}

train:
	$(TRAIN)

test:
	$(TEST)

clean-bin:
	rm -f $(TRAIN) $(OBJS)

clean-params:
	rm -rf $(PARAMS_PATH)/*

debug-train:
	gdb -ex run --args ${TRAIN}

debug-test:
	gdb -ex run --args ${TEST}