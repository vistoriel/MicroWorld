#pragma once

#define GENOME_SIZE			64

#define MIN_GEN				10
#define MAX_GEN				40

#define SCREEN_WIDTH		1280
#define SCREEN_HEIGHT		720
#define SIZE				2

#define LIGHT_ENERGY		500
#define ORGANIC_ENERGY		1000

#define STEPS				10
#define DIVISION_ENERGY		9999
#define RELATIVES_GENES		1

typedef char ret_offset;
#define EMPTY_OFFSET		2
#define WALL_OFFSET			3
#define DEAD_OFFSET			4
#define FRIEND_OFFSET		5
#define ENEMY_OFFSET		6