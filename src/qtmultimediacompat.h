#ifndef QTMULTIMEDIACOMPAT_H
#define QTMULTIMEDIACOMPAT_H

#include <QtGlobal>
#include <QAudio>
#include <QAudioFormat>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QAudioDevice>
#include <QAudioInput>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QAudioSink>
#include <QAudioSource>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaFormat>
#include <QMediaRecorder>

using GuitarToolsAudioDevice = QAudioDevice;
using GuitarToolsAudioInputStream = QAudioSource;
using GuitarToolsAudioOutputStream = QAudioSink;

inline QString guitarToolsAudioDeviceName(const GuitarToolsAudioDevice &device)
{
    return device.description();
}

inline QList<GuitarToolsAudioDevice> guitarToolsAudioInputDevices()
{
    return QMediaDevices::audioInputs();
}

inline GuitarToolsAudioDevice guitarToolsDefaultAudioInputDevice()
{
    return QMediaDevices::defaultAudioInput();
}

inline GuitarToolsAudioDevice guitarToolsDefaultAudioOutputDevice()
{
    return QMediaDevices::defaultAudioOutput();
}

inline QAudioFormat guitarToolsCreateMono16AudioFormat(int sampleRate)
{
    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    return format;
}

inline int guitarToolsBytesPerSample(const QAudioFormat &format)
{
    return format.bytesPerSample();
}

inline int guitarToolsBytesPerFrame(const QAudioFormat &format)
{
    return format.bytesPerFrame();
}

inline QAudioFormat guitarToolsSupportedAudioOutputFormat(const GuitarToolsAudioDevice &device, const QAudioFormat &requestedFormat)
{
    if (device.isFormatSupported(requestedFormat)) {
        return requestedFormat;
    }

    return device.preferredFormat();
}
#else
#include <QAudioDeviceInfo>
#include <QAudioEncoderSettings>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QMediaPlayer>

using GuitarToolsAudioDevice = QAudioDeviceInfo;
using GuitarToolsAudioInputStream = QAudioInput;
using GuitarToolsAudioOutputStream = QAudioOutput;

inline QString guitarToolsAudioDeviceName(const GuitarToolsAudioDevice &device)
{
    return device.deviceName();
}

inline QList<GuitarToolsAudioDevice> guitarToolsAudioInputDevices()
{
    return QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
}

inline GuitarToolsAudioDevice guitarToolsDefaultAudioInputDevice()
{
    return QAudioDeviceInfo::defaultInputDevice();
}

inline GuitarToolsAudioDevice guitarToolsDefaultAudioOutputDevice()
{
    return QAudioDeviceInfo::defaultOutputDevice();
}

inline QAudioFormat guitarToolsCreateMono16AudioFormat(int sampleRate)
{
    QAudioFormat format;
    format.setSampleRate(sampleRate);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    format.setChannelCount(1);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    return format;
}

inline int guitarToolsBytesPerSample(const QAudioFormat &format)
{
    return format.sampleSize() / 8;
}

inline int guitarToolsBytesPerFrame(const QAudioFormat &format)
{
    return format.channelCount() * guitarToolsBytesPerSample(format);
}

inline QAudioFormat guitarToolsSupportedAudioOutputFormat(const GuitarToolsAudioDevice &device, const QAudioFormat &requestedFormat)
{
    return device.nearestFormat(requestedFormat);
}
#endif

#endif // QTMULTIMEDIACOMPAT_H
