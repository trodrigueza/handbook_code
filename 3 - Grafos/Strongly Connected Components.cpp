// Joel lo entiende.
// Strongly connected Components----------------------------------------------------------
vector<vector<int>> get_scc( const vector<vector<int>>& g, vector<int>& scc_id ) {
    int n = g.size(), timer = 0;
    vector<int> dfn( n ), low( n ), stk, in_stk( n );
    vector<vector<int>> sccs;
    
    scc_id.assign( n , -1 );
    
    auto dfs = [&](auto& self, int u) -> void {
        dfn[ u ] = low[ u ] = ++timer;
        stk.push_back( u );
        in_stk[ u ] = 1;
        
        for ( int v : g[ u ] ) {
            if ( !dfn[ v ] ) self( self , v ) , low[ u ] = min( low[ u ] , low[ v ] );
            else if ( in_stk[ v ] ) low[ u ] = min( low[ u ] , dfn[ v ] );
        }
        
        if ( low[ u ] == dfn[ u ] ) {
            sccs.push_back( {} );
            for ( int v = -1; v != u; ) {
                v = stk.back(); stk.pop_back();
                in_stk[ v ] = 0;
                sccs.back().push_back( v );
                
                scc_id[ v ] = sccs.size() - 1; 
            }
        }
    };
    
    for ( int i = 1; i < n; i++ ) if ( !dfn[ i ] ) dfs( dfs , i );

    return sccs;
}
