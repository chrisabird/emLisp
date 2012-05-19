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
// | 768 Bytes     |
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

const Data *datums; 
const Symbol *symbols; 

// Reader 
int currentInteger = 0; 
void read(int c) { 
	if(isdigit(c)) {
	
	}
	
}

void evaluate() { 

}

// Main
int main(int argc, char *argv[]) {
	datums = malloc(333 * sizeof *datums);
	symbols = malloc(67 * sizeof *symbols);
	while(1) {
		int c = getchar();
		read(c);
	}

	return 0;
}
