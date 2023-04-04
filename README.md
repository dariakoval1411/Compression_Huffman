# **Huffman Compression**

Author Daria Koval 

**Program do beztratnej kompresji danych na podstawie algorytmu Huffman.**

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
|    -s [KB]   | Wyświetlanie rozmiaru w pliku przed i po kompresji oraz stopień kompresji pliku    
|    -h        |  Wyświetla okno pomocy (pomoc)  

# Opis funkcji programu

## **./Huffman.h**

--Struktura węzła jest definiowana za pomocą instrukcji typedef.

``` c
#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

/* The structure is responsible for storing the node.*/

typedef struct Node {
    int data;
    int freq;
    char *arr;
    struct Node* left;
    struct Node* right;
} node;

node * createNewNode(int,int ,node*,node*);

void free_node(node*);
#endif


#endif 
```

--Ma pięć pól: **data**, **freq**, **arr**, **left** i **right**.

--**data** to liczba całkowita reprezentująca dane przechowywane w węźle.

--**freq** to liczba całkowita reprezentująca częstotliwość danych.

--**arr** to wskaźnik znakowy, który przechowuje kod binarny danych.

--**left** i **right** są wskaźnikami do struktur węzłów, które reprezentują odpowiednio lewe i prawe dziecko bieżącego węzła.

--**createNewNode**(int,int,node*,node*) to funkcja, która przyjmuje cztery argumenty: dwie liczby całkowite data i freq oraz dwa wskaźniki do struktur węzłowych po lewej i prawej stronie. Przydziela pamięć dla nowej struktury węzłów i inicjalizuje jej pola podanymi argumentami. Funkcja zwraca wskaźnik do nowej struktury węzłów.

--**free_node**(node*) to funkcja, która przyjmuje jako argument wskaźnik do struktury węzła i zwalnia przydzieloną jej pamięć.

## **./MinHeap.h**


Jest to plik nagłówkowy do implementacji struktury danych sterty przy użyciu dynamicznego wektora połączenia. Struktura połączenia jest zdefiniowana w innym pliku nagłówkowym **Huffman_Node.h.**

Struktura **Min_Heap** zawiera wskaźnik do dynamicznej tablicy węzłów zwanej węzłami, a także zmienne określające aktualny rozmiar i pojemność sterty.

```c
#ifndef MINHEAP_H
#define MINHEAP_H

#include "Huffman_Node.h"

//The structure of a dynamic vector storing pointers to nodes.

typedef struct Min_Heap{
    node **nodes;
    int size;
    int capacity;

} minheap;

minheap *createMinHeap(int);
int double_node_capacity(minheap*);
int add_node(minheap*,node*);
void freeMinHeap(minheap*);

#endif  
```

Funkcje zadeklarowane w tym pliku nagłówkowym to:

-**createMinHeap**(int): Przydziela pamięć dla struktury **minheap** z początkową pojemnością int, inicjalizuje jej zmienne i zwraca do niej wskaźnik.

--**double_node_capacity**(minheap*): Podwaja pojemność tablicy węzłów sterty poprzez realokację pamięci i zwraca 1 w przypadku sukcesu, 0 w przypadku niepowodzenia.

--**add_node**(minheap*, node*): Dodaje wskaźnik węzła do tablicy nodes sterty i zapewnia zachowanie minimalnej właściwości sterty. Zwraca 1 w przypadku sukcesu, 0 w przypadku niepowodzenia.

--**freeMinHeap**(minheap*): Zwalnia przydział pamięci dla struktury **minheap** i jej tablicy węzłów.

## **./HeaderMap.h**

Jest to plik nagłówkowy służący do implementacji dynamicznego wektora ciągów do przechowywania nagłówków.

Struktura **Header_Map** zawiera wskaźnik do dynamicznej tablicy char* o nazwie name oraz zmienne określające aktualny rozmiar i pojemność wektora.
``` c
#ifndef HEADERMAP_H
#define HEADERMAP_H

//The structure of a dynamic vector storing pointers to strings.

typedef struct Header_Map{
    char **name;
    int size;
    int capacity;
}header;


header * createHeader(int);
int double_header_capacity(header*);
int add_header(header*,char*);
void free_header(header*);

#endif 
```
Funkcje zadeklarowane w tym pliku nagłówkowym to:

--**createHeader**(int): Przydziela pamięć dla struktury nagłówka o początkowej pojemności int, inicjuje jej zmienne i zwraca do niej wskaźnik.

--**double_header_capacity**(header*): Podwaja pojemność tablicy nazw wektorów poprzez realokację pamięci i zwraca 1 w przypadku sukcesu, 0 w przypadku niepowodzenia.

--**add_header**(header*, char*): Dodaje char* do tablicy nazw wektora i zwraca 1 w przypadku powodzenia, 0 w przypadku niepowodzenia.

--**free_header**(header*): zwalnia pamięć dla struktury nagłówka i jej tablicy nazw.


## **./Huffman.h**

Jest to plik nagłówkowy służący do implementacji algorytmu kodowania Huffmana, który kompresuje dane poprzez przypisywanie kodów o zmiennej długości do każdego symbolu na podstawie częstotliwości ich występowania.

Plik nagłówkowy zawiera pliki nagłówkowe dla struktur danych **Huffman_Node** i **MinHeap**.
``` c
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Huffman_Node.h"
#include "MinHeap.h"

int node_compare(const void *,const void *);
node * buildHuffmanTree(minheap *);
void read_codes(node*,minheap*,char*);
void free_HuffmanTree(node*);


#endif 
```

Funkcje zadeklarowane w tym pliku nagłówkowym to:

--**node_compare**(const void*, const void*): Funkcja porównania używana przez strukturę danych sterty minimalnej do porównania częstotliwości występowania dwóch węzłów.

--**buildHuffmanTree**(minheap*): Tworzy drzewo **Huffmana**, wielokrotnie usuwając dwa węzły o najniższej częstotliwości ze sterty minimalnej, łącząc je w jeden węzeł o częstotliwości równej sumie dwóch węzłów i dodając nowy węzeł do sterta minimalna. Zwraca wskaźnik do korzenia drzewa Huffmana.

--**read_codes**(node*, minheap*, char*): Przechodzi przez drzewo **Huffmana** w celu wygenerowania kodów o zmiennej długości dla każdego symbolu i przechowuje je w dynamicznym wektorze łańcuchów. Zwraca liczbę unikalnych symboli.

--**free_HuffmanTree**(węzeł*): zwalnia pamięć dla drzewa **Huffmana**.


## **./Encode.h**

Jest to plik nagłówkowy służący do implementacji funkcji kodowania algorytmu kodowania Huffmana.

Plik nagłówkowy zawiera plik nagłówkowy **MinHeap**.

``` c
#ifndef ENCODE_H
#define ENCODE_H

#include "MinHeap.h"

char *find_code(int,minheap*);
void encode(FILE*,FILE*,char*,minheap*);

#endif
```

Funkcje zadeklarowane w tym pliku nagłówkowym to:

--**find_code**(int, minheap*): Znajduje kod o zmiennej długości dla danego symbolu, przeszukując dynamiczny wektor kodów generowanych przez funkcję read_codes w **Huffman.h**. Zwraca wskaźnik do kodu.

--**encode**(FILE*, FILE*, char*, minheap*): Koduje dane w pliku wejściowym przy użyciu kodów **Huffmana** i zapisuje zakodowane dane do pliku wyjściowego. Funkcja zapisuje również informacje nagłówka, które obejmują liczbę unikalnych symboli i ich częstotliwości, do pliku wyjściowego przy użyciu określonego formatu. Argument char* to nazwa pliku wejściowego. Argument minheap* jest używany do określenia kodów Huffmana dla każdego symbolu.

## **/.main.c**

Zawiera  pliki  funkcji związanych z tworzeniem i manipulowaniem drzewami Huffmana, strukturami stert i kodowaniem do pliku (**Huffman.h,Encode.h,MinHeap.h,HeaderMap.h**)

Funkcja main zaczyna się od zdefiniowania zmiennych do iteracji, po których następują zmienne getopt do odczytu opcji wiersza poleceń. Tworzona jest również struktura nagłówka do przechowywania nazw plików, które mają zostać skompresowane. Funkcja **createHeader()** przydziela pamięć dla tej struktury i inicjalizuje jej pola.

Następnie istnieje opcja wyświetlania rozmiaru pliku przed i po kompresji. 

Następnie program wczytuje pliki do kompresji, zlicza częstotliwość bajtów w każdym pliku i tworzy struktury węzłów.

Węzły są następnie używane do budowania drzewa **Huffmana** za pomocą funkcji **buildHuffmanTree**.Jeśli funkcja zwraca wartość NULL, na konsoli wyświetlany jest komunikat o błędzie.
``` c
// Creating a tree
		root = buildHuffmanTree(nodes);
		if (root == NULL){
			fprintf(stderr, "%s: Tree memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}
```
Po zbudowaniu drzewa program tworzy kody dla każdego znaku w pliku i zapisuje zakodowane dane do pliku wyjściowego z rozszerzeniem .code. 
``` c
out_file_name = malloc(sizeof(char) * (file_name_n + 5));
		if (out_file_name == NULL){
			fprintf(stderr, "%s: Output file name memory allocation error: %s\n", argv[0], files->name[j]);
			return 3;
		}
		
		strcpy(out_file_name, file_name);
		strcat(out_file_name, ".code\0");
```				

Następnie program wypisuje na konsoli rozmiar pliku oryginalnego i pliku skompresowanego, jeśli podano opcję -s.

``` c
// Displaying file size before and after compression (call option)
		if (show_file_size){
			printf("%s\n", files->name[j]);
			printf("\tSize before compression ---->%ld [KB]\n", get_file_size(in));
			printf("\tCompressed size -----> %ld [KB]\n", get_file_size(out_file));
		}
```
Na koniec program zwalnia pamięć, która została przydzielona dynamicznie i kończy działanie z wartością zwróconą.

``` c
// Freeing memory so the next file can be overwritten
		free(file_name);
		free(out_file_name);
		freeMinHeap(nodes);
		
		for (i = 0; i < codes->size; i++)
			free_node(codes->nodes[i]);
		freeMinHeap(codes);
		
		free_HuffmanTree(root);
```

# Makefile 
---
Makefile służy do budowania i czyszczenia programu, który wykonuje kodowanie Huffmana na plikach.

Pierwsza linia określa zależności i polecenie kompilacji. Zawira listę plików żródłowych do skompilowania , a następnie polecenie skompilowania ich za pomocą kompilatora "cc" i wysłania skompilowanego programu do pliku o nazwie "compressor"
```
compressor: main.c Huffman_Node.c MinHeap.c HeaderMap.c Huffman.c Encode.c
    @cc main.c Huffman_Node.c MinHeap.c HeaderMap.c Huffman.c Encode.c -o compressor 
```

Druga sekcja to "czysty" cel, który ususwa wszelkie wygenerowane pliki z porzedniej kompilacji , takie jak plik wykonywalny "kompresora" i trzy zakodowane pliki.

``` 
clean:
    @rm -f compressor 
    @rm -f  ./test/picture2.code
    @rm -f ./test/picture1.code
    @rm -f ./test/LoremIpsum.code
``` 

# Kompilacja
```
make
```
# Działanie

Uruchom następujące polecenie dla kodowania Huffmana 
```
./compressor 
```
Uruchom następujące polecenie dla kodowania Huffmana z podaniem nazwy pliku 
```
./compressor -f/test/picture1.jpg -s
```
Dane polecenie kompresuje i wyświetlia rozmiar plika przed i po kompresji 
```
./compressor -f/test/picture2.bmp -s 

```
Dane polecenie kompresuje i wyświetlia rozmiar plika przed i po kompresji tekstowy plik 
```
./compressor -f/test/LoremIpsum.txt -s 
```
Dane polecenie jedmocześnie kompresuje  kilka plików 
```
./compressor -f/test/LoremIpsum.txt -f /test/picture1.jpg/ /test/picture2.bmp/ -f /test/LoremIpsum.txt 
```

Dane polecenie pokazuje rozmiar pliku przed kompresję i po kompresji 
```
./compressor -f/test/LoremIpsum.txt -f /test/picture1.jpg/ /test/picture2.bmp/ -f /test/LoremIpsum.txt -s 
```
Dane polecenie usuwa plik compresji i skompresowane pliki 
```
./compressor -f/test/LoremIpsum.txt -f /test/picture1.jpg/ /test/picture2.bmp/ -f /test/LoremIpsum.txt -s 
```

# Przykładowe wyjście 

**picture2.code** : zdekompresowany plik z obrazkiem 

**picture1.code** : zdekompresowany plik z obrazkiem 

**LoremIpsum.code** : zdekompresowany plik teksowy
