#include "UI.h"


void UI_init(void){
    
}

void UI_periodic(void){
    static uint8_t rainbowHue = 0;
    rainbowHue += 2;
    
    HsvColor hsv;
    hsv.h = rainbowHue;
    hsv.s = 255;
    hsv.v = 255;
    
    RgbColor rgb = HsvToRgb(hsv);
    
    switch(UIState){
        case UI_STATE_NORMAL:
            //Set button LED colors
            //Cabin
            LEDBrightness[BUTTON0_RED] =    params[PARAM_CLR_BTN_WHITE_R];
            LEDBrightness[BUTTON0_GREEN] =  params[PARAM_CLR_BTN_WHITE_G];
            LEDBrightness[BUTTON0_BLUE] =   params[PARAM_CLR_BTN_WHITE_B];
            
            //Floods
            LEDBrightness[BUTTON1_RED] =    0;
            LEDBrightness[BUTTON1_GREEN] =  255;
            LEDBrightness[BUTTON1_BLUE] =   0;
            
            //Night
            LEDBrightness[BUTTON2_RED] =    255;
            LEDBrightness[BUTTON2_GREEN] =  0;
            LEDBrightness[BUTTON2_BLUE] =   0;
            
            //Maneuver
            LEDBrightness[BUTTON3_RED] =    params[PARAM_CLR_BTN_ORANGE_R];
            LEDBrightness[BUTTON3_GREEN] =  params[PARAM_CLR_BTN_ORANGE_G];
            LEDBrightness[BUTTON3_BLUE] =   params[PARAM_CLR_BTN_ORANGE_B];
            
            //HV
            LEDBrightness[BUTTON4_RED] = 0;
            LEDBrightness[BUTTON4_GREEN] = 0;
            LEDBrightness[BUTTON4_BLUE] = 255;
            
            if(buttonChangeState.button0){
                if(CabinState){
                    //Turn off cabin lights
                    printf("Turning off cabin lights.\n");
                    CabinState = FALSE;
                }
                else{
                    //Turn on cabin lights
                    printf("Turning on cabin lights.\n");
                    CabinState = TRUE;
                }
            }

            if(buttonChangeState.button1){
                if(FloodState == FLOOD_STATE_OFF){
                    //Turn on floods
                    UIState = UI_STATE_FLOOD;
                }
                else{
                    //Turn off floods
                    FloodState = FLOOD_STATE_OFF;
                    printf("Turning off floods.\n");
                }
            }

            if(buttonChangeState.button2){
                //Night mode
            }
            
            if(buttonChangeState.button3){
                //Maneuvering
                if(maneuver){
                    printf("Turning off maneuvering\n");
                    maneuver = FALSE;
                }
                else{
                    printf("Turning on maneuvering\n");
                    maneuver = TRUE;
                }
            }
            
            if(buttonChangeState.button4){
                if(buttonState.button4){
                    //Turn on HV
                    HV_requestOn();
                }
            }
        break;
        
        case UI_STATE_FLOOD:
        //Pick flood color
            //Set button LED colors
            LEDBrightness[BUTTON0_RED] =    255;
            LEDBrightness[BUTTON0_GREEN] =  0;
            LEDBrightness[BUTTON0_BLUE] =   0;
            
            LEDBrightness[BUTTON1_RED] =    0;
            LEDBrightness[BUTTON1_GREEN] =  255;
            LEDBrightness[BUTTON1_BLUE] =   0;
            
            LEDBrightness[BUTTON2_RED] =    0;
            LEDBrightness[BUTTON2_GREEN] =  0;
            LEDBrightness[BUTTON2_BLUE] =   255;
            
            LEDBrightness[BUTTON3_RED] =    params[PARAM_CLR_BTN_WHITE_R];
            LEDBrightness[BUTTON3_GREEN] =  params[PARAM_CLR_BTN_WHITE_G];
            LEDBrightness[BUTTON3_BLUE] =   params[PARAM_CLR_BTN_WHITE_B];
            
            LEDBrightness[BUTTON4_RED] = rgb.r;
            LEDBrightness[BUTTON4_GREEN] = rgb.g;
            LEDBrightness[BUTTON4_BLUE] = rgb.b;
            
            if(buttonChangeState.button0){
                //Set red
                FloodState = FLOOD_STATE_RED;
                UIState = UI_STATE_NORMAL;
                printf("Red floods\n");
                break;
            }
            
            if(buttonChangeState.button1){
                //Set green
                FloodState = FLOOD_STATE_GREEN;
                UIState = UI_STATE_NORMAL;
                break;
            }
            
            if(buttonChangeState.button2){
                //Set blue
                FloodState = FLOOD_STATE_BLUE;
                UIState = UI_STATE_NORMAL;
                break;
            }
            
            if(buttonChangeState.button3){
                //Set white
                FloodState = FLOOD_STATE_WHITE;
                UIState = UI_STATE_NORMAL;
                break;
            }
            
            if(buttonChangeState.button4){
                //Set rainbow
                FloodState = FLOOD_STATE_RAINBOW;
                UIState = UI_STATE_NORMAL;
                break;
            }
        
        break;
    }
    
    //Implement floods
    switch(FloodState){
        case FLOOD_STATE_OFF:
            NeoPixelData[0] = 0x00;
            NeoPixelData[1] = 0x00;
            NeoPixelData[2] = 0x00;
            NeoPixelData[3] = 0x00;
        break;
        case FLOOD_STATE_RED:
            NeoPixelData[0] = 0x00;
            NeoPixelData[1] = 0x00;
            NeoPixelData[2] = 0xff;
            NeoPixelData[3] = 0x00;
        break; 
        case FLOOD_STATE_GREEN:
            NeoPixelData[0] = 0x00;
            NeoPixelData[1] = 0x00;
            NeoPixelData[2] = 0x00;
            NeoPixelData[3] = 0xff;
        break;
        case FLOOD_STATE_BLUE:
            NeoPixelData[0] = 0x00;
            NeoPixelData[1] = 0xff;
            NeoPixelData[2] = 0x00;
            NeoPixelData[3] = 0x00;
        break;
        case FLOOD_STATE_WHITE:
            NeoPixelData[0] = 0xff;
            NeoPixelData[1] = 0x00;
            NeoPixelData[2] = 0x00;
            NeoPixelData[3] = 0x00;
        break;
        case FLOOD_STATE_RAINBOW:
            NeoPixelData[0] = 0x00;
            NeoPixelData[1] = rgb.b;
            NeoPixelData[2] = rgb.r;
            NeoPixelData[3] = rgb.g;
        break;
    }
}