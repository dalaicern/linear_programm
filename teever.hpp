#ifndef TEEVER
#define TEEVER

#include "item.hpp"

const flo ZERO(0, 1);
class teever{
private:
    int n, m;
    int isMax;
    int nuutsiluudel = 0;
    pair<int, int> last_selected;

public: 
    teever(int equation, int variables){
        n = equation;
        m = variables;
        last_selected.first = -1;
        last_selected.second = -1;
    }

    string cellToString(item &it, int i, int j, int m) {
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
        for (int i = 0; i < n; i++) {
            vector<string> row;
            for (int j = 0; j < m; j++) {
                row.push_back(cellToString(arr[i][j], i, j, m));
            }
            table.push_back(row);
        }
        printTable(table);
    }

    void get_matrix(vector<vector<item>>& arr){
        flo nuuts = ZERO, heregtsee = ZERO; 

        cout << "heregtsee oruul: \n";
        for(int i = 1; i < m; i++){
            int a; cin >> a;
            flo el(a, 1);

            arr[0][i].val = el;
            heregtsee = heregtsee + el;
        }

        cout << "nuuts oruul: \n";
        for(int i = 1; i < n; i++){
            int a; cin >> a;

            flo el(a, 1);

            arr[i][0].val = el;
            nuuts = nuuts + el;
        }

        heregtsee.print();
        nuuts.print();
        cout << endl;

        if(heregtsee < nuuts){
            arr[0][m++].val = nuuts - heregtsee;
            nuutsiluudel = 1;
            arr[0][m - 1].val.print();
            cout << " => nuuts iluudev\n";
            
        }

        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(nuutsiluudel && j == m - 1)
                    continue;
                int a; cin >> a;

                flo el(a, 1);

                arr[i][j].val = el;
            }
        }

    }

    void tulguur(){
        vector<vector<item>> arr(n, vector<item>(m + 1, {"c", 0, 0}));
        get_matrix(arr);

        print(arr);

        int i = 1;

        flo cost = 0;
        for(int j = 1; j < m; j++){
            
            while(i < n && arr[i][0].val <= arr[0][j].val){
                cout << i << " " << j << " => ";
                arr[i][0].val.print();
                cout << endl;

                cost = cost + (arr[i][j].val * arr[i][0].val);
                arr[0][j].val = arr[0][j].val - arr[i][0].val;
                arr[i][0].val = ZERO;

                
                print(arr);


                i++;
            }

            if(i == n)
                break;


            cout << i << " " << j << " => ";
            arr[0][j].val.print();
            cout << endl;

            cost = cost + (arr[i][j].val * arr[0][j].val);
            arr[i][0].val = arr[i][0].val - arr[0][j].val;
            arr[0][j].val = ZERO;


            
            print(arr);


        }


        cout << "Z=";
        cost.print();
        cout << endl;



        
    }

};

#endif

