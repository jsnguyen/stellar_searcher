#include <stdio.h>
#include <stdlib.h>
#include "stellar_searcher/constellation.h"
#include "stellar_searcher/interpolate.h"
#include "stellar_searcher/stellarCoordinate.h"
#include "stellar_searcher/parser.h"
#include "jsmn.h"

// Test for checking the string parser

int main(){

  char *testCoord="11h03m43.67152s";
  printf("input  = %s\n",testCoord);
  double result = strParseCoord(testCoord,'h');
  printf("result = %f\n",result);

  return 0;
}
