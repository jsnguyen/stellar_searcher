#include "stellar_searcher/constellation.h"

Constellation* ConstellationCreate(){
  Constellation* cs=malloc(sizeof(Constellation));
  cs->stars=NULL;
  cs->len=0;
  return cs;
}

void ConstellationInit(Constellation *cs, char name[], StellarCoordinate *stars, int len){
  strcpy(cs->name,name);
  cs->stars = stars;
  cs->len = len;
}

void ConstellationDestroyStars(Constellation *cs){
  if(cs->stars!=NULL) free(cs->stars);
}

void ConstellationDestroy(Constellation *cs){
  free(cs);
}

void ConstellationSetName(Constellation *cs, char name[]){
  strcpy(cs->name,name);
}

void ConstellationSetLen(Constellation *cs, int len){
  cs->len = len;
}

char* ConstellationGetName(Constellation *cs){
  return cs->name;
}

StellarCoordinate* ConstellationGetStars(Constellation *cs){
  return cs->stars;
}

int ConstellationGetLen(Constellation *cs){
  return cs->len;
}

void ConstellationAdd(Constellation *cs, StellarCoordinate *star){
  StellarCoordinate *new = malloc((cs->len+1)*sizeof(StellarCoordinate));

  if(cs->len!=0){
    memcpy(new,cs->stars,cs->len*sizeof(StellarCoordinate));
    free(cs->stars);
  }

  StellarCoordinateCopy(&new[cs->len],star);

  cs->len++;
  cs->stars=new;

}

void ConstellationPrint(Constellation *cs){
  printf("Name: %s\n",cs->name);
  for(int i=0;i<cs->len;i++){
    StellarCoordinatePrintDecimal(&cs->stars[i]);
  }
}
