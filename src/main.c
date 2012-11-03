#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

// -----------------
// | 128 Bytes     |
// | Serial Buffer | 
// |----------------
// | 768 Bytes     |
// | Program Space | 
// | 256 Objects   |
// |---------------|
// | 256 Bytes		 |
// | Symbol Map		 |
// | 32 Symbols    |
// |---------------|
// | 3 Byte        |
// | Reader State  |
// | --------------|
// | 765 Bytes     |
// | Stack Space   |
// -----------------

// Type Definitions
typedef enum dataType { Integer, Boolean } DataType;

typedef struct data Data;
struct data { 
	DataType type;
	union { 
		int val;
		Data *ref;
	} car;
	int references;
};

typedef struct symbol { 
	char name[7];
	Data *ref;
} Symbol;

// Global Variables

Data *datums; 
Symbol *symbols; 

// Reader State Variables
#define SYNTAX_ERROR -2
#define KEEP_READING -1
typedef enum readerState { Nothing, AnInteger, ABoolean  } ReaderState;
int currentDatum = 0;
int currentlyReading  = Nothing;
int currentInteger = 0;

int read_char(int c) { 
	if(currentlyReading == Nothing) {
		if(isdigit(c)) {
			currentlyReading = AnInteger;
		} else if(c == '#') {
			currentlyReading = ABoolean;
		} else if(isspace(c)) {
			return KEEP_READING;
		} else { 
			return SYNTAX_ERROR;
		}
	}

	switch(currentlyReading) { 
		case AnInteger:
			if(isdigit(c)) {
				currentInteger = currentInteger * 10;
				currentInteger = currentInteger + (c - '0') ;
				return KEEP_READING;
			}
			if(isspace(c)) {
				datums[currentDatum].type = Integer;
				datums[currentDatum].references = 0;
				datums[currentDatum].car.val = currentInteger;
				currentInteger = 0;
				currentlyReading = Nothing;
				return currentDatum;
			} else { 
				currentInteger = 0;
				currentlyReading = Nothing;
				return SYNTAX_ERROR;
			}
		case ABoolean: 
			if(c == '#') {
				return KEEP_READING; 
			} else if(c == 't') {
				datums[currentDatum].type = Boolean;
				datums[currentDatum].references = 0;
				datums[currentDatum].car.val = 1;
				return currentDatum;
			} else if(c == 'f') {
				datums[currentDatum].type = Boolean;
				datums[currentDatum].references = 0;
				datums[currentDatum].car.val = 0;
				return currentDatum;
			} else {
				return SYNTAX_ERROR;
			}
		default:
			return KEEP_READING;
	}
}

void print(int datumToPrint) {
	Data *datum = &datums[datumToPrint];
	
	if(datumToPrint == SYNTAX_ERROR) {
		puts("Syntax error");
		return;
	}
	
	switch(datum->type) {
		case Integer:
			printf("%d\n", datum->car.val);
			break;
		case Boolean: 
			printf("%s\n", (datum->car.val == 1) ? "true" : "false");
			break;
		default:
			break;
	}
}

int read() { 
	int r = KEEP_READING;
	while(r == KEEP_READING) {
		r = read_char(getchar());
	}
	return r;
}

// Main
int main(int argc, char *argv[]) {
	datums = malloc(333 * sizeof *datums);
	symbols = malloc(67 * sizeof *symbols);
	while(1) { 
		print(read());
	}
	return 0;
}
