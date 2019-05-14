#ifndef STGU_H_INCLUDED
#define STGU_H_INCLUDED
//Simple Terminal Graphics Utility
/* FOREGROUND */
#define RST   "\033[0m"
#define KRED  "\033[1;31m"
#define KGRN  "\033[1;32m"
#define KYEL  "\033[1;33m"
#define KBLU  "\033[1;34m"
#define KMAG  "\033[1;35m"
#define KCYN  "\033[1;36m"
#define KWHT  "\033[1;37m"

#define RRED  "\033[1;41m"
#define RGRN  "\033[1;42m"
#define RYEL  "\033[1;43m"
#define RBLU  "\033[1;44m"
#define RMAG  "\033[1;45m"
#define RCYN  "\033[1;46m"
#define RWHT  "\033[1;47m"

#define FRED(x) KRED<<x<<RST
#define FGRN(x) KGRN<<x<<RST
#define FYEL(x) KYEL<<x<<RST
#define FBLU(x) KBLU<<x<<RST
#define FMAG(x) KMAG<<x<<RST
#define FCYN(x) KCYN<<x<<RST
#define FWHT(x) KWHT<<x<<RST

/* BACKGROUND */
#define BRED(x) RRED<<x<<RST
#define BGRN(x) RGRN<<x<<RST
#define BYEL(x) RYEL<<x<<RST
#define BBLU(x) RBLU<<x<<RST
#define BMAG(x) RMAG<<x<<RST
#define BCYN(x) RCYN<<x<<RST
#define BWHT(x) RWHT<<x<<RST


/* OTHER */
#define BOLD(x) "\x1B[1m"<<x<<RST
#define UNDL(x) "\x1B[4m"<<x<<RST

/*
 * #include <iostream>
#include "STGU.h"
using namespace std;

int main()
{
    cout << FBLU("I'm blue.") << endl;
    cout << BOLD(FBLU("I'm blue-bold.")) << endl;
    return 0;
}
*/

#endif