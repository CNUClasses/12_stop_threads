//============================================================================
// Name        : 12_stop_threads.cpp
// Author      : 
// Version     :
// Copyright   : Steal this code!
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <time.h>
#include <mutex>
#include <chrono>

using namespace std;

const int TOTAL_THREADS		=20;
volatile bool bDoWork 		= true;

void thrdfunc(int iThread){
	
	//does the following need protection?
	//if you dont care about a few extra cycles 
	//(as is the case for UI loops) then no
	while(bDoWork){
		cout<<"Thread:"<<iThread<<" working..."<<endl;

		//snooze for a bit to simulate work
		std::this_thread::sleep_for(std::chrono::milliseconds(1));	
	}
	cout<<"Thread:"<<iThread<<" exiting"<<endl;
}

int main(){
	
	//create a bunch of threads
	std::vector<std::thread> threads;
	for(int i = 0; i < 20; ++i){
		threads.push_back(std::thread(thrdfunc,i));
	}

	//let em run a bit
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	//ask them all to stop
	bDoWork = false;
	
	//wait for em to finish
	for(auto& thread : threads){
		thread.join();
	}

	cout<<"All threads done!"<<endl;

	return 0;
}
