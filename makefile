CC=gcc
BISON=/usr/local/Cellar/bison/3.8.2/bin/bison
CFLAGS=-std=c11
SOURCEDIR=./src
OUT=./build
SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

run: ${OUT}/mfcalc.out
	${OUT}/mfcalc.out

${OUT}/mfcalc.out: ${OUT}/parser.c ${SOURCES}
	${CC} ${CFLAGS} "${OUT}/parser.c" ${SOURCES} -o "${OUT}/mfcalc.out"

${OUT}/parser.c: ${SOURCEDIR}/parser.y
	${BISON} -M old=new -H -o "${OUT}/parser.c" ${SOURCEDIR}/parser.y
