#include <stdio.h>

#include <conio.h>
#include <math.h> 
#include <process.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <windows.h>





void Set();
void SetupConsole();
void Initialization();
void Blockcreate();
void Revolve_caculate(int y, int x, int a);
int Revolve_Judge(char control);
int CheckGameOver();
void ResetGame();
void ShowGameOver();
void ShowMainMenu();
void ShowSettingsMenu();
void ShowInstructionsMenu();
void ShowPersonalRecords();
void Menu();
void SettingMenu();
void InstructionsMenu();
void PersonalRecords();
void Warn();
void CMD();
void FastDrop(char control);
int CheckLines();
void ShowTitleAnimation();
void UpdateDifficulty();
int Award(int lines_cleared);
void SavePlayerRecord();
void LoadPlayerRecord();
void UpdatePlayerRecord();
void Drop();
void Move(char control);
void Revolve(char control);
int TurnDown();
int TurnLeft();
int TurnRight();
void DeleteRecordConfirm();





//控制台参数
#define CMD_LENGTH      15
#define CMD_HEIGHT      30

//随机数生成
#define BLOCK_Random  (rand()%7)

//颜色处理
#define BLACK          "\033[90m"
#define RED            "\033[91m"
#define GREEN          "\033[92m"
#define YELLOW         "\033[93m"
#define BLUE           "\033[94m"
#define MAGENTA        "\033[95m"
#define CYAN           "\033[96m"
#define WHITE          "\033[97m"
#define COLOR_RESET    "\033[0m"

//方块颜色处理
#define BLOCK_BLACK     BLACK   "[]"       COLOR_RESET
#define BLOCK_RED       RED     "[]"       COLOR_RESET
#define BLOCK_GREEN     GREEN   "[]"       COLOR_RESET
#define BLOCK_YELLOW    YELLOW  "[]"       COLOR_RESET
#define BLOCK_BLUE      BLUE    "[]"       COLOR_RESET
#define BLOCK_MAGENTA   MAGENTA "[]"       COLOR_RESET
#define BLOCK_CYAN      CYAN    "[]"       COLOR_RESET
#define BLOCK_WHITE     WHITE   "[]"       COLOR_RESET

//数据保存
#define SAVE_FILE       "tetris_save.dat"

//重启
#define Restart         system("start TetrisGame.exe")

//初始动画数组
char TitleAnimation[11][9][300] = {
    // 第1帧（显示左侧1/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██                                                                                         │",
        "│    ██╔                                                                                         │",
        "│    ██║                                                                                         │",
        "│    ██║                                                                                         │",
        "│    ╚██████╔╝██                                                                                 │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第2帧（显示左侧2/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████                                                                                     │",
        "│    ██╔═══██╗██                                                                                 │",
        "│    ██║   ██║███                                                                                │",
        "│    ██║   ██║██╔══██╗                                                                           │",
        "│    ╚██████╔╝██║  ██║╚██                                                                        │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第3帧（显示左侧3/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗                                                                            │",
        "│    ██╔═══██╗██╔══██╗██║                                                                        │",
        "│    ██║   ██║██████╔╝██║                                                                        │",
        "│    ██║   ██║██╔══██╗██║   ██║                                                                  │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝████                                                              │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第4帧（显示左侧4/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███                                                               │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔═                                                              │",
        "│    ██║   ██║██████╔╝██║   ██║███████                                                           │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██                                                           │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       █                                                  │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第5帧（显示左侧5/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    █████                                                 │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔═                                               │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   ███                                          │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔═                                         │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   █                                 │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第6帧（显示左侧6/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    ████████╗██████                                       │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔══╝██╔════╝                                     │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   █████╗     ██║                               │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔══╝     ██║   ██╔═══                      │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   ██║   ███████╗█                   │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第7帧（显示左侧7/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    ████████╗███████╗████████╗███                         │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔══╝██╔════╝╚══██╔══╝██╔═══                      │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   █████╗     ██║   █████╗  ████                │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔══╝     ██║   ██╔══╝  ██╔══██╗            │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   ██║   ███████╗██║  ██║██          │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第8帧（显示左侧8/9内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    ████████╗███████╗████████╗███████╗██████╗ ████        │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔══╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗██╔═══      │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   █████╗     ██║   █████╗  ██████╔╝███████╗    │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔══╝     ██║   ██╔══╝  ██╔══██╗╚════██║    │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   ██║   ███████╗██║  ██║███████║    │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
    
    // 第9帧（显示完整内容）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    ████████╗███████╗████████╗███████╗██████╗ ███████╗    │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔══╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗██╔════╝    │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   █████╗     ██║   █████╗  ██████╔╝███████╗    │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔══╝     ██║   ██╔══╝  ██╔══██╗╚════██║    │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   ██║   ███████╗██║  ██║███████║    │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
       
    // 第10帧（闪烁效果 - 全亮）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│     ██████╗ ██████╗ ██╗   ██╗███████╗    ████████╗███████╗████████╗███████╗██████╗ ███████╗    │",
        "│    ██╔═══██╗██╔══██╗██║   ██║██╔════╝    ╚══██╔══╝██╔════╝╚══██╔══╝██╔════╝██╔══██╗██╔════╝    │",
        "│    ██║   ██║██████╔╝██║   ██║███████╗       ██║   █████╗     ██║   █████╗  ██████╔╝███████╗    │",
        "│    ██║   ██║██╔══██╗██║   ██║╚════██║       ██║   ██╔══╝     ██║   ██╔══╝  ██╔══██╗╚════██║    │",
        "│    ╚██████╔╝██║  ██║╚██████╔╝███████║       ██║   ███████╗   ██║   ███████╗██║  ██║███████║    │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },

    // 第11帧（闪烁效果 - 全暗）
    {
        "┌────────────────────────────────────────────────────────────────────────────────────────────────┐",
        "│                                                                                                │",
        "│                                                                                                │",
        "│                                                                                                │",
        "│                                                                                                │",
        "│                                                                                                │",
        "│                                                                                                │",
        "│                                                                                                │",
        "└────────────────────────────────────────────────────────────────────────────────────────────────┘"
    },
};


//玩家记录
typedef struct {
    int highest_score;
    int max_combo;
    int highest_level;
} PlayerRecord;
PlayerRecord player_record;


//坐标位置相关旋转算法                         
int BLOCK_Sort[7][4][2] = {
    {{0,1}, {0,0}, {0,2}, {1,1}},//T型
    {{0,1}, {0,0}, {1,0}, {1,1}},//O型
    {{0,1}, {0,0}, {0,2}, {0,3}},//I型
    {{0,2}, {0,0}, {0,1}, {1,2}},//J型
    {{1,2}, {1,0}, {1,1}, {0,2}},//L型
    {{0,1}, {0,0}, {1,1}, {1,2}},//Z型
    {{1,1}, {1,0}, {0,1}, {0,2}} //S型
};

//变量初始化
int BLOCK_Current[5][2]={0};
int array[CMD_HEIGHT][CMD_LENGTH]={0};
int x_new=0;
int y_new=0;
int score = 0;
bool game_over = false;
bool pause = false;

//计时（下落）
static clock_t last_drop_time = 0;
int drop_interval_ms = 700;

//等级
int level = 1;
int level1= 1;

// 连击数
int combo = 0;
int max_combo = 0;

int speed_setting=0;
int autosaving_setting=1;


void SetupConsole() {
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
}




void Set() {
    SetupConsole();
        
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


//初始化
void Initialization(){
    for(int i=0;i<CMD_HEIGHT;i++) {
        for(int j=0;j<CMD_LENGTH;j++){
            array[i][j]=0;
        }
    }
}


//随机方块生成
void Blockcreate(){
    int Current_sort_shape;
    //随机形状
    Current_sort_shape=BLOCK_Random;
    //随机颜色
    BLOCK_Current[4][0]=BLOCK_Random;
    for(int i=0;i<4;i++){
        BLOCK_Current[i][0]=BLOCK_Sort[Current_sort_shape][i][0]+1;
        BLOCK_Current[i][1]=BLOCK_Sort[Current_sort_shape][i][1]+CMD_LENGTH/2-1;
    }
}


//旋转后坐标计算
void Revolve_caculate(int y, int x, int a){
    int y_basepoint=BLOCK_Current[0][0];
    int x_basepoint=BLOCK_Current[0][1];

    if(a){//a=1时顺时针旋转
        y_new=y_basepoint+(x-x_basepoint);
        x_new=x_basepoint-(y-y_basepoint);
    }
    if(!a){//a=0时逆时针旋转
        y_new=y_basepoint-(x-x_basepoint);
        x_new=x_basepoint+(y-y_basepoint);
    }
}


//旋转判断
int Revolve_Judge(char control){
    if(control=='i'){
        return 0;//逆时针
    }
    if(control=='p'){
        return 1;//顺时针
    }
}



// 检查游戏结束条件
int CheckGameOver() {
    // 检查顶部是否有方块堆积
    for(int j = 0; j < CMD_LENGTH; j++) {
        if(array[2][j]>10 && array[2][j]<150 ) {
            return 1; // 游戏结束
        }
    }
    return 0;
}



//数据初始化
void ResetGame() {
    Initialization();
    score = 0;
    combo = 0;
    max_combo = 0;
    level = 1;
    level1 = 1;
    game_over = false;
    pause = false;
    last_drop_time = clock();
    switch (speed_setting){
        case 0:
        drop_interval_ms = 700;
        break;
        case 1:
        drop_interval_ms = 600;
        break;
        case 2:
        drop_interval_ms = 500;
        break;
        }
}



//游戏结束画面
void ShowGameOver() {
    printf("\n\n");
    printf("╔════════════════════════════════════╗\n");
    printf("║         G A M E   O V E R          ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║                                    ║\n");
    printf("║         最终得分: %6d           ║\n", score);
    printf("║         最高等级: LV. %2d           ║\n", level);
    printf("║         最大连击: %6d           ║\n", max_combo);
    printf("║                                    ║\n");
    if( autosaving_setting){printf("║            自动保存成功            ║\n");}
    if(!autosaving_setting){printf("║           自动保存已关闭           ║\n");}
    printf("║                                    ║\n");
    printf("║         R - 重新开始               ║\n");
    printf("║         M - 返回主菜单             ║\n");
    printf("║         Q - 退出游戏               ║\n");
    printf("║                                    ║\n");
    printf("╚════════════════════════════════════╝\n");
}



//菜单界面
void ShowMainMenu() {
    printf("┌──────────────────────────────────┐\n");
    printf("│         俄罗斯方块 v2.0          │\n");
    printf("├──────────────────────────────────┤\n");
    printf("│  1. 开始游戏                     │\n");
    printf("│  2. 游戏设置                     │\n");
    printf("│  3. 高分记录                     │\n");
    printf("│  4. 游戏说明                     │\n");
    printf("│  5. 重启游戏                     │\n");
    printf("│  6. 退出游戏                     │\n");
    printf("└──────────────────────────────────┘\n");
}



//设置界面
void ShowSettingsMenu() {
    printf("┌─────────────────────────────────────────────────────────┐\n");
    printf("│                      游戏设置                           │\n");
    printf("├─────────────────────────────────────────────────────────┤\n");
    printf("│  1. 下落速度: [慢]   [中]   [快]                        │\n");
    printf("│  2. 自动保存: [开启] [关闭]                             │\n");
    printf("│                                                         │\n");
    printf("│  3. 保存设置并返回主菜单                                │\n");
    printf("│  4. 恢复默认设置                                        │\n");
    printf("│                                                         │\n");
    printf("└─────────────────────────────────────────────────────────┘\n");
    printf("请选择 [1-4]: \n");
}



//说明界面
void ShowInstructionsMenu() {
    printf("┌────────────────────────────────────────────────────────────────┐\n");
    printf("│                       游戏说明与操作指南                       │\n");
    printf("├────────────────────────────────────────────────────────────────┤\n");
    printf("│                                                                │\n");
    printf("│  ▓▓▓▓  游戏目标：                                              │\n");
    printf("│  ▓▓▓▓  1. 通过移动和旋转方块，填满整行进行消除                 │\n");
    printf("│  ▓▓▓▓  2. 一次消除的行数越多，得分越高                         │\n");
    printf("│  ▓▓▓▓  3. 连续消除会触发连击奖励                               │\n");
    printf("│  ▓▓▓▓  4. 避免方块堆积到顶部导致游戏结束                       │\n");
    printf("│                                                                │\n");
    printf("│  ────────────────────────────────────────────────              │\n");
    printf("│                                                                │\n");
    printf("│  ▓▓▓▓  基本操作：                                              │\n");
    printf("│  ▓▓▓▓  A / ←  : 方块向左移动                                   │\n");
    printf("│  ▓▓▓▓  D / →  : 方块向右移动                                   │\n");
    printf("│  ▓▓▓▓  S / ↓  : 方块加速下落                                   │\n");
    printf("│  ▓▓▓▓  W / ↑  : 方块立即下落（硬降）                           │\n");
    printf("│  ▓▓▓▓  I      : 逆时针旋转                                     │\n");
    printf("│  ▓▓▓▓  P      : 顺时针旋转                                     │\n");
    printf("│  ▓▓▓▓  空格键 : 暂停游戏                                       │\n");
    printf("│  ▓▓▓▓  Q      : 退出游戏                                       │\n");
    printf("│                                                                │\n");
    printf("│  ────────────────────────────────────────────────              │\n");
    printf("│                                                                │\n");
    printf("│  ▓▓▓▓  得分规则：                                              │\n");
    printf("│  ▓▓▓▓  消除1行  : 100分                                        │\n");
    printf("│  ▓▓▓▓  消除2行  : 300分                                        │\n");
    printf("│  ▓▓▓▓  消除3行  : 500分                                        │\n");
    printf("│  ▓▓▓▓  消除4行  : 800分                                        │\n");
    printf("│  ▓▓▓▓  MAX_Combo加成 : 刷新最大连击数时分数翻倍                │\n");
    printf("│                                                                │\n");
    printf("│  ────────────────────────────────────────────────              │\n");
    printf("│                                                                │\n");
    printf("│  ▓▓▓▓  小贴士：                                                │\n");
    printf("│  ▓▓▓▓  • 尽量留出中间位置放置长条方块（I型）                   │\n");
    printf("│  ▓▓▓▓  • 注意提前规划方块的放置位置                            │\n");
    printf("│  ▓▓▓▓  • 连续Combo可以获得超高分数                             │\n");
    printf("│                                                                │\n");
    printf("│                      [0] 返回主菜单                            │\n");
    printf("│                                                                │\n");
    printf("└────────────────────────────────────────────────────────────────┘\n");
}



//记录界面
void ShowPersonalRecords() {
    printf("┌─────────────────────────────────────────────┐\n");
    printf("│                个人最高记录                 │\n");
    printf("├─────────────────────────────────────────────┤\n");
    printf("│                                             │\n");
    printf("│          ┌──────────────────┐               │\n");
    printf("│          │  最高分数:       │               │\n");
    printf("│          │  %8d 分     │               │\n",player_record.highest_score);
    printf("│          └──────────────────┘               │\n");
    printf("│                                             │\n");
    printf("│          ┌──────────────────┐               │\n");
    printf("│          │  最大连击:       │               │\n");
    printf("│          │      %4d 连击   │               │\n", player_record.max_combo);
    printf("│          └──────────────────┘               │\n");
    printf("│                                             │\n");
    printf("│          ┌──────────────────┐               │\n");
    printf("│          │  最高等级:       │               │\n");
    printf("│          │       LV.%2d      │               │\n",player_record.highest_level);
    printf("│          └──────────────────┘               │\n");
    printf("│                                             │\n");
    printf("├─────────────────────────────────────────────┤\n");
    printf("│                                             │\n");
    printf("│          [1] 重置记录                       │\n");
    printf("│                                             │\n");
    printf("│          [0] 返回主菜单                     │\n");
    printf("│                                             │\n");
    printf("└─────────────────────────────────────────────┘\n");
}



// 删除确认
void ShowDeleteRecordConfirm() {
    system("cls");
    printf("┌─────────────────────────────────────────────────────┐\n");
    printf("│                   记录删除确认                      │\n");
    printf("├─────────────────────────────────────────────────────┤\n");
    printf("│                                                     │\n");
    printf("│       您确定要删除所有游戏记录吗？                  │\n");
    printf("│                                                     │\n");
    printf("│   将永久删除：                                      │\n");
    printf("│     • 最高分数: %6d 分                           │\n", player_record.highest_score);
    printf("│     • 最大连击: %6d 次                           │\n", player_record.max_combo);
    printf("│     • 最高等级:  LV.%2d                              │\n", player_record.highest_level);
    printf("│                                                     │\n");
    printf("│   ──────────────────────────────────────            │\n");
    printf("│                                                     │\n");
    printf("│   [Y] 是的，删除所有记录                            │\n");
    printf("│   [N] 不，取消操作                                  │\n");
    printf("│                                                     │\n");
    printf("└─────────────────────────────────────────────────────┘\n");
    printf("请选择 [Y/N]: ");
}



//菜单界面
void Menu(){
    while(1){
        system("cls");
        ShowMainMenu();
        printf("\n请选择：");
        char a=_getch();
        switch (a){
        case '1':
        return;
        case '2':
        SettingMenu();
        break;
        case '3':
        PersonalRecords();
        break;
        case '4':
        InstructionsMenu();
        break;
        case '5':
        RestartGame();
        break;
        case '6':
        exit(0);
        }
        Sleep(100);
    }
}

//设置界面
void SettingMenu(){
    while(1){
        system("cls");
        ShowSettingsMenu();

        //下落速度
        printf("当前下落速度：");
        if(speed_setting==3){speed_setting=0;}
        switch (speed_setting){
        case 0:
        printf("[慢]\n");
        break;
        case 1:
        printf("[中]\n");
        break;
        case 2:
        printf("[快]\n");
        break;
        }

        //自动保存状态
        printf("当前自动保存状态：");
        if(autosaving_setting==2){autosaving_setting=0;}
        switch (autosaving_setting){
        case 0:
        printf("[关]\n");
        break;
        case 1:
        printf("[开]\n");
        break;
        }

        //输入获取
        printf("\n请选择：");
        char a=_getch();
        switch (a){
        case '1':
        speed_setting++;
        break;
        case '2':
        autosaving_setting++;
        break;
        case '3':
        return;        
        case '4':
        speed_setting=0;
        autosaving_setting=1;
        break;
        }
        Sleep(100);
    }
}



//说明书
void InstructionsMenu() {
    system("cls");
    ShowInstructionsMenu();
    while(1){
        //输入获取
        char a=_getch();
        if(a=='0'){return;}
        Sleep(100);
    }
}



//个人纪录
void PersonalRecords(){
    system("cls");
    ShowPersonalRecords();
    while(1){
        //输入获取
        char a=_getch();
        if(a=='0'){return;}
        if(a=='1'){
            DeleteRecordConfirm();
            system("cls");
            ShowPersonalRecords();
        }
        Sleep(100);
    }
}



//记录删除
void DeleteRecordConfirm(){
    system("cls");
    ShowDeleteRecordConfirm();
    while(1){
        //输入获取
        char a=_getch();
        if(a=='N'||a=='n'){return;}
        //文件删除
        if(a=='Y'||a=='y'){
            printf("正在删除...\n");
            if(remove(SAVE_FILE) == 0) {
                printf("删除成功！\n");
            } 
            else {
                printf("删除失败。\n文件不存在或路径错误。\n");
            }
            printf("按任意键返回\n");
            _getch();
            player_record.highest_score = 0;
            player_record.max_combo = 0;
            player_record.highest_level = 1;
            return;
        }
        Sleep(100);
    }
}



//可行性验证
//下移
int TurnDown(){
    for(int i=0;i<4;i++) {
        int nextY = BLOCK_Current[i][0]+1;
        int x = BLOCK_Current[i][1];
        if(nextY>=CMD_HEIGHT){
            return 0;
        }//下边界判断
        if(nextY<CMD_HEIGHT&&(array[nextY][x]>10&&array[nextY][x]<150)){
            return 0;
        }//其他方块判断
    }
    return 1;
}
//左移
int TurnLeft(){
    for(int i=0;i<4;i++) {
        int nextX = BLOCK_Current[i][1]-1;
        int y = BLOCK_Current[i][0];
        if(nextX<0){
            return 0;
        }//左边界判断
        if(nextX>=0&&(array[y][nextX]>10&&array[y][nextX]<150)){
            return 0;
        }//其他方块判断
    }
    return 1;
}
//右移
int TurnRight(){
    for(int i=0;i<4;i++) {
        int nextX = BLOCK_Current[i][1]+1;
        int y = BLOCK_Current[i][0];
        if(nextX>=CMD_LENGTH){
            return 0;
        }//左边界判断
        if(nextX<CMD_LENGTH&&(array[y][nextX]>10&&array[y][nextX]<150)){
            return 0;
        }//其他方块判断
    }
    return 1;
}




//移动操作
//下落
void Drop(){
    if(TurnDown()){
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=0;
            BLOCK_Current[i][0]=BLOCK_Current[i][0]+1;
        }
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=200+BLOCK_Current[4][0];
        }
    }
    else{
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=100+BLOCK_Current[4][0];
        }
    }
}
//左右移动
void Move(char control){
    if((control=='a') && TurnLeft()){
    for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=0;
            BLOCK_Current[i][1]=BLOCK_Current[i][1]-1;
        }
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=200+BLOCK_Current[4][0];
        }
    }//向左移动
    if((control=='d') && TurnRight()){
    for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=0;
            BLOCK_Current[i][1]=BLOCK_Current[i][1]+1;
        }
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=200+BLOCK_Current[4][0];
        }
    }//向右移动
}
// 旋转操作
void Revolve(char control){
    //保存原始位置
    int original_pos[4][2];
    for(int i=0;i<4;i++){
        original_pos[i][0] = BLOCK_Current[i][0];
        original_pos[i][1] = BLOCK_Current[i][1];
    }
    
    //计算旋转后的位置
    for(int i=1;i<4;i++){
        int y = BLOCK_Current[i][0];
        int x = BLOCK_Current[i][1];
        Revolve_caculate(y, x, Revolve_Judge(control));
        BLOCK_Current[i][0] = y_new;
        BLOCK_Current[i][1] = x_new;
    }
    
    //检查旋转后位置是否合法
    int valid = 1;
    for(int i=0;i<4;i++){
        int y = BLOCK_Current[i][0];
        int x = BLOCK_Current[i][1];
        
        //检查边界
        if(y<0 || y>=CMD_HEIGHT || x<0 || x>=CMD_LENGTH){
            valid = 0;
            break;
        }
        
        // 检查已固定方块
        if(array[y][x]>=100 && array[y][x]<=106){
            valid = 0;
            break;
        }
    }
    
    //如果不合法，尝试偏移
    if(!valid) {
        //尝试5种偏移
        int offsets[5][2] = {
            {0, 0},    //原始位置
            {0, -1},   //向左微调
            {0, 1},    //向右微调
            {-1, 0},   //向上微调
            {1, 0}     //向下微调
        };
    
        int kick_success = 0;
        
        //对每种偏移进行尝试
        for(int kick = 0; kick < 5; kick++) {
            //重新计算原始位置
            int temp_pos[4][2];
            for(int i=0;i<4;i++){
                temp_pos[i][0] = original_pos[i][0];
                temp_pos[i][1] = original_pos[i][1];
            }
            
            //重新计算旋转位置
            for(int i=1;i<4;i++){
                int y = temp_pos[i][0];
                int x = temp_pos[i][1];
                Revolve_caculate(y, x, Revolve_Judge(control));
                temp_pos[i][0] = y_new;
                temp_pos[i][1] = x_new;
            }
            
            //应用偏移
            for(int i=0;i<4;i++){
                temp_pos[i][0] += offsets[kick][0];
                temp_pos[i][1] += offsets[kick][1];
            }
            
            //检查这个位置是否合法
            int temp_valid = 1;
            for(int i=0;i<4;i++){
                int y = temp_pos[i][0];
                int x = temp_pos[i][1];
                
                if(y < 0 || y >= CMD_HEIGHT || x < 0 || x >= CMD_LENGTH){
                    temp_valid = 0;
                    break;
                }
                
                if(array[y][x] >= 100 && array[y][x] <= 106){
                    temp_valid = 0;
                    break;
                }
            }
            
            //如果找到一个合法的位置
            if(temp_valid) {
                kick_success = 1;
                //更新方块位置
                for(int i=0;i<4;i++){
                    BLOCK_Current[i][0]=temp_pos[i][0];
                    BLOCK_Current[i][1]=temp_pos[i][1];
                }
                valid=1; //标记为合法
                break;
            }
        }
        
        //如果所有尝试都失败，恢复原始位置
        if(!kick_success) {
            for(int i=0;i<4;i++){
                BLOCK_Current[i][0] = original_pos[i][0];
                BLOCK_Current[i][1] = original_pos[i][1];
            }
            return; // 不执行后续的数组更新
        }
    }
    
    //执行实际的方块移动
    //清除原位置
    for(int i=1;i<4;i++){
        int y = original_pos[i][0];
        int x = original_pos[i][1];
        //确保在边界内
        if(y >= 0 && y < CMD_HEIGHT && x >= 0 && x < CMD_LENGTH) {
            array[y][x] = 0;
        }
    }
    
    // 绘制新位置
    for(int i=0;i<4;i++){
        int y = BLOCK_Current[i][0];
        int x = BLOCK_Current[i][1];
        // 确保在边界内
        if(y >= 0 && y < CMD_HEIGHT && x >= 0 && x < CMD_LENGTH) {
            array[y][x] = 200 + BLOCK_Current[4][0];
        }
    }
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
    printf("得分: %d    等级: LV.%d    连击: %d/%d\n\n", score, level, combo, max_combo);
    printf("控制说明：\n");
    printf("A/左箭头: 左移  D/右箭头: 右移  S/下箭头: 加速下落\n");
    printf("I: 逆时针旋转  P: 顺时针旋转  空格:暂停  M: 返回主菜单（暂停时）\n");
    printf("Q: 退出游戏\n");
}



//按s后直接下落
void FastDrop(char control){
    if(control=='s'){
    while(TurnDown()){
        for(int i=0;i<4;i++){
            array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=0;
            BLOCK_Current[i][0]=BLOCK_Current[i][0]+1;
        }
    }
    for(int i=0;i<4;i++){
        array[BLOCK_Current[i][0]][BLOCK_Current[i][1]]=100+BLOCK_Current[4][0];
    }
    }
}



//消行判断与操作
int CheckLines(){
    int lines_cleared = 0;
    for(int i=CMD_HEIGHT-1;i>=0;i--){
        int full = 1;
        for(int j=0;j<CMD_LENGTH;j++){
            if(array[i][j] == 0){
                full = 0;
                break;
            }
        }
        if(full){
            lines_cleared++;
            //将上面的行下移
            for(int k=i;k>0;k--){
                for(int j=0;j<CMD_LENGTH;j++){
                    array[k][j] = array[k-1][j];
                }
            }
            //清空最顶行
            for(int j=0;j<CMD_LENGTH;j++){
                array[0][j] = 0;
            }
            i++; //重新检查当前行
        }
    }
    return lines_cleared;
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



// 根据分数调整难度
void UpdateDifficulty() {
    level = score / 800 + 1;
    if(level!=level1 && drop_interval_ms > 100 ){
        drop_interval_ms=drop_interval_ms-100;
        level1++;
    }
    //每800分时难度提升，下落速度变快100ms
}



//得分规则
int Award(int lines_cleared){
    int base_score = 0;
    //基础得分100分
    //连击分别为300分、500分、800分
    //超过800分的部分为每行300分
    switch(lines_cleared) {
        case 0: base_score =  0 ; break;//连击加倍奖励
        case 1: base_score = 100; break;
        case 2: base_score = 300; break;  
        case 3: base_score = 500; break;
        case 4: base_score = 800; break;
        default: base_score = (lines_cleared-4)*300+800;
    }
    //如果最大连击数刷新则获取分数翻倍
    if(combo > max_combo){base_score=base_score*2;}
    max_combo = (combo > max_combo ? combo : max_combo);
    return base_score;
}



//保存玩家记录到文件
void SavePlayerRecord() {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file == NULL) {
        return;  // 保存失败
    }
    
    // 写入记录
    fwrite(&player_record, sizeof(PlayerRecord), 1, file);
    fclose(file);
}



//从文件加载玩家记录
void LoadPlayerRecord() {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        // 文件不存在，初始化默认记录
        player_record.highest_score = 0;
        player_record.max_combo = 0;
        player_record.highest_level = 1;
        return;
    }
    
    // 读取记录
    fread(&player_record, sizeof(PlayerRecord), 1, file);
    fclose(file);
}



// 更新最高记录
void UpdatePlayerRecord() {
    int updated = 0;
    
    // 检查并更新最高分数
    if (score > player_record.highest_score) {
        player_record.highest_score = score;
        updated = 1;
    }
    
    // 检查并更新最大连击
    if (max_combo > player_record.max_combo) {
        player_record.max_combo = max_combo;
        updated = 1;
    }
    
    // 检查并更新最高等级
    if (level > player_record.highest_level) {
        player_record.highest_level = level;
        updated = 1;
    }
    
    // 如果有更新，保存到文件
    if (updated && autosaving_setting ) {
        SavePlayerRecord();
    }
}



int main() {
    //设置控制台编码
    SetConsoleOutputCP(65001);

    //设置终端
    Set();
    
    //显示开场动画
    ShowTitleAnimation();
    
    //加载玩家记录
    LoadPlayerRecord();

    //画面调整
    Warn();
    
    //随机数种子
    srand((unsigned int)time(NULL));

    //显示主菜单
    Menu();

    //游戏开始
    printf("1\n游戏开始！\n");
    printf("当前设置：速度- %s，自动保存- %s\n",
        speed_setting      == 0 ?   "[慢]" : (speed_setting == 1 ? "[中]" : "[快]"),
        autosaving_setting == 0 ?   "[关]" : "[开]");
    printf("按任意键开始...");
    _getch();
    system("cls");
    

    //游戏主循环
    while(1) {
        // 重置游戏状态
        ResetGame();
        
        // 生成第一个方块
        Blockcreate();
        
        // 上一次的数组状态，用于比较是否变化
        int prev_array[CMD_HEIGHT][CMD_LENGTH] = {0};

        // 重置计时
        last_drop_time = clock();
        
        // 游戏主循环
        while(!game_over) {
            // 处理键盘输入
            int input_processed = 0; // 标记是否有输入处理
            if(_kbhit()) {
                int ch = _getch(); // 改为int类型以支持特殊键
                input_processed = 1;
                
                // 处理扩展键码
                if(ch == 0xE0 || ch == 0) {
                    ch = _getch(); // 获取真正的键码
                    switch(ch) {
                        case 75: // 左箭头
                            Move('a');
                            break;
                        case 77: // 右箭头
                            Move('d');
                            break;
                        case 80: // 下箭头
                            FastDrop('s');
                            break;
                        default:
                            input_processed = 0;
                    }
                } 
                else {
                    // 普通按键
                    switch(ch) {
                        case 'a':
                        case 'A':
                            Move('a');
                            break;
                        case 'd':
                        case 'D':
                            Move('d');
                            break;
                        case 's':
                        case 'S':
                            FastDrop('s');
                            break;
                        case 'i':
                        case 'I':
                            Revolve('i');
                            break;
                        case 'p':
                        case 'P':
                            Revolve('p');
                            break;
                        case ' ': // 空格键暂停
                            pause = true;
                            break;
                        case 'q':
                        case 'Q':
                            return 0;
                        default:
                            input_processed = 0;
                    }
                }
            }
            
            // 检查数组是否有变化
            int array_changed = input_processed; // 如果有输入处理，数组可能变化
            if(!array_changed) {
                // 比较当前数组和之前数组
                for(int i = 0; i < CMD_HEIGHT; i++) {
                    for(int j = 0; j < CMD_LENGTH; j++) {
                        if(array[i][j] != prev_array[i][j]) {
                            array_changed = 1;
                            break;
                        }
                    }
                    if(array_changed){break;} 
                }
            }

            //游戏难度调整
            UpdateDifficulty();


            //等时下落
            //当前时间获取            
            clock_t current_time = clock();
            int elapsed_ms = current_time - last_drop_time ;

            //控制下落速度（每700毫秒下落一次（初始））
            if(elapsed_ms >= drop_interval_ms) { 
                if(TurnDown()) {
                    Drop();
                    array_changed = 1;
                    last_drop_time = current_time;
                } 
                else {
                    // 方块无法下落，固定并检查消行
                    int block_placed = 0;
                    for(int i = 0; i < 4; i++) {
                        int y = BLOCK_Current[i][0];
                        int x = BLOCK_Current[i][1];
                        if(y >= 0 && y < CMD_HEIGHT && x >= 0 && x < CMD_LENGTH) {
                            array[y][x] = 100+BLOCK_Current[4][0];
                            block_placed = 1;
                        }
                    }
                    
                    if(block_placed) {
                        array_changed = 1; 
                        
                        // 检查并清除完整的行
                        int lines_cleared = CheckLines();
                        
                        //分数更新
                        score+=Award(lines_cleared);
                        
                        // 生成新方块
                        Blockcreate();
                        
                        // 检查游戏是否结束
                        game_over = CheckGameOver();
                        
                        //重新计时
                        last_drop_time = current_time;
                    }
                }  
            }
            

            // 只有在数组变化时才更新画面
            if(array_changed) {
                // 更新之前数组状态
                for(int i = 0; i < CMD_HEIGHT; i++) {
                    for(int j = 0; j < CMD_LENGTH; j++) {
                        prev_array[i][j] = array[i][j];
                    }
                }
                
                // 显示游戏界面
                system("cls");
                CMD();
                printf("\n！！！！！难度提升到 LV.%d！！！！！\n", level);
            }


            //暂停
            if(pause) {
                printf("\n游戏暂停中...按空格键继续\n");
                while(pause) {
                    if(_kbhit()) {
                        char ch = _getch();
                        if(ch == ' ' || ch == 32) {
                            pause = false;
                            system("cls"); // 清除暂停信息
                        }
                        if(ch == 'q' || ch == 'Q') {
                            return 0;    // 退出游戏
                        }
                        if(ch == 'm' || ch == 'M') {
                        ResetGame();
                        Menu(); 
                        printf("1\n游戏开始！\n");
                        printf("当前设置：速度- %s，自动保存- %s\n",
                                speed_setting      == 0 ?   "[慢]" : (speed_setting == 1 ? "[中]" : "[快]"),
                                autosaving_setting == 0 ?   "[关]" : "[开]");
                        printf("按任意键开始...");
                        _getch();
                        system("cls");
                        Blockcreate();
                        break;// 返回主菜单
                        }
                    }
                    Sleep(100);
                }
                continue;
            }
            
            // 控制游戏速度 - 稍微加快主循环速度
            Sleep(1);
        }
        
        // 游戏结束后的处理
        system("cls");
        UpdatePlayerRecord();
        ShowGameOver();
        
        // 等待玩家选择
        while(1) {
            if(_kbhit()) {
                char ch = _getch();
                if(ch == 'r' || ch == 'R') {
                    system("cls");
                    ResetGame();
                    break; // 重新开始游戏
                } else if(ch == 'q' || ch == 'Q') {
                    return 0; // 退出游戏
                }else if(ch == 'm' || ch == 'M') {
                    ResetGame();
                    Menu(); 
                    //游戏开始
                    printf("1\n游戏开始！\n");
                    printf("当前设置：速度- %s，自动保存- %s\n",
                        speed_setting      == 0 ?   "[慢]" : (speed_setting == 1 ? "[中]" : "[快]"),
                        autosaving_setting == 0 ?   "[关]" : "[开]");
                    printf("按任意键开始...");
                    _getch();
                    system("cls");
                    break;// 返回主菜单
                }  
            }
            Sleep(100);
        }
    }
    
    return 0;
}