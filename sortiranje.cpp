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
			return rezultat;
		}
		
		vratiSledeceMesto(sledeceMesto.size() - 1);
		zameniSledecegSkorenom();
		zameniOdRoditelja(koren);
		
		return rezultat;
	}
	
	

private:

	void zameniOdRoditelja(Cvor *roditelj){
	
		if (roditelj->deteLevo != nullptr && roditelj->deteLevo->broj < roditelj->broj){
			if (roditelj->deteDesno != nullptr && roditelj->deteDesno->broj < roditelj->deteLevo->broj){
				zameniMestaCvorovima(roditelj, roditelj->deteDesno);
				zameniOdRoditelja(roditelj);
			} else {
				zameniMestaCvorovima(roditelj, roditelj->deteLevo);
				zameniOdRoditelja(roditelj);
			}
		} else if (roditelj->deteDesno != nullptr && roditelj->deteDesno->broj < roditelj->broj){
			zameniMestaCvorovima(roditelj, roditelj->deteDesno);
			zameniOdRoditelja(roditelj);
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

		/* Nastavak stavljanja trenutnog cvora na mesto korena. */		
		if (koren->deteLevo != trenutniCvor){
			trenutniCvor->deteLevo = koren->deteLevo;
		} else {
			trenutniCvor->deteLevo = nullptr;
		}
		
		if (koren->deteDesno != trenutniCvor){
			trenutniCvor->deteDesno = koren->deteDesno;
		} else {
			trenutniCvor->deteDesno = nullptr;
		}
		
		trenutniCvor->cvorRoditelj = nullptr;
		delete koren;
		koren = trenutniCvor;
		
		if (trenutniCvor->deteLevo != nullptr){
			trenutniCvor->deteLevo->cvorRoditelj = trenutniCvor;
		}
		if (trenutniCvor->deteDesno != nullptr){
			trenutniCvor->deteDesno->cvorRoditelj = trenutniCvor;
		}		
	}

	void ispraviHeapNakonDodavanja(Cvor *trenutniCvor){
		if (trenutniCvor->cvorRoditelj == nullptr){
			koren = trenutniCvor;
			return;
		}
		
		if (trenutniCvor->cvorRoditelj->broj > trenutniCvor->broj){
			zameniMestaCvorovima(trenutniCvor->cvorRoditelj, trenutniCvor);
			ispraviHeapNakonDodavanja(trenutniCvor);
		}
	}
	
	void zameniMestaCvorovima(Cvor *roditelj, Cvor *trenutni){
		trenutni->cvorRoditelj = roditelj->cvorRoditelj;
		roditelj->cvorRoditelj = trenutni;
		
		if (trenutni->cvorRoditelj == nullptr){
			koren = trenutni;
		}
		
		Cvor *roditeljDeteLevo = roditelj->deteLevo;
		Cvor *roditeljDeteDesno = roditelj->deteDesno;
		
		roditelj->deteLevo = trenutni->deteLevo;
		roditelj->deteDesno = trenutni->deteDesno;
		
		if (roditeljDeteLevo == trenutni){
			trenutni->deteLevo = roditelj;
			trenutni->deteDesno = roditeljDeteDesno;
		} else if (roditeljDeteDesno == trenutni){
			trenutni->deteDesno = roditelj;
			trenutni->deteLevo = roditeljDeteLevo;
		}
		/* Sad su deteLevo, deteDesno, cvorRoditelj dobri,
		i za trenutni i za roditelj. */
		
		if (trenutni->cvorRoditelj != nullptr){
			if (trenutni->cvorRoditelj->deteLevo == roditelj){
				trenutni->cvorRoditelj->deteLevo = trenutni;
			} else if (trenutni->cvorRoditelj->deteDesno == roditelj){
				trenutni->cvorRoditelj->deteDesno = trenutni;
			}
		}
		
		if (roditelj->deteLevo != nullptr){
			roditelj->deteLevo->cvorRoditelj = roditelj;
		}
		if (roditelj->deteDesno != nullptr){
			roditelj->deteDesno->cvorRoditelj = roditelj;
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
	
	Cvor *koren;
	std::vector<bool> sledeceMesto;
};

int main(){

	MinHeap heap;
	heap.ubaciBroj(2);
	heap.ubaciBroj(3);
	heap.ubaciBroj(5);
	heap.ubaciBroj(10);
	heap.ubaciBroj(4);
	heap.ubaciBroj(6);
	heap.ubaciBroj(4);
	heap.ubaciBroj(1);   
	
	/* heap.ubaciBroj(5);
	heap.ubaciBroj(4);
	heap.ubaciBroj(6);
	heap.ubaciBroj(2); */
	
	for(int i=0; i<8; i++){
		int x = heap.izbaciNajmanjiBroj();
		std::cout << x << std::endl;
	}
	
	return 0;
}
