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
	int fd;
		struct flock flk;
std::cin>>operation;
	for(int crazy=0;crazy<30;crazy++)
	{
		int i=0;
//		while(true)
//		{
			srand((unsigned)time(0)); 
			int random_integer = rand(); 
			std::cout << random_integer << std::endl; 

			fd = open("/home/pi/P0DWaterSytemProject/P0DWaterSytem/CentrolControlSector/src/generatedDepth.txt", O_RDWR);
				
			if(fd==-1)
				std::cout<<"fd==-1"<<std::endl;

			flk.l_type = F_WRLCK; 
			fcntl(fd, F_SETLKW, &flk);
			std::cout<<"inlock"<<std::endl;
			std::string stringtime = GetCurrentTime();	
			write(fd, stringtime.c_str(), 10);
			write(fd, "\n", 1);
			if(operation==1)
			{
				for(int ibag=0;ibag<50;ibag++)
				{
					std::string stringbagid = std::to_string(ibag+1);
					int bagidlen = stringbagid.length();
					if(ibag == i)
					{
						write(fd, stringbagid.c_str(), bagidlen);
						write(fd, " ", 1);
						write(fd, "0", 1);
						write(fd, "\n", 1);
					}
		//				f1<<std::setw(2)<<ibag+1<<" "<<std::setw(2)<<0<<std::endl;
					else
					{
						write(fd, stringbagid.c_str(), bagidlen);
						write(fd, " ", 1);
						int num = (int)rand()/10000;
						std::string stringnum = std::to_string(num);
						int numlen = stringnum.length();
						write(fd, stringnum.c_str(), numlen);
						write(fd, "\n", 1);
					}
//						f1<<std::setw(2)<<ibag+1<<" "<<std::setw(2)<<(int)rand()/10000<<std::endl;
					for(int iii=0; iii<5000000; iii++)
						int fun=iii;
				}
			}
	/*
				if(operation==3)
				{
					for(int ibag=0;ibag<50;ibag++)
					{
						if(ibag == i)
							f1<<std::setw(2)<<ibag+1<<" "<<std::setw(2)<<200<<std::endl;
						else
							f1<<std::setw(2)<<ibag+1<<" "<<std::setw(2)<<(int)rand()%100<<std::endl;
					}
				}
	*/
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

