/*
    Sonivox EAS Synthesizer for Qt applications
    Copyright (C) 2016-2022, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QScopedPointer>
#include <QMainWindow>
#include "synthcontroller.h"

enum PlayerState {
    InitialState,
    EmptyState,
    PlayingState,
    StoppedState
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateState(PlayerState newState);
    void initialize();
    void readFile(const QString &file);
    void listPorts();

protected:
    virtual void showEvent(QShowEvent *ev);
    virtual void closeEvent(QCloseEvent *ev);

private slots:
    void reverbTypeChanged(int index);
    void chorusTypeChanged(int index);
    void reverbChanged(int value);
    void chorusChanged(int value);
    void deviceChanged(int value);
    void subscriptionChanged(int value);
    void bufferSizeChanged(int value);
    void octaveChanged(int value);
    void volumeChanged(int value);
    void songStopped();
    void underrunMessage();
    void stallMessage();

    void openFile();
    void playSong();
    void stopSong();

    void noteOn(const int noteNumber, const int velocity);
    void noteOff(const int noteNumber, const int velocity);
    void showNoteOn(const int noteNumber, const int velocity);
    void showNoteOff(const int noteNumber, const int velocity);
    
private:
    Ui::MainWindow *m_ui;
    QScopedPointer<SynthController> m_synth;
    QString m_songFile;
    PlayerState m_state;
};

#endif // MAINWINDOW_H
