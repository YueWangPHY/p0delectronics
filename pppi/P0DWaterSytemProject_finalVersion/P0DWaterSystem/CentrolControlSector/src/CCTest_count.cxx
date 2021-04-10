#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <stdio.h>

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

#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME
#include "asio.hpp"
//#define ASIO_STANDALONE
//#define ASIO_HAS_BOOST_DATE_TIME

void print(const asio::error_code& error, std::shared_ptr<asio::steady_timer> t, int *count)//(const boost::system::error_code& error)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);

		t->expires_at(t->expires_at() + std::chrono::seconds(1));
		t->async_wait(bind(print,std::placeholders::_1, t, count));
	  }
}

int main()
{
	int count = 0;
	asio::io_service io;
	std::shared_ptr<asio::steady_timer> pt(new asio::steady_timer(io));//, std::chrono::seconds(3)));
//	asio::steady_timer t(io, std::chrono::steady_clock::now() + std::chrono::seconds(8));
//	asio::deadline_timer t(io_service, boost::posix_time::seconds(5));
//	asio::waitable_timer timer(io_service);
//	t.wait();//, std::placeholders::_1);
//	std::cout<<"hello world"<<std::endl;
//	t.expires_from_now(std::chrono::seconds(3));
//	t.async_wait(&print);//, std::placeholders::_1);
//	t.async_wait(bind(print, std::placeholders::_1, &count));//, std::placeholders::_1);
	pt->expires_from_now(std::chrono::seconds(3));
	pt->async_wait(bind(print, std::placeholders::_1, pt, &count));

	std::cout<<"to check the point"<<std::endl;
	io.run();

	std::cout<<"finish..."<<std::endl;
	return 0;

}
