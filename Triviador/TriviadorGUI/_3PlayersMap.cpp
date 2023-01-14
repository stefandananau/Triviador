#include "_3PlayersMap.h"
#include  <QDateTime>
_3PlayersMap::_3PlayersMap(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/new/prefix1/images/ship2.png"));
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(updateBackground()));
	m_timer->start(1000);

}
void _3PlayersMap::updateBackground()
{
	std::vector<QString> backgroundImages;
	backgroundImages.push_back(":/new/prefix1/images/water-2.png");
	backgroundImages.push_back(":/new/prefix1/images/water-3.png");
	backgroundImages.push_back(":/new/prefix1/images/water-4.png");
	backgroundImages.push_back(":/new/prefix1/images/water-5.png");
	backgroundImages.push_back(":/new/prefix1/images/water-6.png");
	int index = QTime::currentTime().second() % backgroundImages.size();
	this->setStyleSheet("background-image: url(" + backgroundImages[index] + ");");


}
_3PlayersMap::~_3PlayersMap()
{}
