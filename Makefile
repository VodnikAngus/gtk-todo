IZLAZ=to-do

ifeq ($(OS),Windows_NT)
	PLATFORMA=windows
	IME=a.exe
else
	PLATFORMA=linux
	IME=a.out
endif

all: ./*
	gcc main.c lib/fajlovi.c lib/razno.c  src/*.c -o ./bin/${PLATFORMA}/${IZLAZ} `pkg-config --cflags --libs gtk+-3.0` && ./bin/${PLATFORMA}/${IZLAZ}
	rm -f ./bin/${PLATFORMA}/${IZLAZ}

proba: ./*
	gcc proba.c lib/fajlovi.c lib/razno.c  `pkg-config --cflags --libs gtk+-3.0` && ./${IME}
	rm -f ${IME}