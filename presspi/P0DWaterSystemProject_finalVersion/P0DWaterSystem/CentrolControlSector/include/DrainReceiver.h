#ifndef DRAINRECEIVER_H
#define DRAINRECEIVER_H

//#define ASIO_HAS_BOOST_DATE_TIME
//#define ASIO_HAS_BOOST_DATE_TIME

#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <sstream>

#define ASIO_STANDALONE
#include <asio.hpp>
#include "GlobalBase.h"
//#include "PSSectorBase.h"


class DrainReceiver
{
public:
	DrainReceiver(asio::io_service& io_service, const short portNoR): socket_(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(),portNoR))
    {
        asio::socket_base::broadcast option(true);
        socket_.set_option(option);
		ptr_DCCReceivdMsgQ.clear();
//		{
			std::unique_lock<std::mutex> ulock(send_rec);
			cond_CC.wait(ulock, []{return f_sent;});
			std::cout<<"Be notified by Main"<<std::endl;
			if(toleave)
                        return;
			ulock.unlock();
//		}
        socket_.async_receive_from(asio::buffer(data_,max_len), sender_endpoint_,
                                    bind(&DrainReceiver::handle_receive_from, this, std::placeholders::_1, std::placeholders::_2));

    }
   
    void handle_receive_from(const asio::error_code& error,std::size_t bytes_recvd)
    {
		std::cout<<"come back in handle_receive_from again"<<std::endl;
        if (!error)
        {
		   std::cout<<"received=";
           std::cout.write(data_,bytes_recvd)<<std::endl;
			
			std::shared_ptr<std::string> p_str(new std::string(ConvertCharArrayToString(data_, bytes_recvd)));
			ptr_DCCReceivdMsgQ.push_back(p_str);
				
			if(*p_str=="AllDone50")
			{
				std::lock_guard<std::mutex> lock(send_rec);
				f_sent = false;
                f_received = true;
				cond_CC.notify_all();
				std::cout<<"leave receiver"<<std::endl;
				return;
			}
			if(ptr_DCCReceivdMsgQ.size()==NMAXBAGSDRAINSIM)
            {
                std::lock_guard<std::mutex> lock(send_rec);
                f_sent = false;
                f_received = true;
				ptr_DCCReceivdMsgQ.clear();
				cond_CC.notify_all();
            }
//			else
//			{
//
//				std::cout<<"not MAXSIM"<<std::endl;
//				std::cout<<"f_sent = "<<f_sent<<std::endl;			
//            cond_CC.notify_one();
//            cond_CC.notify_all();
//			std::cout<<"Notify Main code"<<std::endl;

//			if(*p_str!="AllDone50")
//			{
//				{
					std::unique_lock<std::mutex> ulock1(send_rec);
					cond_CC.wait(ulock1, []{return f_sent;});
					std::cout<<"Be notified by Main"<<std::endl;
					if(toleave)
						return;
					ulock1.unlock();
//				}
					
          		socket_.async_receive_from(asio::buffer(data_,max_len), sender_endpoint_,
                                    bind(&DrainReceiver::handle_receive_from, this, std::placeholders::_1, std::placeholders::_2));
//			}
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
//    std::mutex PSlock_ReceivedMsgQ;

//	std::vector<std::shared_ptr<std::string>> ptr_DCCReceivdMsgQ;//drain central control


};




#endif
