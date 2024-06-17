#!/bin/bash

# Detect operating system (Debian/Ubuntu or Fedora/CentOS)
if [ "$(command -v apt)" ]; then
  # Update package manager and install for Ubuntu/Debian
  echo "Updating apt package manager..."
  sudo apt update
  echo "Installing required packages..."
  sudo apt install libglib2.0-dev
  sudo apt install libpoppler-glib8
  sudo apt install libpoppler-glib-dev
elif [ "$(command -v dnf)" ]; then
  # Update package manager and install for Fedora/CentOS
  echo "Updating dnf package manager..."
  sudo dnf update
  echo "Installing required packages..."
  sudo dnf install glib2 poppler-glib-devel
else
  echo "Error: Unsupported operating system."
  exit 1
fi

echo "Installation complete!"
