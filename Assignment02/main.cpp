#include "Header.h"

int main()
{
	do
	{
		system("cls");

		cout << "1. View All Product.\n";
		cout << "2. Ganerate new product.\n";
		cout << "0. Quit.\n";
		cout << "Enter your choose: ";

		int choose = 0;
		cin >> choose;
		cin.ignore();

		system("cls");

		switch (choose)
		{
		case 1:
		{
			displayAllProducts();
			system("pause");
			break;
		}
		case 2:
		{
			GenerateNProducts();
			break;
		}
		case 0:
		{
			cout << "Program is exiting. Press enter key to quit";
			return 0;
		}
		}

	} while (true);
}