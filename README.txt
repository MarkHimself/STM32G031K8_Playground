
Microcontroller:	STM32G031K8Tx
Board:				Nucleo-32 Development board (Nucleo-G031K8)
Processor Core:		Cortex-M0+
Compiler:			arm-none-eabi-gcc
IDE:				STM32CubeIDE


I've created this project to become familiar with the tools that STM offers and to compare STM's microcontrollers/tools to those of Atmel and TI.

The Nucleo-32 package is very small and i'm interested in using it for drones.
I'm hoping to add examples of how to configure and use timers, SPI, I2C, UART, Interrupts and DMA to this repo.



How to Run the Code With STM32CubeIDE
Create an STM32 Project.
Use the microcontroller name for the part number
Give the project a name. The location should be an empty folder.
Targeted Language: C
Targeted Binary Type: Executable
Targeted Project Type: Empty
Delete the default folders/files and save mine into the folder containing the project.
	- Don't delete the .cproject and the .project files and the .settings folder.
Open "Properties", "C/C++ Build":
	- disable the "Generate Makefiles automatically" option.
	- modify the build directory to the project folder (that's where the Makefile is). STM typically keeps their Makefiles in the Debug folder but I prefer the project folder.
		- Should be similar to this: ${workspace_loc:/YourProjectName}
		- Deleting the "Debug" word should be enough when modifing this
Attempt to Build the project. Note: I installed the compiler and added it to my PATH...
Create a Debug Configuration
I've left my settings at default. Only think you may consider modifying is in the Startup tab. The default breakpoint is at "main". Consider changing it to "Reset_Handler".
Run the debug configuration.
Note: Sometimes pressing the "Run" button (Green circle with white arrow) wouldn't work but pressing the button next to it, Debug (Blue circle with spikes) would work.

These basic steps are not made to teach you how to use STM32CubeIDE. They're mainly for you to setup the project, remove STM's automatic makefiles, and set it up for your makefile.


ARM/Vendor Files
The files in the CMSIS directory came from ARM's github page.
The files in the Device directory come from ST (the vendor) and can be find on ARM's website (takes forever to load): https://developer.arm.com/embedded/cmsis/cmsis-packs/devices/








