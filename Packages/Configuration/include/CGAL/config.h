// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : 
// release_date  : 
//
// file          : include/CGAL/config.h
// package       : Configuration
// maintainer    : Geert-Jan Giezeman <geert@cs.uu.nl>
// source        :
// revision      : $Revision$
// revision_date : $Date$
// author(s)     : Wieger Wesselink <wieger@cs.ruu.nl>
//                 Michael Hoffmann
//
// coordinator   : Utrecht University
//
// ======================================================================

#ifndef CGAL_CONFIG_H
#define CGAL_CONFIG_H

#define CGAL_VERSION 2.4-I-65
#define CGAL_VERSION_NR 1002004065


//----------------------------------------------------------------------//
//             STLport fix for MSVC
//----------------------------------------------------------------------//


#if defined( _MSC_VER) && (_MSC_VER <=1300)
#   if ! defined(__INTEL_COMPILER)
#     define CGAL_LIMITED_ITERATOR_TRAITS_SUPPORT 1
#   endif
#else
#   define CGAL_DEFINE_ITERATOR_TRAITS_POINTER_SPEC(a)
#endif // _MSC_VER


//----------------------------------------------------------------------//
//             include platform specific workaround flags (CGAL_CFG_...)
//----------------------------------------------------------------------//

#include <CGAL/compiler_config.h>

//----------------------------------------------------------------------//
//             do some post processing for the flags
//----------------------------------------------------------------------//


// Used to depend on config macros.
#define CGAL_TYPENAME_MSVC_NULL typename
#define CGAL_TEMPLATE_NULL      template <>

#ifdef CGAL_CFG_NO_NAMESPACE
#  define CGAL_USING_NAMESPACE_STD
#  define CGAL_STD
#  define CGAL std
#else
#  define CGAL_USING_NAMESPACE_STD using namespace std;
#  define CGAL_STD std
#  ifndef CGAL_USE_NAMESPACE
#    define CGAL_USE_NAMESPACE 1
#  endif
#endif

#if CGAL_USE_NAMESPACE
#  define CGAL_BEGIN_NAMESPACE namespace CGAL {
#  define CGAL_END_NAMESPACE }
#else
#  define CGAL_BEGIN_NAMESPACE
#  define CGAL_END_NAMESPACE
#endif

#ifdef CGAL_CFG_VC7_PRIVATE_TYPE_BUG
#  define CGAL_VC7_BUG_PROTECTED protected:
#else
#  define CGAL_VC7_BUG_PROTECTED
#endif

#ifdef CGAL_CFG_MATCHING_BUG_2
#   define CGAL_MSVC_DUMMY_ARGUMENT , int dummy=1
#else
#   define CGAL_MSVC_DUMMY_ARGUMENT
#endif

#ifdef CGAL_CFG_NO_TEMPLATE_FRIEND_DISTINCTION
#  define CGAL_NULL_TMPL_ARGS
#else
#  define CGAL_NULL_TMPL_ARGS <>
#endif

#ifdef CGAL_CFG_NO_STDC_NAMESPACE
#  define CGAL_CLIB_STD
#else
#  define CGAL_CLIB_STD std
#endif

#ifndef CGAL_CFG_NO_LONG_LONG
#  define CGAL_USE_LONG_LONG
#endif

//----------------------------------------------------------------------//
//             include separate workaround files
//----------------------------------------------------------------------//

#ifdef _MSC_VER
#  include <CGAL/MSVC_standard_header_fixes.h>
#endif
#if defined(__BORLANDC__) && __BORLANDC__ > 0x520
#include <CGAL/Borland_fixes.h>
#endif
#if defined(__sun) && defined(__SUNPRO_CC)
#include <CGAL/Sun_fixes.h>
#endif

//--------------------------------------------------------------------//
// This addresses a bug in VC++ 7.0 that (re)defines min(a, b)
// and max(a, b) in windows.h and windef.h 
//-------------------------------------------------------------------//

#ifdef _MSC_VER
#  define NOMINMAX 1
#endif

//-----------------------------------------------------------------------//
// the MSVC 6.0 and 7.0 compilers cannot deal with function overloading
// very well, so we have to use specific templating here with the CGAL
// Polyhedron_3 type in its two different forms (one that is swallowed by
// MSVC6 and the other by MSVC 7.0). 
//----------------------------------------------------------------------//

#if defined(_MSC_VER) && ! defined(__INTEL_COMPILER) && (_MSC_VER < 1310)
#  define CGAL_CFG_FUNCTION_OVERLOAD_BUG
#endif

#endif // CGAL_CONFIG_H
