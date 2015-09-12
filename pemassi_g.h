/***********************************************************************************
/
/ Made by pemassi, Modify - 2015.07.13
/
/ init_absh() - ABSH �� ���� �� �ʱ�ȭ
/
/ chg_absh(�ӵ�) - ABSH ����
/
/ mline(����,�ӵ�,�극��ũ) - �⺻ ����Ʈ���̼�
/
/ smline(����,�ӵ�,�극��ũ) - �⺻ ����Ʈ���̼� + ������ �� ������
/
/ uline(����,�ּҼӵ�,�ִ�ӵ�,�극��ũ) - ���� ����Ʈ���̼�
/
/ dline(����,�ּҼӵ�,�ִ�ӵ�,�극��ũ) - ���� ����Ʈ���̼�
/
/ suline(����,�ּҼӵ�,�ִ�ӵ�,�극��ũ) - ���� ����Ʈ���̼� + ������ �� ������
/
/ sdline(����,�ּҼӵ�,�ִ�ӵ�,�극��ũ) - ���� ����Ʈ���̼� + ������ �� ������
/
/ culine(����,�ּҼӵ�,�ִ�ӵ�,ũ�ν��극��ũ,�극��ũ) - ���� ����Ʈ���̼� + ũ�ν��극��ũ
/
/ cdline(����,�ּҼӵ�,�ִ�ӵ�,ũ�ν��극��ũ,�극��ũ) - ���� ����Ʈ���̼� + ũ�ν��극��ũ
/
/ cdline2(����,�ּҼӵ�,�ִ�ӵ�,������,�극��ũ) - ���� ����Ʈ���̼� + ������ ��ŭ �ִ�ӵ��� ���ٰ� ����
/
/ chg_udt(������) - ���� ������ ����
/
/ chg_ddt(������) - ���� ������ ����
/
/ chg_utt(������) / chg_dtt(������) - �� ������ ������ ����
/
/ udlt, udrt(�ּҼӵ�, �ִ�ӵ�, �극��ũ) - ������ ��(3�������� ������ �� ��� ���� ����)
/
/ udline(������, �ּҼӵ�, �ִ�ӵ�, ���ε�����, �극��ũ) - ���� �� ���� ������ ��ŭ �ִ� �ӵ��� ���� �� ����
/
/
***********************************************************************************/
/* ��ġ��Ʈ
/ 2014.11.21 - init_absh, chg_absh, uline, dline, uuline, ddline, aline, autoline ��ɾ� ����
/
/ 2014.11.26 - culine, cdline, cdline2, suline, sdline ����
/              ����, ���� �� ������ �� ��� �������� �ߴ��ϴ� ���� ���� ���� (if(count==1) break;)
/              ���� Ǫ�� ����Ʈ���̼� ���� ����(4�� ���� -> 3,4,5�� ����)
/
/ 2014.11.29 - chg_udt, chg_ddt, chg_dtt, chg_utt, udlt, udrt, mline, smline, udline ����
/
/ 2015.07.13 - �޸� �뷮 �ּ�ȭ, ��ɾ� �ּ�ȭ
/
/
/
/
/
/
*/

///////////////////////////////////////////////////////////////////
// ����Ʈ���̼� ���� ����


char absh_1[21];
char absh_2[21];
char absh_3[21];
char absh_4[21];
char absh_5[21];

// ABS �ִ�ġ
#define MAX_ABSH1 20
#define MAX_ABSH2 18
#define MAX_ABSH3 12
#define MAX_ABSH4 8
#define MAX_ABSH5 5


// ABS �ּ�ġ
#define MIN_ABSH1 5
#define MIN_ABSH2 3
#define MIN_ABSH3 0
#define MIN_ABSH4 0
#define MIN_ABSH5 0

// ABS ����ġ
#define DC_ABSH1 1
#define DC_ABSH2 1
#define DC_ABSH3 1
#define DC_ABSH4 1
#define DC_ABSH5 1

// ��,���� ���� ������
char UP_DELAY_TIME = 10;
char DOWN_DELAY_TIME = 10;
char UP_TRUN_TIME = 10;
char DOWN_TRUN_TIME = 10;

// ���� ���� ������
char IGNORE_DELAY_TIME = 100;

// ���� �ӵ� & ������ �÷���
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
char UPDOWN_FLAG = UPDOWN_FLAG_START; // 0 - �⺻ / 1 - ���� / 2 - ���� / 3 - �� / 4 - ����
//char CU_DIR = CU_DIR_F; // ���� 0 - �� / 1 - ��

//#define dff chg_dir(FF);
//#define dbb chg_dir(BB);

//////////////////////////////////////////////////////////////////
void init_absh();                                                                               //absh ���� �ʱ�ȭ
void chg_absh(int sp);                                                                          //absh ����
void dline(char kind, char s_speed, char speed,char breaks);                                    //���� ����Ʈ���̽�
void uline(char kind, char s_speed, char speed, char breaks);                                   //���� ����Ʈ���̽�
void culine(char kind, char s_speed, char speed, char crossbreaks, char breaks);                //ũ�ν��극��ũ ���� ����Ʈ���̽�
void cdline(char kind, char s_speed, char speed, char crossbreaks, char breaks);                //ũ�ν��극��ũ ���� ����Ʈ���̽�
void cdline2(char kind, char s_speed, char speed, char crossbreaks, char delays, char breaks);  //ũ�ν��극��ũ & ��� + ���� ����Ʈ���̽�
void suline(char kind, char s_speed, char speed, char breaks);                                  //���� ����Ʈ���̽�(������ ����)
void sdline(char kind, char s_speed, char speed,char breaks);                                   //���� ����Ʈ���̽�(������ ����)
void chg_dtt(char delays);                                                                      //���� �� ������ ����
void chg_udt(char delays);                                                                      //���� �� ������ ����
void chg_utt(char delays);                                                                      //���� ����Ʈ���̽� ������ ����
void chg_dtt(char delays);                                                                      //���� ����Ʈ���̽� ������ ����
void mline(char kind, char speed, char breaks);                                                 //�Ϲ� ����Ʈ���̽�
void smline(char kind, char speed, char breaks);                                                //�Ϲ� ����Ʈ���̽�(������ ����)
void udlt(char s_speed, char f_speed, char breaks);                                             //������ ���� ��
void udrt(char s_speed, char f_speed, char breaks);                                             //������ ������ ��
void linemotor(char delay,char speed);                                                          //����&����(������ ���� ��� ������ Ž)
//void chg_dir(char dirc);                                                                      //�𷺼� ����
int check_front_sensor_or(char kind);                                                           //�� ���� �� ��ȯ(or ��)
int check_front_sensor(char kind);                                                              //�� ���� �� ��ȯ(and ��)
void Flinetrcaer(int speed);                                                                     //���Ͷ���Ʈ���̽�(2,3,4���� ����� ����Ʈ���̽� �̿ܿ� wheel)
int core_dline(char kind, char s_speed, char speed);                                            //���� ����Ʈ���̽� �ھ�
int core_uline(char kind, char s_speed, char speed);                                            //���� ����Ʈ���̽� �ھ�
void absh_wheel(int speed);                                                                     //absh ����� wheel
void lostuline(char kind, char s_speed, char f_speed, char losttime, char breaks);				//���� �ν�Ʈ ����Ʈ���̽�

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
    char count=0;       //ũ�ν� ���� ���� �÷���
    char lost=0;
    
    /* ����̹��� �����ϸ� 'UP_DELAY_TIME' ������ ��ŭ õõ�� �����Ѵ� */
    for(i=s_speed;i<=f_speed;i++)
    {
        chg_absh(i);        //����̹� ����
        itimer1=0;          //Ÿ�̸� ����
        
        while(itimer1<=UP_DELAY_TIME) //Ÿ�̸Ӱ� UP_DELAY_TIME ���� ���� ���� �ݺ�
        {
            /* ���� �� ũ�ν��� �� ��� */
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
    
    if(count==0) //���� �� ������ �� �� ��� ��� ����Ʈ���̼�
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);
            
            servo5(now_speed*3);
            
        }
    }
    
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
        
        while(itimer1<=UP_DELAY_TIME) //UP_DELAY_TIME ��ŭ õõ�� ����
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //���� �� ������ ���� �ı�
            }
            else linetracer(i);
        }
        
        if(count==1) break;
    }
    
    if(count==1)
    {
        while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
        while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
        
        while(itimer1<=DOWN_DELAY_TIME) //DOWN_DELAY_TIME ��ŭ õõ�� ����
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //���� �� ������ ���� �ı�
            }
            else linetracer(i);
        }
        
        if(count==1) break;
        
    }
    
    if(count==0) //���� �� ������ �� �� ��� ��� ����Ʈ���̼�
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);
        }
    }
    
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
        while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
        {
            Flinetrcaer(crossbreaks);
        }

		wheel(0,0);
    }
}

void culine(char kind, char s_speed, char speed, char crossbreaks, char breaks)
{
    int i = core_uline(kind,s_speed,speed);
    
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
    
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
    
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
	 
    while(check_front_sensor_or(kind)) //������ �� ��� ���� ������ ���� �Ѿ��.
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
    else if(now_speed<speed)//���� �ӵ��� ���ϴ� �ӵ����� ���� ��� ����
    {
        uline(kind,now_speed,speed,breaks);   
    }
    else if(now_speed>speed)//���� �ӵ��� ���ϴ� �ӵ����� ���� ��� ����
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
    else if(now_speed<speed)//���� �ӵ��� ���ϴ� �ӵ����� ���� ��� ����
    {
        
        suline(kind,now_speed,speed,breaks);
        
    }
    else if(now_speed>speed)//���� �ӵ��� ���ϴ� �ӵ����� ���� ��� ����
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
        
        while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
            
            while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
        
        while(itimer1<=DOWN_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
        
        while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
            
            while(itimer1<=UP_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
        
        while(itimer1<=DOWN_TRUN_TIME) //UP_TRUN_TIME ��ŭ õõ�� ����
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
    if(FB3||FB4||FB5) linetracer(speed); //3,4,5�� ������ ������ ���� ������ Ʈ���̼�
    else
    {
        //�Ⱥ��� �ִٸ� wheel�� Ǫ��
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
        
        while(itimer1<=DOWN_DELAY_TIME) //DOWN_DELAY_TIME ��ŭ õõ�� ����
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //���� �� ������ ���� �ı�
            }
            else linetracer(i);

			servo5(now_speed*3);

        }
        
        if(count==1) break;
        
    }
    
    if(count==0) //���� �� ������ �� �� ��� ��� ����Ʈ���̼�
    {
        while(!check_front_sensor(kind))
        {
            linetracer(i);

			servo5(now_speed*3);

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
        
        while(itimer1<=UP_DELAY_TIME) //UP_DELAY_TIME ��ŭ õõ�� ����
        {
            if(check_front_sensor(kind))
            {
                count=1;
                break; //���� �� ������ ���� �ı�
            }
            else linetracer(20);

			servo5(now_speed*3);

        }
        
        if(count==1) break;
    }
    
    if(count==0) //���� �� ������ �� �� ��� ��� ����Ʈ���̼�
    {
        while(!check_front_sensor(kind))
        {
            linetracer(20);

			servo5(now_speed*3);

        }
    }

	return i;
}

void absh_wheel(int speed)
{
    abs_ratio(20-absh_1[speed],20-absh_1[speed]);
    wheel(speed,speed);
}
