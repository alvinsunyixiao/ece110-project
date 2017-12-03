#include <Arduino.h>
#include "sonar.hpp"

Sonar::Sonar(int trig, int echo,
             int alarm_dis, int stop_dis, int back_dis) {
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pin_trig = trig;
    pin_echo = echo;
    this->alarm_dis = alarm_dis;
    this->stop_dis = stop_dis;
    this->back_dis = back_dis;
}

unsigned long Sonar::getDuration() {
    digitalWrite(pin_trig, LOW);
    delayMicroseconds(2);
    digitalWrite(pin_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin_trig, LOW);
    return pulseIn(pin_echo, HIGH);
}

unsigned long Sonar::getCentimeter() {
    return getDuration() / 2 / 29.4;
}

int Sonar::getState(int *dis) {
    int ds = getCentimeter();
    if (dis)
        *dis = ds;
    if (ds > alarm_dis)
        return NORMAL;
    else if (ds > stop_dis)
        return ALARM;
    else if (ds > back_dis)
        return STOP;
    else
        return REVERSE;
}
