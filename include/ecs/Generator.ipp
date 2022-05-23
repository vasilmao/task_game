template <typename Id>
Id IdGenerator<Id>::Next() {
  return current_++;
}

template <typename Id>
Id StaticIdGenerator<Id>::Next() {
  return current_++;
}

template <typename Id>
Id StaticIdGenerator<Id>::current_{1};
