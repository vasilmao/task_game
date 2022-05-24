#pragma once

#include <cassert>
#include <cstdlib>
#include <functional>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <auto Fu>
struct ArgConnector {};

template <typename>
class Delegate;

template <typename Ret, typename... Args>
class Delegate<Ret(Args...)> {
  using target_signature = Ret(void*, Args...);
  using function_signature = Ret(Args...);

 public:
  template <auto F, typename... Type>
  Delegate(ArgConnector<F> /*f*/, Type&&... instance_or_args) {
    connect<F>(std::forward<Type>(instance_or_args)...);
  }

  template <auto Candidate>
  void connect() {
    callable_ = [](void*, Args... args) { return Ret(Candidate(std::forward<Args>(args)...)); };
  }

  template <auto Candidate, typename Type>
  void connect(Type& instance) {
    instance_ = &instance;
    callable_ = [](void* instance, Args... args) {
      return Ret(((reinterpret_cast<Type*>(instance))->*(Candidate))(std::forward<Args>(args)...));
    };
  }

  Ret operator()(Args... args) {
    assert(callable_ != nullptr);
    return callable_(instance_, args...);
  }

  bool operator==(const Delegate<Ret(Args...)>& other) {
    return callable_ == other.callable_ && instance_ == other.instance_;
  }

 private:
  void* instance_ = nullptr;
  target_signature* callable_ = nullptr;
};

using EventId = size_t;

struct EventIdGenerator {
  static EventId GetId() {
    static EventId id{0};
    return id++;
  }
};

template <typename T>
struct EventIdHolder {
  static EventId GetId() {
    const static EventId id = EventIdGenerator::GetId();
    return id;
  }
};

class BaseSink {
 public:
  virtual ~BaseSink(){};
};

template <typename EventT>
class Sink final : public BaseSink {
  using function_type = void(const EventT&);

 public:
  template <auto F, typename U>
  void Connect(U& instance) {
    callback_.emplace_back(ArgConnector<F>{}, instance);
  }

  template <auto F>
  void Connect() {
    callback_.emplace_back(ArgConnector<F>{});
  }

  template <auto F, typename U>
  void Disconnect(U& instance) {
    Delegate<function_type> f{ArgConnector<F>{}, instance};
    for (auto it = callback_.begin(); it != callback_.end(); ++it) {
      if (*it == f) {
        callback_.erase(it);
        break;
      }
    }
  }

  template <auto F>
  void Disconnect() {
    Delegate<function_type> f{ArgConnector<F>{}};
    for (auto it = callback_.begin(); it != callback_.end(); ++it) {
      if (*it == f) {
        callback_.erase(it);
        break;
      }
    }
  }

  void Publish(const EventT& event) {
    for (size_t i = 0; i < callback_.size(); ++i) {
      callback_[i](event);
    }
  }

 private:
  std::vector<Delegate<function_type>> callback_;
};

class Dispatcher {
 public:
  template <typename EventType>
  Sink<EventType>& Assure(EventId id) {
    BaseSink* ans_ptr = nullptr;
    if (dispatchers.count(id) == 0) {
      ans_ptr = new Sink<EventType>{};
      dispatchers[id] = ans_ptr;
    } else {
      ans_ptr = dispatchers[id];
    }

    assert(ans_ptr != nullptr);
    return *static_cast<Sink<EventType>*>(ans_ptr);
  }

  template <typename EventType>
  Sink<EventType>& GetSink() {
    return Assure<EventType>(EventIdHolder<EventType>::GetId());
  }

  template <typename EventType, typename... Args>
  void Trigger(Args&&... args) {
    EventType e{std::forward<Args>(args)...};
    Assure<EventType>(EventIdHolder<EventType>::GetId()).Publish(e);
  }

  ~Dispatcher() {
    for (size_t i = 0; i < dispatchers.size(); ++i) {
      delete dispatchers[i];
    }
  }

 private:
  std::unordered_map<EventId, BaseSink*> dispatchers;
};
