#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <iostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango en operator[]");
        }
        Node<T>* curr = first;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        out << "ListLinked [";
        Node<T>* curr = list.first;
        while (curr != nullptr) {
            out << curr->data;
            if (curr->next != nullptr) {
                out << ", ";
            }
            curr = curr->next;
        }
        out << "]";
        return out;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posición inválida en insert()");
        }

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición inválida en remove()");
        }

        Node<T>* toDelete = nullptr;
        T data;

        if (pos == 0) {
            toDelete = first;
            data = toDelete->data;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            toDelete = prev->next;
            data = toDelete->data;
            prev->next = toDelete->next;
        }

        delete toDelete;
        n--;
        return data;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición inválida en get()");
        }
        Node<T>* curr = first;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    int search(T e) override {
        Node<T>* curr = first;
        int index = 0;
        while (curr != nullptr) {
            if (curr->data == e) {
                return index;
            }
            curr = curr->next;
            index++;
        }
        return -1;
    }

    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};

#endif
