#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>

#include <map>
#include <string>

using namespace std;			// cout, endl
using namespace this_thread;	// sleep_for
using namespace chrono;			// seconds, milliseconds

enum Emotions { CALM, ALERT, AGITATED, SURPRISED, HAPPY, ANGRY };
Emotions NPC = CALM;
bool program_running = false;
bool Noise = false;
bool PeopleNearby = false;
bool PeopleAggressive = false;
bool PeopleFriendly = false;
bool PeopleAttack = false;

bool toggle(bool input)
{
	bool value = false;

	if (input)
	{
		value = false;
	}
	else
	{
		value = true;
	}

	return value;
}

void Transitions(Emotions* Original, Emotions Next)
{
	//Pre switch functions
	std::cout<<"From:"<< Original << "To:"<<Next<< "\n";

	*Original = Next;

	//post switch functions
	
	return;
}

void GetInput()
{
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

		// Check for N key. See table here http://www.asciitable.com/
		if (input_char == 78)
		{
			Noise = toggle(Noise);
		}
		// Check for P key. See table here http://www.asciitable.com/
		if (input_char == 80)
		{
			PeopleNearby = toggle(PeopleNearby);
		}
		// Check for A key. See table here http://www.asciitable.com/
		if (input_char == 65)
		{
			PeopleAggressive = toggle(PeopleAggressive);
		}
		// Check for F key. See table here http://www.asciitable.com/
		if (input_char == 70)
		{
			PeopleFriendly = toggle(PeopleFriendly);
		}
		// Check for D key. See table here http://www.asciitable.com/
		if (input_char == 68)
		{
			PeopleAttack = toggle(PeopleAttack);
		}
	}
}

void function()
{
	//mapped classes method

	class BaseState
	{
	public:
		virtual void run() = 0;
	};

	class ExtendedState0 : public BaseState
	{
		virtual void run()
		{
			//Default state
			PeopleAggressive = false;
			PeopleFriendly = false;
			PeopleAttack = false;

			//If NPC hears a noise at any time and there is no one else about then they become ALERT
			if (Noise && !PeopleNearby)
			{
				Transitions(&NPC, ALERT);
			}

			//If NPC sees another character at any time they become AGITATED
			if (PeopleNearby)
			{
				Transitions(&NPC, AGITATED);
			}
		}
	};
	class ExtendedState1 : public BaseState
	{
		virtual void run()
		{
			//If the noise stops and nothing else happens then the NPC becomes CALM
			if (!Noise)
			{
				Transitions(&NPC, CALM);
			}
		}
	};
	class ExtendedState2 : public BaseState
	{
		virtual void run()
		{
			//If the other character starts to act aggressively then they are SURPRISED
			if (PeopleAggressive)
			{
				Transitions(&NPC, SURPRISED);
			}
			//If the other character is friendly and cracks a joke then they become HAPPY
			if (PeopleFriendly)
			{
				Transitions(&NPC, HAPPY);
			}

			//people leave
			if (!PeopleNearby)
			{
				Transitions(&NPC, CALM);
			}
		}
	};
	class ExtendedState3 : public BaseState
	{
		virtual void run()
		{
			//If the other character is aggressive and attacks they become ANGRY
			if (PeopleAttack)
			{
				Transitions(&NPC, ANGRY);
			}
		}
	};
	class ExtendedState4 : public BaseState
	{
		virtual void run()
		{
			//people leave
			if (!PeopleNearby)
			{
				Transitions(&NPC, CALM);
			}
		}
	};
	class ExtendedState5 : public BaseState
	{
		virtual void run()
		{
			//people leave
			if (!PeopleNearby)
			{
				Transitions(&NPC, CALM);
			}
		}
	};

	std::map<std::string, BaseState*> map_of_states;
	map_of_states["CALM"] = new ExtendedState0;
	map_of_states["ALERT"] = new ExtendedState1;
	map_of_states["AGITATED"] = new ExtendedState2;
	map_of_states["SURPRISED"] = new ExtendedState3;
	map_of_states["HAPPY"] = new ExtendedState4;
	map_of_states["ANGRY"] = new ExtendedState5;

	BaseState* current_state = map_of_states["CALM"];

	while (program_running)
	{
		current_state->run();
		GetInput();
	}
}

int main()
{
	program_running = true;	


	//switch statement method
	//do {

	//	/*

	//	Write your code here for the finite state machine example

	//	*/

	//	switch (NPC)
	//	{
	//	case CALM: std::cout << "CALM\n";   
	//		//Default state
	//		PeopleAggressive = false;
	//		PeopleFriendly = false;
	//		PeopleAttack = false;

	//		//If NPC hears a noise at any time and there is no one else about then they become ALERT
	//		if (Noise && !PeopleNearby)
	//		{
	//			Transitions(&NPC, ALERT);		
	//		}

	//		//If NPC sees another character at any time they become AGITATED
	//		if (PeopleNearby)
	//		{
	//			Transitions(&NPC, AGITATED);
	//		}
	//		break;
	//	case ALERT: std::cout << "ALERT\n"; 
	//		
	//		//If the noise stops and nothing else happens then the NPC becomes CALM
	//		if (!Noise)
	//		{
	//			Transitions(&NPC, CALM);
	//		}
	//		break;
	//	case AGITATED: std::cout << "AGITATED\n";  
	//		//If the other character starts to act aggressively then they are SURPRISED
	//		if (PeopleAggressive)
	//		{
	//			Transitions(&NPC, SURPRISED);
	//		}
	//		//If the other character is friendly and cracks a joke then they become HAPPY
	//		if (PeopleFriendly)
	//		{
	//			Transitions(&NPC, HAPPY);
	//		}

	//		//people leave
	//		if (!PeopleNearby)
	//		{
	//			Transitions(&NPC, CALM);
	//		}

	//		break;
	//	case SURPRISED: std::cout << "SURPRISED\n";   
	//		//If the other character is aggressive and attacks they become ANGRY
	//		if (PeopleAttack)
	//		{
	//			Transitions(&NPC, ANGRY);
	//		}
	//		
	//		break;
	//	case HAPPY: std::cout << "HAPPY\n"; 
	//		//people leave
	//		if (!PeopleNearby)
	//		{
	//			Transitions(&NPC, CALM);
	//		}
	//		
	//		break;
	//	case ANGRY: std::cout << "ANGRY\n";  
	//		//people leave
	//		if (!PeopleNearby)
	//		{
	//			Transitions(&NPC, CALM);
	//		}
	//		
	//		break;
	//	}

	cout << "Starting Finite State Machine" << endl;
	do 
	{
		function();
	} while(program_running);

	cout << "Ending Finite State Machine" << endl;

	return 0;
}