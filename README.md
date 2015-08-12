# USgHIFU-qt
This is a software developed in Qt for the phased array B-mode ultrasound guided high-intensity focused ultrasound system.

# Console Plan Library  
Three file folders with the names of bin/lib/example  

In the bin file folder, there are two files, dll-format file (ConsolePlan.dll) and lib-format file (libConsolePlan.a, MinGW Compiler outputs .a file while MSVC Compiler outputs .lib file).  

In the lib file folder, there are three head files. And you can see the declaration of the class in the consoleplan.h file.

In the example file folder, .exe file could be generated, and the ConsolePlan.dll file should be put into the debug/release folder so that .exe could be executed. Otherwise the .exe file would be crashed.

Configuration in the .pro file as below,  

INCLUDEPATH += /libFolder  

LIBS += /binFolder/dllFile  
