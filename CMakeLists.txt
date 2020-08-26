cmake_minimum_required(VERSION 3.0)

# Project Name
project(ilitek_intro)

# Source Files
set(C_SOURCES
    raspberry_pi_demo.c
    ilitek_protocol.c
    )

# Executable
add_executable(ilitek_on_raspberry_pi_demo ${C_SOURCES})
