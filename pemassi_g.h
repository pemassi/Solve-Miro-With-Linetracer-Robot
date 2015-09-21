/***********************************************************************************
/
/ Made by pemassi, Modify - 2015.07.13
/
/ init_absh() - ABSH 값 정렬 및 초기화
/
/ chg_absh(속도) - ABSH 변경
/
/ mline(종류,속도,브레이크) - 기본 라인트레이서
/
/ smline(종류,속도,브레이크) - 기본 라인트레이서 + 교차로 앞 까지만
/
/ uline(종류,최소속도,최대속도,브레이크) - 가속 라인트레이서
/
/ dline(종류,최소속도,최대속도,브레이크) - 감속 라인트레이서
/
/ suline(종류,최소속도,최대속도,브레이크) - 가속 라인트레이서 + 교차로 앞 까지만
/
/ sdline(종류,최소속도,최대속도,브레이크) - 감속 라인트레이서 + 교차로 앞 까지만
/
/ culine(종류,최소속도,최대속도,크로스브레이크,브레이크) - 가속 라인트레이서 + 크로스브레이크
/
/ cdline(종류,최소속도,최대속도,크로스브레이크,브레이크) - 감속 라인트레이서 + 크로스브레이크
/
/ cdline2(종류,최소속도,최대속도,딜레이,브레이크) - 감속 라인트레이서 + 딜레이 만큼 최대속도로 가다가 감속
/
/ chg_udt(딜레이) - 가속 딜레이 변경
/
/ chg_ddt(딜레이) - 감속 딜레이 변경
/
/ chg_utt(딜레이) / chg_dtt(딜레이) - 턴 가감속 딜레이 변경
/
/ udlt, udrt(최소속도, 최대속도, 브레이크) - 가감속 턴(3번센서가 검은색 볼 경우 감속 시작)
/
/ udline(교차로, 최소속도, 최대속도, 라인딜레이, 브레이크) - 가속 후 라인 딜레이 만큼 최대 속도로 주행 후 감속
/
/
***********************************************************************************/
/* 패치노트
/ 2014.11.21 - init_absh, chg_absh, uline, dline, uuline, ddline, aline, autoline 명령어 생성
/
/ 2014.11.26 - culine, cdline, cdline2, suline, sdline 생성
/              가속, 감속 중 라인을 볼 경우 가감속을 중단하는 조건 순서 변경 (if(count==1) break;)
/              라인 푸쉬 라인트레이서 조건 변경(4번 센서 -> 3,4,5번 센서)
/
/ 2014.11.29 - chg_udt, chg_ddt, chg_dtt, chg_utt, udlt, udrt, mline, smline, udline 생성
/
/ 2015.07.13 - 메모리 용량 최소화, 명령어 최소화
/
/
/
/
/
/
*/

///////////////////////////////////////////////////////////////////
// 라인트레이서 관련 선언


char absh_1[21];
char absh_2[21];
char absh_3[21];
char absh_4[21];
char absh_5[21];

// ABS 최대치
#define MAX_ABSH1 20
#define MAX_ABSH2 18
#define MAX_ABSH3 12
#define MAX_ABSH4 8
#define MAX_ABSH5 5


// ABS 최소치
#define MIN_ABSH1 5
#define MIN_ABSH2 3
#define MIN_ABSH3 0
#define MIN_ABSH4 0
#define MIN_ABSH5 0

// ABS 감속치
#define DC_ABSH1 1
#define DC_ABSH2 1
#define DC_ABSH3 1
#define DC_ABSH4 1
#define DC_ABSH5 1

// 가,감속 관련 딜레이
char UP_DELAY_TIME = 10;
char DOWN_DELAY_TIME = 10;
char UP_TRUN_TIME = 10;
char DOWN_TRUN_TIME = 10;

// 라인 무시 딜레이
char IGNORE_DELAY_TIME = 100;

// 현재 속도 & 가감속 플래그
#define UPDOWN_FLAG_NORMAL 0
#define UPDOWN_FLAG_FAST 1
#define UPDOWN_FLAG_SLOW 2
#define UPDOWN_FLAG_TRUN 3
#define UPDOWN_FLAG_START 4


#define all1 55
#define all2 66

//#define CU_DIR_F 0
//#define CU_DIR_B 1

char now_speed = 0;
char UPDOWN_FLAG = UPDOWN_FLAG_START; // 0 - 기본 / 1 - 가속 / 2 - 감속 / 3 - 턴 / 4 - 시작
//char CU_DIR = CU_DIR_F; // 방향 0 - 앞 / 1 - 뒤

//#define dff chg_dir(FF);
//#define dbb chg_dir(BB);

//////////////////////////////////////////////////////////////////
void init_absh();                                                                               //absh 세팅 초기화
void chg_absh(int sp);                                                                          //absh 변경
void dline(char kind, char s_speed, char speed,char breaks);                                    //감속 라인트레이싱
void uline(char kind, char s_speed, char speed, char breaks);                                   //가속 라인트레이싱
void culine(char kind, char s_speed, char speed, char crossbreaks, char breaks);                //크로스브레이크 가속 라인트레이싱
void cdline(char kind, char s_speed, char speed, char crossbreaks, char breaks);                //크로스브레이크 감속 라인트레이싱
void cdline2(char kind, char s_speed, char speed, char crossbreaks, char delays, char breaks);  //크로스브레이크 & 고속 + 감속 라인트레이싱
void suline(char kind, char s_speed, char speed, char breaks);                                  //가속 라인트레이싱(선보고 멈춤)
void sdline(char kind, char s_speed, char speed,char breaks);                                   //감속 라인트레이싱(선보고 멈춤)
void chg_dtt(char delays);                                                                      //감속 턴 딜레이 조절
void chg_udt(char delays);                                                                      //가속 턴 딜레이 조절
void chg_utt(char delays);                                                                      //가속 라인트레이싱 딜레이 조절
void chg_dtt(char delays);                                                                      //감속 라인트레이싱 딜레이 조절
void mline(char kind, char speed, char breaks);                                                 //일반 라인트레이싱
void smline(char kind, char speed, char breaks);                                                //일반 라인트레이싱(선보고 멈춤)
void udlt(char s_speed, char f_speed, char breaks);                                             //가감속 왼쪽 턴
void udrt(char s_speed, char f_speed, char breaks);                                             //가감속 오른쪽 턴
void linemotor(char delay,char speed);                                                          //라인&모터(라인이 있을 경우 라인을 탐)
//void chg_dir(char dirc);                                                                      //디렉션 변경
int check_front_sensor_or(char kind);                                                           //앞 센서 값 반환(or 형)
int check_front_sensor(char kind);                                                              //앞 센서 값 반환(and 형)
void Flinetrcaer(int speed);                                                                     //모터라인트레이싱(2,3,4번이 볼경우 라인트레이싱 이외에 wheel)
int core_dline(char kind, char s_speed, char speed);                                            //감속 라인트레이싱 코어
int core_uline(char kind, char s_speed, char speed);                                            //가속 라인트레이싱 코어
void absh_wheel(int speed);                                                                     //absh 적용된 wheel
void lostuline(char kind, char s_speed, char f_speed, char losttime, char breaks);				//가속 로스트 라인트레이싱

/*
void chg_dir(char dirc)
{
    if(dirc==FF)
    {
        CU_DIR = CU_DIR_F; dir(FF);
    }
    else if(dirc==BB)
    {
        CU_DIR = CU_DIR_B; dir(BB);
    }
}
*/

void chg_utt(char delays)
{
    UP_TRUN_TIME=delays;
}

void chg_dtt(char delays)
{
    DOWN_TRUN_TIME=delays;
}

void chg_ddt(char delays)
{
    DOWN_DELAY_TIME=delays;
}

void chg_udt(char delays)
{
    UP_DELAY_TIME=delays;
}

void init_absh()
{
	int i;
    
	char absh1=MAX_ABSH1;
	char absh2=MAX_ABSH2;
	char absh3=MAX_ABSH3;
	char absh4=MAX_ABSH4;
	char absh5=MAX_ABSH5;
	
	
	for(i=20;i>=1;i--)
	{
		absh_1[i] = absh1;
		absh_2[i] = absh2;
		absh_3[i] = absh3;
		absh_4[i] = absh4;
		absh_5[i] = absh5;

		if(absh1>MIN_ABSH1) absh1-=DC_ABSH1; 
		if(absh2>MIN_ABSH2) absh2-=DC_ABSH2;
		if(absh3>MIN_ABSH3) absh3-=DC_ABSH3;
		if(absh4>MIN_ABSH4) absh4-=DC_ABSH4;
		if(absh5>MIN_ABSH5) absh5-=DC_ABSH5;
        
        if(absh1<MIN_ABSH1) absh1=MIN_ABSH1;
        if(absh1<MIN_ABSH2) absh1=MIN_ABSH2;
        if(absh1<MIN_ABSH3) absh1=MIN_ABSH3;
        if(absh1<MIN_ABSH4) absh1=MIN_ABSH4;
        if(absh1<MIN_ABSH5) absh1=MIN_ABSH5;
        
		if(absh1<0) absh1=0;
		if(absh2<0) absh2=0;
		if(absh3<0) absh3=0;
		if(absh4<0) absh4=0;
		if(absh5<0) absh5=0;
	}
}

void chg_absh(int sp)
{
	absh(absh_1[sp],absh_2[sp],absh_3[sp],absh_4[sp],absh_5[sp]);
}

void lostuline(char kind, char s_speed, char f_speed, char losttime, char breaks)
{
    char i=s_speed;
    char count=0;       //크로스 만남 여부 플래그
    char lost=0;
    
    /* 드라이버를 변경하며 'UP_DELAY_TIME' 딜레이 만큼 천천히 가속한다 */
    for(i=s_speed;i<=f_speed;i++)
    {
        chg_absh(i);        //드라이버 변경
        itimer1=0;          //타이머 리셋
        
        while(itimer1<=UP_DELAY_TIME) //타이머가 UP_DELAY_TIME 보다 작을 동안 반복
        {
            /* 주행 중 크로스를 본 경우 */
            if(FW1&&FW2&&FW3&&FW4&&FW5&&FW6&&FW7)
            {
                if(lost==0)
                {
                    lost=1;
                    itimer3=0;
                }
                else
                {
                    if(itimer3>losttime)
                    {
                        count=1;
                        break;
                    }
                }
            }
            else if(check_front_sensor(kind))
            {
                count=1;
                break;
            }
            else lost=0;
                
            linetracer(i);
            servo5(now_speed*3);
            
        }
        
        if(count==1) break;
    }
    
    if(count==0) //주행 중 라인을 못 본 경우 계속 라인트레이서
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);
            
            servo5(now_speed*3);
            
        }
    }
    
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(i);
    }
    
    linemotor(breaks,i);
    
    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_FAST;
    abs_ratio(20,20);
    wheel(0,0);
}

int udline(char kind, char s_speed, char speed, char delays, char breaks)
{
    char i=s_speed; char count=0;
    
    for(i=s_speed;i<=speed;i++)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=UP_DELAY_TIME) //UP_DELAY_TIME 만큼 천천히 가속
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //가속 중 라인을 보면 파괴
            }
            else linetracer(i);
        }
        
        if(count==1) break;
    }
    
    if(count==1)
    {
        while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
        {
            Flinetrcaer(i);
        }
        
        linemotor(i,breaks);
        
        return 0;
    }
    
    itimer1=0;
    while(itimer1<=delays)
    {
        if(check_front_sensor(kind)) {count=1; break;}
        else linetracer(i);
    }
    
    if(count==1)
    {
        while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
        {
            Flinetrcaer(i);
        }
        
        linemotor(i,breaks);
        
        return 0;
    }
    
    for(;i>=s_speed;i--)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=DOWN_DELAY_TIME) //DOWN_DELAY_TIME 만큼 천천히 가속
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //감속 중 라인을 보면 파괴
            }
            else linetracer(i);
        }
        
        if(count==1) break;
        
    }
    
    if(count==0) //감속 중 라인을 못 본 경우 계속 라인트레이서
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);
        }
    }
    
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(i);
    }
    
    linemotor(i,breaks);
    
	return 0;
}

void cdline2(char kind, char s_speed, char speed, char crossbreaks, char delays, char breaks)
{
    itimer1=0; char count=0;
    while(itimer1<=delays)
    {
        if(check_front_sensor(kind)) count=1;
        linetracer(speed);
    }
    
    if(count==0) cdline(kind,s_speed,speed,crossbreaks,breaks);
    else
    {
        while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
        {
            Flinetrcaer(crossbreaks);
        }

		wheel(0,0);
    }
}

void culine(char kind, char s_speed, char speed, char crossbreaks, char breaks)
{
    int i = core_uline(kind,s_speed,speed);
    
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(crossbreaks);
    }
    
    linemotor(breaks,crossbreaks);
    
    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_FAST;
    abs_ratio(20,20);
    wheel(0,0);
    
}

void cdline(char kind, char s_speed, char speed, char crossbreaks, char breaks)
{
    int i = core_dline(kind,s_speed,speed);
    
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(crossbreaks);
    }
    
    linemotor(breaks,crossbreaks);
    
    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_FAST;
    abs_ratio(20,20);
    wheel(0,0);
    
}

void suline(char kind, char s_speed, char speed, char breaks)
{
    int i = core_uline(kind,s_speed,speed);
    
    linemotor(breaks,i);
    
    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_FAST;
    wheel(0,0);
    
}

void sdline(char kind, char s_speed, char speed, char breaks)
{
    int i = core_dline(kind,s_speed,speed);
    
    linemotor(breaks,i);
    
    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_SLOW;
    abs_ratio(20,20);
    wheel(0,0);
}

void dline(char kind, char s_speed, char speed, char breaks)
{
    int i = core_dline(kind,s_speed,speed);
    
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(i);
    }
	
    linemotor(breaks,i);

    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_SLOW;
    abs_ratio(20,20);
	wheel(0,0);
}

void uline(char kind, char s_speed, char speed, char breaks)
{

	int i = core_uline(kind,s_speed,speed);
	 
    while(check_front_sensor_or(kind)) //라인을 본 경우 다음 라인을 위해 넘어간다.
    {
        Flinetrcaer(i);
    }
	
    linemotor(breaks,i);

    now_speed = i;
    UPDOWN_FLAG=UPDOWN_FLAG_FAST;
    abs_ratio(20,20);
	wheel(0,0);

}

void mline(char kind, char speed, char breaks)
{
    
    if(now_speed==speed)
    {
        chg_absh(speed);
        line(lr1,speed,0);
        linemotor(breaks,speed);
    }
    else if(now_speed<speed)//현재 속도가 원하는 속도보다 작을 경우 가속
    {
        uline(kind,now_speed,speed,breaks);   
    }
    else if(now_speed>speed)//현재 속도가 원하는 속도보다 작을 경우 감속
    {
        cdline(kind,speed,now_speed,10,breaks);
    }
    
    UPDOWN_FLAG=UPDOWN_FLAG_NORMAL;
    //abs_ratio(20,20);
    //wheel(0,0);
}

void smline(char kind, char speed, char breaks)
{
    if(now_speed==speed)
    {
        chg_absh(speed);
        
        int temp=0;
        
        switch (kind) {
            case t1:
                temp = S1+S7;
                break;
            case l1:
                temp = S1;
                break;
            case r1:
                temp = S7;
                break;
        }
        
        sline(temp,speed,0);
        linemotor(breaks,speed);
    }
    else if(now_speed<speed)//현재 속도가 원하는 속도보다 작을 경우 가속
    {
        
        suline(kind,now_speed,speed,breaks);
        
    }
    else if(now_speed>speed)//현재 속도가 원하는 속도보다 작을 경우 감속
    {
        sdline(kind,speed,now_speed,breaks);
    }
    
    UPDOWN_FLAG=UPDOWN_FLAG_NORMAL;
    abs_ratio(20,20);
    wheel(0,0);
}

void udlt(char s_speed, char f_speed, char breaks)
{
    int i; char count=0; char count2=0;
    
    for(i=s_speed;i<=f_speed;i++)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
        {
            if(FB1)
            {
                count=1;
                break;
            }
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(-i,i);
        }
        if(count==1) break;
        
    }
    
    if(count==1)
    {
        for(;i<=f_speed;i++)
        {
            chg_absh(i);
            itimer1=0;
            
            while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
            {
                if(FB2)
                {
                    count2=1;
                    break;
                }
                abs_ratio(20-absh_1[i],20-absh_1[i]);
                wheel(-i,i);
            }
            if(count2==1) break;
            
        }
    }
    else
    {
        while(1)
        {
            if(FB3) {count2=1; break;}
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(-i,i);
        }
    }
    
    if(count2==0)
    {
        while(1)
        {
            if(FB3) break;
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(-i,i);
        }
    }
    
    while(1)
    {
        if(FB3) break;
        abs_ratio(20-absh_1[i],20-absh_1[i]);
        wheel(-i,i);
    }
    
    for(;i>=s_speed;i--)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=DOWN_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
        {
            if(FB4)
            {
                count2=1;
                break;
            }
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(-i,i);
        }
        if(count2==1) break;
        
    }
    
    if(breaks==0);
    else if(breaks<0) motor(-i,i,-breaks);
    else if(breaks>0) motor(i,-i,breaks);
    
    now_speed=0;
    UPDOWN_FLAG=UPDOWN_FLAG_TRUN;
    abs_ratio(20,20);
    wheel(0,0);
}

void udrt(char s_speed, char f_speed, char breaks)
{
    int i; char count=0; char count2=0;
    
    for(i=s_speed;i<=f_speed;i++)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
        {
            if(FB7)
            {
                count=1;
                break;
            }
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(i,-i);
        }
        if(count==1) break;
        
    }
    
    if(count==1)
    {
        for(;i<=f_speed;i++)
        {
            chg_absh(i);
            itimer1=0;
            
            while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
            {
                if(FB6)
                {
                    count2=1;
                    break;
                }
                abs_ratio(20-absh_1[i],20-absh_1[i]);
                wheel(i,-i);
            }
            if(count2==1) break;
            
        }
    }
    else
    {
        while(1)
        {
            if(FB6) {count2=1; break;}
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(i,-i);
        }
    }
    
    if(count2==0)
    {
        while(1)
        {
            if(FB6) break;
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(i,-i);
        }
    }
    
    while(1)
    {
        if(FB5) break;
        abs_ratio(20-absh_1[i],20-absh_1[i]);
        wheel(i,-i);
    }
    
    for(;i>=s_speed;i--)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=DOWN_TRUN_TIME) //UP_TRUN_TIME 만큼 천천히 가속
        {
            if(FB4)
            {
                count2=1;
                break;
            }
            abs_ratio(20-absh_1[i],20-absh_1[i]);
            wheel(i,-i);
        }
        if(count2==1) break;
        
    }
    
    if(breaks==0);
    else if(breaks<0) motor(i,-i,-breaks);
    else if(breaks>0) motor(-i,i,breaks);
    
    now_speed=0;
    UPDOWN_FLAG=UPDOWN_FLAG_TRUN;
    abs_ratio(20,20);
    wheel(0,0);
}

void stline(char s_speed, char f_speed, char delay)
{
    int i; int count=0;
    for(i=s_speed;i<=f_speed;i++)
    {
        chg_absh(i);
        itimer1=0;
        while(itimer1<=delay)
        {
            linetracer(i);
            if(FB1||FB7) {count=1; break;}
        }
        if(count==1) break;
    }
}

void linemotor(char delays, char speed)
{
    if (delays==0);
    else if (delays<0) motor(-speed,-speed,-delays);
    else
    {
        itimer1=0;
        while(itimer1<delays)
        {
            Flinetrcaer(speed);
        }
    }
}

void Flinetrcaer(int speed)
{
    if(FB3||FB4||FB5) linetracer(speed); //3,4,5번 센서가 라인을 보고 있으면 트레이서
    else
    {
        //안보고 있다면 wheel로 푸쉬
        absh_wheel(speed);
    }
}

int check_front_sensor(char kind)
{
    switch (kind) {
        case t1:
            if(FB1&&FB7) return 1;
            else return 0;
            break;
            
        case l1:
            if(FB1) return 1;
            else return 0;
            break;
            
        case r1:
            if(FB7) return 1;
            else return 0;
            break;
            
        case t2:
            if(FB1&&FB2&&FB6&&FB7) return 1;
            else return 0;
            break;
            
        case l2:
            if(FB1&&FB2) return 1;
            else return 0;
            break;
            
        case r2:
            if(FB6&&FB7) return 1;
            else return 0;
            break;
            
        case all1:
            if(FB1||FB7) return 1;
            else return 0;
            break;
            
        case all2:
            if((FB1&&FB2)||(FB6&&FB7)) return 1;
            else return 0;
            break;
     }
	return -1;
}

int check_front_sensor_or(char kind)
{
    switch (kind) {
        case t1:
            if(FB1||FB7) return 1;
            else return 0;
            break;
            
        case l1:
            if(FB1) return 1;
            else return 0;
            break;
            
        case r1:
            if(FB7) return 1;
            else return 0;
            break;
            
        case t2:
            if((FB1&&FB2)||(FB6&&FB7)) return 1;
            else return 0;
            break;
            
        case l2:
            if(FB1||FB2) return 1;
            else return 0;
            break;
            
        case r2:
            if(FB6||FB7) return 1;
            else return 0;
            break;
            
        case all1:
            if(FB1||FB7) return 1;
            else return 0;
            break;
            
        case all2:
            if((FB1&&FB2)||(FB6&&FB7)) return 1;
            else return 0;
            break;
    }

	return -1;
}

int core_dline(char kind, char s_speed, char speed)
{
    char i=speed; char count=0;
    
    for(i=speed;i>=s_speed;i--)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=DOWN_DELAY_TIME) //DOWN_DELAY_TIME 만큼 천천히 가속
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //감속 중 라인을 보면 파괴
            }
            else linetracer(i);
        }
        
        if(count==1) break;
        
    }
    
    if(count==0) //감속 중 라인을 못 본 경우 계속 라인트레이서
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);
        }
    }

	return i;
}

int core_uline(char kind, char s_speed, char speed)
{

    char i=s_speed; char count=0;
    
    for(i=s_speed;i<=speed;i++)
    {
        chg_absh(i);
        itimer1=0;
        
        while(itimer1<=UP_DELAY_TIME) //UP_DELAY_TIME 만큼 천천히 가속
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //가속 중 라인을 보면 파괴
            }
            else linetracer(20);
        }
        
        if(count==1) break;
    }
    
    if(count==0) //가속 중 라인을 못 본 경우 계속 라인트레이서
    {
        while(!check_front_sensor(kind))
        {
            linetracer(20);
        }
    }

	return i;
}

void absh_wheel(int speed)
{
    abs_ratio(20-absh_1[speed],20-absh_1[speed]);
    wheel(speed,speed);
}
