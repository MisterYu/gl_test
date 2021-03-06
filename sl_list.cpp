#include <iostream>
#include <string>
#include <fstream>
#include "sl_list.h"

using std::cout;
using std::endl;
using std::string;

/**
* Append a node to the linked list
*/
void sl_list::append(string data) {

    // Create a new node
    Node* new_node = new Node;
    new_node->data = data;
    new_node->next = NULL;

    // Create a temp pointer
    Node *tmp = head;

    if ( tmp != NULL ) {
        // Nodes already present in the list
        // Parse to end of list
        while ( tmp->next != NULL ) {
            tmp = tmp->next;
        }

        // Point the last node to the new node
        tmp->next = new_node;
    }
    else {
        // First node in the list
        head = new_node;
    }
}

/*
* wrapper function to check if name in data using string::find
*/
bool has_name(Node* n, string name)
{
    std::size_t found = n->data.find(name);
    if (found == string::npos)
        return false;
    else
        return true;
}

/**
* Find a node from the list and maybe delete it
* Recycled loop code for find and delete
* input: 
*   string  - name  - who to find to delete or print
*   bool    - del   - true: delete if name found, else print contact
*/
bool sl_list::find_maybe_delete(string name, bool del) 
{
    bool found = false;

    // Temp pointer
    Node *tmp = head;

    string report = del ? "Deleting: " : "Found: "; 

    // No nodes
    if ( tmp == NULL ) 
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        // check if only 1 element has name
        //if (tmp->next == NULL && tmp->data == name)
        if (tmp->next == NULL && has_name(tmp, name))
        {
            found = true;
            cout << report << tmp->data << endl;
            if (del)
            {
                delete tmp;
                head = NULL;
            }
        }
        // loop thru and check other elements for name
        else
        {
            Node *prev = head;
            // check for name match or end of list
            //while (tmp->data != name && tmp->next != NULL)
            while (!has_name(tmp, name) && tmp->next != NULL)
            {
                prev = tmp;
                tmp = tmp->next;
            }
            // check if name match is found
            //if (tmp->data == name)
            if (has_name(tmp, name))
            {
                found = true;
                cout << report << tmp->data << endl;
                if (del) {
                    prev->next = tmp->next;
                    delete tmp;
                }
            }
        }
    }
    return found;
}

/*
* wrapper around find_maybe_delete for finding something
*/
bool sl_list::find(string name)
{
    bool del = false;
    return find_maybe_delete(name, del);
}

/*
* wrapper around find_maybe_delete for deleting something
*/
bool sl_list::erase(string name)
{
    bool del = true;
    return find_maybe_delete(name, del);
}
