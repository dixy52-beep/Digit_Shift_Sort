/**
 * @brief Trova il valore massimo nell'array.
 * @param {number[]} arr Il vettore di numeri in cui cercare il massimo.
 * @returns {number} Il valore massimo trovato, o 0 se il vettore è vuoto.
 */
function get_max(arr) {
    if (arr.length === 0) {
        return 0; // O si potrebbe lanciare un'eccezione o restituire null/undefined
    }
    // Math.max con lo spread operator (...) è un modo conciso per trovare il massimo
    return Math.max(...arr);
}

/**
 * @brief Implementa l'algoritmo di ordinamento "Ordinamento per Scorrimento di Cifre" (Digit-Shift Sort).
 * Questo algoritmo è una variante del Radix Sort (LSD - Least Significant Digit first)
 * che usa un processo di "scorrimento" simile all'Insertion Sort per ogni passaggio di cifra,
 * garantendo la stabilità.
 *
 * @param {number[]} arr Il vettore di numeri da ordinare. Viene modificato direttamente (passato per riferimento).
 * @returns {number[]} Un riferimento al vettore ordinato.
 */
function Digit_Shift_Sort(arr) {
    const n = arr.length; // Ottieni la dimensione del vettore

    // Caso base: array con 0 o 1 elemento è già ordinato
    if (n <= 1) {
        return arr;
    }

    // 1. Trova il Valore Massimo nell'array
    // Necessario per determinare quante passate di cifre eseguire (quante cifre ha il numero più grande).
    const max_val = get_max(arr);
    
    // Nota: Questo algoritmo è ottimale per numeri interi non negativi.
    // Per numeri negativi o un mix di positivi/negativi, sarebbe necessario
    // un adattamento (es. ordinare i valori assoluti, poi gestire i segni).

    // 2. Ciclo sui Passaggi delle Cifre (dal meno significativo al più significativo)
    // 'exp' rappresenta la posizione della cifra (1 per le unità, 10 per le decine, 100 per le centinaia, ecc.).
    // In JavaScript, i numeri sono float a doppia precisione, ma per operazioni intere
    // su valori ragionevoli si comportano come interi.
    let exp = 1; 
    while (Math.floor(max_val / exp) > 0) { // Continua finché ci sono cifre significative da considerare
        
        // 3. Ciclo di Scorrimento e Inserimento per Cifra
        // Questo ciclo interno funziona in modo simile a un Insertion Sort,
        // ma confronta e sposta gli elementi basandosi sulla cifra corrente ('exp').
        for (let i = 1; i < n; ++i) {
            const current_num = arr[i]; // L'elemento corrente da posizionare
            // Estrai la cifra corrente usando Math.floor per la divisione intera
            const current_digit = Math.floor(current_num / exp) % 10; 
            
            let j = i - 1; // Indice per scorrere gli elementi già "ordinati" in questa passata
            
            // 4. Estrazione, Scorrimento e Posizionamento
            // Sposta gli elementi con una cifra maggiore (nella posizione 'exp') a destra
            // per fare spazio a 'current_num'. Questo mantiene la stabilità.
            while (j >= 0 && (Math.floor(arr[j] / exp) % 10) > current_digit) {
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
 * @param {string} label Una stringa da stampare come etichetta prima del vettore.
 * @param {number[]} vec Il vettore da stampare.
 */
function print_vector(label, vec) {
    // Usiamo template literals e .join() per una stampa concisa e leggibile
    console.log(`${label}: [${vec.join(', ')}]`);
}

// --- Esempio di Utilizzo ---
if (typeof module !== 'undefined' && module.exports) {
    // Se siamo in un ambiente Node.js, possiamo esportare le funzioni
    module.exports = { get_max, Digit_Shift_Sort };
}

// Esegui i test solo se lo script viene eseguito direttamente (non importato)
if (require.main === module || typeof window !== 'undefined') { // Per Node.js e browser
    // Array di test con diversi scenari
    const test_arrays = [
        [],                       // Array vuoto
        [5],                      // Array con un solo elemento
        [4, 2, 8, 1, 6],          // Array standard
        [170, 45, 75, 90, 802, 24, 2, 66], // Numeri di diverse cifre
        [5, 5, 5, 2, 2, 1],       // Test con duplicati e stabilità
        [987, 654, 321],          // Ordinamento decrescente
        [100, 10, 1]              // Numeri con zeri finali
    ];

    // Itera attraverso gli array di test
    for (const arr_original of test_arrays) {
        print_vector("Array originale", arr_original);
        
        // Crea una copia del vettore per l'ordinamento, poiché la funzione modifica in-place.
        // Lo spread operator ([...arr_original]) crea una shallow copy.
        const sorted_arr = [...arr_original]; 
        Digit_Shift_Sort(sorted_arr); // Chiama la funzione di ordinamento
        
        print_vector("Array ordinato", sorted_arr);
        console.log("\n");
    }

    // Test con un array grande per verificare le prestazioni e la correttezza
    const large_arr = [];
    for (let i = 1000; i >= 1; --i) { // Popola l'array con numeri da 1000 a 1
        large_arr.push(i);
    }
    
    // Stampa solo una parte del grande array originale per brevità
    console.log(`Array originale (grande, parte): [${large_arr.slice(0, 10).join(', ')}${large_arr.length > 10 ? ', ...' : ''}]`);

    // Esegui l'ordinamento sul grande array
    const sorted_large_arr = [...large_arr]; // Crea una copia per l'ordinamento
    Digit_Shift_Sort(sorted_large_arr);

    // Stampa solo una parte del grande array ordinato per brevità
    console.log(`Array ordinato (grande, parte):  [${sorted_large_arr.slice(0, 10).join(', ')}${sorted_large_arr.length > 10 ? ', ...' : ''}]`);

    // Verifica l'ordinamento confrontandolo con l'ordinamento standard di JavaScript
    const expected_sorted_large_arr = [...large_arr].sort((a, b) => a - b); // .sort() per numeri richiede una funzione di confronto
    
    // Confronta gli array convertendoli in stringhe JSON per un confronto di contenuto semplice
    if (JSON.stringify(sorted_large_arr) === JSON.stringify(expected_sorted_large_arr)) {
        console.log("Test su grande array superato.");
    } else {
        console.error("L'ordinamento del grande array NON è corretto!");
        // Per debug, puoi stampare le differenze
        // console.error("Atteso:", expected_sorted_large_arr.slice(0, 20));
        // console.error("Ottenuto:", sorted_large_arr.slice(0, 20));
    }
}
