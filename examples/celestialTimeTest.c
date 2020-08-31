#include "stellar_searcher/celestialTime.h"

// Various examples for using celestialTime functions
// Examples on how to convert and print coordinates and times

int main(){

  double longitude = 33;

  printf("CURRENT TIMES\n");
  printf("=============\n\n");

  DateTime currentDateTime;
  GetCurrentDateTime(&currentDateTime);

  int currJDN = GetJDN(currentDateTime);
  double currJD = GetJD(currentDateTime);
  printf("Current JDN -> %i\n", currJDN);
  printf("Current JD  -> %f\n", currJD);
  printf("\n");

  double currGMST = GetGMST(currentDateTime);
  printf("Current GMST -> %f\n",currGMST);
  PrintHMS(currGMST);
  printf("\n");

  double currGAST = GetGAST(currentDateTime);
  printf("Current GAST -> %f\n",currGAST);
  PrintHMS(currGAST);
  printf("\n");

  double currLMST = GetLMST(currentDateTime,longitude);
  printf("Current LMST -> %f\n",currLMST);
  PrintHMS(currLMST);
  printf("\n");

  double currLAST = GetLAST(currentDateTime,longitude);
  printf("Current LAST -> %f\n",currLAST);
  PrintHMS(currLAST);
  printf("\n");

  printf("TIMES ON 09/25/2018 00:00:00\n");
  printf("============================\n\n");

  DateTime testDateA;
  SetDateTime(&testDateA,2018,1,8,0,0,0);
  int JDNtda = GetJDN(testDateA);
  double JDtda = GetJD(testDateA);
  printf("JDN on 1/8/2018 00:00:00 -> %i\n", JDNtda);
  printf("JD  on 1/8/2018 00:00:00 -> %f\n", JDtda);
  printf("\n");

  double GMSTtda = GetGMST(testDateA);
  printf("GMST on 1/8/2018 00:00:00 -> %f\n",GMSTtda);
  PrintHMS(GMSTtda);
  printf("\n");

  double GASTtda = GetGAST(testDateA);
  printf("GAST on 1/8/2018 00:00:00 -> %f\n",GASTtda);
  PrintHMS(GASTtda);
  printf("\n");

  double LMSTtda = GetLMST(testDateA, longitude);
  printf("Current LMST -> %f\n",LMSTtda);
  PrintHMS(LMSTtda);
  printf("\n");

  double LASTtda = GetLAST(testDateA, longitude);
  printf("Current LAST -> %f\n",LASTtda);
  PrintHMS(LASTtda);
  printf("\n");

  printf("HMS/DMS to radians conversion testing\n");
  printf("=====================================\n\n");

  double rad;

  rad = DMSToRad('-', 16, 44, 41.5);
  printf("DMS to Radians\n");
  printf("-16d44\'41.5\" to Radians: %f\n",rad);
  printf("\n");

  rad = HMSToRad('+', 6, 45, 59.19);
  printf("HMS to Radians\n");
  printf("06:45:59.19 to Radians: %f\n",rad);
  printf("\n");

  printf("Radians to DMS/HMS conversion testing\n");
  printf("=====================================\n\n");
  printf("Radians to DMS\n");

  printf("0 rad:     ");
  PrintDMS(0);

  printf("PI/4 rad:  ");
  PrintDMS(PI/4);

  printf("PI/2 rad:  ");
  PrintDMS(PI/2);

  printf("3PI/2 rad: ");
  PrintDMS(3*PI/2);

  printf("7PI/4 rad: ");
  PrintDMS(7*PI/4);

  printf("2PI rad:   ");
  PrintDMS(2*PI);

  printf("\n");
  printf("Radians to HMS\n");

  printf("0 rad:     ");
  PrintHMS(0);

  printf("PI/4 rad:  ");
  PrintHMS(PI/4);

  printf("PI/2 rad:  ");
  PrintHMS(PI/2);

  printf("3PI/2 rad: ");
  PrintHMS(3*PI/2);

  printf("7PI/4 rad: ");
  PrintHMS(7*PI/4);

  printf("2PI rad:   ");
  PrintHMS(2*PI);

  return 0;
}
