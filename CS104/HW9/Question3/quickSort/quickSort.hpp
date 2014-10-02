template <class T>
quickSort<T>::quickSort(T array[], int size)
{
	qSort(array, 0, size-1);
}

template<class T>
quickSort<T>::~quickSort()
{

}

template <class T>
void quickSort<T>::printArray (int *array, int l, int r, int m)
{
	for (int i = 0; i < l; i ++)
		cout << "   ";
	for (int i = l; i <= r; i ++)
		{
			cout << array[i];
			if (i == m || i == m-1) cout << "|";
			else cout << " ";
		}
	cout << endl;
}

template <class T>
void quickSort<T>::swap (T array[], int i, int j)
{
	T b = array[i];
	array[i] = array[j];
	array[j] = b;
}

template <class T>
void quickSort<T>::merge (T array[], int left, int right, int mid)
{
	T temp[right+1-left];
	int i = left, j = mid+1, k = 0;
	while (i <= mid || j <= right)
	{
		if (i <= mid && (j > right || array[i] < array[j]))
			{ temp[k] = array[i]; ++i; ++k; }
		else { temp[k] = array[j]; ++j; ++k; }
	}
	for (k = 0; k < right+1-left; ++k)
		array[k+left] = temp[k];
}

template <class T>
void quickSort<T>::mergeSort (T array[], int left, int right)
{
	if (left < right)
	{
		int mid = (left+right)/2;
		mergeSort(array, left, mid);
		mergeSort(array, mid+1, right);
		merge(array, left, right, mid);
	}
}

template <class T>
int quickSort<T>::partition (T array[], int left, int right)
{
	int i = left;
	T p = array[right];
	for (int j = left; j < right; ++j)
	{
		if (array[j] <= p)
		{ swap (array, i, j); ++i; }
	}
	swap (array, i, right);
	return i;
}




template <class T>
void quickSort<T>::qSort (T array[], int left, int right)
{
	if (left < right)
	{
		int mid = partition (array, left, right);
		qSort (array, left, mid-1);
		qSort (array, mid+1, right);
	}
}

template <class T>
void quickSort<T>::sortArray(T array[], int size)
{
	qSort(array, 0, size-1);
}