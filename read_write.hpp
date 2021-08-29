#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <iostream>
#include <vector>

/**
 * Informations sur la manette
 */
typedef struct Gamepad{
	/**
	 * Chemin de la manette
	 */
	std::string path;

	/**
	 * Nom de la manette
	 */
	std::string name;
} Gamepad;

/**
 * Vecteur de Gamepad
 */
typedef std::vector<Gamepad> vgamepad_list;

typedef js_event Event;

/**
 * Lit les entrées de la manette en /dev/input/js0
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
void write_file(std::string path);

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

#endif