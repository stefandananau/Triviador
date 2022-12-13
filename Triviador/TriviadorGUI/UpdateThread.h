#pragma once
#include <qthread.h>
class UpdateThread : public QThread
{
	Q_OBJECT
public:
	explicit UpdateThread(QObject* parent = nullptr);
	void run();
	bool stop;
signals:
	void updateSignal();
};

