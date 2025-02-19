#include <bits/stdc++.h>
#include "fraction.hpp"

//#define int              long long
#define vi              vector<int >
#define vii              vector<vector<int > >
#define pii             pair<int , int >
#define R(i , n, a) for(int i = n; i >= a; i--)
#define all(x) begin(x), end(x)
#define debug(x) cout << #x << " = " << x << " "
#define debug2(x, y) cout << #x << " = " << x << " " << #y << " = " << y << " "
#define debug3(x, y, z) cout << #x << " = " << x << " " << #y << " = " << y << " " << #z << " = " << z << " "

using namespace std;
const int MOD = 1e9 + 7;
int n, m;

typedef struct {
    string x;
    int index;
    flo val;
} item;

void print(vector<vector<item>>& arr){
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if(arr[i][j].x == "x") cout << "x" << arr[i][j].index << " ";
            else arr[i][j].val.print(), cout << " ";
        }
        cout << endl;
    }
}


int get(vector<vector<item>> & arr, int row ){
    for (int j = 1; j <= m; j++) {
        if(arr[row][j].val.getNumerator() && arr[0][j].x[0] == 'x'){
            return j;
        }
    }

    return -1;
}

void printMultip(item a, item b){
    if(a.x == "x"){
        b.val = b.val * flo(-1, 1);
        b.val.print();
        cout << " * x" << a.index;
    } else if(b.x == "x"){
        a.val = a.val *  flo(-1, 1);
        a.val.print();
        cout << " * x" << b.index;
    }
}

void printSol(vector<vector<item>>& arr){
    for (int i = 1; i <= n; i++) {
        cout << arr[i][0].x << arr[i][0].index << " = ";
        flo C(0, 1);
        for (int j = 1; j <= m; j++) {
            if(arr[i][j].x == "c" && arr[0][j].x == "c"){
                C = C + (arr[i][j].val * arr[0][j].val);
            } else {
                printMultip(arr[i][j], arr[0][j]);
                cout << " + ";
            }
        }
        C.print();
        cout << endl;
    }
}

vector<flo> getRoots(vector<vector<item> >& arr){
    vector<flo> roots(m+1, flo(0,1)); 

    for(int i = 1; i <= m; i++){
        for (int j = 1; j <= m; j++) {
            roots[i] = roots[i] + (arr[0][j].val * arr[i][j].val);
        }
        cout << roots[i] << " ";
    }
    return roots;
}

void checkPossible(vector<vector<item> >& arr){
  
    for(int i = m + 1; i <= n; i++){
        flo sum(0,1);
        for (int j = 1; j <= m; j++) {
            sum = sum + arr[0][j].val * arr[i][j].val;
        }

        if(sum != arr[i][0].val){
            cout << sum;
            cout << "Shiidgui!!!\n";
            return;
        }
    }

    printSol(arr);

}

void solve(){

    cin >> n >> m;

    vector<vector<item>> arr(n + 1, vector<item>(m + 1, {"c", 0, 0}));
    vector<vector<item>> arr1(n + 1, vector<item>(m + 1, {"c", 0, 0}));


    for (int i = 1; i <= m; i++) {
        arr[0][i].val = flo(1,1);
        arr[0][i].x = "x";
        arr[0][i].index = i;
        
        arr[0][i].val = flo(1,1);
        arr1[0][i].x = "x";
        arr1[0][i].index = i;
    }

    // sul gishuunees ehlen daraalan oruulna uu. c = a1 * x1 + a2 * x2 + ... + an * xn
    // temdeg uurchluh shaardlagagui.

    for(int i = 1; i <= n; i++){
        int el;
        for (int j = 0; j <= m; j++) {
            cin >> el;
            if(j) el = -el;
            flo a(el, 1);
            arr[i][j].val = a;
        }
    }

    print(arr);
    cout << endl;

    bool f = true;

    for (int row = 1; row <= n; row++) {
        int col = get(f ? arr : arr1, row);

        // debug2(row, col) << endl;
        if(col == -1){
            if(row <= m)
                cout << "Shiidgui!!!\n";
            else 
                checkPossible(f ? arr : arr1);
            return;
        }
        flo el = f ? arr[row][col].val : arr1[row][col].val;

        for(int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++){  
                if(i == 0){
                    // x elements
                    if(f) arr1[0][j] = arr[0][j];
                    else arr[0][j] = arr1[0][j];

                } else if (j == 0){
                    // constants
                    if(f) arr1[i][0] = arr[i][0];
                    else arr[i][0] = arr1[i][0];

                } else if((i == row && j == col) || (i == row) || (j == col)){
                    continue;
                } else {
                    // remained other elements
                    if(f) arr1[i][j].val = (el * arr[i][j].val - arr[row][j].val * arr[i][col].val) / (el);
                    else arr[i][j].val = (el * arr1[i][j].val - arr1[row][j].val * arr1[i][col].val) / (el);

                }
            }
        }

        // main element
        // if(f) arr1[i][j].val = flo(1,1) / arr[i][j].val;
        // else arr[i][j].val  = flo(1,1) / arr1[i][j].val;


        //  else if(i == row){
        //             // main row elements
        //             if(f) arr1[i][j].val =  arr[i][j].val / el;
        //             else arr[i][j].val = arr1[i][j].val / el;

        //         } else if(j == col){
        //             // main column elements
        //             if(f) arr1[i][j].val = arr[i][j].val / (el * flo(-1, 1));
        //             else arr[i][j].val = arr1[i][j].val / (el * flo(-1, 1));

        //         }

        arr[row][0] = arr1[0][col];
        arr[0][col] = arr1[row][0];
        arr[0][col].val = (arr[0][col].val * flo(-1, 1));

        print(arr);
        cout << endl;
        f = !f;
    }

    printSol(f ? arr : arr1);

}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--) {
        cout << "\n ======> Shine bodlogo. \n\n";
        solve();
    }

}