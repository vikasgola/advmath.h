CXX=clang++
CPPFLAGS=-std=c++11

LIB_DIR=./lib
INCLUDE_DIR=./include
SRC_DIRS=./src
BUILD_DIR=./dist

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

EXAMPLES_SRC := $(shell find examples -name '*.cpp')
EXAMPLES_OUT := $(EXAMPLES_SRC:%.cpp=%)

all: $(LIB_DIR)/libadvmath.so $(LIB_DIR)/libadvmath.a

examples: all $(EXAMPLES_OUT)


$(LIB_DIR)/libadvmath.so: $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) -shared -o $(LIB_DIR)/libadvmath.so $(OBJS)

$(LIB_DIR)/libadvmath.a: $(OBJS)
	ar cr $(LIB_DIR)/libadvmath.a $(OBJS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(EXAMPLES_OUT): $(EXAMPLES_SRC)
	$(CXX) $(CPPFLAGS) -I$(INCLUDE_DIR) $(LIB_DIR)/libadvmath.a $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(EXAMPLES_OUT)
