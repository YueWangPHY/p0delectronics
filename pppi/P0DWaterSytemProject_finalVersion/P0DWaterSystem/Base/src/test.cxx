#include "GlobalBase.h"
#include "InterpretCMD.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	std::cout<<"hello"<<std::endl;
//	InterpretCMD("1111011030FillBag01");
	
//	std::cout<<gr.GetMaxBags()<<std::endl;

	std::cout<<GetCurrentTime()<<std::endl;
	std::string str1= GetCurrentTime();
	std::cout<<str1<<std::endl;

	std::this_thread::sleep_for(std::chrono::duration<int>(2));
	std::string str2 = GetCurrentTime();
	std::cout<<str2<<std::endl;
	std::cout<<GetTimeDifference(str1, str2)<<std::endl;

	std::string str = str1 + "DraiBag20";
	std::pair<int, int> result = InterpretCMD(str);
	std::cout<<result.first<<" "<<result.second<<std::endl;
	std::cout<<"finish..."<<std::endl;
	return 0;
}
