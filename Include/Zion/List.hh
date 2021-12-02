#pragma once
#include <stdlib.h>
#include <exception>

namespace Zion
{
    class ListException : public std::exception
    {
        public:
            inline ListException(const char *what) : what_(what) {}

            inline const char *what() const noexcept
            {
                return this->what_;
            }

            const char *what_;
    };

    template<typename T>
    class List
    {
        public:
            inline List() : data(nullptr), capacity(0), length(0) {}

            inline size_t Push(T value)
            {
                if(this->length >= this->capacity)
                    this->Realloc(this->capacity + 16);

                this->data[this->length++] = value;
                return this->length - 1;
            }

            inline T Pop()
            {
                if(this->length <= 0)
                    throw ListException("Pop() from empty list");

                T value = this->data[--this->length];

                if(this->length + 16 < this->capacity)
                    this->Realloc(this->capacity - 16);

                return value;
            }

            inline T Back()
            {
                if(this->length <= 0)
                    throw ListException("Back() from empty list");

                return this->data[this->length - 1];
            }

            inline T Begin()
            {
                if(this->length <= 0)
                    throw ListException("Begin() from empty list");

                return this->data[0];
            }

            inline T &operator [](size_t index)
            {
                if(index >= this->length)
                    throw ListException("index out of range");

                return this->data[index];
            }

            inline size_t GetLength()
            {
                return this->length;
            }

            inline T *GetData() {
                return this->data;
            }

        private:
            void Realloc(size_t capacity)
            {
                this->capacity = capacity;
                this->data = (T *)realloc(this->data, capacity * sizeof(T));
            }

            T *data;
            size_t capacity;
            size_t length;
    };
};