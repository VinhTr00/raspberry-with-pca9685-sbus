/*----------------------------------- Include ----------------------------------------------*/
#include "speaker.h"
#include <stdio.h>

/*----------------------------------- Private Definitions ----------------------------------*/
#define GPIO_PIN_RESET  0
#define GPIO_PIN_SET    1

/*----------------------------------- Private Functions ------------------------------------*/
static void _speakerTask(void);
static void _speakerInitPin(void);

/*----------------------------------- Private Variables ------------------------------------*/
static TaskIDType speakerTaskID;
static StateSpeaker __speakerState;
/*----------------------------------- Public Variables -------------------------------------*/

/*********** Private Functions Declaration ****************/
static void _speakerInitPin(void){
    pinMode(TONE1_PIN, OUTPUT);
    pinMode(TONE2_PIN, OUTPUT);
    pinMode(MIC_PIN, OUTPUT);
    digitalWrite(TONE1_PIN, GPIO_PIN_RESET);
    digitalWrite(TONE2_PIN, GPIO_PIN_RESET);
    digitalWrite(MIC_PIN, GPIO_PIN_SET);
}

static void _speakerTask(void){
    switch (__speakerState)
    {
        case ERROR_STATE:
            digitalWrite(TONE1_PIN, GPIO_PIN_RESET);
            digitalWrite(TONE2_PIN, GPIO_PIN_RESET);
            digitalWrite(MIC_PIN, GPIO_PIN_SET);
            break;
        case TONE1:
            digitalWrite(MIC_PIN, GPIO_PIN_RESET);
            digitalWrite(TONE2_PIN, GPIO_PIN_RESET);
            digitalWrite(TONE1_PIN, GPIO_PIN_SET);
            break;
        case TONE2:
            digitalWrite(TONE1_PIN, GPIO_PIN_RESET);
            digitalWrite(MIC_PIN, GPIO_PIN_RESET);
            digitalWrite(TONE2_PIN, GPIO_PIN_SET);
            break;
        case MIC:
            digitalWrite(TONE1_PIN, GPIO_PIN_RESET);
            digitalWrite(TONE2_PIN, GPIO_PIN_RESET);
            digitalWrite(MIC_PIN, GPIO_PIN_SET);
            break;
        default:
            break;
    }
}

/************* Public Functions Declaration ******************/
void speakerChangeMode(StateSpeaker mode){
    __speakerState = mode;
}

void speakerSetup(void){
    _speakerInitPin();
    taskCreate(&speakerTaskID, TASK_MODE_REPEATED, _speakerTask);
    taskStart(speakerTaskID, SPEAKER_TASK_PERIOD);
}