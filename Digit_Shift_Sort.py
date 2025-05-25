import math

def get_max(arr):
    """Trova il valore massimo nell'array."""
    if not arr:
        return 0
    max_val = arr[0]
    for x in arr:
        if x > max_val:
            max_val = x
    return max_val

def Digit_Shift_Sort(arr):
    """
    algoritmo di ordinamento "Ordinamento per Scorrimento di Cifre" (Digit-Shift Sort).
    """
    n = len(arr)
    if n <= 1:
        return arr

    # 1. Trova il Valore Massimo
    max_val = get_max(arr)
    
    # Se l'array contiene solo numeri negativi o 0, e vogliamo ordinare assoluti per esempio,
    # dovremmo gestire anche quello. Per semplicità, assumiamo numeri non negativi
    # In un caso generale, si potrebbe ordinare i negativi separatamente, poi gli zero, poi i positivi.
    # Qui, l'ordinamento per cifre assume numeri positivi.

    # 2. Ciclo sui Passaggi delle Cifre (LSD - da meno significativa a più significativa)
    exp = 1 # Rappresenta 1s, 10s, 100s, ecc.
    while max_val // exp > 0:
        
        # 3. Ciclo di Scorrimento e Inserimento per Cifra
        # Questo ciclo è analogo all'Insertion Sort, ma la chiave di confronto è la cifra corrente.
        for i in range(1, n):
            current_num = arr[i]
            current_digit = (current_num // exp) % 10
            
            j = i - 1
            
            # 4. Estrazione, Scorrimento e Posizionamento
            # Sposta gli elementi maggiori (o con cifra maggiore) a destra
            # per fare spazio a current_num, mantenendo la stabilità.
            while j >= 0:
                prev_num = arr[j]
                prev_digit = (prev_num // exp) % 10
                
                if prev_digit > current_digit:
                    # Se la cifra dell'elemento precedente è maggiore, sposta a destra
                    arr[j+1] = arr[j]
                    j -= 1
                elif prev_digit == current_digit:
                    # Se le cifre sono uguali, l'ordine relativo è già corretto
                    # (mantenuto dai passaggi precedenti, garantendo stabilità).
                    # Non è necessario spostare se prev_num > current_num qui,
                    # non muovere elementi con la stessa cifra se l'ordine è già stabilito.
                    break
                else: # prev_digit < current_digit
                    # L'elemento corrente è già nella posizione relativa corretta
                    break
            
            # 5. Posizionamento Finale
            arr[j+1] = current_num
        
        exp *= 10 # Passa alla cifra successiva (decine, centinaia, ecc.)
    
    return arr

# --- Esempio di Utilizzo ---
if __name__ == "__main__":
    test_arrays = [
        [],
        [5],
        [4, 2, 8, 1, 6],
        [170, 45, 75, 90, 802, 24, 2, 66],
        [5, 5, 5, 2, 2, 1], # Test stabilità e duplicati
        [987, 654, 321],
        [100, 10, 1]
    ]

    for arr in test_arrays:
        print(f"Array originale: {arr}")
        sorted_arr = Digit_Shift_Sort(list(arr)) # Passa una copia
        print(f"Array ordinato:  {sorted_arr}\n")

    # Test con numeri grandi
    large_arr = [i for i in range(1000, 0, -1)] # Numeri da 1000 a 1
    print(f"Array originale (grande, parte): {large_arr[:10]}...")
    sorted_large_arr = Digit_Shift_Sort(large_arr)
    print(f"Array ordinato (grande, parte): {sorted_large_arr[:10]}...")
    assert sorted_large_arr == sorted(large_arr), "L'ordinamento del grande array non è corretto!"
    print("Test su grande array superato.")
