#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>

using namespace std;			// cout, endl
using namespace this_thread;	// sleep_for
using namespace chrono;			// seconds, milliseconds

int main()
{
	bool program_running = true;
	bool Noise = false;
	bool PeopleNearby = false;
	bool PeopleAggressive = false;
	bool PeopleFriendly = false;
	bool PeopleAttack = false;

	enum Emotions{ CALM, ALERT, AGITATED, SURPRISED, HAPPY,ANGRY };
	Emotions NPC = CALM;
	cout << "Starting Finite State Machine" << endl;

	do {

		/*

		Write your code here for the finite state machine example

		*/

		switch (NPC)
		{
		case CALM: std::cout << "CALM\n";   
			//Default state
			//If other character appears to be friendly then they become CALM

			//If NPC hears a noise at any time and there is no one else about then they become ALERT
			if (Noise && !PeopleNearby)
			{
				NPC = ALERT;
			}

			//If NPC sees another character at any time they become AGITATED
			if (PeopleNearby)
			{
				NPC = AGITATED;
			}
			break;
		case ALERT: std::cout << "ALERT\n"; 
			
			//If the noise stops and nothing else happens then the NPC becomes CALM
			if (!Noise)
			{
				NPC = CALM;
			}
			break;
		case AGITATED: std::cout << "AGITATED\n";  
			//If the other character starts to act aggressively then they are SURPRISED
			if (PeopleAggressive)
			{
				NPC = SURPRISED;
			}
			//If the other character is friendly and cracks a joke then they become HAPPY
			if (PeopleFriendly)
			{
				NPC = HAPPY;
			}

			//people leave
			if (!PeopleNearby)
			{
				NPC = CALM;
			}

			break;
		case SURPRISED: std::cout << "SURPRISED\n";   
			//If the other character is aggressive and attacks they become ANGRY
			if (PeopleAttack)
			{
				NPC = ANGRY;
			}
			
			break;
		case HAPPY: std::cout << "HAPPY\n"; 
			//people leave
			if (!PeopleNearby)
			{
				NPC = CALM;
			}
			
			break;
		case ANGRY: std::cout << "ANGRY\n";  
			//people leave
			if (!PeopleNearby)
			{
				NPC = CALM;
			}
			
			break;
		}


		// Sleep the current thread for 1000 milliseconds. Can be repalce with seconds(1)
		sleep_for(milliseconds(1000));

		if (_kbhit())
		{
			char input_char = _getch();

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}
		}

	} while(program_running);

	cout << "Ending Finite State Machine" << endl;

	return 0;
}