#include "custom-classes/ChangeDetector.h"

//by chatgpt

template <class T>
ChangeDetector<T>::ChangeDetector(T initial) : previous(initial), current(initial) {}

template <class T>
bool ChangeDetector<T>::update(T newValue) {
    current = newValue;
    if (current != previous) {
        previous = current;
        return true;
    }
    return false;
}

template <class T>
T ChangeDetector<T>::get() const {return current;}

template <class T>
void ChangeDetector<T>::reset(T value) {
    previous = value;
    current  = value;
}

template class ChangeDetector<int>;
template class ChangeDetector<bool>;
template class ChangeDetector<float>;