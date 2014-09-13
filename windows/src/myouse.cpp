#include <myo/myo.hpp>
#include <Windows.h>

int main(int argc, char ** argv)
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


	}
}
