#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"

template <class T>
class SListIterator : public Iterator<T> {     
    public: 
        SListIterator() : Iterator<T>() {};
        SListIterator(Node<T> *current) : Iterator<T>(current) {};
        SListIterator<T> operator++()
        {
            this->current = this->current->next;
            return *this;
        }
};

template <typename Tr>
class SList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
        typedef SListIterator<T> iterator;
      
    private:
        Node<T>* head;
        Operation cmp;
              
    public:
        SList() {
            head = nullptr;
        };

        bool find(T search, Node<T> **&pointer) {

            pointer  = &head;

            while((*pointer)->next!= NULL)
            {
                if((*pointer)->data == search)
                {
                    return true;
                }
                if(!cmp( (*pointer)->data, search))
                {
                    break;                    
                }
                pointer = &((*pointer)->next);
            }
            return false;
        }
             

        bool insert(T data) { // No es necesario controlar el caso base aquí

            Node<T> **temp = &head;

            if(head == NULL)
            {
                head = new Node<T>(data);
                head->next = NULL;
                return true;
            }

            if(!find(data,temp))
            {
                Node<T> *new_node = new Node<T>(data);
                if((*temp)->next == NULL)
                {
                    new_node->next = NULL;
                    (*temp)->next = new_node;
                    return true;
                }
                new_node->next = (*temp)->next;
                (*temp)->next = new_node;
                return true;
            }
            return false;
        }
             

        bool remove(T item) { // No estás usando el find para el remove
            Node<T> *current = head;


            if (current->data == item)
            {
                head = head->next;
                delete current;
                return true;
            }

            Node<T> *temp = head;
            while(current!=NULL)
            {
                temp = current->next;
                if (temp->data == item)
                {
                    current->next = temp->next;
                    delete temp; 
                    return true;
                }
                current = current->next;
            }   

            return false;


        }  
             
        iterator begin() {
            return iterator(head);
        }
             
        iterator end() {
            return iterator(NULL);
            /*
            Node<T> *temp = head;
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            return iterator(temp);
            */
        }
             
        ~SList() {
            if (head) {
                head->killSelf();
            } 
        }         
};

#endif