// -*- C++ -*- std::terminate, std::unexpected and friends.
// Copyright (C) 1994-2019 Free Software Foundation, Inc.
//
// This file is part of GCC.
//
// GCC is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// GCC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include "typeinfo.h"
#include "exception.h"
#include <stdlib.h>
#include "unwind-cxx.h"
#include <bits/exception_defines.h>
#include <bits/atomic_lockfree_defines.h>

static_assert(ATOMIC_POINTER_LOCK_FREE == 2);

using namespace __cxxabiv1;

extern "C" [[noreturn]] void abort();

void
__cxxabiv1::__terminate (std::terminate_handler handler) throw ()
{
  __try 
    {
      handler ();
      abort ();
    } 
  __catch(...) 
    { abort (); }
}

void
std::terminate () throw()
{
  __terminate (get_terminate ());
}

void
__cxxabiv1::__unexpected (std::unexpected_handler handler)
{
  handler();
  std::terminate ();
}

void
std::unexpected ()
{
  __unexpected (get_unexpected ());
}

std::terminate_handler
std::set_terminate (std::terminate_handler func) throw()
{
  if (!func)
    func = abort;

  std::terminate_handler old;
  __atomic_exchange (&__terminate_handler, &func, &old, __ATOMIC_ACQ_REL);
  return old;
}

std::terminate_handler
std::get_terminate () noexcept
{
  std::terminate_handler func;
  __atomic_load (&__terminate_handler, &func, __ATOMIC_ACQUIRE);
  return func;
}

std::unexpected_handler
std::set_unexpected (std::unexpected_handler func) throw()
{
  if (!func)
    func = std::terminate;

  std::unexpected_handler old;
  __atomic_exchange (&__unexpected_handler, &func, &old, __ATOMIC_ACQ_REL);
  return old;
}

std::unexpected_handler
std::get_unexpected () noexcept
{
  std::unexpected_handler func;
  __atomic_load (&__unexpected_handler, &func, __ATOMIC_ACQUIRE);
  return func;
}

/* The current installed user handler.  */
std::unexpected_handler __cxxabiv1::__unexpected_handler = std::terminate;

/* The current installed user handler.  */
std::terminate_handler __cxxabiv1::__terminate_handler = abort;