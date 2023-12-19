#include <gtest/gtest.h>
#include "ThreadSafeContainer.hpp"

TEST(ThreadSafeContainerTest, PushBackAndSize) {
    ThreadSafeContainer<int> container;

    container.push_back(1);
    EXPECT_EQ(container.size(), 1);

    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
}

TEST(ThreadSafeContainerTest, MoveBackAndSize) {
    ThreadSafeContainer<int> container;

    container.move_back(1);
    EXPECT_EQ(container.size(), 1);

    container.move_back(2);
    EXPECT_EQ(container.size(), 2);
}

TEST(ThreadSafeContainerTest, MoveToPosition) {
    ThreadSafeContainer<int> container;
    container.push_back(1);
    container.push_back(2);

    container.move_to_position(1, 0);
    EXPECT_EQ(container[0], 1);
}

TEST(ThreadSafeContainerTest, CopyToPosition) {
    ThreadSafeContainer<int> container;
    container.push_back(1);
    container.push_back(2);

    container.copy_to_position(1, 0);
    EXPECT_EQ(container[0], 1);
}

TEST(ThreadSafeContainerTest, Clear) {
    ThreadSafeContainer<int> container;

    container.push_back(1);
    container.clear();
    EXPECT_EQ(container.size(), 0);
}

TEST(ThreadSafeContainerTest, ReserveAndCapacity) {
    ThreadSafeContainer<int> container;

    container.reserve(100);
    EXPECT_GE(container.capacity(), 100);
}

TEST(ThreadSafeContainerTest, Empty) {
    ThreadSafeContainer<int> container;

    EXPECT_TRUE(container.empty());
    container.push_back(1);
    EXPECT_FALSE(container.empty());
}

TEST(ThreadSafeContainerTest, PushBackThreadSafe) {
    ThreadSafeContainer<int> container;
    const int num_threads = 100;
    const int num_pushes_per_thread = 1000;

    // Create and start threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            for (int j = 0; j < num_pushes_per_thread; ++j) {
                container.push_back(j);
            }
            }));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check that the size of the container is as expected
    EXPECT_EQ(container.size(), num_threads * num_pushes_per_thread);
}

TEST(ThreadSafeContainerTest, MoveBackThreadSafe) {
    ThreadSafeContainer<int> container;
    const int num_threads = 100;
    const int num_pushes_per_thread = 1000;

    // Create and start threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            for (int j = 0; j < num_pushes_per_thread; ++j) {
                // Create a temporary object to pass to move_back
                int temp = j;
                container.move_back(std::move(temp));
            }
            }));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check that the size of the container is as expected
    EXPECT_EQ(container.size(), num_threads * num_pushes_per_thread);
}

TEST(ThreadSafeContainerTest, MoveToPositionThreadSafe) {
    const int num_threads = 100;
    const int num_positions_per_thread = 1000;
    ThreadSafeContainer<int> container(num_threads * num_positions_per_thread);

    // Create and start threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            for (int j = 0; j < num_positions_per_thread; ++j) {
                // Create a temporary object to pass to move_to_position
                int temp = j;
                int index = (i * num_positions_per_thread + j) % (num_threads * num_positions_per_thread);
                container.move_to_position(std::move(temp), index);
            }
            }));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check that the size of the container is as expected
    EXPECT_EQ(container.size(), num_threads * num_positions_per_thread);
}

TEST(ThreadSafeContainerTest, CopyToPositionThreadSafe) {
    const int num_threads = 100;
    const int num_positions_per_thread = 1000;
    ThreadSafeContainer<int> container(num_threads * num_positions_per_thread);

    // Initialize the container with some values
    for (int i = 0; i < num_threads * num_positions_per_thread; ++i) {
        container[i] = i;
    }

    // Create and start threads
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            for (int j = 0; j < num_positions_per_thread; ++j) {
                int index = (i * num_positions_per_thread + j) % (num_threads * num_positions_per_thread);
                container.copy_to_position(container[j], index);
            }
            }));
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    // Check that the size of the container is as expected
    EXPECT_EQ(container.size(), num_threads * num_positions_per_thread);
}