#include <iostream>
#include <vector>
#include <cfloat>
#include <queue>
#include <iomanip>

using namespace std;


typedef pair <double, int> para;

static double *drogi_w_jedna_strone, *drogi_w_druga_strone;

struct adapter {
	bool operator () (para p1, para p2) {
            if (p1.first > p2.first) {
            	return true;
            }
            return false;
	}
};

struct elem {
	vector<para>neigh;
};

void dejstra(elem *graf, double *drogi) {
	int pom_index, pom_sasiad_index;
	double pom_sasiad_weight;
	priority_queue<para, vector<para>, adapter> kjuju;


	kjuju.push(make_pair(0, 0));
	drogi[0] = 0;

	while (!kjuju.empty()) {

		pom_index = kjuju.top().second;
		kjuju.pop();

		for (unsigned int i = 0; i < graf[pom_index].neigh.size(); i++) { //dla wszystkich sasiadow wierzcholka wywoluje

			pom_sasiad_index = graf[pom_index].neigh[i].second;
			pom_sasiad_weight = graf[pom_index].neigh[i].first;


			if (drogi[pom_sasiad_index] > drogi[pom_index] + pom_sasiad_weight) { // jezeli jest krotsza droga, aktualizuje i wrzucam do kolejki
				drogi[pom_sasiad_index] = drogi[pom_index] + pom_sasiad_weight;


				kjuju.push(make_pair(drogi[pom_sasiad_index], pom_sasiad_index));
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int l_wierzcholkow, l_polaczen, wierzcholek_pierwszego, wierzcholek_drugiego, x, l_do_odwiedzenia;
	double dlugosc_pierwszego, czas_pierwszego, dlugosc_drugiego, czas_drugiego, wynik = 0, pomo_val;




	cin >> l_wierzcholkow >> l_polaczen;


	elem *graph_w_jedna_strone = new elem[l_wierzcholkow];
	elem *graph_w_druga_strone = new elem[l_wierzcholkow];
	drogi_w_jedna_strone = new double[l_wierzcholkow];
	drogi_w_druga_strone = new double[l_wierzcholkow];






	for (int i = 0; i < l_polaczen; i++) { //################### wczytanie grafu z wartosciami

		cin >> wierzcholek_pierwszego >> wierzcholek_drugiego >> dlugosc_pierwszego >> czas_pierwszego >> dlugosc_drugiego >> czas_drugiego;


		pomo_val = dlugosc_pierwszego * 0.49 + czas_pierwszego * 0.18;
		graph_w_jedna_strone[wierzcholek_pierwszego].neigh.push_back(make_pair(pomo_val, wierzcholek_drugiego));
		graph_w_druga_strone[wierzcholek_drugiego].neigh.push_back(make_pair(pomo_val, wierzcholek_pierwszego));


		pomo_val = dlugosc_drugiego * 0.49 + czas_drugiego * 0.18;
		graph_w_jedna_strone[wierzcholek_drugiego].neigh.push_back(make_pair(pomo_val, wierzcholek_pierwszego));
		graph_w_druga_strone[wierzcholek_pierwszego].neigh.push_back(make_pair(pomo_val, wierzcholek_drugiego));
	}







	for (int i = 0; i < l_wierzcholkow; i++) {
		drogi_w_jedna_strone[i] = DBL_MAX;
		drogi_w_druga_strone[i] = DBL_MAX;
	}
	dejstra(graph_w_jedna_strone, drogi_w_jedna_strone);  //################### wywolanie dijkstry
	dejstra(graph_w_druga_strone, drogi_w_druga_strone);



	cin >> l_do_odwiedzenia;

	for (int i = 0; i < l_do_odwiedzenia; i++) {
		cin >> x;
		wynik += (drogi_w_druga_strone[x] + drogi_w_jedna_strone[x]);
	}

	printf("%.3f", wynik / l_do_odwiedzenia);

	return 0;
}