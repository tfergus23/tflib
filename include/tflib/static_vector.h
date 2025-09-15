#pragma once
#include <stdexcept>
#include <array>
#include <iostream>

namespace tflib{
    constexpr size_t npos = -1;
    /*
    tflib::static_vector is a std::vector with fixed capacity, meaning it can be allocated on the stack.
    */
    template <typename T, size_t S>
    class static_vector {
    public:
        static_vector() = default;
        static_vector(std::initializer_list<T> init){
#ifndef NDEBUG
            if (init.size() > S){
                throw std::length_error("Initializer list exceeds static_vector capacity.");
            }
#endif
            for (const T& item : init){
                arr[m_size++] = item;
            }
        }
        
        size_t size() const {
            return m_size;
        }
        void push_back(const T& element) {
#ifndef NDEBUG
            if (m_size >= capacity()) {
                throw std::out_of_range("Tried to add element to static vector, but it is already at capacity.");
            }
#endif
            arr[m_size++] = element;
        }

        void push_back(const T&& element) {
#ifndef NDEBUG
            if (m_size >= capacity()) {
                throw std::out_of_range("Tried to add element to static vector, but it is already at capacity.");
            }
#endif
            arr[m_size++] = element;
        }

        template <class... Args>
        void emplace_back(Args&&... args){
#ifndef NDEBUG
            if (m_size >= capacity()) {
                throw std::out_of_range("Tried to add element to static vector, but it is already at capacity.");
            }
#endif
            arr[m_size].~T();
            new(&arr[m_size++]) T(std::forward<Args>(args)...);
        }
        void pop_back() {
            arr[m_size-1].~T();
            m_size--;
        }


        T& operator[](size_t index) {
#ifndef NDEBUG
            if (index >= m_size) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            return arr[index];
        }

        const T& operator[](size_t index) const {
#ifndef NDEBUG
            if (index >= m_size) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            return arr[index];
        }

        void clear(){
            for (size_t i = 0; i < m_size; i++){
                arr[i].~T();
            }
            m_size = 0;
        }
        size_t find(const T& element) const{
            for(size_t i = 0; i < m_size; i++){
                if (arr[i] == element){
                    return i;
                }
            }
            return npos;
        }

        void remove_at(size_t index){
#ifndef NDEBUG
            if (index >= m_size) {
                throw std::out_of_range("Index is out of bounds of the static vector: " + std::to_string(index));
            }
#endif
            if (index == m_size-1){
                pop_back();
                return;
            }

            for (size_t i = index; i < m_size-1; i++){
                arr[i] = std::move(arr[i+1]);
            }
            pop_back();
        }

        constexpr size_t capacity() const{
            return S;
        }

        T* begin(){
            return arr.data();
        }
        T* end(){
            return arr.data() + m_size;
        }
        const T* begin() const{
            return arr.data();
        }
        const T* end() const{
            return arr.data() + m_size;
        }
        const T* cbegin() const{
            return arr.data();
        }
        const T* cend() const{
            return arr.data() + m_size;
        }
    private:
        size_t m_size = 0;
        std::array<T,S> arr;
    };
}