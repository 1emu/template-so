/*
 * Hydrogen.cpp
 *
 * Created on: May 10, 2014
 * Author: jp
 */

#include "utils/Includes.h"

using namespace std;

int main(int argc, char** argv) {

	char* processName = argv[0];
	string id_str;

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 1) {
		string msg = "Usage ";
		msg = msg + processName + " <-id> \n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	id_str = string(argv[1]);
	int id = atoi(id_str.c_str());

	Coin* coin = (Coin*) SharedMemory::get(SHARED_MEMORY_ID, sizeof(Coin));
	SemaphoreArray* readersMutex = SemaphoreArray::get(READERS_MUTEX_ID);
	SemaphoreArray* writersMutex = SemaphoreArray::get(WRITERS_MUTEX_ID);

	Process::announce(processName, id, BLUE, "funcionando.");
	int readCount = 0;

	/********************************************************************/
	for (int i = 0; i < AMOUNT_OF_ITERATIONS; ++i) {
		readersMutex->wait();
		readCount++;
		if (readCount == 1)
			writersMutex->wait();
		readersMutex->post();

		int coinValue = coin->coinValue;
		std::string coinValueMessage = "precio de la moneda: $" + Utils::intToString(coinValue);
		sleep(Process::randomBetween(1,3));
		Process::announce(processName, id, DARKGRAY, coinValueMessage.c_str());

		readersMutex->wait();
		readCount--;
		if (readCount == 0)
			writersMutex->post();
		readersMutex->post();
	}

	/********************************************************************/
	Process::announce(processName, id, LIGHTBLUE, "proceso terminado.");
	return 0;
}

