NAME=qimg
V_MAJOR=1
V_MINOR=0
V_MICRO=0
LIB_NAME=lib${NAME}.so
LIB_PATH=out/${LIB_NAME}
LIB_VER=${LIB_PATH}.${V_MAJOR}.${V_MINOR}.${V_MICRO}

CXX=g++
LD_FLAGS=-Wl,-soname,${LIB_NAME} -shared
CXX_FLAGS=-std=c++17 -fPIC -Wall -Wextra -pedantic -I./include

EXAMPLES_LD_FLAGS=${LIB_VER} -lqarg
EXAMPLES_CXX_FLAGS=-std=c++17 -Wall -Wextra -pedantic -I./src

SOURCES=$(wildcard src/*.cpp)
HEADERS=$(wildcard src/*.hpp)
OBJECTS=$(patsubst src/%,build/%,${SOURCES:.cpp=.o})
DIRS=$(sort $(dir ${OBJECTS})) build/include

EXAMPLE_SOURCES=$(wildcard examples/*.cpp)
EXAMPLE_OBJECTS=$(addprefix build/,${EXAMPLE_SOURCES:.cpp=.o})
EXAMPLES=$(addprefix out/,${EXAMPLE_SOURCES:.cpp=})

DIRS+=$(sort $(dir ${EXAMPLE_OBJECTS})) $(sort $(dir ${EXAMPLES}))

ifdef DEBUG
CXX_FLAGS += -g -DDEBUG
EXAMPLES_CXX_FLAGS += -g -DDEBUG
endif
ifndef DEBUG
CXX_FLAGS += -O2
EXAMPLES_CXX_FLAGS += -O2
endif

.PHONY: all
all: dirs ${LIB_VER}

.PHONY: examples
examples: all ${EXAMPLES}

example_%: out/examples/%
	LD_PRELOAD=${LIB_VER} $<

${LIB_VER}: ${OBJECTS}
	${CXX} $^ ${LD_FLAGS} -o $@

build/%.o: src/%.cpp
	${CXX} $< ${CXX_FLAGS} -c -o $@

out/examples/%: build/examples/%.o
	${CXX} $^ ${EXAMPLES_LD_FLAGS} -o $@

build/examples/%.o: examples/%.cpp
	${CXX} $< ${EXAMPLES_CXX_FLAGS} -c -o $@

.PHONY: dirs
dirs:
	mkdir -p ${DIRS}
	mkdir -p out/

.PHONY: clean
clean:
	-rm -r build/
	-rm -r out/

.PHONY: install
install:
	cp ${LIB_VER} /usr/local/lib
	mkdir -p /usr/local/include/${NAME}/
	cp -r ${HEADERS} /usr/local/include/${NAME}/

.PHONY: uninstall
uninstall:
	rm /usr/local/lib/${LIB_NAME}*
	rm -r /usr/local/include/${NAME}
