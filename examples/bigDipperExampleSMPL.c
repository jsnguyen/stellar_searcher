#include "stellar_searcher/parser.h"

int main(){
  Constellation cs;
  ConstellationInit(&cs,"",NULL,0,NULL,0);

  ParseSMPL("../data/constellations/ursa_major.smpl",&cs);

  ConstellationDestroyStars(&cs);
  ConstellationDestroyPointingOrder(&cs);

  return 0;
}
