/*============================================================
*	@file	 : subject.h
*	@brief	 : サブジェクト
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/25
*	@updated : 2026/06/02
*============================================================*/
#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
#include <list>

/*============================================================
*	@class	: Subject
*	@brief	: Observerへの通知送信
*============================================================*/
class Subject
{
private:
	std::list<Observer*> observers{};

public:
	virtual ~Subject() = default;

	void Attach(Observer* observer) {
		observers.push_back(observer);
	}
	void Detach(Observer* observer) {
		observers.remove(observer);
	}

protected:
	void Notify() {
		for (const auto& observer : observers) {
			observer->OnNotify();
		}
	}
};

#endif // SUBJECT_H