/**************************************
 
 ����Ʈ���̼� �̷� �ΰ�����
 
 ���� ���� : 2015,7,31
 
 
 
 **************************************/

#include "pemassi_g.h"

// ����Ʈ���̼� ũ�ν� ���� ����
#define LINE_KIND_LEFT              0
#define LINE_KIND_RIGHT             1
#define LINE_KIND_BOTH              2
#define LINE_KIND_NOT               3
#define LINE_KIND_NONE              4

// �˰��� ���� ����
#define ALO_LEFT_TURN               0
#define ALO_RIGHT_TURN              1
#define ALO_NOT_TURN                4

#define ALO_PSD                     0
#define ALO_BUTTON                  1

// ����Ʈ���̼� �ν� ���� ����
#define GO_LOST                     0
#define GO_MEET                     1
#define GO_FIN                      2

/* ����� ���� */
#define ALO_MODE                    0                   //�� ���� ���� ��� (0 - PSD 1 - Button)

#define TURN_NOMAL_SPEED            7                   //Ž���� �� �� �ӵ�
#define TURN_FAST_SPEED             8                   //���ƿ� �� �� �ӵ�
#define TURN_ADD_SPEED              4                   //���ƿ� �� �߰� �� �ӵ�

#define LINE_SERACH_SPEED           5                   //Ž���� �� �ӵ�
#define LINE_FAST_SPEED             16                  //���ƿ� �� �ӵ�
#define LINE_LOST_DELAY             50                  //���ην�Ʈ ������
#define LINE_PUSH_DELAY             200                 //Ž���� �� ������ �̴� ��
#define LINE_PUSH_BACK_DELAY        200                 //Ž���� �� �ڷ� �̴� ��
#define LINE_IGNORE_ALO             100                 //�˰��� �� �տ� ������ �ִ� ���� �Ǵ��ϴ� ������
#define LINE_SERACH_ABSH            absh(5,3,1,1,1);    //Ž���� �� ����̹�


/******************************************/
void find_line(int ALO, int speed);                      //�̷� ã��
void go_turn(int speed, int kind);                       //��
int go_line(int speed);                                  //����Ʈ���̽�
int push_line(int speed);                  	             //Ǫ��
void chg_dir(int CDir);                                  //���⺯��
void solve_map(int ALO, int speed);                      //�� Ǯ��
void find_home(int ALO, int speed);                      //������ġ ã�ư���
void find_home_safe(int ALO, int speed);                 //�������� ���ư���
/******************************************/

struct Map
{
    unsigned char kind;
    unsigned int time;
};

int Line_Count = -1;        //���� ī��Ʈ
struct Map Mapping[100];    //����
int Robot_Dir = FF;         //���� �κ� ����
int psd_dis=0;              //psd �Ÿ�
int final_line_time = 0;    //������ ���� �ð�
int search_flag = 0;        //Ž�� ��, ���ƿ��� �� �÷���(0 - Ž���� 1 - ���ƿ��� �� 2 - õõ�� ���ƿ��� ��)

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
    
    //�� ã�ư���
    if(temp_flag==0) {find_home(ALO,LINE_FAST_SPEED); search_flag=1;}
    else {find_home_safe(ALO,LINE_SERACH_SPEED); search_flag=2;}
}

void find_line(int ALO, int speed)
{
    int error_flag=0;
    while(1)
    {
        //����Ʈ���̼� �� ĭ ����
        int temp_line = 0; //���� ���
		
        itimer2=0;
                
	    temp_line = go_line(speed);
        
        Line_Count++;   //ī��Ʈ ����
		
		if(itimer2>LINE_IGNORE_ALO) error_flag=0;

        //������ ������ ��
        if (temp_line == GO_MEET)
        { 

            Mapping[Line_Count].kind = push_line(speed); //���� Ǫ�� & ������ Ȯ��
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
        //������ ������ ������ ��
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
        //���� ������ ������ ��
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
            //����;
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
            // ������ �ϳ��� �� �� ��� ������ ���� �ٽ� ã�´�, �� ã�� ��� GO_LOST ��ȯ
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
            //����;
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
            // ������ �ϳ��� �� �� ��� ������ ���� �ٽ� ã�´�, �� ã�� ��� GO_LOST ��ȯ
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
        //������ �� ���
		if(search_flag==1) ilt2(-TURN_FAST_SPEED-TURN_ADD_SPEED,TURN_FAST_SPEED,0);
		else 
		{
			lt2(TURN_NOMAL_SPEED,-1);
		}
		now_speed=5;
    }
    else if(kind==ALO_RIGHT_TURN)
    {
        //�������� �� ���
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
	        // ���� ���� ������ ���
	        return GO_FIN;
        }
        else if (FW1&&FW2&&FW3&&FW4&&FW5&&FW6&&FW7)
        {
            // ������ �ϳ��� �� �� ��� ������ ���� �ٽ� ã�´�, �� ã�� ��� GO_LOST ��ȯ
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
        //���ο��� ����鼭 �����θ� Ȯ���Ѵ�.
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

