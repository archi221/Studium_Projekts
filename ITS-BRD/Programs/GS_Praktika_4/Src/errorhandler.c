#include <errorhandler.h>

#include "lcd.h"
#include <stdio.h>

#define BUF_SIZE     256
static char buf[BUF_SIZE];

/**
* @brief Simple error handler that writes an error msg on 
*        LCD display and loops forever or returns EOK / NOK.
*        To receive correct file name and line number, this 
*        function should be called using der wrapper macro 
*        ERR_HANDLER.
* @param cnd  If this condition is true, an error will be reported.
* @param file The file containing the current call of this function.
* @param line Line number of the current call of this function
* @param msg  Error message
* @param loopForEver Don't return from this function call

* @retval None
*/

int printError(bool cnd, char *file, int line, char *msg, bool loopForEver) {
   if (cnd){
      snprintf(buf, sizeof(buf) / sizeof(buf[0]), "Error in file %s line %d: %s\n", file, line, msg);
      lcdGotoXY(1,1);
      lcdPrintS(buf);
      while(loopForEver) ;
      return NOK;
   }
   return EOK;
}
// EOF
