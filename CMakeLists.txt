cmake_minimum_required(VERSION 3.14)
project(ForkProcess C)

set(CMAKE_C_STANDARD 11)

add_executable(ForkProcess main.c incl/cpu/Collector_CPU_Minner.cpp incl/cpu/Collector_CPU_Minner.h incl/memory/Collect_Memory_Minner.cpp incl/memory/Collect_Memory_Minner.h incl/network/Collector_Network_Minner.cpp incl/network/Collector_Network_Minner.h incl/disk/Collector_Disk_Minner.cpp incl/disk/Collector_Disk_Minner.h)