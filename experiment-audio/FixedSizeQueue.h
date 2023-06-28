#pragma once
#ifndef FIXED_SIZE_QUEUE_H
#define FIXED_SIZE_QUEUE_H
#include "iostream"

template <class T> class FixedSizeQueue {
private:
	unsigned int size_;
	int start_index_;
	int end_index_;
	unsigned int num_queued_;
	

public:
	T* start_p_;
	// Must be constructed with an argument
	FixedSizeQueue(int size)
		: size_(size), start_index_(-1), end_index_(-1), num_queued_(0), start_p_(new T[size])
	 {
	 }

	~FixedSizeQueue(void)
	 { 
		delete[] start_p_; 
	 }

	bool isEmpty(void) const
	{
		return start_index_ == -1;
	}
	bool isFull(void) const 
	 {
		if ((end_index_ + 1 == start_index_) ||
			(start_index_ == 0 && end_index_ == size_ - 1))
			return true;
		else
			return false;
	}

	// push a single element to the queue
	// returns -1 if queue is full
	// returns index otherwise
	int push(void) {
		int index;
		if (isFull()) {
			index = -1;
			return index;
		}
		else if (isEmpty()) {
			start_index_ = 0;
			end_index_ = 0;
			num_queued_++;
			index = end_index_;
		}
		else if (end_index_ != size_ - 1) {
			num_queued_++;
			index = ++end_index_;
		}
		else {
			end_index_ = 0;
			num_queued_++;
			index = end_index_;
		}
		return index;
	}

	// pop a single index from the queue
	// returns the index on success
	int pop(void) {
		int index;
		if (isEmpty()) {
			index = -1;
			return index;
		}
		else if (start_index_ == end_index_) {
			index = end_index_;
			start_index_ = -1;
			end_index_ = -1;
			num_queued_--;
			return index;
		}
		else if (start_index_ == size_ - 1) {
			start_index_ = 0;
			index = size_ - 1;
			num_queued_--;
			return index;
		}
		else {
			index = start_index_++;
			num_queued_--;
			return index;
		}
	}
	int num_queued(void)
	{
	 return num_queued_;
	}
};

#endif