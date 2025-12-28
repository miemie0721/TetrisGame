#include "tetris.h"


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