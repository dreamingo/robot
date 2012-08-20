#include <cassert>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "servo.h"
#include "config.h"
#include "basic.h"
// #include "test.h"
#include "mission.h"
#include "suzaku.h"

//static Config & C = Config::getInstance();
//const int IO_PATTERN = 0xf00;

int main(){
	init();
	//MFSetPortDirect(IO_PATTERN);
	DelayMS(100);
	MissionManager msm("main_manager");
	msm.init();
	Suzaku suzaku;
	// put missions into missionMagnager
	msm.add(&suzaku);
	// start mainloop
	while(not msm.isEnd()){
		// step all missions
		msm.step(0.1);
		DelayMS(50);
	}

	print("quit\n");
	quit();
	DelayMS(3000);
	return 0;
}
