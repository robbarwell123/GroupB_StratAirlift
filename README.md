# Group B - Strategic Airlift Input Generator

* [Application Overview](#application-overview)
* [Group Information](#group-information)
* [File Structure](#file-structure)
* [How to Compile and Test](#how-to-compile-and-test)
* [Documentation](#documentation)

## Application Overview

The strategic airlift input generator was developed to automatically generate scenarios for use with the strategic airlift simulator.  This is required to generate a large volume of scenarios for the simulator to run based on configuration parameters specified by the user through a config file.

The user is able to specify the initial state of the generator which includes the number of locations the user wants to generate, connections to main logistic bases and the number of scenarios to generate. Further details about the initial state are located in the user documentation.

The generator will output scenario configuration files which the strategic airlift simulator can use to run simulations. 

## Group Information

**Organization:** Carleton Unviersity (SYSC 5709)

### Authors:

**1. Lukeman Hakkim Sheik Alavudeen**

 - Student Number: 101124231
 - GitHub: lukemanhakkim

**2. Olumide Akinola**

 - Student Number: 101174210
 - GitHub: Myde001

**3. Edwin Omoigui**

 - Student Number: 101134330
 - GitHub: Edwin-programmer

**4. Rob Barwell**

 - Student Number: 101092722
 - GitHub: robbarwell123

## File Structure

The following file structure is used to organize files in this repository:

* doc - Includes detailed developer documentation.  The main documentation can be found on the [Strategic Airlift Input Generator Wiki](https://github.com/robbarwell123/GroupB_StratAirlift/wiki).
* include - The main header files are listed below:
  * common_functions.h - Lists all the functions shared throughout the application.
  * data_types.h - Defines the custom data types.
  * strat\_airlift\_functions.h - Lists all the main functions of the application.
  * Other header files are included to capture supporting functions required for each main function. 
* src - Contains the definition for all functions.
* test
  * include - Contains the declarations for all unit tests.
  * src - Contains the definitions for all unit tests.  `test_main.c` is used to call all unit tests.

## How to Compile and Test

The Strategic Airlift Input Generator only requires optional dependencies.  The instructions below have been verified to work on Windows using Cygwin and gcc.

**Dependencies**

* Doxygen (optional) - Required to rebuild the detailed development documentation.  Can be installed using `apt-get install doxygen` on most systems.

### Compile and Build Instructions

The following make commands are available to help compile and build the application:

* `make all` (default) Will build the application and test application.
* `make app` Will build only the application.
* `make test` Will build only the test application.
* `make doxygen` Will build the detailed development documentation.
* `make clean` Will remove all build artifacts.

**Note:** DEBUG can be enabled by appending `DEBUG=1` to the make command (i.e. `make DEBUG=1`)

### Run Application

The application can be run with default values using the following command: `./bin/StratAirliftInit.exe`.

To run the application with user defined values you need to execute the application in the `bin` directory with `StratAirliftInit.exe` and one or more of the command line options.

* `-c` (Optional) Followed by the configuration file you want to use.
* `-d` (Optional) Followed by the common list of airports you want to use.
* `-o` (Optional) The output directory to place the scenario files.  Will default to `output_folder` if this option is not specified.
* `-v` (Optional) Will display the current version of the program and terminate regardless of other options specified.

Additional details can be found in the [user documentation](https://github.com/robbarwell123/GroupB_StratAirlift/wiki).

### Test Application

Use `./bin/StratAirliftInit_Test.exe` to run all tests.  The results are displayed to stdout.  If you want to save the results to a file append "`> results.txt`" to the command.

## Documentation

User documentation can be found in the Github repository at [Strategic Airlift Input Generator Wiki](https://github.com/robbarwell123/GroupB_StratAirlift/wiki).

If the user would like to see the detailed developer documentation they will need to generate it using the `make doxygen` command.  This was done to keep the code base clean.

Additional developer documentation is found in the [Strategic Airlift Input Generator Wiki](https://github.com/robbarwell123/GroupB_StratAirlift/wiki).

