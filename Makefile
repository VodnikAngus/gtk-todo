IME=to-do
CFLAGS=-O2 -Wall `pkg-config --cflags --libs gtk+-3.0`
LIBS=lib/*.c src/*.c

ifeq ($(OS),Windows_NT)
	PLATFORMA=windows
	EXT=.exe
	CFLAGS+=-mwindows
	IZLAZ=./bin/${PLATFORMA}/bin/${IME}
else
	PLATFORMA=linux
	EXT=
	IZLAZ=./bin/${PLATFORMA}/${IME}
endif

all: ./*
	gcc main.c ${LIBS} -o ${IZLAZ}${EXT} ${CFLAGS} && ${IZLAZ}${EXT}
	#rm -f ./bin/${PLATFORMA}/${IZLAZ}

test: ./*
	gcc test.c ${LIBS} -o test${EXT} ${CFLAGS} && ./test${EXT}
	# rm -f test${EXT}