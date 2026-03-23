#include <iostream>
#include <ostream>

namespace atnott {
    template <typename T>
    class shared_ptr {
        public:
            shared_ptr(T* ptr) : ptr(ptr) {
                if (ptr) {
                    cnt = new int(1);
                }
                else cnt = nullptr;
                std::cout << "construct " << this->ptr << std::endl;
            }
            shared_ptr(const shared_ptr<T>& ptr) {
                this->ptr = ptr.ptr;
                this->cnt = ptr.cnt;
                if (cnt) ++(*cnt);
                std::cout << "copy " << this->ptr << std::endl;
            }
            ~shared_ptr() {
                if (cnt) {
                    --(*cnt);
                    if (*cnt == 0) {
                        delete cnt;
                        delete ptr;
                        std::cout << "destruct " << this->ptr << std::endl;
                    }
                }
            }
            T& operator * () {
                    return *ptr;
                }
            shared_ptr& operator = (const shared_ptr& other) {
                if (this != &other) {
                    if (cnt) {
                        --(*cnt);
                        if (*cnt == 0) {
                            delete cnt;
                            delete ptr;
                            std::cout << "destruct " << this->ptr << std::endl;
                        }
                    }
                    this->ptr = other.ptr;
                    this->cnt = other.cnt;
                    if (cnt) ++(*cnt);
                }
                return *this;
            }

            friend std::ostream& operator << (std::ostream& os, const shared_ptr<T>& ptr) {
                os << ptr.ptr;
                return os;
            }

        protected:
            int* cnt = nullptr;
            T* ptr;
    };
}