#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>
#include <linux/input.h>
#include <limits>

#include "event.hpp"
#include "read_write.hpp"

using namespace std;

int main(int argc, char const *argv[]){
	Gamepad_list gamepad;
	if(argc > 1){
		cout << argv[1] << endl;
		gamepad = get_gamepad_by_path(argv[1]);
	} else {
		vgamepad_list list = get_gamepads();
		if(list.empty()){
			cerr << "Il n'y a aucune manette branchée" << endl;
			return 0;
		}
		bool boucle = true;
		do{
			cout << "Choisissez une manette : " << endl;
			for(int i = 0; i < list.size(); i++){
				cout << i +1 << " : " << list[i].name << endl;
			}
			int gamepad_number;
			cout << "> ";
			cin >> gamepad_number;
			if(!cin.good()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			};
			if(gamepad_number > list.size() || gamepad_number == 0){
				continue;
			}
			gamepad = list[gamepad_number - 1];
			cout << gamepad.path << endl;
			boucle = false;
		} while(boucle);
	}
	if(gamepad.path == "")exit(1);
	read_gamepad(gamepad.path);
	
}