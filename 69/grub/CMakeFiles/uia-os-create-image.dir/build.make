# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/knut/ikt218-osdev/69

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/knut/ikt218-osdev/69

# Utility rule file for uia-os-create-image.

# Include any custom commands dependencies for this target.
include grub/CMakeFiles/uia-os-create-image.dir/compiler_depend.make

# Include the progress variables for this target.
include grub/CMakeFiles/uia-os-create-image.dir/progress.make

grub/CMakeFiles/uia-os-create-image:
	cd /home/knut/ikt218-osdev/69/grub && /usr/bin/cmake -E copy /home/knut/ikt218-osdev/69/kernel.bin /home/knut/ikt218-osdev/69/iso/boot/
	cd /home/knut/ikt218-osdev/69/grub && /usr/bin/grub-mkrescue --output=/home/knut/ikt218-osdev/69/kernel.img /home/knut/ikt218-osdev/69/iso
	cd /home/knut/ikt218-osdev/69/grub && /bin/sh /home/knut/ikt218-osdev/69/disk.sh disk.iso

uia-os-create-image: grub/CMakeFiles/uia-os-create-image
uia-os-create-image: grub/CMakeFiles/uia-os-create-image.dir/build.make
.PHONY : uia-os-create-image

# Rule to build all files generated by this target.
grub/CMakeFiles/uia-os-create-image.dir/build: uia-os-create-image
.PHONY : grub/CMakeFiles/uia-os-create-image.dir/build

grub/CMakeFiles/uia-os-create-image.dir/clean:
	cd /home/knut/ikt218-osdev/69/grub && $(CMAKE_COMMAND) -P CMakeFiles/uia-os-create-image.dir/cmake_clean.cmake
.PHONY : grub/CMakeFiles/uia-os-create-image.dir/clean

grub/CMakeFiles/uia-os-create-image.dir/depend:
	cd /home/knut/ikt218-osdev/69 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/knut/ikt218-osdev/69 /home/knut/ikt218-osdev/69/grub /home/knut/ikt218-osdev/69 /home/knut/ikt218-osdev/69/grub /home/knut/ikt218-osdev/69/grub/CMakeFiles/uia-os-create-image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : grub/CMakeFiles/uia-os-create-image.dir/depend
