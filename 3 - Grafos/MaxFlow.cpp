// Código tomado handbook
const int MAXN = 10505;

struct Edge { int to , rev , cap; bool used = 0; };

vector<Edge> graph[ MAXN ];
int level[ MAXN ] , it[ MAXN ];

void add_edge( int u , int v , int cap ) 
{
    graph[ u ].push_back( { v , (int)graph[ v ].size() , cap } );
    graph[ v ].push_back( { u , (int)graph[ u ].size() - 1 , 0LL } );
}

// s -> source
bool bfs( int s , int t , int n )
{
    fill( level , level+MAXN , -1 );
    queue<int> q;
    level[ s ] = 0;
    q.push( s );

    while ( !q.empty() ) {
        int v = q.front(); q.pop();
        for ( auto& e : graph[ v ] ) {
            if ( e.cap > 0 && level[ e.to ] == -1 ) {
                level[ e.to ] = level[ v ]+1;
                q.push( e.to );
            }
        }
    }
    return ( level[ t ] != -1 );
}

int dfs( int v , int t , int pushed )
{
    if ( v == t ) return pushed;
    for ( int& i = it[ v ]; i < (int)graph[ v ].size(); i++ ) {
        Edge& e = graph[ v ][ i ];
        if ( e.cap <= 0 or level[ v ] >= level[ e.to ] ) continue;
        int d = dfs( e.to , t , min( pushed , e.cap ) );
        if ( d > 0 ) {
            e.cap -= d; graph[ e.to ][ e.rev ].cap += d; 
            return d;
        }
    }

    return 0;
}

int max_flow( int s , int t , int n )
{
    int flow = 0;
    while ( bfs( s , t , MAXN ) ) {
        fill( it , it+MAXN , 0 );
        int d;
        while ( ( d = dfs( s , t , oo ) ) > 0 ) flow += d;
    }
    return flow;
}

// ------------------------------------------------------------------------
