#ifndef SIMPLEX
#define SIMPLEX

#include "item.hpp"

const flo ZERO(0, 1);
class simplex{
private:
    int n, m;
    int isMax = 0;
    pair<int, int> last_selected;

public: 
    simplex(int equation, int variables){
        n = equation;
        m = variables;
        last_selected.first = -1;
        last_selected.second = -1;
    }

    string cellToString(item &it, int i, int j) {
        ostringstream oss;
        if (it.x == "c") {
            if (i == 0 && j == m){
                oss << it.x;
            }else{
                oss << it.val.getNumerator();
                if(it.val.getDenominator() != 1) oss << "/" << it.val.getDenominator();
            }
        } else {
            if (it.val < ZERO) {
                oss << "-" << it.x << it.index;
            } else {
                oss << it.x << it.index;
            }
        }
        return oss.str();
    }
    
    vector<size_t> computeColumnWidths(const vector<vector<string>>& table) {
        vector<size_t> widths;
        if (table.empty()) return widths;
        widths.resize(table[0].size(), 0);
        for (const auto& row : table) {
            for (size_t j = 0; j < row.size(); j++) {
                widths[j] = max(widths[j], row[j].size());
            }
        }
        return widths;
    }
    
    void printBorder(const vector<size_t>& widths) {
        cout << "+";
        for (auto w : widths) {
            cout << string(w + 2, '-') << "+";
        }
        cout << "\n";
    }
    
    void printTable(const vector<vector<string>>& table) {
        auto widths = computeColumnWidths(table);
        printBorder(widths);
        for (const auto& row : table) {
            cout << "|";
            for (size_t j = 0; j < row.size(); j++) {
                cout << " " << setw(widths[j]) << left << row[j] << " |";
            }
            cout << "\n";
            printBorder(widths);
        }
    }
    
    void print(vector<vector<item>>& arr) {
        vector<vector<string>> table;
        for (int i = 0; i <= n; i++) {
            vector<string> row;
            for (int j = 0; j <= m; j++) {
                if(arr[0][j].index != -1)
                    row.push_back(cellToString(arr[i][j], i, j));
            }
            table.push_back(row);
        }
        printTable(table);
    }

    void printSol(vector<vector<item>>& arr){
        
        // arr[n][m].val = arr[n][m].val;
        for(int i = 1; i < n; i++){
            cout << arr[i][0].x << arr[i][0].index << "=";
            arr[i][m].val.print();
            cout << endl;
        }

        for(int j = 1; j < m; j++){
            cout << arr[0][j].x << arr[0][j].index << "=0\n";
        }
        cout << "Zorilgiin function utga = ";
        arr[n][m].val.print();

    }

    void get_matrix(vector<vector<item>>& arr){
        int y_index = 1;

        for (int i = 1; i < m; i++) {
            arr[0][i].val = flo(-1,1);
            arr[0][i].x = "x";
            arr[0][i].index = i;
        }

        for(int i = 1; i < n; i++){
            string symbol; cin >> symbol;
            cout << symbol;
            if(symbol == "="){
                arr[i][0].x = "c";
                arr[i][0].val = ZERO;
                arr[i][0].index = -1;
            } else {
                arr[i][0].x = "y";
                arr[i][0].val = flo(1,1);
                arr[i][0].index = y_index++;
            }

            int el;
            for (int j = 1; j <= m; j++) {
                cin >> el;
                if(symbol == ">=") el = -el;
                flo a(el, 1);
                arr[i][j].val = a;
            }
        }

        cout << "MAXIMUM(1) | MINIMUM(0): ";
        cin >> isMax;

        cout << "Zorilgiin function ii coef uud oruul: \n";

        arr[n][0].x = "Z";
        for(int j = 1; j <= m; j++){
            int el; cin >> el;
            if(!isMax) el = -el;
            flo a(el, 1);
            arr[n][j].val = a;
        }
    }

    int get_row(vector<vector<item>> & arr, int col, int isPos){
        for (int i = 1; i < n; i++) {
            if(arr[0][col].index == -1)
                continue;
            if(isPos && arr[i][col].val > ZERO) return i;
            else if(!isPos && arr[i][col].val < ZERO) return i;
        }

        return -1;
    }

    int get_col(vector<vector<item>> & arr, int row,  int isPos){
        for (int j = 1; j < m; j++) {
            // cout << n << endl;
            // arr[row][j].val.print();
            // cout << arr[row][j].index<< endl;

            if(arr[0][j].index == -1)
                continue;
            if(isPos && arr[row][j].val > ZERO) return j;
            else if (!isPos && arr[row][j].val < ZERO) return j;
        }

        return -1;
    }

    int get_min_simplex(vector<vector<item>> & arr, int col){
        int min_row = -1;

        for(int i = 1; i < n; i++){
            if(arr[i][col].val == ZERO || (last_selected.first == i && last_selected.second == col))
                continue;

            flo a = arr[i][m].val / arr[i][col].val;

            if((min_row != -1 && a >= ZERO && arr[min_row][m].val / arr[min_row][col].val  > arr[i][m].val / arr[i][col].val)
                || (min_row == -1 && arr[i][m].val / arr[i][col].val >= ZERO)){
                min_row = i;
            }
        }

        if(min_row != -1){
            last_selected.first = min_row;
            last_selected.second = col;
        }
        

        return min_row;
    }

    int get_transform_col(vector<vector<item>> & arr, int row){
        for (int j = 1; j < m; j++) {
            if(arr[row][j].val != ZERO && arr[0][j].x != "c"){
                return j;
            }
        }

        return -1;
    }


    vector<vector<item>> transform(vector<vector<item>>& arr,int row, int col){
        vector<vector<item>> arr1(n + 1, vector<item>(m + 1, {"c", 0, 0}));

        flo el = arr[row][col].val;

        cout << row  << " " << col << endl;
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

        swap(arr1, row, col);

        print(arr1);
        cout << endl;

        return arr1;
    }

    void swap(vector<vector<item>>& arr, int row, int col){
        item temp = arr[row][0];
        arr[row][0] = arr[0][col];
        arr[0][col] = temp;
        arr[0][col].val = (arr[0][col].val * flo(-1, 1));
        arr[row][0].val = (arr[row][0].val * flo(-1, 1));
    }

    void tulguur(vector<vector<item>>& arr){
        cout << "=> Tulguur shiid\n";
        while(true){
            int negative_row = get_row(arr, m, 0);
            if(negative_row < 0){
                cout << "=> onovchtoi shiid ruu shiljiv. \n";
                return;
            }

            int main_col = get_col(arr, negative_row, 0);

            if(main_col < 0){
                cout << "bodlogo duussan deerees zaaglagdaagui niitsgui\n";
                arr[0][0].val = flo(-1 ,1);
                return;
            }

            int min_simplex = get_min_simplex(arr, main_col);

            if(min_simplex == -1){
                cout << "Buhult uusev.\n";
                arr[0][0].val = flo(-1 ,1);
                return;
            }

            // cout  << negative_row << " " << main_col << " " << min_simplex;
            
            arr = transform(arr, min_simplex, main_col);

        }
    }

    void get_tulguur(vector<vector<item> >& arr){
        cout << "chuluut ul medegdegch: \n";
        // cout << n << m;
        for(int j = 1; j < m; j++){
            string var; cin >> var;
            arr[0][j].x = var[0];
            arr[0][j].index = var[1] - '0';
            arr[0][j].val = flo(-1, 1); 
            cout << var << endl;
        }

        cout << "undsen ul medegdegch: \n";
        for(int i = 1; i <= n; i++){
            string var; cin >> var;
            arr[i][0].x = var[0];
            arr[i][0].index = var[1] - '0';
            arr[i][0].val = flo(1, 1);

            if(var[0] == 'F') isMax = var[1] - '0';
            cout << var << endl;
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                int num, denom; cin >> num >> denom;
                flo a(num, denom);
                arr[i][j].val = a;
                arr[i][j].val.print();
            }
            cout << endl;
        }

        print(arr);
    }

    void onovchtoi_shiid(){
        vector<vector<item>> arr(n + 1, vector<item>(m + 1, {"c", 0, 0}));

        // hamgiin ehend >=, <= , = temdgiin ali negiig zaaj ugnu uu.
        // sul gishuunees ehlen daraalan oruulna uu. a1 * x1 + a2 * x2 ... am * xm >= c
        // temdeg uurchluh shaardlagagui.

        // zorilgiin function ii huvid max esvel min. ali bodlogo ve.
        // temdeg oruulalguiger shuud coef ee oruulna.
        // get_matrix(arr);

        // print(arr);
        // cout << endl;
        
        // for(int i = 1; i < n; i++){
        //     if(arr[i][0].x == "c" && arr[i][0].val == ZERO){
        //         int transform_col = get_transform_col(arr, i);
        //         arr = transform(arr, i, transform_col);
        //     }
        // }

        // tulguur(arr);

        get_tulguur(arr);

        // arr  = transform(arr, 2, 1);
        // print(arr);
        // return;

        if(arr[0][0].val < ZERO){
            return;
        }

        while(true){
            int pos_col = get_col(arr, n, !isMax);
            // cout << pos_col;
            if(pos_col < 0){
                printSol(arr);
                return;
            }
            int pos_row = get_row(arr, pos_col, 1);
            if(pos_row < 0){
                cout << "dooroos zaaglagdaagui onovchtoi oldohgui.\n";
                return;
            }
            // cout << pos_col << pos_row << endl;
            int min_simplex = get_min_simplex(arr, pos_col);

            if(min_simplex == -1){
                printSol(arr);
                return;
            }

            arr = transform(arr, min_simplex, pos_col);
        }
    }
};

#endif

