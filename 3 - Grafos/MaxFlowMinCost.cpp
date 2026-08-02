// Maximum flow Min Cost.
// Joel
struct MCMF {
    struct Edge { int to, cap, cost; };
    vector<Edge> edges;
    vector<vector<int>> g;
    vector<int> dst, pe;
    vector<bool> inq;

    int n;

    MCMF( int n ) : n( n ) , g( n ) {}
    // u -> v
    void add( int u , int v , int cap , int cost ) {
        g[ u ].push_back( (int)edges.size() );
        edges.push_back( { v , cap , cost } );
        g[ v ].push_back( (int)edges.size() );
        edges.push_back( { u , 0 , -cost } );
    }

    pii run( int s , int t ) {
        int flow = 0, cost = 0;
        while ( 1 ) {
            dst.assign( n , oo );
            pe.assign( n , -1 );
            inq.assign( n , 0 );

            dst[ s ] = 0;
            queue<int> q; q.push( s ); inq[ s ] = 1;

            while ( !q.empty() ) {
                int actual = q.front(); q.pop(); inq[ actual ] = 0;
                for ( auto id : g[ actual ] ) {
                    auto& e = edges[ id ];
                    if ( e.cap > 0 and dst[ actual ] + e.cost < dst[ e.to ] ) {
                        dst[ e.to ] = dst[ actual ] + e.cost;
                        pe[ e.to ] = id;
                        if ( !inq[ e.to ] ) q.push( e.to ) , inq[ e.to ] = 1;
                    }
                }
            }
            if ( dst[ t ] == oo ) break;
            int push = oo;

            for ( int v = t; v != s; v = edges[ pe[ v ]^1 ].to ) {
                push = min( push , edges[ pe[ v ] ].cap );
            }
            for ( int v = t; v != s; v = edges[ pe[ v ]^1 ].to ) {
                edges[ pe[ v ] ].cap -= push;
                edges[ pe[ v ]^1 ].cap += push;
            }
            flow += push;
            cost += push*dst[ t ];
        }
        return { flow , cost };
    }

};
