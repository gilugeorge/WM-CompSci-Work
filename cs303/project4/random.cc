void GroupOfNumbers::linear_select(long *tempArr, long left, long right, long k) const{
	if(left + CutOff <= right){
		cout << "left: " << left << endl;
		cout << "right: "<< right<< endl;
		long pivot = median_of_median_of_5(tempArr, left, right);
		cout << "Pivot: " << pivot << endl;

		long i = left, j = right-1;
		for(;;){
			while(tempArr[++i] < pivot){}
			while(pivot < tempArr[--j]){}
			if(i < j)
				swap(tempArr[i], tempArr[j]);
			else
				break;
		}
		swap(tempArr[i], tempArr[right-1]); //Restore Pivot
		if(k <= i){
			linear_select(tempArr, left, i, k); //sort small elements
		}else if(k > i+1){ // if k=(i+1). No need to sort. As (i+1)th item is the pivot element.
			linear_select(tempArr, i, right, k);
		}

	}
	else{ //do an insertion sort on the subarrays
	c_isort(left,right, tempArr);
	}
}//protected linear_select

long GroupOfNumbers::momo_five(long *temp_group, long left, long right) const{
	long numbermedians = (right - left + 1) / 5;
	cout<<"Number of medians = "<<numbermedians<<endl;
	int groupleft, groupright;

	for(int i = 0; i < numbermedians; i ++){
		groupleft = 5*i;
		groupright = groupleft + 4;
		insertion_sort(temp_group, left+groupleft, left+groupright);
		swap(temp_group[groupleft+2], temp_group[i]);
	}
	//displayGroupOfNumbers();
	long medianposition = (numbermedians / 2)-1;
	
	quick_select(temp_group, 0,numbermedians-1, (numbermedians/2));

	return temp_group[medianposition];
}

long GroupOfNumbers::median_of_median_of_5(long *tempArr, long left, long right) const{
	long temp_size= right-left+1;
	cout<<"temp size: "<< temp_size<< endl;
	long *median_5= new long[temp_size];
	long *med_med= new long[temp_size/5];
	if(temp_size>=5){
		int k=0;
		for(int i=left; i<(left+temp_size/5); i++){
			for(int j=0; j<5; j++){
				median_5[(5*k)+j]= tempArr[left+(5*k)+j];
			}
			k++;
		}
		for(int m=0; m< temp_size/5; m++){
		int temp_m= m*5;
			if(median_5[temp_m]>median_5[temp_m+1])
			swap(median_5[temp_m], median_5[temp_m+1]);
			if(median_5[temp_m+3]>median_5[temp_m+4])
			swap(median_5[temp_m+3], median_5[temp_m+4]);
			if(median_5[temp_m]>median_5[temp_m+3])
			swap(median_5[temp_m], median_5[temp_m+3]);
			if(median_5[temp_m+1]>median_5[temp_m+4])
			swap(median_5[temp_m+1], median_5[temp_m+4]);
			if(median_5[temp_m+2]>median_5[temp_m+3])
			swap(median_5[temp_m+2], median_5[temp_m+3]);
			if(median_5[temp_m+1]>median_5[temp_m+2])
			swap(median_5[temp_m+1], median_5[temp_m+2]);
			if(median_5[temp_m+2]>median_5[temp_m+3])
			swap(median_5[temp_m+2], median_5[temp_m+3]);
			//swap(median_5[m+2], median_5[m+3]);
			med_med[m]= median_5[temp_m+2];
//			c_isort(temp_m, temp_m+4, median_5);
			med_med[m]= median_5[temp_m+2];
		}
		return med_med[(temp_size/5)/2];
		//return median_of_median_of_5(med_med, 0, temp_size/5);

	}
	else{
		if(temp_size==4){
		return tempArr[1];
		}
		else if(temp_size==3){
		return tempArr[1];
		}
		else if(temp_size==2){
		return tempArr[0];
		}
		return tempArr[0];
	}
}
