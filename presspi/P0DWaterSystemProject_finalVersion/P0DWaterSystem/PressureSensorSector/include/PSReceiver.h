#ifndef PSRECEIVER_H
#define PSRECEIVER_H

//#define ASIO_HAS_BOOST_DATE_TIME
#define ASIO_STANDALONE

#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>

#include <asio.hpp>
//#include "GlobalBase.h"
#include "PSSectorBase.h"


class PSReceiver//: public ActionBase
{
public:
	PSReceiver(asio::io_service& io_service, const short portNoR): socket_(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(),portNoR))
    {
        asio::socket_base::broadcast option(true);
        socket_.set_option(option);

        socket_.async_receive_from(asio::buffer(data_,max_len), sender_endpoint_,
                                    bind(&PSReceiver::handle_receive_from, this, std::placeholders::_1, std::placeholders::_2));

    }
   
    void handle_receive_from(const asio::error_code& error,std::size_t bytes_recvd)
    {
        if (!error)
        {
		   std::cout<<"received=";
           std::cout.write(data_,bytes_recvd)<<std::endl;
			
			std::shared_ptr<std::string> p_str(new std::string(ConvertCharArrayToString(data_, bytes_recvd)));
			{
				std::unique_lock<std::mutex> lock(lock_PSReceivdMsgQ);
				ptr_PSReceivdMsgQ.push(p_str);
				cond_PS.notify_one();
				lock.unlock();
			}

			if(*p_str!="AllDone50")
          		socket_.async_receive_from(asio::buffer(data_,max_len), sender_endpoint_,
                                    bind(&PSReceiver::handle_receive_from, this, std::placeholders::_1, std::placeholders::_2));
        }

    }
    std::string ConvertCharArrayToString(char array[],std::size_t size,std::size_t startPosition=0)
    {
        std::string str;
        for(std::size_t i=0;i<size;i++)
            str+=array[i+startPosition];
        return str;
    }


private:
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint sender_endpoint_;
    enum {max_len=1024};
    char data_[max_len];
public:
    std::string tranferredMessage ;



};




#endif
