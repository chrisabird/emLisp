typedef enum tokenType {Empty, LeftParen, RightParen, Integer, Symbol} TokenType;
typedef struct token {
  TokenType type;
  union {
    int integer;
    char symbol[7]; 
  } val;
} Token;

Token lex(char c);
