#pragma once

#include "stdafx.h"

struct ValuePoint
{
	void* value;
	ValuePoint* nextPoint;
};

template <class T>
class List
{
private:
	ValuePoint* m_pFirst;

public:
	List(void)
		: m_pFirst(NULL)
	{
	}
	~List(void)
	{
		ValuePoint* lastPoint = NULL;
		ValuePoint* curPoint = m_pFirst;

		while (curPoint->nextPoint != NULL)
		{
			lastPoint = curPoint;
			curPoint = curPoint->nextPoint;

			delete(lastPoint);
		}

		delete(curPoint);
	}

	void Add(T* value)
	{
		if (m_pFirst == NULL)
		{
			m_pFirst = new ValuePoint();
			ZeroMemory(m_pFirst, sizeof(ValuePoint));
		}

		ValuePoint* curPoint = m_pFirst;

		while (curPoint->nextPoint != NULL)
		{
			curPoint = curPoint->nextPoint;
		}

		if (m_pFirst->value == NULL)
		{
			curPoint->value = value;
		}
		else
		{
			ValuePoint* newValue = new ValuePoint();
			ZeroMemory(newValue, sizeof(ValuePoint));

			curPoint->nextPoint = newValue;
			newValue->value = value;
		}
	}

	bool Remove(T* value)
	{
		ValuePoint* lastPoint = NULL;
		ValuePoint* curPoint = m_pFirst;

		while (curPoint->value != value)
		{
			lastPoint = curPoint;
			curPoint = curPoint->nextPoint;

			if (curPoint->nextPoint == NULL) return false;
		}

		if (curPoint == m_pFirst)
		{
			curPoint->value = NULL;
		}
		else
		{
			lastPoint->nextPoint = curPoint->nextPoint;
			delete(curPoint);
		}

		return true;
	}

	int Count()
	{
		int count = 0;

		if (m_pFirst != NULL)
		{
			ValuePoint* curPoint = m_pFirst;

			while (curPoint->nextPoint != NULL)
			{
				curPoint = curPoint->nextPoint;

				if (count == 0) count++;
				count++;
			}
		}

		return count;
	}

	bool Contains(T* value)
	{
		ValuePoint* curPoint = m_pFirst;

		while (curPoint->nextPoint != NULL)
		{
			curPoint = curPoint->nextPoint;

			if (curPoint->value == value) return true;
		}

		return false;
	}

	int IndexOf(T* value)
	{
		int index = 0;
		ValuePoint* curPoint = m_pFirst;

		while (curPoint->nextPoint != NULL)
		{
			curPoint = curPoint->nextPoint;
			index++;

			if (curPoint->value == value) return index;
		}

		return -1;
	}

	T* GetValue(int index)
	{
		int indexCounter = 0;
		ValuePoint* curPoint = m_pFirst;

		while (curPoint->nextPoint != NULL || indexCounter == index)
		{
			if (indexCounter == index) return (T*)curPoint->value;

			curPoint = curPoint->nextPoint;
			indexCounter++;
		}

		return NULL;
	}
};

