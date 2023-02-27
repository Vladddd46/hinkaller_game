#ifndef CONFIG_HPP
#define CONFIG_HPP
#define GAME_NAME "HINKELLER"
#define BACK_GROUND_PATH "./textures/backgrounds/background.png"
#define SCORE_FONT_PATH "./fonts/arial.ttf"
#define BACKGROUND_MUSIC "./audio/main.ogg"
#define CAUGHT_FRIENDLY_OBJECT_SOUND "./audio/caught.ogg"
#define GAME_OVER_SOUND "./audio/gameOver.ogg"

#define MAX_FALLING_OBJECTS_IN_ARRAY 100
#define MAX_NUMBER_OF_FALLING_OBJECTS_CAN_SPAWN_AT_ONCE 10

// this values will be autoincremented after some time
#define MIN_FALLING_SPEED 1 // will be incremented till  MIN_FALLING_SPEED + 4
#define MAX_FALLING_SPEED 4 // will be incremented till  MAX_FALLING_SPEED + 3

/* 
 * 10 = 1 unfriend to 10 friend objects.
 * decrements each 10 seconds by 1.
 */ 
#define PERCENT_OF_UNFRIENDLY_OBJECTS 10

// PERIODS
// increment min. number of objects can spawn in each num. of sec.
#define PREDIOD_INCREMENT_NUM_OF_MIN_OBJECTS_CAN_SPAWN_SEC 25
// increment probability of spawning unfriendly objects in sec.
#define PERIOD_DECREMENT_PROBABILITY_OF_SPAWN_UNFRIEND_OBJECTS 10
// decrement max num of seconds between spawning
#define PERIOD_DECREMENT_MAX_SEC_BETWEEN_SPAWNING_OBJECTS 10
// each num of seconds when increments min falling speed 
#define PERIOD_INCREMENT_MIN_FALLING_SPEED 20
// each num of seconds when increments max num of falling objects.
#define PERIOD_INCREMENT_MAX_NUM_OF_FALLING_OBJECTS 20


// porbability of spawning chacha falling object. In percentage. 
// 50-50% of sawning friendly objects will be chacha
#define PROBABILITY_OF_CHACHA_SPAWN_IN_PERCENT 15
#endif//CONFIG_HPP
