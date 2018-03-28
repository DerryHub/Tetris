#include"acllib.h"
#define CONTINUE "继续"
#define START "开始"
#define image1_color RGB(0,150,70)
#define image2_color RGB(255,150,150)
#define image3_color RGB(100,150,255)
#define image4_color RGB(200,150,50)
#define image5_color RGB(200,100,150)
#define image6_color RGB(70,50,10)
#define image7_color RGB(100,50,10)
#define image8_color RGB(100,140,180)
#define image9_color RGB(50,170,200)
#define image10_color RGB(200,180,50)
#define W 1200
#define H 780 
#define To_top 30
#define To_left 30
#define To_right 150
#define To_bottom 50
#define R_round 20
#define Dia_a 40
#define W_num 25
#define H_num 17
#define Key_dis 10
#define Key_h 50
#define Key_totop 70
#define Key_key 30
#define init_time_step 800
#define Time_step_change 15 
#define Key_color_stkey RGB(color_stkey,0,0)
#define Key_color_st RGB(color_st,0,0)
#define Key_color_ex RGB(color_ex,0,0)
#define Key_color_pa RGB(color_pa,0,0)
#define Key_color_re RGB(color_re,0,0)
#define gamewin_color RGB(0,150,70)
#define ar_static_color YELLOW
#define ar_color GREEN
#define gameover_color BLUE
#define T_color WHITE
#define score_color RGB(score_color_R,score_color_G,score_color_B)
#define dx 5
#define dy 5
#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define TRUE 1
#define FALSE 0
int score_color_R=0,score_color_G=250,score_color_B=0;
ACL_Color win_color=image1_color;
ACL_Sound*pMusic;
ACL_Sound*pClick;
ACL_Sound*pGameover;
ACL_Sound*pDown;
ACL_Image*pImage;
int Time_step=init_time_step;
int image_num=1;
int score=0;
int*fp=NULL;
int z_or_n=FALSE;
int z_rotate=FALSE;
int SPACE=FALSE;
int start_or_n=FALSE;
int kb_or_n=FALSE;
int FK_MOVE=FALSE;
int GAMEOVER=FALSE;
int STOP_all=FALSE;
int ar[H_num][W_num];
int ar_static[H_num][W_num],ar_static_i=0,ar_static_j=0;
int color_st=100,color_ex=100,color_pa=100,color_re=100,color_stkey=100;
void start_click(void);
void exit_click(void);
void pause_click(void);
void replay_click(void); 
void replay(void);
void mouselistener(int x,int y,int button,int event);
char*T_start="开始",*T_exit="退出",*T_pause="暂停",*T_replay="重玩";
char*T_gameover="GAME OVER!";
char T_score[6]="00000",*T_SCORE="得分";
char*T_rule="游戏规则";
char*T_ctrl1="“↑”键旋转，“↓”键加速；";
char*T_ctrl2="“←”“→”键控制左右移动；";
char*T_ctrl3="空格键可控制游戏暂停/开始；"; 
char*T_ctrl4="组成行的方块会被消去；";
char*T_ctrl5="当方块积累超过红线游戏结束。"; 
char*T_design="——Designed By 林德铝&罗立扬";
char*T_know="我知道啦";
void paint_key(void);
void paint_ar(int [][W_num]);
void init_win(void);
void key_clean(void);
void timer(int timerID);
void init_ar(int [][W_num]);
void ar_move(int [][W_num],int);
void launch(void);
void fk1(void);
void fk2(void);
void fk3(void);
void fk4(void);
void fk5(void);
void fk6(void);
void fk7(void);
void paint_static(int [][W_num]);
void artostatic(void);
void keyboardlistener(int key,int event);
void fk_rotate(int*);
void condition_down(void);
int condition_right(void);
int condition_left(void);
void condition_rotate(void);
void paint_limitLine(void);
void paint_all(void);
void condition_gameover(void);
void paint_gameover(void);
void condition_botton(void);
void condition_clear(void);
void clear_fk(int);
void inttochar(int);
int cf(int,int);
void paint_score(int);
void paint_stwin(void);
void paint_stkey(void);
void stkey_click(void);
int condition_boundary(int*);
int condition_boundary(int*p)
{
	int i;
	for(i=0;i<H_num;i++)
	{
		if(&ar[i][0]==p||&ar[i][W_num-1]==p)
		{
			return FALSE;
		}
	}
	return TRUE;
}
void stkey_click(void)
{
	playSound(*pClick,0);
    start_or_n=TRUE;
    beginPaint();
    setPenColor(gamewin_color);
	endPaint();
	paint_ar(ar);
	paint_score(score);
}
void paint_stkey(void)
{
	beginPaint();
	setPenColor(Key_color_stkey);
	setBrushColor(Key_color_stkey);
	roundrect(W-400,To_top+600,W-250,To_top+650,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_stkey);
	paintText(W-400+15,To_top+600+10,T_know);
	endPaint();
}
void paint_stwin(void)
{
	beginPaint();
	setPenColor(gamewin_color);
	setBrushColor(gamewin_color);
	roundrect(To_left,To_top,W-To_right,H-To_bottom,R_round,R_round);
	setTextColor(RED);
	setTextSize(80);
	setTextBkColor(gamewin_color);
	paintText((W-To_left-To_right)/2-130,To_top+50,T_rule);
	setTextColor(T_color);
	setTextSize(30);
	paintText(To_left+300,To_top+200,T_ctrl1);
	paintText(To_left+300,To_top+270,T_ctrl2);
	paintText(To_left+310,To_top+340,T_ctrl3);
	paintText(To_left+350,To_top+410,T_ctrl4);
	paintText(To_left+310,To_top+480,T_ctrl5);
	setTextSize(30);
	paintText(W-650,To_top+550,T_design);
	endPaint();
	paint_stkey();
}
void paint_score(int score)
{
	inttochar(score);
	beginPaint();
	setPenColor(win_color);
	setBrushColor(win_color);
	roundrect(W-145,440,W-5,570,R_round,R_round);
	setTextColor(RED);
	setTextSize(40);
	setTextBkColor(win_color);
	setTextColor(T_color);
	paintText(W-120,450,T_SCORE);
	setTextSize(50);
	setTextColor(score_color);
	paintText(W-140,510,T_score);
	endPaint();
}
int cf(int a,int b)
{
	int c;
	c=a;
	int t;
	if(b==0)
	return 1;
	else
	{
	for(t=1;t<b;t++)
	a*=c;
	return a;
    }
}
void inttochar(int score)
{
	int a,t,b;
	b=score;
	for(a=5;a>0;a--)
	{
		t=b/cf(10,a-1);
		b=b%cf(10,a-1);
		switch(t)
		{
			case 0:T_score[5-a]='0';break;
			case 1:T_score[5-a]='1';break;
			case 2:T_score[5-a]='2';break;
			case 3:T_score[5-a]='3';break;
			case 4:T_score[5-a]='4';break;
			case 5:T_score[5-a]='5';break;
			case 6:T_score[5-a]='6';break;
			case 7:T_score[5-a]='7';break;
			case 8:T_score[5-a]='8';break;
			case 9:T_score[5-a]='9';break;
		}
	}
}
void clear_fk(int line)
{
	int i,j;
	for(j=0;j<W_num;j++)
	{
		ar_static[line][j]=0;
	}
	for(i=line-1;i>=0;i--)
	{
		for(j=0;j<W_num;j++)
		{
			if(ar_static[i][j])
			{
				ar_static[i][j]=0;
				ar_static[i+1][j]=1;
			}
		}
	}
}
void condition_clear(void)
{
	int i,j,im;
	int count;
	for(i=0;i<H_num;i++)
	{
		count=0;
		for(j=0;j<W_num;j++)
		{
			if(ar_static[i][j])
			{
				count++;
			}
		}
		if(count==W_num)
		{
			im=image_num;
			do
			{
				image_num=rand()%10+1;
			}while(image_num==im);
			clear_fk(i);
			score+=10;
			if(score_color_R<250)
			{
				score_color_R+=10;
			}else if(score_color_G>0)
			{
				score_color_G-=10;
			}
			if(Time_step>=120)
			{
				Time_step-=Time_step_change;
		    }
		    startTimer(0,Time_step);
		    switch(image_num)
		    {
		    	case 1:
		    		loadImage("image1.jpg",pImage);
		    		win_color=image1_color;
		    		break;
		    	case 2:
		    		loadImage("image2.jpg",pImage);
		    		win_color=image2_color;
		    		break;
		    	case 3:
		    		loadImage("image3.jpg",pImage);
		    		win_color=image3_color;
		    		break;
		    	case 4:
		    		loadImage("image4.jpg",pImage);
		    		win_color=image4_color;
		    		break;
		    	case 5:
		    		loadImage("image5.jpg",pImage);
		    		win_color=image5_color;
		    		break;
		    	case 6:
		    		loadImage("image6.jpg",pImage);
		    		win_color=image6_color;
		    		break;
		    	case 7:
		    		loadImage("image7.jpg",pImage);
		    		win_color=image7_color;
		    		break;
		    	case 8:
		    		loadImage("image8.jpg",pImage);
		    		win_color=image8_color;
		    		break;
		    	case 9:
		    		loadImage("image9.jpg",pImage);
		    		win_color=image9_color;
		    		break;
		    	case 10:
		    		loadImage("image10.jpg",pImage);
		    		win_color=image10_color;
		    		break;
			}
		}
	}
 } 
void condition_botton(void)
{
	int j;
	for(j=0;j<W_num;j++)
	{
		if(ar[H_num-1][j])
		{
			artostatic();
			FK_MOVE=FALSE;
			break;
		}
	}
}
void paint_gameover(void)
{
	stopSound(*pMusic);
	beginPaint();
	setBrushColor(gameover_color);
	setPenColor(gameover_color);
	rectangle(0,H/2,W,H/2+100);
	setTextBkColor(gameover_color);
	setTextSize(100);
	paintText(W/2-250,H/2,T_gameover);
	endPaint();
	playSound(*pGameover,0);
}
void condition_gameover(void)
{
	int j;
	for(j=0;j<W_num;j++)
	{
		if(ar_static[2][j])
		{
			GAMEOVER=TRUE;
		}
	}
}
void paint_all(void)
{
	paint_ar(ar);
	paint_static(ar_static);
	paint_limitLine();
	paint_score(score);
}
void paint_limitLine(void)
{
	beginPaint();
	setPenColor(RED);
	line(To_left,(To_top+R_round/2)*4,W-To_right,(To_top+R_round/2)*4);
	moveTo(To_left,(To_top+R_round/2)*4);
	setPenColor(BLUE);
	lineTo(To_left,H-To_bottom);
	lineTo(W-To_right,H-To_bottom);
	lineTo(W-To_right,(To_top+R_round/2)*4); 
	endPaint();
}
void condition_rotate(void)
{
	int i,j;
	fk_rotate(fp);
	for(i=0;i<H_num;i++)
	{
		for(j=0;j<W_num;j++)
		{
			if(ar[i][j]&&ar_static[i][j])
			{
				fk_rotate(fp);
				fk_rotate(fp);
				fk_rotate(fp);
				goto label2;
			}
		}
	}
	label2:;
}
int condition_left(void)
{
	int i,j;
	for(i=0;i<H_num;i++)
	{
		for(j=0;j<W_num;j++)
		{
			if(ar[i][j]&&j!=0)
			{
				if(ar_static[i][j-1])
				return FALSE;
			}
		}
	}
	return TRUE;
}
int condition_right(void)
{
	int i,j;
	for(i=0;i<H_num;i++)
	{
		for(j=W_num;j>=0;j--)
		{
			if(ar[i][j]&&j!=W_num)
			{
				if(ar_static[i][j+1])
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}
void condition_down(void)
{
	int i,j;
	for(j=0;j<W_num;j++)
	{	
		for(i=H_num-1;i>=0;i--)
		{
			if(ar[i][j])
			{
				if(ar_static[i+1][j])
				{
					FK_MOVE=FALSE;
					artostatic();
				    goto label1;		
				}
			}
		}
	}
	label1:;
 } 
void fk_rotate(int*p)
{
	if(p!=NULL&&condition_boundary(p))
	{
		int t;
		t=*(p-W_num-1);
		*(p-W_num-1)=*(p+W_num-1);
		*(p+W_num-1)=*(p+W_num+1);
		*(p+W_num+1)=*(p-W_num+1);
		*(p-W_num+1)=t;
		t=*(p+W_num);
		*(p+W_num)=*(p+1);
		*(p+1)=*(p-W_num);
		*(p-W_num)=*(p-1);
		*(p-1)=t;
		if(z_or_n)
		{
			if(z_rotate)
			{
				z_or_n=FALSE;
				fk_rotate(fp);
				fk_rotate(fp);
				z_rotate=FALSE;
				z_or_n=TRUE;
			}
			else
			{
				z_rotate=TRUE;
			}
		}
    }
}
void keyboardlistener(int key,int event)
{
	if(event==0&&GAMEOVER==FALSE&&STOP_all==FALSE&&start_or_n)
	{
		if(kb_or_n)
		{
			switch(key)
			{
				case 37:
			if(condition_left())
			{
				ar_move(ar,LEFT);
				paint_all();
			}
				break;
				case 38:
				condition_rotate();
				paint_all();
				break;
				case 39:
			if(condition_right())
			{
				ar_move(ar,RIGHT);
				paint_all();
			}
				break;
				case 40:
				startTimer(0,10);
				playSound(*pDown,0);
				STOP_all=TRUE;
				break;
			}
		}
		if(event==0&&key==32)
		{
			if(SPACE==FALSE)
			{
				SPACE=TRUE;
				kb_or_n=TRUE;
				if(GAMEOVER==FALSE)
				{
					startTimer(0,Time_step);
					playSound(*pMusic,1);
				}
			}
			else
			{
				SPACE=FALSE;
				kb_or_n=FALSE;
				cancelTimer(0);
				stopSound(*pMusic);
				T_start=CONTINUE; 
			    paint_key();
			}
	    }
	}
}
void artostatic(void)
{
	int i,j;
	for(i=0;i<H_num;i++)
	{
		for(j=0;j<W_num;j++)
		{
			if(ar[i][j]!=0)
			ar_static[i][j]=1;
		}
	}
	init_ar(ar);
}
void paint_static(int (*ar)[W_num])
{
	int i,j;
	beginPaint();
	setPenColor(BLACK);
	for(i=1;i<=H_num;i++)
	{
		for(j=1;j<=W_num;j++)
		{		
			if(ar[i-1][j-1]!=0)
			{
			    setBrushColor(ar_static_color);
			    rectangle((To_left+R_round/2)*j,(To_top+R_round/2)*i,(To_left+R_round/2)*j+Dia_a,(To_top+R_round/2)*i+Dia_a);
		    }	
		}
	}
	endPaint();
 } 
void fk1(void)
{
	ar[0][W_num/2-1]=1;
	ar[0][W_num/2]=1;
	ar[1][W_num/2-1]=1;
	ar[1][W_num/2]=1;
	fp=NULL;
}
void fk2(void)
{
	ar[0][W_num/2-1]=1;
	ar[0][W_num/2]=1;
	ar[1][W_num/2]=1;
	ar[2][W_num/2]=1;
	fp=&ar[1][W_num/2];
}
void fk3(void)
{
	ar[0][W_num/2-1]=1;
	ar[0][W_num/2]=1;
	ar[1][W_num/2-1]=1;
	ar[2][W_num/2-1]=1;
	fp=&ar[1][W_num/2-1];
}
void fk4(void)
{
	ar[0][W_num/2-1]=1;
	ar[1][W_num/2-1]=1;
	ar[2][W_num/2-1]=1;
	fp=&ar[1][W_num/2-1];
}
void fk5(void)
{
	ar[0][W_num/2-1]=1;
	ar[1][W_num/2-1]=1;
	ar[1][W_num/2-2]=1;
	ar[1][W_num/2]=1;
	fp=&ar[1][W_num/2-1];
}
void fk6(void)
{
	ar[0][W_num/2-1]=1;
	ar[1][W_num/2-1]=1;
	ar[1][W_num/2]=1;
	ar[2][W_num/2]=1;
	fp=&ar[1][W_num/2];
}
void fk7(void)
{
	ar[0][W_num/2]=1;
	ar[1][W_num/2-1]=1;
	ar[1][W_num/2]=1;
	ar[2][W_num/2-1]=1;
	fp=&ar[1][W_num/2-1];	
}
void launch(void)
{
	startTimer(0,Time_step);
	STOP_all=FALSE;
	if(GAMEOVER==FALSE)
	{
		int r,i;
		srand((unsigned int)time(0));
		r=rand()%7;
		switch(r)
		{
			case 0:
				fk1();
				z_or_n=FALSE;
				break;
			case 1:
				fk2();
				z_or_n=FALSE;
				break;
			case 2:
				fk3();
				z_or_n=FALSE;
				break;
			case 3:
				fk4();
				z_or_n=FALSE;
				break;
			case 4:
				fk5();
				z_or_n=FALSE;
				break;
			case 5:
				fk6();
				z_or_n=TRUE;
				z_rotate=FALSE;
				break;
			case 6:
				fk7();
				z_or_n=TRUE;
				z_rotate=FALSE;
				break;
		}
		if(r!=1)
		{
			r=rand()%4;
			for(i=0;i<r;i++)
			{
				fk_rotate(fp);
			}
		}
    }
}
void ar_move(int a[][W_num],int d)
{
	int i,j;
     switch(d)
				{
					case RIGHT:
						for(i=0;i<H_num;i++)
						{
							if(a[i][W_num-1]!=0)
							goto label0;
						}
						for(i=0;i<H_num;i++)
						{
							for(j=W_num-1;j>=0;j--)
							{
					    if(a[i][j]!=0)
						{
						a[i][j]=0;
						a[i][j+1]=1;
					    }
							}
						}
						if(fp!=NULL)
						fp++;
					    break;
					case LEFT:
						for(i=0;i<H_num;i++)
						{
							if(a[i][0]!=0)
							goto label0;
						}
						for(i=0;i<H_num;i++)
						{
							for(j=0;j<W_num;j++)
							{
						if(a[i][j]!=0)
						{	
						a[i][j]=0;
						a[i][j-1]=1;
					    }
							}
						}
						if(fp!=NULL)
						fp--;
					    break;
					case DOWN:
						for(i=H_num;i>=0;i--)
						{
							for(j=0;j<W_num;j++)
							{
								if(i+1<H_num&&a[i][j]!=0)
						{
						a[i][j]=0;
						a[i+1][j]=1;
					    }
							}
						}
						if(fp!=NULL)
						fp=fp+W_num;
					    break;	 
				}
				label0:;
}
void init_ar(int a[][W_num])
{
		int i,j;
	for(i=0;i<H_num;i++)
	{
		for(j=0;j<W_num;j++)
		{
		a[i][j]=0;
     	} 
	}
}
void timer(int timerID)
{
	if(timerID==0)
	{
		if(GAMEOVER)
		{
			paint_gameover();
			cancelTimer(0);
			goto label3;
		}
		condition_botton();
		if(FK_MOVE==TRUE)
		{
			condition_down();
			condition_gameover();
		}
	   if(FK_MOVE==FALSE)
	   {
	   launch();
	   FK_MOVE=TRUE;
	   condition_clear();
       }
	   else
	   ar_move(ar,DOWN);
	   paint_all();
	   label3:;
	}
}
int Setup()
{
	init_win();
	paint_key();
    init_ar(ar);
    init_ar(ar_static);
    paint_stwin();
	registerMouseEvent(mouselistener);
	registerTimerEvent(timer);
	registerKeyboardEvent(keyboardlistener);
	return 0;
}
void init_win(void)
{
	initWindow("俄罗斯方块",170,10,W,H);
	pMusic=(ACL_Sound*)malloc(sizeof(ACL_Sound));
	pClick=(ACL_Sound*)malloc(sizeof(ACL_Sound));
	pGameover=(ACL_Sound*)malloc(sizeof(ACL_Sound));
	pDown=(ACL_Sound*)malloc(sizeof(ACL_Sound));
	pImage=(ACL_Image*)malloc(sizeof(ACL_Image));
	loadSound("music.mp3",pMusic);
	loadSound("click.wav",pClick);
	loadSound("gameover.mp3",pGameover);
	loadSound("down.mp3",pDown);
	loadImage("image1.jpg",pImage); 
	beginPaint();
	putImageScale(pImage,0,0,W,H);
    setPenColor(gamewin_color);
	setBrushColor(gamewin_color);
	roundrect(To_left,To_top,W-To_right,H-To_bottom,R_round,R_round);
	endPaint();
	paint_score(score);
}
void replay(void)
{
	beginPaint();
	putImageScale(pImage,0,0,W,H);
	setPenColor(gamewin_color);
	setBrushColor(gamewin_color);
	roundrect(To_left,To_top,W-To_right,H-To_bottom,R_round,R_round);
	endPaint();
	paint_key();
	score=0;
	score_color_R=0;
	score_color_G=250;
	Time_step=init_time_step;
	init_ar(ar);
	init_ar(ar_static);
	paint_ar(ar);
	paint_static(ar_static);
	paint_score(score);
	cancelTimer(0);
	stopSound(*pMusic);
	GAMEOVER=FALSE;
	FK_MOVE=FALSE;
	SPACE=FALSE;	
}
void key_clean(void)
{
	beginPaint();
	setPenColor(win_color);
	setBrushColor(win_color);
	roundrect(W-To_right+Key_dis,Key_totop,W-Key_dis+dx,Key_totop+Key_h+dy,R_round,R_round);
	roundrect(W-To_right+Key_dis,Key_totop+Key_h+Key_key,W-Key_dis+dx,Key_totop+Key_key+2*Key_h+dy,R_round,R_round);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*2,W-Key_dis+dx,Key_totop+Key_key*2+3*Key_h+dy,R_round,R_round);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*3,W-Key_dis+dx,Key_totop+Key_key*3+4*Key_h+dy,R_round,R_round);
	endPaint();
}
void paint_key(void)
{
	key_clean();
	beginPaint();
	setBrushColor(win_color);
	roundrect(W-To_right+Key_dis/2,Key_totop-Key_dis/2,W-Key_dis/2,Key_totop+Key_key*3+4*Key_h+Key_dis/2,R_round,R_round);
	setBrushColor(Key_color_st);
	roundrect(W-To_right+Key_dis,Key_totop,W-Key_dis,Key_totop+Key_h,R_round,R_round);
	setBrushColor(Key_color_pa);
	roundrect(W-To_right+Key_dis,Key_totop+Key_h+Key_key,W-Key_dis,Key_totop+Key_key+2*Key_h,R_round,R_round);
	setBrushColor(Key_color_re);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*2,W-Key_dis,Key_totop+Key_key*2+3*Key_h,R_round,R_round);
	setBrushColor(Key_color_ex);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*3,W-Key_dis,Key_totop+Key_key*3+4*Key_h,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_st);
	paintText(W-To_right+Key_dis+35,Key_totop+10,T_start);
	setTextBkColor(Key_color_pa);
	paintText(W-To_right+Key_dis+35,Key_totop+10+Key_key+Key_h,T_pause);
	setTextBkColor(Key_color_re);
	paintText(W-To_right+Key_dis+35,Key_totop+(Key_h+Key_key)*2+10,T_replay);
	setTextBkColor(Key_color_ex);
	paintText(W-To_right+Key_dis+35,Key_totop+(Key_h+Key_key)*3+10,T_exit);
	endPaint();
}
void exit_click(void)
{
	beginPaint();
	setBrushColor(BLACK);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*3,W-Key_dis,Key_totop+Key_key*3+4*Key_h,R_round,R_round);
	setBrushColor(Key_color_ex);
	roundrect(W-To_right+Key_dis+dx,Key_totop+(Key_h+Key_key)*3+dy,W-Key_dis+dx,Key_totop+Key_key*3+4*Key_h+dy,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_ex);
	paintText(W-To_right+Key_dis+35+dx,Key_totop+(Key_h+Key_key)*3+10+dy,T_exit);
	endPaint();
	playSound(*pClick,0);
}
void replay_click(void)
{
	beginPaint();
	setBrushColor(BLACK);
	roundrect(W-To_right+Key_dis,Key_totop+(Key_h+Key_key)*2,W-Key_dis,Key_totop+Key_key*2+3*Key_h,R_round,R_round);
	setBrushColor(Key_color_re);
	roundrect(W-To_right+Key_dis+dx,Key_totop+(Key_h+Key_key)*2+dy,W-Key_dis+dx,Key_totop+Key_key*2+3*Key_h+dy,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_re);
	paintText(W-To_right+Key_dis+35+dx,Key_totop+(Key_h+Key_key)*2+10+dy,T_replay);
	endPaint();
	playSound(*pClick,0);
}
void start_click(void)
{
	beginPaint();
	setBrushColor(BLACK);
	roundrect(W-To_right+Key_dis,Key_totop,W-Key_dis,Key_totop+Key_h,R_round,R_round);
	setBrushColor(Key_color_st);
	roundrect(W-To_right+Key_dis+dx,Key_totop+dy,W-Key_dis+dx,Key_totop+Key_h+dy,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_st);
	paintText(W-To_right+Key_dis+35+dx,Key_totop+10+dy,T_start);
	endPaint();
	playSound(*pClick,0);
}
void pause_click(void)
{
	paint_key();
	beginPaint();
	setBrushColor(BLACK);
	roundrect(W-To_right+Key_dis,Key_totop+Key_h+Key_key,W-Key_dis,Key_totop+Key_key+2*Key_h,R_round,R_round);
	setBrushColor(Key_color_pa);
	roundrect(W-To_right+Key_dis+dx,Key_totop+Key_h+Key_key+dy,W-Key_dis+dx,Key_totop+Key_key+2*Key_h+dy,R_round,R_round);
	setTextColor(T_color);
	setTextSize(30);
	setTextBkColor(Key_color_pa);
	paintText(W-To_right+Key_dis+35+dx,Key_totop+10+Key_key+Key_h+dy,T_pause);
	endPaint();
	playSound(*pClick,0);
}
void mouselistener(int x,int y,int button,int event)
{
	if(STOP_all==FALSE)
	{
		if(start_or_n==FALSE)
		{
			if(x>W-400&&x<W-250&&y>To_top+600&&y<To_top+650)
			{
				color_stkey=255;
				paint_stwin();
				if(button==1&&event==2)
				stkey_click();
			}
			else
			{
				color_stkey=100;
				paint_stwin();
				paint_key();
			}
	    }
		if(start_or_n)
		{
			if(x>W-To_right+Key_dis&&x<W-Key_dis&&y>Key_totop&&y<Key_totop+Key_h)
			{
			color_st=255;
			if(button==1&&event==0)
			{
				start_click();
			}
			else if(button==1&&event==2)
			{
				if(GAMEOVER==FALSE&&SPACE==FALSE)
				{ 
					startTimer(0,Time_step);
					playSound(*pMusic,1);
					SPACE=TRUE;
			    }
				kb_or_n=TRUE;
				paint_key();
		    }
			else
			paint_key();
		    }
			else if(x>W-To_right+Key_dis&&x<W-Key_dis&&y>Key_totop+Key_h+Key_key&&y<Key_totop+Key_key+2*Key_h)
			{
			color_pa=255;
			if(button==1&&event==0)
			pause_click();
			else if(button==1&&event==2)
			{
			cancelTimer(0);
			stopSound(*pMusic);
			kb_or_n=FALSE;
			if(GAMEOVER==FALSE&&SPACE==TRUE)
			{
				T_start=CONTINUE; 
				SPACE=FALSE;
			}
			paint_key();
		    }
			else
			paint_key();
		    }
		    else if(x>W-To_right+Key_dis&&x<W-Key_dis&&y>Key_totop+2*(Key_h+Key_key)&&y<Key_totop+Key_key*2+3*Key_h)
		    {
		    color_re=255;
		    if(button==1&&event==0)
			replay_click();
			else if(button==1&&event==2)
			{
			replay();
			kb_or_n=FALSE;
			T_start=START;	
			paint_key();	
			}
			else
			paint_key();
			}
			else if(x>W-To_right+Key_dis&&x<W-Key_dis&&y>Key_totop+3*(Key_h+Key_key)&&y<Key_totop+Key_key*3+4*Key_h)
		    {
		    color_ex=255;
		    if(button==1&&event==0)
			exit_click();
			else if(button==1&&event==2)
			{
			paint_key();
			exit(0);
		    }
			else
			paint_key();
			}
			else
			{
			color_ex=color_st=color_pa=color_re=100;
			paint_key();
		    }
		}
	}
}
void paint_ar(int (*ar)[W_num])
{
	int i,j;
	beginPaint();
	putImageScale(pImage,0,0,W,H);
	setPenColor(BLACK); 
	for(i=1;i<=H_num;i++)
	{
		for(j=1;j<=W_num;j++)
		{		
			if(ar[i-1][j-1]!=0)
			{
			    setBrushColor(ar_color);
			    rectangle((To_left+R_round/2)*j,(To_top+R_round/2)*i,(To_left+R_round/2)*j+Dia_a,(To_top+R_round/2)*i+Dia_a);
		    }	
		}
	}
	endPaint();
	paint_key();
}
