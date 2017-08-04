#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "nanoKONTROL2.h"
#include "Board/board_controller.h"

int main()
{
	// Create board
	nanoKONTROL2 nano_kontrol2 { };

	// Initialize controller with board
	board_controller controller(reinterpret_cast<board*>(&nano_kontrol2), true);

	// Setup
	auto result = controller.setup();
	if (result != EXIT_SUCCESS)
		goto exit_fail;

	// Open the ports
	result = controller.open();
	if (result != EXIT_SUCCESS)
		goto exit_fail;

	// Run until escape is pressed
	for (;;)
	{
		std::cout << "Press Esc to stop.." << std::endl;
		if (_getch() == VK_ESCAPE)
			return EXIT_SUCCESS;
	}

exit_fail: // Cleanup
	std::cout << "Press a key to exit.." << std::endl;
	std::cin.get();
	exit(EXIT_FAILURE);
}
