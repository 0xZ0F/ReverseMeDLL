#include <iostream>
#include <string>

class Player {
public:
	int score;
	float health;
	std::string name;
};

extern "C" void __declspec(dllexport) SayHello() {
	std::cout << "Hello!" << std::endl;
}

void __declspec(dllexport) PrintArray(int x[]) {
	for (int i = 0; i <= sizeof(x); i++) {
		std::cout << x[i] << std::endl;
	}
}
void __declspec(dllexport) PrintArray(char x[]) {
	for (int i = 0; i <= sizeof(x); i++) {
		std::cout << x[i] << std::endl;
	}
}

void __declspec(dllexport) InitializeClass(Player* player) {
	player->score = 32;
	player->health = 100.0f;
	player->name = "PLACEHOLDER";
}

extern "C" void __declspec(dllexport) PrintPlayerStats(Player player) {
	printf("PRINTING PLAYER STATS\n");
	printf("Score: %d\n", player.score);
	printf("Health: %f\n", player.health);
	printf("Name: %s\n", player.name.c_str());
}
//Set array to be addrs of elements in Player class. Ret the base addr:
extern "C" __declspec(dllexport) void* MysteryFunc1(Player* player, int* arr[]) {
	arr[0] = (int*)player;
	arr[1] = (int*)& player->score;
	arr[2] = (int*)& player->health;
	arr[3] = (int*)& player->name;
	return player;
}

/*

extern "C" does not add randomness to func name that allows func overriding. This also hides prototype.

*/

//extern "C" class __declspec(dllexport) Player {
//private:
//	std::string p_name;
//	float p_health;
//public:
//	Player(std::string name, float health = 100) {
//		SetName(name);
//		p_health = health;
//	}
//	void SetName(std::string name) {
//		if (name.length() < 100) {
//			p_name = name;
//		}
//	}
//	void ModifyHealth(float amount) {
//		p_health += amount;
//	}
//	float GetHealth() {
//		return p_health;
//	}
//	std::string GetName() {
//		return p_name;
//	}
//};
//extern "C" Player __declspec(dllexport) __cdecl MakePlayer(std::string name, float health = 100) {
//	return Player(name, health);
//}