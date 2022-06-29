/*
    Sonivox EAS Synthesizer for Qt applications
    Copyright (C) 2016-2022, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "programsettings.h"
#include "mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("LinuxEASSynth");
    QApplication::setApplicationName("GUISynth");
    QApplication::setApplicationVersion(TOSTRING(VERSION));
    QCommandLineParser parser;
    parser.setApplicationDescription("GUI MIDI Synthesizer and Player");
    parser.addVersionOption();
    parser.addHelpOption();
    QCommandLineOption bufferOption(QStringList() << "b" << "buffer","Audio buffer time in milliseconds", "bufer_time", "60");
    parser.addOption(bufferOption);
    QCommandLineOption deviceOption(QStringList() << "d" << "device","Audio Device Name", "device_name", "default");
    parser.addOption(deviceOption);
    parser.addPositionalArgument("file", "MIDI File (*.mid; *.kar)");
    parser.process(app);
    ProgramSettings::instance()->ReadFromNativeStorage();
    if (parser.isSet(bufferOption)) {
        int n = parser.value(bufferOption).toInt();
        if (n > 0)
            ProgramSettings::instance()->setBufferTime(n);
        else {
            fputs("Wrong buffer time.\n", stderr);
            parser.showHelp(1);
        }
    }
    if (parser.isSet(deviceOption)) {
        QString s = parser.value(deviceOption);
        if (!s.isEmpty()) {
            ProgramSettings::instance()->setAudioDeviceName(s);
        } else {
            fputs("Wrong Device Name.\n", stderr);
            parser.showHelp(1);
        }
    }
    MainWindow w;
    QStringList args = parser.positionalArguments();
    if (!args.isEmpty())
        w.readFile(args.first());
    w.show();
    return app.exec();
}
