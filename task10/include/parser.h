#ifndef PARSER_H
#define PARSER_H

#include "tree.h"
#include "tokenizator.h"


Tree* Parse(Tokenizator* tokenizator);
void SetupTree(Tokenizator* tokenizator);

#endif // PARSER_H