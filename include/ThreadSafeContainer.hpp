#pragma once
#include <shared_mutex>
#include <vector>

template<typename ValueType>
class ThreadSafeContainer {

    std::vector<ValueType> _container;
    mutable std::shared_mutex _mutex;

public:

    /**
     * @brief A thread-safe container that provides synchronized access to its underlying container.
     */
    ThreadSafeContainer() : _container(), _mutex() {};
    
    /**
     * @class ThreadSafeContainer
     * @brief A thread-safe container that provides synchronized access to its elements.
     *
     * This class provides a thread-safe container that can be accessed by multiple threads concurrently.
     * It uses a mutex to ensure that only one thread can access the container at a time, preventing data races.
     *
     * @tparam T The type of elements stored in the container.
     */
    ThreadSafeContainer(size_t size) : _container(size), _mutex() {};

    /**
     * @brief Adds a value to the end of the container in a thread-safe manner.
     * 
     * @param value The value to be added.
     */
    void push_back(const ValueType& value) {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container.push_back(value);
    };

    /**
     * @brief Moves a value to the back of the container in a thread-safe manner.
     * 
     * @param value The value to be moved to the back of the container.
     */
    void move_back(ValueType&& value) {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container.push_back(std::move(value));
    };

    /**
     * Moves the specified value to the given position in the container.
     * 
     * @param value The value to be moved.
     * @param index The index where the value should be moved to.
     */
    void move_to_position(ValueType&& value, size_t index) {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container[index] = std::move(value);
    }

    /**
     * Copies the given value to the specified position in the container.
     * 
     * @param value The value to be copied.
     * @param index The index of the position where the value should be copied.
     */
    void copy_to_position(const ValueType& value, size_t index) {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container[index] = value;
    };

    /**
     * @brief Clears the container in a thread-safe manner.
     * 
     * This function acquires a unique lock on the internal mutex before clearing the container.
     * It ensures that no other threads can access the container while it is being cleared.
     * 
     * @note This function is noexcept.
     */
    void clear() noexcept {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container.clear();
    };

    /**
     * Reserves memory for at least the specified number of elements.
     *
     * @param size The number of elements to reserve memory for.
     */
    void reserve(size_t size) {
        std::unique_lock<std::shared_mutex> lock(_mutex);
        _container.reserve(size);
    };

    /**
     * Checks if the container is empty.
     * 
     * @return true if the container is empty, false otherwise.
     */
    bool empty() const noexcept {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _container.empty();
    };

    /**
     * @brief Returns the size of the container.
     * 
     * @return The number of elements in the container.
     */
    size_t size() const noexcept {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _container.size();
    };

    /**
     * Returns the maximum number of elements that the container can hold.
     *
     * @return The maximum number of elements that the container can hold.
     */
    size_t capacity() const noexcept {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _container.capacity();
    };

    /**
     * @brief The type of value stored in the container.
     */
    ValueType& operator[](size_t index) {
        std::shared_lock<std::shared_mutex> lock(_mutex);
        return _container[index];
    }
};
