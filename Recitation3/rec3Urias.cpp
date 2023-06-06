// Alexis Urias
// CSE 310 Summer 23

#include <iostream>
#include <string>

using namespace std;

struct LandingRequest {		// struct for plane landing request
	string flightNumber;	// flight number/ID
	int waitDuration;		// wait time before the plane needs to land
	LandingRequest() : flightNumber(""), waitDuration(0) {}	// constructor for flight number and wait time

	LandingRequest(const string& flight, int duration)
		: flightNumber(flight), waitDuration(duration) {}
};

const int MAX_LIMIT = 50;

void heapInsert(LandingRequest* queue, int& size, int maxSize, const LandingRequest& request);	// forward declaration
LandingRequest heapExtract(LandingRequest* queue, int& size);
bool heapEmpty(const int& size);

int main() {

	LandingRequest* landingQueue = new LandingRequest[MAX_LIMIT];	// chose 50 for limit on queue
	int size = 0;

	int choice = 0;		// user input for switch value
	do
	{
		cout << "1. Make a landing request\n";		// menu for plane landing system
		cout << "2. Land a plane\n";
		cout << "3. List all the landing request\n";
		cout << "4. Quit\n";
		cout << "\nSelect your option: ";
		cin >> choice;
		cin.ignore();			


		switch (choice) {		// switch for user input 
		case 1: {				// case 1 for flight ingormation and key (flight number and wait duration)
			string flightNumber;
			int waitTime;
			cout << "\nEnter flight number: ";
			cin >> flightNumber;
			cout << "Enter wait duration (in minutes): ";
			cin >> waitTime;
			LandingRequest request(flightNumber, waitTime);
			heapInsert(landingQueue, size, MAX_LIMIT, request);
			cout << "\nLanding request added.\n";
			break;
		}
		case 2: {				// case 2 is for the plane request with the highest priority (the lowest time)
			if (!heapEmpty(size)) {
				LandingRequest request = heapExtract(landingQueue, size);
				cout << "\nPlane landed. Flight Number: " << request.flightNumber << ", Wait Duration: " << request.waitDuration << " minutes.\n";
			}
			else {
				cout << "\nNo planes in the landing queue.\n";
			}
			break;
		}
		case 3: {				// case 3 list all the landing request in the queue
			if (!heapEmpty(size)) {
				cout << "\nList of landing requests:\n";
				for (int i = 0; i < size; i++) {
					cout << "\nFlight Number: " << landingQueue[i].flightNumber << ", Wait Duration: " << landingQueue[i].waitDuration << " minutes.\n";
				}
			}
			else {
				cout << "\nNo planes in the landing queue.\n";
			}
			break;
		}
		case 4: {		// case 4 quits the program
			cout << "\nExiting the Plane Landing System.\n";
			break;
		}
		default: {		// default case for invalid input
			cout << "\nInvalid input. Try again.\n";
			break;
		}
		}

		cout << endl;

	} while (choice != 4);

	delete[] landingQueue;	// delete 

	return 0;
}


void heapInsert(LandingRequest* queue, int& size, int maxSize, const LandingRequest& request) {	// performs minimum heap insertion
	if (size == maxSize) {
		cout << "\nThe Queue is full.\n";	// check for a full queue
		return;
	}

	int i = size;
	queue[i] = request;

	while (i > 0) {
		int p = (i - 1) / 2; // parent index --> p
		if (queue[i].waitDuration < queue[p].waitDuration) {
			swap(queue[i], queue[p]);	// exchange
			i = p;		// set p to i
		}
		else {
			break;
		}
	}

	size++;
}


LandingRequest heapExtract(LandingRequest* queue, int& size) {	// method removes the element with the highest priority (lowest time) from the priority queue
																// min heap extract
	if (size == 0) {
		cout << "\nThe Queue is empty.\n"; // check for a full queue
		return LandingRequest();
	}

	LandingRequest highestPriority = queue[0]; // highest priority object set to first index of queue
	queue[0] = queue[size - 1];
	size--;

	int i = 0;
	while (true) {				// find the plane request with the min key value
		int l = (2 * i) + 1;	// left child 
		int r = (2 * i) + 2;	// right child
		int min = i;

		if (l < size && queue[l].waitDuration < queue[min].waitDuration) {	// set left child to min if true
			min = l;
		}
		if (r < size && queue[r].waitDuration < queue[min].waitDuration) {	// set right child to min if true
			min = r;
		}

		if (min != i) {
			swap(queue[i], queue[min]); // exchange queue min and queue index
			i = min;
		}
		else {
			break;
		}
	}

	return highestPriority;		// return the plane request with the highest priority
}


bool heapEmpty(const int& size) {	// is the heap empty
	return size == 0;
}