// Boilerplate support routines for -*- C++ -*- dynamic memory management.

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

namespace std
{
  extern "C" void free(void*);
}

#include "new.h"

// The sized deletes are defined in other files.
#pragma GCC diagnostic ignored "-Wsized-deallocation"

_GLIBCXX_WEAK_DEFINITION void
operator delete(void* ptr) noexcept
{
  std::free(ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete(void* ptr, std::align_val_t) noexcept
{
#if _GLIBCXX_HAVE_ALIGNED_ALLOC || _GLIBCXX_HAVE_POSIX_MEMALIGN \
    || _GLIBCXX_HAVE_MEMALIGN
  std::free (ptr);
#elif _GLIBCXX_HAVE__ALIGNED_MALLOC
  _aligned_free (ptr);
#else
  if (ptr)
    std::free (((void **) ptr)[-1]); // See aligned_alloc in new_opa.cc
#endif
}

_GLIBCXX_WEAK_DEFINITION void
operator delete (void *ptr, std::align_val_t al, const std::nothrow_t&) noexcept
{
  ::operator delete (ptr, al);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete (void *ptr, const std::nothrow_t&) noexcept
{
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 206. operator new(size_t, nothrow) may become unlinked to ordinary
  // operator new if ordinary version replaced
  ::operator delete (ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete(void* ptr, size_t) noexcept
{
  ::operator delete (ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete(void* ptr, size_t, std::align_val_t al) noexcept
{
  ::operator delete (ptr, al);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr) _GLIBCXX_USE_NOEXCEPT
{
  ::operator delete (ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr, std::align_val_t al) noexcept
{
  ::operator delete (ptr, al);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr, std::align_val_t al, const std::nothrow_t&) noexcept
{
  ::operator delete[] (ptr, al);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr, const std::nothrow_t&) noexcept
{
  ::operator delete[] (ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr, size_t) noexcept
{
  ::operator delete[] (ptr);
}

_GLIBCXX_WEAK_DEFINITION void
operator delete[] (void *ptr, size_t, std::align_val_t al) noexcept
{
  ::operator delete[] (ptr, al);
}
