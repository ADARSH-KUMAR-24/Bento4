/*****************************************************************
|
|    Copyright 2002-2007 Gilles Boccon-Gibod & Julien Boeuf
|
|    $Id$
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
****************************************************************/

package com.axiosys.bento4;

import java.io.IOException;
import java.io.RandomAccessFile;

public class AudioSampleEntry extends MpegSampleEntry {
    private int sampleRate;           
    private int channelCount;
    private int sampleSize;

    protected AudioSampleEntry(int format, int size, RandomAccessFile source, AtomFactory atomFactory) throws IOException, InvalidFormatException {
        super(format, size, source, atomFactory);
    }

    int getSampleRate()   { return (sampleRate>>16)&0xFFFF; }
    int getSampleSize()   { return sampleSize;     }
    int getChannelCount() { return channelCount;   }

    protected void readFields(RandomAccessFile source) throws IOException {
        super.readFields(source);

        source.skipBytes(8);
        channelCount = source.readUnsignedShort();
        sampleSize = source.readUnsignedShort();
        source.skipBytes(4);
        sampleRate = source.readInt();
    }
    
    public String toString(String indentation) {
        StringBuffer result = new StringBuffer();
        result.append(indentation+"[" + typeString(type) + "] size=" + getHeaderSize() + "+" + getPayloadSize());
        result.append("\n" + indentation + "  sample_rate   = " + getSampleRate());
        result.append("\n" + indentation + "  sample_size   = " + sampleSize);
        result.append("\n" + indentation + "  channel_count = " + channelCount);
        for (int i=0; i<children.size(); i++) {
            result.append("\n");
            result.append(((Atom)children.get(i)).toString(indentation+"  "));
        }
        
        return result.toString();  
    }
}
