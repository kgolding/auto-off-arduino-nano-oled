#include <OneBitDisplay.h>

void displayIntro(OBDISP *pOBD) {
    obdFill(&obd, 0, 1);
    obdWriteString(pOBD, 0, 6, 0, (char *)"1st Tattenhams", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 0, 1, (char *)"      WIFI", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 0, 3, (char *) "      OFF ", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 20, 6, (char *)"Press the green", FONT_SMALL, 0, 1);
    obdWriteString(pOBD, 0, 20, 7, (char *)"button to start", FONT_SMALL, 0, 1);
}

void displayOn(OBDISP *pOBD, long secs) {
    char s[16];
    int mins = secs / 60 + 1;
    sprintf(s, "     For %d mins   ", mins);
    obdWriteString(pOBD, 0, 0, 3, (char *)"     ACTIVE     ", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 0, 4, s, FONT_SMALL, 0, 1);
    obdWriteString(pOBD, 0, 20, 6, (char *)"Green: Add time", FONT_SMALL, 0, 1);
    obdWriteString(pOBD, 0, 20, 7, (char *)"Red: Switch off", FONT_SMALL, 0, 1);
}

void displayWarn(OBDISP *pOBD, long secs) {
    char s[16];
    sprintf(s, "Auto off in %d secs  ", (int)secs);
    obdWriteString(pOBD, 0, 0, 3, (char *)"    WARNING", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 0, 4, s, FONT_SMALL, 0, 1);
    // obdWriteString(pOBD, 0, 20, 6, (char *)"Green: Add time", FONT_SMALL, 0, 1);
    // obdWriteString(pOBD, 0, 20, 7, (char *)"Red: Switch off", FONT_SMALL, 0, 1);
}

void displayOffDelay(OBDISP *pOBD, long secs) {
    char s[16];
    sprintf(s, "     in %d secs       ", (int)secs);
    obdWriteString(pOBD, 0, 0, 3, (char *)"Powering down...  ", FONT_NORMAL, 0, 1);
    obdWriteString(pOBD, 0, 0, 4, s, FONT_SMALL, 0, 1);
    obdWriteString(pOBD, 0, 20, 6, (char *)"Green: Add time", FONT_SMALL, 0, 1);
    obdWriteString(pOBD, 0, 20, 7, (char *)"               ", FONT_SMALL, 0, 1);
}