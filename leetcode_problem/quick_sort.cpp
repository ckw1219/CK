#include<iostream>
#include<vector>
using namespace std;
//快排
int division(vector<int>& nums, int left, int right) {
    int base_val = nums[left];
    int temp_lf = left;
    for (int i = left+1; i <= right; i++) {
        if (nums[i] < base_val) {
            temp_lf++;
            swap(nums[temp_lf],nums[i]);
        }
    }
    swap(nums[temp_lf],nums[left]);

    return temp_lf;
}

void quick_sort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int base = division(nums, left, right);
        quick_sort(nums, left, base-1);

        quick_sort(nums,base+1, right);
    }
}
int main() {
    vector<int> nums{2,4,3,1,5};
    // int res = division(nums, 0, 4);
    quick_sort(nums, 0, 4);

    int m = 0;
    return 0;
}

