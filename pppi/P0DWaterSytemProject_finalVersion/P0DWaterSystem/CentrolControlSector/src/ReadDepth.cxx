#include <iostream>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <thread>
#include <cstdlib> 
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include "CentralBase.h"
#include "GlobalBase.h"

int main()
{
	std::cout<<"which operation want to do? 1 is fill and 3 is drain"<<std::endl;
	int operation = -1;
	std::cin>>operation;
	for(int crazy=0;crazy<30;crazy++)
	{
		int i=0;
//		while(true)
//		{
			srand((unsigned)time(0)); 
			int random_integer = rand(); 
			std::cout << random_integer << std::endl; 

			int fd;
			struct flock flk;
			fd = open("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt", O_RDWR);
				
			if(fd==-1)
				std::cout<<"fd==-1"<<std::endl;

			flk.l_type = F_WRLCK; 
			std::cout<<fcntl(fd, F_SETLKW, &flk)<<std::endl;
			std::cout<<"inlock"<<std::endl;
			std::string stringtime = GetCurrentTime();	
//			int len = stringtime.length();
//			char towrite[10];  
			char* readline = (char*) calloc(20, sizeof(char));
			read(fd, readline, 11);
			std::cout<<readline[0]<<" "<<readline[1]<<" "<<readline[2]<<" "<<readline[4]<<std::endl;
			flk.l_type = F_UNLCK;
			fcntl(fd, F_SETLKW, &flk);
			close(fd);
			std::cout<<"Out of lock"<<std::endl;	
			sleep(2);
			i++;
			if(i>16)
				break;
//		}
	}

}

