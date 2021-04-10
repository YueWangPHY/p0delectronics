#ifndef PIPLATESECTORBASE_H
#define PIPLATESECTORBASE_H

#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>


int InCondWaitCounter = 0;
std::mutex lock_InCondWaitCounter; 

std::condition_variable cond_PP;

std::mutex lock_PPReceivdMsgQ; // lock for push or pop the queue of received messages;
std::mutex lock_PPOperation;

std::queue<std::shared_ptr<std::string>> ptr_PPReceivdMsgQ; //queue of shared_ptr of received message

const int NMAXRELAYS = 56;//Max Relays can be connected on one set of PiPlates
//const int NMAXOPENRELAYS = 4;//MAX number of relays open at the the time

const int RELAYOPENTIMELENGTH = 40 ;//20;//in sec

#endif
