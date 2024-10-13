#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <cstring>

namespace MyVector 
{
    class Container
    {
    public:

        Container() {
            m_data = new int[m_capacity];
        }

        Container(std::size_t capacity) : m_size(0), m_capacity(capacity)   {
            m_data = new int[m_capacity];
            assert(m_data != nullptr);
        }

        Container(const Container& other) : m_size(other.m_size), m_capacity(other.m_capacity)  {
            m_data = new int[m_capacity];

            std::copy(other.m_data, other.m_data + m_size, m_data);
        }

        Container(Container && other) : Container() {
            swap(other);
        }

        Container& operator=(Container &&other) {
            swap(other);

            return *this;
        }

        Container& operator=(const Container &other) {
            Container tmp = other;
            swap(tmp);

            return *this;
        }

        ~Container() {
            std::cout << "Container::~Container" << std::endl;

            delete[] m_data;
        }

        int& operator[](const int idx) {
            assert(idx >= 0);
            assert(idx < m_capacity);
            return m_data[idx];
        }

        const int& operator[](const int idx) const {
            assert(idx >= 0);
            assert(idx < m_capacity);
            return m_data[idx];
        }

        int& front() {
            return m_data[0]; 
        }

        const int& front() const {
            return m_data[0]; 
        }

        int& back() {
            return m_data[m_capacity - 1]; 
        }

        const int& back() const {
            return m_data[m_capacity - 1]; 
        }

        std::size_t size() const { return m_size; }

        std::size_t capacity() const { return m_capacity; }

        bool empty() const { return m_size == 0 ? true : false; }

        void clear() {
            memset(m_data, 0, sizeof(int) * m_size);
            m_size = 0;
        }

        void push_back(int new_val) {
            if (m_size == m_capacity / 2) {
                int *new_data = new int[m_capacity * 2];
                assert(new_data != nullptr);
                std::copy(m_data, m_data + m_size, new_data);
                delete[] m_data;
                m_data = new_data;
                m_capacity = m_capacity * 2;
            }  
            m_data[m_size++] = new_val;
        }

    public:

        void swap(Container & other)
        {
            std::swap(m_data,     other.m_data);
            std::swap(m_size,     other.m_size);
            std::swap(m_capacity, other.m_capacity);
        }

    private:

        int* m_data = nullptr; 
        std::size_t m_size = 0;
        std::size_t m_capacity = default_capacity;

        static constexpr auto default_capacity = 32;
    }; // class Container

    //  ================================================================================================

    inline void swap(Container & x, Container & y) { x.swap(y); }

    //  ================================================================================================
}