LangChain is driven by a few core beliefs:

* Large Language Models (LLMs) are great, powerful new technology.
* LLMs are even better when you combine them with external sources of data.LLMs will transform what the applications of the future look like. Specifically, the applications of the future will look more and more agentic.
* It is still very early on in that transformation.
* While it’s easy to build a prototype of those agentic applications, it’s still really hard to build agents that are reliable enough to put into production.


Today developers can choose how they build agents: use **LangChain** for maximum flexibility and control, or **Deep Agents** which allows for similar flexibility and control but comes with *opinionated built-in planning*, filesystem tools, subagents, and context management. Both are built on **LangGraph**. 




## Tools

https://docs.langchain.com/oss/python/langchain/tools

## Agents

**Agent = Model + Harness**

The job of a harness: get the model the right context at the right time for the given task.

A harness is everything around that loop: the model, its prompt, its tools, and any middleware that shapes its behavior.


## Invocation

You can invoke an agent with a **message**. Behind the scenes that passes an update to the agent’s **State**. All agents include **a sequence of messages in their state**; to invoke the agent, pass a new message along with a `thread_id` so the agent can persist and resume conversation history

`thread_id` scopes the conversation (message history, checkpoints), while context carries per-run data your tools and middleware read at invocation time. Both are commonly passed together.

## Memory


## Observability


### LangSmith

