CC=gcc
BISON=/usr/local/Cellar/bison/3.8.2/bin/bison
CFLAGS=-std=c11
SOURCEDIR=./src
OUT=./build
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

# ${SOURCEDIR}/main.c: ${OUT}/parser.c ${OUT}/lexer.c

${OUT}/parser.c: ${SOURCEDIR}/parser.y
	${BISON} -H -o "./build/parser.c" ${SOURCEDIR}/parser.y

# ${OUT}/lexer.c: ${SRC}/lexer.l