#include <iostream>
#include <Windows.h>

class Player {
public:
	int score;
	float health;
	std::string name;
};

//extern "C" void __declspec(dllexport) __cdecl SayHello()
typedef void(WINAPI* ESayHello)(void);
//void __declspec(dllexport) __cdecl PrintArray(int x[])
typedef void(WINAPI* EPrintArray_Int)(int[]);
typedef void(WINAPI* EPrintArray_Char)(char[]);
//void __declspec(dllexport) InitializeClass(Player* player)
typedef void(WINAPI* EInitializeClass)(Player*);
//extern "C" void __declspec(dllexport) PrintPlayerStats(Player* player)
typedef void(WINAPI* EPrintPlayerStats)(Player);
//extern "C" void __declspec(dllexport) MysteryFunc1(Player* player)
typedef void*(WINAPI* EMysteryFunc1)(Player*, int*[]);

int main()
{
	Player player;

	// Load lib and validate:
	HMODULE dll = LoadLibraryA("DLL.DLL");
	if (dll != NULL) {
		// SayHello:
		ESayHello SayHello = (ESayHello)GetProcAddress(dll, "SayHello");
		if (SayHello != NULL) {
			SayHello();
		}
		else { std::cout << "Can't load function." << std::endl; }

		// PrintArray:
		/*EPrintArray_Char PrintArray = (EPrintArray_Char)GetProcAddress(dll, "?PrintArray@@YAXQEAD@Z");
		if (PrintArray != NULL) {
			char myArray[10] = { 'A','B','C' };
			PrintArray(myArray);
		}
		else { std::cout << "Can't load function." << std::endl; }*/

		// SetupPlayer:
		EInitializeClass InitializeClass = (EInitializeClass)GetProcAddress(dll, "?InitializeClass@@YAXPEAVPlayer@@@Z");
		if (InitializeClass != NULL) {
			InitializeClass(&player);
		}
		else { std::cout << "Can't load function." << std::endl; }

		// PrintPlayerStats:
		EPrintPlayerStats PrintPlayerStats = (EPrintPlayerStats)GetProcAddress(dll, "PrintPlayerStats");
		if (PrintPlayerStats != NULL) {
			PrintPlayerStats(player);
		}
		else { std::cout << "Can't load function." << std::endl; }

		//MysteryFunc1
		EMysteryFunc1 MysteryFunc1 = (EMysteryFunc1)GetProcAddress(dll, "MysteryFunc1");
		if (PrintPlayerStats != NULL) {
			int* arr[4];
			void* ret = MysteryFunc1(&player, arr);
			std::cout << "Info:" << std::endl;
			std::cout << arr[0] << std::endl;
			std::cout << arr[1] << std::endl;
			std::cout << arr[2] << std::endl;
			std::cout << arr[3] << std::endl;
			std::cout << ret << std::endl;
		}
		else { std::cout << "Can't load function." << std::endl; }
	}
	else { std::cout << "Can't load DLL." << std::endl; }
	return 0;
}
//0x000000E1E00FFC28
//0x000000E1E00FFC2C