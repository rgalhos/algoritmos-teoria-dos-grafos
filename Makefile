CXX = g++

CFLAGS := -std=c++20
CFLAGS += -pedantic -Wall -Wextra
# CFLAGS += -g

LIBS := -lstdc++

OUT_DIR = ./build
OBJ_DIR = ./build/obj

ENTRYPOINT = ./main.cpp
COMMON = ./common.cpp

SRCS := $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

.PHONY: all clean

TARGETS = dijkstra kosaraju kruskal prim floyd

all: $(OBJS) $(TARGETS)

$(OBJ_DIR)/%.o: ./*/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OUT_DIR) $(OBJ_DIR)

$(TARGETS): % : $(OBJ_DIR)/%.o
	$(CXX) $(CFLAGS) -o $(OUT_DIR)/$@ $(COMMON) $(OBJ_DIR)/$@.o $(ENTRYPOINT) $(LIBS)
	cp $(OUT_DIR)/$@ ./$@/

clean:
	rm -rf $(OUT_DIR)
	$(foreach target, $(TARGETS), rm -f ./$(target)/$(target) &&) true
