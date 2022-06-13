#include <stdio.h>

int main()
{ /* Integers are used as booleans */
  unsigned char x, y; //Output 
  unsigned char a, b; //Input
  /* State variable for S0-S3 */
  unsigned char state; //State variable holds current state 

  /* Initial State S0 */
  state = 0; //State initialized to zero (Initial state)
  while(1) {
    printf("Read input: ");
    scanf("%hhu %hhu", &a, &b);
    switch(state) {
    case 0:
      x = 0;
      y = 0;

      state = 1; 
      break;
    case 1:
      if (b) {x = 1;}
      else   {x = 0;}
      y = 0;

      if (a==1 && b ==0) {state = 2;}
      else   {state = 1;}
      break;
    case 2:
      if (b || a) {x = 1;}
      else        {x = 0;}
      if (b)      {y = 1;}
      else        {y = 0;}
      if (a !=b) {state = 1;}
      else       {state = 2;}
      break;
  
    default:
      printf("Error: State %hhu undefined!", state);
    }
    printf("x=%hhu y=%hhu\n", x, y);
    
    printf("state =%hhu \n", state);
  }
  return 0;
} 
