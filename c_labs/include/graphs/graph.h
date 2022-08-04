# ifndef __H__GRAPHS__
# define __H__GRAPHS__

    #include "hashtable/hashset.h"
    #include <stdarg.h>

    typedef enum 
    {
        STATUS_SUCCESS = 1,
        STATUS_FAILURE = 0
    }
    RCG_Create_Status_T;


    /* STRUCT: struct __RPaG_Node__ (TYPEDEF: VerticeNode)
    * --------------------------------------------------
    * > Represents a so called Relevant Page Graph Node
    * > It is more correct to call RPaG as:
    * >    Relevant Category Graph
    * > as we deal with categories in this case, but the conception is the same.
    * --------------------------------------------------
    * @attr { char * } name
    *      is the name of the graph vertice (Node)
    * -
    * @attr { HashSet * } adjacents
    *      the special type of so-called hashset
    *      represents the Hash dictionary which items are not mutable
    *      it will contain a set of vertices which are adjacent to given one.
    * --------------------------------------------------
    */
    typedef struct __RCaG_Node__
    {
        char * name;
        HashSet * adjacents;
    }
    RCG_Vertice;




    /* STRUCT: struct __RPaG__ (TYPEDEF: RCaGraph)
    * --------------------------------------------------
    * > Represents a so called Relevant Page Graph Node
    * > It is more correct to call RPaG as:
    * >    Relevant Category Graph
    * > as we deal with categories in this case, but the conception is the same.
    * --------------------------------------------------
    * @attr { char * } name
    *      is the name of the graph vertice (Node)
    * -
    * @attr { HashSet * } adjacents
    *      the special type of so-called hashset
    *      represents the Hash dictionary which items are not mutable
    *      it will contain a set of vertices which are adjacent to given one.
    * --------------------------------------------------
    */
    typedef struct __RCaG__
    {
        char * name;
        RCG_Vertice * root;
        int vertices_count;
        
        void (*__build_random_tree)(struct __RCaG__ *);
        SetIterator * __iter__;
    }
    RCGraph;



    struct __newgraph_params__
    {
        int __sentinel: 1;
        RCGraph ** graph_ptr;
        int ;

        int create_random_vertices: 1;

        char * name;
    };
    RCG_Create_Status_T initRCGraph( struct __newgraph_params__ * args  );


    /* So we can pass named (keyword) arguments to the function
     * =============================================*/
    # define initRCGraph(...) _initRCGraph( &(struct __newgraph_params__ ) \
        { .__sentinel=0, __VA_ARGS__ })
    

# endif /* __H__GRAPHS__ */