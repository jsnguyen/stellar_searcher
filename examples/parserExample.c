#include "stellar_searcher/parser.h"

int main(){
  Constellation cs;
  ParseSMPL("../data/constellations/ursa_major.smpl",&cs);
  ConstellationDestroyStars(&cs);
  ConstellationDestroyPointingOrder(&cs);

  return 0;
}
