// Copyright (c) 2006 Fernando Luis Cacciola Carballal. All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_SET_NO_CACHE_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_SET_NO_CACHE_H

#include <CGAL/Surface_mesh_simplification/Detail/Common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/No_cache.h>

CGAL_BEGIN_NAMESPACE

namespace Surface_mesh_simplification
{

template<class ECM_>    
class Set_no_cache
{
public:

  typedef ECM_ ECM ;

  typedef typename boost::graph_traits<ECM>::edge_descriptor edge_descriptor ;
  
  typedef No_cache Cache ;
  
  typedef void CostParams ;
  typedef void PlacementParams ;
  
public :

  void operator() ( Cache& aCache          
                  , edge_descriptor const&  
                  , ECM&                    
                  , CostParams const*       
                  , PlacementParams const* 
                  ) const 
  {
    aCache = Cache();
  }                         
  
};    

} // namespace Surface_mesh_simplification


CGAL_END_NAMESPACE

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_SET_NO_CACHE_H
// EOF //
 
