#ifndef INTERFACE_H
#define INTERFACE_H


#include <iostream>
#include <string> 

std::string Input()
{
	std::string input; 
	std::cout<<"Input address and relay in the form of AB where A is addr of piplate and B is the relay number"<<std::endl;
	std::cin>>input;
	return input;
}

void Output(int address, int relaynum)
{
	std::cout<<"Operating on relay: addr="<<address<<"  relay="<<relaynum<<std::endl;	
}


#endif
