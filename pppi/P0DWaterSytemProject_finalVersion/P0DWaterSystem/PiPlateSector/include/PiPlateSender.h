#ifndef PIPLATESENDER_H
#define PIPLATESENDER_H

#define ASIO_STANDALONE

#include <asio.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


class PiPlateSender //boradcast sender
{
public:
  	PiPlateSender(asio::io_service& io_service, const short portNo, std::string msg): socket_(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), portNo))//,
	{
		sendStatus=false;
		asio::socket_base::broadcast option(true);
		socket_.set_option(option);

		message_ = msg;
        socket_.async_send_to(asio::buffer(message_), asio::ip::udp::endpoint(asio::ip::address_v4::broadcast(), portNo),
                                bind(&PiPlateSender::handle_send_to, this, message_,std::placeholders::_1, portNo));// asio::placeholders::error, asio::placeholders::bytes_tra
	}

	void handle_send_to(std::string message, const asio::error_code& error, const short portNo)//, std::size_t bytes_transferred)
	{

		if (!error)
		{
			sendStatus = true;
			std::cout << "handle_send:  \"" << error.message() <<
							 "\" message = \"" << message <<std::endl;
		}
		else
            socket_.async_send_to(asio::buffer(message), asio::ip::udp::endpoint(asio::ip::address_v4::broadcast(), portNo),
                                    bind(&PiPlateSender::handle_send_to, this, message,std::placeholders::_1, portNo));

	}
private :
	asio::ip::udp::socket socket_;
	std::string message_;
public:
	bool sendStatus; 
};


#endif

