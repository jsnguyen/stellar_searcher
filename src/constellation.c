#include "stellar_searcher/constellation.h"

Constellation* ConstellationCreate(){
  Constellation* cs=malloc(sizeof(Constellation));
  cs->stars=NULL;
  cs->len_s=0;
  cs->len_po=0;
  return cs;
}

void ConstellationInit(Constellation *cs, char name[], StellarCoordinate *stars, int len_s, int *pointingOrder, int len_po){
  strcpy(cs->name,name);

  cs->stars = stars;
  cs->len_s = len_s;

  cs->pointingOrder = pointingOrder;
  cs->len_po = len_po;
}

void ConstellationDestroyStars(Constellation *cs){
  if(cs->stars!=NULL) free(cs->stars);
}

void ConstellationDestroyPointingOrder(Constellation *cs){
  if(cs->stars!=NULL) free(cs->pointingOrder);
}

void ConstellationDestroy(Constellation *cs){
  free(cs);
}

void ConstellationSetName(Constellation *cs, char name[]){
  strcpy(cs->name,name);
}

void ConstellationSetLenS(Constellation *cs, int len_s){
  cs->len_s = len_s;
}

void ConstellationSetLenPO(Constellation *cs, int len_po){
  cs->len_po = len_po;
}

char* ConstellationGetName(Constellation *cs){
  return cs->name;
}

StellarCoordinate* ConstellationGetStars(Constellation *cs){
  return cs->stars;
}

int ConstellationGetLenS(Constellation *cs){
  return cs->len_s;
}

int ConstellationGetLenPO(Constellation *cs){
  return cs->len_po;
}

void ConstellationAdd(Constellation *cs, StellarCoordinate *star){
  StellarCoordinate *new = malloc((cs->len_s+1)*sizeof(StellarCoordinate));

  if(cs->len_s!=0){
    memcpy(new,cs->stars,cs->len_s*sizeof(StellarCoordinate));
    free(cs->stars);
  }

  StellarCoordinateCopy(&new[cs->len_s],star);

  cs->len_s++;
  cs->stars=new;

}

void ConstellationPrint(Constellation *cs){
  printf("Name: %s\n",cs->name);
  for(int i=0;i<cs->len_s;i++){
    StellarCoordinatePrintDecimal(&cs->stars[i], DEG);
  }
}
