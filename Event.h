#pragma once

#include "stdafx.h"
#include "List.h"

typedef void (CALLBACK* EventHandler)(LPVOID, LPVOID);
/*template <class cInstance>
typedef void (cInstance::*tFunction)(LPVOID, LPVOID);*/
//typedef EventHandler* LPEVENTHANDLER;

class Event
{
public:
	Event(void);
	~Event(void);

	void AddHandler(EventHandler handler);
	void RemoveHandler(EventHandler handler);

	void RaiseEvent(void* sender, void* eventArgs);
private:
	List<EventHandler>* m_listHandler;
};

