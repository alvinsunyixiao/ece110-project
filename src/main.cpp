#include <Arduino.h>
#include <drive.hpp>
#include <sonar.hpp>
#include <config.h>

Car *car;
Sonar *sonar;
volatile unsigned char value = 0;
volatile unsigned char toggle = 0;

void setup() {
    // put your setup code here, to run once:
    car = new Car(LEFT_LOW,
                  LEFT_HIGH,
                  RIGHT_LOW,
                  RIGHT_HIGH);
    car->enableIR(A1, A2, A0);
    sonar = new Sonar(S_TRIG, S_ECHO,
                      ALARM_DIST, STOP_DIST, BACK_DIST);
    //pinMode(6, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    int dis;
    unsigned long st = millis();
    do {
        int state = sonar->getState(&dis);
        switch (state) {
        case NORMAL:
            car->followLine(150);
            //analogWrite(3, 0);
            value = 0;
            Serial.println("NORMAL!!!");
            break;
        case ALARM:
            //analogWrite(3, (18-(dis-7))*255/18);
            //analogWrite(3, 0);
            value = (18-(dis-7))*255/18;
            car->followLine(80);
            Serial.println("ALRAM!!!");
            break;
        case STOP:
            //analogWrite(3, 255);
            //analogWrite(3, 0);
            value = 255;
            car->stop();
            Serial.println("STOP!!!");
            break;
        case REVERSE:
            //analogWrite(3, 255);
            //analogWrite(3, 0);
            value = 255;
            car->left->move(-130);
            car->right->move(-150);
            Serial.println("REVERSE!!!");
            break;
        default:
            //analogWrite(3, 0);
            value = 0;
            Serial.println("DEFAULT!!!");
            break;
        }
        if (4 * value <= 70) {
            analogWrite(3, 0);
            toggle = 0;
            return;
        }
        else if (4 * value >= 950) {
            analogWrite(3, 128);
            toggle = 1;
            return;
        }
    } while (millis() - st <= 80000 / (4*value) * 3 / 7);
    toggle = 1 - toggle;
    analogWrite(3, toggle * 128);
    //delay(100);
    //car->followLine(200);
}
