![Language](https://img.shields.io/badge/language-C-blue) [![Contributors][contributors-shield]][contributors-url] [![Forks][forks-shield]][forks-url] [![Stargazers][stars-shield]][stars-url] [![Issues][issues-shield]][issues-url] [![MIT License][license-shield]][license-url] [![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />

<p align="center">
  <h3 align="center">Persistent Data Structures</h3>
  <p align="center">
    Fully Persistent DS and Partially Persistent DS  
    <br />
    <a href=https://github.com/vineeths96/Persistent-Data-Structures><strong>Explore the repository»</strong></a>
    <br />
    <br />
    <a href=https://github.com/vineeths96/Persistent-Data-Structures/blob/master/Problem%20Statement.pdf>View Problem Statement</a>
    </p>





</p>

> tags : persistent data structure, full persistence, partial persistence, heterogeneous vector, stack, queue, map, dequeue, linked list



<!-- ABOUT THE PROJECT -->

## About The Project

This project implements a small library of persistent data structures in C. A persistent data structure is a data structure that always preserves the previous version of itself when it is modified. They are effectively immutable, in the sense that their operations do not (visibly) update the
structure in-place, but always produce a new updated version. A data structure is partially persistent if all versions can be accessed but only the newest version can be modified. The data structure is fully persistent if every version can be both accessed and modified. In this program, each node contains a modification box with a timestamp to hold a single modification. If more than modification is applied to a node, the node is split to create a new node with the latest values. Amortized O(1) time and space can be achieved for access and updates using this method. This method was originally given by Sleator, Tarjan et al. Each node contains a modification box that can hold:

* One modification to the node (the modification could be of one of the pointers, or to the node’s key or to some other node-specific data)
* The time instance (or version number) when the mod was applied. The timestamp is essential for tracing the path to the version of the node we care about.

This library supports both partially and fully persistent versions of the data structures. The library includes the following data structures and all the usual operations on them.

1. Heterogeneous vector (supports elements of different types)
2. Map
3. Stack
4. Queue 
5. Double-ended queue
6. Singly linked linked list
7. Doubly linked linked list

The library has separate directories for partial and full persistence. Within each directory, there are sub-directories --- each corresponding to a particular data structure. The program for each data structure is written in three files - `client.c`, `header.c`, and `implement.c`. Comments have been added frequently to help in understanding the logic behind implementation. The`client.c` files contains some basic testing of the the persistence for the data structures. Refer [Problem statement](./Problem%20Statement.pdf) file for detailed information.



### Built With
This project was built with 

* C
* Ubuntu 18.04.1 
* gcc version 7.4.0



<!-- GETTING STARTED -->

## Getting Started

Clone the repository into a local machine using

```shell
git clone https://github.com/vineeths96/Persistent-Data-Structures
```

### Instructions to run

##### Fully Persistent Data Structures

Open the terminal, and `cd` to the directory of the data structure within `Fully Persistent Data Structures`.  

```
cd Fully Persistent Data Structures/<DataStructure>
```

Make the program and run it.

```shell
make
./a.out
```

##### Partially Persistent Data Structures

Open the terminal, and `cd` to the directory of the data structure within `Partially Persistent Data Structures`.  

```
cd Partially Persistent Data Structures/<DataStructure>
```

Make the program and run it.

```shell
make
./a.out
```



<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Vineeth S - vs96codes@gmail.com

Project Link: [https://github.com/vineeths96/Persistent-Data-Structures](https://github.com/vineeths96/Persistent-Data-Structures)




<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/vineeths96/Persistent-Data-Structures.svg?style=flat-square
[contributors-url]: https://github.com/vineeths96/Persistent-Data-Structures/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/vineeths96/Persistent-Data-Structures.svg?style=flat-square
[forks-url]: https://github.com/vineeths96/Persistent-Data-Structures/network/members
[stars-shield]: https://img.shields.io/github/stars/vineeths96/Persistent-Data-Structures.svg?style=flat-square
[stars-url]: https://github.com/vineeths96/Persistent-Data-Structures/stargazers
[issues-shield]: https://img.shields.io/github/issues/vineeths96/Persistent-Data-Structures.svg?style=flat-square
[issues-url]: https://github.com/vineeths96/Persistent-Data-Structures/issues
[license-shield]: https://img.shields.io/badge/License-MIT-yellow.svg
[license-url]: https://github.com/vineeths96/Persistent-Data-Structures/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/vineeths

