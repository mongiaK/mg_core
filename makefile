target:=mg_lib

CXX:=clang

INCS=
CFLAGS=-g -Wall -O3
LIBS=
OBJ_DIR=obj

DIRS := $(shell find . -maxdepth 5 -type d)
VPATH = ${DIRS}

SRC=$(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJ=$(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(notdir $(SRC))))

all: prepare $(target)

prepare:
	@mkdir -p ${OBJ_DIR}

$(target): ${OBJ}
	${CXX} ${CFLAGS} ${INCS} $^ -o $@ ${LIBS}

$(OBJ_DIR)/%.o: %.c
	${CXX} ${CFLAGS} ${INCS} -c $< -o $@

.PHONY: clean

clean:
	@rm -rf ${OBJ_DIR} ${target}
