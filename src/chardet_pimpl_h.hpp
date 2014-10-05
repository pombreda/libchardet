#ifndef CHARDET_PIMPL_H_HPP
#define CHARDET_PIMPL_H_HPP

#include <memory>

namespace Chardet {

template<typename T>
class pimpl {
private:
    std::unique_ptr<T> m;
public:
    pimpl();
    template<typename ...Args> pimpl( Args&& ... );
    ~pimpl();
    T* operator->();
    T& operator*();
};

} // Chardet::

#endif // CHARDET_PIMPL_H_HPP
