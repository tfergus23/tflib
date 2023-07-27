#pragma once
#include <stdexcept>

namespace tflib{
    template <typename T, size_t S>
    class static_vector {
    public:
        size_t size() {
            return m_size;
        }
        void push_back(T element) {
            if (m_size >= capacity) {
                throw std::out_of_range("Tried to add element to static vector, but it is already at capacity.");
            }
            arr[m_size++] = element;
        }
        void pop_back() {
            m_size--;
        }
        T& operator[](size_t index) {
            if (index >= m_size || index < 0) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
            return arr[index];
        }
        void clear(){
            m_size = 0;
        }


        const size_t capacity = S;
    private:
        size_t m_size = 0;
        T arr[S];
    };
}