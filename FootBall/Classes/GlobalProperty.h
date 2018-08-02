#pragma once
#include "cocos2d.h"
#define football_field_width 2100
#define football_field_height 1360
#define football_field_offset_bottom 90
#define football_field_offset_top 160
#define football_offset_x 60
#define football_offset_y 20
#define ANIMATION_SCALE_RATE 0.15

#define FOOTBALL_MAN_ZORDER 5000
//简单AI的逻辑,进入距离500内开始靠近对方,距离小于100发动铲球，最多只有2名球员去防守
#define DEFEND_RADIUS  200 //球员的防守半径
#define TACKLE_DISTANCE 40//发动铲球的距离
#define SUPPORT_DISTANCE 600//友方支援队员的距离

#define DEFEND_BACK_OFFSET 80

#define FOOT_BALL_START_SPEED 10

#define MAX_LEVEL_NUM 6//最大关卡的编号

#define PLAYER_TEAM_ID 1//玩家球队的编号D

#define DREAM_SPECIAL_TIME 25

#define PROP_DREAM_NUM 500 //道具价格

#define GAME_TIME 120

#define CAN_CHANGE_FOOTMAN_TIME 1.5

#define foot_ball_in_goal "foot_ball_in_goal"//进球
#define foot_ball_game_start "foot_ball_game_start"//游戏开始
#define foot_man_trackle_success "foot_man_trackle_success"//铲球成功
#define defend_man_run_to_target "defend_man_run_to_target"//防守队员跑向带球队员
