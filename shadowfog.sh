#!/bin/bash

# Check if running as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root" >&2
    exit 1
fi

set -e

echo "Updating package lists..."
apt-get update

echo "Verifying and installing the dependencies..."

# Verifies and installs g++
if ! command -v g++ &> /dev/null; then
    echo "g++ is not installed. Installing it..."
    apt-get install g++ -y
else
    echo "g++ already installed."
fi

# Verifies and installs figlet
if ! command -v figlet &> /dev/null; then
    echo "figlet is not installed. Installing it..."
    apt-get install figlet -y
else
    echo "figlet already installed."
fi

echo
echo "All dependencies installed."
echo

echo "Compiling the program..."
# Make sure to check the correct source file and compilation flags
g++ -o ShadowFog shadowfog.cpp
echo "Compilation finished."
echo

echo "Executing ShadowFog..."
./ShadowFog
