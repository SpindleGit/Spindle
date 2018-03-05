#pragma once
#include <vector>
#include "Element.h"

// Структура самой доски
class desk {
	// Перечень элементов
	std::vector<element*> elements;
	// Адрес входного элемента (Begin)
	element* start;
	// Адрес последнего элемента. По умолчанию элемент, добавленный на доску, крепится с ним связью. Последний элемент всегда есть.
	element* last;
public:
	// Инициализирует доску. Добавляет входной begin.
	desk() :elements() {
		elements.push_back(new beg());
		start = elements[0];
		last = start;
	}
	// Добавление элемента на доску. Скрепляет элемент с последним.
	void add(element* elem) {
		elem->link_prev(last);
		last->link_next(elem);
		if (elements.size() == 1)
			start->link_next(elem);
		elements.push_back(elem);
		last = elem;

	}
	// Удаляет элемент по id. id должны начинаться с 1. Связи перекидывает с сохранением следования
	void remove(size_t id) {
		element* next = elements[id]->next();
		element* prev = elements[id]->prev();
		if (next)
			next->link_prev(prev);
		if (prev)
			prev->link_next(next);
		if (last == elements[id])
			last = prev;
		delete elements[id];
		elements[id] = nullptr;
	}
	// Разрывает связь элементов по id. id_prev - откуда выходит стрелка, id_next - куда заходит.
	void del_link(size_t id_prev, size_t id_next) {
		elements[id_prev]->link_next(nullptr);
		elements[id_next]->link_prev(nullptr);
		if (elements[id_next] == last)
			last = elements[id_prev];
	}
	// Соединяет элементы по id. id_prev - откуда выходит стрелка, id_next - куда заходит.
	void link(size_t id_prev, size_t id_next) {
		elements[id_prev]->link_next(elements[id_next]);
		elements[id_next]->link_prev(elements[id_prev]);
		if (elements[id_prev] == last)
			last = elements[id_prev];
	}
	// Разрывает все связи элемента по id. Сам элемент остается.
	void brk(size_t id) {
		if (last == elements[id])
			last = elements[id]->prev();
		element* prev = elements[id]->prev();
		element* next = elements[id]->next();
		if (next)
			next->link_prev(nullptr);
		if (prev)
			prev->link_next(nullptr);
		elements[id]->link_next(nullptr);
		elements[id]->link_prev(nullptr);
	}
	// Изменяет элемент по id. Принимает строчку с данными.
	bool change(size_t id, std::string d) {
		return elements[id]->change(d);
	}
	// Линкует цикл с первым ВНУТРЕННИМ элементом. Далее внутри элемента можно использовать обычный Link, в том числе и для завершения цикла на себе.
	void link_with_circle(size_t id_circle, size_t id_next) {
		elements[id_circle]->link_out(elements[id_next]);
		elements[id_next]->link_prev(elements[id_circle]);
		
	}
	// Генерирует код на основе доски.
	std::string generate() {
		std::string res = "";
		element* cur = start;
		while (cur) {
			res += cur->generate(2);
			cur = cur->next();
		}
		res += "End;\n";
		return res;
	}
};