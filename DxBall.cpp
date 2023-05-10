#include"iGraphics.h"

//Screen Attributes
double ScreenHeight=700,ScreenWidth=1200,TopBar=100;

//board Attributes
double board_length=175,board_height=20,board_speed=45;
double xboard=(ScreenWidth-board_length)/2,yboard=50;
double pos;

//Ball Attributes
double rball=8,xball=ScreenWidth/2,yball=(yboard+board_height+rball+1);
double ball_speed=20,theta=30;
double dx=ball_speed*sin(theta*acos(-1)/180),dy=ball_speed*cos(theta*acos(-1)/180);
int life=3;
KenKanekiTheOneEyedGhoul
//state
bool start=false;
bool collided;
bool ball_state=0;
bool magnetic=false;
bool music_on=true;
bool InputBoxSelect=false;
int board_state=0;
int game_screen=0;
int sound_track=1;

/*
Sound Track::
1-->Ethano Papa
2-->Freebee
3-->Mega
*/

/*
board_state::
0--> noraml
1--> small
2-->large
*/

/*
ball_state::
0--> noraml
1--> plasma ball
*/

/*
game_screen::
0--> Main Menu
1--> Game
2--> Options
3--> Help
31-->Help Page-2
4--> High Score Levels
5--> End Screen/Save Score
6-->Pause
11-->Level Select
41-->Show High Score
*/

//Menu
double Continue_h=100;
double Continue_w=493;
double New_Game_h=100;
double New_Game_w=500;
double Exit_h=100;
double Exit_w=229;
double Resume_h=100;
double Resume_w=375;
double Main_Menu_h=100;
double Main_Menu_w=624;
double Help_h=100;
double Help_w=236;
double Options_h=100;
double Options_w=388;
double Sound_h=100;
double Sound_w=329;
double High_Score_h=100;
double High_Score_w=542;
double On_h=100;
double On_w=139;
double Off_h=100;
double Off_w=188;
double Back_h=60;
double Back_w=166;
double Next_h=60;
double Next_w=152;
double InputBox_h=60;
double InputBox_w=200;
double Your_Score_Is_h=60;
double Your_Score_Is_w=433;
double New_High_Score_h=100;
double New_High_Score_w=779;
double Your_Name_h=60;
double Your_Name_w=333;
double Level_Select_h=100;
double Level_Select_w=638;
double Level_1_h=60;
double Level_1_w=220;
double Level_2_h=60;
double Level_2_w=230;
double Level_3_h=60;
double Level_3_w=223;
double Endless_Mode_h=80;
double Endless_Mode_w=610;
double Sound_Track_h=100;
double Sound_Track_w=666;
double Symbol_Next_h=40;
double Symbol_Next_w=82;
double Symbol_Back_h=40;
double Symbol_Back_w=82;
double num_h=100;
double num_w=90;

double xContinue=(ScreenWidth-Continue_w)/2;
double yContinue=ScreenHeight-100;
double xNew_Game=(ScreenWidth-New_Game_w)/2;
double yNew_Game=ScreenHeight-200;
double xOptions=(ScreenWidth-Options_w)/2;
double yOptions=ScreenHeight-300;
double xHelp=(ScreenWidth-Help_w)/2;
double yHelp=ScreenHeight-400;
double xHigh_Score=(ScreenWidth-High_Score_w)/2;
double yHigh_Score=ScreenHeight-500;
double xExit=(ScreenWidth-Exit_w)/2;;
double yExit=ScreenHeight-600;
double xResume=(ScreenWidth-Resume_w)/2;
double yResume=ScreenHeight-200;
double xYour_Score_Is=(ScreenWidth-Your_Score_Is_w)/2+100;
double yYour_Score_Is=ScreenHeight-200;
double xNew_High_Score=(ScreenWidth-New_High_Score_w)/2;
double yNew_High_Score=ScreenHeight-100;
double xYour_Name=(ScreenWidth-Your_Name_w)/2-200;
double yYour_Name=ScreenHeight-300;
double xInputBox=xYour_Name+Your_Name_w+20;
double yInputBox=yYour_Name;

double xNext=900;
double yNext=100;
double xBack=100;
double yBack=100;

double xSound=(ScreenWidth-Sound_w)/2-100;
double ySound=ScreenHeight-150;
double xSound_Track=(ScreenWidth-Sound_Track_w)/2;
double ySound_Track=ScreenHeight-250;
double xOn=(ScreenWidth+Sound_w)/2-100;
double yOn=ScreenHeight-150;
double xOff=(ScreenWidth+Sound_w)/2-100;
double yOff=ScreenHeight-150;
double xMain_Menu=(ScreenWidth-Main_Menu_w)/2;
double yMain_Menu=ScreenHeight-350;

double xnum=(ScreenWidth-num_w)/2;
double ynum=ScreenHeight-350;
double xSymbol_Next=xnum+num_w;
double ySymbol_Next=ynum+30;
double xSymbol_Back=xnum-100;
double ySymbol_Back=ynum+30;


double xLevel_Select=(ScreenWidth-Level_Select_w)/2;
double yLevel_Select=ScreenHeight-100;
double xLevel_1=(ScreenWidth-Level_1_w)/2;
double yLevel_1=ScreenHeight-180;
double xLevel_2=(ScreenWidth-Level_2_w)/2;
double yLevel_2=ScreenHeight-260;
double xLevel_3=(ScreenWidth-Level_3_w)/2;
double yLevel_3=ScreenHeight-340;
double xEndless_Mode=(ScreenWidth-Endless_Mode_w)/2;
double yEndless_Mode=ScreenHeight-500;

//brick & grid
int brick_l=60,brick_h=20;
int grid_r=ScreenHeight/brick_h;//==35
int grid_c=ScreenWidth/brick_l;//==20
int total_cell=grid_r*grid_c;
int total_bricks;

//Brick Structure
struct brickStructure{
  double x,y;
  double dx=brick_l,dy=brick_h;
  bool show=false;
  int health;
  int type;
  int power=-1;
} bricks[1000];

//Power Up
int var;
int pow_num=0;
double pow_h=26;
double pow_w=100;

struct power{
int type; //0-->Extend,1-->Shorten,2-->Fast,3-->Slow,4-->Plasma_Ball,5-->Magnet
int duration=0;
int state=-1; //0-->dropping,1--> in effect
double x;
double y;
}poww[50];

//Score
int score=0;
double xScore=200,yScore=700;
double dis2=30;

//Time
int time_s=0;
int temp,d;
double xclock=1100,yclock=ScreenHeight+TopBar/2-15,dis=30;

//HighScore & Name
bool newHigh=false;
int ind;
int HS[10];
char HSP[100][10];
char s[100];
char name[100];

//Level Select
int level;

//prototype declare
void game_physics();
void defineBricks(int level);
void powerUp();
void save();
void read_score(int level);
void write_score(int level);

void iDraw()
{

    iClear();
    if(game_screen==0) //Menu Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-1.bmp");

        FILE* fptr;
        fptr=fopen("Text Files//continue.txt","r");
        if(fptr == NULL)
        {
            iShowBMP2(xContinue+25,yContinue,"Resources//Menu_Options//Continue-2_red.bmp",0);
        }
        else
        {
            iShowBMP2(xContinue,yContinue,"Resources//Menu_Options//Continue-2.bmp",0);
        }
        fclose(fptr);

        iShowBMP2(xNew_Game,yNew_Game,"Resources//Menu_Options//New_Game-2.bmp",0);
        iShowBMP2(xOptions,yOptions,"Resources//Menu_Options//Options-2.bmp",0);
        iShowBMP2(xHelp,yHelp,"Resources//Menu_Options//Help-2.bmp",0);
        iShowBMP2(xHigh_Score,yHigh_Score,"Resources//Menu_Options//High_Score-2.bmp",0);
        iShowBMP2(xExit,yExit,"Resources//Menu_Options//Exit-2.bmp",0);
    }
    else if(game_screen==1) //Game Screen
    {
        //Background
        glutPassiveMotionFunc(iMouseMove);
        iSetColor(113, 245, 203);
        iFilledRectangle(0,0,ScreenWidth,ScreenHeight);
        iSetColor(0,0,0);
        iFilledRectangle(0,ScreenHeight,ScreenWidth,TopBar);

        //Draw Ball
        if(ball_state==0)
        {
            iShowBMP2(xball-rball,yball-rball,"Resources//Ball_n.bmp",0);
        }
        else if(ball_state==1)
        {
            iShowBMP2(xball-rball,yball-rball,"Resources//Plasma_ball.bmp",0);
        }

        //Draw Board
        if(magnetic==false)
        {
            if(board_state==0)
            {
                iShowBMP2(xboard,yboard,"Resources//Board_n.bmp",0);
            }
            else if(board_state==1)
            {
                iShowBMP2(xboard,yboard,"Resources//Board_s.bmp",0);
            }
            else if(board_state==2)
            {
                iShowBMP2(xboard,yboard,"Resources//Board_l.bmp",0);
            }
        }
        else if(magnetic==true)
        {
            if(board_state==0)
            {
                iShowBMP2(xboard,yboard,"Resources//mBoard_n.bmp",0);
            }
            else if(board_state==1)
            {
                iShowBMP2(xboard,yboard,"Resources//mBoard_s.bmp",0);
            }
            else if(board_state==2)
            {
                iShowBMP2(xboard,yboard,"Resources//mBoard_l.bmp",0);
            }
        }

        //Draw Bricks
        for(int i=0;i<total_cell;i++)
        {
            if(bricks[i].show==true&&bricks[i].type!=0)
            {
                if(bricks[i].type==1)
                {
                    iShowBMP(bricks[i].x,bricks[i].y,"Resources//Red_Tile.bmp");
                }
                else if(bricks[i].type==2)
                {
                    iShowBMP(bricks[i].x,bricks[i].y,"Resources//Green_Tile.bmp");
                }
                else if(bricks[i].type==3)
                {
                    iShowBMP(bricks[i].x,bricks[i].y,"Resources//Blue_Tile.bmp");
                }
                else if(bricks[i].type==4)
                {
                    iShowBMP(bricks[i].x,bricks[i].y,"Resources//Orange_Tile.bmp");
                }
                else if(bricks[i].type==5)
                {
                    if(bricks[i].health==2)
                    {
                        iShowBMP(bricks[i].x,bricks[i].y,"Resources//Gray_Tile.bmp");
                    }
                    else if(bricks[i].health==1)
                    {
                        iShowBMP(bricks[i].x,bricks[i].y,"Resources//Gray-2_Tile.bmp");
                    }
                }
                else if(bricks[i].type==6)
                {
                    if(bricks[i].health==2)
                    {
                        iShowBMP(bricks[i].x,bricks[i].y,"Resources//Brown_Tile.bmp");
                    }
                    else if(bricks[i].health==1)
                    {
                        iShowBMP(bricks[i].x,bricks[i].y,"Resources//Brown-2_Tile.bmp");
                    }
                }

            }
        }

        //Draw Score
        //iShowBMP(100,700,"Resources//Score//Score_.bmp");
        temp=score;
        int i=0;
        while(temp!=0||i<5)
        {
            d=temp%10;
            temp/=10;

            if(d==0)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//0.bmp",0);

            }
            else if(d==1)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//1.bmp",0);

            }
            else if(d==2)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//2.bmp",0);

            }
            else if(d==3)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//3.bmp",0);

            }
            else if(d==4)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//4.bmp",0);

            }
            else if(d==5)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//5.bmp",0);

            }
            else if(d==6)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//6.bmp",0);

            }
            else if(d==7)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//7.bmp",0);

            }
            else if(d==8)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//8.bmp",0);

            }
            else if(d==9)
            {
                   iShowBMP2(xScore-i*dis2,yScore,"Resources//Score//9.bmp",0);

            }

            i++;

        }

        //Clock
        temp=time_s;
        for(int i=0;i<5;i++)
        {
            d=temp%10;
            temp/=10;


            if(d==0)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit0.bmp",0);

            }
            else if(d==1)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit1.bmp",0);

            }
            else if(d==2)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit2.bmp",0);

            }
            else if(d==3)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit3.bmp",0);

            }
            else if(d==4)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit4.bmp",0);

            }
            else if(d==5)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit5.bmp",0);

            }
            else if(d==6)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit6.bmp",0);

            }
            else if(d==7)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit7.bmp",0);

            }
            else if(d==8)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit8.bmp",0);

            }
            else if(d==9)
            {
                   iShowBMP2(xclock-i*dis,yclock,"Resources//digit9.bmp",0);

            }

            if(i==1)
            {
                i++;
                iShowBMP2(xclock-i*dis,yclock,"Resources//colon.bmp",0);
            }
        }

        //Power Up Drop
        if(pow_num>0)
        {
            for(int i=0;i<50;i++)
            {
                if(poww[i].type==0&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Extend.bmp",0);
                }
                else if(poww[i].type==1&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Shorten.bmp",0);
                }
                else if(poww[i].type==2&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Fast.bmp",0);
                }
                else if(poww[i].type==3&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Slow.bmp",0);
                }
                else if(poww[i].type==4&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Plasma_Ball.bmp",0);
                }
                else if(poww[i].type==5&&poww[i].state==0)
                {
                    iShowBMP2(poww[i].x,poww[i].y,"Resources//Power Up//Magnet.bmp",0);
                }
            }
        }

        //life
        for(int i=0;i<life;i++)
        {
            iShowBMP2(550-i*30,750,"Resources//Ball_n.bmp",0);
        }
    }
    else if(game_screen==11) //Level Select
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-2.bmp");
        iShowBMP2(xLevel_Select,yLevel_Select,"Resources//Menu_Options//Level_Select.bmp",0);
        iShowBMP2(xLevel_1,yLevel_1,"Resources//Menu_Options//Level_1.bmp",0);
        iShowBMP2(xLevel_2,yLevel_2,"Resources//Menu_Options//Level_2.bmp",0);
        iShowBMP2(xLevel_3,yLevel_3,"Resources//Menu_Options//Level_3.bmp",0);
        iShowBMP2(xEndless_Mode,yEndless_Mode,"Resources//Menu_Options//Endless_Mode.bmp",0xffffff);

        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
    }
    else if(game_screen==2) //Options Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-2.bmp");
        iShowBMP2(xSound,ySound,"Resources//Menu_Options//Sound-2.bmp",0);

        if(music_on==true)
        {
            iShowBMP2(xOn,yOn,"Resources//Menu_Options//On-2.bmp",0);
        }
        else if(music_on==false)
        {
            iShowBMP2(xOff,yOff,"Resources//Menu_Options//Off-2.bmp",0);
        }
        //iShowBMP2(xMain_Menu,yMain_Menu,"Resources//Menu_Options//Main_Menu.bmp",0);
        iShowBMP2(xSound_Track,ySound_Track,"Resources//Menu_Options//Sound_Track-2.bmp",0);

        if(sound_track==1)
        {
            iShowBMP2(xnum,ynum,"Resources//Menu_Options//1.bmp",0);
        }
        else if(sound_track==2)
        {
            iShowBMP2(xnum,ynum,"Resources//Menu_Options//2.bmp",0);
        }
        else if(sound_track==3)
        {
            iShowBMP2(xnum,ynum,"Resources//Menu_Options//3.bmp",0);
        }
        iShowBMP2(xSymbol_Back,ySymbol_Back,"Resources//Menu_Options//Symbol_Back.bmp",0);
        iShowBMP2(xSymbol_Next,ySymbol_Next,"Resources//Menu_Options//Symbol_Next.bmp",0);
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);

    }
    else if(game_screen==3) //Help Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//Help_Page-1.bmp");
        //iShowBMP2(xMain_Menu,yMain_Menu,"Resources//Menu_Options//Main_Menu.bmp",0);
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
        iShowBMP2(xNext,yNext,"Resources//Menu_Options//Next-2.bmp",0);
    }
    else if(game_screen==31)//Help Screen page-2
    {
        iShowBMP(0,0,"Resources//Back_Ground//Help_Page-2.bmp");
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
    }
    else if(game_screen==4) //High Score Level Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-2.bmp");
        //iShowBMP2(xMain_Menu,yMain_Menu,"Resources//Menu_Options//Main_Menu.bmp",0);
        iSetColor(255,255,255);

        iShowBMP2(xLevel_1,yLevel_1,"Resources//Menu_Options//Level_1.bmp",0);
        iShowBMP2(xLevel_2,yLevel_2,"Resources//Menu_Options//Level_2.bmp",0);
        iShowBMP2(xLevel_3,yLevel_3,"Resources//Menu_Options//Level_3.bmp",0);
        iShowBMP2(xEndless_Mode,yEndless_Mode,"Resources//Menu_Options//Endless_Mode.bmp",0xffffff);


        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
    }
    else if(game_screen==41)//Show High Score Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-2.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(400,350,300,400);
        iSetColor(255,255,255);
        for(int i=0;i<10;i++)
        {
            itoa(i+1,s,10);
            strcat(s,".");
            iText(450,700-i*30,s,GLUT_BITMAP_TIMES_ROMAN_24);
            itoa(HS[i],s,10);
            iText(500,700-i*30,HSP[i],GLUT_BITMAP_TIMES_ROMAN_24);
            iText(600,700-i*30,s,GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
    }
    else if(game_screen==5)//End Screen
    {
        temp=score-time_s*2;
        iShowBMP(0,0,"Resources//Back_Ground//BG-3.bmp");
        iShowBMP2(xYour_Score_Is-220,yYour_Score_Is+20,"Resources//Menu_Options/Your_Score_Is-2.bmp",0);
        int i=0;
        if(temp<0) temp=0;
        while(temp!=0||i<5)
        {
            d=temp%10;
            temp/=10;

            if(d==0)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//0.bmp",0);

            }
            else if(d==1)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//1.bmp",0);

            }
            else if(d==2)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//2.bmp",0);

            }
            else if(d==3)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//3.bmp",0);

            }
            else if(d==4)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//4.bmp",0);

            }
            else if(d==5)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//5.bmp",0);

            }
            else if(d==6)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//6.bmp",0);

            }
            else if(d==7)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//7.bmp",0);

            }
            else if(d==8)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//8.bmp",0);

            }
            else if(d==9)
            {
                   iShowBMP2(xYour_Score_Is+400-i*dis2,yYour_Score_Is,"Resources//Score//9.bmp",0);

            }

            i++;

        }
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);

        //If High Score
        for(int i=0;i<10;i++)
        {
            if(score>HS[i])
            {
                ind=i;
                newHigh=true;
                break;
            }
        }

        if(newHigh==true)
        {
            iShowBMP2(xNew_High_Score,yNew_High_Score,"Resources//Menu_Options//New_High_Score-2.bmp",0);
            iShowBMP2(xYour_Name,yYour_Name,"Resources//Menu_Options//Your_Name-2.bmp",0);
            if(InputBoxSelect==true)
            {
                iSetColor(0,0,0);
                iRectangle(xInputBox,yInputBox,InputBox_w,InputBox_h);
                iText(xInputBox+10,yInputBox+10,name,GLUT_BITMAP_TIMES_ROMAN_24);
            }
            else
            {
                iSetColor(0,0,0);
                iRectangle(xInputBox,yInputBox,InputBox_w,InputBox_h);
            }
        }
    }
    else if(game_screen==6)//Pause Screen
    {
        iShowBMP(0,0,"Resources//Back_Ground//BG-2.bmp");
        iShowBMP2(xResume,yResume,"Resources//Menu_Options//Resume-2.bmp",0);
        iShowBMP2(xBack,yBack,"Resources//Menu_Options//Back-2.bmp",0);
    }

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
    xboard=mx-board_length/2;

    if(xboard<0) xboard=0;
    else if (xboard+board_length>ScreenWidth) xboard=ScreenWidth-board_length;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouse(int button, int state, int mx, int my)
{

    //Menu Screen Click Box
    if(game_screen==0)
    {
        if((mx>=xNew_Game&&mx<=xNew_Game+New_Game_w)&&(my>=yNew_Game&&my<=yNew_Game+New_Game_h)&&(state==GLUT_DOWN))
        {
            life=3;
            time_s=0;
            score=0;
            xboard=(ScreenWidth-board_length)/2;
            xball=ScreenWidth/2,yball=(yboard+board_height+rball+1);
            start=false;
            InputBoxSelect=false;
            theta=30;
            dx=ball_speed*sin(theta*acos(-1)/180);
            dy=ball_speed*cos(theta*acos(-1)/180);

            for(int i=0;i<50;i++)
            {
                poww[i].state=-1;
            }
            game_screen=11;
        }
        else if((mx>=xContinue&&mx<=xContinue+Continue_w)&&(my>=yContinue&&my<=yContinue+Continue_h)&&(state==GLUT_DOWN))
        {

            FILE* fptr;
            fptr=fopen("Text Files//continue.txt","r");
            if(fptr != NULL)
            {
                fclose(fptr);
                defineBricks(0);
                remove("Text Files//continue.txt");
                game_screen=1;
            }

        }
        else if((mx>=xOptions&&mx<=xOptions+Options_w)&&(my>=yOptions&&my<=yOptions+Options_h)&&(state==GLUT_DOWN))
        {
            game_screen=2;
        }
        else if((mx>=xHelp&&mx<=xHelp+Help_w)&&(my>=yHelp&&my<=yHelp+Help_h)&&(state==GLUT_DOWN))
        {
            game_screen=3;
        }
        else if((mx>=xHigh_Score&&mx<=xHigh_Score+High_Score_w)&&(my>=yHigh_Score&&my<=yHigh_Score+High_Score_h)&&(state==GLUT_DOWN))
        {
            game_screen=4;
        }
        else if((mx>=xExit&&mx<=xExit+Exit_w)&&(my>=yExit&&my<=yExit+Exit_h)&&(state==GLUT_DOWN))
        {
            exit(0);
        }

    }
    //Level Select
    else if(game_screen==11)
    {
        if((mx>=xLevel_1&&mx<=xLevel_1+Level_1_w)&&(my>=yLevel_1&&my<=yLevel_1+Level_1_h)&&(state==GLUT_DOWN))
        {
            level=1;
            read_score(level);
            defineBricks(level);
            game_screen=1;

            FILE* fptr;
            fptr=fopen("Text Files//continue.txt","r");
            if(fptr != NULL)
            {
                fclose(fptr);
                remove("Text Files//continue.txt");
            }
        }
        else if((mx>=xLevel_2&&mx<=xLevel_2+Level_2_w)&&(my>=yLevel_2&&my<=yLevel_2+Level_2_h)&&(state==GLUT_DOWN))
        {
            level=2;
            read_score(level);
            defineBricks(level);
            game_screen=1;

            FILE* fptr;
            fptr=fopen("Text Files//continue.txt","r");
            if(fptr != NULL)
            {
                fclose(fptr);
                remove("Text Files//continue.txt");
            }
        }
        else if((mx>=xLevel_3&&mx<=xLevel_3+Level_3_w)&&(my>=yLevel_3&&my<=yLevel_3+Level_3_h)&&(state==GLUT_DOWN))
        {
            level=3;
            read_score(level);
            defineBricks(level);
            game_screen=1;

            FILE* fptr;
            fptr=fopen("Text Files//continue.txt","r");
            if(fptr != NULL)
            {
                fclose(fptr);
                remove("Text Files//continue.txt");
            }
        }
        else if((mx>=xEndless_Mode&&mx<=xEndless_Mode+Endless_Mode_w)&&(my>=yEndless_Mode&&my<=yEndless_Mode+Endless_Mode_h)&&(state==GLUT_DOWN))
        {
            level=100;
            read_score(level);
            defineBricks(level);
            game_screen=1;
            life=1;

            FILE* fptr;
            fptr=fopen("Text Files//continue.txt","r");
            if(fptr != NULL)
            {
                fclose(fptr);
                remove("Text Files//continue.txt");
            }
        }
        else if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=0;
        }
    }
    //Game Screen Click
    else if(game_screen==1)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            start=true;
        }
    }
    //Options
    else if(game_screen==2)
    {
        if((mx>=xSound&&mx<=xSound+Sound_w+Off_w)&&(my>=ySound&&my<=ySound+Sound_h)&&(state==GLUT_DOWN))
        {
            music_on=!music_on;

            if(music_on==true)
            {

                if(sound_track==1&&music_on==true)
                {
                    PlaySound("Resources\\Music\\Ethno_Papa.wav",NULL,SND_LOOP|SND_ASYNC);
                }
                else if(sound_track==2&&music_on==true)
                {
                    PlaySound("Resources\\Music\\Freebee.wav",NULL,SND_LOOP|SND_ASYNC);
                }
                else if(sound_track==3&&music_on==true)
                {
                    PlaySound("Resources\\Music\\Mega.wav",NULL,SND_LOOP|SND_ASYNC);
                }
                }
                else if(music_on==false)
                {
                    PlaySound(0,0,0);
                }
        }
        else if((mx>=xSymbol_Next&&mx<=xSymbol_Next+Symbol_Next_w)&&(my>=ySymbol_Next&&my<=ySymbol_Next+Symbol_Next_h)&&(state==GLUT_DOWN))
        {
            if(sound_track!=3)
            {
                sound_track++;
            }

            if(sound_track==1&&music_on==true)
            {
                PlaySound("Resources\\Music\\Ethno_Papa.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(sound_track==2&&music_on==true)
            {
                PlaySound("Resources\\Music\\Freebee.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(sound_track==3&&music_on==true)
            {
                PlaySound("Resources\\Music\\Mega.wav",NULL,SND_LOOP|SND_ASYNC);
            }
        }
        else if((mx>=xSymbol_Back&&mx<=xSymbol_Back+Symbol_Back_w)&&(my>=ySymbol_Back&&my<=ySymbol_Back+Symbol_Back_h)&&(state==GLUT_DOWN))
        {
            if(sound_track!=1)
            {
                sound_track--;
            }


            if(sound_track==1&&music_on==true)
            {
                PlaySound("Resources\\Music\\Ethno_Papa.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(sound_track==2&&music_on==true)
            {
                PlaySound("Resources\\Music\\Freebee.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(sound_track==3&&music_on==true)
            {
                PlaySound("Resources\\Music\\Mega.wav",NULL,SND_LOOP|SND_ASYNC);
            }
        }
        else if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=0;
        }
    }
    //Help
    else if(game_screen==3)
    {
        if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=0;
        }
        else if((mx>=xNext&&mx<=xNext+Next_w)&&(my>=yNext&&my<=yNext+Next_h)&&(state==GLUT_DOWN))
        {
            game_screen=31;
        }
    }
    else if(game_screen==31)
    {
        if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=3;
        }
    }
    //High Score
    else if(game_screen==4)
    {
        if((mx>=xLevel_1&&mx<=xLevel_1+Level_1_w)&&(my>=yLevel_1&&my<=yLevel_1+Level_1_h)&&(state==GLUT_DOWN))
        {
            level=1;
            read_score(level);
            game_screen=41;
        }
        else if((mx>=xLevel_2&&mx<=xLevel_2+Level_2_w)&&(my>=yLevel_2&&my<=yLevel_2+Level_2_h)&&(state==GLUT_DOWN))
        {
            level=2;
            read_score(level);
            game_screen=41;
        }
        else if((mx>=xLevel_3&&mx<=xLevel_3+Level_3_w)&&(my>=yLevel_3&&my<=yLevel_3+Level_3_h)&&(state==GLUT_DOWN))
        {
            level=3;
            read_score(level);
            game_screen=41;
        }
        else if((mx>=xEndless_Mode&&mx<=xEndless_Mode+Endless_Mode_w)&&(my>=yEndless_Mode&&my<=yEndless_Mode+Endless_Mode_h)&&(state==GLUT_DOWN))
        {
            level=100;
            read_score(level);
            game_screen=41;
        }
        else if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=0;
        }
    }
    else if(game_screen==41)
    {
        if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=4;
        }
    }
    //End Screen/High Score
    else if(game_screen==5)
    {

        if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            game_screen=0;
        }
        else if((mx>=xInputBox&&mx<=xInputBox+InputBox_w)&&(my>=yInputBox&&my<=yInputBox+InputBox_h)&&(state==GLUT_DOWN)&&(newHigh==true))
        {
            InputBoxSelect=true;
            var=0;
        }
        else if(state==GLUT_DOWN)
        {
            InputBoxSelect=false;
            name[0]='\0';
        }

    }
    //Pause screen
    else if(game_screen==6)
    {
        if((mx>=xResume&&mx<=xResume+Resume_w)&&(my>=yResume&&my<=yResume+Resume_h)&&(state==GLUT_DOWN))
        {
            game_screen=1;
        }
        else if((mx>=xBack&&mx<=xBack+Back_w)&&(my>=yBack&&my<=yBack+Back_h)&&(state==GLUT_DOWN))
        {
            save();
            game_screen=0;
        }
    }

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    if(game_screen==1)
    {
        if(key=='p')
        {
            game_screen=6;
        }
    }
    else if(game_screen==5&&InputBoxSelect==true&&key=='\r')
    {
        name[var]='\n';
        for(int i=8;i>=ind;i--)
        {
            HS[i+1]=HS[i];
            strcpy(HSP[i+1],HSP[i]);
        }
        HS[ind]=score-time_s;
        strcpy(HSP[ind],name);

        write_score(level);
    }
    else if(game_screen==5&&InputBoxSelect==true&&key=='\b')
    {
      name[var-1]='\0';
      if(var>0)var--;
    }
    else if(game_screen==5&&InputBoxSelect==true)
    {
        name[var]=key;
        var++;
    }
    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }

    if(key==GLUT_KEY_LEFT)
    {
        xboard-=board_speed;
        if(xboard<0) xboard=0;
    }
    else if(key==GLUT_KEY_RIGHT)
    {
        xboard+=board_speed;
        if(xboard+board_length>ScreenWidth) xboard=ScreenWidth-board_length;
    }
    //place your codes for other keys here
}

void game_physics()
{
    if(game_screen==1)
    {
        if(start==true)
        {
            xball+=dx;
            yball+=dy;

            if(xball<=rball)
            {
                 dx*=(-1);
                 xball=rball;
            }
            else if(xball>=ScreenWidth-rball)
            {
                 dx*=(-1);
                 xball=ScreenWidth-rball;
            }
            else if(yball>=ScreenHeight-rball)
            {
                dy*=(-1);
                yball=ScreenHeight-rball;

            }
            else if(yball<=rball) //Dead
            {
               xboard=(ScreenWidth-board_length)/2;
               xball=ScreenWidth/2,yball=(yboard+board_height+rball+1);
               life--;
               start=false;
            }
            else if((xball>=xboard&&xball<=xboard+board_length)&&(yball<=yboard+rball+board_height))
            {
                theta=(board_length-(xboard-xball))/(board_length/2)*90;

                dx=ball_speed*cos(theta*acos(-1)/180),dy=ball_speed*sin(theta*acos(-1)/180)*(-1);

                yball=(yboard+board_height+rball+1);

                if(magnetic==true)
                {
                    start=false;
                    pos=(xball-xboard)/board_length;
                }
            }

            //Collision
             for(int i=0;i<total_cell;i++)
                {
                    collided=false;
                    if(bricks[i].show==true)
                    {
                        if((xball>=bricks[i].x&&xball<=bricks[i].x+bricks[i].dx)&&(yball+rball>=bricks[i].y&&yball+rball<=bricks[i].y+bricks[i].dy))//from below
                        {
                           if(ball_state==0)
                           {
                                dy*=(-1);
                                yball=bricks[i].y-rball;
                           }
                           collided=true;
                        }
                        else if((xball>=bricks[i].x&&xball<=bricks[i].x+bricks[i].dx)&&(yball-rball>=bricks[i].y&&yball-rball<=bricks[i].y+bricks[i].dy))//from top
                        {
                           if(ball_state==0)
                           {
                               dy*=(-1);
                               yball=bricks[i].y+bricks[i].dy+rball;
                           }
                           collided=true;
                        }
                        else if((xball+rball>=bricks[i].x&&xball+rball<=bricks[i].x+bricks[i].dx)&&(yball>=bricks[i].y&&yball<=bricks[i].y+bricks[i].dy))//from right
                        {
                           if(ball_state==0)
                           {
                               dx*=(-1);
                               xball=bricks[i].x-rball;
                           }
                           collided=true;
                        }
                        else if((xball-rball>=bricks[i].x&&xball-rball<=bricks[i].x+bricks[i].dx)&&(yball>=bricks[i].y&&yball<=bricks[i].y+bricks[i].dy))//from left
                        {
                           if(ball_state==0)
                           {
                               dx*=(-1);
                               xball=bricks[i].x+bricks[i].dx+rball;
                           }
                           collided=true;
                        }

                        if(collided==true)
                        {
                             bricks[i].health--;
                             if(ball_state==1) bricks[i].health=0;

                             if(bricks[i].health==0)
                             {
                                  bricks[i].show=false;
                                  score+=50;
                                  total_bricks--;
                                  bricks[i].type=0;

                                  if(bricks[i].power!=-1)
                                  {
                                      poww[pow_num].type=bricks[i].power;
                                      poww[pow_num].x=bricks[i].x;
                                      poww[pow_num].y=bricks[i].y;
                                      poww[pow_num].state=0;
                                      pow_num++;
                                  }
                             }
                             //PlaySound("Resources\\Music\\hit.wav",NULL,SND_ASYNC);
                             break;
                        }

                    }
                }



        }
        else if(start==false&&magnetic==false)
        {
            xball=xboard+board_length/2;
        }
        else if(start==false&&magnetic==true)
        {
            xball=xboard+pos*board_length;
        }

        if(pow_num>0)
        {
            powerUp();
        }
    }

    if(total_bricks==0&&level==100&&game_screen==1)
    {
        defineBricks(100);
    }
    else if((total_bricks==0||life==0)&&game_screen==1)
    {
        game_screen=5;
    }
}

void powerUp()
{
    for(int i=0;i<50;i++)
    {
        if(poww[i].state==0)
        {
            if((poww[i].x+pow_w>=xboard&&poww[i].x<=xboard+board_length)&&(poww[i].y<=yboard+board_height&&poww[i].y>=yboard))
            {
                poww[i].state=1;
                poww[i].duration=time_s;
            }
        }

        if(poww[i].state==1)
        {
            if(time_s-poww[i].duration<15)
            {
                //Apply PowerUp
                if(poww[i].type==0)
                {
                    board_state=2;
                    board_length=250;
                }
                else if(poww[i].type==1)
                {
                    board_state=1;
                    board_length=100;
                }
                else if(poww[i].type==2)
                {
                    ball_speed=25;
                }
                else if(poww[i].type==3)
                {
                    ball_speed=15;
                }
                else if(poww[i].type==4)
                {
                    ball_state=1;
                }
                else if(poww[i].type==5)
                {
                    magnetic=true;
                }
            }
            else
            {
                if(poww[i].state!=-1)
                {
                    poww[i].state=-1;

                    //Revert PowerUp
                    if(poww[i].type==0)
                    {
                        board_state=0;
                        board_length=175;
                    }
                    else if(poww[i].type==1)
                    {
                        board_state=0;
                        board_length=175;
                    }
                    else if(poww[i].type==2)
                    {
                        ball_speed=20;
                    }
                    else if(poww[i].type==3)
                    {
                        ball_speed=20;
                    }
                    else if(poww[i].type==4)
                    {
                        ball_state=0;
                    }
                    else if(poww[i].type==5)
                    {
                        magnetic=false;
                    }
                }
            }
        }

            poww[i].y-=10;
        }
}

void read_score(int level) //0---> read,1-->write
{
    if(level==1)
    {
        FILE *fptr;
        int val;
        fptr = fopen("Text Files//HighScore_1.txt","r");
        for(int i=0;i<10;i++)
        {
            fscanf(fptr,"%d",&val);
            HS[i]=val;
        }

        fclose(fptr);

        fptr = fopen("Text Files//HS_Player_1.txt","r");
        for(int i=0;i<10;i++)
        {
            fgets(s,20,fptr);
            strcpy(HSP[i],s);
        }

        fclose(fptr);
    }
    else if(level==2)
    {
        FILE *fptr;
        int val;
        fptr = fopen("Text Files//HighScore_2.txt","r");
        for(int i=0;i<10;i++)
        {
            fscanf(fptr,"%d",&val);
            HS[i]=val;
        }

        fclose(fptr);

        fptr = fopen("Text Files//HS_Player_2.txt","r");
        for(int i=0;i<10;i++)
        {
            fgets(s,20,fptr);
            strcpy(HSP[i],s);
        }

        fclose(fptr);
    }
    else if(level==3)
    {
        FILE *fptr;
        int val;
        fptr = fopen("Text Files//HighScore_3.txt","r");
        for(int i=0;i<10;i++)
        {
            fscanf(fptr,"%d",&val);
            HS[i]=val;
        }

        fclose(fptr);

        fptr = fopen("Text Files//HS_Player_3.txt","r");
        for(int i=0;i<10;i++)
        {
            fgets(s,20,fptr);
            strcpy(HSP[i],s);
        }

        fclose(fptr);
    }
    else if(level==100)
    {
        FILE *fptr;
        int val;
        fptr = fopen("Text Files//HighScore_e.txt","r");
        for(int i=0;i<10;i++)
        {
            fscanf(fptr,"%d",&val);
            HS[i]=val;
        }

        fclose(fptr);

        fptr = fopen("Text Files//HS_Player_e.txt","r");
        for(int i=0;i<10;i++)
        {
            fgets(s,20,fptr);
            strcpy(HSP[i],s);
        }

        fclose(fptr);
    }

}

void write_score(int level)
{
        if(level==1)
        {
            FILE *fptr;
            fptr = fopen("Text Files//HighScore_1.txt","w");
            for(int i=0;i<10;i++)
            {
                fprintf(fptr,"%d ",HS[i]);
            }

            fclose(fptr);

            fptr = fopen("Text Files//HS_Player_1.txt","w");
            for(int i=0;i<10;i++)
            {
                fputs(HSP[i],fptr);
            }

            fclose(fptr);
        }
        else if(level==2)
        {
            FILE *fptr;
            fptr = fopen("Text Files//HighScore_2.txt","w");
            for(int i=0;i<10;i++)
            {
                fprintf(fptr,"%d ",HS[i]);
            }

            fclose(fptr);

            fptr = fopen("Text Files//HS_Player_2.txt","w");
            for(int i=0;i<10;i++)
            {
                fputs(HSP[i],fptr);
            }

            fclose(fptr);
        }
        else if(level==3)
        {
            FILE *fptr;
            fptr = fopen("Text Files//HighScore_3.txt","w");
            for(int i=0;i<10;i++)
            {
                fprintf(fptr,"%d ",HS[i]);
            }

            fclose(fptr);

            fptr = fopen("Text Files//HS_Player_3.txt","w");
            for(int i=0;i<10;i++)
            {
                fputs(HSP[i],fptr);
            }

            fclose(fptr);
        }
        else if(level==100)
        {
            FILE *fptr;
            fptr = fopen("Text Files//HighScore_e.txt","w");
            for(int i=0;i<10;i++)
            {
                fprintf(fptr,"%d ",HS[i]);
            }

            fclose(fptr);

            fptr = fopen("Text Files//HS_Player_e.txt","w");
            for(int i=0;i<10;i++)
            {
                fputs(HSP[i],fptr);
            }

            fclose(fptr);
        }
}


//Reads data from file and creates map
void defineBricks(int level)   //0-->Continue , 1-->New
{
    int startx=0,starty=ScreenHeight-brick_h;
    total_bricks=0;

    for(int i=0;i<grid_r;i++)
    {
        for(int j=0;j<grid_c;j++)
        {
            bricks[i*grid_c+j].x=startx+j*bricks[i*grid_c+j].dx;
            bricks[i*grid_c+j].y=starty-i*bricks[i*grid_c+j].dy;
            bricks[i*grid_c+j].show=false;
        }
    }

   int type;
   FILE *fptr;

   if(level==0)
   {

       fptr = fopen("Text Files//c_score&time.txt","r");
       fscanf(fptr,"%d",&score);
       fscanf(fptr,"%d",&time_s);
       fscanf(fptr,"%d",&life);
       fclose(fptr);

       fptr = fopen("Text Files//continue.txt","r");

   }
   else if(level==1)
   {
       fptr = fopen("Text Files//map-1.txt","r");
   }
   else if(level==2)
   {
       fptr = fopen("Text Files//map-2.txt","r");
   }
   else if(level==3)
   {
       fptr = fopen("Text Files//map-3.txt","r");
   }

   if(level!=100)
   {
       srand(time(0));
       for(int i = 0; i < total_cell; i++)
       {
           fscanf(fptr, "%d" ,&type);

           if(type==0)
           {
               bricks[i].type=0;
           }
           else if(type!=0)
           {
                total_bricks++;

                bricks[i].show=true;
                bricks[i].type=type;

                if(bricks[i].type>4)
                {
                    bricks[i].health=2;
                }
                else bricks[i].health=1;

                //Random Power Assign
                var=rand();

                if(var%10==0)
                {
                    var=rand();
                    bricks[i].power=var%6;
                }
            }
       }
    fclose(fptr);
   }
   else if(level==100)
   {
       srand(time(0));
       for(int i=0;i<grid_r;i++)
        {
            for(int j=0;j<grid_c;j++)
            {
                var=rand();
                if(var%4==0&&(i<=20&&i>=3)&&(j>=3&&j<=17))
                {
                    var=rand();
                    bricks[i*grid_c+j].type=(var%6)+1;
                    bricks[i*grid_c+j].show=true;

                    total_bricks++;

                    if(bricks[i*grid_c+j].type>4)
                    {
                        bricks[i*grid_c+j].health=2;
                    }
                    else bricks[i*grid_c+j].health=1;

                    var=rand();

                    if(var%10==0)
                    {
                        var=rand();
                        bricks[i*grid_c+j].power=var%6+1;
                    }
                }
            }
        }
   }
}

void save()
{
    FILE *fptr;
    fptr = fopen("Text Files//continue.txt","w");

    for(int i=0;i<grid_r;i++)
    {
        for(int j=0;j<grid_c;j++)
        {
            fprintf(fptr,"%d ",bricks[i*grid_c+j].type);
        }
    }

    fclose(fptr);

    fptr = fopen("Text Files//c_score&time.txt","w");
    fprintf(fptr,"%d ",score);
    fprintf(fptr,"%d ",time_s);
    fprintf(fptr,"%d ",life);
    fprintf(fptr,"%d ",level);

    fclose(fptr);
}

void clockTime()
{
   if(game_screen==1)
   {
       time_s++;
       if(time_s%100==60) time_s=time_s+40;
   }
}

int main()
{
    //place your own initialization codes here.
    PlaySound("Resources\\Music\\Ethno_Papa.wav",NULL,SND_LOOP|SND_ASYNC);
    iSetTimer(1000,clockTime);
    iSetTimer(25,game_physics);
    iInitialize(ScreenWidth, ScreenHeight+TopBar, "Dx ball");
    return 0;
}
