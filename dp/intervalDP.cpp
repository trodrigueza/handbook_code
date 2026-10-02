const int MAXN = 1000;

bool dp[ MAXN ][ MAXN ];

void solve()
{
    string str; cin >> str;
    int n = (int)str.size();

    memset( dp , 0 , sizeof dp );

    for ( int i = 0; i < n-2; i++ ) {
        if ( str[ i ] != str[ i+1 ] and 
                str[ i+1 ] != str[ i+2 ] and str[ i ] != str[ i+2 ] ) {
            dp[ i ][ i+2 ] = 1;
        }
    }

    for ( int len = 3; len <= n; len += 3 ) {
        for ( int l = 0; l+len-1 < n; l++ ) {
            int r = l+len-1;
            for ( int k = l + 2; k < r; k += 3 ) {
                dp[ l ][ r ] |=  dp[ l ][ k ] && dp[ k+1 ][ r ] ;
            }
            for ( int mid = l+1; mid < r; mid++ ) {
                bool left = ( mid-1 < l+1 ? 1 : dp[ l+1 ][ mid-1 ] );
                bool actual = ( str[ l ] != str[ mid ] and str[ mid ] != str[ r ] and str[ l ] != str[ r ] );
                bool right = ( mid+1 > r-1 ? 1 : dp[ mid+1 ][ r-1 ] );
                dp[ l ][ r ] |=  left && actual && right;
            }
        }
    }

    if ( dp[ 0 ][ n-1 ] ) {
        cout << "S\n";
        return;
    }
    cout << "N\n";
}

