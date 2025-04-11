namespace std {

template<typename T>
class deque {
public:
    deque() {
        this->first = NULL;
    }

private:
    struct element {
        T object;
        element * prev;
        element * next;
    }

    element * first;
}

}
