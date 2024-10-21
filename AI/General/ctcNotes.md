# Connectionist Temporal Classification

> This algorithm is found during the study of [EasyOCR](https://github.com/JaidedAI/EasyOCR) whose architecture is shown as below.

![easy_ocr](./assets/easyocr_framework.jpeg)

> This notes is based on the learning of Paper [Sequence Modeling
With CTC](https://distill.pub/2017/ctc/)

> A helper video can be found here [Connectionist Temporal Classification (CTC) Explained](https://www.youtube.com/watch?v=jDPl1QJGLpE&t=162s)

An algorithm used to train deep neural networks in speech recognition, handwriting recognition and other sequence problems. **As the term itself states, it is an algorithm to help training, but not a model that is trainable.** It is more of a **loss function** to a model.

## The problem that CTC solves: Alignment

Especially, in speed recognition where inputs are outputs are not aligned. Ground truths in such situations are hard to be labeled. 

For example, an audio input may consists hundreds and thousands of tiny segments that will be used inputs feeding into a model (e.g. RNN), the expected output however may only consists of word `hello`. So this is an alignment issue `1000 -> 5`.

![issues](./assets/Screenshot%202024-10-21%20at%2023.15.24.png)

## Adding blank symbol

CTC added a blank symbol to help represent repeated symbols. For example the repeated letter `l` in `hello`.

For a longer input -> shorter input, if we simply to assign an output character to each input step and collapse repeats, as shown in the following, we may find ourselves in trouble representing `hello`. 

> We have no way to produce outputs with multiple characters in a row. Consider the alignment [h, h, e, l, l, l, o]. Collapsing repeats will produce “helo” instead of “hello”.

![alignment](./assets/Screenshot%202024-10-21%20at%2023.22.21.png)

## The Loss function

CTC is all about a loss function to a model. The objective of CTC loss function is to maximize the all the probability of all the alignments that can be collapsed to the output.

![loss](./assets/Screenshot%202024-10-22%20at%2000.45.47.png)

Given a possible character set plus a blank token, we can have many different combinations of them. All valid combinations (that can be collapsed to the final output) have to follow the following rules:

1. The alignment has the same length as the original input.
2. The order of characters of the alignment is the same as the output.
3. There has to be a blank token between repeated character e.g. `hello` -> `...l@l...`

**Given these, we can consider one input step a time and map that input to a possible alignment** (This is pure combination of alignment, that has nothing to do with RNN)

1. the current character.
2. a blank token
3. Next character

For example, given that the input is length 5, and the output is a,b,c. So the character set is {a, b, c, @}, where @ is blank.

The first input step:

the first step can be `a` or `@` so that the alignment is still following the rules.
the second step can be `a` or `@` or `b` to be considered following the rules so that can be collapsed into the output.

Such, combination will results in many alignments shown as the following.

![alignment](./assets/Screenshot%202024-10-22%20at%2000.57.27.png)

> Following each path is a valid alignment.

A video illustration can be found [here](https://youtu.be/jDPl1QJGLpE?t=692).

**Still remember the objective of loss is to take the sum of all the probability of each valid alignments.**

To calculate the probability of 1 single valid alignment, we need the product of probability of having a specific token at each input step. Where is the probability of each node from? The RNN.

Running the original input (audio) into a RNN, each round, we get the probability of each possible output character, in total its a matrix of probabilities. We can use that matrix to calculate the probability of alignment.

![RNN](./assets/Screenshot%202024-10-22%20at%2001.02.32.png)

The computation of the loss function requires us to follow all the path of the graph shown above and combine the result of RNN. This process can be optimized using Dynamic programming. 

For each node, there's only 2 cases where the probability of getting there can happen.

More details can be found in the video [Connectionist Temporal Classification (CTC) Explained](https://youtu.be/jDPl1QJGLpE?t=918)









