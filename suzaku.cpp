#include "suzaku.h"
//turn: set speed and dir,
//dir  = 0, go ahead
//dir  = 1, go backward
//dir  = 2, turn right
//dir  = 3, turn left

Suzaku::Suzaku()
{
	count = 1;
	delay_speed = 1;
	for(int i = 0; i < 4; i++)
		obs_information[i] = false;
	for(int i = 0; i < 8; i++)
		edge_information[i] = false;

}
void Suzaku::turn(int speed,int dir)
{
	wheels.setSpeed(speed);
	wheels.setDirect(dir);
	wheels.action();
}

void Suzaku::stop()
{
	wheels.stop();
}

bool Suzaku::fragment_delay(int delay_time, int divise_num, int dir)
{
	int dt = 0;
	int divise_time = delay_time/divise_num;
	for(int i = 0; i < divise_num; i++)
	{
		DelayMS(divise_time);	
		my_eyes.Get_Edge_information(edge_information);
		if(edge_information[dir] == true)
			return true;
	}
	return false;
}

void Suzaku::delay_until(int time, int condition)
{
	while(1)
	{
		DelayMS(time);
		my_eyes.Get_Edge_information(edge_information);
		if(edge_information[condition] == false)
			break;
		time -=200;
		if(time <= 50)
			time = 50;
	}
	return;
}

void Suzaku::Edge_dection()
{	
	if(my_eyes.Get_Edge_information(edge_information) == true)
	{
		bool front_edge = edge_information[0];
		bool back_edge = edge_information[1];
		bool left_edge = edge_information[2];
		bool right_edge = edge_information[3];
		int move_backward = 1; // move back by default
		if(back_edge == true && front_edge == true)
		{
			if(left_edge == true)
				turn(400,2);
			else 
				turn(400,3);
			DelayMS(300);
		}
		else
		{
			if(back_edge == true)
			{
				move_backward = 0;
			}
			turn(800/delay_speed,move_backward);
			DelayMS(300/count);
			stop();
			DelayMS(1000);
			count ++;
			delay_speed++;
			// stop point for test
			//stop(); DelayMS(1200);
			//delay_until(400,1 - move_backward);
			/*(if(fragment_delay(100, 4, move_backward))
			  {
			  if(left_edge == true)
			  turn(400,2);
			  else 
			  turn(400,3);
			  DelayMS(300);
			  }*/
			turn_dir = 3;//turn left by default
			if(left_edge == true)
				turn_dir= 2;
		}
	}
	else
	{
		if(turn_dir != -1){
			turn(900,turn_dir);
			DelayMS(500);
			count = 1;
			turn_dir = -1;
			delay_speed = 1;
		}else{
			turn(350,0);
			DelayMS(10);
		}
	}
}

void Suzaku::brain()
{
	turn_dir = -1;
	while(1)
	{
		Edge_dection();
	}
}

