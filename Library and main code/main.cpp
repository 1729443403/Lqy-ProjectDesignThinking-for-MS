#include "mbed.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

PwmOut servo(D10);
DigitalIn d12_input(D12);
DigitalIn a0_input(A0);
DigitalIn a1_input(A1);
Serial pc(USBTX, USBRX, 115200);
Serial bt(D1, D0, 9600); 
I2C i2c_lcd(D4, D5);

Adafruit_SH1106 display;

enum SystemState {
    NORMAL,
    NOT_NORMAL,
    WELCOME_BACK,
    GOOD_DREAM
};

char bt_buffer[32] = {0};
int bt_index = 0;

void update_display(SystemState state, const char* message) {
    display.clearDisplay();
    display.setTextSize(1);
    
    display.setCursor(0, 0);
    switch(state) {
        case NORMAL:
            display.print("Status:Normal ");
            break;
        case NOT_NORMAL:
            display.print("Status:NotNormal ");
            break;
        case WELCOME_BACK:
            display.setTextSize(2);
            display.setCursor(0, 18);
            display.print("Welcome Back");
            display.setTextSize(1); 
            break;
        case GOOD_DREAM:
            display.setTextSize(2);
            display.setCursor(0, 18);
            display.print("Good Dream");
            display.setTextSize(1); 
            break;
    }
//my debug script
    if(state == NORMAL || state == NOT_NORMAL) {
        display.setCursor(0, 16);  
        display.print("BT:");
        display.print(message);
    }
    
    display.display();
}

int main() {
    servo.period_ms(20);
    a0_input.mode(PullDown);
    a1_input.mode(PullDown);
    d12_input.mode(PullDown);
    
    display.begin(SH1106_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);

    while(true) {
        SystemState current_state = NORMAL;
        
        // 接收蓝牙数据
        if(bt.readable()) {
            memset(bt_buffer, 0, sizeof(bt_buffer));
            bt_index = 0;
            char c = bt.getc();
            bt_buffer[0] = c;  
            bt_buffer[1] = '\0';
            

            if(c == 'o') {
                servo.pulsewidth_us(2040);
                memset(bt_buffer, 0, sizeof(bt_buffer));
                bt_index = 0;
                current_state = WELCOME_BACK;
                update_display(current_state, bt_buffer);
                ThisThread::sleep_for(6000);
                continue;  
            }
            if(c == 's') {
                servo.pulsewidth_us(900);
                memset(bt_buffer, 0, sizeof(bt_buffer));
                bt_index = 0;
                current_state = GOOD_DREAM;
                update_display(current_state, bt_buffer);
                ThisThread::sleep_for(6000);
                continue;  
            }
        }

   
        if(a0_input) {
            servo.pulsewidth_us(2040);
            current_state = WELCOME_BACK;
        } else if(a1_input) {
            servo.pulsewidth_us(900);
            current_state = GOOD_DREAM;
        } else if(d12_input) {
            servo.pulsewidth_us(1500);
            current_state = NORMAL;
        } else {
            current_state = NOT_NORMAL;
        }

        
        update_display(current_state, bt_buffer);
        
        ThisThread::sleep_for(100);
    }
}