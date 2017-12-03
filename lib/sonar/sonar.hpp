#ifndef __SONAR_HPP_
#define __SONAR_HPP__

#define NORMAL  0
#define ALARM   1
#define STOP    2
#define REVERSE 3

class Sonar {
private:
    int pin_trig;
    int pin_echo;
    int alarm_dis;
    int stop_dis;
    int back_dis;
public:
    Sonar(int trig, int echo,
          int alarm_dis, int stop_dis, int back_dis);
    unsigned long getDuration();
    unsigned long getCentimeter();
    int getState(int *dis = 0);
};

#endif
