#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;

struct treeNode {
    map<char,int> dic;

    treeNode():sonNode(nullptr) {};

    treeNode* sonNode;
};


struct treeNode {
    vector<treeNode*> nodeNums{26,nullptr};
    treeNode() {
        isEnd = false;
    };
    bool isEnd;
    // treeNode* sonNode;
};

void insert (string word) {
    // treeNode* root = new treeNode();
    treeNode* temp = root;
    for (char chr : word) {
        int index = chr - '0';

        if (temp->nodeNums[index] == nullptr) {
            temp->nodeNums[index] = new treeNode();
        }
        temp = temp->nodeNums[index];
    }
    temp->isEnd = true;
}

bool find(string word, treeNode* root) {
    if (word.size() == 0) return false;
    treeNode* temp = root;
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == '.') {
            for (int j = 0; j < 26; j++) {
                bool res = false;
                string s_temp;
                for (int k = i+1; k < word.size(); k++) {
                    s_temp += word[k];
                }
                if (temp->nodeNums[j]) {
                    res = find(s_temp, temp->nodeNums[j]);
                }
                if (res) return true;
            }
        }
        else {
            int index = word[i] - '0';
            if (temp->nodeNums[index]) {
                temp = temp->nodeNums[index];
            }
            else {
                return false;
            }
        }
    }
    if (temp->isEnd) return true;
    return false;
}
int main() {
    vector<string> words{"oath","pea","eat","rain"};

    treeNode* root = new treeNode();
    for (string word : words) {
        treeNode* temp = root;
        for (char chr : word) {
            temp->dic[chr]++;
            if (temp->sonNode == nullptr) temp->sonNode = new treeNode();
            temp = temp->sonNode;
        }
    }


    return 0;

}











// class Solution {
// public:
//     bool isValidSudoku(vector<vector<char>>& board) {
//         //验证行
//         vector<vector<int>> res{{0,0},{8,8}};
//         if (!valid1(board,res)) return false;
//         vector<vector<int>> index{{0,0},{2,2}};
//         while (index[0][1] < 8) {
//             if (!valid(board,index)) return false;;
//             index[0][1] += 3;
//             index[1][1] += 3;
//         }

//         vector<vector<int>> index1{{3,0},{5,2}};
//         while (index1[0][1] < 8) {
//             if (!valid(board,index1)) return false;;
//             index1[0][1] += 3;
//             index1[1][1] += 3;
//         }

//         vector<vector<int>> index2{{6,0},{8,2}};
//         while (index2[0][1] < 8) {
//             if (!valid(board,index2)) return false;;
//             index2[0][1] += 3;
//             index2[1][1] += 3;
//         }

//         return true;

//     }

//     bool valid(vector<vector<char>>& board, vector<vector<int>>& index) {
//         int h_lf = index[0][0], h_rh = index[1][0];
//         int l_lf = index[0][1], l_rh = index[1][1];
//         map<int,int> mp_total;
//         for (int i = h_lf; i <= h_rh; i++) {
//             for (int j = l_lf; j <= l_rh; j++) {
//                 if (isdigit(board[i][j])) {
//                     if (mp_total[(int)board[i][j]] > 0) return false;
//                     mp_total[(int)board[i][j]] = 1;
//                 }                
//             }
//         }
//         return true;
//     }
    
//     bool valid1(vector<vector<char>>& board) {
//         for (int i = 0; i <= 8; i++) {
//             map<int,int> mp;
//             for (int j = 0; j <= 8; j++) {
//                 if (isdigit(board[i][j])) {
//                     if (mp[(int)board[i][j]] > 0) return false;
//                     mp[(int)board[i][j]] = 1;
//                 }
//             }
//         }

//         //验证列
//         for (int i = 0; i <= 8; i++) {
//             map<int,int> mp;
//             for (int j = 0; j <= 8; j++) {
//                 if (isdigit(board[j][i])) {
//                     if (mp[(int)board[j][i]] > 0) return false;
//                     mp[(int)board[j][i]] = 1;
//                 }
//             }
//         }

//         return true;
//     }
// };