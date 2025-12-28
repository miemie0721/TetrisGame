#ifndef TETRIS_H
#define TETRIS_H

//头文件
#include <stdio.h>

#include <conio.h>
#include <math.h> 
#include <process.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 
#include <windows.h>

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
#define Restart         system("start tetris.exe")

//函数声明
void Set(void);
void RestartGame(void); 
void Initialization(void);
void Blockcreate(void);
void Revolve_caculate(int y, int x, int a);
int Revolve_Judge(char control);
int CheckGameOver(void) ;
void ResetGame(void) ;
void ShowGameOver(void);
void ShowMainMenu(void) ;
void ShowSettingsMenu(void);
void ShowInstructionsMenu(void);
void ShowPersonalRecords(void);
void ShowDeleteRecordConfirm(void);
void Menu(void);
void SettingMenu(void);
void InstructionsMenu(void) ;
void PersonalRecords(void);
void DeleteRecordConfirm(void);
int TurnDown(void);
int TurnLeft(void);
int TurnRight(void);
void Drop(void);
void Move(char control);
void Revolve(char control);
void Warn(void);
void CMD(void);
void FastDrop(char control);
int CheckLines(void);
void ShowTitleAnimation(void) ;
void UpdateDifficulty(void) ;
int Award(int lines_cleared);
void SavePlayerRecord(void) ;
void LoadPlayerRecord(void) ;
void UpdatePlayerRecord(void) ;


//初始动画数组
extern char TitleAnimation[11][9][300];


//玩家记录
typedef struct {
    int highest_score;
    int max_combo;
    int highest_level;
} PlayerRecord;
extern PlayerRecord player_record;


//坐标位置相关旋转算法                         
extern int BLOCK_Sort[7][4][2];

//变量初始化
extern int BLOCK_Current[5][2];
extern int array[CMD_HEIGHT][CMD_LENGTH];
extern int x_new;
extern int y_new;
extern int score;
extern bool game_over;
extern bool pause;

//计时（下落）
extern clock_t last_drop_time;
extern int drop_interval_ms;

//等级
extern int level;
extern int level1;

// 连击数
extern int combo;
extern int max_combo;

extern int speed_setting;
extern int autosaving_setting;

#endif //tetris.h