#pragma once

#include <sstream>
#include <vector>
#include <string>
#include "date.h"
//#include "database.h"
//#include "condition_parser.h"
using namespace std;

enum class TokenType {
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};
enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};
enum class LogicalOperation {
    And,
    Or
};
struct Token {
    const string value;
    const TokenType type;
};

vector<Token> Tokenize(istream& cl);


