#ifndef __LINE_H
#define __LINE_H
#include <avr/io.h>

extern volatile unsigned char _b7flag,_f7flag,_f7cnt,_b7cnt;

#define DEBUG_BOARD 0
#define HYPERTERNAL 1

/////////////////////////////////////////////////////////////////////
/////////////////////// END함수 인자값  /////////////////////////////
/////////////////////////////////////////////////////////////////////
#define COMPUTER		0
#define computer		0
#define STOPWATCH		1
#define stopwatch		1
#define SERVO_TEST		0
#define INPUT_TEST		1
#define ANALOG_TEST		2
#define PSD_TEST		3
#define servo_test		0
#define input_test		1
#define analog_test		2
#define psd_test		3
#define REMOCON_MOVE	4
#define remocon_move	4
#define PS2_MOVE		5
#define PS2_move		5
#define ULTRA_TEST		6
#define ultra_test		6
#define CPU_RESET		10
#define cpu_reset		10
//// 리모콘 아이디 
#define ID1			0
#define id1			0
#define ID2			1
#define id2			1
#define ID3			2
#define id3			2
#define ID4			3
#define id4			3
#define ID5			4
#define id5			4
#define ID6			5
#define id6			5
#define ID7			6
#define id7			6
#define ID8			7
#define id8			7
#define ID9			8
#define id9			8
#define ID10		9
#define id10		9
#define ID11		10
#define id11		10
#define ID12		11
#define id12		11
#define ID13		12
#define id13		12
#define ID14		13
#define id14		13
#define ID15		14
#define id15		14
#define ID16		15
#define id16		15


#define OLD_VERSION		0
#define NEW_VERSION		1
#define old_version		0
#define new_sersion		1

/////////////////////////////////////////////////////////////////////
////////////////////////   AD 컨버터값  /////////////////////////////
/////////////////////////////////////////////////////////////////////
#define 	ADC1	(ADCDATA[0])
#define 	ADC2	(ADCDATA[1])
#define 	ADC3	(ADCDATA[2])
#define 	ADC4	(ADCDATA[3])
#define 	ADC5	(ADCDATA[4])
#define 	ADC6	(ADCDATA[5])
#define 	ADC7	(ADCDATA[6])
#define 	ADC8	(ADCDATA[7])

#define 	adc1	(ADCDATA[0])
#define 	adc2	(ADCDATA[1])
#define 	adc3	(ADCDATA[2])
#define 	adc4	(ADCDATA[3])
#define 	adc5	(ADCDATA[4])
#define 	adc6	(ADCDATA[5])
#define 	adc7	(ADCDATA[6])
#define 	adc8	(ADCDATA[7])
/////////////////////////////////////////////////////////////////////
////////////////////////   PSD 센서값  //////////////////////////////
/////////////////////////////////////////////////////////////////////
#define 	PSD1	(ADTOPSD[ADCDATA[0]])
#define 	PSD2	(ADTOPSD[ADCDATA[1]])
#define 	PSD3	(ADTOPSD[ADCDATA[2]])
#define 	PSD4	(ADTOPSD[ADCDATA[3]])
#define 	PSD5	(ADTOPSD[ADCDATA[4]])
#define 	PSD6	(ADTOPSD[ADCDATA[5]])
#define 	PSD7	(ADTOPSD[ADCDATA[6]])
#define 	PSD8	(ADTOPSD[ADCDATA[7]])

#define 	psd1	(ADTOPSD[ADCDATA[0]])
#define 	psd2	(ADTOPSD[ADCDATA[1]])
#define 	psd3	(ADTOPSD[ADCDATA[2]])
#define 	psd4	(ADTOPSD[ADCDATA[3]])
#define 	psd5	(ADTOPSD[ADCDATA[4]])
#define 	psd6	(ADTOPSD[ADCDATA[5]])
#define 	psd7	(ADTOPSD[ADCDATA[6]])
#define 	psd8	(ADTOPSD[ADCDATA[7]])


#define 	_PSD1	(ADTOPSD10_80[ADCDATA[0]])
#define 	_PSD2	(ADTOPSD10_80[ADCDATA[1]])
#define 	_PSD3	(ADTOPSD10_80[ADCDATA[2]])
#define 	_PSD4	(ADTOPSD10_80[ADCDATA[3]])
#define 	_PSD5	(ADTOPSD10_80[ADCDATA[4]])
#define 	_PSD6	(ADTOPSD10_80[ADCDATA[5]])
#define 	_PSD7	(ADTOPSD10_80[ADCDATA[6]])
#define 	_PSD8	(ADTOPSD10_80[ADCDATA[7]])

#define 	_psd1	(ADTOPSD10_80[ADCDATA[0]])
#define 	_psd2	(ADTOPSD10_80[ADCDATA[1]])
#define 	_psd3	(ADTOPSD10_80[ADCDATA[2]])
#define 	_psd4	(ADTOPSD10_80[ADCDATA[3]])
#define 	_psd5	(ADTOPSD10_80[ADCDATA[4]])
#define 	_psd6	(ADTOPSD10_80[ADCDATA[5]])
#define 	_psd7	(ADTOPSD10_80[ADCDATA[6]])
#define 	_psd8	(ADTOPSD10_80[ADCDATA[7]])
/////////////////////////////////////////////////////////////////////
////////////////////////  입력 비교값  //////////////////////////////
/////////////////////////////////////////////////////////////////////
#define 	IN1		(INPUT&0x01)
#define 	IN2		(INPUT&0x02)
#define 	IN3		(INPUT&0x04)
#define 	IN4		(INPUT&0x08)
#define 	IN5		(INPUT&0x10)
#define 	IN6		(INPUT&0x20)
#define 	IN7		(INPUT&0x40)
#define 	IN8		(INPUT&0x80)

#define 	in1		(INPUT&0x01)
#define 	in2		(INPUT&0x02)
#define 	in3		(INPUT&0x04)
#define 	in4		(INPUT&0x08)
#define 	in5		(INPUT&0x10)
#define 	in6		(INPUT&0x20)
#define 	in7		(INPUT&0x40)
#define 	in8		(INPUT&0x80)
/////////////////////////////////////////////////////////////////////
/////////////////////  전방센서 비교값 //////////////////////////////
/////////////////////////////////////////////////////////////////////
#define 	FB1		(F_SENSOR_DIGITAL&0x01)
#define 	FB2		(F_SENSOR_DIGITAL&0x02)
#define 	FB3		(F_SENSOR_DIGITAL&0x04)
#define 	FB4		(F_SENSOR_DIGITAL&0x08)
#define 	FB5		(F_SENSOR_DIGITAL&0x10)
#define 	FB6		(F_SENSOR_DIGITAL&0x20)
#define 	FB7		(F_SENSOR_DIGITAL&0x40)
/////////////////////////////////////////////////////////////////////
#define 	fb1		(F_SENSOR_DIGITAL&0x01)
#define 	fb2		(F_SENSOR_DIGITAL&0x02)
#define 	fb3		(F_SENSOR_DIGITAL&0x04)
#define 	fb4		(F_SENSOR_DIGITAL&0x08)
#define 	fb5		(F_SENSOR_DIGITAL&0x10)
#define 	fb6		(F_SENSOR_DIGITAL&0x20)
#define 	fb7		(F_SENSOR_DIGITAL&0x40)
/////////////////////////////////////////////////////////////////////
#define 	FW1		(!(F_SENSOR_DIGITAL&0x01))
#define 	FW2		(!(F_SENSOR_DIGITAL&0x02))
#define 	FW3		(!(F_SENSOR_DIGITAL&0x04))
#define 	FW4		(!(F_SENSOR_DIGITAL&0x08))
#define 	FW5		(!(F_SENSOR_DIGITAL&0x10))
#define 	FW6		(!(F_SENSOR_DIGITAL&0x20))
#define 	FW7		(!(F_SENSOR_DIGITAL&0x40))
/////////////////////////////////////////////////////////////////////
#define 	fw1		(!(F_SENSOR_DIGITAL&0x01))
#define 	fw2		(!(F_SENSOR_DIGITAL&0x02))
#define 	fw3		(!(F_SENSOR_DIGITAL&0x04))
#define 	fw4		(!(F_SENSOR_DIGITAL&0x08))
#define 	fw5		(!(F_SENSOR_DIGITAL&0x10))
#define 	fw6		(!(F_SENSOR_DIGITAL&0x20))
#define 	fw7		(!(F_SENSOR_DIGITAL&0x40))
/////////////////////////////////////////////////////////////////////
/////////////////////  후방센서 비교값 //////////////////////////////
/////////////////////////////////////////////////////////////////////
#define 	BB1		(B_SENSOR_DIGITAL&0x01)
#define 	BB2		(B_SENSOR_DIGITAL&0x02)
#define 	BB3		(B_SENSOR_DIGITAL&0x04)
#define 	BB4		(B_SENSOR_DIGITAL&0x08)
#define 	BB5		(B_SENSOR_DIGITAL&0x10)
#define 	BB6		(B_SENSOR_DIGITAL&0x20)
#define 	BB7		(B_SENSOR_DIGITAL&0x40)
/////////////////////////////////////////////////////////////////////
#define 	bb1		(B_SENSOR_DIGITAL&0x01)
#define 	bb2		(B_SENSOR_DIGITAL&0x02)
#define 	bb3		(B_SENSOR_DIGITAL&0x04)
#define 	bb4		(B_SENSOR_DIGITAL&0x08)
#define 	bb5		(B_SENSOR_DIGITAL&0x10)
#define 	bb6		(B_SENSOR_DIGITAL&0x20)
#define 	bb7		(B_SENSOR_DIGITAL&0x40)
/////////////////////////////////////////////////////////////////////
#define 	BW1		(!(B_SENSOR_DIGITAL&0x01))
#define 	BW2		(!(B_SENSOR_DIGITAL&0x02))
#define 	BW3		(!(B_SENSOR_DIGITAL&0x04))
#define 	BW4		(!(B_SENSOR_DIGITAL&0x08))
#define 	BW5		(!(B_SENSOR_DIGITAL&0x10))
#define 	BW6		(!(B_SENSOR_DIGITAL&0x20))
#define 	BW7		(!(B_SENSOR_DIGITAL&0x40))
/////////////////////////////////////////////////////////////////////
#define 	bw1		(!(B_SENSOR_DIGITAL&0x01))
#define 	bw2		(!(B_SENSOR_DIGITAL&0x02))
#define 	bw3		(!(B_SENSOR_DIGITAL&0x04))
#define 	bw4		(!(B_SENSOR_DIGITAL&0x08))
#define 	bw5		(!(B_SENSOR_DIGITAL&0x10))
#define 	bw6		(!(B_SENSOR_DIGITAL&0x20))
#define 	bw7		(!(B_SENSOR_DIGITAL&0x40))
/////////////////////////////////////////////////////////////////////
/////////////////////    I/O 선택값    //////////////////////////////
/////////////////////////////////////////////////////////////////////
#define	 	OUT1		0x01		
#define 	OUT2		0x02
#define 	OUT3		0x04
#define 	OUT4		0x08
#define 	OUT5		0x10
#define 	OUT6		0x20
#define 	OUT7		0x40
#define 	OUT8		0x80
/////////////////////////////////////////////////////////////////////
#define 	SW1			0x01		
#define 	SW2			0x02
#define 	SW3			0x04
#define 	SW4			0x08
#define 	SW5			0x10
#define 	SW6			0x20
#define 	SW7			0x40
#define 	SW8			0x80
/////////////////////////////////////////////////////////////////////
#define 	sensor1		(0x01)
#define 	sensor2		(0x02)
#define 	sensor3		(0x04)
#define 	sensor4		(0x08)
#define 	sensor5		(0x10)
#define 	sensor6		(0x20)
#define 	sensor7		(0x40)
#define 	sensor8		(0x80)
/////////////////////////////////////////////////////////////////////
#define 	s1			(0x01)
#define 	s2			(0x02)
#define 	s3			(0x04)
#define 	s4			(0x08)
#define 	s5			(0x10)
#define 	s6			(0x20)
#define 	s7			(0x40)
#define 	s8			(0x80)
/////////////////////////////////////////////////////////////////////
#define 	S1			(0x01)
#define 	S2			(0x02)
#define 	S3			(0x04)
#define 	S4			(0x08)
#define 	S5			(0x10)
#define 	S6			(0x20)
#define 	S7			(0x40)
#define 	S8			(0x80)
/////////////////////////////////////////////////////////////////////
////////////////////      초음파 센서   /////////////////////////////
/////////////////////////////////////////////////////////////////////

#define TEMPERATURE	25

#define ULTRA1	(331.5+(0.6*TEMPERATURE))*(ULTRA_CH[0]*0.000004/2)*1000
#define ULTRA2	(331.5+(0.6*TEMPERATURE))*(ULTRA_CH[1]*0.000004/2)*1000
#define ULTRA3	(331.5+(0.6*TEMPERATURE))*(ULTRA_CH[2]*0.000004/2)*1000
#define ULTRA4	(331.5+(0.6*TEMPERATURE))*(ULTRA_CH[3]*0.000004/2)*1000

/////////////////////////////////////////////////////////////////////
////////////////////  크로스 감지 방법  /////////////////////////////
/////////////////////////////////////////////////////////////////////
#define L1		1
#define L2		2
#define L3		3
/////////////////////////////////////////////////////////////////////
#define R1		4
#define R2		5
#define R3		6
/////////////////////////////////////////////////////////////////////
#define LR1		7
#define LR2		8
#define LR3		9
/////////////////////////////////////////////////////////////////////
#define SL1		11
#define SL2		12
#define SL3		13
/////////////////////////////////////////////////////////////////////
#define SR1		14
#define SR2		15
#define SR3		16
/////////////////////////////////////////////////////////////////////
#define SLR1	17
#define SLR2	18
#define SLR3	19
/////////////////////////////////////////////////////////////////////
#define T1		21
#define T2		22
#define T3		23
/////////////////////////////////////////////////////////////////////
#define l1		1
#define l2		2
#define l3		3
/////////////////////////////////////////////////////////////////////
#define r1		4
#define r2		5
#define r3		6
/////////////////////////////////////////////////////////////////////
#define lr1		7
#define lr2		8
#define lr3		9
/////////////////////////////////////////////////////////////////////
#define sl1		11
#define sl2		12
#define sl3		13
/////////////////////////////////////////////////////////////////////
#define sr1		14
#define sr2		15
#define sr3		16
/////////////////////////////////////////////////////////////////////
#define slr1	17
#define slr2	18
#define slr3	19
/////////////////////////////////////////////////////////////////////
#define t1		21
#define t2		22
#define t3		23
/////////////////////////////////////////////////////////////////////
#define ON		1
#define OFF		0
/////////////////////////////////////////////////////////////////////
//////////////////  로봇 진행 방향 선택   ///////////////////////////
/////////////////////////////////////////////////////////////////////
#define FF		0
#define LL		1
#define RR		2
#define BB		3
#define TG		4
/////////////////////////////////////////////////////////////////////
#define ff		0
#define ll		1
#define rr		2
#define bb		3
#define tg		4
/////////////////////////////////////////////////////////////////////
//////////////////       라인 색 설정     ///////////////////////////
/////////////////////////////////////////////////////////////////////
#define BLACK	0
#define WHITE	1
#define black	0
#define white	1
/////////////////////////////////////////////////////////////////////
#define MAXSPEED		20
#define MAXABS			0	//속도 최대 
#define MINABS			20	//속도 감속 
#define ABS_MAX_DUTY	20
/////////////////////////////////////////////////////////////////////
#define LEVEL_1			0
#define LEVEL_2			1
#define LEVEL_3			2
#define LEVEL_4			3
/////////////////////////////////////////////////////////////////////
//////////////////       멜로디 선택      ///////////////////////////
/////////////////////////////////////////////////////////////////////
#define do4		35391 	
#define xdo4	33405 
#define re4		31530 
#define xre4	29760
#define mi4		28090
#define pa4		26513
#define xpa4	25025
#define sol4	23621
#define xsol4	22295
#define ra4		21044
#define xra4	19863
#define si4		18748
#define ci4		18748
/////////////////////////////////////////////////////////////////////
#define do5		17696
#define xdo5	16702
#define re5		15765
#define xre5	14880	
#define mi5		14045
#define pa5		13257
#define xpa5	12513
#define sol5	11810
#define xsol5	11148
#define ra5		10522
#define xra5	9931
#define si5		9374
#define ci5		9374
/////////////////////////////////////////////////////////////////////
#define do6		8848	
#define xdo6	8351
#define re6		7883
#define xre6	7440
#define mi6		7023
#define pa6		6628
#define xpa6	6256
#define sol6	5905
#define xsol6	5574
#define ra6		5261
#define xra6	4966
#define si6		4687
#define ci6		4687
/////////////////////////////////////////////////////////////////////
#define do7		4424	
#define xdo7	4176
#define re7		3941
#define xre7	3720
#define mi7		3511
#define pa7		3314
#define xpa7	3128
#define sol7	2953
#define xsol7	2787
#define ra7		2630
#define xra7	2483
#define si7		2343
#define ci7		2343
/////////////////////////////////////////////////////////////////////
#define	n32		1*3	//3		// define note length
#define	n16		2*3 //6
#define	n16d	3*3	//9
#define	n16t	2*2	//4
#define	n8		4*3	//12
#define	n8d		6*3	//18
#define	n8t		4*2	//8
#define	n4		8*3	//24
#define	n4d		12*3//36
#define	n4t		8*2	//16
#define	n2		16*3	//48
#define	n2d		24*3	//72
#define	n2t		16*2	//32
#define	n1		32*3	//96
/////////////////////////////////////////////////////////////////////
#define START_KEY	(!(PING&0x10))
#define BPS115200		16
#define BPS57600		34
#define BPS9600			207
#define DIGITAL_MODE	0x00
#define ANALOG_MODE		0x08
#define TXD_DIR_F		4
#define RXD_DIR_F		5
#define TXD_DIR_B		6
#define RXD_DIR_B		7
#define SENSOR_LED		0x02
#define SENSOR_DISPLAY	0x04
#define SENSOR_INFRA	0x01


#define exline		bwmotor
#define exturn		bmotor
#define lostline	linelost
#define delayline	linedelay
#define findline	linefind
#define left1		lt1
#define left2		lt2
#define left3		lt3
#define left4		lt4
#define right4		rt4
#define right5		rt5
#define right6		rt6
#define right7		rt7
#define rt3		rt5
#define rt2		rt6
#define rt1		rt7
#define inleft		ilt2
#define inleft1		ilt1
#define inleft2		ilt2
#define inleft3		ilt3
#define inleft4		ilt4
#define inright		irt6
#define inright4	irt4
#define inright5	irt5
#define inright6	irt6
#define inright7	irt7
#define irt3		irt5
#define irt2		irt6
#define irt1		irt7
//
#define ileft		ilt2
#define ileft1		ilt1
#define ileft2		ilt2
#define ileft3		ilt3
#define ileft4		ilt4
#define iright		irt6
#define iright4		irt4
#define iright5		irt5
#define iright6		irt6
#define iright7		irt7
//
#define aleft1		alt1
#define aleft2		alt2
#define aleft3		alt3
#define aleft4		alt4
#define aright4		art4
#define aright5		art5
#define aright6		art6
#define aright7		art7

//
#define outright	ort
#define outleft		olt
#define oright		ort
#define oleft		olt

#define sensor		dir
#define motor_break	abs_ratio
#define motor_out	pwm_ratio
#define motorspeed	motorstop
////////////////////// IR REMOCON  //////////////////////////////

//REMOCON 전방키  
#define R_L2  			(REMOCON&0x0001)
#define R_R2  			(REMOCON&0x0002)
#define R_L1  			(REMOCON&0x0004)
#define R_R1  			(REMOCON&0x0008)

//REMOCON 오른쪽 방향키 
#define R_RF  			(REMOCON&0x0010)
#define R_RR  			(REMOCON&0x0020)
#define R_RB  			(REMOCON&0x0040)
#define R_RL  			(REMOCON&0x0080)


//REMOCON 왼쪽 방향키 
#define R_LF			(REMOCON&0x0100)
#define R_LR  			(REMOCON&0x0200)
#define R_LB  			(REMOCON&0x0400)
#define R_LL  			(REMOCON&0x0800)

//REMOCON 왼쪽 방향키 
#define R_1			(REMOCON&0x01)
#define R_2  		(REMOCON&0x02)
#define R_3  		(REMOCON&0x04)
#define R_4  		(REMOCON&0x08)
//R_ 오른쪽 방향키 
#define R_5  		(REMOCON&0x10)
#define R_6  		(REMOCON&0x20)
#define R_7  		(REMOCON&0x40)
#define R_8  		(REMOCON&0x80)
#define r_1			R_1
#define r_2			R_2
#define r_3			R_3
#define r_4			R_4
#define r_5			R_5
#define r_6			R_6
#define r_7			R_7
#define r_8			R_8
	
#define R__1		0x01
#define R__2		0x02
#define R__3		0x04
#define R__4		0x08
#define R__5		0x10
#define R__6		0x20
#define R__7		0x40
#define R__8		0x80

#define r__1		R__1
#define r__2		R__2
#define r__3		R__3
#define r__4		R__4
#define r__5		R__5
#define r__6		R__6
#define r__7		R__7
#define r__8		R__8
////////////////////// PS2 JOYSTICK //////////////////////////////
#define P_SELECT		(PSDATA[0]&0x01)
#define P_LSW			(PSDATA[0]&0x02)
#define P_RSW			(PSDATA[0]&0x04)
#define P_START 		(PSDATA[0]&0x08)

//PS2 왼쪽 방향키 
#define P_LF			(PSDATA[0]&0x10)
#define P_LR  			(PSDATA[0]&0x20)
#define P_LB  			(PSDATA[0]&0x40)
#define P_LL  			(PSDATA[0]&0x80)

//PS2 오른쪽 방향키 
#define P_RF  			(PSDATA[1]&0x10)
#define P_RR  			(PSDATA[1]&0x20)
#define P_RB  			(PSDATA[1]&0x40)
#define P_RL  			(PSDATA[1]&0x80)

//PS2 전방키  
#define P_L2  			(PSDATA[1]&0x01)
#define P_R2  			(PSDATA[1]&0x02)
#define P_L1  			(PSDATA[1]&0x04)
#define P_R1  			(PSDATA[1]&0x08)

//PS2 왼쪽 아날로그 방향키 
#define P_ALF  			(PSDATA[2]&0x10)
#define P_ALR  			(PSDATA[2]&0x20)
#define P_ALB  			(PSDATA[2]&0x40)
#define P_ALL 			(PSDATA[2]&0x80)

//PS2 오른쪽 아날로그 방향키 
#define P_ARF  			(PSDATA[2]&0x01)
#define P_ARR  			(PSDATA[2]&0x02)
#define P_ARB  			(PSDATA[2]&0x04)
#define P_ARL  			(PSDATA[2]&0x08)



#define VER				1
#define ver				1
#define HOR				2
#define hor				2


#define ZERO			0
#define ONE				1
#define TWO				2
#define THREE			3

//extern volatile unsigned int ADTOPSD[256];
//extern volatile unsigned int ADTOPSD10_80[256];
extern volatile unsigned char sensor_number;
extern volatile unsigned char F_SENSOR_DIGITAL;
extern volatile unsigned char B_SENSOR_DIGITAL;
extern volatile unsigned char F_SENSOR_ANALOG[8];
extern volatile unsigned char B_SENSOR_ANALOG[8];
extern volatile unsigned char line_color;
extern volatile unsigned char ADCDATA[8];
//extern volatile unsigned char REGTOSERVO[256];
extern volatile unsigned char PSDATA[10];
extern volatile unsigned char REMOCON;
extern volatile unsigned char INPUT;
extern volatile unsigned int ULTRA_CH[8];
extern volatile unsigned int ULTRA_MM[8];
extern volatile unsigned char abs_break[6];
extern volatile unsigned int itimer1;
extern volatile unsigned int itimer2;
extern volatile unsigned int itimer3;
extern volatile unsigned int itimer4;
extern volatile unsigned int itimer5;
extern volatile unsigned int itimer6;
extern volatile unsigned int itimer7;
extern volatile unsigned int itimer8;
extern volatile unsigned int itimer9;
extern volatile unsigned int itimer10;
extern volatile unsigned int itimer11;
extern volatile unsigned int itimer12;
extern volatile unsigned char bfline;
extern volatile unsigned char servo_mode;

void reverse(unsigned char data0,unsigned char data1);
void linecolor(unsigned char data);
void abs_ratio(signed char left,signed char right);
void pwm_ratio(signed char left, signed char right);
void abswheel(signed char left, signed char right);
void wheel(signed char left, signed char right);
void ewheel(signed char m1,signed char m2,signed char m3,signed char m4);
void timeline(unsigned char cross,unsigned char speed,signed int backbrake,unsigned int aftertime);
void ttimer(unsigned int data);
void timer(unsigned int data);
void remocon(unsigned char use,unsigned char r_id);
void bluetooth(unsigned char use, unsigned char baudrate);
void autotime(char kind,signed char speed,unsigned int goaltime);
void sensornumber(unsigned char number);
void end(char kind,unsigned char debug_type,unsigned char servo_debug);
unsigned int realtime(void);
void savetime(unsigned char kind);
void funerror(unsigned int funtime);
void error(unsigned char use,unsigned int errtime);
void irt7(signed char lspeed,signed char rspeed, signed char backbrake);
void irt6(signed char lspeed,signed char rspeed, signed char backbrake);
void irt5(signed char lspeed,signed char rspeed, signed char backbrake);
void irt4(signed char lspeed,signed char rspeed, signed char backbrake);
void right(signed char lspeed,signed char rspeed, signed char backbrake);
void left(signed char lspeed,signed char rspeed, signed char backbrake);
void ilt4(signed char lspeed,signed char rspeed, signed char backbrake);
void ilt3(signed char lspeed,signed char rspeed, signed char backbrake);
void ilt2(signed char lspeed,signed char rspeed, signed char backbrake);
void ilt1(signed char lspeed,signed char rspeed, signed char backbrake);
void lt1(signed char speed,signed char backbrake);
void lt2(signed char speed,signed char backbrake);
void lt3(signed char speed,signed char backbrake);
void lt4(signed char speed,signed char backbrake);
void rt7(signed char speed,signed char backbrake);
void rt6(signed char speed,signed char backbrake);
void rt5(signed char speed,signed char backbrake);
void rt4(signed char speed,signed char backbrake);
void outturn(signed char lspeed,signed char rspeed,signed char backbrake);
void olt(signed char lspeed,signed char rspeed, signed char backbrake);
void ort(signed char lspeed,signed char rspeed, signed char backbrake);
void slt(signed char speed);
void _slt(signed char speed);
void srt(signed char speed);
void _srt(signed char speed);
void linedelay(unsigned int dtime,unsigned char speed,signed int backbrake);
void sturnstop(unsigned char stopratio);
void crosspush(unsigned int time,unsigned char startspd, unsigned char overspd);
void USART_Transmit( unsigned char data );
void restart(unsigned char number);
void first_start(unsigned char speed);
void line(unsigned char cross,unsigned char speed,signed int backbrake);
void cline(unsigned char cbrake,unsigned char cross,unsigned char speed,signed int backbrake);
void cline2(unsigned int time,unsigned char cbrake,unsigned char cross,unsigned char speed,signed int backbrake);
void line2(unsigned char cross,unsigned char speed);
void line1(unsigned char speed);
void play(unsigned int sound, unsigned int note);
void tempo(unsigned char data);
void beep(unsigned char data);
void melody(unsigned int data);
void accdectime(unsigned char use,unsigned char s_speed,unsigned char e_speed,unsigned char  acc,unsigned char  del,unsigned int stoptime);
void absh(unsigned char abs1, unsigned char abs2, unsigned char abs3, unsigned char abs4,unsigned char abs5);
void absl(unsigned char abs1, unsigned char abs2, unsigned char abs3, unsigned char abs4,unsigned char abs5);
void turnabsh(unsigned char use,unsigned char abs1);
void turnabs(unsigned char use,unsigned char abs1);
void pline(unsigned char data);
void linetracer(unsigned char speed);
void dir(char data);
void delay(unsigned int count);
void delay_us(unsigned int count);
void motorstop(unsigned char left, unsigned char right);//구 motorspeed
void motor(signed char left, signed char right, unsigned int time);
void sservo(unsigned char number,unsigned char speed,unsigned char position);
void servo(unsigned char number,unsigned char position);
void sservo1(unsigned char speed,unsigned char position);
void sservo2(unsigned char speed,unsigned char position);
void sservo3(unsigned char speed,unsigned char position);
void sservo4(unsigned char speed,unsigned char position);
void sservo5(unsigned char speed,unsigned char position);
void sservo6(unsigned char speed,unsigned char position);
void sservo7(unsigned char speed,unsigned char position);
void sservo8(unsigned char speed,unsigned char position);
void servo1(unsigned char position);
void servo2(unsigned char position);
void servo3(unsigned char position);
void servo4(unsigned char position);
void servo5(unsigned char position);
void servo6(unsigned char position);
void servo7(unsigned char position);
void servo8(unsigned char position);
void ffmotor(unsigned char lspeed, unsigned char rspeed);
void bbmotor(unsigned char lspeed, unsigned char rspeed);
void llmotor(unsigned char lspeed, unsigned char rspeed);
void rrmotor(unsigned char lspeed, unsigned char rspeed);
void bwmotor(signed char lspeed,signed char rspeed,unsigned char sensor,signed int backbrake);
void bmotor(signed char lspeed,signed char rspeed,unsigned char sensor,signed int backbrake);
void linefind(signed char lspeed,signed char rspeed,unsigned int delay);
void sline(unsigned char sensor,signed char speed,signed int backbrake);
void lostline(unsigned int losttime,signed char speed,signed int backbrake);
void before_line(void);
void psdsensor(unsigned char data);
void on(unsigned char output_port);
void off(unsigned char output_port);
void deg_buzzer(unsigned char output);
void start(unsigned char debug_buzzer,unsigned char sensorleduse);
void led(unsigned char count, unsigned int ontime, unsigned int offtime);
void buzzer(unsigned char count, unsigned int ontime, unsigned int offtime);
void mbuzzer(unsigned char count, unsigned int ontime, unsigned int offtime);
void buzzerled(unsigned char count, unsigned int ontime, unsigned int offtime);
void SENSOR_CMD(unsigned char mask,unsigned char data);
void sensing(unsigned char level);
void ewheel(signed char m1,signed char m2,signed char m3,signed char m4);
void ultrasonic(unsigned char data);
void usertimer(unsigned int data);
unsigned int readtime(void);
void inputline(unsigned char sensor_port,unsigned char onoff, unsigned char speed,signed int backbrake);
void psdline(unsigned char sensor_port,unsigned int distance, unsigned char speed,signed int backbrake);


void transtime(unsigned char kind,signed char speed,unsigned int goaltime);
void tabs(unsigned char abs1, unsigned char abs2, unsigned char abs3, unsigned char abs4,unsigned char abs5);
void alt4(signed char lspeed,signed char rspeed, signed char backbrake);
void alt3(signed char lspeed,signed char rspeed, signed char backbrake);
void alt2(signed char lspeed,signed char rspeed, signed char backbrake);
void alt1(signed char lspeed,signed char rspeed, signed char backbrake);
void aleft(signed char lspeed,signed char rspeed,signed char backbrake);
void art7(signed char lspeed,signed char rspeed, signed char backbrake);
void art6(signed char lspeed,signed char rspeed, signed char backbrake);
void art5(signed char lspeed,signed char rspeed, signed char backbrake);
void art4(signed char lspeed,signed char rspeed, signed char backbrake);
void aright(signed char lspeed,signed char rspeed,signed char backbrake);
int u0tx(char data);
void display(unsigned long data);
void start_melody(unsigned char note);
void end_melody(unsigned char note);
void level_up_melody(unsigned char note);
void level_down_melody(unsigned char note);
void servo_program(void);
void servo_set(unsigned char servo_torque,unsigned char servo_number,unsigned int save_addr);
void EEW(unsigned int uiAddress, unsigned char ucData);
unsigned char EER(unsigned int uiAddress);
void pwm_data(unsigned char data);
void _linedelay(unsigned int dtime,unsigned char speed,signed int backbrake);
void b_bline(unsigned char sensor_port,unsigned char speed,signed int backbrake);
void f_bline(unsigned char sensor_port,unsigned char speed,signed int backbrake);
void f_bwline(unsigned char sensor_port,unsigned char speed,signed int backbrake);
void b_bwline(unsigned char sensor_port,unsigned char speed,signed int backbrake);
void flt(signed char lspeed1,signed char rspeed1,signed char lspeed2,signed char rspeed2,signed int backbrake);
void frt(signed char lspeed1,signed char rspeed1,signed char lspeed2,signed char rspeed2,signed int backbrake);
void d_accdec(unsigned int delaytime,unsigned char goal_speed,unsigned int dtime);
void s_accdec(unsigned char sensor,unsigned char goal_speed,unsigned int dtime);
//////// 손쉬운 프로그램 디파인 ///////
#define LL1	line(l1,fs,0);
#define RR1	line(r1,fs,0);
#define TT1	line(t1,fs,0);
#define LL2	line(l2,fs,0);
#define RR2	line(r2,fs,0);
#define TT2	line(t2,fs,0);
#define LL3	line(l3,fs,0);
#define RR3	line(r3,fs,0);
#define TT3	line(t3,fs,0);
#define CLL1	cline(0,l1,fs,0);
#define CRR1	cline(0,r1,fs,0);
#define CTT1	cline(0,t1,fs,0);
#define CLL2	cline(0,l2,fs,0);
#define CRR2	cline(0,r2,fs,0);
#define CTT2	cline(0,t2,fs,0);
#define CLL3	cline(0,l3,fs,0);
#define CRR3	cline(0,r3,fs,0);
#define CTT3	cline(0,t3,fs,0);

#define	LTURN	lt2(rs,0);
#define RTURN	rt6rs,0);
#define SLTURN	slt(zs);
#define SRTURN	srt(zs);
#define PFF	pline(FF);
#define PLL	pline(LL);
#define PRR	pline(RR);

#define ll1	line(l1,fs,0);
#define rr1	line(r1,fs,0);
#define tt1	line(t1,fs,0);
#define ll2	line(l2,fs,0);
#define rr2	line(r2,fs,0);
#define tt2	line(t2,fs,0);
#define ll3	line(l3,fs,0);
#define rr3	line(r3,fs,0);
#define tt3	line(t3,fs,0);
#define cll1	cline(0,l1,fs,0);
#define crr1	cline(0,r1,fs,0);
#define ctt1	cline(0,t1,fs,0);
#define cll2	cline(0,l2,fs,0);
#define crr2	cline(0,r2,fs,0);
#define ctt2	cline(0,t2,fs,0);
#define cll3	cline(0,l3,fs,0);
#define crr3	cline(0,r3,fs,0);
#define ctt3	cline(0,t3,fs,0);
#define	lturn	lt2(rs,0);
#define rturn	rt6rs);
#define slturn	slt(zs);
#define srturn	srt(zs);
#define pff	pline(FF);
#define pll	pline(LL);
#define prr	pline(RR);


#define ASERVO1	(1+(ADC1*100)/255)
#define ASERVO2	(1+(ADC2*100)/255)
#define ASERVO3	(1+(ADC3*100)/255)
#define ASERVO4	(1+(ADC4*100)/255)
#define ASERVO5	(1+(ADC5*100)/255)
#define ASERVO6	(1+(ADC6*100)/255)
#define ASERVO7	(1+(ADC7*100)/255)
#define ASERVO8	(1+(ADC8*100)/255)


#define _ASERVO1	(101-(ADC1*100)/255)
#define _ASERVO2	(101-(ADC2*100)/255)
#define _ASERVO3	(101-(ADC3*100)/255)
#define _ASERVO4	(101-(ADC4*100)/255)
#define _ASERVO5	(101-(ADC5*100)/255)
#define _ASERVO6	(101-(ADC6*100)/255)
#define _ASERVO7	(101-(ADC7*100)/255)
#define _ASERVO8	(101-(ADC8*100)/255)



#endif

