#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QKeyEvent>
#include <QUrl>
#include <QIcon>

class VideoPlayer : public QWidget {
    Q_OBJECT

public:
    VideoPlayer(QWidget *parent = nullptr) : QWidget(parent) {
        // Initialize QMediaPlayer
        mediaPlayer = new QMediaPlayer(this);

        // Create Video Widget
        QVideoWidget *videoWidget = new QVideoWidget(this);

        // Set up the layout
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(videoWidget);
        setLayout(mainLayout);

        // Connect mediaPlayer to videoWidget
        mediaPlayer->setVideoOutput(videoWidget);

        // Set up the window
        setWindowTitle("Simple Video Player in Qt");
        setWindowIcon(QIcon("icon.png"));  // Set the window icon
        setGeometry(100, 100, 600, 400);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        switch (event->key()) {
            case Qt::Key_Space:
                togglePlayPause();
                break;
            case Qt::Key_Left:
                seekBackward();
                break;
            case Qt::Key_Right:
                seekForward();
                break;
            case Qt::Key_O:
                if (event->modifiers() & Qt::ControlModifier) {
                    loadVideo();
                }
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }

private slots:
    void loadVideo() {
        // Open a file dialog to select a video file
        QString fileUrl = QFileDialog::getOpenFileName(this, "Open Video", "", "Videos (*.mp4 *.avi *.mkv)");
        if (!fileUrl.isEmpty()) {
            mediaPlayer->setMedia(QUrl::fromLocalFile(fileUrl));
            mediaPlayer->play();
        }
    }

    void togglePlayPause() {
        // Toggle between play and pause
        if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
            mediaPlayer->pause();
        } else {
            mediaPlayer->play();
        }
    }

    void seekForward() {
        // Seek forward by 3 seconds
        mediaPlayer->setPosition(mediaPlayer->position() + 3000);
    }

    void seekBackward() {
        // Seek backward by 3 seconds
        mediaPlayer->setPosition(mediaPlayer->position() - 3000);
    }

private:
    QMediaPlayer *mediaPlayer;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    VideoPlayer player;
    player.show();
    return app.exec();
}
