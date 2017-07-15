#include <iostream>
using namespace std;

class Degrau {

public:
	int nivel;
	int* elementos;
	Degrau* ProximoDegrau;

	Degrau(int nivel) {
		this->nivel = nivel;
		elementos = new int[nivel];
		ProximoDegrau = NULL;
	}

	~Degrau() {
		delete(elementos);
	}

	int MenorElemento(Degrau* degrau) {
		int menor = degrau->elementos[0];
		for (int i = 1; i < degrau->nivel; i++) if (degrau->elementos[i] < menor) menor = degrau->elementos[i];
		return menor;
	}

	friend class Piramide;
};

class Piramide {

public:
	Degrau* PrimeiroDegrau;

	Piramide() {
		this->PrimeiroDegrau = NULL;
	}

	~Piramide() {
		Degrau* atual;
		while (PrimeiroDegrau != NULL) {
			atual = PrimeiroDegrau->ProximoDegrau;
			PrimeiroDegrau->~Degrau();
			PrimeiroDegrau = atual;
		}
	}

	void InserirDegrau() {
		if (this->PrimeiroDegrau != NULL) {
			Degrau* ultimo = this->PrimeiroDegrau;
			int nivel = 1;
			while (ultimo->ProximoDegrau != NULL) {
				nivel++;
				ultimo = ultimo->ProximoDegrau;
			}

			Degrau* novo = new Degrau(nivel + 1);

			for (int i = 0; i < nivel + 1; i++) {
				cout << "\nInsira o elemento " << i + 1 << " do degrau " << nivel + 1 << ": ";
				cin >> novo->elementos[i];
			}

			ultimo->ProximoDegrau = novo;
		}
		if (this->PrimeiroDegrau == NULL) {
			Degrau* novo = new Degrau(1);
			cout << "\nInsira o elemento 1 do degrau 1: ";
			int entrada;
			cin >> entrada;
			novo->elementos[0] = entrada;
			this->PrimeiroDegrau = novo;
		}
		cout << "\nDegrau inserido na piramide.";
	}

	void Solucao() {
		int soma = 0;
		Degrau* atual = this->PrimeiroDegrau;
		while (atual != NULL) {
			soma = soma + atual->MenorElemento(atual);
			atual = atual->ProximoDegrau;
		}
		cout << "\n\nSoma dos menores elementos/menor percurso: " << soma << ".";
	}
	
};

int main() {

	Piramide piramide;

	int entrada;

	do {
		cout << "\n\n1. Inserir Degrau na piramide.";
		cout << "\n2. Mostrar solucao.";
		cout << "\n3. Finalizar.\n\n";
		cin >> entrada;

		switch (entrada) {
		case 1: {
			piramide.InserirDegrau();
			break;
		}
		case 2: {
			piramide.Solucao();
			break;
		}
		case 3: break;
		default: break;
		}
	} while (entrada != 3);

	piramide.~Piramide();
}

