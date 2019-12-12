// Support for concurrent programing -*- C++ -*-

// Copyright (C) 2003-2017 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file ext/concurrence.h
 *  This file is a GNU extension to the Standard C++ Library.
 */

#ifndef _CONCURRENCE_H
#define _CONCURRENCE_H 1

#pragma GCC system_header

extern "C" void yield() __attribute__((weak));

namespace __gnu_cxx
{
  class __spinlock_mutex 
  {
  private:
    bool _M_locked;

    __spinlock_mutex(const __spinlock_mutex&);
    __spinlock_mutex& operator=(const __spinlock_mutex&);

  public:
    constexpr __spinlock_mutex()
        : _M_locked(false)
    {}

    void lock()
    {
        // TODO: Try busy loop before yielding on SMP
        while(__atomic_test_and_set(&_M_locked, __ATOMIC_ACQUIRE)) {
            if(yield) yield();
        }
    }
    
    void unlock()
    {
        __atomic_clear(&_M_locked, __ATOMIC_RELEASE);
    }
  };

  using __mutex = __spinlock_mutex;

  /// Scoped lock idiom.
  // Acquire the mutex here with a constructor call, then release with
  // the destructor call in accordance with RAII style.
  class __scoped_lock
  {
  public:
    typedef __mutex __mutex_type;

  private:
    __mutex_type& _M_device;

    __scoped_lock(const __scoped_lock&);
    __scoped_lock& operator=(const __scoped_lock&);

  public:
    explicit __scoped_lock(__mutex_type& __name) : _M_device(__name)
    { _M_device.lock(); }

    ~__scoped_lock() throw()
    { _M_device.unlock(); }
  };
} // namespace

#endif
