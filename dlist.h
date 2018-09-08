#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"
#include <stdexcept>

template <typename T>
class DListIterator : public Iterator<T> {     
    public: 
        DListIterator() : Iterator<T>() {};
        DListIterator(Node<T> *current) : Iterator<T>(current) {};
        DListIterator<T> operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        DListIterator<T> operator--()
        {
            this->current = this->current->prev;
            return *this;
        }
};

template <typename Tr>
class DList {     
    public:
        typedef typename Tr::T T;
        typedef DListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Node<T>* tail;
              
    public:
        DList() {
            head = tail = nullptr;
        };

        void push_front(T data) 
        {
            if (head == NULL)
            {
                head = new Node<T>(data);
                tail = head;
                return;
            }

            Node<T> *temp = new Node<T>(data);
            temp->next = head;
            head->prev = temp;
            head = temp;
            return;
        }

        void push_back(T data) 
        {
            if (head == NULL)
            {
                head = new Node<T>(data);
                tail = head;
                return;
            }

            Node<T> *temp = new Node<T>(data);
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
            return;
        }
             
        void pop_front() 
        {
            if (head == NULL)
            {
                throw std::out_of_range("Empty List!");
                return;
            }

            if(head == tail) {tail = NULL;}

            Node<T> *temp = head;
            head = head->next;
            
            if(head!=NULL) {head->prev = NULL;}
            delete temp;
            return;
        }
             
        void pop_back() 
        {
            if(head == NULL)
            {
                throw std::out_of_range("Empty List!");
                return;
            }

            if(head == tail) {head = NULL;}

            Node<T> *temp = tail;
            tail = tail->prev;

            if(tail!=NULL) {tail->next = NULL;}
            delete temp;
            return;
        }
             
        iterator begin() {
            return iterator(head);
        }
             
        iterator end() {
            return iterator(tail);
        }
             
        ~DList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif