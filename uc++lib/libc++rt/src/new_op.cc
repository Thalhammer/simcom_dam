// Support routines for the -*- C++ -*- dynamic memory management.

// Copyright (C) 1997-2019 Free Software Foundation, Inc.
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

#include <bits/c++config.h>
#include <stdlib.h>
#include <bits/exception_defines.h>
#include "new.h"

using std::new_handler;
using std::bad_alloc;

extern "C" void *malloc(size_t);

_GLIBCXX_WEAK_DEFINITION void *
operator new (size_t sz) _GLIBCXX_THROW (std::bad_alloc)
{
  void *p;

  /* malloc (0) is unpredictable; avoid it.  */
  if (__builtin_expect (sz == 0, false))
    sz = 1;

  while ((p = malloc (sz)) == 0)
    {
      new_handler handler = std::get_new_handler ();
      if (! handler)
	_GLIBCXX_THROW_OR_ABORT(bad_alloc());
      handler ();
    }

  return p;
}

extern "C" void *aligned_alloc(size_t al, size_t size) __attribute__((weak));

constexpr bool
__ispow2(size_t x) noexcept
{
  return !(x == 0) && !(x & (x - 1));
}

_GLIBCXX_WEAK_DEFINITION void *
operator new(size_t sz, std::align_val_t al)
{
  if(aligned_alloc == NULL)
    _GLIBCXX_THROW_OR_ABORT(bad_alloc());

  std::size_t align = (size_t)al;

  /* Alignment must be a power of two.  */
  /* XXX This should be checked by the compiler (PR 86878).  */
  if (__builtin_expect(!__ispow2(align), false))
    _GLIBCXX_THROW_OR_ABORT(bad_alloc());

  /* malloc (0) is unpredictable; avoid it.  */
  if (__builtin_expect(sz == 0, false))
    sz = 1;

  void *p;

  while ((p = aligned_alloc(align, sz)) == nullptr)
  {
    new_handler handler = std::get_new_handler();
    if (!handler)
      _GLIBCXX_THROW_OR_ABORT(bad_alloc());
    handler();
  }

  return p;
}

_GLIBCXX_WEAK_DEFINITION void*
operator new(size_t sz, std::align_val_t al, const std::nothrow_t&)
  noexcept
{
  __try
    {
      return operator new(sz, al);
    }
  __catch(...)
    {
      return nullptr;
    }
}

_GLIBCXX_WEAK_DEFINITION void *
operator new (size_t sz, const std::nothrow_t&) noexcept
{
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 206. operator new(size_t, nothrow) may become unlinked to ordinary
  // operator new if ordinary version replaced
  __try
    {
      return ::operator new(sz);
    }
  __catch (...)
    {
      return nullptr;
    }
}

_GLIBCXX_WEAK_DEFINITION void*
operator new[] (size_t sz) _GLIBCXX_THROW (std::bad_alloc)
{
  return ::operator new(sz);
}

_GLIBCXX_WEAK_DEFINITION void*
operator new[] (size_t sz, std::align_val_t al)
{
  return ::operator new(sz, al);
}

_GLIBCXX_WEAK_DEFINITION void*
operator new[] (size_t sz, std::align_val_t al, const std::nothrow_t&)
  noexcept
{
  __try
    {
      return ::operator new[](sz, al);
    }
  __catch(...)
    {
      return nullptr;
    }
}

_GLIBCXX_WEAK_DEFINITION void*
operator new[] (size_t sz, const std::nothrow_t&) noexcept
{
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 206. operator new(size_t, nothrow) may become unlinked to ordinary
  // operator new if ordinary version replaced
  __try
    {
      return ::operator new[](sz);
    }
  __catch (...)
    {
      return nullptr;
    }
}
