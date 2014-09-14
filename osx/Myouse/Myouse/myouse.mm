#include "myouse.h"

static const int FRAMES_PER_SECOND = 60;

int runMyouse()
{
	try
	{
		myo::Hub hub("com.myouse.myouse-win-app");

		std::cout << "Attempting to find a Myo..." << std::endl;

		myo::Myo * myo = hub.waitForMyo(10000);

		if (!myo)
		{
			throw std::runtime_error("Unable to find a Myo.");
		}

		std::cout << "Connected to a Myo." << std::endl << std::endl;

		myouse::MyouseListener listener;

		hub.addListener(&listener);

		while (true)
		{
			hub.run(1000 / FRAMES_PER_SECOND);
		}
	}
	catch (const std::exception & e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		std::cerr << "Press <enter> to continue.";
		std::cin.ignore();
		return 1;
	}

	return 0;
}
