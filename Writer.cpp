/*
 * Oxygen.cpp
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
	srand(time(NULL)+id*300);

	Coin* coin = (Coin*) SharedMemory::get(SHARED_MEMORY_ID, sizeof(Coin));
	SemaphoreArray* readersSemaphore = SemaphoreArray::get(READERS_MUTEX_ID);
	SemaphoreArray* writersSemaphore = SemaphoreArray::get(WRITERS_MUTEX_ID);


	Process::announce(processName, id, BLUE, "funcionando.");
	/********************************************************************/
	for (int i = 0; i < AMOUNT_OF_ITERATIONS; ++i) {

		writersSemaphore->wait();
		readersSemaphore->wait();

		int newCoinValue = Process::randomBetween(MIN_COIN_VALUE,	MAX_COIN_VALUE);
		coin->coinValue = newCoinValue;
		std::string coinValueChangedMessage = "la moneda ahora vale: $"	+ Utils::intToString(newCoinValue);
		Process::announce(processName, id, LIGHTBLUE, coinValueChangedMessage.c_str());

		readersSemaphore->post();
		writersSemaphore->post();

		sleep(Process::randomBetween(2,4));
	}
	/********************************************************************/
	Process::announce(processName, id, LIGHTBLUE, "proceso terminado.");
	return 0;
}

