#ifndef PSSECTORBASE_H
#define PSSECTORBASE_H

#include <iostream>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cond_PS;

std::mutex lock_PSReceivdMsgQ; // lock for push or pop the queue of received messages;
std::mutex lock_PSOperation;

std::queue<std::shared_ptr<std::string>> ptr_PSReceivdMsgQ; //queue of shared_ptr of received message

#endif
