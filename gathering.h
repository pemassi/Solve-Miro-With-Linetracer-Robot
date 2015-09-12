#include <stdlib.h>
extern unsigned char SM[12];	//서보모터 저장 변수
#define S1UP	SM[0]
#define S1DN	SM[1]
#define S2CL	SM[2]
#define S3CL	SM[3]
#define S2OP	SM[4]
#define S3OP	SM[5]

#define S4UP	SM[6]
#define S4DN	SM[7]
#define S5CL	SM[8]
#define S6CL	SM[9]
#define S5OP	SM[10]
#define S6OP	SM[11]


//6개 서보 모터 동작 시작 
void robot_start(void)
{

	servo2(S2OP);
	servo3(S3OP);
	delay(500);
	servo1(S1DN);
	delay(500);
	servo2(S2CL);
	servo3(S3CL);
	delay(500);
	servo1(S1UP);
	delay(500);


	servo5(S5OP);
	servo6(S6OP);
	delay(500);
	servo4(S4DN);
	delay(500);
	servo5(S5CL);
	servo6(S6CL);
	delay(500);
	servo4(S4UP);
	delay(500);

}
void ffdown(void)	{	servo1(S1DN);}
void ffup(void)		{	servo1(S1UP);}
void bbdown(void)   {	servo4(S4DN);}
void bbup(void)		{	servo4(S4UP);}
void ffopen(void)	{	servo2(S2OP);	servo3(S3OP);	}
void ffclose(void)	{	servo2(S2CL);	servo3(S3CL);	}
void bbopen(void)	{	servo5(S5OP);	servo6(S6OP);	}
void bbclose(void)	{	servo5(S5CL);	servo6(S6CL);	}
