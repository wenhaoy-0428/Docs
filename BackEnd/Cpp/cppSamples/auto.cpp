#include <iostream>
#include <vector>
using namespace std;


int const*  find(const vector<int> &v, int a) {

	for (int i = 0; i < v.size(); i++) {
		if (a == v[i]) {
			return &(v[i]);
		}
	}
	return 0;
}

int main() {

}