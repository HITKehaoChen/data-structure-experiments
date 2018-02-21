# Introduction

This repository contains the content of every experiment on data structure course in Harbin Institute of Technology.

As a learner, it is common for you to find some mistakes or pitfalls. If so, just point it out, with my appreciation.

<br>

# Index of Experiments

[Experiment-1st](#Experiment-1st)
> [1.Infix-Notation-and-Prefix-Notation](#expression)
>
> [2.Polynomial](#Polynomial)

[Experiment-2nd](#Experiment-2nd)
> [1.The-Creation-and-Traversal-of-the-Binary-Tree-Structure](#Binary-Tree)
>
> [2.Which-Two-Kinds-of-Traversal-Can-Uniquely-Identify-a-Binary-Tree?](#Identification)

[Experiment-3rd](#Experiment-3rd)
> [1.The-Creation-and-Traversal-of-the-Undirected-Graph](#Undirected-Graph)
>
> [2.Dijkstra's-and-Floyd-Warshall's-Algorithms](#Shortest-Path)

[Experiment-4th](#Experiment-4th)
> [1.AVL-Tree](#AVL-Tree)
>
> [2.Search-and-Sort](#Search-and-Sort)
>

<br>

# Contents of Each Experiment

## <a name="Experiment-1st"></a>Experiment-1st: 线性结构及其应用

### <a name="expression"></a>1.Infix-Notation-and-Prefix-Notation

> **Status**: basically finished
>
> **Things to Be Done**: string processing, expression ADT...
>
> [>>>Code Page<<<][11]

表达式求值是实现程序设计语言的基本问题之一，也是栈的应用的一个典型例子。一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。假设操作数是正整数，运算符只含加减乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，如：#（7+15）\*（23-28/4）#。引入表达式起始、结束符是为了方便。设计一个程序，演示用算符优先法对算术表达式求值的过程。

实验要求：

1.	从文本文件输入任意一个语法正确的（中缀）表达式，显示并保存该表达式。
2.	利用栈结构，把上述（中缀）表达式转换成后缀表达式，并显示栈的状态变化过程和所得到的后缀表达式。
3.	利用栈结构，对上述后缀表达式进行求值，并显示栈的状态变化过程和最终结果。
4.	将操作数类型扩充到实数、扩充运算符集合，并引入变量操作数，来完成表达式求值。

* * *

### <a name="Polynomial"></a>2.Polynomial

> **Status**: basically finished
>
> **Things to Be Done**: string processing...
>
> [>>>Code Page<<<][12]

设计线性表的链式存储结构，并实现一元多项式的代数运算。

实验要求：

1. 以链表存储一元多项式，在此基础上完成对多项式的代数操作。
2. 能够输入多项式（可以按各项的任意输入顺序，建议按指数降幂排列的多项式）和输出多项式（按指数降幂排列）,以文件形式输入和输出，并显示。
3. 能够计算多项式在某一点x=x0的值，其中x0是一个浮点型常量，返回结果为浮点数。
4. 能够给出计算两个多项式加法、减法、乘法和除法运算的结果多项式，除法运算的结果包括商多项式和余数多项式。
5. 要求尽量减少乘法和除法运算中间结果的空间占用和结点频繁的分配与回收操作。（提示：利用循环链表结构和可用空间表的思想，把循环链表表示的多项式返还给可用空间表，从而上述问题）。

<br>

## <a name="Experiment-2nd"></a>Experiment-2nd: 树型结构及其应用

### <a name="Binary-Tree"></a>1.The-Creation-and-Traversal-of-the-Binary-Tree-Structure

> **Status**: basically finished
>
> **Things to Be Done**: template, classes and more visual friendliness
>
> [>>>Code Page<<<][21]

树型结构的遍历是树型结构算法的基础，本实验要求编写程序演示二叉树的存储结构的建立方法和遍历过程。 

实验要求：

1. 至少采用两种方法，编写建立二叉树的二叉链表存储结构的程序，并以适当的形式显示并保存二叉树。
2. 采用二叉树的二叉链表存储结构，编写程序实现二叉树的先序、中序和后序遍历的递归和非递归算法以及层序遍历算法，以适当的形式显示并保存二叉树和相应的遍历序列。
3. 在二叉树的二叉链表存储结构基础上，编写程序实现二叉树的中序线索链表存储结构建立的算法，以适当的形式显示并保存二叉树的相应的线索链表。
4. 在二叉树的线索链表存储结构上，编写程序实现求二叉树一个结点的中序遍历的前驱结点和后继结点的算法。
5. 以上条要求为基础，编写程序实现对中序线索二叉树进行中序遍历的非递归算法，以适当的形式显示并保存二叉树和相应的中序遍历序列。

* * *

### <a name="Identification"></a>2.Which-Two-Kinds-of-Traversal-Can-Uniquely-Identify-a-Binary-Tree?

> **Status**: basically finished
>
> **Things to Be Done**: more visual friendliness
>
> [>>>Code Page<<<][22]

（二叉）树型结构一共有三种遍历方式，前序遍历、中序遍历及后序遍历，那么根据其中的哪两种可以唯一确定一个树呢？答案是中序遍历和前序遍历，抑或中序遍历和后序遍历。而仅知道前序遍历与后序遍历是无法确定一个树的，因为*前序遍历与后序遍历都是表达了左子树与右子树的相对关系并没有指明父结点的位置，缺失了创建一个树的必要信息，也就必然无法唯一确定一个树了。*

下面以前序遍历和中序遍历唯一确定一个树为例：

    Inorder sequence: D B E A F C
    Preorder sequence: A B D E C F

In a Preorder sequence, leftmost element is the root of the tree. So we know ‘A’ is root for given sequences. By searching ‘A’ in Inorder sequence, we can find out all elements on left side of ‘A’ are in left subtree and elements on right are in right subtree. So we know below structure now.

                 A
               /   \
              /     \
           D B E     F C

We recursively follow above steps and get the following tree.

             A
           /   \
          /     \
         B       C
        / \     /
       /   \   /
      D     E F

And Here is the algorithm:

> Algorithm: buildTree()
>
> 1) Pick an element from Preorder. Increment a Preorder Index Variable (preIndex in below code) to pick next element in next recursive call.
>
> 2) Create a new tree node tNode with the data as picked element.
>
> 3) Find the picked element’s index in Inorder. Let the index be inIndex.
>
> 4) Call buildTree for elements before inIndex and make the built tree as left subtree of tNode.
>
> 5) Call buildTree for elements after inIndex and make the built tree as right subtree of tNode.
>
> 6) return tNode.

<br>

## <a name="Experiment-3rd"></a>Experiment-3rd: 图型结构及其应用

### <a name="Undirected-Graph"></a>1.The-Creation-and-Traversal-of-the-Undirected-Graph

> **Status**: basically finished
>
> **Things to Be Done**: delete some unnecessary member functions
>
> [>>>Code Page<<<][31]

图的搜索（遍历）算法是图型结构相关算法的基础，本实验要求编写程序演示无向图三种典型存储结构的建立和（搜索）遍历过程。

实验要求：

1. 分别实现无向图的邻接矩阵、邻接表和邻接多重表存储结构的建立算法，分析和比较各建立算法的时间复杂度以及存储结构的空间占用情况。
2. 实现无向图的邻接矩阵、邻接表和邻接多重表三种存储结构的相互转换算法。
3. 在上述三种存储结构上，分别实现无向图的深度优先搜索（递归和非递归)和广度优先搜索算法。并以适当的方式存储和显示相应的搜索结果（深度优先或广度优先生成森林（或生成树）、深度优先或广度优先序列和编号）。
4. 分析搜索算法的时间复杂度。
5. 以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于10个，边不少于13个。
6. 软件功能结构安排合理，界面友好，便于使用。

* * *

### <a name="Shortest-Path"></a>2.Dijkstra's-and-Floyd-Warshall's-Algorithms

> **Status**: basically finished
>
> **Things to Be Done**: delete some unnecessary member functions, optimization
>
> [>>>Code Page<<<][32]

最短路径算法的实现

实验要求：

1. 实现单源最短路径的Dijkstra算法，输出源点到其他顶点的最短路径长度和最短路径（选做：利用堆结构，改进算法）。
2. 实现全局最短路径的Floyd-Warshall算法。输出任意两个顶点间的最短距离矩阵和最短路径矩阵，并输出任意两个顶点间的最短路径长度和最短路径。
3. 利用Dijkstra或Floyd-Warshall算法解决单目标最短路径问题：找出图中每个顶点v 到某个指定顶点c 最短路径。
4. 利用Dijkstra或Floyd-Warshall算法解决单顶点对间最短路径问题：对于某对顶点u 和 v，找出u 到v 和v到u的一条最短路径。
5. 利用Floyd-Warshall算法，计算有向图的可达矩阵，理解可达矩阵的含义。
6. 以文件形式输入图的顶点和边，并显示相应的结果。要求顶点不少于10个，边不少于13个。
7. 软件功能结构安排合理，界面友好，便于使用。

<br>

## <a name="Experiment-4th"></a>Experiment-4th: 查找结构与排序方法

### <a name="AVL-Tree"></a>1.AVL-Tree

> **Status**: basically finished
>
> **Things to Be Done**: tree class optimization
>
> [>>>Code Page<<<][41]

本实验要求编写程序实现AVL 存储结构的建立（插入）、删除、查找算法，并反映各种旋转变化。

实验要求：

1. 设计AVL 的左右链存储结构。
2. 实现AVL 左右链存储结构上的插入（建立）、删除、查找和排序算法。
3. 测试数据以文件形式保存，能反映插入和删除操作的四种旋转，并输出相应的结果。

* * *

### <a name="Search-and-Sort"></a>2.Search-and-Sort

> **Status**: basically finished
>
> **Things to be done**: a little bug in Quicksort
>
> [>>>Code Page<<<][42]

查找结构与排序方法的实现

实验要求：

1. 利用以下3组排序方法的一组分别对其进行排序，以图示的方式给出排序方法的运行时间随输入大小（问题规模）n的变化趋势，并与理论分析结果比较。
    1. 冒泡排序和快速排序；
    1. 插入排序和希尔排序；
    1. 选择排序和堆排序。
1. 对上述以排序的数据进行递归和非递归的二分（折半）查找。以图示的方式给出折半查找方法的运行时间随输入大小（问题规模）n的变化趋势，并与理论分析结果比较。

<br>

# Others

And if you would like to know more about my university, here is the entry for you:

[Harbin Institue of Technology][100]

[11]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-1st/1.Infix-Notation-and-Prefix-Notation "Go to the code page"

[12]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-1st/2.Polynomial "Go to the code page"

[21]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-2nd/1.The-Creation-and-Traversal-of-the-Binary-Tree-Structure "Go to the code page"

[22]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-2nd/2.Which-Two-Kinds-of-Traversal-Can-Uniquely-Identify-a-Binary-Tree%3F "Go to the code page"

[31]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-3rd/1.The-Creation-and-Traversal-of-the-Undirected-Graph

[32]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-3rd/2.Dijkstra's-and-Floyd-Warshall's-Algorithms

[41]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-4th/1.AVL-Tree

[42]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-4th/2.Search-and-Sort

[100]: https://en.wikipedia.org/wiki/Harbin_Institute_of_Technology "More information"
