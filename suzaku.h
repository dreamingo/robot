#pragma once
#include <vector>
#include <string>
#include "servo.h"
#include "basic.h"
#include "mission.h"


//servos,I/Os class
class Wheels {
	private:
		int direct;//direct: 0->ahead,1->back,2->right,3->left
		int di_speed[4][2];
		int speed;
		Servo servo;
		int servo_num;
	public:
		Wheels();
		void stop();
		void setServoNum(int n);
		void setDirect(int dir);
		void setSpeed(int sp);
		void setMode(int mode);
		void action();
		void init();
};

class Eyes{
	private:
		//Obsticle detection
		bool IsObs;
		//edge detection
		bool IsEdge;
	public:
		void init()
		{
			IsEdge = false;
			IsObs = false;
		}
		//Obsticle detection
		bool Get_Obs_information(bool information[]);
		//edge detection
		bool Get_Edge_information(bool information[]);
};

class Suzaku: public Mission{
    private:
		Wheels wheels;
		Eyes my_eyes;
		bool obs_information[4];
		bool edge_information[8];
        bool normal;
 		double time;
		bool end;
    public:
        void init(){
			time = 0;
			wheels.setServoNum(2);
			wheels.init();
			end=false;
		}
		void turn(int speed,int dir){
			wheels.setSpeed(speed);
			wheels.setDirect(dir);
			wheels.action();
		}
        void step(double dt);
        void stop();
        bool isEnd(){
                return end;
		}
};
