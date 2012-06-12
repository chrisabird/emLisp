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
// | 2 Byte        |
// | Reader State  |
// | --------------|
// | 766 Bytes     |
// | Stack Space   |
// -----------------

// Type Definitions
typedef enum dataType { Integer } DataType;

typedef struct data Data;
struct data { 
	DataType type;
	union { 
		int val;
		Data *ref;
	} car;
};

typedef struct symbol { 
	char name[7];
	Data *ref;
} Symbol;

// Global Variables

Data *datums; 
Symbol *symbols; 

// Reader (Syntax Error = -2, Keep Reading = -1, Datum = x >= 0 ) 
typedef enum readerState { Nothing, AnInteger  } ReaderState;
int currentlyReading  = Nothing;
int currentInteger = 0; 
int read(int c) { 
	if(currentlyReading == Nothing) {
		if(isdigit(c)) {
			currentlyReading = AnInteger;
		} else if(isspace(c)) {
			return -1;
		} else { 
			return -2;
		}
	}

	switch(currentlyReading) { 
		case AnInteger:
			if(isdigit(c)) {
				currentInteger = currentInteger * 10;
				currentInteger = currentInteger + (c - '0') ;
				return -1;
			}
			if(isspace(c)) {
				datums[0].type = Integer;
				datums[0].car.val = currentInteger;
				currentInteger = 0;
				currentlyReading = Nothing;
				return 0;
			} else { 
				currentInteger = 0;
				currentlyReading = Nothing;
				return -2;
			}
		default:
			return -1;
	}
}

void evaluate(int datumToEval) {
	Data *datum = &datums[datumToEval];
	
	switch(datum->type) {
		case Integer:
			printf("%d", datum->car.val);
			break;
		default:
			break;
	}
}

// Main
int main(int argc, char *argv[]) {
	datums = malloc(333 * sizeof *datums);
	symbols = malloc(67 * sizeof *symbols);
	
	int r = -1;
	while(r == -1) {
		r = read(getchar());
		if(r == -2) {
			printf("Syntax error");
		}
	}

	evaluate(r);
	return 0;
}
