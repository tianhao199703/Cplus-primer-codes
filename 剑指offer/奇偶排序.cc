bool iseven(int x){//此处可扩展
	return x % 2 == 0;
}

int main(){
	int n = 2;
	vector<int> a{ 2, 4, 5, 3, 6, 7, 8, 6 };
	int lo = 0, hi = a.size() - 1;
	while (lo < hi){
		while (lo<hi && iseven(a[lo])) lo++;
		while (lo<hi && !iseven(a[hi])) hi--;
		if (lo<hi) swap(a[lo], a[hi]);
	}
	return 0;
}
