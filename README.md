# TestQCompressionLib

### Intro

This Qt application is used to test the compression libraries:
* [Qliblzma](https://github.com/ceccopierangiolieugenio/Qliblzma)

It provide also a basic reference code for their usage inside a Qt Project.

All the different libraries are loaded as submodules inside the [lib](https://github.com/ceccopierangiolieugenio/TestQCompressionLib/tree/master/lib) folder

### Get the code

Clone the project and initialize the submodules:

       git clone https://github.com/ceccopierangiolieugenio/TestQCompressionLib.git test
       cd test
       git submodule update --init

### Build and run

Use [Qt Creator](https://www.qt.io/ide/) to build and run it.

Currently tested on:
* Win7
  * Qt Creator 4.3.0
  * Kit: Qt 5.8.0 MinGW 32bit
  * MinGW 5.3.0 32bit
  
* [LinuxMint 18.1](https://www.linuxmint.com)
  * Qt Creator 3.5.1
  * Kit: Qt 5.5.1
  * gcc 5.4.0-6ubuntu1~16.04.4
  
 
