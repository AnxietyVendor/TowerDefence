#include "towerposition.h"
#include <QPainter>

const QSize TowerPosition::ms_fixedSize(44, 44);

TowerPosition::TowerPosition(QPoint pos, const QPixmap &sprite/* = QPixmap(":/image/open_spot.png")*/)
	: m_hasTower(false)
	, m_pos(pos)
	, m_sprite(sprite)
{
    setTowerType(0);
}

const QPoint TowerPosition::centerPos() const
{
	QPoint offsetPoint(ms_fixedSize.width() / 2, ms_fixedSize.height() / 2);
	return m_pos + offsetPoint;
}

bool TowerPosition::containPoint(const QPoint &pos) const
{
	bool isXInHere = m_pos.x() < pos.x() && pos.x() < (m_pos.x() + ms_fixedSize.width());
	bool isYInHere = m_pos.y() < pos.y() && pos.y() < (m_pos.y() + ms_fixedSize.height());
	return isXInHere && isYInHere;
}

bool TowerPosition::hasTower() const
{
	return m_hasTower;
}
bool TowerPosition::hasTower2() const
{
    return m_hasTower2;
}


void TowerPosition::setHasTower(bool hasTower/* = true*/)
{
	m_hasTower = hasTower;
}
void TowerPosition::setHasTower2(bool hasTower/* = true*/)
{
    m_hasTower2 = hasTower;
}
QPoint TowerPosition::getposition()
{
    return m_pos;
}
void TowerPosition::draw(QPainter *painter) const
{
	painter->drawPixmap(m_pos.x(), m_pos.y(), m_sprite);
}
void TowerPosition::setTowerType(int n)
{
    m_towertype=n;
}
int  TowerPosition::towertype()
{
    return m_towertype;
}
bool TowerPosition::has2Tower() const
{
    return m_has2Tower;
}
bool TowerPosition::has2Tower2() const
{
    return m_has2Tower2;
}


void TowerPosition::setHas2Tower(bool hasTower/* = true*/)
{
    m_has2Tower = hasTower;
}
void TowerPosition::setHas2Tower2(bool hasTower/* = true*/)
{
    m_has2Tower2 = hasTower;
}
