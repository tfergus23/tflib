#pragma once
#include <stdexcept>
//#include <cstring>

namespace tflib{
    template <typename T, size_t S>
    class static_vector {
    public:
        size_t size() const {
            return m_size;
        }
        void push_back(T element) {
#ifndef NDEBUG
            if (m_size >= capacity) {
                throw std::out_of_range("Tried to add element to static vector, but it is already at capacity.");
            }
#endif
            arr[m_size++] = element;
        }
        void pop_back() {
            m_size--;
        }


        T& operator[](size_t index) {
#ifndef NDEBUG
            if (index >= m_size || index < 0) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            return arr[index];
        }

        const T& operator[](size_t index) const {
#ifndef NDEBUG
            if (index >= m_size || index < 0) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            return arr[index];
        }

        void clear(){
            m_size = 0;
        }
        size_t find(const T& element) const{
            for(size_t i = 0; i < m_size; i++){
                if (arr[i] == element){
                    return i;
                }
            }
            return -1;
        }

        void remove_at(size_t index){
#ifndef NDEBUG
            if (index >= m_size || index < 0) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            if (index == m_size-1){
                pop_back();
                return;
            }
            
            for (size_t i = index; i < m_size-1; i++){
                arr[i] = arr[i+1];
            }
            
            m_size--;
        }


        const size_t capacity = S;
    private:
        size_t m_size = 0;
        T arr[S];
    };
}