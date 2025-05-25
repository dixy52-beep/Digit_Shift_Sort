#include <iostream>  // Per l'output su console (std::cout)
#include <vector>    // Per l'uso di std::vector (array dinamici)
#include <algorithm> // Per std::max_element (per get_max) e std::sort (per i test)
#include <string>    // Per std::string (per le etichette di stampa)
#include <cassert>   // Per la macro assert (per i test di correttezza)

/**
 * @brief Trova il valore massimo nell'array.
 * @param arr Il vettore di interi in cui cercare il massimo.
 * @return Il valore massimo trovato, o 0 se il vettore è vuoto.
 */
int get_max(const std::vector<int>& arr) {
    if (arr.empty()) {
        return 0; // O si potrebbe lanciare un'eccezione o restituire un valore sentinel
    }
    // std::max_element restituisce un iteratore all'elemento massimo.
    // Dobbiamo dereferenziarlo (*) per ottenere il valore stesso.
    return *std::max_element(arr.begin(), arr.end());
}

/**
 * @brief Implementa l'algoritmo di ordinamento "Ordinamento per Scorrimento di Cifre" (Digit-Shift Sort).
 * Questo algoritmo è una variante del Radix Sort (LSD - Least Significant Digit first)
 * che usa un processo di "scorrimento" simile all'Insertion Sort per ogni passaggio di cifra,
 * garantendo la stabilità.
 *
 * @param arr Il vettore di interi da ordinare. Viene modificato direttamente (passato per riferimento).
 * @return Un riferimento al vettore ordinato.
 */
std::vector<int>& Digit_Shift_Sort(std::vector<int>& arr) {
    int n = arr.size(); // Ottieni la dimensione del vettore

    // Caso base: array con 0 o 1 elemento è già ordinato
    if (n <= 1) {
        return arr;
    }

    // 1. Trova il Valore Massimo nell'array
    // Necessario per determinare quante passate di cifre eseguire (quante cifre ha il numero più grande).
    int max_val = get_max(arr);
    
    // Nota: Questo algoritmo è ottimale per numeri interi non negativi.
    // Per numeri negativi o un mix di positivi/negativi, sarebbe necessario
    // un adattamento (es. ordinare i valori assoluti, poi gestire i segni).

    // 2. Ciclo sui Passaggi delle Cifre (dal meno significativo al più significativo)
    // 'exp' rappresenta la posizione della cifra (1 per le unità, 10 per le decine, 100 per le centinaia, ecc.).
    // Usiamo 'long long' per 'exp' per prevenire potenziali overflow se 'max_val' è molto grande
    // e 'exp' supera il limite di 'int' durante le moltiplicazioni.
    long long exp = 1; 
    while (max_val / exp > 0) { // Continua finché ci sono cifre significative da considerare
        
        // 3. Ciclo di Scorrimento e Inserimento per Cifra
        // Questo ciclo interno funziona in modo simile a un Insertion Sort,
        // ma confronta e sposta gli elementi basandosi sulla cifra corrente ('exp').
        for (int i = 1; i < n; ++i) {
            int current_num = arr[i]; // L'elemento corrente da posizionare
            int current_digit = (current_num / exp) % 10; // Estrai la cifra corrente
            
            int j = i - 1; // Indice per scorrere gli elementi già "ordinati" in questa passata
            
            // 4. Estrazione, Scorrimento e Posizionamento
            // Sposta gli elementi con una cifra maggiore (nella posizione 'exp') a destra
            // per fare spazio a 'current_num'. Questo mantiene la stabilità.
            while (j >= 0 && ((arr[j] / exp) % 10) > current_digit) {
                arr[j+1] = arr[j]; // Sposta l'elemento a destra
                j--;               // Passa all'elemento precedente
            }
            // Se prev_digit == current_digit o prev_digit < current_digit,
            // il loop si ferma, perché l'ordine relativo è già corretto (stabilità)
            // o l'elemento corrente è già nella posizione giusta rispetto agli altri.
            
            // 5. Posizionamento Finale
            arr[j+1] = current_num; // Inserisci l'elemento corrente nella posizione corretta
        }
        
        exp *= 10; // Passa alla cifra successiva (decine, centinaia, migliaia, ecc.)
    }
    
    return arr; // Restituisce il vettore ordinato
}

/**
 * @brief Funzione helper per stampare il contenuto di un vettore.
 * @param label Una stringa da stampare come etichetta prima del vettore.
 * @param vec Il vettore da stampare.
 */
void print_vector(const std::string& label, const std::vector<int>& vec) {
    std::cout << label << ": [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) { // Aggiungi la virgola e lo spazio solo se non è l'ultimo elemento
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

// --- Esempio di Utilizzo ---
int main() {
    // Array di test con diversi scenari
    std::vector<std::vector<int>> test_arrays = {
        {},                       // Array vuoto
        {5},                      // Array con un solo elemento
        {4, 2, 8, 1, 6},          // Array standard
        {170, 45, 75, 90, 802, 24, 2, 66}, // Numeri di diverse cifre
        {5, 5, 5, 2, 2, 1},       // Test con duplicati e stabilità
        {987, 654, 321},          // Ordinamento decrescente
        {100, 10, 1}              // Numeri con zeri finali
    };

    // Itera attraverso gli array di test
    for (auto arr_original : test_arrays) { // Usa una copia per non modificare l'originale in test_arrays
        print_vector("Array originale", arr_original);
        
        // Crea una copia del vettore per l'ordinamento, poiché la funzione modifica in-place
        std::vector<int> sorted_arr = arr_original; 
        Digit_Shift_Sort(sorted_arr); // Chiama la funzione di ordinamento
        
        print_vector("Array ordinato", sorted_arr);
        std::cout << "\n";
    }

    // Test con un array grande per verificare le prestazioni e la correttezza
    std::vector<int> large_arr;
    for (int i = 1000; i >= 1; --i) { // Popola l'array con numeri da 1000 a 1
        large_arr.push_back(i);
    }
    
    // Stampa solo una parte del grande array originale per brevità
    std::cout << "Array originale (grande, parte): [";
    for (int i = 0; i < std::min((int)large_arr.size(), 10); ++i) {
        std::cout << large_arr[i] << (i == std::min((int)large_arr.size(), 10) - 1 ? "" : ", ");
    }
    if (large_arr.size() > 10) {
        std::cout << "...";
    }
    std::cout << "]\n";

    // Esegui l'ordinamento sul grande array
    std::vector<int> sorted_large_arr = large_arr; // Crea una copia per l'ordinamento
    Digit_Shift_Sort(sorted_large_arr);

    // Stampa solo una parte del grande array ordinato per brevità
    std::cout << "Array ordinato (grande, parte):  [";
    for (int i = 0; i < std::min((int)sorted_large_arr.size(), 10); ++i) {
        std::cout << sorted_large_arr[i] << (i == std::min((int)sorted_large_arr.size(), 10) - 1 ? "" : ", ");
    }
    if (sorted_large_arr.size() > 10) {
        std::cout << "...";
    }
    std::cout << "]\n";

    // Verifica l'ordinamento confrontandolo con l'ordinamento standard di C++ (std::sort)
    std::vector<int> expected_sorted_large_arr = large_arr;
    std::sort(expected_sorted_large_arr.begin(), expected_sorted_large_arr.end());
    
    // assert fermerà il programma con un errore se la condizione è falsa
    assert(sorted_large_arr == expected_sorted_large_arr);
    std::cout << "Test su grande array superato.\n";

    return 0; // Indica che il programma è terminato correttamente
}
