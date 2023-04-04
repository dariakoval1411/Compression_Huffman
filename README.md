# **Huffman Compression**

Author Daria Koval 

**Program do beztratnej kompresji danych na podstawie algorytma Huffman.**

# Opis 

Algorytm kompresji Huffmana to popularny algorytm bezstratnej kompresji danych, który używa kodów o zmiennej długości do reprezentowania znaków w pliku. Jest to algorytm, który ma na celu zmniejszenie rozmiaru pliku bez utraty żadnych informacji.

Algorytm składa się z dwóch głównych etapów: budowania drzewa Huffmana i kodowania danych. 

1.**Pierwszy etap** polega na zliczeniu częstości występowania każdego znaku w pliku i utworzeniu drzewa, które ma wierzchołki dla każdego znaku, a liście są węzłami z częstością występowania każdego znaku. Drzewo jest budowane od liści do korzenia, a wierzchołki są łączone w pary zgodnie z ich częstością występowania. Następnie korzeń drzewa jest korzeniem drzewa Huffmana.

2.**Drugi etap** to kodowanie danych, gdzie każdemu znakowi przypisywany jest kod **Huffmana**, który składa się z 0 i 1 i reprezentuje ścieżkę od korzenia do liścia, na którym znajduje się dany znak. Kody o długości równej liczbie bitów wymaganych do reprezentowania danego znaku są nazywane kodami o stałej długości, a kody o długości mniejszej niż liczba bitów wymaganych do reprezentowania danego znaku są nazywane kodami o zmiennej długości.


**Kodowanie danych** polega na zastąpieniu każdego znaku w pliku jego kodem Huffmana. Oryginalny plik zostaje zastąpiony kodem **Huffmana**, który jest znacznie mniejszy niż oryginalny plik. W celu zdekompresowania pliku, należy użyć drzewa Huffmana, aby odczytać kody Huffmana i zamienić je na oryginalne znaki.

# Stosowanie 
Compressor jest urochomiany z terminala z nazwą pliku do skompresowania przekazaną jako parametr.
Domyślnie compressor doda rozszerzenie pliku .code podczas kompresji.


| Opcja        | Działanie  
| :---         | :---         | 
|    -f        |     Ścieżka pliku do skompresowania          
|    -s [KB]   | Wyświetlanie rozmiaru pliku przed i po kompresji     
|    -h        |  Wyświetla okno pomocy (pomoc)  

# Opis funkcji programu

## **./Huffman_Node.h**

--Struktura węzła jest definiowana za pomocą instrukcji typedef.

--Ma pięć pól: **data**, **freq**, **arr**, **left** i **right**.

--**data** to liczba całkowita reprezentująca dane przechowywane w węźle.

--**freq** to liczba całkowita reprezentująca częstotliwość danych.

--**arr** to wskaźnik znakowy, który przechowuje kod binarny danych.

--**left** i **right** są wskaźnikami do struktur węzłów, które reprezentują odpowiednio lewe i prawe dziecko bieżącego węzła.

--**createNewNode**(int,int,node*,node*) to funkcja, która przyjmuje cztery argumenty: dwie liczby całkowite data i freq oraz dwa wskaźniki do struktur węzłowych po lewej i prawej stronie. Przydziela pamięć dla nowej struktury węzłów i inicjalizuje jej pola podanymi argumentami. Funkcja zwraca wskaźnik do nowej struktury węzłów.

--**free_node**(node*) to funkcja, która przyjmuje jako argument wskaźnik do struktury węzła i zwalnia przydzieloną jej pamięć.

## **./MinHeap.h**
