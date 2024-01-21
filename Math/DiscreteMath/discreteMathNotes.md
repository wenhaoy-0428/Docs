# Discrete Math

Good material: [Discrete Math](https://www.youtube.com/watch?v=hWEZsyF3ZZc&list=RDCMUCcbu9qaBn3MNFYr96mbg72w&index=1)

## Implication

Implication is denoted as $p \to q$ meaning **If p then q**

Different from `conjunction (A.K.A and)` and `disjunction (A.K. A or)`, the truth table of implication when `p` is *false*, the implication is always *true* regardless of `q`. [Reference](https://youtu.be/rAxXcX_w5fE?list=PLl-gb0E4MII28GykmtuBXNUNoej-vY5Rz&t=1050)

| p    | q    | p -> q |
| :--- | :--- | :----- |
| T    | T    | T      |
| T    | F    | F      |
| F    | T    | **T**  |
| F    | F    | F      |


#### Conditional Implications

From the original implication $p \to q$, we can also have 4 more conditional implications

1. Converse: $q \to p$
2. Inverse: $\neg p \to \neg q$

3. Contrapositive: $\neg q \to \neg p$
4. Bi-conditional:  $p \leftrightarrow q$ known as `p if and only if q`
> For a bi-conditional implication to be true, both proposition must **share the same value**.

> `If and only If` is not the same as `Only If`. `Only If` simply creates the **reverse** statement. ["If and only if" vs. "if" or "only if", what’s the difference?](https://www.alphascore.com/post/if-and-only-if-vs-if-or-only-if-whats-the-difference#:~:text=IF%20AND%20ONLY%20IF%2C%20is,statement%20that%20works%20both%20ways.&text=Note%20that%20IF%20AND%20ONLY%20IF%20is%20different%20than%20simply%20ONLY%20IF.)

### Translate Implication 

1. You can get a free sandwich **If** you buy a sandwich or a cup of coffee. 

p: I buy a sandwich
q: I buy a cup of coffee
r: I get a free sandwich

**Answer:** $(p \vee q) \to r$

2. You can get a free sandwich **only if** you buy a sandwich or a cup of coffee.

> `Only If` is simply a reverse of If. ["If and only if" vs. "if" or "only if", what’s the difference?](https://www.alphascore.com/post/if-and-only-if-vs-if-or-only-if-whats-the-difference#:~:text=IF%20AND%20ONLY%20IF%2C%20is,statement%20that%20works%20both%20ways.&text=Note%20that%20IF%20AND%20ONLY%20IF%20is%20different%20than%20simply%20ONLY%20IF.)

p: I buy a sandwich
q: I buy a cup of coffee
r: I get a free sandwich

**Answer:** $r \to (p \vee q)$


## Use Truth Table to solve logic puzzle

When planning a party, you want to know whom to invite. Among the people you would like to invite are three touchy friends. You know that 

1. **if Jasmine attends, she will become unhappy if Samir is there.** 

2. **Samir will attend only if Kanti will be there**

3. Kanti will not attend unless Jasmine also does. 

Which combinations of these three friends can you invite so as not to make someone unhappy.

### Solution

1. We first create a truth table that contains all possibilities based on the friends we have.

2. Write down each compound based on the 3 requirements above.

3. Fill in the table and **only all propositions matched up with the combination can we select it as a valid one.**

![](./Assets/Screenshot%202023-05-24%20at%2020.11.10.png)

A detail walkthrough can be found at [Solving Logic Puzzles](https://youtu.be/N2YHianzseI?list=PLl-gb0E4MII28GykmtuBXNUNoej-vY5Rz&t=556)


## Equivalence

Two propositions are equivalent when they share the same truth table in all possible cases. 

### Laws

T: tautology (always true)
F: contradiction (always false)

* **Commutative Laws**

$$
p \vee q = q \vee p \\
p \wedge q = q \wedge p
$$

* **Associative Laws**

$$
(p \vee q) \vee r = p \vee (q \vee r) \\
(p \wedge q) \wedge r = p \wedge (q \wedge r)
$$

* **Distributive Laws**

$$
p \vee (q \wedge r) = (p \vee q) \wedge (p \vee r) \\ 
p \wedge (q \vee r) = (p \wedge q) \vee (p \wedge r)
$$

* **DeMorgans's Laws**

$$
\neg (p \wedge q) = \neg p \vee \neg q\\
\neg (p \vee q) = \neg p \wedge \neg q
$$

Other equivalent propositions

![](./Assets/Screenshot%202023-05-24%20at%2015.50.43.png)
 


## Predicate Logic

For statements like `x < 3` is not a proposition because it contains a variable and we don't know it. In this statement, `x` is a variable `is less than 3` is what we call a predicate which states the property of the variable. The above above statement can be further written as `P(x) = x < 3` which is also known as a `propositional function`. 

> A propositional function is not a proposition until all values of variables are provided.

Example:

`P(x) denotes x > 0` 

$P(3) \vee p(-1) \equiv T \vee F \equiv T$

In predicate logic, `variables: x,y,z`, `predicates: a property the variable has`, `quantifier` are included. Also a variable can have a domain which states the space the value can be selected from. 

### [Quantifier](https://www.youtube.com/watch?v=DpcUJrYTduc&list=PLl-gb0E4MII28GykmtuBXNUNoej-vY5Rz&index=11)

A quantifier is a symbol used to express the **scope or extent** of a variable in a logical formula. It specifies **how many objects in a domain** satisfy a given predicate or property.

Two main quantifier in predicate logic are:

1. Universal Quantifier (∀): The universal quantifier (∀) is used to express that a certain property or predicate holds for all objects in the domain. It asserts that a statement is true for every possible substitution of the variable.
   
> Example: ∀x P(x) means "For all x, P(x)" or "For every x, P(x)".
This quantifier indicates that the property P holds for every object x in the domain.

1. Existential Quantifier (∃): The existential quantifier (∃) is used to express that there exists at least one object in the domain that satisfies a given property or predicate. It asserts the existence of an object for which the statement is true.

> Example: ∃x P(x) means "There exists an x such that P(x)" or "There is an x for which P(x)".
This quantifier indicates that there is at least one object x in the domain for which the property P holds.

!> $\forall x P(x)$ can be denoted as $P(x_1) \vee P(x_2) \vee P(x_3)...P(x_n)$ where $x_n$ is the all possible values in domain of x.

!> $\exist x P(x)$ can be denoted as $P(x_1) \wedge P(x_2) \wedge P(x_3)...P(x_n)$

#### Negating Quantifier

$\neg\forall x P(x)$ means `not all x Px`. For example, If P(x) is a student in class is older than 18, then $\neg\forall x P(x)$ means not all students in class is older than 18. Which is equivalent to $\exist x \neg P(x)$

$\neg x P(x)$ means `not exist x Px`. For example, If P(x) is a student in class is older than 18, then $\neg\exist x P(x)$ means there doesn't exist a student who is older than 18. Which is equivalent to $\forall x \neg P(x)$

* This introduces to **DeMorgan's Law for quantifiers**

$$
\neg\forall x P(x) \equiv \exist x \neg P(x) \\
\neg\exist x P(x) \equiv \forall x \neg P(x)
$$


#### Translation of Quantifier

Translation of quantifier highly depends on `domain` of x

**Some student** in this class has visited Mexico
* Domain: students in class

    let `M(x)` be **x has visited Mexico**

    **result:** $\exist x M(x)$

* Domain: **All people**

    let `M(x)` be **x has visited Mexico**
    let `C(x)` be **x is a student in this class**

    **result:** $\exist x (M(x) \wedge C(x))$

    > Since the domain is different from the scope in the statement, we have to add an additional proposition.

**Every student** in this class has visited Canada *or* Mexico
* Domain: students in this class
    
    let `M(x)` be **x has visited Mexico**
    
    let `C(x)` be **x has visited Canada**
    
    **result:** $\forall x (C(x) \vee M(x))$

* Domain: All people
    
    let `M(x)` be **x has visited Mexico**
    
    let `C(x)` be **x has visited Canada**

    let `S(x)` be **x is a student in this class**
    
    **result**: $\forall x (S(x) \to C(x) \vee M(x))$
    
    > The reason we have to use implication is that if we use **and** the meaning is totally different. That would be all people are students in this class.



## Inference for Propositional Logic

An argument is what called a sequence of propositions $P_1, P_2 ... P_n$ or called **premises**, implies $q$ or called conclusion. 

$$
P_1 \wedge P_2 \wedge P_3 ... P_n \to q
$$

A valid argument is that the argument is a tautology.

### Rules of Inference

* **Modus Ponens**

   Given a true premise $p \to q$, and $p$ is true, then $q$ must be true.

$$
((p \to q) \wedge p) \to q
$$

* **Modus Tollens**

   Given a true premise $p \to q$, and $q$ is false, then $p$ must be false is a valid argument.

$$
((p \to q) \wedge \neg q) \to \neg p \\
$$

Note: $p \to q \equiv \neg q \to \neg p$ according to [Equivalence](#equivalence) so Modus Tollens can be transformed to Modus Ponens.


* **Hypothetical Syllogism**

   Given a true premise $p \to q$, and $q \to r$, then $q->r$ must be true.

$$
((p \to q) \wedge (q \to r) \to (p \to r))
$$

* **Disjunctive Syllogism**

   Given a true premise $p \vee q$, and $p$ is false, then $q$ must be true.

$$
((p \vee q) \wedge \neg r) \to q
$$

* **Addition**

    Given a true premise $p$, then $p \vee q$ must be true.

* **Simplification**
    
    Given a true premise $p \wedge q$, then $p$ must be true and $q$ must be true.

* **Conjunction**
    
    Given 2 true premises $p$ and $q$, then $p \wedge q$ must be true.

* **Resolution**

   Given a true premise $\neg p \vee r$, and $p \vee q$, then $q \vee r$ must be true.

$$
((\neg p \vee r) \wedge (p \vee q)) \to (q \vee r)
$$

### Example

![propositional_inference_practice](./Assets/Screenshot%202023-05-26%20at%2002.38.21.png)

## Inference for Quantifier

### Rules of inference

* **Universal Instantiation**

    Given a true premise $\forall x P(x)$ then $P(c)$ must also be true for an arbitrary $c$ in the same domain.

$$
\forall x P(x) \to P(c)
$$

* **Universal Generalization**

    Given a true premise $P(c) \text{for arbitrary c}$, then $\forall x P(x)$ must be true.

$$
P(c) \text{for arbitrary c} \to \forall x P(x)
$$

* **Existential INstantiation**

    Given a true premise $\exist x P(x)$, then $p(c)$ must be true **for some** $c$

$$
\exist x P(x) \to p(c) \text{ for some } c
$$

* **Existential Generalization**

    Given a true premise $p(c) \text{ for some } c$, then $\exist x P(x)$ must be true.

*  **Universal Modus Ponens**

    Given a true premise $\forall x P(x) \to Q(x)$ and $P(a) \text{ where a is arbitrary in the domain }$, then $Q(a)$ must also be true.

$$
((\forall x P(x) \to Q(x)) \wedge P(a)) \to Q(a)
$$


## Proof

A proof can be either **direct**, **contraposition**, **contradiction**, or **exhaustion**

### Direct Proof

In a direct proof, We assume the antecedent is true. Then use rules of inference, axioms, definitions and/or previously proven theorems to show the consequent is true. 

![direct_proof](Assets/Screenshot%202023-05-28%20at%2004.46.24.png)

In the above example, we use even numbers are equivalent to `2k` to prove the consequent.

### Proof by Contraposition

Contraposition is indirect proof. Based on a law according to [equivalence](#equivalence) $\neg p \to \neg q \equiv q \to p$. Thus, we can assume $\neg q$ is true and prove $\neg p$ is true to prove $p \to q$


![indirect_proof](Assets/Screenshot%202023-05-28%20at%2004.51.20.png)


### Proof by Contradiction 

We assume the the proposition is **false** and shows it can't be false to proof the original proposition is true. 

![proof_by_contradiction](Assets/Screenshot%202023-05-28%20at%2004.55.06.png)

For a single proposition, we just assume its negation is true and find that can't be possible

![proof_contradiction_proposition](Assets/Screenshot%202023-05-28%20at%2005.10.39.png)



For implication, we assume the **consequent** is false while the premise is true $p \wedge \neg q$.  Then shows this can't be possible.

![proof_contradiction_implication](Assets/Screenshot%202023-05-28%20at%2005.17.46.png)

### Proof by exhaustion

In this method, we will proof the proposition is true by prove all possible cases are true.

