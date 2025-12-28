#include "tetris.h"


//初始化
void Initialization(){
    for(int i=0;i<CMD_HEIGHT;i++) {
        for(int j=0;j<CMD_LENGTH;j++){
            array[i][j]=0;
        }
    }
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
    combo = lines_cleared;
    //如果最大连击数刷新则获取分数翻倍
    if(combo > max_combo){base_score=base_score*2;}
    max_combo = (combo > max_combo ? combo : max_combo);
    combo = 0;
    return base_score;
}