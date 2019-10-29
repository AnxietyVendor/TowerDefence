#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H

#include <QPoint>
#include <QSize>
#include <QPixmap>

class QPainter;

class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap(":/image/towerbase.png"));

	void setHasTower(bool hasTower = true);
	bool hasTower() const;
    bool hasTower2() const;
    int  towertype() ;
    void setTowerType(int n=0) ;
    bool has2Tower()const;
    bool has2Tower2()const;
    void setHas2Tower(bool hastower = true);
    void setHas2Tower2(bool hastower = true);
    void setHasTower2(bool hasTower = true);
	const QPoint centerPos() const;
	bool containPoint(const QPoint &pos) const;
    QPoint getposition();
	void draw(QPainter *painter) const;

private:
    int         m_towertype;
	bool		m_hasTower;
    bool		m_hasTower2;
    bool        m_has2Tower;
    bool        m_has2Tower2;
	QPoint		m_pos;
	QPixmap		m_sprite;

	static const QSize ms_fixedSize;
};

#endif // TOWERPOSITION_H
