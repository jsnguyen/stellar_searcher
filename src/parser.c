#include "stellar_searcher/parser.h"

int jsoneq(const char *json, jsmntok_t *tok, const char *s){
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
    strncmp(json + tok->start, s, tok->end - tok->start) == 0){
    return 0;
  }
  return 1;
}

int jsonParse(Constellation *c, const char *filename){
  char * buffer = 0;
  long length;
  FILE * f = fopen (filename,"rb");

  if (f){
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer){
      if (!fread(buffer, 1, length, f)) return 1; // if fread fails return 1
    }
    fclose (f);
  }
  printf("Contents of file read in.\n");

  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */

  double *ras=NULL,*decs=NULL;
  int raCounter=0,decCounter=0;
  int len=0;

  jsmn_init(&p);
  r = jsmn_parse(&p, buffer, strlen(buffer), t, sizeof(t)/sizeof(t[0]));

  if (r < 0){
    printf("Failed to parse JSON: %d\n", r);
    return 1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT){
    printf("Object expected\n");
    return 1;
  }

  /* Loop over all keys of the root object */
  for (i=1;i<r;i++){
    if (jsoneq(buffer, &t[i], "name") == 0){
      char buf[32];
      sprintf(buf,"%.*s", t[i+1].end-t[i+1].start, buffer+t[i+1].start);
      strcpy(c->name,buf);
      i++;
    }

    else if (jsoneq(buffer, &t[i], "len") == 0){
      char buf[32];
      sprintf(buf,"%.*s\n", t[i+1].end-t[i+1].start, buffer+t[i+1].start);
      //c->len=atoi(buf);
      len=atoi(buf);
      ras  = malloc(len*(sizeof(double)));
      decs = malloc(len*(sizeof(double)));
      //c->stars = malloc(len*(sizeof(StellarCoordinate)));
      i++;
    }

    else if (jsoneq(buffer, &t[i], "coordinates") == 0){
      if(len==0 || ras==NULL || decs==NULL){
        printf("Cannot parse coordinates! Length not initialized.\n");
        break;
      }

      int j;

      if (t[i+1].type != JSMN_ARRAY){
        continue; /* We expect groups to be an array of strings */
      }

      for (j=0;j<t[i+1].size;j++){
        jsmntok_t *g = &t[i+j+2];
        int coordLen = 32;
        char buf[2*coordLen];
        char strRa[coordLen],strDec[coordLen];
        sprintf(buf,"%.*s\n", g->end-g->start, buffer+g->start);

        int counter=0;
        int end=0;
        for(int i=0;i<coordLen;i++){
          if(buf[i]==','){
            counter=i;
          }
          if(buf[i]=='\0'){
            end=i;
            break;
          }
        }

        sprintf(strRa,"%.*s", counter, buf);
        sprintf(strDec,"%.*s", end-counter, buf+counter+1);
        ras[raCounter++]=strParseCoord(strRa,'h');
        decs[decCounter++]=strParseCoord(strDec,'d');
      }
      i += t[i+1].size+1;

    }
    else{
      printf("Unexpected key: %.*s\n", t[i].end-t[i].start, buffer+t[i].start);
    }
  }


  DateTime J2000;
  SetDateTime(&J2000, 2000,1,1,12,0,0);

  for(int i=0;i<len;i++){
    StellarCoordinate star;

    StellarCoordinateInit(&star,
                          ras[i],
                          decs[i],
                          J2000,
                          CS_EQUATORIAL,
                          EPOCH_J2000);

    ConstellationAdd(c,&star);
    printf("%f %f\n",ras[i],decs[i]);
  }

  free(buffer);
  if(ras!=NULL){
    free(ras);
  }
  if(decs!=NULL){
    free(decs);
  }
  return 0;
}

// Uses string of size 16 here
double strParseCoord(char *s, char type){
  if(type!='h' && type!='d'){
    printf("ERROR: Bad type\n");
    return 0;
  }

  int strSecLen = 16;
  char strVal[2+1],strMin[2+1],strSec[strSecLen+1];

  sprintf(strVal,"%.*s", 2, s);
  sprintf(strMin,"%.*s", 2, s+3);

  int len=0;
  for(int i=0;i<strSecLen;i++){
    if((s)[i+6]=='s' || i==strSecLen-1){
      break;
    }
    len++;
  }
  sprintf(strSec,"%.*s",len,s+6);

  double result=0;
  if(type=='h'){
    // RECHECK THIS!!!!
    result = DMSToRad('+', atof(strVal), atof(strMin), atof(strSec));
  }
  else if(type=='d'){
    result = DMSToRad('+', atof(strVal), atof(strMin), atof(strSec));
  }

  return result;
}

