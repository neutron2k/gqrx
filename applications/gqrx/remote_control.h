/* -*- c++ -*- */
/*
 * Gqrx SDR: Software defined radio receiver powered by GNU Radio and Qt
 *           http://gqrx.dk/
 *
 * Copyright 2013 Alexandru Csete OZ9AEC.
 *
 * Gqrx is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * Gqrx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Gqrx; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef REMOTE_CONTROL_H
#define REMOTE_CONTROL_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>


/*! \brief Simple TCP server for remote control.
 *
 * The TCP interface is compatible with the hamlib rigtctld so that applications
 * gpredict can be used with gqrx without any modifications.
 *
 * The hamlib rigctld protocol is described in the man page
 * http://hamlib.sourceforge.net/pdf/rigctld.8.pdf
 * but here is a summary.
 *
 *   client:  F 144500000\n       # set frequency in Hz
 *     gqrx:  RPRT 0\n            # 0 means no error
 *
 *   client:  f\n                 # get frequency
 *     gqrx:  144500000\n         # gqrx replies with frequency in Hz
 *
 * We also have some gqrx specific commands:
 *
 *  close: Close connection (useful for interactive telnet sessions).
 *
 *
 * FIXME: The server code is very minimalistic and probably not very robust.
 */
class RemoteControl : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControl(QObject *parent = 0);
    ~RemoteControl();

    void start_server(void);
    void stop_server(void);

    void readSettings(QSettings *settings);
    void saveSettings(QSettings *settings) const;

    void setPort(int port);
    int  getPort(void) const
    {
        return rc_port;
    }

    void setHosts(QStringList hosts);
    QStringList getHosts(void) const
    {
        return rc_allowed_hosts;
    }

public slots:
    void setNewFrequency(qint64 freq);
    void setFilterOffset(qint64 freq);
    void setBandwidth(qint64 bw);
    void setSignalLevel(float level);
    void setMode(int mode);

    //------------------------
    // start new slots

    void setNewPPM(qint64 ppm);

    // end new slots
    //------------------------

signals:
    void newFrequency(qint64 freq);
    void newFilterOffset(qint64 offset);
    void newMode(int mode);

    //------------------------
    // start new signals

    void newGain(QString name, double gain);

    // end new signals
    //------------------------


    void satAosEvent(void); /*! Satellite AOS event received through the socket. */
    void satLosEvent(void); /*! Satellite LOS event received through the socket. */

private slots:
    void acceptConnection();
    void startRead(QSettings *settings);

private:
    QTcpServer  rc_server;         /*!< The active server object. */
    QTcpSocket* rc_socket;         /*!< The active socket object. */

    QStringList rc_allowed_hosts;  /*!< Hosts where we accept connection from. */
    int         rc_port;           /*!< The port we are listening on. */
    
    qint64      rc_freq;
    qint64      rc_filter_offset;
    qint64      bw_half;

    int         rc_mode;           /*!< Current mode. */
    float       signal_level;      /*!< Signal level in dBFS */

    //------------------------
    // start new vars
    // - these are most likely the incorrect data types
    // - I just added them as floats to test the telnet gets
    
    float       rc_gain;           /*!< Gain level */
    qint64       rc_ppm;            /*!< PPM level */
    float       rc_lnb;            /*!< LNB level */
    float       rc_squelch;        /*!< Squelch level */
    float       rc_ro;             /*!< RO level */
    float       rc_audio_gain;     /*!< Audio Gain */
    float       rc_bandwidth;      /*!< Bandwidth level */
    float       rc_fft_size;       /*!< FFT Size */
    float       rc_fft_rate;       /*!< FFT Rate */
    float       rc_fft_zoom;       /*!< FFT Zoom */
    float       rc_usb;            /*!< USB on/off  */
    float       rc_fullscreen;     /*!< Fullscreen on/off */
    float       rc_udp_audio;      /*!< UDP Audio on/off */
    // end new vars
    //------------------------

    void        setNewRemoteFreq(qint64 freq);
    int         modeStrToInt(const char *buffer);
    QString     intToModeStr(int mode);
};

#endif // REMOTE_CONTROL_H
