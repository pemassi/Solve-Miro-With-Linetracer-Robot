/****************************************************************
버전     : JAGUAR V13.7.26	www.probo.co.kr
CPU      : ATMEGA128 - 16Mhz
컴파일러 : WinAVR 20100110 
에디터   : AvrStudio418
단축키   : F7(컴파일:HEX파일 만들기) 
           F12(클린:HEX파일 지우기)
주의사항 : 다운로드시 버전 정보 폴더가 맞는지 확인하시기 바랍니다.
		   리튬폴리머 배터리 사용시 과충전, 과방전시 고장의 원인 되므로 주의하세요.
START스위치의 기능 
- 한번 눌렀을 경우 : 센서 ON, 센서 튜닝 
- 두번 눌렀을 경우 : 로봇 동작 
- 한번 1초간 눌렀을 경우 : 하이퍼터미널 디버깅 
- 한번 2초간 눌렀을 경우 : 통합 디버깅 
*****************************************************************/

//#include <stdio.h>
#include "line.h"
#include "pemassi_S.h"



int main(void) 
{
	start(OFF,ON);					//1:BUZZER사용유무 2:LED사용유무 
	dir(FF);						//1:로봇의 방향 : FF(앞) BB(뒤)
	error(0,2000);					//1:사용유무 2:센서 변화 시간  
	absh(20,18,15,13,10);				//직진 ABS
	absl(10,9,8,5,0);					//감속 ABS
	tabs(20,20,18,10,3);			//회전 감속 ABS (alt1,2,3,4  art7,6,5,4 에 적용)
	psdsensor(2);
	turnabsh(ON,1);					//회전 ABS
//	accdectime(ON,3,5,50,40,50);	//가감속 설정 함수 
//	sturnstop(255); 				//1:모터STOP 비율: 0~255 slt, srt를 사용하기 위한 설정 
	motorstop(255,255); 			//젠체 모터STOP 비율: 0~255 (0x00~0xff)
	timer(0);						//로봇 시간 
//	fdevopen(u0tx,0);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************************************
	on(OUT8);					    //STOP WATCH 계측 시작 
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
						//STOP WATCH 계측 종료 
//****************************************************
	end(CPU_RESET,0,0);				// CPU 자동 리셋 
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
//      서보 셋팅 프로그램 (가변저항으로 미리 서보 위치값을 저장하여 사용합니다.)        //
//      사용 방법 : 																	 //
//      1. 전원 스위치를 넣는다.														 //
//      2. START버튼을 짧게 한번 누른다.												 //
//      3. START버튼을 길게 누른다. 삐삐삐 소리가 날때 까지 							 //
//      4. 아래 순서대로 서보 위치를 저장 시킨다. 										 //
//***************************************************************************************//
void servo_program(void)
{
	switch(servo_mode)
	{
// 앞쪽 그립 
		case 0:		//그립 올리기  		
			servo_set(ON,1,0x10);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 1:		//그립 내리기 
			servo_set(OFF,1,0x11);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 2:		//왼쪽 그립 닫기 	
			servo_set(ON,2,0x12);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 3:		//오른쪽 그립 닫기 
			servo_set(ON,3,0x13);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 4:		//왼쪽 그립 열기
			servo_set(ON,2,0x14);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 5:		//오른쪽 그립 열기 
			servo_set(ON,3,0x15);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
// 뒤쪽 그립 
		case 6:		//그립 올리기 
			servo_set(ON,4,0x16);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 7:		//그립 내리기 
			servo_set(OFF,4,0x17);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 8:		//왼쪽 그립 닫기 	
			servo_set(ON,5,0x18);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 9:		//오른쪽 그립 닫기 
			servo_set(ON,6,0x19);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 10:	//왼쪽 그립 열기
			servo_set(ON,5,0x1a);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
		case 11:	//오른쪽 그립 열기 
			servo_set(ON,6,0x1b);		// servo_set(서보토크유지,서보선택(1~8) , 메모리 저장 주소)
			break;
//
//더 추가 하세요.


	}
}



