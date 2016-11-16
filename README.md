# Introduction

This repository contains the content of every experiments on data structure course in Harbin Institute of Technology.

As a learner, it is common for you to find some mistakes or pitfalls. If so, just point it out, with my deep appreciation.

<br>
# Index of Experiments

[Experiment-1st](#Experiment-1st)
> [1.Infix-Notation-and-Prefix-Notation](#expression)
>
> [2.Polynomial](#Polynomial)
>
> [3.The-Road-to-the-Exit-of-Maze](#Maze)

[Experiment-2nd](#Experiment-2nd)
> [1.The-Creation-and-Traversal-of-the-Binary-Tree-Structure](#Binary-Tree)
>
> [2.Which-Two-Kinds-of-Traversal-Can-Uniquely-Identify-a-Binary-Tree?](#Identification)
>
> [3.Huffman-Coding](#Huffman-Coding)

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

* * *

### <a name="Maze"></a>3.The-Road-to-the-Exit-of-Maze

> **Status**: *Unfinished*

一个迷宫可以看成是由m×n个房间组成的矩形，迷宫内部的每个房间有8个方向，每个方向或者有障碍（如墙）而不能通过，或者无障碍（如有门）而能通过。入口为左上角房间，出口为右下角房间，问是否有路径从入口到出口，若有则输出一条这样的路径；否则，提示“迷宫无入口到出口的路经”。

实验要求：

1.	设计一个迷宫及其障碍的表示方式，并能随机或手动生成迷宫。
2.	设计并实现一个非递归的算法，输出从入口到出口的一条路径（如存在）。
3.	设计并实现一个递归的算法，找出从入口到出口的一条路径（如存在）。
4.	如果有多条路径，设计并实现一个算法找到步数最少的路径（捷径）。
5.	如果有多条路径，设计并实现一个算法找到所有路径。
6.	以文件方式保存、并显示原始数据和结果。

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

> **Status**: *Unfinished*

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

* * *

### <a name="Huffman-Coding"></a>3.Huffman-Coding

> **Status**: *Unfinished*

哈夫曼编码是一种可以哈夫曼树（最优二叉树，带权路径长度最小的二叉树）为基础变长编码方式。它的基本思想是：将使用次数多的代码转换成长度较短的编码，而使用次数少的可以使用较长的编码，并且保持编码的唯一可解性。在计算机信息处理中，经常应用于数据压缩。是一种一致性编码法（又称"熵编码法"），用于数据的无损耗压缩。要求实现一个完整的哈夫曼编码与译码系统。

实验要求：

1. 从文件中读入任意一篇英文文本文件，分别统计英文文本文件中各字符（包括标点符号和空格）使用频率。
2. 根据字符的使用频率分别构造哈夫曼树，并给出每个字符的哈夫曼编码。
3. 将文本文件利用哈夫曼树进行编码，存储成压缩文件（哈夫曼编码文件）。
4. 计算哈夫曼编码文件的压缩率。
5. 将哈夫曼编码文件译码为文本文件，并与原文件进行比较。
6. 能否利用堆结构，优化的哈夫曼编码算法。
7. 上述1-5的编码和译码是基于字符的压缩，考虑基于单词的压缩，完成上述工作，讨论并比较压缩效果。
8. 上述1-5的编码是二进制的编码，采用K叉的哈夫曼树完成上述工作，实现“K进制”的编码和译码，并与二进制的编码和译码进行比较。

<br>
# Others

And if you would like to know more about my university, here is the entry for you:

[Harbin Institue of Technology][100]

[11]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-1st/1.Infix-Notation-and-Prefix-Notation "Go to the code page"
[12]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-1st/2.Polynomial "Go to the code page"

[22]: https://github.com/ANDI-Mckee/Data-Structure-Experiments/tree/master/The-2nd/1.The-Creation-and-Traversal-of-the-Binary-Tree-Structure "Go to the code page"

[100]: https://en.wikipedia.org/wiki/Harbin_Institute_of_Technology "More information"
