// Event.cpp: Ereigniss-Klasse
// by Tim Boden
//

#include "Event.h"

Event::Event(void)
{
	m_listHandler = new List<EventHandler>();
}

Event::~Event(void)
{
}

void Event::AddHandler(EventHandler handler)
{
	m_listHandler->Add(&handler);
}

void Event::RemoveHandler(EventHandler handler)
{
	m_listHandler->Remove(&handler);
}

void Event::RaiseEvent(void* sender, void* eventArgs)
{
	for (int i = 0; i < m_listHandler->Count(); i++)
	{
		EventHandler handler;
		handler = *m_listHandler->GetValue(i);
		
		handler(sender, eventArgs);
	}
}