#include <iostream>
#include <iomanip>

using namespace std;

struct author
{
	char name[32];
	char surname[56];
};

struct book
{
	char title[56];
	int release_year;
	char publish[56];
	int cost_price; //себестоимость;
	int price;
	int clear_profit; //чистая прибыль;
	author name;
	int count;
};

//функция для выделения памяти если пользователь захочет продолжить ввод;
void memory(book*& arr, int& size)
{
	book* new_array = new book[size + 1];

	for (int i = 0; i < size; i++)
	{
		new_array[i] = arr[i];
	}

	size++;

	delete[] arr;

	arr = new_array;
}

//функция сортировки массива;
void sort(book* arr, int size)
{
	cout << endl;

	int k;

	cout << "Хотите отсортирвать массив? Возможна сортировка по финальной стоимости книги (Введите 1 если да, другое число если нет): ";
	cin >> k;
	cout << endl;

	if (k == 1)
	{
		for (int i = 0; i < size; i++)
		{
			for (int i = 0; i < size - 1; i++)
			{
				if (arr[i].price > arr[i + 1].price)
				{
					book temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}
		}

		cout << "Сортировка прошла успешно!" << endl;
	}

	else
	{
		cout << "Вы решили не сортировать" << endl;
	}

	cout << endl;
}

//функция поиска по названию;
void search(book* arr, int size)
{
	cout << endl;

	string title;
	int count = 0;
	int s, t;

	cout << "Хотите найти нужную вам книгу? Возможен поиск по названию(Нажмите 1 если да, другое число если нет): ";
	cin >> s;
	cout << endl;

	if (s == 1)
	{
		cout << "Введите название: ";
		cin >> title;
		cout << endl;

		for (int i = 0; i < size; i++)
		{
			if (title == arr[i].title)
			{
				cout << "Название: " << arr[i].title << ", Год выпуска: " << arr[i].release_year << ", Публикация: " << arr[i].publish << "\n";
				cout << "Автор: " << arr[i].name.name << " " << arr[i].name.surname << "\n";
				cout << "Себестоимость: " << arr[i].cost_price << ", Цена: " << arr[i].price << ", Чистая прибыль: " << arr[i].clear_profit << endl;
				count++;
			}
		}

		if (count == 0)
		{
			cout << "Книги с таким названием не найдено" << endl;
		}

		cout << endl;
		cout << "Продолжить поиск? Да - 1, Нет - другое число: ";
		cin >> t;
		cout << endl;

		if (t == 1)
		{
			count = 0;
			search(arr, size);
		}

		else
		{
			count = 0;
		}
	}

}

//функция вывода массива на экран
void conclusion(book* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Название: " << arr[i].title << ", Год выпуска: " << arr[i].release_year << ", Публикация: " << arr[i].publish << "\n";
		cout << "Автор: " << arr[i].name.name << " " << arr[i].name.surname << "\n";
		cout << "Себестоимость: " << arr[i].cost_price << ", Цена: " << arr[i].price << ", Чистая прибыль: " << arr[i].clear_profit << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "RU");

	book* arr;
	int size;

	//количество книг не может быть меньше 1;
	do
	{
		cout << "Введите количество книг, данные которых вы будете вводить: ";
		cin >> size;
	} while (size < 1);

	arr = new book[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Введите наименование книги под номером " << i + 1 << ": ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].title, 56);
		cout << endl;

		cout << "Введите имя автора: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].name.name, 32);
		cout << endl;

		cout << "Введите фамилию автора: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].name.surname, 56);
		cout << endl;

		cout << "Год выпуска: ";
		cin >> arr[i].release_year;
		cout << endl;

		cout << "Введите наименование публикации: ";
		cin.ignore(cin.rdbuf()->in_avail());
		cin.getline(arr[i].publish, 56);
		cout << endl;

		cout << "Себестоимость: ";
		cin >> arr[i].cost_price;
		cout << endl;

		//финальная стоимость не может быть меньше либо равна себестоимости;
		do
		{
			cout << "Финальная стоимость: ";
			cin >> arr[i].price;
			cout << endl;
		} while (arr[i].price <= arr[i].cost_price);

		//чистая прибыль равна разнице между финальной стоимостью и себестоимостью;
		arr[i].clear_profit = arr[i].price - arr[i].cost_price;

		//спрашиваем пользователя хочет ли он продолжить ввод и если тот продолжает - вызываем соотвествующую функцию;
		if (i == size - 1)
		{
			arr[i].count = 0;

			cout << "Хотите добавить новую книгу?(Если Да - введите 1, Нет - любое другое число): ";
			cin >> arr[i].count;
			cout << endl;

			if (arr[i].count == 1)
			{
				//если пользователь продолжает ввод то вызываем функцию для выделения памяти под товар;
				memory(arr, size);
			}
		}
	}

	if (size > 1)
	{
		sort(arr, size);

		search(arr, size);
	}

	cout << endl;
	cout << "Вывод информации о книгах: " << endl;

	conclusion(arr, size);
}