#ifndef __DRIVE_HPP_
#define __DRIVE_HPP_

class Motor {
private:
    int ctrl_l;
    int ctrl_h;
public:
    Motor(int c_l, int c_h);
    void move(int speed);
};

class Car {
private:
    int l_speed;
    int r_speed;
    int ir_l;
    int ir_m;
    int ir_r;

    void speed_normalize();
public:
    Motor *left;
    Motor *right;

    Car(int l_low, int l_high, int r_low, int r_high);
    void enableIR(int left, int middle, int right);
    void move(int speed);
    void spin(int speed);
    void turnLeft(int offset);
    void turnRight(int offset);
    void followLine(int speed);
    void stop();
};

#endif
