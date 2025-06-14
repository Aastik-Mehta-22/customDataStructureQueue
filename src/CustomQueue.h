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

    Node* _head;
    Node* _tail;
    std::size_t _size;
    std::mutex _mutex;

    std::string _filename;
    void clear();
public:

    CustomQueue(const std::string& fname = "queue_" + std::string(typeid(T).name()) + ".txt");

    CustomQueue(const CustomQueue& other);

    CustomQueue(CustomQueue&& other) noexcept;

    ~CustomQueue();

    CustomQueue& operator=(const CustomQueue& other);
    CustomQueue& operator=(CustomQueue&& other) noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

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