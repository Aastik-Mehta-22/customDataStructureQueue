#pragma once

#include <cstddef>
#include <stdexcept>
#include <mutex>
#include <string>
#include <vector>
#include <fstream>
#include <typeinfo>

namespace aastik
{

template <typename T>
class CustomQueue
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value): data(value),next(nullptr), prev(nullptr) {}
        Node(T&& value): data(std::move(value)), next(nullptr) , prev(nullptr){}
    };

    Node* _head; // Pointer to the front of the queue
    Node* _tail; // Pointer to the back of the queue
    std::size_t _size; // size of the queue
    std::mutex _mutex; // lock for thread safety

    std::string _filename; // to make it persistance
    void clear(); // Helper function to clear the queue
     
public:

    CustomQueue(const std::string& fname = "queue_" + std::string(typeid(T).name()) + ".txt"); // constructo

    CustomQueue(const CustomQueue& other); // copy constructor

    CustomQueue(CustomQueue&& other) noexcept; // move constructor

    ~CustomQueue(); // destructor

    CustomQueue& operator=(const CustomQueue& other); // copy assignment operator
    CustomQueue& operator=(CustomQueue&& other) noexcept; // move assignment operator

    T& front(); // Get the front element
    const T& front() const; // Get the front element (const)
    T& back(); // Get the back element
    const T& back() const; // Get the back element (const)

    bool empty() const;
    std::size_t size() const;

    void push(const T& value);
    void push(T&& value);
    void pop();
    void appendToFile(const std::string& fname,const T& value) const;
    void removeFrontFromFile(const std::string& fname);
    void loadFromFile(const std::string& fname);
    void push_without_save(const T& value);


};

}