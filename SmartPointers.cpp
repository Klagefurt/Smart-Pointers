struct Expression;
struct Number;
struct BinaryOperation;

struct SharedPtr {
    size_t* count_ = nullptr;
    Expression* ptr_ = nullptr;

    explicit SharedPtr(Expression *ptr = 0): ptr_(ptr), count_(0) {
        if (ptr_) { count_ = new size_t(1); } //если указатель указывает на реальный объект, а не NULL - стартует счетчик
    }

    ~SharedPtr() {
        if (count_ == nullptr) return; //проверка не нулевая ссылка лежит по адресу счетчика
        if (--(*count_) == 0) { 
            delete ptr_;
            delete count_;
        }
    }

    SharedPtr(const SharedPtr & other): ptr_(other.ptr_), count_(other.count_) {
        if (ptr_) { ++(*count_); } //копируем поля указателя, проверяя не нулевой ли это указатель
    }
    
    
    void swap(SharedPtr & other) {
        std::swap(ptr_, other.ptr_);
        std::swap(count_, other.count_);
    }
    /*
    SharedPtr& operator=(const SharedPtr & other) {
        if (this != &other) { SharedPtr(other).swap(*this); }
        return *this;
    }*/
    
    SharedPtr& operator=(const SharedPtr & other) {
        if (this != &other) {
            if (ptr_ != nullptr) { --(*count_); }
            if (other.ptr_ != nullptr) { ++(*other.count_); }
            ptr_ = other.ptr_;
            count_ = other.count_;
        }
        return *this;
    }
    
    //void reset(Expression *ptr = 0) { SharedPtr(ptr).swap(*this); }
    
    void reset(Expression *ptr = 0) { //смена владельца
        this->~SharedPtr();
        ptr_ = ptr;
        count_ = 0;
        if (ptr != nullptr) { count_ = new size_t(1); }
    }

    
    Expression* get() const {
        return ptr_;
    }

    Expression& operator*() const {
        return *ptr_;
    }

    Expression* operator->() const {
        return ptr_;
    }

};
