#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
using namespace std;

struct Node{
	double data;
	Node* prev;
	Node* next;
};

Node* create_void(){
	return nullptr;
}

Node* push_back(Node* head, double val){
	Node* element = new Node{val, nullptr, nullptr};
	if (!head) return element;
	Node* p = head;
	while(p->next) p=p->next;
	p->next = element;
	element->prev = p;
	return head;
}

Node* create_list(int n){
	Node* head = create_void();
	for(int i=0;i<n;i++){
		double v = rand()%101;
		head = push_back(head, v);
	}
	return head;
}

void print_list(Node* head){
	if (!head){
		cout<<"List is empty"<<endl;
		return;
	}

	Node* tail = head;
	while (tail->next){
		tail = tail->next;
	}

	cout<<"От головы к хвосту: ";
	Node* p = head;
	while (p){
		cout<<p->data;
		if (p->next){
			cout<<" => ";
		}
		p = p->next;
	}
	cout<<endl;

	cout<<"От хвоста к голове: ";
	p = tail;
	while (p){
		cout<<p->data;
		if (p->prev){
			cout<<" => ";
		}
		p = p->prev;
	}
	cout<<endl;
}

Node* insert(Node* head, int pos, double val){
	if (pos<1) {
		cout<<"Неправильная позиция."<<endl;
		return head;
	}
	Node* element = new Node{val, nullptr, nullptr};
	if (!head){
		if (pos==1) {
			return element;
		}
		else {
			cout<<"Позиция вне диапазона для пустого списка."<<endl;
			delete element;
			return head;
		}
	}
	if (pos==1){
		element->next = head;
		head->prev = element;
		return element;
	}
	Node* p=head;
	int i=1;
	while(p->next && i<pos-1){
		p=p->next;
		i++;
	}
	if (i<pos-1){
		cout<<"Позиция вне диапазона."<<endl;
		delete element;
		return head;
	}
	element->next = p->next;
	element->prev = p;
	if (p->next) p->next->prev = element;
	p->next = element;
	return head;
}

Node* delete_pos(Node* head, int pos){
	if (!head){
		cout<<"Список пуст."<<endl;
		return head;
	}1
	if (pos<1){
		cout<<"Неправильная позиция."<<endl;
		return head;
	}
	Node* p=head;
	int i=1;
	while(p && i<pos){
		p=p->next;
		i++;
	}
	if (!p){
		cout<<"Позиция вне диапазона."<<endl;
		return head;
	}
	if (p->prev) {
		p->prev->next = p->next;
	}
	else {
		head = p->next;
	}
	if (p->next) {
		p->next->prev = p->prev;
	}
	delete p;
	return head;
}

Node* delete_list(Node* head){
	Node* p=head;
	while(p){
		Node* t=p->next;
		delete p;
		p=t;
	}
	return nullptr;
}

Node* compute_unit_vector(Node* head){
	if (!head){
		cout<<"Исходный список пуст."<<endl;
		return nullptr;
	}
	double sumsq=0.0;
	Node* p=head;
	while(p){
		sumsq += p->data * p->data;
		p=p->next;
	}
	double mag = sqrt(sumsq);
	if (mag==0.0){
		cout<<"Невозможно вычислить единичный вектор."<<endl;
		return nullptr;
	}
	Node* res = create_void();
	p=head;
	while(p){
		res = push_back(res, p->data / mag);
		p=p->next;
	}
	return res;
}

void clear_input(){
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(){
	Node* head = create_void();
	Node* unit = create_void();
	int choice = -1;
	do{
		cout<<"--- Меню ---"<<endl;
		cout<<"1. Создать список (n >= 2)"<<endl;
		cout<<"2. Вывести список"<<endl;
		cout<<"3. Вставить элемент в позицию"<<endl;
		cout<<"4. Удалить элемент по позиции"<<endl;
		cout<<"5. Удалить весь список"<<endl;
		cout<<"6. Вычислить единичный вектор (записать в новый список)"<<endl;
		cout<<"7. Вывести единичный вектор"<<endl;
		cout<<"0. Выход"<<endl;
		cout<<"Выберите пункт: ";
		if (!(cin>>choice)){
			cout<<"Ошибка ввода. Повторите попытку."<<endl;
			clear_input();
            choice=-1;
			continue;
		}
		if (choice==1){
			int n;
			cout<<"Введите n (>=2): ";
			if (!(cin>>n)){
				cout<<"Ошибка ввода. Повторите попытку."<<endl;
				clear_input();
                choice=-1;
				continue;
			}
			if (n<2){
				cout<<"n должно быть >=2."<<endl;
				continue;
			}
			head = delete_list(head);
			unit = delete_list(unit);
			head = create_list(n);
			cout<<"Список создан."<<endl;
		} else if (choice==2){
			cout<<"Содержимое списка:"<<endl;
			print_list(head);
		} else if (choice==3){
			int pos;
			double val;
			cout<<"Позиция для вставки (1..): ";
			if (!(cin>>pos)){
				cout<<"Ошибка ввода. Повторите попытку."<<endl;
				clear_input();
                choice=-1;
				continue;
			}
			cout<<"Значение (число): ";
			if (!(cin>>val)){
				cout<<"Ошибка ввода. Повторите попытку."<<endl;
				clear_input();
                choice=-1;
				continue;
			}
			head = insert(head, pos, val);
		} else if (choice==4){
			int pos;
			cout<<"Позиция для удаления: ";
			if (!(cin>>pos)){
				cout<<"Ошибка ввода. Повторите попытку."<<endl;
				clear_input();
                choice=-1;
				continue;
			}
			head = delete_pos(head, pos);
		} else if (choice==5){
			head = delete_list(head);
			unit = delete_list(unit);
			cout<<"Оба списка удалены."<<endl;
		} else if (choice==6){
			unit = delete_list(unit);
			unit = compute_unit_vector(head);
			if (unit) cout<<"Единичный вектор вычислен и записан."<<endl;
		} else if (choice==7){
			cout<<"Единичный вектор:"<<endl;
			print_list(unit);
		}
	} while(choice!=0);
	head = delete_list(head);
	unit = delete_list(unit);
	cout<<"Завершение."<<endl;
}