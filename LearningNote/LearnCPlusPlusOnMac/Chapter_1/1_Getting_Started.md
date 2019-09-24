- [- revernue# Getting Started](#--revernue-getting-started)
- [Contents](#contents)
- [Words](#words)
  - [introduce](#introduce)
  - [element](#element)
  - [most of](#most-of)
  - [briefly](#briefly)
  - [along the way](#along-the-way)
  - [work through](#work-through)
  - [be able to](#be-able-to)
  - [assume](#assume)
  - [detail](#detail)
  - [transaction](#transaction)
  - [copies](#copies)
  - [the sale of](#the-sale-of)
  - [identifier](#identifier)
  - [from time to time](#from-time-to-time)
  - [compute](#compute)
  - [revernue](#revernue)
---
## Contents
  Section 1.1 Writing a Simple C++ Program
  Section 1.2 A First Look at Input/Output
  Section 1.3 A Word about Comments
  Section 1.4 Flow of Control
  Section 1.5 Introducing Classes
  Section 1.6 The Bookstore Program
  Chapter Summary
  Defined Terms

---
This chapter  [introduce](#introduce) [most of](#most-of) the basic [element](#element) of C++: types, variables,expressions,statments, and functions.  
这章介绍了 大多C++的基础元素：类型，变量，表达式，语句， 和函数。  
[along the way](#along-the-way), we'll [briefly](#briefly) explain how to compile and execute a program.  
一路上?(翻译成 期间 比较好？)，我们将会 简单地介绍 如何 编译和运行一个程序。  

After having read this chapter and [worked through](#work-through) the exercises, you should [be able to](#be-able-to) write, compile, and execut simple programs.  
阅读完本章以及完成了这些练习，你应该有能力编写，编译，和运行简单的程序。  
Later chapters will [assume](#assume) that you can use the features introduced in this chapter, and will explain these features in more [detail](#detail).  
之后的章节将会假定： 你能 使用 这些特征被介绍在本章中的(翻译成 你能使用本章中介绍的这些特性)， 并 更详细地介绍这些特性。  

The way to learn a new programming language is to write programs.  
学习一个新的编程语言的方法 是 写程序。  
In this chapter, we'll write a program to solve a simple problem for a bookstore.  
这一章里， 我们 编写一个程序  去解决 一个书店的简单问题。  

Our Store keeps a file of [transactions](#transaction), each of which records [the sale of](#the-sale-of) one or more [copies](#copies) of a single book.  
我们的商店(书店吧？)保存了 一份 交易文件,  每一条 记录了一本书的 一册或多册 的销售（加个数据会好听点？）  
我们的书店保存了一份交易文件，每一条记录了一本书的销售数据(数据可能是一册或多册的)  
Each transaction contains three data elements:  
每条交易 包含了 三个 数据元素：  
    0-201-70353-X 4 24.99  

The first element is an ISBN(International Standard Book Number, a unique book [identifier](#identifier)), the second is the number of copies sold, and the last is the price at which each of these copies was sold.  
第一个元素是一个ISBN(国际标准书号， 一本书的唯一身份标识符)， 第二个 是 售出册数， 最后一个是 售出册数的平均价格。  
[From time to time](#from-time-to-time), the bookstore owner reads this file and for each book [computes](#compute) the number of copies sold, the total [revernue](#revernue) from that book, and the average sale price.  
有时， 书店店主会看这些记录， 计算每本书的销售册数，和 书的总收入， 和 书的平均售价

To be able to write this program, we need to cover a few basic C++ features.  
为了有能力写这个程序， 我们需要 掌握 极少的 基础的C++特性.  
In addition, we'll need to know how to compile and execute a program.  
此外，我们也需要知道如何编译 和 运行一个程序。  

Altough we haven't yet designed our program, it's easy to see that it must  
尽管我们还没有开始设计我们的程序，但有些是显然必须的？：  
  * Define variables
  * Do input and output
  * Use a data structure to hold the data
  * Test whether two records have the same ISBN  
  * Contain a loop that will process every record in the transactioin file  

  * 定义变量
  * 进行输入输出
  * 使用一个数据结构去存储数据
  * 测试两条记录是否有相同的ISBN
  * 有一个循环，能够处理任何记录在这个交易文件里

We'll start by reviewing how to solve these subproblems in C++ and then write our bookstore program.  
我们将会开始 浏览?（介绍）在C++中 如何解决这些子问题，然后写我们的书店程序

---
## Words
<font color="pink"></font>
---
### introduce
Word forms: 3rd person singular present tense **introduces**, prsent participle **introducing**, past tense,past participle **introduced**
#### 1. [VERB] [V noun] [V n into/to n] [be V-ed into/to n]
<font color="pink">To **introduce** something means to cause it to enter a place or exist in a system from the first time.</font>
* The Government has **introduced** a number of other money-saving moves... *\[VERB noun\]*
* I kept the birds indoors all winter and **introduced** them into an aviary the following June.  *\[V n into/to n\]*
* The word 'Pagoda' was **introduced** to Europe by the 17th century Portuguese. *\[beV-ed + into/to\]*

#### 2. [VERB] [V n to n]
<font color="pink">If you **introduce** someone to something , you cause them to learn about it or experience it for the first time.</font>
* He **introduced** us to the delights of natural food. *\[VERB noun + to\]*
---
### element
Word forms: plural **elements**
#### 1. countable noun[usually plural]
<font color="pink">The different **elements** of something are the differen parts it contains.</font>
* The exchange of prisoners of war was one of the key **elements of** the U.N.'s peace plan. *\[+of\]*

**Synonyms:** component, part, feature, unit

#### 2. countable noun
<font color="pink">A particular **element** of a situation, activity, or process is an important quality or feature that it has or needs.</font>
* Fitness has now become an important **element** in out lives.

#### 3. countable noun[usually plural]
<font color="pink">When you talk about **elements** within a society or organization, you are referring to groups of prople who have similar, beliefs, or habits.</font>
* ...criminal **elements** within the security forces.
* ...the hooligan **element**

**Synonyms:** group, faction, clique, set

---
### most
Most is often considered to be the superlative form of much and , many.
#### 1. quantifier
<font color="pink"> You use most to refer to the majority of a  group of things or people or the largest part of something.</font>
* **Most of** the houses in the capital don't have piped water. *\[+of\]*
* By stopping smoking you are undoing **most of** the damage smoking has caused.*\[+of\]*
* Sadly, **most of** the house was destroyed by fire in 1828. *\[+of\]*

<font color="pink">**Most** is also a determiner</font>
* **Most** people think the Queen has done a good job during her reign.
* **Most** companies are looking to sponsor students on specific courses.

<font color="pink">**Most** is also a pronoun</font>
* Seventeen civilians were hurt. **Most** are students who had been attending a party.
* All of the rooms have private baths, and **most** have radios and TV.

**Synonyms:** nearly all, the majority, the mass, almost all

#### 2. adjective
<font color="pink">You use **the most** mean a larger amount than anyone or anything else, or the largest amount possible.</font>
* The President himself won **the most** votes.
* The skippers get **the most** money, and after them the cooks.
* Tom had **the most** authority of all.

---
### along the way
#### phrase
<font color="pink">If something happens **on the way** or **along the way**, it happens during the course of a particular event or process</font>
* You may have to learn a few new skill **along the way**.

---
### briefly
#### 1. adverb[ADVERB with verb]
Something that happens or is done **briefly** happens or is done for a very short period of time.
* He smiled **briefly**
* Guerillas captured and **briefly** held an important provincial capital.

#### 2. adverb[ADVERB with verb]
If you say or write something **briefly**, you use very few word or give very few details.
* There are four basic alternatives; they are described **briefly** below.

**Synonyms:** in outline, in brief, in passing, in a nutshell

---
### work through
to resolve(a problem, esp an emotional one), by thinking about it repeatedly and hence lessening its intensity either by gaining insight or by becoming bored by it.

---
### be able to
#### phrase
If you **are able to** do something, you have skills or qualities which make it possible for you to do it
* The older child should **be able to** prepare a simple meal.
* The company say **they're able to** keep pricing competitive.
* They seemed **able to** work together very efficiently.

#### phrase
If you **are able to** do something, you have enough feedom, power, time, or money to do it.
* You'll be able to read in peace.
* Have you been able to have any kind of contact?
* It would be nice to be able to afford to retire earlier.

---
### assume
Word forms:3rd person singular present tense **assumes**, present participle **assuming**, past tense, past participle **assume**
#### 1. verb
If you **assume that** something is true, you imagine that it is true, sometimes wrongly.
* It is misconception to **assume that** the two continents are similar. *\[VERB that\]*
* If the package is wrapped well, we **assume** the contents are also wonderful.  *\[VERB that\]*
* If mistakes occured, they were **assumed to** be the fault of the commander on the spot. *\[be VERB-  ed to-infinitive\]*
* "Today?"--"I'd" assume so, yeah.*\[V so\]*

**Synonyms:** presume, think, beleve, expect.

#### 2. verb
If someone assumes power or responsibility, they take power or responsibility.
* My Cross will assume the role of Chief Executive with a team of four director *\[VERB noun\]*
* If there is no president, power will be assumed by the most extremist forces. *\[VERB noun\]*

---
### detail
Word forms:plural, 3rd person singular present tense **details**, present participle **detailing**, past tence, past participle **detailed**
#### 1. countable noun
The **details of** something are its individual features or elements.
* The details of the plan are still being worked out. *\[ + of\]*
* No details of the discussions have been given.

#### 2. plural noun[adjective NOUN]
**Details** about someone or something are facts or pieces of information about them.
* See the bottom of this page for details of how to apply for this exciting offer. *\[ + of\]*
* Full details will be announced soon.

#### 3. countable noun[oft adjective NOUN]
A **detail** is minor point or aspect of something, as opposed to the central ones.
* Only minor details now remain to be settled.


---
### transaction
### copies
### the sale of
### identifier
### from time to time
### compute
### revernue
### cover
### feature
### in addition
### reviewing
### subproblems
