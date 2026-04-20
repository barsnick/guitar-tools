/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2016-2017 Simon Stuerz <stuerz.simon@gmail.com>          *
 *                                                                         *
 *  This file is part of guitar tools.                                     *
 *                                                                         *
 *  Guitar tools is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Guitar tools is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with guitar tools. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QStandardPaths>
#include <QUrl>
#include <QDir>

#include "qtmultimediacompat.h"
#include "audioinput.h"
#include "volumeanalyzer.h"

class Recorder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(QString filePath READ filePath CONSTANT)
    Q_PROPERTY(QString recordTime READ recordTime NOTIFY recordTimeChanged)
    Q_PROPERTY(double volumeLevel READ volumeLevel NOTIFY volumeLevelChanged)

public:
    explicit Recorder(QObject *parent = 0);

    Q_INVOKABLE void startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE void pauseRecording();
    Q_INVOKABLE void resumeRecording();

    Q_INVOKABLE bool deleteRecordFile(const QString &fileName);
    Q_INVOKABLE bool renameRecordFile(const QString &fileName, const QString &newFileName);

    void setMicrophoneVolume(const double &microphoneVolume);
    void setInputDevice(const QString audioInput);

    QString filePath() const;
    QString recordTime() const;
    bool running() const;
    double volumeLevel() const;

private:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QMediaRecorder *m_audioRecorder;
    QMediaCaptureSession *m_captureSession;
    QAudioInput *m_audioInput;
#else
    QAudioRecorder *m_audioRecorder;
    QAudioProbe *m_audioProbe;
#endif

    QString m_filePath;
    QString m_recordTime;
    double m_volumeLevel;

    void setRecordTime(const QString &recordTime);
    void setVolumeLevel(const double &volumeLevel);

private slots:
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    void onAudioBufferProbed(const QAudioBuffer& audioBuffer);
#endif
    void onDurationChanged(const qint64& duration);
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    void onStateChanged(const QMediaRecorder::RecorderState &state);
#else
    void onStateChanged(const QMediaRecorder::State &state);
#endif

signals:
    void runningChanged();
    void recordTimeChanged();
    void volumeLevelChanged();
};

#endif // RECORDER_H
