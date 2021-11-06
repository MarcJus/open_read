#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <iostream>
#include <vector>

/**
 * Informations sur la manette
 */
struct Gamepad{
	/**
	 * Chemin de la manette
	 */
	std::string path;

	/**
	 * Nom de la manette
	 */
	std::string name;
};

struct Test{
	int nombre;
	
	unsigned char character;
};

/**
 * Vecteur de Gamepad
 */
typedef std::vector<Gamepad> vgamepad_list;

/**
 * Evenement de joystick
 * @see js_event
 */
typedef js_event Event;

/**
 * @brief Par defaut, on lit la manette en /dev/input/js0:
 */
void read_gamepad();

/**
 * Lit les entrées de la manette donnée en paramètre
 * @param path Chemin de la manette
 */ 
void read_gamepad(std::string path);

/**
 * @deprecated
 */ 
void write_file();

/**
 * Lit les entrées du clavier
 */ 
void read_keyboard();

/**
 * Récupère les informations d'une manette
 * @param path Chemin de la manette
 * @return Instance de Gamepad, vide si la manette n'a pas été trouvée
 */ 
Gamepad get_gamepad_by_path(std::string path);

/**
 * Récupère la liste des manettes
 * @return Vecteur de Gamepad 
 */
vgamepad_list get_gamepads();

bool read_toread(Test *test);

#endif