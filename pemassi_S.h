/**************************************
 
 라인트레이서 미로 인공지능
 
 최종 수정 : 2015,7,31
 
 Made By 프매씨(ruddbs5301@naver.com)
 
 **************************************/

#include "pemassi_g.h"                                  //라인트레이서 주행 관련 전처리

/**********************************************************************************************************
    참고
    - 이 소스는 프로보의 JAGUAR 보드를 기준으로 작성되었습니다.
    - 이외의 보드는 참고용으로 사용해주세요.
    - 7조 센서 앞, 뒤 모두 사용합니다.
    - PSD, 터치센서는 IN포트 1번에 연결해서 사용해주세요.
    - 본 오픈소스를 수정하여 배포할 경우 제작자 이름을 남겨주세요.
 **********************************************************************************************************/

/**********************************************************************************************************
    사용자 설정
    - 알고리즘 방식이나 주행 속도 등을 수정, 조절하려면 아래 값들을 수정하세요.
 **********************************************************************************************************/

// 턴 지점 감지 방식 - PSD/BUTTON
#define ALO_MODE                    ALO_PSD             //턴 지점 감지 방식 (PSD - ALO_PSD  Button - ALO_BUTTON)

// 회전 속도
#define TURN_NOMAL_SPEED            7                   //탐색할 때 턴 속도
#define TURN_FAST_SPEED             8                   //돌아올 때 턴 속도
#define TURN_ADD_SPEED              4                   //돌아올 때 추가 턴 속도(양쪽 턴 속도가 같게 하려면 0을 대입)

// 라인트레이싱 속도
#define LINE_START_SPEED            5                   //빠른 라인트레이싱 시 시작 속도
#define LINE_SERACH_SPEED           5                   //탐색할 때 속도
#define LINE_FAST_SPEED             16                  //돌아올 때 속도

// 로스트 딜레이 - 라인을 잃었다고 판단하는 데에 걸리는 시간 입니다.
#define LINE_LOST_DELAY             50                  //라인로스트 딜레이

// 푸쉬 딜레이 - 대체로 라인의 두께를 넘어가는 데에 걸리는 시간 입니다.
#define LINE_PUSH_DELAY             200                 //탐색할 때 앞으로 미는 값
#define LINE_PUSH_BACK_DELAY        200                 //탐색할 때 뒤로 미는 값

// 라인 무시 딜레이 - 다음 교차로로 이동하는 데에 설정된 시간보다 더 걸릴 경우 다음 칸에 라인이 있다고 판단.
#define LINE_IGNORE_ALO             100                 //알고리즘 상 앞에 라인이 있는 것을 판단하는 딜레이

// 탐색 드라이버 - 탐색할 때 사용되는 드라이버(JAGUAR 전용)
#define LINE_SERACH_ABSH            absh(5,3,1,1,1);    //탐색할 때 드라이버

/**********************************************************************************************************
    각종 상수 정의
    - 아래 값들은 수정하면 안됩니다.
 **********************************************************************************************************/

// 라인트레이서 크로스 관련 정의
#define LINE_KIND_LEFT              0                   //왼쪽 교차로
#define LINE_KIND_RIGHT             1                   //오른쪽 교차로
#define LINE_KIND_BOTH              2                   //양쪽 교차로
#define LINE_KIND_NOT               3                   //라인이 끊김
#define LINE_KIND_NONE              4                   //교차로가 없으나, 라인이 끊기지 않음

// 알고리즘 관련 정의
#define ALO_LEFT_TURN               0                   //왼쪽 턴
#define ALO_RIGHT_TURN              1                   //오른쪽 턴
#define ALO_NOT_TURN                4                   //턴을 하지 않음

#define ALO_PSD                     0                   //PSD로 턴 지점을 감지함
#define ALO_BUTTON                  1                   //터치센서로 턴 지점을 감지함

// 라인트레이서 인식 관련 정의
#define GO_LOST                     0                   //라인이 끊김
#define GO_MEET                     1                   //교차로를 만남
#define GO_FIN                      2                   //턴 지점을 감지함

// 턴 지점 감지 관련 정의
#define ALO_PSD                     0                   //PSD를 사용하는 경우
#define ALO_BUTTON                  1                   //터치센서를 사용하는 경우

/**********************************************************************************************************/
void find_line(int ALO, int speed);                     //미로 찾기
void go_turn(int speed, int kind);                      //턴
int go_line(int speed);                                 //라인트레이싱
int push_line(int speed);                  	            //푸싱
void chg_dir(int CDir);                                 //방향변경
void solve_map(int ALO, int speed);                     //맵 해석
void find_home(int ALO, int speed);                     //시작위치로 돌아가기
void find_home_safe(int ALO, int speed);                //시작위치로 천천히 돌아가기
int check_turnPoint(int MODE);                          //턴 지점 체크
/**********************************************************************************************************/

struct Map
{
    unsigned char kind;     //각 교차로의 정보를 담음
    unsigned int time;      //각 교차로 사이에 다니는 시간을 담음
};

int Line_Count = -1;        //라인 카운트
struct Map Mapping[100];    //맵핑
int Robot_Dir = FF;         //현재 로봇 방향
int psd_dis=0;              //psd 거리
int final_line_time = 0;    //마지막 라인 시간
int search_flag = 0;        //탐색 중, 돌아오는 중 플래그(0 - 탐색중 1 - 돌아오는 중 2 - 천천히 돌아오는 중)

void solve_map(int ALO, int speed)
{
    //로봇의 방향을 앞으로 전환
    chg_dir(FF);
    
    //맵핑을 초기화 한다.
    int i;
    for(i=0;i<=100;i++)
    {
        Mapping[i].kind=LINE_KIND_NONE;
        Mapping[i].time=0;
    }
    
    //로봇을 시작한 뒤 1초 내로 스타트 버튼을 누른다면 탐색 후 돌아올 때 천천히 돌아온다. 누르지 않을 경우 빠르게 돌아옴.
	int temp_flag=0;
    itimer1=0;
    while(itimer1<1000)
    {
        if(START_KEY) {temp_flag=1; break;}
    }

    //들리는 비프음 갯수로 모드를 판단. (2번 빠른 모드, 3번 느린 모드)
    if(temp_flag==0) buzzer(2,100,100);
    else buzzer(3,100,100);
   
    //PSD모드를 사용할 경우 턴 지점의 물체와의 거리를 측정한다.
	if(ALO_MODE==ALO_PSD)
    {
        while(1)
        {
            //턴 지점과 원하는 거리에 로봇을 둔 후 스타트 버튼을 눌러 측정한다.
            if(START_KEY)
            {
                delay(300);
                psd_dis=adc1;       //현재 1번 IN포트 값을 불러온다.
                buzzer(2,100,100);
                break;
            }
        }
    }

	delay(500);
 
   	restart(1);

    //맵을 탐색한다.
    find_line(ALO,LINE_SERACH_SPEED);
    
    //로봇의 방향을 뒤로 전환
    chg_dir(BB);
    
    //턴 지점을 만났다면 다시 돌아간다.
    if(temp_flag==0) {find_home(ALO,LINE_FAST_SPEED); search_flag=1;}
    else {find_home_safe(ALO,LINE_SERACH_SPEED); search_flag=2;}
}

void find_line(int ALO, int speed)
{
    int error_flag=0;   //카운트를 얼마나 감소할지 판단하는 데에 필요한 함수
    while(1)
    {
        /* 라인트레이서 한 칸 시작 */
        
        int temp_line = 0;  //라인 결과
        itimer2=0;          //다음 교차로로 가는 동안 걸린 시간
        
        //다음 교차로로 이동한다.
	    temp_line = go_line(speed);
        
        Line_Count++;   //카운트 증가
		
        //다음 교차로로 가는 데 만약 LINE_IGNORE_ALO 보다 적게 걸리면 오류 플래그 0을 세운다.
        //(다음 칸에 선이 없다고 판단하는 데에 사용)
		if(itimer2>LINE_IGNORE_ALO) error_flag=0;

        //라인을 만났을 때
        if (temp_line == GO_MEET)
        { 

            Mapping[Line_Count].kind = push_line(speed);    //라인 푸쉬 & 교차로 확인
            Mapping[Line_Count].time = itimer2;             //다음 교차로로 이동하는 데에 걸리는 시간을 저장
            
            //교차로의 종류에 따라 턴 방향을 결정.
            //양쪽일 경우 우선 턴 방향으로 턴을 한다.
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

            //오류 플래그 0
            error_flag=0;
                
        }
        //라인을 만나지 못했을 때
        else if(temp_line == GO_LOST)
        {
            
            //로봇의 방향을 뒤로 바꾼다.
            chg_dir(BB);
            
			int target_P=0;

            //오류 플래그가 1 일경우 2번째 전의 맵핑을 지정한다.
            //오류 플래그가 0 일경우 1번째 전의 맵핑을 지정한다.
            if(error_flag==1) target_P=Line_Count - 2;
            else  target_P=Line_Count - 1;
            
            //오류난 맵핑을 무시하고, 라인카운트를 변경
            Line_Count = target_P;
            
            //전 칸으로 이동한다.
            go_line(speed);
            push_line(speed);

            //지정된 맵핑의 턴 방향의 반대로 턴을 한다.
            if(Mapping[target_P].kind==LINE_KIND_LEFT) 
            {
                go_turn(speed,ALO_RIGHT_TURN);
                Mapping[target_P].kind=LINE_KIND_NOT;       //있었던 교차로는 오류이기 때문에 맵핑에서 지운다.
                
                //만약 다시 라인을 잃을 경우 2번째 전의 맵핑을 살펴봐야 하기 때문에 오류플래그 1을 세운다.
                error_flag=1;
            }
            else if(Mapping[target_P].kind==LINE_KIND_RIGHT)
            {
                go_turn(speed,ALO_LEFT_TURN);
                Mapping[target_P].kind=LINE_KIND_NOT;       //있었던 교차로는 오류이기 때문에 맵핑에서 지운다.
                
                //만약 다시 라인을 잃을 경우 2번째 전의 맵핑을 살펴봐야 하기 때문에 오류플래그 1을 세운다.
                error_flag=1;
            }
            else if(Mapping[target_P].kind==LINE_KIND_BOTH)
            {
                //양쪽 교차로였던 경우 우선 순위에 따라 한쪽 교차로를 지운다.
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
				//지정된 맵핑의 교차로가 직선인 경우 교차로가 있는 위치까지 반복하여 돌아간다.
				while(1)
				{
					Line_Count--;
                    
					go_line(speed);
					push_line(speed);
					
                    if(Mapping[Line_Count].kind==LINE_KIND_LEFT)
                    {
                        Mapping[Line_Count].kind=LINE_KIND_NOT;
                        go_turn(speed,ALO_RIGHT_TURN);
                        
                        error_flag=1;
                    
                        break;
                    }
					else if(Mapping[Line_Count].kind==LINE_KIND_RIGHT)
                    {
                        Mapping[Line_Count].kind=LINE_KIND_NOT;
                        go_turn(speed,ALO_LEFT_TURN);
                        
                        error_flag=1;
                        
                        break;
                    }
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
            final_line_time=itimer2;    //마지막 교차로까지 걸린 시간을 저장한다.
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
            //무시
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
		now_speed=LINE_START_SPEED;
    }
    else if(kind==ALO_RIGHT_TURN)
    {
        //오른쪽턴 일 경우
		if(search_flag==1) irt2(TURN_FAST_SPEED,-TURN_FAST_SPEED-TURN_ADD_SPEED,0);
		else 
		{
			rt2(TURN_NOMAL_SPEED,-1);
		}
		now_speed=LINE_START_SPEED;
    }
}


int go_line(int speed)
{
    char LINE_LOST_FLAG = 0;
    
	chg_absh(speed);
    
    while(1)
    {
      	if (check_turnPoint(ALO_MODE))
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

int check_turnPoint(int MODE)
{
    if(MODE==ALO_PSD)
    {
        if (adc1>=psd_dis) return 1;
        else return 0;
    }
    else if(MODE==ALO_BUTTON)
    {
        if (IN1) retrun 1;
        else return 0;
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
	if(Robot_Dir==BB) motor(20,20,LINE_PUSH_BACK_DELAY);
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

