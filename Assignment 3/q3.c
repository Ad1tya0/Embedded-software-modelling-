/* module SDF_Application where */

/* import ForSyDe.Shallow */

/* system :: Signal Int -> Signal Int -> Signal Int */
/* system s_in1 s_in2 = s_out where */
/*   s_1 = actor_a s_in1 */
/*   s_2 = actor_b s_in2 */
/*   s_3 = actor_c s_1 s_4_delayed */
/*   (s_4, s_out) = actor_d s_2 s_3 */
/*   s_4_delayed = delaySDF [0] s_4 */

/* actor_a :: Signal Int -> Signal Int */
/* actor_a = actor11SDF 2 1 f_1 where */
/*   f_1 [x, y] = [x + y] */

/* actor_b :: Signal Int -> Signal Int */
/* actor_b = actor11SDF 1 2 f_2 where */
/*   f_2 [x] = [x, x+1] */

/* actor_c :: Signal Int -> Signal Int -> Signal Int */
/* actor_c = actor21SDF (2,1) 1 f_3 where */
/*   f_3 [x, y] [z] = [x + y + z] */

/* actor_d :: Signal Int -> Signal Int -> (Signal Int, Signal Int) */
/* actor_d = actor22SDF (2,1) (1,2) f_4 where */
/*   f_4 [x, y] [z] = ([x + y + z], [x + y, x + y + z])  */
  

/* Use DEBUG INFORMATION when the program does not run correctly */
#define DEBUG 0
#define szBuf_ac 2
#define szBuf_bd 2
#define szBuf_cd 1
#define szBuf_dc 1

/*
 * The data type token needs to be defined!
 * 
 *	The library "circular_buffer.h" depends on it 
 */
typedef int token;
#include "circular_buffer.h" /* uses data type 'token' */
#include "sdf.h" /* uses circular_buffer.h */
#include <stdio.h>

/* Definition of functions within actors */
void f_1(token* x, token* y) //x is the input taking 2 tokens, y is output
{
	token sum=0;
	for (int i=0; i<2; i++)
		sum=sum+ x[i];
	*y=sum;		
}
void f_2(token* x, token* y) //x is input, y is the output giving 2 tokens
{
	y[0]=*x;
	y[1]=*x+1;
}
void f_3(token* x1, token* x2, token* y)  //x1 is the input taking 2 tokens, x2 is input taking 1 token, y is output
{
	*y=x1[0]+x1[1]+*x2;
}
void f_4(token* x1, token* x2, token* y1, token* y2) //x1 is the input taking 2 tokens, x2 is input taking in 1 token, y1 is o/p giving 1 token, y2 is o/p giving 2 tokens
{
	*y1    = x1[0]+x1[1]+*x2;
	y2[0] = x1[0]+x1[1];
	y2[1] = x1[0]+x1[1]+*x2;
}

/* Main program */
int main() {
  /* Create FIFO-buffers for channels */
  //First we allocate memory for our buffers:
  token* buffer_ac = malloc(szBuf_ac * sizeof(token)); 
  token* buffer_bd = malloc(szBuf_bd * sizeof(token));
  token* buffer_cd = malloc(szBuf_cd * sizeof(token));
  token* buffer_dc = malloc(szBuf_dc * sizeof(token));
  //Allocate input and output buffers
  token* buffer_in1 = malloc(2 * sizeof(token));
  token* buffer_in2 = malloc(1 * sizeof(token));
  token* buffer_out = malloc(2 * sizeof(token));

  //Create the FIFO channels
  channel ch_ac  = createFIFO(buffer_ac, szBuf_ac);
  channel ch_bd  = createFIFO(buffer_bd, szBuf_bd);
  channel ch_cd  = createFIFO(buffer_cd, szBuf_cd);
  channel ch_dc  = createFIFO(buffer_dc, szBuf_dc);
  //I/O channels
  channel ch_in1 = createFIFO(buffer_in1, 2);
  channel ch_in2 = createFIFO(buffer_in2, 1);
  channel ch_out = createFIFO(buffer_out, 2);


  /* Put initial tokens in channel s_4 */
  writeToken(ch_dc, 0); //delay
  token* outTokens;
  


  /* Repeating schedule: */
  while(1) {

	 /* Read input tokens */
  	 int input1a, input1b, input2; 
  	 printf("Please enter two values for input1 tokens\n");
  	 scanf("%d %d", &input1a, &input1b); //Get Inputs from user
  	 writeToken(ch_in1, (token)input1a);
  	 writeToken(ch_in1, (token)input1b);
  	 printf("Please enter one value for input2 token\n");
     scanf("%d", &input2);
     writeToken(ch_in2, (token)input2);
     /* Execute schedule */ 
     // A,A,B,C,D
  	 actor11SDF(2, 1, &ch_in1, &ch_ac, f_1);                     //actor a
     printf("Please enter two values for input1 tokens\n");
     scanf("%d %d", &input1a, &input1b); //Get Inputs from user
     writeToken(ch_in1, (token)input1a);
     writeToken(ch_in1, (token)input1b);
     actor11SDF(2, 1, &ch_in1, &ch_ac, f_1);                     //actor a  
  	 actor11SDF(1, 2, &ch_in2, &ch_bd, f_2);                     //actor b
  	 actor21SDF(2, 1, 1, &ch_ac, &ch_dc, &ch_cd, f_3);            //actor c
  	 actor22SDF(2, 1, 1, 2, &ch_bd, &ch_cd, &ch_dc, &ch_out, f_4); //actor d

	 /* Write output tokens */

   int err=0;

	 err=readToken(ch_out, outTokens);
	 printf("%d, ",*outTokens);
	 err=readToken(ch_out, outTokens);
	 printf("%d\n",*outTokens);
	 circular_buf_reset(ch_out); 
  }
  //Freeing the allocated memory for the buffers
  free(buffer_ac);
  free(buffer_bd);
  free(buffer_dc);
  free(buffer_cd);
  free(buffer_in1);
  free(buffer_in2);
  free(buffer_out);

  return 0;
}
