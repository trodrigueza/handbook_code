// -----------------------------

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int, int>
#define ff first
#define ss second
#define all( v ) v.begin() , v.end()
#define ld long double

const int oo = 1e18;

const int MAXN = 1e6+1;
const int MAXK = 26;

int dp[ MAXN ][ MAXK ];
int S[ MAXN ];
vector<int> v;
int n, k;

// se usa [ l , r ] intervalo cerrado.
int cost( int l , int r )
{
    // esto permite el grupo vacío.
    if ( l > r ) return 0;
    int m = ( l+r ) / 2;
    int leftCnt  = m-l;
    int leftSum  = S[ m-1 ] - S[ (l-1) ];
    int rightCnt = r-m;
    int rightSum = S[ r ]-S[ m ];
    return ( v[ m ]*leftCnt - leftSum ) + ( rightSum - v[ m ]*rightCnt );
}

// l -> cantidad de grupos actual. lo y hi rango de elementos a asignar ahora.
// optlo opthi -> donde puede estar la respuesta.
void compute( int l , int lo , int hi , int optlo , int opthi )
{
    if ( lo > hi ) return;
    int mid = ( lo+hi ) / 2;
    pii best = { oo , -1 };

    // si se permiten grupos vacios entonces j no va hasta mid-1 sino hasta mid
    for ( int j = optlo; j <= min( mid-1 , opthi ); j++ ) {
        int val = dp[ j ][ l-1 ] + cost( j+1 , mid );
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
    v.resize( n+1 );

    // se considera 1-indexado.
    for ( int i = 1; i <= n; i++ ) cin >> v[ i ];

    S[ 0 ] = 0;
    for ( int i = 1; i <= n; i++ ) S[ i ] = S[ i-1 ] + v[ i ];

    // dp[ i ][ j ] mejor costo para asignar i elementos en j grupos
    for ( int l = 0; l <= k; l++ ) dp[ 0 ][ l ] = 0;
    for ( int i = 1; i <= n; i++ ) dp[ i ][ 0 ] = oo;
    // Permite bloques vacios.
    // for ( int l = 1; l <= k; l++ ) compute( l , 1 , n , 0 , n-1 );
    
    // usa exactamente k grupos.
    for ( int l = 1; l <= k; l++ ) compute( l , l , n , l-1 , n-1 );

    cout << dp[ n ][ k ] << '\n';
}
