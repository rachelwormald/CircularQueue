#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -99999;


// setting initial size, head, and tail
// capacity set to 16 for default constructor
// new queue created with capacity
CircularQueue::CircularQueue() {

    size_ = 0;
    capacity_ = 16;
    head_ = NULL;
    tail_ = NULL;
    items_ = new CircularQueue::QueueItem[capacity_];

}

// initial size, head, tail
// same as previous constructor, but setting capacity as the variable capacity, not 16
CircularQueue::CircularQueue(unsigned int capacity) {

    size_ = 0;
    capacity_ = capacity;
    head_ = NULL;
    tail_ = NULL;
    items_ = new CircularQueue::QueueItem[capacity_];


}

// destructor with delete to de-allocate memory assigned with new operator
CircularQueue::~CircularQueue() {

    delete[] items_;

}

// queue is empty if the size is at or below 0, checks for this case and returns true, will otherwise return false
bool CircularQueue::empty() const {

    if (size_ == 0)
    {
        return true;
    }
    return false;
}

// queue is full if the size has reached or somehow surpassed the capacity
// function will return true if this condition is met, false otherwise
bool CircularQueue::full() const {

    if (size_ == capacity_)
    {
        return true;
    }
    return false;
}

//  returns size_ which is the size of the queue
int CircularQueue::size() const {

    return size_;
}

// adding item to end of queue
bool CircularQueue::enqueue(QueueItem value) {

    // checks if the queue is full, and returns false if the full function returns true
    if (full())
    {
        return false;
    }

    // checks if the queue is empty because head and tail will need to be specifically directed to index 0 and 1
    // since it will be a one-element queue, the value is at the index of the head of the queue
    if (empty())
    {
        head_ = 0;
        tail_ = 1;
        items_[head_] = value;
    }

    // in all other cases, the index of the tail is where the new value is queued, and the tail is increased by one and called with the modulo operation with capacity
    // to maintain structure of circular array
    else
    {
        items_[tail_] = value;
        tail_ = (tail_ + 1) % capacity_;
    }

    // added a value, increasing size
    size_++;
    return true;
}

// removing item at front of queue
CircularQueue::QueueItem CircularQueue::dequeue() {

    // can't dequeue if empty, returning empty queue variable
    if (empty())
    {
        return EMPTY_QUEUE;
    }

    // creating x so it can be returned once it's removed from the queue
    CircularQueue::QueueItem x = items_[head_];

    // specific case for a 1 element queue
    // head a tail need to be null since queue will be empty, and decrease size since removing a value
    if (size_ == 1)
    {
        head_ = NULL;
        tail_ = NULL;
        size_--;
    }

    // all other cases will make remove the value at the head of the queue, increase the head, and decrease the size - removing value at front of the queue
    else
    {
        items_[head_] = NULL;
        head_ = (head_ + 1) % capacity_;
        size_--;
    }

    // returning value that was dequeued
    return x;

}

// reference to front of queue
CircularQueue::QueueItem CircularQueue::peek() const {

    // if the queue is empty, there's no value to return, therefore returning empty queue
    if (empty())
    {
        return EMPTY_QUEUE;
    }

    // otherwise will return the value at the head of the queue (the front)
    return items_[head_];
}

// printing values in queue
void CircularQueue::print() const {

    //creating i to start at the head index and increase by 1 until it's reached the end of the queue, outputting the value at each index
    for (int i = head_; i < size_; i++)
    {
        std::cout << items_[i] << "\t";
    }


}

