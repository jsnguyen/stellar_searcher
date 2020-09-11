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
      if (!fread(buffer, 1, length, f)){
        return 1; // if fread fails return 1
      }
    }
    fclose (f);
  }
  printf("Contents of file read in.\n");

  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */

  double *ras=NULL,*decs=NULL;
  int *pointingOrder=NULL;
  int raCounter=0,decCounter=0;
  int pointingOrderCounter=0;

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

    else if (jsoneq(buffer, &t[i], "coordinates") == 0){

      if (t[i+1].type != JSMN_ARRAY){
        continue; /* We expect groups to be an array of strings */
      }

      ras  = malloc(t[i+1].size*(sizeof(double)));
      decs = malloc(t[i+1].size*(sizeof(double)));

      for (int j=0;j<t[i+1].size;j++){
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

    else if (jsoneq(buffer, &t[i], "pointingOrder") == 0){
      if (t[i+1].type != JSMN_ARRAY){
        continue; 
      }

      pointingOrder = malloc(t[i+1].size*(sizeof(double)));

      for (int j=0;j<t[i+1].size;j++){
        jsmntok_t *g = &t[i+j+2];
        int coordLen = 32;
        char buf[2*coordLen];
        sprintf(buf,"%.*s\n", g->end-g->start, buffer+g->start);

        pointingOrder[pointingOrderCounter++] = atoi(buf);
      }
      i += t[i+1].size+1;

    }

    else {
      printf("Unexpected key: %.*s\n", t[i].end-t[i].start, buffer+t[i].start);
    }
  }


  DateTime J2000;
  SetDateTime(&J2000, 2000,1,1,12,0,0);

  for(int i=0;i<7;i++){
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
  if(pointingOrder!=NULL){
    free(pointingOrder);
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
    result = HMSToRad('+', atof(strVal), atof(strMin), atof(strSec));
  }
  else if(type=='d'){
    result = DMSToRad('+', atof(strVal), atof(strMin), atof(strSec));
  }

  return result;
}

void ParseSMPL(const char *filename, Constellation *cs){
  FILE * f = fopen (filename,"r");
  char line[MAX_LINE];
  int step = 0;

  char name[MAX_LINE];

  int n_stars=0;
  StellarCoordinate *stars=NULL;

  int n_pointing_order=0;
  int *pointing_order=NULL;

  int len_c;
  int len_p;

  StellarCoordinate sc;
  char *token;

  char *triggers[] = { "---- NAME ----",
                       "---- LEN_C ----",
                       "---- COORDINATES ----",
                       "---- LEN_P ----",
                       "---- POINTINGORDER ----"};

  while (fgets(line,MAX_LINE,f) != NULL){
    line[strcspn(line, "\r\n")] = 0; // strip newline

    // skip blank lines
    if(line[0] == '\0'){
      continue;
    }

    if(!strncmp(line,triggers[step],MAX_LINE)){
      step++;
      continue;
    }

    if(step == 1){
      printf("NAME: %s\n", line);
      strcpy(name,line);
    }

    else if(step == 2){
      len_c = atoi(line);
      stars = malloc(len_c*sizeof(StellarCoordinate));
    }

    else if(step == 3){
      printf("COORDINATES: %s\n", line);

      token = strtok(line, ",");
      sc.lon  = strParseCoord(token,'h');

      token = strtok(NULL, ",");
      sc.lat = strParseCoord(token,'d');

      StellarCoordinateSetJ2000(&sc);
      stars[n_stars] = sc;
      n_stars++;
    }

    else if(step == 4){
      len_p = atoi(line);
      pointing_order = malloc(len_p*sizeof(int));
    }

    else if(step == 5){

      printf("POINTINGORDER: %s\n", line);
      token = strtok(line, ",");

      while (token != NULL){
        pointing_order[n_pointing_order++] = atoi(token);
        token = strtok(NULL, ",");
      }

    }

  }

  fclose (f);
  ConstellationInit(cs, name, stars, n_stars, pointing_order, n_pointing_order);

}
