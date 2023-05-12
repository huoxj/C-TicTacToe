#include <cstdio>
#include <graphics.h>
#include <conio.h>

int steps=0;
int mapp[4][4];
int curx,cury;
bool win;

void draw_background(){
    setlinecolor(YELLOW);
    rectangle(50,50,500,500);
    line(200,50,200,500);
    line(350,50,350,500);
    line(50,200,500,200);
    line(50,350,500,350);
    RECT text_rect = {50, 20, 300, 40};
    drawtext("Simple Tic Tac Toe Game by runz",&text_rect,DT_LEFT);
    text_rect={50,510,300,550};
    drawtext("a-left    w-up    s-down  d-right\nenter-confirm      x-quit",&text_rect,DT_LEFT);
}

void draw_cursor(){
    setlinecolor(BLUE);
    setfillcolor(BLUE);
    fillrectangle(52+curx*150,52+cury*150,198+curx*150,198+cury*150);
}

void draw_chess(){
    setlinecolor(WHITE);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(mapp[i][j]==1){
                circle(125+i*150,125+j*150,50);
            }
            if(mapp[i][j]==2){
                line(75+i*150,75+j*150,175+i*150,175+j*150);
                line(175+i*150,75+j*150,75+i*150,175+j*150);
            }
        }
    }
}

void draw_win(){
    setfillcolor(BLACK);
    fillrectangle(70,220,480,320);
    RECT text_rect = {70, 250, 480, 320};
    settextcolor(WHITE);
    if(steps%2==0){
        drawtext("Player 2 Win!",&text_rect,DT_CENTER);
    }else{
        drawtext("Player 1 Win!",&text_rect,DT_CENTER);
    }
    text_rect={70, 280, 480, 300};
    drawtext("Press any key to continue...",&text_rect,DT_CENTER);
}

void draw_draw(){
    setfillcolor(BLACK);
    fillrectangle(70,220,480,320);
    RECT text_rect = {70, 250, 480, 320};
    settextcolor(WHITE);
    drawtext("Draw!",&text_rect,DT_CENTER);
    text_rect={70, 280, 480, 300};
    drawtext("Press any key to continue...",&text_rect,DT_CENTER);
}

bool check_win(){
    for(int i=0;i<3;i++){
        if(mapp[i][0]&&mapp[i][0]==mapp[i][1]&&mapp[i][1]==mapp[i][2])return true;
        if(mapp[0][i]&&mapp[0][i]==mapp[1][i]&&mapp[1][i]==mapp[2][i])return true;
    }
    if(mapp[0][0]&&mapp[0][0]==mapp[1][1]&&mapp[1][1]==mapp[2][2])return true;
    if(mapp[0][2]&&mapp[0][2]==mapp[1][1]&&mapp[1][1]==mapp[2][0])return true;
    return false;
}

void init(){
    steps=0;
    memset(mapp,0,sizeof(mapp));
    curx=0;cury=0;
    win=false;
}

int main()
{
    initgraph(550, 600);
    while(1){//match loop
        init();
        while(1){//step loop
            //draw
            cleardevice();
            draw_background();
            draw_cursor();
            draw_chess();

            //check
            win=check_win();
            if(steps==9){
                draw_draw();
            }
            if(win){
                draw_win();
            }

            //input
            char c=getch();
            if(win||steps==9){
                break;
            }
            if(c=='x'){//exit
                exit(0);
            }
            if(c=='\r'){//confirm
                if(mapp[curx][cury]) continue;
                mapp[curx][cury]=1+steps%2;
                steps++;
            }
            if(c=='w'||c=='a'||c=='s'||c=='d'){//move
                if(c=='w'&&cury>0)cury--;
                if(c=='a'&&curx>0)curx--;
                if(c=='s'&&cury<2)cury++;
                if(c=='d'&&curx<2)curx++;
            }
        }
    }
    return 0;
}