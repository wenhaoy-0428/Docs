#include<string>
#include<vector>
#include<iostream>
using namespace std;

void swap(int &a, int &b);
void display(vector<int> v);
void sort(vector<int> &v);

int main() {
	int arr[] = { 5,3,1,2,4 };
	vector<int> v(arr,arr + 5);
    for (int i = 0; i < v.size(); i++) {
        cout << "HI" << v[i] << endl;
    }
	sort(v);
	display(v);

	return 0;
}


void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void display(vector<int> v)
{
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}

void sort(vector<int> &v)
{
	for (int i = 0; i < v.size() - 1; i++) {
		for (int j = i; j < v.size() - 1 - i; j++) {
			if (v[j] > v[j + 1]) {
				swap(v[j], v[j + 1]);
			}
		}
	}
}
