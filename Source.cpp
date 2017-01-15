#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
int medianFind(double l, double r, double m, int lp, int rp, int mp);
void printarray(double *arr, int l, int r);

//quicksort of the median of 3: first element, middle element & last element (median of this is the pivot)
void QuickSortMedian3(double *arr, int l, int r)
{
	int lengthArray = r - l + 1;
	if (lengthArray > 1)
	{
		int mid1 = 0;
		if (lengthArray % 2 == 0)
		{
			//if array is even
			mid1 = l + (lengthArray / 2) - 1;
		}
		else
		{
			//if array is odd
			mid1 = l + (lengthArray / 2);
		}

		int median = medianFind(arr[l], arr[r], arr[mid1], l, r, mid1);
		//printarray(arr, l, r);
		//cout << "L: " << arr[l] << ", M: " << arr[mid1] << ", R: " << arr[r] << ", Median: " << arr[median] << endl;
		//swap first element with median element
		double temp1 = arr[median];
		arr[median] = arr[l];
		arr[l] = temp1;

		//partition
		double pivot = arr[l];
		int i = l + 1;
		for (int j = i; j <= r; j++)
		{
			if (arr[j] < pivot)
			{
				//swap
				double tempVar = arr[j];
				arr[j] = arr[i];
				arr[i] = tempVar;
				i++;
			}
		}

		//swap 
		temp1 = arr[l];
		arr[l] = arr[i - 1];
		arr[i - 1] = temp1; //here's the pivot
							//printarray(arr, l, r);
							//cout << endl;
		QuickSortMedian3(arr, l, i - 2);
		QuickSortMedian3(arr, i, r);
	}
}

int medianFind(double l, double r, double m, int lp, int rp, int mp)
{
	double smallest;
	double biggest;
	double median;
	double *arr = new double[3];
	double *arr2 = new double[3];
	//values
	arr[0] = l;
	arr[1] = r;
	arr[2] = m;
	//position
	arr2[0] = lp;
	arr2[1] = rp;
	arr2[2] = mp;

	smallest = arr[0]; //initialize
	biggest = arr[0]; //initialize
	for (int i = 1; i < 3; i++)
	{
		if (smallest > arr[i])
		{
			smallest = arr[i];
		}
		if (biggest < arr[i])
		{
			biggest = arr[i];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (arr[i] >= smallest && arr[i] <= biggest)
		{
			median = arr2[i];
		}
	}
	delete[] arr2;
	delete[] arr;

	return median;
}

double Rselect(double *arr, int l, int r, int osi)
{
	int arraylen = r - l + 1;
	if (l < r)
	{
		//random pivot choose then swap with first element
		int pivotPosition = l + (rand() % arraylen) + 1; //random position
		double temp1 = arr[pivotPosition - 1];  //begin swap
			//cout << "X!\n";// for me to track
			//printarray(arr, l, r); // for me to track
			//cout << temp1 << " is the random! pos: " << pivotPosition-1<<" \n"; // for me to track
		arr[pivotPosition - 1] = arr[l];
		arr[l] = temp1;
		//partition
			//printarray(arr, l, r); // for me to track
		double pivot = arr[l];
		int i = l + 1;
		for (int j = i; j <= r; j++)
		{
			if (arr[j] < pivot)
			{
				//swap
				double tempVar = arr[j];
				arr[j] = arr[i];
				arr[i] = tempVar;
				i++;
			}
		}
		//swap 
		temp1 = arr[l];
		arr[l] = arr[i - 1];
		arr[i - 1] = temp1;
			//printarray(arr, l, r); // for me to track
		int j = i;
			//cout << "J " << j << ", I " << i << ", OSI " << osi <<  endl; // for me to track
		if (j == osi)
		{
			return arr[j - 1];
		}
		else if (j > osi)
		{
			return Rselect(arr, l, i - 2, osi);
		}
		else if (j < osi)
		{
			return Rselect(arr, i, r, osi );
		}
	}
	else {
		return arr[l];
	}
}
void printarray(double *arr, int l, int r)
{
	cout << "(";
	for (int i = l; i < r; i++)
	{
		cout << arr[i] << ", ";
	}
	cout << arr[r] << ")" << endl;

}

int main()
{
	srand((unsigned)time(NULL));
	int n = 11;
	double *arr = new double[n];
	double *arr2 = new double[n];
	int l = 0;
	int r = n-1;
	double temp = 0.0;
	
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 1000 + 1; //1 to 1000
		arr2[i] = arr[i];
	}

	QuickSortMedian3(arr2, l, r);
	printarray(arr2, l, r);
	int find = rand() % n + 1;
	
	//printarray(arr, l, r);
	int i = find;
	temp = Rselect(arr, l, r, i);
	cout << "searching for ranked order " << i << endl;
	cout << i<< " position from Rselect : " << temp << endl;
	cout << "Via quicksort " << find << " position : " << arr2[find - 1] << endl;
	//temp pause;
	int userInput;
	cout << "Exiting..." << endl;
	cin >> userInput;
	return 0;
}