// Steiner tree
// Comp O( ( 3^k * n ) + ( 2^k * n^2 ) )

const int lim = (1LL<<20);
const int MAXN = 100;

int dp[ lim ][ MAXN ];

void solve()
{
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> d( n , vector<int>( n , oo ) );

    for ( int i = 0; i < m; i++ ) {
        int a, b; cin >> a >> b;
        cin >> d[ a ][ b ];
        d[ a ][ a ] = 0;
        d[ b ][ b ] = 0;
        d[ b ][ a ] = d[ a ][ b ];
    }
    vector<int> need( n , -1 );
    int cnt = 0;
    for ( int i = 0; i < k; i++ ) {
        int a; cin >> a;
        need[ a ] = cnt;
        cnt++;
    }

    for (int k = 0; k < n; k++)
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int lim = (1LL<<k);
    for ( int S = 0; S < lim; S++ ) {
        for ( int i = 0; i < n; i++ ) dp[ S ][ i ] = oo;
    }

    for ( int i = 0; i < n; i++ ) {
        dp[ 0 ][ i ] = 0;
        if ( need[ i ] != -1 ) dp[ (1LL<<need[ i ]) ][ i ] = 0;
    }

    for ( int S = 1; S < lim; S++ ) {
        for ( int sub = (sub-1) & S; sub > 0; sub = (sub-1) & S ) {
            int nmask = S ^ sub;
            if ( nmask > sub ) break;
            for ( int i = 0; i < n; i++ ) {
                dp[ S ][ i ] = min( dp[ S ][ i ] , dp[ sub ][ i ] + dp[ nmask ][ i ] );
            }
        }
        for ( int i = 0; i < n; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                if ( dp[ S ][ i ] > dp[ S ][ j ]+d[ i ][ j ] ) {
                    dp[ S ][ i ] = dp[ S ][ j ] + d[ i ][ j ];
                }
            }
        }
    }

    int ans = oo;
    for ( int i = 0; i < n; i++ ) ans = min( ans , dp[ lim-1 ][ i ] );

    cout << ans << '\n';
}
