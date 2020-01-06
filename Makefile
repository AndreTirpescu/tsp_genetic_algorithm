PROJECT_NAME := tema2_ag

CXX	:= g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BUILD 		:= build
SRC			:= src
INCLUDE		:= include
LIBRARIES	:=

CUSTOM_FLAGS := -DGENETIC_DEBUG

GA_MODULE_SRC	:= genetic_algorithm
GA_MODULE_INC	:= genetic_algorithm
GRAPH_MODULE	:= graph
TSP_MODULE		:= tsp

all: $(BUILD)/$(PROJECT_NAME)

clean: rm -rf build/*

$(BUILD)/$(PROJECT_NAME): $(SRC)/*.cpp $(GA_MODULE_SRC)/*.cpp $(TSP_MODULE)/*.cpp $(GRAPH_MODULE)/*.cpp
	$(CXX) $(CXX_FLAGS) $(CUSTOM_FLAGS) -I$(INCLUDE) -I$(GA_MODULE_INC) -I$(GRAPH_MODULE) -I$(TSP_MODULE) $^ -o $@ $(LIBRARIES)

