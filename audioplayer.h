#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class QMediaPlayer;

enum SoundType
{
    bianpaotower,
    build,
    die,
    icetower,
    lose,
    loseplayerhp,
    upgrade,
    victory
};

class AudioPlayer : public QObject
{
public:
    explicit AudioPlayer(QObject *parent = 0);

	void startBGM();
	void playSound(SoundType soundType);

private:
	QMediaPlayer *m_backgroundMusic; // 只用来播放背景音乐
};


#endif // AUDIOPLAYER_H
