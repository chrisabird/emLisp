typedef enum tokenType {Empty, LeftParen, RightParen, Integer, Symbol, Character} TokenType;
typedef struct token {
  TokenType type;
  union {
    int integer;
    int character;
    char symbol[7]; 
  } val;
} Token;

void init();
void handleChar(char c);
Token findNextToken();
