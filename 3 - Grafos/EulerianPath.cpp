vector<vector<pii>> g;
vector<int> deg;

const int MAXN = 2e5+1;
bool used[ MAXN ];
int ptr[ MAXN ];

// en grafo no dirigido para encontrar ciclo es todos los vertices pares.
// y al final la respuesta debe tener m+1 vertices.
// para path solo es que el inicio y el final tengan grado impar, solo ellos.
// g[ v ][ i ].ff -> to 
// g[ v ][ i ].ss -> id_edge 
vector<int> euler_cycle( int start )
{
    vector<int> ans;
    stack<int> st;
    st.push( start );
    while ( !st.empty() ) {
        int actual = st.top(); 
        int sz = (int)g[ actual ].size();
        while ( ptr[ actual ] < sz and used[ g[ actual ][ ptr[ actual ] ].ss ]  ) ptr[ actual ]++;
        if ( ptr[ actual ] == sz ) {
            ans.push_back( actual );
            st.pop();
            continue;
        }
        auto [ child , id ] = g[ actual ][ ptr[ actual ] ];
        used[ id ] = 1;
        st.push( child );
    }

    reverse( all( ans ) );
    return ans;
}
