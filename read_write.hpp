#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <iostream>
#include <vector>

typedef struct {
	std::string path;
	std::string name;
} Gamepad_list;

typedef std::vector<Gamepad_list> vgamepad_list;

void read_gamepad();
void read_gamepad(std::string path);
void write_file(std::string path);
void read_keyboard();
Gamepad_list get_gamepad_by_path(std::string path);
vgamepad_list get_gamepads();
void signalHandler(int signal);

#endif