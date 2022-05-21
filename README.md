# PAMSI (Data Structures, Algorithms and AI)
University assigment that contains four sub projects data structures, sorting algorithms, graph shortest path algorithms and droughts game
with artificial inteligence based on min-max algorithm. First three projects contains tests based on Cath2 library.

## [Data structers](Data_structeres)
#### Implemented data structures:  
* Doubly linked list (base for other except map)
* Stack
* Queue
* Priority Queue
* Hash map

## [Sorting algorithms](sort/sortowanie)
#### Implemented sorts:
* Bubble sort
* Heap sort
* Merge sort
* Quick sort

## [Graph shortest path algorithms](graphs)
#### Implemmted algorithms:
* Dijikstra 
* Bellman Ford
* Using both `Adjacency matrix` and `Adjacency list`

## [Droughts game](gra/gra)
#### Droughts game with graphical interface based on SDL2, with AI based on min-max algorithm.
<img src="https://user-images.githubusercontent.com/62207289/169647634-b6910d35-c410-40c2-8127-f7c37be9df5b.png" width="680" height="420">


## Getting started
#### 0. Install SDL2 library (Droughts only)
```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev
```
#### 1. Clone repo
```bash
git clone https://github.com/KacperSynator/PAMSI.git
```
#### 2. Create and enter build directory in subproject you want to build
```bash
mkdir build
cd build
```
#### 3. Build subproject
```bash
cmake ..
make
```
#### 4. Run
```bash
./<executable>
```
