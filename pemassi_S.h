/**************************************
 
 라인트레이서 미로 인공지능
 
 최종 수정 : 2015,7,31
 
 
 
 **************************************/

#include "pemassi_g.h"

// 라인트레이서 크로스 관련 정의
#define LINE_KIND_LEFT              0
#define LINE_KIND_RIGHT             1
#define LINE_KIND_BOTH              2
#define LINE_KIND_NOT               3
#define LINE_KIND_NONE              4

// 알고리즘 관련 정의
#define ALO_LEFT_TURN               0
#define ALO_RIGHT_TURN              1
#define ALO_NOT_TURN                4

#define ALO_PSD                     0
#define ALO_BUTTON                  1

// 라인트레이서 인식 관련 정의
#define GO_LOST                     0
#define GO_MEET                     1
#define GO_FIN                      2

/* 사용자 설정 */
#define ALO_MODE                    0                   //턴 지점 감지 방식 (0 - PSD 1 - Button)

#define TURN_NOMAL_SPEED            7                   //탐색할 때 턴 속도
#define TURN_FAST_SPEED             8                   //돌아올 때 턴 속도
#define TURN_ADD_SPEED              4                   //돌아올 때 추가 턴 속도

#define LINE_SERACH_SPEED           5                   //탐색할 때 속도
#define LINE_FAST_SPEED             16                  //돌아올 때 속도
#define LINE_LOST_DELAY             50                  //라인로스트 딜레이
#define LINE_PUSH_DELAY             200                 //탐색할 때 앞으로 미는 값
#define LINE_PUSH_BACK_DELAY        200                 //탐색할 때 뒤로 미는 값
#define LINE_IGNORE_ALO             100                 //알고리즘 상 앞에 라인이 있는 것을 판단하는 딜레이
#define LINE_SERACH_ABSH            absh(5,3,1,1,1);    //탐색할 때 드라이버


/******************************************/
void find_line(int ALO, int speed);                      //미로 찾기
void go_turn(int speed, int kind);                       //턴
int go_line(int speed);                                  //라인트레이싱
int push_line(int speed);                  	             //푸싱
void chg_dir(int CDir);                                  //방향변경
void solve_map(int ALO, int speed);                      //맵 풀기
void find_home(int ALO, int speed);                      //시작위치 찾아가기
void find_home_safe(int ALO, int speed);                 //안정적인 돌아가기
/******************************************/

struct Map
{
    unsigned char kind;
    unsigned int time;
};

int Line_Count = -1;        //라인 카운트
struct Map Mapping[100];    //맵핑
int Robot_Dir = FF;         //현재 로봇 방향
int psd_dis=0;              //psd 거리
int final_line_time = 0;    //마지막 라인 시간
int search_flag = 0;        //탐색 중, 돌아오는 중 플래그(0 - 탐색중 1 - 돌아오는 중 2 - 천천히 돌아오는 중)

void solve_map(int ALO, int speed)
{
    chg_dir(FF);
    
    int i;
    for(i=0;i<=100;i++)
    {
        Mapping[i].kind=LINE_KIND_NONE;
        Mapping[i].time=0;
    }
    
	int temp_flag=0;
    itimer1=0;
    while(itimer1<1000)
    {
        if(START_KEY) {temp_flag=1; break;}
    }

    if(temp_flag==0) buzzer(2,100,100);
    else buzzer(3,100,100);
   

	while(1)
	{
		if(START_KEY)
		{
			delay(300);
			psd_dis=adc2;
			buzzer(2,100,100);
			break;
		}
	}

	delay(500);    
 
   	restart(1);

    find_line(ALO,LINE_SERACH_SPEED);
    
    chg_dir(BB);
    
    //집 찾아가기
    if(temp_flag==0) {find_home(ALO,LINE_FAST_SPEED); search_flag=1;}
    else {find_home_safe(ALO,LINE_SERACH_SPEED); search_flag=2;}
}

void find_line(int ALO, int speed)
{
    int error_flag=0;
    while(1)
    {
        //라인트레이서 한 칸 시작
        int temp_line = 0; //라인 결과
		
        itimer2=0;
                
	    temp_line = go_line(speed);
        
        Line_Count++;   //카운트 증가
		
		if(itimer2>LINE_IGNORE_ALO) error_flag=0;

        //라인을 만났을 때
        if (temp_line == GO_MEET)
        { 

            Mapping[Line_Count].kind = push_line(speed); //라인 푸쉬 & 교차로 확인
            Mapping[Line_Count].time = itimer2;
                        
            switch (Mapping[Line_Count].kind)
            {
                case LINE_KIND_BOTH:
                    
                    if(ALO==ALO_LEFT_TURN)
                    {
                        go_turn(speed,ALO_LEFT_TURN);
                    }
                    else if(ALO==ALO_RIGHT_TURN)
                    {
                        go_turn(speed,ALO_RIGHT_TURN);
                    }
                    break;
                        
                case LINE_KIND_LEFT:
                    go_turn(speed,ALO_LEFT_TURN);
                    break;
                        
                case LINE_KIND_RIGHT:
                    go_turn(speed,ALO_RIGHT_TURN);
                    break;
                        
                default:
                    break;
            }

            error_flag=0;
                
        }
        //라인을 만나지 못했을 때
        else if(temp_line == GO_LOST)
        {
            
            chg_dir(BB);
			int target_P=0;

            if(error_flag==1) target_P=Line_Count - 2;
            else  target_P=Line_Count - 1;
            
            Line_Count = target_P;
            
            go_line(speed);
            push_line(speed);

            
            if(Mapping[target_P].kind==LINE_KIND_LEFT) 
            {
                go_turn(speed,ALO_RIGHT_TURN);
                Mapping[target_P].kind=LINE_KIND_NOT;           
                error_flag=1;
            }
            else if(Mapping[target_P].kind==LINE_KIND_RIGHT)
            {
                go_turn(speed,ALO_LEFT_TURN);
                Mapping[target_P].kind=LINE_KIND_NOT;
                error_flag=1;
            }
            else if(Mapping[target_P].kind==LINE_KIND_BOTH)
            {
                if(ALO==ALO_LEFT_TURN)
                {
                   Mapping[target_P].kind=LINE_KIND_RIGHT;
                       
                   go_turn(speed,ALO_RIGHT_TURN);
                   go_turn(speed,ALO_RIGHT_TURN);
                }
                else if(ALO==ALO_RIGHT_TURN)
                {
                   Mapping[target_P].kind=LINE_KIND_LEFT;

                   go_turn(speed,ALO_LEFT_TURN);
                   go_turn(speed,ALO_LEFT_TURN);
                }
                
                error_flag=0;
			}
			else if(Mapping[target_P].kind==LINE_KIND_NOT)
			{
				//Line_Count--;
				while(1)
				{
					Line_Count--;
					go_line(speed);
					push_line(speed);
					if(Mapping[Line_Count].kind==LINE_KIND_LEFT) {Mapping[Line_Count].kind=LINE_KIND_NOT; go_turn(speed,ALO_RIGHT_TURN); error_flag=1; break;}
					else if(Mapping[Line_Count].kind==LINE_KIND_RIGHT) {Mapping[Line_Count].kind=LINE_KIND_NOT; go_turn(speed,ALO_LEFT_TURN); error_flag=1; break;}	
					else if(Mapping[Line_Count].kind==LINE_KIND_BOTH)
	            	{
		                if(ALO==ALO_LEFT_TURN)
		                {     
		                   go_turn(speed,ALO_RIGHT_TURN);
		                   go_turn(speed,ALO_RIGHT_TURN);
		                }
		                else if(ALO==ALO_RIGHT_TURN)
		                {
		                   go_turn(speed,ALO_LEFT_TURN);
		                   go_turn(speed,ALO_LEFT_TURN);
		                }
						error_flag=0;
						break;
	            	}
				}			
			}
            chg_dir(FF);
            
        }
        //최종 지점을 만났을 때
        else if(temp_line == GO_FIN)
        {
            final_line_time=itimer2;
            break;
        }
        
        
    }
}

void find_home_safe(int ALO, int speed)
{
    chg_dir(BB);
	
    int i;
	int temp_speed=5;
    int first_turn=0;
    for(i=Line_Count-1;i>=0;i--)
    {
        int temp_turn=-1;
        if(Mapping[i].kind==LINE_KIND_NOT)
        {
			LINE_SERACH_ABSH
            line(lr1,20,0);
			push_line(speed);
			temp_turn=ALO_NOT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_LEFT)
        {
			LINE_SERACH_ABSH
            line(lr1,20,0);
			push_line(speed);
			temp_turn=ALO_RIGHT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_RIGHT)
        {
			LINE_SERACH_ABSH
            line(lr1,20,0);
			push_line(speed);
			temp_turn=ALO_LEFT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_BOTH)
        {
			LINE_SERACH_ABSH
            line(lr1,20,0);
			push_line(speed);
			if(ALO==ALO_LEFT_TURN)  temp_turn=ALO_RIGHT_TURN;
            else if(ALO==ALO_RIGHT_TURN) temp_turn=ALO_LEFT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_NONE)
        {
            //무시;
        }
        
		if(first_turn==0)
    	{
    		if(temp_turn==ALO_LEFT_TURN) {temp_turn=ALO_RIGHT_TURN; first_turn=1; chg_dir(FF);} 
    		else if(temp_turn==ALO_RIGHT_TURN) {temp_turn=ALO_LEFT_TURN; first_turn=1; chg_dir(FF);}
    	}
        go_turn(speed,temp_turn);

    }
    
	

   	char LINE_LOST_FLAG = 0;
    
	chg_absh(speed);
        
    while(1)
    {
        if (FW1&&FW2&&FW3&&FW4&&FW5&&FW6&&FW7)
        {
            // 라인을 하나도 못 볼 경우 딜레이 동안 다시 찾는다, 못 찾을 경우 GO_LOST 반환
            if(LINE_LOST_FLAG == 0)
            {
                LINE_LOST_FLAG=1;
                itimer1=0;
            }
            else if(itimer1>=100)
            {
                break;
            }
            
        }
        else LINE_LOST_FLAG = 0;
        
		linetracer(20);
    }
}


void find_home(int ALO, int speed)
{
    chg_dir(BB);
	
    int i;
	int temp_speed=20;
    int first_turn=0;
    for(i=Line_Count-1;i>=0;i--)
    {
		if(i==0) temp_speed==LINE_FAST_SPEED;

        int temp_turn=-1;
        if(Mapping[i].kind==LINE_KIND_NOT)
        {
            mline(all1,temp_speed,0);
			temp_turn=ALO_NOT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_LEFT)
        {
            mline(all1,LINE_FAST_SPEED,-1);
			temp_turn=ALO_RIGHT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_RIGHT)
        {
            mline(all1,LINE_FAST_SPEED,-1);
			temp_turn=ALO_LEFT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_BOTH)
        {
            mline(all1,LINE_FAST_SPEED,-1);
			if(ALO==ALO_LEFT_TURN)  temp_turn=ALO_RIGHT_TURN;
            else if(ALO==ALO_RIGHT_TURN) temp_turn=ALO_LEFT_TURN;
        }
        else if(Mapping[i].kind==LINE_KIND_NONE)
        {
            //무시;
        }
        
		if(first_turn==0)
    	{
    		if(temp_turn==ALO_LEFT_TURN) {temp_turn=ALO_RIGHT_TURN; first_turn=1; chg_dir(FF);} 
    		else if(temp_turn==ALO_RIGHT_TURN) {temp_turn=ALO_LEFT_TURN; first_turn=1; chg_dir(FF);}
    	}
        go_turn(speed,temp_turn);

    }
    
	

   	char LINE_LOST_FLAG = 0;
    
	chg_absh(20);
        
    while(1)
    {
        if (FW1&&FW2&&FW3&&FW4&&FW5&&FW6&&FW7)
        {
            // 라인을 하나도 못 볼 경우 딜레이 동안 다시 찾는다, 못 찾을 경우 GO_LOST 반환
            if(LINE_LOST_FLAG == 0)
            {
                LINE_LOST_FLAG=1;
                itimer1=0;
            }
            else if(itimer1>=100)
            {
                break;
            }
            
        }
        else LINE_LOST_FLAG = 0;
        
		linetracer(20);
    }
}

void go_turn(int speed, int kind)
{
    if (kind==ALO_LEFT_TURN)
    {
        //왼쪽턴 일 경우
		if(search_flag==1) ilt2(-TURN_FAST_SPEED-TURN_ADD_SPEED,TURN_FAST_SPEED,0);
		else 
		{
			lt2(TURN_NOMAL_SPEED,-1);
		}
		now_speed=5;
    }
    else if(kind==ALO_RIGHT_TURN)
    {
        //오른쪽턴 일 경우
		if(search_flag==1) irt2(TURN_FAST_SPEED,-TURN_FAST_SPEED-TURN_ADD_SPEED,0);
		else 
		{
			rt2(TURN_NOMAL_SPEED,-1);
		}
		now_speed=5;
    }
}


int go_line(int speed)
{
    char LINE_LOST_FLAG = 0;
    
	chg_absh(speed);
    if(speed==5) LINE_SERACH_ABSH;
    while(1)
    {
      	if (adc2>=psd_dis)
		{
	        // 최종 벽을 만났을 경우
	        return GO_FIN;
        }
        else if (FW1&&FW2&&FW3&&FW4&&FW5&&FW6&&FW7)
        {
            // 라인을 하나도 못 볼 경우 딜레이 동안 다시 찾는다, 못 찾을 경우 GO_LOST 반환
            if(LINE_LOST_FLAG == 0)
            {
                LINE_LOST_FLAG=1;
                itimer1=0;
            }
            else if(itimer1>=LINE_LOST_DELAY)
            {
                return GO_LOST;
            }
            
        }
        else if(FB1||FB7) return GO_MEET;
        else LINE_LOST_FLAG = 0;
        
        linetracer(20);
    }
    
}

int push_line(int speed)
{
    char LFlag=0, RFlag=0;
    
	chg_absh(speed);
    while(1)
    {
        //라인에서 벗어나면서 교차로를 확인한다.
        if (FW1&&FW7) break;
		if (FB1) LFlag=1;
        if (FB7) RFlag=1;
		linetracer(20);
    }

	chg_absh(speed);
	if(Robot_Dir==BB) {motor(20,20,LINE_PUSH_BACK_DELAY);}
	else motor(20,20,LINE_PUSH_DELAY);
 
    
    if(LFlag==1&&RFlag==1) return LINE_KIND_BOTH;
    else if(LFlag==1) return LINE_KIND_LEFT;
    else if(RFlag==1) return LINE_KIND_RIGHT;
    else return LINE_KIND_NOT;
}

void chg_dir(int CDir)
{
    Robot_Dir = CDir;
    dir(CDir);
}

