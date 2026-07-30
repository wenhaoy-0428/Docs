LangChain is driven by a few core beliefs:

* Large Language Models (LLMs) are great, powerful new technology.
* LLMs are even better when you combine them with external sources of data.LLMs will transform what the applications of the future look like. Specifically, the applications of the future will look more and more agentic.
* It is still very early on in that transformation.
* While it’s easy to build a prototype of those agentic applications, it’s still really hard to build agents that are reliable enough to put into production.


Today developers can choose how they build agents: use **LangChain** for maximum flexibility and control, or **Deep Agents** which allows for similar flexibility and control but comes with *opinionated built-in planning*, filesystem tools, subagents, and context management. Both are built on **LangGraph**. 

## Langchain vs Langgraph

* LangChain create_agent：

  * 一个预制的 ReAct Loop。
  * 模型围绕 `messages`，不断决定是否调用工具，
  * 直到得到最终答案。

* LangGraph：
  * 自己设计业务状态机。
  * 可以有多个阶段、确定性分支、循环、并行、
  * 暂停恢复、人工审批和复杂状态。



## Tools

https://docs.langchain.com/oss/python/langchain/tools



### Tool execution

In LangChain, tools are used by agents (for example via create_agent) and tool error handling is configured through middleware.

For LangGraph workflows, tool execution is handled by `ToolNode`. See `ToolNode` for Graph API usage, including how tools can access the current graph state and run-scoped context.
​
Tool return values
You can choose different return values for your tools:
* Return a string for human-readable results.
* Return an object for structured results the model should parse.
* Return a Command with optional message when you need to write to state.
​


## Agents

**Agent = Model + Harness**

The job of a harness: get the model the right context at the right time for the given task.

A harness is everything around that loop: the model, its prompt, its tools, and any middleware that shapes its behavior.


## Invocation

You can invoke an agent with a **message**. Behind the scenes that passes an update to the agent’s **State**. All agents include **a sequence of messages in their state**; to invoke the agent, pass a new message along with a `thread_id` so the agent can persist and resume conversation history

`thread_id` scopes the conversation (message history, checkpoints), while context carries per-run data your tools and middleware read at invocation time. Both are commonly passed together.



## Memory


### Trim messages

Most LLMs have a maximum supported context window (denominated in tokens).

One way to decide when to truncate messages is to count the tokens in the message history and truncate whenever it approaches that limit. If you’re using LangChain, you can use the trim messages utility and specify the number of tokens to keep from the list, as well as the strategy (e.g., keep the last max_tokens) to use for handling the boundary.

## Context

https://docs.langchain.com/oss/python/concepts/context

The hard part of building agents (or any LLM application) is making them reliable enough. While they may work for a prototype, they often fail in real-world use cases.
​
Why do agents fail?
When agents fail, it’s usually because the LLM call inside the agent took the wrong action / didn’t do what we expected. 

LLMs fail for one of two reasons:

* **The underlying LLM is not capable enough**
* **The “right” context was not passed to the LLM**

> More often than not - it’s actually the second reason that causes agents to not be reliable.

## Observability


### LangSmith

