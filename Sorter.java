public class Sorter {

	public static int[] selectionSort(int[] data) {
		int j = 0, temp = 0;
		int readCount = 0, writeCount = 0;
		for (int i=0; i<data.length; i++) {
			j=i;
			for (int k=i; k<data.length; k++) {
				readCount++;
				if (data[j] > data[k])
					j=k;
			}
			writeCount += 2;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;
		}
		return data;
	}

	public static int[] mergeSort(int[] data) {
		int readCount = 0;
		int writeCount = 0;
		if (data.length <= 1) return data;
		int[] first = new int[data.length/2];
		int[] second = new int[data.length-first.length];
		for (int i=0; i<first.length; i++)
			readCount++;
			first[i] = data[i];
		for (int i=0; i<second.length; i++)
			second[i] = data[first.length+i];
		first = this.mergeSort(first);
		second = this.mergeSort(second);
		return (merge(first, second));
	}

	public static int[] insertionSort(int[] data) {
		int next, j = 0;
		int readCount = 0, writeCount = 0;
		for (int i=0; i<data.length; i++) {
			next = data[i];
			j=i;
			while ((j > 0) && (data[i-j] > next)) {
				readCount++;
				data[j] = data[j-1];
				writeCount++;
				j--;
			}
			writeCount++;
			data[j] = next;
		}
		return data;
	}

	public static int[] crazySort(int[] data) {
		int i, j, temp;
		int readCount = 0, writeCount = 0;
		for (i=0; i<data.length; i++) {
			for (j=i+1; j<data.length; j++) {
				readCount++;
				if (data[i] > data[j]) {
					writeCount += 2;
					temp = data[j];
					data[j] = data[i];
					data[i] = temp;
				}
			}
		}
		return data;
	}

	public void swap(int i, int j) {
		
	}

	public static int[] merge(int[] first, int[] second) {
		int[] merged = new int[first.length+second.length];
		int i = 0, j = 0, k = 0;
		int readCount = 0, writeCount = 0;
		while ((i<first.length) && (j<second.length)) {
			readCount++;
			if (first[i] < second[i]) {
				writeCount++;
				merged[k] = first[i];
				i++;
			} else {
				writeCount++;
				merged[k] = second[j];
				j++;
			}
			k++;
		}
		while (i<first.length) {
			writeCount++;
			merged[k] = first[i]; i++; k++;
		}
		while (j<second.length) {
			writeCount++;
			merged[k] = second[j]; i++; k++;
		}
		return merged;
	}
}