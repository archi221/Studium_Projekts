#include <stdbool.h>
#define STRING_SIZE 20
#include <limits.h>
#include <string.h>

int modulo;
int counter = 0;
char text[STRING_SIZE];
bool is_minus;



void definitly_not_sprintf(char text_value[], int value) {
		if (value == INT_MIN) {
			strcpy(text_value, "-2147483648");
			return;
		}
    if (counter == 0) { //checking if the value is negativ or 0
        if (value < 0) {
            is_minus = true;
            value = value * (-1);
        } else if (value == 0) {
            text_value[0] = ' ';
            text_value[1] = '0';
            return;
        } else {
					is_minus = false;
				}
    }
		while (value != 0) {
			char c;
      modulo = value % 10;
      c = modulo + '0';
      text_value[counter] = c;
			counter++;
			value = (value - modulo) / 10; 
		}
		
			if (is_minus){
				text_value[counter] = '-';
				counter++;
			}
			text_value[counter] = ' ';
			
			for (int i = 0; (counter - i) >= 0; i++) {//reversing text so that the value is in the correct order
				char c = text_value[i];
				text_value[i] = text_value[counter];
				text_value[counter] = c;
				counter--;

					}
       }
   
