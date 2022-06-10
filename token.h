typedef enum
{
    // grouping
    RIGHT_PAREN,
    LEFT_RAREN,

    // mathematical operations
    MINUS,
    PLUS,
    SLASH,
    STAR,

    // literals
    INTEGER

} token_t;

struct token
{
    token_t type;
    char *lexeme;     // raw substrings of the source code.
};