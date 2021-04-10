#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>
#include <mutex>
#include <thread>
/*
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"
#include "GlobalBase.h"
#include "InterpretBag_PS.h"
#include "ReadPressureSensors.h"

#ifndef I2C_DEVICE
#define I2C_DEVICE "/dev/i2c-1"
#endif
*/
#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"
//#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME

void print(const asio::error_code& error)//(const boost::system::error_code& error)
{
	std::cout<<"handler is called"<<std::endl;
  if (!error)
	std::cout<<"hello world"<<std::endl;
}

void TimerThread(std::shared_ptr<asio::io_service> ptr_io)
{
//	std::cout<<"test"<<std::endl;
	asio::steady_timer t1(*ptr_io, std::chrono::steady_clock::now() + std::chrono::seconds(5));
//  	t1.expires_from_now(std::chrono::seconds(2));
	t1.async_wait(&print);
	ptr_io->run();

}


void NewTimerThread()//(std::shared_ptr<asio::io_service> ptr_io)
{
	asio::io_service io;
	asio::steady_timer t1(io, std::chrono::steady_clock::now() + std::chrono::seconds(5));
//  	t1.expires_from_now(std::chrono::seconds(2));
	t1.async_wait(&print);
//	ptr_io->run();
	io.run();

}

void ThirdTimerThread(std::shared_ptr<asio::steady_timer> ptr_timer)
{
	ptr_timer->expires_from_now(std::chrono::seconds(5));

	ptr_timer->async_wait(&print);	
}



void Repeat(std::shared_ptr<asio::io_service> ptr_io)//, std::shared_ptr<asio::io_service> ptr_io_1)
{
	std::cout<<"repeat"<<std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(1));
//	std::thread thread1(TimerThread, ptr_io);
//	std::thread thread1(NewTimerThread);

	asio::io_service io;
	std::shared_ptr<asio::steady_timer> ptr_timer(new asio::steady_timer(io));
	std::thread thread1(ThirdTimerThread, ptr_timer);

	thread1.join();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	std::cout<<"good"<<std::endl;
	io.run();
	ptr_io->post(std::bind(Repeat, ptr_io));
}

void RepeatThread(std::shared_ptr<asio::io_service> ptr_io)//, std::shared_ptr<asio::io_service> ptr_io_1)
{
//	std::shared_ptr<asio::io_service> ptr_io_1(new asio::io_service);	
	Repeat(ptr_io);
	ptr_io->run();
}

void f1(int n)
{
        std::cout << "Thread 1 executing\n";
}
 

int main()
{
//	std::mutex mu;
//	asio::io_service io;
	std::shared_ptr<asio::io_service> ptr_io(new asio::io_service);
	std::shared_ptr<asio::io_service> ptr_io_1(new asio::io_service);
//	{
//	std::unique_lock<std::mutex> lock(mu);
//	asio::steady_timer t(io);//, std::chrono::steady_clock::now() + std::chrono::seconds(8));
//	asio::deadline_timer t(io_service, boost::posix_time::seconds(5));
//	asio::waitable_timer timer(io_service);
//	t.wait();//, std::placeholders::_1);
//	std::cout<<"hello world"<<std::endl;
//	t.expires_from_now(std::chrono::seconds(15));
//	t.async_wait(&print);//, std::placeholders::_1);
//	std::thread thread1(TimerThread, ptr_io);
//	if(thread1.joinable())
//		thread1.join();
//	std::cout<<"test before run"<<std::endl;
//	std::this_thread::sleep_for(std::chrono::seconds(10));
//	t.cancel();
//	lock.unlock();	
//	}
//	io.run();

	std::vector<std::thread> Threads;
//	Threads.emplace_back(std::thread(TimerThread, ptr_io));
	Threads.emplace_back(std::thread(f1,1));
	Threads.emplace_back(std::thread(RepeatThread, ptr_io));//, ptr_io_1));

  std::cout<<"test before join"<<std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(10));
    for(std::thread& tm : Threads){
        if(tm.joinable())
            tm.join();
    }

//	ptr_io->run();
  std::cout<<"test before run"<<std::endl;
//  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout<<"test after sleep"<<std::endl;

//	std::thread thread1(TimerThread, ptr_io);
//	std::thread thread2(f1, 1);
//	thread1.join();
//	thread2.join();
//	ptr_io->run();
//	t.cancel();

	std::cout<<"finish..."<<std::endl;
	return 0;

}
