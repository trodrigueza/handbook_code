// Código handbook -------------------------------------------------------------------
// 0 indexed Segment, remember to set the default value to return in case
// of not range needed when query
struct Node {
    int x;
};

int n;
Node sgt[800000];
vector<Node> val;
vector<Node> lazy;

Node merge(const Node& x, const Node& y) {
    Node ans = { min( x.x , y.x ) };
    return ans;
}

void build(int node = 1, int l = 0, int r = n - 1) {
    if (l == r) sgt[ node ] = val[ l ];
    else {
        int mid = l + ( r-l ) / 2;
        build( node*2 , l , mid );
        build( node*2+1 , mid+1 , r );
        sgt[ node ] = merge( sgt[ node*2 ] , sgt[ node*2+1 ] );
    }
}

void push( int u )
{
    if ( lazy[ u ].x == 0 ) return;
    lazy[ 2*u ].x += lazy[ u ].x;
    lazy[ 2*u+1 ].x += lazy[ u ].x;
    sgt[ 2*u ].x += lazy[ u ].x;
    sgt[ 2*u+1 ].x += lazy[ u ].x;
    lazy[ u ] = { 0 };
}

Node update(int idx, Node val, int node = 1, int start = 0, int end = n-1) {
    if (start == end) {
        sgt[ node ] = val;
        return sgt[ node ];
    }

    push( node );

    int mid =  start + ( end - start ) / 2;
    if ( start <= idx && idx <= mid ) update( idx , val , 2*node , start , mid );
    else update( idx , val , 2*node+1 , mid+1 , end );
    sgt[ node ] = merge( sgt[ 2*node ] , sgt[ 2*node+1 ] );
    return sgt[ node ];
}

void update_range(int l , int r, Node val, int node = 1, int start = 0, int end = n-1) {
    // l start end r 
    if ( start >= l and end <= r ) {
        sgt[ node ].x += val.x;
        lazy[ node ].x += val.x;
        return;
    }

    push( node );

    int mid =  start + ( end - start ) / 2;

    if ( l <= mid ) update_range( l , r , val , 2*node , start , mid );
    if ( r > mid) update_range( l , r , val , 2*node+1 , mid+1 , end );
    sgt[ node ] = merge( sgt[ 2*node ] , sgt[ 2*node+1 ] );
}

Node query(int a, int b, int node = 1, int l = 0, int r = n - 1) {
    if (l > b || r < a) return Node{ oo };
    if (l >= a && r <= b) return sgt[ node ];
    push( node );
    int mid = (l + r) / 2;
    return merge( query( a , b , node * 2 , l , mid ) , 
            query( a , b , node * 2 + 1 , mid+1 , r ) );
}
// -----------------------------------------------------------------------------------

