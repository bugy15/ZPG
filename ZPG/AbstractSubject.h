// The Abstract Subject
#pragma once

class AbstractObserver; //dopredna deklarace (z duvodu krizoveho odkazu)

class AbstractSubject
{
public:
	virtual void registerObserver(AbstractObserver* ob) = 0;
	virtual void removeObserver(AbstractObserver* ob) = 0;
	virtual void notifyObserver() = 0;
};