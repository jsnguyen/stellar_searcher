#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/celestialTime.h"
#include "jsmn.h"

int jsoneq(const char *json, jsmntok_t *tok, const char *s);
int jsonParse(Constellation *c, const char *filename);
double strParseCoord(char *s, char type);

#endif

