/*
 * Runtime System for TC compiler
 */

#include <stdio.h>

void RTS_outputInteger(int i){
  printf("%d\n", i);
}

void RTS_printDivideByZeroError(int i){
  printf("ERROR: Divide by zero (line %d)\n",i);
}
