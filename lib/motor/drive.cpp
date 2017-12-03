#include "Arduino.h"
#include "drive.hpp"
#include "config.h"

Motor::Motor(int c_l, int c_h) {
    ctrl_l = c_l;
    ctrl_h = c_h;
    pinMode(c_l, OUTPUT);
    pinMode(c_h, OUTPUT);
}

void Motor::move(int speed) {
    if (speed >= 0) {
        if (speed > 255)
            speed = 255;
        digitalWrite(ctrl_l, LOW);
        analogWrite(ctrl_h, speed);
    }
    else {
        if (speed < -255)
            speed = -255;
        speed = -speed;
        digitalWrite(ctrl_h, LOW);
        analogWrite(ctrl_l, speed);
    }
}

Car::Car(int l_low, int l_high, int r_low, int r_high) {
    left = new Motor(l_low, l_high);
    right = new Motor(r_low, r_high);
    l_speed = 0;
    r_speed = 0;
}

void Car::enableIR(int left, int middle, int right) {
    ir_l = left;
    ir_r = right;
    ir_m = middle;
}

void Car::speed_normalize() {
    if (l_speed > 255)
        l_speed = 255;
    if (r_speed > 255)
        r_speed = 255;
    if (l_speed < -255)
        l_speed = -255;
    if (r_speed < -255)
        r_speed = -255;
}

void Car::move(int speed) {
    l_speed = speed;
    r_speed = speed;
    //speed_normalize();
    left->move(l_speed);
    right->move(r_speed);
}

void Car::spin(int speed) {
    l_speed = speed;
    r_speed = -speed;
    //speed_normalize();
    left->move(l_speed);
    right->move(r_speed);
}

void Car::stop() {
    move(0);
}

void Car::turnLeft(int offset) {
    //l_speed -= offset;
    //r_speed += offset;
    //speed_normalize();
    left->move(l_speed - 30);
    right->move(r_speed + 30);
}

void Car::turnRight(int offset) {
    //l_speed += offset;
    //r_speed -= offset;
    //speed_normalize();
    left->move(l_speed - 30);
    right->move(r_speed + 30);
}

void Car::followLine(int speed) {
    int l = analogRead(ir_l);
    int r = analogRead(ir_r);
    int m = analogRead(ir_m);
    if (m <= LINE_THRESH && l <= LINE_THRESH && r <= LINE_THRESH) {
        move(90);
        return;
    }
    if (l <= LINE_THRESH && r <= LINE_THRESH) {
        move(speed);
    }
    else if (r <= LINE_THRESH) {
        turnLeft(30);
    }
    else if (l <= LINE_THRESH) {
        turnRight(30);
    }
    else {
        stop();
    }
}
