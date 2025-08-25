This repository intended to place several STM32 Projects I'm planning to create while working with ***NUCLEO-F401RE*** board.  
The [***STM32CubeIDE***](https://www.st.com/en/development-tools/stm32cubeide.html) development tool and [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)  graphical configuration tool will be used.  
The first of such projects is [***STM32F4xx_LCD1602_parallel***](https://github.com/Oleh-Dubrovskyi/STM32Projects/tree/master/STM32F4xx_LCD1602_parallel).

## Installation

1. You should [***install the STM32CubeIDE***](https://www.st.com/resource/en/user_manual/um2563-stm32cubeide-installation-guide-stmicroelectronics.pdf) in your computer.
2. To clone a project from GitHub and import it into your STM32CubeIDE workspace, follow these steps:
    - Clone the Repository Locally by means of Git client or by using <span style="color: blue;">`git clone`</span> command.
    - Import STM32 Project (for example, ***STM32F4xx_LCD1602_parallel***) into STM32CubeIDE workspace
        - Open STM32CubeIDE and ensure you are in the desired workspace.
        - Navigate to *File* > *Import*: in the top menu bar.
        - In the *Import* window, expand the *General* folder and select *Existing Projects into Workspace*. Click *Next*.
        - On the next screen, you will have two options for selecting the project: *Select root directory* and *Select archive file*.
        - Select root directory: Click *Browse...* and navigate to the root directory of your STM32 project on your file system.  
          This directory should contain file <span style="color: blue;">`.project`</span>.  
          Once the directory is selected, STM32CubeIDE will display the projects found within that location.  
          Select the specific project(s) you wish to import into your workspace.
          *Optional:* If you want a copy of the project files to be placed within your workspace directory, check the *Copy projects into workspace* option.  
          If you leave this unchecked, the project will be linked to its original location on the file system.
        - Click *Finish* to complete the import process.  
          The selected project will now appear in your STM32CubeIDE Project Explorer.

## Configuration And Usage

The detailed instructions concerning to configuration, build, and run the projects will be placed into <span style="color: blue;">`readme.md`</span> files for the respective projects.

## License

The terms of the [***FreeBSD License***](https://opensource.org/licenses/BSD-2-Clause) are applicable to the software projects of this repository.

## Contacts

- Email: duoleedu@gmail.com
- GitHub: [Oleh-Dubrovskyi](https://github.com/Oleh-Dubrovskyi)
