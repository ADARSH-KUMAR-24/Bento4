/*****************************************************************
|
|    AP4 - Arrays
|
|    Copyright 2002-2006 Gilles Boccon-Gibod & Julien Boeuf
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
/**
 * @file 
 * @brief Arrays
 */

#ifndef _AP4_ARRAY_H_
#define _AP4_ARRAY_H_

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include <new>
#include "Ap4Types.h"
#include "Ap4Results.h"

/*----------------------------------------------------------------------
|   constants
+---------------------------------------------------------------------*/
const int AP4_ARRAY_INITIAL_COUNT = 64;

/*----------------------------------------------------------------------
|   AP4_Array
+---------------------------------------------------------------------*/
template <typename T> 
class AP4_Array 
{
public:
    // methods
             AP4_Array(): m_AllocatedCount(0), m_ItemCount(0), m_Items(0) {}
             AP4_Array(const T* items, AP4_Size count);
    virtual ~AP4_Array();
    AP4_Cardinal ItemCount() { return m_ItemCount; }
    AP4_Result   Append(const T& item);
    T& operator[](unsigned long idx) { return m_Items[idx]; }
    const T& operator[](unsigned long idx) const { return m_Items[idx]; }
    AP4_Result Clear();
    AP4_Result EnsureCapacity(AP4_Cardinal count);

protected:
    // members
    AP4_Cardinal m_AllocatedCount;
    AP4_Cardinal m_ItemCount;
    T*           m_Items;
};

/*----------------------------------------------------------------------
|   AP4_Array<T>::AP4_Array<T>
+---------------------------------------------------------------------*/
template <typename T>
AP4_Array<T>::AP4_Array(const T* items, AP4_Size count) :
    m_AllocatedCount(count),
    m_ItemCount(count),
    m_Items((T*)::operator new(count*sizeof(T)))
{
    for (unsigned int i=0; i<count; i++) {
        new ((void*)&m_Items[i]) T(items[i]);
    }
}

/*----------------------------------------------------------------------
|   AP4_Array<T>::~AP4_Array<T>
+---------------------------------------------------------------------*/
template <typename T>
AP4_Array<T>::~AP4_Array()
{
    Clear();
    ::operator delete((void*)m_Items);
}

/*----------------------------------------------------------------------
|   NPT_Array<T>::Clear
+---------------------------------------------------------------------*/
template <typename T>
AP4_Result
AP4_Array<T>::Clear()
{
    // destroy all items
    for (AP4_Ordinal i=0; i<m_ItemCount; i++) {
        m_Items[i].~T();
    }

    m_ItemCount = 0;

    return AP4_SUCCESS;
}

/*----------------------------------------------------------------------
|   AP4_Array<T>::EnsureCapacity
+---------------------------------------------------------------------*/
template <typename T>
AP4_Result
AP4_Array<T>::EnsureCapacity(AP4_Cardinal count)
{
    if (count <= m_AllocatedCount) return AP4_SUCCESS;

    unsigned long new_count;
    if (m_AllocatedCount) {
        new_count = 2*m_AllocatedCount;
    } else {
        new_count = AP4_ARRAY_INITIAL_COUNT;
    }

    // (re)allocate the items
    T* new_items = (T*) ::operator new (new_count*sizeof(T));
    if (new_items == NULL) {
        return AP4_ERROR_OUT_OF_MEMORY;
    }
    if (m_ItemCount && m_Items) {
        for (unsigned int i=0; i<m_ItemCount; i++) {
            new ((void*)&new_items[i]) T(m_Items[i]);
            m_Items[i].~T();
        }
        ::operator delete((void*)m_Items);
    }
    m_Items = new_items;
    m_AllocatedCount = new_count;

    return AP4_SUCCESS;
}

/*----------------------------------------------------------------------
|   AP4_Array<T>::Append
+---------------------------------------------------------------------*/
template <typename T>
AP4_Result
AP4_Array<T>::Append(const T& item)
{
    // ensure capacity
    AP4_Result result = EnsureCapacity(m_ItemCount+1);
    if (result != AP4_SUCCESS) return result;
    
    // store the item
    new ((void*)&m_Items[m_ItemCount++]) T(item);

    return AP4_SUCCESS;
}

#endif // _AP4_ARRAY_H_












