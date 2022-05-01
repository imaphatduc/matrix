#include "../include/Token.hpp"

void Token::debugLog()
{
    std::cout << '(' << sTokenType[type] << ", \"" << value << "\")\n";
}
