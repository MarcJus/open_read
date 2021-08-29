#include <iostream>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <linux/input.h>
#include <sys/stat.h>

#include "event.hpp"
#include "read_write.hpp"

using namespace std;

void read_gamepad(string path){
	int fd = open(path.c_str(), O_RDONLY);
	if(fd < 0){
		cerr << "Erreur fd" << endl;
		exit(1);
	}
	char name[1024];
	int version;
	ioctl(fd, JSIOCGNAME(sizeof(name)), name);
	ioctl(fd, JSIOCGVERSION, &version);
	cout << "Nom de la manette : " << name << endl;
	while(true){
		Event event;
		int size = read(fd, &event, sizeof(event));
		
		if(size < 0){
			cerr << "Erreur read" << endl;
			exit(1);
		}
		cout << "Manette " << name << endl;
		cout << "value : " << (event.type == 1 ? event.value == 1 ? "Appuyé" : "Levé" : to_string(event.value)) << endl;
		if(event.type == 2){
			cout << "angle : " << event.value * 90 / 32767 << "°" << endl;
		}
		cout << "type : " << ((int) event.type == 1 ? "Bouton" : "Joystick") << endl;
		cout << "number : " << (int) event.number << endl;
		cout << endl;
	}
	close(fd);
}

void read_gamepad(){
	read_gamepad("/dev/input/js0");
}

void write_file(string path){
	int fd = open("write", O_RDWR);
	if(fd < 0){
		cerr << "Erreur fd" << endl;
		exit(1);
	}
	Event event = {
		0x00000001,
		1,
		1,
		4
	};
	int size_write = write(fd, &event, sizeof(event));
	if(size_write < 0){
		cerr << "Erreur read" << endl;
		exit(1);
	}
	cout << "Octets ecrits : " << size_write << endl;

	Event autre;
	read(fd, &autre, sizeof(autre));
	cout << autre.time << endl;
	
	close(fd);
}

vgamepad_list get_gamepads(){
	vgamepad_list list;
	for(int i = 0; i < 32; i++){
		std::ostringstream path;
      	path << "/dev/input/js" << i;
		// cout << path.str() << endl;

		struct stat buffer;
		if(stat(path.str().c_str(), &buffer) != 0) break;

		int fd = open(path.str().c_str(), O_RDONLY);
		char name[1024];
		ioctl(fd, JSIOCGNAME(sizeof(name)), name);
		Gamepad_list gamepad = {
			path.str(), string(name)
		};
		list.push_back(gamepad);
	}
	return list;
}

Gamepad_list get_gamepad_by_path(string path){
	
	struct stat buffer;
	if(stat(path.c_str(), &buffer) == 0){
		int fd = open(path.c_str(), O_RDONLY);
		if(fd < 0) return {"", ""};
		char name[1024];
		ioctl(fd, JSIOCGNAME(sizeof(1024)), name);
		Gamepad_list gamepad = {path, string(name)};
		close(fd);
		return gamepad;
	}
	return {
		"", ""
	};
}

void read_keyboard(){
	int fd = open("/dev/input/event2", O_RDONLY);
	if(fd < 0){
		cerr << "Erreur fd" << endl;
		exit(1);
	}
	char name[1024];
	ioctl(fd, EVIOCGNAME(sizeof(name)), name);
	cout << "Clavier : " << name << endl;
	while(true){
		struct input_event event;
		int size = read(fd, &event, sizeof(event));
		cout << "type : " << event.type << endl
			<< "code : " << event.code << endl
			<< "value : " << event.value << endl << endl;

		switch(event.code){
			case KEY_ESC:
				cout << "Au revoir" << endl;
				exit(0);
				break;
		}
	}
}