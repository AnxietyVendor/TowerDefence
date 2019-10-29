#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>



AudioPlayer::AudioPlayer(QObject *parent)
	: QObject(parent)
	, m_backgroundMusic(NULL)
{
	// 创建一直播放的背景音乐
    QUrl backgroundMusicUrl=QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\backgroundmusic.mp3");
	if (QFile::exists(backgroundMusicUrl.toLocalFile()))
	{
        m_backgroundMusic = new QMediaPlayer(this);
        m_backgroundMusic->setVolume(2);
		QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();

        QMediaContent media(backgroundMusicUrl);
		backgroundMusicList->addMedia(media);
		backgroundMusicList->setCurrentIndex(0);
        // 设置背景音乐循环播
		backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
		m_backgroundMusic->setPlaylist(backgroundMusicList);
	}
}

void AudioPlayer::startBGM()
{
	if (m_backgroundMusic)
		m_backgroundMusic->play();
}

void AudioPlayer::playSound(SoundType soundType)
{
	static const QUrl mediasUrls[] =
	{
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\bianpaotower.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\build.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\die.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\icetower.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\lose.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\loseplayerhp.wav"),
        QUrl::fromLocalFile("C:\\Users\ \mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\upgrade.wav"),
        QUrl::fromLocalFile("C:\\Users\\mi\\Desktop\\TDbeta3.2\\TDbeta3.1\\TowerDefense\\upgradedTower\\music\\victory.wav")
	};
	static QMediaPlayer player;

	if (QFile::exists(mediasUrls[soundType].toLocalFile()))
	{
		player.setMedia(mediasUrls[soundType]);
        player.setVolume(100);
		player.play();
	}
}
