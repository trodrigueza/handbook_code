const int MAXP = 41;
const int MAXN = 1e5;

int up[ MAXP ][ MAXN ];

void calc()
{
    for ( int i = 1; i < MAXP; i++ ) {
        for ( int j = 0; j < MAXN; j++ ) {
            up[ i ][ j ] = up[ i-1 ][ up[ i-1 ][ j ] ];
        }
    }
}

int lca( int a , int b )
{
    if ( depth[ a ] < depth[ b ] ) swap( a , b );
    int diff = depth[ a ]-depth[ b ];
    for ( int i = 0; i < MAXP; i++ ) {
        if ( (diff>>i) & 1 ) a = up[ i ][ a ];
    }

    if ( a == b ) return a;

    for ( int i = MAXP-1; i >= 0; i-- ) {
        if ( up[ i ][ a ] == up[ i ][ b ] ) continue;
        a = up[ i ][ a ];
        b = up[ i ][ b ];
    }
    a = up[ 0 ][ a ];
    return a;
}
