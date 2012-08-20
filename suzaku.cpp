#include "suzaku.h"

const int di[4][2]={1,1,-1,-1,-1,1,1,-1};

Wheels::Wheels()
{
	direct=0;
	speed=400;
	servo_num=1;
	for(int i=0;i<4;i++)
		for(int j=0;j<2;j++)
			di_speed[i][j]=di[i][j];
}
void Wheels::stop()
{
	for(int i=1;i<=servo_num;i++)
		servo.setRotaSpeed(i,0);
	servo.action();
}
void Wheels::setServoNum(int n){
	servo_num=n;
}
void Wheels::setDirect(int dir){
	for(int i=1;i<=servo_num;i++)
		servo.setRotaSpeed(i,di_speed[dir][i-1]*speed);
}
void Wheels::setSpeed(int sp){
	speed=sp;
}
void Wheels::setMode(int mode){
	for(int i=1;i<=servo_num;i++)
		servo.setMode(i,mode);
}
void Wheels::action(){
	servo.action();
}	
void Wheels::init(){
	setMode(1);
	setDirect(direct);
}


//This function return a binary number, eg: 000 means there is nothing;
//111means there is Obstacle in the front,left,right side; so as it
bool Eyes::Get_Obs_information(bool information[]){
	information=0;
	bool frontObs = (MFGetDigiInput(2) ==0);
	bool leftObs = (MFGetDigiInput(4) ==0);
	bool rightObs = (MFGetDigiInput(3) ==0);
	//information = (rightObs<<2)+(leftObs<<1) + frontObs;
	if(information != 0)
	{
		IsObs = true;
	}
	printf("Information:%d ", information);
	return IsObs;
}
bool Eyes::Get_Edge_information(bool information[])
{
	for(int i = 0; i < 4; i++)
		information[i] = false;
	//information[0] == true It need to go backward
	//information[1] == true It need to go forward
	//information[2] == true It need to turn rigth 
	//information[3] == true It need to turn left
	if(MFGetDigiInput(6) == 1 || MFGetDigiInput(7) == 1)
		information[0] = true;
	
	if(MFGetDigiInput(8) == 1 || MFGetDigiInput(9) == 1)
		information[1] = true;
	
	if(MFGetDigiInput(7) == 1 || MFGetDigiInput(9) == 1)
		information[3] = true;

	if(MFGetDigiInput(6) == 1 || MFGetDigiInput(8) == 1)
		information[2] = true;
	for(int i = 0; i < 4; i++)
	{
		if(information[i] == true)
		{
			IsObs = true;
			break;
		}
	}
	return IsObs;
}

void Suzaku::stop()
{
	wheels.stop();
}

void Suzaku::step(double dt)
{
	if (!isEnd())
	{
		if (MFGetDigiInput(11) == 0)
		{
			end = true;
			stop();
		}
		if(my_eyes.Get_Edge_information(edge_information)== true)
		{
			bool front_edge = edge_information[0];
			bool back_edge = edge_information[1];
			bool left_edge = edge_information[2];
			bool right_edge = edge_information[3];
			int move_backward = 1; //move_backward = true by default
			if (back_edge == true)
				move_backward = 0;
			turn(512,move_backward);
			DelayMS(500);
			int turn_dir = 3;//move left by default		
			if(left_edge == true)
				turn_dir= 2;
			turn(512,turn_dir);
			DelayMS(300);
		}
	}
	time +=dt;
}
/*
void Suzaku::step(double dt)
{
	if(!isEnd()){
		if(MFGetDigiInput(5) == 0){
			end=true;
			stop();
		}
		if(my_eyes.Get_Edge_information(edge_information) == true)
		{
			wheels.setSpeed(512);
			turn(1);//Hold back
			DelayMS(250);
			if(edge_information==2)//the edge is on the left side of the car
				turn(2);//turn right	
			else//the edge is on the right side of the car or in front of the card
				turn(3);//turn left
			DelayMS(200);

		}
		if(my_eyes.Get_Obs_information(obs_information) == true)
		{
			if(obs_information ==4 )
			{
				turn(2);//Turn right
				DelayMS(250);
			}
			else if(obs_information ==2)
			{
				turn(3);//Turn left;
				DelayMS(250);
			}
			else if(obs_information==1)
			{
				//Clash
				wheels.setSpeed(800);
				turn(0);
				DelayMS(100);
			}
		}
		else
		{
			//goforward;
			wheels.setSpeed(512);
			wheels.setDirect(0);
			wheels.action();
			DelayMS(200);
		}
	}
	time+=dt;
}
*/
