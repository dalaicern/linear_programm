#ifndef JORDAN_2
#define JORDAN_2

#include "item.hpp"

class jordan2{
private:
    int n, m;
public: 
    jordan2(int equation, int variables){
        n = equation;
        m = variables;
    }

    void print(vector<vector<item>>& arr){
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if(arr[i][j].x == "x") cout << "x" << arr[i][j].index << " ";
                else arr[i][j].val.print(), cout << " ";
            }
            cout << endl;
        }
    }

    int get_column(vector<vector<item>> & arr, int row ){
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

    void get_matrix(vector<vector<item>>& arr){
        for(int i = 1; i <= n; i++){
            int el;
            for (int j = 0; j <= m; j++) {
                cin >> el;
                if(j) el = -el;
                flo a(el, 1);
                arr[i][j].val = a;
            }
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

    vector<vector<item>> transform(vector<vector<item>>& arr,int row, int col){
        vector<vector<item>> arr1(n + 1, vector<item>(m + 1, {"c", 0, 0}));

        flo el = arr[row][col].val;

        for(int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++){  
                if(i == 0){
                    // x elements
                    arr1[0][j] = arr[0][j];

                } else if (j == 0){
                    // constants
                    arr1[i][0] = arr[i][0];

                } else if(i == row && j == col){
                    // main element
                    arr1[i][j].val = flo(1,1) / arr[i][j].val;

                } else if(i == row){
                    // main row elements
                    arr1[i][j].val =  arr[i][j].val / el;

                } else if(j == col){
                    // main column elements
                    arr1[i][j].val = arr[i][j].val / (el * flo(-1, 1));

                } else {

                    arr1[i][j].val = (el * arr[i][j].val - arr[row][j].val * arr[i][col].val) / (el);
                }
            }
        }

        return arr1;
    }

    void matrix_solver(){
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
        get_matrix(arr);

        print(arr);
        cout << endl;

        bool f = true;

        for (int row = 1; row <= n; row++) {
            int col = get_column(f ? arr : arr1, row);

            // debug2(row, col) << endl;
            if(col == -1){
                if(row <= m){
                    
                    flo C(0, 1);
                    for(int j = 1; j  <= m; j++){
                        if(arr[0][j].x != "x")
                            C = C + (arr[row][j].val * arr[0][j].val);
                    }

                    if(C == arr[row][0].val){
                        cout << "Niitstei\n";
                        printSol(arr);
                    } else {
                        cout << "Niitsgui!!!\n";
                    }
                } else 
                    checkPossible(f ? arr : arr1);
                return;
            }
            
            if(f) arr1 = transform(arr, row, col);
            else arr = transform(arr1, row, col);

            // change x and constant of main element's row, column.
            if(f){
                arr1[row][0] = arr[0][col];
                arr1[0][col] = arr[row][0];
                arr1[0][col].val = (arr1[0][col].val * flo(-1, 1));
            } else {
                arr[row][0] = arr1[0][col];
                arr[0][col] = arr1[row][0];
                arr[0][col].val = (arr[0][col].val * flo(-1, 1));
            }

            print(f ? arr1 : arr);
            cout << endl;
            f = !f;
        }

        printSol(f ? arr : arr1);
    }
};

#endif

