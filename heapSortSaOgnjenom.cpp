#include<iostream>
#include<vector>

class Cvor{
public:
	int broj;
	Cvor *deteLevo;
	Cvor *deteDesno;
	Cvor *cvorRoditelj;
	
	Cvor(int b, Cvor *deteL, Cvor *deteD, Cvor *cvorR){
		this->broj = b;
		this->deteLevo = deteL;
		this->deteDesno = deteD;
		this->cvorRoditelj = cvorR;
	}
};

class MinHeap{
public:
	MinHeap(){
		koren = nullptr;
	}
	
	bool heapJePrazan(){
		return koren == nullptr;
	}
	
	void ubaciBroj(int broj){
		if (koren == nullptr){
			koren = new Cvor(broj, nullptr, nullptr, nullptr);
			sledeceMesto.push_back(false);
		} else {
		
			Cvor *trenutniCvor = koren;
			for(int i=0; i<sledeceMesto.size()-1; i++){
				if (!sledeceMesto[i]){
					trenutniCvor = trenutniCvor->deteLevo;
				} else {
					trenutniCvor = trenutniCvor->deteDesno;
				}
			}
			
			Cvor *noviCvor = new Cvor(broj, nullptr, nullptr, trenutniCvor);
			
			int poslednjiIndeks = sledeceMesto.size() - 1;
			if (!sledeceMesto[poslednjiIndeks]){
				trenutniCvor->deteLevo = noviCvor; 
			} else {
				trenutniCvor->deteDesno = noviCvor;
			}
			
			ispraviHeapNakonDodavanja(noviCvor);
			azurirajSledeceMestoNakonDodavanja(sledeceMesto.size()-1);
		}
	}
	
	int dajNajmanjiBroj(){
		if (koren == nullptr){
			return 0;
		}
		return koren->broj;
	}
	
	int izbaciNajmanjiBroj(){
		if (koren == nullptr){
			return 0;
		}
		int rezultat = koren->broj;
		if (koren->deteLevo == nullptr && koren->deteDesno == nullptr){
			delete koren;
			koren = nullptr;
			sledeceMesto.resize(0);
			return rezultat;
		}
		
		vratiSledeceMesto(sledeceMesto.size() - 1);
		zameniSledecegSkorenom();
		zameniOdRoditelja(koren);
		
		return rezultat;
	}
	
	

private:
	Cvor *koren;
	std::vector<bool> sledeceMesto;
	
	void zameniOdRoditelja(Cvor *roditelj){
	
		if (roditelj->deteLevo != nullptr && roditelj->deteLevo->broj < roditelj->broj){
			if (roditelj->deteDesno != nullptr && roditelj->deteDesno->broj < roditelj->deteLevo->broj){
				std::swap(roditelj->broj, roditelj->deteDesno->broj);
				zameniOdRoditelja(roditelj->deteDesno);
			} else {
				std::swap(roditelj->broj, roditelj->deteLevo->broj);
				zameniOdRoditelja(roditelj->deteLevo);
			}
		} else if (roditelj->deteDesno != nullptr && roditelj->deteDesno->broj < roditelj->broj){
			std::swap(roditelj->broj, roditelj->deteDesno->broj);
			zameniOdRoditelja(roditelj->deteDesno);
		} 
	}

	void zameniSledecegSkorenom(){
		Cvor *trenutniCvor = koren;
		for(int i=0; i<sledeceMesto.size(); i++){
				if (!sledeceMesto[i]){
					trenutniCvor = trenutniCvor->deteLevo;
				} else {
					trenutniCvor = trenutniCvor->deteDesno;
				}
		}
		
		
		/* Odvezivanje trenutnog cvora od njegovog roditelja */
		if (trenutniCvor->cvorRoditelj->deteLevo == trenutniCvor){
			trenutniCvor->cvorRoditelj->deteLevo = nullptr;
		} 
		if (trenutniCvor->cvorRoditelj->deteDesno == trenutniCvor){
			trenutniCvor->cvorRoditelj->deteDesno = nullptr;
		}
		
		koren->broj = trenutniCvor->broj;
		delete trenutniCvor;		
	}

	void ispraviHeapNakonDodavanja(Cvor *trenutniCvor){
		if (trenutniCvor->cvorRoditelj == nullptr){
			koren = trenutniCvor;
			return;
		}
		
		if (trenutniCvor->cvorRoditelj->broj > trenutniCvor->broj){
			std::swap(trenutniCvor->cvorRoditelj->broj, trenutniCvor->broj);
			ispraviHeapNakonDodavanja(trenutniCvor->cvorRoditelj);
		}
	}
	
	
	void vratiSledeceMesto(int poslednjiIndeks){
		if (poslednjiIndeks < 0){
			return;
		}
		
		if (sledeceMesto[poslednjiIndeks]){
			sledeceMesto[poslednjiIndeks] = false;
			return;
		}
		
		if (poslednjiIndeks == 0){
			sledeceMesto[0] = true;
			sledeceMesto.resize(sledeceMesto.size() - 1);
			return;
		}
		
		sledeceMesto[poslednjiIndeks] = true;
		vratiSledeceMesto(poslednjiIndeks - 1);
	}

	void azurirajSledeceMestoNakonDodavanja(int poslednjiIndeks){
		if (poslednjiIndeks < 0){
			sledeceMesto.push_back(false);
			return;
		}
	
		if (!sledeceMesto[poslednjiIndeks]){
			sledeceMesto[poslednjiIndeks] = true;
			return;
		}
		
		if (poslednjiIndeks == 0){
			sledeceMesto[0] = false;
			sledeceMesto.push_back(false);
			return;
		}
		
		sledeceMesto[poslednjiIndeks] = false;
		azurirajSledeceMestoNakonDodavanja(poslednjiIndeks - 1);
	}
	
};

int main(){

	MinHeap heap;
	
	int n;
	std::cout << "Koliko brojeva cete upisati: ";
	std::cin >> n;
	std::cout << "Upisite " << n <<" brojeva: ";
	
	for(int i=0; i<n; i++){
		int broj;
		std::cin >> broj;
		heap.ubaciBroj(broj);
	}
	
	std::cout << "Sortirani brojevi: \n";
	while(!heap.heapJePrazan()){
		std::cout << heap.izbaciNajmanjiBroj() << std::endl;
	}
	
	return 0;
}
