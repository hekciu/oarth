


namespace std {

class exception {
public:
    exception() noexcept {

    }

    exception(const exception * other) noexcept {

    }

    ~exception() {}

    virtual const char * what() {
        return this->_what;
    }

private:
    const char * _what = "something went wrong...";
};

}
