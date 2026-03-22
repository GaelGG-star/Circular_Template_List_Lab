//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include "Media.h"
#include <iostream>

template <typename T>
struct Node {
    // Data is now hard-coded to the BASE CLASS pointer: Media*
    T* data;
    Node<T>* next;

    // Constructor initializes data and pointer
    Node(T* data) : data(data), next(nullptr) {}
};

// === 5. Hard-coded LinkedList Class (Singly, Non-Circular) ===
// This list is only capable of managing Media* objects (Song*, Podcast*, etc.) and is forward-only.
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;                 // Tracks the last node
    Node<T>* currentPlaylistNode;  // Tracks which song is "playing"

public:
    // Constructor: Initializes an empty list
    LinkedList() : head(nullptr), tail(nullptr), currentPlaylistNode(nullptr) {}

    // Destructor: Cleans up all nodes and the Media objects they point to.
    ~LinkedList() {
        if (head == nullptr) return;

        // 1. Break the circle to make it a linear list again
        tail->next = nullptr;

        // 2. Standard linear deletion
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next_node = current->next;
            delete current->data;
            delete current;
            current = next_node;
        }

        head = tail = currentPlaylistNode = nullptr;
        std::cout << "\n[Circular Playlist cleanup complete.]" << std::endl;
    }

    // Insertion: Adds a new Media pointer to the end of the list.
    void insert(T* newData) {
        Node<T>* newNode = new Node<T>(newData);

        if (head == nullptr) {
            // Case 1: List is empty. New node becomes the head.
            head = newNode;
            tail = newNode;
            newNode->next = head;        // Point to itself to create the circle
            currentPlaylistNode = head;   // Start playback tracking at the head
        } else {
            // Case 2: Traverse to the end and link the new node.
            newNode->next = head;        // New node points to the start
            tail->next = newNode;        // Old tail points to the new node
            tail = newNode;              // The new node is now the tail
        }
    }

    // Traversal: Displays all media items in the list.
    void displayList() const {
        if (head == nullptr) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<T>* current = head;
        int index = 1;

        do {
            std::cout << index++ << ". " << current->data->toString() << std::endl;
            current = current->next;
        } while (current != head); // Stop when we get back to the start

        std::cout << "---------------------------------" << std::endl;
    }

    // Simple play method for demonstration (students will expand this later)
    void playCurrent() const {
        if (currentPlaylistNode != nullptr) {
            currentPlaylistNode->data->play(); // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }

    void playNext() {
        if (currentPlaylistNode == nullptr) {
            std::cout << "[Nothing to play.]" << std::endl;
            return;
        }

        // Move to the next node (wraps automatically)
        currentPlaylistNode = currentPlaylistNode->next;

        std::cout << "\n>>> Switched to next track:" << std::endl;
        currentPlaylistNode->data->play();
    }

};

#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H