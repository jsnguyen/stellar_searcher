#include "stellar_searcher/celestialTime.h"

// Various examples for using celestialTime functions
// Examples on how to convert and print coordinates and times

int main(){

  double longitude = 33;

  int JDN = GetCurrentJDN();
  printf("Current JDN -> %d\n",JDN);
  printf("JDN on 9/25/2018 -> %d\n",GetJDN(2018,9,25));

  double JD = GetCurrentJD();
  printf("Current JD  -> %f\n",JD);
  printf("JDN on 9/25/2018 00:00:00 -> %f\n",GetJD(0,0,0,2018,9,25));

  printf("\n");
  printf("====================\n\n");

  printf("Current GMT -> %f\n",GetGMT());
  PrintDecimalHoursToHMS(GetGMT());
  printf("\n");

  printf("Current GMST -> %f\n",GetGMST(JD));
  PrintDecimalHoursToHMS(GetGMST(JD));
  printf("\n");

  printf("Current GAST -> %f\n",GetGAST(JD));
  PrintDecimalHoursToHMS(GetGAST(JD));
  printf("\n");

  printf("Current LMST -> %f\n",GetLMST(JD,longitude));
  PrintDecimalHoursToHMS(GetLMST(JD,longitude));
  printf("\n");

  printf("Current LAST -> %f\n",GetLAST(JD,longitude));
  PrintDecimalHoursToHMS(GetLAST(JD,longitude));
  printf("\n");

  printf("====================\n\n");

  printf("GMST 0h UTC 2018/2/1-> %f\n",GetGMST(GetJD(0,0,0,2018,2,1)));
  PrintDecimalHoursToHMS(GetGMST(GetJD(0,0,0,2018,2,1)));
  printf("\n");

  printf("GAST 0h UTC 2018/2/1-> %f\n",GetGAST(GetJD(0,0,0,2018,2,1)));
  PrintDecimalHoursToHMS(GetGAST(GetJD(0,0,0,2018,2,1)));
  printf("\n");

  printf("====================\n\n");

  printf("DMS to Decimal Degrees\n");
  printf("-16d44\'41.5\" to Decimal: %f\n",DMSToDecimalDegrees(-16,44,41.5));
  printf("\n");

  printf("HMS to Decimal Hours\n");
  printf("06:45:59.19 to Decimal: %f\n",HMSToDecimalHours(6,45,59.19));
  printf("\n");

  printf("====================\n\n");

  printf("Print Decimal Degrees in DMS\n");
  printf("1.2345d -> ");
  PrintDecimalDegreesToDMS(1.2345);
  printf("-1.2345d -> ");
  PrintDecimalDegreesToDMS(-1.2345);
  printf("\n");

  printf("====================\n\n");

  char out[64];
  printf("Decimal Degrees to DMS Str\n");
  DecimalDegreesToDMSStr(1.2345, out);
  printf("1.2345d -> %s\n",out);

  printf("Decimal Hours to HMS Str\n");
  DecimalHoursToHMSStr(12.345, out);
  printf("12.345h -> %s\n",out);
  printf("\n");

  printf("====================\n\n");

  printf("Decimal Degrees to Decimal Hours\n");
  printf("180.0d -> %f\n",DecimalDegreesToDecimalHours(180.0));
  printf("41.0d -> %f\n",DecimalDegreesToDecimalHours(41.0));
  printf("360.0d -> %f\n",DecimalDegreesToDecimalHours(360.0));
  printf("318.0d -> %f\n",DecimalDegreesToDecimalHours(318.0));
  printf("\n");

  printf("====================\n\n");

  printf("Decimal Hours to Decimal Degrees\n");
  printf("12.0h -> %f\n",DecimalHoursToDecimalDegrees(12.0));
  printf("12.5h -> %f\n",DecimalHoursToDecimalDegrees(12.5));
  printf("23.9h -> %f\n",DecimalHoursToDecimalDegrees(23.9));
  printf("1.235h -> %f\n",DecimalHoursToDecimalDegrees(1.235));

  printf("====================\n\n");

  printf("01/01/2000 12:00:00 -> %f\n",GetJulianYear(12,0,0,2000,1,1));

  return 0;
}
