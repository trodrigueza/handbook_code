const int oo = 1e18;

const int MAXN = 1e6+1;
const int MAXK = 26;

int dp[ MAXN ][ MAXK ];
int S[ MAXN ];
vector<int> v;
int n, k; 

int cost( int l , int r )
{
    int m = ( l + r - 1 ) / 2;
    int leftCnt  = m-l;
    int leftSum  = S[ m ] - S[ l ];
    int rightCnt = r-m-1;
    int rightSum = S[ r ]-S[ m+1 ];
    return ( v[ m ]*leftCnt - leftSum ) + ( rightSum - v[ m ]*rightCnt );
}

int go( int i , int l )
{
    if ( i == 0 ) return l == 0 ? 0 : oo;
    if ( l == 0 ) return oo;
    auto& memo = dp[ i ][ l ];
    if ( memo != -1 ) return memo;

    int ans = oo;
    for ( int j = 0; j < i; j++ ) {
        ans = min( ans , go( j , l-1 ) + cost( j , i ) );
    }

    return memo = ans;
}

void solve()
{
    cin >> n >> k;
    v.resize( n );

    for ( int i = 0; i < n; i++ ) cin >> v[ i ];

    S[ 0 ] = 0;
    for ( int i = 1; i <= n; i++ ) S[ i ] = S[ i-1 ] + v[ i-1 ];

    memset( dp , -1 , sizeof dp );

    int ans = go( n , k );
    cout << ans << '\n';
}

// -----------------------------
//
const int oo = 1e18;

const int MAXN = 1e6+1;
const int MAXK = 26;

int dp[ MAXN ][ MAXK ];
int S[ MAXN ];
vector<int> v;
int n, k; 

int cost( int l , int r )
{
    int m = ( l + r - 1 ) / 2;
    int leftCnt  = m-l;
    int leftSum  = S[ m ] - S[ l ];
    int rightCnt = r-m-1;
    int rightSum = S[ r ]-S[ m+1 ];
    return ( v[ m ]*leftCnt - leftSum ) + ( rightSum - v[ m ]*rightCnt );
}

void compute( int l , int lo , int hi , int optlo , int opthi )
{
    if ( lo > hi ) return;
    int mid = ( lo+hi ) / 2;
    pii best = { oo , -1 };

    for ( int j = optlo; j <= min( mid , opthi ); j++ ) {
        int val = dp[ j ][ l-1 ] + cost( j , mid );
        if ( val < best.ff ) best = { val , j };
    }

    dp[ mid ][ l ] = best.ff;
    int opt = best.ss;

    compute( l , lo , mid-1 , optlo , opt );
    compute( l , mid+1 , hi , opt , opthi );
}

void solve()
{
    cin >> n >> k;
    v.resize( n );

    for ( int i = 0; i < n; i++ ) cin >> v[ i ];

    S[ 0 ] = 0;
    for ( int i = 1; i <= n; i++ ) S[ i ] = S[ i-1 ] + v[ i-1 ];

    for ( int l = 0; l <= k; l++ ) dp[ 0 ][ l ] = 0;
    for ( int i = 1; i <= n; i++ ) dp[ i ][ 0 ] = oo;

    for ( int l = 1; l <= k; l++ ) compute( l , 1 , n , 0 , n-1 );

    cout << dp[ n ][ k ] << '\n';
}
