#ifndef CGAL_APOLLONIUS_GRAPH_HIERARCHY_2_H
#define CGAL_APOLLONIUS_GRAPH_HIERARCHY_2_H

#include <CGAL/Random.h>
#include <map>
#include <CGAL/Triangulation_hierarchy_2.h>

#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_data_structure_2.h>
#include <CGAL/Apollonius_graph_vertex_base_2.h>
#include <CGAL/Apollonius_graph_face_base_2.h>

#include <CGAL/Apollonius_graph_euclidean_traits_wrapper_2.h>

CGAL_BEGIN_NAMESPACE


// parameterization of the  hierarchy
const int ag_hierarchy_2__ratio    = 30;
const int ag_hierarchy_2__minsize  = 20;
const int ag_hierarchy_2__maxlevel = 5;
// maximal number of points is 30^5 = 24 millions !

template < class Gt, bool StoreHidden = true,
  class Agds = Apollonius_graph_data_structure_2<
    Triangulation_hierarchy_vertex_base_2<
       Apollonius_graph_vertex_base_2<Gt,StoreHidden> >,
    Apollonius_graph_face_base_2<Gt> > >
class Apollonius_graph_hierarchy_2
  : public Apollonius_graph_2< Gt, StoreHidden, Agds >
{
private:
  typedef Apollonius_graph_2<Gt,StoreHidden,Agds> Apollonius_graph_base;
  typedef Apollonius_graph_base                   Ag_base;

  typedef typename Ag_base::Vertex                Vertex;
  typedef typename Ag_base::Weighted_point_list   Weighted_point_list;

public:
  typedef Agds                         Data_structure;
  typedef Gt                           Geom_traits;
  typedef typename Gt::Weighted_point  Weighted_point;
  typedef typename Gt::Bare_point      Point;
  typedef typename Gt::Site            Site;
  typedef typename Gt::Weight          Weight;

  typedef typename Ag_base::Vertex_handle    Vertex_handle;
  typedef typename Ag_base::Face_handle      Face_handle;
  typedef typename Ag_base::Edge             Edge;

  typedef typename Ag_base::Face_circulator       Face_circulator;
  typedef typename Ag_base::Edge_circulator       Edge_circulator;
  typedef typename Ag_base::Vertex_circulator     Vertex_circulator;

  typedef typename Ag_base::All_faces_iterator    All_faces_iterator;
  typedef typename Ag_base::Finite_faces_iterator Finite_faces_iterator;

  typedef typename Ag_base::All_vertices_iterator All_vertices_iterator;
  typedef typename Ag_base::Finite_vertices_iterator 
                                                     Finite_vertices_iterator;

  typedef typename Ag_base::All_edges_iterator    All_edges_iterator;
  typedef typename Ag_base::Finite_edges_iterator Finite_edges_iterator;

  //  typedef Finite_vertices_iterator   Vertex_iterator;
  //  typedef Finite_faces_iterator      Face_iterator;
  //  typedef Finite_edges_iterator      Edge_iterator;

protected:
  // some local types
  typedef typename Ag_base::Vertex_base       Vertex_base;

public:
  // CREATION
  //---------
  Apollonius_graph_hierarchy_2
  (const Geom_traits& gt = Geom_traits());

  template<class Input_iterator>
  Apollonius_graph_hierarchy_2(Input_iterator first,
			       Input_iterator beyond,
			       const Geom_traits& gt = Geom_traits())
    : Apollonius_graph_hierarchy_2(gt)
  {
    insert(first, beyond);
  }

  Apollonius_graph_hierarchy_2
  (const Apollonius_graph_hierarchy_2& agh);

  Apollonius_graph_hierarchy_2&
  operator=(const Apollonius_graph_hierarchy_2& agh);

  ~Apollonius_graph_hierarchy_2();

public:
  // INSERTION
  //----------
  template < class Input_iterator >
  void insert(Input_iterator first, Input_iterator beyond)
  {
    // copy the sites to a local container
    typename Apollonius_graph_base::Weighted_point_list wp_list;
    for (Input_iterator it = first; it != beyond; ++it) {
      wp_list.push_back(*it);
    }

    // sort by decreasing weight
    typename Apollonius_graph_base::Weighted_point_less_than_comparator
      less_than(geom_traits());
    std::sort(wp_list.begin(), wp_list.end(), less_than);

    // now insert
    typename Apollonius_graph_base::Weighted_point_list_iterator lit;
    for (lit = wp_list.begin(); lit != wp_list.end(); ++lit) {
      insert(*lit);
    }

    // clear the local container
    wp_list.clear();
  }

  Vertex_handle insert(const Weighted_point& p);
  inline Vertex_handle insert(const Weighted_point& p,
		       Vertex_handle vnear) {
    return insert(p);
  }

public:
  // REMOVAL
  //--------
  void remove(Vertex_handle v);

public:
  // NEAREST NEIGHBOR LOCATION
  //--------------------------
public:
  Vertex_handle nearest_neighbor(const Point& p) const;
  inline Vertex_handle nearest_neighbor(const Point& p,
					Vertex_handle vnear) const {
    return nearest_neighbor(p);
  }

public:
  // VALIDITY CHECK
  //---------------
  bool is_valid(bool verbose = false, int level = 1) const;

public:
  // MISCELLANEOUS
  //--------------
  void clear();
  void swap(Apollonius_graph_hierarchy_2& agh);

private:
  // private methods
  void
  nearest_neighbor(const Point& p,
		   Vertex_handle vnear[ag_hierarchy_2__maxlevel]) const; 

  int random_level();

  void copy(const Apollonius_graph_hierarchy_2 &agh);

private:
  // class variables
  // here is the stack of graphs which form the hierarchy
  Apollonius_graph_base*   hierarchy[ag_hierarchy_2__maxlevel];
  Random random; // random generator
};

CGAL_END_NAMESPACE

#include <CGAL/Apollonius_graph_hierarchy_2.C>

#endif // CGAL_APOLLONIUS_GRAPH_HIERARCHY_2_H
