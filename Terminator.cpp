/*
 * Terminator.cpp
 *
 *  Created on: May 4, 2014
 *      Author: jp
 */

#include "Includes.h"
#include "Queue.h"

int main(){
    Queue::destroy(RECEIVER_QUEUE_ID);
    Queue::destroy(SENDER_QUEUE_ID);
//  SemaphoreArray::destroy(WRITERS_MUTEX_ID);
//	SharedMemory::destroy(SHARED_MEMORY_ID, sizeof(Coin));
    std::string msg = "Termination complete.";
    Colors::writeout(msg, UNDERLINEDGREEN);
    return 0;
}



