#include "tetris.h"


//控制台设置
void Set() {
    //设置控制台为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    // 2. 设置控制台字体
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo = {0};
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    wcscpy(fontInfo.FaceName, L"Consolas"); //宋体
    fontInfo.dwFontSize.Y = 16;
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    
    //隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;  // 隐藏光标
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    //设置窗口标题
    SetConsoleTitle("俄罗斯方块游戏");
}



//重启
void RestartGame() {
    printf("\n正在重启游戏...\n");
    Sleep(1000);
    Restart;
    exit(0);
}



//初始化动画
void ShowTitleAnimation() {
    SetConsoleOutputCP(65001);
    system("cls");

    //播放动画序列
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%s\n", TitleAnimation[i][j]);
        }
        Sleep(400);  //每帧显示400毫秒
        system("cls");
    }
    
    //闪烁效果
    for(int blink = 0; blink < 3; blink++) {
        //显示完整帧
        for(int j = 0; j < 9; j++) {
            printf("%s\n", TitleAnimation[9][j]);
        }
        Sleep(300);
        system("cls");
        
        //显示空白帧
        for(int j = 0; j < 9; j++) {
            printf("%s\n", TitleAnimation[10][j]);
        }
        Sleep(300);
        system("cls");
    }
    
    //保持显示完整帧
    for(int j = 0; j < 9; j++) {
        printf("%s\n", TitleAnimation[9][j]);
    }
    printf("\n\n按任意键继续...\n");
    _getch();
    system("cls");
}



//提示
void Warn(){
    while(1){
    //清屏并移动光标到左上角
    system("cls");
    printf("\033[2J\033[H");

    //打印上边框
    printf("┌");
    for(int i=0;i<CMD_LENGTH+25;i++){
        printf("──");
    }
    printf("┐\n");
    
    for(int i=0;i<CMD_HEIGHT+10-1;i++){
        printf("│");
        if(i==20){    
            for(int j=0;j<9;j++){
                printf("  ");
            }
            printf("请将终端调制正好完全显示此矩形大小或是全屏");
            for(int j=0;j<10;j++){
                printf("  ");
            }
            printf("│\n|");
            for(int j=0;j<15;j++){
                printf("  ");
            }
            printf("输入1退出调整模式");
            for(int j=0;j<16;j++){
                printf("  ");
            }
            printf(" │\n");
            continue;
        }
        for(int j=0;j<CMD_LENGTH+25;j++){
                printf("  ");
        }
        printf("│\n");
    }
    
    //打印下边框
    printf("└");
    for(int i=0;i<CMD_LENGTH+25;i++){
        printf("──");
    }
    printf("┘\n");
    char a=_getch();
    if(a=='1'){
        break;
    }
    }    
}



//屏幕显示
void CMD(){
    //清屏并移动光标到左上角
    printf("\033[2J\033[H");

    printf("\n\n");
    //打印上边框
    printf("┌");
    for(int i=0;i<CMD_LENGTH;i++){
        printf("──");
    }
    printf("┐\n");
    
    //打印游戏区域
    for(int i=0;i<CMD_HEIGHT;i++){
        printf("│");
        for(int j=0;j<CMD_LENGTH;j++){
            switch(array[i][j]){
                case 0:
                printf("  "); 
                break;
                case 100:
                printf(BLOCK_RED);
                break;
                case 101:
                printf(BLOCK_GREEN);
                break;
                case 102:
                printf(BLOCK_YELLOW);
                break;
                case 103:
                printf(BLOCK_BLUE);
                break;
                case 104:
                printf(BLOCK_MAGENTA);
                break;
                case 105:
                printf(BLOCK_CYAN);
                break;
                case 106:
                printf(BLOCK_WHITE);
                break;
                case 200:
                printf(BLOCK_RED);
                break;
                case 201:
                printf(BLOCK_GREEN);
                break;
                case 202:
                printf(BLOCK_YELLOW);
                break;
                case 203:
                printf(BLOCK_BLUE);
                break;
                case 204:
                printf(BLOCK_MAGENTA);
                break;
                case 205:
                printf(BLOCK_CYAN);
                break;
                case 206:
                printf(BLOCK_WHITE);
                break;
            }
        }
        printf("│\n");
    }
    
    //打印下边框
    printf("└");
    for(int i=0;i<CMD_LENGTH;i++){
        printf("──");
    }
    printf("┘\n");
    
    //打印游戏说明
    printf("得分: %d    等级: LV.%d    连击: %d/MAX:%d\n\n", score, level, combo, max_combo);
    printf("控制说明：\n");
    printf("A/左箭头: 左移  D/右箭头: 右移  S/下箭头: 加速下落\n");
    printf("I: 逆时针旋转  P: 顺时针旋转  空格:暂停  M: 返回主菜单（暂停时）\n");
    printf("Q: 退出游戏\n");
}
