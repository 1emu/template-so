/*
 * Initializer.cpp
 *
 * Created on: May 10, 2014
 * Author: jp
 */

#include "utils/Includes.h"

using namespace std;

int main(int argc, char** argv) {

	char* programName = argv[0];
	stringstream ss;

	// Si se ingresan menos argumentos de los necesarios
	if (argc < 3) {
		string msg = "Usage ";
		msg = msg + programName + " <-readers> <-writers> \n";
		Colors::writeerr(msg, RED);
		exit(EXIT_FAILURE);
	}

	int amountOfReaders = atoi(argv[1]);
	int amountOfWriters = atoi(argv[2]);
	int id = MAIN_PROGRAM_ID;


	Coin* coin = (Coin*) SharedMemory::create(SHARED_MEMORY_ID, sizeof(Coin));
	coin->coinValue = INITIAL_COIN_VALUE;

	SemaphoreArray::create(READERS_MUTEX_ID);
	SemaphoreArray::create(WRITERS_MUTEX_ID);

	Process::announce(MAIN_PROGRAM_NAME, id, LIGHTBLUE, "ipcs creados.");

	Process::createProcesses(R_PROCESS_NAME, amountOfReaders, R_FIRST_PROCESS_ID);
	Process::createProcesses(W_PROCESS_NAME, amountOfWriters, W_FIRST_PROCESS_ID);

	Process::announce(MAIN_PROGRAM_NAME, id, LIGHTBLUE, "inicializacion completa.");

}

