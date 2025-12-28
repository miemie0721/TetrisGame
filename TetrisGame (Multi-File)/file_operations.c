#include "tetris.h"

// 保存玩家记录
void SavePlayerRecord() {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (file == NULL) {
        return;
    }
    
    fwrite(&player_record, sizeof(PlayerRecord), 1, file);
    fclose(file);
}

// 加载玩家记录
void LoadPlayerRecord() {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        player_record.highest_score = 0;
        player_record.max_combo = 0;
        player_record.highest_level = 1;
        return;
    }
    
    fread(&player_record, sizeof(PlayerRecord), 1, file);
    fclose(file);
}

// 更新最高记录
void UpdatePlayerRecord() {
    int updated = 0;
    
    if (score > player_record.highest_score) {
        player_record.highest_score = score;
        updated = 1;
    }
    
    if (max_combo > player_record.max_combo) {
        player_record.max_combo = max_combo;
        updated = 1;
    }
    
    if (level > player_record.highest_level) {
        player_record.highest_level = level;
        updated = 1;
    }
    
    if (updated) {
        SavePlayerRecord();
    }
}