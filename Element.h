#pragma once
#include <string>
/*
TODO:
Сделать классы для циклов for и do-while(возможны две реализации). Класс для if. Подумать над системой линковки в циклах и условных операторах.
*/

// Базовый класс для всех элементов доски
class element {
	// Адрес предыдущего элемент
	element* _next;
	// Адрес следующего элемент
	element* _prev;
public:
	// Получение следующего элемента
	virtual element * next() {
		return _next;
	}
	// Получение предыдущего элемента
	virtual element* prev() {
		return _prev;
	}
	// Устанвока связи с последующим элементом
	virtual void link_next(element* n) {
		_next = n;
	}
	// Линковка только для цикла
	virtual void link_out(element* n) {
	}
	// Установка связи с предыдущим элементом
	virtual void link_prev(element* p) {
		_prev = p;
	}
	// Прообраз функции-генератора. Возвращает строчку кода, соответствующую команде.
	virtual std::string generate(size_t n) = 0;
	// Изменяет внутреннее состояние объекта. Возмоно отслеживание успешности изменений
	virtual bool change(std::string d) = 0;
};

// Класс переменных. Только объявляет ее.
class var : public element {
	std::string name;	
	std::string type;
public:
	bool change(std::string d) override {
		size_t sep = d.find("|");
		type = d.substr(0, sep);
		name = d.substr(sep+1);
		return true;
	}
	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n; ++i)
			space += " ";
		return space + "var " + name + " : " + type + ";\n";
	}
};

// Класс-заглушка. Первый элемент.
class beg : public element {
public:
	bool change(std::string d) override {
		return true;
	}

	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n - 2; ++i)
			space += " ";
		return space + "Begin\n";
	}
};

// Класс операции присваивания. Инициализирует переменную. Возможно любое присваивание.
class assig : public element {
	std::string name;
	std::string data;
public:
	bool change(std::string d) override {
		size_t sep = d.find("||");
		name = d.substr(0, sep);
		data = d.substr(sep + 2);
		return true;
	}

	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n; ++i)
			space += " ";
		return space + name + " := " + data + ";\n";
	}
};
// Вывод в консоль. Для текста требует кавычки. Переменные выводит по названию.
class output : public element {
	std::string data;
public:
	bool change(std::string d) override {
		data = d;
		return true;
	}

	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n; ++i)
			space += " ";
		return space + "writeln(" + data + ");\n";
	}
};

// Класс ввода значений в переменную. Принимает имя переменной
class input : public element {
	std::string name;
public:
	bool change(std::string d) override {
		name = d;
		return true;
	}

	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n; ++i)
			space += " ";
		return space + "readln(" + name + ");\n";
	}
};
// Класс цикла while. Имеет свою линковку внутри цикла
class circle_while : public element {
	std::string stmnt;
	element* out;
public:
	circle_while() : stmnt(""), out(this){}
	void link_out(element* n) override {
		out = n;
	}
	bool change(std::string d) override {
		stmnt = d;
		return true;
	}

	std::string generate(size_t n) override {
		std::string space = "";
		for (int i = 0; i < n; ++i)
			space += " ";
		std::string res = space + "while " + stmnt + " do\n" + space + "Begin\n" ;
		element* cur = out;
		while (cur != this) {
			res += cur->generate(n+2);
			cur = cur->next();
		}
		res += space + "End;\n";
		return res;
	}

};