/* =================================================
 * This file is part of the TTK Music Player qmmp plugin project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#ifndef DECODER_ALAC_H
#define DECODER_ALAC_H

#include <qmmp/decoder.h>

class ALACHelper;

class DecoderALAC : public Decoder
{
public:
    DecoderALAC(const QString &path);
    virtual ~DecoderALAC();

    // Standard Decoder API
    virtual bool initialize() override;
    virtual qint64 totalTime() const override;
    virtual int bitrate() const override;
    virtual qint64 read(unsigned char *data, qint64 maxSize) override;
    virtual void seek(qint64 time) override;

private:
    ALACHelper *m_alac;

};

#endif