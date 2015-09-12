/****************************************************************
����     : JAGUAR V13.7.26	www.probo.co.kr
CPU      : ATMEGA128 - 16Mhz
�����Ϸ� : WinAVR 20100110 
������   : AvrStudio418
����Ű   : F7(������:HEX���� �����) 
           F12(Ŭ��:HEX���� �����)
���ǻ��� : �ٿ�ε�� ���� ���� ������ �´��� Ȯ���Ͻñ� �ٶ��ϴ�.
		   ��Ƭ������ ���͸� ���� ������, �������� ������ ���� �ǹǷ� �����ϼ���.
START����ġ�� ��� 
- �ѹ� ������ ��� : ���� ON, ���� Ʃ�� 
- �ι� ������ ��� : �κ� ���� 
- �ѹ� 1�ʰ� ������ ��� : �������͹̳� ����� 
- �ѹ� 2�ʰ� ������ ��� : ���� ����� 
*****************************************************************/

//#include <stdio.h>
#include "line.h"
#include "pemassi_S.h"



int main(void) 
{
	start(OFF,ON);					//1:BUZZER������� 2:LED������� 
	dir(FF);						//1:�κ��� ���� : FF(��) BB(��)
	error(0,2000);					//1:������� 2:���� ��ȭ �ð�  
	absh(20,18,15,13,10);				//���� ABS
	absl(10,9,8,5,0);					//���� ABS
	tabs(20,20,18,10,3);			//ȸ�� ���� ABS (alt1,2,3,4  art7,6,5,4 �� ����)
	psdsensor(2);
	turnabsh(ON,1);					//ȸ�� ABS
//	accdectime(ON,3,5,50,40,50);	//������ ���� �Լ� 
//	sturnstop(255); 				//1:����STOP ����: 0~255 slt, srt�� ����ϱ� ���� ���� 
	motorstop(255,255); 			//��ü ����STOP ����: 0~255 (0x00~0xff)
	timer(0);						//�κ� �ð� 
//	fdevopen(u0tx,0);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************************************
	on(OUT8);					    //STOP WATCH ���� ���� 
//***************************************************
	



	init_absh();

	chg_udt(10);
	chg_ddt(8);
	

	/*
	
	uline(l1,5,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	dline(l1,13,20,0);
	lt3(20,0);

	
	uline(l1,5,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	dline(l1,13,20,0);
	lt3(20,0);

	
	uline(l1,5,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	mline(l1,20,0);
	dline(l1,13,20,0);
	lt3(20,0);


	uline(l1,5,20,0);
	mline(l1,20,0);
	dline(l1,13,20,0);
	lt3(20,0);

	uline(t1,5,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	lt3(20,0);

	uline(t1,5,20,0);
	dline(t1,13,20,0);
	lt3(20,0);
	
	uline(t1,5,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	lt3(20,0);

	uline(t1,5,13,0);
	lt3(20,0);

	uline(t1,5,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	rt3(20,0);
	rt3(20,0);

	uline(t1,5,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	rt3(20,0);

	uline(t1,5,13,0);
	rt3(20,0);

	uline(t1,5,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	rt3(20,0);

	uline(t1,5,20,0);
	dline(t1,13,20,0);
	rt3(20,0);

	uline(t1,5,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	mline(t1,20,0);
	dline(t1,13,20,0);
	rt3(20,0);

	uline(r1,5,20,0);
	mline(r1,20,0);
	dline(r1,13,20,0);
	rt3(20,0);

	uline(r1,5,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	dline(r1,13,20,0);
	rt3(20,0);

	uline(r1,5,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	dline(r1,13,20,0);
	rt3(20,0);

	uline(r1,5,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	mline(r1,20,0);
	dline(r1,13,20,0);

	

	

	restart(1);
	*/

	solve_map(ALO_RIGHT_TURN,20);


//****************************************************
						//STOP WATCH ���� ���� 
//****************************************************
	end(CPU_RESET,0,0);				// CPU �ڵ� ���� 
//	end(REMOCON_MOVE,ID1,0);		//ID1, ID2
//	end(PS2_MOVE,BPS115200,0);		//BPS9600, BPS115200
//	end(ANALOG_TEST,STOPWATCH,S1+S2+S3+S4+S5+S6+S7+S8);
//	end(INPUT_TEST,STOPWATCH,0);
//	end(PSD_TEST,STOPWATCH,S1+S2+S3+S4+S5+S6+S7+S8);
//	end(ULTRA_TEST,STOPWATCH,0);
//	end(SERVO_TEST,STOPWATCH,OUT1+OUT2+OUT3+OUT4+OUT5+OUT6+OUT7+OUT8);
	return 0;

}




//***************************************************************************************//
//      ���� ���� ���α׷� (������������ �̸� ���� ��ġ���� �����Ͽ� ����մϴ�.)        //
//      ��� ��� : 																	 //
//      1. ���� ����ġ�� �ִ´�.														 //
//      2. START��ư�� ª�� �ѹ� ������.												 //
//      3. START��ư�� ��� ������. �߻߻� �Ҹ��� ���� ���� 							 //
//      4. �Ʒ� ������� ���� ��ġ�� ���� ��Ų��. 										 //
//***************************************************************************************//
void servo_program(void)
{
	switch(servo_mode)
	{
// ���� �׸� 
		case 0:		//�׸� �ø���  		
			servo_set(ON,1,0x10);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 1:		//�׸� ������ 
			servo_set(OFF,1,0x11);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 2:		//���� �׸� �ݱ� 	
			servo_set(ON,2,0x12);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 3:		//������ �׸� �ݱ� 
			servo_set(ON,3,0x13);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 4:		//���� �׸� ����
			servo_set(ON,2,0x14);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 5:		//������ �׸� ���� 
			servo_set(ON,3,0x15);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
// ���� �׸� 
		case 6:		//�׸� �ø��� 
			servo_set(ON,4,0x16);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 7:		//�׸� ������ 
			servo_set(OFF,4,0x17);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 8:		//���� �׸� �ݱ� 	
			servo_set(ON,5,0x18);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 9:		//������ �׸� �ݱ� 
			servo_set(ON,6,0x19);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 10:	//���� �׸� ����
			servo_set(ON,5,0x1a);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
		case 11:	//������ �׸� ���� 
			servo_set(ON,6,0x1b);		// servo_set(������ũ����,��������(1~8) , �޸� ���� �ּ�)
			break;
//
//�� �߰� �ϼ���.


	}
}


