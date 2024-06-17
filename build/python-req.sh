#!/bin/bash

# Check for python3
if ! command -v python3 &> /dev/null; then
  echo "Python 3 is not installed. Installing..."
  # Detect operating system (Debian/Ubuntu or Fedora/CentOS)
  if [ "$(command -v apt)" ]; then
    sudo apt update
    sudo apt install -y python3 python3-pip
  elif [ "$(command -v dnf)" ]; then
    sudo dnf update
    sudo dnf install -y python3 python3-pip
  else
    echo "Error: Unsupported operating system."
    exit 1
  fi
else
  echo "Python 3 is already installed."
fi

# Check for pip3
if ! command -v pip3 &> /dev/null; then
  echo "pip3 is not installed. Installing..."
  # Assuming python3 is installed at this point
  python3 -m ensurepip --upgrade
else
  echo "pip3 is already installed."
fi

# Install pyPDF2
echo "Installing pyPDF2..."
python3 -m pip install pyPDF2

echo "Installation complete!"
