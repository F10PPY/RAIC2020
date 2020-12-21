# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/f10ppy/Projects/RAIC2020

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/f10ppy/Projects/RAIC2020

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/f10ppy/Projects/RAIC2020/CMakeFiles /home/f10ppy/Projects/RAIC2020/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/f10ppy/Projects/RAIC2020/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named aicup2020

# Build rule for target.
aicup2020: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 aicup2020
.PHONY : aicup2020

# fast build rule for target.
aicup2020/fast:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/build
.PHONY : aicup2020/fast

DebugInterface.o: DebugInterface.cpp.o

.PHONY : DebugInterface.o

# target to build an object file
DebugInterface.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/DebugInterface.cpp.o
.PHONY : DebugInterface.cpp.o

DebugInterface.i: DebugInterface.cpp.i

.PHONY : DebugInterface.i

# target to preprocess a source file
DebugInterface.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/DebugInterface.cpp.i
.PHONY : DebugInterface.cpp.i

DebugInterface.s: DebugInterface.cpp.s

.PHONY : DebugInterface.s

# target to generate assembly for a file
DebugInterface.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/DebugInterface.cpp.s
.PHONY : DebugInterface.cpp.s

MyStrategy.o: MyStrategy.cpp.o

.PHONY : MyStrategy.o

# target to build an object file
MyStrategy.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/MyStrategy.cpp.o
.PHONY : MyStrategy.cpp.o

MyStrategy.i: MyStrategy.cpp.i

.PHONY : MyStrategy.i

# target to preprocess a source file
MyStrategy.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/MyStrategy.cpp.i
.PHONY : MyStrategy.cpp.i

MyStrategy.s: MyStrategy.cpp.s

.PHONY : MyStrategy.s

# target to generate assembly for a file
MyStrategy.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/MyStrategy.cpp.s
.PHONY : MyStrategy.cpp.s

Stream.o: Stream.cpp.o

.PHONY : Stream.o

# target to build an object file
Stream.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/Stream.cpp.o
.PHONY : Stream.cpp.o

Stream.i: Stream.cpp.i

.PHONY : Stream.i

# target to preprocess a source file
Stream.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/Stream.cpp.i
.PHONY : Stream.cpp.i

Stream.s: Stream.cpp.s

.PHONY : Stream.s

# target to generate assembly for a file
Stream.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/Stream.cpp.s
.PHONY : Stream.cpp.s

TcpStream.o: TcpStream.cpp.o

.PHONY : TcpStream.o

# target to build an object file
TcpStream.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/TcpStream.cpp.o
.PHONY : TcpStream.cpp.o

TcpStream.i: TcpStream.cpp.i

.PHONY : TcpStream.i

# target to preprocess a source file
TcpStream.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/TcpStream.cpp.i
.PHONY : TcpStream.cpp.i

TcpStream.s: TcpStream.cpp.s

.PHONY : TcpStream.s

# target to generate assembly for a file
TcpStream.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/TcpStream.cpp.s
.PHONY : TcpStream.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/main.cpp.s
.PHONY : main.cpp.s

model/Action.o: model/Action.cpp.o

.PHONY : model/Action.o

# target to build an object file
model/Action.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Action.cpp.o
.PHONY : model/Action.cpp.o

model/Action.i: model/Action.cpp.i

.PHONY : model/Action.i

# target to preprocess a source file
model/Action.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Action.cpp.i
.PHONY : model/Action.cpp.i

model/Action.s: model/Action.cpp.s

.PHONY : model/Action.s

# target to generate assembly for a file
model/Action.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Action.cpp.s
.PHONY : model/Action.cpp.s

model/AttackAction.o: model/AttackAction.cpp.o

.PHONY : model/AttackAction.o

# target to build an object file
model/AttackAction.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackAction.cpp.o
.PHONY : model/AttackAction.cpp.o

model/AttackAction.i: model/AttackAction.cpp.i

.PHONY : model/AttackAction.i

# target to preprocess a source file
model/AttackAction.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackAction.cpp.i
.PHONY : model/AttackAction.cpp.i

model/AttackAction.s: model/AttackAction.cpp.s

.PHONY : model/AttackAction.s

# target to generate assembly for a file
model/AttackAction.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackAction.cpp.s
.PHONY : model/AttackAction.cpp.s

model/AttackProperties.o: model/AttackProperties.cpp.o

.PHONY : model/AttackProperties.o

# target to build an object file
model/AttackProperties.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackProperties.cpp.o
.PHONY : model/AttackProperties.cpp.o

model/AttackProperties.i: model/AttackProperties.cpp.i

.PHONY : model/AttackProperties.i

# target to preprocess a source file
model/AttackProperties.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackProperties.cpp.i
.PHONY : model/AttackProperties.cpp.i

model/AttackProperties.s: model/AttackProperties.cpp.s

.PHONY : model/AttackProperties.s

# target to generate assembly for a file
model/AttackProperties.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AttackProperties.cpp.s
.PHONY : model/AttackProperties.cpp.s

model/AutoAttack.o: model/AutoAttack.cpp.o

.PHONY : model/AutoAttack.o

# target to build an object file
model/AutoAttack.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AutoAttack.cpp.o
.PHONY : model/AutoAttack.cpp.o

model/AutoAttack.i: model/AutoAttack.cpp.i

.PHONY : model/AutoAttack.i

# target to preprocess a source file
model/AutoAttack.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AutoAttack.cpp.i
.PHONY : model/AutoAttack.cpp.i

model/AutoAttack.s: model/AutoAttack.cpp.s

.PHONY : model/AutoAttack.s

# target to generate assembly for a file
model/AutoAttack.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/AutoAttack.cpp.s
.PHONY : model/AutoAttack.cpp.s

model/BuildAction.o: model/BuildAction.cpp.o

.PHONY : model/BuildAction.o

# target to build an object file
model/BuildAction.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildAction.cpp.o
.PHONY : model/BuildAction.cpp.o

model/BuildAction.i: model/BuildAction.cpp.i

.PHONY : model/BuildAction.i

# target to preprocess a source file
model/BuildAction.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildAction.cpp.i
.PHONY : model/BuildAction.cpp.i

model/BuildAction.s: model/BuildAction.cpp.s

.PHONY : model/BuildAction.s

# target to generate assembly for a file
model/BuildAction.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildAction.cpp.s
.PHONY : model/BuildAction.cpp.s

model/BuildProperties.o: model/BuildProperties.cpp.o

.PHONY : model/BuildProperties.o

# target to build an object file
model/BuildProperties.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildProperties.cpp.o
.PHONY : model/BuildProperties.cpp.o

model/BuildProperties.i: model/BuildProperties.cpp.i

.PHONY : model/BuildProperties.i

# target to preprocess a source file
model/BuildProperties.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildProperties.cpp.i
.PHONY : model/BuildProperties.cpp.i

model/BuildProperties.s: model/BuildProperties.cpp.s

.PHONY : model/BuildProperties.s

# target to generate assembly for a file
model/BuildProperties.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/BuildProperties.cpp.s
.PHONY : model/BuildProperties.cpp.s

model/Camera.o: model/Camera.cpp.o

.PHONY : model/Camera.o

# target to build an object file
model/Camera.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Camera.cpp.o
.PHONY : model/Camera.cpp.o

model/Camera.i: model/Camera.cpp.i

.PHONY : model/Camera.i

# target to preprocess a source file
model/Camera.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Camera.cpp.i
.PHONY : model/Camera.cpp.i

model/Camera.s: model/Camera.cpp.s

.PHONY : model/Camera.s

# target to generate assembly for a file
model/Camera.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Camera.cpp.s
.PHONY : model/Camera.cpp.s

model/ClientMessage.o: model/ClientMessage.cpp.o

.PHONY : model/ClientMessage.o

# target to build an object file
model/ClientMessage.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ClientMessage.cpp.o
.PHONY : model/ClientMessage.cpp.o

model/ClientMessage.i: model/ClientMessage.cpp.i

.PHONY : model/ClientMessage.i

# target to preprocess a source file
model/ClientMessage.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ClientMessage.cpp.i
.PHONY : model/ClientMessage.cpp.i

model/ClientMessage.s: model/ClientMessage.cpp.s

.PHONY : model/ClientMessage.s

# target to generate assembly for a file
model/ClientMessage.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ClientMessage.cpp.s
.PHONY : model/ClientMessage.cpp.s

model/Color.o: model/Color.cpp.o

.PHONY : model/Color.o

# target to build an object file
model/Color.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Color.cpp.o
.PHONY : model/Color.cpp.o

model/Color.i: model/Color.cpp.i

.PHONY : model/Color.i

# target to preprocess a source file
model/Color.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Color.cpp.i
.PHONY : model/Color.cpp.i

model/Color.s: model/Color.cpp.s

.PHONY : model/Color.s

# target to generate assembly for a file
model/Color.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Color.cpp.s
.PHONY : model/Color.cpp.s

model/ColoredVertex.o: model/ColoredVertex.cpp.o

.PHONY : model/ColoredVertex.o

# target to build an object file
model/ColoredVertex.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ColoredVertex.cpp.o
.PHONY : model/ColoredVertex.cpp.o

model/ColoredVertex.i: model/ColoredVertex.cpp.i

.PHONY : model/ColoredVertex.i

# target to preprocess a source file
model/ColoredVertex.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ColoredVertex.cpp.i
.PHONY : model/ColoredVertex.cpp.i

model/ColoredVertex.s: model/ColoredVertex.cpp.s

.PHONY : model/ColoredVertex.s

# target to generate assembly for a file
model/ColoredVertex.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ColoredVertex.cpp.s
.PHONY : model/ColoredVertex.cpp.s

model/DebugCommand.o: model/DebugCommand.cpp.o

.PHONY : model/DebugCommand.o

# target to build an object file
model/DebugCommand.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugCommand.cpp.o
.PHONY : model/DebugCommand.cpp.o

model/DebugCommand.i: model/DebugCommand.cpp.i

.PHONY : model/DebugCommand.i

# target to preprocess a source file
model/DebugCommand.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugCommand.cpp.i
.PHONY : model/DebugCommand.cpp.i

model/DebugCommand.s: model/DebugCommand.cpp.s

.PHONY : model/DebugCommand.s

# target to generate assembly for a file
model/DebugCommand.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugCommand.cpp.s
.PHONY : model/DebugCommand.cpp.s

model/DebugData.o: model/DebugData.cpp.o

.PHONY : model/DebugData.o

# target to build an object file
model/DebugData.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugData.cpp.o
.PHONY : model/DebugData.cpp.o

model/DebugData.i: model/DebugData.cpp.i

.PHONY : model/DebugData.i

# target to preprocess a source file
model/DebugData.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugData.cpp.i
.PHONY : model/DebugData.cpp.i

model/DebugData.s: model/DebugData.cpp.s

.PHONY : model/DebugData.s

# target to generate assembly for a file
model/DebugData.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugData.cpp.s
.PHONY : model/DebugData.cpp.s

model/DebugState.o: model/DebugState.cpp.o

.PHONY : model/DebugState.o

# target to build an object file
model/DebugState.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugState.cpp.o
.PHONY : model/DebugState.cpp.o

model/DebugState.i: model/DebugState.cpp.i

.PHONY : model/DebugState.i

# target to preprocess a source file
model/DebugState.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugState.cpp.i
.PHONY : model/DebugState.cpp.i

model/DebugState.s: model/DebugState.cpp.s

.PHONY : model/DebugState.s

# target to generate assembly for a file
model/DebugState.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/DebugState.cpp.s
.PHONY : model/DebugState.cpp.s

model/Entity.o: model/Entity.cpp.o

.PHONY : model/Entity.o

# target to build an object file
model/Entity.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Entity.cpp.o
.PHONY : model/Entity.cpp.o

model/Entity.i: model/Entity.cpp.i

.PHONY : model/Entity.i

# target to preprocess a source file
model/Entity.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Entity.cpp.i
.PHONY : model/Entity.cpp.i

model/Entity.s: model/Entity.cpp.s

.PHONY : model/Entity.s

# target to generate assembly for a file
model/Entity.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Entity.cpp.s
.PHONY : model/Entity.cpp.s

model/EntityAction.o: model/EntityAction.cpp.o

.PHONY : model/EntityAction.o

# target to build an object file
model/EntityAction.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityAction.cpp.o
.PHONY : model/EntityAction.cpp.o

model/EntityAction.i: model/EntityAction.cpp.i

.PHONY : model/EntityAction.i

# target to preprocess a source file
model/EntityAction.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityAction.cpp.i
.PHONY : model/EntityAction.cpp.i

model/EntityAction.s: model/EntityAction.cpp.s

.PHONY : model/EntityAction.s

# target to generate assembly for a file
model/EntityAction.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityAction.cpp.s
.PHONY : model/EntityAction.cpp.s

model/EntityProperties.o: model/EntityProperties.cpp.o

.PHONY : model/EntityProperties.o

# target to build an object file
model/EntityProperties.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityProperties.cpp.o
.PHONY : model/EntityProperties.cpp.o

model/EntityProperties.i: model/EntityProperties.cpp.i

.PHONY : model/EntityProperties.i

# target to preprocess a source file
model/EntityProperties.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityProperties.cpp.i
.PHONY : model/EntityProperties.cpp.i

model/EntityProperties.s: model/EntityProperties.cpp.s

.PHONY : model/EntityProperties.s

# target to generate assembly for a file
model/EntityProperties.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/EntityProperties.cpp.s
.PHONY : model/EntityProperties.cpp.s

model/MoveAction.o: model/MoveAction.cpp.o

.PHONY : model/MoveAction.o

# target to build an object file
model/MoveAction.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/MoveAction.cpp.o
.PHONY : model/MoveAction.cpp.o

model/MoveAction.i: model/MoveAction.cpp.i

.PHONY : model/MoveAction.i

# target to preprocess a source file
model/MoveAction.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/MoveAction.cpp.i
.PHONY : model/MoveAction.cpp.i

model/MoveAction.s: model/MoveAction.cpp.s

.PHONY : model/MoveAction.s

# target to generate assembly for a file
model/MoveAction.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/MoveAction.cpp.s
.PHONY : model/MoveAction.cpp.s

model/Player.o: model/Player.cpp.o

.PHONY : model/Player.o

# target to build an object file
model/Player.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Player.cpp.o
.PHONY : model/Player.cpp.o

model/Player.i: model/Player.cpp.i

.PHONY : model/Player.i

# target to preprocess a source file
model/Player.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Player.cpp.i
.PHONY : model/Player.cpp.i

model/Player.s: model/Player.cpp.s

.PHONY : model/Player.s

# target to generate assembly for a file
model/Player.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Player.cpp.s
.PHONY : model/Player.cpp.s

model/PlayerView.o: model/PlayerView.cpp.o

.PHONY : model/PlayerView.o

# target to build an object file
model/PlayerView.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/PlayerView.cpp.o
.PHONY : model/PlayerView.cpp.o

model/PlayerView.i: model/PlayerView.cpp.i

.PHONY : model/PlayerView.i

# target to preprocess a source file
model/PlayerView.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/PlayerView.cpp.i
.PHONY : model/PlayerView.cpp.i

model/PlayerView.s: model/PlayerView.cpp.s

.PHONY : model/PlayerView.s

# target to generate assembly for a file
model/PlayerView.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/PlayerView.cpp.s
.PHONY : model/PlayerView.cpp.s

model/RepairAction.o: model/RepairAction.cpp.o

.PHONY : model/RepairAction.o

# target to build an object file
model/RepairAction.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairAction.cpp.o
.PHONY : model/RepairAction.cpp.o

model/RepairAction.i: model/RepairAction.cpp.i

.PHONY : model/RepairAction.i

# target to preprocess a source file
model/RepairAction.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairAction.cpp.i
.PHONY : model/RepairAction.cpp.i

model/RepairAction.s: model/RepairAction.cpp.s

.PHONY : model/RepairAction.s

# target to generate assembly for a file
model/RepairAction.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairAction.cpp.s
.PHONY : model/RepairAction.cpp.s

model/RepairProperties.o: model/RepairProperties.cpp.o

.PHONY : model/RepairProperties.o

# target to build an object file
model/RepairProperties.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairProperties.cpp.o
.PHONY : model/RepairProperties.cpp.o

model/RepairProperties.i: model/RepairProperties.cpp.i

.PHONY : model/RepairProperties.i

# target to preprocess a source file
model/RepairProperties.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairProperties.cpp.i
.PHONY : model/RepairProperties.cpp.i

model/RepairProperties.s: model/RepairProperties.cpp.s

.PHONY : model/RepairProperties.s

# target to generate assembly for a file
model/RepairProperties.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/RepairProperties.cpp.s
.PHONY : model/RepairProperties.cpp.s

model/ServerMessage.o: model/ServerMessage.cpp.o

.PHONY : model/ServerMessage.o

# target to build an object file
model/ServerMessage.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ServerMessage.cpp.o
.PHONY : model/ServerMessage.cpp.o

model/ServerMessage.i: model/ServerMessage.cpp.i

.PHONY : model/ServerMessage.i

# target to preprocess a source file
model/ServerMessage.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ServerMessage.cpp.i
.PHONY : model/ServerMessage.cpp.i

model/ServerMessage.s: model/ServerMessage.cpp.s

.PHONY : model/ServerMessage.s

# target to generate assembly for a file
model/ServerMessage.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/ServerMessage.cpp.s
.PHONY : model/ServerMessage.cpp.s

model/Vec2Float.o: model/Vec2Float.cpp.o

.PHONY : model/Vec2Float.o

# target to build an object file
model/Vec2Float.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Float.cpp.o
.PHONY : model/Vec2Float.cpp.o

model/Vec2Float.i: model/Vec2Float.cpp.i

.PHONY : model/Vec2Float.i

# target to preprocess a source file
model/Vec2Float.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Float.cpp.i
.PHONY : model/Vec2Float.cpp.i

model/Vec2Float.s: model/Vec2Float.cpp.s

.PHONY : model/Vec2Float.s

# target to generate assembly for a file
model/Vec2Float.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Float.cpp.s
.PHONY : model/Vec2Float.cpp.s

model/Vec2Int.o: model/Vec2Int.cpp.o

.PHONY : model/Vec2Int.o

# target to build an object file
model/Vec2Int.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Int.cpp.o
.PHONY : model/Vec2Int.cpp.o

model/Vec2Int.i: model/Vec2Int.cpp.i

.PHONY : model/Vec2Int.i

# target to preprocess a source file
model/Vec2Int.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Int.cpp.i
.PHONY : model/Vec2Int.cpp.i

model/Vec2Int.s: model/Vec2Int.cpp.s

.PHONY : model/Vec2Int.s

# target to generate assembly for a file
model/Vec2Int.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/model/Vec2Int.cpp.s
.PHONY : model/Vec2Int.cpp.s

vw.o: vw.cpp.o

.PHONY : vw.o

# target to build an object file
vw.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw.cpp.o
.PHONY : vw.cpp.o

vw.i: vw.cpp.i

.PHONY : vw.i

# target to preprocess a source file
vw.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw.cpp.i
.PHONY : vw.cpp.i

vw.s: vw.cpp.s

.PHONY : vw.s

# target to generate assembly for a file
vw.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw.cpp.s
.PHONY : vw.cpp.s

vw_callbacks.o: vw_callbacks.cpp.o

.PHONY : vw_callbacks.o

# target to build an object file
vw_callbacks.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_callbacks.cpp.o
.PHONY : vw_callbacks.cpp.o

vw_callbacks.i: vw_callbacks.cpp.i

.PHONY : vw_callbacks.i

# target to preprocess a source file
vw_callbacks.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_callbacks.cpp.i
.PHONY : vw_callbacks.cpp.i

vw_callbacks.s: vw_callbacks.cpp.s

.PHONY : vw_callbacks.s

# target to generate assembly for a file
vw_callbacks.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_callbacks.cpp.s
.PHONY : vw_callbacks.cpp.s

vw_render_loop.o: vw_render_loop.cpp.o

.PHONY : vw_render_loop.o

# target to build an object file
vw_render_loop.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_loop.cpp.o
.PHONY : vw_render_loop.cpp.o

vw_render_loop.i: vw_render_loop.cpp.i

.PHONY : vw_render_loop.i

# target to preprocess a source file
vw_render_loop.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_loop.cpp.i
.PHONY : vw_render_loop.cpp.i

vw_render_loop.s: vw_render_loop.cpp.s

.PHONY : vw_render_loop.s

# target to generate assembly for a file
vw_render_loop.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_loop.cpp.s
.PHONY : vw_render_loop.cpp.s

vw_render_text.o: vw_render_text.cpp.o

.PHONY : vw_render_text.o

# target to build an object file
vw_render_text.cpp.o:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_text.cpp.o
.PHONY : vw_render_text.cpp.o

vw_render_text.i: vw_render_text.cpp.i

.PHONY : vw_render_text.i

# target to preprocess a source file
vw_render_text.cpp.i:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_text.cpp.i
.PHONY : vw_render_text.cpp.i

vw_render_text.s: vw_render_text.cpp.s

.PHONY : vw_render_text.s

# target to generate assembly for a file
vw_render_text.cpp.s:
	$(MAKE) -f CMakeFiles/aicup2020.dir/build.make CMakeFiles/aicup2020.dir/vw_render_text.cpp.s
.PHONY : vw_render_text.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... aicup2020"
	@echo "... DebugInterface.o"
	@echo "... DebugInterface.i"
	@echo "... DebugInterface.s"
	@echo "... MyStrategy.o"
	@echo "... MyStrategy.i"
	@echo "... MyStrategy.s"
	@echo "... Stream.o"
	@echo "... Stream.i"
	@echo "... Stream.s"
	@echo "... TcpStream.o"
	@echo "... TcpStream.i"
	@echo "... TcpStream.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... model/Action.o"
	@echo "... model/Action.i"
	@echo "... model/Action.s"
	@echo "... model/AttackAction.o"
	@echo "... model/AttackAction.i"
	@echo "... model/AttackAction.s"
	@echo "... model/AttackProperties.o"
	@echo "... model/AttackProperties.i"
	@echo "... model/AttackProperties.s"
	@echo "... model/AutoAttack.o"
	@echo "... model/AutoAttack.i"
	@echo "... model/AutoAttack.s"
	@echo "... model/BuildAction.o"
	@echo "... model/BuildAction.i"
	@echo "... model/BuildAction.s"
	@echo "... model/BuildProperties.o"
	@echo "... model/BuildProperties.i"
	@echo "... model/BuildProperties.s"
	@echo "... model/Camera.o"
	@echo "... model/Camera.i"
	@echo "... model/Camera.s"
	@echo "... model/ClientMessage.o"
	@echo "... model/ClientMessage.i"
	@echo "... model/ClientMessage.s"
	@echo "... model/Color.o"
	@echo "... model/Color.i"
	@echo "... model/Color.s"
	@echo "... model/ColoredVertex.o"
	@echo "... model/ColoredVertex.i"
	@echo "... model/ColoredVertex.s"
	@echo "... model/DebugCommand.o"
	@echo "... model/DebugCommand.i"
	@echo "... model/DebugCommand.s"
	@echo "... model/DebugData.o"
	@echo "... model/DebugData.i"
	@echo "... model/DebugData.s"
	@echo "... model/DebugState.o"
	@echo "... model/DebugState.i"
	@echo "... model/DebugState.s"
	@echo "... model/Entity.o"
	@echo "... model/Entity.i"
	@echo "... model/Entity.s"
	@echo "... model/EntityAction.o"
	@echo "... model/EntityAction.i"
	@echo "... model/EntityAction.s"
	@echo "... model/EntityProperties.o"
	@echo "... model/EntityProperties.i"
	@echo "... model/EntityProperties.s"
	@echo "... model/MoveAction.o"
	@echo "... model/MoveAction.i"
	@echo "... model/MoveAction.s"
	@echo "... model/Player.o"
	@echo "... model/Player.i"
	@echo "... model/Player.s"
	@echo "... model/PlayerView.o"
	@echo "... model/PlayerView.i"
	@echo "... model/PlayerView.s"
	@echo "... model/RepairAction.o"
	@echo "... model/RepairAction.i"
	@echo "... model/RepairAction.s"
	@echo "... model/RepairProperties.o"
	@echo "... model/RepairProperties.i"
	@echo "... model/RepairProperties.s"
	@echo "... model/ServerMessage.o"
	@echo "... model/ServerMessage.i"
	@echo "... model/ServerMessage.s"
	@echo "... model/Vec2Float.o"
	@echo "... model/Vec2Float.i"
	@echo "... model/Vec2Float.s"
	@echo "... model/Vec2Int.o"
	@echo "... model/Vec2Int.i"
	@echo "... model/Vec2Int.s"
	@echo "... vw.o"
	@echo "... vw.i"
	@echo "... vw.s"
	@echo "... vw_callbacks.o"
	@echo "... vw_callbacks.i"
	@echo "... vw_callbacks.s"
	@echo "... vw_render_loop.o"
	@echo "... vw_render_loop.i"
	@echo "... vw_render_loop.s"
	@echo "... vw_render_text.o"
	@echo "... vw_render_text.i"
	@echo "... vw_render_text.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

