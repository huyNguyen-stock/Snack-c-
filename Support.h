#pragma once

template <class T>
void addLast(T* &arr, int &n, T val)	//Thêm 1 phần tử vào cuối mảng
{
	T* arrNew = new T[n + 1];
	if (arrNew != NULL)
	{
		for (int i = 0; i < n; i++)
			arrNew[i] = arr[i];
		arrNew[n] = val;
		n++;
	}
	if (arr != NULL) {
		delete[] arr;
	}
	arr = arrNew;
}

template <class T>
void removeLast(T* &arr, int &n)		//Xoá 1 phần tử ở cuối mảng
{
	if (n == 0 || arr == NULL) return;
	if (n == 1) { delete[] arr; arr = NULL; n = 0; return; }

	T* arrNew = new T[n - 1];
	if (arrNew != NULL)
	{
		for (int i = 0; i < n - 1; i++)
			arrNew[i] = arr[i];
		n--;
		if (arr != NULL) delete[] arr;
		arr = arrNew;
	}
}