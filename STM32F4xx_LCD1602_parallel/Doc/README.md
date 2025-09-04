# LCD1602 Display connected to STM32F4xx board using 4-bit or 8-bit data bus

This STM32 Project is intended to create an API that would help to connect LCD1602 Display to the STM32F4xx board by means of 4-bit or 8-bit parallel data bus.  
The project is based on the [***STM32 Cube Hardware Abstraction Layer (HAL) library***](https://www.st.com/resource/en/user_manual/um1725-description-of-stm32f4-hal-and-lowlayer-drivers-stmicroelectronics.pdf).  
The project includes a complete set of tests for the proposed API.  
The tests demonstrate how to use LCD1602 Display features with proposed API.

<a id="contents_id"></a>
## Contents

- [Contents](#contents_id)
- [Features](#features_id)
- [Installation](#installation_id)
- [Configuration](#configuration_id)

    - [Hardware elements](#hardware_elements_id)
    - [Hardware connection](#hardware_connection_id)
    - [GPIO configuration](#gpio_configuration_id)

- [Testing](#testing_id)
- [Usage](#usage_id)
- [License](#license_id)
- [Acknowledgements](#acknowledgements_id)
- [Contacts](#contacts_id)

<a id="features_id"></a>
## Features

The project supports several functions. They are:

- Configure data bus and registers of the LCD1602 for the 4-bits and for the 8-bits modes
- Configure a data bus pins' set
- Configure Instruction/Data register selection pin
- Configure Enable signal pin
- Initialize the Display for the 4-bits and for the 8-bits modes
- Write byte to the instruction register
- Select instruction or data register to write
- Write byte to the data register
- Screen Clear
- Set Cursor position
- Set moving direction of cursor to left/right
- Set increment cursor moving direction (write from left to right)
- Set decrement cursor moving direction (write from right to left)
- Scroll Display to left/right
- Show/Hide Display
- Show/Hide cursor
- Switch cursor to blink on/off
- Write string from cursor point
- Write number from cursor point
- Write float from cursor point
- Create custom symbol
- Write custom symbol

<a id="installation_id"></a>
## Installation

1. You should [***install the STM32CubeIDE***](https://www.st.com/resource/en/user_manual/um2563-stm32cubeide-installation-guide-stmicroelectronics.pdf) in your computer.
2. To clone a project from GitHub and import it into your STM32CubeIDE workspace, follow these steps:
    - Clone the Repository Locally by means of Git client or by using <span style="color: blue;">`git clone`</span> command.
    - Import STM32 Project ***STM32F4xx_LCD1602_parallel*** into your STM32CubeIDE workspace
        - Open STM32CubeIDE and ensure you are in the desired workspace.
        - Navigate to *File* > *Import*: in the top menu bar.
        - In the *Import* window, expand the *General* folder and select *Existing Projects into Workspace*. Click *Next*.
        - On the next screen, you will have two options for selecting the project: *Select root directory* and *Select archive file*.
        - Select root directory: Click *Browse...* and navigate to the root directory of the STM32 project ***STM32F4xx_LCD1602_parallel*** on your file system.  
          This directory should contain file <span style="color: blue;">`.project`</span>.  
          Once the directory is selected, STM32CubeIDE will display the projects found within that location.  
          Select the project ***STM32F4xx_LCD1602_parallel*** to import it into your workspace.
          *Optional:* If you want a copy of the project files to be placed within your workspace directory, check the *Copy projects into workspace* option.  
          If you leave this unchecked, the project will be linked to its original location on the file system.
        - Click *Finish* to complete the import process.  
          The project ***STM32F4xx_LCD1602_parallel*** will now appear in your STM32CubeIDE Project Explorer.

<a id="configuration_id"></a>
## Configuration

<a id="hardware_elements_id"></a>
### Hardware elements

The project ***STM32F4xx_LCD1602_parallel*** requires such hardware elements:

- NUCLEO-F401RE board
- LCD1602 Display
- Variable resistor 10 kOM
- Resistor 100 OM

<a id="hardware_connection_id"></a>
### Hardware connection

1. Connect the LCD1602 VSS (pin 1), RW (pin 5), and K (pin 16) to NUCLEO-F401RE GND (pin CN6-6) and to the left contact of the variable resistor 10 kOM.
2. Connect the LCD1602 VDD (pin 2) to the NUCLEO-F401RE +5V (pin CN6-5).
3. Connect the LCD1602 V0 (pin 3) to the middle contact of the variable resistor 10 kOM.
4. Connect the right contact of the variable resistor to the NUCLEO-F401RE 3V3 (pin CN6-4) and to the left contact of the Resistor 100 OM.
5. Connect the right contact of the Resistor 100 OM to the LCD1602 A (pin 15).
6. Connect the LCD1602 RS (pin 4) to the NUCLEO-F401RE D4 (PB5, CN9-5).
7. Connect the LCD1602 E (pin 6) to the NUCLEO-F401RE D5 (PB4, CN9-6).
8. Connect the LCD1602 D0, D1, D2, D3 (pins 7-10) to the NUCLEO-F401RE A1 (PA1, CN8-2), A2 (PA4, CN8-3), A3 (PB0, CN8-4), A4 (PC1, CN8-5).
9. Connect the LCD1602 D4, D5, D6, D7 (pins 11-14) to the NUCLEO-F401RE D9 (PC7, CN5-2), D10 (PB6, CN5-3), D11 (PA7, CN5-4), D12 (PA6, CN5-5).

Please, take a look at the connection diagram:

![LCD1602-F401RE connection diagram](./LCD1602-F401RE_connection_diagram.jpg)  

The NUCLEO-F401RE board's pins usage is shown below:  

![NUCLEO-F401RE_connections](./NUCLEO-F401RE_connections.jpg)  

The LCD1602's connections are shown below:  

![LCD1602_connections](./LCD1602_connections.jpg)  

A general picture of connections between NUCLEO-F401RE and LCD1602 is shown below:  

![LCD1602 and F401RE connections](./LCD1602-F401RE_connections.jpg)  

<a id="gpio_configuration_id"></a>
### GPIO configuration

Please, take a look at the ***STM32F4xx_LCD1602_parallel.ioc*** and analyze GPIO configuration:

![Pinout View](./PinoutView.jpg)  

Functions <span style="color: blue;">`Lcd1602Configure4Bits()`</span> and <span style="color: blue;">`Lcd1602Configure8Bits()`</span> are intended to configure GPIOs for 4-bit and 8-bit modes, Enable signal pin and Register selection pin:  

![Data Bus Configuration](./DataBusConfiguration.jpg)  

<a id="testing_id"></a>
## Testing

Function <span style="color: blue;">`TestsLCD1602()`</span> is used to perform 21 different steps to test the project's API:  

![CommonLCD1602Test](./CommonLCD1602Test.jpg)

The cycle of testing consists of two steps. Each step suppose to call function <span style="color: blue;">`TestsLCD1602()`</span> for 4-bit mode and then for 8-mode:  

![CycleOfTesting](./CycleOfTesting.jpg)

[***You can take a look at the results of testing by clicking here. It takes 5 minutes***](./STM32F401_LCD1602_4-bit_8bit_tests.mp4)

<a id="usage_id"></a>
## Usage

After [Installation](#installation_id) and [Configuration](#configuration_id) steps you can build and run this project on the NUCLEO-F401RE board.  

1. Connect your NUCLEO-F401RE board to your computer:

![Connect NUCLEO-F401RE to your computer](./ConnectNUCLEO-F401RE_to_computer.jpg)

2. Start STM32CubeIDE in the workspace where you have already prepared this project. Then click on ***hammer icon*** to build the project:

![Build the Project](./BuildProject.jpg)

3. Getting clean build you will be able to run it on your NUCLEAR-F401RE board by click on ***Run icon***:

![Run the Project](./RunProject.jpg)

<a id="license_id"></a>
## License

The terms of the [***FreeBSD License***](https://opensource.org/licenses/BSD-2-Clause) are applicable to the software projects of this repository.

<a id="acknowledgements_id"></a>
## Acknowledgements

While working on this project I've got several helpful sources.  
Here they are:  

1. [***UM1725. STM32 Cortex-M4 MCUs and MPUs programming manual. Rev 8 - March 2023***](https://www.st.com/resource/en/programming_manual/pm0214-stm32-cortexm4-mcus-and-mpus-programming-manual-stmicroelectronics.pdf)
2. [***DS10086. STM32F401xD STM32F401xE. Revision 4. 24-Jan-2025***](https://www.st.com/resource/en/datasheet/stm32f401re.pdf)
3. [***UM2563. STM32CubeIDE installation guide. Rev 5 - March 2024***](https://www.st.com/resource/en/user_manual/um2563-stm32cubeide-installation-guide-stmicroelectronics.pdf)
4. [***LCD MOUDULE SPECIFICATION FOR APPROVAL. Waveshare LCD1602. INITIAL RELEASE***](https://www.waveshare.com/datasheet/LCD_en_PDF/LCD1602.pdf)

<a id="contacts_id"></a>
## Contacts

- Email: duoleedu@gmail.com
- GitHub: [Oleh-Dubrovskyi](https://github.com/Oleh-Dubrovskyi)

