#pragma once
#include <vector>
#include <string>
#include "servo.h"
#include "basic.h"
#include "wheels.h"
#include "mission.h"
#include "eyes.h"

class Suzaku {
    private:
		Wheels wheels;
		Eyes my_eyes;
		int count;
		int delay_speed;
		bool obs_information[4];
		bool edge_information[8];
        int turn_dir;
    public:
		Suzaku();
        void brain();
        void stop();
		void delay_until(int time, int condition);
		//turn: set speed and dir,
		//dir  = 0, go ahead
		//dir  = 1, go backward
		//dir  = 2, turn right
		//dir  = 3, turn left
		void turn(int speed, int dir);

		bool fragment_delay(int delay_time, int divise_num, int dir);
		void Edge_dection();
};
