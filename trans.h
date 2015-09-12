
volatile unsigned char inits1=0;
volatile unsigned char inits2=0;
volatile unsigned char inits3=0;
volatile unsigned char inits4=0;
volatile unsigned char pginits1=0;
volatile unsigned char pginits2=0;
volatile unsigned char peinits1=0;
volatile unsigned char peinits2=0;
volatile unsigned char rinits1=0;
volatile unsigned char rinits2=0;
volatile unsigned char cinits1=0;
volatile unsigned char cinits2=0;
volatile unsigned char l2inits3=0;
volatile unsigned char l2inits4=0;
volatile unsigned char l3inits3=0;
volatile unsigned char l3inits4=0;
volatile unsigned char object = 0;	


#define tff1		absh(20,18,12,8);
#define tff2		absh(15,13,8,3);
#define tff3		absh(10,7,3,0);	
#define tff4		absh(7,3,0,0);	
#define tff5		absh(5,0,0,0);	


#define mb 		12
#define pick_d	300  //��� �����̰� 
#define up_d	300  //��� �ø��� �����̰� 

//////////////////////////TransPorter///////////////////////////////

void tinit(unsigned char ins1, unsigned char ins2, unsigned char ins3, unsigned char ins4)
{
	pginits1 = inits1 = ins1;  //11�� ������ ��� 1�� ������
	pginits2 = inits2 = ins2;  //11�� ������ ��� 2�� ������
	peinits1 = pginits1 - 3; //�������� ������ ��� 1�� ������
	peinits2 = pginits2 + 3; //�������� ������ ��� 2�� ����
	inits3 = ins3;
	inits4 = ins4;
	servo1(inits1);
	servo2(inits2);
	servo3(inits3);
	servo4(inits4);
	delay(1000);
}

void tpalinit(unsigned char rins1, unsigned char rins2, unsigned char cins1, unsigned char cins2)
{
	rinits1 = pginits1 + rins1;  //�簢 �ȷ�Ʈ ���� ��� 1�� ������ 
	rinits2 = pginits2 - rins2;  //�簢 �ȷ�Ʈ ���� ��� 2�� ������
	cinits1 = pginits1 + cins1;  //�� �ȷ�Ʈ ���� ��� 1�� ������
	cinits2 = pginits2 - cins2;  //�� �ȷ�Ʈ ���� ��� 2�� ������
}

void tlevelinit(unsigned char l2ins3, unsigned char l2ins4, unsigned char l3ins3, unsigned char l3ins4)
{
	l2inits3 = l2ins3;  //2�ܿ� �״� 3�� ������ 
	l2inits4 = l2ins4;  //2�ܿ� �״� 4�� ������
	l3inits3 = l3ins3;  //3�ܿ� �״� 3�� ������
	l3inits4 = l3ins4;  //3�ܿ� �״� 4�� ������
}

void topenpoint(void)  //���� �Ǵ� �������� ��� ���� 1��, 2�� ������ ���� ��
{
	servo1(pginits1+30);
	servo2(pginits2-30);
}
void topenpointslow(void)  //���� �Ǵ� �������� ��� ���� 1��, 2�� ������ ���� ��
{
char i;
	for(i=10;i<=30;i++)
	{
		servo1(pginits1+i);
		servo2(pginits2-i);
		delay(30);
	}
}
void tpick(unsigned char kind)  //�������� ��� 1��, 2�� ������ 
{
	switch(kind)
	{
		case 0 : //������'
			servo1(pginits1);
			servo2(pginits2);
			delay(pick_d);
			break;
		case 1 : //�׿� ������
			servo1(peinits1);
			servo2(peinits2);
			delay(pick_d);
			break;
		case 2 : //�簢 �ȷ�Ʈ
			servo1(rinits1);
			servo2(rinits2);
			delay(pick_d);
			break;
		case 3 : //�� �ȷ�Ʈ
			servo1(cinits1);
			servo2(cinits2);
			delay(pick_d);
			break;
		case 4 : //���簢 �ȷ�Ʈ
			servo1(rinits1);
			servo2(rinits2);
			delay(pick_d);
			break;
	}
	object = kind;
}

void topenpal(void)  //�ȷ�Ʈ�� ��� ���� 11�� 1��, 2�� ������
{
	servo1(peinits1);
	servo2(peinits2);
//	delay(300);
}


void tpickup(void)  //������ �� �ȷ�Ʈ�� ���ø��� 4�� ������ 
{
	if(object<2)
	{
		servo3(inits3 + 20);
		servo4(inits4 - 75);
		delay(up_d);
	}
	else
	{
		servo4(inits4 - 75);
		delay(up_d);
	}
}

void tputdown(unsigned char kind)  //������ �� �ȷ�Ʈ�� ���� 3��, 4�� ������
{
	unsigned char i;
	switch(kind)
	{
		case 1 : //1��
			servo3(inits3);
			servo4(inits4-30);
			delay(500);	//�������� �ּҰ��� ã���ÿ�
			for(i=inits4-30;i<inits4;i++)
			{
				servo4(i);
				delay(30);
			}
			break;

		case 2 : //2��
			for(i=inits3;i<l2inits3;i+=2)
			{
				servo3(i);
				delay(30);
			}

			for(i=inits4-75;i<l2inits4;i++)
			{
				servo4(i);
				delay(30);
			}
			break;
			
		case 3 : //3��
			for(i=inits3;i<l3inits3;i+=3)
			{
				servo3(i);
				delay(50);
			}

			for(i=inits4 - 75;i<l3inits4;i++)
			{
				servo4(i);
				delay(50);
			}
			break;
	}
}

void tready12(unsigned char kind)  //������ �� �ȷ�Ʈ�� ���� �����·� �����ϴ� 1��, 2�� ������
{
	unsigned char i;
	switch(kind)
	{
		case 0 : //������ 
			for(i=0;i<10;i++)
			{
				servo1(pginits1+i);
				servo2(pginits2-i);
				delay(50);
			}
			delay(200);
			//topenpoint();
			break;

		case 1 : //��Ÿ ������
			for(i=0;i<10;i++)
			{
				servo1(peinits1+i);
				servo2(peinits2-i);
				delay(30);
			}
			//topenpoint();
			break;
		
		case 2: //�簢 �ȷ�Ʈ
			for(i=0;i<10;i++)
			{
				servo1(rinits1 - i);
				servo2(rinits2 + i);
				delay(30);
			}
			//topenpal();
			break;

		case 3 : //�� �ȷ�Ʈ
			for(i=0;i<10;i++)
			{
				servo1(cinits1-i);
				servo2(cinits2+i);
				delay(30);
			}
			//topenpal();
			break;

		case 4: //���簢 �ȷ�Ʈ
			for(i=0;i<10;i++)
			{
				servo1(rinits1 - i);
				servo2(rinits2 + i);
				delay(30);
			}
			//topenpal();
			break;
	}

}

void tready34(void)  //3��, 4�� ������ 1������ ����ġ
{
	servo3(inits3);
	servo4(inits4);
//	delay(250);
}

void treadyoff34(void)  //3��, 4�� ������ 1������ ����ġ
{
	servo3(0);
	servo4(0);
//	delay(300);
}

void app(unsigned char repeat, unsigned char correction)  //������ ���� 
{
	unsigned char i;
	for(i=0; i<repeat; i++)	
	{
		servo1(pginits1+correction);
		servo2(pginits2-correction);
		delay(100);
		servo1(pginits1);
		servo2(pginits2);
		delay(50);
	}

}


void tservotest(unsigned char point, unsigned char level)
{
	switch(point)
	{
		case 0 : // ������ ������ ��� �� 
			topenpoint();
			delay(500);
			tpick(0);
			break;

		case 1 : // �׿� ������ ��� �� 
			topenpoint();
			delay(2000);
			tpick(1);
			break;
						
		case 2 : // �簢 �ȷ�Ʈ ��� ��	
			topenpal();
			delay(500);
			tpick(2);
			break;

		case 3 : // ���� �ȷ�Ʈ ��� ��	
			topenpal();
			delay(500);
			tpick(3);
			break;

		case 4 : // ���簢 �ȷ�Ʈ ��� ��	
			topenpal();
			delay(500);
			tpick(2);
			break;

	}
	delay(500);
	tpickup();
	delay(500);
	if(point==0)	app(1,10);
	delay(500);	

	if(level == 1) tputdown(1);
	else if(level == 2) tputdown(2);
	else if(level == 3) tputdown(3);
	delay(500);

	if(point == 2)  tready12(2);//�簢 �ȷ�Ʈ �ݴ´�.
	else if(point == 3) tready12(3); //�� �ȷ�Ʈ �ݴ´�
	else if(point == 1) tready12(1); // ��Ÿ �������� ������.
	else tready12(0); //�������� ������.


tff4;
	motor(-10,-10,500);

	tready34();

//	saveTimeProcess();	

}

void b_white_stop(unsigned char speed)
{
	while(1)
	{
		linetracer(speed); 
		if(( BB1 && BB2 ) || ( BB6 && BB7 ))	break; 
	}
	while(1)
	{
		linetracer(speed); 
		if( BW1 && BW7 )	break; 
		
	}
}
void b_balck_stop(unsigned char speed)
{
	while(1)
	{
		linetracer(speed); 
		if(( BB1&& BB2 ) || ( BB6 && BB7 ))	break; 
	}
}

void get(unsigned char kind, unsigned char speed)
{
	tready34();

	if(kind<2)	topenpoint();
	else		topenpal();	

	switch(kind)
	{
// ������ 	
		case 0:
			tff5;
			b_white_stop(speed); //�޼��� ũ�ν� ������ ������� ���� 
			wheel(0,0);
			tpick(kind);
			tpickup();
			tff1;
			line(lr1,speed,0);
			break;
// �����丷 
		case 1:
			tff5;
			b_white_stop(speed); //�޼��� ������ �������� ���� ���� 
			wheel(0,0);
			tpick(kind);
			tpickup();
			tff1;
			line(lr1,speed,0);
			break;						
// ���簢 �ȷ�Ʈ 
		case 2:	
			tff5;
			b_white_stop(speed);
			wheel(0,0);
			tpick(kind);
			tpickup();
			tff1;
			line(lr1,speed,0);
			break;
// ���� �ȷ�Ʈ 
		case 3:	
			tff5;
			b_white_stop(speed);
			wheel(0,0);
			tpick(kind);
			tpickup();
			tff1;
			line(lr1,speed,0);
			break;
// ���簢 �ȷ�Ʈ 			
		case 4:	
			tff5;
			b_white_stop(speed);
			wheel(0,0);
			tpick(kind);
			tpickup();
			tff1;
			line(lr1,speed,0);
			break;				
					
	}
	wheel(0,0);
	tff1;

}

void put(unsigned char level, signed char speed)
{
	switch(level)
	{
		case 1:			//	1��
			tff5;
			if(object==4){b_white_stop(speed);}
			else {b_balck_stop(speed);}						
			wheel(0,0);
			if(object==2)
			{
				dir(BB);
				while(1)
				{
					linetracer(speed);
					if(BW1&&BW7)	break;
				}
				//line(lr1,speed,0);
			}
			wheel(0,0);
			tff1;
			tputdown(1);
			tready12(object);
			topenpal();
			tff5;
			dir(BB);
			if(object==2)
			{
				motor(speed,speed,100);
			}
			else if(object==3)
			{
				line(lr1,speed,0);
			}
			break;

		case 2:			//	2��
			if(object==0)		// �������̸�
			{
				tff5;
				b_white_stop(speed);
				wheel(0,0);
				tff1;
				tputdown(2);
				tready12(object);
				topenpoint();
				motor(0,0,200);
			}
			else if(object==1)	//	�����丷�̸�		
			{
				tff5;
				b_balck_stop(speed);
				wheel(0,0);
				tff1;
				tputdown(2);
				tready12(object);
				motor(0,0,200);
			}
			else if(object==2||4)	//	�ȷ�Ʈ(�簢��)�̸�
			{
				tff5;
				b_balck_stop(speed);
				wheel(0,0);
				tff1;
				tputdown(2);
				tready12(object);
				topenpal();
				tff5;
				dir(BB);
				line(lr1,speed,0);
				motor(speed,speed,200);
				dir(FF);
				tff1;
			}
			else if(object==3)	//	�ȷ�Ʈ(����)�̸�
			{
				tff5;
				b_balck_stop(speed/2);
				wheel(0,0);
				tff1;
				tputdown(2);
				tready12(object);
				topenpal();
				tff5;
				dir(BB);
				line(lr1,speed,0);
				motor(speed,speed,200);
			}
			break;	

		case 3:		//	3�� 
			if(object==0)		// �������̸�
			{
				tff5;
				b_white_stop(speed);
				wheel(0,0);
				tff1;
				tputdown(3);
				tready12(object);
				topenpoint();
			}
			else if(object==1||4)	//	�����丷�̸�		
			{
				tff5;
				b_white_stop(speed);
				wheel(0,0);
				tff1;
				tputdown(3);
				tready12(object);
				tff5;
				dir(BB);
				line(lr1,speed,0);
			}
			break;
	}
	/*
	treadyoff34();
	tff5;
	dir(BB);
	linedelay(250,speed,0);
	tff1;
	if(object<2)
	{
		topenpoint();
	}
	else
	{
		topenpal();
	}
	motor(speed,speed,50);//48���� ������ ��� �ٿ����� 
	tready34();
	delay(250);
	dir(FF);
	*/
}
void ffbbdelayline(signed int delaytime, signed char speed)
{
itimer1=0;itimer2=0;
	if(delaytime>0)
	{
		dir(FF);	
		while(1)
		{
			linetracer(speed);
			if((itimer1>=delaytime)&&(itimer2>=delaytime))	break;
		}
	}
	else if(delaytime<0)
	{
		delaytime*=-1;
		dir(BB);
		while(1)
		{
			linetracer(speed);
			if((itimer1>=delaytime)&&(itimer2>=delaytime))	break;

		}
	}
	wheel(0,0);
	dir(FF);

}
void delayput(signed int delaytime,unsigned char level,unsigned char _dir, signed char speed)
{


	switch(level)
	{
		case 1:			//	1��
			tff5;
			if(object==4)		//���簢 �ȷ�Ʈ 
			{
				b_white_stop(speed);
			}
			else 
			{
				b_balck_stop(speed);
			}
			wheel(0,0);
			if(object==2) //���簢 �ȷ�Ʈ 
			{
				dir(BB);
				while(1)
				{
					linetracer(speed);
					if(BW1&&BW7)	break;
				}
				//line(lr1,speed,0);
			}
			ffbbdelayline(delaytime,speed);			//�յڷ� �� �б� 
			
			tputdown(1);
			tready12(object);
			topenpal();
			break;
		case 2:			//	2��
			if(object==0)		// �������̸�
			{
				tff5;
				b_balck_stop(speed);
				ffbbdelayline(delaytime,speed);
				tputdown(2);
				tready12(object);
				//topenpoint();
				topenpointslow();
				motor(0,0,400);
			}
			else if(object==1)	//	�����丷�̸�		
			{
				if(_dir==FF)
				{
					tputdown(2);
					tff5;
					b_balck_stop(speed);
					ffbbdelayline(delaytime,speed);
					//tputdown(2);
					tready12(object);

					motor(0,0,400);
					servo4(l3inits4);delay(100);
					servo3(l3inits3);
				
				
					motor(0,0,400);

				}
				else if(_dir==LL)
				{
					tff5;
					b_balck_stop(speed);
					ffbbdelayline(delaytime,speed);

					bmotor(-5,5,S5,0);
					bmotor(-5,5,S6,0);

					tputdown(2);
					tready12(object);

					motor(0,0,400);
					if((_dir==LL)||(_dir==RR))	motor(-5,-5,400);
					//tputdown(3);
					servo4(l3inits4);delay(100);
					servo3(l3inits3);
				
				
					motor(0,0,400);


				}
				else if(_dir==RR)
				{
					tff5;
					b_balck_stop(speed);
					ffbbdelayline(delaytime,speed);

					bmotor(5,-5,S3,0);
					bmotor(5,-5,S2,0);
					tputdown(2);
					tready12(object);

					motor(0,0,400);
					if((_dir==LL)||(_dir==RR))	motor(-5,-5,400);
					//tputdown(3);
					servo4(l3inits4);delay(100);
					servo3(l3inits3);
				
				
					motor(0,0,400);


				}				
			}
			else if(object==2||4)	//	�ȷ�Ʈ(�簢��)�̸�
			{
				tff5;
				b_balck_stop(speed);
				ffbbdelayline(delaytime,speed);
				tputdown(2);
				tready12(object);
				topenpal();
			}
			else if(object==3)	//	�ȷ�Ʈ(����)�̸�
			{
				tff5;
				b_balck_stop(speed);
				ffbbdelayline(delaytime,speed);
				tputdown(2);
				tready12(object);
				topenpal();
			}
			break;	

		case 3:		//	3�� 
			if(object==0)		// �������̸�
			{
				tff5;
				b_white_stop(speed);
				ffbbdelayline(delaytime,speed);
				tputdown(3);
				tready12(object);
				topenpoint();
			}
			else if(object==1||4)	//	�����丷�̸�		
			{
				tff5;
				b_white_stop(speed);
				ffbbdelayline(delaytime,speed);
				if(_dir==LL)
				{
					bmotor(-5,5,S5,0);
					bmotor(-5,5,S6,0);
				}
				else if(_dir==RR)
				{
					bmotor(5,-5,S3,0);
					bmotor(5,-5,S2,0);
				}				
				tputdown(3);
				tready12(object);
				motor(0,0,400);
				if((_dir==LL)||(_dir==RR))	motor(-5,-5,400);
				//tputdown(3);
				servo4(l3inits4);delay(100);
				servo3(l3inits3);
				
				
				motor(0,0,400);


			}
			break;
	}
	treadyoff34();
	tff5;
	dir(BB);
	linedelay(300,speed,0);
	tff1;
	if(object<2)
	{
		topenpoint();
	}
	else
	{
		topenpal();
	}
	motor(speed,speed,50);//48���� ������ ��� �ٿ����� 
	tready34();
	delay(250);
	dir(FF);
}

