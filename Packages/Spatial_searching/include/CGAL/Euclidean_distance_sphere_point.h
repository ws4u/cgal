// ======================================================================
//
// Copyright (c) 2002 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-2.5-I-99 $
// release_date  : $CGAL_Date: 2003/05/23 $
//
// file          : include/CGAL/Euclidean_distance_sphere_point.h
// package       : ASPAS (3.12)
// maintainer    : Hans Tangelder <hanst@cs.uu.nl>
// revision      : 2.4 
// revision_date : 2002/16/08 
// authors       : Hans Tangelder (<hanst@cs.uu.nl>)
// coordinator   : Utrecht University
//
// ======================================================================



#ifndef CGAL_EUCLIDEAN_DISTANCE_SPHERE_POINT_H
#define CGAL_EUCLIDEAN_DISTANCE_SPHERE_POINT_H
#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class GeomTraits, class Sphere>
  class Euclidean_distance_sphere_point {

    public:

    typedef typename GeomTraits::Point Point;
    typedef typename GeomTraits::NT    NT;
    typedef Sphere Query_item;    
    public:

    	// default constructor
    	Euclidean_distance_sphere_point() {}


	inline NT distance(const Sphere& q, const Point& p) const {
                Point c=q.center();
		NT distance = NT(0);
		typename GeomTraits::Construct_cartesian_const_iterator construct_it;
                typename GeomTraits::Cartesian_const_iterator cit = construct_it(c),
		  ce = construct_it(c,1), pit = construct_it(p);
		for(; cit != ce; cit++, pit++){
		  distance += ((*cit)-(*pit))*((*cit)-(*pit));
		}
                distance += -q.squared_radius();
                if (distance<0) distance=NT(0);
        	return distance;
	}


	inline NT min_distance_to_rectangle(const Sphere& q,
					     const Kd_tree_rectangle<GeomTraits>& r) const {
                Point c=q.center();
		NT distance = NT(0);
		typename GeomTraits::Construct_cartesian_const_iterator construct_it;
                typename GeomTraits::Cartesian_const_iterator cit = construct_it(c),
		  ce = construct_it(c,1);
		for (unsigned int i = 0; cit != ce; ++i, ++cit) {
			if ((*cit) < r.min_coord(i))
				distance += 
				(r.min_coord(i)-(*cit))*(r.min_coord(i)-(*cit));
			if ((*cit) > r.max_coord(i))
				distance +=  
				((*cit)-r.max_coord(i))*((*cit)-r.max_coord(i));
			
		};
                distance += -q.squared_radius();
                if (distance<0) distance=NT(0);
		return distance;
	}

	inline NT max_distance_to_rectangle(const Sphere& q,
					      const Kd_tree_rectangle<GeomTraits>& r) const {
                Point c=q.center();
		NT distance=NT(0);
		typename GeomTraits::Construct_cartesian_const_iterator construct_it;
                typename GeomTraits::Cartesian_const_iterator cit = construct_it(c),
		  ce = construct_it(c,1);
		for (unsigned int i = 0; cit != ce; ++i, ++cit) {
				if ((*cit) <= (r.min_coord(i)+r.max_coord(i))/NT(2.0))
					distance += (r.max_coord(i)-(*cit))*(r.max_coord(i)-(*cit));
				else
					distance += ((*cit)-r.min_coord(i))*((*cit)-r.min_coord(i));
		};
		distance += -q.squared_radius();
                if (distance<0) distance=NT(0);
		return distance;
	}



  inline NT transformed_distance(NT d) const {
		return d*d;
	}

  inline NT inverse_of_transformed_distance(NT d) const {
		return CGAL::sqrt(d);
	}

  }; // class Euclidean_distance_sphere_point

} // namespace CGAL
#endif // EUCLIDEAN_DISTANCE_SPHERE_POINT_H

