#include "tetris.h"
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