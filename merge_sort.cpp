#include<iostream>
#include<vector>
/*
void objediniNiz(int *niz, int levoPocetak, int levoKraj, int desnoPocetak, int desnoKraj, int *pomocni){
	int duzinaLevog = levoKraj - levoPocetak + 1;
	int duzinaDesnog = desnoKraj - desnoPocetak + 1;
	
	int i=0, j=0, k=0;
	while(i < duzinaLevog && j < duzinaDesnog){
		if (niz[levoPocetak + i] < niz[desnoPocetak + j]){
			pomocni[k] = niz[levoPocetak + i];
			i++;
		} else {
			pomocni[k] = niz[desnoPocetak + j];
			j++;
		}
		k++;
	}
	
	while(i < duzinaLevog){
		pomocni[k] = niz[levoPocetak + i];
		i++;
		k++;
	}
	while (j < duzinaDesnog){
		pomocni[k] = niz[desnoPocetak + j];
		j++;
		k++;
	}
} */


void objediniNiz(int *niz, int levoPocetak, int levoKraj, int desnoPocetak, int desnoKraj, int *pomocni){
	int i = levoPocetak, j = desnoPocetak, k = 0;
	while(i <= levoKraj && j <= desnoKraj){
		if (niz[i] < niz[j]){
			pomocni[k++] = niz[i++];
		} else {
			pomocni[k++] = niz[j++];
		}
	}
	
	while (i <= levoKraj){
		pomocni[k++] = niz[i++];
	}
	while (j <= desnoKraj){
		pomocni[k++] = niz[j++];
	}
}

void mergeSort(int *niz, int levo, int desno){
	if (levo >= desno) return;
	
	int sredina = (levo+desno)/2;
	mergeSort(niz, levo, sredina);
	mergeSort(niz, sredina+1, desno);
	
	std::vector<int> pomocni(desno-levo+1);
	objediniNiz(niz, levo, sredina, sredina+1, desno, pomocni.data());
	for(int i=levo, j=0; i<=desno; i++, j++){
		niz[i] = pomocni[j];
	}
}

void mergeSort(std::vector<int> &niz){
	mergeSort(niz.data(), 0, niz.size()-1);
}

int main(){
	int n;
	std::cout << "Upisi duzinu niza: ";
	std::cin >> n;

	std::vector<int> niz(n);
	std::cout << "Upisite " << n << " brojeva: ";
	for(int i=0; i<n; i++){
		std::cin >> niz[i];
	}
	
	mergeSort(niz);
	
	for(int x : niz){
		std::cout << x << std::endl;
	}

	return 0;
}
