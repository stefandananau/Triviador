#include "UpdateThread.h"

UpdateThread::UpdateThread(QObject* parent) : QThread(parent)
{
	stop = false;
}

void UpdateThread::run()
{
	while (!stop) {
		emit updateSignal();
		this->msleep(500);
	}
}

