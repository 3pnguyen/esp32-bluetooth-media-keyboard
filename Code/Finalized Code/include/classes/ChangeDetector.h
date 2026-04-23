#pragma once

template <typename T>
class ChangeDetector {
  private:
    T previous;
    T current;

  public:
      ChangeDetector(T initial);
      bool update(T newValue);
      T get() const;
      void reset(T value);
};
