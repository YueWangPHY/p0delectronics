#ifndef CENTRALBASE_H
#define CENTRALBASE_H

#include <mutex>
#include <thread>
#include <condition_variable>

std::condition_variable cond_CC;
std::mutex send_rec;
bool f_sent = false;
bool f_received =  false;
bool toleave = false;

bool toreset = false;

std::mutex m_alldone;
bool f_alldone = false;

std::mutex lockfile;

#endif
