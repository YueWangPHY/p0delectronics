#ifndef CENTRALSENDER_H
#define CENTRALSENDER_H

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


class CentralSender //boradcast sender
{
public:
  	CentralSender(asio::io_service& io_service, const short portNo, std::string msg): socket_(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), portNo))//,
//      timer_(io_service)
	{
		sendStatus=false;
		asio::socket_base::broadcast option(true);
		socket_.set_option(option);

		outAllSentMsg.open("StoreAllSentMsg.txt", std::ofstream::out|std::ofstream::app);
		message_ = msg;
		socket_.async_send_to(asio::buffer(message_), asio::ip::udp::endpoint(asio::ip::address_v4::broadcast(), portNo),
        						bind(&CentralSender::handle_send_to, this, message_,std::placeholders::_1, portNo));// asio::placeholders::error, asio::placeholders::bytes_transferred));//broadcasting meaasge	

	}

	void handle_send_to(std::string message, const asio::error_code& error, const int portNo)//, std::size_t bytes_transferred)
	{

		if (!error)
		{
			sendStatus = true;
			std::cout << "handle_send:  \"" << error.message() <<
							 "\" message = \"" << message <<std::endl;
			outAllSentMsg<<message <<std::endl;
		}
		else
			socket_.async_send_to(asio::buffer(message), asio::ip::udp::endpoint(asio::ip::address_v4::broadcast(), portNo),
									bind(&CentralSender::handle_send_to, this, message,std::placeholders::_1, portNo));
	}
private :
	asio::ip::udp::socket socket_;
//	asio::basic_deadline_timer timer_;
//	asio::deadline_timer time_;
	std::string message_;
	std::ofstream outAllSentMsg;
public:
	bool sendStatus; 
};


#endif

