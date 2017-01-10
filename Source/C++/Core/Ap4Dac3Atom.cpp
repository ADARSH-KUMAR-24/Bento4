/*****************************************************************
|
|    AP4 - dac3 Atoms
|
|    Copyright 2002-2008 Axiomatic Systems, LLC
|
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

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Ap4Dac3Atom.h"
#include "Ap4AtomFactory.h"
#include "Ap4Utils.h"
#include "Ap4Types.h"

/*----------------------------------------------------------------------
|   dynamic cast support
+---------------------------------------------------------------------*/
AP4_DEFINE_DYNAMIC_CAST_ANCHOR(AP4_Dac3Atom)

/*----------------------------------------------------------------------
|   AP4_Dac3Atom::Create
+---------------------------------------------------------------------*/
AP4_Dac3Atom* 
AP4_Dac3Atom::Create(AP4_Size size, AP4_ByteStream& stream)
{
    // read the raw bytes in a buffer
    unsigned int payload_size = size-AP4_ATOM_HEADER_SIZE;
    AP4_DataBuffer payload_data(payload_size);
    AP4_Result result = stream.Read(payload_data.UseData(), payload_size);
    if (AP4_FAILED(result)) return NULL;
    
    // check the version
    const AP4_UI08* payload = payload_data.GetData();
    return new AP4_Dac3Atom(size, payload);
}

/*----------------------------------------------------------------------
|   AP4_Dac3Atom::AP4_Dac3Atom
+---------------------------------------------------------------------*/
AP4_Dac3Atom::AP4_Dac3Atom(AP4_UI32 size, const AP4_UI08* payload) :
    AP4_Atom(AP4_ATOM_TYPE_DAC3, size),
    m_Fscod(0),
    m_Bsid(0),
    m_Bsmod(0),
    m_Acmod(0),
    m_Lfeon(0),
    m_BitRateCode(0),
    m_Reserved(0)
{
    // make a copy of our configuration bytes
    unsigned int payload_size = size-AP4_ATOM_HEADER_SIZE;
    m_RawBytes.SetData(payload, payload_size);

    // sanity check
    if (payload_size < 2) return;
    
    // parse the payload
    m_Fscod = (payload[0]>>6) & 0x3;
    m_Bsid = (payload[0]>>1) & 0x1F;
    m_Bsmod = (payload[0]<<2 | payload[1]>>6) & 0x3;
    m_Acmod =  (payload[1]>>3) & 0x7;
    m_Lfeon = (payload[1]>>2) & 0x1;
    m_BitRateCode = (payload[1]<<3 | payload[2]>>5) & 0x1F;
    m_Reserved = payload[2] & 0x1F;

}

/*----------------------------------------------------------------------
|   AP4_Dac3Atom::WriteFields
+---------------------------------------------------------------------*/
AP4_Result
AP4_Dac3Atom::WriteFields(AP4_ByteStream& stream)
{
    return stream.Write(m_RawBytes.GetData(), m_RawBytes.GetDataSize());
}

/*----------------------------------------------------------------------
|   AP4_Dac3Atom::InspectFields
+---------------------------------------------------------------------*/
AP4_Result
AP4_Dac3Atom::InspectFields(AP4_AtomInspector& inspector)
{
    inspector.AddField("fscod", m_Fscod);
    inspector.AddField("bsid", m_Bsid);
    inspector.AddField("bsmod", m_Bsmod);
    inspector.AddField("acmod", m_Acmod);
    inspector.AddField("lfeon", m_Lfeon);
    inspector.AddField("bit_rate_code", m_BitRateCode);

    return AP4_SUCCESS;
}