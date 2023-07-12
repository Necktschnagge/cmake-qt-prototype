# cmake-qt-prototype

## Get Started For Development
### Install Dependencies
   * Windows:
      * Install **cmake**
      * Install the latest C++ compiler with **Visual Studio**.
      * Install **Qt6** or Qt5 (Qt6 is recommended). We recommend to [download the official Installer of **Qt Creator**](https://www.qt.io/product/development-tools). Alternatively, to install Qt from command line using **aqt**, see our [Azure Pipeline configuration](https://github.com/Necktschnagge/cmake-qt-prototype/blob/main/azure-pipelines.yml) (not recommended for Desktop Development).
      * Remark: You may use the MinGW toolchain shipped with the Qt Creator IDE. However we do not recommend this.
      * Check that system environment variables are set to enable cmake to find Qt when running `*--create-project.[ps1|sh|bat]` script at later steps, e.g.:
         * `QT_DIR = C:\Qt`
         * `PATH = C:\Qt\6.5.0\msvc2019_64\bin;...`
   * Linux:
      * Install cmake, gcc/g++, Qt (Qt6 is recommended, Qt5 is supported)
      * Installing Qt [using the official Installer of **Qt Creator**](https://www.qt.io/product/development-tools) is recommended. Alternatively, you may use `apt-get install build-essential libgl1-mesa-dev qt6-base-dev libqt6svg6 libqt6svg6-dev` instead. See our [Azure Pipeline configuration](https://github.com/Necktschnagge/cmake-qt-prototype/blob/main/azure-pipelines.yml) for details.
   * MacOS:
      * *See instructions for Linux. You may use clang instead of g++.*
### Setup Local Repository
   * Clone this repository.
   * `cd` into directory `script/
   * Run `*-clean-init.[ps1|sh|bat]` to update (in particular *initialize*) the git submodules
   * Run `*--create-project.[ps1|sh|bat]` to create a project for your custom toolchain
   * Run `*-build.[ps1|sh|bat]` to build your entire CMake Project, including multiple targets
   
   * On Windows you may use `wos-win-open-sln.ps1` to open your project in Visual Studio
   * You may use Qt Creator to open a cmake project instead of running `*--create-project.[ps1|sh|bat]` scripts and following.

### Qt6 versus Qt5
   * We recommend using the latest version **Qt6**. However we support Qt5 as well.
   * To build your project with Qt5, use the flag `-DUSE_QT6:BOOL=FALSE` for creating projects with cmake instead of just running script `*--create-project.[ps1|sh|bat]`. The complete command to create a project using Qt5 is
```
cmake -S . -B ./build/ -DUSE_QT6:BOOL=FALSE
```
   * When opening a cmake project with Qt Creator, you may select your toolchain while clicking through the project generation assistant.
