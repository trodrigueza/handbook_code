* Implementacion del algoritmo de Dijkstra para encontrar los caminos mas cortos desde un unico origen en un grafo con pesos no negativos.
Complejidad: O(E log V).

const int MAXN = 1e4+5;

struct Edge {
    int from;
    int to;
    int length;
};

vector<Edge> graph[ MAXN ];

void add_edge( int u , int v , int l )
{
    graph[ u ].push_back( { u , v , l } );
    graph[ v ].push_back( { v , u , l } );
}

vector<int> dijkstra ( int s , int to , int n )
{
    vector<int> dst( n , oo );
    priority_queue< pii , vector<pii> , greater<pii> > pq;
    dst[ s ] = 0;
    pq.push( { 0 , s } );

    while ( !pq.empty() ) {
        pii _ = pq.top(); pq.pop();
        int actual = _.ss;
        if ( _.ff != dst[ actual ] ) continue;
        for ( auto [ _ , v , w ] : graph[ actual ] ) {
            int new_d = dst[ actual ] + w;
            if ( new_d < dst[ v ] ) {
                dst[ v ] = new_d;
                pq.push( { dst[ v ] , v } );
            }
        }
    }
    return dst;
}
