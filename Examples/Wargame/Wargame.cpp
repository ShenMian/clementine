// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>
#include <iostream>
#include <string>

using namespace std;
using namespace clem;

class MyCircularQueue
{
public:
	MyCircularQueue(int k)
			: maxSize(k)
	{
		data = new int[maxSize];
	}

	~MyCircularQueue()
	{
		delete[] data;
	}

	bool enQueue(int value)
	{
		if(tail != -1 && isFull())
			return false;
		tail       = (tail + 1) % maxSize;
		data[tail] = value;
		return true;
	}

	bool deQueue()
	{
		if(isEmpty())
			return false;
		head = (head + 1) % maxSize;
		return true;
	}

	int Front()
	{
		if(isEmpty())
			return -1;
		return data[head];
	}

	int Rear()
	{
		if(isEmpty())
			return -1;
		return data[tail];
	}

	bool isEmpty()
	{
		return head == tail;
	}

	bool isFull()
	{
		return (tail + 1) % maxSize == head;
	}

private:
	int*  data;
	short head = 0;
	short tail = -1;
	short maxSize;
};

class App : public Application
{
public:
	App()
			: Application("Wargame")
	{
	}

	void init() override
	{
		pushScene(scene);

		MyCircularQueue circularQueue(3); // 设置长度为 3
		circularQueue.enQueue(6);         // 返回 true
		circularQueue.Rear();             // 返回 3
		circularQueue.isFull();           // 返回 true
		circularQueue.deQueue();          // 返回 true
		circularQueue.enQueue(4);         // 返回 true
		circularQueue.Rear();             // 返回 4
	}

private:
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}
