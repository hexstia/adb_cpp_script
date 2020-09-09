cmake_minimum_required(VERSION 2.8.4)
project(cc)

set(CMAKE_CXX_STANDARD 11)

add_executable(cc main.cpp ICommand.h Adb_Command.cpp Adb_Command.h Device.cpp Device.h Adb_Log.cpp Adb_Log.h Adb_Shell.cpp Adb_Shell.h DeviceList.h DeviceList.cpp Tools.cpp Tools.h)